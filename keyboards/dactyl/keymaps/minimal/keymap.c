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
};

const uint16_t PROGMEM fn_actions[] =
{
    [LT_SYM_ENT]  = ACTION_MACRO_TAP(LT_SYM_ENT),
    [LT_SYM_SPC]  = ACTION_MACRO_TAP(LT_SYM_SPC),
};

void switch_layer(keyrecord_t *record, uint16_t keycode)
{
    static uint8_t layer = QWERTY;

    if (record->event.pressed)
    {
        if (record->tap.count && !record->tap.interrupted)
            register_code(keycode);
        else
            layer_on(++layer);
    }
    else
    {
        if(record->tap.count && !record->tap.interrupted)
            unregister_code(keycode);
        else
            layer_off(layer--);
    }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id)
    {
        case LT_SYM_ENT:
            switch_layer(record, KC_ENT);
            break;
        case LT_SYM_SPC:
            switch_layer(record, KC_SPC);
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

#define SFT_Z LSFT_T(KC_Z)
#define CTL_X LCTL_T(KC_X)
#define CTL_DOT RCTL_T(KC_DOT)
#define SFT_SLS RSFT_T(KC_SLSH)
#define SYM_ENT F(LT_SYM_ENT)
#define SYM_SPC F(LT_SYM_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [QWERTY] = {
        /* left hand */
        { _______, _______, _______, _______, _______, _______ },
        { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T    },
        { KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G    },
        { KC_LSFT, SFT_Z,   CTL_X,   KC_C,    KC_V,    KC_B    },
        { _______, _______, _______, _______, _______, XXXXXXX },
        /* left thumb */
        { KC_LALT, _______, KC_DEL, SYM_ENT,  _______, KC_LCTL },
        /* right hand */
        { _______, _______, _______, _______, _______, _______ },
        { KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS },
        { KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT },
        { KC_N,    KC_M,    KC_COMM, CTL_DOT, SFT_SLS, KC_RSFT },
        { XXXXXXX, _______, _______, _______, _______, _______ },
        /* right thumb */
        { KC_RCTL, _______, SYM_SPC, KC_BSPC, _______, KC_RGUI },
    },
    [SYM] = {
        /* left hand */
        { _______, _______, _______, _______, _______, _______ },
        { KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_LCBR },
        { KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_UNDS, KC_LPRN },
        { KC_GRV,  KC_PLUS, KC_EQL,  KC_MINS, KC_DQUO, KC_LBRC },
        { _______, _______, _______, _______, _______, XXXXXXX },
        /* left thumb */
        { RESET,   _______, _______, _______, _______, _______ },
        /* right hand */
        { _______, _______, _______, _______, _______, _______ },
        { KC_RCBR, KC_7,    KC_8,    KC_9,    KC_COMM, _______ },
        { KC_RPRN, KC_4,    KC_5,    KC_6,    KC_0,    _______ },
        { KC_RBRC, KC_1,    KC_2,    KC_3,    KC_DOT,  _______ },
        { XXXXXXX, _______, _______, _______, _______, _______ },
        /* rght thumb */
        { _______, _______, _______, _______, _______, RESET   },
    },
    [FUN] = {
        /* left hand */
        { _______, _______, _______, _______, _______, _______ },
        { KC_NLCK, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_PAUS },
        { KC_CAPS, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_PSCR },
        { KC_SLCK, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS  },
        { _______, _______, _______, _______, _______, XXXXXXX },
        /* left thumb */
        { RESET,   _______, _______, _______, _______, _______ },
        /* right hand */
        { _______, _______, _______, _______, _______, _______ },
        { KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_APP,  _______ },
        { KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DREF, _______ },
        { KC_EQEQ, KC_NTEQ, KC_LTEQ, KC_GTEQ, KC_HDIR, _______ },
        { XXXXXXX, _______, _______, _______, _______, _______ },
        /* rght thumb */
        { _______, _______, _______, _______, _______, RESET   },
    }
};

void persistant_default_layer_set(uint16_t default_layer)
{
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

