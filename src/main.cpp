//
// Created by user on 3/10/2018.
//

#include <string>
#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include "Number.h"
#include "Model.h"
#include "../test/TestingData.h"
#include "Training.h"
#include "Classifying.h"

using std::string;
using std::cin;
using std::cout;
using std::ofstream;
using std::ifstream;


void LoadModel(Model &model);
void TrainModel();
void ClassifyImage(Model model);

int main(){

    Model model;
    while(true){

        cout << "Select an action: Training, Load, Classify, or Exit\n";


        string input;
        cin >> input;

        if(input == "Training") {
            TrainModel();
        } else if(input == "Load") {
            LoadModel(model);
        } else if(input == "Classify") {
            ClassifyImage(model);
        }
        else if(input == "Exit") {
            break;
        }
        else {
            cout << "Unknown Command.";
            continue;
        }
    }
    return 0;

}

void ClassifyImage(Model model) {
    string file_name;
    vector<string> all_images;
    vector<string> all_labels;
    while (true) {
        cout << "Please choose a \"testing images\" file!\n";
        cin >> file_name;
        if (file_name == "exit") {
            return;
        }
        bool success = Classifying::ReadTestingImages(all_images, file_name);
        if (!success) {
            cout << file_name + " does not exist!\n";
            continue;
        }
        break;
    }

    while(true) {
        cout << "Please choose a \"testing labels\" file!\n";
        cin >> file_name;
        if (file_name == "exit") {
            return;
        }
        bool success = Classifying::ReadTestingLabels(all_labels, file_name);
        if (!success) {
            cout << file_name + " does not exist!\n";
            continue;
        }
        break;
    }


    while(true) {
        string file_name;
        cout << "Please choose a location to save to!\n";
        cin >> file_name;

        bool success = Classifying::ClassifyAllImages(model, all_images, all_labels, file_name);
        if(!success){
            cout << "Failed to generate test results! Invalid file name.\n";
            break;
        }
        break;
    }


}
//
void LoadModel(Model &model){
    string file_name;
    while(true) {
        cout << "Please choose a Model to load!\n";
        cin >> file_name;
        if(file_name == "exit") {
            return;
        }
        bool success = model.LoadModel(file_name);
        if(success) {
            cout << file_name + " successfully loaded!\n";
            return;
        } else {
            cout << file_name + " does not exist!\n";
            continue;
        }
    }
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

//Model model = Model();
//    model.LoadModel("../models/TrainingModel.txt");
//
//    vector<string> load_test = TestingData::input_split(TestingData::load_test_one);
//    string image;
//    for (int i = 0; i < load_test.size(); ++i) {
//        image += load_test.at(i);
//    }
//
//    vector<string> hi;
//    hi.push_back(image);
//
//    vector<string> num;
//    num.push_back(std::to_string(9));
//
//    Classifying::ClassifyAllImages(model, hi, num);
