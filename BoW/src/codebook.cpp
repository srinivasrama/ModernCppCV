#include "codebook.h"

namespace ipb {
std::vector<cv::Mat>
getInitialClusterCenters(const std::vector<cv::Mat> &descriptors, int k) {
  std::vector<cv::Mat> centroids;
  centroids.reserve(k);
  int ind = rand() % descriptors.size();
  centroids.emplace_back(descriptors[ind]);
  std::set<int> inds;
  inds.insert(ind);
  while (centroids.size() < k) {
    int ind_;
    while (true) {
      ind_ = rand() % descriptors.size();
      const bool is_in = inds.find(ind_) != inds.end();
      if (!is_in)
        break;
    }
    inds.insert(ind_);
    centroids.emplace_back(descriptors[ind_]);
  }
  return centroids;
}

void assignToClusters(const std::vector<cv::Mat> &descriptors,
                      const std::vector<cv::Mat> &centroids,
                      std::map<int, std::vector<cv::Mat>> &clusters) {
  for (const auto &descriptor : descriptors) {
    float distance_min = std::numeric_limits<float>::max();
    int centroid_id = std::numeric_limits<int>::max();
    // 1. Compute the distance from each point x to each cluster
    // centroid
    for (int j = 0; j < centroids.size(); j++) {
      auto centroid = centroids[j];
      float current_distance = cv::norm(centroid, descriptor, cv::NORM_L2SQR);
      if (current_distance - distance_min < 0) {
        distance_min = current_distance;
        centroid_id = j;
      }
    }
    // 2. Assign each point to the centroid it is closest to
    clusters[centroid_id].push_back(descriptor);
  }
}

void recomputeCenters(std::vector<cv::Mat> &centroids,
                      const std::map<int, std::vector<cv::Mat>> &clusters) {
  // 3. Reassign centroids
  for (auto const &x : clusters) {
    auto cluster_ = x.second;
    cv::Mat acc(centroids[0].size(), CV_64FC1, cv::Scalar(0.0));
    for (const auto &c : cluster_) {
      cv::accumulate(c, acc);
    }

    centroids[x.first] = acc / static_cast<float>(cluster_.size());
  }
}
cv::Mat kMeans(const std::vector<cv::Mat> &descriptors, int k, int max_iter) {
  // 1. Given cluster centroids i initialized randomly
  std::vector<cv::Mat> descriptors_d;
  for (auto descriptor : descriptors) {
    cv::Mat desc;
    descriptor.convertTo(desc, CV_64FC1);
    descriptors_d.emplace_back(desc);
  }

  auto centroids = getInitialClusterCenters(descriptors_d, k);
  // 2. For iteration t=1..T
  std::map<int, std::vector<cv::Mat>> clusters;
  for (int i = 0; i < max_iter; i++) {
    // 2.1 assign clusters
    assignToClusters(descriptors_d, centroids, clusters);
    // 3. Reassign centroids
    recomputeCenters(centroids, clusters);
  }
  // stack k centroids into one multidimensional cv::Mat
  cv::Mat out(0, centroids[0].size().width, CV_64FC1);
  for (const auto &centroid : centroids) {
    cv::vconcat(out, centroid, out);
  }
  return out;
}

}; // namespace ipb