#ifndef PROCESSCAM_H
#define PROCESSCAM_H

#include <QThread>
#include <QElapsedTimer>
#include "myDefine.h"
#include "myvision.h"
#include "process.h"
#include "processcheckauto.h"

class MainWindow;
class aProcessDarkSpot;
class aProcessSStain;
class aProcessWhiteSStain;
class aProcessLStain;
class aProcessWhiteLStain;
class aProcessWrongColor;
class aProcessGlare;
class aProcessFocus;
class aProcessDoThing;
class aProcessDoThingWait;

struct _sDeviceParam {
    int ipModel = N960;
    bool bUseComIO = false;
    bool bUseComSocket = true;
    QString qstrComIO = "";
    QString qstrComport = "COM1";
    QString qstrID = "";
    QString qstrKeyStart = "1";
    QString qstrKeyStop = "Esc";
    QString qstrFolderInput = "";
    QString qstrFolderOutput = "";
    QString qstrFolderPhone  = "";
    QSerialPort *qspComIO;
    QSerialPort *qspCom;
    QProcess *qpAuADB;
};

struct _sMainUI {
    QLabel *lbDisplay;
    QLabel *lbDisplayGlare;
    QLabel *lbProcess;
    QLabel *lbResIris;
    QLabel *lbStain;
    QLabel *lbWhiteStain;
    QLabel *lbResGlare;
    QLabel *lbFocus;
    QLabel *lbColor;
    QLabel *lbDarkSport;
    QTableWidget *tbLog;
    QTableWidget *tbError;
    QToolButton *btnInit;
};

class ProcessCam : public QThread  {
      Q_OBJECT
public: /* varible*/
    ProcessCam(_sMainUI stranMainUi, _sDeviceParam stransDevice, int itransSide, _sGeneral stransGeneral);
    ~ProcessCam();

    _sGeneral mGenenal;
    _sDeviceParam mDevice;
    _sDataCom ADBcommand[NUM_ADB], ATcommand[NUM_AT];

    MTickTimer delay_thread;
    QProcess *processADB;
    QSerialPort *qspCom;

    /*data com all*/
    QString qstrDataCom;

    QString strErr[NUM_CAM] = {"",""};
    bool m_bRun = false;
    bool bErrproc = false;

    /*opt var*/
    bool bShowImg[NUM_CAM] = {false};
    bool bSaveImg[NUM_CAM] = {false};
    bool bCheckIris = true;
    bool bCheckStain[NUM_CAM] = {false};
    bool bCheckWhiteStain[NUM_CAM] = {false};
    bool bCheckGlare[NUM_CAM] = {false};
    bool bCheckFocus[NUM_CAM] = {false};
    bool bCheckColor[NUM_CAM] = {false};
    bool bCheckDarkSport[NUM_CAM] = {false};
    bool bCaptureUseAF[NUM_CAM] = {false};
    bool bResultCam[NUM_CAM] = {false};
    bool bSaveImgResize = false;

    int proc_Error = NONE;
    int vision_Error[NUM_CAM] ={no_Err};
    int iTotalCam = FW1;
    int iSide = SIDE_LEFT;
    int numCap[NUM_CAM] = {2,2};
    int iTotalImg = 2;
    int iCurrentCam = FW1;
    vector<QString> vImageFile;
    cv::Mat mImread[NUM_CAM][NUM_IMG];
    _sMainUI linkMain;

public:
    bool bCheckResultStain[NUM_CAM] = {false};
    bool bCheckResultWhiteStain[NUM_CAM] = {false};
    bool bCheckResultGlare[NUM_CAM] = {false};
    bool bCheckResultFocus[NUM_CAM] = {false};
    bool bCheckResultColor[NUM_CAM] = {false};
    bool bCheckResultDarkSport[NUM_CAM] = {false};

public: /*fuction*/
    void StartThread();
    void StopThread();
    void SetStep(int iStep);
    void AddLog(QString str, QColor iColor);
    void WriteLogFileID(QString data);
    void saveResultImg(QString strIDmd, QString nameCam, Mat img, bool bType);

    QString splitStrCom(QString str);
    vector<QString> GetAllFileInFolder(QString folder);

public:
    void initThread();
    ThreadIO *ptrIO = nullptr;
    QThread *thread = nullptr;
    bool bCheckCam[NUM_CAM] = {false, false};

protected:
    void run();
    int iCurStep = LOOP_DOTHING;
    QString qstrLogUI = "";

private: /*Var*/
    QString qstrDataADB;
    QString qstrlogFileID = "";
    MyVision myVision;
    QMutex mutexADB;
    cv::Mat mStart, mStop, mError, mDontUse, mWait, mNG, mOK;
    cv::Mat mImSave[NUM_CAM][NUM_IMG];

/*Var Special*/

    aProcessSStain *pSStain[NUM_CAM];

    aProcessWhiteSStain *pWhiteSStain[NUM_CAM];

    aProcessLStain *pLStain[NUM_CAM];

    aProcessWhiteLStain *pWhiteLStain[NUM_CAM];

    aProcessDarkSpot *pDarkspot[NUM_CAM];

    aProcessWrongColor *pWrongColor[NUM_CAM];

    aProcessGlare *pGlare[NUM_CAM];

    aProcessFocus *pFocus[NUM_CAM];

/*Var Result Handle*/
    vector<Rect> vStain[NUM_CAM][NUM_TYPE];

    vector<Rect> vWhiteStain[NUM_CAM][NUM_TYPE];

    vector<Rect> vGlare[NUM_CAM];

    vector<Rect> vDarkpot[NUM_CAM];

    vector<Rect> vFocus[NUM_CAM];

    bool bWrongColor [NUM_CAM];

    QFile qflogFileID;

    QMutex qmutexCom;

    int fCapCount = 0;

private:
    void LoopProcess();

    void InitMat();

    void ResetStatus();

    void ResetTbwErr();

    void InitUI();

    void ProcessFW1();

    void ProcessFB1();

    void ProcessFW1Wait();

    void ProcessFB1Wait();

private slots:
    void readDataComport();

    void readDataCmd();

    void handleComportError(QSerialPort::SerialPortError serialPortError);

    void handleComportIO();

    void handleCmdError(QProcess::ProcessError processError);

    void SendCom(QSerialPort* pCom, QString data);

    void SendADB(QString strIn);

    void SetResultUI(QLabel *label, QString str, int iColor);


    void slotTbLog();

    void Display_Image(Mat m, QLabel* lb);

    void SetResultTbw(QPoint PosNotify, QString qstrConTent, QColor qColor);

    void SetReultHeaderTbw(int iCamNo, QString qstrConTent, QColor qColor);


/*Fuction Check Error*/
    /*FW1*/
    void visionSStainFW1(int Img);

    void visionWhiteSStainFW1(int Img);

    void visionLStainFW1(int Img);

    void visionWhiteLStainFW1(int Img);

    void visionGlareFW1(int Img);

    void visionFocusFW1(int Img);

    void visionDarkpotFW1(int Img);

    void visionColorFW1(int Img);


    /*FB1*/
    void visionSStainFB1(int Img);

    void visionWhiteSStainFB1(int Img);

    void visionLStainFB1(int Img);

    void visionWhiteLStainFB1(int Img);

    void visionGlareFB1(int Img);

    void visionFocusFB1(int Img);

    void visionDarkpotFB1(int Img);

    void visionColorFB1(int Img);

    /*Comon*/
    void FinishProcess();


signals:

    void eSendCOM(QSerialPort* pPort, QString qstr);

    void eSendADB(QString strIn);

    void eSetResultUI(QLabel *label, QString qstr, int iColor);

    void eSetResultCam(QPushButton* btn,QString qstr);

    void eDisplayImage(Mat m, QLabel* lb);

    void eSetReultTbw(QPoint PosNotify, QString qstrConTent, QColor qColor);

    void logUI(QString str, int iColor);

    void emitThreadIO(QString str);

    void eFinishProcess();


};

#endif // PROCESSCAM_H
