//
// Created by user on 3/10/2018.
//

#include "Number.h"
#include <string>
#include <vector>
#include <iostream>

using std::cout;
using std::vector;
using std::string;

/**
 * Initializes numbers object with a number and empty probability matrix(28x28)
 * @param number
 */
Number::Number(int number) {
    Number::number = number;
    Number::probability_matrix.resize(Number::kDimension, vector<double>(Number::kDimension));
}

/**
 * Trains a number for a specific image. Adds one if tile is black/gray
 * @param training_image
 */
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

/**
 * Calculates the probability of each tile by adding in smoothing value and divide by times appeared.
 */
void Number::CalcProbability() {
    for (int i = 0; i < probability_matrix.size(); ++i) {
        for (int j = 0; j < probability_matrix[0].size(); ++j) {
            probability_matrix[i][j] += kSmoothingValue;
            probability_matrix[i][j] /= (times_appeared + 2*kSmoothingValue);
        }
    }
}

