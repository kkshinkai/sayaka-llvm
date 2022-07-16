// Copyright (c) Kk Shinkai. All Rights Reserved. See LICENSE.txt in the project
// root for license information.

#ifndef SAYAKA_AST_TOKEN_KIND_HPP
#define SAYAKA_AST_TOKEN_KIND_HPP

#include <llvm/Support/raw_ostream.h>

namespace sayaka {
    enum class TokenKind {
        Ident,
        Int,
        Float,
        String,
        LParen,
        RParen,
        Invalid,
        Eof,
    };

    auto operator<<(llvm::raw_ostream &os, const TokenKind &kind) -> llvm::raw_ostream &;
}

#endif // SAYAKA_AST_TOKEN_KIND_HPP
