#ifndef __STATE_HPP__
#define __STATE_HPP__
#include <unordered_map>

using namespace std;

class State {
    private:
#ifdef DEBUG
        int id;
#endif
        unordered_map<wchar_t, State*> dict;
        

    public:
        bool is_final;

        State();

        State *get_child(wchar_t c);
        void add_child(wchar_t c, State* child);
#ifdef DEBUG
        wstring to_string(int indent_level);
#endif
};
#endif
