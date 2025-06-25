// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "epd_ws2in9V2.h"
#include "generated/img_296_blank.h"
#include "generated/img_296_navi.h"
#include "generated/img_296_fusion360_sketch.h"
#include "generated/img_296_halfkey_left.h"
#include "generated/img_296_halfkey_right.h"
#include "generated/img_296_numkey.h"
#include "generated/img_296_mode.h"

enum layer_number {
    LAYER_NAVI = 0,
    LAYER_FUSION360_SKETCH,
    LAYER_HALFKEY_COLEMAKDH_LEFT,
    LAYER_HALFKEY_COLEMAKDH_RIGHT,
    LAYER_NUM,
    LAYER_MODE
};

static const uint8_t LAYER_MARK_MODE_START = LAYER_NAVI;
static const uint8_t LAYER_MARK_MODE_END = LAYER_HALFKEY_COLEMAKDH_LEFT;

#define XK_NUM  MO(LAYER_NUM)
#define XK_HKLF MO(LAYER_HALFKEY_COLEMAKDH_LEFT)
#define XK_HKRG LT(LAYER_HALFKEY_COLEMAKDH_RIGHT, KC_SPACE)
#define XK_LSFT OSM(MOD_LSFT)
#define XK_MODE MO(LAYER_MODE)

// Fusion360
#define FC_TRM  KC_T        // Trim
#define FC_EXT  LSFT(KC_X)  // Extend
#define FC_DIM  KC_D        // Dimmensions
#define FC_CNS  KC_X        // Construction
#define FC_FLT  LCTL(KC_F)  // Fillet
#define FC_ARC  KC_A        // Arc
#define FC_CRC  KC_C        // Circle
#define FC_RCT  KC_R        // Rectangle
#define FC_LIN  KC_L        // Line
#define FC_PNT  LCTL(KC_P)  // Point
#define FC_MID  LSFT(KC_M)  // Mid Point
#define FC_PRL  LSFT(KC_P)  // Parallel
#define FC_PRP  LCTL(KC_R)  // Perpendicular
#define FC_CIN  LSFT(KC_C)  // Coincidence
#define FC_HV   LCTL(KC_H)  // Horz/Vert
#define FC_ORB  LSFT(MS_BTN3)   // Orbiting
#define FC_PAN  MS_BTN3     // Panning

// Select mode
#define SM_NAVI (QK_USER + 0)
#define SM_FS36 (QK_USER + 1)

// US-JP keys
#define XK_PLUS LSFT(0x33)
#define XK_ASTR LSFT(0x34)
#define XK_QUOT LSFT(0x24)
#define XK_DQUT LSFT(0x1f)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┐
     * │Esc│   │   │   │F5 │F11│
     * ├───┼───┼───┼───┼───┼───┤
     * │   │ ← │ ↓ │ ↑ │ → │   │
     * ├───┼───┼───┼───┼───┼───┤
     * │   │Hom│PgD│PgU│End│   │
     * ├───┼───┼───┼───┼───┼───┤
     * │ ← │ → │Mod│   │Spc│Num│
     * └───┴───┴───┴───┴───┴───┘
     */
    [LAYER_NAVI] = LAYOUT_ortho_4x6(
        KC_ESC,   KC_NO,   KC_NO,   KC_NO,   KC_F5,   KC_F11,
        KC_NO,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,
        KC_NO,    KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_NO,
        KC_LEFT,  KC_RGHT, XK_MODE, XK_HKLF, XK_HKRG, XK_NUM
    ),
    /*
     * ┌───┬───┬───┬───┬───┬───┐
     * │Esc│Trm|Ext│Dim│Cns│Flt│
     * ├───┼───┼───┼───┼───┼───┤
     * │Ent│Arc│Crc│Rct│Lin│Pnt│
     * ├───┼───┼───┼───┼───┼───┤
     * │Del│Mid│Prl│Prp│Cin│H/V│
     * ├───┼───┼───┼───┼───┼───┤
     * │Orb│Pan│Mod│ABL|ABR│Num│
     * └───┴───┴───┴───┴───┴───┘
     */
     [LAYER_FUSION360_SKETCH] = LAYOUT_ortho_4x6(
        KC_ESC,   FC_TRM,  FC_EXT,  FC_DIM,  FC_CNS,  FC_FLT,
        KC_ENT,   FC_ARC,  FC_CRC,  FC_RCT,  FC_LIN,  FC_PNT,
        KC_DEL,   FC_MID,  FC_PRL,  FC_PRP,  FC_CIN,  FC_HV,
        FC_ORB,   FC_PAN,  XK_MODE, XK_HKLF, XK_HKRG, XK_NUM
    ),
    /*
     * ┌───┬───┬───┬───┬───┬───┐
     * │   │ q │ w │ f │ p │ g │
     * ├───┼───┼───┼───┼───┼───┤
     * │   │ a │ r │ s │ t │ g │
     * ├───┼───┼───┼───┼───┼───┤
     * │   │ z │ x │ c │ d │ v │
     * ├───┼───┼───┼───┼───┼───┤
     * │   │   │Mod│   |*1 │Num│
     * └───┴───┴───┴───┴───┴───┘
     * *1: Tap: Space, Hold: Flip to right
     */
     [LAYER_HALFKEY_COLEMAKDH_LEFT] = LAYOUT_ortho_4x6(
        KC_ESC,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,
        KC_TAB,   KC_A,    KC_R,    KC_S,    KC_T,    KC_G,
        KC_BSPC,  KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    /*
     * ┌───┬───┬───┬───┬───┬───┐
     * │ - │ ; │ Y │ U │ L │ J │
     * ├───┼───┼───┼───┼───┼───┤
     * │ ' │ O │ I │ E │ N │ M │
     * ├───┼───┼───┼───┼───┼───┤
     * │Ent│ / │ . │ , │ H │ K │
     * ├───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │Flp│Num│
     * └───┴───┴───┴───┴───┴───┘
     */
     [LAYER_HALFKEY_COLEMAKDH_RIGHT] = LAYOUT_ortho_4x6(
        KC_MINS,  KC_SCLN, KC_Y,    KC_U,    KC_L,    KC_J,
        XK_QUOT,  KC_O,    KC_I,    KC_E,    KC_N,    KC_M,
        KC_ENT,   KC_SLSH, KC_DOT,  KC_COMM, KC_H,    KC_K,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    /*
     * ┌───┬───┬───┬───┬───┬───┐
     * │ESC│ 6 │ 7 │ 8 │ 9 │ 0 │
     * ├───┼───┼───┼───┼───┼───┤
     * │Ent│ 1 │ 2 │ 3 │ 4 │ 5 │
     * ├───┼───┼───┼───┼───┼───┤
     * │BS │ + │ - │ * │ / │ . │
     * ├───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │   │Num│
     * └───┴───┴───┴───┴───┴───┘
     */
     [LAYER_NUM] = LAYOUT_ortho_4x6(
        KC_ESC,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_ENT,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
        KC_BSPC,  XK_PLUS, KC_MINS, XK_ASTR, KC_SLSH, KC_DOT,
        KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS
    ),
    /*
     * ┌───┬───┬───┬───┬───┬───┐
     * │   │   │   │   │   │   │
     * ├───┼───┼───┼───┼───┼───┤
     * │   │   │   │Fsn│Nav│   │
     * ├───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │   │   │
     * ├───┼───┼───┼───┼───┼───┤
     * │Trn│Trn│Trn│Trn│Trn│Trn│
     * └───┴───┴───┴───┴───┴───┘
     */
     [LAYER_MODE] = LAYOUT_ortho_4x6(
        KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,    KC_NO,   KC_NO,   SM_FS36, SM_NAVI, KC_NO,
        KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
};

const uint16_t PROGMEM encoder_keymaps[][1][2] = {
    [LAYER_NAVI] = {{ KC_VOLU, KC_VOLD }},
    [LAYER_FUSION360_SKETCH] = {{ MS_WHLU, MS_WHLD }},
    [LAYER_HALFKEY_COLEMAKDH_LEFT] = {{ KC_VOLU, KC_VOLD }},
    [LAYER_HALFKEY_COLEMAKDH_RIGHT] = {{ KC_VOLU, KC_VOLD }},
    [LAYER_NUM] = {{ KC_VOLU, KC_VOLD }},
    [LAYER_MODE] = {{ KC_VOLU, KC_VOLD }},
};


uint32_t tim_mark;


static uint32_t p28;
static uint32_t p29;

void keyboard_post_init_user(void)
{
    debug_enable = true;
    debug_matrix = true;

    epd_task_init(img_296_navi);

//    gpio_set_pin_input_high(GP28);
//    gpio_set_pin_input_high(GP29);
    p28 = gpio_read_pin(GP28);
    p29 = gpio_read_pin(GP29);

    tim_mark = timer_read32();
}


void housekeeping_task_user(void)
{
    tim_mark = timer_read32();
    uint32_t p28_prev = p28;
    uint32_t p29_prev = p29;
    p28 = gpio_read_pin(GP28);
    p29 = gpio_read_pin(GP29);
    if ((p28 != p28_prev) || (p29 != p29_prev)){
        dprintf("GP28: %lu, GP29: %lu\n", p28, p29);
    }
    epd_task();
}


layer_state_t layer_state_set_user(layer_state_t state)
{
    dprintf("layerrc_state_set_user. state: %02x, highest: %u\n", state, get_highest_layer(state));
#if 1
    switch (get_highest_layer(state)){
    case LAYER_FUSION360_SKETCH:
        epd_display_image_partial(img_296_fusion360_sketch);
        break;
    case LAYER_HALFKEY_COLEMAKDH_LEFT:
        epd_display_image_partial(img_296_halfkey_left);
        break;
    case LAYER_HALFKEY_COLEMAKDH_RIGHT:
        epd_display_image_partial(img_296_halfkey_right);
        break;
    case LAYER_NUM:
        epd_display_image_partial(img_296_numkey);
        break;
    case LAYER_MODE:
        epd_display_image_partial(img_296_mode);
        break;
    case LAYER_NAVI:
        // fall through, no break
    default:
        epd_display_image_partial(img_296_navi);
        break;
    }
#endif
    return state;
}

#if 1
static void set_mode(uint16_t keycode)
{
    uint8_t layer_selected = (uint8_t)(keycode - QK_USER);
    for (uint8_t layer = LAYER_MARK_MODE_START; layer <= LAYER_MARK_MODE_END; layer++){
        if (layer == layer_selected){
            layer_on(layer);
        } else {
            layer_off(layer);
        }
    }
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
    dprintf("process_record_user. keycode: %02x\n", keycode);
#if 0
    if (keycode == KC_ESC && record->event.pressed){
        epd_test();
    }
#endif
#if 1
    switch (keycode){
        case SM_NAVI:
        case SM_FS36:
            if (record->event.pressed){
                set_mode(keycode);
                return false;
            }
            break;
        default:
            break;
    }
#endif
    return true;
}


bool encoder_update_user(uint8_t index, bool clockwise) {
    uint idx_layer = get_highest_layer(layer_state);
    uint idx_direction = clockwise ? 0: 1;
    uint16_t key_code = encoder_keymaps[idx_layer][index][idx_direction];
    tap_code(key_code);
    return false;
}
