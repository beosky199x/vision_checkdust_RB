#ifndef MYDEFINE_H
#define MYDEFINE_H

#include <opencv2/opencv.hpp>
#include <QTextStream>
#include <QString>
#include <QtWidgets>
#include <vector>
#include <QString>
#include <iostream>
#include <string>
#include <QKeyEvent>
#include <QObject>
#include <QCloseEvent>
#include <QPainter>
#include "MTickTimer.h"
#include <QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QFileDialog>
#include <QMouseEvent>

using namespace cv;
using namespace std;

/*Define Error slot*/
#define RES_IRIS_FW1                QPoint(0,0)
#define RES_STAIN_FW1               QPoint(1,0)
#define RES_WHITESTAIN_FW1          QPoint(2,0)
#define RES_GLARE_FW1               QPoint(3,0)
#define RES_FOCUS_FW1               QPoint(4,0)
#define RES_COLOR_FW1               QPoint(5,0)
#define RES_DARKSPORT_FW1           QPoint(6,0)

#define RES_IRIS_FB1                QPoint(0,1)
#define RES_STAIN_FB1               QPoint(1,1)
#define RES_WHITESTAIN_FB1          QPoint(2,1)
#define RES_GLARE_FB1               QPoint(3,1)
#define RES_FOCUS_FB1               QPoint(4,1)
#define RES_COLOR_FB1               QPoint(5,1)
#define RES_DARKSPORT_FB1           QPoint(6,1)

//Camera
#define NUM_CAM                            2
#define NUM_TYPE                           2
#define NUM_IMG                            2
#define NUM_SIDE                           2
#define NUM_PARA                           3
#define NUM_ROI                            6
#define NUM_DELAY                          30
#define NUM_HOLE                           4
#define NUM_CHECKBOX                       10
#define NUM_LINEDIT                        150
#define NUM_COMBOBOX                       15
#define NUM_AT                             11
#define NUM_ADB                            3
// define input Module IO
#define Input_1                            0b00000001                  /* start*/
#define Input_2                            0b00000010                  /* Sensor clynder back*/
#define Input_3                            0b00000100                  /* Sensor clynder for*/
#define Input_4                            0b00001000
#define Input_5                            0b00010000
#define Input_6                            0b00100000
// define output Module IO
#define GetValue                           "I"
#define Output1_ON                         "A"                         /* Sol On*/
#define Output1_OFF                        "a"                         /* Sol Off*/
#define Output2_ON                         "B"                         /* Led On*/
#define Output2_OFF                        "b"                         /* Led Off*/
#define Output3_ON                         "C"
#define Output3_OFF                        "c"
#define Output4_ON                         "D"
#define Output4_OFF                        "d"
#define Output5_ON                         "E"
#define Output5_OFF                        "e"
#define Output6_ON                         "F"
#define Output6_OFF                        "f"
#define Output7_ON                         "G"
#define Output7_OFF                        "g"

//*************************** //*************************** //*************************** //***************************
//Parameter path
#define PATH_COMMON                        "./Parameter/ParamGeneral.json"
#define PATH_GENERAL                       "./Parameter/%1/"
#define PATH_NAME                          "ParamModel.json"
#define PATH_GRAP                          "./Result/Image"
#define PATH_LEFT                          "./Parameter/Left/Param.json"
#define PATH_RIGHT                         "./Parameter/Right/Param.json"
#define LEFT_PATTERN                       "./Parameter/Left/Pattern.jpg"
#define RIGHT_PATTERN                      "./Parameter/Right/Pattern.jpg"
#define LEFT_Folder                        "./Parameter/Left/"
#define RIGHT_Folder                       "./Parameter/Right/"
#define PATH_OK                            "./Result/OK"
#define PATH_NG                            "./Result/NG"
#define PATH_DB                            "D:/Image/Debug"
#define PATH_DB_STAIN                      "D:/Image/Debug/Stain"
#define PATH_DB_WHITESTAIN                 "D:/Image/Debug/White-Stain"
#define PATH_DB_DARKSPOT                   "D:/Image/Debug/Darkspot"
#define PATH_DB_COLOR                      "D:/Image/Debug/Color"
#define PATH_DB_GLARE                      "D:/Image/Debug/Glare"
#define PATH_DB_ATK                        "D:/atk"
//*************************** //*************************** //*************************** //***************************
// const
const QString   strBorder                 = ";border-radius: 12px;background-color: rgb(170, 255, 127);";
const QString   strBorderResult           = "border-radius: 5px;background-color: rgb(0, 85, 127);padding-left:5px;";
const QString   strBorderError            = "color: red;border-radius: 12px;background-color: rgb(170, 255, 127);";
const QString   listModel[]               = {
    "G950",
    "G960",
    "J500",
    "J700",
    "G955",
    "G965",
    "N960",
    "N975",
    "G970",
    "G973",
    "A102",
    "A505",
    "G975",
};


const QStringList   qstrlistModel        = {
    "G950",
    "G960",
    "J500",
    "J700",
    "G955",
    "G965",
    "N960",
    "N975",
    "G970",
    "G973",
    "A102",
    "A505",
    "G975"
};

enum _eListModel {

    G950,
    G960,
    J500,
    J700,
    G955,
    G965,
    N960,
    N975,
    G970,
    G973,
    A102,
    A505,
    G975
};

const QString   listErrorProc[]           = {
    "None",
    "Prepare",
    "Open Iris",
    "Close Iris",
    "Open FW1",
    "Close FW1",
    "Open FB1",
    "Close FB1",
    "Clynder Forward",
    "Clynder Backward",
    "Capture",
    "Get List",
    "Pull2PC",
    "Load Image",
    "Process",

};
const QString   listCam[]                 = {
    "FW1",
    "FB1"
};
const QString   listProc[]                = {
    "None",
    "Prepare",
    "Open\r\nIris",
    "Close\r\nIris",
    "Open\r\nFW1",
    "Close\r\nFW1",
    "Open\r\nFB1",
    "Close\r\nFB1",
    "CLD\r\nFW",
    "CLD\r\nBW",
    "Capture",
    "Get\r\nList",
    "Pull\r\nPC",
    "Load\r\nIMG",
    "Process"
};
const QString   listAT[] = {
    // all list AT in combobox manual.
    "AT+SWATD=1",                           /* UART by USB*/
    "AT+SWATD=0",                           /* UART by UART*/
    "AT+CAMETEST=0,1,0,3",                  /* open iris */
    "AT+CAMETEST=0,9,3,0",                  /* close iris */
    "AT+CAMETEST=0,1,0,0",                  /* open front */
    "AT+CAMETEST=0,9,0,0",                  /* close front */
    "AT+CAMETEST=0,1,2,0",                  /* capture front use AF */
    "AT+CAMETEST=0,1,2,3",                  /* capture front dont use AF */
    "AT+NCAMTEST=0,0,1,FW1",                /* OPEN CAM FRONT FW1 */
    "AT+NCAMTEST=0,0,1,FB1",                /* OPEN CAM FRONT FB1 */
    "AT+NCAMTEST=0,0,1,0",                  /* CLOSE CAM */
    "AT+NCAMTEST=0,1,0,0",                  /* CAPTURE WITH AF */
    "AT+NCAMTEST=0,1,0,1",                  /* CAPTURE WITHOUT AF */
    "AT+NCAMTEST=0,1,0,2",                  /* CAPTURE WITH TRY AF */
    "AT+FUNCTEST=0,0",                      /* Home screen */
    "AT+DISPTEST=0,4",                      /* off screen */
    "AT+DISPTEST=0,3",                      /* on screen */
    "A",                                    /* Out1: On */
    "a",                                    /* Out1: Off */
    "B",                                    /* Out2: On */
    "b",                                    /* Out2: Off */
    "C",                                    /* Out3: On */
    "c",                                    /* Out3: Off */
    "D",                                    /* Out4: On */
    "d",                                    /* Out4: Off */
    "E",                                    /* Out5: On */
    "e",                                    /* Out5: Off */
    "F",                                    /* Out6: On */
    "f",                                    /* Out6: Off */
    "G",                                    /* Out7: On */
    "g",                                    /* Out7: Off */
};
const QString   listADB[] = {
    "adb -s %1 shell ls /storage/emulated/0/fImage",            /*lisrt image from fImage folder*/
    "adb -s %1 pull /storage/emulated/0/fImage D:/atk",         /*pull file from fImage to PC*/
    "adb -s %1 shell rm -r /storage/emulated/0/fImage",         /*remove folder*/
    "adb kill-server",                                          /*kill-server*/
    "adb -s %1 shell dumpsys display | find \"mScreenState\"",  /*kill-server*/
    "adb -s %1 shell input keyevent 26",                        /*lock-unlock*/
    "adb -s %1 shell input keyevent 26",                        /*lock-unlock*/
    "adb -s %1 shell rm -r /storage/emulated/0/log",            /*remove log*/
};
const QString   nameSide[] = {
    "Socket 1",
    "Socket 2"
};

/* enum*/
enum _elistTypeImage{
    IMG_CHECK_STEP1,    /*STEP1: Check Dust, Stain, Color*/
    IMG_CHECK_STEP2     /*STEP2: Check Glare, Focus*/
};
enum _elistProc {
    NONE,
    PREPARE,
    OPEN_IRIS,
    CLOSE_IRIS,
    OPEN_FW1,
    CLOSE_FW1,
    OPEN_FB1,
    CLOSE_FB1,
    CLD_FW,
    CLD_BW,
    CAPTURE,
    GETLIST,
    PULL2PC,
    LOADIMG,
    PROCESS,
};
enum _eSide {
    SIDE_LEFT,
    SIDE_RIGHT,
    PARA_CONTAIN,
    SIDE_IMAGE
};
enum _eImg {
    FW1_FUCTIONCHECK,
    FW1_GLAREFOCUS,

    FB1_FUCTIONCHECK,
    FB1_GLAREFOCUS
};

enum _eCam {
    CAM_LEFT,
    CAM_RIGHT
};
enum _eBinaryType {
    BINARY=0,  /**< value = CAM_TELE  > threshold ? max_value : 0       */
    BINARY_INV,  /**< value = value > threshold ? 0 : max_value       */
    OTSU, /**< use Otsu algorithm to choose the optimal threshold value;
                                 combine the flag with one of the above CV_THRESH_* values */
    TRIANGLE, /**< use Triangle algorithm to choose the optimal threshold value;
                                 combine the flag with one of the above CV_THRESH_* values, but not
                                 with CV_THRESH_OTSU */
    ADAPTIVE
};

enum _eDlg {
    AUTO,
    MANUAL,
    TEACH,
    DATA,
};
enum _eResult {
    NG,
    OK,
    WAIT,
    RUN,
    STOP
};
enum _eTimer {
    TIME_SYSTEM = 1000,
    TIME_WAIT_RESULT = 500,
    TIME_WAIT_RESULT_THREAD = 2
};
enum _eVision_Err {
    no_Err         = 0b00000000,
    err_St         = 0b00000001,
    err_WSt        = 0b00000010,
    err_Dp         = 0b00000100,
    err_WC         = 0b00001000,
    err_WG         = 0b00010000,
    err_Fs         = 0b00100000,
};
enum _eLastButton {
    Btn_None,
    Btn_Stain,
    Btn_WhiteStain,
    Btn_Darkspot,
    Btn_WrongColor,
    btn_Focus,
    Btn_Glare
};
enum _eCodeRun {
    RUN_MANUAL_TEST,
};
enum _ePosATcmd {
    AT_UART_USB,
    AT_HOMECREEN,
    AT_OPENIRIS,
    AT_CLOSEIRIS,
    AT_OPENFW1,
    AT_CLOSEFW1,
    AT_OPENFB1,
    AT_CLOSEFB1,
    AT_CAPTURENOAF,
    AT_CAPTUREAF,
    AT_CAPTURETRYAF
};
enum _ePositionADB {
    ADB_GET_LIST,
    ADB_PULL_TO_PC,
    ADB_REMOVE_FOLDER,
    ADB_KILL_SERVER,
    ADB_STATUS_SCREEN,
    ADB_UNLOCK_PHONE,
    ADB_LOCK_PHONE,
    ADB_REMOVE_LOG
};
enum _eRespone {
    RES_NONE = -1,
    RES_NG,
    RES_OK,
    RES_TIMEOUT
};

// UPDATE HERE !!!!!!!!!
enum _ePara {
    _SETTING_CAMERA,
    _OPTION,
    _DELAY_TIME,
    _PARA_PAINT,
    _PARA_NORMALIZE,
    _PARA_STAIN,
    _PARA_WHITESTAIN,
    _PARA_GLARE,
    _PARA_FOCUS,
    _PARA_DARKSPORT,
    _PARA_WRONGCOLOR,
    _PARA_ATCMD,
    _PARA_ADBCMD
};

enum _eCbsymbol {
    _SHOW_IMG,
    _SAVE_IMG,
    _CHECK_IRIS,
    _CHECK_STAIN,
    _CHECK_WHITESAIN,
    _CHECK_GLARE,
    _CHECK_FOCUS,
    _CHECK_COLOR,
    _CHECK_DARKSPORT,
    _CAP_AF
};

enum _etypeblur {
    BLUR,
    GAUSSIAN,
    MEDIAN,
    BOX,
    BILATERAL,
    NONLINEARDIFF
};

enum _ecbbsymbol {
    CAMERA_TYPE,
    NOR_TYPE,
    STAIN_SIZE,
    WSTAIN_SIZE,
    ROI_GLARE,
    ROI_FOCUS,
    BLUR_STAIN_TYPE,
    BLUR_WSTAIN_TYPE,
    BLUR_GLARE_TYPE
};
enum _edtsymbol {
    /* DELAY LINE EDIT*/
    /*AT COMMAND*/
    DL_UART_USB_SEND,
    DL_UART_USB_RESPONE,
    DL_HOME_SCREEN_SEND,
    DL_HOME_SCREEN_RESPONE,
    DL_OPEN_IRIS_SEND,
    DL_OPEN_IRIS_RESPONE,
    DL_CLOSE_IRIS_SEND,
    DL_CLOSE_IRIS_RESPONE,
    DL_OPEN_FW1_SEND,
    DL_OPEN_FW1_RESPONE,
    DL_CLOSE_FW1_SEND,
    DL_CLOSE_FW1_RESPONE,
    DL_OPEN_FB1_SEND,
    DL_OPEN_FB1_RESPONE,
    DL_CLOSE_FB1_SEND,
    DL_CLOSE_FB1_RESPONE,
    DL_CAPTURE_NOAF_SEND,
    DL_CAPTURE_NOAF_RESPONE,
    DL_CAPTURE_AF_SEND,
    DL_CAPTURE_AF_RESPONE,
    DL_CAPTURE_TRYAF_SEND,
    DL_CAPTURE_TRYAF_RESPONE,
    /*ADB COMMAND*/
    DL_GET_LIST_SEND,
    DL_GET_LIST_RESPONE,
    DL_PULL_2_PC_SEND,
    DL_PULL_2_PC_RESPONE,
    DL_REMOVE_FOLDER_SEND,
    DL_REMOVE_FOLDER_RESPONE,
    /*Clynder*/
    DL_CLYNDER_FORWARD,
    DL_CLYNDER_BACKWARD,
    /*paint parameter*/
    PAINT_THICKNESS,
    PAINT_OFFSET,
    /*normalize parameter*/
    NOR_ALPHA,
    NOR_BETA,
    /* STAIN LINE EDIT -S: SMALL */
    STAIN_THRESHOLD,
    STAIN_BLOCKSIZE,
    STAIN_BLURSIZE,
    STAIN_ERODE_SIZE,
    STAIN_ERODE_LOOP,
    STAIN_DILATE_SIZE,
    STAIN_DILATE_LOOP,
    STAIN_REMOVE_EDGE,
    STAIN_REMOVE_CONNER,
    STAIN_FILTER_AREA,
    STAIN_FILTER_WIDTH,
    STAIN_FILTER_HEIGHT,
    /* WHITESTAIN LINE EDIT -S: SMALL */
    WSTAIN_THRESHOLD,
    WSTAIN_BLOCKSIZE,
    WSTAIN_BLURSIZE,
    WSTAIN_ERODE_SIZE,
    WSTAIN_ERODE_LOOP,
    WSTAIN_DILATE_SIZE,
    WSTAIN_DILATE_LOOP,
    WSTAIN_REMOVE_EDGE,
    WSTAIN_REMOVE_CONNER,
    WSTAIN_FILTER_AREA,
    WSTAIN_FILTER_WIDTH,
    WSTAIN_FILTER_HEIGHT,
    /* GLARE LINE EDIT */
    GLARE_THRESHOLD,
    GLARE_BLUR_SIZE,
    GLARE_ROI1,
    GLARE_ROI2,
    GLARE_ROI3,
    GLARE_ROI4,
    GLARE_ROI5,
    GLARE_ROI6,
    GLARE_ERODE_SIZE,
    GLARE_ERODE_LOOP,
    GLARE_DILATE_SIZE,
    GLARE_DILATE_LOOP,
    GLARE_REMOVE_EDGE,
    GLARE_REMOVE_CONNER,

    GLARE_FILTER_MROI1,
    GLARE_FILTER_MROI2,
    GLARE_FILTER_MROI3,
    GLARE_FILTER_MROI4,
    GLARE_FILTER_MROI5,
    GLARE_FILTER_MROI6,

    GLARE_FILTER_AREA1,
    GLARE_FILTER_AREA2,
    GLARE_FILTER_AREA3,
    GLARE_FILTER_AREA4,
    GLARE_FILTER_AREA5,
    GLARE_FILTER_AREA6,

    GLARE_FILTER_WIDTH1,
    GLARE_FILTER_WIDTH2,
    GLARE_FILTER_WIDTH3,
    GLARE_FILTER_WIDTH4,
    GLARE_FILTER_WIDTH5,
    GLARE_FILTER_WIDTH6,

    GLARE_FILTER_HEIGHT1,
    GLARE_FILTER_HEIGHT2,
    GLARE_FILTER_HEIGHT3,
    GLARE_FILTER_HEIGHT4,
    GLARE_FILTER_HEIGHT5,
    GLARE_FILTER_HEIGHT6,

    /*Focus line edit*/
    FOCUS_ROI1,
    FOCUS_ROI2,
    FOCUS_ROI3,
    FOCUS_ROI4,
    FOCUS_ROI5,
    FOCUS_ROI6,

    FOCUS_FILTER_SROI1,
    FOCUS_FILTER_SROI2,
    FOCUS_FILTER_SROI3,
    FOCUS_FILTER_SROI4,
    FOCUS_FILTER_SROI5,
    FOCUS_FILTER_SROI6,

    /*DARKSPORT LINE EDIT*/
    DARKSPORT_THRESHOULD,
    DARKSPORT_BLOCK_SIZE,
    DARKSPORT_FILT_AREA,

    /* WRONG COLOR LINE EDIT*/
    COLOR_MEANRED,
    COLOR_MEANGREEN,
    COLOR_MEANBLUE,

    /*AT COMMAND*/
    AT_UART_USB_SEND,
    AT_UART_USB_RESPONE,
    AT_HOME_SCREEN_SEND,
    AT_HOME_SCREEN_RESPONE,
    AT_OPEN_IRIS_SEND,
    AT_OPEN_IRIS_RESPONE,
    AT_CLOSE_IRIS_SEND,
    AT_CLOSE_IRIS_RESPONE,
    AT_OPEN_FW1_SEND,
    AT_OPEN_FW1_RESPONE,
    AT_CLOSE_FW1_SEND,
    AT_CLOSE_FW1_RESPONE,
    AT_OPEN_FB1_SEND,
    AT_OPEN_FB1_RESPONE,
    AT_CLOSE_FB1_SEND,
    AT_CLOSE_FB1_RESPONE,

    AT_CAPTURE_NOAF_SEND,
    AT_CAPTURE_NOAF_RESPONE,
    AT_CAPTURE_AF_SEND,
    AT_CAPTURE_AF_RESPONE,
    AT_CAPTURE_TRYAF_SEND,
    AT_CAPTURE_TRYAF_RESPONE,

    /*ADB COMMAND*/
    ADB_GET_LIST_SEND,
    ADB_GET_LIST_RESPONE,
    ADB_PULL_2_PC_SEND,
    ADB_PULL_2_PC_RESPONE,
    ADB_REMOVE_FOLDER_SEND,
    ADB_REMOVE_FOLDER_RESPONE

};

enum _eMainProcess {
    LOOP_DOTHING = 0,

    LOOP_PREPARE,

    LOOP_OPENIRIS_SEND,

    LOOP_OPENIRIS_WAIT,

    LOOP_CLOSEIRIS_SEND,

    LOOP_CLOSEIRIS_WAIT,

    LOOP_OPENFW1_SEND,

    LOOP_OPENFW1_WAIT,

    LOOP_CLOSEFW1_SEND,

    LOOP_CLOSEFW1_WAIT,

    LOOP_OPENFB1_SEND,

    LOOP_OPENFB1_WAIT,

    LOOP_CLOSEFB1_SEND,

    LOOP_CLOSEFB1_WAIT,

    LOOP_CAPTURE_SEND,

    LOOP_CAPTURE_WAIT,

    LOOP_CLDFORWARD_SEND,

    LOOP_CLDFORWARD_WAIT,

    LOOP_CLDBACKWARD_SEND,

    LOOP_CLDBACKWARD_WAIT,

    LOOP_GETLIST_SEND,

    LOOP_GETLIST_WAIT,

    LOOP_PULL2PC_SEND,

    LOOP_PULL2PC_WAIT,

    LOOP_LOADIMG_DO,

    LOOP_PROCESS_DO,

    LOOP_PROCESS_WAIT,

    LOOP_PROCESS_RESULT,

    LOOP_ERR,

};

enum _eSizeTypeStain{
    TYPE_SIZE_SMALL,
    TYPE_SIZE_LARGE,
};

enum _eRotate {
    DEGREE_0,
    DEGREE_90,
    DEGREE_180,
    DEGREE_270
};

enum _eNormType {
    _NORM_INF,
    _NORM_L1,
    _NORM_L2,
    _NORM_MINMAX
};



enum _iTypeCam {
    FW1,
    FB1,
    NO
};
// struct:
struct _sParameter                          {
    /*  para check issue vision   */
    /*small size & large size*/
    int ipThreshold[NUM_TYPE]                       = {};
    int ipBlockSize[NUM_TYPE]                       = {};
    int ipBlurSize[NUM_TYPE]                        = {};
    int ipBlurType[NUM_TYPE]                        = {};
    int ipErodeSize[NUM_TYPE]                       = {};
    int ipErodeLoop[NUM_TYPE]                       = {};
    int ipDilateSize[NUM_TYPE]                      = {};
    int ipDilateLoop[NUM_TYPE]                      = {};
    int ipRemoveConner[NUM_TYPE]                    = {};
    int ipRemoveEdge[NUM_TYPE]                      = {};
    int ipFilterAreaMin[NUM_TYPE]                   = {};
    int ipFilterAreaMax[NUM_TYPE]                   = {};
    int ipFilterWMin[NUM_TYPE]                      = {};
    int ipFilterWMax[NUM_TYPE]                      = {};
    int ipFilterHMin[NUM_TYPE]                      = {};
    int ipFilterHMax[NUM_TYPE]                      = {};

    /* glare checkipg|| ipg: int parameter glare || MS mean / std */
    int ipgThreshold[NUM_ROI]               = {};
    int ipgBlurSize[NUM_ROI]                = {};
    int ipgBlurType[NUM_ROI]               = {};
    Rect rpRoi[NUM_ROI]                     = {};
    int ipgErodeSize[NUM_ROI]               = {};
    int ipgErodeLoop[NUM_ROI]               = {};
    int ipgDilateSize[NUM_ROI]              = {};
    int ipgDilateLoop[NUM_ROI]              = {};
    int ipgRemoveConner[NUM_ROI]            = {};
    int ipgRemoveEdge[NUM_ROI]              = {};
    double ipgMSRoiMin[NUM_ROI]             = {};
    double ipgMSRoiMax[NUM_ROI]             = {};
    int ipgFilterAreaMin[NUM_ROI]           = {};
    int ipgFilterAreaMax[NUM_ROI]           = {};
    int ipgFilterWMin[NUM_ROI]              = {};
    int ipgFilterWMax[NUM_ROI]              = {};
    int ipgFilterHMin[NUM_ROI]              = {};
    int ipgFilterHMax[NUM_ROI]              = {};
    /* darksport || ipds: int parameter darksport*/
    int ipdsThreshold                       = 1;
    int ipdsBlockSize                       = 3;
    int ipdsFilterAreaMin                   = 100;
    int ipdsFilterAreaMax                   = 100;
    /*wrong color || ipwc: int parameter wrong color */
    int ipwcMeanRedMin                        = 50;
    int ipwcMeanRedMax                        = 50;
    int ipwcMeanGreenMin                      = 50;
    int ipwcMeanGreenMax                      = 50;
    int ipwcMeanBlueMin                       = 50;
    int ipwcMeanBlueMax                       = 50;
};

struct _sDevice                             {
    bool           bUse                    = true;
    QString        qstrComport             = "COM1";
    QString        qstrID                  = "";
    QString        qstrKeyStart            = "1";
    QString        qstrKeyStop             = "Esc";
    QString        qstrFolderInput         = "";
    QString        qstrFolderOutput        = "";
    QString        qstrFolderPhone         = "";
    int            ipModel                 = N960;
    bool           bUsecomIO               = false;
    QString        qstrComIO               = "COM111";
};

struct _sDataCom                            {
    int         iStatus          = -1;           //status
    double      dDelay_Send      = 0.5;          //sec
    double      dDelay_Wait      = 0.5;          //sec
    QString     send             = "None";           //send data
    QString     respone          = "None";           //respone data
};


struct _sGeneral                            {
    QString        qstrVer                 = "ver3_28/12/2019";
    QString        qstrFolderLog           = PATH_DB_ATK;
    /*Shocket Setiing*/
    _sDevice       Device;
    /*  option   */
    bool           bOptShowImg[NUM_CAM]             = {};
    bool           bOptSaveImg[NUM_CAM]             = {};
    bool           bOptCheckIris                    = {};
    bool           bOptCheckStain[NUM_CAM]          = {};
    bool           bOptCheckWhiteStain[NUM_CAM]     = {};
    bool           bOptCheckGlare[NUM_CAM]          = {};
    bool           bOptCheckFocus[NUM_CAM]          = {};
    bool           bOptCheckColor[NUM_CAM]          = {};
    bool           bOptDarkSport[NUM_CAM]           = {};
    bool           bOptCaptrueAf[NUM_CAM]           = {};
    bool           bOptSaveImageResize = true;

    /*  delay time   */
    double          dbDelay[NUM_DELAY]              = {};
    /*  para check   */
    double ipPaintThickness                         = 3;
    int ipPaintOffset                               = 3;
    /*  para normalize  */
    int ipNormType[NUM_CAM];
    int ipNormAlpha[NUM_CAM];
    int ipNormBeta[NUM_CAM];

    _sParameter    spStain     [NUM_CAM];
    _sParameter    spWhiteStain[NUM_CAM];
    _sParameter    spGlare     [NUM_CAM];
    _sParameter    spFocus     [NUM_CAM];
    _sParameter    spDarksport [NUM_CAM];
    _sParameter    spWrongColor[NUM_CAM];

    /* AT command qstring*/
    _sDataCom      ATCMD[NUM_AT];

    /* AT command ADB*/
    _sDataCom      ADBCMD[NUM_ADB];
};


// inline
inline QString Int2QString(int i)           {
    return QString("%1").arg(i);
}
inline QString Double2QString(double d)     {
    QString str = "";
    str.setNum(d,'f',1);
    return str;
}
inline QString Rect2QString(Rect r)         {
    QString str = QString("%1,%2,%3,%4").arg(r.x).arg(r.y).arg(r.width).arg(r.height);
    return str;
}
inline QString Point2QString(Point p)       {
    QString str = QString("%1,%2").arg(p.x).arg(p.y);
    return str;
}
inline double  QString2Double(QString str)  {
    return str.toDouble();
}
inline Rect    QString2Rect(QString str)    {
    QStringList listRectElement;
    listRectElement = str.split(",");
    Rect r(0,0,0,0);
    r.x = QString(listRectElement[0]).toInt();
    r.y = QString(listRectElement[1]).toInt();
    r.width = QString(listRectElement[2]).toInt();
    r.height = QString(listRectElement[3]).toInt();

    return r;
}
inline Point   QString2Point(QString str)   {
    QStringList listRectElement;
    listRectElement = str.split(",");
    Point p(0,0);
    p.x = QString(listRectElement[0]).toInt();
    p.y = QString(listRectElement[1]).toInt();

    return p;
}
inline int QString2Int(QString str)     {
    return str.toInt();
}
//color
#define cv_aliceblue                        cv::Scalar(255, 248, 240)
#define cv_aliceblue                        cv::Scalar(255, 248, 240)
#define cv_antiquewhite                     cv::Scalar(215, 235, 250)
#define cv_aqua                             cv::Scalar(255, 255, 0)
#define cv_aquamarine                       cv::Scalar(212, 255, 127)
#define cv_azure                            cv::Scalar(255, 255, 240)
#define cv_beige                            cv::Scalar(220, 245, 245)
#define cv_bisque                           cv::Scalar(196, 228, 255)
#define cv_black                            cv::Scalar(0, 0, 0)
#define cv_blanchedalmond                   cv::Scalar(205, 235, 255)
#define cv_blue                             cv::Scalar(255, 0, 0)
#define cv_blueviolet                       cv::Scalar(226, 43, 138)
#define cv_brown                            cv::Scalar(42, 42, 165)
#define cv_burlywood                        cv::Scalar(135, 184, 222)
#define cv_cadetblue                        cv::Scalar(160, 158, 95)
#define cv_chartreuse                       cv::Scalar(0, 255, 127)
#define cv_chocolate                        cv::Scalar(30, 105, 210)
#define cv_coral                            cv::Scalar(80, 127, 255)
#define cv_cornflowerblue                   cv::Scalar(237, 149, 100)
#define cv_cornsilk                         cv::Scalar(220, 248, 255)
#define cv_crimson                          cv::Scalar(60, 20, 220)
#define cv_cyan                             cv::Scalar(255, 255, 0)
#define cv_darkblue                         cv::Scalar(139, 0, 0)
#define cv_darkcyan                         cv::Scalar(139, 139, 0)
#define cv_darkgoldenrod                    cv::Scalar(11, 134, 184)
#define cv_darkgray                         cv::Scalar(169, 169, 169)
#define cv_darkgreen                        cv::Scalar(0, 100, 0)
#define cv_darkgrey                         cv::Scalar(169, 169, 169)
#define cv_darkkhaki                        cv::Scalar(107, 183, 189)
#define cv_darkmagenta                      cv::Scalar(139, 0, 139)
#define cv_darkolivegreen                   cv::Scalar(47, 107, 85)
#define cv_darkorange                       cv::Scalar(0, 140, 255)
#define cv_darkorchid                       cv::Scalar(204, 50, 153)
#define cv_darkred                          cv::Scalar(0, 0, 139)
#define cv_darksalmon                       cv::Scalar(122, 150, 233)
#define cv_darkseagreen                     cv::Scalar(143, 188, 143)
#define cv_darkslateblue                    cv::Scalar(139, 61, 72)
#define cv_darkslategray                    cv::Scalar(79, 79, 47)
#define cv_darkslategrey                    cv::Scalar(79, 79, 47)
#define cv_darkturquoise                    cv::Scalar(209, 206, 0)
#define cv_darkviolet                       cv::Scalar(211, 0, 148)
#define cv_deeppink                         cv::Scalar(147, 20, 255)
#define cv_deepskyblue                      cv::Scalar(255, 191, 0)
#define cv_dimgray                          cv::Scalar(105, 105, 105)
#define cv_dimgrey                          cv::Scalar(105, 105, 105)
#define cv_dodgerblue                       cv::Scalar(255, 144, 30)
#define cv_firebrick                        cv::Scalar(34, 34, 178)
#define cv_floralwhite                      cv::Scalar(240, 250, 255)
#define cv_forestgreen                      cv::Scalar(34, 139, 34)
#define cv_fuchsia                          cv::Scalar(255, 0, 255)
#define cv_gainsboro                        cv::Scalar(220, 220, 220)
#define cv_ghostwhite                       cv::Scalar(255, 248, 248)
#define cv_gold                             cv::Scalar(0, 215, 255)
#define cv_goldenrod                        cv::Scalar(32, 165, 218)
#define cv_gray                             cv::Scalar(128, 128, 128)
#define cv_green                            cv::Scalar(0, 255, 0)
#define cv_greenyellow                      cv::Scalar(47, 255, 173)
#define cv_grey                             cv::Scalar(128, 128, 128)
#define cv_honeydew                         cv::Scalar(240, 255, 240)
#define cv_hotpink                          cv::Scalar(180, 105, 255)
#define cv_indianred                        cv::Scalar(92, 92, 205)
#define cv_indigo                           cv::Scalar(130, 0, 75)
#define cv_ivory                            cv::Scalar(240, 255, 255)
#define cv_khaki                            cv::Scalar(140, 230, 240)
#define cv_lavender                         cv::Scalar(250, 230, 230)
#define cv_lavenderblush                    cv::Scalar(245, 240, 255)
#define cv_lawngreen                        cv::Scalar(0, 252, 124)
#define cv_lemonchiffon                     cv::Scalar(205, 250, 255)
#define cv_lightblue                        cv::Scalar(230, 216, 173)
#define cv_lightcoral                       cv::Scalar(128, 128, 240)
#define cv_lightcyan                        cv::Scalar(255, 255, 224)
#define cv_lightgoldenrodyellow             cv::Scalar(210, 250, 250)
#define cv_lightgray                        cv::Scalar(211, 211, 211)
#define cv_lightgreen                       cv::Scalar(144, 238, 144)
#define cv_lightgrey                        cv::Scalar(211, 211, 211)
#define cv_lightpink                        cv::Scalar(193, 182, 255)
#define cv_lightsalmon                      cv::Scalar(122, 160, 255)
#define cv_lightseagreen                    cv::Scalar(170, 178, 32)
#define cv_lightskyblue                     cv::Scalar(250, 206, 135)
#define cv_lightslategray                   cv::Scalar(153, 136, 119)
#define cv_lightslategrey                   cv::Scalar(153, 136, 119)
#define cv_lightsteelblue                   cv::Scalar(222, 196, 176)
#define cv_lightyellow                      cv::Scalar(224, 255, 255)
#define cv_lime                             cv::Scalar(0, 255, 0)
#define cv_limegreen                        cv::Scalar(50, 205, 50)
#define cv_linen                            cv::Scalar(230, 240, 250)
#define cv_magenta                          cv::Scalar(255, 0, 255)
#define cv_maroon                           cv::Scalar(0, 0, 128)
#define cv_mediumaquamarine                 cv::Scalar(170, 205, 102)
#define cv_mediumblue                       cv::Scalar(205, 0, 0)
#define cv_mediumorchid                     cv::Scalar(211, 85, 186)
#define cv_mediumpurple                     cv::Scalar(219, 112, 147)
#define cv_mediumseagreen                   cv::Scalar(113, 179, 60)
#define cv_mediumslateblue                  cv::Scalar(238, 104, 123)
#define cv_mediumspringgreen                cv::Scalar(154, 250, 0)
#define cv_mediumturquoise                  cv::Scalar(204, 209, 72)
#define cv_mediumvioletred                  cv::Scalar(133, 21, 199)
#define cv_midnightblue                     cv::Scalar(112, 25, 25)
#define cv_mintcream                        cv::Scalar(250, 255, 245)
#define cv_mistyrose                        cv::Scalar(225, 228, 255)
#define cv_moccasin                         cv::Scalar(181, 228, 255)
#define cv_navajowhite                      cv::Scalar(173, 222, 255)
#define cv_navy                             cv::Scalar(128, 0, 0)
#define cv_oldlace                          cv::Scalar(230, 245, 253)
#define cv_olive                            cv::Scalar(0, 128, 128)
#define cv_olivedrab                        cv::Scalar(35, 142, 107)
#define cv_orange                           cv::Scalar(0, 165, 255)
#define cv_orangered                        cv::Scalar(0, 69, 255)
#define cv_orchid                           cv::Scalar(214, 112, 218)
#define cv_palegoldenrod                    cv::Scalar(170, 232, 238)
#define cv_palegreen                        cv::Scalar(152, 251, 152)
#define cv_paleturquoise                    cv::Scalar(238, 238, 175)
#define cv_palevioletred                    cv::Scalar(147, 112, 219)
#define cv_papayawhip                       cv::Scalar(213, 239, 255)
#define cv_peachpuff                        cv::Scalar(185, 218, 255)
#define cv_peru                             cv::Scalar(63, 133, 205)
#define cv_pink                             cv::Scalar(203, 192, 255)
#define cv_plum                             cv::Scalar(221, 160, 221)
#define cv_powderblue                       cv::Scalar(230, 224, 176)
#define cv_purple                           cv::Scalar(128, 0, 128)
#define cv_red                              cv::Scalar(0, 0, 255)
#define cv_rosybrown                        cv::Scalar(143, 143, 188)
#define cv_royalblue                        cv::Scalar(225, 105, 65)
#define cv_saddlebrown                      cv::Scalar(19, 69, 139)
#define cv_salmon                           cv::Scalar(114, 128, 250)
#define cv_sandybrown                       cv::Scalar(96, 164, 244)
#define cv_seagreen                         cv::Scalar(87, 139, 46)
#define cv_seashell                         cv::Scalar(238, 245, 255)
#define cv_sienna                           cv::Scalar(45, 82, 160)
#define cv_silver                           cv::Scalar(192, 192, 192)
#define cv_skyblue                          cv::Scalar(235, 206, 135)
#define cv_slateblue                        cv::Scalar(205, 90, 106)
#define cv_slategray                        cv::Scalar(144, 128, 112)
#define cv_slategrey                        cv::Scalar(144, 128, 112)
#define cv_snow                             cv::Scalar(250, 250, 255)
#define cv_springgreen                      cv::Scalar(127, 255, 0)
#define cv_steelblue                        cv::Scalar(180, 130, 70)
#define cv_tan                              cv::Scalar(140, 180, 210)
#define cv_teal                             cv::Scalar(128, 128, 0)
#define cv_thistle                          cv::Scalar(216, 191, 216)
#define cv_tomato                           cv::Scalar(71, 99, 255)
#define cv_turquoise                        cv::Scalar(208, 224, 64)
#define cv_violet                           cv::Scalar(238, 130, 238)
#define cv_wheat                            cv::Scalar(179, 222, 245)
#define cv_white                            cv::Scalar(255, 255, 255)
#define cv_whitesmoke                       cv::Scalar(245, 245, 245)
#define cv_yellow                           cv::Scalar(0, 255, 255)
#define cv_backgroundResult                 cv::Scalar(127, 255, 170)
#define cv_yellowgreen                      cv::Scalar(50, 205, 154)

// external:
#define AT_HEADINFO                         "AT+HEADINFO=0,2\r\n"
#define AT_SCREEN_ON                        "AT+DISPTEST=0,3"
#define AT_CREEN_OFF                        "AT+DISPTEST=0,4"
#define AT_CAPSCREEN                        "AT+CAMETEST=0,1,2,2\r\n"
#define AT_CAPTURE                          "AT+CAMETEST=0,1,2,0\r\n"
#define AT_FLASH_ON                         "AT+CAMETEST=0,3,2,0\r\n"
#define AT_FLASH_OFF                        "AT+CAMETEST=0,3,1,1\r\n"
#define AT_SET_ERROR                        "AT+SETTESTNV=235,E\r\n"
#define AT_SET_PASS                         "AT+SETTESTNV=235,P\r\n"
#define AT_SET_FAIL                         "AT+SETTESTNV=235,F\r\n"
#define AT_REAR1_OPEN                       "AT+CAMETEST=0,1,0,1\r\n"
#define AT_REAR2_OPEN                       "AT+CAMETEST=0,1,0,4\r\n"
#define AT_FRONT_OPEN                       "AT+CAMETEST=0,1,0,0\r\n"
#define NUM_THREAD                          2
#define USB_IN                              "!"
#define USB_OUT                             "@"
#define HEADER_INFOR                        "HEADINFO:1,"
#define HEADER_OK                           "OK"
#define CMD_FUNC_TEST                       "AT+FUNCTEST=0,2\r\n"
#define CMD_HEADINFO_TEST                   "AT+HEADINFO=0,2\r\n"
#define CMD_SWATD                           "AT+SWATD=1\r\n"
#define CMD_CAP_WITH_AF                     "AT+NCAMTEST=0,1,0,0\r\n"
#define CMD_CAP_WITHOUT_AF                  "AT+NCAMTEST=0,1,0,1\r\n"
#define CMD_CAP_TRY_AF                      "AT+NCAMTEST=0,1,0,1\r\n"
#define CMD_B0_TRIPLE                       "AT+NCAMTEST=1,0,1,RW1_RS1\r\n"
#define CMD_B2_TRIPLE                       "AT+NCAMTEST=1,0,1,RW1_RS1_RT1\r\n"
#define CMD_B0_OPEN_REAR1                   "AT+NCAMTEST=0,0,1,RW1\r\n"
#define CMD_B0_OPEN_REAR2                   "AT+NCAMTEST=0,0,1,RS1\r\n"
#define CMD_B2_OPEN_REAR1                   "AT+NCAMTEST=0,0,1,RW1\r\n"
#define CMD_B2_OPEN_REAR2                   "AT+NCAMTEST=0,0,1,RS1\r\n"
#define CMD_B2_OPEN_REAR3                   "AT+NCAMTEST=0,0,1,RT1\r\n"
#define TRIPLE_CAL_BEGIN                    "AT+NCAMTEST=1,0,1,RW1_RS1\r\n\r\n+NCAMTEST:"
#define TRIPLE_CAL_BEGIN_D0                 "AT+NCAMTEST=1,0,1,RW1_RD1\r\n\r\n+NCAMTEST:"
#define TRIPLE_CAL_FINISH                   "\r\n\r\nOK\r\n"
#define AT_HEADINFO                         "AT+HEADINFO=0,2\r\n"
#define AT_SCREEN_ON                        "AT+DISPTEST=0,3"
#define AT_CREEN_OFF                        "AT+DISPTEST=0,4"
#define AT_CAPSCREEN                        "AT+CAMETEST=0,1,2,2\r\n"
#define AT_CAPTURE                          "AT+CAMETEST=0,1,2,0\r\n"
#define AT_FLASH_ON                         "AT+CAMETEST=0,3,2,0\r\n"
#define AT_FLASH_OFF                        "AT+CAMETEST=0,3,1,1\r\n"
#define AT_SET_ERROR                        "AT+SETTESTNV=235,E\r\n"
#define AT_SET_PASS                         "AT+SETTESTNV=235,P\r\n"
#define AT_SET_FAIL                         "AT+SETTESTNV=235,F\r\n"
#define AT_REAR1_OPEN                       "AT+CAMETEST=0,1,0,1\r\n"
#define AT_REAR2_OPEN                       "AT+CAMETEST=0,1,0,4\r\n"
#define AT_FRONT_OPEN                       "AT+CAMETEST=0,1,0,0\r\n"
#define NUM_THREAD                          2
#define USB_IN                              "!"
#define USB_OUT                             "@"
#define HEADER_INFOR                        "HEADINFO:1,"
#define HEADER_OK                           "OK"
#define CMD_FUNC_TEST                       "AT+FUNCTEST=0,2\r\n"
#define CMD_HEADINFO_TEST                   "AT+HEADINFO=0,2\r\n"
#define CMD_SWATD                           "AT+SWATD=1\r\n"
#define CMD_CAP_WITH_AF                     "AT+NCAMTEST=0,1,0,0\r\n"
#define CMD_CAP_WITHOUT_AF                  "AT+NCAMTEST=0,1,0,1\r\n"
#define CMD_CAP_TRY_AF                      "AT+NCAMTEST=0,1,0,1\r\n"
#define CMD_B0_TRIPLE                       "AT+NCAMTEST=1,0,1,RW1_RS1\r\n"
#define CMD_B2_TRIPLE                       "AT+NCAMTEST=1,0,1,RW1_RS1_RT1\r\n"
#define CMD_B0_OPEN_REAR1                   "AT+NCAMTEST=0,0,1,RW1\r\n"
#define CMD_B0_OPEN_REAR2                   "AT+NCAMTEST=0,0,1,RS1\r\n"
#define CMD_B2_OPEN_REAR1                   "AT+NCAMTEST=0,0,1,RW1\r\n"
#define CMD_B2_OPEN_REAR2                   "AT+NCAMTEST=0,0,1,RS1\r\n"
#define CMD_B2_OPEN_REAR3                   "AT+NCAMTEST=0,0,1,RT1\r\n"
#define TRIPLE_CAL_BEGIN                    "AT+NCAMTEST=1,0,1,RW1_RS1\r\n\r\n+NCAMTEST:"
#define TRIPLE_CAL_BEGIN_D0                 "AT+NCAMTEST=1,0,1,RW1_RD1\r\n\r\n+NCAMTEST:"
#define TRIPLE_CAL_FINISH                   "\r\n\r\nOK\r\n"

#endif // SYSTEMDEFINE_H

