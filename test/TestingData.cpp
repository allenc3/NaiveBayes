//
// Created by user on 3/11/2018.
//

#include "TestingData.h"
#include <string>
#include <regex>
#include <iostream>

using std::string;
using std::regex;
using std::sregex_token_iterator;
using std::cout;


const string TestingData::input =
        "                            \n"
        "                            \n"
        "                            \n"
        "                            \n"
        "                            \n"
        "                +++++##+    \n"
        "        +++++######+###+    \n"
        "       +##########+++++     \n"
        "        #######+##          \n"
        "        +++###  ++          \n"
        "           +#+              \n"
        "           +#+              \n"
        "            +#+             \n"
        "            +##++           \n"
        "             +###++         \n"
        "              ++##++        \n"
        "                +##+        \n"
        "                 ###+       \n"
        "              +++###        \n"
        "            ++#####+        \n"
        "          ++######+         \n"
        "        ++######+           \n"
        "       +######+             \n"
        "    ++######+               \n"
        "    +####++                 \n"
        "                            \n"
        "                            \n"
        "                            \n"
        "                            \n"
        "                            \n"
        "                            \n"
        "                            \n"
        "               ++#++        \n"
        "              +#####        \n"
        "             +######+       \n"
        "            +#####+##+      \n"
        "           +######++#+      \n"
        "          +###++##++#+      \n"
        "         +###+ +++  ##+     \n"
        "        ++###+      ##+     \n"
        "        +##+ +      ###     \n"
        "       +##+         ###     \n"
        "       ##+          ###     \n"
        "      +##+          ##+     \n"
        "      +##+         +#+      \n"
        "      +##         +##+      \n"
        "      +#+       ++#+        \n"
        "      +##      +##+         \n"
        "      +##+++++###++         \n"
        "      +#########+           \n"
        "      +#######+             \n"
        "       ++###++              \n"
        "                            \n"
        "                            \n"
        "                            \n"
        "                            \n"
        "                            \n"
        "                            \n"
        "                            \n"
        "                            \n"
        "                            \n"
        "                            \n"
        "                            \n"
        "                            \n"
        "                    +++##+  \n"
        "                  ++######  \n"
        "                +#####++    \n"
        "               +###+++      \n"
        "              +#+           \n"
        "            +#++            \n"
        "           +#+              \n"
        "           ##+              \n"
        "           ###+             \n"
        "        +   +##+            \n"
        "      +##+  +##+            \n"
        "      ##+   +#+             \n"
        "      +#######+             \n"
        "       ++###++              \n"
        "                            \n"
        "                            \n"
        "                            \n"
        "                            \n"
        "                            \n"
        "                            \n"
        "                            \n5\n0\n5";

const string TestingData::trainingtest =
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "                +++++##+\n"
        "        +++++######+###+\n"
        "       +##########+++++\n"
        "        #######+##\n"
        "        +++###  ++\n"
        "           +#+\n"
        "           +#+\n"
        "            +#+\n"
        "            +##++\n"
        "             +###++\n"
        "              ++##++\n"
        "                +##+\n"
        "                 ###+\n"
        "              +++###\n"
        "            ++#####+\n"
        "          ++######+\n"
        "        ++######+\n"
        "       +######+\n"
        "    ++######+\n"
        "    +####++\n"
        "\n"
        "\n"
        "\n5";

const vector<string> TestingData::all_input = TestingData::input_split(TestingData::input);

vector<string> TestingData::input_split(string input) {

    regex match ("\n");
    sregex_token_iterator iterate(input.begin(), input.end(), match, -1);
    sregex_token_iterator end;

    vector<string> all_input;
    while(iterate != end) {
        all_input.push_back(iterate->str());
        iterate++;
    }

    return all_input;
}
