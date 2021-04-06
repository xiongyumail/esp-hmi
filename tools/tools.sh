#!/bin/bash
WORK_PATH=$(cd $(dirname $0); pwd)
TEMP_PATH=~/workspace/.tmp/${MY_NAME}
echo "WORK_PATH: ${WORK_PATH}"
echo "TEMP_PATH: ${TEMP_PATH}"

sudo apt-get update

if [ ! -d "${TEMP_PATH}" ]; then
   mkdir ~/workspace/.tmp
   mkdir ${TEMP_PATH}
fi
cd ${TEMP_PATH}
if [ ! -d ".config" ]; then
   mkdir .config
fi
if [ ! -d ".tools" ]; then
   mkdir .tools
fi

cd ${TEMP_PATH}/.config
if [ ! -d ".config" ]; then
   mkdir .config
   sudo rm -rf ~/.config
   sudo ln -s $PWD/.config ~/.config
fi
if [ ! -d ".tmux" ]; then
   mkdir .tmux
   sudo rm -rf ~/.tmux
   sudo ln -s $PWD/.tmux ~/.tmux
fi
if [ ! -d ".espressif" ]; then
   mkdir .espressif
   sudo rm -rf ~/.espressif
   sudo ln -s $PWD/.espressif ~/.espressif
fi

# tmux
sudo apt-get install -y \
   tmux
if [ ! -f "${TEMP_PATH}/.tools/tmux" ]; then
   cd ${WORK_PATH}
   cd tmux
   sudo rm -rf ~/.tmux.conf
   sudo ln -s $PWD/.tmux.conf ~/.tmux.conf
   echo "export TMUX_PATH=${WORK_PATH}/tmux" >> ${HOME}/.bashrc
   echo "tmux install ok" >> ${TEMP_PATH}/.tools/tmux
fi

# esp-idf
sudo apt-get install -y \
   python3 \
   python3-pip \
   cmake \
   libusb-1.0
if [ ! -f "${TEMP_PATH}/.tools/esp-idf" ]; then
   cd ${WORK_PATH}
   cd esp-idf
   sudo rm -rf /usr/bin/python
   sudo ln -s /usr/bin/python3 /usr/bin/python
   ./install.sh
   echo "export IDF_PATH=${WORK_PATH}/esp-idf" >> ${HOME}/.bashrc
   echo "esp-idf install ok" >> ${TEMP_PATH}/.tools/esp-idf
fi

# lvgl
sudo apt-get install -y \
   build-essential \
   libsdl2-dev
if [ ! -f "${TEMP_PATH}/.tools/lvgl" ]; then
   cd ${WORK_PATH}
   cd lvgl
   cat Gui-Guider-Setup-1.0.0-GA.deb.aa Gui-Guider-Setup-1.0.0-GA.deb.ab > Gui-Guider-Setup-1.0.0-GA.deb
   sudo dpkg -i Gui-Guider-Setup-1.0.0-GA.deb
   sudo apt --fix-broken install -y
   sudo dpkg -i Gui-Guider-Setup-1.0.0-GA.deb
   sudo rm Gui-Guider-Setup-1.0.0-GA.deb
   echo "lvgl install ok" >> ${TEMP_PATH}/.tools/lvgl
fi


sudo apt-get clean
sudo apt-get autoclean
sudo rm -rf /tmp/*
sudo rm -rf /var/tmp/*
sudo rm -rf /var/cache/*
sudo rm -rf /var/lib/apt/lists/*
