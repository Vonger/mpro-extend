# MPRO LVGL EXTEND GUILD

### Prepare

- Linux System: for example, Ubuntu.

- Install arm toolchain(arm-none-eabi-gcc), recommand version 10.3-2021.10.

- Install make, gcc, lzma, cmake.

- Download lvgl source code, put to extend folder.
  
  - Makefile will try to execute extend/lvgl/CMakeList.txt to compile LVGL.

- Copy MPROB.xxx.NOLOGO.bin to extend folder, rename to MPRO.bin.
  
  - "xxx" in the firmware file name is the size code of the screen.

### Compile

- goto extend folder.

- call "make" to genernate x.bin, this bin file is not compressed LVGL.

- call "make bin" to genernate firmware, after this step, we will have the new firmware name is MPRO.output.bin

### Upgrade & Run

- download from https://vocore.io/misc/v2scrctl.zip

- install driver for MPRO screen by zadig(Windows, Linux do not need driver).

- run v2scrctl.exe(Windows) or v2scrctl(Linux).

- connect screen to your computer by USB cable.

- click on "Upgrade" button, and choose firmware MPRO.output.bin manually.

- wait for upgrade done, screen will reboot itself, then you will see.
