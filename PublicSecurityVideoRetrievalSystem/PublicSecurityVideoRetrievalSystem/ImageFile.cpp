#include "stdafx.h"
#include "ImageFile.h"

//��ȡ���ھ��
ImageFile::ImageFile(CWnd *imageWnd,char * filePath)
{
	this->filePath = filePath;
	this->imageWnd = imageWnd;
	CRect rect;
	this->imageWnd->GetClientRect(&rect);//rcΪ�ؼ��Ĵ�С��
	this->width = rect.Width();
	this->height = rect.Height();
}


ImageFile::~ImageFile()
{
}

void ImageFile::ShowImage()
{
	filePath = "C:\\Users\\76008\\Desktop\\test\\lena.bmp";
	namedWindow("ImageShow");//����OpenCV����
	HWND hWnd = (HWND)cvGetWindowHandle("ImageShow");//Ƕ��opencv����  ����һ�����ھ��
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, this->imageWnd->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

	this->image = imread(filePath);//opencv��ȡͼƬ

	Size dsize = Size(width, height);
	Mat img2 = Mat(dsize, CV_32S);
	resize(this->image, img2, dsize);

	imshow("ImageShow", img2);//opencv��ʾͼƬ
	waitKey(1);
}

void ImageFile::SetScale(double scale)
{
	//���Ų���
	Size dsize = Size(width*scale, height*scale);

	Mat img2 = Mat(dsize, CV_32S);
	resize(this->image, img2, dsize);

	imshow("ImageShow", img2);//opencv��ʾͼƬ
}
