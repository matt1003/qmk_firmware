#include "dactyl.h"
#include "action_layer.h"
#include "eeconfig.h"

#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define QWERTY 0
#define SYM 1
#define FUN 2

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
    LT_SYM_ENT,
    LT_SYM_SPC,
    LT_FUN_DEL,
    LT_FUN_BSPC,
};

const uint16_t PROGMEM fn_actions[] =
{
    [LT_SYM_ENT]  = ACTION_MACRO_TAP(LT_SYM_ENT),
    [LT_SYM_SPC]  = ACTION_MACRO_TAP(LT_SYM_SPC),
    [LT_FUN_DEL]  = ACTION_MACRO_TAP(LT_FUN_DEL),
    [LT_FUN_BSPC] = ACTION_MACRO_TAP(LT_FUN_BSPC),
};

void switch_layer(keyrecord_t *record, uint8_t layer, uint16_t keycode)
{
    if (record->event.pressed)
    {
        if (record->tap.count && !record->tap.interrupted)
            register_code(keycode);
        else
            layer_on(layer);
    }
    else
    {
        if(record->tap.count && !record->tap.interrupted)
            unregister_code(keycode);
        else
            layer_off(layer);
    }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id)
    {
        case LT_SYM_ENT:
            switch_layer(record, SYM, KC_ENT);
            break;
        case LT_SYM_SPC:
            switch_layer(record, SYM, KC_SPC);
            break;
        case LT_FUN_DEL:
            switch_layer(record, FUN, KC_DEL);
            break;
        case LT_FUN_BSPC:
            switch_layer(record, FUN, KC_BSPC);
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
    [QWERTY] = {
        /* left hand */
        { KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5    },
        { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T    },
        { KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G    },
        { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B    },
        { KC_LCTL, KC_LGUI, KC_LALT, KC_LEFT, KC_RGHT, XXXXXXX },
        /* left thumb */
        { KC_LALT, TG(SYM), F(LT_FUN_DEL), F(LT_SYM_ENT), KC_LGUI, KC_LCTRL },
        /* right hand */
        { KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS },
        { KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS },
        { KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT },
        { KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT },
        { XXXXXXX, KC_DOWN, KC_UP,   KC_RALT, KC_APP,  KC_RCTL },
        /* right thumb */
        { KC_RCTL, KC_CAPS, F(LT_SYM_SPC), F(LT_FUN_BSPC), TG(FUN), KC_RALT },
    },
    [SYM] = {
        /* left hand */
        { _______, _______, _______, _______, _______, _______ },
        { KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_LCBR },
        { KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_UNDS, KC_LPRN },
        { KC_GRV,  KC_PLUS, KC_EQL,  KC_MINS, KC_DQUO, KC_LBRC },
        { _______, _______, _______, KC_HOME, KC_END,  XXXXXXX },
        /* left thumb */
        { _______, _______, _______, _______, _______, _______ },
        /* right hand */
        { _______, _______, _______, _______, _______, _______ },
        { KC_RCBR, KC_7,    KC_8,    KC_9,    KC_COMM, _______ },
        { KC_RPRN, KC_4,    KC_5,    KC_6,    KC_0,    _______ },
        { KC_RBRC, KC_1,    KC_2,    KC_3,    KC_DOT,  _______ },
        { XXXXXXX, KC_PGDN, KC_PGUP, _______, _______, _______ },
        /* rght thumb */
        { _______, _______, _______, _______, _______, _______ },
    },
    [FUN] = {
        /* left hand */
        { _______, _______, _______, _______, _______, _______ },
        { KC_NLCK, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_PAUS },
        { KC_CAPS, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_PSCR },
        { KC_SLCK, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS  },
        { _______, _______, _______, KC_HOME, KC_END, XXXXXXX },
        /* left thumb */
        { RESET,   _______, _______, _______, _______, _______ },
        /* right hand */
        { _______, _______, _______, _______, _______, _______ },
        { KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______ },
        { KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DREF, _______ },
        { KC_EQEQ, KC_NTEQ, KC_LTEQ, KC_GTEQ, KC_HDIR, _______ },
        { XXXXXXX, KC_PGDN, KC_PGUP, _______, _______, _______ },
        /* rght thumb */
        { _______, _______, _______, _______, _______, RESET   },
    }
};

void persistant_default_layer_set(uint16_t default_layer)
{
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

