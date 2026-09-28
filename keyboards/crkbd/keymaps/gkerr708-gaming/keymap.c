/*
Flashing (Blok / RP2040, CONVERT_TO=blok):
  1. Unplug the half you want to flash.
  2. Run:  qmk flash -kb crkbd -km gkerr708-gaming
     and wait for it to say it is waiting for the bootloader.
  3. Plug the half in while holding BOOT and tapping RESET
     (or hold the top-left key while plugging in for Bootmagic on the left half).
  4. It shows up as the RPI-RP2 drive. If it does not auto-mount:
       lsblk -f
       udisksctl mount -b /dev/sdX1
  5. The .uf2 copies over and the half reboots itself. Repeat for the other half.
*/

#include QMK_KEYBOARD_H

// Layer order matters: the highest active layer wins, so NUM/NAV/GAMING sit on
// top of the game layers and stay reachable while a game is active.
enum layers {
    _BASE,
    _CSGO,
    _SC_A,
    _SC_B,
    _DOTA_A,
    _DOTA_B,
    _NUM,
    _NAV,
    _GAMING,
};

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_P(PSTR("CRKBD (v1.13)\n"), false);
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case _BASE:   oled_write_P(PSTR("Layer: MAIN\n"), false); break;
            case _CSGO:   oled_write_P(PSTR("Layer: CSGO\n"), false); break;
            case _SC_A:   oled_write_P(PSTR("Layer: SCII (A)\n"), false); break;
            case _SC_B:   oled_write_P(PSTR("Layer: SCII (B)\n"), false); break;
            case _DOTA_A: oled_write_P(PSTR("Layer: DOTA (A)\n"), false); break;
            case _DOTA_B: oled_write_P(PSTR("Layer: DOTA (B)\n"), false); break;
            case _NUM:    oled_write_P(PSTR("Layer: NUM\n"), false); break;
            case _NAV:    oled_write_P(PSTR("Layer: NAV\n"), false); break;
            case _GAMING: oled_write_P(PSTR("Layer: GAMING\n"), false); break;
            default:      oled_write_P(PSTR("Layer: Undefined\n"), false); break;
        }
    } else {
        oled_write_P(PSTR("CRKBD (v1.13)"), false);
    }
    return false;
}
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
   MO(_NAV),    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
  //| --------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT, KC_LSFT, MO(_NUM),   KC_ESC,  KC_SPC, KC_LGUI
                                      //`--------------------------'  `--------------------------'
  ),

    // CSGO
    [_CSGO] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         KC_5,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_VOLD, KC_VOLU,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_MPLY, XXXXXXX,MO(_GAMING), KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL,    KC_3,    KC_2,    KC_ESC,  KC_SPC, KC_LCTL
                                      //`--------------------------'  `--------------------------'
  ),
    // starcraft (a)
    [_SC_A] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         KC_K,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_VOLD, KC_VOLU,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 LM(_SC_B,MOD_LCTL),  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                    KC_N,    KC_M, KC_MPLY, XXXXXXX,MO(_GAMING), KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                          LM(_SC_B,MOD_LALT), MO(_SC_B), LM(_SC_B,MOD_LSFT),    KC_ESC,  KC_SPC, KC_LCTL
                                      //`--------------------------'  `--------------------------'
  ),
    // starcraft (B)
    [_SC_B] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),
    // dota (a)
    [_DOTA_A] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         KC_0,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT, MO(_DOTA_B),  KC_SPC,     KC_ESC,  KC_SPC, KC_LCTL
                                      //`--------------------------'  `--------------------------'
  ),
    // dota (B)
    [_DOTA_B] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_F11,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT, KC_MUTE,_______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      _______, _______, _______, _______, KC_VOLD, KC_VOLU,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          MO(_GAMING), _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    // NUM
    [_NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
 LSFT(KC_GRV),    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_PPLS, KC_PMNS, KC_PAST,  KC_EQL, KC_AMPR,  KC_DLR,                      KC_UNDS, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_GRV, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_LBRC, KC_RBRC, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),
    // NAV
    [_NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT, KC_MUTE,_______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, KC_VOLD, KC_VOLU,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     MO(_GAMING), KC_F12, KC_F12,XXXXXXX, XXXXXXX, XXXXXXX,                      KC_BRID, KC_BRIU, KC_CALC, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, KC_CAPS, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),
    // GAMING: hold NAV, then hold the "Z" key (this slot), then tap a selector with the right hand.
    // DF() sets the base layer, so a stray tap can never leave a game stuck "toggled".
    [_GAMING] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   DF(_BASE), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX, DF(_CSGO),DF(_SC_A),DF(_DOTA_A)
                                      //`--------------------------'  `--------------------------'
  )
};
