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
        Histogram(const cv::Mat &descriptors, BowDictionary &dictionary);
        //initiate all vector functionality
        int size() const { return data_.size();}
        bool empty() const {return !(data_.size()>0);}
        std::vector<int> data() const{return data_;}
        int operator[](int ind){
            return data_[ind];
        }
        std::vector<int>::const_iterator begin() const {
            return data_.begin();
        }
        std::vector<int>::const_iterator cbegin () const {
            return data_.cbegin();
        }
        std::vector<int>::const_iterator cend() const {
            return data_.cend();
        }
          std::vector<int>::const_iterator end() const {
            return data_.cend();
        }


    private:
        void histogram(const cv::Mat &descriptors,  BowDictionary &dictionary) ;
        std::vector<int> data_;


};
}

#endif