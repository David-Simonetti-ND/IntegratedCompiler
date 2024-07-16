#include "dfa.h"
DFA::DFA(std::set<state_t> states, dfa_transition_table transitions, state_t start_state, std::unordered_set<state_t> accept_states) :
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
    snprintf(line_buff, sizeof(line_buff), "%-12s %-12s %-12s\n", "From State", "Symbol", "To States");
    DFA_string += line_buff;
    std::map<state_t, std::unordered_map<token_t, std::pair<state_t, token_t>>> ordered_transitions(this->m_transitions.begin(), this->m_transitions.end());
    for (auto [from_state, transitions] : ordered_transitions) {
        for (auto [symbol, to_state] : transitions) {
            snprintf(line_buff, sizeof(line_buff), "%-12d %-12s %-12d\n", from_state, symbol == '\0' ? "EPSILON" : std::string(1, symbol).c_str(), to_state.first);
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
std::set<state_t> &DFA::get_states() {
    return this->m_states;
}
dfa_transition_table &DFA::get_table() {
    return this->m_transitions;
}
state_t DFA::get_start_state() {
    return this->m_start_state;
}
state_t DFA::get_max_state() {
    return *std::max_element(this->m_states.begin(), this->m_states.end());
}
std::unordered_set<state_t> &DFA::get_accept_states() {
    return this->m_accept_states;
}

std::shared_ptr<DFA> DFA::string_to_DFA(std::string str, token_t token) {
    std::set<state_t> states = {};
    dfa_transition_table transitions = {};
    state_t start_state = 1;
    std::unordered_set<state_t> accept_states = {};
    for (int i = 0; i < str.length(); i++) {
        states.insert(i + 1);
        transitions[i + 1].insert({str[i], {i + 2, (i == str.length() - 1) ? token : NO_TOKEN}});
    }
    states.insert(str.length() + 1);
    accept_states.insert(str.length() + 1);
    return std::make_shared<DFA>(states, transitions, start_state, accept_states);
}
token_t DFA::parse(std::string input_str) {
    state_t current_state = this->m_start_state;
    token_t current_token;
    for (int i = 0; i < input_str.length(); i++) {
        if (this->m_transitions[current_state].find(input_str[i]) == this->m_transitions[current_state].end()) {
            return ERROR_TOKEN;
        }
        current_token = this->m_transitions[current_state][input_str[i]].second;
        current_state = this->m_transitions[current_state][input_str[i]].first;
    }
    if (this->m_accept_states.find(current_state) == this->m_accept_states.end()) {
        return ERROR_TOKEN;
    }
    if (current_token == NO_TOKEN) {
        return ERROR_TOKEN;
    }
    return current_token;
}

std::shared_ptr<DFA> DFA::powerset_construction(std::set<state_t> states, 
                                                nfa_transition_table transitions, 
                                                state_t start_state, 
                                                std::unordered_set<state_t> accept_states) {
    auto epsilon_closure = [&transitions](std::vector<std::pair<state_t, token_t>> &states) {
        std::unordered_set<state_t> visited;
        for (auto [state, token] : states) {
            visited.insert(state);
        }
        for (int j = 0; j < states.size(); j++) {
            state_t current_state = states[j].first;
            for (auto [to_state, token] : transitions[current_state][EPSILON_TRANS]) {
                if (visited.count(to_state)) {
                    if (states[j].second == NO_TOKEN && token != NO_TOKEN) {
                        states[j].second = token;
                        continue;
                    }
                    else {
                        continue;
                    }
                }
                states.push_back({to_state, token});
                visited.insert(to_state);
            }
        }
    };

    auto cmp = [](std::pair<state_t, token_t> i, std::pair<state_t, token_t> j){ return i.first < j.first; };

    auto find_next_states = [&transitions, &cmp](const std::vector<std::pair<state_t, token_t>> &states, token_t symbol) {
        std::vector<std::pair<state_t, token_t>> new_states;
        std::unordered_set<state_t> visited;
        for (auto [from_state, token] : states) {
            for (auto [to_state, token] : transitions[from_state][symbol]) {
                if (visited.count(to_state)) {
                    continue;
                }
                visited.insert(to_state);
                new_states.push_back({to_state, token});
            }
        }
        std::sort(new_states.begin(), new_states.end(), cmp);
        return new_states;
    };

    auto find_outgoing_symbols = [&transitions](const std::vector<std::pair<state_t, token_t>> &states) {
        std::set<token_t> symbols;
        for (auto [from_state, token] : states) {
            for (auto [symbol, map] : transitions[from_state]) {
                symbols.insert({symbol});
            }
        }
        return symbols;
    };

    std::map<std::vector<std::pair<state_t, token_t>>, state_t> state_map;
    state_t current_new_state = 1;

    std::vector<std::pair<state_t, token_t>> current_states = {{start_state, NO_TOKEN}};
    std::deque<std::vector<std::pair<state_t, token_t>>> frontier = {current_states};

    std::set<state_t> dfa_states;
    dfa_transition_table dfa_transitions;
    state_t dfa_start_state = 1;
    std::unordered_set<state_t> dfa_accept_states;
    while (frontier.size() > 0) {
        current_states = frontier.front();
        frontier.pop_front();

        if (current_states.size() == 0) {
            continue;
        }

        epsilon_closure(current_states);
        std::sort(current_states.begin(), current_states.end(), cmp);

        if (state_map.find(current_states) != state_map.end()) {
            continue;
        }
        state_map.insert({current_states, current_new_state++});

        std::set<token_t> outgoing_symbols = find_outgoing_symbols(current_states);
        for (token_t symbol : outgoing_symbols) {
            if (symbol == EPSILON_TRANS) {
                continue;
            }
            frontier.push_back(find_next_states(current_states, symbol));
        }
    }
    
    for (auto &[nfa_states, new_state] : state_map) {
        std::set<token_t> outgoing_symbols = find_outgoing_symbols(nfa_states);
        for (token_t symbol : outgoing_symbols) {
            if (symbol == EPSILON_TRANS) {
                continue;
            }
            auto connected_state = find_next_states(nfa_states, symbol);
            epsilon_closure(connected_state);
            std::sort(connected_state.begin(), connected_state.end(), cmp);
            if (state_map.find(connected_state) == state_map.end()) {
                continue;
            }
            token_t transition_token = NO_TOKEN;
            for (auto [state, token] : connected_state) {
                if (token != NO_TOKEN) {
                    transition_token = token;
                }
            }
            dfa_transitions[new_state][symbol] = {state_map[connected_state], transition_token};
        }
        for (auto [state, token] : nfa_states) {
            if (accept_states.find(state) != accept_states.end()) {
                dfa_accept_states.insert(new_state);
            }
        }
        dfa_states.insert(new_state);
    }
    
    return std::make_shared<DFA>(dfa_states, dfa_transitions, dfa_start_state, dfa_accept_states);
}