# MPRO LVGL EXTEND GUILD

### Prepare

- Linux System: for example, Ubuntu.

- Install arm toolchain(arm-none-eabi-gcc), recommand version [10.3-2021.10](https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2?rev=78196d3461ba4c9089a67b5f33edf82a&hash=5631ACEF1F8F237389F14B41566964EC). Compile require autoconf, autopoint.

- Install make, gcc, lzma(5.8.1), cmake.
  - make sure your lzma version is 5.8.1, download https://github.com/tukaani-project/xz/archive/refs/tags/v5.8.1.tar.gz to compile latest version, replace /usr/bin/lzma and /usr/bin/xz. Ubuntu default version is out of date, normally it is 5.2.5, that liblzma version won't work.

- Copy MPRO.xxx.NOLOGO.bin or MPRO.xxx.VOCORE.bin to extend folder, rename to MPRO.bin.
  - firmware download at https://vocore.io/misc/v2scrctl.zip
  - "xxx" in the firmware file name is the size code of the screen, it must match the screen type you plan to use.

### Compile

- goto extend folder.

- clone lvgl to submodule
  - option 1: call `git submodule update --init --recursive`
  - option 2: directly clone lvgl by `git clone https://github.com/lvgl/lvgl.git -b release/v9.3 --depth=1`, then rename the folder to lvgl and replace the exists one.

- call "make" to genernate x.bin, this bin file is not compressed LVGL.

- call "make bin" to genernate firmware, after this step, we will have the new firmware name is MPRO.output.bin

### Upgrade & Run

- download from https://vocore.io/misc/v2scrctl.zip

- install driver for MPRO screen by zadig(Windows only, Linux do not need driver).

- run v2scrctl.exe(Windows) or v2scrctl(Linux).

- connect screen to your computer by USB cable.

- click on "Upgrade" button, and choose firmware MPRO.output.bin manually.

- wait for upgrade done, screen will reboot itself, then you will see.
