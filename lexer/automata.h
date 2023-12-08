#ifndef AUTOMATA_H
#define AUTOMATA_H
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <deque>
#include <map>
#include <sstream>

using state_t = int;
using token_t = int;

using dfa_transition_table = std::unordered_map<state_t, std::unordered_map<token_t, std::pair<state_t, token_t>>>;
using nfa_transition_table = std::unordered_map<state_t, std::unordered_map<token_t, std::unordered_map<state_t, token_t>>>;

const char EPSILON = '\0';
const token_t NO_TOKEN = 0;
const token_t ERROR_TOKEN = -1;

#endif