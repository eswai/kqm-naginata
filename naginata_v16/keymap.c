/* Copyright 2020 sekigon-gonnoc
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 #include QMK_KEYBOARD_H

 #include "pointing_device.h"
 #include "virtser.h"
 #include "eeconfig.h"
 #include "vial.h"
 
 #include "keymap.h"
 #include "quantizer_mouse.h"
 #include "report_parser.h"
 #include "cli.h"
 #include "os_key_override.h"
 
 // 薙刀式
 #include "naginata.h"
 NGKEYS naginata_keys;

 const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {{
     {0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7},
     {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07},
     {0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f},
     {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17},
     {0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f},
     {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27},
     {0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f},
     {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37},
     {0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f},
     {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47},
     {0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f},
     {0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57},
     {0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f},
     {0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67},
     {0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f},
     {0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77},
     {0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f},
     {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87},
     {0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f},
     {0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97},
     {0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f},
     {0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7},
     {0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf},
     {0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7},
     {0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf},
     {0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7},
     {0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf},
     {0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7},
     {0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf},
     {0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7},
     {0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef},
 }};
 user_config_t user_config;
 
 int8_t virtser_send_wrap(uint8_t c) {
     virtser_send(c);
     return 0;
 }
 
 void keyboard_pre_init_user(void) {
     cli_init();
     print_set_sendchar(virtser_send_wrap);
 }
 
 static uint8_t get_gesture_threshold(void) {
     return 50;
 }
 
 void keyboard_post_init_user(void) {
     set_mouse_gesture_threshold(get_gesture_threshold());
     os_key_override_init();
 
     user_config.raw = eeconfig_read_user();
     switch (user_config.key_os_override) {
         case KEY_OS_OVERRIDE_DISABLE:
             remove_all_os_key_overrides();
             break;
         case US_KEY_JP_OS_OVERRIDE_DISABLE:
             register_us_key_on_jp_os_overrides();
             break;
         case JP_KEY_US_OS_OVERRIDE_DISABLE:
             register_jp_key_on_us_os_overrides();
             break;
     }

    // 薙刀式
    uint16_t ngonkeys[] = {KC_H, KC_J};
    uint16_t ngoffkeys[] = {KC_F, KC_G};
    set_naginata(1, ngonkeys, ngoffkeys);
    // 薙刀式
 }
 
 bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
     return pre_process_record_mouse(keycode, record);
 }
 
 #define DEFFERED_KEY_RECORD_LEN 6
 static keyrecord_t deferred_key_record[DEFFERED_KEY_RECORD_LEN];
 
 static void push_deferred_key_record(uint16_t keycode, keyevent_t *event) {
     for (int i = 0; i < DEFFERED_KEY_RECORD_LEN; i++) {
         if (deferred_key_record[i].keycode == KC_NO) {
             keyrecord_t record     = {.event = *event, .keycode = keycode};
             deferred_key_record[i] = record;
             return;
         }
     }
 }
 
 bool process_record_user(uint16_t keycode, keyrecord_t *record) {
     bool cont = process_record_mouse(keycode, record);
 
     // To apply key overrides to keycodes combined shift modifier, separate to two actions
     if (keycode >= QK_MODS && keycode <= QK_MODS_MAX) {
         if (record->event.pressed) {
             register_mods(QK_MODS_GET_MODS(keycode));
             uint16_t   deferred_keycode   = QK_MODS_GET_BASIC_KEYCODE(keycode);
             keyevent_t deferred_key_event = (keyevent_t){.type = KEY_EVENT, .key = (keypos_t){.row = VIAL_MATRIX_MAGIC, .col = VIAL_MATRIX_MAGIC}, .pressed = 1, .time = (timer_read() | 1)};
             push_deferred_key_record(deferred_keycode, &deferred_key_event);
         } else {
             uint16_t   deferred_keycode   = QK_MODS_GET_BASIC_KEYCODE(keycode);
             keyevent_t deferred_key_event = ((keyevent_t){.type = KEY_EVENT, .key = (keypos_t){.row = VIAL_MATRIX_MAGIC, .col = VIAL_MATRIX_MAGIC}, .pressed = 0, .time = (timer_read() | 1)});
             unregister_mods(QK_MODS_GET_MODS(keycode));
             push_deferred_key_record(deferred_keycode, &deferred_key_event);
         }
         return false;
     }
 
     if (record->event.pressed) {
         switch (keycode) {
             case QK_KB_0:
             remove_all_os_key_overrides();
             user_config.key_os_override = KEY_OS_OVERRIDE_DISABLE;
             eeconfig_update_user(user_config.raw);
             return false;
 
             case QK_KB_1:
             register_us_key_on_jp_os_overrides();
             user_config.key_os_override = US_KEY_JP_OS_OVERRIDE_DISABLE;
             eeconfig_update_user(user_config.raw);
             return false;
 
             case QK_KB_2:
             register_jp_key_on_us_os_overrides();
             user_config.key_os_override = JP_KEY_US_OS_OVERRIDE_DISABLE;
             eeconfig_update_user(user_config.raw);
             return false;
         }
     }
    
     // 薙刀式
    if (!process_naginata(keycode, record))
        return false;
    // 薙刀式

     return cont;
 }
 
 void post_process_record_user(uint16_t keycode, keyrecord_t* record) {
     post_process_record_mouse(keycode, record);
 }
 
 void housekeeping_task_user(void) {
     for (int i = 0; i < DEFFERED_KEY_RECORD_LEN; i++) {
         if (deferred_key_record[i].keycode != KC_NO) {
             g_vial_magic_keycode_override = deferred_key_record[i].keycode;
             action_exec(deferred_key_record[i].event);
             deferred_key_record[i].keycode = KC_NO;
         } else {
             break;
         }
     }
     cli_exec();
 }
 