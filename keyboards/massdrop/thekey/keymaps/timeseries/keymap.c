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

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_ENT_MOUSE] = ACTION_TAP_DANCE_DOUBLE(KC_ENT, KC_BTN1),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    [0] = LAYOUT(TK_URL, MT(KC_MS_BTN1, KC_ENT) , KC_ESC),
    [LY_BASE]  = LAYOUT(LT(LV_MOUSE, KC_ENT), TD(TD_ENT_MOUSE), KC_ESC),
    [LV_MOUSE] = LAYOUT(KC_BTN1,              KC_A,             KC_ESC),
//  [0] = LAYOUT(TK_URL, QK_MOUSE_BUTTON_1, KC_ESC),
//  [0] = LAYOUT(TK_URL, KC_ENT, KC_ESC),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TK_URL:
            if (record->event.pressed) {
                SEND_STRING("Time Series Uplift Deployed: Ross, Nathan, Sasa, Alex, Tom, Adarsh, Kapil & Dameon\n");
            }
            break;
        default:
            break;
    }
    return true;
}
