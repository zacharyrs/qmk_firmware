#include "quantum/color.h"

extern HSV  zrs_grad_start;
extern HSV  zrs_grad_end;
extern bool zrs_reflected;

static HSV INTERPOLATE_HSV(float step, HSV grad_start, HSV grad_end) {
    uint8_t cw, ccw;
    HSV     color;

    cw  = (grad_start.h >= grad_end.h) ? 255 + grad_end.h - grad_start.h : grad_end.h - grad_start.h;  // Hue range is 0 to 255.
    ccw = (grad_start.h >= grad_end.h) ? grad_start.h - grad_end.h : 255 + grad_start.h - grad_end.h;

    if (cw < ccw) {  // going clockwise
        color.h = grad_start.h + (uint8_t)(step * cw);
    } else {  // Going counter clockwise
        color.h = grad_start.h - (uint8_t)(step * ccw);
    }

    color.s = grad_start.s + step * (grad_end.s - grad_start.s);

    // Scale V with global RGB Matrix's V, so users can still control overall brightness with RGB_VAI & RGB_VAD0
    color.v = round((grad_start.v + step * (grad_end.v - grad_start.v)) * ((float)rgb_matrix_config.hsv.v / 255));

    return color;
}

static HSV ZRS_PULSE_math(uint8_t led_x, uint8_t min_x, uint8_t max_x) {
    float step             = (float)led_x / (max_x - min_x);
    float mid_gradient_pos = 0.5;

    if (zrs_reflected) {
        if (step <= mid_gradient_pos) {
            return INTERPOLATE_HSV(step * (1 / mid_gradient_pos), zrs_grad_start, zrs_grad_end);
        } else {
            return INTERPOLATE_HSV((step - mid_gradient_pos) * (1 / (1 - mid_gradient_pos)), zrs_grad_end, zrs_grad_start);
        }

    } else {
        return INTERPOLATE_HSV(step, zrs_grad_start, zrs_grad_end);
    }
}

static bool ZRS_PULSE(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t min_x = 0;    // X coordinate of the left-most LED
    uint8_t max_x = 224;  // X coordinate of the right-most LED

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();

        HSV hsv_orig = ZRS_PULSE_math(g_led_config.point[i].x, min_x, max_x);
        RGB rgb      = hsv_to_rgb(hsv_orig);

        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    return led_max < DRIVER_LED_TOTAL;
}
