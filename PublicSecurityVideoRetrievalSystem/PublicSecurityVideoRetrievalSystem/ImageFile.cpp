#include "stdafx.h"
#include "ImageFile.h"

//获取窗口句柄
ImageFile::ImageFile(CWnd *imageWnd,char * filePath)
{
	this->filePath = filePath;
	this->imageWnd = imageWnd;
	CRect rect;
	this->imageWnd->GetClientRect(&rect);//rc为控件的大小。
	this->width = rect.Width();
	this->height = rect.Height();
}


ImageFile::~ImageFile()
{
}

void ImageFile::ShowImage()
{
	filePath = "C:\\Users\\76008\\Desktop\\test\\lena.bmp";
	namedWindow("ImageShow");//创建OpenCV窗口
	HWND hWnd = (HWND)cvGetWindowHandle("ImageShow");//嵌套opencv窗口  返回一个窗口句柄
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, this->imageWnd->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

	this->image = imread(filePath);//opencv读取图片

	Size dsize = Size(width, height);
	Mat img2 = Mat(dsize, CV_32S);
	resize(this->image, img2, dsize);

	imshow("ImageShow", img2);//opencv显示图片
	waitKey(1);
}

void ImageFile::SetScale(double scale)
{
	//缩放操作
	Size dsize = Size(width*scale, height*scale);

	Mat img2 = Mat(dsize, CV_32S);
	resize(this->image, img2, dsize);

	imshow("ImageShow", img2);//opencv显示图片
}
