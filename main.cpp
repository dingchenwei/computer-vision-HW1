//
//  main.cpp
//  OpenCV
//
//  Created by 丁晨炜 on 16/11/24.
//  Copyright © 2016年 zju. All rights reserved.
//


#include "ppt.h"
#include "processVideo.h"

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    //新建一个用于放映ppt效果的对象
    PPT* ppt = new PPT();
    
    //用于读取原视频
    cv::VideoCapture srcVideo = cv::VideoCapture("/Users/dingchenwei/xcodeProjects/OpenCV/originalVideo.mp4");
    
    //用来写入片头以及经过PPT效果处理后的视频
    cv::VideoWriter convertPPTToVideo = cv::VideoWriter();
    convertPPTToVideo.open("/Users/dingchenwei/xcodeProjects/OpenCV/finialVideo.mp4", CV_FOURCC('8', 'B', 'P', 'S'), srcVideo.get(CV_CAP_PROP_FPS), Size(IMG_WIDTH, IMG_HEIGHT),1);
    
    //制作片头
    cv::Mat frame = cv::imread("/Users/dingchenwei/xcodeProjects/OpenCV/IMG0.jpg");
    CvPoint wordsPosition;  //插入文字的位置
    wordsPosition.x = 20;
    wordsPosition.y = 200;
    cv::putText(frame, "Military Training(This video is created by Dingchenwei_3140103310)", wordsPosition, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar::all(255),1);  //插入文字
    for(int i = 0; i < 30; i++)
        convertPPTToVideo << frame;
    
    //制作PPT效果的视频
    IplImage* currentImg;  //当前图像
    IplImage* nextImg;  //下一个图像
    IplImage* blankImg;  //目标图像，将经过相应效果处理的图像储存起来
    blankImg = cvCreateImage(cvSize(IMG_WIDTH, IMG_HEIGHT), IPL_DEPTH_8U, 3);
    char imgName[50];  //图像的文件名
    sprintf(imgName, "/Users/dingchenwei/xcodeProjects/OpenCV/IMG0.jpg");
    currentImg = cvLoadImage(imgName);  //读取图像
    for(int i = 1; i < 6; ++i){
        sprintf(imgName, "/Users/dingchenwei/xcodeProjects/OpenCV/IMG%d.jpg", i);
        nextImg = cvLoadImage(imgName);
        ppt->start(blankImg, currentImg, nextImg, i%3, convertPPTToVideo);  //启动ppt效果，一共实现了三种效果，i%3表示循环使用这三种效果
        currentImg = nextImg;
    }
    
    //处理大小，使得视频和图片一样大，并且与PPT视频合并
    processVideo myProcessVideo = processVideo();
    myProcessVideo.resizeVideo(srcVideo, convertPPTToVideo, IMG_WIDTH, IMG_HEIGHT);  //剪裁大小
    
    //释放资源
    cvReleaseImage(&currentImg);
    cvReleaseImage(&blankImg);
}
