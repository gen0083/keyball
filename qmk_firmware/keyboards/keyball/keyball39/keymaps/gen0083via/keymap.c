/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"
#include "lib/features/auto_click_layer.h"
#include "tap_customize.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT(
    KC_Q     , KC_W     , KC_E     , KC_R     , LT(6,KC_T)     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , KC_S     , KC_D     , LT(3,KC_F)     , KC_G     ,                            KC_H     , LT(4,KC_J)     , KC_K     , KC_L     , KC_QUOT  ,
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  ,
    KC_LCTL  , MT(MOD_LALT,KC_BSPC) , KC_LGUI  , KC_LSFT  , MO(1) , LT(2,KC_MINS),   KC_ENT, KC_SPACE,                           KC_UNDS
  ),

  // 記号・シフトで入力される記号
  [1] = LAYOUT(
    KC_1   , KC_2 , KC_3  , KC_4  , KC_5  ,                            KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,
    S(KC_1)   , S(KC_2) , S(KC_3)  , S(KC_4)  , S(KC_5)  ,                            KC_LBRC  , KC_RBRC  , S(KC_LBRC)  , S(KC_RBRC)  , KC_GRV  ,
    S(KC_6)   , S(KC_7) , S(KC_8)  , S(KC_9)  , S(KC_0)  ,                            KC_EQUAL  , S(KC_EQUAL)  , KC_COLN, KC_SCLN , S(KC_GRV),
    _______   , _______, _______  , _______  , _______  , _______  ,      KC_LANG1  , KC_LANG2  ,                      KC_INT3
  ),

  // 記号・操作
  [2] = LAYOUT(
    KC_ESC   , _______ , _______     , _______     , C(G(KC_T))  ,                            _______  , _______ , _______  , KC_DEL  , KC_BSPC  ,
    KC_TAB   , C(KC_TAB) , C(S(KC_TAB)) , SGUI(KC_A)  , _______ ,                            _______  , _______ , _______  , KC_GRV  , S(KC_GRV)  ,
    KC_CAPS   , _______ , _______  , _______   , _______ ,                           _______  , _______ , _______  , KC_BSLS  , S(KC_BSLS)  ,
    _______   , _______  , _______   , _______  , _______  , _______  ,      KC_INT4   , KC_INT5 ,                                  KC_INT3
  ),

  // 矢印
  [3] = LAYOUT(
    _______   , _______    , _______     , _______     , _______  ,                            LGUI(KC_LEFT)  , KC_HOME  , KC_END , LGUI(KC_RGHT)  , _______  ,
    _______   , KC_ESC    , KC_BSPC     , _______ , _______ ,                            KC_LEFT  , KC_DOWN  , KC_UP  , KC_RIGHT  , KC_LSFT  ,
    _______   , _______    , _______     , _______     , _______ ,                            LALT(KC_LEFT)  , LALT(KC_DOWN)  , LALT(KC_UP)  , LALT(KC_RIGHT)  , _______  ,
    _______   , _______    , _______ , _______  , _______  , _______  ,      KC_ENT   , KC_BSPC  ,                                  _______
  ),
  // テンキー
  [4] = LAYOUT(
    _______   , KC_7    , KC_8     , KC_9     , KC_BSPC  ,                           _______  , _______  , _______ , _______  , _______  ,
    _______   , KC_4    , KC_5     , KC_6     , KC_PMNS ,                            _______  , _______  , _______ , _______  , _______  ,
    KC_PAST   , KC_1    , KC_2     , KC_3     , KC_PPLS ,                            _______  , _______  , _______ , _______  , _______  ,
    KC_PSLS   , KC_0    , KC_DOT   , KC_PEQL  , KC_ENT  , _______  ,      KC_BSPC  , _______  ,                                  _______
  ),

  // Mouse
  [5] = LAYOUT(
    KC_ESC   , _______ , _______  , _______  , _______  ,                            _______  , LGUI(KC_BSPC)  , KC_TO_CLICKABLE_INC , KC_TO_CLICKABLE_DEC, _______  ,
    KC_TAB   , _______ , _______  , _______  , _______  ,                            LSG(KC_T)  , KC_MS_BTN1   , KC_MS_BTN2, KC_MY_SCRL_V , _______  ,
    _______   , _______ , _______  , _______  , _______  ,                            LGUI(KC_W) , KC_MS_BTN4   , KC_MS_BTN5, KC_MY_SCRL_H, _______  ,
    KC_LCTL  , KC_LALT   , KC_LGUI  , KC_LSFT  , _______  , _______  ,      _______   , _______  ,                                           _______
  ),

  // Config
  [6] = LAYOUT(
    RGB_TOG  , _______  , _______  , _______  ,  _______  ,                           RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  ,  SCRL_DVI ,                           RGB_M_K  , RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  ,  SCRL_DVD ,                           CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE ,
    RESET    , KBC_RST  , _______  , _______  ,  _______  , _______  ,     _______   , KBC_RST ,                                  RESET
  ),

  [7] = LAYOUT(
    _______   , _______ , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______   , _______ , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______   , _______ , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______   , _______ , _______  , _______  , _______  , _______  ,      _______  , _______  ,                                  _______
  ),

};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    //    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    uint8_t layer = biton32(state);
    switch (layer) {
        case 1:
            rgblight_sethsv(HSV_CORAL);
            break;
        case 2:
            rgblight_sethsv(HSV_GOLD);
            break;
        case 3:
            rgblight_sethsv(HSV_TEAL);
            break;
        case 4:
            rgblight_sethsv(HSV_BLACK);
            break;
        case 5:
            rgblight_sethsv(HSV_MAGENTA);
            break;
        default:
            rgblight_sethsv(HSV_WHITE);
    }

    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();

    oled_write_P(PSTR("L:"), false);
    oled_write(get_u8_str(get_highest_layer(layer_state), ' '), false);
    oled_write_P(PSTR("/"), false);
    oled_write(get_u16_str(user_config.to_clickable_time, ' '), false);
}
#endif
