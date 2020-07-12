//
// Created by Oguzhan San on 27.05.20.
//

#include "data.hpp"

data::data(){
    this->features = new std::vector<uint8_t>;
}
data::~data(){

}

void data::set_features(std::vector<uint8_t>* tensor1d){
    features = tensor1d;
}
void data::append(uint8_t num){
    (*features).push_back(num);
}
void data::set_label(uint8_t label_value){
    label = label_value;
}
void data::set_enumerator(int enum_label){
    enumerator = enum_label;
}
int data::get_length(){
    return features->size();
}
uint8_t data::get_label(){
    return label;
}
uint8_t data::get_enumerator(){
    return enumerator;
}
std::vector<uint8_t> * data::get_features(){
    return features;
}
void data::set_distance(double value){
    distance = value;
}