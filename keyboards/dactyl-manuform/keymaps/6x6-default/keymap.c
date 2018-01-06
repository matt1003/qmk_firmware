#include "dactyl-manuform.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define _QWERTY 0
#define _NUM 1
#define _SYM 2

/*              Thumb Cluster Mapping
 *         +---+ +---+        +---+ +---+
 *         | 6 | | 1 |        | 6 | | 1 |
 *   +---+ +---+ +---+        +---+ +---+ +---+
 *   |   | |   | | 5 |        | 2 | |   | |   |
 *   | 4 | | 3 | +---+        +---+ | 4 | | 3 |
 *   |   | |   | | 2 |        | 5 | |   | |   |
 *   +---+ +---+ +---+        +---+ +---+ +---+
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = {
    /* left hand */
    { KC_EQL,   KC_1,         KC_2,     KC_3     KC_4,    KC_5    },
    { KC_TAB,   LALT_T(KC_Q), KC_W,     KC_E,    KC_R,    KC_T    },
    { KC_ESC,   LSFT_T(KC_A), KC_S,     KC_D,    KC_F,    KC_G    },
    { KC_LSFT,  LCTL_T(KC_Z), KC_X,     KC_C,    KC_V,    KC_B    },
    { KC_LGUI,  MO(_NUM),     MO(_SYM), KC_LEFT, KC_RGHT, XXXXXXX },
	/* left thumb */
    { KC_LALT, KC_ESC, LT(_SYM, KC_DEL), LT(_NUM, KC_BSPC), KC_CAPS, KC_LCTL },
    /* right hand */
    { KC_6,    KC_7,    KC_8,    KC_9,     KC_0,            KC_MINS },
    { KC_Y,    KC_U,    KC_I,    KC_O,     RALT_T(KC_P),    KC_BSLS },
    { KC_H,    KC_J,    KC_K,    KC_L,     RSFT_T(KC_SCLN), KC_QUOT },
    { KC_N,    KC_M,    KC_COMM, KC_DOT,   RCTL_T(KC_SLSH), KC_RSFT },
    { XXXXXXX, KC_DOWN, KC_UP,   MO(_SYM), MO(_NUM),        KC_RGUI },
	/* right thumb */
    { KC_RCTL, KC_NLCK, LT(_NUM, KC_SPC), LT(_SYM, KC_ENT), KC_TAB, KC_RALT },
  },
  [_NUM] = {
    /* left hand */
    { _______, _______, _______, _______, _______, _______ },
    { _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_PAST },
    { _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_DLR  },
    { _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSLS },
    { _______, _______, _______, KC_HOME, KC_END,  XXXXXXX },
	/* left thumb */
    { RESET, _______, _____,  _______, _______, _______ },
    /* right hand */
    { _______, _______, _______, _______, _______, _______ },
    { KC_PPLS, KC_P7,   KC_P8,   KC_P9,   KC_CMM,  _______ },
    { KC_PEQL, KC_P4,   KC_P5,   KC_P6,   KC_P0,   _______ },
    { KC_PMNS, KC_P1,   KC_P2,   KC_P3,   KC_DOT,  _______ },
    { XXXXXXX, PC_PGDN, KC_PGUP, _______, _______, _______ },
	/* rght thumb */
    { _______, _______, _______, _______, _______, RESET },
  },
  [_SYM] = {
    /* left hand */
    { _______, _______, _______, _______, _______, _______ },
    { _______, KC_EXLM, KC_AT,   KC_HASH, KC_PERC, KC_ASTR },
    { _______, KC_CIRC, KC_AMPR, KC_LBRC, KC_RBRC, KC_DLR  },
    { _______, UC(168), KC_TILD, KC_LABK, KC_RABK, KC_SLSH },
    { _______, _______, _______, KC_HOME, KC_END,  XXXXXXX },
	/* left thumb */
    { RESET, _______, _______, _______, _______, _______ },
    /* right hand */
    { _______, _______, _______, _______, _______, _______ },
    { KC_PLUS, KC_DQUO, KC_QUOT, KC_GRAV, KC_BSLS, _______ },
    { KC_EQL,  KC_LPRN, KC_RPRN, KC_UNDS, KC_COLN, _______ },
    { KC_MINS, KC_LCBR, KC_RCBR, KC_PIPE, KC_QUES, _______ },
    { XXXXXXX, PC_PGDN, KC_PGUP, _______, _______, _______ },
	/* rght thumb */
    { _______, _______, _______, _______, _______, RESET },
  }
};

void persistant_default_layer_set(uint16_t default_layer)
{
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

