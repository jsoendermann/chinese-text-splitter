#ifndef __STATE_H__
#define __STATE_H__
#include <unordered_map>

using namespace std;

class State {
    private:
        int id; // This is only used in to_string
        unordered_map<wstring, State*> dict;
        

    public:
        bool is_final;

        State();

        State *get_successor(wstring c);
        void add_successor(wstring c, State* successor);

        wstring to_string(int indent_level);
};
#endif
