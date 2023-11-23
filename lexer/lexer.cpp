#include "lexer.h"
DFA::DFA(std::set<state_t> states, transition_table transitions, state_t start_state, std::unordered_set<state_t> accept_states) :
    m_states(states),
    m_transitions(transitions),
    m_start_state(start_state),
    m_accept_states(accept_states)
{}

std::set<state_t> &DFA::get_states() {
    return this->m_states;
}
transition_table &DFA::get_table() {
    return this->m_transitions;
}
state_t DFA::get_start_state() {
    return this->m_start_state;
}
std::unordered_set<state_t> &DFA::get_accept_states() {
    return this->m_accept_states;
}

state_t DFA::get_max_state() {
    return *std::max_element(this->m_states.begin(), this->m_states.end());
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

std::unique_ptr<DFA> DFA::string_to_DFA(std::string str) {
    std::set<state_t> states = {};
    transition_table transitions = {};
    state_t start_state = 1;
    std::unordered_set<state_t> accept_states = {};
    for (int i = 0; i < str.length(); i++) {
        states.insert(i + 1);
        transitions[i + 1].insert({str[i], i + 2});
    }
    states.insert(str.length() + 1);
    accept_states.insert(str.length() + 1);
    return std::make_unique<DFA>(states, transitions, start_state, accept_states);
}

std::unique_ptr<DFA> DFA::concat_DFAs(std::unique_ptr<DFA> A, std::unique_ptr<DFA> B) {
    std::set<state_t> states = A->get_states();
    transition_table transitions = A->get_table();
    state_t start_state = A->get_start_state();
    std::unordered_set<state_t> accept_states = {};
    
    state_t max_state = A->get_max_state() - 1;
    std::set<state_t> B_states = B->get_states();
    transition_table B_transitions = B->get_table();
    for (auto state : B_states) {
        states.insert(state + max_state);
        for (auto [symbol, to_state] : B_transitions[state]) {
            transitions[state + max_state].insert({symbol, to_state + max_state});
        }
    }
    std::unordered_set<state_t> B_accept_states = B->get_accept_states();
    for (auto state : B_accept_states) {
        accept_states.insert(state + max_state);
    }
    return std::make_unique<DFA>(states, transitions, start_state, accept_states);
}



bool DFA::parse(std::string input_str) {
    state_t current_state = this->m_start_state;
    for (int i = 0; i < input_str.length(); i++) {
        char current_symbol = input_str[i];
        auto &outgoing_transitions = this->m_transitions[current_state];
        state_t next_state = outgoing_transitions[current_symbol];
        if (next_state == 0) {
            return false;
        }
        current_state = next_state;
    }
    return this->m_accept_states.find(current_state) != this->m_accept_states.end();
}