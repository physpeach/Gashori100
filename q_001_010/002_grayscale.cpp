#include <opencv2/opencv.hpp>

namespace me {
    cv::Mat gray(const cv::Mat& img){
        const int w = img.cols;
        const int h = img.rows;
        
        cv::Mat out = cv::Mat::zeros(h, w, CV_8UC1);

        for(int y = 0; y < h; y++){
            for(int x = 0; x < w; x++){
                //r, g, b = 2, 1, 0
                out.at<uchar>(y, x) = 0.2126 * img.at<cv::Vec3b>(y, x)[2] + 0.7152 * img.at<cv::Vec3b>(y, x)[1] + 0.0722 * img.at<cv::Vec3b>(y, x)[0];
            }
        }
        
        return out;
    }
}
int main(int argc, char* argv[]) {
    const cv::Mat& src = cv::imread("Gasyori100knock/dataset/images/imori.jpg");
    const cv::Mat& out = me::gray(src);
    cv::imwrite("q_001_010/q002.jpg", out);
    return 0;
}