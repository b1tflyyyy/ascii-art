#include <cstddef>
#include <iostream>
#include <ascii-converter.hpp>

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#include <bfl-perf-timer.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "error: too few  arguments\n";
        return -1; 
    }
    
    cv::Mat image{ cv::imread(argv[1], cv::IMREAD_GRAYSCALE) };
    AAscii_Converter ascii_converter{};
    
    ascii_converter.Set_Base_Image(&image);
    ascii_converter.Resize_Image(cv::Size{ 400, 150 });
    
    { // perf test 
        bfl::auto_perf_timer<> timer{ std::cout };
        for (std::size_t i{}; i < 500; ++i)
        {
            ascii_converter.Convert_Image_To_Ascii();
        }
    }

    ascii_converter.Save_Image_To_File("ascii_image.txt");
    
    const auto& formatted_image{ ascii_converter.Get_Formatted_Output_Ascii_Image() };
    std::cout << std::data(formatted_image);

    cv::imshow("base image", image);
    cv::waitKey();

    return 0;
}
