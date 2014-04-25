#include <vector>
#include <unordered_map>
#include <string>
#include <vector>

#include "trie.hpp"
#include "unicode_functions.hpp"

using namespace std;


State* Trie::get_state_for_word(string s) {
    auto state = root;
    size_t s_length =  get_length(s);

    for (int i = 0; i < s_length; i++) {
        string c = get_char_at(s, i);

        state = state->get_successor(c);

        if (state == NULL) {
            return NULL;
        }
    }
    return state;
}

string Trie::feed_char(string c) {
    string output = "";

    auto next = current_state->get_successor(c);
    word_since_last_final_state += c;

    if (next == NULL) {
        // If there was no final state on the path from the root to next,
        // cut off the first char and try to match the remaining string
        if (last_full_word == "") {
            // TODO Maybe these two lines could be made faster by 
            // using iterators directly.
            output += get_char_at(word_since_last_final_state, 0) + " ";
            string remaining_string = Utf8SubStr(word_since_last_final_state, 1);
            output += _feed_string(remaining_string);
        // Otherwise output the word that was already matched and
        // only match the remaining substring
        } else {
            output += last_full_word  + " ";
            output += _feed_string(word_since_last_final_state);
        }
    } else {
        current_state = next;
        if (current_state->is_final) {
            last_full_word += word_since_last_final_state;
            word_since_last_final_state = "";
        }
    }
    return output;
}

string Trie::_feed_string(string s) {
    string output = "";

    // Reset the matching part of the Trie
    current_state = root;
    word_since_last_final_state = "";
    last_full_word = "";

    std::string::const_iterator it = s.begin();
    // This iterator is necessary because GetUtf8FromUnicode
    // requires a second iterator that points to the end of the string.
    std::string::const_iterator it2 = s.end();

    while (it != s.end()) { // GetNextUnicodeFromUtf8 increases the iterator
        auto c = GetUtf8FromUnicode(GetNextUnicodeFromUtf8(it, it2));
        output += feed_char(c);
    }



    return output;
}

string Trie::flush() {
    string output = "";

    output += last_full_word + " ";

    do {
        output += _feed_string(word_since_last_final_state);
        output += last_full_word + " ";
    } while (current_state != root);

    return output;
}

Trie::Trie() {
    root = new State();
    current_state = root;

    word_since_last_final_state = "";
    last_full_word = "";

    current_state = root;
}

void Trie::add_word(string word) {
    auto state = root;
    size_t word_length = get_length(word);

    // This could be made faster by using iterators like in _feed_string.
    // Because this function is only used to build up the Trie when the program
    // starts up, I prefer the more readable version for now.
    for (int i = 0; i < word_length; i++) {
        string c = get_char_at(word, i);

        State *next_state = state->get_successor(c);

        if (next_state == NULL) {
            next_state = new State();
            state->add_successor(c, next_state);
        } 

        state = next_state;

        if (i == word_length - 1) {
            state->is_final = true;
        }
    }
}

void Trie::add_words(vector<string> words) {
    for (string word : words) 
        add_word(word);
}


string Trie::feed_string(string s) {
    string output = "";

    output += _feed_string(s);
    output += flush();

    return output;
}

string Trie::to_string() {
    return root->to_string(0);
}
