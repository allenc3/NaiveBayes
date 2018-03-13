//
// Created by user on 3/12/2018.
//

#include "Classifying.h"
#include <fstream>
#include <math.h>
#include <iostream>

using std::ifstream;
using std::cout;

bool Classifying::ReadTestingImages(vector<string> &all_images, string file_name) {

    ifstream testing_images(file_name);

    if (testing_images.fail()) {
        return false;
    } else {
        string line;
        string image;
        int count = 0;
        while (std::getline(testing_images, line)) {
            if(count < 28) {
                image += line;
                count++;
            }
            if(count == 28) {
                all_images.push_back(image);
                image.clear();
                count = 0;
            }

        }
        return true;
    }
}

bool Classifying::ReadTestingLabels(vector<string> &all_labels, string file_name) {
    ifstream testing_labels(file_name);

    if (testing_labels.fail()) {
        return false;
    } else {
        string line;
        while (std::getline(testing_labels, line)) {
            all_labels.push_back(line);
        }
        return true;
    }
}

int Classifying::ClassifyingImage(Model model, string image) {
    vector<double> posteriori_classification(kDigits, 0);

    for (int j = 0; j < model.probability_matrix.size(); ++j) {
        posteriori_classification[j] += log2(model.probability_matrix[j][0]);
    }

    for (int pixel = 0; pixel < image.length(); ++pixel) {
        for (int digit = 0; digit < kDigits; ++digit) {
            // pixel + 1 since 0 is used for the
            if(image.at(pixel) != kWhite) {
                posteriori_classification[digit] +=  log2(model.probability_matrix[digit][pixel + 1]);
            } else {
                posteriori_classification[digit] +=  log2(1 - model.probability_matrix[digit][pixel + 1]);
            }
        }
    }

    int max = 0;
    double max_probability = posteriori_classification.at(0);
    for (int i = 1; i < posteriori_classification.size(); ++i) {
        if(posteriori_classification.at(i) > max_probability) {
            max_probability = posteriori_classification.at(i);
            max = i;
        }
    }

    return max;
}

void Classifying::ClassifyAllImages(Model model, vector<string> testing_image, vector<string> testing_labels) {

    vector<vector<double>> confusion_matrix(kDigits, vector<double>(kDigits));

    vector<int> num_frequency(kDigits);

    for (int i = 0; i < testing_labels.size(); ++i) {
        int classification = Classifying::ClassifyingImage(model, testing_image.at(i));
        int actual_num = std::stoi(testing_labels.at(i));
        confusion_matrix[actual_num][classification]++;
        num_frequency[actual_num]++;
    }

    for (int j = 0; j < confusion_matrix.size(); ++j) {
        int num_appeared = num_frequency[j];
        for (int i = 0; i < confusion_matrix.at(0).size(); ++i) {
            if(confusion_matrix[j][i] == 0) {
                cout << std::to_string(confusion_matrix[j][i]) << " ";
                continue;
            }

            confusion_matrix[j][i] /= (double) num_appeared;
            cout << std::to_string(confusion_matrix[j][i]) << " ";
        }
        cout << "\n";
    }
}


