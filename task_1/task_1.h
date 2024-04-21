#include <iostream>
#include <vector>
#include <unordered_map>
#include <variant>


// (1 + 2) * 3 / 4 + 5 * (6 - 7)

// 1. Токенизация
// 2. Парсер (построение дерева разбора выражения)

// +, -, *, /, %

struct OpeningBracket {};

struct ClosingBracket {};

struct Number {
    int value;
};

struct UnknownToken {
    std::string value;
};

struct MinToken {};

struct MaxToken {};

struct AbsToken {};

struct SqrToken {};

struct Plus {};

struct Minus {};

struct Multiply {};

struct Modulo {};

struct Divide {};


using Token = std::variant<OpeningBracket, ClosingBracket, Number, UnknownToken, 
    MinToken, MaxToken, AbsToken, Plus, Minus, Multiply, Modulo, Divide, SqrToken>;

// 1234

const std::unordered_map<char, Token> kSymbol2Token {
    {'+', Plus{}},
    {'-', Minus{}},
    {'*', Multiply{}},
    {'/', Divide{}},
    {'%', Modulo{}},
    {'(', OpeningBracket{}},
    {')', ClosingBracket{}},
};

const std::unordered_map<std::string, Token> kFunction2Token{
    { "min", MinToken{} },
    { "max", MaxToken{} },
    { "abs", AbsToken{} },
    { "sqr", SqrToken{} }
};

int ToDigit(unsigned char symbol) {
    return symbol - '0';
}

Number ParseNumber(const std::string& input, size_t& pos) {
    int value = 0;
    auto symbol = static_cast<unsigned char>(input[pos]);
    while (std::isdigit(symbol)) {
        value = value * 10 + ToDigit(symbol);
        if (pos == input.size() - 1) {
            break;
        }
        symbol = static_cast<unsigned char>(input[++pos]);
    }
    return Number{ value };
}

Token ParseName(const std::string& input, size_t& pos) {
    std::string value;
    auto symbol = static_cast<unsigned char>(input[pos]);
    while (std::isalpha(symbol)) {
        value.push_back(symbol);
        if (pos == input.size() - 1) {
            break;
        }
        symbol = static_cast<unsigned char>(input[++pos]);
        if (auto it = kFunction2Token.find(value); it != kFunction2Token.end()) {
            return it->second;
        }
    }
    return UnknownToken{ value };
}

std::vector<Token> Tokenize(const std::string& input) {
    std::vector<Token> tokens;
    const size_t size = input.size();
    size_t pos = 0;
    while (pos < size) {
        const auto symbol = static_cast<unsigned char>(input[pos]);
        if (std::isspace(symbol)) {
            ++pos;
        }
        else if (std::isdigit(symbol)) {
            tokens.emplace_back(ParseNumber(input, pos));
        }
        else if (auto it = kSymbol2Token.find(symbol); it != kSymbol2Token.end()) {
            tokens.emplace_back(it->second);
        } else {
            tokens.emplace_back(ParseName(input, pos));
        }
    }
    return tokens;
}

