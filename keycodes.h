enum s2l_keycodes {
	// Кейкоды, на основе которых реализуются кейкоды ниже, пользователю их лучше не использовать.
    KS_GRV   /* ` */ = S2L_RANGE,
    KS_TILD, /* ~ */
    KS_1,    /* 1 */
    KS_EXCL, /* ! */
    KS_2,    /* 2 */
    KS_AT,   /* @ */
    KS_3,    /* 3 */
    KS_HASH, /* # */
    KS_4,    /* 4 */
    KS_DLR,  /* $ */
    KS_5,    /* 5 */
    KS_PERC, /* % */
    KS_6,    /* 6 */
    KS_CIRC, /* ^ */
    KS_7,    /* 7 */
    KS_AMPR, /* & */
    KS_8,    /* 8 */
    KS_ASTR, /* * */
    KS_9,    /* 9 */
    KS_LPRN, /* ( */
    KS_0,    /* 0 */
    KS_RPRN, /* ) */
    KS_MINS, /* - */
    KS_UNDS, /* _ */
    KS_EQL,  /* = */
    KS_PLUS, /* + */

    KS_Q,    /* q */
    KS_S_Q,  /* Q */
    KS_W,    /* w */
    KS_S_W,  /* W */
    KS_E,    /* e */
    KS_S_E,  /* E */
    KS_R,    /* r */
    KS_S_R,  /* R */
    KS_T,    /* t */
    KS_S_T,  /* T */
    KS_Y,    /* y */
    KS_S_Y,  /* Y */
    KS_U,    /* u */
    KS_S_U,  /* U */
    KS_I,    /* i */
    KS_S_I,  /* I */
    KS_O,    /* o */
    KS_S_O,  /* O */
    KS_P,    /* p */
    KS_S_P,  /* P */
    KS_LBRC, /* [ */
    KS_LCBR, /* { */
    KS_RBRC, /* ] */
    KS_RCBR, /* } */

    KS_A,    /* a */
    KS_S_A,  /* A */
    KS_S,    /* s */
    KS_S_S,  /* S */
    KS_D,    /* d */
    KS_S_D,  /* D */
    KS_F,    /* f */
    KS_S_F,  /* F */
    KS_G,    /* g */
    KS_S_G,  /* G */
    KS_H,    /* h */
    KS_S_H,  /* H */
    KS_J,    /* j */
    KS_S_J,  /* J */
    KS_K,    /* k */
    KS_S_K,  /* K */
    KS_L,    /* l */
    KS_S_L,  /* L */
    KS_SCLN, /* ; */
    KS_COLN, /* : */
    KS_QUOT, /* ' */
    KS_DQUO, /* " */
    KS_BSLS, /* \ */
    KS_PIPE, /* | */

#ifndef LANG_USE_ANSI
    KS_LT2,   /* < */
    KS_GT2,   /* > */
#endif
    KS_Z,    /* z */
    KS_S_Z,  /* Z */
    KS_X,    /* x */
    KS_S_X,  /* X */
    KS_C,    /* c */
    KS_S_C,  /* C */
    KS_V,    /* v */
    KS_S_V,  /* V */
    KS_B,    /* b */
    KS_S_B,  /* B */
    KS_N,    /* n */
    KS_S_N,  /* N */
    KS_M,    /* m */
    KS_S_M,  /* M */
    KS_COMM, /* , */
    KS_LT,   /* < */
    KS_DOT,  /* . */
    KS_GT,   /* > */
    KS_SLSH, /* / */
    KS_QUES, /* ? */

	/* -------------------------------------------------------------------- */
	/* Английские символы */
	EN_GRV,  /* ` */
	EN_TILD, /* ~ */
	EN_1,    /* 1 */
	EN_EXCL, /* ! */
	EN_2,    /* 2 */
	EN_AT,   /* @ */
	EN_3,    /* 3 */
	EN_HASH, /* # */
	EN_4,    /* 4 */
	EN_DLR,  /* $ */
	EN_5,    /* 5 */
	EN_PERC, /* % */
	EN_6,    /* 6 */
	EN_CIRC, /* ^ */
	EN_7,    /* 7 */
	EN_AMPR, /* & */
	EN_8,    /* 8 */
	EN_ASTR, /* * */
	EN_9,    /* 9 */
	EN_LPRN, /* ( */
	EN_0,    /* 0 */
	EN_RPRN, /* ) */
	EN_MINS, /* - */
	EN_UNDS, /* _ */
	EN_EQL,  /* = */
	EN_PLUS, /* + */

	EN_Q,    /* q */
	EN_S_Q,  /* Q */
	EN_W,    /* w */
	EN_S_W,  /* W */
	EN_E,    /* e */
	EN_S_E,  /* E */
	EN_R,    /* r */
	EN_S_R,  /* R */
	EN_T,    /* t */
	EN_S_T,  /* T */
	EN_Y,    /* y */
	EN_S_Y,  /* Y */
	EN_U,    /* u */
	EN_S_U,  /* U */
	EN_I,    /* i */
	EN_S_I,  /* I */
	EN_O,    /* o */
	EN_S_O,  /* O */
	EN_P,    /* p */
	EN_S_P,  /* P */
	EN_LBRC, /* [ */
	EN_LCBR, /* { */
	EN_RBRC, /* ] */
	EN_RCBR, /* } */

	EN_A,    /* a */
	EN_S_A,  /* A */
	EN_S,    /* s */
	EN_S_S,  /* S */
	EN_D,    /* d */
	EN_S_D,  /* D */
	EN_F,    /* f */
	EN_S_F,  /* F */
	EN_G,    /* g */
	EN_S_G,  /* G */
	EN_H,    /* h */
	EN_S_H,  /* H */
	EN_J,    /* j */
	EN_S_J,  /* J */
	EN_K,    /* k */
	EN_S_K,  /* K */
	EN_L,    /* l */
	EN_S_L,  /* L */
	EN_SCLN, /* ; */
	EN_COLN, /* : */
	EN_QUOT, /* ' */
	EN_DQUO, /* " */
	EN_BSLS, /* \ */
	EN_PIPE, /* | */

#ifndef LANG_USE_ANSI
	EN_LT2,  /* < */
	EN_GT2,  /* > */
#endif
	EN_Z,    /* z */
	EN_S_Z,  /* Z */
	EN_X,    /* x */
	EN_S_X,  /* X */
	EN_C,    /* c */
	EN_S_C,  /* C */
	EN_V,    /* v */
	EN_S_V,  /* V */
	EN_B,    /* b */
	EN_S_B,  /* B */
	EN_N,    /* n */
	EN_S_N,  /* N */
	EN_M,    /* m */
	EN_S_M,  /* M */
	EN_COMM, /* , */
	EN_LT,   /* < */
	EN_DOT,  /* . */
	EN_GT,   /* > */
	EN_SLSH, /* / */
	EN_QUES, /* ? */

	/* -------------------------------------------------------------------- */
	/* Русские символы */
	RU_JO,   /* ё */
	RU_S_JO, /* Ё */
	RU_1,    /* 1 */
	RU_EXCL, /* ! */
	RU_2,    /* 2 */
	RU_DQUO, /* " */
	RU_3,    /* 3 */
	RU_NUME, /* № */
	RU_4,    /* 4 */
	RU_SCLN, /* ; */
	RU_5,    /* 5 */
	RU_PERC, /* % */
	RU_6,    /* 6 */
	RU_COLN, /* : */
	RU_7,    /* 7 */
	RU_QUES, /* ? */
	RU_8,    /* 8 */
	RU_ASTR, /* * */
	RU_9,    /* 9 */
	RU_LPRN, /* ( */
	RU_0,    /* 0 */
	RU_RPRN, /* ) */
	RU_MINS, /* - */
	RU_UNDS, /* _ */
	RU_EQL,  /* = */
	RU_PLUS, /* + */

	RU_J,    /* й */
	RU_S_J,  /* Й */
	RU_TS,   /* ц */
	RU_S_TS, /* Ц */
	RU_U,    /* у */
	RU_S_U,  /* У */
	RU_K,    /* к */
	RU_S_K,  /* К */
	RU_JE,   /* е */
	RU_S_JE, /* Е */
	RU_N,    /* н */
	RU_S_N,  /* Н */
	RU_G,    /* г */
	RU_S_G,  /* Г */
	RU_SH,   /* ш */
	RU_S_SH, /* Ш */
	RU_SC,   /* щ */
	RU_S_SC, /* Щ */
	RU_Z,    /* з */
	RU_S_Z,  /* З */
	RU_H,    /* х */
	RU_S_H,  /* Х */
	RU_HD,   /* ъ */
	RU_S_HD, /* Ъ */

	RU_F,    /* ф */
	RU_S_F,  /* Ф */
	RU_Y,    /* ы */
	RU_S_Y,  /* Ы */
	RU_V,    /* в */
	RU_S_V,  /* В */
	RU_A,    /* а */
	RU_S_A,  /* А */
	RU_P,    /* п */
	RU_S_P,  /* п */
	RU_R,    /* р */
	RU_S_R,  /* Р */
	RU_O,    /* о */
	RU_S_O,  /* О */
	RU_L,    /* л */
	RU_S_L,  /* Л */
	RU_D,    /* д */
	RU_S_D,  /* Д */
	RU_ZH,   /* ж */
	RU_S_ZH, /* Ж */
	RU_E,    /* э */
	RU_S_E,  /* Э */
	RU_BSLS, /* \ */
	RU_SLSH, /* / */

#ifndef LANG_USE_ANSI
	RU_SLS2, /* / */
	RU_PIPE, /* | */
#endif
	RU_JA,   /* я */
	RU_S_JA, /* Я */
	RU_CH,   /* ч */
	RU_S_CH, /* Ч */
	RU_S,    /* с */
	RU_S_S,  /* С */
	RU_M,    /* м */
	RU_S_M,  /* М */
	RU_I,    /* и */
	RU_S_I,  /* И */
	RU_T,    /* т */
	RU_S_T,  /* Т */
	RU_SF,   /* ь */
	RU_S_SF, /* Ь */
	RU_B,    /* б */
	RU_S_B,  /* Б */
	RU_JU,   /* ю */
	RU_S_JU, /* Ю */
	RU_DOT,  /* . */
	RU_COMM, /* , */

	/* -------------------------------------------------------------------- */
	/* Символы, нажимаемые независимо от текущего языка. Language-agnostic-keycodes. */
	AG_1,    /* 1 */
	AG_2,    /* 2 */
	AG_3,    /* 3 */
	AG_4,    /* 4 */
	AG_5,    /* 5 */
	AG_6,    /* 6 */
	AG_7,    /* 7 */
	AG_8,    /* 8 */
	AG_9,    /* 9 */
	AG_0,    /* 0 */
	AG_EXCL, /* ! */
	AG_PERC, /* % */
	AG_ASTR, /* * */
	AG_LPRN, /* ( */
	AG_RPRN, /* ) */
	AG_MINS, /* - */
	AG_UNDS, /* _ */
	AG_EQL,  /* = */
	AG_PLUS, /* + */
	AG_SCLN, /* ; */
	AG_COLN, /* : */
	AG_DQUO, /* " */
	AG_BSLS, /* \ */
#ifndef LANG_USE_ANSI
	AG_PIPE, /* | */
#endif
	AG_COMM, /* , */
	AG_DOT,  /* . */
	AG_SLSH, /* / */
#ifndef LANG_USE_ANSI
	AG_S_SL, /* / */ // This keycode uses the slash with shift on Russian layout instead the slash without shift
#endif
	AG_QUES, /* ? */

	/* -------------------------------------------------------------------- */
	/* Кастомные language-agnostic-кейкоды */
	AG_3DOT, /* ... */
	AG_SDOT, /* Dot + Space + Shift to next key */
	AG_CMSP, /* Comma + Space */

	/* -------------------------------------------------------------------- */
	/* Шифты для набора текста. */
	SFT_N,   /* Работает как обычный шифт, при её зажатии, шифт зажат. Параллельно переключает на (шифтовый) следующий слой относительно текущего языка (если язык 0, то включает слой 1, если язык 1, то включает слой 3). */
	SFT_N_O, /* Данная клавиша применит шифт и переключение на шифтовый слой только к следующему символу. Неважно, была ли она нажата одновременно со следующей клавишей, или до неё, или вместе с двумя клавишами. Применится только к одной клавише. То есть это как залипающий шифт, если нажимать отдельно от всех клавиш, и как одиночный шифт, если эту клавишу зажимать. Такая клавиша может пригодиться если вы печатаете с большой скоростью и вам сложно выдерживать время удержания шифта, и у вас получается что-то вроде "ПРивет". */

	/* -------------------------------------------------------------------- */
	/* Модификаторы, переключащие текущий слой на 0. Такое нужно чтобы при включённом русском языке были такие же хоткеи с модификаторами, как и на английском языке. */
	CTRL_0, /* Ctrl on 0 layer */
	ALT_0,  /* Alt on 0 layer */
	WIN_0,  /* Win on 0 layer */
	SHAL_0, /* Shift+Alt on 0 layer */
	CTAL_0, /* Ctrl+Alt on 0 layer */
	CTSH_0, /* Ctrl+Shift on 0 layer */
	MCAS_0, /* Ctrl+Alt+Shift on 0 layer */

	/* А данные модификаторы помимо включения 0 слоя ещё и переключают язык на английский. Такое разделение нужно, потому что у некоторых смена языка идёт на комбинации с Ctrl, или Shift, и у них может сниматься выделение текста, например. */
	CTRL_EN, /* Ctrl on 0 layer */
	ALT_EN,  /* Alt on 0 layer */
	WIN_EN,  /* Win on 0 layer */
	SHAL_EN, /* Shift+Alt on 0 layer */
	CTAL_EN, /* Ctrl+Alt on 0 layer */
	CTSH_EN, /* Ctrl+Shift on 0 layer */
	MCAS_EN, /* Ctrl+Alt+Shift on 0 layer */

	/* -------------------------------------------------------------------- */
	/* Кнопки, отвечающие за переключение языка. */
	LA_CHNG, /* Переключает язык и переключает на 2 или 0 слой в зависимости от текущего языка. */
	LA_SYNC, /* Кнопка для синхронизации языков. Её нужно нажимать в случае если язык в системе и язык в клавиатуре различаются. Данная клавиша изменит язык в системе. */
	LA_CAPS, /* Задаёт переключение языка на Caps. */
	LA_ALSH, /* Задаёт переключение языка на Alt + Shift. */
	LA_SHAL, /* Задаёт переключение языка на Shift + Alt. На Win10 это позволяет избежать появления окна переключения языков. */
	LA_CTSH, /* Задаёт переключение языка на Ctrl + Shift. */
	LA_SHCT, /* Задаёт переключение языка на Shift + Ctrl. На Win10 это позволяет избежать появления окна переключения языков. */
	LA_WISP  /* Задаёт переключение языка на Win + Shift. */
};

