FROM ubuntu:22.04
RUN apt update && apt install -y git python3-pip gcc-arm-none-eabi binutils-avr avr-libc
RUN python3 -m pip install qmk

RUN git clone --recursive --depth 1 -b bmp-vial-1.0.6 https://github.com/sekigon-gonnoc/vial-qmk.git /vial-qmk

WORKDIR /vial-qmk
RUN pip3 install -r requirements.txt 
RUN qmk setup -H /vial-qmk
RUN qmk config user.overlay_dir="/qmk_userspace"

RUN cp -r /vial-qmk/keyboards/sekigon/keyboard_quantizer/mini/keymaps/vial /vial-qmk/keyboards/sekigon/keyboard_quantizer/mini/keymaps/naginata_v16
COPY ./naginata_v16/*.* /vial-qmk/keyboards/sekigon/keyboard_quantizer/mini/keymaps/naginata_v16/
COPY ./naginata_v16/keymap.h /vial-qmk/keyboards/sekigon/keyboard_quantizer/mini/keymaps/vial/
COPY c1_usbh.c /vial-qmk/keyboards/sekigon/keyboard_quantizer/mini/