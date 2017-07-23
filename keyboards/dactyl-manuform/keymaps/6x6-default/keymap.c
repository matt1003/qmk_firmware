#include "dactyl-manuform.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _____ KC_TRNS
#define XXXXX KC_NO

#define _QWERTY 0
#define _FN   1

/*              Thumb Cluster Mapping
 *         +---+ +---+        +---+ +---+
 *         | x | | x |        | 6 | | 1 |
 *   +---+ +---+ +---+        +---+ +---+ +---+
 *   |   | |   | | x |        | 2 | |   | |   |
 *   | x | | x | +---+        +---+ | 4 | | 3 |
 *   |   | |   | | x |        | 5 | |   | |   |
 *   +---+ +---+ +---+        +---+ +---+ +---+
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = {
    /* left hand */
    { KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5  },
    { KC_GRV,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T  },
    { KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G  },
    { KC_LSHIFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B  },
    { KC_A,      KC_B,    KC_C,    KC_D,    KC_E  ,  XXXXX },
    { KC_1,      KC_2,    KC_3,    KC_4,    KC_5,    KC_6  },
    /* right hand */
    { KC_6,      KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS   },
    { KC_Y,      KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL    },
    { KC_H,      KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT   },
    { KC_N,      KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSHIFT },
    { XXXXX,     KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,MO(_FN)   },
    { KC_DEL,    KC_RALT, KC_SPC,  KC_ENTER,KC_RCTRL,KC_BSPC   },
  },
  [_FN] = {
    /* left hand */
    { _____,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5 },
    { _____,   _____,   _____,   _____,   _____,   _____ },
    { _____,   _____,   _____,   _____,   _____,   _____ },
    { _____,   _____,   _____,   _____,   _____,   _____ },
    { _____,   _____,   _____,   _____,   _____,   XXXXX },
    { _____,   _____,   _____,   _____,   _____,   _____ },
    /* right hand */
    { KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _____ },
    { _____,   _____,   _____,   _____,   _____,   _____ },
    { _____,   _____,   _____,   _____,   _____,   _____ },
    { _____,   _____,   _____,   _____,   _____,   _____ },
    { XXXXX,   RESET,   _____,   _____,   _____,   _____ },
    { _____,   _____,   _____,   _____,   _____,   _____ },
  }
};

void persistant_default_layer_set(uint16_t default_layer)
{
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

