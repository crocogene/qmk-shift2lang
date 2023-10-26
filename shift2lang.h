#pragma once

#ifndef S2L_RANGE
  #error "You must specify S2L_RANGE for the keycodes range."
#endif

#ifndef LANG_CHANGE_DEFAULT
  #error "You must specify default language change method by defining variable LANG_CHANGE_DEFAULT."
#endif

#ifndef LAYER_BASE_EN
  #error "You must specify base EN layer number by defining variable LAYER_BASE_EN."
#endif
#ifndef LAYER_SHIFT_EN
  #error "You must specify shift EN layer number by defining variable LAYER_SHIFT_EN."
#endif
#ifndef LAYER_BASE_RU
  #error "You must specify base RU layer number by defining variable LAYER_BASE_RU."
#endif
#ifndef LAYER_SHIFT_RU
  #error "You must specify shift RU layer number by defining variable LAYER_SHIFT_RU."
#endif

#define LAYER_NO 255

#include "keycodes.h"

// Способ смены языка
typedef enum {
  LANG_CHANGE_CAPS,
  LANG_CHANGE_ALT_SHIFT,
  LANG_CHANGE_SHIFT_ALT,
  LANG_CHANGE_CTRL_SHIFT,
  LANG_CHANGE_SHIFT_CTRL,
  LANG_CHANGE_WIN_SPACE
} lang_change_t;

// Языки, фиксированный список
typedef enum {
  LANG_EN = 0,
  LANG_RU = 1,
  LANG_NO // ignore this lang
} lang_t;

// Состояния шифта
typedef enum {
  SHIFT_OFF = 0,
  SHIFT_ON = 1,
  SHIFT_NO // ignore this shift state 
} shift_state_t;

// Состояния обработки одиночного шифта
typedef enum {
    ONCE_SHIFT_OFF = 0,
    ONCE_SHIFT_LAYER_OFF = 1,
    ONCE_SHIFT_ON = 2
} once_shift_state_t;

// Таймаут шифта
#ifndef S2L_SHIFT_TERM
#    define S2L_SHIFT_TERM 100
#endif

// Таймаут одиночного шифта
#ifndef S2L_ONCE_SHIFT_TERM
#    define S2L_ONCE_SHIFT_TERM 1000
#endif

uint16_t s2l_translate_shift_keycode(uint16_t keycode);
shift_state_t s2l_get_shift_state_from_keycode(uint16_t keycode);
void s2l_activate_shift_kb(shift_state_t shift_state);
void s2l_activate_shift(shift_state_t shift_state);
void s2l_process_shift(uint16_t keycode, bool down);
// ??? убрать user из названия
void s2l_shift_user_timer(void);

void s2l_activate_once_shift(void);
void s2l_process_once_shift(uint16_t keycode, keyrecord_t* record);
void s2l_once_shift_user_timer(void);

uint16_t s2l_translate_lang_keycode(uint16_t keycode);
lang_t s2l_get_lang_from_keycode(uint16_t keycode);
uint16_t s2l_translate_agnostic_keycode(uint16_t keycode);
uint8_t s2l_get_shift_layer_by_lang(lang_t lang);
void s2l_send_change_lang_to_host(void);
void s2l_activate_lang_kb(lang_t lang);
void s2l_activate_lang(lang_t lang, bool sync);
void s2l_process_lang(uint16_t keycode, bool down);
// ??? убрать user из названия
void s2l_lang_user_timer(void);

void s2l_press_key(uint16_t keycode, bool down);
void s2l_tap_key(uint16_t keycode);
bool s2l_process_sp_keycodes(uint16_t keycode, keyrecord_t* record);
bool s2l_process_en_modifiers(uint16_t keycode, keyrecord_t* record);
bool s2l_process(uint16_t keycode, keyrecord_t* record);
// ??? убрать user из названия
void s2l_user_timer(void);

#include "shift2lang.c" 