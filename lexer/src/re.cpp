#include "re.h"

regular_expression::regular_expression(re_type variety, re_ptr left, re_ptr right) {
    this->m_variety = variety;
    this->m_left = left;
    this->m_right = right;
}

re_ptr parse_re(std::string re_expr) {
    int l = 0;
    int r = re_expr.length();
    return parse_re_s(re_expr, l, r);
}

re_ptr parse_re_s(std::string re_expr, int &l, int &r) {
    if (l >= r || l >= re_expr.length()) {
        return nullptr;
    }


    
    return nullptr;
}   

re_ptr parse_re_c(std::string re_expr, int &l, int &r) {
    if (l >= r || l >= re_expr.length()) {
        return nullptr;
    }

    while (re_expr[l] != '(' && re_expr[l] != '&' && re_expr[l] != '|')
    
    return nullptr;
}   

