#include "dactyl.h"
#include "action_layer.h"
#include "eeconfig.h"

#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define QWERTY 0
#define SYM 1
#define NUM 2
#define FUN 3

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
    LT_NUM_TAB, // number layer when held, tab when pressed
    LT_SYM_BSP, // symbol layer when held, back-space when pressed
    LT_SFT_ENT, // shift when held, enter when pressed
    LT_CTL_SPC, // control when held, space when pressed
};

const uint16_t PROGMEM fn_actions[] =
{
    [LT_NUM_TAB] = ACTION_MACRO_TAP(LT_NUM_TAB),
    [LT_SYM_BSP] = ACTION_MACRO_TAP(LT_SYM_BSP),
    [LT_SFT_ENT] = ACTION_MACRO_TAP(LT_SFT_ENT),
    [LT_CTL_SPC] = ACTION_MACRO_TAP(LT_CTL_SPC),
};

void switch_layer(keyrecord_t *record, uint8_t layer, uint16_t keycode)
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
               layer_on(FUN);
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
               layer_off(FUN);
            count--;
        }
    }
}

void switch_modifier(keyrecord_t *record, uint16_t modifier, uint16_t keycode)
{
    static int count = 0;

    if (record->event.pressed)
    {
        if (count == 0)
        {
            if (record->tap.count && !record->tap.interrupted)
                register_code(keycode);
            else
            {
                register_code(modifier);
                count++;
            }
        }
        else
        {
            register_code(KC_MINS);
            count++;
        }
    }
    else
    {
        if (count == 2)
        {
            unregister_code(KC_MINS);
            count--;
        }
        else
        {
            if(record->tap.count && !record->tap.interrupted)
                unregister_code(keycode);
            else
            {
                unregister_code(modifier);
                count--;
            }
        }
    }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id)
    {
        case LT_NUM_TAB:
            switch_layer(record, NUM, KC_TAB);
            break;
        case LT_SYM_BSP:
            switch_layer(record, SYM, KC_BSPC);
            break;
        case LT_SFT_ENT:
            switch_modifier(record, KC_LSFT, KC_ENT);
            break;
        case LT_CTL_SPC:
            switch_modifier(record, KC_RCTL, KC_SPC);
            break;    }
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
        { _______, _______, _______, _______, _______, _______ },
        { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T    },
        { KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G    },
        { KC_LSFT,LCTL_T(KC_Z),KC_X, KC_C,    KC_V,    KC_B    },
        { _______, _______, _______, _______, _______, XXXXXXX },
        /* left thumb */
        { _______, LALT_T(KC_ESC), F(LT_NUM_TAB), F(LT_SFT_ENT), _______, _______ },
        /* right hand */
        { _______, _______, _______, _______, _______, _______ },
        { KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS },
        { KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT },
        { KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT },
        { XXXXXXX, _______, _______, _______, _______, _______ },
        /* right thumb */
        { _______, _______, F(LT_CTL_SPC), F(LT_SYM_BSP), RGUI_T(KC_DEL), _______ },
    },
    [SYM] = {
        /* left hand */
        { _______, _______, _______, _______, _______, _______ },
        { _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_LCBR },
        { _______, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN },
        { _______, KC_TILD, KC_PLUS, KC_MINS, KC_EQL,  KC_LBRC },
        { _______, _______, _______, _______, _______, XXXXXXX },
        /* left thumb */
        { RESET,   _______, _______, _______, _______, _______ },
        /* right hand */
        { _______, _______, _______, _______, _______, _______ },
        { KC_RCBR, KC_UNDS, KC_HDIR, KC_DREF, KC_BSLS, _______ },
        { KC_RPRN, KC_DQUO, KC_QUOT, KC_GRV,  KC_COLN, _______ },
        { KC_RBRC, KC_PIPE, KC_LT,   KC_GT,   KC_QUES, _______ },
        { XXXXXXX, _______, _______, _______, _______, _______ },
        /* rght thumb */
        { _______, _______, _______, _______, _______, RESET   },
    },
    [NUM] = {
        /* left hand */
        { _______, _______, _______, _______, _______, _______ },
        { _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_LCBR },
        { _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_LPRN },
        { _______, KC_EQEQ, KC_LTEQ, KC_GTEQ, KC_NTEQ, KC_LBRC },
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
        { _______, _______, KC_UNDS, _______, _______, RESET   },
    },
    [FUN] = {
        /* left hand */
        { _______, _______, _______, _______, _______, _______ },
        { _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_PGUP },
        { _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN },
        { _______, KC_EQEQ, KC_LTEQ, KC_GTEQ, KC_NTEQ, KC_LBRC },
        { _______, _______, _______, _______, _______, XXXXXXX },
        /* left thumb */
        { RESET,   _______, _______, _______, _______, _______ },
        /* right hand */
        { _______, _______, _______, _______, _______, _______ },
        { KC_CAPS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______ },
        { KC_PSCR, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______ },
        { KC_SLCK, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______ },
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

