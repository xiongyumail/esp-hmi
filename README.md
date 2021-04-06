# _ESP32-HMI_

## Contents

    * projects

      Development examples

    * tools

      * esp-idf sdk
      * gdocker
      * lvgl tool

    * Data

      * Schematic diagram

      * Misc

## How to use

You can follow the steps below to set up the development environment, or directly download the release version of the full environment.

* docker.io

  ```
  sudo apt install docker.io
  ```

* clone

  ```bash
  git clone --recursive https://github.com/xiongyumail/esp32-hmi
  cd esp32-hmi
  ```

  * note

    Don't omit `--recursive`, because we use submodule.

* update

  ```bash
  git pull
  git submodule update --init --recursive
  ```

* Run

  ```bash
  ./start.sh
  ```

## Appendix

### Schematic

### Datasheet

* [CAM-OV2640](docs/OV2640_DS+(2.2).pdf)
