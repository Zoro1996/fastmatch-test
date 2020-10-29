#pragma once
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/core.hpp>
#include <opencv2/highgui/highgui_c.h> 
#include <fstream>
#include <string>
#include <vector>
#include<iostream>
#include <iterator>
#include "MyFunction.h"

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

static constexpr const float PI = 3.14;
static constexpr const int scale = 4;
static constexpr const float sampleRate = 0.001;
static constexpr const float mfactor = 0.9;


struct Gradient
{
	float theta;
	float margin;
};

struct Contours
{
	/*轮廓图*/
	Mat dstImage;

	/*质心坐标*/
	int centerX;
	int centerY;

	/*点集*/
	vector<Point2f> pointSet;

	/*梯度表*/
	vector<Gradient> gradientTable;
};

struct TransVariable
{
	int tx;
	int ty;
	float theta;
};


struct CurrentBestReusult
{
	//tuple<int, int, float> currentBestTrans;
	int transX;
	int transY;
	float theta;
	float currentBestDistance;
};

struct GradientTable
{
	vector<Point2f> pointSet;
	vector<float> gradientTable;
};

struct Measurement
{
	float SAD;
	float inversPointSetSize;
};


Point2f AfterTrans(tuple<int, int, float>&curTrans, Point2f curPoint, float centerX, float centerY);

vector<tuple<int, int, float>> ConstructNet(int row, int col, float delta);

Contours ExistedMaskImage(Mat &maskImage, Mat& srcImage);

CurrentBestReusult GetBestTrans(Mat& maskImage, Mat& srcImage, vector<Point2f>& subMaskPointSet,
	vector<tuple<int, int, float>>& TransNet, float delta, float epsilon);

vector <tuple<int, int, float >> GetNextNet(Mat&srcImage, vector<tuple<int, int, float >> &GoodTransNet,
	vector<Point2f>&subMaskPointSet, float centerX, float centerY, float delta);

vector<Gradient> GetTableFromPointSet(vector<Point2f> &pointSet, Mat&image);

float GradientAtCurPoint(Mat&image, Point2f &pt, float kernel[][3]);

float SingleTransEvaluation(Mat& maskImage, Mat &srcImage, vector<Point2f> &subMaskPointSet,
	tuple<int, int, float>& curTrans, float epsilon);

tuple<int, int, float> FastMatch(Mat &maskStruct, Mat &srcImage, float delta, float epsilon, float factor);
