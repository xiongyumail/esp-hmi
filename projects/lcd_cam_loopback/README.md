# _LCD_CAM_LOOPBACK_

FPS: 38 Hz

![fps.png](fps.png)

## How to use

* Compile and download

Please unplug the camera module before downloading the code!!!

* esp32
```bash
idf.py set-target esp32
cp sdkconfig.defaults.esp32 sdkconfig
idf.py build flash monitor
```
* esp32s2
```bash
idf.py set-target esp32s2
cp sdkconfig.defaults.esp32s2 sdkconfig
idf.py build flash monitor
```
* esp32
```bash
idf.py set-target esp32s3
cp sdkconfig.defaults.esp32s3 sdkconfig
idf.py build flash monitor
```