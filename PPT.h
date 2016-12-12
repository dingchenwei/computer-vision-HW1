//
//  ppt.h
//  OpenCV
//
//  Created by 丁晨炜 on 16/11/24.
//  Copyright © 2016年 zju. All rights reserved.
//

#ifndef _EFFECT_H_
#define _EFFECT_H_

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>

#define IMG_WIDTH 600
#define IMG_HEIGHT 450

class PPT {
public:
    
    void start(IplImage* dst, IplImage* img1, IplImage* img2, int effect_kind, cv::VideoWriter& convertPPTToVideo);
    
private:
    //百叶窗
    void shutters(IplImage* dst, IplImage* img1, IplImage* img2, cv::VideoWriter convertPPTToVideo);
    //向左平移
    void moveLeft(IplImage* dst, IplImage* img1, IplImage* img2, cv::VideoWriter convertPPTToVideo);
    //向右平移
    void moveRight(IplImage* dst, IplImage* img1, IplImage* img2, cv::VideoWriter convertPPTToVideo);
};

#endif // _EFFECT_H_
