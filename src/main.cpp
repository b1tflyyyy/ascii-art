#include <iostream>
#include <ascii-converter.hpp>

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

#define ENABLE_ONLY_IMAGES false

int main(int argc, char** argv)
{
#if ENABLE_ONLY_IMAGES
    if (argc < 2)
    {
        std::cerr << "error: too few  arguments\n";
        return -1; 
    }
    
    cv::Mat image{ cv::imread(argv[1], cv::IMREAD_GRAYSCALE) };
    AAscii_Converter ascii_converter{};
    
    ascii_converter.Set_Base_Image(&image);
    ascii_converter.Resize_Image(cv::Size{ 400, 150 });
    
    ascii_converter.Convert_Image_To_Ascii();
    ascii_converter.Save_Image_To_File("ascii_image.txt");
    
    const auto& formatted_image{ ascii_converter.Get_Formatted_Output_Ascii_Image() };
    std::cout << std::data(formatted_image);

    cv::imshow("base image", image);
    cv::waitKey();
#else
    cv::Mat frame{};

    std::int32_t device_id{ 0 };
    std::int32_t api_id{ cv::CAP_ANY };

    cv::VideoCapture capture{}; 
    capture.open(device_id, api_id);

    if (!capture.isOpened())
    {
        std::cerr << "can not open specified device\n";
        return -1;
    }

    AAscii_Converter ascii_converter{};
    
    for (;;)
    {
        capture.read(frame);
        cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);

        ascii_converter.Set_Base_Image(&frame);
        ascii_converter.Resize_Image(cv::Size{ 500, 155 });
        ascii_converter.Convert_Image_To_Ascii();
        const auto& formatted_image{ ascii_converter.Get_Formatted_Output_Ascii_Image(AAscii_Converter::EOutput_Formatted_Ascii_Image::CALCULATE) };
        std::cout << std::data(formatted_image);
    }

#endif

    return 0;
}
