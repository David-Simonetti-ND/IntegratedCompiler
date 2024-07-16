#include "nfa.h"

NFA::NFA(std::set<state_t> states, nfa_transition_table transitions, state_t start_state, std::unordered_set<state_t> accept_states) :
    m_states(states),
    m_transitions(transitions),
    m_start_state(start_state),
    m_accept_states(accept_states)
{
    std::string error;
    if (m_states.find(m_start_state) == m_states.end()) {
        error = "Error: state " + std::to_string(m_start_state) + " is not in the set of states\n";
        throw std::logic_error(error);
    }
    for (state_t accept_state : m_accept_states) {
        if (m_states.find(accept_state) == m_states.end()) {
            error = "Error: accept state " + std::to_string(accept_state) + " is not in the set of states\n";
            throw std::logic_error(error);
        }
    }
}

std::set<state_t> &NFA::get_states() {
    return this->m_states;
}
nfa_transition_table &NFA::get_table() {
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
    std::map<state_t, std::unordered_map<token_t, std::unordered_map<state_t, token_t>>> ordered_transitions(this->m_transitions.begin(), this->m_transitions.end());
    for (auto [from_state, transitions] : ordered_transitions) {
        for (auto [symbol, to_set] : transitions) {
            snprintf(line_buff, sizeof(line_buff), "%-12d %-12s {", from_state, symbol == '\0' ? "EPSILON" : std::string(1, symbol).c_str());
            NFA_string += line_buff;
            for (auto [to_state, token] : to_set) {
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

std::shared_ptr<NFA> NFA::string_to_NFA(std::string str, token_t token) {
    std::set<state_t> states = {};
    nfa_transition_table transitions = {};
    state_t start_state = 1;
    std::unordered_set<state_t> accept_states = {};
    for (int i = 0; i < str.length(); i++) {
        states.insert(i + 1);
        transitions[i + 1][str[i]].insert({i + 2, i == str.length() - 1 ? token : NO_TOKEN});
    }
    states.insert(str.length() + 1);
    accept_states.insert(str.length() + 1);
    return std::make_shared<NFA>(states, transitions, start_state, accept_states);
}

std::shared_ptr<NFA> NFA::concat_NFAs(std::shared_ptr<NFA> A, std::shared_ptr<NFA> B, token_t token) {
    std::set<state_t> states = A->get_states();
    nfa_transition_table transitions = A->get_table();
    state_t start_state = A->get_start_state();
    
    state_t max_state = A->get_max_state() + 1;
    state_t accept_state = max_state;
    states.insert(accept_state);
    std::unordered_set<state_t> accept_states = {max_state};
    std::set<state_t> B_states = B->get_states();
    nfa_transition_table B_transitions = B->get_table();
    for (auto state : B_states) {
        states.insert(state + max_state);
        for (auto [symbol, to_set] : B_transitions[state]) {
            for (auto [to_state, token] : to_set) {
                transitions[state + max_state][symbol].insert({to_state + max_state, NO_TOKEN});
            }
        }
    }
    std::unordered_set<state_t> A_accept_states = A->get_accept_states();
    std::unordered_set<state_t> B_accept_states = B->get_accept_states();
    for (auto state : B_accept_states) {
        transitions[state + max_state][EPSILON_TRANS].insert({accept_state, token});
        states.insert({state + max_state});
    }
    for (auto state : A_accept_states) {
        transitions[state][EPSILON_TRANS].insert({B->get_start_state() + max_state, NO_TOKEN});
    }
    return std::make_unique<NFA>(states, transitions, start_state, accept_states);
}

std::shared_ptr<NFA> NFA::alternate_NFAs(std::shared_ptr<NFA> A, std::shared_ptr<NFA> B, token_t token) {
    std::set<state_t> states = A->get_states();
    nfa_transition_table transitions = A->get_table();
    
    state_t max_state = A->get_max_state() + 2;
    state_t start_state = max_state - 1;
    state_t accept_state = max_state;
    std::unordered_set<state_t> accept_states = {accept_state};
    states.insert(start_state);
    states.insert(accept_state);
    std::set<state_t> B_states = B->get_states();
    nfa_transition_table B_transitions = B->get_table();
    for (auto state : B_states) {
        states.insert(state + max_state);
        for (auto [symbol, to_set] : B_transitions[state]) {
            for (auto [to_state, token] : to_set) {
                transitions[state + max_state][symbol].insert({to_state + max_state, token});
            }
        }
    }
    std::unordered_set<state_t> A_accept_states = A->get_accept_states();
    std::unordered_set<state_t> B_accept_states = B->get_accept_states();
    for (auto state : A_accept_states) {
        transitions[state][EPSILON_TRANS].insert({accept_state, token});
    }
    for (auto state : B_accept_states) {
         transitions[state + max_state][EPSILON_TRANS].insert({accept_state, token});
    }
    transitions[start_state][EPSILON_TRANS].insert({A->get_start_state(), NO_TOKEN});
    transitions[start_state][EPSILON_TRANS].insert({B->get_start_state() + max_state, NO_TOKEN});
    return std::make_unique<NFA>(states, transitions, start_state, accept_states);
}

std::shared_ptr<NFA> NFA::repeat_NFA(std::shared_ptr<NFA> nfa, token_t token) {
     std::set<state_t> states = nfa->get_states();
    nfa_transition_table transitions = nfa->get_table();
    
    state_t start_state = nfa->get_max_state() + 1;
    state_t end_state = start_state + 1;
    std::unordered_set<state_t> accept_states = {start_state, end_state};
    states.insert(start_state);
    states.insert(end_state);

    transitions[start_state][EPSILON_TRANS].insert({nfa->get_start_state(), NO_TOKEN});
    transitions[start_state][EPSILON_TRANS].insert({start_state, token});
    transitions[end_state][EPSILON_TRANS].insert({start_state, NO_TOKEN});
    auto nfa_accept_states = nfa->get_accept_states();
    for (auto accept_state : nfa_accept_states) {
        transitions[accept_state][EPSILON_TRANS].insert({end_state, token});
    }

    return std::make_unique<NFA>(states, transitions, start_state, accept_states);
}


token_t NFA::parse(std::string input_str) {
    std::vector<std::pair<state_t, token_t>> frontier = {{this->m_start_state, NO_TOKEN}};
    auto epsilon_closure = [&frontier, this]() {
        std::unordered_set<state_t> visited;
        for (auto [state, token] : frontier) {
            visited.insert(state);
        }
        for (int j = 0; j < frontier.size(); j++) {
            state_t current_state = frontier[j].first;
            if (this->m_transitions[current_state].find(EPSILON_TRANS) == this->m_transitions[current_state].end()) {
                continue;
            }
            for (auto [to_state, token] : this->m_transitions[current_state][EPSILON_TRANS]) {
                if (visited.count(to_state)) {
                    if (frontier[j].second == NO_TOKEN && token != NO_TOKEN) {
                        frontier[j].second = token;
                    }
                    else {
                        continue;
                    }
                }
                frontier.push_back({to_state, token});
                visited.insert(to_state);
            }
        }
    };
    for (int i = 0; i < input_str.length(); i++) {
        epsilon_closure();
 
        std::vector<std::pair<state_t, token_t>> new_frontier = {};
        char current_symbol = input_str[i];
        for (auto [from_state, ignore_token] : frontier) {
            if (this->m_transitions[from_state].find(current_symbol) == this->m_transitions[from_state].end()) {
                continue;
            }
            for (auto [to_state, token] : this->m_transitions[from_state][current_symbol]) {
                new_frontier.push_back({to_state, token});
            }
        }
        frontier = new_frontier;
    }
    epsilon_closure();
    for (auto [state, token] : frontier) {
        if (this->m_accept_states.count(state) != 0 && token != NO_TOKEN) {
            return token;
        }
    }
    return ERROR_TOKEN;
}