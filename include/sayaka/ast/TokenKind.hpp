// Copyright (c) Kk Shinkai. All Rights Reserved. See LICENSE.txt in the project
// root for license information.

namespace sakaya {
    enum class TokenKind {
        Ident,
        True,
        False,
        Int,
        String,
        LParen,
        RParen,
        Invalid,
    };

    llvm::raw_ostream &operator<<(llvm::raw_ostream &os, const TokenKind &kind) {
        switch (kind) {
            case TokenKind::Ident:   return os << "ident";
            case TokenKind::True:    return os << "true";
            case TokenKind::False:   return os << "false";
            case TokenKind::Int:     return os << "int";
            case TokenKind::String:  return os << "string";
            case TokenKind::LParen:  return os << "lparen";
            case TokenKind::RParen:  return os << "rparen";
            case TokenKind::Invalid: return os << "invalid";
        }
    }
}
