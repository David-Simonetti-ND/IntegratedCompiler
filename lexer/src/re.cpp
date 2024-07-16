#include "re.h"
#include "automata.h"

// based on https://matt.might.net/articles/parsing-regex-with-recursive-descent/
/*      <regex> ::= <term> '|' <regex>
                    |  <term>

        <term> ::= { <factor> }

        <factor> ::= <base> { '*' }
                    
        <base> ::= <char>
                |  '\' <char>
                |  '(' <regex> ')'  */

regular_expression::regular_expression(re_type variety, re_ptr left, re_ptr right, std::string re_str) {
    this->m_variety = variety;
    this->m_left = left;
    this->m_right = right;
    this->re_str = re_str;
}

re_ptr regular_expression::parse_re(std::string re_expr) {
    int l = 0;
    int r = re_expr.length();
    re_ptr re = regular_expression::parse_re(re_expr, l, r);
    re->compress_re_strings();
    return re;
}

bool regular_expression::compare_re(re_ptr other) {
    if (this->m_variety != other->m_variety) return false;
    if ( (this->m_left == nullptr && other->m_left != nullptr) ||
             (this->m_left != nullptr && other->m_left == nullptr) ||
             (this->m_right == nullptr && other->m_right != nullptr) ||
             (this->m_right != nullptr && other->m_right == nullptr))
        return false;
    else if (this->m_variety == EPSILON || this->m_variety == STRING)
        return this->re_str == other->re_str;
    else if (this->m_variety == STAR) 
        return this->m_left->compare_re(other->m_left);
    else {
        bool are_left_equal = this->m_left == nullptr ? true : this->m_left->compare_re(other->m_left);
        bool are_right_equal = this->m_right == nullptr ? true : this->m_right->compare_re(other->m_right);
        return are_left_equal && are_right_equal;
    }
}

re_ptr regular_expression::parse_re(std::string re_expr, int &l, int &r) {
    re_ptr term = parse_term(re_expr, l, r);

    if ((l < r) && re_expr[l] == '|') {
        l++;
        if ((l < r) && re_expr[l] == ')') { 
            return std::make_shared<regular_expression>(ALTERNATION, term, std::make_shared<regular_expression>(EPSILON, nullptr, nullptr, ""), "");
        }
        else {
            re_ptr new_regex = parse_re(re_expr, l, r);
            return std::make_shared<regular_expression>(ALTERNATION, term, new_regex, "");
        }
    }
    else {
        return term;
    }
}

re_ptr regular_expression::parse_term(std::string re_expr, int &l, int &r) {
    re_ptr factor = nullptr, next_factor;

    while ((l < r) && re_expr[l] != '|' && re_expr[l] != ')') {
        next_factor = parse_factor(re_expr, l, r);
        factor = std::make_shared<regular_expression>(CONCATENATION, factor, next_factor, "");
    }
    
    return factor;
}
re_ptr regular_expression::parse_factor(std::string re_expr, int &l, int &r) {
    re_ptr base = parse_base(re_expr, l, r);
    
    while ((l < r) && re_expr[l] == '*') {
        while (re_expr[l] == '*')
            l++;
        base = std::make_shared<regular_expression>(STAR, base, nullptr, "");
    }

    return base;
}
re_ptr regular_expression::parse_base(std::string re_expr, int &l, int &r) {
    if (re_expr[l] == '(') {
        l++;
        re_ptr new_regex = parse_re(re_expr, l, r);
        l++;
        return new_regex;
    }
    else {
        return std::make_shared<regular_expression>(STRING, nullptr, nullptr, std::string(1, re_expr[l++]));
    }
}

std::string regular_expression::print_re() {
    std::string leftval, rightval;
    if (this->m_left != nullptr)  { 
        leftval  = this->m_left->print_re();
        if (this->m_variety < this->m_left->m_variety)
            leftval = "(" + leftval + ")";
    }
    if (this->m_right != nullptr) {
        rightval = this->m_right->print_re();
        if (this->m_variety < this->m_right->m_variety)
            rightval = "(" + rightval + ")";
    }
    switch (this->m_variety) {
        case EPSILON:
            return "";
        case ALTERNATION:
            return leftval + "|" + rightval;
        case CONCATENATION:
            return leftval + rightval;
        case STRING:
            return this->re_str;
        case STAR:
            return leftval + "*";
    }
}

void regular_expression::compress_re_strings() {
    //std::cout << this->print_re() << " before\n";
    if (this->m_left == nullptr && this->m_right != nullptr && this->m_right->m_variety == STRING && this->m_variety == CONCATENATION) {
        this->m_variety = STRING;
        this->re_str = this->m_right->re_str;
        this->m_left = nullptr;
        this->m_right = nullptr;
        return;
    }
    if (this->m_left == nullptr || this->m_right == nullptr) return;
    //std::cout << this->print_re() << " after " << this->m_left->print_re() << " "  << this->m_right->print_re() <<  " " << this->m_variety << "\n";
    //std::cout << (this->m_left->m_variety) << " " << (this->m_right->m_variety) << "\n";
    this->m_left->compress_re_strings();
    this->m_right->compress_re_strings();

    

    if (this->m_variety == CONCATENATION) {
        if (this->m_left->m_variety == STRING && this->m_right->m_variety == STRING) {
            this->m_variety = STRING;
            this->re_str = this->m_left->re_str + this->m_right->re_str;
            this->m_left = nullptr;
            this->m_right = nullptr;
        }
    }
    //std::cout << this->print_re() << " " << this->m_variety << " afterafter\n";
    return;
}