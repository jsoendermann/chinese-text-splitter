#include <vector>
#include <unordered_map>
#include <string>
#include <vector>

#include "trie.hpp"
#include "util.hpp"

using namespace std;


State* Trie::get_state_for_word(wstring s) {
    auto state = root;

    for (int i = 0; i < s.length(); i++) {
        state = state->get_successor(s[i]);

        if (state == NULL) {
            return NULL;
        }
    }
    return state;
}

vector<wstring> Trie::feed_char(wchar_t c) {
    vector<wstring> output;

    auto next = current_state->get_successor(c);
    word_since_last_final_state += c;

    if (next == NULL) {
        // If there was no final state on the path from the root to next,
        // cut off the first char and try to match the remaining string
        if (last_full_word == L"") {
            output.push_back(word_since_last_final_state.substr(0, 1));

            vector<wstring> remaining_words = _feed_string(word_since_last_final_state.substr(1));
            output.insert(output.end(), remaining_words.begin(), remaining_words.end());
        // Otherwise output the word that was already matched and
        // only match the remaining substring
        } else {
            output.push_back(last_full_word);

            vector<wstring> remaining_words = _feed_string(word_since_last_final_state);
            output.insert(output.end(), remaining_words.begin(), remaining_words.end());
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

vector<wstring> Trie::_feed_string(wstring s) {
    vector<wstring> output;

    // Reset the matching part of the Trie
    current_state = root;
    word_since_last_final_state = L"";
    last_full_word = L"";

    // TODO use iterator for this
    for (int i = 0; i < s.length(); i++) {
        vector<wstring> result = feed_char(s[i]);
        output.insert(output.end(), result.begin(), result.end());
    }

    return output;
}

vector<wstring> Trie::flush() {
    vector<wstring> output;

    while (current_state != root) {
        output.push_back(last_full_word);

        vector<wstring> result = _feed_string(word_since_last_final_state);
        output.insert(output.end(), result.begin(), result.end());
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


vector<wstring> Trie::feed_string(wstring s) {
    vector<wstring> output;

    output = _feed_string(s);

    vector<wstring> flush_result = flush();
    output.insert(output.end(), flush_result.begin(), flush_result.end());

    return output;
}

wstring Trie::to_string() {
    return root->to_string(0);
}
