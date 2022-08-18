#include <opencv2/opencv.hpp>

namespace me {
    int periodic(const int n, const int len){
        if(n < 0){
            return periodic(n + len, len);
        }
        else if( len <= n){
            return periodic(n - len, len);
        }
        else{
            return n;
        }

    }
    cv::Mat median_filter(const cv::Mat& img, const int range, const float sigma){
        const int w = img.cols;
        const int h = img.rows;
        
        cv::Mat out = cv::Mat::zeros(h, w, CV_8UC3);
        for(int y = 0; y < h; y++){
            for(int x = 0; x < w; x++){
                for(int z = 0; z < 3; z++){
                    std::array<uchar, 9> c;
                    int i = 0;
                    for(int ry = -range; ry <= range; ry++){
                        for(int rx = -range; rx <= range; rx++){
                            c[i] = img.at<cv::Vec3b>(periodic(y + ry, h), periodic(x + rx, w))[z];
                            i++;
                        }
                    }
                    std::sort(c.begin(), c.end());
                    out.at<cv::Vec3b>(y, x)[z] = c[4];
                }
            }
        }
        
        return out;
    }
}
int main(int argc, char* argv[]) {
    const cv::Mat& src = cv::imread("Gasyori100knock/dataset/images/imori_256x256_noise.png");
    const cv::Mat& out = me::median_filter(src, 4, 1.3);
    cv::imwrite("q_001_010/q010.jpg", out);
    return 0;
}