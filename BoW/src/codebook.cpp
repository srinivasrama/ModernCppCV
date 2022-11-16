#include "codebook.h"

namespace ipb {

cv::Mat kMeans(const std::vector<cv::Mat> &descriptors, int k, int max_iter) {
  // 1. Given cluster centroids i initialized randomly
  std::vector<cv::Mat> centroids;
  centroids.reserve(k);
  std::set<int> ids;
  while (ids.size() <= k) {
    int ind = std::rand() % k;
    ids.insert(ind);
  }
  for (const auto &id_ : ids) {
    centroids.emplace_back(descriptors[id_]);
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
    for (int j = 0; j < k; j++) {
      auto cluster= clusters[k];  
      cv::Mat acc(cluster[0].size(), CV_64F, cv::Scalar(0));
      for(const auto &c: cluster){
          cv::accumulate(c,acc);
      }
      cv::Mat avg; 
      acc.convertTo(avg, CV_8U, 1.0/cluster.size());
      centroids[k]= avg;
    }
  }
  //stack k centroids into one multidimensional cv::Mat  
  cv::Mat out;
  cv::merge(centroids, out);
  return out;
}

} // namespace igg
