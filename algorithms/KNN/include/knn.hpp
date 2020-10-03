//
// Created by Oguzhan San on 12.07.20.
//
#ifndef ML_ALGORITHMS_IN_CPP_KNN_HPP
#define ML_ALGORITHMS_IN_CPP_KNN_HPP

#include "utils.hpp"


class knn: public HelperVariable{
    int k;

    std::vector<data *> * neighbors;


    public:
    knn(int);
    knn();
    ~knn();

    void find_k_nearest(data *query);
    void set_k(int k);

    float predict();
    double calculate_distance(data* query, data* input);
    double validator();
    double tester();


};

#endif //ML_ALGORITHMS_IN_CPP_KNN_HPP
