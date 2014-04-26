#ifndef __STATE_HPP__
#define __STATE_HPP__
#include <unordered_map>

using namespace std;

class State {
    private:
        int id; // This is only used in to_string
        unordered_map<wchar_t, State*> dict;
        

    public:
        bool is_final;

        State();

        State *get_successor(wchar_t c);
        void add_successor(wchar_t c, State* successor);

        wstring to_string(int indent_level);
};
#endif
