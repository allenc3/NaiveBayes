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

/**
 * Class for training a model
 */
class Training {
    public:

        /**
         * Initializes all the Number objects(0-9)
         * @return
         */
        static vector<Number> InitializeAllNum();
        /**
         * Takes in two training files
         */
        static bool ReadTrainingImages(vector<string> &all_input, string file_name);
        static bool ReadTrainingLabels(vector<string> &all_input, string file_name);

        /**
         * Processes input by putting it in a readable form.
         * @param input
         * @param training_images
         * @param training_labels
         */
        static void ProcessInput(vector<string> input, vector<string> &training_images,
                                 vector<string> &training_labels);

        /**
         * Trains all the numbers and fills in the probability matrix for each Number
         */
        static void TrainAllNum(vector<Number> &all_num, vector<string> training_images,
                                vector<string> training_labels);

        /**
         * Saves a model to a .txt file
         */
        static bool SaveModel(vector<string> all_input, string file_name);

};


#endif //NAIVEBAYES_TRAINING_H
