#include "codebook.h"
#include <opencv2/core/base.hpp>

namespace ipb {
  float euclideanDistance(const cv::Mat &a, const cv::Mat &b) {
    cv::Mat diff;
    cv::absdiff(a, b, diff);
    return cv::sqrt(cv::sum(diff.mul(diff))[0]);
}
std::vector<cv::Mat> getInitialClusterCenters(const std::vector<cv::Mat> &descriptors, int k) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, descriptors.size() - 1);

    std::unordered_map<int, bool> selected;
    std::vector<cv::Mat> centroids;

    while (centroids.size() < k) {
        int index = distribution(gen);
        if (!selected[index]) {
            selected[index] = true;
            centroids.push_back(descriptors[index].clone());
        }
    }
    return centroids;
}

void assignToClusters(const std::vector<cv::Mat> &descriptors,
                      const std::vector<cv::Mat> &centroids,
                      std::map<int, std::vector<cv::Mat>> &clusters) {
  for (const auto &descriptor : descriptors) {
    float distance_min = std::numeric_limits<float>::max();
    int centroid_id =-1;
    // 1. Compute the distance from each point x to each cluster
    // centroid
    for (int j = 0; j < centroids.size(); j++) {
      auto centroid = centroids[j];
      float current_distance = euclideanDistance(centroid,descriptor);
      if (current_distance < distance_min ) {
        distance_min = current_distance;
        centroid_id = j;
      }
    }
    // 2. Assign each point to the centroid it is closest to
    clusters[centroid_id].push_back(descriptor);
  }
}

 std::vector<cv::Mat> recomputeCenters(int k,
                      const std::map<int, std::vector<cv::Mat>> &clusters, const std::vector<cv::Mat> centroids) {
  std::vector<cv::Mat> centroids_out;
  centroids_out.reserve(k);
  // 3. Reassign centroids
  for (int i=0;i<k;i++) {
    auto pos = clusters.find(i);
    if (clusters.count(i)>0){
    auto cluster_ = pos->second;

    cv::Mat acc(cluster_[0].size(), CV_32FC1, cv::Scalar(0.0));
    for (const auto &c : cluster_) {
      cv::accumulate(c, acc);
    }
    centroids_out.push_back(acc /cluster_.size());
    }
    else{
        centroids_out.push_back(centroids[i]);
    }
  }

  return centroids_out;
}
cv::Mat kMeans(const std::vector<cv::Mat> &descriptors, int k, int max_iter) {
  // 1. Given cluster centroids i initialized randomly
  std::vector<cv::Mat> descriptors_d;
  for (const auto &descriptor : descriptors) {
    cv::Mat desc;
    descriptor.convertTo(desc, CV_32FC1);
    descriptors_d.emplace_back(desc);
  }
 std::vector<cv::Mat> centroids;
 const auto centroids_init = getInitialClusterCenters(descriptors_d, k);
 centroids= centroids_init;
  // 2. For iteration t=1..T
  for (int i = 0; i < max_iter; i++) {
    // 2.1 assign clusters
    std::map<int, std::vector<cv::Mat>> clusters;
    assignToClusters(descriptors_d, centroids, clusters);
    // 3. Reassign centroids
    centroids= std::move(recomputeCenters(k, clusters, centroids));
  }
  // stack k centroids into one multidimensional cv::Mat
  cv::Mat out;
  for (const auto &centroid : centroids) {
    out.push_back(centroid);
  }
  return out;
}

}; // namespace ipb