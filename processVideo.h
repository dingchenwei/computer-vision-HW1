//
//  playVideo.hpp
//  OpenCV
//
//  Created by 丁晨炜 on 16/11/24.
//  Copyright © 2016年 zju. All rights reserved.
//

#ifndef playVideo_hpp
#define playVideo_hpp

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>
class processVideo{
public:
    void resizeVideo(cv::VideoCapture& Srcvideo, cv::VideoWriter& dstVideo, int videoWidth, int videoHeight);  //用作剪裁视频
//    void mergeVideos(cv::VideoCapture &src1, cv::VideoCapture &src2, cv::VideoWriter &dst);  //用作合并视频
};

#endif /* playVideo_hpp */
