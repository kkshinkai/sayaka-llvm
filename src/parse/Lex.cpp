// Copyright (c) Kk Shinkai. All Rights Reserved. See LICENSE.txt in the project
// root for license information.

#include <cassert>

#include <sayaka/ast/Token.hpp>
#include <sayaka/parse/Lex.hpp>

namespace sayaka {
    auto Lexer::next() -> Token {
        // Skip whitespaces.
        while (chars::isWhitespace(cursor.peek())) {
            cursor.eat();
        }

        // Skip comments.
        if (cursor.peek() == ';') {
            while (cursor.peek() != '\n') {
                cursor.eat();
            }
        }

        cursor.resetConsumedSize();

        auto kind = lexNext();
        if (kind == TokenKind::Invalid) {
            return next();
        }

        size_t end = source.size() - cursor.restSize();
        size_t start = end - cursor.getConsumedSize();
        auto text = source.substr(start, end - start);

        return { kind, text };
    }

    auto Lexer::lexNext() -> TokenKind {
        if (cursor.isEof()) {
            return TokenKind::Eof;
        }

        if (chars::isIdentHead(cursor.peek())) {
            if (chars::isSign(cursor.peek()) && chars::isDigit(cursor.peekSnd())) {
                return lexNumber();
            } else {
                return lexIdent();
            }
        } else if (chars::isDigit(cursor.peek())) {
            return lexNumber();
        } else if (cursor.peek() == '"') {
            return lexString();
        } else if (cursor.peek() == '(') {
            cursor.eat();
            return TokenKind::LParen;
        } else if (cursor.peek() == ')') {
            cursor.eat();
            return TokenKind::RParen;
        } else {
            cursor.eat();
            return TokenKind::Invalid;
        }
    }

    auto Lexer::lexIdent() -> TokenKind {
        assert(chars::isIdentHead(cursor.eat()));
        cursor.eatWhile(chars::isIdentBody);
        return TokenKind::Ident;
    }

    auto Lexer::lexNumber() -> TokenKind {
        assert(chars::isNumberHead(cursor.peek()));

        // Eat number sign '+' or '-'.
        if (chars::isSign(cursor.peek())) {
            cursor.eat();
        }

        cursor.eatWhile(chars::isDigit);

        // If this is a float-pointing number.
        if (cursor.peek() == '.' && chars::isDigit(cursor.peekSnd())) {
            cursor.eat(); // Eat '.'.

            cursor.eatWhile(chars::isDigit);
            return TokenKind::Float;
        } else {
            return TokenKind::Int;
        }
    }

    auto Lexer::lexString() -> TokenKind {
        assert(cursor.eat() == '"');

        while (!cursor.isEof() && cursor.peek() != '"') {
            if (cursor.peek() == '\\') {
                cursor.eat();
                cursor.eat();
            }
            cursor.eat();
        }

        if (cursor.eat() != '"') {
            llvm::errs() << "string literal without termination\n";
            return TokenKind::Invalid;
        }

        return TokenKind::String;
    }
}
