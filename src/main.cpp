// Copyright (c) Kk Shinkai. All Rights Reserved. See LICENSE.txt in the project
// root for license information.

#include <iostream>

#include <llvm/ADT/StringRef.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/MemoryBuffer.h>

#include <sayaka/parse/Lex.hpp>

int main(int argc, char **argv) {
    llvm::StringRef greeting = "Hello, world!";
    llvm::outs() << greeting << "\n";

    auto buffer = std::move(llvm::MemoryBuffer::getFile("../examples/main.sayaka").get());
    auto lexer = sayaka::Lexer(buffer->getBuffer());

    auto token = lexer.next();
    while (token.kind != sayaka::TokenKind::Eof) {
        llvm::outs() << token << "\n";
        token = lexer.next();
    }

    return 0;
}
