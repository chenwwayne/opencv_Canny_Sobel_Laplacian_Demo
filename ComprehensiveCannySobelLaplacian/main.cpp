#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;
//�ص�����
void CallbackCanny(int, void*);
void CallbackSobel(int, void*);
void CallbackLaplacian(int, void*);
//ȫ�ֶ�������
Mat CannyBWSrcImg, CannyDstImg;
Mat SobelBWSrcImg, SobelDstImgX, SobelDstImgY, SobelDstImg;
Mat LaplacianBWSrcImg, LaplacianRGBSrcImg, LaplacianDstImg;
//���ֱ�Ե����õ��Ĳ���ֵ
int CannyLowThres=1;
int CannyHighThres=3;
int SobelKsize= 1;
int LaplacianKsize = 1;
//������
int main()
{
	Mat CannyRGBSrcImg, SobelRGBSrcImg,LaplacianRGBSrcImg;
	//��ȡͼ��
	CannyRGBSrcImg = imread("benz.jpg");
	SobelRGBSrcImg = imread("benz.jpg");
	LaplacianRGBSrcImg = imread("benz.jpg");
	//��ȡʧ�ܷ���
	if ((!CannyRGBSrcImg.data )||( ! SobelRGBSrcImg.data)||(!LaplacianRGBSrcImg.data))
		return false;
	//�ֱ��������˲�
	GaussianBlur(CannyRGBSrcImg, CannyRGBSrcImg, Size(3, 3), 0);
	medianBlur(SobelRGBSrcImg, SobelRGBSrcImg, 3);
	boxFilter(LaplacianRGBSrcImg, LaplacianRGBSrcImg, CV_8U, Size(3, 3));
	//�˲�����лҶ�ͼת��
	cvtColor(CannyRGBSrcImg, CannyBWSrcImg,CV_RGB2GRAY);
	cvtColor(SobelRGBSrcImg, SobelBWSrcImg, CV_RGB2GRAY);
	cvtColor(LaplacianRGBSrcImg, LaplacianBWSrcImg, CV_RGB2GRAY);
	//���ڴ���
	namedWindow("Canny��Ե���");
	namedWindow("Sobel��Ե���");
	namedWindow("Laplacian��Ե���");
	//�ص�����
	CallbackCanny(CannyLowThres, 0);
	CallbackCanny(CannyHighThres, 0);
	CallbackSobel(SobelKsize,0);
	CallbackLaplacian(LaplacianKsize, 0);
	//����Trackbar
	createTrackbar("����ֵ", "Canny��Ե���", &CannyLowThres, 60, CallbackCanny);
	createTrackbar("����ֵ", "Canny��Ե���", &CannyHighThres, 120, CallbackCanny);
	createTrackbar("�˴�С", "Sobel��Ե���", &SobelKsize, 3, CallbackSobel);
	createTrackbar("�˴�С", "Laplacian��Ե���", &LaplacianKsize, 5, CallbackLaplacian);

	waitKey();
	return true;
}

void CallbackCanny(int ,void*)
{
	Canny(CannyBWSrcImg, CannyDstImg, CannyLowThres, CannyHighThres);
	imshow("Canny��Ե���", CannyDstImg);
}

void CallbackSobel(int, void*)
{
	//ksize �C Size of the extended Sobel kernel. It must be 1, 3, 5, or 7.
	Sobel(SobelBWSrcImg, SobelDstImgX, CV_8U, 1, 0, SobelKsize*2+1);
	Sobel(SobelBWSrcImg, SobelDstImgY, CV_8U, 0,1, SobelKsize* 2+1);
	//X��Y�����Ȩ
	addWeighted(SobelDstImgX, 0.5, SobelDstImgY, 0.5, 0, SobelDstImg);
	imshow("Sobel��Ե���", SobelDstImg);
}

void CallbackLaplacian(int, void*)
{
	Laplacian(LaplacianBWSrcImg, LaplacianDstImg, CV_8U, LaplacianKsize*2+1);
	imshow("Laplacian��Ե���", LaplacianDstImg);
}