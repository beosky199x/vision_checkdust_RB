#ifndef PROCESSCHECKAUTO_H
#define PROCESSCHECKAUTO_H

#include <QThread>
#include <QElapsedTimer>

enum  _eaStatusThread{
    aTHREAD_NONE = -1,
    aTHREAD_STOP,
    aTHREAD_RUNNING,
};

//Process Stain as front check Stain small size
class aProcessSStain : public QThread {
    Q_OBJECT
public:
    explicit aProcessSStain(QObject *parent = 0);
    ~aProcessSStain();
    void    StartThread();
    void    StopThread();
    bool    m_bRun;
    int     iIMG;
    int     status;
    bool    bResult;
protected:
    void run();
signals:
    void threadaProcessSStain(int iIMG);
};

//Process Stain as front check Stain large size
class aProcessLStain : public QThread {
    Q_OBJECT
public:
    explicit aProcessLStain(QObject *parent = 0);
    ~aProcessLStain();
    void    StartThread();
    void    StopThread();
    bool    m_bRun;
    int     iIMG;
    int     status;
    bool    bResult;
protected:
    void run();
signals:
    void threadaProcessLStain(int iIMG);
};


//Process Darkspot as front check black dust
class aProcessDarkSpot : public QThread {
    Q_OBJECT
public:
    explicit aProcessDarkSpot(QObject *parent = 0);
    ~aProcessDarkSpot();
    void    StartThread();
    void    StopThread();
    bool    m_bRun;
    int     iIMG;
    int     status;
    bool    bResult;
protected:
    void run();
signals:
    void threadaProcessDarkspot(int iIMG);
};

//Process WrongColor as Front check Gray
class aProcessWrongColor : public QThread {
    Q_OBJECT
public:
    explicit aProcessWrongColor(QObject *parent = 0);
    ~aProcessWrongColor();
    void    StartThread();
    void    StopThread();
    bool    m_bRun;
    int     iIMG;
    int     status;
    bool    bResult;
protected:
    void run();
signals:
    void threadaProcessWrongColor(int iIMG);
};

//Process Glare front camera
class aProcessGlare : public QThread {
    Q_OBJECT
public:
    explicit aProcessGlare(QObject *parent = 0);
    ~aProcessGlare();
    void    StartThread();
    void    StopThread();
    bool    m_bRun;
    int     iIMG;
    int     status;
    bool    bResult;
protected:
    void run();
signals:
    void threadaProcessGlare(int iIMG);
};

//Process WhiteStain Small Size
class aProcessWhiteSStain : public QThread {
    Q_OBJECT
public:
    explicit aProcessWhiteSStain(QObject *parent = 0);
    ~aProcessWhiteSStain();
    void    StartThread();
    void    StopThread();
    bool    m_bRun;
    int     iIMG;
    int     status;
    bool    bResult;
protected:
    void run();
signals:
    void threadaProcessWhiteSStain(int iIMG);
};

//Process WhiteStain Large Size
class aProcessWhiteLStain : public QThread {
    Q_OBJECT
public:
    explicit aProcessWhiteLStain(QObject *parent = 0);
    ~aProcessWhiteLStain();
    void    StartThread();
    void    StopThread();
    bool    m_bRun;
    int     iIMG;
    int     status;
    bool    bResult;
protected:
    void run();
signals:
    void threadaProcessWhiteLStain(int iIMG);
};


//Process check focus
class aProcessFocus : public QThread {
    Q_OBJECT
public:
    explicit aProcessFocus(QObject *parent = 0);
    ~aProcessFocus();
    void    StartThread();
    void    StopThread();
    bool    m_bRun;
    int     iIMG;
    int     status;
    bool    bResult;
protected:
    void run();
signals:
    void threadaProcessFocus(int iIMG);
};

//Process Check
class aProcessDoThing : public QThread {
    Q_OBJECT
public:
    explicit aProcessDoThing(QObject *parent = 0);
    ~aProcessDoThing();
    void    StartThread();
    void    StopThread();
    bool    m_bRun;
    int     status;
    bool    bResult;
protected:
    void run();
signals:
    void threadaProcessDoThing();
};

//Process Wait Dothing
class aProcessDoThingWait : public QThread {
    Q_OBJECT
public:
    explicit aProcessDoThingWait(QObject *parent = 0);
    ~aProcessDoThingWait();
    void    StartThread();
    void    StopThread();
    bool    m_bRun;
    int     status;
    bool    bResult;
protected:
    void run();
signals:
    void threadaProcessDoThingWait();
};


#endif //PROCESSCHECKAUTO_H
