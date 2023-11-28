#include "gtest.h"
#include "nfa.h"
TEST(test_nfa, string_to_NFA) {
    std::shared_ptr<NFA> nfa = NFA::string_to_NFA("testing");
    ASSERT_EQ(nfa->parse("testing"), 1);
    ASSERT_NE(nfa->parse("1234"), 1);
}

TEST(test_nfa, concat_NFA) {
    std::shared_ptr<NFA> nfa1 = NFA::string_to_NFA("testing");
    ASSERT_EQ(nfa1->parse("testing"), 1);
    ASSERT_NE(nfa1->parse("1234"), 1);

    std::shared_ptr<NFA> nfa2 = NFA::string_to_NFA("1234");
    ASSERT_EQ(nfa2->parse("1234"), 1);
    ASSERT_NE(nfa2->parse("testing"), 1);

    std::shared_ptr<NFA> nfa3 = NFA::concat_NFAs(nfa1, nfa2);
    ASSERT_EQ(nfa3->parse("testing1234"), 1);
    ASSERT_NE(nfa3->parse("testing"), 1);
    ASSERT_NE(nfa3->parse("1234"), 1);
    ASSERT_NE(nfa3->parse("testing123"), 1);
}

TEST(test_nfa, alternate_NFA) {
    std::shared_ptr<NFA> nfa1 = NFA::string_to_NFA("testing");
    ASSERT_EQ(nfa1->parse("testing"), 1);
    ASSERT_NE(nfa1->parse("1234"), 1);

    std::shared_ptr<NFA> nfa2 = NFA::string_to_NFA("1234");
    ASSERT_EQ(nfa2->parse("1234"), 1);
    ASSERT_NE(nfa2->parse("testing"), 1);

    std::shared_ptr<NFA> nfa3 = NFA::alternate_NFAs(nfa1, nfa2);
    ASSERT_NE(nfa3->parse("testing1234"), 1);
    ASSERT_EQ(nfa3->parse("testing"), 1);
    ASSERT_EQ(nfa3->parse("1234"), 1);
    ASSERT_NE(nfa3->parse("testing123"), 1);
}

TEST(test_nfa, concat_and_alternate_NFA) {
    std::shared_ptr<NFA> nfa1 = NFA::alternate_NFAs(NFA::string_to_NFA("testing"), NFA::string_to_NFA("test"));
    ASSERT_EQ(nfa1->parse("testing"), 1);
    ASSERT_EQ(nfa1->parse("test"), 1);

    std::shared_ptr<NFA> nfa2 = NFA::alternate_NFAs(NFA::string_to_NFA("123"), NFA::string_to_NFA("456"));
    ASSERT_EQ(nfa2->parse("123"), 1);
    ASSERT_EQ(nfa2->parse("456"), 1);

    std::shared_ptr<NFA> nfa3 = NFA::concat_NFAs(nfa1, nfa2);
    ASSERT_EQ(nfa3->parse("testing123"), 1);
    ASSERT_EQ(nfa3->parse("test123"), 1);
    ASSERT_EQ(nfa3->parse("testing456"), 1);
    ASSERT_EQ(nfa3->parse("test456"), 1);

    ASSERT_NE(nfa3->parse("testingtesting"), 1);
    ASSERT_NE(nfa3->parse("testtest"), 1);
    ASSERT_NE(nfa3->parse("123456"), 1);
    ASSERT_NE(nfa3->parse("123test"), 1);
}

TEST(test_nfa, alternate_and_concat_NFAs) {
    std::shared_ptr<NFA> nfa1 = NFA::concat_NFAs(NFA::string_to_NFA("testing"), NFA::string_to_NFA("123"));
    ASSERT_EQ(nfa1->parse("testing123"), 1);

    std::shared_ptr<NFA> nfa2 = NFA::concat_NFAs(NFA::string_to_NFA("test"), NFA::string_to_NFA("456"));
    ASSERT_EQ(nfa2->parse("test456"), 1);

    std::shared_ptr<NFA> nfa3 = NFA::alternate_NFAs(nfa1, nfa2);
    ASSERT_EQ(nfa3->parse("testing123"), 1);
    ASSERT_EQ(nfa3->parse("test456"), 1);

    ASSERT_NE(nfa3->parse("testing456"), 1);
    ASSERT_NE(nfa3->parse("test123"), 1);
}


int main(int argc, char **argv) { 
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}