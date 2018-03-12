//
// Created by user on 3/10/2018.
//

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../src/Number.h"
#include "TestingData.h"
#include <string>
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

    SECTION("InitializeAllNum"){
        vector<Number> num = Number::InitializeAllNum();
        REQUIRE(num.at(0).number == 0);
        REQUIRE(num.at(9).number == 9);
    }

    SECTION("TestingData.class, ProcessInput"){
        vector<string> training_images;
        vector<string> training_labels;
        vector<string> all_input = TestingData::all_input;
        Number::ProcessInput(all_input, training_images, training_labels);

        REQUIRE(training_images.at(0).size() == 784);
        REQUIRE(stoi(training_labels.at(0)) == 5);
        REQUIRE(training_images.at(1).size() == 784);
        REQUIRE(stoi(training_labels.at(1)) == 0);
    }

    SECTION("TrainOneNum"){
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

    SECTION("TrainAllNum, DivideByAppearance"){
        vector<string> training_images;
        vector<string> training_labels;
        vector<string> all_input = TestingData::all_input;
        Number::ProcessInput(all_input, training_images, training_labels);
        vector<Number> all_num = Number::InitializeAllNum();

        Number::TrainAllNum(all_num, training_images, training_labels);
        REQUIRE(all_num.at(5).probability_matrix[5][17] == 0.5);
        REQUIRE(all_num.at(5).probability_matrix[13][12] == 1);
        REQUIRE(all_num.at(0).probability_matrix[4][15] == 1);
    }


}

