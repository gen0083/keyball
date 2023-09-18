// https://github.com/takashicompany/qmk_firmware/blob/keyball/keyboards/keyball/keyball44/keymaps/takashicompany/keymap.c

enum custom_keycodes {
    KC_MY_BTN1 = KEYBALL_SAFE_RANGE,
    KC_MY_BTN2,
    KC_MY_SCRL_V,
    KC_MY_SCRL_H,
    KC_TO_CLICKABLE_INC,
    KC_TO_CLICKABLE_DEC,
    MY_MOUSE_RANGE,
};

enum click_state {
    NONE = 0,
    WAITING,     // マウスレイヤーが有効になるのを待つ。 Wait for mouse layer to activate.
    CLICKABLE,   // マウスレイヤー有効になりクリック入力が取れる。 Mouse layer is enabled to take click input.
    CLICKING,    // クリック中。 Clicking.
    SCROLLING,   // スクロール中。 Scrolling.
    SCROLLING_H, // horizontal scroll
    SCROLLING_V, // vertical scroll
};

typedef union {
    uint32_t raw;
    struct {
        // int16_t to_clickable_time; // // この秒数(千分の一秒)、WAITING状態ならクリックレイヤーが有効になる。  For this number of seconds (milliseconds), if in WAITING state, the click layer is activated.
        int16_t to_clickable_movement;
    };
} user_config_t;

user_config_t user_config;

enum click_state state;       // 現在のクリック入力受付の状態 Current click input reception status
uint16_t         click_timer; // タイマー。状態に応じて時間で判定する。 Timer. Time to determine the state of the system.

// uint16_t to_clickable_time = 50;   // この秒数(千分の一秒)、WAITING状態ならクリックレイヤーが有効になる。  For this number of seconds (milliseconds), if in WAITING state, the click layer is activated.
uint16_t to_reset_time = 600; // この秒数(千分の一秒)、CLICKABLE状態ならクリックレイヤーが無効になる。 For this number of seconds (milliseconds), the click layer is disabled if in CLICKABLE state.

const uint16_t click_layer = 5; // マウス入力が可能になった際に有効になるレイヤー。Layers enabled when mouse input is enabled

int16_t scroll_mouse_interval_counter; // スクロールの入力をカウントする。　Counting Vertical Scroll Inputs
int16_t scroll_threshold = 50; // この閾値を超える度に垂直スクロールが実行される。 Vertical scrolling is performed each time this threshold is exceeded.

int16_t after_click_lock_movement = 0; // クリック入力後の移動量を測定する変数。 Variable that measures the amount of movement after a click input.

int16_t mouse_record_threshold = 30; // ポインターの動きを一時的に記録するフレーム数。 Number of frames in which the pointer movement is temporarily recorded.
int16_t mouse_move_count_ratio = 5;  // ポインターの動きを再生する際の移動フレームの係数。 The coefficient of the moving frame when replaying the pointer movement.

int16_t mouse_movement;

void eeconfig_init_user(void) {
    user_config.raw                   = 0;
    user_config.to_clickable_movement = 50; // user_config.to_clickable_time = 10;
    eeconfig_update_user(user_config.raw);
}

void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
}

// クリック用のレイヤーを有効にする。　Enable layers for clicks
void enable_click_layer(void) {
    layer_on(click_layer);
    click_timer = timer_read();
    state       = CLICKABLE;
}

// クリック用のレイヤーを無効にする。 Disable layers for clicks.
void disable_click_layer(void) {
    state = NONE;
    layer_off(click_layer);
    scroll_mouse_interval_counter = 0;
    scroll_mouse_interval_counter = 0;
    mouse_movement = 0;
}

// 自前の絶対数を返す関数。 Functions that return absolute numbers.
int16_t my_abs(int16_t num) {
    if (num < 0) {
        num = -num;
    }

    return num;
}

// 自前の符号を返す関数。 Function to return the sign.
int16_t mmouse_move_y_sign(int16_t num) {
    if (num < 0) {
        return -1;
    }

    return 1;
}

// 現在クリックが可能な状態か。 Is it currently clickable?
bool is_clickable_mode(void) {
    return state == CLICKABLE || state == CLICKING || state == SCROLLING_V || state == SCROLLING_H;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint16_t my_timer;

    switch (keycode) {
        // defaultのマウスボタンを扱えるようにする
        case KC_MS_BTN1:
        case KC_MS_BTN2:
        case KC_MS_BTN3:
        case KC_MS_BTN4:
        case KC_MS_BTN5: {
            report_mouse_t currentReport = pointing_device_get_report();

            // どこのビットを対象にするか。 Which bits are to be targeted?
            uint8_t btn = 1 << (keycode - KC_MS_BTN1);

            if (record->event.pressed) {
                // ビットORは演算子の左辺と右辺の同じ位置にあるビットを比較して、両方のビットのどちらかが「1」の場合に「1」にします。
                // Bit OR compares bits in the same position on the left and right sides of the operator and sets them to "1" if either of both bits is "1".
                currentReport.buttons |= btn;
                state                     = CLICKING;
                after_click_lock_movement = 30;
            } else {
                // ビットANDは演算子の左辺と右辺の同じ位置にあるビットを比較して、両方のビットが共に「1」の場合だけ「1」にします。
                // Bit AND compares the bits in the same position on the left and right sides of the operator and sets them to "1" only if both bits are "1" together.
                currentReport.buttons &= ~btn;
                enable_click_layer();
            }

            pointing_device_set_report(currentReport);
            pointing_device_send();
            return true;
        }

        // scroll button
        // 独自コードはtap-holdが設定できないので独自にハンドリング
        case KC_MY_SCRL_V:
            if (record->event.pressed) {
                my_timer = timer_read();
                state = SCROLLING_V;
            } else {
                if (timer_elapsed(my_timer) < TAPPING_TERM) {
                     disable_click_layer();
                     tap_code(KC_L);
                } else {
                     enable_click_layer();
                }
            }
            return false;
        case KC_MY_SCRL_H:
            if (record->event.pressed) {
                my_timer = timer_read();
                state = SCROLLING_H;
            } else {
                if (timer_elapsed(my_timer) < TAPPING_TERM) {
                     disable_click_layer();
                     tap_code(KC_DOT);
                } else {
                    enable_click_layer();
                }
            }
            return false;

        case KC_TO_CLICKABLE_INC:
            if (record->event.pressed) {
                user_config.to_clickable_movement += 5; // user_config.to_clickable_time += 10;
                eeconfig_update_user(user_config.raw);
            }
            return false;

        case KC_TO_CLICKABLE_DEC:
            if (record->event.pressed) {
                user_config.to_clickable_movement -= 5; // user_config.to_clickable_time -= 10;

                if (user_config.to_clickable_movement < 5) {
                    user_config.to_clickable_movement = 5;
                }

                eeconfig_update_user(user_config.raw);
            }
            return false;

        case KC_LSFT:
        case KC_LALT:
        case KC_LGUI:
            // modifier keyはそのまま扱いたい(trueを返すとデフォルトのキーコードの動作）
            return true;

        case LGUI(KC_X):
        case LGUI(KC_C):
        case LGUI(KC_V):
        case LGUI(KC_Z):
             // cut/copy/paste/undoのショートカットキーはマウス操作と同時に使うことが多いのでそのまま処理する
        case LGUI(KC_W):
        case LSG(KC_T):
            // tab close/re-openもよく使うので除外する
             return true;

        // スクロールの挙動を理想的にする(スクロール時は先にボタンを押してからトラックボールを動かすことがあるのでその調整）
        case LT(5,KC_L):
            if (!record->tap.count && record->event.pressed) {
                enable_click_layer();
                state = SCROLLING_V;
                return false;
            } else if (!record->tap.count) {
                enable_click_layer();
                return false;
            } else {
                return true;
            }
        case LT(5,KC_DOT):
            if (!record->tap.count && record->event.pressed) {
                enable_click_layer();
                state = SCROLLING_H;
                return false;
            } else if (!record->tap.count) {
                enable_click_layer();
                return false;
            } else {
                return true;
            }
        
        case KC_ESC:
            // click layer on時にESC押した際はESC入力せずlayer offだけする
            disable_click_layer();
            return false;

        default:
            if (record->event.pressed) {
                disable_click_layer();
            }
    }

    return true;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    int16_t current_x = mouse_report.x;
    int16_t current_y = mouse_report.y;
    int16_t current_h = 0;
    int16_t current_v = 0;

    if (current_x != 0 || current_y != 0) {
        switch (state) {
            case CLICKABLE:
                click_timer = timer_read();
                break;

            case CLICKING:
                after_click_lock_movement -= my_abs(current_x) + my_abs(current_y);

                if (after_click_lock_movement > 0) {
                    current_x = 0;
                    current_y = 0;
                }

                break;

            case SCROLLING:
                break;

            case SCROLLING_V: {
                int8_t rep_v = 0;
                int8_t rep_h = 0;
                scroll_mouse_interval_counter += current_y;
                while (my_abs(scroll_mouse_interval_counter) > scroll_threshold) {
                    if (scroll_mouse_interval_counter < 0) {
                        scroll_mouse_interval_counter += scroll_threshold;
                        rep_v += scroll_threshold;
                    } else {
                        scroll_mouse_interval_counter -= scroll_threshold;
                        rep_v -= scroll_threshold;
                    }
                }
                current_h = rep_h / scroll_threshold;
                current_v = rep_v / scroll_threshold;
                current_x = 0;
                current_y = 0;
            } break;

            case SCROLLING_H: {
                int8_t rep_h = 0;
                int8_t rep_v = 0;
                scroll_mouse_interval_counter += current_x;

                while (my_abs(scroll_mouse_interval_counter) > scroll_threshold) {
                    if (scroll_mouse_interval_counter < 0) {
                        scroll_mouse_interval_counter += scroll_threshold;
                        rep_h -= scroll_threshold;
                    } else {
                        scroll_mouse_interval_counter -= scroll_threshold;
                        rep_h += scroll_threshold;
                    }
                }
                current_h = rep_h / scroll_threshold;
                current_v = -rep_v / scroll_threshold;
                current_x = 0;
                current_y = 0;
            } break;

            case WAITING:
                enable_click_layer();
                break;

            default:
                click_timer    = timer_read();
                state          = WAITING;
                mouse_movement = 0;
        }
    } else {
        switch (state) {
            case CLICKING:
            case SCROLLING:
            case SCROLLING_H:
            case SCROLLING_V:

                break;

            case CLICKABLE:
                if (timer_elapsed(click_timer) > to_reset_time) {
                    disable_click_layer();
                }
                break;

            case WAITING:
                if (timer_elapsed(click_timer) > 50) {
                    mouse_movement = 0;
                    state          = NONE;
                }
                break;

            default:
                mouse_movement = 0;
                state          = NONE;
        }
    }

    mouse_report.x = current_x;
    mouse_report.y = current_y;
    mouse_report.h = current_h;
    mouse_report.v = current_v;

    return mouse_report;
}