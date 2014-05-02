#ifndef __TEXT_SPLITTER_HPP__
#define __TEXT_SPLITTER_HPP__

#define SIMP 0
#define TRAD 1

#include <vector>

#include "trie.hpp"

using namespace std;

class TextSplitter {
    private:
        Trie *trad_trie;
        Trie *simp_trie;


    public:
        TextSplitter(string cedict_file_path);
        vector<wstring> split_string(wstring s, int charset);
};

#endif
