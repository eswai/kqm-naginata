
VIA_ENABLE = yes
VIAL_ENABLE = yes
VIAL_INSECURE = yes

SRC += quantizer_mouse.c raw_hid.c

include keyboards/sekigon/keyboard_quantizer/mini/keymaps/naginata_v16/cli/rules.mk
include keyboards/sekigon/keyboard_quantizer/mini/keymaps/naginata_v16/key_override/rules.mk
VPATH += keyboards/sekigon/keyboard_quantizer/mini/keymaps/naginata_v16/cli
VPATH += keyboards/sekigon/keyboard_quantizer/mini/keymaps/naginata_v16/key_override

GIT_DESCRIBE := $(shell git describe --tags --long --dirty="\\*" 2>/dev/null)
CFLAGS += -DGIT_DESCRIBE=$(GIT_DESCRIBE)

# Override raw_hid_receive to support both of VIA and VIAL
$(BUILD_DIR)/obj_sekigon_keyboard_quantizer_mini_naginata_v16/quantum/via.o:: CFLAGS += -Draw_hid_receive=raw_hid_receive_vial
SRC += tmk_core/protocol/bmp/via_qmk.c

UNICODE_ENABLE = yes
# CONSOLE_ENABLE = yes
# COMMAND_ENABLE = yes

# If you want to change the display of OLED, you need to change here
SRC +=  naginata_v16.c
SRC +=  nglist.c
SRC +=  nglistarray.c

