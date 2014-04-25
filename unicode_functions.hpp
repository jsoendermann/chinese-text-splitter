#include <string>

// These functions (except the last two) were taken from 
// http://sourceforge.net/p/openlierox/code/ci/master/tree/include/Unicode.h

template<typename _Iterator1, typename _Iterator2>
inline size_t IncUtf8StringIterator(_Iterator1& it, const _Iterator2& last) {
    if(it == last) return 0;
    unsigned char c;
    size_t res = 1;
    for(++it; last != it; ++it, ++res) {
        c = *it;
        if(!(c&0x80) || ((c&0xC0) == 0xC0)) break;
    }

    return res;
}

inline size_t Utf8StringSize(const std::string& str)  {
    size_t res = 0;
    std::string::const_iterator it = str.begin();
    for(; it != str.end(); IncUtf8StringIterator(it, str.end()))
        res++;

    return res;
}


template<typename _Iterator>
inline size_t MultIncUtf8StringIterator(_Iterator& it, const _Iterator& last, size_t count) {
    size_t res = 0;
    for(size_t i = 0; i < count; i++) {
        if(it == last) break;
        res += IncUtf8StringIterator(it, last);
    }

    return res;
}

inline std::string::iterator Utf8PositionToIterator(std::string& str, size_t pos) {
    std::string::iterator res = str.begin();
    MultIncUtf8StringIterator(res, str.end(), pos);
    return res;
}


inline std::string Utf8SubStr(std::string& str, size_t start, size_t n = (size_t)-1) {
    if (n == (size_t)-1)
        return std::string(Utf8PositionToIterator(str, start), str.end());
    else
        return std::string(
                Utf8PositionToIterator(str, start),
                Utf8PositionToIterator(str, start + n));
}



// TODO these two functions are very slow, because array access for utf8 strings is in
// O(n)
inline std::string get_char_at(std::string s, int i) {
    return Utf8SubStr(s, i, 1);
}

inline size_t get_length(std::string s) {
    return Utf8StringSize(s);
}
