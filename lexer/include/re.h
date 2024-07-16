#ifndef RE_H
#define RE_H
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

enum re_type {
    EPSILON,
    STRING,
    CONCATENATION,
    ALTERNATION,
    STAR
};

struct regular_expression;
using re_ptr = std::shared_ptr<regular_expression>;

struct regular_expression {
    regular_expression(re_type variety, re_ptr left, re_ptr right, std::string re_str);
    re_type m_variety;
    re_ptr m_left;
    re_ptr m_right;
    std::string re_str;

    static re_ptr parse_re(std::string re_expr);
    static re_ptr parse_re(std::string re_expr, int &l, int &r);
    static re_ptr parse_term(std::string re_expr, int &l, int &r);
    static re_ptr parse_factor(std::string re_expr, int &l, int &r);
    static re_ptr parse_base(std::string re_expr, int &l, int &r);
    
    std::string print_re();
    void compress_re_strings();
    bool compare_re(re_ptr other);
};



#endif