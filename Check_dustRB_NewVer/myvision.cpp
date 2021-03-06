#include "myvision.h"

MyVision::MyVision()
{

}

int MyVision::Gray(const cv::Mat mInput, int iMin, int iMax)
{
    int iNumGray = 0;

    cv::Mat mImage = mInput.clone();


    if (mImage.channels() != 1)//rgb image
        cv::cvtColor(mImage, mImage, CV_BGR2GRAY);

    for (int i = 0; i < mImage.rows; i++)
        for (int j = 0; j < mImage.cols; j++)
        {
            UCHAR iGray = mImage.at<UCHAR>(i, j);

            if ((iGray >= iMin) && (iGray < iMax))
                iNumGray++;
        }

    return iNumGray;
}

int MyVision::Gray(const cv::Mat mInput,cv::Mat &mOutput, int iMin, int iMax, cv::Scalar color)
{
    int iNumGray = 0;
    cv::Mat mImage = mInput.clone();
    if (mInput.channels() == 3){
        //cv::cvtColor(mInput, mGray, CV_BGR2GRAY);
        mOutput = mInput.clone();
    }
    else{
        //mGray = mInput.clone();
        cv::cvtColor(mInput, mOutput, CV_GRAY2RGB);
    }
    for (int i = 0; i < mImage.rows; i++)
        for (int j = 0; j < mImage.cols; j++) {
            UCHAR iGray = mImage.at<UCHAR>(i, j);
            if ((iGray >= iMin) && (iGray < iMax)){
                iNumGray++;
                mOutput.at<Vec3b>(i,j)[0] = color[0];
                mOutput.at<Vec3b>(i,j)[1] = color[1];
                mOutput.at<Vec3b>(i,j)[2] = color[2];
            }
        }
    return iNumGray;
}

int MyVision::Std(const cv::Mat mInput,cv::Mat &mOutput) {
    cv::Mat mGray, mLaplace;
    cv::Scalar mean = cv::Scalar(0,0,0);
    cv::Scalar std  = cv::Scalar(0,0,0);
    if (mInput.channels() == 3){
        cv::cvtColor(mInput, mGray, CV_BGR2GRAY);
        mOutput = mInput.clone();
    }
    else{
        mGray = mInput.clone();
        cv::cvtColor(mInput, mOutput, CV_GRAY2RGB);
    }
    //laplace
    cv::Laplacian(mGray,mLaplace,CV_16S);
    //Get meanStdDev
    cv::meanStdDev(mLaplace, mean, std);
    double blurMeasure = std.val[0] * std.val[0];
    putText(mOutput,"Std = " + Double2QString(blurMeasure).toStdString(),
            Point(5,50),CV_FONT_HERSHEY_COMPLEX, 1.2,Scalar(0,255,0),2);
    return blurMeasure;
}

int MyVision::Mean(const cv::Mat mInput,cv::Mat &mOutput) {
    cv::Mat mGray;
    cv::Scalar mean = cv::Scalar(0,0,0);
    //gray
    if (mInput.channels() == 3){
        cv::cvtColor(mInput, mGray, CV_BGR2GRAY);
        mOutput = mInput.clone();
    }
    else{
        mGray = mInput.clone();
        cv::cvtColor(mInput, mOutput, CV_GRAY2RGB);
    }
    //Get meanStdDev
    mean = cv::mean(mGray);
    putText(mOutput,"Mean = " + Double2QString(mean[0]).toStdString(),
            Point(5,50),CV_FONT_HERSHEY_COMPLEX, 1.2,Scalar(0,255,0),2);
    return (int)mean[0];
}

int MyVision::Mean(const cv::Mat mInput) {
    cv::Mat mGray;
    cv::Scalar mean = cv::Scalar(0,0,0);
    //gray
    if (mInput.channels() == 3){
        cv::cvtColor(mInput, mGray, CV_BGR2GRAY);
    }
    else{
        mGray = mInput.clone();
    }
    //Get meanStdDev
    mean = cv::mean(mGray);
    return mean[0];
}
cv::Mat	MyVision::shiffImage(const cv::Mat inImage, int shiftX, int shiftY) {
    cv::Mat retImage(inImage.size(), inImage.type(), cv::Scalar::all(255));
    cv::Rect rSource = cv::Rect(max(0, -shiftX), max(0, -shiftY), inImage.cols - abs(shiftX), inImage.rows - abs(shiftY));
    cv::Rect rTarget = cv::Rect(max(0, shiftX), max(0, shiftY), inImage.cols - abs(shiftX), inImage.rows - abs(shiftY));
    inImage(rSource).copyTo(retImage(rTarget));
    return retImage;
}

// rotate image
cv::Mat	MyVision::rotateImage(const cv::Mat inImage, cv::Point center, double angle) {
    cv::Mat retImage/*(inImage.rows, inImage.cols, CV_8UC3, Scalar(212, 230, 233))*/;
    cv::Mat r = getRotationMatrix2D(center, angle, 1.0);
    cv::warpAffine(inImage, retImage, r, cv::Size(retImage.cols, retImage.rows), INTER_LINEAR, BORDER_CONSTANT, Scalar(212, 230, 233));
    return retImage;
}

/*
Tang giam do sang, do tuong phan anh xam
*/
void MyVision::Constrast(cv::Mat &mInput, int alpha, int beta) {
    for (int i = 0; i < mInput.rows; i++)
        for (int j = 0; j < mInput.cols; j++) {
            mInput.at<UCHAR>(i, j) = cv::saturate_cast<uchar>(alpha*mInput.at<UCHAR>(i, j) + beta);
        }
}

cv::Mat MyVision::RotateImage(const cv::Mat Image, int degree) {
    cv::Mat m = Image.clone();

    switch (degree) {
    case DEGREE_0:
        break;
    case DEGREE_90://xoay theo chieu kim dong ho
        m = m.t();
        cv::flip(m, m, 1);
        break;
    case DEGREE_180:
        cv::flip(m, m, -1);
        break;
    case DEGREE_270:
        m = m.t();
        cv::flip(m, m, 1);
        cv::flip(m, m, -1);
        break;
    default:
        break;
    }

    return m;
}
void  MyVision::rotateImage(cv::Mat &Image, int degree) {
    //cv::Mat m = Image.clone();
    switch (degree) {
    case DEGREE_0:
        break;
    case DEGREE_90://xoay theo chieu kim dong ho
        Image = Image.t();
        cv::flip(Image, Image, 1);
        break;
    case DEGREE_180:
        cv::flip(Image, Image, -1);
        break;
    case DEGREE_270:
        Image = Image.t();
        cv::flip(Image, Image, 1);
        cv::flip(Image, Image, -1);
        break;
    default:
        break;
    }

    //return m;
}
void MyVision::TempleMatching(cv::Mat mTemple, cv::Mat mObjToFind, cv::Point &p, double &d) {
    if (mTemple.empty() || mObjToFind.empty()) {
        return;}
    cv::Mat InImage = mTemple.clone();
    if (mTemple.channels() == 3) {
        cvtColor(InImage, InImage, COLOR_RGB2GRAY);
    }
    if (mObjToFind.channels() == 3) {
        cvtColor(mObjToFind, mObjToFind, COLOR_RGB2GRAY);
    }
    int result_cols = InImage.cols - mObjToFind.cols + 1;
    int result_rows = InImage.rows - mObjToFind.rows + 1;
    if (result_cols <= 0 || result_rows <= 0)
        return;
    cv::Mat result = cv::Mat(result_rows, result_cols, CV_32FC1, Scalar::all(0.0));
    /// Do the Matching and Normalize
    double minVal=0; double maxVal=0; cv::Point minLoc(0,0); cv::Point maxLoc(0,0);
    cv::Point matchLoc;
    //Mat mOutput = InImage;
    int method = CV_TM_CCOEFF_NORMED;
    cv::matchTemplate(InImage, mObjToFind, result, method);
    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
    /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
    double score = 0;
    if (method == CV_TM_SQDIFF || method == CV_TM_SQDIFF_NORMED) {
        matchLoc = minLoc;
        score = (1 - minVal) * 100;
    }
    else {
        matchLoc = maxLoc;
        score = maxVal * 100;
    }

    p = matchLoc;
    d = score;

}

vector<QString> MyVision::GetAllFileInFolder(QString folder) {
    vector<QString> vAllFile;
    QDir directory(folder);
    directory.refresh();
    QStringList images = directory.entryList(QStringList() << "*.jpg" << "*.JPG",QDir::Files);
    foreach(QString filename, images) {
        //do whatever you need to do
        qDebug()<<filename;
        vAllFile.push_back(filename);
    }

    return vAllFile;
}

/* spStain check:*/
_sResVision MyVision::CheckStain( const cv::Mat mIn, _sGeneral param, int iCam, int iTypeSize, QString strFileName, bool bDebug) {

     _sResVision sRes;
    try{
        /*Creat Var*/
        QString strFileSave = "";
        QString folderSaveStain = PATH_DB_STAIN;
        Mat mInput = mIn.clone();

        qDebug()<<mInput.cols<<"_"<<mInput.rows<<"SIZE OF IMAGE";

        if(mInput.empty()) {
            qDebug()<<"Empty Input";
            return sRes;
        }

        qDebug()<<"1";

        if(mInput.channels() != 3) {
            qDebug()<<"Fail Input";
            return sRes;
        }
        else {

            cvtColor(mInput, mInput, CV_BGR2GRAY);
        }

        qDebug()<<"2";

        blur(mInput,mInput,Size(param.spStain[iCam].ipBlurSize[iTypeSize],param.spStain[iCam].ipBlurSize[iTypeSize]));

        if(bDebug) {
            strFileSave = folderSaveStain + "/1_Blur[1]" + strFileName;
            imwrite(strFileSave.toStdString(), mInput);
        }

        //normalize
        //update norm_type
        int iNormType = NORM_MINMAX;
        if(param.ipNormType[iCam] == 3)
            iNormType = NORM_MINMAX;
        else if(param.ipNormType[iCam] == 0)
            iNormType = NORM_INF;
        else if(param.ipNormType[iCam] == 1)
            iNormType = NORM_L1;
        else if(param.ipNormType[iCam] == 2)
            iNormType = NORM_L2;

        normalize(mInput,mInput,param.ipNormAlpha[iCam], param.ipNormBeta[iCam], iNormType);

        if(bDebug) {
            strFileSave = folderSaveStain + "/2_Normalize" + strFileName;
            imwrite(strFileSave.toStdString(), mInput);
        }

        //blur
       blur(mInput,mInput,Size(param.spStain[iCam].ipBlurSize[iTypeSize],param.spStain[iCam].ipBlurSize[iTypeSize]));

        if(bDebug) {
            strFileSave = folderSaveStain + "/3_Blur[2]" + strFileName;
            imwrite(strFileSave.toStdString(), mInput);
        }

        qDebug()<<"3";
        Mat mAdaptive;
        int iBlock = param.spStain[iCam].ipBlockSize[iTypeSize];
        int iThresh = param.spStain[iCam].ipThreshold[iTypeSize];

        cv::adaptiveThreshold(mInput,
                              mAdaptive,
                              255,
                              ADAPTIVE_THRESH_MEAN_C,
                              THRESH_BINARY_INV,
                              iBlock,
                              iThresh);
        qDebug()<<"4";


        qDebug()<<"5";

        if(bDebug) {
            strFileSave = folderSaveStain + "/4_adaptive" + strFileName;
            imwrite(strFileSave.toStdString(), mAdaptive);
        }

        rectangle(mAdaptive,
                  Rect(0, 0, param.spStain[iCam].ipRemoveConner[iTypeSize], param.spStain[iCam].ipRemoveConner[iTypeSize]),
                  Scalar(0, 0, 0),
                  -1);

        qDebug()<<"6";

        rectangle(mAdaptive,
                  Rect(mAdaptive.cols - param.spStain[iCam].ipRemoveConner[iTypeSize],
                       0,
                       param.spStain[iCam].ipRemoveConner[iTypeSize],
                       param.spStain[iCam].ipRemoveConner[iTypeSize]),
                  Scalar(0, 0, 0),
                  -1);
        qDebug()<<"7";

        rectangle(mAdaptive,
                  Rect(mAdaptive.cols - param.spStain[iCam].ipRemoveConner[iTypeSize],
                       mAdaptive.rows - param.spStain[iCam].ipRemoveConner[iTypeSize],
                       param.spStain[iCam].ipRemoveConner[iTypeSize],
                       param.spStain[iCam].ipRemoveConner[iTypeSize]),
                  Scalar(0, 0, 0),
                  -1);

        qDebug()<<"8";

        rectangle(mAdaptive,
                  Rect(0,
                       mAdaptive.rows - param.spStain[iCam].ipRemoveConner[iTypeSize],
                       param.spStain[iCam].ipRemoveConner[iTypeSize],
                       param.spStain[iCam].ipRemoveConner[iTypeSize]),
                  Scalar(0, 0, 0),
                  -1);

        qDebug()<<"9";

        rectangle(mAdaptive,
                  Rect(0,
                       0,
                       mAdaptive.cols,
                       param.spStain[iCam].ipRemoveEdge[iTypeSize]),
                  Scalar(0, 0, 0),
                  -1);

        qDebug()<<"10";

        rectangle(mAdaptive,
                  Rect(0,
                       0,
                       param.spStain[iCam].ipRemoveEdge[iTypeSize],
                       mAdaptive.rows),
                  Scalar(0, 0, 0),
                  -1);

        qDebug()<<"11";

        rectangle(mAdaptive,
                  Rect(mAdaptive.cols - param.spStain[iCam].ipRemoveEdge[iTypeSize],
                       0,
                       param.spStain[iCam].ipRemoveEdge[iTypeSize],
                       mAdaptive.rows),
                  Scalar(0, 0, 0),
                  -1);

        qDebug()<<"12";

        rectangle(mAdaptive,
                  Rect(0,
                       mAdaptive.rows - param.spStain[iCam].ipRemoveEdge[iTypeSize],
                       mAdaptive.cols,
                       param.spStain[iCam].ipRemoveEdge[iTypeSize]),
                  Scalar(0, 0, 0),
                  -1);
        qDebug()<<"13";

        if(bDebug) {
            strFileSave = folderSaveStain + "/5_remove" + strFileName;
            imwrite(strFileSave.toStdString(), mAdaptive);
        }

        cvtColor(mAdaptive, sRes.mRes, CV_GRAY2BGR);


        Mat structElement = getStructuringElement(MORPH_RECT,Size(param.spStain[iCam].ipErodeSize[iTypeSize], param.spStain[iCam].ipErodeSize[iTypeSize]));
        erode(mAdaptive,mAdaptive,structElement,Point(-1,-1),param.spStain[iCam].ipErodeLoop[iTypeSize]);

        qDebug()<<"14";

        if(bDebug) {
            strFileSave = QString("%1/6_erode_%2").arg(folderSaveStain).arg(strFileName);
            imwrite(strFileSave.toStdString(), mAdaptive);
        }

        structElement = getStructuringElement(MORPH_RECT,Size(param.spStain[iCam].ipDilateSize[iTypeSize],param.spStain[iCam].ipDilateSize[iTypeSize]));
        dilate(mAdaptive,mAdaptive,structElement,Point(-1,-1),param.spStain[iCam].ipDilateLoop[iTypeSize]);

        qDebug()<<"15";

        if(bDebug) {
            strFileSave = QString("%1/7_dilate_%2").arg(folderSaveStain).arg(strFileName);
            imwrite(strFileSave.toStdString(), mAdaptive);
        }

        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;

        findContours(mAdaptive, contours, hierarchy, RETR_EXTERNAL,CHAIN_APPROX_NONE);

        qDebug()<<"16";
        if(!contours.empty()){
            cv::Rect blobRect;
            int iContourCnt = (int)contours.size();
            for (int i = 0; i<iContourCnt; i++) {
                blobRect = cv::boundingRect(contours[i]);
                if (param.spStain[iCam].ipFilterWMin[iTypeSize] > 0 && blobRect.width  < param.spStain[iCam].ipFilterWMin[iTypeSize])   continue;
                if (param.spStain[iCam].ipFilterHMin[iTypeSize] > 0 && blobRect.height < param.spStain[iCam].ipFilterHMin[iTypeSize])   continue;
                if (param.spStain[iCam].ipFilterWMax[iTypeSize] > 0 && blobRect.width  > param.spStain[iCam].ipFilterWMax[iTypeSize])   continue;
                if (param.spStain[iCam].ipFilterHMax[iTypeSize] > 0 && blobRect.height > param.spStain[iCam].ipFilterHMax[iTypeSize])   continue;

                int iContourArea = (int)cv::contourArea(contours[i]);
                if (param.spStain[iCam].ipFilterAreaMin[iTypeSize] > 0 && iContourArea < param.spStain[iCam].ipFilterAreaMin[iTypeSize]) continue;
                if (param.spStain[iCam].ipFilterAreaMax[iTypeSize] > 0 && iContourArea > param.spStain[iCam].ipFilterAreaMax[iTypeSize]) continue;

//                result_contours.push_back(contours[i]);
                cv::Rect rError = Rect(blobRect.x - param.ipPaintOffset,
                                       blobRect.y - param.ipPaintOffset,
                                       blobRect.width + 2*param.ipPaintOffset,
                                       blobRect.height + 2*param.ipPaintOffset);
                sRes.vRes.push_back(rError);

//                rectangle(sRes.mRes, rError, cv_aqua, param.ipPaintThickness);


            }

            if(!sRes.vRes.empty())
                sRes.bRes = false;
        }
        qDebug()<<"17";

        qDebug()<<strFileName<<"- Result-Stain: "<<sRes.bRes;

        if(bDebug) {
            strFileSave = folderSaveStain + "/8_Stain_" + strFileName;
            imwrite(strFileSave.toStdString(), sRes.mRes);

        }

        return sRes;
    }
    catch(cv::Exception& e) {
        QString strerror = QString::fromStdString(e.what());
        qDebug()<<"[Stain Error_Break]"<<strerror;
        return sRes;
    }
}

_sResVision MyVision::CheckWhiteStain(const cv::Mat mIn,  _sGeneral param, int iCam, int iTypeSize, QString strFileName, bool bDebug){

    _sResVision sRes;
    try{

        QString strFileSave = "";
        QString folderSaveWhiteStain = PATH_DB_WHITESTAIN;
        Mat mInput = mIn.clone();


        if(mInput.empty()) {
            qDebug()<<"Empty Input";
            return sRes;
        }
        if(mInput.channels() != 3) {
            qDebug()<<"Fail Input";
            return sRes;
        }
        else {
            cvtColor(mInput, mInput, CV_BGR2GRAY);
        }

        blur(mInput, mInput, Size(param.spWhiteStain[iCam].ipBlurSize[iTypeSize],param.spWhiteStain[iCam].ipBlurSize[iTypeSize]));

        //invert
        cv::bitwise_not(mInput,mInput);

//        mInput *=  mInput;
        mInput *=  1;

        if(bDebug) {
            strFileSave = folderSaveWhiteStain + "/1_Blur_bitwise_double" + strFileName;
            imwrite(strFileSave.toStdString(), mInput);
        }
        Mat mAdaptive;
        cv::adaptiveThreshold(mInput, mAdaptive,255, ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY_INV, param.spWhiteStain[iCam].ipBlockSize[iTypeSize], param.spWhiteStain[iCam].ipThreshold[iTypeSize]);


        if(bDebug) {
            strFileSave = folderSaveWhiteStain + "/2_adaptive" + strFileName;
            imwrite(strFileSave.toStdString(), mAdaptive);
        }
        rectangle(mAdaptive,
                  Rect(0,
                       0,
                       param.spWhiteStain[iCam].ipRemoveConner[iTypeSize],
                       param.spWhiteStain[iCam].ipRemoveConner[iTypeSize]),
                  Scalar(0, 0, 0),
                  -1);

        rectangle(mAdaptive,
                  Rect(mAdaptive.cols - param.spWhiteStain[iCam].ipRemoveConner[iTypeSize],
                       0,
                       param.spWhiteStain[iCam].ipRemoveConner[iTypeSize],
                       param.spWhiteStain[iCam].ipRemoveConner[iTypeSize]),
                  Scalar(0, 0, 0),
                  -1);

        rectangle(mAdaptive,
                  Rect(mAdaptive.cols - param.spWhiteStain[iCam].ipRemoveConner[iTypeSize],
                       mAdaptive.rows - param.spWhiteStain[iCam].ipRemoveConner[iTypeSize],
                       param.spWhiteStain[iCam].ipRemoveConner[iTypeSize],
                       param.spWhiteStain[iCam].ipRemoveConner[iTypeSize]),
                  Scalar(0, 0, 0),
                  -1);

        rectangle(mAdaptive,
                  Rect(0,
                       mAdaptive.rows - param.spWhiteStain[iCam].ipRemoveConner[iTypeSize],
                       param.spWhiteStain[iCam].ipRemoveConner[iTypeSize],
                       param.spWhiteStain[iCam].ipRemoveConner[iTypeSize]),
                  Scalar(0, 0, 0),
                  -1);

        rectangle(mAdaptive,
                  Rect(0,
                       0,
                       mAdaptive.cols,
                       param.spWhiteStain[iCam].ipRemoveEdge[iTypeSize]),
                  Scalar(0, 0, 0),
                  -1);
        rectangle(mAdaptive,
                  Rect(0,
                       0,
                       param.spWhiteStain[iCam].ipRemoveEdge[iTypeSize],
                       mAdaptive.rows),
                  Scalar(0, 0, 0),
                  -1);

        rectangle(mAdaptive,
                  Rect(mAdaptive.cols - param.spWhiteStain[iCam].ipRemoveEdge[iTypeSize],
                       0,
                       param.spWhiteStain[iCam].ipRemoveEdge[iTypeSize],
                       mAdaptive.rows),
                  Scalar(0, 0, 0),
                  -1);

        rectangle(mAdaptive,
                  Rect(0, mAdaptive.rows - param.spWhiteStain[iCam].ipRemoveEdge[iTypeSize], mAdaptive.cols, param.spWhiteStain[iCam].ipRemoveEdge[iTypeSize]),
                  Scalar(0, 0, 0),
                  -1);

        if(bDebug) {
            strFileSave = folderSaveWhiteStain + "/3_remove" + strFileName;
            imwrite(strFileSave.toStdString(), mAdaptive);
        }

        cv::cvtColor(mAdaptive, sRes.mRes,CV_GRAY2BGR);

        Mat structElement = getStructuringElement(MORPH_RECT,Size(param.spWhiteStain[iCam].ipErodeSize[iTypeSize], param.spWhiteStain[iCam].ipErodeSize[iTypeSize]));
        erode(mAdaptive, mAdaptive, structElement, Point(-1,-1), param.spWhiteStain[iCam].ipErodeLoop[iTypeSize]);

        if(bDebug) {
            strFileSave = QString("%1/4_erode_%2").arg(folderSaveWhiteStain).arg(strFileName);
            imwrite(strFileSave.toStdString(), mAdaptive);
        }

        structElement = getStructuringElement(MORPH_RECT, Size(param.spWhiteStain[iCam].ipDilateSize[iTypeSize], param.spWhiteStain[iCam].ipDilateSize[iTypeSize]));
        dilate(mAdaptive, mAdaptive, structElement, Point(-1,-1), param.spWhiteStain[iCam].ipDilateLoop[iTypeSize]);

        if(bDebug) {
            strFileSave = QString("%1/5_dilate_%2").arg(folderSaveWhiteStain).arg(strFileName);
            imwrite(strFileSave.toStdString(), mAdaptive);
        }

        vector<vector<Point> > contours;
//        vector<vector<Point> > result_contours;
        vector<Vec4i> hierarchy;
        findContours(mAdaptive, contours, hierarchy, RETR_LIST,CHAIN_APPROX_NONE);
        if(!contours.empty()){
            cv::Rect blobRect;
            int iContourCnt = (int)contours.size();
            for (int i = 0; i<iContourCnt; i++) {
                blobRect = cv::boundingRect(contours[i]);
                if (param.spWhiteStain[iCam].ipFilterWMin[iTypeSize] > 0 && blobRect.width < param.spWhiteStain[iCam].ipFilterWMin[iTypeSize]) continue;
                if (param.spWhiteStain[iCam].ipFilterHMin[iTypeSize] > 0 && blobRect.height < param.spWhiteStain[iCam].ipFilterHMin[iTypeSize]) continue;
                if (param.spWhiteStain[iCam].ipFilterWMax[iTypeSize] > 0 && blobRect.width > param.spWhiteStain[iCam].ipFilterWMax[iTypeSize]) continue;
                if (param.spWhiteStain[iCam].ipFilterHMax[iTypeSize] > 0 && blobRect.height > param.spWhiteStain[iCam].ipFilterHMax[iTypeSize]) continue;

                int iContourArea = (int)cv::contourArea(contours[i]);
                if (param.spWhiteStain[iCam].ipFilterAreaMin[iTypeSize] > 0 && iContourArea < param.spWhiteStain[iCam].ipFilterAreaMin[iTypeSize]) continue;
                if (param.spWhiteStain[iCam].ipFilterAreaMax[iTypeSize] > 0 && iContourArea > param.spWhiteStain[iCam].ipFilterAreaMax[iTypeSize]) continue;

//                result_contours.push_back(contours[i]);
                cv::Rect rError = Rect(blobRect.x - param.ipPaintOffset,
                                       blobRect.y - param.ipPaintOffset,
                                       blobRect.width + 2*param.ipPaintOffset,
                                       blobRect.height + 2*param.ipPaintOffset);
                sRes.vRes.push_back(rError);
                rectangle(sRes.mRes, rError, cv_red, param.ipPaintThickness);
            }
            if(!sRes.vRes.empty())
                sRes.bRes = false;
        }
        qDebug()<<strFileName<<"- Result-WhiteStain: "<<sRes.bRes;


        if(bDebug) {
            strFileSave = folderSaveWhiteStain + "/WhiteStain_" + strFileName;
            imwrite(strFileSave.toStdString(), sRes.mRes);

        }
        return sRes;
    }
    catch(cv::Exception& e) {
        QString strerror = QString::fromStdString(e.what());
        qDebug()<<"[WhiteStain Error]"<<strerror;
        return sRes;
    }
}

_sResVision  MyVision::CheckGlare(const cv::Mat mIn, _sGeneral param, int iCam, QString strFileName, bool bDebug){
    _sResVision sRes;
    try{
        QString strFileSave = "";
        QString folderSaveGlare = PATH_DB_GLARE;
        Mat mInput = mIn.clone();

        if(mInput.empty()) {
            qDebug()<<"Empty Input";
            return sRes;
        }

        if(mInput.channels() != 3){
//            qDebug()<<"Fail Input";
//            return sRes;
        }
        else{
            sRes.mRes = mInput.clone();
            cvtColor(mInput, mInput, CV_BGR2GRAY);

        }

        if(bDebug) {
            strFileSave = folderSaveGlare + QString("/0_Input")+ strFileName;
            imwrite(strFileSave.toStdString(), mInput);
        }

        int iHoleNo = 4;
        if(param.Device.ipModel == G960) iHoleNo = 6;

        for(int j = 0; j < iHoleNo ; j++) {
            Mat mCheck = mInput(param.spGlare[iCam].rpRoi[j]);
            if(bDebug) {
                strFileSave = folderSaveGlare + QString("/1_Crop_R%1").arg(j+1) + strFileName;
                imwrite(strFileSave.toStdString(), mCheck);
            }

//            int iMean = Mean(mCheck,mCheck);
//            if (param.spGlare[iCam].ipgMSRoiMin[j] > 0 && iMean < param.spGlare[iCam].ipgMSRoiMin[j]){
//                sRes.vRes.push_back(param.spGlare[iCam].rpRoi[j]);
//                rectangle(sRes.mRes, param.spGlare[iCam].rpRoi[j], cv_orange, param.ipPaintThickness);
//                continue;
//            }

//            else if (param.spGlare[iCam].ipgFilterAreaMax[j] > 0 && iMean > param.spGlare[iCam].ipgFilterAreaMax[j]){
//                sRes.vRes.push_back(param.spGlare[iCam].rpRoi[j]);
//                rectangle(sRes.mRes, param.spGlare[iCam].rpRoi[j], cv_orange, param.ipPaintThickness);
//                continue;
//            }

            Mat mThreshold;
            cv::threshold(mCheck, mThreshold, param.spGlare[iCam].ipgThreshold[j], 255, THRESH_BINARY);

            if(bDebug) {
                strFileSave = folderSaveGlare + QString("/2_threshold_R%1").arg(j+1) + strFileName;
                imwrite(strFileSave.toStdString(), mThreshold);
            }

            Mat structElement = getStructuringElement(MORPH_RECT, Size(param.spGlare[iCam].ipgErodeSize[j], param.spGlare[iCam].ipgErodeSize[j]));
            erode(mThreshold, mThreshold, structElement, Point(-1,-1), param.spGlare[iCam].ipgErodeLoop[j]);

            if(bDebug) {
                strFileSave = folderSaveGlare + QString("/3_erode_R%1").arg(j+1) + strFileName;
                imwrite(strFileSave.toStdString(), mThreshold);
            }

            structElement = getStructuringElement(MORPH_RECT, Size(param.spGlare[iCam].ipgDilateSize[j], param.spGlare[iCam].ipgDilateSize[j]));
            dilate(mThreshold, mThreshold, structElement, Point(-1,-1), param.spGlare[iCam].ipgDilateLoop[j]);

            if(bDebug) {
                strFileSave = folderSaveGlare + QString("/4_dilate_R%1").arg(j+1) + strFileName;
                imwrite(strFileSave.toStdString(), mThreshold);
            }

            vector<vector<Point> > contours;
            vector<Vec4i> hierarchy;
            findContours(mThreshold, contours, hierarchy, RETR_LIST, CHAIN_APPROX_NONE);
            qDebug() << contours.size();

            if(contours.empty()){ return sRes; }
            else{
                cv::Rect blobRect;
                int iContourCnt = (int)contours.size();
                for (int i = 0; i<iContourCnt; ++i) {

                    blobRect = cv::boundingRect(contours[i]);
                    if (param.spGlare[iCam].ipgFilterWMin[j] > 0 && blobRect.width < param.spGlare[iCam].ipgFilterWMin[j]) continue;
                    if (param.spGlare[iCam].ipgFilterHMin[j] > 0 && blobRect.height < param.spGlare[iCam].ipgFilterHMin[j]) continue;
                    if (param.spGlare[iCam].ipgFilterWMax[j] > 0 && blobRect.width > param.spGlare[iCam].ipgFilterWMax[j]) continue;
                    if (param.spGlare[iCam].ipgFilterHMax[j] > 0 && blobRect.height > param.spGlare[iCam].ipgFilterHMax[j]) continue;

                    int iContourArea = (int)cv::contourArea(contours[i]);
                    if (param.spGlare[iCam].ipgFilterAreaMin[j] > 0 && iContourArea < param.spGlare[iCam].ipgFilterAreaMin[j]) continue;
                    if (param.spGlare[iCam].ipgFilterAreaMax[j] > 0 && iContourArea > param.spGlare[iCam].ipgFilterAreaMax[j]) continue;

                    sRes.vRes.push_back(param.spGlare[iCam].rpRoi[j]);
                    rectangle(sRes.mRes, param.spGlare[iCam].rpRoi[j], cv_orange, param.ipPaintThickness);
                }
            }
        }
        if(bDebug) {
            strFileSave = folderSaveGlare + "/5_Glare_Result" + strFileName;
            imwrite(strFileSave.toStdString(), sRes.mRes);
        }

        if(!sRes.vRes.empty()){
            sRes.bRes = false;
        }
        return sRes;
    }
    catch(cv::Exception& e) {
        QString strerror = QString::fromStdString(e.what());
        qDebug()<<"[Glare Error]"<<strerror;
        return sRes;
    }
}

_sResVision MyVision::CheckDarkspot(const cv::Mat mIn , _sGeneral param, int iCam, QString strFileName, bool bDebug){
    _sResVision sRes;
    try{
        QString strFileSave = "";
        QString folderSaveDarkspot = PATH_DB_DARKSPOT;
        Mat mInput = mIn.clone();
        /*Check Image*/
        if(mInput.empty()) {
            qDebug()<<"Empty Input";
            return sRes;
        }
        /*Convert Color*/
        if(mInput.channels() != 3) {
            qDebug()<<"Fail Input";
            return sRes;
        }
        else {
            sRes.mRes = mInput.clone();
            cvtColor(mInput, mInput, CV_BGR2GRAY);
        }

        Mat mAdaptive, mAdaptive2;
        cv::adaptiveThreshold(mInput, mAdaptive, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, param.spDarksport[iCam].ipdsBlockSize, param.spDarksport[iCam].ipdsThreshold);

        if(bDebug) {
            strFileSave = folderSaveDarkspot + "/2_adaptive" + strFileName;
            imwrite(strFileSave.toStdString(), mAdaptive);
        }

        cv::threshold(mInput, mAdaptive2, param.spDarksport[iCam].ipdsThreshold, 255, THRESH_BINARY_INV);
        if(bDebug) {
            strFileSave = folderSaveDarkspot + "/3_Threshold" + strFileName;
            imwrite(strFileSave.toStdString(), mAdaptive2);
        }

        Mat structElement = getStructuringElement(MORPH_RECT, Size(3, 3));
        dilate(mAdaptive2, mAdaptive2, structElement, Point(-1,-1),5);

        if(bDebug) {
            strFileSave = folderSaveDarkspot + "/21_mor_bit" + strFileName;
            imwrite(strFileSave.toStdString(), mAdaptive2);
        }

        vector<vector<Point> > contours, contours2;
        vector<vector<Point> > result_contours;
        vector<Vec4i> hierarchy;

        findContours(mAdaptive2, contours2, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        findContours(mAdaptive, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        contours.insert(contours.end(), contours2.begin(), contours2.end());

        Mat mContour;
        if(!contours.empty()){
            cv::Rect blobRect;
            int iContourCnt = (int)contours.size();
            for (int i = 0; i<iContourCnt; i++) {

                blobRect = cv::boundingRect(contours[i]);

                mContour = Mat::zeros(mAdaptive.size(), mAdaptive.type());

                drawContours(mContour, contours, i, Scalar::all(255), -1);

                int iContourArea = countNonZero(mContour);

                if (iContourArea < param.spDarksport[iCam].ipdsFilterAreaMin && param.spDarksport[iCam].ipdsFilterAreaMin > 0) continue;

                if (iContourArea > param.spDarksport[iCam].ipdsFilterAreaMax && param.spDarksport[iCam].ipdsFilterAreaMax > 0 ) continue;

                result_contours.push_back(contours[i]);

                cv::Rect rError = Rect(blobRect.x - param.ipPaintOffset, blobRect.y - param.ipPaintOffset, blobRect.width + 2*param.ipPaintOffset, blobRect.height + 2*param.ipPaintOffset);

                sRes.vRes.push_back(rError);
                rectangle(sRes.mRes, rError, cv_purple, param.ipPaintThickness);

                mContour.release();
            }
            if(!sRes.vRes.empty())
                sRes.bRes = false;
        }

        qDebug()<<strFileName<<"- Result-Darkspot: "<<sRes.bRes << sRes.vRes.size();
        if(bDebug) {
            strFileSave = folderSaveDarkspot + "/Darkspot_" + strFileName;
            imwrite(strFileSave.toStdString(), sRes.mRes);
        }
        return sRes;
    }
    catch(cv::Exception& e) {
        QString strerror = QString::fromStdString(e.what());
        qDebug()<<"[Darkspot Error]"<<strerror;
        return sRes;
    }
}

_sResVision MyVision::CheckColor(const cv::Mat mIn, _sGeneral param, int iCam, QString strFileName, bool bDebug) {
    _sResVision sRes;
    try{
        QString strFileSave = "";
        QString folderSaveWrongColor = PATH_DB_COLOR;
        Mat mInput = mIn.clone();
        if(mInput.empty()) {
            qDebug()<<"Empty Input";
            return sRes;
        }
        if(mInput.channels() != 3){
            qDebug()<<"Fail Input";
            return sRes;
        }
        sRes.mRes = mInput.clone();
        cv::Scalar meanVal = cv::mean(mInput);
        qDebug()<<"blue = "<<meanVal[0]<<" - green = "<<meanVal[1]<<" - red = "<<meanVal[2];
        if(meanVal[0] >= param.spWrongColor[iCam].ipwcMeanBlueMin
           && meanVal[0] <= param.spWrongColor[iCam].ipwcMeanBlueMax
           && meanVal[1] >= param.spWrongColor[iCam].ipwcMeanGreenMin
           && meanVal[1] <= param.spWrongColor[iCam].ipwcMeanGreenMax
           && meanVal[2] >= param.spWrongColor[iCam].ipwcMeanRedMin
           && meanVal[2] <= param.spWrongColor[iCam].ipwcMeanRedMax) {
            qDebug()<<"OK";
            sRes.bRes = true;
        }
        else {
            qDebug()<<"NG";
            sRes.bRes = false;
        }
        qDebug()<<strFileName<<"- Result-WrongColor: "<<sRes.bRes;
        if(bDebug) {
            QString str = QString("b = %1, g = %2, r = %3").arg(meanVal[0]).arg(meanVal[1]).arg(meanVal[2]);
            putText(sRes.mRes, str.toStdString(), Point(100,100), CV_FONT_HERSHEY_COMPLEX, 2.5, cv_red, 5);

            strFileSave = folderSaveWrongColor + "/WrongColor_" + strFileName;
            imwrite(strFileSave.toStdString(), sRes.mRes);
        }
        return sRes;
    }
    catch(cv::Exception& e) {
        QString strerror = QString::fromStdString(e.what());
        qDebug()<<"[CheckColor Error]"<<strerror;
        return sRes;
    }
}

_sResVision MyVision::CheckFocus(const Mat mIn, _sGeneral param, int iCam, QString strFileName, bool bDebug) {
    _sResVision sRes;
    try{
        cv::Mat     mLaplace;
        cv::Scalar  mean        = cv::Scalar(0,0,0);
        cv::Scalar  std         = cv::Scalar(0,0,0);
        cv::Mat mInput = mIn.clone();

        if(mInput.channels() != 3) {
            qDebug()<<"Fail Input";
            return sRes;
        }
        else {
            sRes.mRes = mInput.clone();
            cvtColor(mInput, mInput, CV_BGR2GRAY);
        }

        for(int i = 0; i<NUM_ROI; i++){
            cv::Mat mCheck = mInput(param.spFocus[iCam].rpRoi[i]);
            cv::Laplacian(mCheck,mLaplace,CV_16S);
            cv::meanStdDev(mLaplace, mean, std);
            double blurMeasure = std.val[0] * std.val[0];
            sRes.vStd.push_back(blurMeasure);
            if((blurMeasure < param.spFocus[iCam].ipgMSRoiMin[i] && param.spFocus[iCam].ipgMSRoiMin[i] > 0 )
            || (blurMeasure > param.spFocus[iCam].ipgMSRoiMax[i] && param.spFocus[iCam].ipgMSRoiMax[i] > 0)){
                sRes.bRes =  false;
                rectangle(sRes.mRes,param.spFocus[iCam].rpRoi[i],cv_blue, param.ipPaintThickness);
                putText(sRes.mRes,"Std = " + Double2QString(blurMeasure).toStdString(), Point(5,100),CV_FONT_HERSHEY_COMPLEX, 3,cv_red,2);
//                break;
            }
            else{
                rectangle(sRes.mRes,param.spFocus[iCam].rpRoi[i],cv_green, param.ipPaintThickness);
                putText(sRes.mRes,"Std = " + Double2QString(blurMeasure).toStdString(), Point(5,100),CV_FONT_HERSHEY_COMPLEX, 3,cv_green,2);
            }
        }
        return sRes;
    }
    catch(Exception e){
        QString strerror = QString::fromStdString(e.what());
        qDebug()<<"[Focus Error_Break]"<<strerror;
        return sRes;
    }
}



