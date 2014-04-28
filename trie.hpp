#ifndef __TRIE_HPP__
#define __TRIE_HPP__

#include "state.hpp"

using namespace std;

class Trie {
    private:
        State * const root = new State();
        State *current_state;

        // On the path from the root to the current_state,
        // longest_match contains the string that led
        // to the last final state. This is the longest matched word. 
        // string_since_last_match contains
        // the remaining string, i.e. the chars of the states from the last final state
        // to current_state
        wstring longest_match = L"", string_since_last_match = L"";

        vector<wstring> split_text;

        // If s is in the Trie, this function returns its
        // state (starting from the root), otherwise it returns NULL
        State* get_state_for_word(const wstring &s);  

        void feed_char(wchar_t c);
        // TODO s should be a constant reference
        void feed_string(wstring s);
        // flush returns to the root after the entire string was fed to the trie and
        // returns the words that are currently being processed by the trie.
        void flush();


    public:
        Trie();

        void add_word(wstring word);
        void add_words(vector<wstring> words);

        vector<wstring> split_string(wstring s);

        wstring to_string();
};

#endif
