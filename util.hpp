#ifndef __UTIL_HPP__
#define __UTIL_HPP__


wstring add_word_to_output(wstring s) {
    // TODO make this work with wstring
    //replace_all(s, "\"", "\\\"");

    return s + L" ";//"\"" + s + "\", ";
}

#endif
