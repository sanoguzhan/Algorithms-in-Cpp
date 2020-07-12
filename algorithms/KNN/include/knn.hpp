//
// Created by Oguzhan San on 12.07.20.
//
#ifndef ML_ALGORITHMS_IN_CPP_KNN_HPP
#define ML_ALGORITHMS_IN_CPP_KNN_HPP

#include "data.hpp"
#include <vector>

class knn{
    int k;

    std::vector<data *> * neighbors;
    std::vector<data *> * training;
    std::vector<data *> * test;
    std::vector<data *> * validation;

    public:
    knn(int);
    knn();
    ~knn();

    void find_k_nearest(data *query);
    void set_training(std::vector<data *> *vec);
    void set_test(std::vector<data *> * vec);
    void set_validation(std::vector<data *> * vec);
    void set_k(int k);

    float predict();
    double calculate_distance(data* query, data* input);
    double validator();
    double tester();


};

#endif //ML_ALGORITHMS_IN_CPP_KNN_HPP
