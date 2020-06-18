#ifndef MYVISION_H
#define MYVISION_H

#include "myDefine.h"
#include <QMutex>

struct _sResVision {
    bool bRes = true;
    Mat mRes;
    vector<Rect> vRes;
    vector<double> vStd;
};


class MyVision
{
public:

    MyVision();
    int Gray(const cv::Mat mInput, int iMin, int iMax);
    int Gray(const cv::Mat mInput,cv::Mat &mOutput, int iMin, int iMax, cv::Scalar color);
    cv::Mat shiffImage(const cv::Mat inImage, int shiftX, int shiftY);
    cv::Mat rotateImage(const cv::Mat inImage, cv::Point center, double angle);
    void Constrast(cv::Mat &mInput, int alpha, int beta);
    void TempleMatching(cv::Mat mTemple, cv::Mat mObjToFind, cv::Point &p, double &d);
    cv::Mat RotateImage(const cv::Mat Image, int degree);
    void rotateImage(cv::Mat &Image, int degree);
    int Std(const cv::Mat mInput,cv::Mat &mOutput);
    int Mean(const cv::Mat mInput,cv::Mat &mOutput);
    int Mean(const cv::Mat mInput);



    /*vission check stain :*/
    _sResVision CheckStain(const cv::Mat mIn, _sGeneral param, int iCam, int iTypeSize, QString strFileName = "", bool bDebug = false);

    /*vission check white stain :*/
    _sResVision CheckWhiteStain(const cv::Mat mIn, _sGeneral param, int iCam, int iTypeSize, QString strFileName = "", bool bDebug = false);

    /* vission check glare:*/
    _sResVision CheckGlare(const cv::Mat mIn, _sGeneral param,  int iCam, QString strFileName = "", bool bDebug = false);

    /*vission check DarkSpot :*/
    _sResVision CheckDarkspot(const cv::Mat mIn, _sGeneral param, int iCam, QString strFileName = "", bool bDebug = false);

    /*vission check color:*/
    _sResVision CheckColor(const cv::Mat mIn, _sGeneral param, int iCam, QString strFileName = "", bool bDebug = false);

    /*vission check focus:*/
    _sResVision CheckFocus(const cv::Mat mIn, _sGeneral param, int iCam, QString strFileName = "", bool bDebug = false);

    /*other */
    std::vector<QString> GetAllFileInFolder(QString folder);
};


#endif // MYVISION_H
