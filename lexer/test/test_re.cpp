#include "gtest.h"
#include "re.h"

TEST(test_nfa, concat_parse) {
    std::string reg_expr = "abcd";
    re_ptr parsed_expr = parse_re(reg_expr);
}

TEST(test_nfa, alternate_parse) {
    std::string reg_expr = "a|b";
    re_ptr parsed_expr = parse_re(reg_expr);
}


TEST(test_nfa, simple_parse) {
    std::string reg_expr = "(ab|c)|d*";
    re_ptr parsed_expr = parse_re(reg_expr);
}

int main(int argc, char **argv) { 
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}