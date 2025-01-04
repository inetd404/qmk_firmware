// Copyright 2022 Mark Stosberg (@markstos)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  FUNC,
  BACKLIT
};

/* status variables */
int   current_wpm = 0;
led_t led_usb_state;

// enum combos {
//   DF_DASH,
//   JK_ESC
// };

const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};

 combo_t key_combos[COMBO_COUNT] = {
//   // Add commonly used dash to home row
//   [DF_DASH]    = COMBO(df_combo, KC_MINS),
//   // For Vim, put Escape on the home row
//   [JK_ESC]    = COMBO(jk_combo, KC_ESC),
};

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_DEL  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 OSM(MOD_LSFT), LGUI_T(KC_A),LALT_T(KC_S), LSFT_T(KC_D), LCTL_T(KC_F), KC_G, KC_H ,RCTL_T(KC_J) ,RSFT_T(KC_K) ,LALT_T(KC_L), RGUI_T(KC_QUOT), LT_GAME,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     OSM_LCTL,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                     KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,OSL_FUN ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_ESC, KC_ENT, LOW_TAB,       RSE_SPC ,KC_BSPC ,KC_DEL
                                      //`--------------------------'  `--------------------------'
  ),

  [_LOWER] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_EXLM, KC_AT,  KC_HASH, KC_DLR,  KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_QUES ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_1,    KC_2,   KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX , KC_TILD,KC_GRV, KC_LBRC, KC_LCBR,                       KC_RCBR, KC_RBRC, KC_COMM,KC_DOT,  KC_SLSH, _______ ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS,  KC_TRNS, LOWER,    KC_TRNS, KC_TRNS, KC_COLON
                                      //`--------------------------'  `--------------------------'
  ),

  [_RAISE] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    KC_INSERT, KC_DEL , XXXXXXX, KC_UNDS, KC_PLUS, KC_PGUP,                      XXXXXXX, XXXXXXX, KC_UP, KC_BSLS, KC_PIPE,KC_QUES ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_HOME, KC_END , KC_MINS, KC_EQL , KC_PGDN,                      XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_APP ,_______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LT  , KC_GT  , KC_COPY, XXXXXXX, XXXXXXX,                      KC_MPLY, KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU,_______ ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          CTL_ESC, KC_TRNS, XXXXXXX,    RAISE  , KC_TRNS, KC_TRNS
                                      //`--------------------------'  `--------------------------'
  ),

  [_FUNC] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_F1  , KC_F2  , KC_F3   , KC_F4 ,  KC_F5 ,                     KC_F6   , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,_______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_F11 , KC_F12 , XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX , KC_RCTL, KC_RSFT, KC_RALT, KC_RGUI,_______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, FUNC   , XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [_NUM] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX ,                    KC_KP_7,  KC_KP_8, KC_KP_9, KC_KP_MINUS, KC_EQUAL,       _______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     KC_KP_4,  KC_KP_5, KC_KP_6, KC_KP_PLUS,  KC_KP_SLASH,    _______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     KC_KP_1,  KC_KP_2, KC_KP_3, KC_KP_ENTER, KC_KP_ASTERISK, XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_ESC, KC_ENT, KC_TAB,      KC_ENT,  KC_KP_0,  KC_KP_DOT
                                      //`--------------------------'  `--------------------------'
  ),

  [_GAME] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                        XXXXXXX, XXXXXXX, XXXXXXX, KC_O,    XXXXXXX, XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_LEFT_SHIFT, KC_A, KC_S,   KC_D,    KC_F,    KC_G,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_LCTL,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LEFT_ALT, KC_SPC, MO(_GAME1),  XXXXXXX, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [_GAME1] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ESC,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
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

#ifdef OLED_ENABLE
/* 32 * 32 logo */
static void render_logo(void) {
    // HTML <> Hell Logo
    //static const char PROGMEM logo[] = {0x00, 0x80, 0xc0, 0xc0, 0x60, 0x60, 0x30, 0x30, 0x18, 0x1c, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x78, 0x1e, 0x06, 0x00, 0x0c, 0x1c, 0x18, 0x30, 0x30, 0x60, 0x60, 0xc0, 0xc0, 0x80, 0x00, 0x01, 0x03, 0x07, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x70, 0x60, 0x00, 0xc0, 0xf0, 0x3c, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x60, 0x70, 0x30, 0x18, 0x18, 0x0c, 0x0c, 0x06, 0x07, 0x03, 0x01, 0x00, 0xf8, 0xf8, 0x80, 0x80, 0x80, 0xf8, 0xf8, 0x00, 0x80, 0xc0, 0xc0, 0x40, 0xc0, 0xc0, 0x80, 0x00, 0xf8, 0xf8, 0x00, 0xf8, 0xf8, 0x00, 0x08, 0x38, 0x08, 0x00, 0x38, 0x08, 0x30, 0x08, 0x38, 0x00, 0x1f, 0x1f, 0x01, 0x01, 0x01, 0x1f, 0x1f, 0x00, 0x0f, 0x1f, 0x1a, 0x12, 0x1a, 0x1b, 0x0b, 0x00, 0x1f, 0x1f, 0x00, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    // Doom Logo
    static const char PROGMEM logo[] = {0x00,0xFC,0xFC,0x0C,0x0C,0x0C,0xFC,0xF8,0x00,0xF8,0xFC,0x0C,0x0C,0xFC,0xF8,0x00,0xF8,0xFC,0x0C,0x0C,0xFC,0xF8,0x00,0xFC,0xFC,0xF8,0xC0,0xC0,0xF8,0xFC,0xFC,0x00,0x00,0xFF,0xFF,0x80,0xC0,0xE0,0x7F,0x3F,0x00,0x3F,0x7F,0xE0,0xE0,0x7F,0x3F,0x00,0x3F,0x7F,0xE0,0xE0,0x7F,0x3F,0x00,0x3F,0x7F,0x03,0x3F,0xFF,0x03,0xFF,0xFF,0x00,0x00,0x7F,0x1F,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x1F,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,};

    oled_write_raw_P(logo, sizeof(logo));
}

static void print_logo_narrow(void) {
    render_logo();

    /* wpm counter */
    uint8_t n = get_current_wpm();
    char    wpm_str[4];
    oled_set_cursor(1, 4);
    wpm_str[3] = '\0';
    wpm_str[2] = '0' + n % 10;
    wpm_str[1] = '0' + (n /= 10) % 10;
    wpm_str[0] = '0' + n / 10;
    oled_write(wpm_str, false);

    oled_set_cursor(0, 5);
    oled_write(" FPS", false);
}

static void print_status_narrow(void) {

    render_logo();

    uint8_t current_layer = get_highest_layer(layer_state);

    /* Print current mode */
    oled_set_cursor(0, 4);
    //oled_write(msg1[current_layer], false);
    switch (current_layer) {
        case _QWERTY:
            oled_write("QWRTY", false);
            break;
        case _GAME:
            oled_write("GAME ", true);
            break;
        case _NUM:
            oled_write(" NUM ", true);
            break;            
        default:
            oled_write("--?--", true);
    }

    oled_set_cursor(0, 6);
    switch (current_layer) {
        case _QWERTY:
            oled_write(".....", false);
            break;
        case _GAME:
            oled_write(".....", false);
            break;
        case _NUM:
            oled_write(".....", false);
            break;            
        default:
            oled_write("-Mod-", true);
    }
 
    oled_set_cursor(0, 8);
    switch (current_layer) {
        case _QWERTY:
            oled_write("Q Def", false);
            break;
        case _LOWER:
            oled_write("Lower", false);
            break;
        case _RAISE:
            oled_write("Raise", false);
            break;
        case _FUNC: 
            oled_write("Func ", false);
            break;
        case _NUM:
            oled_write("Num1 ", false);
            break;
        case _GAME:
            oled_write("G Def", false);
            break;
        case _GAME1:
            oled_write("Game1", false);
            break;            
        default:
            oled_write("--?--", false);
    }

    /* caps lock */
    oled_set_cursor(0, 10);
    if (led_usb_state.caps_lock) {
        oled_write("CAPS ",true);
    } else {
        oled_write(".....",false);
    }    
    

}

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

bool oled_task_user(void) {

    current_wpm   = get_current_wpm();
    led_usb_state = host_keyboard_led_state();

    /* KEYBOARD PET VARIABLES END */

    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        print_logo_narrow();
    }
    return false;
}
#endif