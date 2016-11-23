/*
 findlocale-0.46.tar.gz from http://icculus.org/~aspirin/findlocale/

Copyright (C) 2004 Adam D. Moss (the "Author").  All Rights Reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is fur-
nished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FIT-
NESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CON-
NECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the Author of the
Software shall not be used in advertising or otherwise to promote the sale,
use or other dealings in this Software without prior written authorization
from the Author.

*/
#include <config.h>

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
#include <winnt.h>
#endif

#ifdef MACOSX
#include <Carbon/Carbon.h>
#endif

#include "findlocale.hpp"

static int
is_lcchar(const int c) {
  return isalnum(c);
}

static void
lang_country_variant_from_envstring(const char *str,
                                    char **lang,
                                    char **country,
                                    char **variant) {
  int end = 0;
  int start;

  /* get lang, if any */
  start = end;
  while (is_lcchar(str[end])) {
    ++end;
  }
  if (start != end) {
    int i;
    int len = end - start;
    char *s = (char*) malloc(len + 1);
    for (i=0; i<len; ++i) {
      s[i] = tolower(str[start + i]);
    }
    s[i] = '\0';
    *lang = s;
  } else {
    *lang = NULL;
  }

  if (str[end] && str[end]!=':') { /* not at end of str */
    ++end;
  }

  /* get country, if any */
  start = end;
  while (is_lcchar(str[end])) {
    ++end;
  }
  if (start != end) {
    int i;
    int len = end - start;
    char *s = (char*) malloc(len + 1);
    for (i=0; i<len; ++i) {
      s[i] = toupper(str[start + i]);
    }
    s[i] = '\0';
    *country = s;
  } else {
    *country = NULL;
  }

  if (str[end] && str[end]!=':') { /* not at end of str */
    ++end;
  }

  /* get variant, if any */
  start = end;
  while (str[end] && str[end]!=':') {
    ++end;
  }
  if (start != end) {
    int i;
    int len = end - start;
    char *s = (char*) malloc(len + 1);
    for (i=0; i<len; ++i) {
      s[i] = str[start + i];
    }
    s[i] = '\0';
    *variant = s;
  } else {
    *variant = NULL;
  }
}


static int
accumulate_locstring(const char *str, FL_Locale *l) {
  char *lang = NULL;
  char *country = NULL;
  char *variant = NULL;
  if (str) {
    lang_country_variant_from_envstring(str, &lang, &country, &variant);
    if (lang) {
      l->lang = lang;
      l->country = country;
      l->variant = variant;
      return 1;
    }
  }
  free(lang); free(country); free(variant);
  return 0;
}


#ifndef _WIN32
static int
accumulate_env(const char *name, FL_Locale *l) {
  char *env;
  char *lang = NULL;
  char *country = NULL;
  char *variant = NULL;
  env = getenv(name);
  if (env) {
    return accumulate_locstring(env, l);
  }
  free(lang); free(country); free(variant);
  return 0;
}
#endif

static void
canonise_fl(FL_Locale *l) {
  /* this function fixes some common locale-specifying mistakes */
  /* en_UK -> en_GB */
  if (l->lang && 0 == strcmp(l->lang, "en")) {
    if (l->country && 0 == strcmp(l->country, "UK")) {
      free((void*)l->country);
      l->country = strdup("GB");
    }
  }
  /* ja_JA -> ja_JP */
  if (l->lang && 0 == strcmp(l->lang, "ja")) {
    if (l->country && 0 == strcmp(l->country, "JA")) {
      free((void*)l->country);
      l->country = strdup("JP");
    }
  }
}


#ifdef _WIN32
#include <stdio.h>
#define ML(pn,sn) MAKELANGID(LANG_##pn, SUBLANG_##pn##_##sn)
#define MLN(pn) MAKELANGID(LANG_##pn, SUBLANG_DEFAULT)
#define RML(pn,sn) MAKELANGID(LANG_##pn, SUBLANG_##sn)
typedef struct {
  LANGID id;
  char*  code;
} IDToCode;
static const IDToCode both_to_code[] = {
  {ML(ENGLISH,US),                          (char*)"en_US.ISO_8859-1"},
  {ML(ENGLISH,CAN),                         (char*)"en_CA"}, /* english / canadian */
  {ML(ENGLISH,UK),                          (char*)"en_GB"},
  {ML(ENGLISH,EIRE),                        (char*)"en_IE"},
  {ML(ENGLISH,AUS),                         (char*)"en_AU"},
  {MLN(GERMAN),                             (char*)"de_DE"},
  {MLN(SPANISH),                            (char*)"es_ES"},
  {ML(SPANISH,MEXICAN),                     (char*)"es_MX"},
  {MLN(FRENCH),                             (char*)"fr_FR"},
  {ML(FRENCH,CANADIAN),                     (char*)"fr_CA"},
  {ML(FRENCH,BELGIAN),                      (char*)"fr_BE"}, /* ? */
  {ML(DUTCH,BELGIAN),                       (char*)"nl_BE"}, /* ? */
  {ML(PORTUGUESE,BRAZILIAN),                (char*)"pt_BR"},
  {MLN(PORTUGUESE),                         (char*)"pt_PT"},
  {MLN(SWEDISH),                            (char*)"sv_SE"},
  {ML(CHINESE,HONGKONG),                    (char*)"zh_HK"},
  /* these are machine-generated and not yet verified */
  {RML(AFRIKAANS,DEFAULT),                  (char*)"af_ZA"},
  {RML(ALBANIAN,DEFAULT),                   (char*)"sq_AL"},
  {RML(ARABIC,ARABIC_ALGERIA),              (char*)"ar_DZ"},
  {RML(ARABIC,ARABIC_BAHRAIN),              (char*)"ar_BH"},
  {RML(ARABIC,ARABIC_EGYPT),                (char*)"ar_EG"},
  {RML(ARABIC,ARABIC_IRAQ),                 (char*)"ar_IQ"},
  {RML(ARABIC,ARABIC_JORDAN),               (char*)"ar_JO"},
  {RML(ARABIC,ARABIC_KUWAIT),               (char*)"ar_KW"},
  {RML(ARABIC,ARABIC_LEBANON),              (char*)"ar_LB"},
  {RML(ARABIC,ARABIC_LIBYA),                (char*)"ar_LY"},
  {RML(ARABIC,ARABIC_MOROCCO),              (char*)"ar_MA"},
  {RML(ARABIC,ARABIC_OMAN),                 (char*)"ar_OM"},
  {RML(ARABIC,ARABIC_QATAR),                (char*)"ar_QA"},
  {RML(ARABIC,ARABIC_SAUDI_ARABIA),         (char*)"ar_SA"},
  {RML(ARABIC,ARABIC_SYRIA),                (char*)"ar_SY"},
  {RML(ARABIC,ARABIC_TUNISIA),              (char*)"ar_TN"},
  {RML(ARABIC,ARABIC_UAE),                  (char*)"ar_AE"},
  {RML(ARABIC,ARABIC_YEMEN),                (char*)"ar_YE"},
  {RML(ARMENIAN,DEFAULT),                   (char*)"hy_AM"},
  {RML(AZERI,AZERI_CYRILLIC),               (char*)"az_AZ"},
  {RML(AZERI,AZERI_LATIN),                  (char*)"az_AZ"},
  {RML(BASQUE,DEFAULT),                     (char*)"eu_ES"},
  {RML(BELARUSIAN,DEFAULT),                 (char*)"be_BY"},
/*{RML(BRETON,DEFAULT), "br_FR"},*/
  {RML(BULGARIAN,DEFAULT),                  (char*)"bg_BG"},
  {RML(CATALAN,DEFAULT),                    (char*)"ca_ES"},
  {RML(CHINESE,CHINESE_HONGKONG),           (char*)"zh_HK"},
  {RML(CHINESE,CHINESE_MACAU),              (char*)"zh_MO"},
  {RML(CHINESE,CHINESE_SIMPLIFIED),         (char*)"zh_CN"},
  {RML(CHINESE,CHINESE_SINGAPORE),          (char*)"zh_SG"},
  {RML(CHINESE,CHINESE_TRADITIONAL),        (char*)"zh_TW"},
/*{RML(CORNISH,DEFAULT), "kw_GB"},*/
  {RML(CZECH,DEFAULT),                      (char*)"cs_CZ"},
  {RML(DANISH,DEFAULT),                     (char*)"da_DK"},
  {RML(DUTCH,DUTCH),                        (char*)"nl_NL"},
  {RML(DUTCH,DUTCH_BELGIAN),                (char*)"nl_BE"},
/*{RML(DUTCH,DUTCH_SURINAM), "nl_SR"},*/
  {RML(ENGLISH,ENGLISH_AUS),                (char*)"en_AU"},
  {RML(ENGLISH,ENGLISH_BELIZE),             (char*)"en_BZ"},
  {RML(ENGLISH,ENGLISH_CAN),                (char*)"en_CA"},
  {RML(ENGLISH,ENGLISH_CARIBBEAN),          (char*)"en_CB"},
  {RML(ENGLISH,ENGLISH_EIRE),               (char*)"en_IE"},
  {RML(ENGLISH,ENGLISH_JAMAICA),            (char*)"en_JM"},
  {RML(ENGLISH,ENGLISH_NZ),                 (char*)"en_NZ"},
  {RML(ENGLISH,ENGLISH_PHILIPPINES),        (char*)"en_PH"},
  {RML(ENGLISH,ENGLISH_SOUTH_AFRICA),       (char*)"en_ZA"},
  {RML(ENGLISH,ENGLISH_TRINIDAD),           (char*)"en_TT"},
  {RML(ENGLISH,ENGLISH_UK),                 (char*)"en_GB"},
  {RML(ENGLISH,ENGLISH_US),                 (char*)"en_US"},
  {RML(ENGLISH,ENGLISH_ZIMBABWE),           (char*)"en_ZW"},
/*{RML(ESPERANTO,DEFAULT), "eo_"},*/
  {RML(ESTONIAN,DEFAULT),                   (char*)"et_EE"},
  {RML(FAEROESE,DEFAULT),                   (char*)"fo_FO"},
  {RML(FARSI,DEFAULT),                      (char*)"fa_IR"},
  {RML(FINNISH,DEFAULT),                    (char*)"fi_FI"},
  {RML(FRENCH,FRENCH),                      (char*)"fr_FR"},
  {RML(FRENCH,FRENCH_BELGIAN),              (char*)"fr_BE"},
  {RML(FRENCH,FRENCH_CANADIAN),             (char*)"fr_CA"},
  {RML(FRENCH,FRENCH_LUXEMBOURG),           (char*)"fr_LU"},
  {RML(FRENCH,FRENCH_MONACO),               (char*)"fr_MC"},
  {RML(FRENCH,FRENCH_SWISS),                (char*)"fr_CH"},
/*{RML(GAELIC,GAELIC), "ga_IE"},*/
/*{RML(GAELIC,GAELIC_MANX), "gv_GB"},*/
/*{RML(GAELIC,GAELIC_SCOTTISH), "gd_GB"},*/
/*{RML(GALICIAN,DEFAULT), "gl_ES"},*/
  {RML(GEORGIAN,DEFAULT),                   (char*)"ka_GE"},
  {RML(GERMAN,GERMAN),                      (char*)"de_DE"},
  {RML(GERMAN,GERMAN_AUSTRIAN),             (char*)"de_AT"},
  {RML(GERMAN,GERMAN_LIECHTENSTEIN),        (char*)"de_LI"},
  {RML(GERMAN,GERMAN_LUXEMBOURG),           (char*)"de_LU"},
  {RML(GERMAN,GERMAN_SWISS),                (char*)"de_CH"},
  {RML(GREEK,DEFAULT),                      (char*)"el_GR"},
  {RML(GUJARATI,DEFAULT),                   (char*)"gu_IN"},
  {RML(HEBREW,DEFAULT),                     (char*)"he_IL"},
  {RML(HINDI,DEFAULT),                      (char*)"hi_IN"},
  {RML(HUNGARIAN,DEFAULT),                  (char*)"hu_HU"},
  {RML(ICELANDIC,DEFAULT),                  (char*)"is_IS"},
  {RML(INDONESIAN,DEFAULT),                 (char*)"id_ID"},
  {RML(ITALIAN,ITALIAN),                    (char*)"it_IT"},
  {RML(ITALIAN,ITALIAN_SWISS),              (char*)"it_CH"},
  {RML(JAPANESE,DEFAULT),                   (char*)"ja_JP"},
  {RML(KANNADA,DEFAULT),                    (char*)"kn_IN"},
  {RML(KAZAK,DEFAULT),                      (char*)"kk_KZ"},
  {RML(KONKANI,DEFAULT),                    (char*)"kok_IN"},
  {RML(KOREAN,KOREAN),                      (char*)"ko_KR"},
/*{RML(KYRGYZ,DEFAULT), "ky_KG"},*/
  {RML(LATVIAN,DEFAULT),                    (char*)"lv_LV"},
  {RML(LITHUANIAN,LITHUANIAN),              (char*)"lt_LT"},
  {RML(MACEDONIAN,DEFAULT),                 (char*)"mk_MK"},
  {RML(MALAY,MALAY_BRUNEI_DARUSSALAM),      (char*)"ms_BN"},
  {RML(MALAY,MALAY_MALAYSIA),               (char*)"ms_MY"},
  {RML(MARATHI,DEFAULT),                    (char*)"mr_IN"},
/*{RML(MONGOLIAN,DEFAULT), "mn_MN"},*/
  {RML(NORWEGIAN,NORWEGIAN_BOKMAL),         (char*)"nb_NO"},
  {RML(NORWEGIAN,NORWEGIAN_NYNORSK),        (char*)"nn_NO"},
  {RML(POLISH,DEFAULT),                     (char*)"pl_PL"},
  {RML(PORTUGUESE,PORTUGUESE),              (char*)"pt_PT"},
  {RML(PORTUGUESE,PORTUGUESE_BRAZILIAN),    (char*)"pt_BR"},
  {RML(PUNJABI,DEFAULT),                    (char*)"pa_IN"},
  {RML(ROMANIAN,DEFAULT),                   (char*)"ro_RO"},
  {RML(RUSSIAN,DEFAULT),                    (char*)"ru_RU"},
  {RML(SANSKRIT,DEFAULT),                   (char*)"sa_IN"},
  {RML(SERBIAN,DEFAULT),                    (char*)"hr_HR"},
  {RML(SERBIAN,SERBIAN_CYRILLIC),           (char*)"sr_SP"},
  {RML(SERBIAN,SERBIAN_LATIN),              (char*)"sr_SP"},
  {RML(SLOVAK,DEFAULT),                     (char*)"sk_SK"},
  {RML(SLOVENIAN,DEFAULT),                  (char*)"sl_SI"},
  {RML(SPANISH,SPANISH),                    (char*)"es_ES"},
  {RML(SPANISH,SPANISH_ARGENTINA),          (char*)"es_AR"},
  {RML(SPANISH,SPANISH_BOLIVIA),            (char*)"es_BO"},
  {RML(SPANISH,SPANISH_CHILE),              (char*)"es_CL"},
  {RML(SPANISH,SPANISH_COLOMBIA),           (char*)"es_CO"},
  {RML(SPANISH,SPANISH_COSTA_RICA),         (char*)"es_CR"},
  {RML(SPANISH,SPANISH_DOMINICAN_REPUBLIC), (char*)"es_DO"},
  {RML(SPANISH,SPANISH_ECUADOR),            (char*)"es_EC"},
  {RML(SPANISH,SPANISH_EL_SALVADOR),        (char*)"es_SV"},
  {RML(SPANISH,SPANISH_GUATEMALA),          (char*)"es_GT"},
  {RML(SPANISH,SPANISH_HONDURAS),           (char*)"es_HN"},
  {RML(SPANISH,SPANISH_MEXICAN),            (char*)"es_MX"},
  {RML(SPANISH,SPANISH_MODERN),             (char*)"es_ES"},
  {RML(SPANISH,SPANISH_NICARAGUA),          (char*)"es_NI"},
  {RML(SPANISH,SPANISH_PANAMA),             (char*)"es_PA"},
  {RML(SPANISH,SPANISH_PARAGUAY),           (char*)"es_PY"},
  {RML(SPANISH,SPANISH_PERU),               (char*)"es_PE"},
  {RML(SPANISH,SPANISH_PUERTO_RICO),        (char*)"es_PR"},
  {RML(SPANISH,SPANISH_URUGUAY),            (char*)"es_UY"},
  {RML(SPANISH,SPANISH_VENEZUELA),          (char*)"es_VE"},
  {RML(SWAHILI,DEFAULT),                    (char*)"sw_KE"},
  {RML(SWEDISH,SWEDISH),                    (char*)"sv_SE"},
  {RML(SWEDISH,SWEDISH_FINLAND),            (char*)"sv_FI"},
/*{RML(SYRIAC,DEFAULT), "syr_SY"},*/
  {RML(TAMIL,DEFAULT),                      (char*)"ta_IN"},
  {RML(TATAR,DEFAULT),                      (char*)"tt_TA"},
  {RML(TELUGU,DEFAULT),                     (char*)"te_IN"},
  {RML(THAI,DEFAULT),                       (char*)"th_TH"},
  {RML(TURKISH,DEFAULT),                    (char*)"tr_TR"},
  {RML(UKRAINIAN,DEFAULT),                  (char*)"uk_UA"},
  {RML(URDU,URDU_PAKISTAN),                 (char*)"ur_PK"},
  {RML(UZBEK,UZBEK_CYRILLIC),               (char*)"uz_UZ"},
  {RML(UZBEK,UZBEK_LATIN),                  (char*)"uz_UZ"},
  {RML(VIETNAMESE,DEFAULT),                 (char*)"vi_VN"},
/*{RML(WALON,DEFAULT), "wa_BE"},*/
/*{RML(WELSH,DEFAULT), "cy_GB"},*/
};
static const IDToCode primary_to_code[] = {
  {LANG_AFRIKAANS,  (char*)"af"},
  {LANG_ARABIC,     (char*)"ar"},
  {LANG_AZERI,      (char*)"az"},
  {LANG_BULGARIAN,  (char*)"bg"},
/*{LANG_BRETON,     "br"},*/
  {LANG_BELARUSIAN, (char*)"by"},
  {LANG_CATALAN,    (char*)"ca"},
  {LANG_CZECH,      (char*)"cs"},
/*{LANG_WELSH,      "cy"},*/
  {LANG_DANISH,     (char*)"da"},
  {LANG_GERMAN,     (char*)"de"},
  {LANG_GREEK,      (char*)"el"},
  {LANG_ENGLISH,    (char*)"en"},
/*{LANG_ESPERANTO,  "eo"},*/
  {LANG_SPANISH,    (char*)"es"},
  {LANG_ESTONIAN,   (char*)"et"},
  {LANG_BASQUE,     (char*)"eu"},
  {LANG_FARSI,      (char*)"fa"},
  {LANG_FINNISH,    (char*)"fi"},
  {LANG_FAEROESE,   (char*)"fo"},
  {LANG_FRENCH,     (char*)"fr"},
/*{LANG_GAELIC,     "ga"},*/
/*{LANG_GALICIAN,   "gl"},*/
  {LANG_GUJARATI,   (char*)"gu"},
  {LANG_HEBREW,     (char*)"he"},
  {LANG_HINDI,      (char*)"hi"},
  {LANG_SERBIAN,    (char*)"hr"},
  {LANG_HUNGARIAN,  (char*)"hu"},
  {LANG_ARMENIAN,   (char*)"hy"},
  {LANG_INDONESIAN, (char*)"id"},
  {LANG_ITALIAN,    (char*)"it"},
  {LANG_JAPANESE,   (char*)"ja"},
  {LANG_GEORGIAN,   (char*)"ka"},
  {LANG_KAZAK,      (char*)"kk"},
  {LANG_KANNADA,    (char*)"kn"},
  {LANG_KOREAN,     (char*)"ko"},
/*{LANG_KYRGYZ,     "ky"},*/
  {LANG_LITHUANIAN, (char*)"lt"},
  {LANG_LATVIAN,    (char*)"lv"},
  {LANG_MACEDONIAN, (char*)"mk"},
/*{LANG_MONGOLIAN,  "mn"},*/
  {LANG_MARATHI,    (char*)"mr"},
  {LANG_MALAY,      (char*)"ms"},
  {LANG_NORWEGIAN,  (char*)"nb"},
  {LANG_DUTCH,      (char*)"nl"},
  {LANG_NORWEGIAN,  (char*)"nn"},
  {LANG_NORWEGIAN,  (char*)"no"},/* unofficial? */
  {LANG_PUNJABI,    (char*)"pa"},
  {LANG_POLISH,     (char*)"pl"},
  {LANG_PORTUGUESE, (char*)"pt"},
  {LANG_ROMANIAN,   (char*)"ro"},
  {LANG_RUSSIAN,    (char*)"ru"},
  {LANG_SLOVAK,     (char*)"sk"},
  {LANG_SLOVENIAN,  (char*)"sl"},
  {LANG_ALBANIAN,   (char*)"sq"},
  {LANG_SERBIAN,    (char*)"sr"},
  {LANG_SWEDISH,    (char*)"sv"},
  {LANG_SWAHILI,    (char*)"sw"},
  {LANG_TAMIL,      (char*)"ta"},
  {LANG_THAI,       (char*)"th"},
  {LANG_TURKISH,    (char*)"tr"},
  {LANG_TATAR,      (char*)"tt"},
  {LANG_UKRAINIAN,  (char*)"uk"},
  {LANG_URDU,       (char*)"ur"},
  {LANG_UZBEK,      (char*)"uz"},
  {LANG_VIETNAMESE, (char*)"vi"},
/*{LANG_WALON,      "wa"},*/
  {LANG_CHINESE,    (char*)"zh"},
};
static int num_primary_to_code =
  sizeof(primary_to_code) / sizeof(*primary_to_code);
static int num_both_to_code =
  sizeof(both_to_code) / sizeof(*both_to_code);

static int lcid_to_fl(LCID lcid, FL_Locale *rtn) {
	LANGID langid       = LANGIDFROMLCID(lcid);
	LANGID primary_lang = PRIMARYLANGID(langid);
#if 0
	LANGID sub_lang     = SUBLANGID(langid);
#endif
	int i;
	/* try to find an exact primary/sublanguage combo that we know about */
	for (i=0; i<num_both_to_code; ++i) {
		if (both_to_code[i].id == langid) {
			accumulate_locstring(both_to_code[i].code, rtn);
			return 1;
		}
	}
	/* fallback to just checking the primary language id */
	for (i=0; i<num_primary_to_code; ++i) {
		if (primary_to_code[i].id == primary_lang) {
			accumulate_locstring(primary_to_code[i].code, rtn);
			return 1;
		}
	}
	return 0;
}
#endif


FL_Success
FL_FindLocale(FL_Locale **locale, FL_Domain /*domain*/) {
  FL_Success success = FL_FAILED;
  FL_Locale *rtn = (FL_Locale*) malloc(sizeof(FL_Locale));
  rtn->lang = NULL;
  rtn->country = NULL;
  rtn->variant = NULL;

#ifdef _WIN32
  /* win32 >= mswindows95 */
  {
    LCID lcid = GetThreadLocale();
    if (lcid_to_fl(lcid, rtn)) {
      success = FL_CONFIDENT;
    }
    if (success == FL_FAILED) {
      /* assume US English on mswindows systems unless we know otherwise */
      if (accumulate_locstring("en_US.ISO_8859-1", rtn)) {
        success = FL_DEFAULT_GUESS;
      }
    }
  }
#else
  /* assume unixoid */
  {
#ifdef MACOSX
    CFIndex sz;
    CFArrayRef languages;
    CFStringRef uxstylelangs;
    char *uxsl;

    /* get the languages from the user's presets */
    languages = (CFArrayRef)CFPreferencesCopyValue(CFSTR("AppleLanguages"),
      kCFPreferencesAnyApplication, kCFPreferencesCurrentUser,
      kCFPreferencesAnyHost);

    /* join the returned string array into a string separated by colons */
    uxstylelangs = CFStringCreateByCombiningStrings(kCFAllocatorDefault,
      languages, CFSTR(":"));

    /* convert this string into a C string */
    sz = CFStringGetLength(uxstylelangs) + 1;
    uxsl = (char*)malloc(sz);
    CFStringGetCString(uxstylelangs, uxsl, sz, kCFStringEncodingISOLatin1);

    /* add it to the list */
    if (accumulate_locstring(uxsl, rtn)) {
      success = FL_CONFIDENT;
    }
    /* continue the UNIX method */
#endif
    /* examples: */
    /* sv_SE.ISO_8859-1 */
    /* fr_FR.ISO8859-1 */
    /* no_NO_NB */
    /* no_NO_NY */
    /* no_NO */
    /* de_DE */
    /* try the various vars in decreasing order of authority */
    if (accumulate_env("LC_ALL", rtn) ||
        accumulate_env("LC_MESSAGES", rtn) ||
        accumulate_env("LANG", rtn) ||
        accumulate_env("LANGUAGE", rtn)) {
      success = FL_CONFIDENT;
    }
    if (success == FL_FAILED) {
      /* assume US English on unixoid systems unless we know otherwise */
      if (accumulate_locstring("en_US.ISO_8859-1", rtn)) {
        success = FL_DEFAULT_GUESS;
      }
    }
  }
#endif

  if (success != FL_FAILED) {
    canonise_fl(rtn);
  }

  *locale = rtn;
  return success;
}


void
FL_FreeLocale(FL_Locale **locale) {
  if (locale) {
    FL_Locale *l = *locale;
    if (l) {
      if (l->lang) {
        free((void*)l->lang);
      }
      if (l->country) {
        free((void*)l->country);
      }
      if (l->variant) {
        free((void*)l->variant);
      }
      free(l);
      *locale = NULL;
    }
  }
}
