#ifndef LEXER_H
#define LEXER_H
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <deque>
#include <map>

using state_t = int;
using transition_table = std::unordered_map<state_t, std::unordered_map<char, std::unordered_set<state_t>>>;

const char EPSILON = '\0';

class NFA {
    public:
        NFA(std::set<state_t> states, transition_table transitions, state_t start_state, std::unordered_set<state_t> accept_states);
        std::string to_string();
        static std::shared_ptr<NFA> string_to_NFA(std::string str);
        static std::shared_ptr<NFA> concat_NFAs(std::shared_ptr<NFA> A, std::shared_ptr<NFA> B);
        static std::shared_ptr<NFA> alternate_NFAs(std::shared_ptr<NFA> A, std::shared_ptr<NFA> B);
        std::set<state_t> &get_states();
        transition_table &get_table();
        state_t get_start_state();
        state_t get_max_state();
        std::unordered_set<state_t> &get_accept_states();
        bool parse(std::string input_str);
    private:
        std::set<state_t> m_states;
        transition_table m_transitions;
        state_t m_start_state;
        std::unordered_set<state_t> m_accept_states;

};

#endif