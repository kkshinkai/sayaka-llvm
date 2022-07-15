// Copyright (c) Kk Shinkai. All Rights Reserved. See LICENSE.txt in the project
// root for license information.

#include <string>
#include <llvm/Support/raw_ostream.h>

#include <sayaka/ast/TokenKind.hpp>

namespace sakaya {
    struct Token {
        TokenKind kind;
        llvm::StringRef text;
    };

    llvm::raw_ostream &operator<<(llvm::raw_ostream &os, const Token &token) {
        os << "(token (kind " << token.kind << ") (text \"" << token.text << "\"))";
    }
}
