/**
* StringCalculator v1.0
* Copyright (c) 2017, MidnightGalaxy
* https://github.com/midnightgalaxy
*/


#include "stringcalculator.h"

// this method evaluates the expression and make sure it's okay before it deligates the work to the calc() method
double StringCalculator::calculator(const std::string & input)  // will throw exception if bad expression
{
    // check for no valid expression and throw runtime_error if so
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == '0' || input[i] == '1' || input[i] == '2' || input[i] == '3' || input[i] == '4' || input[i] == '5' || input[i] == '6' ||
                input[i] == '7' || input[i] == '8' || input[i] == '9' || input[i] == '+' || input[i] == '-' || input[i] == '*' ||
                input[i] == '/' || input[i] == '.' || input[i] == '(' || input[i] == ')')
            continue;
        else
            throw std::runtime_error("no valid expression! :( -> some unvalid character");
    }

    // check parathesis valid expression
    int paraCount1 = 0;
    int paraCount2 = 0;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == '(')
            paraCount1++;
        if (input[i] == ')')
            paraCount2++;
    }
    if (paraCount1 != paraCount2)
        throw std::runtime_error("no valid expression! :( -> parathesis");

    // check index 0 and make sure it's okay
    if (input[0] != '0' && input[0] != '1' && input[0] != '2' && input[0] != '3' && input[0] != '4' && input[0] != '5' && input[0] != '6' &&
            input[0] != '7' && input[0] != '8' && input[0] != '9' && input[0] != '-' && input[0] != '(' && input[0] != ')')
        throw std::runtime_error("no valid expression! :( -> index 0 faulty");

    // check last index and make sure it's okay
    if (input[input.size()-1] != '0' && input[input.size()-1] != '1' && input[input.size()-1] != '2' &&
            input[input.size()-1] != '3' && input[input.size()-1] != '4' && input[input.size()-1] != '5' &&input[input.size()-1] != '6' &&
            input[input.size()-1] != '7' && input[input.size()-1] != '8' && input[input.size()-1] != '9' &&
            input[input.size()-1] != '-' && input[input.size()-1] != '(' && input[input.size()-1] != ')')
        throw std::runtime_error("no valid expression! :( -> index last faulty");

    return calc(input);
}

double StringCalculator::calc(const std::string & input)
{
    int operators = 0;
    std::vector<int> vecPosAll;
    std::vector<int> vecPosAdd;
    std::vector<int> vecPosSub;
    std::vector<int> vecPosMult;
    std::vector<int> vecPosDiv;

    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == '+') {
            vecPosAll.push_back(i);
            vecPosAdd.push_back(i);
        } else if (input[i] == '-') {
            vecPosAll.push_back(i);
            vecPosSub.push_back(i);
        } else if (input[i] == '*') {
            vecPosAll.push_back(i);
            vecPosMult.push_back(i);
        } else if (input[i] == '/') {
            vecPosAll.push_back(i);
            vecPosDiv.push_back(i);
        }
    }

    operators = vecPosAdd.size() + vecPosSub.size() + vecPosMult.size() + vecPosDiv.size();

    // base case: if there's only one operation (left) then calculate the two operands and return
    if (operators == 1 || /*THIS IS FOR IF FIRST INDEX IS MINUS ->*/ (operators == 2 && vecPosSub.size() > 0 && vecPosSub.front() == 0)) {

        // IMPORTANT CODE IS FIRST INDEX IS MINUS
        bool firstMinus;
        if (operators == 2 && vecPosSub.size() > 0 && vecPosSub.front() == 0)
             firstMinus = vecPosSub.front() == 0;
        else
            firstMinus = false;

        if (vecPosAdd.size()) {
            double op1 = std::stod(input.substr(0, vecPosAdd.at(0)));
            double op2 = std::stod(input.substr(vecPosAdd.at(0)+1, input.size()));
            return op1+op2;
        }
        else if (vecPosMult.size()) {
            double op1 = std::stod(input.substr(0, vecPosMult.at(0)));
            double op2 = std::stod(input.substr(vecPosMult.at(0)+1, input.size()));
            return op1*op2;
        }
        else if (vecPosDiv.size()) {
            double op1 = std::stod(input.substr(0, vecPosDiv.at(0)));
            double op2 = std::stod(input.substr(vecPosDiv.at(0)+1, input.size()));
            return op1/op2;
        }
        else if (vecPosSub.size()) {    // IMPORTANT THAT THIS IS LAST IF FIRST INDEX IS MINUS -> OTHERWISE: BUG!
            if (firstMinus) {
                double op1 = std::stod(input.substr(0, vecPosSub.at(1)));
                double op2 = std::stod(input.substr(vecPosSub.at(1)+1, input.size()));
                return op1-op2;
            } else {
                double op1 = std::stod(input.substr(0, vecPosSub.at(0)));
                double op2 = std::stod(input.substr(vecPosSub.at(0)+1, input.size()));
                return op1-op2;
            }

        }


    }

    // important code because it's important to start from the back in the expression and work forward if first is minus
    bool startMult = true;
    if (vecPosMult.size() != 0 && vecPosDiv.size() != 0) {
        if (vecPosDiv.back() > vecPosMult.back())
            startMult = false;
    }


    else if (vecPosMult.size() != 0 && startMult) {
        std::string input2 = input;
        // construct new string with one less mult operation and return the new expression to calc...

        if (vecPosMult.back() == vecPosAll.back()) {     // if mult expr is last
            // OLD CODE: REMOVE LATER ON! Keep for so long if i can have usage for it...
            /*double newExpr = calc(input.substr((vecPosAll.size()-2)+1, input.size()));
            input2.erase((vecPosAll.size()-2)+1, input.size());
            input2.insert(input2.size(), std::to_string(newExpr));*/
            double newExpr = calc(input.substr(vecPosAll.at(vecPosAll.size()-2)+1, input.size()));
            input2.erase(vecPosAll.at(vecPosAll.size()-2)+1, input.size());
            input2.insert(input2.size(), std::to_string(newExpr));

            return calc(input2);
        } else if (vecPosMult.front() == vecPosAll.front()) {  // if the mult expr is first!
            // OLD CODE: REMOVE LATER ON! Keep for so long if i can have usage for it...
            /*double op1 = std::stod(input.substr(0, vecPosMult.front()));
            double op2 = std::stod(input.substr(vecPosMult.front()+1, vecPosAll));
            double newExpr = op1*op2;*/
            double newExpr = calc(input.substr(0, vecPosAll.at(1)));   // will be more DRY than above

            // MOD input2 with newExpr
            input2.erase(0, vecPosAll.at(1)-1);
            input2.insert(0, std::to_string(newExpr));

            return calc(input2);
        } else {
            int firstMultOpIndex = vecPosMult.front();
            int indexInVecPosAll;
            for (int i = 0; i < vecPosAll.size(); i++)
            {
                if (vecPosAll.at(i) == firstMultOpIndex) {
                    indexInVecPosAll = i;
                    break;
                }
            }
            int firstIndexBorder = vecPosAll.at(indexInVecPosAll - 1);
            int secondIndexBorder = vecPosAll.at(indexInVecPosAll + 1);

            double newExpr = calc(input.substr(firstIndexBorder+1, secondIndexBorder));
            input2.erase(firstIndexBorder+1, secondIndexBorder);
            input2.insert(firstIndexBorder+1, std::to_string(newExpr));

            return calc(input2);
        }



    } else if (vecPosDiv.size() != 0) {
        std::string input2 = input;

        if (vecPosDiv.back() == vecPosAll.back()) {     // if div expr is last
            double newExpr = calc(input.substr(vecPosAll.at(vecPosAll.size()-2)+1, input.size()));
            input2.erase(vecPosAll.at(vecPosAll.size()-2)+1, input.size());
            input2.insert(input2.size(), std::to_string(newExpr));
            return calc(input2);
        } else if (vecPosDiv.front() == vecPosAll.front()) {  // if the div expr is first!
            double newExpr = calc(input.substr(0, vecPosAll.at(1)));
            input2.erase(0, vecPosAll.at(1)-1);
            input2.insert(0, std::to_string(newExpr));
            return calc(input2);
        } else {
            int firstDivOpIndex = vecPosDiv.front();
            int indexInVecPosAll;
            for (int i = 0; i < vecPosAll.size(); i++)
            {
                if (vecPosAll.at(i) == firstDivOpIndex) {
                    indexInVecPosAll = i;
                    break;
                }
            }
            int firstIndexBorder = vecPosAll.at(indexInVecPosAll - 1);
            int secondIndexBorder = vecPosAll.at(indexInVecPosAll + 1);

            double newExpr = calc(input.substr(firstIndexBorder+1, secondIndexBorder));
            input2.erase(firstIndexBorder+1, secondIndexBorder);
            input2.insert(firstIndexBorder+1, std::to_string(newExpr));

            return calc(input2);
        }


    } else {
        std::string input2 = input;
        // when there are no mult/div operations left just do the last plus/minus operations. For every op. make a new string
        // and return it to the calc function, until base base is reached! :)
        double newExpr = calc(input.substr(0, vecPosAll.at(1)));
        input2.erase(0, vecPosAll.at(1)-1);
        input2.insert(0, std::to_string(newExpr));
        return calc(input2);
    }


}
