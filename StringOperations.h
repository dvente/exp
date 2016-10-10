//
// Created by daniel on 10-10-16.
//

#ifndef EXP_STRINGOPERATIONS_H
#define EXP_STRINGOPERATIONS_H
#include <string>

void toLower(std::string &data);
bool stringIsDouble(const std::string input);
bool stringIsOperator(const std::string subExpr);
bool stringIsUnaryOperator(const std::string subExpr);
bool stringIsBinaryOperator(const std::string subExpr);
bool extractFirstWord(std::string & original, std::string &word);

#endif //EXP_STRINGOPERATIONS_H
