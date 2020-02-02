/*
Copyright 2019 MakiTsukasa

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "keymap_jp.h"
#include "from24to128.h"
#include "bpm.h"

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define TXLED0 PORTD |= (1<<5)
#define TXLED1 PORTD &= ~(1<<5)
#define RXLED0 PORTB |= (1<<0)
#define RXLED1 PORTB &= ~(1<<0)

#define LTMH(layer) LT(layer, KC_MHEN)
#define LTHE(layer) LT(layer, KC_HENK)
#define SandC LCTL_T(KC_SPC)

enum boxy_keycodes {
    SandS_1 = SAFE_RANGE,
    SandS_3,
};

static bool shift_pressed = false;
static bool modkey_pressed = false; // 修飾キーを押下中のフラグ
uint16_t key_timer; // 親指のSandSの長押し時間用タイマー

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// default
	[0] = KEYMAP( \
		// +--------+                                                                                                              +--------+
			KC_ESC,                                                                                                                 KC_DEL,
		// +--------+--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+--------+
			KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,       KC_DEL,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
		// +--------+--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+--------+
			JP_MINS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,       JP_LBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
		// +--------+--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+--------+
			XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,       JP_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, XXXXXXX,
		// +--------+--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+--------+

		//          +--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+
			         KC_LGUI, KC_LALT, XXXXXXX, LTMH(2), SandS_1, SandC,      SandC,   SandS_1, LTHE(2), XXXXXXX, KC_F2,   KC_APP
		//          +--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+
	),
	// shift
	[1] = KEYMAP( \
		// +--------+                                                                                                              +--------+
			_______,                                                                                                                _______,
		// +--------+--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+--------+
			_______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
		// +--------+--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+--------+
			JP_UNDS, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, JP_COLN, _______,
		// +--------+--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+--------+
			_______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
		// +--------+--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+--------+

		//          +--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+
			         _______, _______, _______, MO(3),   _______, _______,    _______, _______, MO(3),   _______, _______, _______
		//          +--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+
	),
	// nums and arrows
	[2] = KEYMAP( \
		// +--------+                                                                                                              +--------+
			_______,                                                                                                                _______,
		// +--------+--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+--------+
			_______, JP_GRV,  JP_MINS, JP_EQL,  JP_QUOT, JP_YEN,  _______,    _______, _______, _______, _______, _______, _______, _______,
		// +--------+--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+--------+
			_______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,    _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
		// +--------+--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+--------+
			_______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,    _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
		// +--------+--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+--------+

		//          +--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+
			         _______, _______, _______, _______, SandS_3, _______,    _______, SandS_3, _______, _______, KC_PSCR, _______
		//          +--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+
	),
	// shift nums and arrows
	[3] = KEYMAP( \
		// +--------+                                                                                                              +--------+
			_______,                                                                                                                _______,
		// +--------+--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+--------+
			_______, JP_TILD, JP_UNDS, JP_PLUS, JP_DQT,  JP_PIPE,  _______,   _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
		// +--------+--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+--------+
			_______, JP_EXLM, JP_AT,   JP_HASH, JP_DLR,  JP_PERC, _______,    _______, _______, _______, _______, _______, _______, _______,
		// +--------+--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+--------+
			_______, JP_CIRC, JP_AMPR, JP_ASTR, JP_LPRN, JP_RPRN, _______,    _______, _______, _______, _______, _______, _______, _______,
		// +--------+--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+--------+

		//          +--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+
			         _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______
		//          +--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+
	),
	// function keys
    /*
	[4] = KEYMAP( \
		// +--------+--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+--------+
			_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,      KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
		// +--------+--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+--------+
			_______, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX,    RESET,   XXXXXXX, KC_MUTE, KC_VOLU, KC_VOLD, XXXXXXX, _______,
		// +--------+--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+--------+
			_______, XXXXXXX, KC_BTN1, KC_BTN3, KC_BTN2, XXXXXXX, XXXXXXX,    EEP_RST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
		// +--------+--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+--------+
			_______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______
		// +--------+--------+--------+--------+--------+--------+--------+  +--------+--------+--------+--------+--------+--------+--------+
	),
    */
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	return MACRO_NONE;
}

// https://qiita.com/Nymphium/items/2775b8c3555f733fafdc
// users/ridingqwerty/process_record.c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
	case KC_LGUI: // Winキー
	case KC_LALT: // 左Alt
	case KC_LCTRL: // 左Ctrl
		if (record->event.pressed) {
			register_code(keycode);
			modkey_pressed = true;
		}
		else {
			unregister_code(keycode);
			modkey_pressed = false;
		}
		return false;

	case SandS_1:
		if (record->event.pressed) {
			register_code(KC_LSFT);
            key_timer = timer_read();
			if (!modkey_pressed) { // modキーを押下していないときのみレイヤーを切り替える
				shift_pressed = true;
                layer_on(1);
			}
		}
        else {
			unregister_code(KC_LSFT);
			if (shift_pressed) {
				shift_pressed = false;
				layer_off(1);
			}
            if (timer_elapsed(key_timer) < TAPPING_TERM) {
                tap_code(KC_SPC);
            }
        }
		return false;

	case SandS_3:
		if (record->event.pressed) {
			register_code(KC_LSFT);
            key_timer = timer_read();
			if (!modkey_pressed) { // modキーを押下していないときのみレイヤーを切り替える
				shift_pressed = true;
                layer_on(3);
			}
		}
        else {
			unregister_code(KC_LSFT);
			if (shift_pressed) {
				shift_pressed = false;
				layer_off(3);
			}
            if (timer_elapsed(key_timer) < TAPPING_TERM) {
                tap_code(KC_SPC);
            }
        }
		return false;

    case JP_COLN:
    case JP_UNDS:
    case JP_AT:
		if (record->event.pressed) {
			unregister_code(KC_LSFT);
			register_code(keycode);
		}
		else {
            unregister_code(keycode);
            if (shift_pressed) register_code(KC_LSFT);
		}
		return true;

	default:
		return true;
	}
}
