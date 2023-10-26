#include <stdint.h>
#include "keycodes.h"
#include "s2l_keycodes.h"
#include "s2l.h"
#include "keyboard.h"
#include "action_tapping.h"
#include "quantum.h"

lang_change_t lang_change_current = LANG_CHANGE_DEFAULT;

shift_state_t shift_should_be = SHIFT_OFF;
shift_state_t shift_current = SHIFT_OFF;
uint32_t shift_timer = 0;
uint8_t shift_press_count = 0;

once_shift_state_t once_shift_state = ONCE_SHIFT_OFF; 
uint8_t once_shift_layer_save = S2L_LAYER_NO;
uint32_t once_shift_timer = 0; 
bool once_shift_timer_enabled = true;

lang_t lang_should_be = LANG_EN;
lang_t lang_current = LANG_EN;
uint32_t lang_timer = 0;
uint8_t lang_press_count = 0;

// ---------------------------------------------------------------------------
//                               Работа с шифтом
// ---------------------------------------------------------------------------

uint16_t s2l_translate_shift_keycode(uint16_t keycode) {
  switch (keycode) {
    case KS_GRV:  return KC_GRV;
    case KS_TILD: return KC_GRV;
    case KS_1:    return KC_1;
    case KS_EXCL: return KC_1;
    case KS_2:    return KC_2;
    case KS_AT:   return KC_2;
    case KS_3:    return KC_3;
    case KS_HASH: return KC_3;
    case KS_4:    return KC_4;
    case KS_DLR:  return KC_4;
    case KS_5:    return KC_5;
    case KS_PERC: return KC_5;
    case KS_6:    return KC_6;
    case KS_CIRC: return KC_6;
    case KS_7:    return KC_7;
    case KS_AMPR: return KC_7;
    case KS_8:    return KC_8;
    case KS_ASTR: return KC_8;
    case KS_9:    return KC_9;
    case KS_LPRN: return KC_9;
    case KS_0:    return KC_0;
    case KS_RPRN: return KC_0;
    case KS_MINS: return KC_MINS;
    case KS_UNDS: return KC_MINS;
    case KS_EQL:  return KC_EQL;
    case KS_PLUS: return KC_EQL;
    case KS_Q:    return KC_Q;
    case KS_S_Q:  return KC_Q;
    case KS_W:    return KC_W;
    case KS_S_W:  return KC_W;
    case KS_E:    return KC_E;
    case KS_S_E:  return KC_E;
    case KS_R:    return KC_R;
    case KS_S_R:  return KC_R;
    case KS_T:    return KC_T;
    case KS_S_T:  return KC_T;
    case KS_Y:    return KC_Y;
    case KS_S_Y:  return KC_Y;
    case KS_U:    return KC_U;
    case KS_S_U:  return KC_U;
    case KS_I:    return KC_I;
    case KS_S_I:  return KC_I;
    case KS_O:    return KC_O;
    case KS_S_O:  return KC_O;
    case KS_P:    return KC_P;
    case KS_S_P:  return KC_P;
    case KS_LBRC: return KC_LBRC;
    case KS_LCBR: return KC_LBRC;
    case KS_RBRC: return KC_RBRC;
    case KS_RCBR: return KC_RBRC;
    case KS_A:    return KC_A;
    case KS_S_A:  return KC_A;
    case KS_S:    return KC_S;
    case KS_S_S:  return KC_S;
    case KS_D:    return KC_D;
    case KS_S_D:  return KC_D;
    case KS_F:    return KC_F;
    case KS_S_F:  return KC_F;
    case KS_G:    return KC_G;
    case KS_S_G:  return KC_G;
    case KS_H:    return KC_H;
    case KS_S_H:  return KC_H;
    case KS_J:    return KC_J;
    case KS_S_J:  return KC_J;
    case KS_K:    return KC_K;
    case KS_S_K:  return KC_K;
    case KS_L:    return KC_L;
    case KS_S_L:  return KC_L;
    case KS_SCLN: return KC_SCLN;
    case KS_COLN: return KC_SCLN;
    case KS_QUOT: return KC_QUOT;
    case KS_DQUO: return KC_QUOT;
#ifdef LANG_USE_ANSI
    case KS_BSLS: return KC_BSLS;
    case KS_PIPE: return KC_BSLS;
#else
    case KS_BSLS: return KC_NUHS; // ISO keyboards use another backslash code
    case KS_PIPE: return KC_NUHS; // but there is no difference for OS
    case KS_LT2:  return KC_NUBS;
    case KS_GT2:  return KC_NUBS;
#endif
    case KS_Z:    return KC_Z;
    case KS_S_Z:  return KC_Z;
    case KS_X:    return KC_X;
    case KS_S_X:  return KC_X;
    case KS_C:    return KC_C;
    case KS_S_C:  return KC_C;
    case KS_V:    return KC_V;
    case KS_S_V:  return KC_V;
    case KS_B:    return KC_B;
    case KS_S_B:  return KC_B;
    case KS_N:    return KC_N;
    case KS_S_N:  return KC_N;
    case KS_M:    return KC_M;
    case KS_S_M:  return KC_M;
    case KS_COMM: return KC_COMM;
    case KS_LT:   return KC_COMM;
    case KS_DOT:  return KC_DOT;
    case KS_GT:   return KC_DOT;
    case KS_SLSH: return KC_SLSH;
    case KS_QUES: return KC_SLSH;
    default: return KC_NO; 
  }
}

shift_state_t s2l_get_shift_state_from_keycode(uint16_t keycode) {
  if (KS_GRV <= keycode && keycode <= KS_QUES) {
    if ((keycode - KS_GRV) % 2 == 0) {
        return SHIFT_OFF;
    } else {
        return SHIFT_ON;
    }
  } else {
    return SHIFT_NO;
  }
}

void s2l_activate_shift_kb(shift_state_t shift_state) {
	if (shift_current == shift_state) { return; }
	shift_timer = timer_read();
  switch (shift_state) {
    case SHIFT_ON:     
      register_code16(KC_LSFT);
      break;
    case SHIFT_OFF:
      unregister_code16(KC_LSFT);
      break;
    default: 
      return;       
  }
	shift_current = shift_state;
}

void s2l_activate_shift(shift_state_t shift_state) {
  shift_should_be = shift_state;
  s2l_activate_shift_kb(shift_state);
}

void s2l_process_shift(uint16_t keycode, bool down) {
	shift_state_t new_shift_state = s2l_get_shift_state_from_keycode(keycode);
	if (down) {
		if (new_shift_state != SHIFT_NO) {
			s2l_activate_shift_kb(new_shift_state);
		} else {
			s2l_activate_shift_kb(shift_should_be); 
		}
	}

	if (new_shift_state != SHIFT_NO) {
		if (down) {
			shift_press_count++;
		} else {
			shift_press_count--;
		}
	}
}

void s2l_shift_user_timer(void) {
	// Нужно выключать шифт после прохождения определённого времени, потому что пользователь ожидает как будто шифт на самом деле включён
	if (shift_press_count == 0 && shift_current != shift_should_be && timer_elapsed(shift_timer) >= S2L_SHIFT_TERM) {
		s2l_activate_shift_kb(shift_should_be);
		//shift_timer = timer_read(); //в выстоящей функции уже есть
	}
}

// ---------------------------------------------------------------------------
//                          Работа с одиночным шифтом
// ---------------------------------------------------------------------------

void s2l_activate_once_shift(void) {
  if (shift_current == SHIFT_OFF) {
    s2l_activate_shift(SHIFT_ON); 
    uint8_t layer = s2l_get_shift_layer_by_lang(lang_should_be);
    layer_on(layer); 
    once_shift_state = ONCE_SHIFT_ON;
    once_shift_layer_save = layer;
    once_shift_timer = timer_read();
  }
}

void s2l_process_once_shift(uint16_t keycode, keyrecord_t* record) {
  if (once_shift_state == ONCE_SHIFT_LAYER_OFF) {
    once_shift_state = ONCE_SHIFT_OFF;
    s2l_activate_shift(SHIFT_OFF); 
  }
  if (record->event.pressed && keycode != SFT_N_O && once_shift_state == ONCE_SHIFT_ON) {
    once_shift_state = ONCE_SHIFT_LAYER_OFF;
    layer_off(once_shift_layer_save);
  }
}

void s2l_once_shift_user_timer(void) {
  if (once_shift_timer_enabled && once_shift_state == ONCE_SHIFT_ON && timer_elapsed(once_shift_timer) >= S2L_ONCE_SHIFT_TERM) {
    layer_off(once_shift_layer_save);
    s2l_activate_shift(SHIFT_OFF); 
    once_shift_state = ONCE_SHIFT_OFF;
  }
}

// ---------------------------------------------------------------------------
//                               Работа с языком
// ---------------------------------------------------------------------------

uint16_t s2l_translate_lang_keycode(uint16_t keycode) {
  if (EN_GRV <= keycode && keycode <= EN_QUES) {
    return (keycode - EN_GRV) + KS_GRV;
  } else if (RU_JO <= keycode && keycode <= RU_COMM) {
    return (keycode - RU_JO) + KS_GRV;
  } else {
    return keycode; //во всех прочих случаях транслируем без изменений
  }
}

lang_t s2l_get_lang_from_keycode(uint16_t keycode) {
  if (EN_GRV <= keycode && keycode <= EN_QUES) {
    return LANG_EN;
  } else if (RU_JO <= keycode && keycode <= RU_COMM) {
    return LANG_RU;
  } else {
    return LANG_NO;
  }
}

uint16_t s2l_translate_agnostic_keycode(uint16_t keycode) {
  if (lang_current == LANG_EN) {
    switch (keycode) {
      case AG_1:    return EN_1;
      case AG_2:    return EN_2;
      case AG_3:    return EN_3;
      case AG_4:    return EN_4;
      case AG_5:    return EN_5;
      case AG_6:    return EN_6;
      case AG_7:    return EN_7;
      case AG_8:    return EN_8;
      case AG_9:    return EN_9;
      case AG_0:    return EN_0;
      case AG_EXCL: return EN_EXCL;
      case AG_PERC: return EN_PERC;
      case AG_ASTR: return EN_ASTR;
      case AG_LPRN: return EN_LPRN;
      case AG_RPRN: return EN_RPRN;
      case AG_MINS: return EN_MINS;
      case AG_UNDS: return EN_UNDS;
      case AG_EQL:  return EN_EQL;
      case AG_PLUS: return EN_PLUS;
      case AG_SCLN: return EN_SCLN;
      case AG_COLN: return EN_COLN;
      case AG_DQUO: return EN_DQUO;
      case AG_BSLS: return EN_BSLS;
#ifndef LANG_USE_ANSI
      case AG_PIPE: return EN_PIPE;
#endif
      case AG_COMM: return EN_COMM;
      case AG_DOT:  return EN_DOT;
      case AG_SLSH: return EN_SLSH;
#ifndef LANG_USE_ANSI
      case AG_S_SL: return EN_SLSH;
#endif
      case AG_QUES: return EN_QUES;
      default:      return keycode; //если не agnostic -> транслируем без изменений
    }
  } else if (lang_current == LANG_RU) {
    switch (keycode) {
      case AG_1:    return RU_1;
      case AG_2:    return RU_2;
      case AG_3:    return RU_3;
      case AG_4:    return RU_4;
      case AG_5:    return RU_5;
      case AG_6:    return RU_6;
      case AG_7:    return RU_7;
      case AG_8:    return RU_8;
      case AG_9:    return RU_9;
      case AG_0:    return RU_0;
      case AG_EXCL: return RU_EXCL;
      case AG_PERC: return RU_PERC;
      case AG_ASTR: return RU_ASTR;
      case AG_LPRN: return RU_LPRN;
      case AG_RPRN: return RU_RPRN;
      case AG_MINS: return RU_MINS;
      case AG_UNDS: return RU_UNDS;
      case AG_EQL:  return RU_EQL;
      case AG_PLUS: return RU_PLUS;
      case AG_SCLN: return RU_SCLN;
      case AG_COLN: return RU_COLN;
      case AG_DQUO: return RU_DQUO;
      case AG_BSLS: return RU_BSLS;
#ifndef LANG_USE_ANSI
      case AG_PIPE: return RU_PIPE;
#endif
      case AG_COMM: return RU_COMM;
      case AG_DOT:  return RU_DOT;
#ifdef LANG_USE_ANSI
      case AG_SLSH: return RU_SLSH;
#else
      case AG_SLSH: return RU_SLS2;
      case AG_S_SL: return RU_SLSH;
#endif
      case AG_QUES: return RU_QUES;
      default:      return keycode; //если не agnostic -> транслируем без изменений
    }
  }
  return keycode; //если не задан язык -> транслируем без изменений
}

uint8_t s2l_get_shift_layer_by_lang(lang_t lang) {
  switch (lang) {
    case LANG_EN: return S2L_LAYER_SHIFT_EN;
    case LANG_RU: return S2L_LAYER_SHIFT_RU;
    default: return S2L_LAYER_NO;
  }
}

void s2l_send_lang_change_to_host(void) {
  lang_timer = timer_read();
  switch (lang_change_current) {
    case LANG_CHANGE_CAPS: {
      // Костыль, потому что при нажатии Shift+Caps включается режим Caps, а не переключение языка :facepalm:
      if (shift_current == SHIFT_ON) {
      	unregister_code16(KC_LSFT);
      	tap_code16(KC_CAPS);
      	register_code16(KC_LSFT);
      } else {
      	tap_code16(KC_CAPS);
      }
    } break;
    case LANG_CHANGE_ALT_SHIFT: {
      register_code16(KC_LALT);
      tap_code16(KC_LSFT);
      unregister_code16(KC_LALT);
      // Костыль, потому что при зажатом шифте если хочется нажать клавишу, которая переключает язык, то шифт слетает... 
      if (shift_current == SHIFT_ON) {
        register_code16(KC_LSFT);
      }
    } break;
    case LANG_CHANGE_SHIFT_ALT: {
      register_code16(KC_LSFT);
      tap_code16(KC_LALT);
      unregister_code16(KC_LSFT);
      // Костыль, потому что при зажатом шифте если хочется нажать клавишу, которая переключает язык, то шифт слетает... 
      if (shift_current == SHIFT_ON) {
        register_code16(KC_LSFT);
      }
    } break;
    case LANG_CHANGE_CTRL_SHIFT: {
      register_code16(KC_LCTL);
      tap_code16(KC_LSFT);
      unregister_code16(KC_LCTL);
      // Костыль, потому что при зажатом шифте если хочется нажать клавишу, которая переключает язык, то шифт слетает...
      if (shift_current == SHIFT_ON) {
        register_code16(KC_LSFT);
      }
    } break;
    case LANG_CHANGE_SHIFT_CTRL: {
      register_code16(KC_LSFT);
      tap_code16(KC_LCTL);
      unregister_code16(KC_LSFT);
      // Костыль, потому что при зажатом шифте если хочется нажать клавишу, которая переключает язык, то шифт слетает...
      if (shift_current == SHIFT_ON) {
        register_code16(KC_LSFT);
      }
    } break;
    case LANG_CHANGE_WIN_SPACE: {
      register_code16(KC_LGUI);
      tap_code16(KC_SPACE);
      unregister_code16(KC_LGUI);
    } break;
  }
}

void s2l_activate_lang_kb(lang_t lang) {
  if ( lang_current == lang ) { return; }
  uprintf("activate_lang_kb: current %s, change to %s\n", lang_current == LANG_EN ? "EN" : "RU", lang == LANG_EN ? "EN" : "RU");
  s2l_send_lang_change_to_host();
  lang_current = lang;
}

void s2l_activate_lang(lang_t lang, bool sync) {
	lang_should_be = lang;
  if (sync) {
    s2l_activate_lang_kb(lang);
  } else {
    lang_current = lang;  
  }
}

void s2l_process_lang(uint16_t keycode, bool down) {
  lang_t new_lang = s2l_get_lang_from_keycode(keycode);
  if (down) {
    if (new_lang != LANG_NO) {
      uprintf("process_lang: new_lang %s\n", new_lang == LANG_EN ? "EN" : "RU");
      s2l_activate_lang_kb(new_lang);
	} else {
      uprintf("process_lang: can't determine lang from keycode\n");
      s2l_activate_lang_kb(lang_should_be);
	}
  }

  if (new_lang != LANG_NO) {
    if (down) {
      lang_press_count++;
    } else {
      lang_press_count--;
    }
  }

}

void s2l_lang_user_timer(void) {
	// Нужно выключать язык после прохождения определённого времени, потому что пользователь ожидает как будто шифт на самом деле включён
	if (lang_press_count == 0 && lang_current != lang_should_be && timer_elapsed(lang_timer) >= S2L_SHIFT_TERM) {
    uprintf("lang_user_timer: activate lang\n");
		s2l_activate_lang_kb(lang_should_be);
	}
}

// ---------------------------------------------------------------------------
//                                Обработка клавиш
// ---------------------------------------------------------------------------

//способ нажания произвольной клавиши взят из qmk
// см. quantum/process_keycode/process_combo.c -> release_combo()
// будет работать только с COMBO_ENABLE = yes или REPEAT_KEY_ENABLE = yes в rules.mk
void s2l_press_key(uint16_t keycode, bool down) {
  keyrecord_t record = {
    .event   = MAKE_KEYEVENT(0,0,down),
    .keycode = keycode 
  };
#ifndef NO_ACTION_TAPPING
  action_tapping_process(record);
#else
  process_record(&record);
#endif
}

void s2l_tap_key(uint16_t keycode) {
  s2l_press_key(keycode, true);
  s2l_press_key(keycode, false);
  s2l_activate_shift_kb(shift_should_be);
  s2l_activate_lang_kb(lang_should_be);
}

bool s2l_process_sp_keycodes(uint16_t keycode, keyrecord_t* record) {

  // Обрабатываем клавиши, связанные с кастомным шифтом и кастомным переключением языка
  switch (keycode) {
    case SFT_N_O:
      if (record->event.pressed) {
        once_shift_timer_enabled = false;
        s2l_activate_once_shift();
      } else {
        once_shift_timer_enabled = true;
        once_shift_timer = timer_read();
      }
      return false;
    case SFT_N:
      if (record->event.pressed) {
        s2l_activate_shift(SHIFT_ON); 
        layer_on(s2l_get_shift_layer_by_lang(lang_should_be));
      } else {
        shift_should_be = SHIFT_OFF; 
        if (shift_press_count == 0) {
          s2l_activate_shift(SHIFT_OFF); 
        }
        layer_off(s2l_get_shift_layer_by_lang(lang_should_be));
      }
      return false;
  }

  if (record->event.pressed) {
    switch (keycode) {
      case LA_CAPS: lang_change_current = LANG_CHANGE_CAPS;
                    return false;
      case LA_ALSH: lang_change_current = LANG_CHANGE_ALT_SHIFT;
                    return false;
      case LA_SHAL: lang_change_current = LANG_CHANGE_SHIFT_ALT;
                    return false;
      case LA_CTSH: lang_change_current = LANG_CHANGE_CTRL_SHIFT;
                    return false;
      case LA_SHCT: lang_change_current = LANG_CHANGE_SHIFT_CTRL;
                    return false;
      case LA_WISP: lang_change_current = LANG_CHANGE_WIN_SPACE;
                    return false;
      case LA_CHNG:
        if (lang_should_be == LANG_EN) {
          uprintf("LA_CHNG: lang_should_be EN, will change to RU\n");  
          s2l_activate_lang(LANG_RU, true);
          layer_on(S2L_LAYER_BASE_RU);  
        } else {
          uprintf("LA_CHNG: lang_should_be RU, will change to EN\n");  
          s2l_activate_lang(LANG_EN, true);
          layer_off(S2L_LAYER_BASE_RU); 
        }
        return false;
      case LA_SYNC: s2l_send_lang_change_to_host();
                    return false;
      case AG_3DOT: s2l_tap_key(AG_DOT);
                    s2l_tap_key(AG_DOT);
                    s2l_tap_key(AG_DOT);
                    return false;
      case AG_CMSP: s2l_tap_key(AG_COMM);
                    tap_code16(KC_SPC);
                    return false;
      case AG_SDOT: s2l_tap_key(AG_DOT);
                    tap_code16(KC_SPC);
                    s2l_activate_once_shift();
                    return false;
    }
  }

  return true;
}

bool s2l_process_en_modifiers(uint16_t keycode, keyrecord_t* record) {
  static lang_t lang_stack[3] = {};
  static uint8_t modifiers_count = 0;
  #define PROCESS(NAME, REGISTER, UNREGISTER, SYNC) \
    case NAME: \
      if (record->event.pressed) { \
        lang_stack[modifiers_count] = lang_should_be; \
        modifiers_count++; \
        if (lang_should_be == LANG_RU) { \
          layer_off(S2L_LAYER_BASE_RU); \
        } \
        s2l_activate_lang(LANG_EN, SYNC); \
        REGISTER; \
      } else { \
        UNREGISTER; \
        modifiers_count--; \
        s2l_activate_lang(lang_stack[modifiers_count], SYNC); \
        if (lang_should_be == LANG_RU) { \
          layer_on(S2L_LAYER_BASE_RU); \
        } \
      } \
      return false

  #define Rg(x) register_code16(KC_L ## x)    
  #define Un(x) unregister_code16(KC_L ## x)

  switch (keycode) {
    PROCESS(CTRL_0, Rg(CTL), Un(CTL), false);
    PROCESS(ALT_0,  Rg(ALT),  Un(ALT), false);
    PROCESS(WIN_0,  Rg(GUI),  Un(GUI), false);
    PROCESS(CTAL_0, { Rg(CTL);  Rg(ALT);   }, { Un(ALT);   Un(CTL);  }, false);
    PROCESS(SHAL_0, { Rg(SFT); Rg(ALT);   }, { Un(ALT);   Un(SFT); }, false);
    PROCESS(CTSH_0, { Rg(CTL);  Rg(SFT); }, { Un(SFT); Un(CTL);  }, false);
    PROCESS(MCAS_0, { Rg(CTL);  Rg(ALT); Rg(SFT); }, { Un(SFT); Un(ALT); Un(CTL); }, false);

    PROCESS(CTRL_EN, Rg(CTL), Un(CTL), true);
    PROCESS(ALT_EN,  Rg(ALT),  Un(ALT), true);
    PROCESS(WIN_EN,  Rg(GUI),  Un(GUI), true);
    PROCESS(CTAL_EN, { Rg(CTL);  Rg(ALT);   }, { Un(ALT);   Un(CTL);  }, true);
    PROCESS(SHAL_EN, { Rg(SFT); Rg(ALT);   }, { Un(ALT);   Un(SFT); }, true);
    PROCESS(CTSH_EN, { Rg(CTL);  Rg(SFT); }, { Un(SFT); Un(CTL);  }, true);
    PROCESS(MCAS_EN, { Rg(CTL);  Rg(ALT); Rg(SFT); }, { Un(SFT); Un(ALT); Un(CTL); }, true);
  }

  return true;
}

bool s2l_process(uint16_t keycode, keyrecord_t* record) {

  s2l_process_once_shift(keycode, record);

  uint16_t keycode_ag = s2l_translate_agnostic_keycode(keycode);
  if (keycode_ag != KC_NO) {
    uprintf("keycode is agnostic\n");
  }

  // Разбираемся, имеет ли эта клавиша какой-то язык, заданный в ней
  s2l_process_lang(keycode_ag, record->event.pressed);
  uint16_t keycode_lang = s2l_translate_lang_keycode(keycode_ag);

  // Разбираемся, имеет ли эта клавиша шифт, засунутый в неё
  // Это нужно отдельно от обработки языка, чтобы шифт мог выключаться для обычных клавиш
  s2l_process_shift(keycode_lang, record->event.pressed);
  uint16_t qk = s2l_translate_shift_keycode(keycode_lang);

/*
#define DEBUG_KC(x) \
    (x > AG_CMSP ? "?" : \
    (x >= AG_1 ? "AG" : \
    ( x >= RU_JO ? "RU" : \
    ( x >= EN_GRV ? "EN" : \
    ( x >= KS_GRV ? "KS" : "?" ))))), \
    (x > AG_CMSP ? 0 : \
    (x >= AG_1 ? x - AG_1 : \
    ( x >= RU_JO ? x - RU_JO : \
    ( x >= EN_GRV ? x - EN_GRV : \
    ( x >= KS_GRV ? x - KS_GRV : 0 )))))  

  uprintf("s2l_process: kc %d (%s,%d), kс2sft %d (%s,%d), qk %d\n", \
    keycode, DEBUG_KC(keycode), \
    keycode_to_shift, DEBUG_KC(keycode_to_shift), \
    qk);
*/

  if (qk != KC_NO) {
    if (record->event.pressed) {
      register_code16(qk); 
    } else {
      unregister_code16(qk);
    }
    return false;
  }

  if (!s2l_process_sp_keycodes(keycode, record)) {
    return false;
  }

  if (!s2l_process_en_modifiers(keycode, record)) {
    return false;
  }

  return true;
}

void s2l_user_timer(void) {
	s2l_shift_user_timer();
	s2l_once_shift_user_timer();
	s2l_lang_user_timer();
}