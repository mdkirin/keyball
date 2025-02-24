/*
This is the c configuration file for the keymap

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

#pragma once

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL+6  // 기본 모드를 레인보우 스월 6으로 설정
#    define RGBLIGHT_DEFAULT_SPD 10  // 기본 속도 설정
#    define RGBLIGHT_LIMIT_VAL 125  // LED 밝기 제한 (전력 부족 문제 해결)
#    define RGBLIGHT_HUE_STEP 8  // 색상 변경 단계
#    define RGBLIGHT_SAT_STEP 8  // 채도 변경 단계
#    define RGBLIGHT_VAL_STEP 8  // 밝기 변경 단계
#endif

#define TAP_CODE_DELAY 5

#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DEFAULT_LAYER 1

// 콤보 기능 활성화
#define COMBO_ENABLE
#define COMBO_COUNT 8  // 콤보 수 수정
#define COMBO_TERM 50  // 콤보 입력 시간 (ms) 