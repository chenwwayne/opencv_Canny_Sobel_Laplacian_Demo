#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;
//回调函数
void CallbackCanny(int, void*);
void CallbackSobel(int, void*);
void CallbackLaplacian(int, void*);
//全局对象声明
Mat CannyBWSrcImg, CannyDstImg;
Mat SobelBWSrcImg, SobelDstImgX, SobelDstImgY, SobelDstImg;
Mat LaplacianBWSrcImg, LaplacianRGBSrcImg, LaplacianDstImg;
//三种边缘检测用到的参数值
int CannyLowThres=1;
int CannyHighThres=3;
int SobelKsize= 1;
int LaplacianKsize = 1;
//主函数
int main()
{
	Mat CannyRGBSrcImg, SobelRGBSrcImg,LaplacianRGBSrcImg;
	//读取图像
	CannyRGBSrcImg = imread("benz.jpg");
	SobelRGBSrcImg = imread("benz.jpg");
	LaplacianRGBSrcImg = imread("benz.jpg");
	//读取失败返回
	if ((!CannyRGBSrcImg.data )||( ! SobelRGBSrcImg.data)||(!LaplacianRGBSrcImg.data))
		return false;
	//分别用三种滤波
	GaussianBlur(CannyRGBSrcImg, CannyRGBSrcImg, Size(3, 3), 0);
	medianBlur(SobelRGBSrcImg, SobelRGBSrcImg, 3);
	boxFilter(LaplacianRGBSrcImg, LaplacianRGBSrcImg, CV_8U, Size(3, 3));
	//滤波后进行灰度图转化
	cvtColor(CannyRGBSrcImg, CannyBWSrcImg,CV_RGB2GRAY);
	cvtColor(SobelRGBSrcImg, SobelBWSrcImg, CV_RGB2GRAY);
	cvtColor(LaplacianRGBSrcImg, LaplacianBWSrcImg, CV_RGB2GRAY);
	//窗口创建
	namedWindow("Canny边缘检测");
	namedWindow("Sobel边缘检测");
	namedWindow("Laplacian边缘检测");
	//回调函数
	CallbackCanny(CannyLowThres, 0);
	CallbackCanny(CannyHighThres, 0);
	CallbackSobel(SobelKsize,0);
	CallbackLaplacian(LaplacianKsize, 0);
	//创建Trackbar
	createTrackbar("低阈值", "Canny边缘检测", &CannyLowThres, 60, CallbackCanny);
	createTrackbar("高阈值", "Canny边缘检测", &CannyHighThres, 120, CallbackCanny);
	createTrackbar("核大小", "Sobel边缘检测", &SobelKsize, 3, CallbackSobel);
	createTrackbar("核大小", "Laplacian边缘检测", &LaplacianKsize, 5, CallbackLaplacian);

	waitKey();
	return true;
}

void CallbackCanny(int ,void*)
{
	Canny(CannyBWSrcImg, CannyDstImg, CannyLowThres, CannyHighThres);
	imshow("Canny边缘检测", CannyDstImg);
}

void CallbackSobel(int, void*)
{
	//ksize – Size of the extended Sobel kernel. It must be 1, 3, 5, or 7.
	Sobel(SobelBWSrcImg, SobelDstImgX, CV_8U, 1, 0, SobelKsize*2+1);
	Sobel(SobelBWSrcImg, SobelDstImgY, CV_8U, 0,1, SobelKsize* 2+1);
	//X，Y方向加权
	addWeighted(SobelDstImgX, 0.5, SobelDstImgY, 0.5, 0, SobelDstImg);
	imshow("Sobel边缘检测", SobelDstImg);
}

void CallbackLaplacian(int, void*)
{
	Laplacian(LaplacianBWSrcImg, LaplacianDstImg, CV_8U, LaplacianKsize*2+1);
	imshow("Laplacian边缘检测", LaplacianDstImg);
}