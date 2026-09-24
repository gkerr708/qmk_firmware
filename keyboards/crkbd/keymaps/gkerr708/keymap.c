/*
Flashing (Blok / RP2040, CONVERT_TO=blok):
  1. Unplug the half you want to flash.
  2. Run:  qmk flash -kb crkbd -km gkerr708
     and wait for it to say it is waiting for the bootloader.
  3. Plug the half in while holding BOOT and tapping RESET
     (or hold the top-left key while plugging in for Bootmagic on the left half).
  4. It shows up as the RPI-RP2 drive. If it does not auto-mount:
       lsblk -f
       udisksctl mount -b /dev/sdX1
  5. The .uf2 copies over and the half reboots itself. Repeat for the other half.
*/

#include QMK_KEYBOARD_H
#ifdef OLED_ENABLE


bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_P(PSTR("CRKBD (v1.13)\n"), false);
        }
    else{
        oled_write_P(PSTR("CRKBD (v1.13)"), false);
        }
    return false;
}
#endif



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        MO(2),    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
  //| --------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT, KC_LSFT, MO(1),     KC_ESC,  KC_SPC, KC_LGUI
                                      //`--------------------------'  `--------------------------'
  ),

    [1] = LAYOUT_split_3x6_3(
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
    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT, KC_MUTE,_______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, KC_VOLD, KC_VOLU,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_F11,  KC_F12, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_BRID, KC_BRIU, KC_CALC, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, KC_CAPS, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};
