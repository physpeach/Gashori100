#include <opencv2/opencv.hpp>
#include <cmath>
#include <algorithm>

namespace me {
    cv::Mat bgr2hsv(const cv::Mat& img){
        const int w = img.cols;
        const int h = img.rows;
        
        cv::Mat out = cv::Mat::zeros(h, w, CV_32FC3);

        for(int y = 0; y < h; y++){
            for(int x = 0; x < w; x++){
                const float c[3] = {static_cast<float>(img.at<cv::Vec3b>(y, x)[0]), static_cast<float>(img.at<cv::Vec3b>(y, x)[1]), static_cast<float>(img.at<cv::Vec3b>(y, x)[2])};
                const float Imax = std::max(std::max(c[0], c[1]), c[2] );
                const float Imin = std::min(std::min(c[0], c[1]), c[2] );
                
                if (Imin == c[0]) {
                    out.at<cv::Vec3f>(y, x)[0] = ((c[2] - c[1]) / (Imax - Imin) + 4.) * M_PI / 3. ;
                }
                else if (Imin == c[1]) {
                    out.at<cv::Vec3f>(y, x)[0] = ((c[0] - c[2]) / (Imax - Imin) + 2.) * M_PI / 3.;
                }
                else if (Imin == c[2]) {
                    out.at<cv::Vec3f>(y, x)[0] = (c[1] - c[0]) / (Imax - Imin) * M_PI / 3.;
                }
                out.at<cv::Vec3f>(y, x)[1] = (Imax - Imin)/Imax;
                out.at<cv::Vec3f>(y, x)[2] = Imax;
            }
        }
        return out;
    }
    cv::Mat hsv_transform(const cv::Mat& img){
        const int w = img.cols;
        const int h = img.rows;
        
        cv::Mat out = cv::Mat::zeros(h, w, CV_32FC3);

        for(int y = 0; y < h; y++){
            for(int x = 0; x < w; x++){
                out.at<cv::Vec3f>(y, x)[0] = img.at<cv::Vec3f>(y, x)[0] + M_PI;
                if(out.at<cv::Vec3f>(y, x)[0] > 2 * M_PI){
                    out.at<cv::Vec3f>(y, x)[0] -= 2 * M_PI;
                }
                out.at<cv::Vec3f>(y, x)[1] = img.at<cv::Vec3f>(y, x)[1];
                out.at<cv::Vec3f>(y, x)[2] = img.at<cv::Vec3f>(y, x)[2];
            }
        }
        return out;
    }
    cv::Mat hsv2bgr(const cv::Mat& img){
        const int w = img.cols;
        const int h = img.rows;
        
        cv::Mat out = cv::Mat::zeros(h, w, CV_8UC3);
        for(int y = 0; y < h; y++){
            for(int x = 0; x < w; x++){
                const float c[3] = {img.at<cv::Vec3f>(y, x)[0], img.at<cv::Vec3f>(y, x)[1], img.at<cv::Vec3f>(y, x)[2]};
                const float _H = c[0] * 3. / M_PI;
                const uchar h = _H;
                const uchar I = c[2];
                const uchar P = I * (1 - c[1]);
                const uchar Q = I * (1 - c[1] * (_H - static_cast<float>(h)));
                const uchar T = I * (1 - c[1] * (1 - _H + static_cast<float>(h)));
                switch(h){
                case 6:
                case 0:
                    out.at<cv::Vec3b>(y, x)[0] = P;
                    out.at<cv::Vec3b>(y, x)[1] = T;
                    out.at<cv::Vec3b>(y, x)[2] = I;
                    break;
                case 1:
                out.at<cv::Vec3b>(y, x)[0] = P;
                out.at<cv::Vec3b>(y, x)[1] = I;
                out.at<cv::Vec3b>(y, x)[2] = Q;
                break;
                case 2:
                out.at<cv::Vec3b>(y, x)[0] = T;
                out.at<cv::Vec3b>(y, x)[1] = I;
                out.at<cv::Vec3b>(y, x)[2] = P;
                break;
                case 3:
                out.at<cv::Vec3b>(y, x)[0] = I;
                out.at<cv::Vec3b>(y, x)[1] = Q;
                out.at<cv::Vec3b>(y, x)[2] = P;
                break;
                case 4:
                out.at<cv::Vec3b>(y, x)[0] = I;
                out.at<cv::Vec3b>(y, x)[1] = P;
                out.at<cv::Vec3b>(y, x)[2] = T;
                break;
                case 5:
                out.at<cv::Vec3b>(y, x)[0] = Q;
                out.at<cv::Vec3b>(y, x)[1] = P;
                out.at<cv::Vec3b>(y, x)[2] = I;
                break;
                }
            }
        }
        return out;
    }
}
int main(int argc, char* argv[]) {
    const cv::Mat& src = cv::imread("Gasyori100knock/dataset/images/imori.jpg");
    const cv::Mat& out = me::hsv2bgr(me::hsv_transform(me::bgr2hsv(src)));
    cv::imwrite("q_001_010/q005.jpg", out);
    return 0;
}