#pragma once
#include <core\core.hpp>
#include <opencv.hpp>
#include <highgui\highgui.hpp>
#include <highgui\highgui_c.h>


//��Ҫ��ͼƬ����ͷ�ļ�

using namespace cv;
class ImageFile
{
public:
	ImageFile(CWnd *imageWnd,char * filePath);
	~ImageFile();

public:
	void ShowImage();//��ʾͼƬ
	void SetScale(double scale);//�������Ų���

public:
	char* filePath;
	int width;
	int height;
	Mat image;
	CWnd *imageWnd;

};

