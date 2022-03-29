/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */



#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
    BASE,  // default layer
    SYMB,  // symbols
    MDIA,  // media keys
};

enum custom_keycodes {
    VRSN = ML_SAFE_RANGE,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_moonlander(
        KC_GRAVE,         KC_1,       KC_2,    KC_3,           KC_4,    KC_5,    KC_6,                       KC_7,     KC_8,    KC_9,    KC_0,         KC_MINUS,    KC_EQUAL,          KC_BSPACE,
        KC_TAB,           KC_Q,       KC_W,    KC_E,           KC_R,    KC_T,    TG(MDIA),                   TG(SYMB), KC_Y,    KC_U,    KC_I,         KC_O,        KC_P,              KC_BSLS,
        CTL_T(KC_ESCAPE), KC_A,       KC_S,    LT(MDIA, KC_D), KC_F,    KC_G,    KC_HYPR,                 MEH_T(KC_B), KC_H,    KC_J,    KC_K,         KC_L,     LT(SYMB, KC_SCLN), ALT_T(KC_QUOT),
        KC_LSPO,          KC_Z,       KC_X,    KC_C,           KC_V,    KC_B,                                          KC_N,    KC_M,    KC_COMM,      KC_DOT,      KC_SLSH,           KC_RSPC,
        MO(MDIA),      KC_LEFT, A(KC_LSFT), KC_LALT,  GUI_T(KC_LANG2),       KC_HYPR,           HYPR_T(KC_B),       RGUI_T(KC_LANG1),    KC_RALT,      A(KC_RSFT),  KC_RIGHT,          MO(SYMB),
                                            SFT_T(KC_SPC),  CTL_T(KC_TAB), ALT_T(KC_ENT),     ALT_T(KC_SPC),  CTL_T(KC_BSPACE),  SFT_T(KC_ENT)
    ),

    [SYMB] = LAYOUT_moonlander(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,           _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, _______,           _______, KC_PLUS, KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12,
        _______, KC_HASH, KC_DLR,  KC_LBRC, KC_RBRC, KC_GRV,  _______,           _______, KC_MINUS,KC_4,    KC_5,    KC_6,    KC_PLUS, _______,
        _______, KC_PERC, KC_CIRC, KC_LPRN, KC_RPRN, KC_TILD,                             KC_ASTR, KC_1,    KC_2,    KC_3,    KC_BSLS, _______,
        EEP_RST, KC_AMPR, KC_ASTR, _______, _______,         _______,            _______,          KC_0,    KC_DOT,  _______, KC_EQL,  _______,
                                           _______, _______, _______,            _______, _______, _______
    ),

    [MDIA] = LAYOUT_moonlander(
        LED_LEVEL,_______,_______, _______, _______, _______, _______,           _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, RESET,
        _______, _______, _______, _______, _______, _______, _______,           _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______, _______,
        _______, _______, _______, _______, KC_BTN1, KC_BTN2, _______,           _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, KC_MPLY,
        _______, _______, _______, _______, KC_BTN3, _______,                             KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT, _______, _______,
        _______, _______, _______, _______, TOGGLE_LAYER_COLOR, RGB_MOD,         RGB_TOG,          KC_VOLD, KC_VOLU, KC_MUTE, _______, _______,
                                              RGB_VAI, RGB_VAD, RGB_SAD,         RGB_SAI, RGB_HUD, RGB_HUI
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
        case VRSN:
            SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            return false;
        }
    }
    return true;
}
