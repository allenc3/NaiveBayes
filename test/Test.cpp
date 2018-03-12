//
// Created by user on 3/10/2018.
//

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../src/Number.h"
#include "TestingData.h"
#include "../src/Training.h"
#include <string>
#include <math.h>
#include <sstream>


using std::string;

TEST_CASE("Testing Number Class"){

    SECTION("Create Number Object"){
        Number one = Number(1);
        REQUIRE(one.number == 1);
        REQUIRE(one.probability_matrix.size() == 28);
        REQUIRE(one.probability_matrix.at(0).size() == 28);
        REQUIRE(one.times_appeared == 0);
    }

    SECTION("Number::TrainOneNum"){
        Number five = Number(5);
        vector<string> all_input = TestingData::all_input;
        string five_image;
        for (int i = 0; i < 28; ++i) {
            five_image += all_input.at(i);
        }
        five.TrainOneNum(five_image);
        REQUIRE(five.probability_matrix[7][6] == 0);
        REQUIRE(five.probability_matrix[7][7] == 1);
        REQUIRE(five.probability_matrix[7][8] == 1);
    }
}

TEST_CASE("Training Class"){
    SECTION("Training::InitializeAllNum"){
        vector<Number> num = Training::InitializeAllNum();
        REQUIRE(num.at(0).number == 0);
        REQUIRE(num.at(9).number == 9);
    }

    SECTION("Training::ProcessInput, TestingData.class"){
        vector<string> training_images;
        vector<string> training_labels;
        vector<string> all_input = TestingData::all_input;
        Training::ProcessInput(all_input, training_images, training_labels);

        REQUIRE(training_images.at(0).size() == 784);
        REQUIRE(stoi(training_labels.at(0)) == 5);
        REQUIRE(training_images.at(1).size() == 784);
        REQUIRE(stoi(training_labels.at(1)) == 0);
    }

    SECTION("Training::TrainAllNum, Number::CalcProbability"){
        vector<string> training_images;
        vector<string> training_labels;
        vector<string> all_input = TestingData::all_input;
        Training::ProcessInput(all_input, training_images, training_labels);
        vector<Number> all_num = Training::InitializeAllNum();

        Training::TrainAllNum(all_num, training_images, training_labels);
        REQUIRE(all_num.at(5).probability_matrix[5][17] == 0.5);
        double prob = all_num.at(5).probability_matrix[13][12];
        REQUIRE(fabs(prob - 0.9545454545) <= 0.00001);
        prob = all_num.at(0).probability_matrix[4][15];
        REQUIRE(fabs(prob - 0.9166666667) <= 0.00001);
    }

    SECTION("Training::ReadTrainingImages, Training::ReadTrainingLabels, Training::SaveModel"){
        vector<string> test = TestingData::input_split(TestingData::trainingtest);
        vector<string> all_input;
        REQUIRE(Training::ReadTrainingImages(all_input, "../data/mytestimages") == true);
        REQUIRE(Training::ReadTrainingLabels(all_input, "../data/mytestlabels") == true);
        REQUIRE(Training::SaveModel(all_input, "../models/test") == true);
    }

}

