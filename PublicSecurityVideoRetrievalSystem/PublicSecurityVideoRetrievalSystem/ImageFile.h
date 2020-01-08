#pragma once
#include <core\core.hpp>
#include <opencv.hpp>
#include <highgui\highgui.hpp>
#include <highgui\highgui_c.h>


//主要的图片处理头文件

using namespace cv;
class ImageFile
{
public:
	ImageFile(CWnd *imageWnd,char * filePath);
	~ImageFile();

public:
	void ShowImage();//显示图片
	void SetScale(double scale);//进行缩放操作

public:
	char* filePath;
	int width;
	int height;
	Mat image;
	CWnd *imageWnd;

};

