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
#include "features/auto_click_layer.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT(
    KC_ESC    , KC_Q     , KC_W      , KC_E        , KC_R      , KC_T        ,         KC_Y           , KC_U         , KC_I      , KC_O           , KC_P         , KC_BSPC  ,
    KC_TAB    , KC_A     , KC_S      , KC_D        , LT(2,KC_F),KC_G         ,         KC_H           , KC_J         , KC_K      , KC_L           , KC_LBRC      , KC_RBRC  ,
    KC_LCTL   , KC_Z     , KC_X      , KC_C        , KC_V      , KC_B        ,         KC_N           , KC_M         , KC_COMM   , KC_DOT         , KC_SLSH      , S(KC_MINS)  ,
                KC_LALT  , KC_LGUI   , KC_LSFT     , MO(1)     , LT(3,KC_MINS),        SFT_T(KC_ENT)  , KC_SPC                                , LT(2, KC_GRV)
  ),

  [1] = LAYOUT(
    _______  , KC_1      , KC_2      , KC_3        , KC_4      , KC_5        ,         KC_6           , KC_7         , KC_8      , KC_9           , KC_0         , KC_DEL   ,
    KC_CAPS  , S(KC_1)   , S(KC_2)   , S(KC_3)     , S(KC_4)   , S(KC_5)     ,         KC_LEFT        , KC_DOWN      , KC_UP     , KC_RIGHT       , S(KC_SCLN)   , KC_SCLN  ,
    _______  , S(KC_6)   , S(KC_7)   , S(KC_8)     , S(KC_9)   , S(KC_0)     ,         KC_EQL         , S(KC_EQL)    , KC_BSLS   , KC_QUOT        , S(KC_QUOT)   , KC_INT3  ,
               _______   , _______   , _______     , _______   , _______     ,         SFT_T(KC_LNG1) , GUI_T(KC_LNG2)                            , KC_GRV
  ),

  [2] = LAYOUT(
    _______  , KC_PSLS   , KC_P7     , KC_P8       , KC_P9     , KC_PAST     ,         _______        , LGUI(KC_BSPC), KC_HOME   , KC_END         , _______      , _______  ,
    _______  , KC_PCMM   , KC_P4     , KC_P5       , KC_P6     , KC_PMNS     ,         KC_MS_BTN3     , KC_MS_BTN1   , KC_MS_BTN2, SCRL_MO        , KC_QUOT      , S(KC_2)  ,
    _______  , KC_BSPC   , KC_P1     , KC_P2       , KC_P3     , KC_PPLS     ,         _______        , KC_MS_BTN4   , KC_MS_BTN5, _______        , _______      , _______  ,
               KC_P0     , KC_PDOT   , KC_BSPC     , KC_PEQL   , _______     ,         _______        , _______                                   , _______
  ),

  [3] = LAYOUT(
    RGB_TOG  , KC_F1     , KC_F2     , KC_F3       , KC_F4     , KC_F5       ,         RGB_M_P        , RGB_M_B      , RGB_M_R   , RGB_M_SW        , RGB_M_SN    , RGB_M_K  ,
    RGB_MOD  , KC_F6     , KC_F7     , KC_F8       , KC_F9     , KC_F10      ,         RGB_M_X        , RGB_M_G      , RGB_M_T   , RGB_M_TW        , _______     , _______  ,
    RGB_RMOD , RGB_HUD   , LGUI(KC_W), LSG(KC_T)   , SCRL_DVI  , SCRL_DVD    ,         CPI_D100       , CPI_I100     , _______   , _______         , _______     , KBC_SAVE ,
               _______   , _______   , _______     , _______   , _______     ,         _______        , _______                                    , _______
  ),

  [4] = LAYOUT(
    _______  , _______   , _______   , _______     , _______   , _______     ,         _______        , _______      , _______   , _______         , _______     , _______  ,
    _______  , _______   , _______   , _______     , _______   , _______     ,         _______        , _______      , _______   , _______         , _______     , _______  ,
    _______  , _______   , _______   , _______     , _______   , _______     ,         _______        , _______      , _______   , _______         , _______     , _______  ,
               _______   , _______   , _______     , _______   , _______     ,         _______        , _______                                    , _______
  ),

  [5] = LAYOUT(
    KBC_RST  , CPI_D1K   , CPI_I1K   , SCRL_DVD    , SCRL_DVI  , _______     ,         _______        , LGUI(KC_BSPC), KC_TO_CLICKABLE_INC   , KC_TO_CLICKABLE_DEC         , _______      , _______  ,
    _______  , CPI_D100  , CPI_I100  , _______     , _______   , _______     ,         KC_MS_BTN3     , KC_MS_BTN1   , KC_MS_BTN2, KC_MY_SCRL_V   , SCRL_MO      , _______  ,
    KC_LCTL  , _______   , _______   , _______     , _______   , _______     ,         _______        , KC_MS_BTN4   , KC_MS_BTN5, KC_MY_SCRL_H   , _______      , _______  ,
               KC_LALT   , KC_LGUI   , KC_LSFT     , KBC_SAVE  , _______     ,         _______        , _______                                   , _______
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
            rgblight_sethsv(HSV_MAGENTA);
            break;
        case 3:
            rgblight_sethsv(HSV_TEAL);
            break;
        case 4:
            rgblight_sethsv(HSV_BLACK);
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

    oled_write_P(PSTR("Layer:"), false);
    oled_write(get_u8_str(get_highest_layer(layer_state), ' '), false);
    oled_write_P(PSTR(" MV:"), false);
    oled_write(get_u8_str(mouse_movement, ' '), false);
    oled_write_P(PSTR("/"), false);
    oled_write(get_u8_str(user_config.to_clickable_movement, ' '), false);
}
#endif
