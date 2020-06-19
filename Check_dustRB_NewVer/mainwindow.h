#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTableWidgetItem>
#include <QMainWindow>
#include <QMessageBox>
#include <QDateTime>
#include <QCloseEvent>
#include <QTimer>
#include <QFontInfo>
#include <QThread>
#include <QList>
#include <QStringList>
#include <QTextStream>
#include <QList>
#include <QStringList>
#include <QDir>
#include <vector>
#include <QVector>
#include <QSharedMemory>
#include <QToolButton>
#include <ctime>
#include <QElapsedTimer>
#include <QKeyEvent>
#include <QFile>
#include <QThread>
#include <qtoolbutton.h>
#include "myvision.h"
#include "process.h"
#include "processvision.h"
#include "myDefine.h"
#include "processcam.h"
//using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void                  closeEvent (QCloseEvent *event);
    Ui::MainWindow *ui;

//variable - biến all
public:
/* show time current*/
    QTimer               *qtrTimeSys;                                                        /* qtr: QTimer run show current time on UI*/
    QDateTime            qdCurTime;                                                          /* qd: QDateTime */
    int                  iImgWidth,
                         iImgHeight;
    MyVision             fVision;
    _sGeneral            mGeneral[NUM_PARA];                                                 /* parameter all */
    Point                pPrePoint,                                                          /*Mouse spare*/
                         pCurPoint;
    Rect                 rCurRect;                                                           /* r: Rect */
    QRect                qrPosDisp;                                                          /* qr: QRect */
    QTime                qtTime;                                                             /* qt: QTime */
    QString              qstrTime;                                                           /* qstr: QString */
    Mat                  mPattern;                                                           /* m: Mat load img manual test */
    QSerialPort          *qspSerial;                                                         /* qsp: QSerialPort */
    QString              qstrSerialPort                   = "COM100",
                         qstrDataSerial                   = "";
    int                  iBaudRate                        = 9600;
    QString              qstrDataADB                      = "";
    bool                 bEnableScanDevices               = false,
                         bLoadParaFirst                   = false,
                         bEnableFindImg                   = false;
    int                  iLastButton                      = -1,
                         idxModelLeft                     = N960,
                         idxModelRight                    = N960;
    /**/
    _sMainUI             lMain[NUM_SIDE];                                                     /* l: link, link UI     */
    _sDeviceParam        lDevPara[NUM_SIDE];                                                  /* link para            */
    QFile                qfLog[NUM_SIDE];                                                     /* qf: QFile            */
    QString              qstrLogFile[NUM_SIDE]            = {"",""};
    /* Pointer -- all */
    ProcessDarkSpot      *m_ProcessDarkspot;
    ProcessSStain        *m_ProcessSStain;
    ProcessWhiteSStain   *m_ProcessWhiteSStain;

    ProcessLStain        *m_ProcessLStain;
    ProcessWhiteLStain   *m_ProcessWhiteLStain;

    ProcessWrongColor    *m_ProcessWrongColor;
    ProcessGlare         *m_ProcessGlare;
    ProcessFocus         *m_ProcessFocus;
    ProcessCheckComIO    *m_ProcessCheckComIO;

    QCheckBox            *m_CheckBox[NUM_CHECKBOX];                                          /* insert to treewidget */
    QLineEdit            *m_LineEdit[NUM_LINEDIT];                                           /* insert to treewidget */
    QComboBox            *m_ComboBox[NUM_COMBOBOX];                                          /* insert to treewidget */

    QProcess             *qpManADB;                                                          /* qp: QProcess , Man: Manual use */
    QSerialPort          *qspAuComIO[NUM_SIDE];                                              /* Au: Auto use (Creat) */
    QSerialPort          *qspAuComport[NUM_SIDE];
    QProcess             *qpAuADB[NUM_SIDE];
    ProcessCam           *pProc[NUM_SIDE];                                                   /* process auto run all */
    processSimulation    *Simulation;
    vector<Mat> mRes;

    // fuction - hàm all
public:
    bool eventFilter(QObject *obj, QEvent *event);                           /*EVENT SYSTEM*/
    void StartPrg();
    void StopPrg();
    void ResizeTableLog();
    void ConnectSignalObject();

/*save para from Ui to json*/
    void GetDataBufferTemp();
    void SaveDataGeneral();
    void SaveData();

/*get from json file to buffer on Program*/
    void LoadBufferDataGeneral(int iSlide);
    void LoadBufferDataParaCheck(int iSlide, int iIdxModel);
    void LoadBufferParameterStain(int iSlide, int iCam, QJsonObject json);
    void LoadBufferParameterWhiteStain(int iSlide, int iCam, QJsonObject json);
    void LoadBufferParameterGlare(int iSlide, int iCam, QJsonObject json);
    void LoadBufferParameterFocus(int iSlide, int iCam, QJsonObject json);
    void LoadBufferParameterDarkSport(int iSlide, int iCam, QJsonObject json);
    void LoadBufferParameterWrongColor(int iSlide, int iCam, QJsonObject json);
    void LoadBufferParameterATCommand(int iSlide, QJsonObject json);
    void LoadBufferParameterADBCommand(int iSlide, QJsonObject json);

    void OnInitDlg();
    void OnInitDlg_Auto();
    void OnInitDlg_Teach();
    void OnInitDlg_Manual();
    void InitGUI(int iIdxPara);
    void InitProcCam();
    void InitComport();
    void InitFolder();
    void InitLogFile(int iSide);

    void InitUiParameterCam(int iIdxModel, int iCam);
    void InitUiParameterStain(int iCam, int iTypeSize, QJsonObject json);
    void InitUiParameterWhiteStain(int iCam, int iTypeSize, QJsonObject json);
    void InitUiParameterGlare(int iCam, int iRoi, QJsonObject json);

    std::vector<QString> GetListComport();
    std::vector<QString> GetListDevices();
    vector<QString>      GetAllFileInFolder(QString folder);

    void SendADB(QString strIn, int iSide);
    void ExeCmdATK(QString strIn);
    void AddDataCmd(QString str, QColor iColor=Qt::blue);
    QString ExeCmd(QString strIn);

    bool OpenSerialPort(QString NamePort, int Baudrate = 115200);
    void AddDataComport(QString str, QColor iColor=Qt::blue);




    void SendCom(QString data);
    void SendCom(QSerialPort *pCom, QString data);
    bool OpenCom(QSerialPort *pCom, QString NamePort, int typle, int Baudrate = 115200 );
    bool CloseCom(QSerialPort *pCom);

    void WriteLogFile(QString data, int iSide);
    void WriteLogComIO(QString data);
    void CloseLogFile();
    bool MakeFolder(QString folder);

    void CreatTreePara();
    // disnable/enable parameter
    void DisableParameter();
    void EnableParamter();
    /* json file*/
    void saveJson(QJsonDocument document, QString fileName) const;
    QJsonDocument loadJson(QString fileName);
    void drawTreeWidget();
signals:
    void currentIndexChanged(int iInDex);
    void eAddLogTestManual(QString str, QColor iColor = Qt::blue);
    void eDisplay_Image(Mat Image, int iLabel);
    void esetValueProcessBar(int iValue);
public slots:

    void setValueProcessBar(int iValue);
    void showImageWhenClick(int iRow, int iCol);
    void DisplayDateTime();
    void ButtonProcess();
    // fuction manual:
    void VisionSStain(int iCode);
    void VisionLStain(int iCode);
    void VisionWhiteSStain(int iCode);
    void VisionWhiteLStain(int iCode);
    void VisionGlare(int iCode);
    void VisionDarkSpot(int iCode);
    void VisionWrongColor(int iCode);
    void VisionFocus(int iCode);
    void SelectCmd(int iIndex);

    void Display_Image(Mat Image, int iLabel);

    void simulatorVision(int iCam, int iModel, QStringList listImage);

    QStringList getListImageFromFolder(QString qstrFolder);

     void AddLogTestManual(QString str,  QColor iColor=Qt::blue);



    // read data com liên tục quét sự kiện start:
    void readDataComIO();
    // read comport manual
    void handleComportError(QSerialPort::SerialPortError serialPortError);
    void readDataComport();
    // read adb
    void handleCmdError(QProcess::ProcessError processError);
    void readDataCmd();
    /*tbw Left click*/
    void tbwProcessLeft(int iRow, int iCol);
    /*tbw Right click*/
    void tbwProcessRight(int iRow, int iCol);

private slots:
/*button alllllll*/
    void on_tabWidget_tabBarClicked(int iIndex);

    void on_btnScanCOM_clicked();

    void on_btnCoDisComport_clicked();

    void on_btnSendCOM_clicked();

    void on_btnClearCOM_clicked();

    void on_btnScanDevices_clicked();

    void on_btnSendADB_clicked();

    void on_btnClearCMD_clicked();

    void on_tbwLogLeft_itemClicked(QTableWidgetItem *item);

    void on_btnDisconnectAll_clicked();

    void on_btnOpenATK_clicked();

    void on_btnDelATK_clicked();

    void on_btnOpenClear_clicked();

    void on_btnClearFolderOutput_clicked();

    void on_btnClearFolderPhone_clicked();

    void on_btnDelLog_clicked();

    void on_btnLogo_clicked();

    void on_btnDeviceManeger_clicked();

    void on_btnADBCMD_clicked();

    void on_btnADBKillserver_clicked();

    void on_btnInital_clicked();

    void on_cbbSelectModel_currentIndexChanged(int iIndex);

    void on_cbbSelectParaCam_activated(int iInDexCam);

    void on_cbbSizeStain_activated(int iInDexSize);

    void on_cbbSizeWhiteStain_activated(int iInDexSize);

    void on_cbbRoiGlare_activated(int iInDex);

    void on_btn_clynderFWD_left_clicked();
    void on_btn_clynderMID_left_clicked();
    void on_btn_clynderBWD_left_clicked();
    void on_btn_ledON_left_clicked();
    void on_btn_ledOFF_left_clicked();
    void on_btn_clynderFWD_right_clicked();
    void on_btn_clynderMID_right_clicked();
    void on_btn_clynderBWD_right_clicked();
    void on_btn_ledOFF_right_clicked();
    void on_btn_ledON_right_clicked();
    void on_btnStartSimulator_clicked();
    void on_btnStopSimulator_clicked();
};
#endif // MAINWINDOW_H
