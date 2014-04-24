#include <string>
#include <unordered_map>

#include "state.hpp"

using namespace std;

State::State() {
    static int counter = 0;
    id = counter++;

    is_final = false;
}

State *State::get_successor(string c) {
    auto r = dict.find(c);

    if (r == dict.end()) {
        return NULL;
    } else {
        // r->second is the value (the key would be r->first)
        return r->second;
    }
}

void State::add_successor(string c, State *successor) {
    dict[c] = successor;
}

string State::to_string(int indent_level) {
    string indentation = "";
    for (int i = 0; i < indent_level; i++)
        indentation += " ";

    string output = "";

    output += indentation + std::to_string(id);

    if (is_final)
        output += " (f)";

    output += ":\n";


    for (auto it = dict.begin(); it != dict.end(); ++it) {
        output += indentation + " " + it->first + " -> \n";
        output += it->second->to_string(indent_level + 2);
    }

    return output;
}
