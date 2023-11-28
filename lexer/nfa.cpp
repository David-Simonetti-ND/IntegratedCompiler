#include "nfa.h"
NFA::NFA(std::set<state_t> states, transition_table transitions, state_t start_state, std::unordered_set<state_t> accept_states) :
    m_states(states),
    m_transitions(transitions),
    m_start_state(start_state),
    m_accept_states(accept_states)
{}

std::set<state_t> &NFA::get_states() {
    return this->m_states;
}
transition_table &NFA::get_table() {
    return this->m_transitions;
}
state_t NFA::get_start_state() {
    return this->m_start_state;
}
std::unordered_set<state_t> &NFA::get_accept_states() {
    return this->m_accept_states;
}

state_t NFA::get_max_state() {
    return *std::max_element(this->m_states.begin(), this->m_states.end());
}

std::string NFA::to_string() {
    std::string NFA_string;
    NFA_string += "States: \n{";
    for (auto state : this->m_states) {
        NFA_string += std::to_string(state) + ", ";
    }
    NFA_string.pop_back(); 
    NFA_string.pop_back();
    NFA_string += "}\n";

    NFA_string += "Transistions:\n";
    char line_buff[1000];
    snprintf(line_buff, sizeof(line_buff), "%-12s %-12s %-12s\n", "From State", "Symbol", "To States");
    NFA_string += line_buff;
    std::map<state_t, std::unordered_map<char, std::unordered_set<state_t>>> ordered_transitions(this->m_transitions.begin(), this->m_transitions.end());
    for (auto [from_state, transitions] : ordered_transitions) {
        for (auto [symbol, to_set] : transitions) {
            snprintf(line_buff, sizeof(line_buff), "%-12d %-12s {", from_state, symbol == '\0' ? "EPSILON" : std::string(1, symbol).c_str());
            NFA_string += line_buff;
            for (auto to_state : to_set) {
                NFA_string += std::to_string(to_state) + ", ";
            }
            if (to_set.size() != 0){
                NFA_string.pop_back(); 
                NFA_string.pop_back();
            }
            NFA_string += "}\n";
        }
    }
    NFA_string += "Start State:\n" + std::to_string(this->m_start_state) + "\n";
    NFA_string += "Accept States: \n{";
    for (auto state : this->m_accept_states) {
        NFA_string += std::to_string(state) + ", ";
    }
    NFA_string.pop_back(); 
    NFA_string.pop_back();
    NFA_string += "}\n";
    return NFA_string;
}

std::shared_ptr<NFA> NFA::string_to_NFA(std::string str) {
    std::set<state_t> states = {};
    transition_table transitions = {};
    state_t start_state = 1;
    std::unordered_set<state_t> accept_states = {};
    for (int i = 0; i < str.length(); i++) {
        states.insert(i + 1);
        transitions[i + 1].insert({str[i], {i + 2}});
    }
    states.insert(str.length() + 1);
    accept_states.insert(str.length() + 1);
    return std::make_shared<NFA>(states, transitions, start_state, accept_states);
}

std::shared_ptr<NFA> NFA::concat_NFAs(std::shared_ptr<NFA> A, std::shared_ptr<NFA> B) {
    std::set<state_t> states = A->get_states();
    transition_table transitions = A->get_table();
    state_t start_state = A->get_start_state();
    std::unordered_set<state_t> accept_states = {};
    
    state_t max_state = A->get_max_state() - 1;
    std::set<state_t> B_states = B->get_states();
    transition_table B_transitions = B->get_table();
    for (auto state : B_states) {
        states.insert(state + max_state);
        for (auto [symbol, to_set] : B_transitions[state]) {
            for (auto to_state : to_set) {
                transitions[state + max_state][symbol].insert({to_state + max_state});
            }
        }
    }
    std::unordered_set<state_t> A_accept_states = A->get_accept_states();
    std::unordered_set<state_t> B_accept_states = B->get_accept_states();
    for (auto state : B_accept_states) {
        accept_states.insert(state + max_state);
    }
    for (auto state : A_accept_states) {
        transitions[state][EPSILON].insert({B->get_start_state() + max_state});
    }
    return std::make_unique<NFA>(states, transitions, start_state, accept_states);
}

std::shared_ptr<NFA> NFA::alternate_NFAs(std::shared_ptr<NFA> A, std::shared_ptr<NFA> B) {
    std::set<state_t> states = A->get_states();
    transition_table transitions = A->get_table();
    std::unordered_set<state_t> accept_states = A->get_accept_states();
    
    state_t max_state = A->get_max_state() + 1;
    state_t start_state = max_state;
    states.insert(start_state);
    std::set<state_t> B_states = B->get_states();
    transition_table B_transitions = B->get_table();
    for (auto state : B_states) {
        states.insert(state + max_state);
        for (auto [symbol, to_set] : B_transitions[state]) {
            for (auto to_state : to_set) {
                transitions[state + max_state][symbol].insert({to_state + max_state});
            }
        }
    }
    std::unordered_set<state_t> B_accept_states = B->get_accept_states();
    for (auto state : B_accept_states) {
        accept_states.insert(state + max_state);
    }
    transitions[start_state][EPSILON].insert({A->get_start_state()});
    transitions[start_state][EPSILON].insert({B->get_start_state() + max_state});
    return std::make_unique<NFA>(states, transitions, start_state, accept_states);
}


bool NFA::parse(std::string input_str) {
    std::vector<state_t> frontier = {this->m_start_state};

    for (int i = 0; i < input_str.length(); i++) {
        // epsilon closure
        std::unordered_set<state_t> visited(frontier.begin(), frontier.end());
        for (int j = 0; j < frontier.size(); j++) {
            state_t current_state = frontier[j];
            for (auto to_state : this->m_transitions[current_state][EPSILON]) {
                if (visited.count(to_state)) {
                    continue;
                }
                frontier.push_back(to_state);
                visited.insert(to_state);
            }
        }
 
        std::vector<state_t> new_frontier = {};
        char current_symbol = input_str[i];
        for (auto from_state : frontier) {
            for (auto to_state : this->m_transitions[from_state][current_symbol]) {
                new_frontier.push_back(to_state);
            }
        }
        frontier = new_frontier;
    }
    for (auto state : frontier) {
        if (this->m_accept_states.count(state) != 0) {
            return true;
        }
    }
    return false;
}