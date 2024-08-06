#include "ascii-converter.hpp"

AAscii_Converter::AAscii_Converter() :
    Base_Image{ nullptr }, 
    Ascii_Image{},
    Look_Up_Table(1, 256, CV_8U, cv::Scalar::all(0)),
    Formatted_Output_Ascii_Image{},
    Ascii_Art_Symbols{ '.', '-', '=', '*', ':', 'o', '&', '8', '#', '@' }
{  
    Create_Look_Up_Table();
}

void AAscii_Converter::Set_Base_Image(cv::Mat* base_image)
{
    if (!base_image)
    {
        throw std::runtime_error{ "base_image == nullptr !" };
    }

    CV_Assert(base_image->isContinuous());
    CV_Assert(base_image->type() == CV_8U);
    CV_Assert(base_image->channels() == 1);
    CV_Assert(!base_image->empty());

    Base_Image = base_image;
    Ascii_Image.reserveBuffer(static_cast<std::size_t>(Base_Image->rows) * static_cast<std::size_t>(Base_Image->cols));
}

void AAscii_Converter::Resize_Image(const cv::Size size)
{
    cv::Mat tmp{}; 
    cv::resize(*Base_Image, tmp, size);

    *Base_Image = tmp;
}

void AAscii_Converter::Convert_Image_To_Ascii()
{
    cv::LUT(*Base_Image, Look_Up_Table, Ascii_Image);
}

void AAscii_Converter::Save_Image_To_File(const std::filesystem::path& path)
{
    std::ofstream fout{ path.native(), std::ios::out | std::ios::trunc };
    if (!fout.is_open())
    {
        throw std::runtime_error{ std::format("can not open file: {}", path.native()) };
    }
 
    const uchar* ascii_ptr{ Ascii_Image.ptr() };
    for (std::size_t i{}; i < Base_Image->rows; ++i)
    {
        for (std::size_t j{}; j < Base_Image->cols; ++j)
        {
            fout << ascii_ptr[i * Base_Image->cols + j];
        }
        fout << '\n';
    }
}

const cv::Mat& AAscii_Converter::Get_Ascii_Image() const noexcept
{
    return Ascii_Image;
}

const std::vector<uchar>& AAscii_Converter::Get_Formatted_Output_Ascii_Image(EOutput_Formatted_Ascii_Image action)
{
    if (action == EOutput_Formatted_Ascii_Image::CALCULATE)
    {
        Calculate_Formatted_Output_Ascii_Image();
    }

    return Formatted_Output_Ascii_Image;
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

void AAscii_Converter::Calculate_Formatted_Output_Ascii_Image()
{
    Formatted_Output_Ascii_Image.clear();

    // +1 for '\n' and for '\0'
    Formatted_Output_Ascii_Image.reserve(static_cast<std::size_t>(Ascii_Image.cols + 1) * static_cast<std::size_t>(Ascii_Image.rows) + 1);

    const uchar* ascii_image_ptr{ Ascii_Image.ptr() };
    for (std::size_t i{}; i < Ascii_Image.rows; ++i)
    {
        for (std::size_t j{}; j < Ascii_Image.cols; ++j)
        {
            Formatted_Output_Ascii_Image.push_back(ascii_image_ptr[i * Ascii_Image.cols + j]);
        } 

        Formatted_Output_Ascii_Image.push_back('\n');
    }
    
    // [..., '\n', '\0'] fix it ?
    Formatted_Output_Ascii_Image.push_back('\0');
}

