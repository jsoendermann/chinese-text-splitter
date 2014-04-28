#include <vector>
#include <unordered_map>
#include <string>
#include <vector>

#include "trie.hpp"

using namespace std;


State* Trie::get_state_for_word(const wstring &s) {
    State *state = root;

    for (auto it = s.begin(); it != s.end(); it++) {
        state = state->get_child(*it);

        if (state == NULL) {
            return NULL;
        }
    }
    return state;
}

void Trie::feed_string(wstring s) {
    // Reset the matching part of the Trie
    current_state = root;
    string_since_last_match = L"";
    longest_match = L"";

    for (auto it = s.begin(); it != s.end(); it++) {
        feed_char(*it);
    }
}

void Trie::feed_char(wchar_t c) {
    string_since_last_match += c;

    auto child = current_state->get_child(c);
    if (child == NULL) {
        no_child_for_char(c);
    } else {
        transition_to_child_state(child);
    }
}

void Trie::no_child_for_char(wchar_t c) {
    if (longest_match == L"") {
        cut_off_first_char_and_feed_rest_to_trie();
    } else {
        split_text.push_back(longest_match);
        feed_string(string_since_last_match);
    }
}

void Trie::cut_off_first_char_and_feed_rest_to_trie() {
        split_text.push_back(string_since_last_match.substr(0, 1));
        feed_string(string_since_last_match.substr(1));
}

void Trie::transition_to_child_state(State *child) {
    current_state = child;
    if (current_state->is_final) {
        longest_match += string_since_last_match;
        string_since_last_match = L"";
    }
}

void Trie::flush() {
    while (current_state != root) {
        split_text.push_back(longest_match);
        feed_string(string_since_last_match);
    }
}


Trie::Trie() {
    current_state = root;
}

void Trie::add_word(wstring word) {
    auto state = root;
    size_t word_length = word.length();

    for (int i = 0; i < word_length; i++) {
        wchar_t c = word[i];

        State *next_state = state->get_child(c);

        if (next_state == NULL) {
            next_state = new State();
            state->add_child(c, next_state);
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


vector<wstring> Trie::split_string(wstring s) {
    split_text.clear();

    feed_string(s);
    flush();

    return split_text;
}
#ifdef DEBUG
wstring Trie::to_string() {
    return root->to_string(0);
}
#endif
