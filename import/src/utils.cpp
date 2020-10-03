#include "utils.hpp"
#
void HelperVariable::set_training(std::vector<data *> *vec){
    training = vec;
}
void HelperVariable::set_test(std::vector<data *> * vec){
    test = vec;
}
void HelperVariable::set_validation(std::vector<data *> * vec){
    validation = vec;
}

