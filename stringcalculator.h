/**
* Copyright (c) 2017, MidnightGalaxy
* https://github.com/midnightgalaxy
*/


#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

#include <string>
#include <stdexcept>
#include <vector>

class StringCalculator
{
public:
    StringCalculator() {}
    static double calculator(const std::string & input);    // this method checks and validates the expression before calling calc

private:
    static double calc(const std::string & input);          // this method is recursive and does the calculations

};

#endif // STRINGCALCULATOR_H
