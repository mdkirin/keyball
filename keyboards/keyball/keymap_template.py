KEYMAP_TEMPLATE = '''
#include QMK_KEYBOARD_H
#include "quantum.h"

// GACS 홈로우 매크로
{home_row_macros}

// Combos
{combo_definitions}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    {layers}
};
// clang-format on

{additional_functions}
'''

CONFIG_TEMPLATE = '''
#pragma once

#ifdef RGBLIGHT_ENABLE
    {rgb_effects}
#endif

{auto_shift_config}

#define TAP_CODE_DELAY 5

#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DEFAULT_LAYER 1

// Combo configuration
#define COMBO_COUNT {combo_count}
#define COMBO_TERM 50
'''

RULES_TEMPLATE = '''
RGBLIGHT_ENABLE = yes
OLED_ENABLE = yes
COMBO_ENABLE = yes
{additional_features}
''' 