#include "processcheckauto.h"
#include "mainwindow.h"

/*=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=*/
//Stain - front stain
//Process Stain Small Size
aProcessSStain::aProcessSStain(QObject *parent) : QThread(parent) {
    m_bRun = false;
    iIMG = -1;
    status = aTHREAD_NONE;
    bResult = false;
}

aProcessSStain::~aProcessSStain() {
    this->StopThread();
    this->terminate();
    this->wait(10);
}

void aProcessSStain::StartThread() {
    m_bRun = true;
    status = aTHREAD_RUNNING;
    bResult = false;
    this->start(QThread::NormalPriority);
}

void aProcessSStain::StopThread() {
    m_bRun = false;
    iIMG = -1;
    status = aTHREAD_STOP;
    usleep(10000);
    this->quit();
}

void aProcessSStain::run() {
    QMutex mutex;
    mutex.lock();
    emit threadaProcessSStain(iIMG);
    mutex.unlock();
}

/*=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=*/
//Stain - front stain
//Process Stain Large Size
aProcessLStain::aProcessLStain(QObject *parent) : QThread(parent) {
    m_bRun = false;
    iIMG = -1;
    status = aTHREAD_NONE;
    bResult = false;
}
aProcessLStain::~aProcessLStain() {
    this->StopThread();
    this->terminate();
    this->wait(10);
}

void aProcessLStain::StartThread() {
    m_bRun = true;
    status = aTHREAD_RUNNING;
    bResult = false;
    this->start(QThread::NormalPriority);
}

void aProcessLStain::StopThread() {
    m_bRun = false;
    iIMG = -1;
    status = aTHREAD_STOP;
    usleep(10000);
    this->quit();
}


void aProcessLStain::run() {
    QMutex mutex;
    mutex.lock();
    emit threadaProcessLStain(iIMG);
    mutex.unlock();
}
/*=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=*/
//darkspot - dust
//Process Darkspot
aProcessDarkSpot::aProcessDarkSpot(QObject *parent) : QThread(parent) {
    m_bRun = false;
    iIMG = -1;
    status = aTHREAD_NONE;
    bResult = false;
}

aProcessDarkSpot::~aProcessDarkSpot() {
    this->StopThread();
    this->terminate();
    this->wait(10);
}

void aProcessDarkSpot::StartThread() {
    m_bRun = true;
    status = aTHREAD_RUNNING;
    bResult = false;
    this->start(QThread::NormalPriority);
}

void aProcessDarkSpot::StopThread() {
    m_bRun = false;
    iIMG = -1;
    status = aTHREAD_STOP;
    usleep(10000);
    this->quit();
}


void aProcessDarkSpot::run() {
    QMutex mutex;
    mutex.lock();
    emit threadaProcessDarkspot(iIMG);
    mutex.unlock();
}

/*=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=*/
//WrongColor - Gray
//Process WrongColor
aProcessWrongColor::aProcessWrongColor(QObject *parent) : QThread(parent) {
    m_bRun = false;
    iIMG = -1;
    status = aTHREAD_NONE;
    bResult = false;
}
aProcessWrongColor::~aProcessWrongColor() {
    this->StopThread();
    this->terminate();
    this->wait(10);
}
void aProcessWrongColor::StartThread() {
    m_bRun = true;
    status = aTHREAD_RUNNING;
    bResult = false;
    this->start(QThread::NormalPriority);
}
void aProcessWrongColor::StopThread() {
    m_bRun = false;
    iIMG = -1;
    status = aTHREAD_STOP;
    usleep(10000);
    this->quit();
}
void aProcessWrongColor::run() {
    QMutex mutex;
    mutex.lock();
    emit threadaProcessWrongColor(iIMG);
    mutex.unlock();
}

/*=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=*/
//Glare
//Process Glare
aProcessGlare::aProcessGlare(QObject *parent) : QThread(parent) {
    m_bRun = false;
    iIMG = -1;
    status = aTHREAD_NONE;
    bResult = false;
}
aProcessGlare::~aProcessGlare() {
    this->StopThread();
    this->terminate();
    this->wait(10);
}

void aProcessGlare::StartThread() {
    m_bRun = true;
    status = aTHREAD_RUNNING;
    bResult = false;
    this->start(QThread::NormalPriority);
}

void aProcessGlare::StopThread() {
    m_bRun = false;
    iIMG = -1;
    status = aTHREAD_STOP;
    usleep(10000);
    this->quit();
}

void aProcessGlare::run() {
    QMutex mutex;
    mutex.lock();
    emit threadaProcessGlare(iIMG);
    mutex.unlock();
}
/*=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=*/
//WhiteStain
//Process WhiteStain Small Size
aProcessWhiteSStain::aProcessWhiteSStain(QObject *parent) : QThread(parent) {
    m_bRun = false;
    iIMG = -1;
    status = aTHREAD_NONE;
    bResult = false;
}
aProcessWhiteSStain::~aProcessWhiteSStain() {
    this->StopThread();
    this->terminate();
    this->wait(10);
}

void aProcessWhiteSStain::StartThread() {
    m_bRun = true;
    status = aTHREAD_RUNNING;
    bResult = false;
    this->start(QThread::NormalPriority);
}

void aProcessWhiteSStain::StopThread() {
    m_bRun = false;
    iIMG = -1;
    status = aTHREAD_STOP;
    usleep(10000);
    this->quit();
}

void aProcessWhiteSStain::run() {
    QMutex mutex;
    mutex.lock();
    emit threadaProcessWhiteSStain(iIMG);
    mutex.unlock();
}

/*=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=*/
//WhiteStain
//Process WhiteStain Large Size
aProcessWhiteLStain::aProcessWhiteLStain(QObject *parent) : QThread(parent) {
    m_bRun = false;
    iIMG = -1;
    status = aTHREAD_NONE;
    bResult = false;
}
aProcessWhiteLStain::~aProcessWhiteLStain() {
    this->StopThread();
    this->terminate();
    this->wait(10);
}

void aProcessWhiteLStain::StartThread() {
    m_bRun = true;
    status = aTHREAD_RUNNING;
    bResult = false;
    this->start(QThread::NormalPriority);
}
void aProcessWhiteLStain::StopThread() {
    m_bRun = false;
    iIMG = -1;
    status = aTHREAD_STOP;
    usleep(10000);
    this->quit();
}

void aProcessWhiteLStain::run() {
    QMutex mutex;
    mutex.lock();
    emit threadaProcessWhiteLStain(iIMG);
    mutex.unlock();
}

/*=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=*/
//Focus
//Process Focus
aProcessFocus::aProcessFocus(QObject *parent) : QThread(parent) {
    m_bRun = false;
    iIMG = -1;
    status = aTHREAD_NONE;
    bResult = false;
}

aProcessFocus::~aProcessFocus() {
    this->StopThread();
    this->terminate();
    this->wait(10);
}

void aProcessFocus::StartThread() {
    m_bRun = true;
    status = aTHREAD_RUNNING;
    bResult = false;
    this->start(QThread::NormalPriority);
}
void aProcessFocus::StopThread() {
    m_bRun = false;
    iIMG = -1;
    status = aTHREAD_STOP;
    usleep(10000);
    this->quit();
}

void aProcessFocus::run() {
    QMutex mutex;
    mutex.lock();
    emit threadaProcessFocus(iIMG);
    mutex.unlock();
}

/*=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=*/
//Process
aProcessDoThing::aProcessDoThing(QObject *parent) : QThread(parent) {
    m_bRun = false;
    status = aTHREAD_NONE;
}

aProcessDoThing::~aProcessDoThing() {
    this->StopThread();
    this->terminate();
    this->wait(10);
}

void aProcessDoThing::StartThread() {
    m_bRun = true;
    status = aTHREAD_RUNNING;
    this->start(QThread::NormalPriority);
}
void aProcessDoThing::StopThread() {
    m_bRun = false;
    status = aTHREAD_STOP;
    usleep(10000);
    this->quit();
}

void aProcessDoThing::run() {
    QMutex mutex;
    mutex.lock();
    emit threadaProcessDoThing();
    mutex.unlock();
}

/*=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=*/
//Process
aProcessDoThingWait::aProcessDoThingWait(QObject *parent) : QThread(parent) {
    m_bRun = false;
    status = aTHREAD_NONE;
}

aProcessDoThingWait::~aProcessDoThingWait() {
    this->StopThread();
    this->terminate();
    this->wait(10);
}

void aProcessDoThingWait::StartThread() {
    m_bRun = true;
    status = aTHREAD_RUNNING;
    this->start(QThread::NormalPriority);
}

void aProcessDoThingWait::StopThread() {
    m_bRun = false;
    status = aTHREAD_STOP;
    usleep(10000);
    this->quit();
}

void aProcessDoThingWait::run() {
    QMutex mutex;
    mutex.lock();
    while(m_bRun){
    emit threadaProcessDoThingWait();
        msleep(30);
    }

    mutex.unlock();
}
