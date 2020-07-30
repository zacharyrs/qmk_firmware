#include QMK_KEYBOARD_H

HSV stt_gradient_0 = {205, 250, 255};
HSV stt_gradient_100 = {140, 215, 125};
bool stt_reflected_gradient = false;
uint8_t stt_gp_i = 0;

typedef struct {
    HSV gradient_0;
    HSV gradient_1;
    bool reflected;
} STT_CUSTOM_PRESETS;

enum ctrl_keycodes {
    U_T_AUTO = SAFE_RANGE,  //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,               //USB Toggle Automatic GCR control
    DBG_TOG,                //DEBUG Toggle On / Off
    DBG_MTRX,               //DEBUG Toggle Matrix Prints
    DBG_KBD,                //DEBUG Toggle Keyboard Prints
    DBG_MOU,                //DEBUG Toggle Mouse Prints
    MD_BOOT,                //Restart into bootloader after hold timeout
    ZMOD_KEY,
    STT_G0_HUI,             //Custom gradient color 1 hue increase
    STT_G0_HUD,             //Custom gradient color 1 hue decrease
    STT_G0_SAI,             //Custom gradient color 1 saturation increase
    STT_G0_SAD,             //Custom gradient color 1 saturation decrease
    STT_G0_VAI,             //Custom gradient color 1 value increase
    STT_G0_VAD,             //Custom gradient color 1 value decrease
    STT_G100_HUI,           //Custom gradient color 2 hue increase
    STT_G100_HUD,           //Custom gradient color 2 hue decrease
    STT_G100_SAI,           //Custom gradient color 2 saturation increase
    STT_G100_SAD,           //Custom gradient color 2 saturation decrease
    STT_G100_VAI,           //Custom gradient color 2 value increase
    STT_G100_VAD,           //Custom gradient color 2 value decrease
    STT_GRADIENT_PRESETS,   //Gradient presets
    STT_REFLECTED_GRADIENT, //Toggle between linear and reflected gradient
    STT_GRADIENT_FLIP,      //Flip the gradient colors
};

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KC_PSCR, KC_SLCK, KC_PAUS, \
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN, \
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                              KC_UP, \
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, ZMOD_KEY,   KC_APP,  KC_RCTL,            KC_LEFT, KC_DOWN, KC_RGHT \
    ),
    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            KC_MUTE, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   KC_MPLY, KC_MSTP, KC_VOLU, \
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, U_T_AUTO,U_T_AGCR,_______, _______, _______, _______, _______,   KC_MPRV, KC_MNXT, KC_VOLD, \
        _______, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______, _______, \
        _______, RGB_TOG, _______, _______, _______, MD_BOOT, NK_TOGG, _______, _______, _______, _______, _______,                              _______, \
        _______, _______, _______,                   _______,                            _______, ZMOD_KEY, _______, _______,            _______, _______, _______ \
    ),
    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, \
        _______, STT_G0_HUD, STT_G0_HUI, STT_G0_SAD, STT_G0_SAI, STT_G0_VAD, STT_G0_VAI, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, \
        _______, STT_G100_HUD, STT_G100_HUI, STT_G100_SAD, STT_G100_SAI, STT_G100_VAD, STT_G100_VAI, _______, _______, _______, _______, _______, _______, \
        _______, STT_GRADIENT_PRESETS, STT_REFLECTED_GRADIENT, STT_GRADIENT_FLIP, _______, _______, _______, _______, _______, _______, _______, _______,                              _______, \
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______ \
    )
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

#define MODS_SHIFT  (get_mods() & MOD_MASK_SHIFT)
#define MODS_CTRL   (get_mods() & MOD_MASK_CTRL)
#define MODS_ALT    (get_mods() & MOD_MASK_ALT)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;
    uint8_t color_adj_step = 5;
    STT_CUSTOM_PRESETS stt_gradient_presets[] = {
        {{205, 250, 255}, {140, 215, 125}, false },
        {{41, 255, 255}, {233, 245, 255}, false },
        {{45, 245, 155}, {160, 255, 80}, false },
        {{173, 245, 40}, {41, 255, 205}, true },
        {{32, 255, 165}, {217, 185, 70}, false },
        {{240, 255, 145}, {115, 255, 245}, true },
        {{118, 255, 255}, {242, 255, 255}, false },
        {{118, 255, 255}, {242, 255, 255}, false },
        {{212, 0, 0}, {223, 235, 165}, true },
    };
    uint8_t stt_gp_length = sizeof(stt_gradient_presets)/sizeof(stt_gradient_presets[0]);

    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case ZMOD_KEY:
            if (record->event.pressed) {
                if (MODS_CTRL) {
                    layer_on(2);
                } else {
                    layer_on(1);
                }
            } else {
                layer_off(1);
                layer_off(2);
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER: {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
        case STT_G0_HUI:
            if (record->event.pressed) {
                stt_gradient_0.h += color_adj_step;
                dprintf("Gradient 0 HSV: %d, %d, %d\n", stt_gradient_0.h, stt_gradient_0.s, stt_gradient_0.v);
            }
            return false;
        case STT_G0_HUD:
            if (record->event.pressed) {
                stt_gradient_0.h -= color_adj_step;
                dprintf("Gradient 0 HSV: %d, %d, %d\n", stt_gradient_0.h, stt_gradient_0.s, stt_gradient_0.v);
            }
            return false;
        case STT_G0_SAI:
            if (record->event.pressed) {
                stt_gradient_0.s = (stt_gradient_0.s + color_adj_step * 2 <= 255) ? stt_gradient_0.s + color_adj_step * 2 : 255;
                dprintf("Gradient 0 HSV: %d, %d, %d\n", stt_gradient_0.h, stt_gradient_0.s, stt_gradient_0.v);
            }
            return false;
        case STT_G0_SAD:
            if (record->event.pressed) {
                stt_gradient_0.s = (stt_gradient_0.s - color_adj_step * 2 >= 0) ? stt_gradient_0.s - color_adj_step * 2 : 0;
                dprintf("Gradient 0 HSV: %d, %d, %d\n", stt_gradient_0.h, stt_gradient_0.s, stt_gradient_0.v);
            }
            return false;
        case STT_G0_VAI:
            if (record->event.pressed) {
                stt_gradient_0.v = (stt_gradient_0.v + color_adj_step * 2 <= 255) ? stt_gradient_0.v + color_adj_step * 2 : 255;
                dprintf("Gradient 0 HSV: %d, %d, %d\n", stt_gradient_0.h, stt_gradient_0.s, stt_gradient_0.v);
            }
            return false;
        case STT_G0_VAD:
            if (record->event.pressed) {
                stt_gradient_0.v = (stt_gradient_0.v - color_adj_step * 2 >= 0) ? stt_gradient_0.v - color_adj_step * 2 : 0;
                dprintf("Gradient 0 HSV: %d, %d, %d\n", stt_gradient_0.h, stt_gradient_0.s, stt_gradient_0.v);
            }
            return false;
        case STT_G100_HUI:
            if (record->event.pressed) {
                stt_gradient_100.h += color_adj_step;
                dprintf("Gradient 100 HSV: %d, %d, %d\n", stt_gradient_100.h, stt_gradient_100.s, stt_gradient_100.v);
            }
            return false;
        case STT_G100_HUD:
            if (record->event.pressed) {
                stt_gradient_100.h -= color_adj_step;
                dprintf("Gradient 100 HSV: %d, %d, %d\n", stt_gradient_100.h, stt_gradient_100.s, stt_gradient_100.v);
            }
            return false;
        case STT_G100_SAI:
            if (record->event.pressed) {
                stt_gradient_100.s = (stt_gradient_100.s + color_adj_step * 2 <= 255) ? stt_gradient_100.s + color_adj_step * 2 : 255;
                dprintf("Gradient 100 HSV: %d, %d, %d\n", stt_gradient_100.h, stt_gradient_100.s, stt_gradient_100.v);
            }
            return false;
        case STT_G100_SAD:
            if (record->event.pressed) {
                stt_gradient_100.s = (stt_gradient_100.s - color_adj_step * 2 >= 0) ? stt_gradient_100.s - color_adj_step * 2 : 0;
                dprintf("Gradient 100 HSV: %d, %d, %d\n", stt_gradient_100.h, stt_gradient_100.s, stt_gradient_100.v);
            }
            return false;
        case STT_G100_VAI:
            if (record->event.pressed) {
                stt_gradient_100.v = (stt_gradient_100.v + color_adj_step * 2 <= 255) ? stt_gradient_100.v + color_adj_step * 2 : 255;
                dprintf("Gradient 100 HSV: %d, %d, %d\n", stt_gradient_100.h, stt_gradient_100.s, stt_gradient_100.v);
            }
            return false;
        case STT_G100_VAD:
            if (record->event.pressed) {
                stt_gradient_100.v = (stt_gradient_100.v - color_adj_step * 2 >= 0) ? stt_gradient_100.v - color_adj_step * 2 : 0;
                dprintf("Gradient 100 HSV: %d, %d, %d\n", stt_gradient_100.h, stt_gradient_100.s, stt_gradient_100.v);
            }
            return false;
        case STT_GRADIENT_PRESETS:
            if (record->event.pressed) {
                stt_gp_i = (stt_gp_i + stt_gp_length ) % stt_gp_length;

                stt_gradient_0 = stt_gradient_presets[stt_gp_i].gradient_0;
                stt_gradient_100 = stt_gradient_presets[stt_gp_i].gradient_1;
                stt_reflected_gradient = stt_gradient_presets[stt_gp_i].reflected;

                stt_gp_i += 1;
            }
            return false;
        case STT_REFLECTED_GRADIENT:
            if (record->event.pressed) {
                stt_reflected_gradient = !stt_reflected_gradient;
            }
            return false;
        case STT_GRADIENT_FLIP:
            if (record->event.pressed) {
                HSV temp_color = stt_gradient_0;
                stt_gradient_0 = stt_gradient_100;
                stt_gradient_100 = temp_color;
            }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}

void keyboard_post_init_user(void) {
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_STT_CUSTOM_GRADIENT);
}
