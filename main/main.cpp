#include "compiler.h"

int main(int argc, char *argv[]) {
    std::unique_ptr<DFA> A = DFA::string_to_DFA("Notre");
    std::unique_ptr<DFA> B = DFA::string_to_DFA("Dame");
    std::cout << DFA::concat_DFAs(std::move(A), std::move(B))->to_string() << "\n";
    return 0;
}