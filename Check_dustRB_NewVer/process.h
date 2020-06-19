#ifndef PROCESS_H
#define PROCESS_H

#include <QThread>
#include <QElapsedTimer>
#include <QSerialPort>

enum  _eStatusThread{
    THREAD_NONE = -1,
    THREAD_STOP,
    THREAD_RUNNING,
};

//Process CheckComIO
class ProcessCheckComIO : public QThread
{
    Q_OBJECT
public:
    explicit ProcessCheckComIO(QObject *parent = 0);
    ~ProcessCheckComIO();

    void StartThread();
    void StopThread();
    bool m_bRun;
    int code;
    int status;
    bool bResult;
public:
    void Loop();
protected:
    void run();
signals:
    void threadProcessCheckComIO();
};
//Process Stain as front check Stain small size
class ProcessSStain : public QThread
{
    Q_OBJECT
public:
    explicit ProcessSStain(QObject *parent = 0);
    ~ProcessSStain();
    void    StartThread();
    void    StopThread();
    bool    m_bRun;
    int     code;
    int     status;
    bool    bResult;
protected:
    void run();
signals:
    void threadProcessSStain(int i);
};

//Process Stain as front check Stain large size
class ProcessLStain : public QThread
{
    Q_OBJECT
public:
    explicit ProcessLStain(QObject *parent = 0);
    ~ProcessLStain();
    void    StartThread();
    void    StopThread();
    bool    m_bRun;
    int     code;
    int     status;
    bool    bResult;
protected:
    void run();
signals:
    void threadProcessLStain(int i);
};


//Process Darkspot as front check black dust
class ProcessDarkSpot : public QThread
{
    Q_OBJECT
public:
    explicit ProcessDarkSpot(QObject *parent = 0);
    ~ProcessDarkSpot();
    void    StartThread();
    void    StopThread();
    bool    m_bRun;
    int     code;
    int     status;
    bool    bResult;
protected:
    void run();
signals:
    void threadProcessDarkspot(int i);
};

//Process WrongColor as Front check Gray
class ProcessWrongColor : public QThread
{
    Q_OBJECT
public:
    explicit ProcessWrongColor(QObject *parent = 0);
    ~ProcessWrongColor();
    void    StartThread();
    void    StopThread();
    bool    m_bRun;
    int     code;
    int     status;
    bool    bResult;
protected:
    void run();
signals:
    void threadProcessWrongColor(int i);
};

//Process Glare front camera
class ProcessGlare : public QThread
{
    Q_OBJECT
public:
    explicit ProcessGlare(QObject *parent = 0);
    ~ProcessGlare();
    void    StartThread();
    void    StopThread();
    bool    m_bRun;
    int     code;
    int     status;
    bool    bResult;
protected:
    void run();
signals:
    void threadProcessGlare(int i);
};

//Process WhiteStain Small Size
class ProcessWhiteSStain : public QThread
{
    Q_OBJECT
public:
    explicit ProcessWhiteSStain(QObject *parent = 0);
    ~ProcessWhiteSStain();
    void    StartThread();
    void    StopThread();
    bool    m_bRun;
    int     code;
    int     status;
    bool    bResult;
protected:
    void run();
signals:
    void threadProcessWhiteSStain(int i);
};

//Process WhiteStain Large Size
class ProcessWhiteLStain : public QThread
{
    Q_OBJECT
public:
    explicit ProcessWhiteLStain(QObject *parent = 0);
    ~ProcessWhiteLStain();
    void    StartThread();
    void    StopThread();
    bool    m_bRun;
    int     code;
    int     status;
    bool    bResult;
protected:
    void run();
signals:
    void threadProcessWhiteLStain(int i);
};


//Process check focus
class ProcessFocus : public QThread
{
    Q_OBJECT
public:
    explicit ProcessFocus(QObject *parent = 0);
    ~ProcessFocus();
    void    StartThread();
    void    StopThread();
    bool    m_bRun;
    int     code;
    int     status;
    bool    bResult;
protected:
    void run();
signals:
    void threadProcessFocus(int i);
};

class ThreadIO : public QThread
{
    Q_OBJECT
public:
     ThreadIO(QString strCom, QObject *parent = 0);
    ~ThreadIO();
    void StartThread();
    void StopThread();
    bool m_bRun = false ;
    void LoopIO();
    bool isOpen();
private slots:
    void    readDataCOM();
public slots:
    void    sendDataCOM(QString str);
protected:
    void run();
public:
    QSerialPort *pCom;
    bool m_InStart = false;
    bool m_InClynderFWD = false;
    bool m_InClynderMID = false;
    bool m_InClynderBWD = false;
private:
    QString splitStrComIO(QString str);
    QByteArray strData;
    bool bEnable = false;
public slots:
    void ErrorComportIO(QSerialPort::SerialPortError serialPortError);
signals:
    void emitErrorComportIO();
    void emitThreadIO(QString str);
};

//Simulation Loop
class processSimulation : public QThread {
    Q_OBJECT
public:
    explicit processSimulation(QObject *parent = 0);
    ~processSimulation();
    void    StartThread();
    void    StopThread();
    bool    m_bRun;



    int iCam;
    int iModel;
    QStringList ListImage;

    int iStep;
    int status;

protected:
    void run();
signals:
    void threadsimulation(int iC, int iM, QStringList lImage);
};


#endif // PROCESS_H
