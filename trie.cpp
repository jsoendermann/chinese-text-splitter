#include <vector>
#include <unordered_map>
#include <string>
#include <vector>

#include "trie.hpp"
#include "util.hpp"

using namespace std;


State* Trie::get_state_for_word(const wstring &s) {
    State *state = root;

    for (auto it = s.begin(); it != s.end(); it++) {
        state = state->get_successor(*it);

        if (state == NULL) {
            return NULL;
        }
    }
    return state;
}

void Trie::feed_char(wchar_t c) {
    auto next = current_state->get_successor(c);
    string_since_last_match += c;

    if (next == NULL) {
        // If there was no final state on the path from the root to next,
        // cut off the first char and try to match the remaining string
        if (longest_match == L"") {
            split_text.push_back(string_since_last_match.substr(0, 1));

            feed_string(string_since_last_match.substr(1));
        // Otherwise output the word that was already matched and
        // only match the remaining substring
        } else {
            split_text.push_back(longest_match);

            feed_string(string_since_last_match);
        }
    } else {
        current_state = next;
        if (current_state->is_final) {
            longest_match += string_since_last_match;
            string_since_last_match = L"";
        }
    }
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


vector<wstring> Trie::split_string(wstring s) {
    split_text.clear();

    feed_string(s);
    flush();

    return split_text;
}

wstring Trie::to_string() {
    return root->to_string(0);
}
