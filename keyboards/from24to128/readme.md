from24to128 keyboard firmware
======================

## Quantum MK Firmware

For the full Quantum feature list, see [the parent readme](/).

## Building

Download or clone the whole firmware and navigate to the keyboards/alter folder. Once your dev env is setup, you'll be able to type `make` to generate your .hex - you can then use the Teensy Loader to program your .hex file.

Depending on which keymap you would like to use, you will have to compile slightly differently.

### Default

To build with the default keymap, simply run `make default`.

### Other Keymaps

Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create a folder with the name of your keymap in the keymaps folder, and see keymap documentation (you can find in top readme.md) and existant keymap files.

To build the firmware binary hex file with a keymap just do `make` with a keymap like this:

```
$ make [default|jack|<name>]
```

Keymaps follow the format **__\<name\>.c__** and are stored in the `keymaps` folder.


## メモ I CAN NOT WRITE ENGLISH
### 書き込んだ方法
コマンドプロンプトでmakeが動かなかったので，wslで
```
$ make from24to128:default
```
ってやって，コマンドプロンプトに切り替えるのが面倒だからwslから
```
$ ./upload.sh
```
ってやった．

準備で
```
$ sudo apt install avr-gcc
$ sudo apt install avr-libc
```
とかやった．
windowsにarduinoを入れてたので，それのavrdude.exeを使った．

### 物理レイアウトを変えるときに弄るとこ
- config.h
  - \#define MATRIX_ROWS 4
  - \#define MATRIX_COLS 14

- from24to128.h
  - \#define KEYMAP

- keymap.c
  - const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS]
