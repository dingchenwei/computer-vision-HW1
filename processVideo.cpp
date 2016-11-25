//
//  playVideo.cpp
//  OpenCV
//
//  Created by 丁晨炜 on 16/11/24.
//  Copyright © 2016年 zju. All rights reserved.
//

#include "processVideo.h"
#include "PPT.h"
//改变视频尺寸
void processVideo::resizeVideo(cv::VideoCapture& srcVideo, cv::VideoWriter& dstVideo, int videoWidth, int videoHeight){
    double count = srcVideo.get(CV_CAP_PROP_FRAME_COUNT);  //获取帧数
    cv::Mat frame;
    cv::Mat temp;  //临时储存尺寸改变后的图像
    CvPoint wordsPosition1;  //视频中字幕的位置
    wordsPosition1.x = 20;
    wordsPosition1.y = IMG_HEIGHT - 20;
    for (int i = 0; i < count; ++i){
        if(srcVideo.read(frame)){  //读取图像
            cv::resize(frame, temp, cv::Size(videoWidth,videoHeight));  //改变图像的尺寸
            cv::putText(frame, "Created by Dingchenwei_3140103310", wordsPosition1, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar::all(255), 1);  //插入字幕
            dstVideo << temp;  //写入目标视频
        }
        else
            std::cout << "frame = null" << std::endl;
    }
    
}

//合并视频
//void processVideo::mergeVideos(cv::VideoCapture &src1, cv::VideoCapture &src2, cv::VideoWriter &dst){
//    cv::Mat frame;
//    CvPoint wordsPosition1;  //视频中字幕的位置
//    wordsPosition1.x = 20;
//    wordsPosition1.y = IMG_HEIGHT - 20;
//    for(int i = 0; i < src1.get(CV_CAP_PROP_FRAME_COUNT); i++){
//        src1 >> frame;  //从PPT视频中读入
//        cv::putText(frame, "Created by Dingchenwei_3140103310", wordsPosition1, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar::all(255), 1);  //插入字幕
//        dst << frame;  //输出视频
//    }
//    for(int i = 0; i < src2.get(CV_CAP_PROP_FRAME_COUNT); i++){
//        src2 >> frame;  //从原视频中读入
//        cv::putText(frame, "Created by Dingchenwei_3140103310", wordsPosition1, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar::all(255), 1);  //插入字幕
//        dst << frame;  //输出视频
//    }
//}
