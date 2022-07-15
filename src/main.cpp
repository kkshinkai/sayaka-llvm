#include <iostream>
#include <llvm/ADT/StringRef.h>

int main() {
    llvm::StringRef greeting = "Hello, world!";
    std::cout << greeting.str() << std::endl;
    return 0;
}
