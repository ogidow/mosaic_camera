//
//  main.cpp
//  opencv_test
//
//  Created by usr0600438 on 2016/04/22.
//  Copyright © 2016年 usr0600438. All rights reserved.
//
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <string>
#include <vector>

int main(int argc, const char * argv[])
{
    
    cv::Mat image;
    cv::VideoCapture cap(0);
    if (!cap.isOpened()){
        std::cout << "faild open camera" << std::endl;
        return 0;
    }
    
    cv::namedWindow("camera");
    
    cv::Mat gray_image;
    
    std::string cascade_name = "/usr/local/Cellar/opencv3/3.1.0_3/share/OpenCV/haarcascades/haarcascade_eye.xml";
    cv::CascadeClassifier cascade;
    std::vector<cv::Rect> eyes;
    if(!cascade.load(cascade_name)) {
        std::cout << "faild open cascade file" << std::endl;
        return 0;
    }
    
    
    while (1){
        cap >> image;
        
        cv::cvtColor(image, gray_image, CV_BGR2GRAY);
        
        cascade.detectMultiScale(gray_image, eyes, 1.1, 3, CV_HAAR_SCALE_IMAGE, cv::Size(10, 10));
        
        for (const auto& r : eyes) {
            // mosaic filter
            const double f = 0.05;
            cv::Mat tmp;
            cv::resize(image(r), tmp, {}, f, f);
            cv::resize(tmp, image(r), r.size(), 0, 0, cv::INTER_NEAREST);
            // draw area border
            cv::rectangle(image, r.tl(), r.br(), {0,0,0});
        }
        /*
        for (std::vector<cv::Rect>::iterator it = eyes.begin(); it != eyes.end(); it++){
            cv::rectangle(image, *it, cv::Scalar(255, 0, 0), 1);
            
        }*/
        
        
        
        
        cv::imshow("camera", image);
        
        if (cv::waitKey(30) == 'q') break;
        
        
    }
    
    
}
