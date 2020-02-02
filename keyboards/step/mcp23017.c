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

/* 2019 MakiTsukasa
 * cloned from https://github.com/MakotoKurauchi/qmk_firmware/tree/feature/alter
 *
 * http://zattouka.net/GarageHouse/micon/circuit/MCP23017.htm
 */

#include "i2cmaster.h"
#include "mcp23017.h"

#define TXLED0 PORTD |= (1<<5)
#define TXLED1 PORTD &= ~(1<<5)
#define RXLED0 PORTB |= (1<<0)
#define RXLED1 PORTB &= ~(1<<0)

uint8_t MCP23017_writeRegister(uint8_t i2cAddr, uint8_t regAddr, uint8_t val){

    uint8_t err = i2c_start(((MCP23017_ADDRESS | i2cAddr)<<1) | I2C_WRITE);
    if (err) goto i2c_error;

    err = i2c_write(regAddr);
    if (err) goto i2c_error;

    err = i2c_write(val);
    if (err) goto i2c_error;

    i2c_stop();
    return 0;

i2c_error:
    i2c_stop();
    return err;
}

uint8_t MCP23017_readRegister(uint8_t i2cAddr, uint8_t regAddr){

    uint8_t data = 0;
    uint8_t err = i2c_start(((MCP23017_ADDRESS | i2cAddr)<<1) | I2C_WRITE);
    if (err) goto i2c_error;

    err = i2c_write(regAddr);
    if (err) goto i2c_error;

    err = i2c_rep_start(((MCP23017_ADDRESS | i2cAddr)<<1) | I2C_READ);
    if (err) goto i2c_error;

    data = i2c_readNak();
    i2c_stop();
    return data;


i2c_error:
    i2c_stop();
    TXLED1;
    return data;
}

uint8_t MCP23017_Mode_A(uint8_t i2cAddr, uint8_t val){
    return MCP23017_writeRegister(i2cAddr, MCP23017_BANK0_IODIRA, val);
}

uint8_t MCP23017_Mode_B(uint8_t i2cAddr, uint8_t val){
    return MCP23017_writeRegister(i2cAddr, MCP23017_BANK0_IODIRB, val);
}

uint8_t MCP23017_Polarity_A(uint8_t i2cAddr, uint8_t val){
    return MCP23017_writeRegister(i2cAddr, MCP23017_BANK0_IPOLA, val);
}

uint8_t MCP23017_Polarity_B(uint8_t i2cAddr, uint8_t val){
    return MCP23017_writeRegister(i2cAddr, MCP23017_BANK0_IPOLB, val);
}

uint8_t MCP23017_Pullup_A(uint8_t i2cAddr, uint8_t val){
    return MCP23017_writeRegister(i2cAddr, MCP23017_BANK0_GPPUA, val);
}

uint8_t MCP23017_Pullup_B(uint8_t i2cAddr, uint8_t val){
    return MCP23017_writeRegister(i2cAddr, MCP23017_BANK0_GPPUB, val);
}

uint8_t MCP23017_Write_A(uint8_t i2cAddr, uint8_t val){
    return MCP23017_writeRegister(i2cAddr, MCP23017_BANK0_GPIOA, val);
}

uint8_t MCP23017_Write_B(uint8_t i2cAddr, uint8_t val){
    return MCP23017_writeRegister(i2cAddr, MCP23017_BANK0_GPIOB, val);
}

uint8_t MCP23017_Read_A(uint8_t i2cAddr){
    return MCP23017_readRegister(i2cAddr, MCP23017_BANK0_GPIOA);
}

uint8_t MCP23017_Read_B(uint8_t i2cAddr){
    return MCP23017_readRegister(i2cAddr, MCP23017_BANK0_GPIOB);
}
