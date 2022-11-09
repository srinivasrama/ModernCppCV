#include "image.hpp"
#include <iostream>
namespace igg {

bool Image::FillFromPgm(const std::string &file_name) {
  io_tools::ImageData img_data = io_tools::ReadFromPgm(file_name);
  if (img_data.data.empty()) {
    return false;
  }
  for (int i = 0; i < img_data.data.size(); i++) {
    data_.push_back(img_data.data.at(i));
  }
  rows_=img_data.rows;
  cols_=img_data.cols;
  return true;
}

void Image::WriteToPgm_(const std::string& file_name){
 io_tools::ImageData image_data;
    image_data.rows=rows_;
    image_data.cols=cols_;
    image_data.data=data_;
    image_data.max_val=255;
    if(image_data.data.empty()) return;
    io_tools::WriteToPgm(image_data, file_name);
}
std::vector<float> Image::ComputeHistogram(int bins) const{
      float interval= 255./bins;
      std::vector<float> histo(bins,0.);
      for(const auto &pixel: data_){
        float histo_val_prev=0.;
        for(int i=0;i<bins;i++){
          float histo_val_current= (i+1)*1.*interval;
          if(pixel-histo_val_prev>=0 && pixel-histo_val_current<=0) histo[i]+=1./data_.size();
          histo_val_prev= histo_val_current;
        }
      }
      return histo;
}
// void Image::DownScale(int scale){

// }
} // namespace igg

int main() { 
  
  igg::Image image;
  image.FillFromPgm("/home/bruno/Learning/ModernCppCV/Image_Manager/tests/data/dummy_file.pgm");
  const auto& image_ref = image;
  auto histogram = image_ref.ComputeHistogram(10);
  std::cout << "SIZE=" << histogram.size() << std::endl;
  std::cout << "value=" << histogram[0] << std::endl;
  std::cout << "value=" << histogram[9] << std::endl;
  return 0;
   }