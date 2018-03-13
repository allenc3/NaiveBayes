//
// Created by user on 3/11/2018.
//

#include "Model.h"
#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include <iostream>

using std::string;
using std::vector;
using std::ifstream;
using std::regex;
using std::sregex_token_iterator;
using std::cout;

/**
 * Constructor that initializes size of probability matrix
 */
Model::Model() {
    probability_matrix.resize(Model::all_digits, vector<double>(Model::all_probability));
}

/**
 * Loads Model
 */
bool Model::LoadModel(string file_name) {

    ifstream training_images(file_name);
    // If faile fails to read, return false
    if (training_images.fail()) {
        return false;
    } else {
        // Form a string of a data
        string data;
        string line;
        while (std::getline(training_images, line)) {
            data += line;
        }
        // Split by white spaces since that's how I structured the data
        regex match ("\\s+");
        sregex_token_iterator iterate(data.begin(), data.end(), match, -1);
        sregex_token_iterator end;

        for (int i = 0; i < Model::all_digits; ++i) {
            for (int j = 0; j < Model::all_probability; ++j) {
                probability_matrix[i][j] = std::stod(iterate->str());
                iterate++;
            }
        }
        return true;
    }
}
