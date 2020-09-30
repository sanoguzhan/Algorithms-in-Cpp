//
// Created by Oguzhan San on 12.07.20.
//

#include "knn.hpp"
#include <cmath>
#include <limits>
#include <map>
#include "stdint.h"
#include "preprocess.hpp"

knn::knn(int val){
    k = val;
}
knn::knn(){

}
knn::~knn(){

}

void knn::find_k_nearest(data *query){
    neighbors = new std::vector<data *>;
    double min = std::numeric_limits<double>::max();
    double min_temp = min;
    int index = 0;
    for(int i=0; i <k; i++){
        if(i == 0){
            for(int j=0; j < training->size(); j++){
                double distance = calculate_distance(query, training->at(j));
                training->at(j)->set_distance(distance);
                if (distance < min){
                    min =distance;
                    index = j;
                }
            }
            neighbors->push_back(training->at(index));
            min_temp = min;
            min = std::numeric_limits<double>::max();
        } else{
            for(int j = 0; j < training->size(); j++){
                double distance = calculate_distance(query, training->at(j));
                if(distance > min_temp && distance < min){
                    min =distance;
                    index = j;
                }
            }
            neighbors->push_back(training->at(index));
            min_temp = min;
            min = std::numeric_limits<double>::max();
        }
    }
}
void knn::set_training(std::vector<data *> *vec){
    training = vec;
}
void knn::set_test(std::vector<data *> * vec){
    test = vec;
}
void knn::set_validation(std::vector<data *> * vec){
    validation = vec;
}
void knn::set_k(int k){
    this->k = k;
}

float knn::predict(){
    std::map<uint8_t, int> frequency;
    for(int i=0; i< neighbors->size(); i++){
        if(frequency.find(neighbors->at(i)->get_label()) == frequency.end()){
            frequency[neighbors->at(i)->get_label()] = 1;
        }else{
            frequency[neighbors->at(i)->get_label()]++;
        }
    }

    int best = 0;
    int max = 0;
    for(auto key: frequency){
        max = key.second;
        best = (float)key.first;
    }
    delete neighbors;
    return best;
}
double knn::calculate_distance(data* query, data* input){
    double distance = 0.0;
    if(query->get_length() != input->get_length()){
        std::cerr << "Mismatch sizes" << std::endl;
        exit(1);
    }
#ifdef EUCLID
    for(unsigned i =0; i < query->get_length(); i++){
        distance += pow(query->get_features()->at(i) - input->get_features()->at(i),2);
    }
    distance = sqrt(distance);
    return distance;
#elif defined MANHATTAN
#endif
    return distance;
}
double knn::validator(){
    int count = 0;
    int indx = 0;
    for(data *query_p: *validation){
        find_k_nearest(query_p);
        float prediction = predict();
        if (prediction == query_p->get_label()){
            count++;
        }
        indx++;
        std::cout << "Performance at iteration: " << indx  << " "<<(((double)count*100.0) / ((double)indx)) << "%" << std::endl;
    }
    double performance = (((double ) count*100) / ((double)validation->size()));
    std::cout << "For k:" << k  << "\n" <<"Final Validation Performance " << performance << std::endl;
    return performance;
}
double knn::tester(){
    int count = 0;

    for(data *query_p: *test){
        find_k_nearest(query_p);
        float prediction = predict();
        if (prediction == query_p->get_label()){
            count++;
        }
    }
    double performance = (((double) count*100) / ((double)test->size()));
    std::cout << "Final Test Performance " << performance;
    return performance;
}

int main(void){
    preprocess *import = new preprocess();
    import->read_feature("../../data/train-images.idx3-ubyte");
    import->read_labels("../../data/train-labels.idx1-ubyte");
    import->split_data();
    import->count_digits();
    knn *knearest = new knn();
    knearest->set_training(import->get_data("train"));
    knearest->set_test(import->get_data("test"));
    knearest->set_validation(import->get_data("val"));
    float accuracy=0;
    float best_accuracy =0;
    int best_k = 1;
    for (int i = 1; i <= 4; i++) {
        if (i ==1){
            knearest->set_k(i);
            accuracy =knearest->validator();
            best_k = i;}
            else{
                knearest->set_k(i);
                accuracy =knearest->validator();
                if(accuracy > best_accuracy){
                    best_accuracy = accuracy;
                    best_k = i;
                }
            }

        }

    knearest->set_k(best_k);
    knearest->tester();
    return 0;
}
