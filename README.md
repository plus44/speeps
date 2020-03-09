# E-Paper Display Speed Reader

This is a project with the aim of creating a device with multiple e-paper displays (for ease of reading) that sequentially (and rapidly!) flash words to the user, in order for them to improve their reading speed, similar to [Spritz](https://www.spritz.com). Targeting a peak speed of approximately 600-800wpm.

One goal is to determine whether or not an improvement in learning to read quickly on a device will also improve the user's reading speed off the device (e.g. on a physical book).

It's proving rather difficult to design adequately quick look-up-tables (LUTs) for partial refresh, so in the short-term an iPhone attachment may be constructed, to allow the user to experiment with setting LUTs on the fly, without requiring a laptop.

The code presented is in no way complete and will continue to be a hack until this sentence gets taken down from this file.

**Goals for the e-Paper display driver:**

 - Platform independent hardware layer with compile-time selection of required hardware. Currently targeting RaspberryPi, STM32 and Linux streams (for unit testing).
 - Display independent layer with a runtime selection of displays.
 - Displays to share SPI bus, but have their own chip selects.
 - EPD LUTs to be runtime configurable (because why not?)

More info to come.