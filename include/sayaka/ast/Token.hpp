// Copyright (c) Kk Shinkai. All Rights Reserved. See LICENSE.txt in the project
// root for license information.

#ifndef SAYAKA_AST_TOKEN_HPP
#define SAYAKA_AST_TOKEN_HPP

#include <llvm/Support/raw_ostream.h>

#include <sayaka/ast/TokenKind.hpp>

namespace sayaka {
    struct Token {
        TokenKind kind;
        llvm::StringRef text;
    };

    inline auto operator<<(llvm::raw_ostream &os, const Token &token) -> llvm::raw_ostream & {
        return os << "(token (kind " << token.kind << ") "
                            "(text \"" << token.text << "\"))";
    }
}

#endif // SAYAKA_AST_TOKEN_HPP
