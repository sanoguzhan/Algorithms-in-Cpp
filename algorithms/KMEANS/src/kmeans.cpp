
#include "kmeans.hpp"


KMeans::KMeans(int k){
cluster_num = k;
clusters = new std::vector<cluster_type *>;
indexes = new std::unordered_set<int>;
}
void KMeans::initialize(){
    for(int i=0; i < cluster_num ; i++){
        int index = (rand() % training->size());
        while(indexes->find(index) != indexes->end()){
            index = (rand() % training->size());
        }
        clusters->push_back(new cluster(training->at(index)));
        indexes->insert(index);
    }
}
void KMeans::initialize_all(){
    std::unordered_set<int> on_set;
    for(size_t i=0; i<training->size(); i++){
        if(on_set.find(training->at(i)->get_label()) == on_set.end()){
            clusters->push_back(new cluster_type(training->at(i)));
            on_set.insert(training->at(i)->get_label());
            indexes->insert(i);
        }
    }
}
void KMeans::train(){
    while(indexes->size() < training->size()){
        int index = (rand() % training->size());
        while(indexes->find(index) != indexes->end()){
            index = (rand() % training->size());
        }
        double min_dist = std::numeric_limits<double>::max();
        int best_cluster = 0;
        for(size_t j=0; j < clusters->size(); j++){
            double current = euclidean_distance(clusters->at(j)->centroid, training->at(index));
            if(current < min_dist){
            min_dist = current;
            best_cluster = j;
            }
        }
        clusters->at(best_cluster)->insert_to_cluster(training->at(index));
        indexes->insert(index);
    }
}
double KMeans::euclidean_distance(std::vector<double> *centroid, data *point){
    double dist = 0;
    for(size_t i=0; i< centroid->size(); i++){
        dist += pow(centroid->at(i) - point->get_features()->at(i), 2);
    }
    return sqrt(dist);
}
double KMeans::validate(){
    double correctness = 0;
    for(auto query: *validation){
        double min_dist = std::numeric_limits<double>::max();
        int best = 0;
        for(size_t i = 0; i < clusters->size(); i++){
        double current = euclidean_distance(clusters->at(i)->centroid, query);
        if(current < min_dist){
            min_dist = current;
            best = i;
        }
    }
    if(clusters->at(best)->median == query->get_label()) correctness++;
    }
    return 100.0 * (correctness / (double) validation->size());
}
double KMeans::tests(){
    double correctness = 0;
    for(auto query: *test){
        double min_dist = std::numeric_limits<double>::max();
        int best = 0;
        for(size_t i = 0; i < clusters->size(); i++){
        double current = euclidean_distance(clusters->at(i)->centroid, query);
        if(current < min_dist){
            min_dist = current;
            best = i;
        }
    }
    if(clusters->at(best)->median == query->get_label()) correctness++;
    }
    return 100.0 * (correctness / (double) test->size());
}

int main(void){
    preprocess *import = new preprocess();
    import->read_feature("../../data/train-images.idx3-ubyte");
    import->read_labels("../../data/train-labels.idx1-ubyte");
    import->split_data();
    import->count_digits();
    float accuracy=0;
    float best_accuracy =0;
    int best = 0;
    int best_k = 0;
    double performance = 0.0;
    for(int k = import->get_count(); k < import->get_data("train")->size()*0.1; k++){
            KMeans *kmeans = new KMeans(k);
            kmeans->set_training(import->get_data("train"));
            kmeans->set_test(import->get_data("test"));
            kmeans->set_validation(import->get_data("val"));
            kmeans->initialize();
            kmeans->train();
            performance = kmeans->validate();
            std::cout << "Performance at k=" << k  <<  " : "<< performance << "%" << std::endl;
            if (performance > best){
                best = performance;
                best_k = k;
            }
    }

    KMeans *kmeans = new KMeans(best_k);
    kmeans->set_training(import->get_data("train"));
    kmeans->set_test(import->get_data("test"));
    kmeans->set_validation(import->get_data("val"));
    kmeans->initialize();
    kmeans->tests();
    performance = kmeans->validate();
    std::cout << "Performance for Test at k=" << best_k  <<  " : "<< performance << "%" << std::endl;




    return 0;
}