/*
Copyright 2012-2017 Jun Wako, Jack Humbert

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
/* Copyright 2017 MakotoKurauchi <http://yushakobo.jp/>
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


#include <stdint.h>
#include <stdbool.h>
#if defined(__AVR__)
#include <avr/io.h>
#endif
#include "wait.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "timer.h"
#include "i2cmaster.h"
#include "mcp23017.h"
#include "expander.h"
#include "from24to128.h"

/* Set 0 if debouncing isn't needed */

#ifndef DEBOUNCING_DELAY
#define DEBOUNCING_DELAY 10
#endif

#if (DEBOUNCING_DELAY > 0)
static uint16_t debouncing_time;
static bool debouncing = false;
#endif

#if (MATRIX_COLS <= 8)
#define print_matrix_header()  print("\nr/c 01234567\n")
#define print_matrix_row(row)  print_bin_reverse8(matrix_get_row(row))
#define matrix_bitpop(i)       bitpop(matrix[i])
#define ROW_SHIFTER ((uint8_t)1)
#elif (MATRIX_COLS <= 16)
#define print_matrix_header()  print("\nr/c 0123456789ABCDEF\n")
#define print_matrix_row(row)  print_bin_reverse16(matrix_get_row(row))
#define matrix_bitpop(i)       bitpop16(matrix[i])
#define ROW_SHIFTER ((uint16_t)1)
#elif (MATRIX_COLS <= 32)
#define print_matrix_header()  print("\nr/c 0123456789ABCDEF0123456789ABCDEF\n")
#define print_matrix_row(row)  print_bin_reverse32(matrix_get_row(row))
#define matrix_bitpop(i)       bitpop32(matrix[i])
#define ROW_SHIFTER  ((uint32_t)1)
#endif

#define TXLED0 PORTD |= (1<<5)
#define TXLED1 PORTD &= ~(1<<5)
#define RXLED0 PORTB |= (1<<0)
#define RXLED1 PORTB &= ~(1<<0)

#ifdef MATRIX_MASKED
extern const matrix_row_t matrix_mask[];
#endif

static const uint8_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const uint8_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[PLATE_NUM];

static matrix_row_t matrix_debouncing[PLATE_NUM];

static bool read_plate(matrix_row_t current_matrix[], uint8_t current_row);

__attribute__ ((weak)) void matrix_init_quantum(void) {
    matrix_init_kb();
}

__attribute__ ((weak)) void matrix_scan_quantum(void) {
    matrix_scan_kb();
}

__attribute__ ((weak)) void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__ ((weak)) void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__ ((weak)) void matrix_init_user(void) {
}

__attribute__ ((weak)) void matrix_scan_user(void) {
}

inline uint8_t matrix_rows(void) {
    return MATRIX_ROWS;
}

inline uint8_t matrix_cols(void) {
    return MATRIX_COLS;
}

void matrix_init(void) {
    debug_enable = true;

    TXLED0;
    RXLED0;
    // expander_init(0);
    // expander_init(1);
    // expander_init(2);
    // expander_init(3);
    // return;

    // all pin read mode
    for (uint8_t p = 0; p < PLATE_NUM; p++) {
        expander_init(p);
        if(expander_write(p, EXPANDER_REG_GPPUA, 0xff)) TXLED1;
        if(expander_write(p, EXPANDER_REG_GPPUB, 0xff)) TXLED1;
        if(expander_write(p, EXPANDER_REG_IPOLA, 0xff)) TXLED1;
        if(expander_write(p, EXPANDER_REG_IPOLB, 0xff)) TXLED1;
    }

    // To use PORTF disable JTAG with writing JTD bit twice within four cycles.
#if (defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__) || defined(__AVR_ATmega32U4__))
    MCUCR |= _BV(JTD);
    MCUCR |= _BV(JTD);
#endif

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < PLATE_NUM; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    // do nothing
    // return 0;

    // test
    // uint8_t data[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    // for(uint8_t i = 0; i < 4; i++){
    //     if(expander_read(i, EXPANDER_REG_GPIOA, &data[i])) TXLED1;
    //     if(expander_read(i, EXPANDER_REG_GPIOB, &data[i+4])) TXLED1;
    // }
    // if(data[0] || data[1] || data[2] || data[3] || data[4] || data[5] || data[6] || data[7]) RXLED1;
    // else RXLED0;
    // return 0;

    for (uint8_t current_plate = 0; current_plate < PLATE_NUM; current_plate++) {
#if (DEBOUNCING_DELAY > 0)
        bool matrix_changed = read_plate(matrix_debouncing, current_plate);

        if (matrix_changed) {
            debouncing = true;
            debouncing_time = timer_read();
        }
#else
        read_plate(matrix, current_plate);
#endif

    }

#if (DEBOUNCING_DELAY > 0)
    if (debouncing && (timer_elapsed(debouncing_time) > DEBOUNCING_DELAY)) {
        for (uint8_t i = 0; i < PLATE_NUM; i++) {
            matrix[i] = matrix_debouncing[i];
        }
        debouncing = false;
    }
#endif

    matrix_scan_quantum();
    return 1;
}

bool matrix_is_modified(void)
{
#if (DEBOUNCING_DELAY > 0)
    if (debouncing) return false;
#endif
    return true;
}

inline bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<col));
}

inline matrix_row_t matrix_get_row(uint8_t row)
{
    // Matrix mask lets you disable switches in the returned matrix data. For example, if you have a
    // switch blocker installed and the switch is always pressed.
#ifdef MATRIX_MASKED
    return matrix[row] & matrix_mask[row];
#else
    return matrix[row];
#endif
}

void matrix_print(void)
{
    print_matrix_header();

    for (uint8_t row = 0; row < PLATE_NUM; row++) {
        phex(row); print(": ");
        print_matrix_row(row);
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < PLATE_NUM; i++) {
        count += matrix_bitpop(i);
    }
    return count;
}

static bool read_plate(matrix_row_t current_matrix[], uint8_t plate) {

    // Store last value of row prior to reading
    matrix_row_t last_row_value = current_matrix[plate];
    uint8_t data;

    current_matrix[plate] = 0;
    expander_read(plate, EXPANDER_REG_GPIOA, &data);
    current_matrix[plate] |= data;
    expander_read(plate, EXPANDER_REG_GPIOB, &data);
    current_matrix[plate] |= data << 8;

    return (last_row_value != current_matrix[plate]);
}
