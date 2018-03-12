//
// Created by user on 3/11/2018.
//

#include <string>
#include <vector>

using std::string;
using std::vector;

#ifndef NAIVEBAYES_TESTINGDATA_H
#define NAIVEBAYES_TESTINGDATA_H

class TestingData{

    public:
        static const string input;
        static vector<string> input_split(string input);
        static const vector<string> all_input;
        static const string trainingtest;

};


#endif //NAIVEBAYES_TESTINGDATA_H
