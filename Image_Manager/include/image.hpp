#ifndef IMAGE_HPP_
#define IMAGE_HPP_
#include <vector>
#include <string>
#include "io_tools.hpp"
using mat = std::vector<int>;

namespace igg{
    class Image{
        public:
        //constructors
            Image() = default;
            Image(int rows, int cols){
                rows_=rows;
                cols_=cols;
                data_.reserve(rows*cols);
            };
            Image(Image &&var) = default;
            Image(const Image &var) = default;
            Image& operator=(Image&& var) = default;
            Image& operator=(Image& var) = default;

        //getters
        const int& rows() const{
            return rows_;
            }
        const int& cols() const{
            return cols_;
            }
        //pixels access from image
        //TODO: document function
        inline const int& at(const int &row,const int &col) const { return data_[row*cols_+col];}
        //pixels modified
        //TODO: document function
        inline int& at(const int &row,const int &col)  { return data_[row*cols_+col];}
        
        //TODO: read image from pgm file
        bool FillFromPgm(const std::string& file_name);

        //TODO: write image object to file
        void WriteToPgm_(const std::string& file_name);

        // void DownScale(int scale);
        
        // void UpScale(int scale);
         
        std::vector<float> ComputeHistogram(int bins) const;
        private:
            int rows_=0;
            int cols_=0;
            mat data_;
            
    };

};
#endif