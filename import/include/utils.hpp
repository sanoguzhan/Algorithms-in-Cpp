#ifndef __UTILS_HPP
#define __UTILS_HPP

#include "data.hpp"
#include <vector>

class HelperVariable{

protected:
    std::vector<data *> * training;
    std::vector<data *> * test;
    std::vector<data *> * validation;
    
public:
    void set_training(std::vector<data *> *vec);
    void set_test(std::vector<data *> * vec);
    void set_validation(std::vector<data *> * vec);

};
#endif