//
// Created by Oguzhan San on 27.05.20.
//

#ifndef ML_ALGORITHMS_IN_CPP_PREPROCESS_HPP
#define ML_ALGORITHMS_IN_CPP_PREPROCESS_HPP


#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <unordered_set>
#include "stdint.h"
#include "data.h"


class preprocess {

    std::vector<data *> *data_vector;
    std::vector<data *> *training_data;
    std::vector<data *> *test_data;
    std::vector<data *> *validation_data;
    std::map<uint8_t, int>digit_map;

    constexpr float train_data_size = 0.80; // Train data size percentage
    constexpr float test_data_size = 0.15; // Test data size percentage
    constexpr float val_data_size = 0.5; // Validation data size percentage
    int digits; // number of classes in data
    int size; // feature vector size


public:
    preprocess();
    ~preprocess();

    void read_feature(std::string);
    void read_labels(std::string);
    void split_data();
    void count_digits();

    uint32_t transform_endian(const unsigned char*);

    std::vector<data *> * get_data(); // Retrieves data [training, test, validation]


};


#endif //ML_ALGORITHMS_IN_CPP_PREPROCESS_HPP
