#include "lexer.h"
DFA::DFA(std::set<state_t> states, transition_table transitions, state_t start_state, std::unordered_set<state_t> accept_states) :
    m_states(states),
    m_transitions(transitions),
    m_start_state(start_state),
    m_accept_states(accept_states)
{}

std::unique_ptr<DFA> DFA::string_to_DFA(std::string str) {
    std::set<state_t> states = {};
    transition_table transitions = {};
    state_t start_state = 0;
    std::unordered_set<state_t> accept_states = {};
    for (int i = 0; i < str.length(); i++) {
        states.insert(i);
        transitions[i].insert({str[i], i + 1});
    }
    states.insert(str.length());
    accept_states.insert(str.length());
    return std::make_unique<DFA>(states, transitions, start_state, accept_states);
}

std::string DFA::to_string() {
    std::string DFA_string;
    DFA_string += "States: \n{";
    for (auto state : this->m_states) {
        DFA_string += std::to_string(state) + ", ";
    }
    DFA_string.pop_back(); 
    DFA_string.pop_back();
    DFA_string += "}\n";

    DFA_string += "Transistions:\n";
    char line_buff[1000];
    snprintf(line_buff, sizeof(line_buff), "%-12s %-7s %-12s\n", "From State", "Symbol", "To State");
    DFA_string += line_buff;
    for (auto [from_state, transitions] : this->m_transitions) {
        for (auto [symbol, to_state] : transitions) {
            snprintf(line_buff, sizeof(line_buff), "%-12d %-7c %-12d\n", from_state, symbol, to_state);
            DFA_string += line_buff;
        }
    }
    DFA_string += "Start State:\n" + std::to_string(this->m_start_state) + "\n";
    DFA_string += "Accept States: \n{";
    for (auto state : this->m_accept_states) {
        DFA_string += std::to_string(state) + ", ";
    }
    DFA_string.pop_back(); 
    DFA_string.pop_back();
    DFA_string += "}\n";
    return DFA_string;
}