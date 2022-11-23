#ifndef BOWDIC_HPP_
#define BOWDIC_HPP_
#include <algorithm>
#include <functional>
#include <map>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <random>
#include <set>
#include <string>
#include <vector>

namespace ipb {
class BowDictionary {
private:
  // constructor and destructor
  BowDictionary() = default;
  ~BowDictionary() = default;
  int n_iter_ = 0;
  int k_ = 0;
  std::vector<cv::Mat> descriptors_;
  cv::Mat codebook_;

public:
  // copy assignment operators
  BowDictionary(const BowDictionary &var) = delete;
  void operator=(const BowDictionary &var) = delete;
  BowDictionary(const BowDictionary &&var) = delete;
  void operator=(const BowDictionary &&var) = delete;
  // one time object instance
  static BowDictionary &GetInstance() {
    static BowDictionary instance;
    return instance;
  };

  // getter methods
  int max_iterations() const { return n_iter_; };
  int size() const{return descriptors_.size();}; // number of centroids/ code words
  std::vector<cv::Mat> descriptors() const { return descriptors_; };
  cv::Mat vocabulary() const { return codebook_; };
  int total_features() const {
    return descriptors_.size();
  }; // number of input features
  bool empty() const { return !(descriptors_.size() > 0); };
  // setter methods
  void set_max_iterations(int iter_) { n_iter_ = iter_; }
  void set_size(int n) { descriptors_.resize(n); }
  void set_descriptors(const std::vector<cv::Mat> &input);
  void set_params(int n_iter, int size, std::vector<cv::Mat> descriptors);
};
} // namespace ipb
#endif