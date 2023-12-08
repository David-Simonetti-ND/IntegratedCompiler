#include "gtest.h"
#include "dfa.h"
#include "nfa.h"

token_t successful_parse = 1;

TEST(test_dfa, string_to_dfa) {
    std::shared_ptr<DFA> dfa = DFA::string_to_DFA("testing", successful_parse);
    ASSERT_EQ(dfa->parse("testing"), successful_parse);
    ASSERT_EQ(dfa->parse("test"), ERROR_TOKEN);
    ASSERT_EQ(dfa->parse("testing123"), ERROR_TOKEN);
}

TEST(test_dfa, convert_nfa) {
    std::shared_ptr<NFA> nfa = NFA::string_to_NFA("testing", successful_parse);
    ASSERT_EQ(nfa->parse("testing"), successful_parse);
    ASSERT_EQ(nfa->parse("1234"), ERROR_TOKEN);

    std::shared_ptr<DFA> dfa = DFA::powerset_construction(nfa->get_states(), nfa->get_table(), nfa->get_start_state(), nfa->get_accept_states());
    ASSERT_EQ(dfa->parse("testing"), successful_parse);
    ASSERT_EQ(dfa->parse("1234"), ERROR_TOKEN);
}

TEST(test_dfa, convert_complex_nfa) {
    std::shared_ptr<NFA> nfa1 = NFA::concat_NFAs(NFA::string_to_NFA("testing"), NFA::string_to_NFA("123"));
    std::shared_ptr<NFA> nfa2 = NFA::concat_NFAs(NFA::string_to_NFA("test"), NFA::string_to_NFA("456"));
    std::shared_ptr<NFA> nfa3 = NFA::alternate_NFAs(nfa1, nfa2, successful_parse);


    std::shared_ptr<DFA> dfa = DFA::powerset_construction(nfa3->get_states(), nfa3->get_table(), nfa3->get_start_state(), nfa3->get_accept_states());
    ASSERT_EQ(dfa->parse("testing123"), successful_parse);
    ASSERT_EQ(dfa->parse("test456"), successful_parse);

    ASSERT_EQ(dfa->parse("testing456"), ERROR_TOKEN);
    ASSERT_EQ(dfa->parse("test123"), ERROR_TOKEN);
}

TEST(test_dfa, convert_super_complex_nfa) {
    std::shared_ptr<NFA> nfa1 = NFA::concat_NFAs(NFA::string_to_NFA("testing"), NFA::string_to_NFA("123"));
    std::shared_ptr<NFA> nfa2 = NFA::concat_NFAs(NFA::string_to_NFA("test"), NFA::string_to_NFA("456"));
    std::shared_ptr<NFA> nfa3 = NFA::repeat_NFA(NFA::alternate_NFAs(nfa1, nfa2), successful_parse);
    std::shared_ptr<DFA> dfa = DFA::powerset_construction(nfa3->get_states(), nfa3->get_table(), nfa3->get_start_state(), nfa3->get_accept_states());
    ASSERT_EQ(dfa->parse("testing123"), successful_parse);
    ASSERT_EQ(dfa->parse("test456"), successful_parse);
    ASSERT_EQ(dfa->parse("testing123test456"), successful_parse);
    ASSERT_EQ(dfa->parse("test456testing123"), successful_parse);
    ASSERT_EQ(dfa->parse("testing123testing123testing123test456"), successful_parse);

    std::cout << dfa->to_string() << "\n";
}

int main(int argc, char **argv) { 
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}