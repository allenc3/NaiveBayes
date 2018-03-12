//
// Created by user on 3/10/2018.
//

#ifndef NAIVEBAYES_NUMBER_H
#define NAIVEBAYES_NUMBER_H

#include <string>
#include <vector>

using std::vector;
using std::string;


class Number {

    public:
        const static int kDimension = 28;
        const static char kGray = '+';
        const static char kBlack = '#';
        const static char kWhite = ' ';
        constexpr static double kSmoothingValue = 0.1;

        Number(int number);
        int number;
        double times_appeared = 0;
        vector<vector<double>> probability_matrix;
        int priors;

        void TrainOneNum(string data);
        void CalcProbability();

        static vector<Number> InitializeAllNum();
        static void ProcessInput(vector<string> input, vector<string> &training_images,
                                 vector<string> &training_labels);
        static void TrainAllNum(vector<Number> &all_num, vector<string> training_images,
                                vector<string> training_labels);

};


#endif //NAIVEBAYES_NUMBER_H
