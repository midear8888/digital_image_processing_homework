#include "main.h"

int main()
{
    Mat image, gray_image;
    Mat fin_image= Mat::zeros(image.rows, image.cols, CV_8UC1);
    image = imread("c++.jpeg");
    if (image.empty())
    {
        cout << "Could not open or find the image" << endl;
        return -1;
    }
    else
        cvtColor(image, gray_image, CV_RGB2GRAY);
    imshow("gray_image", gray_image);
    imwrite("gray_image.jpg", gray_image);
    int high_threshold=100; // 120
    int low_threshold=20; // 50

    MyCanny(gray_image, fin_image, high_threshold, low_threshold);
    Mat cvCanny_image = Mat::zeros(gray_image.rows, gray_image.cols, CV_8UC1);

    Canny(gray_image, cvCanny_image, high_threshold, low_threshold);
    imshow("cvCanny_image", cvCanny_image);
    imwrite("cvCanny_image.jpg", cvCanny_image);

    waitKey(0);
    return 0;
}
