#include <ascii-converter.hpp>
#include <bfl-perf-timer.hpp>
#include <cassert>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

int main()
{
    cv::Mat image{ cv::imread("skull.jpg", cv::IMREAD_GRAYSCALE) };
    AAscii_Converter ascii_converter{};
    
    ascii_converter.Set_Base_Image(&image);
    ascii_converter.Resize_Image(cv::Size{ 500, 500 });

    {
        bfl::auto_perf_timer<> timer{ std::cout };
        for (std::size_t i{}; i < 1'000; ++i)
        {
            ascii_converter.Convert_Image_To_Ascii();
        }
    }

    {
        bfl::auto_perf_timer<> timer{ std::cout };
        for (std::size_t i{}; i < 1'000; ++i)
        {
            ascii_converter.Get_Formatted_Output_Ascii_Image(AAscii_Converter::EOutput_Formatted_Ascii_Image::CALCULATE);
        }
    }
    
    std::cout << std::data(ascii_converter.Get_Formatted_Output_Ascii_Image(AAscii_Converter::EOutput_Formatted_Ascii_Image::DEFAULT));

    return 0;
}
