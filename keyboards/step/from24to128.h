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

#ifndef FROM24TO128_H
#define FROM24TO128_H

#include "quantum.h"

// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define KEYMAP( \
    ll_f,                                                                         rr_f,\
    ll_c, ll_8, ll_4, ll_0, lr_0, lr_4, lr_8, rl_8, rl_4, rl_0, rr_0, rr_4, rr_8, rr_c,\
    ll_d, ll_9, ll_5, ll_1, lr_1, lr_5, lr_9, rl_9, rl_5, rl_1, rr_1, rr_5, rr_9, rr_d,\
    ll_e, ll_a, ll_6, ll_2, lr_2, lr_6, lr_a, rl_a, rl_6, rl_2, rr_2, rr_6, rr_a, rr_e,\
          ll_b, ll_7, ll_3, lr_3, lr_7, lr_b, rl_b, rl_7, rl_3, rr_3, rr_7, rr_b       \
) \
{ \
	{ ll_0, ll_1, ll_2, ll_3, ll_4, ll_5, ll_6, ll_7, ll_8, ll_9, ll_a, ll_b, ll_c,  ll_d,  ll_e,  ll_f  },\
	{ lr_0, lr_1, lr_2, lr_3, lr_4, lr_5, lr_6, lr_7, lr_8, lr_9, lr_a, lr_b, KC_NO, KC_NO, KC_NO, KC_NO },\
	{ rl_0, rl_1, rl_2, rl_3, rl_4, rl_5, rl_6, rl_7, rl_8, rl_9, rl_a, rl_b, KC_NO, KC_NO, KC_NO, KC_NO },\
	{ rr_0, rr_1, rr_2, rr_3, rr_4, rr_5, rr_6, rr_7, rr_8, rr_9, rr_a, rr_b, rr_c,  rr_d,  rr_e,  rr_f  },\
}

#define PLATE_NUM 4

#endif
