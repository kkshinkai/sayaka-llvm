// Copyright (c) Kk Shinkai. All Rights Reserved. See LICENSE.txt in the project
// root for license information.

#include <iostream>
#include <llvm/ADT/StringRef.h>
#include <llvm/Support/raw_ostream.h>

#include <sayaka/ast/Token.hpp> // unused
#include <sayaka/parse/Lex.hpp> // unused

int main() {
    llvm::StringRef greeting = "Hello, world!";
    llvm::outs() << greeting << "\n";
    return 0;
}
