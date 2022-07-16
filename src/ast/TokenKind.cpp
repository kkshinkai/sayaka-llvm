// Copyright (c) Kk Shinkai. All Rights Reserved. See LICENSE.txt in the project
// root for license information.

#include <sayaka/ast/TokenKind.hpp>

namespace sayaka {
    auto operator<<(llvm::raw_ostream &os, const TokenKind &kind) -> llvm::raw_ostream & {
        switch (kind) {
        case TokenKind::Ident:   return os << "ident";
        case TokenKind::Int:     return os << "int";
        case TokenKind::Float:   return os << "float";
        case TokenKind::String:  return os << "string";
        case TokenKind::LParen:  return os << "lparen";
        case TokenKind::RParen:  return os << "rparen";
        case TokenKind::Invalid: return os << "invalid";
        case TokenKind::Eof:     return os << "eof";
        }
    }
}
