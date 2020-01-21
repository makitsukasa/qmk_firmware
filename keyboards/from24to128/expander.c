#include <stdbool.h>
#include "action.h"
#include "i2cmaster.h"
#include "expander.h"
#include "debug.h"

#define TXLED0 PORTD |= (1<<5)
#define TXLED1 PORTD &= ~(1<<5)
#define RXLED0 PORTB |= (1<<0)
#define RXLED1 PORTB &= ~(1<<0)

static uint8_t expander_status[8] = {0, 0, 0, 0, 0, 0, 0, 0};
static uint8_t expander_input[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void expander_config(uint8_t addr);
uint8_t expander_write(uint8_t addr, uint8_t reg, uint8_t data);
uint8_t expander_read(uint8_t addr, uint8_t reg, uint8_t *data);

void expander_init(uint8_t addr)
{
  i2c_init();
  expander_scan(addr);
}

void expander_scan(uint8_t addr)
{
  dprintf("expander status: %d ... ", expander_status[addr]);
  uint8_t ret = i2c_start(((0x20 | addr) << 1) | I2C_WRITE);
  if (ret == 0) {
    i2c_stop();
    if (expander_status[addr] == 0) {
      dprintf("attached\n");
      expander_status[addr] = 1;
      expander_config(addr);
      clear_keyboard();
    }
  }
  else {
    TXLED1;
    if (expander_status[addr] == 1) {
      dprintf("detached\n");
      expander_status[addr] = 0;
      clear_keyboard();
    }
  }
  dprintf("%d\n", expander_status[addr]);
}

void expander_read_cols(uint8_t addr)
{
  expander_read(addr, EXPANDER_REG_GPIOA, &expander_input[addr]);
}

uint8_t expander_get_col(uint8_t addr, uint8_t col)
{
  if (col > 4) {
    col++;
  }
  return expander_input[addr] & (1<<col) ? 1 : 0;
}

matrix_row_t expander_read_row(uint8_t addr)
{
  expander_read_cols(addr);

  /* make cols */
  matrix_row_t cols = 0;
  for (uint8_t col = 0; col < MATRIX_COLS; col++) {
    if (expander_get_col(addr, col)) {
      cols |= (1UL << (MATRIX_COLS - 1 - col));
    }
  }

  return cols;
}

void expander_unselect_rows(uint8_t addr)
{
  expander_write(addr, EXPANDER_REG_IODIRB, 0xFF);
}

void expander_select_row(uint8_t addr, uint8_t row)
{
  expander_write(addr, EXPANDER_REG_IODIRB, ~(1<<(row+1)));
}

void expander_config(uint8_t addr)
{
  expander_write(addr, EXPANDER_REG_IPOLA, 0xFF);
  expander_write(addr, EXPANDER_REG_GPPUA, 0xFF);
  expander_write(addr, EXPANDER_REG_IODIRB, 0xFF);
}

uint8_t expander_write(uint8_t addr, uint8_t reg, uint8_t data)
{
  if (expander_status[addr] == 0) {
    return 0;
  }
  uint8_t ret;
  ret = i2c_start(((0x20 | addr) << 1) | I2C_WRITE);
  if (ret) goto stop;
  ret = i2c_write(reg);
  if (ret) goto stop;
  ret = i2c_write(data);
 stop:
  i2c_stop();
  return ret;
}

uint8_t expander_read(uint8_t addr, uint8_t reg, uint8_t *data)
{
  if (expander_status[addr] == 0) {
    return 0;
  }
  uint8_t ret;
  ret = i2c_start(((0x20 | addr) << 1) | I2C_WRITE);
  if (ret) goto stop;
  ret = i2c_write(reg);
  if (ret) goto stop;
  ret = i2c_rep_start(((0x20 | addr) << 1) | I2C_READ);
  if (ret) goto stop;
  *data = i2c_readNak();
 stop:
  i2c_stop();
  return ret;
}
