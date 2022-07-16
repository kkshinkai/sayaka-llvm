// Copyright (c) Kk Shinkai. All Rights Reserved. See LICENSE.txt in the project
// root for license information.

#ifndef SAYAKA_PARSE_LEX_HPP
#define SAYAKA_PARSE_LEX_HPP

#include <llvm/Support/MemoryBufferRef.h>

#include <sayaka/ast/Token.hpp>

namespace sayaka {
    namespace detail {
        class Cursor {
            llvm::StringRef source;
            size_t initialSize;
        public:
            explicit Cursor(llvm::StringRef source)
                : source(source), initialSize(source.size()) {}

            [[nodiscard]]
            auto restSize() const -> size_t {
                return source.size();
            }

            [[nodiscard]]
            auto isEof() const -> bool {
                return source.empty();
            }

            [[nodiscard]]
            auto peek(int n = 0) const -> char {
                return n < source.size() ? source[n] : '\0';
            }

            [[nodiscard]] auto peekSnd() const -> char { return peek(1); }
            [[nodiscard]] auto peekTrd() const -> char { return peek(2); }

            auto eat() -> char {
                if (!isEof()) {
                    char next = peek();
                    source = source.drop_front();
                    return next;
                } else {
                    return '\0';
                }
            }

            template<typename Fn>
            auto eatWhile(Fn predicate) {
                while (predicate(peek())) {
                    eat();
                }
            }

            auto resetConsumedSize() -> void {
                initialSize = source.size();
            }

            [[nodiscard]]
            auto getConsumedSize() const -> size_t {
                return initialSize - source.size();
            }
        };
    }

    class Lexer {
        llvm::StringRef source;
        detail::Cursor cursor;
    public:
        explicit Lexer(llvm::StringRef source)
            : source(source), cursor(detail::Cursor(source)) {}

        auto next() -> Token;

    private:
        auto lexNext() -> TokenKind;
        auto lexIdent() -> TokenKind;
        auto lexNumber() -> TokenKind;
        auto lexString() -> TokenKind;
    };

    namespace chars {
        inline bool isWhitespace(char c) {
            switch (c) {
            case ' ': case '\a': case '\b': case '\t': case '\r': case '\n':
                return true;
            default:
                return false;
            }
        }

        inline bool isSign(char c) {
            return c == '+' || c == '-';
        }

        inline bool isDigit(char c) {
            return c >= '0' && c <= '9';
        }

        inline bool isNumberHead(char c) {
            return isSign(c) || isDigit(c);
        }

        inline bool isIdentHead(char c) {
            switch (c) {
            case '!': case '$': case '&': case '*': case '/':
            case ':': case '<': case '=': case '>': case '?':
            case '^': case '_': case '~': case '+': case '-':
                return true;
            default:
                return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
            }
        }

        inline bool isIdentBody(char c) {
            return isIdentHead(c) || isDigit(c);
        }
    }
}

#endif // SAYAKA_PARSE_LEX_HPP
