#pragma once

#include <cassert>
#include <cstdint>
#include <filesystem>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <algorithm>

#include <opencv2/core/hal/interface.h>
#include <opencv2/core/types.hpp>
#include <opencv2/opencv.hpp>

class AAscii_Converter
{
public:
    enum class EOutput_Formatted_Ascii_Image : std::uint8_t
    {
        DEFAULT,
        CALCULATE
    };

public:
    explicit AAscii_Converter();
    ~AAscii_Converter() = default;
    
    void Set_Base_Image(cv::Mat* base_image); 
    
    void Resize_Image(const cv::Size size);
    void Convert_Image_To_Ascii();
    void Save_Image_To_File(const std::filesystem::path& path);
    
    const cv::Mat& Get_Ascii_Image() const noexcept;
    const std::vector<uchar>& Get_Formatted_Output_Ascii_Image(EOutput_Formatted_Ascii_Image action = EOutput_Formatted_Ascii_Image::CALCULATE);

private:
    inline std::size_t Map_Values(const float old_value, const float old_value_min, const float old_value_max, const float new_min, const float new_max);
    void Create_Look_Up_Table();
    void Calculate_Formatted_Output_Ascii_Image();

private:
    cv::Mat* Base_Image;
    cv::Mat Ascii_Image;
    cv::Mat Look_Up_Table;
    std::vector<uchar> Formatted_Output_Ascii_Image;
    std::array<uchar, 10> Ascii_Art_Symbols;
};
