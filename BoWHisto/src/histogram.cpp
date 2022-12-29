#include "histogram.h"

namespace ipb {

Histogram::Histogram(const cv::Mat &descriptors, BowDictionary &dictionary) {
  histogram(descriptors, dictionary);
}
void Histogram::histogram(const cv::Mat &descriptors,
                          BowDictionary &dictionary) {
  if(descriptors.size().height==0) return;
  data_.reserve(dictionary.size());
  for (int i = 0; i < data_.capacity(); i++) {
    data_.push_back(0.);
  }
  static cv::flann::Index flann_index(dictionary.vocabulary(),
                                      cv::flann::KDTreeIndexParams(1));
  unsigned int max_neighbours = 10;
  cv::Mat indices, dists; // neither assume type nor size here !
  double radius =10.0;
  for (int i = 0; i < descriptors.rows; ++i) {
    flann_index.radiusSearch(descriptors.row(i), indices, dists, radius,
                             max_neighbours, cv::flann::SearchParams(32));
    std::cout << indices <<std::endl;
    data_[indices.at<int>(0, 0)] += 1;
  }
}

Histogram Histogram::ReadFromCSV(const std::string &file) {
  std::ifstream ifs{file};
  std::vector<int> data;
  for (std::string line; std::getline(ifs, line, ',');) {
    data.push_back(stoi(line));
  }
  return Histogram(data);
}

void Histogram::WriteToCSV(const std::string &file) const {
  std::ofstream myfile;
  myfile.open(file);
  for (int i = 0; i < data_.size() - 1; i++) {
    myfile << data_[i] << ",";
  }
  myfile << data_[data_.size() - 1];
  myfile.close();
}

} // namespace ipb