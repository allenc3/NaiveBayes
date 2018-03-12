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

bool Training::ReadTrainingImages(vector<string> &all_input, string file_name) {

    string base_path = "data/";
    ifstream training_images(base_path + file_name);

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

bool Training::ReadTrainingLabels(vector<string> &all_input, string file_name) {

    string base_path = "data/";
    ifstream training_labels(base_path + file_name);


    if (training_labels.fail()) {
        return false;
    } else{
        string line;
        while (std::getline(training_labels, line)) {
            all_input.push_back(line);
        }

//        for (int i = 0; i < all_input.size(); ++i) {
//            cout << all_input.at(i) + "\n";
//        }
        return true;
    }
}



vector<Number> Training::InitializeAllNum(){
    vector<Number> all_num;
    const int kDigitLimit = 10;
    for (int i = 0; i < kDigitLimit; i++) {
        all_num.push_back(Number(i));
    }
    return all_num;
}

void Training::ProcessInput(vector<string> input, vector<string> &training_images, vector<string> &training_labels){

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

void Training::TrainAllNum(vector<Number> &all_num, vector<string> training_images, vector<string> training_labels) {

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

bool Training::SaveModel(vector<string> all_input, string file_name) {

    ofstream myfile;

    myfile.open("models/" + file_name + ".txt");

    if (myfile.good()) {
        vector<string> training_images;
        vector<string> training_labels;

        vector<Number> all_num = Training::InitializeAllNum();

        Training::ProcessInput(all_input, training_images, training_labels);
        Training::TrainAllNum(all_num, training_images, training_labels);

        vector<double> priors;
        for (int i = 0; i < 10; ++i) {
            priors.push_back(all_num.at(i).times_appeared / (double) training_labels.size());
        }

        for (int i = 0; i < 10; ++i) {
            myfile << priors.at(i) << "\n";
            for (int j = 0; j < 28; ++j) {
                for (int k = 0; k < 28; ++k) {
                    myfile << std::to_string(all_num[i].probability_matrix[j][k]);
                }
                myfile << "\n";
            }
        }
        myfile.close();
        return true;
    } else {
        return false;
    }



}

