#include "nfa.h"
#include "dfa.h"
#include <chrono>
#include <cassert>

int main() {
    std::shared_ptr<NFA> final_nfa;
    std::shared_ptr<DFA> final_dfa;
    {
        std::shared_ptr<NFA> nfa1 = NFA::concat_NFAs(NFA::string_to_NFA("testing"), NFA::string_to_NFA("123"));
        std::shared_ptr<NFA> nfa2 = NFA::concat_NFAs(NFA::string_to_NFA("test"), NFA::string_to_NFA("456"));
        std::shared_ptr<NFA> nfa3 = NFA::repeat_NFA(NFA::alternate_NFAs(nfa1, nfa2), 1);

        std::shared_ptr<NFA> nfa4 = NFA::concat_NFAs(NFA::string_to_NFA("blah"), NFA::string_to_NFA("321"));
        std::shared_ptr<NFA> nfa5 = NFA::concat_NFAs(NFA::string_to_NFA("nah"), NFA::string_to_NFA("654"));
        std::shared_ptr<NFA> nfa6 = NFA::repeat_NFA(NFA::alternate_NFAs(nfa4, nfa5), 1);

        final_nfa = NFA::repeat_NFA(NFA::alternate_NFAs(nfa3, nfa6), 1);
        final_dfa = DFA::powerset_construction(final_nfa->get_states(), final_nfa->get_table(), final_nfa->get_start_state(), final_nfa->get_accept_states());
    }

    const int NUM_ITERATIONS = 10;
    const int NUM_REPETITIONS = 100;
    std::string base_str = "testing123test456blah321nah654";
    std::string to_parse = base_str;
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        auto t1 = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < NUM_REPETITIONS; j++) {
            assert(final_nfa->parse(to_parse) == 1);
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < NUM_REPETITIONS; j++) {
            assert(final_dfa->parse(to_parse) == 1);
        }
        auto t3 = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> delta1 = (t2 - t1) / NUM_REPETITIONS;
        std::chrono::duration<double, std::milli> delta2 = (t3 - t2) / NUM_REPETITIONS;

        std::cout << "Parsing string of length " << to_parse.length() << "\n";
        std::cout << "Using NFA to parse (avg over 10 parses): " << delta1.count() << "ms\n";
        std::cout << "Using DFA to parse (avg over 10 parses): " << delta2.count() << "ms\n";

        to_parse += base_str;
    }
    return 0;
}