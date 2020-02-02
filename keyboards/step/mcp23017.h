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

#ifndef _MCP23017_H_
#define _MCP23017_H_


uint8_t MCP23017_writeRegister(uint8_t i2cAddr, uint8_t regAddr, uint8_t val);
uint8_t MCP23017_readRegister(uint8_t i2cAddr, uint8_t regAddr);
uint8_t MCP23017_Mode_A(uint8_t i2cAddr, uint8_t val);
uint8_t MCP23017_Mode_B(uint8_t i2cAddr, uint8_t val);
uint8_t MCP23017_Polarity_A(uint8_t i2cAddr, uint8_t val);
uint8_t MCP23017_Polarity_B(uint8_t i2cAddr, uint8_t val);
uint8_t MCP23017_Pullup_A(uint8_t i2cAddr, uint8_t val);
uint8_t MCP23017_Pullup_B(uint8_t i2cAddr, uint8_t val);
uint8_t MCP23017_Write_A(uint8_t i2cAddr, uint8_t val);
uint8_t MCP23017_Write_B(uint8_t i2cAddr, uint8_t val);
uint8_t MCP23017_Read_A(uint8_t i2cAddr);
uint8_t MCP23017_Read_B(uint8_t i2cAddr);


#define MCP23017_ADDRESS 0x20

#define MCP23017_BANK0_IODIRA 0x00
#define MCP23017_BANK0_IPOLA 0x02
#define MCP23017_BANK0_GPINTENA 0x04
#define MCP23017_BANK0_DEFVALA 0x06
#define MCP23017_BANK0_INTCONA 0x08
#define MCP23017_BANK0_IOCONA 0x0A
#define MCP23017_BANK0_GPPUA 0x0C
#define MCP23017_BANK0_INTFA 0x0E
#define MCP23017_BANK0_INTCAPA 0x10
#define MCP23017_BANK0_GPIOA 0x12
#define MCP23017_BANK0_OLATA 0x14

#define MCP23017_BANK0_IODIRB 0x01
#define MCP23017_BANK0_IPOLB 0x03
#define MCP23017_BANK0_GPINTENB 0x05
#define MCP23017_BANK0_DEFVALB 0x07
#define MCP23017_BANK0_INTCONB 0x09
#define MCP23017_BANK0_IOCONB 0x0B
#define MCP23017_BANK0_GPPUB 0x0D
#define MCP23017_BANK0_INTFB 0x0F
#define MCP23017_BANK0_INTCAPB 0x11
#define MCP23017_BANK0_GPIOB 0x13
#define MCP23017_BANK0_OLATB 0x15

#define MCP23017_BANK1_IODIRA 0x00
#define MCP23017_BANK1_IPOLA 0x01
#define MCP23017_BANK1_GPINTENA 0x02
#define MCP23017_BANK1_DEFVALA 0x03
#define MCP23017_BANK1_INTCONA 0x04
#define MCP23017_BANK1_IOCONA 0x05
#define MCP23017_BANK1_GPPUA 0x06
#define MCP23017_BANK1_INTFA 0x07
#define MCP23017_BANK1_INTCAPA 0x08
#define MCP23017_BANK1_GPIOA 0x09
#define MCP23017_BANK1_OLATA 0x0A

#define MCP23017_BANK1_IODIRB 0x10
#define MCP23017_BANK1_IPOLB 0x11
#define MCP23017_BANK1_GPINTENB 0x12
#define MCP23017_BANK1_DEFVALB 0x13
#define MCP23017_BANK1_INTCONB 0x14
#define MCP23017_BANK1_IOCONB 0x15
#define MCP23017_BANK1_GPPUB 0x16
#define MCP23017_BANK1_INTFB 0x17
#define MCP23017_BANK1_INTCAPB 0x18
#define MCP23017_BANK1_GPIOB 0x19
#define MCP23017_BANK1_OLATB 0x1A

#define MCP23017_INT_ERR 255


#endif
