//
// Created by user on 3/12/2018.
//

#ifndef NAIVEBAYES_CLASSIFYING_H
#define NAIVEBAYES_CLASSIFYING_H

#include <string>
#include <vector>
#include "Model.h"

using std::vector;
using std::string;

class Classifying {
    public:
        const static char kGray = '+';
        const static char kBlack = '#';
        const static char kWhite = ' ';
        const static int kDigits = 10;
        static bool ReadTestingImages(vector<string> &all_images, string file_name);
        static bool ReadTestingLabels(vector<string> &all_labels, string file_name);
        static int ClassifyingImage(Model model, string image);
        static void ClassifyAllImages(Model model, vector<string> testing_image, vector<string> testing_labels);


};


#endif //NAIVEBAYES_CLASSIFYING_H
