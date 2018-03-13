//
// Created by user on 3/11/2018.
//

#ifndef NAIVEBAYES_MODEL_H
#define NAIVEBAYES_MODEL_H

#include "Number.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

/**
 * Defines a model for classification
 */
class Model {

    public:
        // 784 probabilities + class's own probability = 785
        const static int all_probability = 785;
        const static int all_digits = 10;
        // 10 digits X 785 probabilities
        vector<vector<double>> probability_matrix;

        /**
         * Instantiates model object
         */
        Model();

        /**
         * Loads model
         * @param file_name file to load from
         * @return true if loaded, false if failed.
         */
        bool LoadModel(string file_name);
};


#endif //NAIVEBAYES_MODEL_H
