#ifndef __KMEANS_HPP
#define __KMEANS_HPP


#include <unordered_set>
#include <limits>
#include <cstdlib>
#include <cmath>
#include <map>
#include "preprocess.hpp"
#include "utils.hpp"

typedef struct cluster{
    std::vector<double> *centroid;
    std::vector<data * > *cluster_group;
    std::map<int, int> count;
    int median;

    cluster(data *initial){
        centroid = new std::vector<double>;
        cluster_group = new std::vector<data *>;

        for(auto v: *(initial->get_features())){
            centroid->push_back(v);
        }
        cluster_group->push_back(initial);
        count[initial->get_label()] = 1;
        median = initial->get_label();

    }

    void insert_to_cluster(data *point){
        int previous = cluster_group->size();
        cluster_group->push_back(point);
        for(size_t i=0; i<centroid->size()-1; i++){
            double val = centroid->at(i);
            val *= previous;
            val += point->get_features()->at(i);
            val /= (double)cluster_group->size();
            centroid->at(i) = val;
            }
            if(count.find(point->get_label()) == count.end()){
                count[point->get_label()] =1;

            }else{
                count[point->get_label()]++;
            }
        }

    void set_median(){
        int best;
        int frequency;
        for(auto pair: count){
            if(pair.second > frequency){
                frequency = pair.second;
                best = pair.first;

            }
        }
        median = best;
    }
} cluster_type;


class KMeans: public HelperVariable{
    int cluster_num;
    std::vector<cluster_type *> *clusters;
    std::unordered_set<int> *indexes;

    public:
        KMeans(int k);
        void initialize();
        void initialize_all();
        void train();
        double euclidean_distance(std::vector<double> *, data *);
        double validate();
        double tests();
};
#endif