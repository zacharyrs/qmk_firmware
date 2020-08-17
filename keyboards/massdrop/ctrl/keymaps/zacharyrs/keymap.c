#include QMK_KEYBOARD_H

HSV     zrs_grad_start = {70, 240, 255};
HSV     zrs_grad_end   = {200, 160, 255};
bool    zrs_reflected  = false;
uint8_t zrs_preset     = 0;

typedef struct {
    HSV  grad_start;
    HSV  grad_end;
    bool reflected;
} ZRS_PRESETS;

ZRS_PRESETS zrs_presets[] = {
    {{70, 240, 255}, {200, 160, 255}, false},
    {{70, 240, 255}, {190, 160, 255}, false},
    {{205, 250, 255}, {140, 215, 125}, false},
};

uint8_t color_adj_step = 5;
uint8_t zrs_preset_len = sizeof(zrs_presets) / sizeof(zrs_presets[0]);

enum ctrl_keycodes {
    U_T_AUTO = SAFE_RANGE,  // USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,               // USB Toggle Automatic GCR control
    DBG_TOG,                // DEBUG Toggle On / Off
    DBG_MTRX,               // DEBUG Toggle Matrix Prints
    DBG_KBD,                // DEBUG Toggle Keyboard Prints
    DBG_MOU,                // DEBUG Toggle Mouse Prints
    MD_BOOT,                // Restart into bootloader after hold timeout
    ZGS_HUI,                // Custom gradient color 1 hue increase
    ZGS_HUD,                // Custom gradient color 1 hue decrease
    ZGS_SAI,                // Custom gradient color 1 saturation increase
    ZGS_SAD,                // Custom gradient color 1 saturation decrease
    ZGS_VAI,                // Custom gradient color 1 value increase
    ZGS_VAD,                // Custom gradient color 1 value decrease
    ZGE_HUI,                // Custom gradient color 2 hue increase
    ZGE_HUD,                // Custom gradient color 2 hue decrease
    ZGE_SAI,                // Custom gradient color 2 saturation increase
    ZGE_SAD,                // Custom gradient color 2 saturation decrease
    ZGE_VAI,                // Custom gradient color 2 value increase
    ZGE_VAD,                // Custom gradient color 2 value decrease
    ZG_PRES,                // Gradient presets
    Z_REFL,                 // Toggle between linear and reflected gradient
    Z_FLIP,                 // Flip the gradient colors
    ZMOD,
};

keymap_config_t keymap_config;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KC_PSCR, KC_SLCK, KC_PAUS, \
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN, \
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                              KC_UP, \
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, ZMOD,   KC_APP,  KC_RCTL,            KC_LEFT, KC_DOWN, KC_RGHT \
    ),
    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            KC_MUTE, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   KC_MPLY, KC_MSTP, KC_VOLU, \
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, U_T_AUTO,U_T_AGCR,_______, _______, _______, _______, _______,   KC_MPRV, KC_MNXT, KC_VOLD, \
        _______, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______, _______, \
        _______, RGB_TOG, _______, _______, _______, MD_BOOT, NK_TOGG, _______, _______, _______, _______, _______,                              _______, \
        _______, _______, _______,                   _______,                            _______, ZMOD, _______, _______,            _______, _______, _______ \
    ),
    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, \
        _______, ZGS_HUD, ZGS_HUI, ZGS_SAD, ZGS_SAI, ZGS_VAD, ZGS_VAI, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, \
        _______, ZGE_HUD, ZGE_HUI, ZGE_SAD, ZGE_SAI, ZGE_VAD, ZGE_VAI, _______, _______, _______, _______, _______, _______, \
        _______, ZG_PRES,  Z_REFL,  Z_FLIP, _______, _______, _______, _______, _______, _______, _______, _______,                              _______, \
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______ \
    )
};
// clang-format on

// Runs just one time when the keyboard initializes.
void matrix_init_user(void){};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void){};

#define MODS_SHIFT (get_mods() & MOD_MASK_SHIFT)
#define MODS_CTRL (get_mods() & MOD_MASK_CTRL)
#define MODS_ALT (get_mods() & MOD_MASK_ALT)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

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
        case ZMOD:
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
                    } break;
                    case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER: {
                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    case LED_FLAG_UNDERGLOW: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_disable_noeeprom();
                    } break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        rgb_matrix_enable_noeeprom();
                    } break;
                }
            }
            return false;
        case ZGS_HUI:
            if (record->event.pressed) {
                zrs_grad_start.h += color_adj_step;  // Wraps around as 8-bit
                dprintf("grad_start: %d, %d, %d\n", zrs_grad_start.h, zrs_grad_start.s, zrs_grad_start.v);
            }
            return false;
        case ZGS_HUD:
            if (record->event.pressed) {
                zrs_grad_start.h -= color_adj_step;  // Wraps around as 8-bit
                dprintf("grad_start: %d, %d, %d\n", zrs_grad_start.h, zrs_grad_start.s, zrs_grad_start.v);
            }
            return false;
        case ZGS_SAI:
            if (record->event.pressed) {
                if (zrs_grad_start.s + color_adj_step > 255) {
                    zrs_grad_start.s = 255;  // Prevent overflows, cap it to 255
                } else {
                    zrs_grad_start.s += color_adj_step;
                }
                dprintf("grad_start: %d, %d, %d\n", zrs_grad_start.h, zrs_grad_start.s, zrs_grad_start.v);
            }
            return false;
        case ZGS_SAD:
            if (record->event.pressed) {
                if (zrs_grad_start.s - color_adj_step < 0) {
                    zrs_grad_start.s = 0;  // Prevent overflows, floor it to 0
                } else {
                    zrs_grad_start.s -= color_adj_step;
                }
                dprintf("grad_start: %d, %d, %d\n", zrs_grad_start.h, zrs_grad_start.s, zrs_grad_start.v);
            }
            return false;
        case ZGS_VAI:
            if (record->event.pressed) {
                if (zrs_grad_start.v + color_adj_step > 255) {
                    zrs_grad_start.v = 255;  // Prevent overflows, cap it to 255
                } else {
                    zrs_grad_start.v += color_adj_step;
                }
                dprintf("grad_start: %d, %d, %d\n", zrs_grad_start.h, zrs_grad_start.s, zrs_grad_start.v);
            }
            return false;
        case ZGS_VAD:
            if (record->event.pressed) {
                if (zrs_grad_start.v - color_adj_step < 0) {
                    zrs_grad_start.v = 0;  // Prevent overflows, floor it to 0
                } else {
                    zrs_grad_start.v -= color_adj_step;
                }
                dprintf("grad_start: %d, %d, %d\n", zrs_grad_start.h, zrs_grad_start.s, zrs_grad_start.v);
            }
            return false;
        case ZGE_HUI:
            if (record->event.pressed) {
                zrs_grad_end.h += color_adj_step;  // Wraps around as 8-bit
                dprintf("grad_end: %d, %d, %d\n", zrs_grad_end.h, zrs_grad_end.s, zrs_grad_end.v);
            }
            return false;
        case ZGE_HUD:
            if (record->event.pressed) {
                zrs_grad_end.h -= color_adj_step;  // Wraps around as 8-bit
                dprintf("grad_end: %d, %d, %d\n", zrs_grad_end.h, zrs_grad_end.s, zrs_grad_end.v);
            }
            return false;
        case ZGE_SAI:
            if (record->event.pressed) {
                if (zrs_grad_end.s + color_adj_step > 255) {
                    zrs_grad_end.s = 255;  // Prevent overflows, cap it to 255
                } else {
                    zrs_grad_end.s += color_adj_step;
                }
                dprintf("grad_end: %d, %d, %d\n", zrs_grad_end.h, zrs_grad_end.s, zrs_grad_end.v);
            }
            return false;
        case ZGE_SAD:
            if (record->event.pressed) {
                if (zrs_grad_end.s - color_adj_step < 0) {
                    zrs_grad_end.s = 0;  // Prevent overflows, cap it to 255
                } else {
                    zrs_grad_end.s -= color_adj_step;
                }
                dprintf("grad_end: %d, %d, %d\n", zrs_grad_end.h, zrs_grad_end.s, zrs_grad_end.v);
            }
            return false;
        case ZGE_VAI:
            if (record->event.pressed) {
                if (zrs_grad_end.v + color_adj_step > 255) {
                    zrs_grad_end.v = 255;  // Prevent overflows, cap it to 255
                } else {
                    zrs_grad_end.v += color_adj_step;
                }
                dprintf("grad_end: %d, %d, %d\n", zrs_grad_end.h, zrs_grad_end.s, zrs_grad_end.v);
            }
            return false;
        case ZGE_VAD:
            if (record->event.pressed) {
                if (zrs_grad_end.v - color_adj_step < 0) {
                    zrs_grad_end.v = 0;  // Prevent overflows, cap it to 255
                } else {
                    zrs_grad_end.v -= color_adj_step;
                }
                dprintf("grad_end: %d, %d, %d\n", zrs_grad_end.h, zrs_grad_end.s, zrs_grad_end.v);
            }
            return false;
        case ZG_PRES:
            if (record->event.pressed) {
                zrs_preset = (zrs_preset + 1) % zrs_preset_len;

                zrs_grad_start = zrs_presets[zrs_preset].grad_start;
                zrs_grad_end   = zrs_presets[zrs_preset].grad_end;
                zrs_reflected  = zrs_presets[zrs_preset].reflected;
            }
            return false;
        case Z_REFL:
            if (record->event.pressed) {
                zrs_reflected = !zrs_reflected;
            }
            return false;
        case Z_FLIP:
            if (record->event.pressed) {
                HSV temp_color = zrs_grad_start;
                zrs_grad_start = zrs_grad_end;
                zrs_grad_end   = temp_color;
            }
            return false;
        default:
            return true;  // Process all other keycodes normally
    }
}

void keyboard_post_init_user(void) {
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_ZRS_PULSE);
}
