//
// Created by user on 3/12/2018.
//

#ifndef NAIVEBAYES_CLASSIFYING_H
#define NAIVEBAYES_CLASSIFYING_H

#include <string>
#include <vector>
#include "Model.h"
#include <fstream>

using std::vector;
using std::string;
using std::ofstream;

/**
 * Class for classifying images
 */
class Classifying {
    public:
        const static char kWhite = ' ';
        const static int kDigits = 10;
        const static int kHighLow = 2;

        /**
         * Recreates image for display in test results
         */
        static void RecreateImage(string image, ofstream &my_file);

        /**
         * Finds the least/most prototypical image.
         */
        static void PrototypeProbabilities(vector<vector<string>> &prototypes, vector<vector<double>> &probability,
                                           int label, vector<double> posteriori_classification, string image);

        /**
         * Reads the testing images and labels
         */
        static bool ReadTestingImages(vector<string> &all_images, string file_name);
        static bool ReadTestingLabels(vector<string> &all_labels, string file_name);

        /**
         * Classifies one image
         */
        static int ClassifyingImage(Model model, string image, vector<vector<string>> &prototypes,
                                    vector<vector<double>> &probability, int label);

        /**
         * Classifies all imagees
         */
        static bool ClassifyAllImages(Model model, vector<string> testing_image,
                                      vector<string> testing_labels, string file_name);


};


#endif //NAIVEBAYES_CLASSIFYING_H
