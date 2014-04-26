#ifndef __UTIL_H__
#define __UTIL_H__

#include <boost/algorithm/string.hpp>

using namespace boost::algorithm;

wstring add_word_to_output(wstring s) {
    // TODO make this work with wstring
    //replace_all(s, "\"", "\\\"");

    return s + L" ";//"\"" + s + "\", ";
}

#endif
