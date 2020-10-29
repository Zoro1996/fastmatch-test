#include "MyFunction.h"


int main(int argc, char *argv[])
{
	int index = 2;
	char  srcPath[100], maskPath[100];

	sprintf_s(srcPath, "C:\\Users\\dell\\Desktop\\lena512color.tiff");
	sprintf_s(maskPath, "C:\\Users\\dell\\Desktop\\LenaMask2.bmp");

	Mat src = imread(srcPath, 0);
	Mat srcRGB = imread(srcPath, 1);

	Mat mask = imread(maskPath, 0);
	Mat maskRGB = imread(maskPath, 1);

	if (src.empty() || srcRGB.empty() || mask.empty())
	{
		cout << "load image failed !" << endl;
	}

	resize(src, src, Size(src.cols / 2, src.rows / 2));
	resize(mask, mask, Size(mask.cols / 2, mask.rows / 2));

	Mat srcImage = src.clone();
	Mat maskImage = mask.clone();


	/*存储当前模板的轮廓图、点集、质心坐标、梯度表*/
	Contours maskStruct = ExistedMaskImage(maskImage, srcImage);


	/*计算最佳变换参数*/
	srcImage.convertTo(srcImage, CV_32FC1);
	maskImage.convertTo(maskImage, CV_32FC1);
	maskImage /= 255;
	srcImage /= 255;


	float delta = 0.2;
	float epsilon = 1;
	float factor = 0.5;
	tuple<int, int, float> bestTrans = FastMatch(maskImage, srcImage, delta, epsilon, factor);

	//float centerX = floor(maskImage.cols / 2);
	//float centerY = floor(maskImage.rows / 2);
	//for (int x = 0; x < maskImage.cols; x++)
	//{
	//	for (int y = 0; y < maskImage.rows; y++)
	//	{
	//		Point2f curPoint = Point2f(x, y);
	//		Point2f transPoint = AfterTrans(bestTrans, curPoint, centerX, centerY);
	//		if (transPoint.x >= 0 && transPoint.x < srcRGB.cols
	//			&& transPoint.y >= 0 && transPoint.y < srcRGB.rows)
	//		{
	//			srcRGB.at<Vec3b>(transPoint)[0] = 0;
	//			srcRGB.at<Vec3b>(transPoint)[1] = 0;
	//			srcRGB.at<Vec3b>(transPoint)[2] = mask.at<uchar>(curPoint);
	//		}
	//	}
	//}

	waitKey(0);
	return 0;
}