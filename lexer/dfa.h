#ifndef DFA_H
#define DFA_H
#include "automata.h"

class DFA {
    public:
        DFA(std::set<state_t> states, dfa_transition_table transitions, state_t start_state, std::unordered_set<state_t> accept_states);
        std::string to_string();
        std::set<state_t> &get_states();
        dfa_transition_table &get_table();
        state_t get_start_state();
        state_t get_max_state();
        std::unordered_set<state_t> &get_accept_states();
        static std::shared_ptr<DFA> string_to_DFA(std::string str, token_t token = NO_TOKEN);
        token_t parse(std::string input_str);
        static std::shared_ptr<DFA> powerset_construction(std::set<state_t> states, 
                                                nfa_transition_table transitions, 
                                                state_t start_state, 
                                                std::unordered_set<state_t> accept_states);
    private:
        std::set<state_t> m_states;
        dfa_transition_table m_transitions;
        state_t m_start_state;
        std::unordered_set<state_t> m_accept_states;

};

#endif