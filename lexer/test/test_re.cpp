#include <gtest/gtest.h>
#include "re.h"

TEST(test_nfa, concat_parse) {
    std::string reg_expr = "abcd";
    re_ptr truth = std::make_shared<regular_expression>(STRING, nullptr, nullptr, "abcd");

    re_ptr parsed_expr = regular_expression::parse_re(reg_expr);
    ASSERT_EQ(reg_expr, parsed_expr->print_re());
    ASSERT_EQ(true, parsed_expr->compare_re(truth));
}

TEST(test_nfa, alternate_parse) {
    std::string reg_expr = "a|b";
    re_ptr truth = std::make_shared<regular_expression>(ALTERNATION, 
                                                        std::make_shared<regular_expression>(STRING, nullptr, nullptr, "a"), 
                                                        std::make_shared<regular_expression>(STRING, nullptr, nullptr, "b"), 
                                                        "");

    re_ptr parsed_expr = regular_expression::parse_re(reg_expr);
    ASSERT_EQ(reg_expr, parsed_expr->print_re());
    ASSERT_EQ(true, parsed_expr->compare_re(truth));
}


TEST(test_nfa, simple_parse) {
    std::string reg_expr = "(ab|c)|(d*)";
    re_ptr parsed_expr = regular_expression::parse_re(reg_expr);
    ASSERT_EQ(reg_expr, parsed_expr->print_re());
} 

TEST(test_nfa, complex_re) {
    std::string reg_expr = "(ash(gd*)****f|h|b|c||||)|d*";
    re_ptr parsed_expr = regular_expression::parse_re(reg_expr);
    ASSERT_EQ("(ash(g(d*)*)f|h|b|c||||)|(d*)", parsed_expr->print_re());
} 


int main(int argc, char **argv) { 
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}