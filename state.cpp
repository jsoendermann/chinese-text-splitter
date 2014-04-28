#include <string>
#include <unordered_map>

#include "state.hpp"

using namespace std;

State::State() {
#ifdef DEBUG
    static int counter = 0;
    id = counter++;
#endif

    is_final = false;
}

State *State::get_successor(wchar_t c) {
    auto r = dict.find(c);

    if (r == dict.end()) {
        return NULL;
    } else {
        // r->second is the value (the key would be r->first)
        return r->second;
    }
}

void State::add_successor(wchar_t c, State *successor) {
    dict[c] = successor;
}

#ifdef DEBUG
wstring State::to_string(int indent_level) {
    wstring indentation = L"";
    for (int i = 0; i < indent_level; i++)
        indentation += L" ";

    wstring output = L"";

    output += indentation + std::to_wstring(id);

    if (is_final)
        output += L" (f)";

    output += L":\n";


    for (auto it = dict.begin(); it != dict.end(); ++it) {
        output += indentation + L" " + it->first + L" -> \n";
        output += it->second->to_string(indent_level + 2);
    }

    return output;
}
#endif
