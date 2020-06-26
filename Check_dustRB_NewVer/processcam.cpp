#include "processcam.h"

ProcessCam::ProcessCam(_sMainUI stransMainUi, _sDeviceParam stransDevices, int itransSide, _sGeneral stransGeneral) {
    /* - - --------------------------------------------------------------------------------------------------- - - */
    linkMain = stransMainUi;
    iSide    = itransSide;
    mGenenal = stransGeneral;
    mDevice  = stransDevices;
    m_bRun   = false;

    if(mGenenal.Device.ipModel >= G975){
        iTotalCam = FB1;
        iTotalImg = 4;
    }
    else{
        iTotalCam = FW1;
        iTotalImg = 2;
    }

    /*opt var*/
        bSaveImgResize      = mGenenal.bOptSaveImageResize;
    for(int i = FW1; i<= iTotalCam; i++){
        bShowImg[i]         = mGenenal.bOptShowImg[i];
        bSaveImg[i]         = mGenenal.bOptSaveImg[i];
        bCheckIris          = mGenenal.bOptCheckIris;
        bCheckStain[i]      = mGenenal.bOptCheckStain[i];
        bCheckWhiteStain[i] = mGenenal.bOptCheckWhiteStain[i];
        bCheckGlare[i]      = mGenenal.bOptCheckGlare[i];
        bCheckFocus[i]      = mGenenal.bOptCheckFocus[i];
        bCheckDarkSport[i]  = mGenenal.bOptDarkSport[i];
        bCheckColor[i]      = mGenenal.bOptCheckColor[i];
        bCaptureUseAF[i]    = mGenenal.bOptCaptrueAf[i];
        bResultCam[i]       = false;

        if(!bCheckGlare[i] && !bCheckFocus[i]){
            iTotalImg--;
            numCap[i] = 1;
        }
    }

    linkMain.lbDisplay->setScaledContents(true);
    linkMain.lbDisplay->installEventFilter(this);
    InitUI();
    /*Load AT, ADB from data*/
    for(int i = AT_UART_USB; i < NUM_AT; i++){
        ATcommand[i] = mGenenal.ATCMD[i];
    }
    for(int i = ADB_GET_LIST; i<NUM_ADB; i++){
        ADBcommand[i] = mGenenal.ADBCMD[i];
    }

    processADB = new QProcess();
    processADB->waitForFinished(5);
    qspCom = mDevice.qspCom;

    if(this->qspCom->isOpen()){
        QObject::connect(qspCom, &QSerialPort::readyRead,     this, &ProcessCam::readDataComport);
        QObject::connect(qspCom, &QSerialPort::errorOccurred, this, &ProcessCam::handleComportError);
        if(iSide == SIDE_LEFT)
            AddLog(tr("Open com port Left %1 OK!").arg(nameSide[iSide]), Qt::black);
        else
            AddLog(tr("Open com port Right %1 OK!").arg(nameSide[iSide]), Qt::black);

        SendCom(qspCom, mGenenal.ATCMD[AT_UART_USB].send);
    }
    else{
        if(iSide == SIDE_LEFT)
            AddLog(tr("Open com port Left %1 NG!").arg(nameSide[iSide]), Qt::red);
        else
            AddLog(tr("Open com port Right %1 NG!").arg(nameSide[iSide]), Qt::red);
    }
    initThread();
    if(ptrIO->isOpen()){
        connect(ptrIO, &ThreadIO::emitErrorComportIO, this, &ProcessCam::handleComportIO);
        if(iSide == SIDE_LEFT)
            AddLog(tr("Open com IO Left %1 OK!").arg(nameSide[iSide]), Qt::black);
        else
            AddLog(tr("Open com IO Right %1 OK!").arg(nameSide[iSide]), Qt::black);
    }
    else{
        if(iSide == SIDE_LEFT)
            AddLog(tr("Open com IO Left %1 NG!").arg(nameSide[iSide]), Qt::red);
        else
            AddLog(tr("Open com IO Right %1 NG!").arg(nameSide[iSide]), Qt::red);
    }
    for(int i = FW1; i < NUM_CAM; i++){
        this->pSStain[i]  = new aProcessSStain(this);
        this->pWhiteSStain[i] = new aProcessWhiteSStain(this);
        this->pLStain[i] = new aProcessLStain(this);
        this->pWhiteLStain[i] = new aProcessWhiteLStain(this);

        this->pGlare[i] = new aProcessGlare(this);
        this->pDarkspot[i] = new aProcessDarkSpot(this);
        this->pFocus[i] = new aProcessFocus(this);
        this->pWrongColor[i] = new aProcessWrongColor(this);
    }

    /*connect signals and slots run thread*/
    QObject::connect(this, SIGNAL(eSendCOM(QSerialPort*,QString)),       this,  SLOT(SendCom(QSerialPort*, QString)));
    QObject::connect(this, SIGNAL(eSendADB(QString)),                    this,  SLOT(SendADB(QString)));
    QObject::connect(this, SIGNAL(eSetResultUI(QLabel*,QString,int)),    this,  SLOT(SetResultUI(QLabel*,QString,int)));
    QObject::connect(this, SIGNAL(eSetReultTbw(QPoint,QString,QColor)),  this,  SLOT(SetResultTbw(QPoint,QString,QColor)));
    QObject::connect(this, SIGNAL(eSetResultCam(QPushButton*,QString)),  this,  SLOT(SetResultCam(QPushButton*,QString)));
    /*FW1*/
    QObject::connect(pSStain[FW1],      SIGNAL(threadaProcessSStain(int)),      this, SLOT(visionSStainFW1(int)));
    QObject::connect(pWhiteSStain[FW1], SIGNAL(threadaProcessWhiteSStain(int)), this, SLOT(visionWhiteSStainFW1(int)));
    QObject::connect(pLStain[FW1],      SIGNAL(threadaProcessLStain(int)),      this, SLOT(visionLStainFW1(int)));
    QObject::connect(pWhiteLStain[FW1], SIGNAL(threadaProcessWhiteLStain(int)), this, SLOT(visionWhiteLStainFW1(int)));
    QObject::connect(pDarkspot[FW1],    SIGNAL(threadaProcessDarkspot(int)),    this, SLOT(visionDarkpotFW1(int)));
    QObject::connect(pWrongColor[FW1],  SIGNAL(threadaProcessWrongColor(int)),  this, SLOT(visionColorFW1(int)));
    QObject::connect(pGlare[FW1],       SIGNAL(threadaProcessGlare(int)),       this, SLOT(visionGlareFW1(int)));
    QObject::connect(pFocus[FW1],       SIGNAL(threadaProcessFocus(int)),       this, SLOT(visionFocusFW1(int)));
    /*FB1*/
    QObject::connect(pSStain[FB1],      SIGNAL(threadaProcessSStain(int)),      this, SLOT(visionSStainFB1(int)));
    QObject::connect(pWhiteSStain[FB1], SIGNAL(threadaProcessWhiteSStain(int)), this, SLOT(visionWhiteSStainFB1(int)));
    QObject::connect(pLStain[FB1],      SIGNAL(threadaProcessLStain(int)),      this, SLOT(visionLStainFB1(int)));
    QObject::connect(pWhiteLStain[FB1], SIGNAL(threadaProcessWhiteLStain(int)), this, SLOT(visionWhiteLStainFB1(int)));
    QObject::connect(pDarkspot[FB1],    SIGNAL(threadaProcessDarkspot(int)),    this, SLOT(visionDarkpotFB1(int)));
    QObject::connect(pWrongColor[FB1],  SIGNAL(threadaProcessWrongColor(int)),  this, SLOT(visionColorFB1(int)));
    QObject::connect(pGlare[FB1],       SIGNAL(threadaProcessGlare(int)),       this, SLOT(visionGlareFB1(int)));
    QObject::connect(pFocus[FB1],       SIGNAL(threadaProcessFocus(int)),       this, SLOT(visionFocusFB1(int)));

    QObject::connect(this,              SIGNAL(eDisplayImage(Mat, QLabel*)),    this, SLOT(Display_Image(Mat, QLabel*)));
    QObject::connect(this,              SIGNAL(eFinishProcess()),               this, SLOT(FinishProcess()));

    QObject::connect(processADB, &QProcess::errorOccurred, this, &ProcessCam::handleCmdError);
    QObject::connect(processADB, &QProcess::readyRead,     this, &ProcessCam::readDataCmd);

    /*init log file*/
    qstrlogFileID = QString(mGenenal.qstrFolderLog) + "/qstrlogFileID_" + QDateTime::currentDateTime().toString("dd-MM-yyyy") + ".txt";
    qflogFileID.setFileName(qstrlogFileID);

    if(qflogFileID.exists()) {
        /*open file*/
        if(qflogFileID.open(QIODevice::ReadWrite| QIODevice::Append | QIODevice::Text)){
            qDebug()<< "Open file: " + qstrlogFileID + " OK" ;
        }
        else{
            qDebug()<< "Open file: " + qstrlogFileID + " NG" ;
        }
    }
    else {
        /*make file*/
        if(qflogFileID.open(QIODevice::ReadWrite| QIODevice::Append | QIODevice::Text)){
            qDebug()<< "Create file: " + qstrlogFileID + " OK" ;
        }
        else{
            qDebug()<< "Create file: " + qstrlogFileID + " NG" ;
        }
    }
    InitMat();
    ResetStatus();
    ResetTbwErr();
    emit Display_Image(mStop,linkMain.lbDisplay);


/*faker*/
//    if(iSide == SIDE_LEFT){
//        emit eSetReultTbw(RES_STAIN_FW1,      "OK", Qt::green);

//        emit eSetReultTbw(RES_WHITESTAIN_FW1,      "NG", Qt::red);

//        AddLog("Start Process", Qt::red);

//        AddLog("Step 1 : Check Iris & Check Stain, Dust, Gray", Qt::black);
//        Mat m = imread("ng.jpg");
//        emit Display_Image(m, linkMain.lbDisplay);
//    }

}

ProcessCam::~ProcessCam() {
    for(int i = FW1; i<NUM_CAM; i++){
        if(pSStain[i]->m_bRun)
            pSStain[i]->StopThread();
        if(pWhiteSStain[i]->m_bRun)
            pWhiteSStain[i]->StopThread();
        if(pLStain[i]->m_bRun)
            pLStain[i]->StopThread();
        if(pWhiteLStain[i]->m_bRun)
            pWhiteLStain[i]->StopThread();
        if(pDarkspot[i]->m_bRun)
            pDarkspot[i]->StopThread();
        if(pWrongColor[i]->m_bRun)
            pWrongColor[i]->StopThread();
        if(pGlare[i]->m_bRun)
            pGlare[i]->StopThread();
        if(pFocus[i]->m_bRun)
            pFocus[i]->StopThread();

        delete pSStain[i];
        delete pWhiteSStain[i];
        delete pLStain[i];
        delete pWhiteLStain[i];
        delete pDarkspot[i];
        delete pWrongColor[i];
        delete pGlare[i];
        delete pFocus[i];
    }

    thread->quit();
    QThread::msleep(1000);



    this->StopThread();
    this->terminate();
    this->wait(10);

     delete ptrIO;
}

void ProcessCam::StartThread() {
    if(mDevice.bUseComSocket){


        if(!m_bRun){
            emit Display_Image(mStart,linkMain.lbDisplay);
            for(int i = FW1; i<=FB1; i++){
                for(int j = IMG_CHECK_STEP1; j <= IMG_CHECK_STEP2; j++){
                    this->mImread[i][j].release();
                    this->mImSave[i][j].release();
                }
            }
            ResetTbwErr();
            fCapCount = 0;
            ResetStatus();
            AddLog("Start Process", Qt::red);
            AddLog("Step 1 : Check Iris & Check Stain, Dust, Gray", Qt::black);
            iCurStep = LOOP_PREPARE;
            for(int i = FW1; i <= iTotalCam; i++){
                bResultCam[i] = false;
            }

            this->m_bRun = true;
            this->start(QThread::HighestPriority);

        }
    }
    else{
        emit Display_Image(mDontUse, linkMain.lbDisplay);
    }
}

void ProcessCam::StopThread() {
    if(mDevice.bUseComSocket){
        AddLog("Stop Process", Qt::red);
        m_bRun = false;
        usleep(10000);
        this->quit();
    }
    else{
        emit Display_Image(mDontUse, linkMain.lbDisplay);
    }
}

void ProcessCam::run() {
    while (m_bRun) {
        LoopProcess();
        msleep(30);
    }
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Run main:=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
void ProcessCam::LoopProcess() {
    switch (iCurStep) {
    case LOOP_DOTHING:{
        /*Notify label*/
//        emit eSetResultUI(linkMain.lbDisplay, listProc[NONE], Qt::yellow);
//        msleep(500);
        /* ... */
    }
        break;
    case LOOP_PREPARE:{

        if(mDevice.bUseComIO){
            emit emitThreadIO(Output1_ON);
            msleep(50);
            emit emitThreadIO(Output2_ON);
        }

        emit eSetResultUI(linkMain.lbDisplay, listProc[PREPARE], Qt::yellow);
        emit eSendADB(tr("adb -s %1 shell input keyevent KEYCODE_WAKEUP").arg(mDevice.qstrID));
        AddLog("Remove folder", Qt::black);
        msleep(2000);
        qstrDataCom.clear();
        emit eSendADB(ADBcommand[ADB_REMOVE_FOLDER].send);
        emit eSendCOM(qspCom, ATcommand[AT_UART_USB].send);
        QDir dir(mDevice.qstrFolderInput + "/fImage");
        dir.removeRecursively();

        if(bCheckIris){
            delay_thread.StartTimer();
            SetStep(LOOP_OPENIRIS_SEND);
        }
        else{
            delay_thread.StartTimer();
            SetStep(LOOP_OPENFW1_SEND);
        }
    }
        break;

    case LOOP_OPENIRIS_SEND: {
        if(delay_thread.LessThan(ATcommand[AT_OPENIRIS].dDelay_Send)) {
            break;
        }
        emit eSetResultUI(linkMain.lbDisplay, listProc[OPEN_IRIS], Qt::yellow);
        AddLog("Open Iris", Qt::black);
        qstrDataCom.clear();
        emit eSendCOM(qspCom,ATcommand[AT_OPENIRIS].send);
        delay_thread.StartTimer();
        SetStep(LOOP_OPENIRIS_WAIT);
    }
        break;
    case LOOP_OPENIRIS_WAIT: {
        if(delay_thread.LessThan(ATcommand[AT_OPENIRIS].dDelay_Wait) && !qstrDataCom.contains(ATcommand[AT_OPENIRIS].respone)){
            qDebug() << ATcommand[AT_OPENIRIS].dDelay_Wait << qstrDataCom;
            break;
        }
        if(qstrDataCom.contains(ATcommand[AT_OPENIRIS].respone)){
            if (qstrDataCom.contains("NG")) {
                emit eSetReultTbw(RES_IRIS_FW1,"NG", Qt::red);
                emit eSetReultTbw(RES_IRIS_FB1,"NG", Qt::red);
                AddLog("Open Iris NG", Qt::red);
                ATcommand[AT_OPENIRIS].iStatus = RES_NG;
                proc_Error = OPEN_IRIS;
                SetStep(LOOP_ERR);
                break;
            }
            else {
                emit eSetReultTbw(RES_IRIS_FW1,"OK", Qt::green);
                emit eSetReultTbw(RES_IRIS_FB1,"OK", Qt::green);
                AddLog("Open Iris OK", Qt::black);
                ATcommand[AT_OPENIRIS].iStatus = RES_OK;
                delay_thread.StartTimer();
                SetStep(LOOP_CLOSEIRIS_SEND);
                break;
            }
        }
        else {
            emit eSetReultTbw(RES_IRIS_FW1,"NG", Qt::red);
            emit eSetReultTbw(RES_IRIS_FB1,"NG", Qt::red);
            AddLog("Open Iris TimeOut!!!", Qt::red);
            ATcommand[AT_OPENIRIS].iStatus = RES_NG;
            proc_Error = OPEN_IRIS;
            SetStep(LOOP_ERR);
            break;
        }
    }
        break;
    case LOOP_CLOSEIRIS_SEND: {
        emit eSetResultUI(linkMain.lbDisplay, listProc[CLOSE_IRIS], Qt::yellow);
        if(delay_thread.LessThan(ATcommand[AT_CLOSEIRIS].dDelay_Send)) {
            break;
        }
        qstrDataCom.clear();
        emit eSendCOM(qspCom,ATcommand[AT_CLOSEIRIS].send);
        AddLog("Closing Iris...", Qt::black);
        delay_thread.StartTimer();
        SetStep(LOOP_CLOSEIRIS_WAIT);
    }
        break;
    case LOOP_CLOSEIRIS_WAIT: {
        if(delay_thread.LessThan(ATcommand[AT_CLOSEIRIS].dDelay_Wait) && !qstrDataCom.contains(ATcommand[AT_CLOSEIRIS].respone)){
            break;
        }
        if(qstrDataCom.contains(ATcommand[AT_CLOSEIRIS].respone)){
            if (qstrDataCom.contains("NG")) {
                AddLog("Close Iris NG", Qt::red);
                proc_Error = CLOSE_IRIS;
                SetStep(LOOP_ERR);
                break;
            }
            else {
                AddLog("Close Iris OK!", Qt::black);
                ATcommand[AT_CLOSEIRIS].iStatus = RES_OK;
                delay_thread.StartTimer();
                SetStep(LOOP_OPENFW1_SEND);
                break;
            }
        }
        else {
            AddLog("Close Iris timeout", Qt::red);
            proc_Error = CLOSE_IRIS;
            SetStep(LOOP_ERR);
            break;
        }
    }
        break;
    case LOOP_OPENFW1_SEND: {
        if(!bCheckIris){
            if(delay_thread.LessThan(ATcommand[AT_OPENFW1].dDelay_Send)){

                break;
            }
        }
        emit eSetResultUI(linkMain.lbDisplay, listProc[OPEN_FW1], Qt::yellow);
        AddLog("Open FW1", Qt::black);
        qstrDataCom.clear();
        emit eSendCOM(qspCom,ATcommand[AT_OPENFW1].send);
        delay_thread.StartTimer();
        SetStep(LOOP_OPENFW1_WAIT);
    }
        break;
    case LOOP_OPENFW1_WAIT: {
        if(delay_thread.LessThan(ATcommand[AT_OPENFW1].dDelay_Wait) && !qstrDataCom.contains(ATcommand[AT_OPENFW1].respone)){
            qDebug() << ATcommand[AT_OPENFW1].dDelay_Wait << qstrDataCom;
            break;
        }
        if(qstrDataCom.contains(ATcommand[AT_OPENFW1].respone)){
            if (qstrDataCom.contains("NG")) {
                AddLog("Open FW1 NG", Qt::red);
                proc_Error = OPEN_FW1;
                SetStep(LOOP_ERR);
                break;
            }
            else {
                /*2 way if... else...*/
                if(!mDevice.bUseComIO||(!bCheckFocus[iCurrentCam]&&!bCheckGlare[iCurrentCam])){
                    iCurrentCam = FW1;
                    AddLog("Open FW1 OK", Qt::black);
                    ATcommand[AT_OPENFW1].iStatus = RES_OK;
                    delay_thread.StartTimer();
                    SetStep(LOOP_CAPTURE_SEND);
                    break;
                }
                else{
                    iCurrentCam = FW1;
                    AddLog("Open FW1 OK", Qt::black);
                    ATcommand[AT_OPENFW1].iStatus = RES_OK;
                    delay_thread.StartTimer();
                    SetStep(LOOP_CLDFORWARD_WAIT);
                    break;
                }
            }
        }
        else {
            AddLog("Open FW1 timeout", Qt::red);
            proc_Error = OPEN_FW1;
            SetStep(LOOP_ERR);
            break;
        }
    }
        break;
        /*FB1 When ipModel >= G975 */
    case LOOP_OPENFB1_SEND:{
        if(delay_thread.LessThan(ATcommand[AT_OPENFB1].dDelay_Send)){
            break;
        }
        emit eSetResultUI(linkMain.lbDisplay, listProc[OPEN_FB1], Qt::yellow);
        AddLog("Open FB1", Qt::black);
        qstrDataCom.clear();
        emit eSendCOM(qspCom,ATcommand[AT_OPENFB1].send);
        delay_thread.StartTimer();
        SetStep(LOOP_OPENFB1_WAIT);
    }
        break;
    case LOOP_OPENFB1_WAIT:{
        if(delay_thread.LessThan(ATcommand[AT_OPENFB1].dDelay_Wait) && !qstrDataCom.contains(ATcommand[AT_OPENFB1].respone)){
            qDebug() << ATcommand[AT_OPENFB1].dDelay_Wait << qstrDataCom;
            break;
        }

        if(qstrDataCom.contains(ATcommand[AT_OPENFB1].respone)){
            if (qstrDataCom.contains("NG")) {
                AddLog("Open FB1 NG", Qt::red);
                proc_Error = OPEN_FB1;
                SetStep(LOOP_ERR);
                break;
            }
            else {
                iCurrentCam = FB1;
                AddLog("Open FB1 OK", Qt::black);
                ATcommand[AT_OPENFB1].iStatus = RES_OK;
                delay_thread.StartTimer();
                SetStep(LOOP_CAPTURE_SEND);
                break;
            }
        }
        else {
            AddLog("Open FB1 timeout", Qt::red);
            proc_Error = OPEN_FB1;
            SetStep(LOOP_ERR);
            break;
        }
    }
        break;
    case LOOP_CLDFORWARD_SEND: {
        AddLog("Clynder forward Send", Qt::black);
        emit emitThreadIO(Output1_ON);
        msleep(50);
        emit emitThreadIO(Output2_ON);
        delay_thread.StartTimer();
        SetStep(LOOP_CLDFORWARD_WAIT);
    }
    case LOOP_CLDFORWARD_WAIT: {
        if(iCurrentCam == FB1){
            if(delay_thread.LessThan(mGenenal.dbDelay[DL_CLYNDER_FORWARD])){
                break;
            }
        }
        QThread::msleep(10);
        AddLog("Clynder forward OK", Qt::black);
        delay_thread.StartTimer();
        SetStep(LOOP_CAPTURE_SEND);
    }
        break;
    case LOOP_CLDBACKWARD_SEND:{
        AddLog("Step 2: Capture IMG Glare + Focus", Qt::black);
        emit eSetResultUI(linkMain.lbDisplay, listProc[CLD_BW], Qt::yellow);
        emit emitThreadIO(Output1_OFF);
        msleep(50);
        emit emitThreadIO(Output2_OFF);
        delay_thread.StartTimer();
        SetStep(LOOP_CLDBACKWARD_WAIT);
    }
        break;
    case LOOP_CLDBACKWARD_WAIT:{
        if(delay_thread.LessThan(mGenenal.dbDelay[DL_CLYNDER_BACKWARD])){
            break;
        }
        AddLog("Clynder Backward OK", Qt::black);
        delay_thread.StartTimer();
        SetStep(LOOP_CAPTURE_SEND);
    }
        break;

    case LOOP_CAPTURE_SEND:{
        emit eSetResultUI(linkMain.lbDisplay, listProc[CAPTURE], Qt::yellow);
        if(bCaptureUseAF[iCurrentCam] || fCapCount == 1){
            if(delay_thread.LessThan(ATcommand[AT_CAPTUREAF].dDelay_Send)) {
                break;
            }
            AddLog("cmd -> Capture use AF", Qt::black);
            qstrDataCom.clear();
            emit eSendCOM(qspCom,ATcommand[AT_CAPTUREAF].send);
        }
        else {
            if(delay_thread.LessThan(ATcommand[AT_CAPTURENOAF].dDelay_Send)) break;
            AddLog("cmd -> Capture dont use AF", Qt::black);
            qstrDataCom.clear();
            emit eSendCOM(qspCom,ATcommand[AT_CAPTURENOAF].send);
        }
        delay_thread.StartTimer();
        SetStep(LOOP_CAPTURE_WAIT);
    }
        break;
    case LOOP_CAPTURE_WAIT: {
        if(bCaptureUseAF[iCurrentCam] || fCapCount == 1){
            if(delay_thread.LessThan(ATcommand[AT_CAPTUREAF].dDelay_Wait) && !qstrDataCom.contains(ATcommand[AT_CAPTUREAF].respone)){
                break;
            }
        }
        else{
            if(delay_thread.LessThan(ATcommand[AT_CAPTURENOAF].dDelay_Wait) && !qstrDataCom.contains(ATcommand[AT_CAPTURENOAF].respone)){
                break;
            }
        }
        if(qstrDataCom.contains(ATcommand[AT_CAPTUREAF].respone)){
            if (qstrDataCom.contains("NG")) {
                AddLog("Capture Error ", Qt::red);
                proc_Error = CAPTURE;
                SetStep(LOOP_ERR);
                break;
            }
            else {
                AddLog(tr("Capture OK_%1").arg(fCapCount+1), Qt::black);
                ATcommand[AT_CAPTUREAF].iStatus = RES_OK;
                if(fCapCount != numCap[iCurrentCam]){
                    fCapCount++;
                }
                if((fCapCount < numCap[iCurrentCam]) && (bCheckFocus[iCurrentCam] || bCheckGlare[iCurrentCam])){
                    delay_thread.StartTimer();
                    if(mDevice.bUseComIO)
                        SetStep(LOOP_CLDBACKWARD_SEND);
                    else
                        SetStep(LOOP_CAPTURE_SEND);
                    break;
                }
                else{
                    if(iCurrentCam == FW1){
                        emit emitThreadIO(Output1_OFF);
                        msleep(50);
                        emit emitThreadIO(Output2_OFF);
                        delay_thread.StartTimer();
                        SetStep(LOOP_CLOSEFW1_SEND);
                        break;
                    }
                    else if(iCurrentCam == FB1){
                        delay_thread.StartTimer();
                        SetStep(LOOP_CLOSEFB1_SEND);
                        break;
                    }
                }
            }
        }
        else {
            AddLog("Capture timeout", Qt::red);
            proc_Error = CAPTURE;
            SetStep(LOOP_ERR);
            break;
        }
    }
        break;
    case LOOP_CLOSEFW1_SEND: {
        if(delay_thread.LessThan(ATcommand[AT_CLOSEFW1].dDelay_Send)){
            break;
        }
        fCapCount = 0;
        qstrDataCom.clear();
        emit eSendCOM(qspCom,ATcommand[AT_CLOSEFW1].send);
        emit eSetResultUI(linkMain.lbDisplay, listProc[CLOSE_FW1], Qt::yellow);
        AddLog("Closing Cam FW1 ...", Qt::black);
        delay_thread.StartTimer();
        SetStep(LOOP_CLOSEFW1_WAIT);
    }
        break;
    case LOOP_CLOSEFW1_WAIT: {
        if(delay_thread.LessThan(ATcommand[AT_CLOSEFW1].dDelay_Wait) && !qstrDataCom.contains(ATcommand[AT_CLOSEFW1].respone)){
            break;
        }
        if(qstrDataCom.contains(ATcommand[AT_CLOSEFW1].respone)){
            if (qstrDataCom.contains("NG")) {
                AddLog("Close cam FW1 NG", Qt::red);
                proc_Error = CLOSE_FW1;
                SetStep(LOOP_ERR);
                break;
            }
            else {
                iCurrentCam = NO;
                AddLog("Close cam FW1 OK!", Qt::black);
                ATcommand[AT_CLOSEFW1].iStatus = RES_OK;

                if(mDevice.ipModel < G975){
                    delay_thread.StartTimer();
                    SetStep(LOOP_GETLIST_SEND);
                    break;
                }
                else{
                    delay_thread.StartTimer();
                    SetStep(LOOP_OPENFB1_SEND);
                    break;
                }
            }
        }
        else {
            AddLog("Close FW1 timeout", Qt::red);
            proc_Error = CLOSE_FW1;
            SetStep(LOOP_ERR);
            break;
        }
    }
        break;
    case LOOP_CLOSEFB1_SEND:{
        if(delay_thread.LessThan(ATcommand[AT_CLOSEFB1].dDelay_Send)){
            break;
        }
        fCapCount = 0;
        qstrDataCom.clear();
        emit eSendCOM(qspCom,ATcommand[AT_CLOSEFB1].send);
        emit eSetResultUI(linkMain.lbDisplay, listProc[CLOSE_FB1], Qt::yellow);
        AddLog("Closing Cam FB1 ...", Qt::black);
        delay_thread.StartTimer();
        SetStep(LOOP_CLOSEFB1_WAIT);
    }
        break;
    case LOOP_CLOSEFB1_WAIT:{
        if(delay_thread.LessThan(ATcommand[AT_CLOSEFB1].dDelay_Wait) && !qstrDataCom.contains(ATcommand[AT_CLOSEFB1].respone)){
            break;
        }
        if(qstrDataCom.contains(ATcommand[AT_CLOSEFB1].respone)){
            if (qstrDataCom.contains("NG")) {
                AddLog("Close cam FW1 NG", Qt::red);
                proc_Error = CLOSE_FB1;
                SetStep(LOOP_ERR);
                break;
            }
            else {
                iCurrentCam = NO;
                AddLog("Close cam FW1 OK!", Qt::black);
                ATcommand[AT_CLOSEFB1].iStatus = RES_OK;
                delay_thread.StartTimer();
                SetStep(LOOP_GETLIST_SEND);
                break;
            }
        }
        else {
            AddLog("Close FB1 timeout", Qt::red);
            proc_Error = CLOSE_FB1;
            SetStep(LOOP_ERR);
            break;
        }
    }
        break;
    case LOOP_GETLIST_SEND: {
        if(delay_thread.LessThan(ADBcommand[ADB_GET_LIST].dDelay_Send)){
            break;
        }
        AddLog("--->Get list image ",Qt::black);
        emit eSetResultUI(linkMain.lbDisplay, listProc[GETLIST], Qt::yellow);
        qstrDataCom.clear();
        emit eSendADB(ADBcommand[ADB_GET_LIST].send);
        delay_thread.StartTimer();
        SetStep(LOOP_GETLIST_WAIT);
    }
        break;
    case LOOP_GETLIST_WAIT: {
        int iCount =  qstrDataADB.count(ADBcommand[ADB_GET_LIST].respone);
        if(delay_thread.LessThan(ADBcommand[ADB_GET_LIST].dDelay_Wait) && iCount != iTotalImg){
            break;
        }
        if(iCount != iTotalImg){
            qDebug() << iCount;
            AddLog("Get List Img timeout or Img Err", Qt::red);
            proc_Error = GETLIST;
            SetStep(LOOP_ERR);
            break;
        }
        AddLog("Get list image OK!",Qt::black);
        ADBcommand[ADB_GET_LIST].iStatus = RES_OK;
        delay_thread.StartTimer();
        SetStep(LOOP_PULL2PC_SEND);
    }
        break;
    case LOOP_PULL2PC_SEND: {
        if(delay_thread.LessThan(ADBcommand[ADB_PULL_TO_PC].dDelay_Send)){
            break;
        }
        AddLog("--->Pull to PC...",Qt::black);
        emit eSendADB(ADBcommand[ADB_PULL_TO_PC].send);
        emit eSetResultUI(linkMain.lbDisplay, listProc[PULL2PC], Qt::yellow);
        delay_thread.StartTimer();
        SetStep(LOOP_PULL2PC_WAIT);
    }
        break;
    case LOOP_PULL2PC_WAIT: {
        if(delay_thread.LessThan(ADBcommand[ADB_PULL_TO_PC].dDelay_Wait) && !qstrDataADB.contains(ADBcommand[ADB_PULL_TO_PC].respone)){
            break;
        }
        if(!qstrDataADB.contains(ADBcommand[ADB_PULL_TO_PC].respone)){
            AddLog("Pull2PC Err", Qt::red);
            proc_Error = PULL2PC;
            SetStep(LOOP_ERR);
            break;
        }
        AddLog("Pull file to PC OK",Qt::black);
        ADBcommand[ADB_PULL_TO_PC].iStatus = RES_OK;
        delay_thread.StartTimer();
        SetStep(LOOP_LOADIMG_DO);
    }
        break;
    case LOOP_LOADIMG_DO: {
        if(delay_thread.LessThan(1)) break;
        emit eSetResultUI(linkMain.lbDisplay, listProc[LOADIMG], Qt::yellow);
        AddLog("Load image to proces....", Qt::black);

        QString folderPath = mDevice.qstrFolderInput + "/fImage";
        vImageFile = GetAllFileInFolder(folderPath);

        if((int)vImageFile.size() != iTotalImg) {
            proc_Error = LOADIMG;
            AddLog(tr("Not enough image: %1").arg(vImageFile.size()), Qt::red);
            SetStep(LOOP_ERR);
            break;
        }
        for(QString qstrFile : vImageFile) {
            if(qstrFile.contains(ADBcommand[ADB_PULL_TO_PC].respone)) {
                QString qstrpath =  folderPath + "/" + qstrFile;
                qDebug()<< qstrpath;
                if((bCheckStain[FW1]||bCheckWhiteStain[FW1]||bCheckColor[FW1]) && mImread[FW1][IMG_CHECK_STEP1].empty()){
                    mImread[FW1][IMG_CHECK_STEP1] = imread(qstrpath.toStdString(),IMREAD_COLOR);
                    mImSave[FW1][IMG_CHECK_STEP1] = imread(qstrpath.toStdString(),IMREAD_COLOR);
                    continue;
                }
                else if((bCheckFocus[FW1]||bCheckGlare[FW1])){
                    mImread[FW1][IMG_CHECK_STEP2] = imread(qstrpath.toStdString(),IMREAD_COLOR);
                    mImSave[FW1][IMG_CHECK_STEP2] = imread(qstrpath.toStdString(),IMREAD_COLOR);
                    continue;
                }
            }
            /*Issue*/
//            else if(qstrFile.contains("FRONTIMAGE")) {
//                QString qstrpath =  folderPath + "/" + qstrFile;
//                qDebug()<< qstrpath;
//                if((bCheckStain[FB1]||bCheckWhiteStain[FB1]||bCheckColor[FB1]) && mImread[FB1][IMG_CHECK_STEP1].empty()){
//                    mImread[FB1][IMG_CHECK_STEP1] = imread(qstrpath.toStdString(),IMREAD_COLOR);
//                    mImSave[FB1][IMG_CHECK_STEP1] = imread(qstrpath.toStdString(),IMREAD_COLOR);
//                    continue;
//                }
//                else if((bCheckFocus[FB1]||bCheckGlare[FB1])){
//                    mImread[FB1][IMG_CHECK_STEP2] = imread(qstrpath.toStdString(),IMREAD_COLOR);
//                    mImSave[FB1][IMG_CHECK_STEP2] = imread(qstrpath.toStdString(),IMREAD_COLOR);
//                    continue;
//                }
//            }
        }
        delay_thread.StartTimer();
        SetStep(LOOP_PROCESS_DO);
    }
        break;
    case LOOP_PROCESS_DO: {
        emit eSetResultUI(linkMain.lbDisplay,listProc[PROCESS] , Qt::yellow);
        if(mDevice.ipModel < G975){
          ProcessFW1();
        }
        else{
           ProcessFW1();
           ProcessFB1();
        }
//        delay_thread.StartTimer();
        SetStep(LOOP_PROCESS_WAIT);
    }
        break;
    case LOOP_PROCESS_WAIT: {
        if(mDevice.ipModel < G975){
            if(!bResultCam[FW1] )
                ProcessFW1Wait();

            if(bResultCam[FW1]){
                SetStep(LOOP_PROCESS_RESULT);
            }
        }
        else{
            if(!bResultCam[FW1])
                ProcessFW1Wait();
            if(!bResultCam[FB1])
               ProcessFB1Wait();

            if(bResultCam[FW1] && bResultCam[FB1]){
                SetStep(LOOP_PROCESS_RESULT);
            }
        }
    }
        break;
    case LOOP_PROCESS_RESULT: {
        emit eFinishProcess();
        SetStep(LOOP_DOTHING);
    }
        break;
    case LOOP_ERR: {

        emit eDisplayImage(mError, linkMain.lbDisplay);
        AddLog("Error = " + listErrorProc[proc_Error], Qt::red);
        bErrproc = true;

        emit eFinishProcess();
        AddLog("...........Finish process............",Qt::darkRed);
    }
        break;
    }
}
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-End main:=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

void ProcessCam::InitMat() {
    mStart   = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);
    mStop    = mStart.clone();
    mError   = mStart.clone();
    mDontUse = mStart.clone();
    mWait    = mStart.clone();
    mNG      = mStart.clone();
    mOK      = mStart.clone();
    for(int i = FW1; i<=FB1; i++){
        for(int j = IMG_CHECK_STEP1; j <= IMG_CHECK_STEP2; j++){
            this->mImread[i][j].release();
            this->mImSave[i][j].release();
        }
    }

    cv::putText(mStart,   "START",     cv::Point(150, 250), CV_FONT_HERSHEY_SIMPLEX, 3.5, cv::Scalar(0, 255, 0), 4);
    cv::putText(mStop,    "STOP",      cv::Point(180, 250), CV_FONT_HERSHEY_SIMPLEX, 3.5, cv::Scalar(0, 0, 255), 4);
    cv::putText(mError,   "ERROR",     cv::Point(150, 250), CV_FONT_HERSHEY_SIMPLEX, 3.5, cv::Scalar(0, 0, 255), 4);
    cv::putText(mDontUse, "DON'T USE", cv::Point(30, 250),  CV_FONT_HERSHEY_SIMPLEX, 3.5, cv_orange, 4);
    cv::putText(mWait,    "WAIT",      cv::Point(180, 250), CV_FONT_HERSHEY_SIMPLEX, 3.5, cv::Scalar(0, 255, 0), 4);
    cv::putText(mNG,      "NG",        cv::Point(180, 250), CV_FONT_HERSHEY_SIMPLEX, 3.5, cv::Scalar(0, 255, 0), 9);
    cv::putText(mOK,      "OK",        cv::Point(180, 250), CV_FONT_HERSHEY_SIMPLEX, 3.5, cv::Scalar(0, 0, 255), 9);
}

void ProcessCam::ResetStatus() {
    /*reset string error*/
    for(int i = 0; i < NUM_CAM; i++){
        strErr[i].clear();
    }
    /*reset vision_error*/
    for(int i = 0; i < NUM_CAM; i++){
        vStain[i][TYPE_SIZE_SMALL].clear();
        vStain[i][TYPE_SIZE_LARGE].clear();
        vWhiteStain[i][TYPE_SIZE_SMALL].clear();
        vWhiteStain[i][TYPE_SIZE_LARGE].clear();
        vGlare[i].clear();
        vDarkpot[i].clear();
        bWrongColor[i] = true;
        vision_Error[i] = no_Err;
    }
    bErrproc  = false;

}

void ProcessCam::ResetTbwErr()
{
    for(int i = FW1; i <= iTotalCam; i++){
        if(i == FW1){
            if(!bCheckIris)
                emit eSetReultTbw(RES_IRIS_FW1,"Null", Qt::gray);
            else
                emit eSetReultTbw(RES_IRIS_FW1,"", Qt::gray);

            if(!bCheckStain[i])
                emit eSetReultTbw(RES_STAIN_FW1, "Null", Qt::gray);
            else
                emit eSetReultTbw(RES_STAIN_FW1,"", Qt::gray);

            if(!bCheckWhiteStain[i])
                emit eSetReultTbw(RES_WHITESTAIN_FW1,"Null", Qt::gray);
            else
                emit eSetReultTbw(RES_WHITESTAIN_FW1, "", Qt::gray);

            if(!bCheckGlare[i])
                emit eSetReultTbw(RES_GLARE_FW1, "Null", Qt::gray);
            else
                emit eSetReultTbw(RES_GLARE_FW1, "", Qt::gray);

            if(!bCheckFocus[i])
                emit eSetReultTbw(RES_FOCUS_FW1, "Null", Qt::gray);
            else
                emit eSetReultTbw(RES_FOCUS_FW1, "", Qt::gray);

            if(!bCheckDarkSport[i])
                emit eSetReultTbw(RES_DARKSPORT_FW1, "Null", Qt::gray);
            else
                emit eSetReultTbw(RES_DARKSPORT_FW1, "", Qt::gray);

            if(!bCheckColor[i])
                emit eSetReultTbw(RES_COLOR_FW1, "Null", Qt::gray);
            else
                emit eSetReultTbw(RES_COLOR_FW1, "", Qt::gray);
        }
        else{
            if(!bCheckIris)
                emit eSetReultTbw(RES_IRIS_FB1, "Null", Qt::gray);
            else
                emit eSetReultTbw(RES_IRIS_FB1, "", Qt::gray);

            if(!bCheckStain[i])
                emit eSetReultTbw(RES_STAIN_FB1, "Null", Qt::gray);
            else
                emit eSetReultTbw(RES_STAIN_FB1, "", Qt::gray);

            if(!bCheckWhiteStain[i])
                emit eSetReultTbw(RES_WHITESTAIN_FB1, "Null", Qt::gray);
            else
                emit eSetReultTbw(RES_WHITESTAIN_FB1, "", Qt::gray);

            if(!bCheckGlare[i])
                emit eSetReultTbw(RES_GLARE_FB1, "Null", Qt::gray);
            else
                emit eSetReultTbw(RES_GLARE_FB1, "", Qt::gray);

            if(!bCheckFocus[i])
                emit eSetReultTbw(RES_FOCUS_FB1, "Null", Qt::gray);
            else
                emit eSetReultTbw(RES_FOCUS_FB1, "", Qt::gray);

            if(!bCheckDarkSport[i])
                emit eSetReultTbw(RES_DARKSPORT_FB1, "Null", Qt::gray);
            else
                emit eSetReultTbw(RES_DARKSPORT_FB1, "", Qt::gray);

            if(!bCheckColor[i])
                emit eSetReultTbw(RES_COLOR_FB1, "Null", Qt::gray);
            else
                emit eSetReultTbw(RES_COLOR_FB1, "", Qt::gray);
        }
    }

    if(mDevice.ipModel < G975){
            emit eSetReultTbw(RES_IRIS_FB1,"Null", Qt::gray);
            emit eSetReultTbw(RES_STAIN_FB1,"Null", Qt::gray);
            emit eSetReultTbw(RES_WHITESTAIN_FB1,"Null", Qt::gray);
            emit eSetReultTbw(RES_GLARE_FB1,"Null", Qt::gray);
            emit eSetReultTbw(RES_FOCUS_FB1,"Null", Qt::gray);
            emit eSetReultTbw(RES_DARKSPORT_FB1,"Null", Qt::gray);
            emit eSetReultTbw(RES_COLOR_FB1,"Null", Qt::gray);
    }

}

void ProcessCam::InitUI() {
    int widthLog = linkMain.tbLog->geometry().width();
    linkMain.tbLog->setColumnCount(2);
    linkMain.tbLog->setColumnWidth(0,widthLog/4);
    linkMain.tbLog->setColumnWidth(1,3*widthLog/4);

    int widthError = linkMain.tbError->geometry().width();
    linkMain.tbError->setColumnCount(2);
    linkMain.tbError->setColumnWidth(0,widthError/4);
    linkMain.tbError->setColumnWidth(1,3*widthError/4);

    QStringList strList;
    strList<<"Time"<<"Log Data";
    linkMain.tbLog->setHorizontalHeaderLabels(strList);
    linkMain.tbLog->verticalHeader()->setVisible(false);    // ẩn số thự tự dòng
    //  emit eSetResultUI(linkMain.lbDisplay, "WAIT", Qt::yellow);
}

void ProcessCam::SendCom(QSerialPort *qspCom, QString data) {
    QByteArray cmd;
    if(qspCom->isOpen()) {
        qDebug() << qspCom->portName();
        data += "\r\n";
        cmd = data.toLocal8Bit();
        qDebug()<<"send com ="<<cmd;
        qspCom->write(cmd.data());
    }
}

void ProcessCam::SendADB(QString strIn) {
    processADB->start(strIn.toLocal8Bit());
    processADB->waitForFinished(-1);
    qDebug()<< strIn;
}

void ProcessCam::SetResultUI(QLabel *label, QString str, int iColor) {
    QString color = "";
    switch (iColor) {
    case Qt::green:
        color = "green";

        break;
    case Qt::red:
        color = "red";

        break;
    case Qt::yellow:
        color = "yellow";

        break;
    default:
        break;
    }
    label->clear();
    QString styleOK = tr("QLabel{" "border: 2px solid black;" "border-radius: 5px;" "background-color:%1" "}").arg(color) ;
    label->setStyleSheet(styleOK);
    if(str != "FAIL" && iColor == Qt::red)
        str  = "Err " + str;
    label->setText(str);
}

/*Fuction Check Err - FW1*/
void ProcessCam::visionSStainFW1(int Img) {
    vStain[FW1][TYPE_SIZE_SMALL] = myVision.CheckStain(mImread[FW1][Img], mGenenal, FW1, TYPE_SIZE_SMALL).vRes;

    if(!vStain[FW1][TYPE_SIZE_SMALL].empty()){
        vision_Error[FW1] += err_St;
        emit eSetReultTbw(RES_STAIN_FW1, "NG", Qt::red);
        AddLog(tr("%1 NG SStain = %2").arg(listCam[FW1]).arg(vStain[FW1][TYPE_SIZE_SMALL].size()), Qt::red);
    }
    else{
        AddLog(tr("%1 OK SStain").arg(listCam[FW1]), Qt::black);
    }
    pSStain[FW1]->StopThread();
}

void ProcessCam::visionLStainFW1(int Img) {
    vStain[FW1][TYPE_SIZE_LARGE] = myVision.CheckStain(mImread[FW1][Img], mGenenal, FW1, TYPE_SIZE_LARGE).vRes;

    if(!vStain[FW1][TYPE_SIZE_LARGE].empty()){
        vision_Error[FW1] += err_St;
        emit eSetReultTbw(RES_STAIN_FW1, "NG", Qt::red);
        AddLog(tr("%1 NG LStain = %2").arg(listCam[FW1]).arg(vStain[FW1][TYPE_SIZE_LARGE].size()), Qt::red);
    }
    else{
        AddLog(tr("%1 OK LStain").arg(listCam[FW1]), Qt::black);
    }
    pLStain[FW1]->StopThread();
}

void ProcessCam::visionWhiteSStainFW1(int Img) {
    vWhiteStain[FW1][TYPE_SIZE_SMALL] = myVision.CheckWhiteStain(mImread[FW1][Img], mGenenal, FW1, TYPE_SIZE_SMALL).vRes;

    if(!vWhiteStain[FW1][TYPE_SIZE_SMALL].empty()){
        vision_Error[FW1] += err_WSt;
        emit eSetReultTbw(RES_WHITESTAIN_FW1, "NG", Qt::red);
        AddLog(tr("%1 NG WhiteSStain = %2").arg(listCam[FW1]).arg(vWhiteStain[FW1][TYPE_SIZE_SMALL].size()), Qt::red);
    }
    else{
        AddLog(tr("%1 OK WhiteSStain").arg(listCam[FW1]), Qt::black);
    }
    pWhiteSStain[FW1]->StopThread();
}

void ProcessCam::visionWhiteLStainFW1(int Img) {
    vWhiteStain[FW1][TYPE_SIZE_LARGE] = myVision.CheckWhiteStain(mImread[FW1][Img], mGenenal, FW1, TYPE_SIZE_LARGE).vRes;

    if(!vWhiteStain[FW1][TYPE_SIZE_LARGE].empty()){
        vision_Error[FW1] += err_WSt;
        emit eSetReultTbw(RES_WHITESTAIN_FW1, "NG", Qt::red);
        AddLog(tr("%1 NG WhiteLStain = %2").arg(listCam[FW1]).arg(vWhiteStain[FW1][TYPE_SIZE_LARGE].size()), Qt::red);
    }
    else{

        AddLog(tr("%1 OK WhiteLStain").arg(listCam[FW1]), Qt::black);
    }
    pWhiteLStain[FW1]->StopThread();
}

void ProcessCam::visionGlareFW1(int Img) {
    vGlare[FW1] = myVision.CheckGlare(mImread[FW1][Img], mGenenal, FW1).vRes;

    if(!vGlare[FW1].empty()){
        vision_Error[FW1] += err_WG;
        emit eSetReultTbw(RES_GLARE_FW1, "NG", Qt::red);
        AddLog(tr("%1 NG Glare").arg(listCam[FW1]), Qt::red);
    }
    else{
        AddLog(tr("%1 OK Glare").arg(listCam[FW1]), Qt::black);
    }
    pGlare[FW1]->StopThread();

}

void ProcessCam::visionFocusFW1(int Img) {
    _sResVision sRes;
  sRes = myVision.CheckFocus(mImread[FW1][Img], mGenenal, FW1);
    vFocus[FW1] = sRes.vRes;
    int iSizeRoi    = (int)vFocus[FW1].size();
    if(!vFocus[FW1].empty()){
        vision_Error[FW1] += err_Fs;
        emit eSetReultTbw(RES_FOCUS_FW1, "NG", Qt::red);
        for(int i = 0; i < iSizeRoi; i++)
            AddLog(tr("%1 NG Focus Roi%3-std: %2").arg(listCam[FW1]).arg(sRes.vStd[i]).arg(i+1), Qt::red);
    }
    else{
        for(int i = 0; i < iSizeRoi; i++)
            AddLog(tr("%1 OK Focus Roi%3-std: %2").arg(listCam[FW1]).arg(sRes.vStd[i]).arg(i+1), Qt::black);
    }
    pFocus[FW1]->StopThread();
}

void ProcessCam::visionDarkpotFW1(int Img) {
    vDarkpot[FW1] = myVision.CheckDarkspot(mImread[FW1][Img], mGenenal,FW1).vRes;
    if(!vDarkpot[FW1].empty()){
        vision_Error[FW1] += err_Dp;
        emit eSetReultTbw(RES_DARKSPORT_FW1, "NG", Qt::red);
        AddLog(tr("%1 NG Darkpot = %2").arg(listCam[FW1]).arg(vDarkpot[FW1].size()), Qt::red);
    }
    else{
        AddLog(tr("%1 OK Darkpot").arg(listCam[FW1]), Qt::black);
    }
    pDarkspot[FW1]->StopThread();
}

void ProcessCam::visionColorFW1(int Img) {
    bWrongColor[FW1] = myVision.CheckColor(mImread[FW1][Img], mGenenal, FW1).bRes;
    if(!bWrongColor[FW1]){
        vision_Error[FW1] += err_WC;
        emit eSetReultTbw(RES_COLOR_FW1, "NG", Qt::red);
        AddLog(tr("%1 NG WrongColor").arg(listCam[FW1]), Qt::red);
    }
    else{
        AddLog(tr("%1 OK WrongColor").arg(listCam[FW1]), Qt::black);
    }
    pWrongColor[FW1]->StopThread();

}

void ProcessCam::ProcessFW1() {
    if(bCheckStain[FW1]){
        pSStain[FW1]->iIMG = IMG_CHECK_STEP1;
        pLStain[FW1]->iIMG = IMG_CHECK_STEP1;
        pSStain[FW1]->StartThread();
        pLStain[FW1]->StartThread();
    }
    else{
        pSStain[FW1]->StopThread();
        pLStain[FW1]->StopThread();
        vStain[FW1][TYPE_SIZE_SMALL].clear();
        vStain[FW1][TYPE_SIZE_LARGE].clear();
    }

    if(bCheckWhiteStain[FW1]){
        pWhiteSStain[FW1]->iIMG = IMG_CHECK_STEP1;
        pWhiteLStain[FW1]->iIMG = IMG_CHECK_STEP1;
        pWhiteSStain[FW1]->StartThread();
        pWhiteLStain[FW1]->StartThread();
    }
    else{
        pWhiteSStain[FW1]->StopThread();
        pWhiteLStain[FW1]->StopThread();
        vWhiteStain[FW1][TYPE_SIZE_SMALL].clear();
        vWhiteStain[FW1][TYPE_SIZE_LARGE].clear();
    }

    if(bCheckGlare[FW1]){
        pGlare[FW1]->iIMG = IMG_CHECK_STEP2;
        pGlare[FW1]->StartThread();
    }
    else{
        pGlare[FW1]->StopThread();
        vGlare[FW1].clear();
    }

    if(bCheckDarkSport[FW1]){
        pDarkspot[FW1]->iIMG = IMG_CHECK_STEP1;
        pDarkspot[FW1]->StartThread();
    }
    else{
        pDarkspot[FW1]->StopThread();
        vDarkpot[FW1].clear();
    }

    if(bCheckColor[FW1]){
        pWrongColor[FW1]->iIMG = IMG_CHECK_STEP1;
        pWrongColor[FW1]->StartThread();
    }
    else{
        pWrongColor[FW1]->StopThread();
        bWrongColor[FW1] = true;
    }

    if(bCheckFocus[FW1]){
        pFocus[FW1]->iIMG = IMG_CHECK_STEP2;
        pFocus[FW1]->StartThread();
    }
    else{
        pFocus[FW1]->StopThread();
        vFocus[FW1].clear();
    }
}

void ProcessCam::ProcessFW1Wait() {
    if(pSStain[FW1]->m_bRun || pLStain[FW1]->m_bRun
            || pWhiteLStain[FW1]->m_bRun || pWhiteSStain[FW1]->m_bRun
            || pFocus[FW1]->m_bRun || pGlare[FW1]->m_bRun
            || pWrongColor[FW1]->m_bRun || pDarkspot[FW1]->m_bRun) {
        return;
    }
    else {
        AddLog(tr("Done cam %1").arg(FW1+1), Qt::black);
        if(vStain[FW1][TYPE_SIZE_SMALL].empty() && vStain[FW1][TYPE_SIZE_LARGE].empty()
                && vWhiteStain[FW1][TYPE_SIZE_SMALL].empty()  && vWhiteStain[FW1][TYPE_SIZE_LARGE].empty()
                && vGlare[FW1].empty() && vDarkpot[FW1].empty() && bWrongColor[FW1] && vFocus[FW1].empty()){
            qDebug() << tr("cam %1 ok").arg(FW1+1);
            emit eSetReultTbw(RES_STAIN_FW1,      "OK", Qt::green);
            emit eSetReultTbw(RES_WHITESTAIN_FW1, "OK", Qt::green);
            emit eSetReultTbw(RES_GLARE_FW1,      "OK", Qt::green);
            emit eSetReultTbw(RES_FOCUS_FW1,      "OK", Qt::green);
            emit eSetReultTbw(RES_COLOR_FW1,      "OK", Qt::green);
            emit eSetReultTbw(RES_DARKSPORT_FW1,  "OK", Qt::green);
            bCheckCam[FW1] = true;
        }
        else{

            if(vStain[FW1][TYPE_SIZE_SMALL].empty() && vStain[FW1][TYPE_SIZE_LARGE].empty() && bCheckStain[FW1]){
                bCheckResultStain[FW1] = true;
                emit eSetReultTbw(RES_STAIN_FW1, "OK", Qt::green);
            }
            else
                bCheckResultStain[FW1] = false;

            if(vWhiteStain[FW1][TYPE_SIZE_SMALL].empty()  && vWhiteStain[FW1][TYPE_SIZE_LARGE].empty() && bCheckWhiteStain[FW1]){
                bCheckResultWhiteStain[FW1] = true;
                emit eSetReultTbw(RES_WHITESTAIN_FW1, "OK", Qt::green);
            }
            else
                bCheckResultWhiteStain[FW1] = false;

            if(vGlare[FW1].empty() && bCheckGlare[FW1]){
                bCheckResultGlare[FW1] = true;
                emit eSetReultTbw(RES_GLARE_FW1,      "OK", Qt::green);
            }
            else
                bCheckResultGlare[FW1] = false;

            if( vDarkpot[FW1].empty() && bCheckDarkSport[FW1]){
                bCheckResultDarkSport[FW1] = true;
                emit eSetReultTbw(RES_DARKSPORT_FW1,  "OK", Qt::green);

            }
            else
                bCheckResultDarkSport[FW1] = false;

            if(bWrongColor[FW1] && bCheckColor[FW1]){
                bCheckResultColor[FW1] = true;
                emit eSetReultTbw(RES_COLOR_FW1,      "OK", Qt::green);
            }
            else
                bCheckResultColor[FW1] = false;

            if(vFocus[FW1].empty() && bCheckFocus[FW1]){
                bCheckResultFocus[FW1] = true;
                emit eSetReultTbw(RES_FOCUS_FW1,      "OK", Qt::green);
            }
            else
                bCheckResultFocus[FW1] = false;
            bCheckCam[FW1] = false;

            bool b1, b2 = false;

            for(Rect r : vStain[FW1][TYPE_SIZE_SMALL]){
                cv::rectangle(mImread[FW1][IMG_CHECK_STEP1], r, cv_aqua,  mGenenal.ipPaintThickness);
                if(!b1)
                    b1 = true;
            }


            if(!b1){
                for(Rect r : vStain[FW1][TYPE_SIZE_LARGE]){
                    cv::rectangle(mImread[FW1][IMG_CHECK_STEP1], r, cv_aqua,  mGenenal.ipPaintThickness);
                }
            }



            for(Rect r : vWhiteStain[FW1][TYPE_SIZE_SMALL]){
                cv::rectangle(mImread[FW1][IMG_CHECK_STEP1], r, cv_red,    mGenenal.ipPaintThickness);
            }


            for(Rect r : vWhiteStain[FW1][TYPE_SIZE_LARGE]){
                cv::rectangle(mImread[FW1][IMG_CHECK_STEP1], r, cv_red,    mGenenal.ipPaintThickness);
            }


            for(Rect r : vDarkpot[FW1]){
                cv::rectangle(mImread[FW1][IMG_CHECK_STEP1], r, cv_purple, mGenenal.ipPaintThickness);
            }


            for(Rect r : vGlare[FW1]){
                cv::rectangle(mImread[FW1][IMG_CHECK_STEP2], r, cv_orange, mGenenal.ipPaintThickness);
            }


            for(Rect r : vFocus[FW1]){
                cv::rectangle(mImread[FW1][IMG_CHECK_STEP2], r, cv_blue,   mGenenal.ipPaintThickness);
            }
        }
    }
    if(bSaveImg[FW1]){
        QString time = QDateTime::currentDateTime().toString("yy_MM_dd_hh_mm_ss");
        if(!mImSave[FW1][IMG_CHECK_STEP1].empty())
            saveResultImg(time, tr("%1_SDG").arg(FW1+1), mImSave[FW1][IMG_CHECK_STEP1]);
        if(!mImSave[FW1][IMG_CHECK_STEP2].empty())
            saveResultImg(time, tr("%1_GrF").arg(FW1+1), mImSave[FW1][IMG_CHECK_STEP2]);
    }

    bResultCam[FW1] = true;
}

void ProcessCam::visionSStainFB1(int Img) {
    vStain[FB1][TYPE_SIZE_SMALL] = myVision.CheckStain(mImread[FB1][Img], mGenenal, FB1, TYPE_SIZE_SMALL).vRes;

    if(!vStain[FB1][TYPE_SIZE_SMALL].empty()){
        vision_Error[FB1] += err_St;
        emit eSetReultTbw(RES_STAIN_FB1, "NG", Qt::red);
        AddLog(tr("%1 NG SStain = %2").arg(listCam[FB1]).arg(vStain[FB1][TYPE_SIZE_SMALL].size()), Qt::red);
    }
    else{
        AddLog(tr("%1 OK SStain").arg(listCam[FB1]), Qt::black);
    }
    pSStain[FB1]->StopThread();
}

void ProcessCam::visionLStainFB1(int Img) {
    vStain[FB1][TYPE_SIZE_LARGE] = myVision.CheckStain(mImread[FB1][Img], mGenenal, FB1, TYPE_SIZE_LARGE).vRes;

    if(!vStain[FB1][TYPE_SIZE_LARGE].empty()){
        vision_Error[FB1] += err_St;
        emit eSetReultTbw(RES_STAIN_FB1,      "NG", Qt::red);
        AddLog(tr("%1 NG LStain = %2").arg(listCam[FB1]).arg(vStain[FB1][TYPE_SIZE_LARGE].size()), Qt::red);
    }
    else{
        AddLog(tr("%1 OK LStain").arg(listCam[FB1]), Qt::black);
    }
    pLStain[FB1]->StopThread();
}

void ProcessCam::visionWhiteSStainFB1(int Img) {
    vWhiteStain[FB1][TYPE_SIZE_SMALL] = myVision.CheckWhiteStain(mImread[FB1][Img], mGenenal, FB1, TYPE_SIZE_SMALL).vRes;

    if(!vWhiteStain[FB1][TYPE_SIZE_SMALL].empty()){
        vision_Error[FB1] += err_WSt;
        emit eSetReultTbw(RES_WHITESTAIN_FB1,      "NG", Qt::red);
        AddLog(tr("%1 NG WhiteSStain = %2").arg(listCam[FB1]).arg(vWhiteStain[FB1][TYPE_SIZE_SMALL].size()), Qt::red);
    }
    else{
        AddLog(tr("%1 OK WhiteSStain").arg(listCam[FB1]), Qt::black);
    }
    pWhiteSStain[FB1]->StopThread();
}

void ProcessCam::visionWhiteLStainFB1(int Img) {
    vWhiteStain[FB1][TYPE_SIZE_LARGE] = myVision.CheckWhiteStain(mImread[FB1][Img], mGenenal, FB1, TYPE_SIZE_LARGE).vRes;

    if(!vWhiteStain[FB1][TYPE_SIZE_LARGE].empty()){
        vision_Error[FB1] += err_WSt;
        emit eSetReultTbw(RES_WHITESTAIN_FB1,      "NG", Qt::red);
        AddLog(tr("%1 NG WhiteLStain = %2").arg(listCam[FB1]).arg(vWhiteStain[FB1][TYPE_SIZE_LARGE].size()), Qt::red);
    }
    else{
        AddLog(tr("%1 OK WhiteLStain").arg(listCam[FB1]), Qt::black);
    }
    pWhiteSStain[FB1]->StopThread();
}

void ProcessCam::visionGlareFB1(int Img) {
    vGlare[FB1] = myVision.CheckGlare(mImread[FB1][Img], mGenenal, FB1).vRes;

    if(!vGlare[FB1].empty()){
        vision_Error[FB1] += err_WG;
        emit eSetReultTbw(RES_GLARE_FB1,      "NG", Qt::red);
        AddLog(tr("%1 NG Glare").arg(listCam[FB1]), Qt::red);
    }
    else{
        AddLog(tr("%1 OK Glare").arg(listCam[FB1]), Qt::black);
    }
    pGlare[FB1]->StopThread();

}

void ProcessCam::visionFocusFB1(int Img) {
    _sResVision sRes;
    sRes = myVision.CheckFocus(mImread[FB1][Img], mGenenal, FB1);
    vFocus[FB1] = sRes.vRes;
    int iSizeRoi    = (int)vFocus[FB1].size();
    if(!vFocus[FB1].empty()){
        vision_Error[FB1] += err_Fs;
        emit eSetReultTbw(RES_FOCUS_FB1,      "NG", Qt::red);
        for(int i = 0; i < iSizeRoi; i++)
            AddLog(tr("%1 NG Focus Roi%3-std: %2").arg(listCam[FB1]).arg(sRes.vStd[i]).arg(i+1), Qt::red);
    }
    else{
        for(int i = 0; i < iSizeRoi; i++)
            AddLog(tr("%1 OK Focus Roi%3-std: %2").arg(listCam[FB1]).arg(sRes.vStd[i]).arg(i+1), Qt::black);
    }

    pFocus[FB1]->StopThread();
}

void ProcessCam::visionDarkpotFB1(int Img) {
    vDarkpot[FB1] = myVision.CheckDarkspot(mImread[FB1][Img], mGenenal,FB1).vRes;
    if(!vDarkpot[FB1].empty()){
        vision_Error[FB1] += err_Dp;
        emit eSetReultTbw(RES_DARKSPORT_FB1,"NG", Qt::red);
        AddLog(tr("%1 NG Darkpot = %2").arg(listCam[FB1]).arg(vDarkpot[FB1].size()), Qt::red);
    }
    else{
        AddLog(tr("%1 OK Darkpot").arg(listCam[FB1]), Qt::black);
    }

    pDarkspot[FB1]->StopThread();
}

void ProcessCam::visionColorFB1(int Img) {
    bWrongColor[FB1] = myVision.CheckColor(mImread[FB1][Img], mGenenal, FB1).bRes;

    if(!bWrongColor[FB1]){
        vision_Error[FB1] += err_WC;
        emit eSetReultTbw(RES_COLOR_FB1,"NG", Qt::red);
        AddLog(tr("%1 NG WrongColor").arg(listCam[FB1]), Qt::red);
    }
    else{
        AddLog(tr("%1 OK WrongColor").arg(listCam[FB1]), Qt::black);
    }

    pWrongColor[FB1]->StopThread();
}

void ProcessCam::ProcessFB1() {
    if(bCheckStain[FB1]){
        pSStain[FB1]->iIMG = IMG_CHECK_STEP1;
        pLStain[FB1]->iIMG = IMG_CHECK_STEP1;
        pSStain[FB1]->StartThread();
        pLStain[FB1]->StartThread();
    }
    else{
        pSStain[FB1]->StopThread();
        pLStain[FB1]->StopThread();

        vStain[FB1][TYPE_SIZE_SMALL].clear();
        vStain[FB1][TYPE_SIZE_LARGE].clear();
    }

    if(bCheckWhiteStain[FB1]){
        pWhiteSStain[FB1]->iIMG = IMG_CHECK_STEP1;
        pWhiteLStain[FB1]->iIMG = IMG_CHECK_STEP1;

        pWhiteSStain[FB1]->StartThread();
        pWhiteLStain[FB1]->StartThread();
    }
    else{
        pWhiteSStain[FB1]->StopThread();
        pWhiteLStain[FB1]->StopThread();

        vWhiteStain[FB1][TYPE_SIZE_SMALL].clear();
        vWhiteStain[FB1][TYPE_SIZE_LARGE].clear();
    }

    if(bCheckGlare[FB1]){
        pGlare[FB1]->iIMG = IMG_CHECK_STEP2;
        pGlare[FB1]->StartThread();
    }
    else{
        pGlare[FB1]->StopThread();
        vGlare[FB1].clear();
    }

    if(bCheckDarkSport[FB1]){
        pDarkspot[FB1]->iIMG = IMG_CHECK_STEP1;
        pDarkspot[FB1]->StartThread();
    }
    else{
        pDarkspot[FB1]->StopThread();
        vDarkpot[FB1].clear();
    }

    if(bCheckColor[FB1]){
        pWrongColor[FB1]->iIMG = IMG_CHECK_STEP1;
        pWrongColor[FB1]->StartThread();
    }
    else{
        pWrongColor[FB1]->StopThread();
        bWrongColor[FB1] = true;
    }

    if(bCheckFocus[FB1]){
        pFocus[FB1]->iIMG = IMG_CHECK_STEP2;
        pFocus[FB1]->StartThread();
    }
    else{
        pFocus[FB1]->StopThread();
        vFocus[FB1].clear();
    }
}

void ProcessCam::ProcessFB1Wait() {
    if(pSStain[FB1]->m_bRun || pLStain[FB1]->m_bRun
            || pWhiteLStain[FB1]->m_bRun || pWhiteSStain[FB1]->m_bRun
            || pFocus[FB1]->m_bRun || pGlare[FB1]->m_bRun
            || pWrongColor[FB1]->m_bRun || pDarkspot[FB1]->m_bRun) {
        return;
    }
    else {
        AddLog(tr("Done cam %1").arg(FB1+1), Qt::black);
        if(vStain[FB1][TYPE_SIZE_SMALL].empty() && vStain[FB1][TYPE_SIZE_LARGE].empty()
                && vWhiteStain[FB1][TYPE_SIZE_SMALL].empty()  && vWhiteStain[FB1][TYPE_SIZE_LARGE].empty()
                && vGlare[FB1].empty() && vDarkpot[FB1].empty() && bWrongColor[FB1] && vFocus[FB1].empty()){
            qDebug() << tr("cam %1 ok").arg(FB1+1);
            emit eSetReultTbw(RES_STAIN_FB1,      "OK", Qt::green);
            emit eSetReultTbw(RES_WHITESTAIN_FB1, "OK", Qt::green);
            emit eSetReultTbw(RES_GLARE_FB1,      "OK", Qt::green);
            emit eSetReultTbw(RES_FOCUS_FB1,      "OK", Qt::green);
            emit eSetReultTbw(RES_COLOR_FB1,      "OK", Qt::green);
            emit eSetReultTbw(RES_DARKSPORT_FB1,  "OK", Qt::green);
            bCheckCam[FB1] = true;
        }
        else{
            if(vStain[FB1][TYPE_SIZE_SMALL].empty() && vStain[FB1][TYPE_SIZE_LARGE].empty() && bCheckStain[FB1]){
                bCheckResultStain[FB1] = true;
                emit eSetReultTbw(RES_STAIN_FB1,      "OK", Qt::green);
            }
            else
                bCheckResultStain[FB1] = false;

            if(vWhiteStain[FB1][TYPE_SIZE_SMALL].empty()  && vWhiteStain[FB1][TYPE_SIZE_LARGE].empty() && bCheckWhiteStain[FB1]){
                bCheckResultWhiteStain[FB1] = true;
                emit eSetReultTbw(RES_WHITESTAIN_FB1, "OK", Qt::green);
            }
            else
                bCheckResultWhiteStain[FB1] = false;

            if(vGlare[FB1].empty() && bCheckGlare[FB1]){
                bCheckResultGlare[FB1] = true;
                emit eSetReultTbw(RES_GLARE_FB1,      "OK", Qt::green);
            }
            else
                bCheckResultGlare[FB1] = false;

            if( vDarkpot[FB1].empty() && bCheckDarkSport[FB1]){
                bCheckResultDarkSport[FB1] = true;
                emit eSetReultTbw(RES_DARKSPORT_FB1,  "OK", Qt::green);

            }
            else
                bCheckResultDarkSport[FB1] = false;

            if(bWrongColor[FB1] && bCheckColor[FB1]){
                bCheckResultColor[FB1] = true;
                emit eSetReultTbw(RES_COLOR_FB1,      "OK", Qt::green);

            }
            else
                bCheckResultColor[FB1] = false;

            if(vFocus[FB1].empty() && bCheckFocus[FB1]){
                bCheckResultFocus[FB1] = true;
                emit eSetReultTbw(RES_FOCUS_FB1,      "OK", Qt::green);
            }
            else
                bCheckResultFocus[FB1] = false;


            bCheckCam[FB1] = false;

            for(Rect r : vStain[FB1][TYPE_SIZE_SMALL])
                cv::rectangle(mImread[FB1][IMG_CHECK_STEP1], r, cv_aqua,  mGenenal.ipPaintThickness);

            for(Rect r : vStain[FB1][TYPE_SIZE_LARGE])
                cv::rectangle(mImread[FB1][IMG_CHECK_STEP1], r, cv_aqua,  mGenenal.ipPaintThickness);

            for(Rect r : vWhiteStain[FB1][TYPE_SIZE_SMALL])
                cv::rectangle(mImread[FB1][IMG_CHECK_STEP1], r, cv_red,    mGenenal.ipPaintThickness);

            for(Rect r : vWhiteStain[FB1][TYPE_SIZE_LARGE])
                cv::rectangle(mImread[FB1][IMG_CHECK_STEP1], r, cv_red,    mGenenal.ipPaintThickness);

            for(Rect r : vGlare[FB1])
                cv::rectangle(mImread[FB1][IMG_CHECK_STEP2], r, cv_orange, mGenenal.ipPaintThickness);

            for(Rect r : vDarkpot[FB1])
                cv::rectangle(mImread[FB1][IMG_CHECK_STEP1], r, cv_purple, mGenenal.ipPaintThickness);

            for(Rect r : vFocus[FB1])
                cv::rectangle(mImread[FB1][IMG_CHECK_STEP2], r, cv_blue,   mGenenal.ipPaintThickness);
        }
    }

    if(bSaveImg[FB1]){
        QString time = QDateTime::currentDateTime().toString("yy_MM_dd_hh_mm_ss");
        if(!mImSave[FB1][IMG_CHECK_STEP1].empty())
            saveResultImg(time, tr("%1_SDG").arg(FB1+1), mImSave[FB1][IMG_CHECK_STEP1]);
        if(!mImSave[FB1][IMG_CHECK_STEP2].empty())
            saveResultImg(time, tr("%1_GrF").arg(FB1+1), mImSave[FB1][IMG_CHECK_STEP2]);
    }
    bResultCam[FB1] = true;
}

void ProcessCam::FinishProcess() {
    emit emitThreadIO(Output1_OFF);
    msleep(50);
    emit emitThreadIO(Output2_OFF);

    QString strID ="";
    QString vision_Response = "";
    fCapCount = 0;
    if(!bErrproc){
        bool bSocketOK = true;
        for(int i = FW1; i< NUM_CAM; i++) {
            if(vision_Error[i] != no_Err) {
                bSocketOK = false;
                break;
            }
        }

        if(bSocketOK) {
            strID = tr("\tSocket: %2\tID Module: %1\tResult: Pass").arg(mGenenal.Device.qstrID).arg(iSide+1);
            vision_Response = tr("OK_%1_%2").arg(vision_Error[FW1]).arg(vision_Error[FB1]);
            AddLog(vision_Response, Qt::black);
            emit eSetResultUI(linkMain.lbDisplay, "PASS", Qt::green);
        }
        else{
            strID = tr("\tSocket: %1\tID: %2\tResult: Fail  Cam FW1: %3   Cam FB1: %4").arg(iSide+1)
                    .arg(mGenenal.Device.qstrID).arg(strErr[FW1]).arg(strErr[FB1]);
            vision_Response = tr("NG_%1_%2").arg(iSide).arg(vision_Error[FW1]).arg(vision_Error[FB1]);
            AddLog(vision_Response, Qt::red);
            if(!bShowImg[FW1] && !bShowImg [FB1]){
                emit eSetResultUI(linkMain.lbDisplay, "FAIL", Qt::red);
            }
            else{
                if((!bCheckResultStain[FW1] || !bCheckResultWhiteStain[FW1] || !bCheckResultDarkSport[FW1] || !bCheckResultColor[FW1]) && !mImread[FW1][IMG_CHECK_STEP1].empty())
                    emit eDisplayImage(mImread[FW1][IMG_CHECK_STEP1], linkMain.lbDisplay);

                else if((!bCheckResultGlare[FW1] || !bCheckResultFocus[FW1]) && !mImread[FW1][IMG_CHECK_STEP2].empty())
                    emit eDisplayImage(mImread[FW1][IMG_CHECK_STEP2], linkMain.lbDisplay);

                else if((!bCheckResultStain[FB1] || !bCheckResultWhiteStain[FB1] || !bCheckResultDarkSport[FB1] || !bCheckResultColor[FB1]) && !mImread[FB1][IMG_CHECK_STEP1].empty())
                    emit eDisplayImage(mImread[FB1][IMG_CHECK_STEP1], linkMain.lbDisplay);

                else if((!bCheckResultGlare[FB1] || !bCheckResultFocus[FB1]) && !mImread[FB1][IMG_CHECK_STEP2].empty())
                    emit eDisplayImage(mImread[FB1][IMG_CHECK_STEP2], linkMain.lbDisplay);
            }

        }
        WriteLogFileID(strID);
    }
    else{
        vision_Response = tr("%1_ERR_%2").arg(iSide).arg(proc_Error);
         emit eSetResultUI(linkMain.lbDisplay, listErrorProc[proc_Error], Qt::red);
    }

    for(int i = FW1; i <= iTotalCam; i++){
        bResultCam[i] = false;
    }

    this->StopThread();
}

void ProcessCam::slotTbLog() {

    for(int i = linkMain.tbLog->rowCount(); i>=0; i--)
        linkMain.tbLog->removeRow(i);
}

QString ProcessCam::splitStrCom(QString str) {
    QString strRes = ",,";
    QStringList listStr= str.split("\r\n");
    if (listStr.size() > 2)
        strRes = listStr.at(2);
    return strRes;
}

void ProcessCam::AddLog(QString str, QColor iColor) {

    QTime time = QTime::currentTime();
    QString timeString = time.toString();

    //set color
    QTableWidgetItem *timeLog = new QTableWidgetItem(QString(timeString));
    timeLog->setForeground(Qt::black);
    timeLog->setTextAlignment(Qt::AlignCenter);

    QTableWidgetItem *logdata = new QTableWidgetItem(QString(str));
    logdata->setForeground(iColor);

    linkMain.tbLog->insertRow(0);
    linkMain.tbLog->setItem(0, 0, timeLog);
    linkMain.tbLog->setItem(0, 1, logdata);
}

void ProcessCam::readDataComport() {
    qmutexCom.lock();
    qstrDataCom += qspCom->readAll();

    if(qstrDataCom.isEmpty()){
        qmutexCom.unlock();
        return;
    }

    qDebug()<<"DATACOM: "<< qstrDataCom;
    qmutexCom.unlock();
}

void ProcessCam::handleComportError(QSerialPort::SerialPortError serialPortError) {
    QString err =  QObject::tr("socket3:: port %1, error: %2, type = ")
            .arg(qspCom->portName())
            .arg(qspCom->errorString());

    switch (serialPortError) {
    case QSerialPort::NoError:
        return;
    default:
        err += QString::number(serialPortError);
        break;
    }

    if(m_bRun) {
        StopThread();
        AddLog("ComportErrorSk::Stop thread", Qt::red);
    }
    else{
        AddLog("Error ComportSocket", Qt::red);
    }

    if(qspCom->isOpen())
        qspCom->close();

    if(mDevice.bUseComIO){

    }
    emit eDisplayImage(mError, linkMain.lbDisplay);
}

void ProcessCam::handleComportIO() {
    if(m_bRun) {
        StopThread();
        AddLog("ComportErrorIO::Stop thread", Qt::red);
    }
    else{
        AddLog("Error ComportIO", Qt::red);
    }

    emit eDisplayImage(mError, linkMain.lbDisplay);
}

void ProcessCam::readDataCmd() {
    mutexADB.lock();
    qstrDataADB = processADB->readAllStandardOutput();
    if(qstrDataADB.isEmpty()){
        mutexADB.unlock();
        return;
    }
    qDebug()<<"*"<<qstrDataADB;
    mutexADB.unlock();
}

void ProcessCam::handleCmdError(QProcess::ProcessError processError) {
    QString err =  QObject::tr("adb test:: adb error: %1, type = ")
            .arg(processADB->errorString());

    switch (processError) {
    case QProcess::ReadError:
        err += "Read Error";
        break;
    case QProcess::WriteError:
        err += "Write Error";
        break;
    default:
        err += QString::number(processError);
        break;
    }
    qDebug() << err;
    AddLog(err, Qt::red);
}

void ProcessCam::Display_Image(Mat m, QLabel* lb) {
    if (m.empty()){
        return;
    }
    cv::Mat OutImg;
    QImage qImage;

    OutImg = m.clone();

    if(OutImg.channels() == 3)
        cv::cvtColor(OutImg, OutImg, CV_BGR2RGB);
    else if(OutImg.channels() == 1){
        cv::cvtColor(OutImg, OutImg, CV_GRAY2RGB);
    }
    qImage = QImage(OutImg.data, OutImg.cols, OutImg.rows, OutImg.step, QImage::Format_RGB888);
    lb->setPixmap(QPixmap::fromImage(qImage));
}

void ProcessCam::SetResultTbw(QPoint PosNotify, QString qstrConTent, QColor qColor) {

    msleep(1);

    QTableWidgetItem *iTemTemp = new QTableWidgetItem(qstrConTent);
    iTemTemp->setForeground(qColor);
    linkMain.tbError->setItem(PosNotify.x(),PosNotify.y(),iTemTemp);
}

void ProcessCam::SetReultHeaderTbw(int iCamNo, QString qstrConTent, QColor qColor) {
    QTableWidgetItem *iTemTemp = new QTableWidgetItem(qstrConTent);
    iTemTemp->setForeground(qColor);
    linkMain.tbError->setHorizontalHeaderItem(iCamNo,iTemTemp);
}

vector<QString> ProcessCam::GetAllFileInFolder(QString folder) {
    vector<QString> vAllFile;
    QDir directory(folder);
    directory.refresh();
    QStringList images = directory.entryList(QStringList() << "*.jpg" << "*.JPG",QDir::Files);
    foreach(QString filename, images) {
        //do whatever you need to do
        qDebug()<<"[img]="<<filename;
        vAllFile.push_back(filename);
    }
    qDebug()<<"[num img = ]"<< vAllFile.size();
    return vAllFile;
}

void ProcessCam::initThread()
{
    if(ptrIO != nullptr){
       thread->quit();
       QThread::msleep(1000);
       delete ptrIO;
    }

    ptrIO =  new ThreadIO(this->mDevice.qstrComIO);
    thread = new QThread;

    //auto serial = new SerialPort;
    ptrIO->moveToThread(thread);
    QApplication::connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    QApplication::connect(thread, &QThread::finished,  ptrIO, &ThreadIO::StopThread);
    QApplication::connect(thread, &QThread::started,   ptrIO, &ThreadIO::StartThread);
    connect(this, &ProcessCam::emitThreadIO, ptrIO, &ThreadIO::sendDataCOM);

    thread->start();
}

void ProcessCam::WriteLogFileID(QString data) {
    QString time = "[" + QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss") + "]";
    if(QString(mGenenal.qstrFolderLog) + "/qstrlogFileID_" + QDateTime::currentDateTime().toString("dd-MM-yyyy") + ".txt" != qstrlogFileID){
        qstrlogFileID = QString(mGenenal.qstrFolderLog) + "/qstrlogFileID_" + QDateTime::currentDateTime().toString("dd-MM-yyyy") + ".txt";
        qflogFileID.setFileName(qstrlogFileID);
        qflogFileID.open(QIODevice::ReadWrite| QIODevice::Append | QIODevice::Text);
    }
    if(qflogFileID.isOpen()) {
        QString str = time + "\t" + data + "\n";
        QTextStream qStream(&qflogFileID);
        qStream << str;
    }
}

void ProcessCam::saveResultImg(QString strIDmd, QString nameCam, Mat img) {

    if(bSaveImgResize)
        resize(img, img, cv::Size(640,480));
    QString strFileSave = mDevice.qstrFolderOutput + "/" + strIDmd + "_" + nameCam + ".jpg" ;
    imwrite(strFileSave.toStdString(), img);
}


void ProcessCam::SetStep(int iStep) {
    iCurStep = iStep;
}
