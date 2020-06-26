#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::StartPrg() {

    for(int i = 0 ; i < NUM_CAM;  i++){
        if(!pProc[i]->m_bRun){
            pProc[i]->StartThread();
        }
    }
}

void MainWindow::StopPrg()
{
    for(int i = 0 ; i < NUM_CAM;  i++){
        if(pProc[i]->m_bRun){
            pProc[i]->StopThread();
        }
    }
}

//MainWindow *manwinl;
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent,Qt::Window), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    cv::setUseOptimized(true); // set toi uu ham open cv

    setWindowTitle("fVision Check Cam - v3.1 ");

    setWindowIcon(QIcon(":/Icon/Vietnam.png"));

    ui->tabWidget->setCurrentIndex(0);

    bLoadParaFirst = true;

    for(int i=0; i<NUM_LINEDIT; i++){

        m_LineEdit[i] = new QLineEdit();
    }

    for(int i=0 ; i<NUM_CHECKBOX; i++){

        m_CheckBox[i] = new QCheckBox();
    }

    for(int i=0; i<NUM_COMBOBOX; i++){

        m_ComboBox[i] = new QComboBox();
    }

    DisableParameter();

    m_ProcessSStain         =    new ProcessSStain(this);
    m_ProcessWhiteSStain    =    new ProcessWhiteSStain(this);
    m_ProcessLStain         =    new ProcessLStain(this);
    m_ProcessWhiteLStain    =    new ProcessWhiteLStain(this);
    m_ProcessGlare          =    new ProcessGlare(this);
    m_ProcessDarkspot       =    new ProcessDarkSpot(this);
    m_ProcessFocus          =    new ProcessFocus(this);
    m_ProcessWrongColor     =    new ProcessWrongColor(this);
    m_ProcessCheckComIO     =    new ProcessCheckComIO(this);
    Simulation = new processSimulation(this);

    qDebug()<< qstrlistModel.size()<<"Size";
    ui->cbbSelectModel->addItems(qstrlistModel);
    ui->cbbSelectModel_Left->addItems(qstrlistModel);
    ui->cbbSelectModel_Right->addItems(qstrlistModel);

    for(int i =0; i< NUM_SIDE; i++)  {
        pProc[i] = nullptr;
    }
    connect(m_ProcessSStain,      SIGNAL(threadProcessSStain(int)),      this, SLOT(VisionSStain(int)));               //test stain small
    connect(m_ProcessWhiteSStain, SIGNAL(threadProcessWhiteSStain(int)), this, SLOT(VisionWhiteSStain(int)));          //test whitestain small
    connect(m_ProcessLStain,      SIGNAL(threadProcessLStain(int)),      this, SLOT(VisionLStain(int)));               //test stain large
    connect(m_ProcessWhiteLStain, SIGNAL(threadProcessWhiteLStain(int)), this, SLOT(VisionWhiteLStain(int)));          //test whitestain large

    connect(m_ProcessGlare,       SIGNAL(threadProcessGlare(int)),        this, SLOT(VisionGlare(int)));               //test Glare
    connect(m_ProcessDarkspot,    SIGNAL(threadProcessDarkspot(int)),     this, SLOT(VisionDarkSpot(int)));            //test spDarksport
    connect(m_ProcessWrongColor,  SIGNAL(threadProcessWrongColor(int)),   this, SLOT(VisionWrongColor(int)));          //test wrong color
    connect(m_ProcessFocus,       SIGNAL(threadProcessFocus(int)),        this, SLOT(VisionFocus(int)));               //test focus
    connect(m_ProcessCheckComIO,  SIGNAL(threadProcessCheckComIO()),      this, SLOT(readDataComIO()));                //test focus

    connect(this, SIGNAL(eDisplay_Image(Mat,int)), this, SLOT(Display_Image(Mat,int)));
    connect(this, SIGNAL(eAddLogTestManual(QString,QColor)), this, SLOT(AddLogTestManual(QString,QColor)));
    connect(ui->tbwLogTestManual, SIGNAL(cellClicked(int, int)), this, SLOT(showImageWhenClick(int, int)));
    connect(this, SIGNAL(esetValueProcessBar(int)), this, SLOT(setValueProcessBar(int)));

    QObject::connect(Simulation, SIGNAL(threadsimulation(int,int,QStringList)), this, SLOT(simulatorVision(int,int,QStringList)));

    CreatTreePara();
    /*Zoom -> link to eventFilter*/
    this->installEventFilter(this);

    ui->txt_delay->setText("0.5");

    OnInitDlg();
    LoadBufferDataGeneral(SIDE_LEFT);
    LoadBufferDataGeneral(SIDE_RIGHT);
    ui->cbbSelectModel->setCurrentIndex(mGeneral[SIDE_LEFT].Device.ipModel);
    int i = mGeneral[SIDE_LEFT].Device.ipModel;
    LoadBufferDataParaCheck(PARA_CONTAIN, i);
    InitGUI(mGeneral[SIDE_LEFT].Device.ipModel);
    InitFolder();
    InitLogFile(SIDE_LEFT);
    InitLogFile(SIDE_RIGHT);
    InitComport();

    /*Show date tTime*/
    qtrTimeSys = new QTimer(this);
    qtrTimeSys->start(TIME_SYSTEM);
    connect(qtrTimeSys, SIGNAL(timeout()), this, SLOT(DisplayDateTime()));

    InitProcCam();
    bLoadParaFirst = false;

}

MainWindow::~MainWindow() {
    CloseLogFile();
    if(m_ProcessDarkspot->m_bRun)
        m_ProcessDarkspot->StopThread();

    if(m_ProcessSStain->m_bRun)
        m_ProcessSStain->StopThread();

    if(m_ProcessWhiteSStain->m_bRun)
        m_ProcessWhiteSStain->StopThread();

    if(m_ProcessLStain->m_bRun)
        m_ProcessLStain->StopThread();

    if(m_ProcessWhiteLStain->m_bRun)
        m_ProcessWhiteLStain->StopThread();

    if(m_ProcessWrongColor->m_bRun)
        m_ProcessWrongColor->StopThread();

    if(m_ProcessGlare->m_bRun)
        m_ProcessGlare->StopThread();

    if(m_ProcessFocus->m_bRun)
        m_ProcessFocus->StopThread();

    if(m_ProcessCheckComIO->m_bRun)
        m_ProcessCheckComIO->StopThread();

    for(int i = 0; i< NUM_SIDE; i++) {
        delete pProc[i];
    }
    //close comport
    CloseCom(qspSerial);

    for(int i =0; i<NUM_SIDE; i++){
        CloseCom(qspAuComport[i]);
    }

    qDebug("Destroy");
    delete m_ProcessDarkspot;
    delete m_ProcessSStain;
    delete m_ProcessWhiteSStain;
    delete m_ProcessLStain;
    delete m_ProcessWhiteLStain;
    delete m_ProcessWrongColor;
    delete m_ProcessGlare;
    delete m_ProcessFocus;
    delete ui;
}

void MainWindow::ResizeTableLog() {
    /*Log*/
    int widthTableRect = ui->tbwLogTestManual->geometry().width();

    ui->tbwLogTestManual->setColumnCount(2);
    ui->tbwLogTestManual->setColumnWidth(0, widthTableRect/1);
    ui->tbwLogTestManual->setColumnWidth(1,6*widthTableRect/1);

    /*tbwReceiverDataCom*/
    int widthDataCom = ui->tbwReceiverDataCom->geometry().width();
    ui->tbwReceiverDataCom->setColumnCount(2);
    ui->tbwReceiverDataCom->setColumnWidth(0,widthDataCom/4);
    ui->tbwReceiverDataCom->setColumnWidth(1,3*widthDataCom/4);

    /*tbwReceiverDataCmd*/
    int widthDataCmd = ui->tbwReceiverDataCmd->geometry().width();
    ui->tbwReceiverDataCmd->setColumnCount(2);
    ui->tbwReceiverDataCmd->setColumnWidth(0,widthDataCmd/4);
    ui->tbwReceiverDataCmd->setColumnWidth(1,3*widthDataCmd/4);

    /*tbwError_Left*/
    int widthTableErrorL = ui->tbwErrorLeft->geometry().width();
    ui->tbwErrorLeft->setColumnCount(2);
    ui->tbwErrorLeft->setColumnWidth(0,widthTableErrorL/4);
    ui->tbwErrorLeft->setColumnWidth(1,3*widthTableErrorL/4);

    /*tbwError_Right*/
    int widthTableErrorR = ui->tbwErrorRight->geometry().width();
    ui->tbwErrorRight->setColumnCount(2);
    ui->tbwErrorRight->setColumnWidth(0,widthTableErrorR/4);
    ui->tbwErrorRight->setColumnWidth(1,3*widthTableErrorR/4);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    /*Zoom*/
    if (obj == this) {
        if (event->type() == QEvent::Resize) {
            static int iCount = 0;
            static QSize baseSize = this->window()->size();
            static QList<QRect> baseRectElement;
            static QList<QWidget *> widgets = this->window()->findChildren<QWidget *>(QString(), Qt::FindChildrenRecursively);
            iCount++;
            if (iCount==1) {
                baseSize = this->size();
                baseRectElement.clear();
                for (int i = 0; i < widgets.size(); ++i) {
                    baseRectElement.push_back(widgets[i]->geometry());
                }
                return true;
            }
            double dScaleW = (double)this->window()->size().width()/baseSize.width();
            double dScaleH = (double)this->window()->size().height()/baseSize.height();

            for (int i = 0; i < widgets.size(); ++i) {
                QRect rect = baseRectElement[i];
                QRect newRect = QRect(dScaleW*rect.left(),
                                      dScaleH*rect.top(),
                                      dScaleW*rect.width(),
                                      dScaleH*rect.height());
                widgets[i]->setGeometry(newRect);
                widgets[i]->updateGeometry();
            }

            qrPosDisp = ui->display->geometry();
            ResizeTableLog();
            return true;
        }
        else
            if(event->type()==QEvent::KeyRelease && (ui->tabWidget->currentIndex() == AUTO)) {

                QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
                QString keyboard = QKeySequence(keyEvent->key()).toString();
                //QString path = "null";
                qDebug()<<"Release"<<keyboard;

                if(keyboard.contains(mGeneral[SIDE_LEFT].Device.qstrKeyStart) ||keyboard.contains(mGeneral[SIDE_RIGHT].Device.qstrKeyStart)){

                }
                else {
                    qDebug()<<"Invalue key";
                    return false;
                }

                //Left - socket1
                if(mGeneral[SIDE_LEFT].Device.bUse) {

                    if((keyboard.contains(mGeneral[SIDE_LEFT].Device.qstrKeyStart)) && qspAuComport[SIDE_LEFT]->isOpen()&&!pProc[SIDE_LEFT]->m_bRun) {

                        pProc[SIDE_LEFT]->StartThread();
                        return false;
                    }

                    else if (keyboard.contains(mGeneral[SIDE_LEFT].Device.qstrKeyStart) && !qspAuComport[SIDE_LEFT]->isOpen()){
                        WriteLogFile("Check COM Port", SIDE_LEFT);
                        return false;
                    }

                    else if (keyboard.contains(mGeneral[SIDE_LEFT].Device.qstrKeyStart) && mGeneral[SIDE_LEFT].Device.bUsecomIO&& !qspAuComIO[SIDE_LEFT]->isOpen()){
                        WriteLogFile("Check COM Port IO Left", SIDE_LEFT);
                        return false;
                    }
                }

                //RIGHT - socket2
                if(mGeneral[SIDE_RIGHT].Device.bUse) {
                    if(keyboard.contains(mGeneral[SIDE_RIGHT].Device.qstrKeyStart)&& qspAuComport[SIDE_RIGHT]->isOpen()&&!pProc[SIDE_RIGHT]->m_bRun) {

                        pProc[SIDE_RIGHT]->StartThread();
                        return false;
                    }
                    else if (keyboard.contains(mGeneral[SIDE_RIGHT].Device.qstrKeyStart) && !qspAuComport[SIDE_RIGHT]->isOpen()) {
                        WriteLogFile("Check COM Port", SIDE_RIGHT);
                    }
                    else if(keyboard.contains(mGeneral[SIDE_RIGHT].Device.qstrKeyStart) && mGeneral[SIDE_RIGHT].Device.bUsecomIO &&!qspAuComIO[SIDE_RIGHT]->isOpen()){
                        WriteLogFile("Check COM Port IO Right", SIDE_RIGHT);
                    }
                }

            }
        return false;
    }
    return false;
}

void MainWindow:: readDataComIO(){
    /*Left - socket1*/
    if(mGeneral[SIDE_LEFT].Device.bUse && mGeneral[SIDE_LEFT].Device.bUsecomIO && pProc[SIDE_LEFT]->qspCom->isOpen()) {
        if(!pProc[SIDE_LEFT]->m_bRun && pProc[SIDE_LEFT]->ptrIO->m_InStart)
            pProc[SIDE_LEFT]->StartThread();
        }
//    QThread::msleep(500);
    /*Right - socket2*/
    if(mGeneral[SIDE_RIGHT].Device.bUse && mGeneral[SIDE_RIGHT].Device.bUsecomIO && pProc[SIDE_RIGHT]->qspCom->isOpen()) {
        if(!pProc[SIDE_RIGHT]->m_bRun && pProc[SIDE_RIGHT ]->ptrIO->m_InStart)
            pProc[SIDE_RIGHT]->StartThread();
    }
}

void MainWindow::saveJson(QJsonDocument document, QString fileName) const
{
    if(!QFileInfo(fileName).exists()){
        QDir dir;
        dir.mkpath(fileName);
    }
    QFile jsonFile(fileName);

    if(jsonFile.open(QFile::WriteOnly)){
        jsonFile.write(document.toJson());
        qDebug()<<"write file ok";
    }
    else
        qDebug()<<"write file ng";
}
QJsonDocument MainWindow::loadJson(QString fileName) {
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
}

void MainWindow::setValueProcessBar(int iValue)
{
    ui->progressBar->setValue(iValue);
}

void MainWindow::SaveDataGeneral() {
    try{
        QJsonObject json;
        json["version"]               = ui->edtVersion->text().trimmed();
        json["folderLog"]             = ui->edtFolderLog->text().trimmed();
        /*socket Device*/
        json["left_useSK"]          = ui->checkBoxUseLeft->isChecked();
        json["left_comSK"]          = ui->edtComLeft->text().trimmed();
        json["left_id"]             = ui->edtIDLeft->text().trimmed();
        json["left_keystart"]       = ui->edtKeyStartLeft->text().trimmed();
        json["left_inputfolder"]    = ui->edtInputFolderLeft->text().trimmed();
        json["left_outputfolder"]   = ui->edtOutputFolderLeft->text().trimmed();
        json["left_phonefolder"]    = ui->edtPhoneFolderLeft->text().trimmed();
        json["left_model"]          = ui->cbbSelectModel_Left->currentIndex();
        json["left_usecomIO"]       = ui->checkBoxUseComportIO_Left->isChecked();
        json["left_comIO"]          = ui->edtComportIO_Left->text().trimmed();
        /*socket Device*/
        json["right_useSK"]         = ui->checkBoxUseRight->isChecked();
        json["right_comSK"]         = ui->edtComRight->text().trimmed();
        json["right_id"]            = ui->edtIDRight->text().trimmed();
        json["right_keystart"]      = ui->edtKeyStartRight->text().trimmed();
        json["right_inputfolder"]   = ui->edtInputFolderRight->text().trimmed();
        json["right_outputfolder"]  = ui->edtOutputFolderRight->text().trimmed();
        json["right_phonefolder"]   = ui->edtPhoneFolderRight->text().trimmed();
        json["right_model"]         = ui->cbbSelectModel_Right->currentIndex();
        json["right_usecomIO"]      = ui->checkBoxUseComportIO_Right->isChecked();
        json["right_comIO"]         = ui->edtComportIO_Right->text().trimmed();

        json["opt_saveimg_resize"] = ui->cbSaveImageResize->isChecked();

        QJsonDocument saveDoc(json);
        saveJson(saveDoc,PATH_COMMON);
    }
    catch(Exception &e){
        QString qstrerror = QString::fromStdString(e.what());
        qDebug()<<"[SaveGeneralPara]"<<qstrerror;
        QMessageBox::warning(this,"Error",qstrerror);
    }
}
void MainWindow::SaveData() {
    try{
        /*save data camera*/
        QJsonObject json;
        int iCamNo = FW1;
        if(ui->cbbSelectModel->currentIndex() >= G975){
            iCamNo = FB1;
        }
        for(int iTypeCam = FW1; iTypeCam <= iCamNo; iTypeCam++){
            /*Option fuction check */
            json[tr("opt_showimg_%1").arg(iTypeCam)]                                 = mGeneral[PARA_CONTAIN].bOptShowImg[iTypeCam];
            json[tr("opt_saveimg_%1").arg(iTypeCam)]                                 = mGeneral[PARA_CONTAIN].bOptSaveImg[iTypeCam];
            json[tr("opt_checkiris")]                                                = mGeneral[PARA_CONTAIN].bOptCheckIris;
            json[tr("opt_checkstain_%1").arg(iTypeCam)]                              = mGeneral[PARA_CONTAIN].bOptCheckStain[iTypeCam];
            json[tr("opt_checkwhitestain_%1").arg(iTypeCam)]                         = mGeneral[PARA_CONTAIN].bOptCheckWhiteStain[iTypeCam];
            json[tr("opt_checkglare_%1").arg(iTypeCam)]                              = mGeneral[PARA_CONTAIN].bOptCheckGlare[iTypeCam];
            json[tr("opt_checkfocus_%1").arg(iTypeCam)]                              = mGeneral[PARA_CONTAIN].bOptCheckFocus[iTypeCam];
            json[tr("opt_checkcolor_%1").arg(iTypeCam)]                              = mGeneral[PARA_CONTAIN].bOptCheckColor[iTypeCam];
            json[tr("opt_checkdarksport_%1").arg(iTypeCam)]                          = mGeneral[PARA_CONTAIN].bOptDarkSport[iTypeCam];
            json[tr("opt_captureaf_%1").arg(iTypeCam)]                               = mGeneral[PARA_CONTAIN].bOptCaptrueAf[iTypeCam];
            /*delay time*/
            for(int iDlNo = DL_UART_USB_SEND; iDlNo < NUM_DELAY; iDlNo++ ) {
                json[tr("delay_%1").arg(iDlNo)]                                      = Double2QString(mGeneral[PARA_CONTAIN].dbDelay[iDlNo]);
            }
            /*paint parameter*/
            json["com_thickness"]                                                    = Int2QString(mGeneral[PARA_CONTAIN].ipPaintThickness);
            json["com_offset"]                                                       = Int2QString(mGeneral[PARA_CONTAIN].ipPaintOffset);
            /*normalize parameter*/
            json[tr("nor_type_%1").arg(iTypeCam)]                                    = Int2QString(mGeneral[PARA_CONTAIN].ipNormType[iTypeCam]);
            json[tr("nor_beta_%1").arg(iTypeCam)]                                    = Int2QString(mGeneral[PARA_CONTAIN].ipNormBeta[iTypeCam]);
            json[tr("nor_alpha_%1").arg(iTypeCam)]                                   = Int2QString(mGeneral[PARA_CONTAIN].ipNormAlpha[iTypeCam]);

            for(int iTypeSize = TYPE_SIZE_SMALL; iTypeSize <= TYPE_SIZE_LARGE; iTypeSize++){
                /*Stain parameter*/
                json[tr("stain_threshold_%1_%2").arg(iTypeCam).arg(iTypeSize)]         = Int2QString(mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipThreshold[iTypeSize]);
                json[tr("stain_block_size_%1_%2").arg(iTypeCam).arg(iTypeSize)]        = Int2QString(mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipBlockSize[iTypeSize]);
                json[tr("stain_blur_size_%1_%2").arg(iTypeCam).arg(iTypeSize)]         = Int2QString(mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipBlurSize[iTypeSize]);
                json[tr("stain_erode_size_%1_%2").arg(iTypeCam).arg(iTypeSize)]        = Int2QString(mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipErodeSize[iTypeSize]);
                json[tr("stain_erode_loop_%1_%2").arg(iTypeCam).arg(iTypeSize)]        = Int2QString(mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipErodeLoop[iTypeSize]);
                json[tr("stain_dilate_size_%1_%2").arg(iTypeCam).arg(iTypeSize)]       = Int2QString(mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipDilateSize[iTypeSize]);
                json[tr("stain_dilate_loop_%1_%2").arg(iTypeCam).arg(iTypeSize)]       = Int2QString(mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipDilateLoop[iTypeSize]);
                json[tr("stain_remove_edge_%1_%2").arg(iTypeCam).arg(iTypeSize)]       = Int2QString(mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipRemoveEdge[iTypeSize]);
                json[tr("stain_remove_conner_%1_%2").arg(iTypeCam).arg(iTypeSize)]     = Int2QString(mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipRemoveConner[iTypeSize]);
                json[tr("stain_filter_area_%1_%2").arg(iTypeCam).arg(iTypeSize)]       = Point2QString(Point(mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipFilterAreaMin[iTypeSize],
                                                                                                             mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipFilterAreaMax[iTypeSize]));

                json[tr("stain_filter_width_%1_%2").arg(iTypeCam).arg(iTypeSize)]      = Point2QString(Point(mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipFilterWMin[iTypeSize],
                                                                                                             mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipFilterWMax[iTypeSize]));

                json[tr("stain_filter_height_%1_%2").arg(iTypeCam).arg(iTypeSize)]     = Point2QString(Point(mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipFilterHMin[iTypeSize],
                                                                                                             mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipFilterHMax[iTypeSize]));
                /*WhiteStain parameter*/
                json[tr("wstain_threshold_%1_%2").arg(iTypeCam).arg(iTypeSize)]        = Int2QString(mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipThreshold[iTypeSize]);
                json[tr("wstain_block_size_%1_%2").arg(iTypeCam).arg(iTypeSize)]       = Int2QString(mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipBlockSize[iTypeSize]);
                json[tr("wstain_blur_size_%1_%2").arg(iTypeCam).arg(iTypeSize)]        = Int2QString(mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipBlurSize[iTypeSize]);
                json[tr("wstain_erode_size_%1_%2").arg(iTypeCam).arg(iTypeSize)]       = Int2QString(mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipErodeSize[iTypeSize]);
                json[tr("wstain_erode_loop_%1_%2").arg(iTypeCam).arg(iTypeSize)]       = Int2QString(mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipErodeLoop[iTypeSize]);
                json[tr("wstain_dilate_size_%1_%2").arg(iTypeCam).arg(iTypeSize)]      = Int2QString(mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipDilateSize[iTypeSize]);
                json[tr("wstain_dilate_loop_%1_%2").arg(iTypeCam).arg(iTypeSize)]      = Int2QString(mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipDilateLoop[iTypeSize]);
                json[tr("wstain_remove_edge_%1_%2").arg(iTypeCam).arg(iTypeSize)]      = Int2QString(mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipRemoveEdge[iTypeSize]);
                json[tr("wstain_remove_conner_%1_%2").arg(iTypeCam).arg(iTypeSize)]    = Int2QString(mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipRemoveConner[iTypeSize]);
                json[tr("wstain_filter_area_%1_%2").arg(iTypeCam).arg(iTypeSize)]      = Point2QString(Point(mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipFilterAreaMin[iTypeSize],
                                                                                                             mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipFilterAreaMax[iTypeSize]));

                json[tr("wstain_filter_width_%1_%2").arg(iTypeCam).arg(iTypeSize)]     = Point2QString(Point(mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipFilterWMin[iTypeSize],
                                                                                                             mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipFilterWMax[iTypeSize]));

                json[tr("wstain_filter_height_%1_%2").arg(iTypeCam).arg(iTypeSize)]    = Point2QString(Point(mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipFilterHMin[iTypeSize],
                                                                                                             mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipFilterHMax[iTypeSize]));
            }

            /*Glare Check*/
            for(int iRoi = 1 ; iRoi <= NUM_ROI; iRoi++){

                json[tr("glare_threshold%2_%1").arg(iTypeCam).arg(iRoi)]                  = Int2QString(mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgThreshold[iRoi-1]);
                json[tr("glare_blur_size%2_%1").arg(iTypeCam).arg(iRoi)]                             = Int2QString(mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgBlurSize[iRoi-1]);
                json[tr("glare_roicheck%2_%1").arg(iTypeCam).arg(iRoi)]                             = Rect2QString(mGeneral[PARA_CONTAIN].spGlare[iTypeCam].rpRoi[iRoi-1]);
                json[tr("glare_erode_size%2_%1").arg(iTypeCam).arg(iRoi)]                            = Int2QString(mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgErodeSize[iRoi-1]);
                json[tr("glare_erode_loop%2_%1").arg(iTypeCam).arg(iRoi)]                            = Int2QString(mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgErodeLoop[iRoi-1]);
                json[tr("glare_dilate_size%2_%1").arg(iTypeCam).arg(iRoi)]                           = Int2QString(mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgDilateSize[iRoi-1]);
                json[tr("glare_dilate_loop%2_%1").arg(iTypeCam).arg(iRoi)]                           = Int2QString(mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgDilateLoop[iRoi-1]);
                json[tr("glare_remove_edge%2_%1").arg(iTypeCam).arg(iRoi)]                           = Int2QString(mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgRemoveEdge[iRoi-1]);
                json[tr("glare_remove_conner%2_%1").arg(iTypeCam).arg(iRoi)]                         = Int2QString(mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgRemoveConner[iRoi-1]);

                json[tr("glare_filtermean_roi%2_%1").arg(iTypeCam).arg(iRoi)]                       = Point2QString(Point(mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgMSRoiMin[iRoi-1],
                                                                                                         mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgMSRoiMax[iRoi-1]));

                json[tr("glare_filter_area%2_%1").arg(iTypeCam).arg(iRoi)]                           = Point2QString(Point(mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgFilterAreaMin[iRoi-1],
                                                                                                          mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgFilterAreaMax[iRoi-1]));

                json[tr("glare_filter_width%2_%1").arg(iTypeCam).arg(iRoi)]                          = Point2QString(Point(mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgFilterWMin[iRoi-1],
                                                                                                          mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgFilterWMax[iRoi-1]));

                json[tr("glare_filter_height%2_%1").arg(iTypeCam).arg(iRoi)]                         = Point2QString(Point(mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgFilterHMin[iRoi-1],
                                                                                                          mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgFilterHMax[iRoi-1]));

            }

            /*Focus Check*/
            json[tr("focus_roicheck1_%1").arg(iTypeCam)]                             = Rect2QString(mGeneral[PARA_CONTAIN].spFocus[iTypeCam].rpRoi[0]);
            json[tr("focus_roicheck2_%1").arg(iTypeCam)]                             = Rect2QString(mGeneral[PARA_CONTAIN].spFocus[iTypeCam].rpRoi[1]);
            json[tr("focus_roicheck3_%1").arg(iTypeCam)]                             = Rect2QString(mGeneral[PARA_CONTAIN].spFocus[iTypeCam].rpRoi[2]);
            json[tr("focus_roicheck4_%1").arg(iTypeCam)]                             = Rect2QString(mGeneral[PARA_CONTAIN].spFocus[iTypeCam].rpRoi[3]);
            json[tr("focus_roicheck5_%1").arg(iTypeCam)]                             = Rect2QString(mGeneral[PARA_CONTAIN].spFocus[iTypeCam].rpRoi[4]);
            json[tr("focus_roicheck6_%1").arg(iTypeCam)]                             = Rect2QString(mGeneral[PARA_CONTAIN].spFocus[iTypeCam].rpRoi[5]);

            json[tr("focus_stdroi1_%1").arg(iTypeCam)]                               = Point2QString(Point(mGeneral[PARA_CONTAIN].spFocus[iTypeCam].ipgMSRoiMin[0],
                                                                                                     mGeneral[PARA_CONTAIN].spFocus[iTypeCam].ipgMSRoiMax[0]));
            json[tr("focus_stdroi2_%1").arg(iTypeCam)]                               = Point2QString(Point(mGeneral[PARA_CONTAIN].spFocus[iTypeCam].ipgMSRoiMin[1],
                                                                                                     mGeneral[PARA_CONTAIN].spFocus[iTypeCam].ipgMSRoiMax[1]));
            json[tr("focus_stdroi3_%1").arg(iTypeCam)]                               = Point2QString(Point(mGeneral[PARA_CONTAIN].spFocus[iTypeCam].ipgMSRoiMin[2],
                                                                                                     mGeneral[PARA_CONTAIN].spFocus[iTypeCam].ipgMSRoiMax[2]));
            json[tr("focus_stdroi4_%1").arg(iTypeCam)]                               = Point2QString(Point(mGeneral[PARA_CONTAIN].spFocus[iTypeCam].ipgMSRoiMin[3],
                                                                                                     mGeneral[PARA_CONTAIN].spFocus[iTypeCam].ipgMSRoiMax[3]));
            json[tr("focus_stdroi5_%1").arg(iTypeCam)]                               = Point2QString(Point(mGeneral[PARA_CONTAIN].spFocus[iTypeCam].ipgMSRoiMin[4],
                                                                                                     mGeneral[PARA_CONTAIN].spFocus[iTypeCam].ipgMSRoiMax[4]));
            json[tr("focus_stdroi6_%1").arg(iTypeCam)]                               = Point2QString(Point(mGeneral[PARA_CONTAIN].spFocus[iTypeCam].ipgMSRoiMin[5],
                                                                                                     mGeneral[PARA_CONTAIN].spFocus[iTypeCam].ipgMSRoiMax[5]));
            /*DrakSport*/
            json[tr("darksport_threshold_%1").arg(iTypeCam)]                         = Int2QString(mGeneral[PARA_CONTAIN].spDarksport[iTypeCam].ipdsThreshold);
            json[tr("darksport_blocksize_%1").arg(iTypeCam)]                         = Int2QString(mGeneral[PARA_CONTAIN].spDarksport[iTypeCam].ipdsBlockSize);
            json[tr("darksport_filtarea_%1").arg(iTypeCam)]                          = Point2QString(Point(mGeneral[PARA_CONTAIN].spDarksport[iTypeCam].ipdsFilterAreaMin,
                                                                                                           mGeneral[PARA_CONTAIN].spDarksport[iTypeCam].ipdsFilterAreaMax));
            /*Erong Color*/
            json[tr("wrongcolor_meanred_%1").arg(iTypeCam)]                          = Point2QString(Point(mGeneral[PARA_CONTAIN].spWrongColor[iTypeCam].ipwcMeanRedMin,
                                                                                                           mGeneral[PARA_CONTAIN].spWrongColor[iTypeCam].ipwcMeanRedMax));
            json[tr("wrongcolor_meangreen_%1").arg(iTypeCam)]                        = Point2QString(Point(mGeneral[PARA_CONTAIN].spWrongColor[iTypeCam].ipwcMeanGreenMin,
                                                                                                           mGeneral[PARA_CONTAIN].spWrongColor[iTypeCam].ipwcMeanGreenMax));
            json[tr("wrongcolor_meanblue_%1").arg(iTypeCam)]                         = Point2QString(Point(mGeneral[PARA_CONTAIN].spWrongColor[iTypeCam].ipwcMeanBlueMin,
                                                                                                           mGeneral[PARA_CONTAIN].spWrongColor[iTypeCam].ipwcMeanBlueMax));
        }

        json["atcommand_uartusb_send"]         = mGeneral[PARA_CONTAIN].ATCMD[AT_UART_USB].send;
        json["atcommand_uartusb_respone"]      = mGeneral[PARA_CONTAIN].ATCMD[AT_UART_USB].respone;

        json["atcommand_homescreen_send"]      = mGeneral[PARA_CONTAIN].ATCMD[AT_HOMECREEN].send;
        json["atcommand_homescreen_respone"]   = mGeneral[PARA_CONTAIN].ATCMD[AT_HOMECREEN].respone;

        json["atcommand_openiris_send"]        = mGeneral[PARA_CONTAIN].ATCMD[AT_OPENIRIS].send;
        json["atcommand_openiris_respone"]     = mGeneral[PARA_CONTAIN].ATCMD[AT_OPENIRIS].respone;

        json["atcommand_closeiris_send"]       = mGeneral[PARA_CONTAIN].ATCMD[AT_CLOSEIRIS].send;
        json["atcommand_closeiris_respone"]    = mGeneral[PARA_CONTAIN].ATCMD[AT_CLOSEIRIS].respone;

        json["atcommand_openfw1_send"]         = mGeneral[PARA_CONTAIN].ATCMD[AT_OPENFW1].send;
        json["atcommand_openfw1_respone"]      = mGeneral[PARA_CONTAIN].ATCMD[AT_OPENFW1].respone;

        json["atcommand_closefw1_send"]        = mGeneral[PARA_CONTAIN].ATCMD[AT_CLOSEFW1].send;
        json["atcommand_closefw1_respone"]     = mGeneral[PARA_CONTAIN].ATCMD[AT_CLOSEFW1].respone;

        json["atcommand_openfb1_send"]         = mGeneral[PARA_CONTAIN].ATCMD[AT_OPENFB1].send;
        json["atcommand_openfb1_respone"]      = mGeneral[PARA_CONTAIN].ATCMD[AT_OPENFB1].respone;

        json["atcommand_closefb1_send"]        = mGeneral[PARA_CONTAIN].ATCMD[AT_CLOSEFB1].send;
        json["atcommand_closefb1_respone"]     = mGeneral[PARA_CONTAIN].ATCMD[AT_CLOSEFB1].respone;

        json["atcommand_capturenoaf_send"]     = mGeneral[PARA_CONTAIN].ATCMD[AT_CAPTURENOAF].send;
        json["atcommand_capturenoaf_respone"]  = mGeneral[PARA_CONTAIN].ATCMD[AT_CAPTURENOAF].respone;

        json["atcommand_captureaf_send"]       = mGeneral[PARA_CONTAIN].ATCMD[AT_CAPTUREAF].send;
        json["atcommand_captureaf_respone"]    = mGeneral[PARA_CONTAIN].ATCMD[AT_CAPTUREAF].respone;

        json["atcommand_capturetryaf_send"]    = mGeneral[PARA_CONTAIN].ATCMD[AT_CAPTURETRYAF].send;
        json["atcommand_capturetryaf_respone"] = mGeneral[PARA_CONTAIN].ATCMD[AT_CAPTURETRYAF].respone;

        json["adbcommand_getlist_send"]        = mGeneral[PARA_CONTAIN].ADBCMD[ADB_GET_LIST].send;
        json["adbcommand_getlist_respone"]      = mGeneral[PARA_CONTAIN].ADBCMD[ADB_GET_LIST].respone;

        json["adbcommand_pull2pc_send"]        = mGeneral[PARA_CONTAIN].ADBCMD[ADB_PULL_TO_PC].send;
        json["adbcommand_pull2pc_respone"]      = mGeneral[PARA_CONTAIN].ADBCMD[ADB_PULL_TO_PC].respone;

        json["adbcommand_removefolder_send"]   = mGeneral[PARA_CONTAIN].ADBCMD[ADB_REMOVE_FOLDER].send;
        json["adbcommand_removefolder_respone"] = mGeneral[PARA_CONTAIN].ADBCMD[ADB_REMOVE_FOLDER].respone;

        /*Save to json file */
        int iCurModel                                                            = ui->cbbSelectModel->currentIndex();
        QJsonDocument saveDoc(json);
        saveJson(saveDoc,tr(PATH_GENERAL).arg(listModel[iCurModel])+ PATH_NAME);
    }
    catch(Exception &e){

        QString strerror = QString::fromStdString(e.what());
        qDebug()<<"[SavePara]"<<strerror;
        QMessageBox::warning(this,"Error",strerror);
    }
}
void MainWindow::LoadBufferDataGeneral(int iSlide) {
    try{
        /*Load json file*/
        QJsonDocument loadData      = loadJson(PATH_COMMON);
        QJsonObject json            = loadData.object();
        /*load socket setting */
        mGeneral[iSlide].qstrVer                                             = json["version"].toString().trimmed();
        mGeneral[iSlide].qstrFolderLog                                       = json["folderLog"].toString().trimmed();

        QString qstrKeySaveResize                                            = tr("opt_saveimg_resize");

        mGeneral[iSlide].bOptSaveImageResize                                 = json[qstrKeySaveResize].toBool();
        /*Setting Socket*/
        if(iSlide == SIDE_LEFT){
            mGeneral[iSlide].Device.bUse                                     = json["left_useSK"].toBool();
            mGeneral[iSlide].Device.qstrID                                   = json["left_id"].toString().trimmed();
            mGeneral[iSlide].Device.qstrKeyStart                             = json["left_keystart"].toString().trimmed();
            mGeneral[iSlide].Device.qstrKeyStop                              = "ESC";
            mGeneral[iSlide].Device.qstrFolderInput                          = json["left_inputfolder"].toString().trimmed();
            mGeneral[iSlide].Device.qstrFolderOutput                         = json["left_outputfolder"].toString().trimmed();
            mGeneral[iSlide].Device.qstrFolderPhone                          = json["left_phonefolder"].toString().trimmed();

            mGeneral[iSlide].Device.ipModel                                  = json["left_model"].toInt();

            mGeneral[iSlide].Device.bUsecomIO                                = json["left_usecomIO"].toBool();
            mGeneral[iSlide].Device.qstrComIO                                = json["left_comIO"].toString().trimmed();

            /*com socket 1 - Device*/
            QString qstrCurComSocket1                                        = json["left_comSK"].toString().trimmed();
            if(!qstrCurComSocket1.contains(mGeneral[iSlide].Device.qstrComport)) {
                bool bCloseCom                                               = CloseCom(qspAuComport[SIDE_LEFT]);
                if(bCloseCom){
                    mGeneral[iSlide].Device.qstrComport                      = qstrCurComSocket1;
                    QString a                                                = QString("Close old comport socket Left = %1\r\nUpdate new comport %2").arg(bCloseCom).arg(qstrCurComSocket1);
                    QMessageBox::information(this,"Update Com socket Left", a);
                }
                else {
                    QMessageBox::warning(this,"Update Com socket Left", "Can't close old comport\r\nCan't update new com");
                }
            }
            mGeneral[iSlide].Device.qstrComport                              = qstrCurComSocket1;
        }
        else {
            mGeneral[iSlide].Device.bUse                                     = json["right_useSK"].toBool();
            mGeneral[iSlide].Device.qstrID                                   = json["right_id"].toString();
            mGeneral[iSlide].Device.qstrKeyStart                             = json["right_keystart"].toString();
            mGeneral[iSlide].Device.qstrKeyStop                              = "ESC";
            mGeneral[iSlide].Device.qstrFolderInput                          = json["right_inputfolder"].toString();
            mGeneral[iSlide].Device.qstrFolderOutput                         = json["right_outputfolder"].toString();
            mGeneral[iSlide].Device.qstrFolderPhone                          = json["right_phonefolder"].toString();
            mGeneral[iSlide].Device.ipModel                                  = json["right_model"].toInt();
            mGeneral[iSlide].Device.bUsecomIO                                = json["right_usecomIO"].toBool();
            mGeneral[iSlide].Device.qstrComIO                                = json["right_comIO"].toString().trimmed();
//            if(!qstrCurComIO_Device.contains(mGeneral[iSlide].Device.qstrComIO)) {
//                bool bCloseComIO                                = CloseCom(qspAuComIO[SIDE_RIGHT]);
//                if(bCloseComIO){
//                    mGeneral[iSlide].Device.qstrComIO           = qstrCurComIO_Device;
//                    QString a                                   = QString("Close old comport IO Right = %1\r\nUpdate new comport %2").arg(bCloseComIO).arg(qstrCurComIO_Device);
//                    QMessageBox::information(this,"Update Com IO Right", a);
//                }
//                else {
//                    QMessageBox::warning(this,"Update Com IO Right", "Can't close old comport\r\nCan't update new com");
//                }
//            }
//            mGeneral[iSlide].Device.qstrComIO                                = qstrCurComIO_Device;
            /*com socket 2 - Device*/
            QString qstrCurComSocket2                                        = json["right_comSK"].toString().trimmed();
            if(!qstrCurComSocket2.contains(mGeneral[iSlide].Device.qstrComport)) {
                bool bCloseCom                                                = CloseCom(qspAuComport[SIDE_RIGHT]);
                if(bCloseCom){
                    mGeneral[iSlide].Device.qstrComport                       = qstrCurComSocket2;
                    QString a                                                 = QString("Close old comport socket Right = %1\r\nUpdate new comport %2").arg(bCloseCom).arg(qstrCurComSocket2);
                    QMessageBox::information(this,"Update Com socket Right", a);
                }
                else {
                    QMessageBox::warning(this,"Update Com socket Right", "Can't close old comport\r\nCan't update new com");
                }
            }
            mGeneral[iSlide].Device.qstrComport                              = qstrCurComSocket2;
        }

        LoadBufferDataParaCheck(iSlide,mGeneral[iSlide].Device.ipModel);
    }
    catch(Exception &e){
        QString qstrerror = QString::fromStdString(e.what());
        qDebug()<<"[LoadGeneralPara2Buffer]"<<qstrerror;
        QMessageBox::warning(this,"Error",qstrerror);
    }
}
void MainWindow::LoadBufferDataParaCheck(int iSlide, int iIdxModel) {
    try{
          int iTypeCam = NUM_CAM;

              if(iIdxModel < G975){
                iTypeCam = 1;

                if(bLoadParaFirst){
                    if(iSlide == SIDE_LEFT){
                        m_ComboBox[CAMERA_TYPE]->setEnabled(false);
                    }
                }
                else{
                    m_ComboBox[CAMERA_TYPE]->setEnabled(false);
                }

            }
            else{
                m_ComboBox[CAMERA_TYPE]->setEnabled(true);
            }

        /*Load json file*/
        QJsonDocument loadData                                               = loadJson(tr(PATH_GENERAL).arg(listModel[iIdxModel]) + PATH_NAME);
        QJsonObject   json                                                   = loadData.object();




        for(int iCam = FW1; iCam < iTypeCam; iCam++){
            QString qstrKeyShowImg                                           = tr("opt_showimg_%1").arg(iCam);
            QString qstrKeySaveImg                                           = tr("opt_saveimg_%1").arg(iCam);
            QString qstrKeyCheckIris                                         = tr("opt_checkiris");
            QString qstrKeyCheckStain                                        = tr("opt_checkstain_%1").arg(iCam);
            QString qstrKeyCheckWhiteStain                                   = tr("opt_checkwhitestain_%1").arg(iCam);
            QString qstrKeyCheckGlare                                        = tr("opt_checkglare_%1").arg(iCam);
            QString qstrKeyCheckFocus                                        = tr("opt_checkfocus_%1").arg(iCam);
            QString qstrKeyCheckColor                                        = tr("opt_checkcolor_%1").arg(iCam);
            QString qstrKeyCheckDarkSort                                     = tr("opt_checkdarksport_%1").arg(iCam);
            QString qstrKeyCaptureAf                                         = tr("opt_captureaf_%1").arg(iCam);

            mGeneral[iSlide].bOptShowImg[iCam]                               = json[qstrKeyShowImg].toBool();
            mGeneral[iSlide].bOptSaveImg[iCam]                               = json[qstrKeySaveImg].toBool();
            mGeneral[iSlide].bOptCheckIris                                   = json[qstrKeyCheckIris].toBool();
            mGeneral[iSlide].bOptCheckStain[iCam]                            = json[qstrKeyCheckStain].toBool();
            mGeneral[iSlide].bOptCheckWhiteStain[iCam]                       = json[qstrKeyCheckWhiteStain].toBool();
            mGeneral[iSlide].bOptCheckGlare[iCam]                            = json[qstrKeyCheckGlare].toBool();
            mGeneral[iSlide].bOptCheckFocus[iCam]                            = json[qstrKeyCheckFocus].toBool();
            mGeneral[iSlide].bOptCheckColor[iCam]                            = json[qstrKeyCheckColor].toBool();
            mGeneral[iSlide].bOptDarkSport[iCam]                             = json[qstrKeyCheckDarkSort].toBool();
            mGeneral[iSlide].bOptCaptrueAf[iCam]                             = json[qstrKeyCaptureAf].toBool();
            for(int iDelayNo = DL_UART_USB_SEND; iDelayNo < NUM_DELAY; iDelayNo++){
                mGeneral[iSlide].dbDelay[iDelayNo]                           = QString2Double(json[tr("delay_%1").arg(iDelayNo)].toString());
            }
            /*Paint*/
            mGeneral[iSlide].ipPaintThickness                                = QString2Int(json[tr("com_thickness")].toString());
            mGeneral[iSlide].ipPaintOffset                                   = QString2Int(json[tr("com_offset")].toString());
            /*Normalize*/
            mGeneral[iSlide].ipNormType[iCam]                                = QString2Int(json[tr("nor_type_%1").arg(iCam)].toString());
            mGeneral[iSlide].ipNormBeta[iCam]                                = QString2Int(json[tr("nor_beta_%1").arg(iCam)].toString());
            mGeneral[iSlide].ipNormAlpha[iCam]                               = QString2Int(json[tr("nor_alpha_%1").arg(iCam)].toString());

            LoadBufferParameterStain     (iSlide, iCam, json);
            LoadBufferParameterWhiteStain(iSlide, iCam, json);
            LoadBufferParameterGlare     (iSlide, iCam, json);
            LoadBufferParameterFocus     (iSlide, iCam, json);
            LoadBufferParameterDarkSport (iSlide, iCam, json);
            LoadBufferParameterWrongColor(iSlide, iCam, json);       
        }

        LoadBufferParameterATCommand(iSlide, json);
          LoadBufferParameterADBCommand(iSlide, json);
    }
    catch(Exception &e){
        QString qstrerror = QString::fromStdString(e.what());
        qDebug()<<"[LoadCameraParaCheck]"<<qstrerror;
        QMessageBox::warning(this,"Error",qstrerror);
    }
}
void MainWindow::LoadBufferParameterStain(int iSlide, int iCam, QJsonObject json) {
    try{
        for( int iTypeSize = TYPE_SIZE_SMALL; iTypeSize < NUM_TYPE; iTypeSize++) {
            /*Threshould*/
            mGeneral[iSlide].spStain[iCam].ipThreshold[iTypeSize]        = QString2Int(json[tr("stain_threshold_%1_%2").arg(iCam).arg(iTypeSize)].toString());
            /*BlockSize*/
            mGeneral[iSlide].spStain[iCam].ipBlockSize[iTypeSize]        = QString2Int(json[tr("stain_block_size_%1_%2").arg(iCam).arg(iTypeSize)].toString());
            if(mGeneral[iSlide].spStain[iCam].ipBlockSize[iTypeSize] %2  == 0){
                mGeneral[iSlide].spStain[iCam].ipBlockSize[iTypeSize]    -= 1;
            }
            /*Blur*/
            mGeneral[iSlide].spStain[iCam].ipBlurSize[iTypeSize]         = QString2Int(json[tr("stain_blur_size_%1_%2").arg(iCam).arg(iTypeSize)].toString());
            if(mGeneral[iSlide].spStain[iCam].ipBlurSize[iTypeSize] %2   == 0){
                mGeneral[iSlide].spStain[iCam].ipBlurSize[iTypeSize]     -= 1;
            }
            /*Erode*/
            mGeneral[iSlide].spStain[iCam].ipErodeSize[iTypeSize]        = QString2Int(json[tr("stain_erode_size_%1_%2").arg(iCam).arg(iTypeSize)].toString());
            if(mGeneral[iSlide].spStain[iCam].ipErodeSize[iTypeSize] %2  == 0){
                mGeneral[iSlide].spStain[iCam].ipErodeSize[iTypeSize]    -= 1;
            }
            mGeneral[iSlide].spStain[iCam].ipErodeLoop[iTypeSize]        = QString2Int(json[tr("stain_erode_loop_%1_%2").arg(iCam).arg(iTypeSize)].toString());
            /*Dilate*/
            mGeneral[iSlide].spStain[iCam].ipDilateSize[iTypeSize]       = QString2Int(json[tr("stain_dilate_size_%1_%2").arg(iCam).arg(iTypeSize)].toString());
            if(mGeneral[iSlide].spStain[iCam].ipDilateSize[iTypeSize] %2 == 0){
                mGeneral[iSlide].spStain[iCam].ipDilateSize[iTypeSize]   -= 1;
            }
            mGeneral[iSlide].spStain[iCam].ipDilateLoop[iTypeSize]       = QString2Int(json[tr("stain_dilate_loop_%1_%2").arg(iCam).arg(iTypeSize)].toString());
            /*Remove: Conner, Edge*/
            mGeneral[iSlide].spStain[iCam].ipRemoveConner[iTypeSize]     = QString2Int(json[tr("stain_remove_edge_%1_%2").arg(iCam).arg(iTypeSize)].toString());
            mGeneral[iSlide].spStain[iCam].ipRemoveEdge[iTypeSize]       = QString2Int(json[tr("stain_remove_conner_%1_%2").arg(iCam).arg(iTypeSize)].toString());
            /*Filter: area, width, height*/
            QString strArea  = json[tr("stain_filter_area_%1_%2").arg(iCam).arg(iTypeSize)].toString();
            Point   pArea    = QString2Point(strArea);
            mGeneral[iSlide].spStain[iCam].ipFilterAreaMin[iTypeSize]    = pArea.x;
            mGeneral[iSlide].spStain[iCam].ipFilterAreaMax[iTypeSize]    = pArea.y;

            QString strWidth  = json[tr("stain_filter_width_%1_%2").arg(iCam).arg(iTypeSize)].toString();
            Point   pWidth    = QString2Point(strWidth);
            mGeneral[iSlide].spStain[iCam].ipFilterWMin[iTypeSize]       = pWidth.x;
            mGeneral[iSlide].spStain[iCam].ipFilterWMax[iTypeSize]       = pWidth.y;

            QString strHeight  = json[tr("stain_filter_height_%1_%2").arg(iCam).arg(iTypeSize)].toString();
            Point   pheight    = QString2Point(strHeight);
            mGeneral[iSlide].spStain[iCam].ipFilterHMin[iTypeSize]       = pheight.x;
            mGeneral[iSlide].spStain[iCam].ipFilterHMax[iTypeSize]       = pheight.y;
        }
    }
    catch(QException &e) {
        QString strerror = QString::fromStdString(e.what());
        qDebug()<<"[LoadParaStain]"<<strerror;
        QMessageBox::warning(this,"Error",strerror);
    }
}
void MainWindow::LoadBufferParameterWhiteStain(int iSlide, int iCam, QJsonObject json) {
    try{
        for( int iTypeSize = TYPE_SIZE_SMALL; iTypeSize < NUM_TYPE; iTypeSize++) {
            /*Threshould*/
            mGeneral[iSlide].spWhiteStain[iCam].ipThreshold[iTypeSize]        = QString2Int(json[tr("wstain_threshold_%1_%2").arg(iCam).arg(iTypeSize)].toString());
            /*BlockSize*/
            mGeneral[iSlide].spWhiteStain[iCam].ipBlockSize[iTypeSize]        = QString2Int(json[tr("wstain_block_size_%1_%2").arg(iCam).arg(iTypeSize)].toString());
            if(mGeneral[iSlide].spWhiteStain[iCam].ipBlockSize[iTypeSize] %2  == 0){
                mGeneral[iSlide].spWhiteStain[iCam].ipBlockSize[iTypeSize]    -= 1;
            }
            /*Blur*/
            mGeneral[iSlide].spWhiteStain[iCam].ipBlurSize[iTypeSize]         = QString2Int(json[tr("wstain_blur_size_%1_%2").arg(iCam).arg(iTypeSize)].toString());
            if(mGeneral[iSlide].spWhiteStain[iCam].ipBlurSize[iTypeSize] %2   == 0){
                mGeneral[iSlide].spWhiteStain[iCam].ipBlurSize[iTypeSize]     -= 1;
            }
            /*Erode*/
            mGeneral[iSlide].spWhiteStain[iCam].ipErodeSize[iTypeSize]        = QString2Int(json[tr("wstain_erode_size_%1_%2").arg(iCam).arg(iTypeSize)].toString());
            if(mGeneral[iSlide].spWhiteStain[iCam].ipErodeSize[iTypeSize] %2  == 0){
                mGeneral[iSlide].spWhiteStain[iCam].ipErodeSize[iTypeSize]    -= 1;
            }
            mGeneral[iSlide].spWhiteStain[iCam].ipErodeLoop[iTypeSize]        = QString2Int(json[tr("wstain_erode_loop_%1_%2").arg(iCam).arg(iTypeSize)].toString());
            /*Dilate*/
            mGeneral[iSlide].spWhiteStain[iCam].ipDilateSize[iTypeSize]       = QString2Int(json[tr("wstain_dilate_size_%1_%2").arg(iCam).arg(iTypeSize)].toString());
            if(mGeneral[iSlide].spWhiteStain[iCam].ipDilateSize[iTypeSize] %2 == 0){
                mGeneral[iSlide].spWhiteStain[iCam].ipDilateSize[iTypeSize]   -= 1;
            }
            mGeneral[iSlide].spWhiteStain[iCam].ipDilateLoop[iTypeSize]       = QString2Int(json[tr("wstain_dilate_loop_%1_%2").arg(iCam).arg(iTypeSize)].toString());
            /*Remove: Conner, Edge*/
            mGeneral[iSlide].spWhiteStain[iCam].ipRemoveConner[iTypeSize]     = QString2Int(json[tr("wstain_remove_edge_%1_%2").arg(iCam).arg(iTypeSize)].toString());
            mGeneral[iSlide].spWhiteStain[iCam].ipRemoveEdge[iTypeSize]       = QString2Int(json[tr("wstain_remove_conner_%1_%2").arg(iCam).arg(iTypeSize)].toString());
            /*Filter: area, width, height*/
            QString strArea  = json[tr("wstain_filter_area_%1_%2").arg(iCam).arg(iTypeSize)].toString();
            Point   pArea   = QString2Point(strArea);
            mGeneral[iSlide].spWhiteStain[iCam].ipFilterAreaMin[iTypeSize]    = pArea.x;
            mGeneral[iSlide].spWhiteStain[iCam].ipFilterAreaMax[iTypeSize]    = pArea.y;

            QString strWidth  = json[tr("wstain_filter_width_%1_%2").arg(iCam).arg(iTypeSize)].toString();
            Point   pWidth    = QString2Point(strWidth);
            mGeneral[iSlide].spWhiteStain[iCam].ipFilterWMin[iTypeSize]       = pWidth.x;
            mGeneral[iSlide].spWhiteStain[iCam].ipFilterWMax[iTypeSize]       = pWidth.y;

            QString strHeight  = json[tr("wstain_filter_height_%1_%2").arg(iCam).arg(iTypeSize)].toString();
            Point   pheight    = QString2Point(strHeight);
            mGeneral[iSlide].spWhiteStain[iCam].ipFilterHMin[iTypeSize]       = pheight.x;
            mGeneral[iSlide].spWhiteStain[iCam].ipFilterHMax[iTypeSize]       = pheight.y;
        }
    }
    catch(QException &e) {
        QString strerror = QString::fromStdString(e.what());
        qDebug()<<"[LoadParaWhiteStain]"<<strerror;
        QMessageBox::warning(this,"Error",strerror);
    }
}
void MainWindow::LoadBufferParameterGlare(int iSlide, int iCam, QJsonObject json) {

    for(int i = 0 ; i<NUM_ROI; i++){
        /*Threshold*/
        mGeneral[iSlide].spGlare[iCam].ipgThreshold[i]             =  QString2Int(json[tr("glare_threshold%2_%1").arg(iCam).arg(i+1)].toString());
        /*BlurSize*/
        mGeneral[iSlide].spGlare[iCam].ipgBlurSize[i]              =  QString2Int(json[tr("glare_blur_size%2_%1").arg(iCam).arg(i+1)].toString());
        if( mGeneral[iSlide].spGlare[iCam].ipgBlurSize[i] %2       == 0){
            mGeneral[iSlide].spGlare[iCam].ipgBlurSize[i]         -=  1;
        }
        /*Crop RoiCheck*/
        QString strRoi                                         = json[tr("glare_roicheck%2_%1").arg(iCam).arg(i+1)].toString();
        mGeneral[iSlide].spGlare[iCam].rpRoi[i]                 = QString2Rect(strRoi);
        /*Erode*/
        mGeneral[iSlide].spGlare[iCam].ipgErodeSize[i]             = QString2Int(json[tr("glare_erode_size%2_%1").arg(iCam).arg(i+1)].toString());
        if(mGeneral[iSlide].spGlare[iCam].ipgErodeSize[i] %2       ==0){
            mGeneral[iSlide].spGlare[iCam].ipgErodeSize[i]        -= 1;
        }
        mGeneral[iSlide].spGlare[iCam].ipgErodeLoop[i]             = QString2Int(json[tr("glare_erode_loop%2_%1").arg(iCam).arg(i+1)].toString());
        /*Dilate*/
        mGeneral[iSlide].spGlare[iCam].ipgDilateSize[i]            = QString2Int(json[tr("glare_dilate_size%2_%1").arg(iCam).arg(i+1)].toString());
        if(mGeneral[iSlide].spGlare[iCam].ipgDilateSize[i] %2      ==0){
            mGeneral[iSlide].spGlare[iCam].ipgDilateSize[i]       -= 1;
        }
        mGeneral[iSlide].spGlare[iCam].ipgDilateLoop[i]            = QString2Int(json[tr("glare_dilate_loop%2_%1").arg(iCam).arg(i+1)].toString());
        /*Remove*/
        mGeneral[iSlide].spGlare[iCam].ipgRemoveEdge[i]            = QString2Int(json[tr("glare_remove_edge%2_%1").arg(iCam).arg(i+1)].toString());
        mGeneral[iSlide].spGlare[iCam].ipgRemoveConner[i]          = QString2Int(json[tr("glare_remove_conner%2_%1").arg(iCam).arg(i+1)].toString());
        /*Filter with M: mean */
        QString strMeanRoi                                     = json[tr("glare_roicheck%2_%1").arg(iCam).arg(i+1)].toString();

        Point pMeanRoi                                         = QString2Point(strMeanRoi);

        mGeneral[iSlide].spGlare[iCam].ipgMSRoiMin[i]           = pMeanRoi.x;
        mGeneral[iSlide].spGlare[iCam].ipgMSRoiMax[i]           = pMeanRoi.y;

        /*Filter with area, width, height*/
        QString strArea                                         = json[tr("glare_filter_area%2_%1").arg(iCam).arg(i+1)].toString();

        Point   pArea                                           = QString2Point(strArea);

        mGeneral[iSlide].spGlare[iCam].ipgFilterAreaMin[i]       = pArea.x;
        mGeneral[iSlide].spGlare[iCam].ipgFilterAreaMax[i]       = pArea.y;

        QString strWidth                                        = json[tr("glare_filter_width%2_%1").arg(iCam).arg(i+1)].toString();

        Point   pWidth                                          = QString2Point(strWidth);

        mGeneral[iSlide].spGlare[iCam].ipgFilterWMin[i]          = pWidth.x;
        mGeneral[iSlide].spGlare[iCam].ipgFilterWMax[i]          = pWidth.y;

        QString strHeight                                       = json[tr("glare_filter_height%2_%1").arg(iCam).arg(i+1)].toString();

        Point   pHeight                                         = QString2Point(strHeight);

        mGeneral[iSlide].spGlare[iCam].ipgFilterHMin[i]            = pHeight.x;
        mGeneral[iSlide].spGlare[iCam].ipgFilterHMax[i]            = pHeight.y;

    }

}
void MainWindow::LoadBufferParameterFocus(int iSlide, int iCam, QJsonObject json) {
    /*Crop RoiCheck*/
    QString strRoi1                                         = json[tr("focus_roicheck1_%1").arg(iCam)].toString();
    QString strRoi2                                         = json[tr("focus_roicheck2_%1").arg(iCam)].toString();
    QString strRoi3                                         = json[tr("focus_roicheck3_%1").arg(iCam)].toString();
    QString strRoi4                                         = json[tr("focus_roicheck4_%1").arg(iCam)].toString();
    QString strRoi5                                         = json[tr("focus_roicheck5_%1").arg(iCam)].toString();
    QString strRoi6                                         = json[tr("focus_roicheck6_%1").arg(iCam)].toString();
    mGeneral[iSlide].spFocus[iCam].rpRoi[0]                 = QString2Rect(strRoi1);
    mGeneral[iSlide].spFocus[iCam].rpRoi[1]                 = QString2Rect(strRoi2);
    mGeneral[iSlide].spFocus[iCam].rpRoi[2]                 = QString2Rect(strRoi3);
    mGeneral[iSlide].spFocus[iCam].rpRoi[3]                 = QString2Rect(strRoi4);
    mGeneral[iSlide].spFocus[iCam].rpRoi[4]                 = QString2Rect(strRoi5);
    mGeneral[iSlide].spFocus[iCam].rpRoi[5]                 = QString2Rect(strRoi6);
    /*Filter with S: std */
    QString strStdRoi1                                      = json[tr("focus_stdroi1_%1").arg(iCam)].toString();
    QString strStdRoi2                                      = json[tr("focus_stdroi2_%1").arg(iCam)].toString();
    QString strStdRoi3                                      = json[tr("focus_stdroi3_%1").arg(iCam)].toString();
    QString strStdRoi4                                      = json[tr("focus_stdroi4_%1").arg(iCam)].toString();
    QString strStdRoi5                                      = json[tr("focus_stdroi5_%1").arg(iCam)].toString();
    QString strStdRoi6                                      = json[tr("focus_stdroi6_%1").arg(iCam)].toString();

    Point pStdRoi1                                          = QString2Point(strStdRoi1);
    Point pStdRoi2                                          = QString2Point(strStdRoi2);
    Point pStdRoi3                                          = QString2Point(strStdRoi3);
    Point pStdRoi4                                          = QString2Point(strStdRoi4);
    Point pStdRoi5                                          = QString2Point(strStdRoi5);
    Point pStdRoi6                                          = QString2Point(strStdRoi6);

    mGeneral[iSlide].spFocus[iCam].ipgMSRoiMin[0]           = pStdRoi1.x;
    mGeneral[iSlide].spFocus[iCam].ipgMSRoiMax[0]           = pStdRoi1.y;
    mGeneral[iSlide].spFocus[iCam].ipgMSRoiMin[1]           = pStdRoi2.x;
    mGeneral[iSlide].spFocus[iCam].ipgMSRoiMax[1]           = pStdRoi2.y;
    mGeneral[iSlide].spFocus[iCam].ipgMSRoiMin[2]           = pStdRoi3.x;
    mGeneral[iSlide].spFocus[iCam].ipgMSRoiMax[2]           = pStdRoi3.y;
    mGeneral[iSlide].spFocus[iCam].ipgMSRoiMin[3]           = pStdRoi4.x;
    mGeneral[iSlide].spFocus[iCam].ipgMSRoiMax[3]           = pStdRoi4.y;
    mGeneral[iSlide].spFocus[iCam].ipgMSRoiMin[4]           = pStdRoi5.x;
    mGeneral[iSlide].spFocus[iCam].ipgMSRoiMax[4]           = pStdRoi5.y;
    mGeneral[iSlide].spFocus[iCam].ipgMSRoiMin[5]           = pStdRoi6.x;
    mGeneral[iSlide].spFocus[iCam].ipgMSRoiMax[5]           = pStdRoi6.y;
}
void MainWindow::LoadBufferParameterDarkSport(int iSlide, int iCam, QJsonObject json) {
    /*Threshold*/
    mGeneral[iSlide].spDarksport[iCam].ipdsThreshold          = QString2Int(json[tr("darksport_threshold_%1").arg(iCam)].toString());
    /*BlockSize*/
    mGeneral[iSlide].spDarksport[iCam].ipdsBlockSize          = QString2Int(json[tr("darksport_blocksize_%1").arg(iCam)].toString());
    if(mGeneral[iSlide].spDarksport[iCam].ipdsBlockSize %2    ==0){
        mGeneral[iSlide].spDarksport[iCam].ipdsBlockSize     -= 1;
    }
    /*FilterArea*/
    QString strAreaDarkspot                                   = json[tr("darksport_filtarea_%1").arg(iCam)].toString();
    Point pAreaDarkspot                                       = QString2Point(strAreaDarkspot);
    mGeneral[iSlide].spDarksport[iCam].ipdsFilterAreaMin      = pAreaDarkspot.x;
    mGeneral[iSlide].spDarksport[iCam].ipdsFilterAreaMax      = pAreaDarkspot.y;

}
void MainWindow::LoadBufferParameterWrongColor(int iSlide, int iCam, QJsonObject json)     {
    /*Wrong Color: RGB*/
    QString strRed                                           = json[tr("wrongcolor_meanred_%1").arg(iCam)].toString();
    Point pRed                                               = QString2Point(strRed);
    mGeneral[iSlide].spWrongColor[iCam].ipwcMeanRedMin       = pRed.x;
    mGeneral[iSlide].spWrongColor[iCam].ipwcMeanRedMax       = pRed.y;

    QString strGreen                                         = json[tr("wrongcolor_meangreen_%1").arg(iCam)].toString();
    Point pGreen                                             = QString2Point(strGreen);
    mGeneral[iSlide].spWrongColor[iCam].ipwcMeanGreenMin     = pGreen.x;
    mGeneral[iSlide].spWrongColor[iCam].ipwcMeanGreenMax     = pGreen.y;

    QString strBlue                                          = json[tr("wrongcolor_meanblue_%1").arg(iCam)].toString();
    Point pBlue                                              = QString2Point(strBlue);
    mGeneral[iSlide].spWrongColor[iCam].ipwcMeanBlueMin      = pBlue.x;
    mGeneral[iSlide].spWrongColor[iCam].ipwcMeanBlueMax      = pBlue.y;
}
void MainWindow::LoadBufferParameterATCommand(int iSlide, QJsonObject json) {
    try{
        /*UART USB*/
        mGeneral[iSlide].ATCMD[AT_UART_USB].iStatus     = RES_NONE;
        mGeneral[iSlide].ATCMD[AT_UART_USB].send        = json["atcommand_uartusb_send"].toString();
        mGeneral[iSlide].ATCMD[AT_UART_USB].respone     = json["atcommand_uartusb_respone"].toString();
        mGeneral[iSlide].ATCMD[AT_UART_USB].dDelay_Send = mGeneral[iSlide].dbDelay[DL_UART_USB_SEND];
        mGeneral[iSlide].ATCMD[AT_UART_USB].dDelay_Wait = mGeneral[iSlide].dbDelay[DL_UART_USB_RESPONE];

        /*HOME SCREEN*/
        mGeneral[iSlide].ATCMD[AT_HOMECREEN].iStatus     = RES_NONE;
        mGeneral[iSlide].ATCMD[AT_HOMECREEN].send        = json["atcommand_homescreen_send"].toString();
        mGeneral[iSlide].ATCMD[AT_HOMECREEN].respone     = json["atcommand_homescreen_respone"].toString();
        mGeneral[iSlide].ATCMD[AT_HOMECREEN].dDelay_Send = mGeneral[iSlide].dbDelay[DL_HOME_SCREEN_SEND];
        mGeneral[iSlide].ATCMD[AT_HOMECREEN].dDelay_Wait = mGeneral[iSlide].dbDelay[DL_HOME_SCREEN_RESPONE];

        /*OPEN IRIS*/
        mGeneral[iSlide].ATCMD[AT_OPENIRIS].iStatus     = RES_NONE;
        mGeneral[iSlide].ATCMD[AT_OPENIRIS].send        = json["atcommand_openiris_send"].toString();
        mGeneral[iSlide].ATCMD[AT_OPENIRIS].respone     = json["atcommand_openiris_respone"].toString();
        mGeneral[iSlide].ATCMD[AT_OPENIRIS].dDelay_Send = mGeneral[iSlide].dbDelay[DL_OPEN_IRIS_SEND];
        mGeneral[iSlide].ATCMD[AT_OPENIRIS].dDelay_Wait = mGeneral[iSlide].dbDelay[DL_OPEN_IRIS_RESPONE];

        /*CLOSE IRIS*/
        mGeneral[iSlide].ATCMD[AT_CLOSEIRIS].iStatus     = RES_NONE;
        mGeneral[iSlide].ATCMD[AT_CLOSEIRIS].send        = json["atcommand_closeiris_send"].toString();
        mGeneral[iSlide].ATCMD[AT_CLOSEIRIS].respone     = json["atcommand_closeiris_respone"].toString();
        mGeneral[iSlide].ATCMD[AT_CLOSEIRIS].dDelay_Send = mGeneral[iSlide].dbDelay[DL_CLOSE_IRIS_SEND];
        mGeneral[iSlide].ATCMD[AT_CLOSEIRIS].dDelay_Wait = mGeneral[iSlide].dbDelay[DL_CLOSE_IRIS_RESPONE];

        /*OPEN FW1*/
        mGeneral[iSlide].ATCMD[AT_OPENFW1].iStatus     = RES_NONE;
        mGeneral[iSlide].ATCMD[AT_OPENFW1].send        = json["atcommand_openfw1_send"].toString();
        mGeneral[iSlide].ATCMD[AT_OPENFW1].respone     = json["atcommand_openfw1_respone"].toString();
        mGeneral[iSlide].ATCMD[AT_OPENFW1].dDelay_Send = mGeneral[iSlide].dbDelay[DL_OPEN_FW1_SEND];
        mGeneral[iSlide].ATCMD[AT_OPENFW1].dDelay_Wait = mGeneral[iSlide].dbDelay[DL_OPEN_FW1_RESPONE];

        /*CLOSE FW1*/
        mGeneral[iSlide].ATCMD[AT_CLOSEFW1].iStatus     = RES_NONE;
        mGeneral[iSlide].ATCMD[AT_CLOSEFW1].send        = json["atcommand_closefw1_send"].toString();
        mGeneral[iSlide].ATCMD[AT_CLOSEFW1].respone     = json["atcommand_closefw1_respone"].toString();
        mGeneral[iSlide].ATCMD[AT_CLOSEFW1].dDelay_Send = mGeneral[iSlide].dbDelay[DL_CLOSE_FW1_SEND];
        mGeneral[iSlide].ATCMD[AT_CLOSEFW1].dDelay_Wait = mGeneral[iSlide].dbDelay[DL_CLOSE_FW1_RESPONE];

        /*OPEN FB1*/
        mGeneral[iSlide].ATCMD[AT_OPENFB1].iStatus     = RES_NONE;
        mGeneral[iSlide].ATCMD[AT_OPENFB1].send        = json["atcommand_openfb1_send"].toString();
        mGeneral[iSlide].ATCMD[AT_OPENFB1].respone     = json["atcommand_openfb1_respone"].toString();
        mGeneral[iSlide].ATCMD[AT_OPENFB1].dDelay_Send = mGeneral[iSlide].dbDelay[DL_OPEN_FB1_SEND];
        mGeneral[iSlide].ATCMD[AT_OPENFB1].dDelay_Wait = mGeneral[iSlide].dbDelay[DL_OPEN_FB1_RESPONE];

        /*CLOSE FB1*/
        mGeneral[iSlide].ATCMD[AT_CLOSEFB1].iStatus     = RES_NONE;
        mGeneral[iSlide].ATCMD[AT_CLOSEFB1].send        = json["atcommand_closefb1_send"].toString();
        mGeneral[iSlide].ATCMD[AT_CLOSEFB1].respone     = json["atcommand_closefb1_respone"].toString();
        mGeneral[iSlide].ATCMD[AT_CLOSEFB1].dDelay_Send = mGeneral[iSlide].dbDelay[DL_CLOSE_FB1_SEND];
        mGeneral[iSlide].ATCMD[AT_CLOSEFB1].dDelay_Wait = mGeneral[iSlide].dbDelay[DL_CLOSE_FB1_RESPONE];

        /*CAPTURE NOAF*/
        mGeneral[iSlide].ATCMD[AT_CAPTURENOAF].iStatus     = RES_NONE;
        mGeneral[iSlide].ATCMD[AT_CAPTURENOAF].send        = json["atcommand_capturenoaf_send"].toString();
        mGeneral[iSlide].ATCMD[AT_CAPTURENOAF].respone     = json["atcommand_capturenoaf_respone"].toString();
        mGeneral[iSlide].ATCMD[AT_CAPTURENOAF].dDelay_Send = mGeneral[iSlide].dbDelay[DL_CAPTURE_NOAF_SEND];
        mGeneral[iSlide].ATCMD[AT_CAPTURENOAF].dDelay_Wait = mGeneral[iSlide].dbDelay[DL_CAPTURE_NOAF_RESPONE];

        /*CAPTURE AF*/
        mGeneral[iSlide].ATCMD[AT_CAPTUREAF].iStatus     = RES_NONE;
        mGeneral[iSlide].ATCMD[AT_CAPTUREAF].send        = json["atcommand_captureaf_send"].toString();
        mGeneral[iSlide].ATCMD[AT_CAPTUREAF].respone     = json["atcommand_captureaf_respone"].toString();
        mGeneral[iSlide].ATCMD[AT_CAPTUREAF].dDelay_Send = mGeneral[iSlide].dbDelay[DL_CAPTURE_AF_SEND];
        mGeneral[iSlide].ATCMD[AT_CAPTUREAF].dDelay_Wait = mGeneral[iSlide].dbDelay[DL_CAPTURE_AF_RESPONE];

        /*CAPTURE TRYAF*/
        mGeneral[iSlide].ATCMD[AT_CAPTURETRYAF].iStatus     = RES_NONE;
        mGeneral[iSlide].ATCMD[AT_CAPTURETRYAF].send        = json["atcommand_capturetryaf_send"].toString();
        mGeneral[iSlide].ATCMD[AT_CAPTURETRYAF].respone     = json["atcommand_capturetryaf_respone"].toString();
        mGeneral[iSlide].ATCMD[AT_CAPTURETRYAF].dDelay_Send = mGeneral[iSlide].dbDelay[DL_CAPTURE_TRYAF_SEND];
        mGeneral[iSlide].ATCMD[AT_CAPTURETRYAF].dDelay_Wait = mGeneral[iSlide].dbDelay[DL_CAPTURE_TRYAF_RESPONE];
    }
    catch(Exception &e){

    }
}
void MainWindow::LoadBufferParameterADBCommand(int iSlide, QJsonObject json) {
    /*GET LIST*/
    mGeneral[iSlide].ADBCMD[ADB_GET_LIST].iStatus     = RES_NONE;
    mGeneral[iSlide].ADBCMD[ADB_GET_LIST].send        = (json["adbcommand_getlist_send"].toString()).arg(mGeneral[iSlide].Device.qstrID);
    mGeneral[iSlide].ADBCMD[ADB_GET_LIST].respone     = json["adbcommand_getlist_respone"].toString();
    mGeneral[iSlide].ADBCMD[ADB_GET_LIST].dDelay_Send = mGeneral[iSlide].dbDelay[DL_GET_LIST_SEND];
    mGeneral[iSlide].ADBCMD[ADB_GET_LIST].dDelay_Wait = mGeneral[iSlide].dbDelay[DL_GET_LIST_RESPONE];

    /*PULL 2 PC*/
    mGeneral[iSlide].ADBCMD[ADB_PULL_TO_PC].iStatus     = RES_NONE;
    mGeneral[iSlide].ADBCMD[ADB_PULL_TO_PC].send        = (json["adbcommand_pull2pc_send"].toString()).arg(mGeneral[iSlide].Device.qstrID).arg(mGeneral[iSlide].Device.qstrFolderInput);
    mGeneral[iSlide].ADBCMD[ADB_PULL_TO_PC].respone     = json["adbcommand_pull2pc_respone"].toString();
    mGeneral[iSlide].ADBCMD[ADB_PULL_TO_PC].dDelay_Send = mGeneral[iSlide].dbDelay[DL_PULL_2_PC_SEND];
    mGeneral[iSlide].ADBCMD[ADB_PULL_TO_PC].dDelay_Wait = mGeneral[iSlide].dbDelay[DL_PULL_2_PC_RESPONE];

    /*REMOVE FOLDER*/
    mGeneral[iSlide].ADBCMD[ADB_REMOVE_FOLDER].iStatus     = RES_NONE;
    mGeneral[iSlide].ADBCMD[ADB_REMOVE_FOLDER].send        = (json["adbcommand_removefolder_send"].toString()).arg(mGeneral[iSlide].Device.qstrID);
    mGeneral[iSlide].ADBCMD[ADB_REMOVE_FOLDER].respone     = json["adbcommand_removefolder_respone"].toString();
    mGeneral[iSlide].ADBCMD[ADB_REMOVE_FOLDER].dDelay_Send = mGeneral[iSlide].dbDelay[DL_REMOVE_FOLDER_SEND];
    mGeneral[iSlide].ADBCMD[ADB_REMOVE_FOLDER].dDelay_Wait = mGeneral[iSlide].dbDelay[DL_REMOVE_FOLDER_RESPONE];
}
void MainWindow::OnInitDlg() {
    /*Init gui */
    /*Connect button in auto*/
    connect(ui->btnStart,                       SIGNAL(clicked()),                     this, SLOT(ButtonProcess()));
    connect(ui->btnStop,                        SIGNAL(clicked()),                     this, SLOT(ButtonProcess()));
    connect(ui->btnInital,                      SIGNAL(clicked()),                     this, SLOT(ButtonProcess()));
    connect(ui->btnOpenLogFolder,               SIGNAL(clicked()),                     this, SLOT(ButtonProcess()));
    connect(ui->lblSk1_folderIn,                SIGNAL(clicked()),                     this, SLOT(ButtonProcess()));
    connect(ui->lblSk2_folderIn,                SIGNAL(clicked()),                     this, SLOT(ButtonProcess()));
    connect(ui->lblSk1_folderOut,               SIGNAL(clicked()),                     this, SLOT(ButtonProcess()));
    connect(ui->lblSk2_folderOut,               SIGNAL(clicked()),                     this, SLOT(ButtonProcess()));
    connect(ui->lblSk1_folderPhone,             SIGNAL(clicked()),                     this, SLOT(ButtonProcess()));
    connect(ui->lblSk2_folderPhone,             SIGNAL(clicked()),                     this, SLOT(ButtonProcess()));
    connect(ui->lblNameProject,                 SIGNAL(clicked()),                     this, SLOT(ButtonProcess()));
    connect(ui->btnLoad,                        SIGNAL(clicked()),                     this, SLOT(ButtonProcess()));
    connect(ui->btnCheckStain,                  SIGNAL(clicked()),                     this, SLOT(ButtonProcess()));
    connect(ui->btnCheckGlare,                  SIGNAL(clicked()),                     this, SLOT(ButtonProcess()));
    connect(ui->btnCheckWhiteStain,             SIGNAL(clicked()),                     this, SLOT(ButtonProcess()));
    connect(ui->btnCheckDarkspot,               SIGNAL(clicked()),                     this, SLOT(ButtonProcess()));
    connect(ui->btnCheckWrongColor,             SIGNAL(clicked()),                     this, SLOT(ButtonProcess()));
    connect(ui->btnOpenDebug,                   SIGNAL(clicked()),                     this, SLOT(ButtonProcess()));
    connect(ui->btnCheckFocus,                  SIGNAL(clicked()),                     this, SLOT(ButtonProcess()));
    connect(ui->tbwErrorLeft,                   SIGNAL(cellPressed(int, int)),         this, SLOT(tbwProcessLeft(int, int)));
    connect(ui->tbwErrorRight,                  SIGNAL(cellPressed(int, int)),         this, SLOT(tbwProcessRight(int, int)));
    connect(m_ComboBox[CAMERA_TYPE],            SIGNAL(currentIndexChanged(int)),      this, SLOT(on_cbbSelectParaCam_activated(int)));
    connect(m_ComboBox[STAIN_SIZE],             SIGNAL(currentIndexChanged(int)),      this, SLOT(on_cbbSizeStain_activated(int)));
    connect(m_ComboBox[WSTAIN_SIZE],            SIGNAL(currentIndexChanged(int)),      this, SLOT(on_cbbSizeWhiteStain_activated(int)));
    connect(m_ComboBox[ROI_GLARE],              SIGNAL(currentIndexChanged(int)),      this, SLOT(on_cbbRoiGlare_activated(int)));
    QObject::connect(ui->cbbListFunction,       SIGNAL(activated(int)),                this, SLOT(SelectCmd(int)));
    QObject::connect(ui->cbbListFunctionADB,    SIGNAL(activated(int)),                this, SLOT(SelectCmd(int)));
    connect(ui->btnSave,                        SIGNAL(clicked()),                     this, SLOT(ButtonProcess()));

    /*Connect button in teach*/
    ui->display->installEventFilter(this);


    qrPosDisp = ui->display->geometry();

    OnInitDlg_Auto();
    OnInitDlg_Teach();
    OnInitDlg_Manual();
}
void MainWindow::OnInitDlg_Auto() {
    //Zoom out scale
    ui->displayLeft->setScaledContents(true);
    ui->displayRight->setScaledContents(true);

    /**/
    int widthErrorLeft = ui->tbwErrorLeft->geometry().width();
    ui->tbwErrorLeft->setColumnCount(2);
    ui->tbwErrorLeft->setColumnWidth(0,widthErrorLeft/4-10);
    ui->tbwErrorLeft->setColumnWidth(1,3*widthErrorLeft/4-10);

    /**/
    int widthErrorRight = ui->tbwErrorRight->geometry().width();
    ui->tbwErrorRight->setColumnCount(2);
    ui->tbwErrorRight->setColumnWidth(0,widthErrorRight/4-10);
    ui->tbwErrorRight->setColumnWidth(1,3*widthErrorRight/4-10);

    /**/
    int widthLogLeft = ui->tbwLogLeft->geometry().width();
    ui->tbwLogLeft->setColumnCount(2);
    ui->tbwLogLeft->setColumnWidth(0,widthLogLeft/4-10);
    ui->tbwLogLeft->setColumnWidth(1,3*widthLogLeft/4-10);

    int widthLogRight = ui->tbwLogRight->geometry().width();
    ui->tbwLogRight->setColumnCount(2);
    ui->tbwLogRight->setColumnWidth(0,widthLogRight/4-10);
    ui->tbwLogRight->setColumnWidth(1,3*widthLogRight/4-10);

    QStringList strList;
    strList<<"Time"<<"Log Data";
    ui->tbwLogLeft->setHorizontalHeaderLabels(strList);
    ui->tbwLogLeft->verticalHeader()->setVisible(false);    // ẩn số thự tự dòng
    ui->tbwLogRight->setHorizontalHeaderLabels(strList);
    ui->tbwLogRight->verticalHeader()->setVisible(false);    // ẩn số thự tự dòng
}
void MainWindow::OnInitDlg_Teach() {
    /*Init Display*/
    ui->display->setScaledContents(true);
    ui->manualSimulation->setChecked(false);

    ui->progressBar->setValue(0);

    /*Log*/
    int widthTableRect = ui->tbwLogTestManual->geometry().width();

    ui->tbwLogTestManual->setColumnCount(2);
    ui->tbwLogTestManual->setColumnWidth(0, widthTableRect/1-10);
    ui->tbwLogTestManual->setColumnWidth(1,6*widthTableRect/1-10);

    QStringList strList;
    strList<<"No"<<"Data";
    ui->tbwLogTestManual->setHorizontalHeaderLabels(strList);
    ui->tbwLogTestManual->verticalHeader()->setVisible(false);    // ẩn số thự tự dòng
}
void MainWindow::OnInitDlg_Manual() {
    //comport
    qspSerial                                        = new QSerialPort(this);
    connect(qspSerial, &QSerialPort::errorOccurred,  this, &MainWindow::handleComportError);
    connect(qspSerial, &QSerialPort::readyRead,      this, &MainWindow::readDataComport);
    ConnectSignalObject();

    /*tbwReceiverDataCom*/
    int widthLog = ui->tbwReceiverDataCom->geometry().width();
    ui->tbwReceiverDataCom->setColumnCount(2);
    ui->tbwReceiverDataCom->setColumnWidth(0,widthLog/4-10);
    ui->tbwReceiverDataCom->setColumnWidth(1,3*widthLog/4-10);

    QStringList strList;
    strList<<"Time"<<"Log Data";
    ui->tbwReceiverDataCom->setHorizontalHeaderLabels(strList);
    ui->tbwReceiverDataCom->verticalHeader()->setVisible(false);    // ẩn số thự tự dòng

    //adb
    /*tbwReceiverDataCmd*/
    int widthDataCmd = ui->tbwReceiverDataCmd->geometry().width();
    ui->tbwReceiverDataCmd->setColumnCount(2);
    ui->tbwReceiverDataCmd->setColumnWidth(0,widthDataCmd/4-10);
    ui->tbwReceiverDataCmd->setColumnWidth(1,3*widthDataCmd/4-10);

    ui->tbwReceiverDataCmd->setHorizontalHeaderLabels(strList);
    ui->tbwReceiverDataCmd->verticalHeader()->setVisible(false);    // ẩn số thự tự dòng

    qpManADB = new QProcess();
    qpManADB->waitForFinished(5);
    QObject::connect(qpManADB, &QProcess::errorOccurred, this, &MainWindow::handleCmdError);
    QObject::connect(qpManADB, &QProcess::readyRead, this, &MainWindow::readDataCmd);
    qDebug("Init Manual Done");
    return;
}
void MainWindow::InitGUI(int iIdxPara) {
    /*general*/
    ui->edtVersion->setText(mGeneral[SIDE_LEFT].qstrVer);
    ui->edtFolderLog->setText(mGeneral[SIDE_LEFT].qstrFolderLog);
    ui->cbSaveImageResize->setChecked(mGeneral[PARA_CONTAIN].bOptSaveImageResize);
    /*socket - Device*/
    ui->checkBoxUseLeft->setChecked(mGeneral[SIDE_LEFT].Device.bUse);
    ui->edtComLeft->setText(mGeneral[SIDE_LEFT].Device.qstrComport);
    ui->edtIDLeft->setText(mGeneral[SIDE_LEFT].Device.qstrID);
    ui->edtKeyStartLeft->setText(mGeneral[SIDE_LEFT].Device.qstrKeyStart);
    ui->edtInputFolderLeft->setText(mGeneral[SIDE_LEFT].Device.qstrFolderInput);
    ui->edtOutputFolderLeft->setText(mGeneral[SIDE_LEFT].Device.qstrFolderOutput);
    ui->edtPhoneFolderLeft->setText(mGeneral[SIDE_LEFT].Device.qstrFolderPhone);
    ui->cbbSelectModel_Left->setCurrentIndex(mGeneral[SIDE_LEFT].Device.ipModel);
    ui->checkBoxUseComportIO_Left->setChecked(mGeneral[SIDE_LEFT].Device.bUsecomIO);
    ui->edtComportIO_Left->setText(mGeneral[SIDE_LEFT].Device.qstrComIO);
    /*socket - Device*/
    ui->checkBoxUseRight->setChecked(mGeneral[SIDE_RIGHT].Device.bUse);
    ui->edtComRight->setText(mGeneral[SIDE_RIGHT].Device.qstrComport);
    ui->edtIDRight->setText(mGeneral[SIDE_RIGHT].Device.qstrID);
    ui->edtKeyStartRight->setText(mGeneral[SIDE_RIGHT].Device.qstrKeyStart);
    ui->edtInputFolderRight->setText(mGeneral[SIDE_RIGHT].Device.qstrFolderInput);
    ui->edtOutputFolderRight->setText(mGeneral[SIDE_RIGHT].Device.qstrFolderOutput);
    ui->edtPhoneFolderRight->setText(mGeneral[SIDE_RIGHT].Device.qstrFolderPhone);
    ui->cbbSelectModel_Right->setCurrentIndex(mGeneral[SIDE_RIGHT].Device.ipModel);
    ui->checkBoxUseComportIO_Right->setChecked(mGeneral[SIDE_RIGHT].Device.bUsecomIO);
    ui->edtComportIO_Right->setText(mGeneral[SIDE_RIGHT].Device.qstrComIO);

    InitUiParameterCam(iIdxPara,FW1);

}
void MainWindow::InitProcCam()
{
    for(int i = 0; i < NUM_CAM; i++){
        if(pProc[i]                               != nullptr)
            delete pProc[i];
    }

    lMain[SIDE_LEFT].lbDisplay                    = ui->displayLeft;
    lMain[SIDE_LEFT].tbLog                        = ui->tbwLogLeft;
    lMain[SIDE_LEFT].tbError                      = ui->tbwErrorLeft;

    lDevPara[SIDE_LEFT].qspCom                    = qspAuComport[SIDE_LEFT];
    lDevPara[SIDE_LEFT].qpAuADB                   = qpAuADB[SIDE_LEFT];
    lDevPara[SIDE_LEFT].qstrFolderInput           = mGeneral[SIDE_LEFT].Device.qstrFolderInput;
    lDevPara[SIDE_LEFT].qstrFolderOutput          = mGeneral[SIDE_LEFT].Device.qstrFolderOutput;
    lDevPara[SIDE_LEFT].qstrFolderPhone           = mGeneral[SIDE_LEFT].Device.qstrFolderPhone;
    lDevPara[SIDE_LEFT].bUseComSocket                      = mGeneral[SIDE_LEFT].Device.bUse;
    lDevPara[SIDE_LEFT].qstrKeyStart              = mGeneral[SIDE_LEFT].Device.qstrKeyStart;
    lDevPara[SIDE_LEFT].qstrKeyStop               = mGeneral[SIDE_LEFT].Device.qstrKeyStop;
    lDevPara[SIDE_LEFT].qstrID                    = mGeneral[SIDE_LEFT].Device.qstrID;
    lDevPara[SIDE_LEFT].qstrComIO                 = mGeneral[SIDE_LEFT].Device.qstrComIO;
    lDevPara[SIDE_LEFT].bUseComIO                 = mGeneral[SIDE_LEFT].Device.bUsecomIO;
    lDevPara[SIDE_LEFT].ipModel                   = mGeneral[SIDE_LEFT].Device.ipModel;

    lMain[SIDE_RIGHT].lbDisplay                   = ui->displayRight;
    lMain[SIDE_RIGHT].tbLog                       = ui->tbwLogRight;
    lMain[SIDE_RIGHT].tbError                     = ui->tbwErrorRight;

    lDevPara[SIDE_RIGHT].qspCom                   = qspAuComport[SIDE_RIGHT];
    lDevPara[SIDE_RIGHT].qpAuADB                  = qpAuADB[SIDE_RIGHT];
    lDevPara[SIDE_RIGHT].qstrFolderInput          = mGeneral[SIDE_RIGHT].Device.qstrFolderInput;
    lDevPara[SIDE_RIGHT].qstrFolderOutput         = mGeneral[SIDE_RIGHT].Device.qstrFolderOutput;
    lDevPara[SIDE_RIGHT].qstrFolderPhone          = mGeneral[SIDE_RIGHT].Device.qstrFolderPhone;
    lDevPara[SIDE_RIGHT].bUseComSocket                     = mGeneral[SIDE_RIGHT].Device.bUse;
    lDevPara[SIDE_RIGHT].qstrKeyStart             = mGeneral[SIDE_RIGHT].Device.qstrKeyStart;
    lDevPara[SIDE_RIGHT].qstrKeyStop              = mGeneral[SIDE_RIGHT].Device.qstrKeyStop;
    lDevPara[SIDE_RIGHT].qstrID                   = mGeneral[SIDE_RIGHT].Device.qstrID;
    lDevPara[SIDE_RIGHT].qstrComIO                = mGeneral[SIDE_RIGHT].Device.qstrComIO;
    lDevPara[SIDE_RIGHT].bUseComIO                = mGeneral[SIDE_RIGHT].Device.bUsecomIO;
    lDevPara[SIDE_RIGHT].ipModel                  = mGeneral[SIDE_RIGHT].Device.ipModel;


    // creat process check camera
    for(int i = 0; i < NUM_CAM; i++){

        pProc[i] = new ProcessCam(lMain[i], lDevPara[i],i, mGeneral[i]);
    }
    QThread::msleep(100);

    m_ProcessCheckComIO->StartThread();
}
void MainWindow::InitComport() {
    if(m_ProcessCheckComIO->m_bRun)
        m_ProcessCheckComIO->StopThread();
    //close all comport
    if(CloseCom(qspAuComport[SIDE_LEFT]))
        qDebug("Close com Device ok");
    else
        qDebug("Close com Device ng");

    if(CloseCom(qspAuComport[SIDE_RIGHT]))
        qDebug("Close com Device ok");
    else
        qDebug("Close com Device ng");

    //close comport
    if(CloseCom(qspSerial))
        qDebug("Close com test ok");
    else
        qDebug("Close com test ng");


    /*com socket left*/
    if(!qspAuComport[SIDE_LEFT]->isOpen()) {
        if(OpenCom(qspAuComport[SIDE_LEFT],mGeneral[SIDE_LEFT].Device.qstrComport,1)){
            /*convert UART by USB*/
            qDebug()<<mGeneral[SIDE_LEFT].Device.qstrComport<<" open ok";
            SendCom(qspAuComport[SIDE_LEFT],"AT+SWATD=1");
        }
        else {
            qDebug()<<mGeneral[SIDE_LEFT].Device.qstrComport<<" open NG";
        }
    }
    else {
        qDebug()<<mGeneral[SIDE_LEFT].Device.qstrComport<<" was opened";
    }

    /*com socket right*/
    if(!qspAuComport[SIDE_RIGHT]->isOpen()) {
        if(OpenCom(qspAuComport[SIDE_RIGHT],mGeneral[SIDE_RIGHT].Device.qstrComport,1)){

            /*convert UART by USB*/
            qDebug()<<mGeneral[SIDE_RIGHT].Device.qstrComport<<" open ok";
            SendCom(qspAuComport[SIDE_RIGHT],"AT+SWATD=1");
        }
        else {
            qDebug()<<mGeneral[SIDE_RIGHT].Device.qstrComport<<" open NG";
        }

    }
    else {
        qDebug()<<mGeneral[SIDE_RIGHT].Device.qstrComport<<" was opened";
    }
}
void MainWindow::InitFolder() {
    try{
        for(int i = 0; i< NUM_SIDE; i++){
            qDebug()<<mGeneral[i].Device.qstrFolderInput;
            qDebug()<<mGeneral[i].Device.qstrFolderOutput;
            qDebug()<<mGeneral[i].Device.qstrFolderPhone;
            qDebug()<<mGeneral[i].qstrFolderLog;
            MakeFolder(mGeneral[i].Device.qstrFolderInput);
            MakeFolder(mGeneral[i].Device.qstrFolderOutput);
            MakeFolder(mGeneral[i].Device.qstrFolderPhone);
            MakeFolder(mGeneral[i].qstrFolderLog);
        }
        MakeFolder(PATH_DB_STAIN);
        MakeFolder(PATH_DB_WHITESTAIN);
        MakeFolder(PATH_DB_DARKSPOT);
        MakeFolder(PATH_DB_COLOR);
        MakeFolder(PATH_DB_GLARE);

    }
    catch(QException& e) {
        QString strerror = QString::fromStdString(e.what());
        qDebug()<<"[InitFolder Error]"<<strerror;

    }
}
void MainWindow::InitLogFile(int iSide) {
    qstrLogFile[iSide]       = QString(mGeneral[iSide].qstrFolderLog) + tr("/LogSocket%1_").arg(iSide+1) + qdCurTime.currentDateTime().toString("dd-MM-yyyy") + ".txt";
    QString strlogComIO      = QString(mGeneral[iSide].qstrFolderLog) + tr("/LogComIO%1_").arg(iSide+1) + qdCurTime.currentDateTime().toString("dd-MM-yyyy") + ".txt";
    qDebug()<<qstrLogFile[iSide];
    qfLog[iSide].setFileName(qstrLogFile[iSide]);
    if(qfLog[iSide].exists()) {
        qDebug()<< qstrLogFile[iSide] + "is exists" ;
        //open file
        if(qfLog[iSide].open(QIODevice::ReadWrite| QIODevice::Append | QIODevice::Text)){
            qDebug()<< "Open file: " + qstrLogFile[iSide] + " OK" ;
        }
        else{
            qDebug()<< "Open file: " + qstrLogFile[iSide] + " NG" ;
        }
    }
    else {
        //make file
        if(qfLog[iSide].open(QIODevice::ReadWrite| QIODevice::Append | QIODevice::Text)){
            qDebug()<< "Create file: " + qstrLogFile[iSide] + " OK" ;
        }
        else{
            qDebug()<< "Create file: " + qstrLogFile[iSide] + " NG" ;
        }
    }
}

void MainWindow::InitUiParameterCam(int iIdxModel, int iCam) {
    try{
        /*Load json file*/
         QJsonDocument loadData = loadJson(tr(PATH_GENERAL).arg(listModel[iIdxModel]) + PATH_NAME);
        QJsonObject   json = loadData.object();
        /*camera type combobox*/
        m_ComboBox[CAMERA_TYPE]->setCurrentIndex(iCam);
        /*option check box*/

        m_CheckBox[_SHOW_IMG]->setChecked(json[tr("opt_showimg_%1").arg(iCam)].toBool());
        m_CheckBox[_SAVE_IMG]->setChecked(json[tr("opt_saveimg_%1").arg(iCam)].toBool());
        m_CheckBox[_CHECK_IRIS]->setChecked(json["opt_checkiris"].toBool());
        m_CheckBox[_CHECK_STAIN]->setChecked(json[tr("opt_checkstain_%1").arg(iCam)].toBool());
        m_CheckBox[_CHECK_WHITESAIN]->setChecked(json[tr("opt_checkwhitestain_%1").arg(iCam)].toBool());
        m_CheckBox[_CHECK_GLARE]->setChecked(json[tr("opt_checkglare_%1").arg(iCam)].toBool());
        m_CheckBox[_CHECK_FOCUS]->setChecked(json[tr("opt_checkfocus_%1").arg(iCam)].toBool());
        m_CheckBox[_CHECK_COLOR]->setChecked(json[tr("opt_checkcolor_%1").arg(iCam)].toBool());
        m_CheckBox[_CHECK_DARKSPORT]->setChecked(json[tr("opt_checkdarksport_%1").arg(iCam)].toBool());
        m_CheckBox[_CAP_AF]->setChecked(json[tr("opt_captureaf_%1").arg(iCam)].toBool());
        /*delay line edit*/
        for(int iDelayNo = DL_UART_USB_SEND; iDelayNo < NUM_DELAY; iDelayNo++ ){
            QString qstrKeyDelay = json[tr("delay_%1").arg(iDelayNo)].toString();
            m_LineEdit[iDelayNo]->setText(qstrKeyDelay);
            qDebug()<<"DL: "<<m_LineEdit[iDelayNo]->text();
        }
        /*paint line edit*/
        m_LineEdit[PAINT_THICKNESS]->setText(json[tr("com_thickness")].toString());
        m_LineEdit[PAINT_OFFSET]->setText(json[tr("com_offset")].toString());
        /*normalize combox & line edit*/
        m_ComboBox[NOR_TYPE]->setCurrentIndex(QString2Int(json[tr("nor_type_%1").arg(iCam)].toString()));
        m_LineEdit[NOR_BETA]->setText(json[tr("nor_beta_%1").arg(iCam)].toString());
        m_LineEdit[NOR_ALPHA]->setText(json[tr("nor_alpha_%1").arg(iCam)].toString());

        /*stain line edit*/
        m_ComboBox[STAIN_SIZE]->setCurrentIndex(TYPE_SIZE_SMALL);
        InitUiParameterStain(iCam, TYPE_SIZE_SMALL, json);

        /*whitestain line edit*/
        m_ComboBox[WSTAIN_SIZE]->setCurrentIndex(TYPE_SIZE_SMALL);
        InitUiParameterWhiteStain(iCam, TYPE_SIZE_SMALL, json);

        m_ComboBox[ROI_GLARE]->setCurrentIndex(0);
        InitUiParameterGlare(iCam, 1, json);

        m_LineEdit[FOCUS_ROI1]->setText(json[tr("focus_roicheck1_%1").arg(iCam)].toString());
        m_LineEdit[FOCUS_ROI2]->setText(json[tr("focus_roicheck2_%1").arg(iCam)].toString());
        m_LineEdit[FOCUS_ROI3]->setText(json[tr("focus_roicheck3_%1").arg(iCam)].toString());
        m_LineEdit[FOCUS_ROI4]->setText(json[tr("focus_roicheck4_%1").arg(iCam)].toString());
        m_LineEdit[FOCUS_ROI5]->setText(json[tr("focus_roicheck5_%1").arg(iCam)].toString());
        m_LineEdit[FOCUS_ROI6]->setText(json[tr("focus_roicheck6_%1").arg(iCam)].toString());

        m_LineEdit[FOCUS_FILTER_SROI1]->setText(json[tr("focus_stdroi1_%1").arg(iCam)].toString());
        m_LineEdit[FOCUS_FILTER_SROI2]->setText(json[tr("focus_stdroi2_%1").arg(iCam)].toString());
        m_LineEdit[FOCUS_FILTER_SROI3]->setText(json[tr("focus_stdroi3_%1").arg(iCam)].toString());
        m_LineEdit[FOCUS_FILTER_SROI4]->setText(json[tr("focus_stdroi4_%1").arg(iCam)].toString());
        m_LineEdit[FOCUS_FILTER_SROI5]->setText(json[tr("focus_stdroi5_%1").arg(iCam)].toString());
        m_LineEdit[FOCUS_FILTER_SROI6]->setText(json[tr("focus_stdroi6_%1").arg(iCam)].toString());

        m_LineEdit[DARKSPORT_THRESHOULD]->setText(json[tr("darksport_threshold_%1").arg(iCam)].toString());

        int iDarkSportBlockSize = QString2Int(json[tr("darksport_blocksize_%1").arg(iCam)].toString());
        if(iDarkSportBlockSize % 2 == 0){
            iDarkSportBlockSize -= 1;
        }
        m_LineEdit[DARKSPORT_BLOCK_SIZE]->setText(QString::number(iDarkSportBlockSize));
        m_LineEdit[DARKSPORT_FILT_AREA]->setText(json[tr("darksport_filtarea_%1").arg(iCam)].toString());
        m_LineEdit[COLOR_MEANRED]->setText(json[tr("wrongcolor_meanred_%1").arg(iCam)].toString());
        m_LineEdit[COLOR_MEANGREEN]->setText(json[tr("wrongcolor_meangreen_%1").arg(iCam)].toString());
        m_LineEdit[COLOR_MEANBLUE]->setText(json[tr("wrongcolor_meanblue_%1").arg(iCam)].toString());

        /*mLineEdit AT*/
        m_LineEdit[AT_UART_USB_SEND]->setText(json["atcommand_uartusb_send"].toString());
        m_LineEdit[AT_UART_USB_RESPONE]->setText(json["atcommand_uartusb_respone"].toString());
        m_LineEdit[AT_HOME_SCREEN_SEND]->setText(json["atcommand_homescreen_send"].toString());
        m_LineEdit[AT_HOME_SCREEN_RESPONE]->setText(json["atcommand_homescreen_respone"].toString());
        m_LineEdit[AT_OPEN_IRIS_SEND]->setText(json["atcommand_openiris_send"].toString());
        m_LineEdit[AT_OPEN_IRIS_RESPONE]->setText(json["atcommand_openiris_respone"].toString());
        m_LineEdit[AT_CLOSE_IRIS_SEND]->setText(json["atcommand_closeiris_send"].toString());
        m_LineEdit[AT_CLOSE_IRIS_RESPONE]->setText(json["atcommand_closeiris_respone"].toString());
        m_LineEdit[AT_OPEN_FW1_SEND]->setText(json["atcommand_openfw1_send"].toString());
        m_LineEdit[AT_OPEN_FW1_RESPONE]->setText(json["atcommand_openfw1_respone"].toString());
        m_LineEdit[AT_CLOSE_FW1_SEND]->setText(json["atcommand_closefw1_send"].toString());
        m_LineEdit[AT_CLOSE_FW1_RESPONE]->setText(json["atcommand_closefw1_respone"].toString());
        m_LineEdit[AT_OPEN_FB1_SEND]->setText(json["atcommand_openfb1_send"].toString());
        m_LineEdit[AT_OPEN_FB1_RESPONE]->setText(json["atcommand_openfb1_respone"].toString());
        m_LineEdit[AT_CLOSE_FB1_SEND]->setText(json["atcommand_closefb1_send"].toString());
        m_LineEdit[AT_CLOSE_FB1_RESPONE]->setText(json["atcommand_closefb1_respone"].toString());
        m_LineEdit[AT_CAPTURE_NOAF_SEND]->setText(json["atcommand_capturenoaf_send"].toString());
        m_LineEdit[AT_CAPTURE_NOAF_RESPONE]->setText(json["atcommand_capturenoaf_respone"].toString());
        m_LineEdit[AT_CAPTURE_AF_SEND]->setText(json["atcommand_captureaf_send"].toString());
        m_LineEdit[AT_CAPTURE_AF_RESPONE]->setText(json["atcommand_captureaf_respone"].toString());
        m_LineEdit[AT_CAPTURE_TRYAF_SEND]->setText(json["atcommand_capturetryaf_send"].toString());
        m_LineEdit[AT_CAPTURE_TRYAF_RESPONE]->setText(json["atcommand_capturetryaf_respone"].toString());

        /*mLineEdit ADB*/
        m_LineEdit[ADB_GET_LIST_SEND]->setText(json["adbcommand_getlist_send"].toString());
        m_LineEdit[ADB_GET_LIST_RESPONE]->setText(json["adbcommand_getlist_respone"].toString());
        m_LineEdit[ADB_PULL_2_PC_SEND]->setText(json["adbcommand_pull2pc_send"].toString());
        m_LineEdit[ADB_PULL_2_PC_RESPONE]->setText(json["adbcommand_pull2pc_respone"].toString());
        m_LineEdit[ADB_REMOVE_FOLDER_SEND]->setText(json["adbcommand_removefolder_send"].toString());
        m_LineEdit[ADB_REMOVE_FOLDER_RESPONE]->setText(json["adbcommand_removefolder_respone"].toString());


    }
    catch(QException &e) {
        QString strerror = QString::fromStdString(e.what());
        qDebug()<<"[InitUiParaCam]"<<strerror;
        QMessageBox::warning(this,"Error",strerror);
    }
}
void MainWindow::InitUiParameterStain(int iCam, int iTypeSize, QJsonObject json) {
    try{

        m_LineEdit[STAIN_THRESHOLD]->setText(json[tr("stain_threshold_%1_%2").arg(iCam).arg(iTypeSize)].toString());
        int iStainBlockSize = QString2Int(json[tr("stain_block_size_%1_%2").arg(iCam).arg(iTypeSize)].toString());
        if(iStainBlockSize % 2 == 0){
            iStainBlockSize -= 1;
        }
        m_LineEdit[STAIN_BLOCKSIZE]->setText(QString::number(iStainBlockSize));

        /*Blur*/
        int iStainBlurSize = QString2Int(json[tr("stain_blur_size_%1_%2").arg(iCam).arg(iTypeSize)].toString());
        if(iStainBlurSize %2 == 0){
            iStainBlurSize -= 1;
        }
        m_LineEdit[STAIN_BLURSIZE]->setText(QString::number(iStainBlurSize));
        /*Erode*/
        int iStainErodeSize = QString2Int(json[tr("stain_erode_size_%1_%2").arg(iCam).arg(iTypeSize)].toString());
        if(iStainErodeSize %2  == 0){
            iStainErodeSize -= 1;
        }
        m_LineEdit[STAIN_ERODE_SIZE]->setText(QString::number(iStainErodeSize));
        m_LineEdit[STAIN_ERODE_LOOP]->setText(json[tr("stain_erode_loop_%1_%2").arg(iCam).arg(iTypeSize)].toString());

        /*Dilate*/
        int iStainDilateSize = QString2Int(json[tr("stain_dilate_size_%1_%2").arg(iCam).arg(iTypeSize)].toString());
        if(iStainDilateSize %2  == 0){
            iStainDilateSize -= 1;
        }
        m_LineEdit[STAIN_DILATE_SIZE]->setText(QString::number(iStainDilateSize));
        m_LineEdit[STAIN_DILATE_LOOP]->setText(json[tr("stain_dilate_loop_%1_%2").arg(iCam).arg(iTypeSize)].toString());

        /*Remove: Conner, Edge*/
        m_LineEdit[STAIN_REMOVE_EDGE]->setText(json[tr("stain_remove_edge_%1_%2").arg(iCam).arg(iTypeSize)].toString());
        m_LineEdit[STAIN_REMOVE_CONNER]->setText(json[tr("stain_remove_conner_%1_%2").arg(iCam).arg(iTypeSize)].toString());
        /*Filter: area, width, height*/
        QString strArea  = json[tr("stain_filter_area_%1_%2").arg(iCam).arg(iTypeSize)].toString();
        QString strWidth  = json[tr("stain_filter_width_%1_%2").arg(iCam).arg(iTypeSize)].toString();
        QString strHeight  = json[tr("stain_filter_height_%1_%2").arg(iCam).arg(iTypeSize)].toString();

        m_LineEdit[STAIN_FILTER_AREA]->setText(strArea);
        m_LineEdit[STAIN_FILTER_WIDTH]->setText(strWidth);
        m_LineEdit[STAIN_FILTER_HEIGHT]->setText(strHeight);
    }
    catch(QException &e) {
        QString strerror = QString::fromStdString(e.what());
        qDebug()<<"[InitUiStainPara]"<<strerror;
        QMessageBox::warning(this,"Error",strerror);
    }
}
void MainWindow::InitUiParameterWhiteStain(int iCam, int iTypeSize, QJsonObject json) {
    try{

        m_LineEdit[WSTAIN_THRESHOLD]->setText(json[tr("wstain_threshold_%1_%2").arg(iCam).arg(iTypeSize)].toString());
        int iwStainBlockSize = QString2Int(json[tr("wstain_block_size_%1_%2").arg(iCam).arg(iTypeSize)].toString());
        if(iwStainBlockSize % 2 == 0){
            iwStainBlockSize -= 1;
        }
        m_LineEdit[WSTAIN_BLOCKSIZE]->setText(QString::number(iwStainBlockSize));

        /*Blur*/
        int iwStainBlurSize = QString2Int(json[tr("wstain_blur_size_%1_%2").arg(iCam).arg(iTypeSize)].toString());
        if(iwStainBlurSize %2 == 0){
            iwStainBlurSize -= 1;
        }
        m_LineEdit[WSTAIN_BLURSIZE]->setText(QString::number(iwStainBlurSize));
        /*Erode*/
        int iwStainErodeSize = QString2Int(json[tr("wstain_erode_size_%1_%2").arg(iCam).arg(iTypeSize)].toString());
        if(iwStainErodeSize %2  == 0){
            iwStainErodeSize -= 1;
        }
        m_LineEdit[WSTAIN_ERODE_SIZE]->setText(QString::number(iwStainErodeSize));
        m_LineEdit[WSTAIN_ERODE_LOOP]->setText(json[tr("wstain_erode_loop_%1_%2").arg(iCam).arg(iTypeSize)].toString());

        /*Dilate*/
        int iwStainDilateSize = QString2Int(json[tr("wstain_dilate_size_%1_%2").arg(iCam).arg(iTypeSize)].toString());
        if(iwStainDilateSize %2  == 0){
            iwStainDilateSize -= 1;
        }
        m_LineEdit[WSTAIN_DILATE_SIZE]->setText(QString::number(iwStainDilateSize));
        m_LineEdit[WSTAIN_DILATE_LOOP]->setText(json[tr("wstain_dilate_loop_%1_%2").arg(iCam).arg(iTypeSize)].toString());

        /*Remove: Conner, Edge*/
        m_LineEdit[WSTAIN_REMOVE_EDGE]->setText(json[tr("wstain_remove_edge_%1_%2").arg(iCam).arg(iTypeSize)].toString());
        m_LineEdit[WSTAIN_REMOVE_CONNER]->setText(json[tr("wstain_remove_conner_%1_%2").arg(iCam).arg(iTypeSize)].toString());
        /*Filter: area, width, height*/
        QString strwStainArea  = json[tr("wstain_filter_area_%1_%2").arg(iCam).arg(iTypeSize)].toString();
        QString strwStainWidth  = json[tr("wstain_filter_width_%1_%2").arg(iCam).arg(iTypeSize)].toString();
        QString strwStainHeight  = json[tr("wstain_filter_height_%1_%2").arg(iCam).arg(iTypeSize)].toString();

        m_LineEdit[WSTAIN_FILTER_AREA]->setText(strwStainArea);
        m_LineEdit[WSTAIN_FILTER_WIDTH]->setText(strwStainWidth);
        m_LineEdit[WSTAIN_FILTER_HEIGHT]->setText(strwStainHeight);
    }
    catch(QException &e) {
        QString strerror = QString::fromStdString(e.what());
        qDebug()<<"[InitUiWhiteStainPara]"<<strerror;
        QMessageBox::warning(this,"Error",strerror);
    }
}

void MainWindow::InitUiParameterGlare(int iCam, int iRoi, QJsonObject json)
{
    try{
        m_LineEdit[GLARE_THRESHOLD]->setText(json[tr("glare_threshold%2_%1").arg(iCam).arg(iRoi)].toString());

         /*Blur*/
        int iGlareBlurSize = QString2Int(json[tr("glare_blur_size%2_%1").arg(iCam).arg(iRoi)].toString());
        if(iGlareBlurSize % 2 == 0){
            iGlareBlurSize -= 1;
        }
        m_LineEdit[GLARE_BLUR_SIZE]->setText(QString::number(iGlareBlurSize));


        m_LineEdit[GLARE_ROI1]->setText(json[tr("glare_roicheck%2_%1").arg(iCam).arg(iRoi)].toString());

        int iGlareErodeSize = QString2Int(json[tr("glare_erode_size%2_%1").arg(iCam).arg(iRoi)].toString());
        if(iGlareErodeSize % 2 == 0){
            iGlareErodeSize -= 1;
        }
        m_LineEdit[GLARE_ERODE_SIZE]->setText(QString::number(iGlareBlurSize));

        m_LineEdit[GLARE_ERODE_LOOP]->setText(json[tr("glare_erode_size%2_%1").arg(iCam).arg(iRoi)].toString());

        int iGlareDilateSize = QString2Int(json[tr("glare_dilate_size%2_%1").arg(iCam).arg(iRoi)].toString());
        if(iGlareDilateSize % 2 == 0){
            iGlareDilateSize -= 1;
        }
        m_LineEdit[GLARE_DILATE_SIZE]->setText(QString::number(iGlareDilateSize));
        m_LineEdit[GLARE_DILATE_LOOP]->setText(json[tr("glare_dilate_size%2_%1").arg(iCam).arg(iRoi)].toString());

        m_LineEdit[GLARE_REMOVE_EDGE]->setText(json[tr("glare_remove_edge%2_%1").arg(iCam).arg(iRoi)].toString());
        m_LineEdit[GLARE_REMOVE_CONNER]->setText(json[tr("glare_remove_conner%2_%1").arg(iCam).arg(iRoi)].toString());

        m_LineEdit[GLARE_FILTER_MROI1]->setText(json[tr("glare_filtermean_roi%2_%1").arg(iCam).arg(iRoi)].toString());

        m_LineEdit[GLARE_FILTER_AREA1]->setText(json[tr("glare_filter_area%2_%1").arg(iCam).arg(iRoi)].toString());

        m_LineEdit[GLARE_FILTER_WIDTH1]->setText(json[tr("glare_filter_width%2_%1").arg(iCam).arg(iRoi)].toString());

        m_LineEdit[GLARE_FILTER_HEIGHT1]->setText(json[tr("glare_filter_height%2_%1").arg(iCam).arg(iRoi)].toString());
    }
    catch(QException &e) {
        QString strerror = QString::fromStdString(e.what());
        qDebug()<<"[InitUiGlarePara]"<<strerror;
        QMessageBox::warning(this,"Error",strerror);
    }
}
vector<QString> MainWindow::GetAllFileInFolder(QString folder) {
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
void MainWindow::closeEvent (QCloseEvent *event)
{
    event->ignore();
    if (QMessageBox::Yes == QMessageBox::question(this, "Notice", "Are you sure to exit?", QMessageBox::Yes | QMessageBox::No))
    {
        qDebug("atk::Program Exit");
        event->accept();
    }
}

void MainWindow::SelectCmd(int iIndex) {
    if(QObject::sender()==ui->cbbListFunction) {
        qDebug()<<"cmd: "<<listAT[iIndex];
        ui->edtDataSendCom->setText(listAT[iIndex]);
    }
    if(QObject::sender()==ui->cbbListFunctionADB) {
        QString cmd = QString(listADB[iIndex]).arg(ui->cbbListDevices->currentText());
        qDebug()<<"cmd: "<<cmd;
        ui->edtDataSendADB->setText(cmd);
    }
}

void MainWindow::simulatorVision(int iCam, int iModel, QStringList listImage)
{
    ui->tbwLogTestManual->clearContents();
    ui->tbwLogTestManual->setRowCount(listImage.size());
    mRes.clear();
    mRes.resize(listImage.size());
    ui->progressBar->setRange(0,listImage.size());
    int i = 0;
    int iDelay = QString2Double(ui->txt_delay->text()) * 1000;
    bool bDebug = ui->manualDebug->isChecked();
    foreach(QString filename, listImage) {
        i++;

        cv::Mat mIn;
        _sResVision stResStain[NUM_TYPE];
        _sResVision stResWStain[NUM_TYPE];
        _sResVision stGlare;
        _sResVision stFocus;
        _sResVision stDarkSport;
        _sResVision stColor;

        Mat mOut;

        QString name = ui->edtPath->text() +"/"+ filename;
        mIn = cv::imread(name.toStdString());


        if(mIn.empty()) continue;

        if(mGeneral[iModel].bOptCheckStain[iCam])
            for(int i = TYPE_SIZE_SMALL; i<= TYPE_SIZE_LARGE; i++){
                if(!stResStain[TYPE_SIZE_SMALL].bRes && i == TYPE_SIZE_LARGE)
                    continue;
                stResStain[i] = fVision.CheckStain(mIn, mGeneral[iModel], iCam, i, filename, bDebug);
                if(!stResStain[i].bRes)
                    mOut = stResStain[i].mRes.clone();
            }

        if(mGeneral[iModel].bOptCheckWhiteStain[iCam])
            for(int i = TYPE_SIZE_SMALL; i<= TYPE_SIZE_LARGE; i++){
                if(!stResWStain[TYPE_SIZE_SMALL].bRes && i == TYPE_SIZE_LARGE){
                    continue;
                }
                stResWStain[i] = fVision.CheckWhiteStain(mIn, mGeneral[iModel], iCam, i, filename, bDebug);

//                if(!stResWStain[i].bRes)
//                    mOut = stResWStain[i].mRes.clone();
            }

        if(mGeneral[iModel].bOptCheckGlare[iCam])
            stGlare = fVision.CheckGlare(mIn, mGeneral[iModel], iCam, filename, bDebug);

        if(mGeneral[iModel].bOptCheckFocus[iCam])
            stFocus = fVision.CheckFocus(mIn, mGeneral[iModel], iCam, filename, bDebug);

        if(mGeneral[iModel].bOptDarkSport[iCam])
            stDarkSport = fVision.CheckDarkspot(mIn, mGeneral[iModel], iCam, filename, bDebug);

        if(mGeneral[iModel].bOptCheckColor[iCam])
            stColor = fVision.CheckColor(mIn, mGeneral[iModel], iCam, filename, bDebug);


        if(stResStain[TYPE_SIZE_SMALL].bRes && stResStain[TYPE_SIZE_LARGE].bRes &&
                stResWStain[TYPE_SIZE_SMALL].bRes && stResWStain[TYPE_SIZE_LARGE].bRes &&
                stGlare.bRes && stFocus.bRes && stDarkSport.bRes && stColor.bRes ){

            cv::putText(mOut, "PASS", Point(500,500),1,15,cv_green,4);
        }
        else{
            for(Rect r : stResStain[TYPE_SIZE_SMALL].vRes){
                cv::rectangle(mOut, r, cv_aqua,  mGeneral[iModel].ipPaintThickness);
            }


            for(Rect r : stResStain[TYPE_SIZE_LARGE].vRes){
                cv::rectangle(mOut, r, cv_aqua,  mGeneral[iModel].ipPaintThickness);
            }

            for(Rect r : stResWStain[TYPE_SIZE_SMALL].vRes){
                cv::rectangle(mOut, r, cv_red, mGeneral[iModel].ipPaintThickness);
            }

            for(Rect r : stResWStain[TYPE_SIZE_LARGE].vRes){
                cv::rectangle(mOut, r, cv_red, mGeneral[iModel].ipPaintThickness);
            }

            for(Rect r : stDarkSport.vRes){
                cv::rectangle(mOut, r, cv_purple, mGeneral[iModel].ipPaintThickness);
            }

            for(Rect r : stGlare.vRes){
                cv::rectangle(mOut, r, cv_orange, mGeneral[iModel].ipPaintThickness);
            }


            for(Rect r : stFocus.vRes){
                cv::rectangle(mOut, r, cv_blue,   mGeneral[iModel].ipPaintThickness);
            }

               cv::putText(mOut, "FAIL", Point(500,500),1,15,cv_yellow,4);

        }


        mRes.at(i-1) = mOut ;
        emit eDisplay_Image(mOut, SIDE_IMAGE);


        QString nameSave = ui->edtPath->text() +"/Res_"+ filename;
        emit eAddLogTestManual(nameSave,Qt::black);



        QThread::msleep(iDelay);
        emit esetValueProcessBar(i);

    }

    Simulation->StopThread();
}

QStringList MainWindow::getListImageFromFolder(QString qstrFolder)
{
    QDir directory(qstrFolder);
     QStringList images = directory.entryList(QStringList() << "*.jpg" << "*.JPG" << "*.png" << "*.PNG",QDir::Files);
     return images;
}
void MainWindow::handleComportError(QSerialPort::SerialPortError serialPortError) {
    QString err =  QObject::tr("comTest:: port %1, error: %2, type = ").arg(qspSerial->portName()).arg(qspSerial->errorString());
    switch (serialPortError) {
    case QSerialPort::NoError:
        return;
    default:
        err += QString::number(serialPortError);
        break;
    }
    WriteLogComIO(err);
    QMessageBox::warning(this,"Error Com test", err);
}
void MainWindow::readDataComport() {
    qstrDataSerial = qspSerial->readAll();
    if(qstrDataSerial.isEmpty()){
        qDebug()<<"Empty";
        return;
    }
    qDebug()<<"com test = "<<qstrDataSerial;
    AddDataComport(qstrDataSerial);
}
void MainWindow::handleCmdError(QProcess::ProcessError processError) {
    QString err =  QObject::tr("adb test:: adb error: %1, type = ")
            .arg(qpManADB->errorString());

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

    WriteLogComIO(err);
    QMessageBox::warning(this,"Error ADB test", err);
}
void MainWindow::readDataCmd() {
    qstrDataADB = qpManADB->readAllStandardOutput();
    if(qstrDataADB.isEmpty()){
        qDebug()<<"Empty";
        return;
    }
    qDebug()<<"*"<<qstrDataADB;
    AddDataCmd(qstrDataADB);
    //Process adb devices
    if(bEnableScanDevices) {
        bEnableScanDevices = false;
        ui->cbbListDevices->clear();

        QStringList line;
        line = qstrDataADB.split("\r\n");

        bool bHaveDevices = false;

        for(QString str:line){
            //qDebug()<<"data = "<<str;
            if(!str.isEmpty() && str.contains("\tdevice", Qt::CaseSensitive)) {
                bHaveDevices = true;
                QString devices = str.left(str.indexOf("\tdevice"));
                qDebug()<<"ID = "<<devices;
                ui->cbbListDevices->addItem(devices);
            }
        }
        if(!bHaveDevices)
            ui->cbbListDevices->addItem("null");
        ui->cbbListDevices->setCurrentIndex(0);
        QString cmd = QString(listADB[ADB_GET_LIST]).arg(ui->cbbListDevices->currentText());
        ui->edtDataSendADB->setText(cmd);
    }
    //Process find img
    if(bEnableFindImg)
    {
        bEnableFindImg = false;

        QStringList line;
        line = qstrDataADB.split("\r\n");

        bool bHaveImage = false;

        for(QString str:line){
            if(!str.isEmpty() && str.contains(".jpg", Qt::CaseSensitive))
            {
                bHaveImage = true;
                qDebug()<<"# = "<<str;
                AddDataCmd(str,Qt::red);
            }
        }
        if(!bHaveImage)
            AddDataCmd("null",Qt::red);
    }
}

void MainWindow::tbwProcessLeft(int iRow, int iCol) {
    if(!pProc[SIDE_LEFT]->mDevice.bUseComSocket) return;
    QPoint qpTemp(iRow, iCol);
        if(qpTemp == RES_STAIN_FW1 || qpTemp == RES_WHITESTAIN_FW1
                || qpTemp == RES_COLOR_FW1 || qpTemp == RES_DARKSPORT_FW1 ){
            if(!pProc[SIDE_LEFT]->mImread[FW1][IMG_CHECK_STEP1].empty() && !pProc[SIDE_LEFT]->m_bRun){
                pProc[SIDE_LEFT]->eDisplayImage(pProc[SIDE_LEFT]->mImread[FW1][IMG_CHECK_STEP1], pProc[SIDE_LEFT]->linkMain.lbDisplay);
            }
        }
        else if(qpTemp == RES_GLARE_FW1 || qpTemp == RES_FOCUS_FW1){
            if(!pProc[SIDE_LEFT]->mImread[FW1][IMG_CHECK_STEP2].empty() && !pProc[SIDE_LEFT]->m_bRun){
                pProc[SIDE_LEFT]->eDisplayImage(pProc[SIDE_LEFT]->mImread[FW1][IMG_CHECK_STEP2], pProc[SIDE_LEFT]->linkMain.lbDisplay);
            }
        }
        if(pProc[SIDE_LEFT]->mDevice.ipModel>= G975){
            if(qpTemp == RES_STAIN_FB1 || qpTemp == RES_WHITESTAIN_FB1
                    || qpTemp == RES_COLOR_FB1 || qpTemp == RES_DARKSPORT_FB1 ){
                if(!pProc[SIDE_LEFT]->mImread[FB1][IMG_CHECK_STEP1].empty() && !pProc[SIDE_LEFT]->m_bRun){
                    pProc[SIDE_LEFT]->eDisplayImage(pProc[SIDE_LEFT]->mImread[FB1][IMG_CHECK_STEP1], pProc[SIDE_LEFT]->linkMain.lbDisplay);
                }
            }
            else if(qpTemp == RES_GLARE_FB1 || qpTemp == RES_FOCUS_FB1){
                if(!pProc[SIDE_LEFT]->mImread[FB1][IMG_CHECK_STEP2].empty() && !pProc[SIDE_LEFT]->m_bRun){
                    pProc[SIDE_LEFT]->eDisplayImage(pProc[SIDE_LEFT]->mImread[FB1][IMG_CHECK_STEP2], pProc[SIDE_LEFT]->linkMain.lbDisplay);
                }
            }
        }
}

void MainWindow::tbwProcessRight(int iRow, int iCol) {
    if(!pProc[SIDE_RIGHT]->mDevice.bUseComSocket) return;
    QPoint qpTemp(iRow, iCol);
        if(qpTemp == RES_STAIN_FW1 || qpTemp == RES_WHITESTAIN_FW1
                || qpTemp == RES_COLOR_FW1 || qpTemp == RES_DARKSPORT_FW1 ){
            if(!pProc[SIDE_RIGHT]->mImread[FW1][IMG_CHECK_STEP1].empty() && !pProc[SIDE_RIGHT]->m_bRun){
                pProc[SIDE_RIGHT]->eDisplayImage(pProc[SIDE_RIGHT]->mImread[FW1][IMG_CHECK_STEP1], pProc[SIDE_RIGHT]->linkMain.lbDisplay);
            }
        }
        else if(qpTemp == RES_GLARE_FW1 || qpTemp == RES_FOCUS_FW1){
            if(!pProc[SIDE_RIGHT]->mImread[FW1][IMG_CHECK_STEP2].empty() && !pProc[SIDE_RIGHT]->m_bRun){
                pProc[SIDE_RIGHT]->eDisplayImage(pProc[SIDE_RIGHT]->mImread[FW1][IMG_CHECK_STEP2], pProc[SIDE_RIGHT]->linkMain.lbDisplay);
            }
        }
        if(pProc[SIDE_RIGHT]->mDevice.ipModel>= G975){
            if(qpTemp == RES_STAIN_FB1 || qpTemp == RES_WHITESTAIN_FB1
                    || qpTemp == RES_COLOR_FB1 || qpTemp == RES_DARKSPORT_FB1 ){
                if(!pProc[SIDE_RIGHT]->mImread[FB1][IMG_CHECK_STEP1].empty() && !pProc[SIDE_RIGHT]->m_bRun){
                    pProc[SIDE_RIGHT]->eDisplayImage(pProc[SIDE_RIGHT]->mImread[FB1][IMG_CHECK_STEP1], pProc[SIDE_RIGHT]->linkMain.lbDisplay);
                }
            }
            else if(qpTemp == RES_GLARE_FB1 || qpTemp == RES_FOCUS_FB1){
                if(!pProc[SIDE_RIGHT]->mImread[FB1][IMG_CHECK_STEP2].empty() && !pProc[SIDE_RIGHT]->m_bRun){
                    pProc[SIDE_RIGHT]->eDisplayImage(pProc[SIDE_RIGHT]->mImread[FB1][IMG_CHECK_STEP2], pProc[SIDE_RIGHT]->linkMain.lbDisplay);
                }
            }
        }
}

bool MainWindow::OpenSerialPort(QString NamePort, int Baudrate) {
    qspSerial->setPortName(NamePort); //ttyUSB1
    qspSerial->setBaudRate(Baudrate);
    qspSerial->setDataBits(QSerialPort::Data8);
    qspSerial->setParity(QSerialPort::NoParity);
    qspSerial->setStopBits(QSerialPort::OneStop);
    qspSerial->setFlowControl(QSerialPort::NoFlowControl);

    if (!qspSerial->open(QIODevice::ReadWrite))
        return false;
    else
        return true;
}
bool MainWindow::OpenCom(QSerialPort *qspCom, QString NamePort,  int Typle, int Baudrate) {
    qspCom->setPortName(NamePort); //ttyUSB1
    if(Typle == 0) {
        qspCom->setBaudRate(9600);
    }
    else{
        qspCom->setBaudRate(Baudrate);
    }
    qspCom->setDataBits(QSerialPort::Data8);
    qspCom->setParity(QSerialPort::NoParity);
    qspCom->setStopBits(QSerialPort::OneStop);
    qspCom->setFlowControl(QSerialPort::NoFlowControl);
    if (!qspCom->open(QIODevice::ReadWrite))
        return false;
    else
        return true;
}
bool MainWindow::CloseCom(QSerialPort *qspCom) {
    qDebug()<<"close comport = "<<qspCom->portName();
    bool bResult = false;
    if(qspCom->isOpen()) {
        qspCom->close();
        return true;
    }
    else {
        bResult = true;
    }
    qDebug()<<"close comport = "<<bResult;
    return bResult;
}
void MainWindow::SendCom(QString data) {
    static  QByteArray cmd;
    if(qspSerial->isOpen()) {
        data += "\r\n";
        cmd = data.toLocal8Bit();
        qDebug()<<"send="<<cmd;
        qspSerial->write(cmd.data());
    }
    else {
        QMessageBox::warning(this, "Error", "Open Com before send data");
    }
}
void MainWindow::SendCom(QSerialPort *qspCom, QString data) {
    //mutextSendCom.lock();
    QByteArray cmd;
    if(qspCom->isOpen()) {
        data += "\r\n";
        cmd = data.toLocal8Bit();
        qDebug()<<"send com ="<<cmd;
        qspCom->write(cmd.data());
    }
    else {
        QMessageBox::warning(this, "Error", "Open Com before send data");
    }
}
void MainWindow::ConnectSignalObject() {
    //comport
    for(int i = 0; i<NUM_SIDE; i++){
        qspAuComport[i] = new QSerialPort(this);
        qspAuComIO[i] = new QSerialPort(this);
    }
}

void MainWindow::GetDataBufferTemp() {
    try{
        /*getData2Buffertemp camera*/
        int iTypeCam                                                                   = m_ComboBox[CAMERA_TYPE]->currentIndex();
        /*Option fuction check */
        mGeneral[PARA_CONTAIN].bOptSaveImageResize                                     = ui->cbSaveImageResize->isChecked();
        mGeneral[PARA_CONTAIN].bOptShowImg[iTypeCam]                                   = m_CheckBox[_SHOW_IMG]->isChecked();
        mGeneral[PARA_CONTAIN].bOptSaveImg[iTypeCam]                                   = m_CheckBox[_SAVE_IMG]->isChecked();
        mGeneral[PARA_CONTAIN].bOptCheckIris                                           = m_CheckBox[_CHECK_IRIS]->isChecked();
        mGeneral[PARA_CONTAIN].bOptCheckStain[iTypeCam]                                = m_CheckBox[_CHECK_STAIN]->isChecked();
        mGeneral[PARA_CONTAIN].bOptCheckWhiteStain[iTypeCam]                           = m_CheckBox[_CHECK_WHITESAIN]->isChecked();
        mGeneral[PARA_CONTAIN].bOptCheckGlare[iTypeCam]                                = m_CheckBox[_CHECK_GLARE]->isChecked();
        mGeneral[PARA_CONTAIN].bOptCheckFocus[iTypeCam]                                = m_CheckBox[_CHECK_FOCUS]->isChecked();
        mGeneral[PARA_CONTAIN].bOptCheckColor[iTypeCam]                                = m_CheckBox[_CHECK_COLOR]->isChecked();
        mGeneral[PARA_CONTAIN].bOptDarkSport[iTypeCam]                                 = m_CheckBox[_CHECK_DARKSPORT]->isChecked();
        mGeneral[PARA_CONTAIN].bOptCaptrueAf[iTypeCam]                                 = m_CheckBox[_CAP_AF]->isChecked();
        /*delay time*/
        for(int iDelayNo = DL_UART_USB_SEND; iDelayNo < NUM_DELAY; iDelayNo++ ) {
            mGeneral[PARA_CONTAIN].dbDelay[iDelayNo]                                   = QString2Double(m_LineEdit[iDelayNo]->text().trimmed());
        }
        /*paint parameter*/
        mGeneral[PARA_CONTAIN].ipPaintThickness                                        = QString2Int(m_LineEdit[PAINT_THICKNESS]->text().trimmed());
        mGeneral[PARA_CONTAIN].ipPaintOffset                                           = QString2Int(m_LineEdit[PAINT_OFFSET]->text().trimmed());
        /*normalize parameter*/
        mGeneral[PARA_CONTAIN].ipNormType[iTypeCam]                                    = m_ComboBox[NOR_TYPE]->currentIndex();
        mGeneral[PARA_CONTAIN].ipNormBeta[iTypeCam]                                    = QString2Int(m_LineEdit[NOR_BETA]->text().trimmed());
        mGeneral[PARA_CONTAIN].ipNormAlpha[iTypeCam]                                   = QString2Int(m_LineEdit[NOR_ALPHA]->text().trimmed());
        /*Stain parameter*/
        int iTypeSSize                                                                 = m_ComboBox[STAIN_SIZE]->currentIndex();
        mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipThreshold[iTypeSSize]               = QString2Int(m_LineEdit[STAIN_THRESHOLD]->text().trimmed());
        mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipBlockSize[iTypeSSize]               = QString2Int(m_LineEdit[STAIN_BLOCKSIZE]->text().trimmed());
        if(mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipBlockSize[iTypeSSize] < 3){
            m_LineEdit[STAIN_BLOCKSIZE]->setText("3");
            mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipBlockSize[iTypeSSize]               = QString2Int(m_LineEdit[STAIN_BLOCKSIZE]->text().trimmed());
        }

        mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipBlurSize[iTypeSSize]                = QString2Int(m_LineEdit[STAIN_BLURSIZE]->text().trimmed());
        if(mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipBlurSize[iTypeSSize] %2 == 0 || mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipBlurSize[iTypeSSize] <= 1){
            m_LineEdit[STAIN_BLURSIZE]->setText("3");
            mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipBlurSize[iTypeSSize]                = QString2Int(m_LineEdit[STAIN_BLURSIZE]->text().trimmed());
        }

        mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipErodeSize[iTypeSSize]               = QString2Int(m_LineEdit[STAIN_ERODE_SIZE]->text().trimmed());
        if(mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipErodeSize[iTypeSSize] %2 ==0 || mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipErodeSize[iTypeSSize] <= 1){
            m_LineEdit[STAIN_ERODE_SIZE]->setText("3");
            mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipErodeSize[iTypeSSize]               = QString2Int(m_LineEdit[STAIN_ERODE_SIZE]->text().trimmed());
        }

        mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipErodeLoop[iTypeSSize]               = QString2Int(m_LineEdit[STAIN_ERODE_LOOP]->text().trimmed());
        if(mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipErodeLoop[iTypeSSize] <= 0 || mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipErodeLoop[iTypeSSize] > 20){
            m_LineEdit[STAIN_ERODE_LOOP]->setText("1");
            mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipErodeLoop[iTypeSSize]               = QString2Int(m_LineEdit[STAIN_ERODE_LOOP]->text().trimmed());
        }

        mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipDilateSize[iTypeSSize]              = QString2Int(m_LineEdit[STAIN_DILATE_SIZE]->text().trimmed());
        if(mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipDilateSize[iTypeSSize] %2 ==0 || mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipDilateSize[iTypeSSize] <= 1){
            m_LineEdit[STAIN_DILATE_SIZE]->setText("3");
            mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipDilateSize[iTypeSSize]               = QString2Int(m_LineEdit[STAIN_DILATE_SIZE]->text().trimmed());
        }

        mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipDilateLoop[iTypeSSize]              = QString2Int(m_LineEdit[STAIN_DILATE_LOOP]->text().trimmed());
        if(mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipDilateLoop[iTypeSSize] <= 0 || mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipDilateLoop[iTypeSSize] > 20){
            m_LineEdit[STAIN_DILATE_LOOP]->setText("1");
            mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipDilateLoop[iTypeSSize]               = QString2Int(m_LineEdit[STAIN_ERODE_LOOP]->text().trimmed());
        }

        mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipRemoveEdge[iTypeSSize]              = QString2Int(m_LineEdit[STAIN_REMOVE_EDGE]->text().trimmed());
        mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipRemoveConner[iTypeSSize]            = QString2Int(m_LineEdit[STAIN_REMOVE_CONNER]->text().trimmed());

        if((m_LineEdit[STAIN_FILTER_AREA]->text().split(",").count()) == 2){
            mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipFilterAreaMin[iTypeSSize]       = QString2Point(m_LineEdit[STAIN_FILTER_AREA]->text().trimmed()).x;
            mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipFilterAreaMax[iTypeSSize]       = QString2Point(m_LineEdit[STAIN_FILTER_AREA]->text().trimmed()).y;
        }
        else{
            QMessageBox::warning(this,"Error","Stain Filter Area input fail (Format: min,max)");
            return;
        }

        if((m_LineEdit[STAIN_FILTER_WIDTH]->text().split(",").count()) == 2){
            mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipFilterWMin[iTypeSSize]          = QString2Point(m_LineEdit[STAIN_FILTER_WIDTH]->text().trimmed()).x;
            mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipFilterWMax[iTypeSSize]          = QString2Point(m_LineEdit[STAIN_FILTER_WIDTH]->text().trimmed()).y;
        }
        else{
            QMessageBox::warning(this,"Error","Stain Filter Width input fail (Format: min,max)");
            return;
        }

        if((m_LineEdit[STAIN_FILTER_HEIGHT]->text().split(",").count()) == 2){
            mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipFilterHMin[iTypeSSize]          = QString2Point(m_LineEdit[STAIN_FILTER_HEIGHT]->text().trimmed()).x;
            mGeneral[PARA_CONTAIN].spStain[iTypeCam].ipFilterHMax[iTypeSSize]          = QString2Point(m_LineEdit[STAIN_FILTER_HEIGHT]->text().trimmed()).y;
        }
        else{
            QMessageBox::warning(this,"Error","Stain Filter Height input fail (Format: min,max)");
            return;
        }

        /*WStain parameter*/
        int iTypeWSSize                                                                = m_ComboBox[WSTAIN_SIZE]->currentIndex();
        mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipThreshold[iTypeWSSize]               = QString2Int(m_LineEdit[WSTAIN_THRESHOLD]->text().trimmed());
        mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipBlockSize[iTypeWSSize]               = QString2Int(m_LineEdit[WSTAIN_BLOCKSIZE]->text().trimmed());
        if(mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipBlockSize[iTypeWSSize] < 3){
            m_LineEdit[WSTAIN_BLOCKSIZE]->setText("3");
            mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipBlockSize[iTypeWSSize]               = QString2Int(m_LineEdit[WSTAIN_BLOCKSIZE]->text().trimmed());
        }

        mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipBlurSize[iTypeWSSize]                = QString2Int(m_LineEdit[WSTAIN_BLURSIZE]->text().trimmed());
        if(mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipBlurSize[iTypeWSSize] %2 == 0 || mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipBlurSize[iTypeWSSize] <= 1){
            m_LineEdit[WSTAIN_BLURSIZE]->setText("3");
            mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipBlurSize[iTypeWSSize]                = QString2Int(m_LineEdit[WSTAIN_BLURSIZE]->text().trimmed());
        }

        mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipErodeSize[iTypeWSSize]               = QString2Int(m_LineEdit[WSTAIN_ERODE_SIZE]->text().trimmed());
        if(mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipErodeSize[iTypeWSSize] %2 ==0 || mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipErodeSize[iTypeWSSize] <= 1){
            m_LineEdit[WSTAIN_ERODE_SIZE]->setText("3");
            mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipErodeSize[iTypeWSSize]               = QString2Int(m_LineEdit[WSTAIN_ERODE_SIZE]->text().trimmed());
        }

        mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipErodeLoop[iTypeWSSize]               = QString2Int(m_LineEdit[WSTAIN_ERODE_LOOP]->text().trimmed());
        if(mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipErodeLoop[iTypeWSSize] <= 0 || mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipErodeLoop[iTypeWSSize] > 20){
            m_LineEdit[WSTAIN_ERODE_LOOP]->setText("1");
            mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipErodeLoop[iTypeWSSize]               = QString2Int(m_LineEdit[WSTAIN_ERODE_LOOP]->text().trimmed());
        }

        mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipDilateSize[iTypeWSSize]              = QString2Int(m_LineEdit[WSTAIN_DILATE_SIZE]->text().trimmed());
        if(mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipDilateSize[iTypeWSSize] %2 ==0 || mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipDilateSize[iTypeWSSize] <= 1){
            m_LineEdit[WSTAIN_DILATE_SIZE]->setText("3");
            mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipDilateSize[iTypeWSSize]               = QString2Int(m_LineEdit[WSTAIN_DILATE_SIZE]->text().trimmed());
        }

        mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipDilateLoop[iTypeWSSize]              = QString2Int(m_LineEdit[WSTAIN_DILATE_LOOP]->text().trimmed());
        if(mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipDilateLoop[iTypeWSSize] <= 0 || mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipDilateLoop[iTypeWSSize] > 20){
            m_LineEdit[WSTAIN_DILATE_LOOP]->setText("1");
            mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipDilateLoop[iTypeWSSize]               = QString2Int(m_LineEdit[WSTAIN_ERODE_LOOP]->text().trimmed());
        }

        mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipRemoveEdge[iTypeWSSize]              = QString2Int(m_LineEdit[WSTAIN_REMOVE_EDGE]->text().trimmed());
        mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipRemoveConner[iTypeWSSize]            = QString2Int(m_LineEdit[WSTAIN_REMOVE_CONNER]->text().trimmed());

        if((m_LineEdit[WSTAIN_FILTER_AREA]->text().split(",").count()) == 2){
            mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipFilterAreaMin[iTypeWSSize]     = QString2Point(m_LineEdit[WSTAIN_FILTER_AREA]->text().trimmed()).x;
            mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipFilterAreaMax[iTypeWSSize]     = QString2Point(m_LineEdit[WSTAIN_FILTER_AREA]->text().trimmed()).y;
        }
        else{
            QMessageBox::warning(this,"Error","WhiteStain Filter Area input fail (Format: min,max)");
            return;
        }

        if((m_LineEdit[WSTAIN_FILTER_WIDTH]->text().split(",").count()) == 2){
            mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipFilterWMin[iTypeWSSize]        = QString2Point(m_LineEdit[WSTAIN_FILTER_WIDTH]->text().trimmed()).x;
            mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipFilterWMax[iTypeWSSize]        = QString2Point(m_LineEdit[WSTAIN_FILTER_WIDTH]->text().trimmed()).y;
        }
        else{
            QMessageBox::warning(this,"Error","WhiteStain Filter Width input fail (Format: min,max)");
            return;
        }

        if((m_LineEdit[WSTAIN_FILTER_HEIGHT]->text().split(",").count()) == 2){
            mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipFilterHMin[iTypeWSSize]        = QString2Point(m_LineEdit[WSTAIN_FILTER_HEIGHT]->text().trimmed()).x;
            mGeneral[PARA_CONTAIN].spWhiteStain[iTypeCam].ipFilterHMax[iTypeWSSize]        = QString2Point(m_LineEdit[WSTAIN_FILTER_HEIGHT]->text().trimmed()).y;
        }
        else{
            QMessageBox::warning(this,"Error","WhiteStain Filter Height input fail (Format: min,max)");
            return;
        }


        /*Glare Check*/
        int iRoi                                                                       = m_ComboBox[ROI_GLARE]->currentIndex();
        mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgThreshold[iRoi]                    = QString2Int(m_LineEdit[GLARE_THRESHOLD]->text().trimmed());
        if(mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgThreshold[iRoi] < 0 || mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgThreshold[iRoi] > 255){
            m_LineEdit[GLARE_THRESHOLD]->setText("128");
            mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgThreshold[iRoi]                    = QString2Int(m_LineEdit[GLARE_THRESHOLD]->text().trimmed());
        }
        mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgBlurSize[iRoi]                     = QString2Int(m_LineEdit[GLARE_BLUR_SIZE]->text().trimmed());

        if(mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgBlurSize[iRoi] %2 == 0 || mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgBlurSize[iRoi] <= 1){
            m_LineEdit[GLARE_BLUR_SIZE]->setText("3");
            mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgBlurSize[iRoi]                     = QString2Int(m_LineEdit[GLARE_BLUR_SIZE]->text().trimmed());

        }

        if(m_LineEdit[GLARE_ROI1]->text().split(",").count() == 4){
            mGeneral[PARA_CONTAIN].spGlare[iTypeCam].rpRoi[iRoi]                       = QString2Rect(m_LineEdit[GLARE_ROI1]->text().trimmed());
        }
        else{
            QMessageBox::warning(this,"Error","Glare Roi input fail (Format: x,y,width,height)");
            return;
        }


        mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgErodeSize[iRoi]                          = QString2Int(m_LineEdit[GLARE_ERODE_SIZE]->text().trimmed());
        if(mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgErodeSize[iRoi] %2 == 0 || mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgErodeSize[iRoi] <= 1){
            m_LineEdit[GLARE_ERODE_SIZE]->setText("3");
            mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgErodeSize[iRoi]                     = QString2Int(m_LineEdit[GLARE_ERODE_SIZE]->text().trimmed());

        }
        mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgErodeLoop[iRoi]                          = QString2Int(m_LineEdit[GLARE_ERODE_LOOP]->text().trimmed());
        if(mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgErodeLoop[iRoi] <= 0 || mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgErodeLoop[iRoi] > 20){
            m_LineEdit[GLARE_ERODE_LOOP]->setText("3");
            mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgErodeLoop[iRoi]                          = QString2Int(m_LineEdit[GLARE_ERODE_LOOP]->text().trimmed());
        }
        mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgDilateSize[iRoi]                         = QString2Int(m_LineEdit[GLARE_DILATE_SIZE]->text().trimmed());
        if(mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgDilateSize[iRoi] %2 ==0 || mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgDilateSize[iRoi] <= 1){
            m_LineEdit[GLARE_DILATE_SIZE]->setText("3");
            mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgDilateSize[iRoi]                         = QString2Int(m_LineEdit[GLARE_DILATE_SIZE]->text().trimmed());
        }

        mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgDilateLoop[iRoi]                         = QString2Int(m_LineEdit[GLARE_DILATE_LOOP]->text().trimmed());
        if(mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgDilateLoop[iRoi] <=0 || mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgDilateLoop[iRoi] > 20){
            m_LineEdit[GLARE_DILATE_LOOP]->setText("1");
            mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgDilateLoop[iRoi]                         = QString2Int(m_LineEdit[GLARE_DILATE_LOOP]->text().trimmed());
        }
        mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgRemoveConner[iRoi]                       = QString2Int(m_LineEdit[GLARE_REMOVE_EDGE]->text().trimmed());
        mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgRemoveEdge[iRoi]                         = QString2Int(m_LineEdit[GLARE_REMOVE_CONNER]->text().trimmed());

        if(m_LineEdit[GLARE_FILTER_MROI1]->text().split(",").count() == 2){
            mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgMSRoiMin[iRoi]                        = QString2Point(m_LineEdit[GLARE_FILTER_MROI1]->text().trimmed()).x;
            mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgMSRoiMax[iRoi]                        = QString2Point(m_LineEdit[GLARE_FILTER_MROI1]->text().trimmed()).y;
        }
        else{
            QMessageBox::warning(this,"Error","Filer Mean Roi input fail (Format: min,max)");
            return;
        }

        /*Filter Area*/
        if(m_LineEdit[GLARE_FILTER_AREA1]->text().split(",").count() == 2){
            mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgFilterAreaMin[iRoi]                      = QString2Point(m_LineEdit[GLARE_FILTER_AREA1]->text().trimmed()).x;
            mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgFilterAreaMax[iRoi]                      = QString2Point(m_LineEdit[GLARE_FILTER_AREA1]->text().trimmed()).y;
        }
        else{
            QMessageBox::warning(this,"Error","Filer Area input fail (Format: min,max)");
            return;
        }

        /*Filter Width*/
        if(m_LineEdit[GLARE_FILTER_WIDTH1]->text().split(",").count() == 2){
            mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgFilterWMin[iRoi]                         = QString2Point(m_LineEdit[GLARE_FILTER_WIDTH1]->text().trimmed()).x;
            mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgFilterWMax[iRoi]                         = QString2Point(m_LineEdit[GLARE_FILTER_WIDTH1]->text().trimmed()).y;
        }
        else{
            QMessageBox::warning(this,"Error","Filer Width input fail (Format: min,max)");
            return;
        }

        /*Filter Height*/
        if(m_LineEdit[GLARE_FILTER_HEIGHT1]->text().split(",").count() == 2){
            mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgFilterHMin[iRoi]                         = QString2Point(m_LineEdit[GLARE_FILTER_HEIGHT1]->text().trimmed()).x;
            mGeneral[PARA_CONTAIN].spGlare[iTypeCam].ipgFilterHMax[iRoi]                         = QString2Point(m_LineEdit[GLARE_FILTER_HEIGHT1]->text().trimmed()).y;
        }
        else{
            QMessageBox::warning(this,"Error","Filer Height input fail (Format: min,max)");
            return;
        }

        /*Focus Check*/

        if(m_LineEdit[FOCUS_ROI1]->text().split(",").count() == 4){
            mGeneral[PARA_CONTAIN].spFocus[iTypeCam].rpRoi[0]                              = QString2Rect(m_LineEdit[FOCUS_ROI1]->text().trimmed());
        }
        else{
            QMessageBox::warning(this,"Error","Focus Roi1 input fail (Format: x,y,width,height)");
            return;
        }

        if(m_LineEdit[FOCUS_ROI2]->text().split(",").count() == 4){
            mGeneral[PARA_CONTAIN].spFocus[iTypeCam].rpRoi[1]                              = QString2Rect(m_LineEdit[FOCUS_ROI2]->text().trimmed());
        }
        else{
            QMessageBox::warning(this,"Error","Focus Roi2 input fail (Format: x,y,width,height)");
            return;
        }

        if(m_LineEdit[FOCUS_ROI3]->text().split(",").count() == 4){
            mGeneral[PARA_CONTAIN].spFocus[iTypeCam].rpRoi[2]                              = QString2Rect(m_LineEdit[FOCUS_ROI3]->text().trimmed());
        }
        else{
            QMessageBox::warning(this,"Error","Focus Roi3 input fail (Format: x,y,width,height)");
            return;
        }

        if(m_LineEdit[FOCUS_ROI4]->text().split(",").count() == 4){
            mGeneral[PARA_CONTAIN].spFocus[iTypeCam].rpRoi[3]                              = QString2Rect(m_LineEdit[FOCUS_ROI4]->text().trimmed());
        }
        else{
            QMessageBox::warning(this,"Error","Focus Roi4 input fail (Format: x,y,width,height)");
            return;
        }

        if(m_LineEdit[FOCUS_ROI5]->text().split(",").count() == 4){
            mGeneral[PARA_CONTAIN].spFocus[iTypeCam].rpRoi[4]                              = QString2Rect(m_LineEdit[FOCUS_ROI5]->text().trimmed());
        }
        else{
            QMessageBox::warning(this,"Error","Focus Roi5 input fail (Format: x,y,width,height)");
            return;
        }

        if(m_LineEdit[FOCUS_ROI6]->text().split(",").count() == 4){
            mGeneral[PARA_CONTAIN].spFocus[iTypeCam].rpRoi[5]                              = QString2Rect(m_LineEdit[FOCUS_ROI6]->text().trimmed());
        }
        else{
            QMessageBox::warning(this,"Error","Focus Roi6 input fail (Format: x,y,width,height)");
            return;
        }


        if(m_LineEdit[FOCUS_FILTER_SROI1]->text().split(",").count() == 2){
            mGeneral[PARA_CONTAIN].spFocus[iTypeCam].ipgMSRoiMin[0]                        = QString2Point(m_LineEdit[FOCUS_FILTER_SROI1]->text().trimmed()).x;
            mGeneral[PARA_CONTAIN].spFocus[iTypeCam].ipgMSRoiMax[0]                        = QString2Point(m_LineEdit[FOCUS_FILTER_SROI1]->text().trimmed()).y;
        }
        else{
            QMessageBox::warning(this,"Error","Filer std Roi1 input fail (Format: min,max)");
            return;
        }

        if(m_LineEdit[FOCUS_FILTER_SROI2]->text().split(",").count() == 2){
            mGeneral[PARA_CONTAIN].spFocus[iTypeCam].ipgMSRoiMin[1]                        = QString2Point(m_LineEdit[FOCUS_FILTER_SROI2]->text().trimmed()).x;
            mGeneral[PARA_CONTAIN].spFocus[iTypeCam].ipgMSRoiMax[1]                        = QString2Point(m_LineEdit[FOCUS_FILTER_SROI2]->text().trimmed()).y;
        }
        else{
            QMessageBox::warning(this,"Error","Filer std Roi2 input fail (Format: min,max)");
            return;
        }

        if(m_LineEdit[FOCUS_FILTER_SROI3]->text().split(",").count() == 2){
            mGeneral[PARA_CONTAIN].spFocus[iTypeCam].ipgMSRoiMin[2]                        = QString2Point(m_LineEdit[FOCUS_FILTER_SROI3]->text().trimmed()).x;
            mGeneral[PARA_CONTAIN].spFocus[iTypeCam].ipgMSRoiMax[2]                        = QString2Point(m_LineEdit[FOCUS_FILTER_SROI3]->text().trimmed()).y;
        }
        else{
            QMessageBox::warning(this,"Error","Filer std Roi3 input fail (Format: min,max)");
            return;
        }

        if(m_LineEdit[FOCUS_FILTER_SROI4]->text().split(",").count() == 2){
            mGeneral[PARA_CONTAIN].spFocus[iTypeCam].ipgMSRoiMin[3]                        = QString2Point(m_LineEdit[FOCUS_FILTER_SROI4]->text().trimmed()).x;
            mGeneral[PARA_CONTAIN].spFocus[iTypeCam].ipgMSRoiMax[3]                        = QString2Point(m_LineEdit[FOCUS_FILTER_SROI4]->text().trimmed()).y;
        }
        else{
            QMessageBox::warning(this,"Error","Filer std Roi4 input fail (Format: min,max)");
            return;
        }

        if(m_LineEdit[FOCUS_FILTER_SROI5]->text().split(",").count() == 2){
            mGeneral[PARA_CONTAIN].spFocus[iTypeCam].ipgMSRoiMin[4]                        = QString2Point(m_LineEdit[FOCUS_FILTER_SROI5]->text().trimmed()).x;
            mGeneral[PARA_CONTAIN].spFocus[iTypeCam].ipgMSRoiMax[4]                        = QString2Point(m_LineEdit[FOCUS_FILTER_SROI5]->text().trimmed()).y;
        }
        else{
            QMessageBox::warning(this,"Error","Filer std Roi5 input fail (Format: min,max)");
            return;
        }

        if(m_LineEdit[FOCUS_FILTER_SROI6]->text().split(",").count() == 2){
            mGeneral[PARA_CONTAIN].spFocus[iTypeCam].ipgMSRoiMin[5]                        = QString2Point(m_LineEdit[FOCUS_FILTER_SROI6]->text().trimmed()).x;
            mGeneral[PARA_CONTAIN].spFocus[iTypeCam].ipgMSRoiMax[5]                        = QString2Point(m_LineEdit[FOCUS_FILTER_SROI6]->text().trimmed()).y;
        }
        else{
            QMessageBox::warning(this,"Error","Filer std Roi6 input fail (Format: min,max)");
            return;
        }

        /*DrakSport*/
        mGeneral[PARA_CONTAIN].spDarksport[iTypeCam].ipdsThreshold                     = QString2Int(m_LineEdit[DARKSPORT_THRESHOULD]->text().trimmed());
        mGeneral[PARA_CONTAIN].spDarksport[iTypeCam].ipdsBlockSize                     = QString2Int(m_LineEdit[DARKSPORT_BLOCK_SIZE]->text().trimmed());

        if(m_LineEdit[DARKSPORT_FILT_AREA]->text().split(",").count() == 2){
            mGeneral[PARA_CONTAIN].spDarksport[iTypeCam].ipdsFilterAreaMin                 = QString2Point(m_LineEdit[DARKSPORT_FILT_AREA]->text().trimmed()).x;
            mGeneral[PARA_CONTAIN].spDarksport[iTypeCam].ipdsFilterAreaMax                 = QString2Point(m_LineEdit[DARKSPORT_FILT_AREA]->text().trimmed()).y;
        }
        else{
            QMessageBox::warning(this,"Error","Filer Area input fail (Format: min,max)");
            return;
        }

        /*Erong Color*/

        if(m_LineEdit[COLOR_MEANRED]->text().split(",").count() == 2){
            mGeneral[PARA_CONTAIN].spWrongColor[iTypeCam].ipwcMeanRedMin                   = QString2Point(m_LineEdit[COLOR_MEANRED]->text().trimmed()).x;
            mGeneral[PARA_CONTAIN].spWrongColor[iTypeCam].ipwcMeanRedMax                   = QString2Point(m_LineEdit[COLOR_MEANRED]->text().trimmed()).y;
        }
        else{
            QMessageBox::warning(this,"Error","Filer MeanRed input fail (Format: min,max)");
            return;
        }

        if(m_LineEdit[COLOR_MEANGREEN]->text().split(",").count() == 2){
            mGeneral[PARA_CONTAIN].spWrongColor[iTypeCam].ipwcMeanGreenMin                 = QString2Point(m_LineEdit[COLOR_MEANGREEN]->text().trimmed()).x;
            mGeneral[PARA_CONTAIN].spWrongColor[iTypeCam].ipwcMeanGreenMax                 = QString2Point(m_LineEdit[COLOR_MEANGREEN]->text().trimmed()).y;
        }
        else{
            QMessageBox::warning(this,"Error","Filer MeanGreen input fail (Format: min,max)");
            return;
        }

        if(m_LineEdit[COLOR_MEANBLUE]->text().split(",").count() == 2){
            mGeneral[PARA_CONTAIN].spWrongColor[iTypeCam].ipwcMeanBlueMin                  = QString2Point(m_LineEdit[COLOR_MEANBLUE]->text().trimmed()).x;
            mGeneral[PARA_CONTAIN].spWrongColor[iTypeCam].ipwcMeanBlueMax                  = QString2Point(m_LineEdit[COLOR_MEANBLUE]->text().trimmed()).y;
        }
        else{
            QMessageBox::warning(this,"Error","Filer MeanBlue input fail (Format: min,max)");
            return;
        }


        mGeneral[PARA_CONTAIN].ATCMD[AT_UART_USB].send = m_LineEdit[AT_UART_USB_SEND]->text();
        mGeneral[PARA_CONTAIN].ATCMD[AT_UART_USB].respone = m_LineEdit[AT_UART_USB_RESPONE]->text();

        mGeneral[PARA_CONTAIN].ATCMD[AT_HOMECREEN].send = m_LineEdit[AT_HOME_SCREEN_SEND]->text();
        mGeneral[PARA_CONTAIN].ATCMD[AT_HOMECREEN].respone = m_LineEdit[AT_HOME_SCREEN_RESPONE]->text();

        mGeneral[PARA_CONTAIN].ATCMD[AT_OPENIRIS].send = m_LineEdit[AT_OPEN_IRIS_SEND]->text();
        mGeneral[PARA_CONTAIN].ATCMD[AT_OPENIRIS].respone = m_LineEdit[AT_OPEN_IRIS_RESPONE]->text();

        mGeneral[PARA_CONTAIN].ATCMD[AT_CLOSEIRIS].send = m_LineEdit[AT_CLOSE_IRIS_SEND]->text();
        mGeneral[PARA_CONTAIN].ATCMD[AT_CLOSEIRIS].respone = m_LineEdit[AT_CLOSE_IRIS_RESPONE]->text();

        mGeneral[PARA_CONTAIN].ATCMD[AT_OPENFW1].send = m_LineEdit[AT_OPEN_FW1_SEND]->text();
        mGeneral[PARA_CONTAIN].ATCMD[AT_OPENFW1].respone = m_LineEdit[AT_OPEN_FW1_RESPONE]->text();

        mGeneral[PARA_CONTAIN].ATCMD[AT_CLOSEFW1].send = m_LineEdit[AT_CLOSE_FW1_SEND]->text();
        mGeneral[PARA_CONTAIN].ATCMD[AT_CLOSEFW1].respone = m_LineEdit[AT_CLOSE_FW1_RESPONE]->text();

        mGeneral[PARA_CONTAIN].ATCMD[AT_OPENFB1].send = m_LineEdit[AT_OPEN_FB1_SEND]->text();
        mGeneral[PARA_CONTAIN].ATCMD[AT_OPENFB1].respone = m_LineEdit[AT_OPEN_FB1_RESPONE]->text();

        mGeneral[PARA_CONTAIN].ATCMD[AT_CLOSEFB1].send = m_LineEdit[AT_CLOSE_FB1_SEND]->text();
        mGeneral[PARA_CONTAIN].ATCMD[AT_CLOSEFB1].respone = m_LineEdit[AT_CLOSE_FB1_RESPONE]->text();

        mGeneral[PARA_CONTAIN].ATCMD[AT_CAPTURENOAF].send = m_LineEdit[AT_CAPTURE_NOAF_SEND]->text();
        mGeneral[PARA_CONTAIN].ATCMD[AT_CAPTURENOAF].respone = m_LineEdit[AT_CAPTURE_NOAF_RESPONE]->text();

        mGeneral[PARA_CONTAIN].ATCMD[AT_CAPTUREAF].send = m_LineEdit[AT_CAPTURE_AF_SEND]->text();
        mGeneral[PARA_CONTAIN].ATCMD[AT_CAPTUREAF].respone = m_LineEdit[AT_CAPTURE_AF_RESPONE]->text();

        mGeneral[PARA_CONTAIN].ATCMD[AT_CAPTURETRYAF].send = m_LineEdit[AT_CAPTURE_TRYAF_SEND]->text();
        mGeneral[PARA_CONTAIN].ATCMD[AT_CAPTURETRYAF].respone = m_LineEdit[AT_CAPTURE_TRYAF_RESPONE]->text();

        mGeneral[PARA_CONTAIN].ADBCMD[ADB_GET_LIST].send = m_LineEdit[ADB_GET_LIST_SEND]->text();
        mGeneral[PARA_CONTAIN].ADBCMD[ADB_GET_LIST].respone = m_LineEdit[ADB_GET_LIST_RESPONE]->text();

        mGeneral[PARA_CONTAIN].ADBCMD[ADB_PULL_TO_PC].send = m_LineEdit[ADB_PULL_2_PC_SEND]->text();
        mGeneral[PARA_CONTAIN].ADBCMD[ADB_PULL_TO_PC].respone = m_LineEdit[ADB_PULL_2_PC_RESPONE]->text();

        mGeneral[PARA_CONTAIN].ADBCMD[ADB_REMOVE_FOLDER].send = m_LineEdit[ADB_REMOVE_FOLDER_SEND]->text();
        mGeneral[PARA_CONTAIN].ADBCMD[ADB_REMOVE_FOLDER].respone = m_LineEdit[ADB_REMOVE_FOLDER_RESPONE]->text();

        /*Save Data*/
        SaveDataGeneral();
        SaveData();



    }
    catch(Exception &e){
        QString strerror = QString::fromStdString(e.what());
        qDebug()<<"[LoadDataToBufferTemp]"<<strerror;
        QMessageBox::warning(this,"Error",strerror);
    }
}
void MainWindow::DisplayDateTime() {
    QString tTime = qdCurTime.currentDateTime().toString("dd-MM-yyyy \n hh:mm:ss");
    ui-> lblTime->setText(tTime);
}
void MainWindow::AddLogTestManual(QString str,  QColor iColor) {

    qtTime = QTime::currentTime();
    qstrTime = qtTime.toString();

    //set color
    QTableWidgetItem *timeLog = new QTableWidgetItem(QString(qstrTime));
    timeLog->setForeground(Qt::blue);
    timeLog->setTextAlignment(Qt::AlignCenter);

    QTableWidgetItem *logdata = new QTableWidgetItem(QString(str));
    logdata->setForeground(iColor);

    ui->tbwLogTestManual->insertRow(0);
    ui->tbwLogTestManual->setItem(0, 0, timeLog);
    ui->tbwLogTestManual->setItem(0, 1, logdata);

}
void MainWindow::AddDataComport(QString str, QColor iColor) {
    qtTime = QTime::currentTime();
    qstrTime = qtTime.toString();
    ui->tbwReceiverDataCom->insertRow(0);
    //set color
    QTableWidgetItem *timeLog = new QTableWidgetItem(QString(qstrTime));
    timeLog->setForeground(Qt::blue);
    timeLog->setTextAlignment(Qt::AlignCenter);

    QTableWidgetItem *logdata = new QTableWidgetItem(QString(str));

    logdata->setForeground(iColor);

    ui->tbwReceiverDataCom->setItem(0, 0, timeLog);
    ui->tbwReceiverDataCom->setItem(0, 1, logdata);
}
void MainWindow::AddDataCmd(QString str, QColor iColor) {
    qtTime = QTime::currentTime();
    qstrTime = qtTime.toString();
    ui->tbwReceiverDataCmd->insertRow(0);
    //set color
    QTableWidgetItem *timeLog = new QTableWidgetItem(QString(qstrTime));
    timeLog->setForeground(Qt::blue);
    timeLog->setTextAlignment(Qt::AlignCenter);

    QTableWidgetItem *logdata = new QTableWidgetItem(QString(str));

    logdata->setForeground(iColor);

    ui->tbwReceiverDataCmd->setItem(0, 0, timeLog);
    ui->tbwReceiverDataCmd->setItem(0, 1, logdata);
}
void MainWindow::Display_Image(Mat Image,int iLabel) {
    if (Image.empty()){
        return;
    }
    cv::Mat OutImg;
    QImage qImage;
    OutImg = Image.clone();
    if(OutImg.channels() == 3)
        cv::cvtColor(OutImg, OutImg, CV_BGR2RGB);
    else if(OutImg.channels() == 1){
        cv::cvtColor(OutImg, OutImg, CV_GRAY2RGB);
    }
    qImage = QImage(OutImg.data, OutImg.cols, OutImg.rows, OutImg.step, QImage::Format_RGB888);
    switch (iLabel) {
    case SIDE_LEFT:
        ui->displayLeft->setPixmap(QPixmap::fromImage(qImage));
        break;
    case SIDE_RIGHT:
        ui->displayRight->setPixmap(QPixmap::fromImage(qImage));
        break;
    case SIDE_IMAGE:
        ui->display->setPixmap(QPixmap::fromImage(qImage));
        break;


    default:
        break;
    }

}
void MainWindow::ButtonProcess() {
    /***********Auto***********/
    if(QObject::sender()==ui->btnStart) {
        StartPrg();
    }
    else if(QObject::sender()==ui->btnStop) {
        StopPrg();
    }
    else if(QObject::sender()==ui->btnInital) {
        LoadBufferDataGeneral(SIDE_LEFT);
        LoadBufferDataGeneral(SIDE_RIGHT);
        InitFolder();
        InitComport();
        InitProcCam();
    }
    else if(QObject::sender()==ui->btnSave) {
        if (QMessageBox::Yes == QMessageBox::question(this, "Notice", "Are you sure to Save Parameter?", QMessageBox::Yes | QMessageBox::No)) {
            qDebug("Button data::Save is Pressed!");
            GetDataBufferTemp();
            SaveDataGeneral();
            SaveData();

            if(ui->cbbSelectModel->currentIndex() == mGeneral[SIDE_LEFT].Device.ipModel){
                LoadBufferDataGeneral(SIDE_LEFT);
            }
            else if(ui->cbbSelectModel->currentIndex() == mGeneral[SIDE_RIGHT].Device.ipModel){
                LoadBufferDataGeneral(SIDE_RIGHT);
            }
        }
    }
    /***********Manual test***********/
    /*Load from folder*/
    else if(QObject::sender()==ui->btnLoad) {
        qDebug("Button teach::Load is Pressed!");
        if(!ui->manualSimulation->isChecked()){
            QString folderPath = QFileDialog::getOpenFileName(this,tr("Open File"),"",tr("All File(*.*);;JPEG (*.jpg *.jpeg);;PNG (*.png)" ));
            if(!folderPath.isEmpty()){
                ui->edtPath->setText(folderPath);
                AddLogTestManual(folderPath);
                mPattern = imread(folderPath.toStdString(),IMREAD_COLOR);
                if(mPattern.empty()){
                    AddLogTestManual("mPartten empty.");
                    return;
                }
                if(mPattern.channels() != 3){
                    AddLogTestManual("mPartten is not a color image");
                    return;
                }

                iImgWidth = mPattern.cols;
                iImgHeight = mPattern.rows;
                Display_Image(mPattern,SIDE_IMAGE);
            }
        }
        else{
            QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        "/home",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);

            if(dir != "")
                ui->edtPath->setText(dir);
        }
    }
    /* stain Check Small Stain */
    else if(QObject::sender()==ui->btnCheckStain && ui->cbbSelectSizeCheckManual->currentIndex() == TYPE_SIZE_SMALL) {
        qDebug("Button checkStain::Stain With Small Size is Pressed!");
        if(mPattern.empty()){
            AddLogTestManual("mPartten empty.");
            return;
        }

        m_ProcessSStain->code = RUN_MANUAL_TEST;
        if(!m_ProcessSStain->m_bRun)
            m_ProcessSStain->StartThread();
        iLastButton = Btn_Stain;
    }
    /* stain Check Large Stain */
    else if(QObject::sender()==ui->btnCheckStain && ui->cbbSelectSizeCheckManual->currentIndex() == TYPE_SIZE_LARGE) {
        qDebug("Button checkStain::Stain With Large Size is Pressed!");
        if(mPattern.empty()){
            AddLogTestManual("mPartten empty.");
            return;
        }

        m_ProcessLStain->code = RUN_MANUAL_TEST;
        if(!m_ProcessLStain->m_bRun)
            m_ProcessLStain->StartThread();
        iLastButton = Btn_Stain;
    }
    /*Check Small WhiteStain*/
    else if(QObject::sender()==ui->btnCheckWhiteStain && ui->cbbSelectSizeCheckManual->currentIndex() == TYPE_SIZE_SMALL) {
        qDebug("Button CheckWhiteStain::WhiteStain is Pressed!");
        if(mPattern.empty()){
            AddLogTestManual("mPartten empty.");
            return;
        }

        m_ProcessWhiteSStain->code = RUN_MANUAL_TEST;
        if(!m_ProcessWhiteSStain->m_bRun)
            m_ProcessWhiteSStain->StartThread();
        iLastButton = Btn_WhiteStain;
    }

    /*Check Large WhiteStain*/
    else if(QObject::sender()==ui->btnCheckWhiteStain && ui->cbbSelectSizeCheckManual->currentIndex() == TYPE_SIZE_LARGE) {
        qDebug("Button CheckWhiteStain::WhiteStain is Pressed!");
        if(mPattern.empty()){
            AddLogTestManual("mPartten empty.");
            return;
        }

        m_ProcessWhiteLStain->code = RUN_MANUAL_TEST;
        if(!m_ProcessWhiteLStain->m_bRun)
            m_ProcessWhiteLStain->StartThread();
        iLastButton = Btn_WhiteStain;
    }

    /*btnCheckglare*/
    else if(QObject::sender()==ui->btnCheckGlare) {
        qDebug("Button Check Glare::Glare is Pressed!");
        if(mPattern.empty()){
            AddLogTestManual("mPartten empty.");
            return;
        }

        m_ProcessGlare->code = RUN_MANUAL_TEST;
        if(!m_ProcessGlare->m_bRun)
            m_ProcessGlare->StartThread();
        iLastButton = Btn_Glare;
    }

    /*btnDarkSpot*/
    else if(QObject::sender()==ui->btnCheckDarkspot) {
        qDebug("Button btnCheckDarkspot::Darkspot is Pressed!");
        if(mPattern.empty()){
            AddLogTestManual("mPartten empty.");
            return;
        }

        m_ProcessDarkspot->code = RUN_MANUAL_TEST;
        if(!m_ProcessDarkspot->m_bRun)
            m_ProcessDarkspot->StartThread();

        iLastButton = Btn_Darkspot;
    }

    /*btnCheckWrongcolor*/
    else if(QObject::sender()==ui->btnCheckWrongColor) {
        qDebug("Button btnCheckWrongColor::WrongColor is Pressed!");
        if(mPattern.empty()){
            AddLogTestManual("mPartten empty.");
            return;
        }

        m_ProcessWrongColor->code = RUN_MANUAL_TEST;
        if(!m_ProcessWrongColor->m_bRun)
            m_ProcessWrongColor->StartThread();

        iLastButton = Btn_WrongColor;
    }

    //btnCheckFocus
    else if(QObject::sender()==ui->btnCheckFocus) {
        qDebug("Button btnCheckFocus::Focus is Pressed!");
        if(mPattern.empty()){
            AddLogTestManual("mPartten empty.");
            return;
        }

        m_ProcessFocus->code = RUN_MANUAL_TEST;
        if(!m_ProcessFocus->m_bRun)
            m_ProcessFocus->StartThread();

        iLastButton = btn_Focus;
    }

    else if(QObject::sender()==ui->btnOpenDebug) {
        QString cmd = PATH_DB;
        switch (iLastButton) {
        case Btn_None: cmd = PATH_DB; break;
        case Btn_Stain: cmd = PATH_DB_STAIN; break;
        case Btn_WhiteStain: cmd = PATH_DB_WHITESTAIN; break;
        case Btn_Darkspot: cmd = PATH_DB_DARKSPOT; break;
        case Btn_WrongColor: cmd = PATH_DB_COLOR; break;
        case Btn_Glare: cmd = PATH_DB_GLARE; break;
        }

        QDesktopServices::openUrl(cmd);
    }

    /*button folder*/
    else if(QObject::sender() == ui->btnOpenLogFolder){
        QDesktopServices::openUrl(ui->edtFolderLog->text());
    }

    /*folder in*/
    else if(QObject::sender()== ui->lblSk1_folderIn) {
        QDesktopServices::openUrl(mGeneral[SIDE_LEFT].Device.qstrFolderInput);
    }

    else if(QObject::sender()== ui->lblSk2_folderIn) {
        QDesktopServices::openUrl(mGeneral[SIDE_LEFT].Device.qstrFolderInput);
    }

    /*folder out*/
    else if(QObject::sender()==  ui->lblSk1_folderOut) {
        QDesktopServices::openUrl(mGeneral[SIDE_LEFT].Device.qstrFolderOutput);
    }

    else if(QObject::sender()==  ui->lblSk2_folderOut) {
        QDesktopServices::openUrl(mGeneral[SIDE_RIGHT].Device.qstrFolderOutput);
    }
    /*folder phone*/
    else if(QObject::sender() == ui->lblSk1_folderPhone) {
        QDesktopServices::openUrl(mGeneral[SIDE_LEFT].Device.qstrFolderPhone);
    }

    else if(QObject::sender() == ui->lblSk2_folderPhone) {
        QDesktopServices::openUrl(mGeneral[SIDE_RIGHT].Device.qstrFolderPhone);
    }

    else if(QObject::sender() == ui->lblNameProject){
        bool ok;
        QString text = QInputDialog::getText(this, tr("Password"), tr("Pass:"), QLineEdit::Password, /*QDir::home().dirName()*/"Input Password", &ok);
        if (ok && text.contains("cam")) {
            qDebug("Log in ok");
            EnableParamter();
        }
        else{

            QMessageBox::warning(this,"Error","Wrong Password\n Fail");
        }
    }
}

std::vector<QString> MainWindow::GetListComport() {
    vector<QString> listCom;
    foreach(QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
        listCom.push_back(port.portName());
        qstrSerialPort = port.portName();
    }
    return listCom;
}

QString MainWindow::ExeCmd(QString strIn)
{
    QProcess pProcess;
    pProcess.start(strIn.toLocal8Bit());
    //pProcess.waitForFinished(2000);
    pProcess.waitForFinished(5);
    return pProcess.readAll();

}

void MainWindow::ExeCmdATK(QString strIn)
{
    qDebug()<<"adb test ="<<strIn;
    qpManADB->start(strIn.toLocal8Bit());
}

void MainWindow::SendADB(QString strIn, int iSide)
{
    //mutextSendADB[iSide].lock();
    QString strLog = tr("adb::%1=%2").arg(iSide).arg(strIn);
    qDebug()<<strLog;
    WriteLogFile(strLog, iSide);
    qpAuADB[iSide]->start(strIn.toLocal8Bit());
    //mutextSendADB[iSide].unlock();
}

void MainWindow::on_btnScanCOM_clicked()
{
    ui->cbbListComport->clear();
    std::vector<QString> listCom = GetListComport();

    //    QStringList preventCom = mGeneral.comPhysical.split(",");
    //    qDebug()<<preventCom;

    for(QString str:listCom)
    {
        //        if(!mGeneral.comPhysical.contains(str))
        ui->cbbListComport->addItem(str);
    }

    if(listCom.empty() || !ui->cbbListComport->currentText().contains("COM"))
        ui->cbbListComport->addItem("Null");
    ui->cbbListComport->setCurrentIndex(0);
}

void MainWindow::on_btnCoDisComport_clicked() {
    qstrSerialPort = ui->cbbListComport->currentText();
    iBaudRate      = ui->cbbListBaudrate->currentText().toInt();
    if(!qspSerial->isOpen()) {
        if(OpenSerialPort(qstrSerialPort, iBaudRate)){
            ui->btnCoDisComport->setText("Close");
            qDebug()<<qstrSerialPort<<iBaudRate<<" open ok";
        }
        else{
            qDebug()<<"Open fail!";
        }

    }
    else {
        qspSerial->close();
        ui->btnCoDisComport->setText("Open");
        qDebug()<<"Close!";
    }
}

void MainWindow::on_btnSendCOM_clicked()
{
    static QString data = "";
    static  QByteArray cmd;
    if(qspSerial->isOpen()) {
        data = ui->edtDataSendCom->text()+"\r\n";
        cmd = data.toLocal8Bit();
        qspSerial->write(cmd.data());
    }
    else {
        QMessageBox::warning(this, "Error", "Open Com before send data");
    }
}

void MainWindow::on_btnClearCOM_clicked()
{
    ui->tbwReceiverDataCom->clearContents();
    qstrDataSerial.clear();
}

void MainWindow::on_btnScanDevices_clicked() {
    bEnableScanDevices = true;
    GetListDevices();
}

void MainWindow::on_btnSendADB_clicked() {
    QString data = ui->edtDataSendADB->text();
    ExeCmdATK(data);
    if(ui->cbbListFunctionADB->currentIndex()==ADB_GET_LIST)
        bEnableFindImg = true;
}

std::vector<QString> MainWindow::GetListDevices() {
    std::vector<QString> devices;
    ExeCmdATK("adb devices");
    qDebug()<< "send cmt";
    return devices;
}

void MainWindow::on_btnClearCMD_clicked() {
    ui->tbwReceiverDataCmd->clearContents();
}

/* manual Small stain:*/
void MainWindow::VisionSStain(int iCode) {
    int iPara = ui->cbbSelectParameterCheckManual->currentIndex();
    int iCam = ui->cbbSelectCamToCheck->currentIndex();
    bool bDebug = ui->manualDebug->isChecked();
    if(!mGeneral[iPara].bOptCheckStain[iCam]){
        AddLogTestManual("Stain Not Fuction");
        /*stop thread*/
        m_ProcessLStain->StopThread();
        return;
    }
    switch(iCode) {
    case RUN_MANUAL_TEST: {
        AddLogTestManual("Small Size Stain checking...");
        QString path = ui->edtPath->text();
        QString qstrFileName = qdCurTime.currentDateTime().toString("dd-MM-yyyy_hhmmss_") + path.split("/").last();

        /* update ++*/
        _sResVision sRes = fVision.CheckStain(mPattern, mGeneral[iPara], iCam, TYPE_SIZE_SMALL, qstrFileName, bDebug);

        if(sRes.bRes) {
            putText(sRes.mRes, "OK", Point(200,200), CV_FONT_HERSHEY_COMPLEX, 5.5, cv_green, 5);
            AddLogTestManual("Small Check Stain OK");
        }
        else {
            putText(sRes.mRes, "NG", Point(200,200), CV_FONT_HERSHEY_COMPLEX, 5.5, cv_red, 5);
            AddLogTestManual("Small Check Stain NG", Qt::red);
        }

        if(!sRes.mRes.empty())
            Display_Image(sRes.mRes, SIDE_IMAGE);
        /*stop thread*/
        m_ProcessSStain->StopThread();
    }
        break;
    }
}

/* manual Large stain:*/
void MainWindow::VisionLStain(int iCode) {
    int iPara = ui->cbbSelectParameterCheckManual->currentIndex();
    int iCam = ui->cbbSelectCamToCheck->currentIndex();
    bool bDebug = ui->manualDebug->isChecked();
    if(!mGeneral[iPara].bOptCheckStain[iCam]){
        AddLogTestManual("Stain Not Fuction");
        /*stop thread*/
        m_ProcessLStain->StopThread();
        return;
    }
    switch(iCode) {
    case RUN_MANUAL_TEST: {
        AddLogTestManual("Large Size Stain checking...");
        QString path = ui->edtPath->text();
        QString qstrFileName = qdCurTime.currentDateTime().toString("dd-MM-yyyy_hhmmss_") + path.split("/").last();

        /* update ++*/
        _sResVision sRes = fVision.CheckStain(mPattern, mGeneral[iPara], iCam, TYPE_SIZE_LARGE, qstrFileName, bDebug);

        if(sRes.bRes) {
            putText(sRes.mRes, "OK", Point(200,200), CV_FONT_HERSHEY_COMPLEX, 5.5, cv_green, 5);
            AddLogTestManual("Large Check Stain OK");
        }
        else {
            putText(sRes.mRes, "NG", Point(200,200), CV_FONT_HERSHEY_COMPLEX, 5.5, cv_red, 5);
            AddLogTestManual("Large Check Stain NG", Qt::red);
        }
        if(!sRes.mRes.empty())
            Display_Image(sRes.mRes, SIDE_IMAGE);
        /*stop thread*/
        m_ProcessLStain->StopThread();
    }
        break;
    }
}

/*manual white Small stain:*/
void MainWindow::VisionWhiteSStain(int iCode) {
    int iPara = ui->cbbSelectParameterCheckManual->currentIndex();
    int iCam  = ui->cbbSelectCamToCheck->currentIndex();
    bool bDebug = ui->manualDebug->isChecked();
    if(!mGeneral[iPara].bOptCheckWhiteStain[iCam]){
        AddLogTestManual("WhiteStain Not Fuction");
        /*stop thread*/
        m_ProcessWhiteSStain->StopThread();
        return;
    }
    switch(iCode) {
    case RUN_MANUAL_TEST: {
        AddLogTestManual("White Small Size Stain checking");
        QString path = ui->edtPath->text();
        QString strFileName = qdCurTime.currentDateTime().toString("dd-MM-yyyy_hhmmss_") + path.split("/").last();

        _sResVision sRes = fVision.CheckWhiteStain(mPattern,mGeneral[iPara],iCam,TYPE_SIZE_SMALL,strFileName,bDebug);
        if(sRes.bRes) {
            putText(sRes.mRes, "OK", Point(200,200), CV_FONT_HERSHEY_COMPLEX, 5.5, cv_green, 5);
            AddLogTestManual("Small WhiteStain OK");
        }
        else {
            putText(sRes.mRes, "NG", Point(200,200), CV_FONT_HERSHEY_COMPLEX, 5.5, cv_red, 5);
            AddLogTestManual("Small WhiteStain NG", Qt::red);
        }
        if(!sRes.mRes.empty()){
            Display_Image(sRes.mRes, SIDE_IMAGE);
        }
        /*stop thread*/
        m_ProcessWhiteSStain->StopThread();
    }
        break;
    }
}

/*manual white Small stain:*/
void MainWindow::VisionWhiteLStain(int iCode) {
    int iPara = ui->cbbSelectParameterCheckManual->currentIndex();
    int iCam  = ui->cbbSelectCamToCheck->currentIndex();
    bool bDebug = ui->manualDebug->isChecked();
    if(!mGeneral[iPara].bOptCheckWhiteStain[iCam]){
        AddLogTestManual("WhiteStain Not Fuction");
        /*stop thread*/
        m_ProcessWhiteSStain->StopThread();
        return;
    }
    switch(iCode) {
    case RUN_MANUAL_TEST: {
        AddLogTestManual("White Large Size Stain checking");
        QString path = ui->edtPath->text();
        QString strFileName = qdCurTime.currentDateTime().toString("dd-MM-yyyy_hhmmss_") + path.split("/").last();
        _sResVision sRes = fVision.CheckWhiteStain(mPattern,mGeneral[iPara],iCam,TYPE_SIZE_LARGE,strFileName,bDebug);
        if(sRes.bRes) {
            putText(sRes.mRes, "OK", Point(200,200), CV_FONT_HERSHEY_COMPLEX, 5.5, cv_green, 5);
            AddLogTestManual("Large WhiteStain OK");
        }
        else {
            putText(sRes.mRes, "NG", Point(200,200), CV_FONT_HERSHEY_COMPLEX, 5.5, cv_red, 5);
            AddLogTestManual("Large WhiteStain NG", Qt::red);
        }
        if(!sRes.mRes.empty()){
            Display_Image(sRes.mRes, SIDE_IMAGE);
        }
        /*stop thread*/
        m_ProcessWhiteLStain->StopThread();
    }
        break;
    }
}

/* manual glare:*/
void MainWindow::VisionGlare(int iCode) {
    int iPara = ui->cbbSelectParameterCheckManual->currentIndex();
    int iCam  = ui->cbbSelectCamToCheck->currentIndex();
    bool bDebug = ui->manualDebug->isChecked();
    if(!mGeneral[iPara].bOptCheckGlare[iCam]){
        AddLogTestManual("Glare Not Fuction");
        /*stop thread*/
        m_ProcessGlare->StopThread();
        return;
    }
    switch(iCode) {
    case RUN_MANUAL_TEST: {
        AddLogTestManual("Glare checking");
        QString path = ui->edtPath->text();
        QString strFileName = qdCurTime.currentDateTime().toString("dd-MM-yyyy_hhmmss_") + path.split("/").last();
        _sResVision sRes = fVision.CheckGlare(mPattern,mGeneral[iPara],iCam,strFileName,bDebug);
        if(sRes.bRes) {
            putText(sRes.mRes, "OK", Point(200,200), CV_FONT_HERSHEY_COMPLEX, 5.5, cv_green, 5);
            AddLogTestManual("Glare OK");
        }
        else {
            putText(sRes.mRes, "NG", Point(200,200), CV_FONT_HERSHEY_COMPLEX, 5.5, cv_red, 5);
            AddLogTestManual("Glare NG", Qt::red);
        }
        if(!sRes.mRes.empty()){
            Display_Image(sRes.mRes, SIDE_IMAGE);
        }
        /*stop thread*/
        m_ProcessGlare->StopThread();
    }
        break;
    }
}

/* manual dark spot:*/
void MainWindow::VisionDarkSpot(int iCode) {
    int iPara = ui->cbbSelectParameterCheckManual->currentIndex();
    int iCam = ui->cbbSelectCamToCheck->currentIndex();
    bool bDebug = ui->manualDebug->isChecked();
    if(!mGeneral[iPara].bOptDarkSport[iCam]){
        AddLogTestManual("DarkSport Not Fuction");
        /*stop thread*/
        m_ProcessDarkspot->StopThread();
        return;
    }
    switch(iCode) {
    case RUN_MANUAL_TEST: {
        AddLogTestManual("Darkspot checking...");
        QString path = ui->edtPath->text();
        QString strFileName = qdCurTime.currentDateTime().toString("dd-MM-yyyy_hhmmss_") + path.split("/").last()+ ".jpg";


        _sResVision sRes = fVision.CheckDarkspot(mPattern,mGeneral[iPara], iCam, strFileName,bDebug);
        if(sRes.bRes) {
            putText(sRes.mRes, "OK", Point(200,200), CV_FONT_HERSHEY_COMPLEX, 5.5, cv_green, 5);
            AddLogTestManual("Darkspot OK");
        }
        else {
            putText(sRes.mRes, "NG", Point(200,200), CV_FONT_HERSHEY_COMPLEX, 5.5, cv_red, 5);
            AddLogTestManual("Darkspot NG", Qt::red);
        }
        if(!sRes.mRes.empty()){
            Display_Image(sRes.mRes, SIDE_IMAGE);
        }
        /*stop thread*/
        m_ProcessDarkspot->StopThread();
    }
        break;
    }
}

/*manual Wrong color:*/
void MainWindow::VisionWrongColor(int iCode) {
    int iPara = ui->cbbSelectParameterCheckManual->currentIndex();
    int iCam = ui->cbbSelectCamToCheck->currentIndex();
    bool bDebug = ui->manualDebug->isChecked();
    if(!mGeneral[iPara].bOptCheckColor[iCam]){
        AddLogTestManual("WrongColor Not Fuction");
        /*stop thread*/
        m_ProcessWrongColor->StopThread();
        return;
    }
    switch(iCode) {
    case RUN_MANUAL_TEST: {
        AddLogTestManual("Color Checking", Qt::green);
        QString path = ui->edtPath->text();
        QString strFileName = qdCurTime.currentDateTime().toString("dd-MM-yyyy_hhmmss_") + path.split("/").last();
        _sResVision sRes = fVision.CheckColor(mPattern,mGeneral[iPara],iCam,strFileName,bDebug);
        if(sRes.bRes) {
            putText(sRes.mRes, "OK", Point(200,200), CV_FONT_HERSHEY_COMPLEX, 5.5, cv_green, 3);
            AddLogTestManual("Color OK", Qt::green);
        }
        else {
            putText(sRes.mRes, "NG", Point(200,200), CV_FONT_HERSHEY_COMPLEX, 5.5, cv_red, 3);
            AddLogTestManual("Color NG", Qt::red);
        }
        if(!sRes.mRes.empty()){
            Display_Image(sRes.mRes, SIDE_IMAGE);
        }
        /*stop thread*/
        m_ProcessWrongColor->StopThread();
    }
        break;
    }
}

/* manual glare:*/
void MainWindow::VisionFocus(int iCode) {
    int iPara = ui->cbbSelectCamToCheck->currentIndex();
    int iCam  = ui->cbbSelectCamToCheck->currentIndex();
    bool bDebug = ui->manualDebug->isChecked();
    if(!mGeneral[iPara].bOptCheckFocus[iCam]){
        AddLogTestManual("Focus Not Fuction");
        /*stop thread*/
        m_ProcessFocus->StopThread();
        return;
    }
    switch(iCode) {
        case RUN_MANUAL_TEST: {
            AddLogTestManual("Focus checking");
            QString path = ui->edtPath->text();
            QString strFileName = qdCurTime.currentDateTime().toString("dd-MM-yyyy_hhmmss_") + path.split("/").last();
            _sResVision sRes = fVision.CheckFocus(mPattern,mGeneral[iPara],iCam,strFileName, bDebug);
            if(sRes.bRes) {
                putText(sRes.mRes, "OK", Point(200,400), CV_FONT_HERSHEY_COMPLEX, 5.5, cv_green, 5);
                AddLogTestManual("Focus OK");
            }
            else {
                putText(sRes.mRes, "NG", Point(200,400), CV_FONT_HERSHEY_COMPLEX, 5.5, cv_red, 5);
                AddLogTestManual("Focus NG", Qt::red);
            }
            if(!sRes.mRes.empty())
                Display_Image(sRes.mRes, SIDE_IMAGE);
            /*stop thread*/
            m_ProcessFocus->StopThread();
        }
            break;
    }
}

void MainWindow::on_tbwLogLeft_itemClicked(QTableWidgetItem *item) {
    return;
    QString data = item->text();
    qDebug()<<data;

    Mat mShow = imread(data.toStdString());
    Display_Image(mShow,SIDE_LEFT);
}

bool MainWindow::MakeFolder(QString folder) {
    bool bResult = true;
    if(!QDir(folder).exists()) {
        //if(QDir().mkdir())
        if(QDir().mkpath(folder)) {
            qDebug()<<"Make folder: "<<folder;
            QDir(folder).refresh();
        }
        else {
            qDebug()<<"Can't make folder: "<<folder;
            bResult = false;
        }
    }
    else {
        qDebug()<<"folder "<<folder<<" is exits";
    }
    return bResult;
}

void MainWindow::CreatTreePara() {

    m_ComboBox[BLUR_STAIN_TYPE]->addItems(QStringList() << "BLUR" << "GAUSSIAN" << "MEDIAN" << "BOX" << "BILATERAL" << "NONLINEAR DIFF");

    m_ComboBox[BLUR_WSTAIN_TYPE]->addItems(QStringList() << "BLUR" << "GAUSSIAN" << "MEDIAN" << "BOX" << "BILATERAL" << "NONLINEAR DIFF");

    m_ComboBox[BLUR_GLARE_TYPE]->addItems(QStringList() << "BLUR" << "GAUSSIAN" << "MEDIAN" << "BOX" << "BILATERAL" << "NONLINEAR DIFF");

    /* add camera setting treewidget*/
    m_ComboBox[CAMERA_TYPE]->addItems(QStringList() << "FRONT/FW1" << "FB1");
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_SETTING_CAMERA),1,m_ComboBox[CAMERA_TYPE]);
    /* add check box*/
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_OPTION)->child(0),1,m_CheckBox[_SHOW_IMG]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_OPTION)->child(1),1,m_CheckBox[_SAVE_IMG]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_OPTION)->child(2),1,m_CheckBox[_CHECK_IRIS]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_OPTION)->child(3),1,m_CheckBox[_CHECK_STAIN]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_OPTION)->child(4),1,m_CheckBox[_CHECK_WHITESAIN]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_OPTION)->child(5),1,m_CheckBox[_CHECK_GLARE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_OPTION)->child(6),1,m_CheckBox[_CHECK_FOCUS]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_OPTION)->child(7),1,m_CheckBox[_CHECK_COLOR]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_OPTION)->child(8),1,m_CheckBox[_CHECK_DARKSPORT]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_OPTION)->child(9),1,m_CheckBox[_CAP_AF]);

    /* add delay line edit*/
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(0), 1,m_LineEdit[DL_UART_USB_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(1), 1,m_LineEdit[DL_UART_USB_RESPONE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(2), 1,m_LineEdit[DL_HOME_SCREEN_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(3), 1,m_LineEdit[DL_HOME_SCREEN_RESPONE]);

    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(4), 1,m_LineEdit[DL_OPEN_IRIS_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(5), 1,m_LineEdit[DL_OPEN_IRIS_RESPONE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(6), 1,m_LineEdit[DL_CLOSE_IRIS_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(7), 1,m_LineEdit[DL_CLOSE_IRIS_RESPONE]);

    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(8), 1,m_LineEdit[DL_OPEN_FW1_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(9), 1,m_LineEdit[DL_OPEN_FW1_RESPONE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(10),1,m_LineEdit[DL_CLOSE_FW1_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(11),1,m_LineEdit[DL_CLOSE_FW1_RESPONE]);

    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(12),1,m_LineEdit[DL_OPEN_FB1_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(13),1,m_LineEdit[DL_OPEN_FB1_RESPONE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(14),1,m_LineEdit[DL_CLOSE_FB1_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(15),1,m_LineEdit[DL_CLOSE_FB1_RESPONE]);

    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(16),1,m_LineEdit[DL_CAPTURE_NOAF_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(17),1,m_LineEdit[DL_CAPTURE_NOAF_RESPONE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(18),1,m_LineEdit[DL_CAPTURE_AF_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(19),1,m_LineEdit[DL_CAPTURE_AF_RESPONE]);

    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(20),1,m_LineEdit[DL_CAPTURE_TRYAF_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(21),1,m_LineEdit[DL_CAPTURE_TRYAF_RESPONE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(22),1,m_LineEdit[DL_GET_LIST_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(23),1,m_LineEdit[DL_GET_LIST_RESPONE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(24),1,m_LineEdit[DL_PULL_2_PC_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(25),1,m_LineEdit[DL_PULL_2_PC_RESPONE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(26),1,m_LineEdit[DL_REMOVE_FOLDER_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(27),1,m_LineEdit[DL_REMOVE_FOLDER_RESPONE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(28),1,m_LineEdit[DL_CLYNDER_FORWARD]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_DELAY_TIME)->child(29),1,m_LineEdit[DL_CLYNDER_BACKWARD]);

    /*add pain treewidget*/
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_PAINT)->child(0),1,m_LineEdit[PAINT_THICKNESS]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_PAINT)->child(1),1,m_LineEdit[PAINT_OFFSET]);

    /*add normalize treewidget*/
    m_ComboBox[NOR_TYPE]->addItems(QStringList() << "INF" << "L1" << "L2" << "MINMAX");
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_NORMALIZE)->child(0),1,m_ComboBox[NOR_TYPE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_NORMALIZE)->child(1),1,m_LineEdit[NOR_BETA]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_NORMALIZE)->child(2),1,m_LineEdit[NOR_ALPHA]);

    /*add stain small treewidget*/
    m_ComboBox[STAIN_SIZE]->addItems(QStringList() << "SMALL" << "LARGE");
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_STAIN),1,m_ComboBox[STAIN_SIZE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_STAIN)->child(0),1,m_LineEdit [STAIN_THRESHOLD]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_STAIN)->child(1),1,m_LineEdit [STAIN_BLOCKSIZE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_STAIN)->child(2),1,m_LineEdit [STAIN_BLURSIZE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_STAIN)->child(2)->child(0),1,m_ComboBox[BLUR_STAIN_TYPE]);

    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_STAIN)->child(3),1,m_LineEdit [STAIN_ERODE_SIZE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_STAIN)->child(4),1,m_LineEdit [STAIN_ERODE_LOOP]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_STAIN)->child(5),1,m_LineEdit [STAIN_DILATE_SIZE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_STAIN)->child(6),1,m_LineEdit [STAIN_DILATE_LOOP]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_STAIN)->child(7),1,m_LineEdit [STAIN_REMOVE_EDGE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_STAIN)->child(8),1,m_LineEdit [STAIN_REMOVE_CONNER]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_STAIN)->child(9),1,m_LineEdit [STAIN_FILTER_AREA]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_STAIN)->child(10),1,m_LineEdit[STAIN_FILTER_WIDTH]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_STAIN)->child(11),1,m_LineEdit[STAIN_FILTER_HEIGHT]);

    /*add whitestain treewidget*/
    m_ComboBox[WSTAIN_SIZE]->addItems(QStringList() << "SMALL" << "LARGE");
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_WHITESTAIN),1,m_ComboBox[WSTAIN_SIZE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_WHITESTAIN)->child(0),1,m_LineEdit [WSTAIN_THRESHOLD]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_WHITESTAIN)->child(1),1,m_LineEdit [WSTAIN_BLOCKSIZE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_WHITESTAIN)->child(2),1,m_LineEdit [WSTAIN_BLURSIZE]);

    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_WHITESTAIN)->child(2)->child(0),1,m_ComboBox[BLUR_WSTAIN_TYPE]);

    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_WHITESTAIN)->child(3),1,m_LineEdit [WSTAIN_ERODE_SIZE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_WHITESTAIN)->child(4),1,m_LineEdit [WSTAIN_ERODE_LOOP]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_WHITESTAIN)->child(5),1,m_LineEdit [WSTAIN_DILATE_SIZE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_WHITESTAIN)->child(6),1,m_LineEdit [WSTAIN_DILATE_LOOP]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_WHITESTAIN)->child(7),1,m_LineEdit [WSTAIN_REMOVE_EDGE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_WHITESTAIN)->child(8),1,m_LineEdit [WSTAIN_REMOVE_CONNER]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_WHITESTAIN)->child(9),1,m_LineEdit [WSTAIN_FILTER_AREA]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_WHITESTAIN)->child(10),1,m_LineEdit[WSTAIN_FILTER_WIDTH]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_WHITESTAIN)->child(11),1,m_LineEdit[WSTAIN_FILTER_HEIGHT]);

    /*add glare treewidget*/
    m_ComboBox[ROI_GLARE]->addItems(QStringList()<<"Roi1"<<"Roi2"<<"Roi3"<<"Roi4"<<"Roi5"<<"Roi6");
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_GLARE),1,m_ComboBox[ROI_GLARE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_GLARE)->child(0),1,m_LineEdit[GLARE_THRESHOLD]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_GLARE)->child(1),1,m_LineEdit[GLARE_BLUR_SIZE]);

     ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_GLARE)->child(1)->child(0),1,m_ComboBox[BLUR_GLARE_TYPE]);

    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_GLARE)->child(2),1,m_LineEdit[GLARE_ROI1]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_GLARE)->child(3),1,m_LineEdit[GLARE_ERODE_SIZE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_GLARE)->child(4),1,m_LineEdit[GLARE_ERODE_LOOP]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_GLARE)->child(5),1,m_LineEdit[GLARE_DILATE_SIZE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_GLARE)->child(6),1,m_LineEdit[GLARE_DILATE_LOOP]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_GLARE)->child(7),1,m_LineEdit[GLARE_REMOVE_EDGE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_GLARE)->child(8),1,m_LineEdit[GLARE_REMOVE_CONNER]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_GLARE)->child(9),1,m_LineEdit[GLARE_FILTER_MROI1]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_GLARE)->child(10),1,m_LineEdit[GLARE_FILTER_AREA1]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_GLARE)->child(11),1,m_LineEdit[GLARE_FILTER_WIDTH1]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_GLARE)->child(12),1,m_LineEdit[GLARE_FILTER_HEIGHT1]);


    //add focus treewidget
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_FOCUS)->child(0),1,m_LineEdit[FOCUS_ROI1]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_FOCUS)->child(1),1,m_LineEdit[FOCUS_ROI2]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_FOCUS)->child(2),1,m_LineEdit[FOCUS_ROI3]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_FOCUS)->child(3),1,m_LineEdit[FOCUS_ROI4]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_FOCUS)->child(4),1,m_LineEdit[FOCUS_ROI5]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_FOCUS)->child(5),1,m_LineEdit[FOCUS_ROI6]);

    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_FOCUS)->child(6),1,m_LineEdit[FOCUS_FILTER_SROI1]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_FOCUS)->child(7),1,m_LineEdit[FOCUS_FILTER_SROI2]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_FOCUS)->child(8),1,m_LineEdit[FOCUS_FILTER_SROI3]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_FOCUS)->child(9),1,m_LineEdit[FOCUS_FILTER_SROI4]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_FOCUS)->child(10),1,m_LineEdit[FOCUS_FILTER_SROI5]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_FOCUS)->child(11),1,m_LineEdit[FOCUS_FILTER_SROI6]);

    // add darksport treewidget
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_DARKSPORT)->child(0),1,m_LineEdit[DARKSPORT_THRESHOULD]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_DARKSPORT)->child(1),1,m_LineEdit[DARKSPORT_BLOCK_SIZE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_DARKSPORT)->child(2),1,m_LineEdit[DARKSPORT_FILT_AREA]);

    //add wrongcolor treewidget
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_WRONGCOLOR)->child(0),1,m_LineEdit[COLOR_MEANRED]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_WRONGCOLOR)->child(1),1,m_LineEdit[COLOR_MEANGREEN]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_WRONGCOLOR)->child(2),1,m_LineEdit[COLOR_MEANBLUE]);

    //add AT command treewidget
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ATCMD)->child(0)->child(0),1,m_LineEdit[AT_UART_USB_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ATCMD)->child(0)->child(1),1,m_LineEdit[AT_UART_USB_RESPONE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ATCMD)->child(1)->child(0),1,m_LineEdit[AT_HOME_SCREEN_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ATCMD)->child(1)->child(1),1,m_LineEdit[AT_HOME_SCREEN_RESPONE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ATCMD)->child(2)->child(0),1,m_LineEdit[AT_OPEN_IRIS_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ATCMD)->child(2)->child(1),1,m_LineEdit[AT_OPEN_IRIS_RESPONE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ATCMD)->child(3)->child(0),1,m_LineEdit[AT_CLOSE_IRIS_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ATCMD)->child(3)->child(1),1,m_LineEdit[AT_CLOSE_IRIS_RESPONE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ATCMD)->child(4)->child(0),1,m_LineEdit[AT_OPEN_FW1_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ATCMD)->child(4)->child(1),1,m_LineEdit[AT_OPEN_FW1_RESPONE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ATCMD)->child(5)->child(0),1,m_LineEdit[AT_CLOSE_FW1_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ATCMD)->child(5)->child(1),1,m_LineEdit[AT_CLOSE_FW1_RESPONE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ATCMD)->child(6)->child(0),1,m_LineEdit[AT_OPEN_FB1_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ATCMD)->child(6)->child(1),1,m_LineEdit[AT_OPEN_FB1_RESPONE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ATCMD)->child(7)->child(0),1,m_LineEdit[AT_CLOSE_FB1_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ATCMD)->child(7)->child(1),1,m_LineEdit[AT_CLOSE_FB1_RESPONE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ATCMD)->child(8)->child(0),1,m_LineEdit[AT_CAPTURE_NOAF_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ATCMD)->child(8)->child(1),1,m_LineEdit[AT_CAPTURE_NOAF_RESPONE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ATCMD)->child(9)->child(0),1,m_LineEdit[AT_CAPTURE_AF_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ATCMD)->child(9)->child(1),1,m_LineEdit[AT_CAPTURE_AF_RESPONE]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ATCMD)->child(10)->child(0),1,m_LineEdit[AT_CAPTURE_TRYAF_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ATCMD)->child(10)->child(1),1,m_LineEdit[AT_CAPTURE_TRYAF_RESPONE]);

    // add ADB command treewidget
    ui->treeWidget_Parameter->topLevelItem(_PARA_ADBCMD)->child(0)->child(0)->setToolTip(0,"adb -s %1 shell ls /storage/emulated/0/fImage /r/n %1: ID Set");
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ADBCMD)->child(0)->child(0),1,m_LineEdit[ADB_GET_LIST_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ADBCMD)->child(0)->child(1),1,m_LineEdit[ADB_GET_LIST_RESPONE]);
    ui->treeWidget_Parameter->topLevelItem(_PARA_ADBCMD)->child(1)->child(0)->setToolTip(0,"adb -s %1 pull /storage/emulated/0/fImage %2 /r/n %1: ID Set /r/n %2: FolderInput");
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ADBCMD)->child(1)->child(0),1,m_LineEdit[ADB_PULL_2_PC_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ADBCMD)->child(1)->child(1),1,m_LineEdit[ADB_PULL_2_PC_RESPONE]);
    ui->treeWidget_Parameter->topLevelItem(_PARA_ADBCMD)->child(2)->child(0)->setToolTip(0,"adb -s %1 shell rm -r /storage/emulated/0/fImage /r/n %1: ID Set");
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ADBCMD)->child(2)->child(0),1,m_LineEdit[ADB_REMOVE_FOLDER_SEND]);
    ui->treeWidget_Parameter->setItemWidget(ui->treeWidget_Parameter->topLevelItem(_PARA_ADBCMD)->child(2)->child(1),1,m_LineEdit[ADB_REMOVE_FOLDER_RESPONE]);
}

void MainWindow::WriteLogFile(QString data, int iSide) {
    QString tTime = qdCurTime.currentDateTime().toString("hh:mm:ss:");
    if(qfLog[iSide].isOpen()) {
        QString str = tTime + "\t" + data + "\n";
        QTextStream qStream(&qfLog[iSide]);
        qStream << str;
    }
}

void MainWindow::WriteLogComIO(QString data) {
    //    QString tTime = qdCurTime.currentDateTime().toString("hh:mm:ss:");
    //    if(qLogComIO.isOpen())
    //    {
    //        QString str = tTime + "\t" + data + "\n";
    //        QTextStream qStream(&logComIO);
    //        qStream << str;
    //    }
}

void MainWindow::CloseLogFile() {
    for(int i = 0; i<NUM_SIDE; i++) {
        if(qfLog[i].isOpen()) {
            qfLog[i].close();
            qDebug()<< qstrLogFile[i] + " close file" ;
        }
    }

    //    //close com phone jig
    //    if(logComIO.isOpen()){
    //        logComIO.close();
    //        qDebug()<< " close log file ID jig" ;
    //    }
}

/* button All*/
void MainWindow::on_btnDisconnectAll_clicked() {

    for(int i =0; i<NUM_SIDE; i++){

        QString strCOM = tr("Close com %1").arg(i);
        if(CloseCom(qspAuComport[i])){
            AddDataComport(strCOM + " OK");
        }
        else{
            AddDataComport(strCOM + "NG");
        }

    }

    //close comport
    if(CloseCom(qspSerial)){
        AddDataComport("Close com test ok");
    }
    else{
        AddDataComport("Close com test ng");
    }

    //close comport IO
    if(CloseCom(qspAuComIO[SIDE_LEFT])){
        AddDataComport("Close comIO left ok");
    }
    else{
        AddDataComport("Close comIO left ng");
    }

    //close comport IO
    if(CloseCom(qspAuComIO[SIDE_RIGHT])){
        AddDataComport("Close comIO right ok");
    }
    else{
        AddDataComport("Close comIO right ng");
    }



    ui->btnCoDisComport->setText("Open");
}

void MainWindow::on_btnOpenATK_clicked() {
    /* QString cmd = mGeneral.folderLog +"/fImage";*/
    /* QDesktopServices::openUrl(cmd);*/
}

void MainWindow::on_btnDelATK_clicked() {
    /*    QString cmd = mGeneral.folderLog +"/fImage";     */
    /*    QDir dir(cmd);                                   */
    /*    dir.removeRecursively();                         */
}


void MainWindow::on_btnOpenClear_clicked() {
    ui->tbwLogTestManual->clearContents();
}

void MainWindow::on_btnClearFolderOutput_clicked() {
    QDir dirLeft(mGeneral[SIDE_LEFT].Device.qstrFolderOutput);
    QDir dirRight(mGeneral[SIDE_RIGHT].Device.qstrFolderOutput);
    if (QMessageBox::Yes == QMessageBox::question(this, "Notice", "Are you sure to Clear Image?", QMessageBox::Yes | QMessageBox::No)) {
        switch (ui->cbbSelectSideToDel->currentIndex()) {
        case SIDE_LEFT:
            dirLeft.refresh();
            dirLeft.removeRecursively();
            break;
        case SIDE_RIGHT:
            dirRight.refresh();
            dirRight.removeRecursively();
            break;
        case 4:
            dirLeft.refresh();
            dirLeft.removeRecursively();

            dirRight.refresh();
            dirRight.removeRecursively();

            break;
        }
        for(int i=0; i<NUM_SIDE; i++){
            MakeFolder(mGeneral[i].Device.qstrFolderOutput);
        }
        QMessageBox::information(this,"Infor","Done");
    }
}

void MainWindow::on_btnClearFolderPhone_clicked() {
    QDir dirLeft(mGeneral[SIDE_LEFT].Device.qstrFolderPhone);
    QDir dirRight(mGeneral[SIDE_RIGHT].Device.qstrFolderPhone);
    if (QMessageBox::Yes == QMessageBox::question(this, "Notice", "Are you sure to Clear Image?", QMessageBox::Yes | QMessageBox::No)) {
        switch (ui->cbbSelectSideToDel->currentIndex()) {
        case SIDE_LEFT:
            dirLeft.refresh();
            dirLeft.removeRecursively();
            break;

        case SIDE_RIGHT:
            dirRight.refresh();
            dirRight.removeRecursively();
            break;
        case 4:
            dirLeft.refresh();
            dirLeft.removeRecursively();
            dirRight.refresh();
            dirRight.removeRecursively();
            break;

        }
        for(int i=0; i<NUM_SIDE; i++){
            MakeFolder(mGeneral[i].Device.qstrFolderPhone);
        }
        QMessageBox::information(this,"Infor","Done");
    }
}

void MainWindow::on_btnDelLog_clicked()
{
    ui->cbbListFunctionADB->setCurrentIndex(ADB_REMOVE_LOG);

    QString cmd = QString(listADB[ADB_REMOVE_LOG]).arg(ui->cbbListDevices->currentText());
    ui->edtDataSendADB->setText(cmd);
}

void MainWindow::on_btnLogo_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Password"), tr("Pass:"), QLineEdit::Password, /*QDir::home().dirName()*/"Input Password", &ok);
    if (ok && text.contains("cam")) {
        qDebug("Log in ok");
        EnableParamter();
    }
    else{

        QMessageBox::warning(this,"Error","Wrong Password\n Fail");
    }
}

void MainWindow::DisableParameter() {

    for(int i = 0 ; i<NUM_LINEDIT ; i++){

        m_LineEdit[i]->setEnabled(false);
    }

    for(int i = 0 ; i<NUM_CHECKBOX ; i++){

        m_CheckBox[i]->setEnabled(false);
    }

    //    for(int i = 0 ; i<NUM_COMBOBOX ; i++){

    //        m_ComboBox[i]->setEnabled(false);
    //    }

    ui->btnSave->setEnabled(false);
    m_ComboBox[NOR_TYPE]->setEnabled(false);
    ui->edtVersion->setEnabled(false);
    ui->edtFolderLog->setEnabled(false);
    /*socket left*/
    ui->edtComLeft->setEnabled(false);
    ui->checkBoxUseLeft->setEnabled(false);
    ui->edtIDLeft->setEnabled(false);
    ui->edtKeyStartLeft->setEnabled(false);

    ui->edtInputFolderLeft->setEnabled(false);
    ui->edtOutputFolderLeft->setEnabled(false);
    ui->edtPhoneFolderLeft->setEnabled(false);

    ui->cbbSelectModel_Left->setEnabled(false);
    ui->edtComportIO_Left->setEnabled(false);
    ui->checkBoxUseComportIO_Left->setEnabled(false);

    /*socket right*/
    ui->edtComRight->setEnabled(false);
    ui->checkBoxUseRight->setEnabled(false);
    ui->edtIDRight->setEnabled(false);
    ui->edtKeyStartRight->setEnabled(false);

    ui->edtInputFolderRight->setEnabled(false);
    ui->edtOutputFolderRight->setEnabled(false);
    ui->edtPhoneFolderRight->setEnabled(false);

    ui->cbbSelectModel_Right->setEnabled(false);
    ui->edtComportIO_Right->setEnabled(false);
    ui->checkBoxUseComportIO_Right->setEnabled(false);
}

void MainWindow::EnableParamter() {

    for(int i = 0 ; i<NUM_LINEDIT ; i++){

        m_LineEdit[i]->setEnabled(true);
    }

    for(int i = 0 ; i<NUM_CHECKBOX ; i++){

        m_CheckBox[i]->setEnabled(true);
    }

    ui->btnSave->setEnabled(true);
    m_ComboBox[NOR_TYPE]->setEnabled(true);

    ui->edtVersion->setEnabled(true);
    ui->edtFolderLog->setEnabled(true);
    /*socket left*/
    ui->edtComLeft->setEnabled(true);
    ui->checkBoxUseLeft->setEnabled(true);
    ui->edtIDLeft->setEnabled(true);
    ui->edtKeyStartLeft->setEnabled(true);

    ui->edtInputFolderLeft->setEnabled(true);
    ui->edtOutputFolderLeft->setEnabled(true);
    ui->edtPhoneFolderLeft->setEnabled(true);

    ui->cbbSelectModel_Left->setEnabled(true);
    ui->edtComportIO_Left->setEnabled(true);
    ui->checkBoxUseComportIO_Left->setEnabled(true);

    /*socket right*/
    ui->edtComRight->setEnabled(true);
    ui->checkBoxUseRight->setEnabled(true);
    ui->edtIDRight->setEnabled(true);
    ui->edtKeyStartRight->setEnabled(true);

    ui->edtInputFolderRight->setEnabled(true);
    ui->edtOutputFolderRight->setEnabled(true);
    ui->edtPhoneFolderRight->setEnabled(true);

    ui->cbbSelectModel_Right->setEnabled(true);
    ui->edtComportIO_Right->setEnabled(true);
    ui->checkBoxUseComportIO_Right->setEnabled(true);
}


void MainWindow::on_btnDeviceManeger_clicked() {

    system("C:/Windows/System32/devmgmt.msc");
}

void MainWindow::on_btnADBCMD_clicked() {
    QString cmdfile = QDir::currentPath() + "/cmd-here.exe";
    if(!QDesktopServices::openUrl(cmdfile)) {
        QMessageBox::warning(this,"Open adb-cmd","Not found file: \r\n" + cmdfile);
    }
}

void MainWindow::on_btnADBKillserver_clicked() {
    ExeCmdATK("adb kill-server");
}

void MainWindow::on_btnInital_clicked() {
    ui->tbwLogLeft->clearContents();
    ui->tbwLogRight->clearContents();
}

void MainWindow::on_cbbSelectModel_currentIndexChanged(int iIndex) {
    try{
        LoadBufferDataParaCheck(PARA_CONTAIN,iIndex);
        InitGUI(iIndex);
    }
    catch(exception e){
        QMessageBox::warning(this,"Open Model","Not found file!");
    }
}

void MainWindow::on_tabWidget_tabBarClicked(int iIndex) {
    if(iIndex != DATA){
        DisableParameter();
    }
    switch(iIndex) {
    case AUTO:
        qDebug("Auto Dlg");
        break;
    case MANUAL:
        //scan comport and show combobox
        this->on_btnScanCOM_clicked();
        qDebug("MAnual Dlg");
        break;
    case TEACH:
        qDebug("Teach Dlg");
        break;
    case DATA:
        qDebug("Data Dlg");
        break;
    }
}

void MainWindow::on_cbbSelectParaCam_activated(int iInDexCam) {
    int iIdxModel = ui->cbbSelectModel->currentIndex();
    InitUiParameterCam(iIdxModel,iInDexCam);
}

void MainWindow::on_cbbSizeStain_activated(int iInDexSize) {
    /*Load json file*/
    QJsonDocument loadData = loadJson(tr(PATH_GENERAL).arg(listModel[ui->cbbSelectModel->currentIndex()]) + PATH_NAME);
    QJsonObject   json = loadData.object();
    int iCamType  = m_ComboBox[CAMERA_TYPE]->currentIndex();
    int iSizeType = iInDexSize;
    InitUiParameterStain(iCamType, iSizeType, json);
}

void MainWindow::on_cbbSizeWhiteStain_activated(int iInDexSize) {
    /*Load json file*/
    QJsonDocument loadData = loadJson(tr(PATH_GENERAL).arg(listModel[ui->cbbSelectModel->currentIndex()]) + PATH_NAME);
    QJsonObject   json = loadData.object();
    int iCamType  = m_ComboBox[CAMERA_TYPE]->currentIndex();
    int iSizeType = iInDexSize;
    InitUiParameterWhiteStain(iCamType, iSizeType, json);
}

void MainWindow::on_cbbRoiGlare_activated(int iInDex)
{
    /*Load json file*/
    QJsonDocument loadData = loadJson(tr(PATH_GENERAL).arg(listModel[ui->cbbSelectModel->currentIndex()]) + PATH_NAME);
    QJsonObject   json = loadData.object();
    int iCamType  = m_ComboBox[CAMERA_TYPE]->currentIndex();
    int iRoi = iInDex + 1;
    InitUiParameterGlare(iCamType, iRoi, json);
}

MTickTimer t,t1;
void MainWindow::on_btn_clynderFWD_left_clicked()
{
    emit pProc[SIDE_LEFT]->emitThreadIO(Output1_ON);
    emit pProc[SIDE_LEFT]->emitThreadIO(Output2_OFF);
}


void MainWindow::on_btn_clynderMID_left_clicked()
{
    if(pProc[SIDE_LEFT]->ptrIO->m_InClynderMID) return;


    if(pProc[SIDE_LEFT]->ptrIO->m_InClynderBWD){

        emit pProc[SIDE_LEFT]->emitThreadIO(Output1_ON);
        QThread::msleep(50);
        emit pProc[SIDE_LEFT]->emitThreadIO(Output2_OFF);
        t.StartTimer();
        while(t.LessThan(10) && !pProc[SIDE_LEFT]->ptrIO->m_InClynderMID){
            emit pProc[SIDE_LEFT]->emitThreadIO(Output1_OFF);
            emit pProc[SIDE_LEFT]->emitThreadIO(Output2_OFF);
        }
    }
    else if(pProc[SIDE_LEFT]->ptrIO->m_InClynderFWD){
        emit pProc[SIDE_LEFT]->emitThreadIO(Output1_OFF);
        emit pProc[SIDE_LEFT]->emitThreadIO(Output2_ON);
        t.StartTimer();
        while(t.LessThan(10) && !pProc[SIDE_LEFT]->ptrIO->m_InClynderMID){
            emit pProc[SIDE_LEFT]->emitThreadIO(Output1_OFF);
            emit pProc[SIDE_LEFT]->emitThreadIO(Output2_OFF);
        }
    }

}

void MainWindow::on_btn_clynderBWD_left_clicked()
{
    emit pProc[SIDE_LEFT]->emitThreadIO(Output1_OFF);

    emit pProc[SIDE_LEFT]->emitThreadIO(Output2_ON);
}

void MainWindow::on_btn_ledON_left_clicked()
{
    emit pProc[SIDE_LEFT]->emitThreadIO(Output4_ON);

}

void MainWindow::on_btn_ledOFF_left_clicked()
{
    emit pProc[SIDE_LEFT]->emitThreadIO(Output4_OFF);
}

void MainWindow::on_btn_clynderFWD_right_clicked()
{

    emit pProc[SIDE_RIGHT]->emitThreadIO(Output1_ON);
    emit pProc[SIDE_RIGHT]->emitThreadIO(Output2_OFF);
}

void MainWindow::on_btn_clynderMID_right_clicked()
{
    if(pProc[SIDE_RIGHT]->ptrIO->m_InClynderMID) return;


    if(pProc[SIDE_RIGHT]->ptrIO->m_InClynderBWD){

        emit pProc[SIDE_RIGHT]->emitThreadIO(Output1_ON);
        emit pProc[SIDE_RIGHT]->emitThreadIO(Output2_OFF);
        t1.StartTimer();
        while(t1.LessThan(10) && !pProc[SIDE_RIGHT]->ptrIO->m_InClynderMID){
            emit pProc[SIDE_RIGHT]->emitThreadIO(Output1_OFF);
            emit pProc[SIDE_RIGHT]->emitThreadIO(Output2_OFF);
        }
    }
    else if(pProc[SIDE_RIGHT]->ptrIO->m_InClynderFWD){
        emit pProc[SIDE_RIGHT]->emitThreadIO(Output1_OFF);
        emit pProc[SIDE_RIGHT]->emitThreadIO(Output2_ON);
        t1.StartTimer();
        while(t1.LessThan(10) && !pProc[SIDE_RIGHT]->ptrIO->m_InClynderMID){
            emit pProc[SIDE_RIGHT]->emitThreadIO(Output1_OFF);
            emit pProc[SIDE_RIGHT]->emitThreadIO(Output2_OFF);
        }
    }

}

void MainWindow::on_btn_clynderBWD_right_clicked()
{
    emit pProc[SIDE_RIGHT]->emitThreadIO(Output1_OFF);

    emit pProc[SIDE_RIGHT]->emitThreadIO(Output2_ON);
}


void MainWindow::on_btn_ledOFF_right_clicked()
{
    emit pProc[SIDE_RIGHT]->emitThreadIO(Output4_ON);
}

void MainWindow::on_btn_ledON_right_clicked()
{
    emit pProc[SIDE_RIGHT]->emitThreadIO(Output4_OFF);
}

void MainWindow::on_btnStartSimulator_clicked()
{
    if(ui->manualSimulation->isChecked() && ui->edtPath->text() != ""){

        Simulation->iCam = ui->cbbSelectCamToCheck->currentIndex();
        Simulation->iModel = ui->cbbSelectParameterCheckManual->currentIndex();
        Simulation->ListImage = getListImageFromFolder(ui->edtPath->text());

        if(!Simulation->m_bRun)
            Simulation->StartThread();
    }

}

void MainWindow::on_btnStopSimulator_clicked()
{
    Simulation->StopThread();
}

void MainWindow::showImageWhenClick(int iRow, int iCol)
{
    if(!ui->manualSimulation->isChecked()) return;
    if(iRow >= mRes.size()) return;
    int iIdx = mRes.size()-1-iRow;
    if(mRes.at(iIdx).empty()) return;
    emit eDisplay_Image(mRes.at(iIdx), SIDE_IMAGE);
}
