#ifndef HISTOGRAM_HPP_
#define HISTOGRAM_HPP_
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include "bow_dictionary.h"
#include <opencv2/flann.hpp>
namespace ipb{
class Histogram{
    public:
        Histogram();
        Histogram(const std::vector<int> &data){
            data_=data;
        };
        //TODO: imlementation constructor 
        Histogram(const cv::Mat &descriptors, BowDictionary &dictionary);
        //initiate all vector functionality
        int size() const { return data_.size();}
        bool empty() const {return !(data_.size()>0);}
        std::vector<int> data() const{return data_;}

    private:
        void histogram(const cv::Mat &descriptors,  BowDictionary &dictionary) ;
        std::vector<int> data_;


};
}

#endif