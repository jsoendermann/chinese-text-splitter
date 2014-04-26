#ifndef __UTIL_H__
#define __UTIL_H__

#include <boost/algorithm/string.hpp>

using namespace boost::algorithm;

string add_word_to_output(string s) {
    replace_all(s, "\"", "\\\"");

    return "\"" + s + "\", ";
}

#endif
