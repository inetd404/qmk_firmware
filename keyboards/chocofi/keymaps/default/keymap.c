#include QMK_KEYBOARD_H
#include <stdio.h>

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  FUNC,
  BACKLIT
};

enum custom_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _FUNC,
  _NUM,  
  _GAME,
  _GAME1,
};

const char msg1[7][5]={
  [_QWERTY] ="QWRTY",
  [_LOWER]  ="QWRTY",
  [_RAISE]  ="QWRTY",
  [_FUNC]   ="QWRTY",
  [_NUM]    ="QWRTY",
  [_GAME]   ="GAME ",
  [_GAME1]  ="GAME ",
};

int max_layers=6;

// For _QWERTY layer
#define OSM_LCTL OSM(MOD_LCTL)
#define OSM_AGR  OSM(MOD_RALT)
#define OSL_FUN  OSL(_FUNC)
#define GUI_ENT  GUI_T(KC_ENT)
#define LOW_TAB  LT(_LOWER, KC_TAB)
#define RSE_SPC  LT(_RAISE, KC_SPC)
#define OSM_SFT  OSM(MOD_LSFT)
#define LT_GAME  LT(0,KC_SCLN)

// For _RAISE layer
#define CTL_ESC  LCTL_T(KC_ESC)

// Define the keycode, `QK_USER` avoids collisions with existing keycodes
enum keycodes {
  KC_CYCLE_LAYERS = QK_USER,
};

/* 
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x5_3(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                                   KC_LGUI, KC_BSPC, KC_SPC,           KC_SPC,  KC_ENT,  KC_RALT
    )
};
*/


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x5_3(
   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,
   LGUI_T(KC_A),LALT_T(KC_S), LSFT_T(KC_D), LCTL_T(KC_F), KC_G, KC_H ,RCTL_T(KC_J) ,RSFT_T(KC_K) ,LALT_T(KC_L), RGUI_T(KC_QUOT),
   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                     KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,
                                KC_ESC, KC_ENT, LOW_TAB,       RSE_SPC ,KC_BSPC ,KC_DEL
  ),

  [_LOWER] = LAYOUT_split_3x5_3(
     KC_EXLM, KC_AT,  KC_HASH, KC_DLR,  KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
     KC_1,    KC_2,   KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, 
     XXXXXXX , KC_TILD,KC_GRV, KC_LBRC, KC_LCBR,                       KC_RCBR, KC_RBRC, KC_COMM,KC_DOT,  KC_SLSH,
                                  KC_TRNS,  KC_TRNS, LOWER,    KC_TRNS, KC_TRNS, KC_COLON
  ),

  [_RAISE] = LAYOUT_split_3x5_3(
    KC_DEL , KC_INSERT, KC_UNDS, KC_PLUS, KC_PGUP,                      XXXXXXX, KC_UP,   KC_BSLS, KC_PIPE, KC_QUES, 
    KC_HOME, KC_END   , KC_MINS, KC_EQL , KC_PGDN,                      XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_APP,
    KC_LT  , KC_GT    , KC_COPY, XXXXXXX, XXXXXXX,                      KC_MPLY, KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU,
                                  CTL_ESC, KC_TRNS, XXXXXXX,    RAISE  , KC_TRNS, KC_TRNS
  ),

  [_FUNC] = LAYOUT_split_3x5_3(
      KC_F1  , KC_F2  , KC_F3   , KC_F4 ,  KC_F5 ,                     KC_F6   , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,
      KC_F11 , KC_F12 , XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX , KC_RCTL, KC_RSFT, KC_RALT, KC_RGUI,
      KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
                                  XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, FUNC   , XXXXXXX
  ),

  [_NUM] = LAYOUT_split_3x5_3(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     KC_KP_7,  KC_KP_8, KC_KP_9, KC_KP_MINUS, KC_EQUAL,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     KC_KP_4,  KC_KP_5, KC_KP_6, KC_KP_PLUS,  KC_KP_SLASH,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     KC_KP_1,  KC_KP_2, KC_KP_3, KC_KP_ENTER, KC_KP_ASTERISK,
                                    KC_ESC, KC_ENT, KC_TAB,      KC_ENT,  KC_KP_0,  KC_KP_DOT
  ),

  [_GAME] = LAYOUT_split_3x5_3(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                    XXXXXXX, XXXXXXX, XXXXXXX, KC_O,    XXXXXXX,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          KC_LEFT_ALT, KC_SPC, MO(_GAME1),  XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_GAME1] = LAYOUT_split_3x5_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ESC,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX
  )

};

// sets tapping term per key rules
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case LT(_RAISE, KC_BSPC):
            return TAPPING_TERM_THUMB;
      case LT(_LOWER, KC_TAB):
            return TAPPING_TERM_THUMB;
      default:
            return TAPPING_TERM;
    }
}


// 1st layer on the cycle
#define LAYER_CYCLE_START 0
// Last layer on the cycle
#define LAYER_CYCLE_END   max_layers

// Add the behaviour of this new keycode
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    case LT_GAME:
        if (!record->tap.count && record->event.pressed) {
            //tap_code16(KC_CYCLE_LAYERS); // Intercept hold function to send game mode change
            switch (get_highest_layer(layer_state)) {
                case _GAME:
                    layer_move(_NUM);
                    break;
                case _NUM:
                    layer_move(_QWERTY);
                    break;
                default:
                    layer_move(_GAME);
            } 
            return false;
        }
        return true; // Return true for normal processing of tap keycode
/*
    case KC_CYCLE_LAYERS:
      // Our logic will happen on presses, nothing is done on releases
      if (!record->event.pressed) { 
        // Keyup
        // We've already handled the keycode (doing nothing), let QMK know so no further code is run unnecessarily
        return false;
      }
      
      uint8_t current_layer = get_highest_layer(layer_state);

      // Check if we are within the range, if not quit
      if (current_layer > LAYER_CYCLE_END || current_layer < LAYER_CYCLE_START) {
        return false;
      }

      uint8_t next_layer = current_layer + 1;
      if (next_layer > LAYER_CYCLE_END) {
          next_layer = LAYER_CYCLE_START;
      } 

      switch (get_highest_layer(layer_state)) {
        case _GAME:
            layer_move(_QWERTY);
            break;
        default:
            layer_move(_GAME);
      }      
      return false;
*/;
    // Process other keycodes normally
    default:
      return true;
  }
}