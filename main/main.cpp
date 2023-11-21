#include "compiler.h"

int main(int argc, char *argv[]) {
    std::unique_ptr<DFA> A = DFA::string_to_DFA("abcd");
    std::cout << A->to_string() << "\n";
    return 0;
}