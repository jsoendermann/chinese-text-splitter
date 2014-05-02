#include <fstream>

#include "text-splitter.hpp"

using namespace std;

TextSplitter::TextSplitter(string cedict_file_path) {
    wifstream cedict_file;
    cedict_file.open(cedict_file_path);
    // Calling imbue on the file handle is necessary to make reading
    // utf-8 files work on OS X
    cedict_file.imbue(locale(locale(), "", LC_CTYPE));
    
    vector<wstring> trad_words, simp_words;

    if (cedict_file.is_open()) {
        wstring line, trad, simp;
        while(getline(cedict_file, line)) {
            if (line.at(0) != L'#') {
                size_t first_space_index = line.find(L' ');
                size_t second_space_index = line.find(L' ', first_space_index + 1);

                trad = line.substr(0, first_space_index);
                simp = line.substr(first_space_index + 1, second_space_index - first_space_index);

                trad_words.push_back(trad);
                simp_words.push_back(simp);
            }
        }
    } else {
        throw new exception();
    }
    cedict_file.close();
    
    trad_trie = new Trie();
    simp_trie = new Trie();

    trad_trie->add_words(trad_words);
    simp_trie->add_words(simp_words);

}

vector<wstring> TextSplitter::split_string(wstring s, int charset) {
    if (charset == TRAD) {
        return trad_trie->split_string(s);
    } else if (charset == SIMP) {
        return simp_trie->split_string(s);
    } else {
        throw exception();
    }
}
