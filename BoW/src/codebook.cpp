#include "codebook.h"

namespace ipb {

cv::Mat kMeans(const std::vector<cv::Mat> &descriptors, int k, int max_iter) {
  // 1. Given cluster centroids i initialized randomly
  std::vector<cv::Mat> centroids;
  centroids.reserve(k);
  int ind = rand() % descriptors.size();
  cv::Mat descriptor_depth;
  descriptors[ind].convertTo(descriptor_depth, CV_64FC1);
  centroids.emplace_back(descriptor_depth);
  
  while(centroids.size()<k){
    auto last_centroid= centroids.back();
    cv::Mat last_cent;
    last_centroid.convertTo(last_cent, CV_64FC1);
    
    float distance_max= std::numeric_limits<float>::min();
    cv::Mat choose_one;
    float distance=0.;
    for(int i=0;i<descriptors.size();++i){
        cv::Mat descriptor_depth;
        descriptors[i].convertTo(descriptor_depth, CV_64FC1);
        distance+= cv::norm(descriptor_depth, last_cent, cv::NORM_L2SQR);
        if(distance-distance_max>0) {
          distance_max= distance;
          choose_one= descriptor_depth;
        }
    }
    centroids.emplace_back(choose_one);

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
      clusters[centroid_id].push_back(descriptor_depth);
    }
    // 3. Reassign centroids
    for (auto const &x : clusters) {
      auto cluster_ = x.second;
      cv::Mat acc(descriptors[0].size(), CV_64FC1, cv::Scalar(0.0));
      for (const auto &c : cluster_) {
        cv::accumulate(c, acc);
      }
      cv::Mat avg(descriptors[0].size(), CV_64FC1);
      acc.convertTo(avg, CV_64FC1);
      centroids[x.first] = acc/cluster_.size()*1.;
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
  auto gt= Get5Kmeans();
  auto centroids = ipb::kMeans(data, gt.rows, iterations);
    cv::sort(centroids, centroids, cv::SORT_EVERY_COLUMN + cv::SORT_ASCENDING);
  std::cout << "M = " << std::endl << " "  << centroids << std::endl << std::endl;
  std::cout << "GT = " << std::endl << " "  << gt << std::endl << std::endl;
  std::cout << "end" <<std::endl;
  return 0;
}