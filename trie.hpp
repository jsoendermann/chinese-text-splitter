#ifndef __TRIE_H__
#define __TRIE_H__

#include "state.hpp"

using namespace std;

class Trie {
    private:
        // current_state is used in matching
        State *root, *current_state;

        // These two strings are used in matching.
        // On the path from the root to the current_state,
        // last_full_word contains the accumulated chars that led
        // to the last state on the path, that's a final state. This
        // is the last matched word. word_since_last_final_state contains
        // the rest, i.e. the chars of the states from the last final state
        // to current_state
        string last_full_word, word_since_last_final_state;

        // If s is in the Trie, this function returns its
        // state (starting from the root), otherwise it returns NULL
        State* get_state_for_word(string s);  

        // These three functions are used to match words in a string.
        // _feed_string is the internal version of feed_string, it is necessary
        // because of recursive calls. flush has to be called after feeding all
        // characters in the string to the Trie to add the last bit of the 
        // text, that is still being processed, to the output.
        string feed_char(string c);
        string _feed_string(string s);
        string flush();


    public:
        Trie();

        void add_word(string word);
        void add_words(vector<string> words);

        // This function calls _feed_string and flush
        string feed_string(string s);

        string to_string();
};

#endif
