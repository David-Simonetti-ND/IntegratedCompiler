#include "compiler.h"

int main(int argc, char *argv[]) {
    std::shared_ptr<NFA> A = NFA::string_to_NFA("Notre");
    std::shared_ptr<NFA> B = NFA::string_to_NFA("Dame");
    std::cout << NFA::concat_NFAs(A, B)->to_string() << "\n";
    return 0;
}