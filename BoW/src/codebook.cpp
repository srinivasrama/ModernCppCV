#include "codebook.h"

namespace ipb {

cv::Mat kMeans(const std::vector<cv::Mat> &descriptors, int k, int max_iter) {
  // 1. Given cluster centroids i initialized randomly
  std::vector<cv::Mat> centroids;
  centroids.reserve(k);
  for (int i = 0; i < k; i++) {
    int ind = rand() % descriptors.size();
    cv::Mat
        descriptor_depth; //(descriptors[0].size(), CV_64FC1, cv::Scalar(0.0));
    descriptors[ind].convertTo(descriptor_depth, CV_64FC1);
    centroids.emplace_back(descriptor_depth);
  }
  // 2. For iteration t=1..T
  std::map<int, std::vector<cv::Mat>> clusters;
  for (int i = 0; i < max_iter; i++) {
    for (const auto &descriptor : descriptors) {
      cv::Mat
        descriptor_depth;
      descriptor.convertTo(descriptor_depth, CV_64FC1);

      float distance_min= cv::norm(descriptor_depth, centroids[0], cv::NORM_L2SQR); 
      int centroid_id = 0;
      // 1. Compute the distance from each point x to each cluster
      // centroid
      for (int j = 1; j < k; j++) {
        auto centroid = centroids[j];
        float current_distance= cv::norm(descriptor_depth, centroids[j], cv::NORM_L2SQR); 
        if (current_distance - distance_min < 0) {
          distance_min = current_distance;
          centroid_id = j;
        }
      }
      // 2. Assign each point to the centroid it is closest to
      clusters[centroid_id].push_back(descriptor);
    }
    // 3. Reassign centroids
    for (auto const &x : clusters) {
      auto cluster_ = x.second;
      cv::Mat acc(descriptors[0].size(), CV_64FC1, cv::Scalar(0.0));
      for (const auto &c : cluster_) {
        cv::accumulate(c, acc);
      }
      cv::Mat avg(centroids[0].size(), CV_64FC1);
      acc.convertTo(avg, CV_64FC1, 1.0 / cluster_.size() * 1.0);
      centroids[x.first] = avg;
    }
  }
  // stack k centroids into one multidimensional cv::Mat
  cv::Mat out(0, descriptors[0].size().width, CV_64FC1);
  for (const auto &centroid : centroids) {
    cv::vconcat(out, centroid, out);
  }
  return out;
}

}; // namespace ipb
cv::Mat Get2Kmeans() {
  // init some parameters
  const int rows_num = 1;
  const int cols_num = 10;
  cv::Mat data;

  data.push_back(cv::Mat_<float>(rows_num, cols_num, 20.000002F));
  data.push_back(cv::Mat_<float>(rows_num, cols_num, 70.0F));

  return data;
}


int main(){
  const int rows_num = 1;
  const int cols_num = 10;
  static std::vector<cv::Mat> data;

  for (int i = 0; i < 100; i += 20) {
    for (size_t j = 0; j < 5; j++) {
      data.push_back(cv::Mat_<float>(rows_num, cols_num, i));
    }
  }
  const int iterations = 10;
  auto gt= Get2Kmeans();
  auto centroids = ipb::kMeans(data, gt.rows, iterations);
  
  return 0;
}