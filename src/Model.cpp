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

Model::Model() {
    probability_matrix.resize(Model::all_num, vector<double>(Model::all_probability));
}

bool Model::LoadModel(string file_name) {

    ifstream training_images(file_name);

    if (training_images.fail()) {
        return false;
    } else {
        string data;
        string line;
        while (std::getline(training_images, line)) {
            data += line;
        }

        regex match ("\\s+");
        sregex_token_iterator iterate(data.begin(), data.end(), match, -1);
        sregex_token_iterator end;

        for (int i = 0; i < Model::all_num; ++i) {
            for (int j = 0; j < Model::all_probability; ++j) {
                probability_matrix[i][j] = std::stod(iterate->str());
                iterate++;
            }
        }

//        for (int i = 0; i < 10; ++i) {
////            cout << std::to_string(i) + "). " << " \n" << "\n";
//            for (int j = 0; j < 785; ++j) {
//                cout << probability_matrix[i][j];
//            }
//        }

        return true;
    }

}
