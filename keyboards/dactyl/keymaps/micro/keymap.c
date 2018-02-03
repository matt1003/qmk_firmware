#include "dactyl.h"
#include "action_layer.h"
#include "eeconfig.h"

#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define _QWERTY 0
#define _COLEMAK 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 4

// =============================================================================

enum custom_keycodes
{
    KC_DREF = SAFE_RANGE,
    KC_EQEQ,
    KC_NTEQ,
    KC_LTEQ,
    KC_GTEQ,
    KC_HDIR,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    if (!record->event.pressed)
        return true;

    switch (keycode)
    {
        case KC_DREF:
            SEND_STRING("->");
            return false;
        case KC_EQEQ:
            SEND_STRING("==");
            return false;
        case KC_NTEQ:
            SEND_STRING("!=");
            return false;
        case KC_LTEQ:
            SEND_STRING("<=");
            return false;
        case KC_GTEQ:
            SEND_STRING(">=");
            return false;
        case KC_HDIR:
            SEND_STRING("~/");
            return false;
    }

    return true;
};

// =============================================================================

enum custom_actions
{
    LOWER,
    RAISE,
    CNRTL,
    SHIFT,
};

const uint16_t PROGMEM fn_actions[] =
{
    [LOWER] = ACTION_MACRO_TAP(LOWER),
    [RAISE] = ACTION_MACRO_TAP(RAISE),
    [CNRTL] = ACTION_MACRO_TAP(CNRTL),
    [SHIFT] = ACTION_MACRO_TAP(SHIFT),
};

void select_layer(keyrecord_t *record, uint8_t layer, uint16_t keycode)
{
    static int count = 0;

    if (record->event.pressed)
    {
        if (record->tap.count && !record->tap.interrupted)
            register_code(keycode);
        else
        {
            layer_on(layer);
            if (count == 1)
               layer_on(_ADJUST);
            count++;
        }
    }
    else
    {
        if(record->tap.count && !record->tap.interrupted)
            unregister_code(keycode);
        else
        {
            layer_off(layer);
            if (count == 2)
               layer_off(_ADJUST);
            count--;
        }
    }
}

void select_modifier(keyrecord_t *record, uint16_t modifier, uint16_t keycode)
{
    static bool shift = false;
    static bool underscore = false;

    if (record->event.pressed)
    {
        if (record->tap.count && !record->tap.interrupted)
        {
            if (shift && keycode == KC_SPC)
            {
                register_code(KC_MINS);
                underscore = true;
            }
            else
                register_code(keycode);
        }
        else
        {
            if (modifier == KC_LSFT || modifier == KC_RSFT)
                shift = true;
            register_code(modifier);
        }
    }
    else
    {
        if(record->tap.count && !record->tap.interrupted)
        {
            if (underscore && keycode == KC_SPC)
            {
                unregister_code(KC_MINS);
                underscore = false;
            }
            else
                unregister_code(keycode);
        }
        else
        {
            if (modifier == KC_LSFT || modifier == KC_RSFT)
                shift = false;
            unregister_code(modifier);
        }
    }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id)
    {
        case LOWER:
            select_layer(record, _LOWER, KC_BSPC);
            break;
        case RAISE:
            select_layer(record, _RAISE, KC_TAB);
            break;
        case CNRTL:
            select_modifier(record, KC_RCTL, KC_SPC);
            break;
        case SHIFT:
            select_modifier(record, KC_LSFT, KC_ENT);
            break;
    }
    return MACRO_NONE;
}

// =============================================================================

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
        { _______, _______, _______, _______, _______, _______ },
        { _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T    },
        { KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G    },
        { _______,LSFT_T(KC_Z),KC_X, KC_C,    KC_V,    KC_B    },
        { _______, _______, _______, _______, _______, XXXXXXX },
        /* left thumb */
        { RESET, LALT_T(KC_DEL), F(LOWER), F(CNRTL), KC_NO, TG(_COLEMAK)},
        /* right hand */
        { _______, _______, _______, _______, _______, _______ },
        { KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______ },
        { KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, _______ },
        { KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______ },
        { XXXXXXX, _______, _______, _______, _______, _______ },
        /* right thumb */
        { TG(_COLEMAK), KC_NO, F(SHIFT), F(RAISE), RGUI_T(KC_ESC), RESET },
    },
    [_COLEMAK] = {
        /* left hand */
        { _______, _______, _______, _______, _______, _______ },
        { _______, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G    },
        { _______, KC_A,    KC_R,    KC_S,    KC_T,    KC_D    },
        { _______,LSFT_T(KC_Z),KC_X, KC_C,    KC_V,    KC_B    },
        { _______, _______, _______, _______, _______, XXXXXXX },
        /* left thumb */
        { _______, _______, _______, _______, _______, _______ },
        /* right hand */
        { _______, _______, _______, _______, _______, _______ },
        { KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, _______ },
        { KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    _______ },
        { KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______ },
        { XXXXXXX, _______, _______, _______, _______, _______ },
        /* right thumb */
        { _______, _______, _______, _______, _______, _______ },
    },
    [_LOWER] = {
        /* left hand */
        { _______, _______, _______, _______, _______, _______ },
        { _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_NO   },
        { _______, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_NO   },
        { _______, KC_TILD, KC_PLUS, KC_MINS, KC_EQL,  KC_NO   },
        { _______, _______, _______, _______, _______, XXXXXXX },
        /* left thumb */
        { _______, _______, _______, _______, _______, _______ },
        /* right hand */
        { _______, _______, _______, _______, _______, _______ },
        { KC_NO,   KC_7,    KC_8,    KC_9,    KC_COMM, _______ },
        { KC_NO,   KC_4,    KC_5,    KC_6,    KC_0,    _______ },
        { KC_NO,   KC_1,    KC_2,    KC_3,    KC_DOT,  _______ },
        { XXXXXXX, _______, _______, _______, _______, _______ },
        /* rght thumb */
        { _______, _______, _______, _______, _______, _______ },
    },
    [_RAISE] = {
        /* left hand */
        { _______, _______, _______, _______, _______, _______ },
        { _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_NO   },
        { _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO   },
        { _______, KC_BSLS, KC_PIPE, KC_QUOT, KC_DQUO, KC_NO   },
        { _______, _______, _______, _______, _______, XXXXXXX },
        /* left thumb */
        { _______, _______, _______, _______, _______, _______ },
        /* right hand */
        { _______, _______, _______, _______, _______, _______ },
        { KC_NO,   KC_NO,   KC_LCBR, KC_RCBR, KC_GRV,  _______ },
        { KC_NO,   KC_NO,   KC_LPRN, KC_RPRN, KC_DREF, _______ },
        { KC_NO,   KC_NO,   KC_LBRC, KC_RBRC, KC_HDIR, _______ },
        { XXXXXXX, _______, _______, _______, _______, _______ },
        /* rght thumb */
        { _______, _______, _______, _______, _______, _______ },
    },
    [_ADJUST] = {
        /* left hand */
        { _______, _______, _______, _______, _______, _______ },
        { _______, KC_APP,  KC_PAUS, KC_INS,  KC_PSCR, KC_NO   },
        { _______, KC_CAPS, KC_NLCK, KC_SLCK, KC_LALT, KC_NO   },
        { _______, KC_EQEQ, KC_LTEQ, KC_GTEQ, KC_NTEQ, KC_NO   },
        { _______, _______, _______, _______, _______, XXXXXXX },
        /* left thumb */
        { _______, _______, _______, _______, _______, _______ },
        /* right hand */
        { _______, _______, _______, _______, _______, _______ },
        { KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______ },
        { KC_NO,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______ },
        { KC_NO,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______ },
        { XXXXXXX, _______, _______, _______, _______, _______ },
        /* rght thumb */
        { _______, _______, _______, _______, _______, _______ },
    }
};

void persistant_default_layer_set(uint16_t default_layer)
{
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

