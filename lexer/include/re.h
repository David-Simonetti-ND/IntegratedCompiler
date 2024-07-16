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
    CHARACTER,
    ALTERNATION,
    CONCATENATION,
    STRING,
    STAR
};

struct regular_expression;
using re_ptr = std::shared_ptr<regular_expression>;

struct regular_expression {
    regular_expression(re_type variety, re_ptr left, re_ptr right);
    re_type m_variety;
    re_ptr m_left;
    re_ptr m_right;
};

re_ptr parse_re(std::string re_expr);
re_ptr parse_re(std::string re_expr, int &l, int &r);

#endif