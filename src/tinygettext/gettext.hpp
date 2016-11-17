#ifndef GETTEXT_H
#define GETTEXT_H

#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || _MSC_VER > 1000
#pragma once
#endif

#include "tinygettext/TinyGetText.hpp"

extern TinyGetText::DictionaryManager* dictionaryManager;

#ifdef NEED_GETTEXT_CHARHACK
static inline char* _(const char* message)
{
    return const_cast<char*>
        (dictionaryManager->get_dictionary().translate(message));
}
#else
static inline const char* _(const char* message)
{
    return dictionaryManager->get_dictionary().translate(message);
}
#endif

#define N_(s)      s

#endif
