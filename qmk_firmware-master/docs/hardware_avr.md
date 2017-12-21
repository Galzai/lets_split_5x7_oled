# Keyboards With AVR Processors

This page describes the support for for AVR processors in QMK. AVR processors include the atmega32u4, atmega32u2, at90usb1286, and other processors from Atmel Corporation. AVR processors are 8-bit MCU's that are designed to be easy to work with. The most common AVR processors in keyboards have on-board USB and plenty of GPIO for supporting large keyboard matrices. They are the most popular MCU for use in keyboards today.

If you have not yet you should read the [Keyboard Guidelines](hardware_keyboard_guidelines.md) to get a sense of how keyboards fit into QMK.

## Adding Your AVR Keyboard to QMK

QMK has a number of features to simplify working with AVR keyboards. For most keyboards you don't have to write a single line of code. To get started run the `util/new_project.sh` script:

```
$ util/new_project.sh my_awesome_keyboard
######################################################
# /keyboards/my_awesome_keyboard project created. To start
# working on things, cd into keyboards/my_awesome_keyboard
######################################################
```

This will create all the files needed to support your new keyboard, and populate the settings with default values. Now you just need to customize it for your keyboard.

## `readme.md`

This is where you'll describe your keyboard. Please follow the [Keyboard Readme Template](documentation_templates.md#keyboard-readmemd-template) when writing your `readme.md`. You're encouraged to place an image at the top of your `readme.md`, please use an external service such as [Imgur](http://imgur.com) to host the images.

## `<keyboard>.c`

This is where all the custom logic for your keyboard goes. Many keyboards do not need to put anything at all in here. You can learn more about writing custom logic in [Custom Quantum Functions](custom_quantum_functions.md).

## `<keyboard>.h`

This is the file you define your [Layout Macro(s)](feature_layouts.md) in. At minumum you should have a `#define LAYOUT` for your keyboard that looks something like this:

```
#define LAYOUT(          \
      k00, k01, k02,     \
      k10,   k11         \
) {                      \
    { k00, k01,   k02 }, \
    { k10, KC_NO, k11 }, \
}
```

The first half of the `LAYOUT` pre-processor macro defines the physical arrangement of keys. The second half of the macro defines the matrix the switches are connected to. This allows you to have a physical arrangement of keys that differs from the wiring matrix.

Each of the `k__` variables needs to be unique, and typically they follow the format `k<row><col>`.

The physical matrix (the second half) must have a number of rows equalling `MATRIX_ROWS`, and each row must have exactly `MATRIX_COLS` elements in it. If you do not have this many physical keys you can use `KC_NO` to fill in the blank spots.

## `config.h`

The `config.h` file is where you configure the hardware and feature set for your keyboard. There are a lot of options that can be placed in that file, too many to list there. For a complete overview of available options see the [Config Options](config_options.md) page.

### Hardware Configuration


At the top of the `config.h` you'll find USB related settings. These control how your keyboard appears to the Operating System. If you don't have a good reason to change you should leave the `VENDOR_ID` as `0xFEED`. For the `PRODUCT_ID` you should pick a number that is not yet in use.

Do change the `MANUFACTURER`, `PRODUCT`, and `DESCRIPTION` lines to accurately reflect your keyboard.

```
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    You
#define PRODUCT         my_awesome_keyboard
#define DESCRIPTION     A custom keyboard
```

{% hint style='info' %}
Note: On Windows and macOS the `MANUFACTURER`, `PRODUCT`, and `DESCRIPTION` fields will be displayed in the list of USB devices. On Linux these values will not be visible in `lsusb`, since Linux takes that information from the list published by the USB-IF.
{% endhint %}

### Keyboard Matrix Configuration

The next section of the `config.h` file deals with your keyboard's matrix. The first thing you should set is the matrix's size. This is usually, but not always, the same number of rows and columns as the physical key arrangement.

```
#define MATRIX_ROWS 2
#define MATRIX_COLS 3
```

Once you've defined the size of your matrix you need to define which pins on your MCU are connected to rows and columns. To do so simply specify the names of those pins:

```
#define MATRIX_ROW_PINS { D0, D5 }
#define MATRIX_COL_PINS { F1, F0, B0 }
#define UNUSED_PINS
```

The number of `MATRIX_ROW_PINS` entries must be the same as the number you assigned to `MATRIX_ROWS`, and likewise for `MATRIX_COL_PINS` and `MATRIX_COLS`. You do not have to specify `UNUSED_PINS`, but you can if you want to document what pins are open.

Finally, you can specify the direction your diodes point. This can be `COL2ROW`, `ROW2COL`, or `CUSTOM_MATRIX`.

```
#define DIODE_DIRECTION COL2ROW
```

### Backlight Configuration

By default QMK supports backlighting on pins `B5`, `B6`, and `B7`. If you are using one of those you can simply enable it here. For more details see the [Backlight Documentation](feature_backlight.md).

```
#define BACKLIGHT_PIN B7
#define BACKLIGHT_BREATHING
#define BACKLIGHT_LEVELS 3
```

{% hint style='info' %}
You can use backlighting on any pin you like, but you will have to do more work to support that. See the [Backlight Documentation](feature_backlight.md) for more details.
{% endhint %}

### Other Configuration Options

There are a lot of features that can be configured or tuned in `config.h`. You should see the [Config Options](config_options.md) page for more details.

## `rules.mk`

You use the `rules.mk` file to tell QMK what files to build and what features to enable. If you are building around an atmega32u4 you can largely leave these defaults alone. If you are using another MCU you may have to tweak some parameters.

### MCU Options

These options tell the build system what CPU to build for. Be very careful if you change any of these settings, you can render your keyboard inoperable.

```
MCU = atmega32u4
F_CPU = 16000000
ARCH = AVR8
F_USB = $(F_CPU)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT
```

### Bootloader Size

The bootloader is a special section of your MCU that allows you to upgrade the code stored on the MCU. Think of it like a Rescue Partition for your keyboard. If you are using a teensy 2.0, or a device like the Ergodox EZ that uses the teensy bootloader you should set this to `512`. Most other bootloaders should be set to `4096`, but `1024` and `2048` are other possible values you may encounter.

#### Teensy 2.0 Bootloader Example

```
OPT_DEFS += -DBOOTLOADER_SIZE=512
```

#### Teensy 2.0++ Bootloader Example

```
OPT_DEFS += -DBOOTLOADER_SIZE=1024
```

#### Atmel DFU Loader Example

```
OPT_DEFS += -DBOOTLOADER_SIZE=4096
```

### Build Options

There are a number of features that can be turned on or off in `rules.mk`. See the [Config Options](config_options.md#feature-options) page for a detailed list and description.

