#include <opencv2/opencv.hpp>

namespace me {
    uchar ohtsu_threshold(const cv::Mat& img){
        const int& w = img.cols;
        const int& h = img.rows;
        
        double maxbv = -1;
        uchar threshold = 0;
        for(uchar i = 0; i < 255; i++){
            double w0 = 0;
            double m0 = 0;
            double w1 = 0;
            double m1 = 0;
            for(int y = 0; y < h; y++){
                for(int x = 0; x < w; x++){
                    const uchar& val = img.at<uchar>(y, x);
                    if (val < i){
                        w0++;
                        m0 += val;
                    }
                    else{
                        w1++;
                        m1 += val;
                    }
                }
            }
            m0 /= w0;
            m1 /= w1;
            w0 /= (h * w);
            w1 /= (h * w);
            double bv = w0 * w1 * (m1 - m0) * (m1 - m0);
            if(maxbv < bv){
                maxbv = bv;
                threshold = i;
            }
        }
        return threshold;
    }
    cv::Mat ohtsu_binalize(const cv::Mat& img){
        const int& w = img.cols;
        const int& h = img.rows;
        
        cv::Mat out = cv::Mat::zeros(h, w, CV_8UC1);
        cv::threshold(img, out, ohtsu_threshold(img), 255, cv::THRESH_BINARY);
        
        return out;
    }
}
int main(int argc, char* argv[]) {
    const cv::Mat& src = cv::imread("Gasyori100knock/dataset/images/imori.jpg");
    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_RGB2GRAY);
    const cv::Mat& out = me::ohtsu_binalize(gray);
    cv::imwrite("q_001_010/q004.jpg", out);
    return 0;
}