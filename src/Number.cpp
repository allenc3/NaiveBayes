//
// Created by user on 3/10/2018.
//

#include "Number.h"
#include <string>
#include <vector>
#include <iostream>
//#include <stdlib.h>

using std::cout;
using std::vector;
using std::string;

Number::Number(int number) {
    Number::number = number;
    Number::probability_matrix.resize(Number::kDimension, vector<double>(Number::kDimension));
}

void Number::TrainOneNum(string training_image) {
    Number::times_appeared++;
    for(int i = 0; i < Number::kDimension; i++) {
        for (int j = 0; j < Number::kDimension; ++j) {
            if(training_image[j + i*Number::kDimension] != Number::kWhite) {
                probability_matrix[i][j]++;
            }
        }
    }
}

void Number::TrainAllNum(vector<Number> &all_num, vector<string> training_images, vector<string> training_labels) {

    for (int i = 0; i < training_labels.size(); ++i) {
        int num = stoi(training_labels.at(i));
        for (int j = 0; j < all_num.size(); ++j) {
            if(num == all_num.at(j).number) {
                all_num.at(j).TrainOneNum(training_images.at(i));
                continue;
            }
        }
    }

    for (int k = 0; k < all_num.size(); ++k) {
        all_num.at(k).CalcProbability();
    }
}

void Number::CalcProbability() {
    for (int i = 0; i < probability_matrix.size(); ++i) {
        for (int j = 0; j < probability_matrix[0].size(); ++j) {
            probability_matrix[i][j] += kSmoothingValue;
            probability_matrix[i][j] /= (times_appeared + 2*kSmoothingValue);
        }
    }
}



vector<Number> Number::InitializeAllNum(){
    vector<Number> all_num;
    const int kDigitLimit = 10;
    for (int i = 0; i < kDigitLimit; i++) {
        all_num.push_back(Number(i));
    }
    return all_num;
}

void Number::ProcessInput(vector<string> input, vector<string> &training_images, vector<string> &training_labels){

    string image;
    int count = 1;
    for (int i = 0; i < input.size(); ++i) {
        string line = input.at(i);
        if(line.find_first_of("0123456789") != string::npos) {
            training_labels.push_back(line);
            continue;
        }
        image += line;
//        image += "\n";
        if(count == 28) {
            training_images.push_back(image);
            image.clear();
            count = 1;
        } else {
            count++;
        }
    }
}
