#!/bin/bash
WORK_PATH=$(cd $(dirname $0); pwd)
echo "WORK_PATH: ${WORK_PATH}"

cd ${WORK_PATH}/lcd_cam_loopback
idf.py --preview set-target esp32s3
idf.py -p /dev/ttyUSB0 build flash monitor



