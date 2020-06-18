#include "process.h"
#include "mainwindow.h"

/*=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=*/
//ProcessCheckComIO - ProcessCheckComIO
//ProcessCheckComIO
ProcessCheckComIO::ProcessCheckComIO(QObject *parent) : QThread(parent) {

    m_bRun = false;
    code = -1;
    status = THREAD_NONE;
    bResult = false;
}
ProcessCheckComIO::~ProcessCheckComIO() {

    this->StopThread();
    this->terminate();
    this->wait(10);
}

void ProcessCheckComIO::StartThread() {

    m_bRun = true;
    status = THREAD_RUNNING;
    bResult = false;
    this->start(QThread::NormalPriority);
}

void ProcessCheckComIO::StopThread() {

    m_bRun = false;
    code = -1;
    status = THREAD_STOP;
    usleep(10000);
    this->quit();
}

void ProcessCheckComIO::Loop()
{
    static MainWindow* parent = (MainWindow*)this->parent();
    parent->readDataComIO();

}


void ProcessCheckComIO::run() {

    while(this->m_bRun){
        QMutex mutex;
        mutex.lock();
        Loop();
        msleep(30);
        mutex.unlock();
    }

}

/*=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=*/
//Stain - front stain
//Process Stain Small Size
ProcessSStain::ProcessSStain(QObject *parent) : QThread(parent) {
    m_bRun = false;
    code = -1;
    status = THREAD_NONE;
    bResult = false;
}

ProcessSStain::~ProcessSStain() {
    this->StopThread();
    this->terminate();
    this->wait(10);
}

void ProcessSStain::StartThread() {
    m_bRun = true;
    status = THREAD_RUNNING;
    bResult = false;
    this->start(QThread::NormalPriority);
}

void ProcessSStain::StopThread() {

    m_bRun = false;
    code = -1;
    status = THREAD_STOP;
    usleep(10000);
    this->quit();
}

void ProcessSStain::run() {
    QMutex mutex;
    mutex.lock();
    emit threadProcessSStain(code);
    mutex.unlock();
}

/*=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=*/
//Stain - front stain
//Process Stain Large Size
ProcessLStain::ProcessLStain(QObject *parent) : QThread(parent) {

    m_bRun = false;
    code = -1;
    status = THREAD_NONE;
    bResult = false;
}
ProcessLStain::~ProcessLStain() {

    this->StopThread();
    this->terminate();
    this->wait(10);
}

void ProcessLStain::StartThread() {

    m_bRun = true;
    status = THREAD_RUNNING;
    bResult = false;
    //this->start(QThread::NormalPriority);
    this->start(QThread::NormalPriority);
}

void ProcessLStain::StopThread() {

    m_bRun = false;
    code = -1;
    status = THREAD_STOP;
    usleep(10000);
    this->quit();
}


void ProcessLStain::run() {

    QMutex mutex;
    mutex.lock();
    emit threadProcessLStain(code);
    mutex.unlock();
}
/*=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=*/
//darkspot - dust
//Process Darkspot
ProcessDarkSpot::ProcessDarkSpot(QObject *parent) : QThread(parent) {

    m_bRun = false;
    code = -1;
    status = THREAD_NONE;
    bResult = false;
}
ProcessDarkSpot::~ProcessDarkSpot() {

    this->StopThread();
    this->terminate();
    this->wait(10);
}

void ProcessDarkSpot::StartThread() {

    m_bRun = true;
    status = THREAD_RUNNING;
    bResult = false;
    //this->start(QThread::NormalPriority);
    this->start(QThread::NormalPriority);
}

void ProcessDarkSpot::StopThread() {

    m_bRun = false;
    code = -1;
    status = THREAD_STOP;
    usleep(10000);
    this->quit();
}


void ProcessDarkSpot::run() {

    QMutex mutex;
    mutex.lock();
    emit threadProcessDarkspot(code);
    mutex.unlock();
}

/*=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=*/
//WrongColor - Gray
//Process WrongColor
ProcessWrongColor::ProcessWrongColor(QObject *parent) : QThread(parent) {

    m_bRun = false;
    code = -1;
    status = THREAD_NONE;
    bResult = false;
}
ProcessWrongColor::~ProcessWrongColor() {

    this->StopThread();
    this->terminate();
    this->wait(10);
}
void ProcessWrongColor::StartThread() {

    m_bRun = true;
    status = THREAD_RUNNING;
    bResult = false;
    //this->start(QThread::NormalPriority);
    this->start(QThread::NormalPriority);
}
void ProcessWrongColor::StopThread() {

    m_bRun = false;
    code = -1;
    status = THREAD_STOP;
    usleep(10000);
    this->quit();

}
void ProcessWrongColor::run() {

    QMutex mutex;
    mutex.lock();
    emit threadProcessWrongColor(code);
    mutex.unlock();
}

/*=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=*/
//Glare
//Process Glare
void ProcessGlare::StartThread() {
    m_bRun = true;
    status = THREAD_RUNNING;
    bResult = false;
    //this->start(QThread::NormalPriority);
    this->start(QThread::NormalPriority);
}
void ProcessGlare::StopThread() {
    m_bRun = false;
    code = -1;
    status = THREAD_STOP;
    usleep(10000);
    this->quit();
}
ProcessGlare::ProcessGlare(QObject *parent) : QThread(parent) {
    m_bRun = false;
    code = -1;
    status = THREAD_NONE;
    bResult = false;
}
ProcessGlare::~ProcessGlare() {
    this->StopThread();
    this->terminate();
    this->wait(10);
}
void ProcessGlare::run() {
    QMutex mutex;
    mutex.lock();
    emit threadProcessGlare(code);
    mutex.unlock();
}
/*=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=*/
//WhiteStain
//Process WhiteStain Small Size
void ProcessWhiteSStain::StartThread() {

    m_bRun = true;
    status = THREAD_RUNNING;
    bResult = false;
    this->start(QThread::NormalPriority);
}
void ProcessWhiteSStain::StopThread() {
    m_bRun = false;
    code = -1;
    status = THREAD_STOP;
    usleep(10000);
    this->quit();
}
ProcessWhiteSStain::ProcessWhiteSStain(QObject *parent) : QThread(parent) {

    m_bRun = false;
    code = -1;
    status = THREAD_NONE;
    bResult = false;
}
ProcessWhiteSStain::~ProcessWhiteSStain() {

    this->StopThread();
    this->terminate();
    this->wait(10);
}
void ProcessWhiteSStain::run() {

    QMutex mutex;
    mutex.lock();
    emit threadProcessWhiteSStain(code);
    mutex.unlock();
}

/*=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=*/
//WhiteStain
//Process WhiteStain Large Size
void ProcessWhiteLStain::StartThread() {

    m_bRun = true;
    status = THREAD_RUNNING;
    bResult = false;
    this->start(QThread::NormalPriority);
}
void ProcessWhiteLStain::StopThread() {
    m_bRun = false;
    code = -1;
    status = THREAD_STOP;
    usleep(10000);
    this->quit();
}
ProcessWhiteLStain::ProcessWhiteLStain(QObject *parent) : QThread(parent) {

    m_bRun = false;
    code = -1;
    status = THREAD_NONE;
    bResult = false;
}
ProcessWhiteLStain::~ProcessWhiteLStain() {

    this->StopThread();
    this->terminate();
    this->wait(10);
}
void ProcessWhiteLStain::run() {

    QMutex mutex;
    mutex.lock();
    emit threadProcessWhiteLStain(code);
    mutex.unlock();
}

/*=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=*/
//Focus
//Process Focus
void ProcessFocus::StartThread() {

    m_bRun = true;
    status = THREAD_RUNNING;
    bResult = false;
    this->start(QThread::NormalPriority);
}
void ProcessFocus::StopThread() {
    m_bRun = false;
    code = -1;
    status = THREAD_STOP;
    usleep(10000);
    this->quit();
}
ProcessFocus::ProcessFocus(QObject *parent) : QThread(parent) {

    m_bRun = false;
    code = -1;
    status = THREAD_NONE;
    bResult = false;
}
ProcessFocus::~ProcessFocus() {

    this->StopThread();
    this->terminate();
    this->wait(10);
}
void ProcessFocus::run() {

    QMutex mutex;
    mutex.lock();
    emit threadProcessFocus(code);
    mutex.unlock();
}


ThreadIO::ThreadIO(QString strCom, QObject *parent)
{
    pCom = new QSerialPort(this);
    pCom->setPortName(strCom); //ttyUSB1
    pCom->setBaudRate(9600);

    pCom->setDataBits(QSerialPort::Data8);
    pCom->setParity(QSerialPort::NoParity);
    pCom->setStopBits(QSerialPort::OneStop);
    pCom->setFlowControl(QSerialPort::NoFlowControl);
    if (pCom->open(QIODevice::ReadWrite)){
        qDebug() << "Open OK" << pCom->portName();
        connect(pCom, &QSerialPort::readyRead, this, &ThreadIO::readDataCOM);
        connect(pCom, &QSerialPort::errorOccurred, this, &ThreadIO::ErrorComportIO);
    }
    else
        qDebug() << "Open Fail" << pCom->portName();

    connect(this, SIGNAL(emitThreadIO(QString)), this, SLOT(sendDataCOM(QString)));
}

ThreadIO::~ThreadIO()
{

}

void ThreadIO::StartThread()
{
    m_bRun = true;
    this->start(QThread::HighestPriority);

}

void ThreadIO::StopThread()
{
    m_bRun = false;

    if(pCom->isOpen()){
        pCom->close();
    }
    this->quit();
}

void ThreadIO::LoopIO()
{
    if(!pCom->isReadable())
        return;

    QByteArray str1 = pCom->read(1);

    if(str1 == "I"){
        bEnable = true;
    }
    if(bEnable){
        strData += str1;
        //qDebug()<<"DATA COMPORT IO: "<< pCom->portName() << strData<< " - "<<strData.length();
    }
    if(str1 == "\n"){
        bEnable = false;
        QByteArray qstrDataTemp = strData;
        if(qstrDataTemp.length() == 5){
            qDebug()<<"DATA COMPORT IO: "<< pCom->portName() << qstrDataTemp<< " - "<<qstrDataTemp.length();
            QString temp = splitStrComIO(qstrDataTemp);
            short iTemp = temp.toShort();

            short iAnd;
            iAnd = iTemp&Input_1;
            if(iAnd == (short)1){
                m_InStart = false;
                qDebug()<<"Input Start OFF";
            }
            else{
                m_InStart = true;
                qDebug()<<"Input Start ON";
            }

            iAnd = iTemp&Input_2;
            if(iAnd == (short)1){
                m_InClynderFWD = false;
            }
            else{
                m_InClynderFWD = true;
            }

            iAnd = iTemp&Input_3;
            if(iAnd == (short)1){
                m_InClynderMID = false;
            }
            else{
                m_InClynderMID = true;
            }

            iAnd = iTemp&Input_4;
            if(iAnd == (short)1){
                m_InClynderBWD = false;
            }
            else{
                m_InClynderBWD = true;
            }

        }
        strData.clear();
        pCom->clear(QSerialPort::Direction::AllDirections);
    }
}

bool ThreadIO::isOpen()
{
    return pCom->isOpen();
}

void ThreadIO::readDataCOM()
{
    LoopIO();
}

void ThreadIO::sendDataCOM(QString str)
{
    QMutex mutex;
    mutex.lock();
    if(pCom->isWritable()){

        pCom->write(str.toLocal8Bit());
        //        qDebug() << "send " << pCom->portName() << ": " << str;
    }
    mutex.unlock();
}

void ThreadIO::run()
{
    while (m_bRun ) {
        if(pCom->error() == QSerialPort::NoError)
            emit emitThreadIO("I");

        msleep(30);

    }
}

QString ThreadIO::splitStrComIO(QString str)
{
    QString strRes = "null";
    QStringList listStr= str.split("\r\n");
    if (listStr.size() > 1){
        strRes = listStr.at(0);
        strRes = strRes.remove("I");
    }

    return strRes;

}

void ThreadIO::ErrorComportIO(QSerialPort::SerialPortError serialPortError)
{
    if(pCom->isOpen())
        emit emitErrorComportIO();
    pCom->close();
    msleep(1000);
}


//Process Simulation
processSimulation::processSimulation(QObject *parent) : QThread(parent) {

    status = THREAD_NONE;
    m_bRun = false;
    iCam = FW1;
    iModel = SIDE_LEFT;
    ListImage.push_back("");
}
processSimulation::~processSimulation() {
    StopThread();
    terminate();
    wait(10);
}

void processSimulation::StartThread() {

    m_bRun = true;
    status = THREAD_RUNNING;
    start(QThread::NormalPriority);
}

void processSimulation::StopThread() {
    status = THREAD_STOP;
    m_bRun = false;
    msleep(10);
    quit();
}


void processSimulation::run() {

    emit threadsimulation(iCam, iModel, ListImage);
}
