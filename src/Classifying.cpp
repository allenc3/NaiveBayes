//
// Created by user on 3/12/2018.
//

#include "Classifying.h"
#include <fstream>
#include <math.h>
#include <iostream>
#include <iomanip>

using std::ifstream;
using std::ofstream;
using std::cout;

/**
 * Reads in testing images from a file and places content in a vector of strings.
 */
bool Classifying::ReadTestingImages(vector<string> &all_images, string file_name) {

    // Reads file stream.
    ifstream testing_images(file_name);

    if (testing_images.fail()) {
        return false;
    } else {
        string line;
        string image;
        int count = 0;
        // Adds an image(28) to vector
        while (std::getline(testing_images, line)) {
            if(count < 28) {
                image += line;
                count++;
            }
            if(count == 28) {
                all_images.push_back(image);
                image.clear();
                count = 0;
            }

        }
        testing_images.close();
        return true;
    }

}

/**
 * Reads in testing labels from a file and places content in a vector of strings.
 */
bool Classifying::ReadTestingLabels(vector<string> &all_labels, string file_name) {

    ifstream testing_labels(file_name);
    // Returns false if can't read
    if (testing_labels.fail()) {
        return false;
    } else {
        string line;
        while (std::getline(testing_labels, line)) {
            all_labels.push_back(line);
        }
        testing_labels.close();
        return true;
    }

}

/**
 * Classifies an image as a number.
 * @param model The model to use
 * @param image Image to classify
 * @param prototypes keeps track of most/least prototypical
 * @param probability keeps track of highest/lowest probability
 * @param label the label according to testlabels
 * @return the digit the model classified the image as
 */
int Classifying::ClassifyingImage(Model model, string image, vector<vector<string>> &prototypes,
                                  vector<vector<double>> &probability, int label) {

    vector<double> posteriori_classification(kDigits, 0);

    // Adds in the class's individual probabilities first.
    for (int j = 0; j < model.probability_matrix.size(); ++j) {
        posteriori_classification[j] += log2(model.probability_matrix[j][0]);
    }

    // Adds in the class's probability based on the image
    for (int pixel = 0; pixel < image.length(); ++pixel) {
        for (int digit = 0; digit < kDigits; ++digit) {
            // pixel + 1 since 0 is used for the
            if(image.at(pixel) != kWhite) {
                posteriori_classification[digit] +=  log2(model.probability_matrix[digit][pixel + 1]);
            } else {
                posteriori_classification[digit] +=  log2(1 - model.probability_matrix[digit][pixel + 1]);
            }
        }
    }

    // Classifies image as a number
    int max = 0;
    double max_probability;
    for (int i = 0; i < posteriori_classification.size(); ++i) {
        // Keeps track of most/least prototypical.
        if(i == label) {
            PrototypeProbabilities(prototypes, probability, label, posteriori_classification, image);
        }

        if(i == 0) {
            max_probability = posteriori_classification.at(0);
        } else {
            if (posteriori_classification.at(i) > max_probability) {
                max_probability = posteriori_classification.at(i);
                max = i;
            }
        }
    }
    return max;
}

/**
 * Keeps track of most/least prototypical.
 * @param prototypes vector of images
 * @param probability vector of probabilities
 * @param label from testing label
 * @param posteriori_classification the probability
 * @param image
 */
void Classifying::PrototypeProbabilities(vector<vector<string>> &prototypes, vector<vector<double>> &probability,
                                         int label, vector<double> posteriori_classification, string image) {
    int lowest = 0;
    int highest = 1;

    // Low and High in Probability vector is not filled in yet, then automatically fill in the lowest.
    if(probability[label][lowest] == 0 && probability[label][highest] == 0) {
        probability[label][lowest] = posteriori_classification[label];
        prototypes[label][lowest] = image;
    }

    // If low is filled in but high is not
    else if(probability[label][lowest] != 0 && probability[label][highest] == 0) {
        // If new probability found is greater than the low, set the high to it.
        if(posteriori_classification[label] > probability[label][lowest]) {
            probability[label][highest] = posteriori_classification[label];
            prototypes[label][highest] = image;
        }
        // If new probability found is lower than the low, set the low to it.
        else if(posteriori_classification[label] < probability[label][lowest]) {
            double temp_prob = probability[label][lowest];
            string temp_image = prototypes[label][lowest];

            probability[label][lowest] = posteriori_classification[label];
            prototypes[label][lowest] = image;

            probability[label][highest] = temp_prob;
            prototypes[label][highest] = temp_image;
        }
    }
    // If both low and high is filled
    else if(probability[label][lowest] != 0 && probability[label][highest] != 0) {
        // If new probability found is lower than low, set the low to it.
        if(posteriori_classification[label] < probability[label][lowest]) {
            probability[label][lowest] = posteriori_classification[label];
            prototypes[label][lowest] = image;
        }
        // If new probability found is higher than the high, set the high to it.
        else if(posteriori_classification[label] > probability[label][highest]) {
            probability[label][highest] = posteriori_classification[label];
            prototypes[label][highest] = image;
        }
    }
}

/**
 * Classifies all the images
 * @param model
 * @param testing_image
 * @param testing_labels
 * @param file_name
 * @return
 */
bool Classifying::ClassifyAllImages(Model model, vector<string> testing_image,
                                       vector<string> testing_labels, string file_name) {

    ofstream myfile;
    myfile.open(file_name);
    if(myfile.good()) {

        vector<vector<double>> confusion_matrix(kDigits, vector<double>(kDigits));

        // Keep track of each num's frequency for confusion matrix
        vector<int> num_frequency(kDigits);

        vector<vector<string>> prototypes(kDigits, vector<string>(kHighLow));
        vector<vector<double>> probabilities(kDigits, vector<double>(kHighLow));

        // Classifies all images and fill in corresponding spot for confusion matrix
        for (int i = 0; i < testing_labels.size(); ++i) {
            int actual_num = std::stoi(testing_labels.at(i));
            int classification = Classifying::ClassifyingImage(model, testing_image.at(i),
                                                               prototypes, probabilities, actual_num);

            confusion_matrix[actual_num][classification]++;
            num_frequency[actual_num]++;
        }

        // Formatting confusion matrix
        for (int j = 0; j < confusion_matrix.size() + 1; ++j) {
            if (j == 0) {
                for (int i = 0; i < confusion_matrix.size() + 1; ++i) {
                    if (i == 0) {
                        myfile << "  ";
                    }
                    if (i > 0) {
                        myfile << "    " << i - 1 << "    ";
                    }
                }
                myfile << "\n";
            } else {
                int num_appeared = num_frequency[j - 1];
                for (int i = 0; i < confusion_matrix.at(0).size() + 1; ++i) {
                    if (i == 0) {
                        myfile << j - 1 << " ";
                    } else {
                        if (confusion_matrix[j - 1][i - 1] == 0) {
                            myfile << std::to_string(confusion_matrix[j - 1][i - 1]) << " ";
                            continue;
                        }

                        confusion_matrix[j - 1][i - 1] /= (double) num_appeared;
                        myfile << std::to_string(confusion_matrix[j - 1][i - 1]) << " ";
                    }
                }
                myfile << "\n";
            }
        }

        // Formatting display for least/most prototypical
        for (int k = 0; k < probabilities.size(); ++k) {
            myfile << "For " + std::to_string(k) + ": \n";
            for (int i = 0; i < probabilities[0].size(); ++i) {
                if (i == 0) {
                    myfile << "Least Prototypical: " + std::to_string(probabilities[k][i]) + "\n";
                } else {
                    myfile << "Most Prototypical: " + std::to_string(probabilities[k][i]) + "\n";
                }
                RecreateImage(prototypes[k][i], myfile);
                myfile << "\n";
            }
        }
        myfile.close();
        return true;
    }
    return false;

}

/**
 * Recreates image for display
 */
void Classifying::RecreateImage(string image, ofstream &my_file) {

    int count = 0;
    for (int i = 0; i < image.size(); ++i) {
        if(count == 28) {
            my_file << "\n";
            count = 0;
        }
        my_file << image[i];
        count++;
    }
}
