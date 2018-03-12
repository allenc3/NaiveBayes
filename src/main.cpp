//
// Created by user on 3/10/2018.
//

#include <string>
#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include "Number.h"
#include "../test/TestingData.h"
#include "Training.h"

using std::string;
using std::cin;
using std::cout;
using std::ofstream;
using std::ifstream;


void TrainModel();

int main(){

    while(true){

        cout << "Select an action: Training, load model, classify image, or exit\n";
        string input;
        cin >> input;

        if(input == "Training") {
            TrainModel();
        }

        else if(input == "exit"){
            break;
        }
        else{
            cout << "Unknown Command.";
            continue;
        }
    }
    return 0;
}

void TrainModel(){
    vector<string> all_input;
    string file_name;
    while (true) {
        cout << "Please choose a \"training images\" file!\n";
        cin >> file_name;
        if (file_name == "exit") {
            return;
        }
        bool success = Training::ReadTrainingImages(all_input, file_name);
        if (!success) {
            cout << file_name + " does not exist!\n";
            continue;
        }
        break;
    }

    while(true) {
        cout << "Please choose a \"training labels\" file!\n";
        cin >> file_name;
        if (file_name == "exit") {
            return;
        }
        bool success = Training::ReadTrainingLabels(all_input, file_name);
        if (!success) {
            cout << file_name + " does not exist!\n";
            continue;
        }
        break;
    }

    while(true) {
        cout << "What is the file name you want to save to?\n";
        cin >> file_name;
        if(file_name == "exit") {
            return;
        }
        bool success = Training::SaveModel(all_input, file_name);
        if(!success) {
            cout << "File path invalid!\n";
            continue;
        }
        break;
    }
}



//vector<string> training_images;
//vector<string> training_labels;
//vector<string> all_input = TestingData::all_input;
//Number::ProcessInput(all_input, training_images, training_labels);
//vector<Number> all_num = Number::InitializeAllNum();
//
//Number::TrainAllNum(all_num, training_images, training_labels);
//
//for (int i = 0; i < 10; ++i) {
//cout << all_num[i].number << "\n";
//for (int j = 0; j < 28; ++j) {
//for (int k = 0; k < 28; ++k) {
//cout << all_num[i].probability_matrix[j][k];
//}
//cout << "\n";
//}
//cout << "\n";
//}


// THIS SHIT IS SAVING MODEL
//ofstream myfile;
//myfile.open("../models/" + hi + ".txt");
//vector<string> training_images;
//vector<string> training_labels;
//
//vector<string> all_input;
//
//string line;
//while (std::getline(cin, line)) {
//all_input.push_back(line);
//}
//
//vector<Number> all_num = Number::InitializeAllNum();
//
//Number::ProcessInput(all_input, training_images, training_labels);
//Number::TrainAllNum(all_num, training_images, training_labels);
//
//vector<double> priors;
//for (int i = 0; i < 10; ++i) {
//priors.push_back(all_num.at(i).times_appeared / (double) training_labels.size());
//}
//for (int i = 0; i < 10; ++i) {
//for (int j = 0; j < 28; ++j) {
//for (int k = 0; k < 28; ++k) {
//myfile << std::to_string(all_num[i].probability_matrix[j][k]);
//}
//myfile << "\n";
//}
//myfile << "\n";
//}
//myfile.close();