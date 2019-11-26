#ifndef CANNY_H
#define CANNY_H

#include "main.h"

using namespace cv;
using namespace std;

int MyCanny(const Mat gray_image, Mat &fin_image, int high_threshold, int low_threshold);
void GaussFilter(const Mat orig_image, Mat& gauss_image);
void SingleGaussFilter(Mat orig_image, Mat& single_gauss_image);
void Gradient(Mat image, Mat& X, Mat& Y);
void SingleGradient(Mat image, Mat& single_gradient);
void AmpliPhase(Mat X, Mat Y, Mat &ampli, Mat &phase);
void NonMaximaSuppression(Mat ampli, Mat phase, Mat &nms_image);
void DoubleThreshold(Mat image, Mat& high_threshold_image, Mat& low_threshold_image, int high_threshold, int low_threshold);
void EdgeTracking(Mat high_threshold_image, Mat low_threshold_image, Mat &edge_tracking_image);
void SinglePointTracking(Mat &high_threshold_image, Mat &subtract_image, Mat& edge_tracking_image, int row, int col);

#endif // CANNY_H
