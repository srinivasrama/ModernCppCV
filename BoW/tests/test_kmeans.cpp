#include <gtest/gtest.h>

#include <opencv2/core/types.hpp>
#include <opencv2/opencv.hpp>

#include "homework_7.h"
#include "test_data.hpp"
#include "test_utils.hpp"
using namespace std;
using namespace cv;

void TestKMeans(const cv::Mat& gt_cluster) {
  const auto& data = GetDummyData();
    cv::Mat out(0., 10, CV_32FC1);
  for (const auto &centroid : data) {
    cv::vconcat(out, centroid, out);
  }


  const int dict_size = gt_cluster.rows;
  const int iterations = 10;

   int K = dict_size;
    cv::Mat bestLabels, centers, clustered;
    cv::kmeans(out, K, bestLabels,
            TermCriteria(cv::TermCriteria::MAX_ITER +
                cv::TermCriteria::EPS,10,0.001),
            10, KMEANS_PP_CENTERS, centers);
  auto centroids = ipb::kMeans(data, dict_size, iterations);
  EXPECT_EQ(centroids.rows, dict_size);
  EXPECT_EQ(centroids.size, gt_cluster.size);


  // Need to sort the output, otherwise the comparison will fail
  cv::sort(centroids, centroids, cv::SORT_EVERY_COLUMN + cv::SORT_ASCENDING);
   cv::sort(centers, centers, cv::SORT_EVERY_COLUMN + cv::SORT_ASCENDING);
  std::cout<<"CENTROIDS"<<centers<<std::endl;

  EXPECT_TRUE(mat_are_equal<float>(centroids, gt_cluster))
      << "gt_centroids:\n"
      << gt_cluster << "\ncomputed centroids:\n"
      << centroids;
}


TEST(KMeansCluster, SelectAllFeatures) { TestKMeans(GetAllFeatures()); }

TEST(KMeansCluster, Use2Words) { TestKMeans(Get2Kmeans()); }
TEST(KMeansCluster, Use3Words) { TestKMeans(Get3Kmeans()); }
TEST(KMeansCluster, MinimumSignificantCluster) { TestKMeans(Get5Kmeans()); }
TEST(KMeansCluster, MoreLabelsThanFeatures) { TestKMeans(Get18Kmeans()); }