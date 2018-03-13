//
// Created by user on 3/10/2018.
//

#ifndef NAIVEBAYES_NUMBER_H
#define NAIVEBAYES_NUMBER_H

#include <string>
#include <vector>

using std::vector;
using std::string;

/**
 * Defines Number object to hold specific digit
 */
class Number {

    public:
        const static int kDimension = 28;
        const static char kWhite = ' ';
        constexpr static double kSmoothingValue = 0.1;

        /**
         * Number constructor and its following properties
         * @param number
         */
        Number(int number);
        int number;
        double times_appeared = 0;
        vector<vector<double>> probability_matrix;

        /**
         * Trains a single num based on the provided image
         * @param data
         */
        void TrainOneNum(string data);

        /**
         * Calculates the probability for every element of the probability matrix
         */
        void CalcProbability();



};


#endif //NAIVEBAYES_NUMBER_H
