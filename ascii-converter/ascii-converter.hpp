#pragma once

#include <cassert>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <format>

#include <opencv2/core/hal/interface.h>
#include <opencv2/core/types.hpp>
#include <opencv2/opencv.hpp>

class AAscii_Converter
{
public:
    explicit AAscii_Converter(cv::Mat& base_image);
    ~AAscii_Converter() = default;
    
    void Resize_Image_By_Width(const std::int32_t width);
    void Convert_Image_To_Ascii();
    void Save_Image_To_File(const std::filesystem::path& path);
    
    const cv::Mat& Get_Ascii_Image() const noexcept;

private:
    std::size_t Map_Values(const float old_value, const float old_value_min, const float old_value_max, const float new_min, const float new_max);
    void Create_Look_Up_Table();

private:
    cv::Mat& Base_Image;
    cv::Mat Ascii_Image;
    cv::Mat Look_Up_Table;
    std::array<uchar, 10> Ascii_Art_Symbols;
};
