//
// Created by user on 3/10/2018.
//

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Number.h"
#include "../test/TestingData.h"

using std::string;
using std::cin;
using std::cout;
using std::ofstream;

int main(){

//    vector<string> training_images;
//    vector<string> training_labels;
//
//    vector<string> all_input;
//
//    string line;
//    while(std::getline(cin, line)) {
//        all_input.push_back(line);
//    }
//
//    vector<Number> all_num = Number::InitializeAllNum();
//
//    Number::ProcessInput(all_input, training_images, training_labels);
//    Number::TrainAllNum(all_num, training_images, training_labels);
//
//    vector<double> priors;
//    for (int i = 0; i < 10; ++i) {
//        priors.push_back(all_num.at(i).times_appeared/(double)training_labels.size());
//    }

    string hi;
//    cout << "please enter file name";
    while(true){
        cin >> hi;
        if(hi == "exit") {
            break;
        } else {

            ofstream myfile;
            myfile.open("../models/" + hi + ".txt");
//            for (int i = 0; i < 10; ++i) {
//                for (int j = 0; j < 28; ++j) {
//                    for (int k = 0; k < 28; ++k) {
//                        myfile << std::to_string(all_num[i].probability_matrix[j][k]);
//                    }
//                    myfile << "\n";
//                }
//                myfile << "\n";
//            }
            myfile << "whuchu doing";

            myfile.close();
        }
    }

    return 0;

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
