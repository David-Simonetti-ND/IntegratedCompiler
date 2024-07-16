#include <gtest/gtest.h>
#include "nfa.h"

token_t successful_parse = 1;

TEST(test_nfa, string_to_NFA) {
    std::shared_ptr<NFA> nfa = NFA::string_to_NFA("testing", successful_parse);
    ASSERT_EQ(nfa->parse("testing"), successful_parse);
    ASSERT_EQ(nfa->parse("1234"), ERROR_TOKEN);
}

TEST(test_nfa, concat_NFA) {
    std::shared_ptr<NFA> nfa1 = NFA::string_to_NFA("testing", successful_parse);
    ASSERT_EQ(nfa1->parse("testing"), successful_parse);
    ASSERT_EQ(nfa1->parse("1234"), ERROR_TOKEN);

    std::shared_ptr<NFA> nfa2 = NFA::string_to_NFA("1234", successful_parse);
    ASSERT_EQ(nfa2->parse("1234"), successful_parse);
    ASSERT_EQ(nfa2->parse("testing"), ERROR_TOKEN);

    std::shared_ptr<NFA> nfa3 = NFA::concat_NFAs(nfa1, nfa2, successful_parse);
    ASSERT_EQ(nfa3->parse("testing1234"), successful_parse);
    ASSERT_EQ(nfa3->parse("testing"), ERROR_TOKEN);
    ASSERT_EQ(nfa3->parse("1234"), ERROR_TOKEN);
    ASSERT_EQ(nfa3->parse("testing123"), ERROR_TOKEN);
}

TEST(test_nfa, alternate_NFA) {
    std::shared_ptr<NFA> nfa1 = NFA::string_to_NFA("testing", successful_parse);
    ASSERT_EQ(nfa1->parse("testing"), successful_parse);
    ASSERT_EQ(nfa1->parse("1234"), ERROR_TOKEN);

    std::shared_ptr<NFA> nfa2 = NFA::string_to_NFA("1234", successful_parse);
    ASSERT_EQ(nfa2->parse("1234"), successful_parse);
    ASSERT_EQ(nfa2->parse("testing"), ERROR_TOKEN);

    std::shared_ptr<NFA> nfa3 = NFA::alternate_NFAs(nfa1, nfa2, successful_parse);
    ASSERT_EQ(nfa3->parse("testing1234"), ERROR_TOKEN);
    ASSERT_EQ(nfa3->parse("testing"), successful_parse);
    ASSERT_EQ(nfa3->parse("1234"), successful_parse);
    ASSERT_EQ(nfa3->parse("testing123"), ERROR_TOKEN);
}

TEST(test_nfa, concat_and_alternate_NFA) {
    std::shared_ptr<NFA> nfa1 = NFA::alternate_NFAs(NFA::string_to_NFA("testing"), NFA::string_to_NFA("test"));

    std::shared_ptr<NFA> nfa2 = NFA::alternate_NFAs(NFA::string_to_NFA("123"), NFA::string_to_NFA("456"));

    std::shared_ptr<NFA> nfa3 = NFA::concat_NFAs(nfa1, nfa2, successful_parse);
    ASSERT_EQ(nfa3->parse("testing123"), successful_parse);
    ASSERT_EQ(nfa3->parse("test123"), successful_parse);
    ASSERT_EQ(nfa3->parse("testing456"), successful_parse);
    ASSERT_EQ(nfa3->parse("test456"), successful_parse);

    ASSERT_EQ(nfa3->parse("testingtesting"), ERROR_TOKEN);
    ASSERT_EQ(nfa3->parse("testtest"), ERROR_TOKEN);
    ASSERT_EQ(nfa3->parse("123456"), ERROR_TOKEN);
    ASSERT_EQ(nfa3->parse("123test"), ERROR_TOKEN);
}

TEST(test_nfa, alternate_and_concat_NFAs) {
    std::shared_ptr<NFA> nfa1 = NFA::concat_NFAs(NFA::string_to_NFA("testing"), NFA::string_to_NFA("123"));
    std::shared_ptr<NFA> nfa2 = NFA::concat_NFAs(NFA::string_to_NFA("test"), NFA::string_to_NFA("456"));
    std::shared_ptr<NFA> nfa3 = NFA::alternate_NFAs(nfa1, nfa2, successful_parse);
    ASSERT_EQ(nfa3->parse("testing123"), successful_parse);
    ASSERT_EQ(nfa3->parse("test456"), successful_parse);

    ASSERT_EQ(nfa3->parse("testing456"), ERROR_TOKEN);
    ASSERT_EQ(nfa3->parse("test123"), ERROR_TOKEN);
}

TEST(test_nfa, repeat_NFA) {
    std::shared_ptr<NFA> nfa1 = NFA::repeat_NFA(NFA::string_to_NFA("testing"), successful_parse);
    ASSERT_EQ(nfa1->parse(""), successful_parse);
    ASSERT_EQ(nfa1->parse("testing"), successful_parse);
    ASSERT_EQ(nfa1->parse("testingtesting"), successful_parse);
    ASSERT_EQ(nfa1->parse("testingtestingtesting"), successful_parse);
    ASSERT_EQ(nfa1->parse("testingtestingtestingtesting"), successful_parse);
}

TEST(test_nfa, complex_nfa) {
    std::shared_ptr<NFA> nfa1 = NFA::concat_NFAs(NFA::string_to_NFA("testing"), NFA::string_to_NFA("123"));
    std::shared_ptr<NFA> nfa2 = NFA::concat_NFAs(NFA::string_to_NFA("test"), NFA::string_to_NFA("456"));
    std::shared_ptr<NFA> nfa3 = NFA::repeat_NFA(NFA::alternate_NFAs(nfa1, nfa2), successful_parse);
    ASSERT_EQ(nfa3->parse("testing123"), successful_parse);
    ASSERT_EQ(nfa3->parse("test456"), successful_parse);
    ASSERT_EQ(nfa3->parse("testing123test456"), successful_parse);
    ASSERT_EQ(nfa3->parse("test456testing123"), successful_parse);
    ASSERT_EQ(nfa3->parse("testing123testing123testing123test456"), successful_parse);
    ASSERT_EQ(nfa3->parse(""), successful_parse);
}


int main(int argc, char **argv) { 
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}