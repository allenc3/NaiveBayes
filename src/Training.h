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
        static bool ReadTrainingImages(vector<string> &all_input, string file_name);
        static bool ReadTrainingLabels(vector<string> &all_input, string file_name);
        static vector<Number> InitializeAllNum();
        static void ProcessInput(vector<string> input, vector<string> &training_images,
                                 vector<string> &training_labels);
        static void TrainAllNum(vector<Number> &all_num, vector<string> training_images,
                                vector<string> training_labels);
        static bool SaveModel(vector<string> all_input, string file_name);

};


#endif //NAIVEBAYES_TRAINING_H
