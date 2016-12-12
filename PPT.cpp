//
//  ppt.cpp
//  OpenCV
//
//  Created by 丁晨炜 on 16/11/24.
//  Copyright © 2016年 zju. All rights reserved.
//

#include "PPT.h"

void PPT::start(IplImage* dst, IplImage* img1, IplImage* img2, int effect_kind, cv::VideoWriter& convertPPTToVideo)  //启动PPT效果
{
	switch(effect_kind) {
	case 0:
        shutters(dst, img1, img2, convertPPTToVideo);  //百叶窗
		break;
	case 1:
        moveLeft(dst, img1, img2, convertPPTToVideo);  //向左平移
        break;
	case 2:
        moveRight(dst, img1, img2, convertPPTToVideo);  //向右平移
        break;
	default:
		break;
	}
}


//百叶窗
void PPT::shutters(IplImage* dst, IplImage* img1, IplImage* img2, cv::VideoWriter convertPPTToVideo)
{
    int pieces = 7;  //百叶窗叶条的数目
    int dividedHeight = IMG_HEIGHT / pieces;  //每个叶条的高度
	IplImage* res = cvCreateImage(cvGetSize(dst), dst->depth, dst->nChannels);
	for(int count=0; count<IMG_HEIGHT/20; count+=1) {  //循环20次后完成切换
		cvCopy(img2, dst);  //先把后一张图像覆盖到目标图像上去，然后把前一张图像也覆盖上去，但是慢慢减少其覆盖面积，让后一张露出来
		IplImage* tmp = cvCreateImage(cvSize(IMG_WIDTH, 2*(dividedHeight/2-count)), img1->depth, img1->nChannels);  //每次减少第一张的覆盖面积

		for(int i=0; i<pieces; i++) {  //有10个叶条
			cvSetImageROI(img1, cvRect(0, dividedHeight * i, IMG_WIDTH, dividedHeight));
			cvResize(img1, tmp, CV_INTER_LINEAR);
			cvSetImageROI(dst, cvRect(0, dividedHeight * i + count, IMG_WIDTH, 2*(dividedHeight/2-count)));
			cvCopy(tmp, dst);
		}
        
		cvResetImageROI(img1);  //把roireset为原图像
		cvResetImageROI(dst);
        cv::Mat temp(dst, 0);
        CvPoint wordsPosition1;  //视频中字幕的位置
        wordsPosition1.x = 20;
        wordsPosition1.y = IMG_HEIGHT - 20;
        cv::putText(temp, "Created by Dingchenwei_3140103310", wordsPosition1, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar::all(255), 1);  //插入字幕
        convertPPTToVideo << temp;

		cvReleaseImage(&tmp);  //释放
	}

	cvReleaseImage(&res);  //释放
}

//向左平移
void PPT::moveLeft(IplImage* dst, IplImage* img1, IplImage* img2, cv::VideoWriter convertPPTToVideo)
{
    int barWidth = 30;  //每一个纵条的宽度
    IplImage* tmp = cvCreateImage(cvGetSize(dst), dst->depth, dst->nChannels);
	CvScalar s;  //图像第三维的向量
	cvCopy(img1, dst);
	for(int w=IMG_WIDTH-1; w>0; w-=barWidth) {  //遍历每一个纵条
		for(int h=0; h<IMG_HEIGHT; h++) {  //对每一个纵条上每一行做处理
			s = cvGet2D(img2, h, w);
			cvSet2D(dst, h, w, s);
            for (int i = 1; i < barWidth; i++){  //对每一个纵条的最开头一部分做处理，不加的话每个纵条最开头一部分会被忽视
                if (w > i){  //要判断有没有出边界
                    s = cvGet2D(img2, h, w-i);
                    cvSet2D(dst, h, w-i, s);
                }
            }
		}
        cv::Mat temp(dst, 0);
        CvPoint wordsPosition1;  //视频中字幕的位置
        wordsPosition1.x = 20;
        wordsPosition1.y = IMG_HEIGHT - 20;
        cv::putText(temp, "Created by Dingchenwei_3140103310", wordsPosition1, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar::all(255), 1);  //插入字幕
        convertPPTToVideo << temp;
	}

	cvReleaseImage(&tmp);
}

//向右平移
void PPT::moveRight(IplImage* dst, IplImage* img1, IplImage* img2, cv::VideoWriter convertPPTToVideo)
{
    int barWidth = 30;  //每一个纵条的宽度
	IplImage* tmp = cvCreateImage(cvGetSize(dst), dst->depth, dst->nChannels);
	CvScalar s;  //图像第三维的向量
	cvCopy(img1, dst);
	for(int w=1; w<IMG_WIDTH; w+=barWidth) {
		for(int h=0; h<IMG_HEIGHT; h++) {  //对每一个纵条上每一行做处理
			s = cvGet2D(img2, h, w);
			cvSet2D(dst, h, w, s);
            for (int i = 1; i < barWidth; i++){  //对每一个纵条的最后一部分做处理，不加的话每个纵条最后一部分会被忽视
                if (w < IMG_WIDTH - i){  //要判断有没有出边界
                    s = cvGet2D(img2, h, w+i);
                    cvSet2D(dst, h, w+i, s);
                }
            }

		}
        cv::Mat temp(dst, 0);
        CvPoint wordsPosition1;  //视频中字幕的位置
        wordsPosition1.x = 20;
        wordsPosition1.y = IMG_HEIGHT - 20;
        cv::putText(temp, "Created by Dingchenwei_3140103310", wordsPosition1, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar::all(255), 1);  //插入字幕
        convertPPTToVideo << temp;
	}

	cvReleaseImage(&tmp);
}
