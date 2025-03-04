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

// 콤보 정의
enum combo_events {
  QW_ESC,
  AS_TAB,
  DE_DEL,
  UI_LBRACKET,
  IO_RBRACKET,
  OP_BSLASH,
  JK_SEMICOLON,
  KL_QUOTE,
  MC_COPY,
  CD_PASTE,
  WER_MACRO1,
  UIO_MACRO2,
  ZXC_MACRO3,
  COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

// 콤보 키 조합 정의 - mt(), lt() 특수 매핑 적용
const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM as_combo[] = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM de_combo[] = {KC_D, KC_E, COMBO_END};
const uint16_t PROGMEM ui_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM io_combo[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM op_combo[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {MT(MOD_RSFT,KC_J), KC_K, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM mc_combo[] = {KC_M, LT(1,KC_COMM), COMBO_END};
const uint16_t PROGMEM cd_combo[] = {LT(1,KC_COMM), KC_DOT, COMBO_END};
const uint16_t PROGMEM wer_combo[] = {KC_W, KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM uio_combo[] = {KC_U, KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM zxc_combo[] = {KC_Z, KC_X, KC_C, COMBO_END};

// 매크로 정의
enum custom_keycodes {
  MACRO1 = SAFE_RANGE,
  MACRO2,
  MACRO3
};

// 콤보 테이블
combo_t key_combos[] = {
  [QW_ESC] = COMBO(qw_combo, KC_ESC),
  [AS_TAB] = COMBO(as_combo, KC_TAB),
  [DE_DEL] = COMBO(de_combo, KC_DEL),
  [UI_LBRACKET] = COMBO(ui_combo, KC_LBRC),
  [IO_RBRACKET] = COMBO(io_combo, KC_RBRC),
  [OP_BSLASH] = COMBO(op_combo, KC_BSLS),
  [JK_SEMICOLON] = COMBO(jk_combo, KC_SCLN),
  [KL_QUOTE] = COMBO(kl_combo, KC_QUOT),
  [MC_COPY] = COMBO(mc_combo, C(KC_C)),
  [CD_PASTE] = COMBO(cd_combo, C(KC_V)),
  [WER_MACRO1] = COMBO(wer_combo, MACRO1),
  [UIO_MACRO2] = COMBO(uio_combo, MACRO2),
  [ZXC_MACRO3] = COMBO(zxc_combo, MACRO3)
};

// 매크로 처리 함수
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MACRO1:
      if (record->event.pressed) {
        SEND_STRING("tjfleks22!");
      }
      return false;
    case MACRO2:
      if (record->event.pressed) {
        SEND_STRING("dltmdghks80!");
      }
      return false;
    case MACRO3:
      if (record->event.pressed) {
        // 실제로 7, 7, 4, 8 키를 누르는 것처럼 에뮬레이션
        tap_code(KC_7);
        wait_ms(100); // 키 사이에 약간의 지연을 줌
        tap_code(KC_7);
        wait_ms(100);
        tap_code(KC_4);
        wait_ms(100);
        tap_code(KC_8);
      }
      return false;
    default:
      return true;
  }
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // keymap for default
    [0] = LAYOUT_universal(
        KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
        KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , MT(MOD_RSFT,KC_J)     , KC_K     , KC_L     , KC_ENT  ,
        KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , LT(1,KC_COMM)  , KC_DOT   , LT(3,KC_SLSH)  ,
        KC_LCTL  , KC_LGUI  , KC_LALT  , LT(1,KC_ENT) , LT(2,KC_SPC), LT(3,KC_LNG1), LT(2,KC_BSPC), LT(1,KC_SPC), _______, _______, _______, MO(4)
    ),

    [1] = LAYOUT_universal(
        KC_F1    , KC_F2    , KC_F3    , KC_F4    , S(KC_9)  ,                            S(KC_0)    , KC_HOME   , KC_UP    , KC_END   , _______   ,
        KC_F5    , KC_F6    , KC_F7    , KC_F8    , S(KC_EQUAL),                          KC_MINUS   , KC_LEFT   , KC_DOWN   , KC_RIGHT   , _______   ,
        KC_F9    , KC_F10   , KC_F11   , KC_F12   , KC_F13   ,                           _______   , KC_BTN1   , _______   , KC_BTN2   , SCRL_MO  ,
        _______  , _______  , _______  , _______  , _______  , _______  ,      _______    , _______   , _______  , _______  , _______  , _______ 
    ),

    [2] = LAYOUT_universal(
        _______  , C(KC_W)  , _______  , _______  , _______  ,                            S(KC_EQUAL)   , KC_7  , KC_8  , KC_9  , KC_BSPC  ,
        C(KC_A)  , C(KC_S)  , _______  , _______  , _______  ,                            KC_MINUS   , KC_4  , KC_5  , KC_6  , KC_QUOT  ,
        C(KC_Z)  , C(KC_X)  , C(KC_C)  , C(KC_V)  , _______  ,                            KC_DOT, KC_1  , KC_2  , KC_3  , _______  ,
        _______  , _______  , _______  , _______  , _______  , KC_DEL  ,       _______  , KC_0  , _______  , _______  , _______  , _______
    ),

    [3] = LAYOUT_universal(
        S(KC_Q)  , S(KC_W)  , S(KC_E)  , S(KC_R)  , S(KC_T)  ,                            S(KC_Y)  , S(KC_U)  , S(KC_I)  , S(KC_O)  , S(KC_P)  ,
        S(KC_A)  , S(KC_S)  , S(KC_D)  , S(KC_F)  , S(KC_G)  ,                            S(KC_H)  , S(KC_J)  , S(KC_K)  , S(KC_L)  , KC_LNG1  ,
        S(KC_Z)  , S(KC_X)  , S(KC_C)  , S(KC_V)  , S(KC_B)  ,                            S(KC_N)  , S(KC_M)  , S(KC_COMM) , S(KC_DOT) , S(KC_SLSH) ,
        _______  , _______  , _______  , KC_LNG1  , KC_SPC   , _______  ,     KC_DEL  , KC_LNG1   , _______  , _______  , _______  , _______
    ),
 
    [4] = LAYOUT_universal(
        RGB_TOG  , _______  , _______  , _______  , QK_BOOT  ,                            AML_TO    , _______  , _______  , _______  , SSNP_FRE ,
        RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  ,                            AML_I50   , _______  , CPI_I100 , SCRL_DVI , SSNP_VRT ,
        RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  ,                            AML_D50   , _______  , CPI_D100 , SCRL_DVD , SSNP_HOR ,
        KBC_SAVE  , _______  , _______  , KC_MPRV  , KC_MPLY  , KC_MNXT  ,      KC_VOLD  , KC_VOLU  , _______  , _______  , _______  , _______
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
