#include <opencv2/opencv.hpp>

namespace me {
    cv::Mat rgb2bgr(const cv::Mat& img){
        const int w = img.cols;
        const int h = img.rows;
        
        cv::Mat out = cv::Mat::zeros(h, w, CV_8UC3);

        for(int y = 0; y < h; y++){
            for(int x = 0; x < w; x++){
                out.at<cv::Vec3b>(y, x)[0] = img.at<cv::Vec3b>(y, x)[2];
                out.at<cv::Vec3b>(y, x)[1] = img.at<cv::Vec3b>(y, x)[1];
                out.at<cv::Vec3b>(y, x)[2] = img.at<cv::Vec3b>(y, x)[0];
            }
        }
        
        return out;
    }
}
int main(int argc, char* argv[]) {
    const cv::Mat& src = cv::imread("Gasyori100knock/dataset/images/imori.jpg");
    const cv::Mat& out = me::rgb2bgr(src);
    cv::imwrite("q_001_010/q001.jpg", out);
    return 0;
}