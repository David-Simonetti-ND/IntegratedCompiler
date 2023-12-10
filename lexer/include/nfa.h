#ifndef NFA_H
#define NFA_H
#include "automata.h"

class NFA {
    public:
        NFA(std::set<state_t> states, nfa_transition_table transitions, state_t start_state, std::unordered_set<state_t> accept_states);
        std::string to_string();
        static std::shared_ptr<NFA> string_to_NFA(std::string str, token_t token = NO_TOKEN);
        static std::shared_ptr<NFA> concat_NFAs(std::shared_ptr<NFA> A, std::shared_ptr<NFA> B,  token_t token = NO_TOKEN);
        static std::shared_ptr<NFA> alternate_NFAs(std::shared_ptr<NFA> A, std::shared_ptr<NFA> B,  token_t token = NO_TOKEN);
        static std::shared_ptr<NFA> repeat_NFA(std::shared_ptr<NFA> nfa,  token_t token = NO_TOKEN);
        std::set<state_t> &get_states();
        nfa_transition_table &get_table();
        state_t get_start_state();
        state_t get_max_state();
        std::unordered_set<state_t> &get_accept_states();
        token_t parse(std::string input_str);
    private:
        std::set<state_t> m_states;
        nfa_transition_table m_transitions;
        state_t m_start_state;
        std::unordered_set<state_t> m_accept_states;

};

#endif