import gettext
import locale
import os
import sys

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
LOCALE_DIR = os.path.join(BASE_DIR, 'locale')

def get_system_language():
    """Detecta el idioma del sistema (es o en)."""
    try:
        lang = locale.getdefaultlocale()[0]
        if lang:
            code = lang.split("_")[0].lower()
            return code if code in ["es", "en"] else "en"
    except Exception:
        pass
    return "en"

active_lang = get_system_language()

try:
    translator = gettext.translation(
        domain=active_lang,
        localedir=LOCALE_DIR,
        languages=[active_lang],
        fallback=True
    )
except FileNotFoundError:
    print(f"Advertencia: No se encontró traducción para '{active_lang}' en {LOCALE_DIR}")
    translator = gettext.NullTranslations()

def _(message):
    return translator.gettext(message)

def set_locale(lang_code):
    global translator
    try:
        translator = gettext.translation(
            domain=lang_code,
            localedir=LOCALE_DIR,
            languages=[lang_code],
            fallback=True
        )
    except Exception:
        pass
