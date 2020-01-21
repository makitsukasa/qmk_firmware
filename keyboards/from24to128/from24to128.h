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
	p0kc, p0k8, p0k4, p0k0, p1k8, p1k4, p1k0, p2kc, p2k8, p2k4, p2k0, p3k8, p3k4, p3k0,\
	p0kd, p0k9, p0k5, p0k1, p1k9, p1k5, p1k1, p2kd, p2k9, p2k5, p2k1, p3k9, p3k5, p3k1,\
	p0ke, p0ka, p0k6, p0k2, p1ka, p1k6, p1k2, p2ke, p2ka, p2k6, p2k2, p3ka, p3k6, p3k2,\
	p0kf, p0kb, p0k7, p0k3, p1kb, p1k7, p1k3, p2kf, p2kb, p2k7, p2k3, p3kb, p3k7, p3k3 \
) \
{ \
	{ p0k0, p0k1, p0k2, p0k3, p0k4, p0k5, p0k6, p0k7, p0k8, p0k9, p0ka, p0kb, p0kc, p0kd, p0ke, p0kf },\
	{ p1k0, p1k1, p1k2, p1k3, p1k4, p1k5, p1k6, p1k7, p1k8, p1k9, p1ka, p1kb, KC_NO, KC_NO, KC_NO, KC_NO },\
	{ p2k0, p2k1, p2k2, p2k3, p2k4, p2k5, p2k6, p2k7, p2k8, p2k9, p2ka, p2kb, p2kc, p2kd, p2ke, p2kf },\
	{ p3k0, p3k1, p3k2, p3k3, p3k4, p3k5, p3k6, p3k7, p3k8, p3k9, p3ka, p3kb, KC_NO, KC_NO, KC_NO, KC_NO },\
}

#define PLATE_NUM 4

#endif
