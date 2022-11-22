#ifndef CODEBOOK_HPP_
#define CODEBOOK_HPP_
#include <map>
#include<set>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <functional>
#include <numeric>
namespace ipb {
/**
 * @brief
 * 1. Given cluster centroids i initialized in some way,
 * 2. For iteration t=1..T:
 * 1. Compute the distance from each point x to each cluster centroid ,
 * 2. Assign each point to the centroid it is closest to,
 * 3. Recompute each centroid as the mean of all points assigned to it,
 *
 * @param descriptors The input SIFT descriptors to cluster.
 * @param k The size of the dictionary, ie, number of visual words.
 * @param max_iterations Maximum number of iterations before convergence.
 * @return cv::Mat One unique Matrix representing all the $k$-means(stacked).
 */
cv::Mat kMeans(const std::vector<cv::Mat> &descriptors, int k,
               int max_iter);


std::vector<cv::Mat> getInitialClusterCenters(const std::vector<cv::Mat> &descriptors, int k);

std::map<int, std::vector<cv::Mat>> assignToClusters(const std::vector<cv::Mat> &descriptors,const std::vector<cv::Mat> &centroids, int k, std::map<int, std::vector<cv::Mat>> &clusters);

void recomputeCenters(std::vector<cv::Mat> &centroids, std::map<int, std::vector<cv::Mat>> clusters);
// class BowDictionary {
// private:
//   // constructor and destructor
//   BowDictionary() = default;
//   ~BowDictionary() = default;

// public:
//   // copy assignment operators
//   BowDictionary(const BowDictionary &var) = delete;
//   void operator=(const BowDictionary &var) = delete;
//   BowDictionary(const BowDictionary &&var) = delete;
//   void operator=(const BowDictionary &&var) = delete;
//   // one time object instance
//   static BowDictionary &GetInstance() {
//     static BowDictionary instance;
//     return instance;
//   }
  
// };
}; // namespace igg
#endif