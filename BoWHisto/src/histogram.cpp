#include "histogram.h"
#include <iostream>

namespace ipb {

Histogram::Histogram(const cv::Mat &descriptors,
                      BowDictionary &dictionary) {
histogram(descriptors, dictionary);                        
                     }
void Histogram::histogram(const cv::Mat &descriptors,
                                      BowDictionary &dictionary) {
  data_.reserve(dictionary.size());
  for(int i=0;i<data_.capacity();i++){
    data_.push_back(0.);
  }
  static cv::flann::Index flann_index(dictionary.vocabulary(), cv::flann::KDTreeIndexParams(1));
  unsigned int max_neighbours = 10;
  cv::Mat indices, dists; //neither assume type nor size here !
  double radius= 2.0;
  for(int i=0;i< descriptors.rows;++i){
    flann_index.radiusSearch(descriptors.row(i), indices, dists, radius, max_neighbours,
        cv::flann::SearchParams(32));
    data_[indices.at<int>(0,0)]+=1;
  }       
}
} // namespace ipb
cv::Mat Get5Kmeans() {
  // init some parameters
  const int rows_num = 1;
  const int cols_num = 10;
  cv::Mat data;

  for (int i = 0; i < 100; i += 20) {
    cv::Mat_<float> vec(rows_num, cols_num, i);
    data.push_back(vec);
  }

  return data;
}

cv::Mat GetAllFeatures() {
  // init some parameters
  const int rows_num = 1;
  const int cols_num = 10;
  cv::Mat data;

  for (int i = 0; i < 100; i += 20) {
    for (size_t j = 0; j < 5; j++) {
      data.push_back(cv::Mat_<float>(rows_num, cols_num, i));
    }
  }

  return data;
}

int main(){
    auto& dictionary = ipb::BowDictionary::GetInstance();
    dictionary.set_vocabulary(Get5Kmeans());
    auto histogram_ = ipb::Histogram(GetAllFeatures(), dictionary);
    for(auto it=histogram_.begin();it<histogram_.end();it++){
        std::cout<<"i="<<*it<<std::endl;
    }
    return 0;
}