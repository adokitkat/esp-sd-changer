| Supported Targets | ESP32-S3 |
| ----------------- | -------- |


## SD Changer code example

This code demonstrates a use of SD-Changer library on 8-slot ESP32S3 SD-Changer device. 
The device is expected to be connected via serial port to allow this example work.

The SD-Changer specific code looks as follows:

```c
esp_sdchngr_dev_t changer = SDCHNGR_DEFAULT();
ESP_ERROR_CHECK(esp_sdchngr_init(&changer));
ESP_ERROR_CHECK(esp_sdchngr_set_power(changer, SLOT, 1));
ESP_ERROR_CHECK(esp_sdchngr_set_selected(changer, SLOT, &slot_config));
...
// process your application
...
```

To run the example code:

1. set proper IDF environment - for instance, run the following scripts in your SD changer working directory:
```
<ESP-IDF-INSTALL-PATH>/install.sh
. <ESP-IDF-INSTALL-PATH>/export.sh>
```

2. navigate to the example directory, set ESP32S3 target and build the example code. Flash the binary into the device as the last step
```
cd example
idf.py set-target esp32s3
idf.py build
idf.py flash monitor
```

The console output should be similar to the following depending on SD card slots used:
```bash
I (285) main_task: Calling app_main()
I (285) example: Initializing SD card
I (285) example: Using SDMMC peripheral
I (285) sdchngr: Initializing SD changer

I (285) i2c_bus: I2C Bus V2 uses the externally initialized bus handle
I (295) sdchngr: I2C speed 100000
I (555) sdchngr: Initialized

I (555) example: Detected num 2 mask 41
I (555) example: [SLOT 0]
I (555) example: Mounting filesystem
I (555) SD_HOST: src_freq_hz: 160000000
W (625) SD_HOST: input line delay not supported, fallback to 0 delay
W (625) SD_HOST: input line delay not supported, fallback to 0 delay
I (625) example: Filesystem mounted
Name: SD64G
Type: SDHC
Speed: 40.00 MHz (limit: 40.00 MHz)
Size: 59640MB
CSD: ver=2, sector_size=512, capacity=122142720 read_bl_len=9
SSR: bus_width=4
I (635) example: Opening file /sdcard/hello.txt
I (655) example: File written
I (665) example: Renaming file /sdcard/hello.txt to /sdcard/foo.txt
I (675) example: Reading file /sdcard/foo.txt
I (675) example: Read from file: 'Hello SD64G!'
I (675) example: Opening file /sdcard/nihao.txt
I (695) example: File written
I (695) example: Reading file /sdcard/nihao.txt
I (695) example: Read from file: 'Nihao SD64G!'
I (695) example: Card unmounted
I (695) example: [SLOT 1]
W (705) example: [SLOT 1] Card not inserted!
I (705) example: [SLOT 2]
W (705) example: [SLOT 2] Card not inserted!
I (705) example: [SLOT 3]
W (715) example: [SLOT 3] Card not inserted!
I (715) example: [SLOT 4]
W (715) example: [SLOT 4] Card not inserted!
I (725) example: [SLOT 5]
W (725) example: [SLOT 5] Card not inserted!
I (725) example: [SLOT 6]
I (735) example: Mounting filesystem
I (735) SD_HOST: src_freq_hz: 160000000
W (775) SD_HOST: input line delay not supported, fallback to 0 delay
W (785) SD_HOST: input line delay not supported, fallback to 0 delay
I (785) example: Filesystem mounted
Name: SD
Type: SDHC
Speed: 40.00 MHz (limit: 40.00 MHz)
Size: 29818MB
CSD: ver=2, sector_size=512, capacity=61067264 read_bl_len=9
SSR: bus_width=4
I (795) example: Opening file /sdcard/hello.txt
I (815) example: File written
I (825) example: Renaming file /sdcard/hello.txt to /sdcard/foo.txt
I (835) example: Reading file /sdcard/foo.txt
I (835) example: Read from file: 'Hello SD!'
I (835) example: Opening file /sdcard/nihao.txt
I (865) example: File written
I (865) example: Reading file /sdcard/nihao.txt
I (865) example: Read from file: 'Nihao SD!'
I (865) example: Card unmounted
I (865) example: [SLOT 7]
W (865) example: [SLOT 7] Card not inserted!
I (875) example: Powered count 0 mask 00
I (875) example: Last selected slot 6
I (875) main_task: Returned from app_main()
```