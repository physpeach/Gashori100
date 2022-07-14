#include <opencv2/opencv.hpp>

namespace me {
    cv::Mat color_subtraction(const cv::Mat& img){
        const int w = img.cols;
        const int h = img.rows;
        
        cv::Mat out = cv::Mat::zeros(h, w, CV_8UC3);

        for(int y = 0; y < h; y++){
            for(int x = 0; x < w; x++){
                for(int z = 0; z < 3; z++){
                    out.at<cv::Vec3b>(y, x)[z] = 32 + (( img.at<cv::Vec3b>(y, x)[z] >> 6 ) << 6);
                }
            }
        }
        
        return out;
    }
}
int main(int argc, char* argv[]) {
    const cv::Mat& src = cv::imread("Gasyori100knock/dataset/images/imori.jpg");
    const cv::Mat& out = me::color_subtraction(src);
    cv::imwrite("q_001_010/q006.jpg", out);
    return 0;
}