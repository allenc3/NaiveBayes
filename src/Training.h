//
// Created by user on 3/11/2018.
//

#ifndef NAIVEBAYES_TRAINING_H
#define NAIVEBAYES_TRAINING_H

#include "Number.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class Training {
    public:
        static bool ReadTrainingFiles(vector<string> &all_input);
        static vector<Number> InitializeAllNum();
        static void ProcessInput(vector<string> input, vector<string> &training_images,
                                 vector<string> &training_labels);
        static void TrainAllNum(vector<Number> &all_num, vector<string> training_images,
                                vector<string> training_labels);
        static bool SaveModel(vector<string> all_input);

};


#endif //NAIVEBAYES_TRAINING_H
