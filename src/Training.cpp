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

bool Training::ReadTrainingFiles(vector<string> &all_input) {

    string file_name;
    while(true) {
        cout << "Please choose a \"training images\" file!\n";

        cin >> file_name;
        if (file_name == "exit") {
            return true;
        }

        ifstream training_images(file_name);
        if (training_images.fail()) {
            cout << file_name + " does not exist!\n";
            continue;
        } else {
            string line;
            while (std::getline(training_images, line)) {
                all_input.push_back(line);
            }
            break;
        }
    }

    while(true) {
        cout << "Please choose a \"training labels\" file!\n";
        cin >> file_name;
        if(file_name == "exit") {
            return true;
        }

        ifstream training_labels(file_name);
        if (training_labels.fail()) {
            cout << file_name + " does not exist!\n";
            continue;
        } else{
            string line;
            while (std::getline(training_labels, line)) {
                all_input.push_back(line);
            }

//            for (int i = 0; i < all_input.size(); ++i) {
//                cout << all_input.at(i) + "\n";
//            }
            return false;
        }
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

bool Training::SaveModel(vector<string> all_input) {

    ofstream myfile;

    while(true) {
        string input;
        cout << "What is the file name you want to save to?\n";
        cin >> input;
        if(input == "exit") {
            return false;
        }
        myfile.open(input);

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
            cout << "File path invalid!\n";
        }
    }


}

