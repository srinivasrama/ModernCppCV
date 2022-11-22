#include "codebook.h"

namespace ipb {
std::vector<cv::Mat> getInitialClusterCenters(const std::vector<cv::Mat> &descriptors, int k){
std::vector<cv::Mat> centroids;
  centroids.reserve(k);
  int ind = rand() % descriptors.size();
  cv::Mat descriptor_depth;
  descriptors[ind].convertTo(descriptor_depth, CV_64FC1);
  centroids.emplace_back(descriptor_depth);

  while(centroids.size()<k){
    std::vector<double> distances;
    for (const auto &descriptor: descriptors){
        double distance_min= std::numeric_limits<float>::max();
        for(const auto &centroid: centroids){
            cv::Mat descriptor_depth_;
            descriptor.convertTo(descriptor_depth_, CV_64FC1);
            cv::Mat centroid_;
            centroid.convertTo(centroid_, CV_64FC1);
            distance_min= std::min(distance_min,cv::norm(descriptor_depth_, centroid_, cv::NORM_L2SQR));
        }
        distances.emplace_back(distance_min);
    }
    centroids.emplace_back(descriptors[std::distance(distances.begin(), std::max_element(distances.begin(), distances.begin() + distances.size()))]);  
  }
  return centroids;
}

void assignToClusters(const std::vector<cv::Mat> &descriptors,const std::vector<cv::Mat> &centroids,int k, std::map<int, std::vector<cv::Mat>> &clusters ){
  for (const auto &descriptor : descriptors) {
      cv::Mat descriptor_depth;
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
}

void recomputeCenters(std::vector<cv::Mat> &centroids, const std::map<int, std::vector<cv::Mat>> &clusters){
    // 3. Reassign centroids
    for (auto const &x : clusters) {
      auto cluster_ = x.second;
      cv::Mat acc(centroids[0].size(), CV_64FC1, cv::Scalar(0.0));
      for (const auto &c : cluster_) {
        cv::accumulate(c, acc);
      }

      cv::Mat avg(centroids[0].size(), CV_64FC1);
      acc.convertTo(avg, CV_64FC1);

      centroids[x.first] = acc/cluster_.size()*1.;

    }
}
cv::Mat kMeans(const std::vector<cv::Mat> &descriptors, int k, int max_iter) {
  // 1. Given cluster centroids i initialized randomly
  auto centroids= getInitialClusterCenters(descriptors,k);
  // 2. For iteration t=1..T
  std::map<int, std::vector<cv::Mat>> clusters;
  for (int i = 0; i < max_iter; i++) {
    //2.1 assign clusters
    assignToClusters(descriptors,centroids, k, clusters );
    // 3. Reassign centroids
    recomputeCenters(centroids,  clusters);
  }
  // stack k centroids into one multidimensional cv::Mat
  cv::Mat out(0, centroids[0].size().width, CV_64FC1);
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
  // auto centroids = ipb::kMeans(data, gt.rows, iterations);
  auto centroids= ipb::getInitialClusterCenters(data,gt.rows);
  // cv::sort(centroids, centroids, cv::SORT_EVERY_COLUMN + cv::SORT_ASCENDING);
  for(const auto &centroid: centroids){
    std::cout << "M = " << std::endl << " "  << centroid << std::endl << std::endl;
  }
  // std::cout << "GT = " << std::endl << " "  << gt << std::endl << std::endl;
  std::cout << "end" <<std::endl;
  return 0;
}