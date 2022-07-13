#include <opencv2/opencv.hpp>

namespace me {
    cv::Mat binalize(const cv::Mat& img, const uchar threshold){
        const int w = img.cols;
        const int h = img.rows;
        
        cv::Mat out = cv::Mat::zeros(h, w, CV_8UC1);

        for(int y = 0; y < h; y++){
            for(int x = 0; x < w; x++){
                out.at<uchar>(y, x) = img.at<uchar>(y, x) < threshold ? 0 : 255;
            }
        }
        
        return out;
    }
}
int main(int argc, char* argv[]) {
    const cv::Mat& src = cv::imread("Gasyori100knock/dataset/images/imori.jpg");
    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_RGB2GRAY);
    const cv::Mat& out = me::binalize(gray, 128);
    cv::imwrite("q_001_010/q003.jpg", out);
    return 0;
}