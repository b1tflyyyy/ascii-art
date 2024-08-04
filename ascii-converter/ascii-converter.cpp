#include "ascii-converter.hpp"

AAscii_Converter::AAscii_Converter(cv::Mat& base_image) :
    Base_Image{ base_image }, 
    Ascii_Image(base_image.size(), CV_8U, cv::Scalar(0)),
    Look_Up_Table(1, 256, CV_8U, cv::Scalar(0)),
    Ascii_Art_Symbols{ '.', '-', '=', '*', ':', 'o', '&', '8', '#', '@' }
{  
    CV_Assert(Base_Image.isContinuous());
    CV_Assert(Base_Image.type() == CV_8U);
    CV_Assert(!Base_Image.empty());

    Create_Look_Up_Table();
}

void AAscii_Converter::Resize_Image_By_Width(const std::int32_t width)
{
    if (!width)
    {
        return;
    }
    
    const auto base_image_size{ Base_Image.size() };
    const auto resized_height{ static_cast<std::int32_t>(base_image_size.height * width / base_image_size.width) };

    if (base_image_size.width > width || base_image_size.height > resized_height)
    { 
        cv::Mat tmp{}; 
        cv::resize(Base_Image, tmp, cv::Size{ width, resized_height });
        
        Base_Image = tmp;   
    }
}

void AAscii_Converter::Convert_Image_To_Ascii()
{
    cv::LUT(Base_Image, Look_Up_Table, Ascii_Image);
}

void AAscii_Converter::Save_Image_To_File(const std::filesystem::path& path)
{
    std::ofstream fout{ path.native(), std::ios::out | std::ios::trunc };
    if (!fout.is_open())
    {
        throw std::runtime_error{ std::format("can not open file: {}", path.native()) };
    }
 
    const uchar* ascii_ptr{ Ascii_Image.ptr() };
    for (std::size_t i{}; i < Base_Image.rows; ++i)
    {
        for (std::size_t j{}; j < Base_Image.cols; ++j)
        {
            fout << ascii_ptr[i * Base_Image.cols + j];
        }
        fout << '\n';
    }
}

const cv::Mat& AAscii_Converter::Get_Ascii_Image() const noexcept
{
    return Ascii_Image;
}

std::size_t AAscii_Converter::Map_Values(const float old_value, const float old_value_min, const float old_value_max, const float new_min, const float new_max)
{
    return static_cast<std::size_t>(((old_value - old_value_min) / (old_value_max - old_value_min)) * (new_max - new_min) + new_min);
}

void AAscii_Converter::Create_Look_Up_Table()
{
    uchar* ptr{ Look_Up_Table.ptr() };
    for (std::size_t i{}; i < 256; ++i)
    {
        const auto mapped_index{ Map_Values(i, 0, 255, 0, Ascii_Art_Symbols.size() - 1) };
        ptr[i] = Ascii_Art_Symbols[mapped_index];
    }
}


