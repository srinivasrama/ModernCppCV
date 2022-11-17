#include "codebook.h"

namespace ipb {

cv::Mat kMeans(const std::vector<cv::Mat> &descriptors, int k, int max_iter) {
  // 1. Given cluster centroids i initialized randomly
  std::vector<cv::Mat> centroids;
  centroids.reserve(k);
  for (int i=0;i<k;i++) {
    int ind= rand()% descriptors.size();
    cv::Mat descriptor_depth;//(descriptors[0].size(), CV_64FC1, cv::Scalar(0.0));
    descriptors[ind].convertTo(descriptor_depth,CV_64FC1);
    centroids.emplace_back(descriptor_depth);
  }
  // 2. For iteration t=1..T
  std::map<int, std::vector<cv::Mat>> clusters;
  for (int i = 0; i < max_iter; i++) {
    for (const auto &descriptor : descriptors) {
      // 1. Compute the distance from each point x to each cluster
      // centroid
      float distance_min = 0;
      const float *descriptor_ptr = descriptor.ptr<float>(0);
      const float *centroid_ptr = centroids[0].ptr<float>(0);
      for (int i = 0; i < descriptor.cols; i++)
        distance_min += (descriptor_ptr[i] - centroid_ptr[i]) *
                        (descriptor_ptr[i] - centroid_ptr[i]);
      int centroid_id = 0;
      for (int j = 1; j < k; j++) {
        auto centroid = centroids[j];
        float current_distance = 0.;
        const float *a_ptr = descriptor.ptr<float>(0);
        const float *b_ptr = centroid.ptr<float>(0);
        for (int i = 0; i < descriptor.cols; i++)
          current_distance += (a_ptr[i] - b_ptr[i]) * (a_ptr[i] - b_ptr[i]);
        // 2. Assign each point to the centroid it is closest to
        if (current_distance - distance_min < 0) {
          distance_min = current_distance;
          centroid_id = j;
        }
      }
      clusters[centroid_id].push_back(descriptor);
    }
    //3. Reassign centroids 
    for (auto const& x : clusters){
      auto cluster_= x.second;  
      cv::Mat acc(descriptors[0].size(), CV_64FC1, cv::Scalar(0.0));
      for(const auto &c: cluster_){
          cv::accumulate(c,acc);
      }
      cv::Mat avg(centroids[0].size() ,CV_64FC1); 
      acc.convertTo(avg, CV_64FC1, 1.0/cluster_.size()*1.0);
      centroids[x.first]= avg;
    }
  }
  //stack k centroids into one multidimensional cv::Mat  
  cv::Mat out(0,descriptors[0].size().width, CV_64FC1);
  for(const auto &centroid: centroids){
  cv::vconcat(out, centroid, out);
  }
  return out;
}

}; // namespace igg
// cv::Mat GetAllFeatures() {
//   // init some parameters
//   const int rows_num = 1;
//   const int cols_num = 10;
//   cv::Mat data;

//   for (int i = 0; i < 100; i += 20) {
//     for (size_t j = 0; j < 5; j++) {
//       data.push_back(cv::Mat_<float>(rows_num, cols_num, i));
//     }
//   }

//   return data;
// }

// int main(){
//   const int rows_num = 1;
//   const int cols_num = 10;
//   static std::vector<cv::Mat> data;

//   for (int i = 0; i < 100; i += 20) {
//     for (size_t j = 0; j < 5; j++) {
//       data.push_back(cv::Mat_<float>(rows_num, cols_num, i));
//     }
//   }
//   const int iterations = 10;
//   auto gt= GetAllFeatures();
//   auto centroids = ipb::kMeans(data, gt.rows, iterations);
//   return 0;
// }