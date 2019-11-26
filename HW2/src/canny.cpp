#include "main.h"


int MyCanny(const Mat gray_image, Mat& fin_image, int high_threshold, int low_threshold)
{
    Mat gauss_image = Mat::zeros(gray_image.rows, gray_image.cols, CV_8UC1);

    // 高斯滤波
    GaussFilter(gray_image, gauss_image);
    imshow("gauss_image", gauss_image);
    imwrite("gauss_image.jpg", gauss_image);

    // X、Y方向梯度计算
    Mat X = Mat::zeros(gray_image.rows, gray_image.cols, CV_32FC1);
    Mat Y = Mat::zeros(gray_image.rows, gray_image.cols, CV_32FC1);
    Gradient(gray_image, X, Y);
    Mat temp_X = X.clone();
    temp_X.convertTo(temp_X, CV_8UC1);
    imshow("X", temp_X);
    imwrite("X.jpg", temp_X);
    Mat temp_Y = Y.clone();
    temp_Y.convertTo(temp_Y, CV_8UC1);
    imshow("Y", temp_Y);
    imwrite("Y.jpg", temp_Y);

    // 计算幅值、相角
    Mat ampli = Mat::zeros(gray_image.rows, gray_image.cols, CV_32FC1);
    Mat phase = Mat::zeros(gray_image.rows, gray_image.cols, CV_32FC1);
    AmpliPhase(X, Y, ampli, phase);
    Mat temp_ampli = ampli.clone();
    temp_ampli.convertTo(temp_ampli, CV_8UC1);
    imshow("ampli", temp_ampli);
    imwrite("ampli.jpg", temp_ampli);
    Mat temp_phase = phase.clone();
    temp_ampli.convertTo(temp_phase, CV_8UC1);
    imshow("phase", temp_phase);
    imwrite("phase.jpg", temp_phase);

    // 非极大值抑制
    Mat nms_image = Mat::zeros(gray_image.rows, gray_image.cols, CV_8UC1);
    NonMaximaSuppression(ampli, phase, nms_image);
    nms_image.convertTo(nms_image, CV_8UC1);
    imshow("nms_image", nms_image);
    imwrite("nms_image.jpg", nms_image);


    // 双阈值分割
    Mat high_threshold_image = Mat::zeros(gray_image.rows, gray_image.cols, CV_8UC1);
    Mat low_threshold_image = Mat::zeros(gray_image.rows, gray_image.cols, CV_8UC1);
    DoubleThreshold(nms_image, high_threshold_image, low_threshold_image, high_threshold, low_threshold);
    imshow("high_threshold_image", high_threshold_image);
    imwrite("high_threshold_image.jpg", high_threshold_image);
    imshow("low_threshold_image", low_threshold_image);
    imwrite("low_threshold_image.jpg", low_threshold_image);

    // 边缘连接
    Mat edge_tracking_image= Mat::zeros(gray_image.rows, gray_image.cols, CV_8UC1);
    EdgeTracking( high_threshold_image,low_threshold_image, edge_tracking_image);
    imshow("edge_tracking_image", edge_tracking_image);
    imwrite("edge_tracking_image.jpg", edge_tracking_image);

    return 0;
}

void GaussFilter(const Mat orig_image, Mat &gauss_image)
{
    Mat temp_gauss_image = Mat::zeros(orig_image.rows, orig_image.cols, CV_8UC1);
    SingleGaussFilter(orig_image, temp_gauss_image);

    Mat t_temp_gauss_image = temp_gauss_image.t();
    Mat temp_fin_gauss_image= Mat::zeros(t_temp_gauss_image.rows, t_temp_gauss_image.cols, CV_8UC1);
    SingleGaussFilter(t_temp_gauss_image, temp_fin_gauss_image);
    gauss_image = temp_fin_gauss_image.t();
}

void SingleGaussFilter(Mat orig_image, Mat& single_gauss_image)
{
    int gauss_template[] = {1, 4, 6, 4, 1};
    int template_length = sizeof(gauss_template) / sizeof(gauss_template[0]);
    int total = 0;
    int rows = orig_image.rows;
    int cols = orig_image.cols;


    for (int i = 0; i < template_length; i++)
        total += gauss_template[i];

    for (int i = 0; i < rows; i++)
    {
        uchar* data = orig_image.ptr<uchar>(i);
        for (int j = 0; j < cols; j++)
        {
            int sum = 0;
            for (int k = -int((template_length - 1) / 2); k <= int((template_length - 1) / 2); k++)
            {
                // 边界处理，超出边界的值赋为边界值
                int col = j + k;
                col = col < 0 ? 0 : col;
                col = col >= cols ? cols - 1 : col;
                // 卷积和
                sum += gauss_template[k+ int((template_length - 1) / 2)] * data[col];
            }
            single_gauss_image.ptr<uchar>(i)[j] = sum / total;
        }
    }
}

void Gradient(Mat image, Mat &X, Mat &Y)
{
    Mat t_Y = Mat::zeros(image.cols, image.rows, CV_32FC1);
    Mat t_image = image.t();
    SingleGradient(image, X);
    SingleGradient(t_image, t_Y);
    Y = t_Y.t();
}

void SingleGradient(Mat image, Mat& single_gradient)
{
    int grad_template[2][2] = {{-1,1},{-1,1}};
    int rows = image.rows;
    int cols = image.cols;

    for (int i = 0; i < rows; i++)
    {
        // 读取两行数据
        uchar* image_row[2];
        image_row[0] = image.ptr<uchar>(i);
        image_row[1] = image.ptr<uchar>((i + 1) >= rows ? i:i+1);

        for (int j = 0; j < cols; j++)
        {
            int sum = 0;

            for (int k = 0; k < 2 ; k++)
            {
                // 边界处理，超出边界的值赋为边界值
                int row = i + k;
                row = row >= rows ? rows - 1 : row;
                for (int g = 0; g < 2 ; g++)
                {
                    // 边界处理，超出边界的值赋为边界值
                    int col = j + g;
                    col = col >= cols ? cols - 1 : col;
                    sum += grad_template[k][g] * image_row[k][col];
                }
            }
            single_gradient.ptr<float>(i)[j] = sum / 2;
        }
    }
}

void AmpliPhase(Mat X, Mat Y, Mat &ampli, Mat &phase)
{
    for (int i = 0; i < X.rows; i++)
    {
        float* data_X = X.ptr<float>(i);
        float* data_Y = Y.ptr<float>(i);
        float* data_ampli = ampli.ptr<float>(i);
        float* data_phase = phase.ptr<float>(i);

        for (int j = 0; j < X.cols; j++)
        {
            data_ampli[j] = sqrt(data_X[j]* data_X[j]+ data_Y[j] * data_Y[j]);
            data_phase[j] = atan(data_Y[j] / (data_X[j]>0.000001? data_X[j]:0.000001)) * 180/3.141592;

            if (int(abs(data_phase[j])) > 90)
            {
                cout << int(abs(data_phase[j])) << endl;
                waitKey(0);
            }
        }
    }
}

void NonMaximaSuppression(Mat ampli, Mat phase, Mat& nms_image)
{
    int up = 1;
    int down = 1;
    int left = 1;
    int right = 1;
    for (int i = 1; i < ampli.rows-1; i++)
    {
        float* ampli_data[3];
        ampli_data[0] = ampli.ptr<float>(i-up);
        ampli_data[1] = ampli.ptr<float>(i);
        ampli_data[2] = ampli.ptr<float>(i+down);
        float* temp_phase = phase.ptr<float>(i);
        uchar* temp_nms_image = nms_image.ptr<uchar>(i);

        for (int j = 1; j < ampli.cols-1; j++)
        {
            int temp_single_phase = int(temp_phase[j]);
            // 左右比
            if (temp_single_phase >= -22.5 && temp_single_phase <= 22.5)
            {
                if (ampli_data[1][j] >= ampli_data[1][i-left] && ampli_data[1][j] >= ampli_data[1][i+right])
                {
                    temp_nms_image[j] = uchar(ampli_data[1][j]);
                }
            }
            // 右上左下比
            else if (temp_single_phase < -22.5 && temp_single_phase >= -22.5 - 45)
            {
                if (ampli_data[1][j] >= ampli_data[1-up][j+right] && ampli_data[1][j] >= ampli_data[1 + down][j - left])
                {
                    temp_nms_image[j] = uchar(ampli_data[1][j]);
                }
            }
            // 右下左上比
            else if (temp_single_phase > 22.5 && temp_single_phase <= 22.5 + 45)
            {
                if (ampli_data[1][j] >= ampli_data[1 +down][j + right] && ampli_data[1][j] >= ampli_data[1 - up][j - left])
                {
                    temp_nms_image[j] = uchar(ampli_data[1][j]);
                }
            }
            // 上下比
            else if ((temp_single_phase > 22.5 + 45 && temp_single_phase <= 90) || (temp_single_phase < -22.5 - 45 && temp_single_phase >= -90))
            {
                if (ampli_data[1][j] >= ampli_data[1 - up][j] && ampli_data[1][j] >= ampli_data[1 + down][j ])
                {
                    temp_nms_image[j] = uchar(ampli_data[1][j]);
                }
            }
            else if(0)
            {
                cout << temp_phase[j]<< "error in angles!!!"<<endl;
                waitKey(0);
                return;
            }

        }
    }
}

void DoubleThreshold(Mat image, Mat& high_threshold_image, Mat& low_threshold_image, int high_threshold, int low_threshold)
{
    for (int i = 0; i < image.rows; i++)
    {
        uchar* data = image.ptr<uchar>(i);
        uchar* high_threshold_data = high_threshold_image.ptr<uchar>(i);
        uchar* low_threshold_data = low_threshold_image.ptr<uchar>(i);

        for (int j = 0; j < image.cols; j++)
        {
            high_threshold_data[j] = data[j] > high_threshold ? 255 : 0;
            low_threshold_data[j] = data[j] > low_threshold ? 255 : 0;
        }
    }
}


void EdgeTracking(Mat high_threshold_image, Mat low_threshold_image, Mat &edge_tracking_image)
{
    edge_tracking_image = high_threshold_image.clone();
    Mat subtract_image = low_threshold_image - high_threshold_image;
    imshow("subtract_image ", subtract_image);
    imwrite("subtract_image.jpg", subtract_image);

    for (int i = 0; i < high_threshold_image.rows; i++)
    {
        for (int j = 0; j < high_threshold_image.cols; j++)
        {
            if (high_threshold_image.at<uchar>(i, j) == 255)
            {
                SinglePointTracking(high_threshold_image, subtract_image, edge_tracking_image,i,j);
            }
        }
    }
}

void SinglePointTracking(Mat &high_threshold_image,Mat &subtract_image,Mat &edge_tracking_image,int row, int col)
{
    // 右点
    if ((col + 1 <= subtract_image.cols - 1) && (subtract_image.at<uchar>(row, col+1) == 255))
    {
        edge_tracking_image.at<uchar>( row, col+1) = 255;
        subtract_image.at<uchar>(row, col + 1) = 0;
        SinglePointTracking(high_threshold_image, subtract_image, edge_tracking_image, row,  col + 1);
    }
    // 右下点
    if ((row + 1 <= subtract_image.rows - 1) && (col + 1 <= subtract_image.cols - 1) && (subtract_image.at<uchar>(row + 1 , col + 1) == 255))
    {
        edge_tracking_image.at<uchar>(row + 1, col + 1) = 255;
        subtract_image.at<uchar>(row+1, col + 1) = 0;
        SinglePointTracking(high_threshold_image, subtract_image, edge_tracking_image, row + 1, col + 1);
    }
    // 下点
    if ((row + 1 <= subtract_image.rows - 1) && (subtract_image.at<uchar>(row + 1, col ) == 255))
    {
        edge_tracking_image.at<uchar>(row + 1, col) = 255;
        subtract_image.at<uchar>(row+1, col ) = 0;
        SinglePointTracking(high_threshold_image, subtract_image, edge_tracking_image, row + 1, col);
    }
    // 左下点
    if ((row + 1 <= subtract_image.rows-1)&&(col-1 >= 0) && (subtract_image.at<uchar>(row+1,col-1) == 255))
    {
        edge_tracking_image.at<uchar>(row + 1, col - 1) = 255;
        subtract_image.at<uchar>(row+1, col - 1) = 0;
        SinglePointTracking(high_threshold_image, subtract_image, edge_tracking_image, row + 1, col - 1);
    }
    // 左点
    if ((col - 1 >= 0) && (subtract_image.at<uchar>( row,col-1) == 255))
    {
        edge_tracking_image.at<uchar>(row, col - 1) = 255;
        subtract_image.at<uchar>(row, col - 1) = 0;
        SinglePointTracking(high_threshold_image, subtract_image, edge_tracking_image, row, col - 1);
    }
    // 左上点
    if ((row-1>=0) && (col-1>=0) && (subtract_image.at<uchar>(row-1,col - 1) == 255))
    {
        edge_tracking_image.at<uchar>(row - 1, col - 1) = 255;
        subtract_image.at<uchar>(row-1, col - 1) = 0;
        SinglePointTracking(high_threshold_image, subtract_image, edge_tracking_image, row - 1, col - 1);
    }
    // 上点
    if ( (row - 1 >= 0) && (subtract_image.at<uchar>( row-1,col) == 255))
    {
        edge_tracking_image.at<uchar>(row - 1, col) = 255;
        subtract_image.at<uchar>(row-1, col) = 0;
        SinglePointTracking(high_threshold_image, subtract_image, edge_tracking_image, row - 1, col);
    }
    // 右上点
    if ((row -1 >= 0) && (col + 1 <= subtract_image.cols - 1) && (subtract_image.at<uchar>(row - 1,col + 1) == 255))
    {
        edge_tracking_image.at<uchar>(row - 1, col + 1) = 255;
        subtract_image.at<uchar>(row-1, col + 1) = 0;
        SinglePointTracking(high_threshold_image, subtract_image, edge_tracking_image, row - 1, col + 1);
    }
}
