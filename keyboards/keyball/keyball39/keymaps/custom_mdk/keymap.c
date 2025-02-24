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

// 매크로 정의
enum custom_keycodes {
    MACRO_1 = SAFE_RANGE,  // tjfleks22!
    MACRO_2,               // dltmdghks80!
    MACRO_3                // 7748
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MACRO_1:
            if (record->event.pressed) {
                SEND_STRING("tjfleks22!");
            }
            return false;
        case MACRO_2:
            if (record->event.pressed) {
                SEND_STRING("dltmdghks80!");
            }
            return false;
        case MACRO_3:
            if (record->event.pressed) {
                SEND_STRING(SS_DELAY(50)"7"SS_DELAY(50)"7"SS_DELAY(50)"4"SS_DELAY(50)"8");
            }
            return false;
        default:
            return true;
    }
}

// 콤보 정의
enum combo_events {
    COMBO_ESC,
    COMBO_TAB,
    COMBO_DEL,
    COMBO_LBRACKET,
    COMBO_RBRACKET,
    COMBO_SEMICOLON,
    COMBO_QUOTE,
    COMBO_MINUS,
    COMBO_CUT,    // ZX for cut
    COMBO_COPY,   // XC for copy
    COMBO_PASTE,  // CV for paste
    COMBO_BSLS,   // OP for backslash
    COMBO_MACRO1, // WER for tjfleks22!
    COMBO_MACRO2, // UIO for dltmdghks80!
    COMBO_MACRO3  // JKL for 7748
};

const uint16_t PROGMEM esc_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {LGUI_T(KC_A), LALT_T(KC_S), COMBO_END};
const uint16_t PROGMEM del_combo[] = {LCTL_T(KC_D), KC_E, COMBO_END};
const uint16_t PROGMEM lbracket_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM rbracket_combo[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM semicolon_combo[] = {RSFT_T(KC_J), RCTL_T(KC_K), COMBO_END};
const uint16_t PROGMEM quote_combo[] = {RCTL_T(KC_K), RALT_T(KC_L), COMBO_END};
const uint16_t PROGMEM minus_combo[] = {RALT_T(KC_L), RGUI_T(KC_ENT), COMBO_END};
const uint16_t PROGMEM cut_combo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM copy_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM bsls_combo[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM macro1_combo[] = {KC_W, KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM macro2_combo[] = {KC_U, KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM macro3_combo[] = {RSFT_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), COMBO_END};

combo_t key_combos[] = {
    [COMBO_ESC] = COMBO(esc_combo, KC_ESC),
    [COMBO_TAB] = COMBO(tab_combo, KC_TAB),
    [COMBO_DEL] = COMBO(del_combo, KC_DEL),
    [COMBO_LBRACKET] = COMBO(lbracket_combo, KC_LBRC),
    [COMBO_RBRACKET] = COMBO(rbracket_combo, KC_RBRC),
    [COMBO_SEMICOLON] = COMBO(semicolon_combo, KC_SCLN),
    [COMBO_QUOTE] = COMBO(quote_combo, KC_QUOT),
    [COMBO_MINUS] = COMBO(minus_combo, KC_MINS),
    [COMBO_CUT] = COMBO(cut_combo, C(KC_X)),
    [COMBO_COPY] = COMBO(copy_combo, C(KC_C)),
    [COMBO_PASTE] = COMBO(paste_combo, C(KC_V)),
    [COMBO_BSLS] = COMBO(bsls_combo, KC_BSLS),
    [COMBO_MACRO1] = COMBO(macro1_combo, MACRO_1),
    [COMBO_MACRO2] = COMBO(macro2_combo, MACRO_2),
    [COMBO_MACRO3] = COMBO(macro3_combo, MACRO_3)
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Base Layer 
  [0] = LAYOUT_universal(
    //,---------------+---------------+---------------+---------------+---------------.                                   ,---------------+---------------+---------------+---------------+---------------.
         KC_Q        , KC_W          , KC_E          , KC_R          , KC_T          ,                                  KC_Y          , KC_U          , KC_I          , KC_O          , KC_P          ,
    //|---------------+---------------+---------------+---------------+---------------|                                   |---------------+---------------+---------------+---------------+---------------|
         LGUI_T(KC_A), LALT_T(KC_S)  , LCTL_T(KC_D)  , LSFT_T(KC_F)  , KC_G          ,                                  KC_H          , RSFT_T(KC_J)  , RCTL_T(KC_K)  , RALT_T(KC_L)  , KC_ENT    ,
    //|---------------+---------------+---------------+---------------+---------------|                                   |---------------+---------------+---------------+---------------+---------------|
         KC_Z        , KC_X          , KC_C          , KC_V          , KC_B          ,                                  KC_N          , KC_M          , LT(3,KC_COMM) , KC_DOT        , KC_SLSH       ,
    //|---------------+---------------+---------------+---------------+---------------+---------------. ,---------------+---------------+---------------+---------------+---------------+---------------|
         KC_LCTL     , KC_LGUI       , KC_LALT       ,LT(1,KC_ENT)  ,LT(2,KC_SPC)   ,LT(3,KC_LNG1)  , LT(2,KC_BSPC)  ,LT(1,KC_SPC)  , _______       , _______       , _______       , MO(4)
    //`---------------+---------------+---------------+---------------+---------------+---------------' `---------------+---------------+---------------+---------------+---------------+---------------'
  ),

  // Function & Navigation Layer
  [1] = LAYOUT_universal(
    //,---------------+---------------+---------------+---------------+---------------.                                   ,---------------+---------------+---------------+---------------+---------------.
         KC_F1       , KC_F2         , KC_F3         , KC_F4         , S(KC_9)       ,                                  S(KC_0)       , KC_HOME       , KC_UP         , KC_END       , KC_P          ,
    //|---------------+---------------+---------------+---------------+---------------|                                   |---------------+---------------+---------------+---------------+---------------|
         KC_F5       , KC_F6         , KC_F7         , KC_F8         , KC_MINS       ,                                  S(KC_EQL)     ,  KC_LEFT      ,   KC_DOWN     ,   KC_RGHT     , KC_ENT        ,
    //|---------------+---------------+---------------+---------------+---------------|                                   |---------------+---------------+---------------+---------------+---------------|
         KC_F9       , KC_F10        , KC_F11        , KC_F12        , _______       ,                                  _______       ,  KC_BTN1      ,    _______    ,   KC_BTN2     , KC_SLSH       ,
    //|---------------+---------------+---------------+---------------+---------------+---------------. ,---------------+---------------+---------------+---------------+---------------+---------------|
         KC_F13      , KC_F14        , KC_F15        , _______       , KC_BTN1       , KC_BTN2       , _______        , _______       , _______       , _______       , _______       , _______
    //`---------------+---------------+---------------+---------------+---------------+---------------' `---------------+---------------+---------------+---------------+---------------+---------------'
  ),

  // Numpad Layer
  [2] = LAYOUT_universal(
    //,---------------+---------------+---------------+---------------+---------------.                                   ,---------------+---------------+---------------+---------------+---------------.
         _______      , KC_7          , KC_8          , KC_9          , _______       ,                                  S(KC_EQL)     , KC_7          , KC_8          , KC_9          , KC_P          ,
    //|---------------+---------------+---------------+---------------+---------------|                                   |---------------+---------------+---------------+---------------+---------------|
         _______      , KC_4          , KC_5          , KC_6          , _______       ,                                  KC_MINS       , KC_4          , KC_5          , KC_6          , KC_ENT        ,
    //|---------------+---------------+---------------+---------------+---------------|                                   |---------------+---------------+---------------+---------------+---------------|
         KC_DOT       , KC_1          , KC_2          , KC_3          , _______       ,                                  KC_DOT        , KC_1          , KC_2          , KC_3          , KC_SLSH       ,
    //|---------------+---------------+---------------+---------------+---------------+---------------. ,---------------+---------------+---------------+---------------+---------------+---------------|
         KC_0         , KC_DOT        , _______       , _______       , _______       , _______       , _______           , KC_0       , _______      , _______       , _______       , _______
    //`---------------+---------------+---------------+---------------+---------------+---------------' `---------------+---------------+---------------+---------------+---------------+---------------'
  ),

  // RGB & Mouse Control Layer
  [3] = LAYOUT_universal(
    //,---------------+---------------+---------------+---------------+---------------.                                   ,---------------+---------------+---------------+---------------+---------------.
         _______      , _______       , _______       , _______       , _______       ,                                  _______       , _______       , _______       , _______       , _______       ,
    //|---------------+---------------+---------------+---------------+---------------|                                   |---------------+---------------+---------------+---------------+---------------|
         _______      , _______       , _______       , _______       , _______       ,                                  _______       , _______       , _______       , _______       , _______       ,
    //|---------------+---------------+---------------+---------------+---------------|                                   |---------------+---------------+---------------+---------------+---------------|
         _______      , _______       , _______       , _______       , _______       ,                                  _______       , KC_BTN1       , KC_BTN3       , KC_BTN2       , _______       ,
    //|---------------+---------------+---------------+---------------+---------------+---------------. ,---------------+---------------+---------------+---------------+---------------+---------------|
         C(S(KC_LEFT)), _______       , _______       , _______       , _______       , _______       , KC_DEL        , C(S(KC_LEFT))       , _______       , _______       , _______       , C(S(KC_RGHT))
    //`---------------+---------------+---------------+---------------+---------------+---------------' `---------------+---------------+---------------+---------------+---------------+---------------'
  ),

  // Media & Extra Layer
  [4] = LAYOUT_universal(
    //,---------------+---------------+---------------+---------------+---------------.                                   ,---------------+---------------+---------------+---------------+---------------.
         RGB_TOG      , _______       , _______       , _______       , QK_BOOT       ,                                  AML_TO        , _______       , _______       , _______       , SSNP_FRE      ,
    //|---------------+---------------+---------------+---------------+---------------|                                   |---------------+---------------+---------------+---------------+---------------|
         RGB_MOD      , RGB_HUI       , RGB_SAI       , RGB_VAI       , KC_VOLU       ,                                  AML_I50       , CPI_I1K       , CPI_I100      , SCRL_DVI      , SSNP_HOR      ,
    //|---------------+---------------+---------------+---------------+---------------|                                   |---------------+---------------+---------------+---------------+---------------|
         RGB_RMOD     , RGB_HUD       , RGB_SAD       , RGB_VAD       , KC_VOLD       ,                                  AML_D50       , CPI_D1K       , CPI_D100      , SCRL_DVD      , SSNP_VRT      ,
    //|---------------+---------------+---------------+---------------+---------------+---------------. ,---------------+---------------+---------------+---------------+---------------+---------------|
         KBC_SAVE      , _______       , _______       , KC_MPRV       , KC_MPLY       , KC_MNXT       , KC_VOLD       , KC_VOLU       , _______       , _______       , _______       , _______
    //`---------------+---------------+---------------+---------------+---------------+---------------' `---------------+---------------+---------------+---------------+---------------+---------------'
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE
#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif 