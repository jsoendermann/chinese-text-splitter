#include <string>

// These functions (except for the last two) were taken from 
// http://sourceforge.net/p/openlierox/code/ci/master/tree/include/Unicode.h
// They are used for unicode string handling.

typedef uint32_t UnicodeChar;
typedef std::basic_string<UnicodeChar> UnicodeString;

// Some function declarations
template<typename _Iterator>
inline size_t MultIncUtf8StringIterator(_Iterator& it, const _Iterator& last, size_t count);
inline std::string::iterator Utf8PositionToIterator(std::string& str, size_t pos);


////////////////////////
// Reads next unicode character from a UTF8 encoded string
// the iterator shows at the next character after this operation
UnicodeChar GetNextUnicodeFromUtf8(std::string::const_iterator &it, const std::string::const_iterator& last, size_t& num_skipped) {
	num_skipped = 0;
	if(it == last) return 0;
	
	unsigned char ch = *it;
	UnicodeChar res = ch;
	if ( ch >= 0xFC ) {
		res  =  (ch&0x01) << 30; it++; num_skipped++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F) << 24; it++; num_skipped++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F) << 18; it++; num_skipped++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F) << 12; it++; num_skipped++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F) << 6; it++;  num_skipped++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F);
	} else
	if ( ch >= 0xF8 ) {
		res  =  (ch&0x03) << 24; num_skipped++; it++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F) << 18; num_skipped++; it++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F) << 12; num_skipped++; it++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F) << 6;  num_skipped++; it++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F);
	} else
	if ( ch >= 0xF0 ) {
		res  =  (ch&0x07) << 18; it++; num_skipped++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F) << 12; it++; num_skipped++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F) << 6; it++;  num_skipped++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F);
	} else
	if ( ch >= 0xE0 ) {
		res  =  (ch&0x0F) << 12; it++; num_skipped++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F) << 6; it++; num_skipped++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F);
	} else
	if ( ch >= 0xC0 ) {
		res  =  (ch&0x1F) << 6; it++; num_skipped++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F);
	}

	it++; num_skipped++;
	return res;
}

inline UnicodeChar GetNextUnicodeFromUtf8(std::string::const_iterator& it, const std::string::const_iterator& last)  {
	size_t tmp;	
    return GetNextUnicodeFromUtf8(it, last, tmp); 
}

inline UnicodeChar GetUnicodeFromUtf8(std::string& str, size_t pos) {
	std::string::const_iterator it = Utf8PositionToIterator(str, pos);
	return GetNextUnicodeFromUtf8(it, str.end());
}


static void UNICODE_to_UTF8(unsigned char *utf8, UnicodeChar unicode)
{
    int j=0;

    if (unicode < 0x80)
    {
        utf8[j] = unicode & 0x7F;
    }
    else if (unicode < 0x800)
    {
        utf8[j] = 0xC0 | (unicode >> 6);
        utf8[++j] = 0x80 | (unicode & 0x3F);
    }
    else if (unicode < 0x10000)
    {
        utf8[j] = 0xE0 | (unicode >> 12);
        utf8[++j] = 0x80 | ((unicode >> 6) & 0x3F);
        utf8[++j] = 0x80 | (unicode & 0x3F);
    }
    else if (unicode < 0x200000)
    {
        utf8[j] = 0xF0 | (unicode >> 18);
        utf8[++j] = 0x80 | ((unicode >> 12) & 0x3F);
        utf8[++j] = 0x80 | ((unicode >> 6) & 0x3F);
        utf8[++j] = 0x80 | (unicode & 0x3F);
    }
    else if (unicode < 0x4000000)
    {
        utf8[j] = 0xF8 | (unicode >> 24);
        utf8[++j] = 0x80 | ((unicode >> 18) & 0x3F);
        utf8[++j] = 0x80 | ((unicode >> 12) & 0x3F);
        utf8[++j] = 0x80 | ((unicode >> 6) & 0x3F);
        utf8[++j] = 0x80 | (unicode & 0x3F);
    }
    else if (unicode < 0x80000000)
    {
        utf8[j] = 0xFC | (unicode >> 30);
        utf8[++j] = 0x80 | ((unicode >> 24) & 0x3F);
        utf8[++j] = 0x80 | ((unicode >> 18) & 0x3F);
        utf8[++j] = 0x80 | ((unicode >> 12) & 0x3F);
        utf8[++j] = 0x80 | ((unicode >> 6) & 0x3F);
        utf8[++j] = 0x80 | (unicode & 0x3F);
    }
    else
    	utf8[j] = 0;

    utf8[++j] = 0;
}

////////////////////
// Gets the UTF8 representation of the unicode character (can be more bytes)
std::string GetUtf8FromUnicode(UnicodeChar ch) {
	if(ch == 0) return std::string("\0", 1);
	unsigned char utf8[7];
	UNICODE_to_UTF8(utf8, ch);
	return (const char*)utf8;
}

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

inline std::wstring get_char_at(std::wstring s, int i) {
    return s.substr(i, 1);
}

inline size_t get_length(std::wstring s) {
    return s.length();
}
