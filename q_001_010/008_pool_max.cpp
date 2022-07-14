#include <opencv2/opencv.hpp>

namespace me {
    cv::Mat pool_max(const cv::Mat& img, const int range){
        const int ow = img.cols / range;
        const int oh = img.rows / range;
        
        cv::Mat out = cv::Mat::zeros(oh, ow, CV_8UC3);

        for(int oy = 0; oy < oh; oy++){
            for(int ox = 0; ox < ow; ox++){
                for(int z = 0; z < 3; z++){
                    uchar c = 0;
                    for(int ry = 0; ry < range; ry++){
                        const int iy = oy * range;
                        for(int rx = 0; rx < range; rx++){
                            const int ix = ox * range;
                            c = std::max(c, img.at<cv::Vec3b>(iy + ry, ix + rx)[z]);
                        }
                    }
                    out.at<cv::Vec3b>(oy, ox)[z] = c;
                }
            }
        }
        
        return out;
    }
}
int main(int argc, char* argv[]) {
    const cv::Mat& src = cv::imread("Gasyori100knock/dataset/images/imori.jpg");
    const cv::Mat& out = me::pool_max(src, 8);
    cv::imwrite("q_001_010/q008.jpg", out);
    return 0;
}