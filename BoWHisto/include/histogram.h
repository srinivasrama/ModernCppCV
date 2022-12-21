#ifndef HISTOGRAM_HPP_
#define HISTOGRAM_HPP_
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include "bow_dictionary.h"

namespace ipb{
class Histogram{
    public:
        Histogram();
        Histogram(const std::vector<int> &data){
            data_=data;
        };
        Histogram(const std::vector<cv::Mat> &descriptors, const BowDictionary &dictionary){
            
        };

    private:
        std::vector<int> data_;

};
}

#endif