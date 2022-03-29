#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
    BASE, // default layer
    SYMB, // symbols
    MDIA,  // media keys
};

enum custom_keycodes {
#ifdef ORYX_CONFIGURATOR
  VRSN = EZ_SAFE_RANGE,
#else
  VRSN = SAFE_RANGE,
#endif
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer */
[BASE] = LAYOUT_ergodox_pretty(
  // left hand
  KC_GRAVE,         KC_1,        KC_2,          KC_3,    KC_4,    KC_5,    KC_6,              KC_7,      KC_8,    KC_9,    KC_0,    KC_MINS,           KC_EQL,         KC_BSPC,
  KC_TAB,           KC_Q,        KC_W,          KC_E,    KC_R,    KC_T,    TG(MDIA),          TG(SYMB),  KC_Y,    KC_U,    KC_I,    KC_O,              KC_P,           KC_BSLS,
  CTL_T(KC_ESCAPE), KC_A,        KC_S, LT(MDIA,KC_D),    KC_F,    KC_G,                                  KC_H,    KC_J,    KC_K,    KC_L,  LT(SYMB, KC_SCLN),   ALT_T(KC_QUOT),
  KC_LSPO,          KC_Z,        KC_X,          KC_C,    KC_V,    KC_B,    ALL_T(KC_NO),    MEH_T(KC_B), KC_N,    KC_M,    KC_COMM, KC_DOT,            KC_SLSH,        KC_RSPC,
  MO(MDIA),         KC_LEFT,     LALT(KC_LSFT), KC_LALT, GUI_T(KC_LANG2),                                           GUI_T(KC_LANG1),   KC_RALT, A(KC_RSFT), KC_RIGHT, MO(SYMB),
                                                 ALL_T(KC_NO), KC_LALT,                KC_RALT, ALL_T(KC_NO),
                                                                KC_LGUI,                 KC_RGUI,
                                    SFT_T(KC_SPACE), CTL_T(KC_TAB), KC_ESC,                  KC_ESC, CTL_T(KC_BSPC), SFT_T(KC_ENT)
 /*
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
),
/* Keymap 1: Symbol Layer */
[SYMB] = LAYOUT_ergodox_pretty(
  // left hand
  VRSN,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,     _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, _______,     _______, KC_PLUS, KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12,
  _______, KC_HASH, KC_DLR,  KC_LBRC, KC_RBRC, KC_GRV,                        KC_MINS, KC_4,    KC_5,    KC_6,    KC_PLUS, _______,
  _______, KC_PERC, KC_CIRC, KC_LPRN, KC_RPRN, KC_TILD, _______,     _______, KC_ASTR, KC_1,    KC_2,    KC_3,    KC_BSLS, _______,
  EEP_RST, KC_AMPR, KC_ASTR, _______, _______,                                         KC_0,    KC_DOT,  KC_EQL,  KC_ENT,  _______,
                                               _______, _______,     _______, _______,
                                                        _______,     _______,
                                      _______, _______, _______,     _______, _______, _______
),
/* Keymap 2: Media and mouse keys */
[MDIA] = LAYOUT_ergodox_pretty(
  // left hand
  _______, _______, _______, _______, _______, _______, _______,     _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, RESET,
  _______, _______, _______, _______, _______, _______, _______,     _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______, _______,
  _______, _______, _______, _______, KC_BTN1, KC_BTN2,                       KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, KC_MPLY,
  _______, _______, _______, _______, KC_BTN3, _______, _______,     _______, KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT, _______, _______,
  _______, _______, _______, _______, _______,                                         KC_VOLD, KC_VOLU, KC_MUTE, _______, _______,

                                               _______, _______,     _______, _______,
                                                        _______,     _______,
                                      _______, _______, _______,     _______, _______, _______
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case VRSN:
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        return false;
      #ifdef RGBLIGHT_ENABLE
      case RGB_SLD:
        rgblight_mode(1);
        return false;
      #endif
    }
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = get_highest_layer(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
        #endif
        break;
      default:
        break;
    }

  return state;
};
