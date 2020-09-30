//
// Created by Oguzhan San on 27.05.20.
//

#include "preprocess.hpp"


preprocess::preprocess(){
    data_vector = new std::vector<data *>;
    training_data = new std::vector<data *>;
    test_data = new std::vector<data *>;
    validation_data = new std::vector<data *>;

}
preprocess::~preprocess(){
    //free memory
}

void preprocess::read_feature(std::string path){
    uint32_t header[4]; // In order [Magic Number, Number of Images, Row Size, Column Size]
    unsigned char bytes[4];
    FILE *f = fopen(path.c_str(), "r");
    if(f){
        for(int i=0; i<4; i++){
            if(fread(bytes, sizeof(bytes), 1, f)){
                header[i] = transform_endian(bytes);
            }
        }
        std::cout << "Reading File Header for Input" << std::endl;
        int img_size = header[2] * header[3];

        for(int j=0; j<header[1]; j++){
            data *container = new data();
            uint8_t element[1];
            for(int i=0; i < img_size; i++){
                if(fread(element, sizeof(element), 1, f)){
                    container->append(element[0]);
                }else{
                    std::cerr << "IO Error" << std::endl;
                    exit(1);
                }
            }
            data_vector->push_back(container);
        }
        std::cout << "Successful\nFeature Size: " <<  data_vector->size() << std::endl;
    }else{
        std::cerr << "IO Error No File Found" << std::endl;
    }
}
void preprocess::read_labels(std::string path){
    uint32_t header[4]; // In order [Magic Number, Number of Images]
    unsigned char bytes[4];
    FILE *f = fopen(path.c_str(), "r");
    if(f){
        for(int i=0; i<2; i++){
            if(fread(bytes, sizeof(bytes), 1, f)){
                header[i] = transform_endian(bytes);
            }
        }
        std::cout << "Reading File Header for Label" << std::endl;

        for(int j=0; j < header[1]; j++){

            uint8_t element[1];
            if(fread(element, sizeof(element), 1, f)){
                data_vector->at(j)->set_label(element[0]);
            }else{
                std::cerr << "IO Error" << std::endl;
                exit(1);
            }

        }
        std::cout << "Successful\nLabel Size: " <<  data_vector->size() << std::endl;
    }else{
        std::cerr << "IO Error No File Found" << std::endl;
    }
}
void preprocess::split_data(){
    std::unordered_set<int> index;
    int train_size = data_vector->size() * train_data_pct;
    int test_size =  data_vector->size() * test_data_pct;
    int validation_size = data_vector->size() * val_data_pct;

    long count=0; // Training Data
    while(count < train_size){
        int indx = rand() % data_vector->size();
        if(index.find(indx) == index.end()){
            training_data->push_back(data_vector->at(indx));
            index.insert(indx);
            count++;
        }
    }

    count=0; // Test Data
    while(count < test_size){
        int indx = rand() % data_vector->size();
        if(index.find(indx) == index.end()){
            test_data->push_back(data_vector->at(indx));
            index.insert(indx);
            count++;
        }
    }

    count=0; // Validation Data
    while(count < validation_size){

        int indx = rand() % data_vector->size();
        if(index.find(indx) == index.end()){
            validation_data->push_back(data_vector->at(indx));
            index.insert(indx);
            count++;

        }
    }
    std::cout << "Training Data: " << training_data->size() << "\n"
    << "Test Data: " << test_data->size() << "\n"
    << "Validation Data: " << validation_data->size() << std::endl;

}

void preprocess::count_digits(){
    int temp = 0;
    for(size_t i=0; i< data_vector->size(); i++){
        if(digit_map.find(data_vector->at(i)->get_label()) == digit_map.end()){
            digit_map[data_vector->at(i)->get_label()] = temp;
            data_vector->at(i)->set_enumerator(temp);
            temp++;
        }
    }
    digits = temp;
    std::cout << "Number of unique classes: " << digits << std::endl;
}

uint32_t preprocess::transform_endian(const unsigned char* bytes){
    return (uint32_t) ((bytes[0] << 24) |
                        (bytes[1] << 16) |
                        (bytes[2] << 8) |
                        (bytes[3]));
}

std::vector<data *> * preprocess::get_data(std::string type){
    if (type == "train"){
        return training_data;
    }else if(type == "test"){
        return test_data;
    }else if(type == "val"){
        return validation_data;
    }
    return nullptr;
}


//int main(){
//    preprocess *import = new preprocess();
//    import->read_feature("../data/train-images.idx3-ubyte");
//    import->read_labels("../data/train-images.idx1-ubyte");
//    import->split_data();
//    import->count_digits();
//    return 0;
//}