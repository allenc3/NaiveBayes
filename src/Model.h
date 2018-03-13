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


class Model {

    public:
        const static int all_probability = 785;
        const static int all_num = 10;
        vector<vector<double>> probability_matrix;

        Model();
        bool LoadModel(string file_name);

};


#endif //NAIVEBAYES_MODEL_H
