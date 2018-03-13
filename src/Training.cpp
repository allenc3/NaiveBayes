//
// Created by user on 3/11/2018.
//

#include "Training.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>


using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;

/**
 * Reads image file
 */
bool Training::ReadTrainingImages(vector<string> &all_input, string file_name) {

    ifstream training_images(file_name);
    //Returns false if file cannot be read
    if (training_images.fail()) {
        return false;
    } else {
        string line;
        while (std::getline(training_images, line)) {
            all_input.push_back(line);
        }
        return true;
    }
}

/**
 * Reads labels file
 */
bool Training::ReadTrainingLabels(vector<string> &all_input, string file_name) {

    ifstream training_labels(file_name);
    //Returns false if file cannot be read
    if (training_labels.fail()) {
        return false;
    } else{
        string line;
        while (std::getline(training_labels, line)) {
            all_input.push_back(line);
        }
        return true;
    }
}

/**
 * Initializes all Number objects
 */
vector<Number> Training::InitializeAllNum(){
    vector<Number> all_num;
    const int kDigitLimit = 10;
    for (int i = 0; i < kDigitLimit; i++) {
        all_num.push_back(Number(i));
    }
    return all_num;
}

/**
 * Process's input by combining image and label data
 */
void Training::ProcessInput(vector<string> input, vector<string> &training_images, vector<string> &training_labels){

    string image;
    int count = 1;
    for (int i = 0; i < input.size(); ++i) {
        string line = input.at(i);
        // Once images is done, start reading labels
        if(line.find_first_of("0123456789") != string::npos) {
            training_labels.push_back(line);
            continue;
        }
        image += line;
        if(count == 28) {
            training_images.push_back(image);
            image.clear();
            count = 1;
        } else {
            count++;
        }
    }
}

/**
 * Trains all the Numbers by using all the images
 */
void Training::TrainAllNum(vector<Number> &all_num, vector<string> training_images, vector<string> training_labels) {

    for (int i = 0; i < training_labels.size(); ++i) {
        // Find the label, and use this to determine what the image is at a particular index
        int num = stoi(training_labels.at(i));
        for (int j = 0; j < all_num.size(); ++j) {
            // Use label to train the number with the image.
            if(num == all_num.at(j).number) {
                all_num.at(j).TrainOneNum(training_images.at(i));
            }
        }
    }

    // Calculates probability for each element of the probability matrix for each Number.
    for (int k = 0; k < all_num.size(); ++k) {
        all_num.at(k).CalcProbability();
    }
}

/**
 * Saves Model
 */
bool Training::SaveModel(vector<string> all_input, string file_name) {

    ofstream model;
    model.open(file_name);

    // Returns true if file can be saved, false otherwise.
    if (model.good()) {
        vector<string> training_images;
        vector<string> training_labels;

        vector<Number> all_num = Training::InitializeAllNum();

        Training::ProcessInput(all_input, training_images, training_labels);
        Training::TrainAllNum(all_num, training_images, training_labels);

        // The class's probability, P(class)
        vector<double> priors;
        for (int i = 0; i < 10; ++i) {
            priors.push_back(all_num.at(i).times_appeared / (double) training_labels.size());
        }

        // Formatting saved file
        for (int i = 0; i < 10; ++i) {
            model << priors.at(i) << " \n";
            for (int j = 0; j < 28; ++j) {
                for (int k = 0; k < 28; ++k) {
                    model << std::to_string(all_num[i].probability_matrix[j][k]) << " ";
                }
                model << "\n";
            }
        }
        model.close();
        return true;
    } else {
        return false;
    }
}

