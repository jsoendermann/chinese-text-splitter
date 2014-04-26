#include <vector>
#include <unordered_map>
#include <string>
#include <vector>

#include "trie.hpp"
#include "unicode_functions.hpp"
#include "util.hpp"

using namespace std;


State* Trie::get_state_for_word(wstring s) {
    auto state = root;
    size_t s_length =  get_length(s);

    for (int i = 0; i < s_length; i++) {
        state = state->get_successor(s[i]);

        if (state == NULL) {
            return NULL;
        }
    }
    return state;
}

wstring Trie::feed_char(wchar_t c) {
    wstring output = L"";

    auto next = current_state->get_successor(c);
    word_since_last_final_state += c;

    if (next == NULL) {
        // If there was no final state on the path from the root to next,
        // cut off the first char and try to match the remaining string
        if (last_full_word == L"") {
            output += add_word_to_output(get_char_at(word_since_last_final_state, 0));// + " ";
            wstring remaining_string = word_since_last_final_state.substr(1);
            output += _feed_string(remaining_string);
        // Otherwise output the word that was already matched and
        // only match the remaining substring
        } else {
            output += add_word_to_output(last_full_word);//  + " ";
            output += _feed_string(word_since_last_final_state);
        }
    } else {
        current_state = next;
        if (current_state->is_final) {
            last_full_word += word_since_last_final_state;
            word_since_last_final_state = L"";
        }
    }
    return output;
}

wstring Trie::_feed_string(wstring s) {
    wstring output = L"";

    // Reset the matching part of the Trie
    current_state = root;
    word_since_last_final_state = L"";
    last_full_word = L"";

    // TODO use iterator for this
    for (int i = 0; i < s.length(); i++) {
        output += feed_char(s[i]);
    }

    return output;
}

wstring Trie::flush() {
    wstring output = L"";

    //output += add_word_to_output(last_full_word);// + " ";

    while (current_state != root) {
        output += add_word_to_output(last_full_word);
        output += _feed_string(word_since_last_final_state);
    }

    return output;
}

Trie::Trie() {
    root = new State();
    current_state = root;

    word_since_last_final_state = L"";
    last_full_word = L"";

    current_state = root;
}

void Trie::add_word(wstring word) {
    auto state = root;
    size_t word_length = get_length(word);

    // This could be made faster by using iterators like in _feed_string.
    // Because this function is only used to build up the Trie when the program
    // starts up, I prefer the more readable version for now.
    for (int i = 0; i < word_length; i++) {
        wchar_t c = word[i];

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

void Trie::add_words(vector<wstring> words) {
    for (wstring word : words) 
        add_word(word);
}


wstring Trie::feed_string(wstring s) {
    wstring output = L"";

    output += _feed_string(s);
    output += flush();

    return output;
}

wstring Trie::to_string() {
    return root->to_string(0);
}
