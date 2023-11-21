#ifndef LEXER_H
#define LEXER_H
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

using state_t = int;
using transition_table = std::unordered_map<state_t, std::unordered_map<char, state_t>>;

class DFA {
    public:
        DFA(std::set<state_t> states, transition_table transitions, state_t start_state, std::unordered_set<state_t> accept_states);
        std::string to_string();
        static std::unique_ptr<DFA> string_to_DFA(std::string str);
    private:
        std::set<state_t> m_states;
        transition_table m_transitions;
        state_t m_start_state;
        std::unordered_set<state_t> m_accept_states;

};

#endif