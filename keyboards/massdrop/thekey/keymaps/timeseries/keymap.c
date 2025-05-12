/* Copyright 2021 Joe Maples <joe@maples.dev>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#define LY_BASE  0
#define LV_MOUSE 1

enum custom_keycodes {
    TK_URL = SAFE_RANGE,
};

// Tap Dance declarations
enum {
    TD_ENT_MOUSE,
};

// Setup Layers to flash the button after a key is pressed 
const rgblight_segment_t PROGMEM _key_layer[] = RGBLIGHT_LAYER_SEGMENTS( 
    {0, 6, HSV_RED} 
);
const rgblight_segment_t PROGMEM _no_layer[]  = RGBLIGHT_LAYER_SEGMENTS( 
    {0, 6, HSV_RED} 
);
const rgblight_segment_t* const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST( 
    _key_layer, 
    _no_layer 
);

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_ENT_MOUSE] = ACTION_TAP_DANCE_DOUBLE(KC_ENT, KC_BTN1),
};

// Enable breathing mode again after the button has stopped flashing
uint32_t callback_postkey(uint32_t trigger_time, void *cb_arg) {
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3); // sets mode to Fast breathing without saving
    return 0;
}

// Button is a momentary so can't be held. Default is enter & tap dance presses left mouse button, 
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    [0] = LAYOUT(TK_URL, MT(KC_MS_BTN1, KC_ENT) , KC_ESC),
    [LY_BASE]  = LAYOUT(LT(LV_MOUSE, KC_ENT), TD(TD_ENT_MOUSE), KC_ESC),
    [LV_MOUSE] = LAYOUT(KC_BTN1,              KC_A,             KC_ESC),
//  [0] = LAYOUT(TK_URL, QK_MOUSE_BUTTON_1, KC_ESC),
//  [0] = LAYOUT(TK_URL, KC_ENT, KC_ESC),
};

// turn off background & set the lights to flash after any key has been pressed, callback to enable breathing again
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    static deferred_token idle_token = INVALID_DEFERRED_TOKEN;

    switch (keycode) {
        case TK_URL:
            if (record->event.pressed) {
                SEND_STRING("Time Series Uplift Deployed: Ross, Nathan, Sasa, Alex, Tom, Adarsh, Kapil & Dameon\n");
            }
            break;
        default:
            break;
    }
    
    // Turn off the RB Light Mode, blink & set a callback to enable RB light mode again
    rgblight_disable_noeeprom();
    rgblight_blink_layer_repeat(0, 100, 5);
    if (!extend_deferred_exec(idle_token, 1000)) {
        idle_token = defer_exec(1000, callback_postkey, NULL);
      }  

    return true;
}

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {

  rgblight_enable_noeeprom(); // enables RGB, without saving settings
  rgblight_sethsv_noeeprom(HSV_RED); // sets the color to red without saving
  rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3); // sets mode to Fast breathing without saving

  rgblight_layers = _rgb_layers;
}
#endif
