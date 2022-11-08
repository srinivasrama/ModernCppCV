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

} // namespace igg

int main() { 
  
  igg::Image image;
  image.FillFromPgm("/home/bruno/Learning/ModernCppCV/Image_Manager/data/lena.ascii.pgm");
  image.WriteToPgm_("/home/bruno/Learning/ModernCppCV/Image_Manager/data/out.ascii.pgm");
  return 0;
   }