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
    cv::Mat gaussian_filter(const cv::Mat& img, const int range, const float sigma){
        const int w = img.cols;
        const int h = img.rows;
        
        cv::Mat out = cv::Mat::zeros(h, w, CV_8UC3);

        const float _k0 = 1. / (2. * M_PI * sigma * sigma);
        const float _k1 = -1. / (2. * sigma * sigma);
        std::vector<std::vector<float>> k(2 * range + 1, std::vector<float>(2 * range + 1));
        for(int y = 0; y <= 2 * range; y++){
            int ry = y - range;
            for(int x = 0; x <= 2 * range; x++){
                int rx = x - range;
                k[y][x] = _k0 * exp(_k1 * (rx*rx + ry*ry));
            }
        }

        for(int y = 0; y < h; y++){
            for(int x = 0; x < w; x++){
                for(int z = 0; z < 3; z++){
                    float c = 0;
                    for(int ry = -range; ry <= range; ry++){
                        for(int rx = -range; rx <= range; rx++){
                            c += k[ry + range][rx + range] * static_cast<float>(img.at<cv::Vec3b>(periodic(y + ry, h), periodic(x + rx, w))[z]);
                        }
                    }
                    out.at<cv::Vec3b>(y, x)[z] = static_cast<uchar>(c);
                }
            }
        }
        
        return out;
    }
}
int main(int argc, char* argv[]) {
    const cv::Mat& src = cv::imread("Gasyori100knock/dataset/images/imori_256x256_noise.png");
    const cv::Mat& out = me::gaussian_filter(src, 4, 1.3);
    cv::imwrite("q_001_010/q009.jpg", out);
    return 0;
}