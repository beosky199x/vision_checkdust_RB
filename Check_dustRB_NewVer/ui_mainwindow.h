/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupTitle;
    QLabel *lblTime;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *lblErrColorStain;
    QPushButton *lblErrColor_WhiteStain;
    QPushButton *lblErrColorDust;
    QPushButton *lblErrColorGray;
    QPushButton *lblErrColor_Glare;
    QPushButton *lblErrColor_Glare_3;
    QToolButton *lblNameProject;
    QTabWidget *tabWidget;
    QWidget *tabAuto;
    QTableWidget *tbwLogLeft;
    QLabel *displayLeft;
    QLabel *displayRight;
    QLabel *lblMouse_3;
    QToolButton *btnStart;
    QToolButton *btnStop;
    QTableWidget *tbwLogRight;
    QToolButton *btnInital;
    QLabel *lblNameErrorTableLeft;
    QLabel *lblMouse_4;
    QLabel *lblNameLogTableLeft;
    QTableWidget *tbwErrorLeft;
    QLabel *lblNameLogTableRight;
    QLabel *lblNameErrorTableRight;
    QTableWidget *tbwErrorRight;
    QWidget *tabManual;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QPushButton *btnSendCOM;
    QComboBox *cbbListFunction;
    QLineEdit *edtDataSendCom;
    QLabel *label_20;
    QLabel *label_21;
    QGroupBox *groupBox_3;
    QPushButton *btnClearCOM;
    QTableWidget *tbwReceiverDataCom;
    QGroupBox *groupBox_4;
    QPushButton *btnCoDisComport;
    QComboBox *cbbListComport;
    QLabel *label_31;
    QComboBox *cbbListBaudrate;
    QLabel *label_32;
    QPushButton *btnScanCOM;
    QPushButton *btnDisconnectAll;
    QPushButton *btnDeviceManeger;
    QGroupBox *groupBox_5;
    QComboBox *cbbListDevices;
    QLabel *label_33;
    QPushButton *btnScanDevices;
    QPushButton *btnSendADB;
    QLineEdit *edtDataSendADB;
    QLabel *label_26;
    QComboBox *cbbListFunctionADB;
    QLabel *label_34;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btnOpenATK;
    QPushButton *btnDelATK;
    QPushButton *btnDelLog;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *btnADBKillserver;
    QPushButton *btnADBCMD;
    QGroupBox *groupBox_6;
    QTableWidget *tbwReceiverDataCmd;
    QPushButton *btnClearCMD;
    QWidget *tabTeach;
    QWidget *gridLayoutWidget_5;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_14;
    QLabel *display;
    QGridLayout *gridLayout_12;
    QProgressBar *progressBar;
    QPushButton *btnStopSimulator;
    QPushButton *btnStartSimulator;
    QGridLayout *gridLayout_10;
    QPushButton *btnOpenClear;
    QPushButton *btnOpenDebug;
    QGridLayout *gridLayout_3;
    QTableWidget *tbwLogTestManual;
    QGridLayout *gridLayout_2;
    QLabel *lblMouse_7;
    QLabel *lblMouse_9;
    QLabel *lblMouse_10;
    QComboBox *cbbSelectParameterCheckManual;
    QComboBox *cbbSelectCamToCheck;
    QLabel *lblMouse_11;
    QComboBox *cbbSelectSizeCheckManual;
    QLabel *lblMouse_12;
    QGridLayout *gridLayout_7;
    QCheckBox *manualDebug;
    QGridLayout *gridLayout_9;
    QCheckBox *manualSimulation;
    QLineEdit *txt_delay;
    QLabel *label;
    QGridLayout *gridLayout_6;
    QLineEdit *edtPath;
    QLabel *label_2;
    QLabel *lblMouse;
    QPushButton *btnLoad;
    QGridLayout *gridLayout_4;
    QPushButton *btnCheckDarkspot;
    QPushButton *btnCheckWrongColor;
    QPushButton *btnCheckGlare;
    QPushButton *btnCheckFocus;
    QPushButton *btnCheckWhiteStain;
    QPushButton *btnCheckStain;
    QWidget *tab_3;
    QGroupBox *groupBox_12;
    QGroupBox *groupBoxDarkSport_5;
    QCheckBox *checkBoxUseLeft;
    QLineEdit *edtComLeft;
    QLineEdit *edtIDLeft;
    QLineEdit *edtKeyStartLeft;
    QLineEdit *edtInputFolderLeft;
    QLineEdit *edtOutputFolderLeft;
    QLineEdit *edtPhoneFolderLeft;
    QLabel *label_107;
    QLabel *label_108;
    QLabel *label_109;
    QToolButton *lblSk1_folderPhone;
    QToolButton *lblSk1_folderOut;
    QToolButton *lblSk1_folderIn;
    QLineEdit *edtComportIO_Left;
    QLabel *label_116;
    QCheckBox *checkBoxUseComportIO_Left;
    QLabel *label_119;
    QComboBox *cbbSelectModel_Left;
    QGroupBox *groupBoxDarkSport_6;
    QCheckBox *checkBoxUseRight;
    QLineEdit *edtComRight;
    QLineEdit *edtIDRight;
    QLineEdit *edtKeyStartRight;
    QLineEdit *edtInputFolderRight;
    QLineEdit *edtOutputFolderRight;
    QLineEdit *edtPhoneFolderRight;
    QLabel *label_110;
    QLabel *label_111;
    QLabel *label_112;
    QToolButton *lblSk2_folderPhone;
    QToolButton *lblSk2_folderOut;
    QToolButton *lblSk2_folderIn;
    QLabel *label_117;
    QLineEdit *edtComportIO_Right;
    QCheckBox *checkBoxUseComportIO_Right;
    QLabel *label_118;
    QComboBox *cbbSelectModel_Right;
    QToolButton *btnOpenLogFolder;
    QLabel *labelVerSion;
    QLineEdit *edtVersion;
    QLineEdit *edtFolderLog;
    QCheckBox *cbSaveImageResize;
    QGroupBox *groupBox_11;
    QTreeWidget *treeWidget_Parameter;
    QPushButton *btnSave;
    QComboBox *cbbSelectModel;
    QGroupBox *groupBoxDarkSport_9;
    QPushButton *btnClearFolderOutput;
    QPushButton *btnClearFolderPhone;
    QComboBox *cbbSelectSideToDel;
    QWidget *tab;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_7;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *btn_clynderFWD_left;
    QPushButton *btn_clynderMID_left;
    QPushButton *btn_clynderBWD_left;
    QPushButton *btn_ledON_left;
    QPushButton *btn_ledOFF_left;
    QGroupBox *groupBox_8;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btn_clynderFWD_right;
    QPushButton *btn_clynderMID_right;
    QPushButton *btn_clynderBWD_right;
    QPushButton *btn_ledON_right;
    QPushButton *btn_ledOFF_right;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1280, 720);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupTitle = new QGroupBox(centralWidget);
        groupTitle->setObjectName(QStringLiteral("groupTitle"));
        groupTitle->setGeometry(QRect(0, 0, 1280, 50));
        groupTitle->setStyleSheet(QLatin1String("QGroupBox{\n"
"	border: 0px solid rgb(10, 57, 167);\n"
"    border-radius: 0px;\n"
"	background-color:rgb(207, 219, 242);\n"
"}"));
        lblTime = new QLabel(groupTitle);
        lblTime->setObjectName(QStringLiteral("lblTime"));
        lblTime->setGeometry(QRect(1125, 0, 151, 51));
        QFont font;
        font.setFamily(QStringLiteral("Lao UI"));
        font.setPointSize(10);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        lblTime->setFont(font);
        lblTime->setStyleSheet(QLatin1String("font: 10pt \"Lao UI\";\n"
"color: rgb(255, 0, 0);"));
        lblTime->setAlignment(Qt::AlignCenter);
        horizontalLayoutWidget = new QWidget(groupTitle);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(680, 15, 436, 21));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lblErrColorStain = new QPushButton(horizontalLayoutWidget);
        lblErrColorStain->setObjectName(QStringLiteral("lblErrColorStain"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        lblErrColorStain->setFont(font1);
        lblErrColorStain->setStyleSheet(QLatin1String("background-color: rgb(0, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"border-radius: 5px;\n"
"padding-left:5px;\n"
"text-align: left;"));

        horizontalLayout->addWidget(lblErrColorStain);

        lblErrColor_WhiteStain = new QPushButton(horizontalLayoutWidget);
        lblErrColor_WhiteStain->setObjectName(QStringLiteral("lblErrColor_WhiteStain"));
        lblErrColor_WhiteStain->setFont(font1);
        lblErrColor_WhiteStain->setStyleSheet(QLatin1String("background-color: red;\n"
"color: rgb(0, 0, 0);\n"
"border-radius: 5px;\n"
"padding-left:5px;\n"
"text-align: left;"));

        horizontalLayout->addWidget(lblErrColor_WhiteStain);

        lblErrColorDust = new QPushButton(horizontalLayoutWidget);
        lblErrColorDust->setObjectName(QStringLiteral("lblErrColorDust"));
        lblErrColorDust->setFont(font1);
        lblErrColorDust->setStyleSheet(QLatin1String("background-color: rgb(128, 0, 128);\n"
"color: rgb(0, 0, 0);\n"
"border-radius: 5px;\n"
"padding-left:5px;\n"
"text-align: left;"));

        horizontalLayout->addWidget(lblErrColorDust);

        lblErrColorGray = new QPushButton(horizontalLayoutWidget);
        lblErrColorGray->setObjectName(QStringLiteral("lblErrColorGray"));
        lblErrColorGray->setFont(font1);
        lblErrColorGray->setStyleSheet(QLatin1String("background-color: rgb(0, 85, 127);\n"
"color: rgb(0, 0, 0);\n"
"border-radius: 5px;\n"
"padding-left:5px;\n"
"text-align: left;"));

        horizontalLayout->addWidget(lblErrColorGray);

        lblErrColor_Glare = new QPushButton(horizontalLayoutWidget);
        lblErrColor_Glare->setObjectName(QStringLiteral("lblErrColor_Glare"));
        lblErrColor_Glare->setFont(font1);
        lblErrColor_Glare->setStyleSheet(QLatin1String("background-color: orange;\n"
"color: rgb(0, 0, 0);\n"
"border-radius: 5px;\n"
"padding-left:5px;\n"
"text-align: left;"));

        horizontalLayout->addWidget(lblErrColor_Glare);

        lblErrColor_Glare_3 = new QPushButton(horizontalLayoutWidget);
        lblErrColor_Glare_3->setObjectName(QStringLiteral("lblErrColor_Glare_3"));
        lblErrColor_Glare_3->setFont(font1);
        lblErrColor_Glare_3->setStyleSheet(QLatin1String("background-color: blue;\n"
"color: rgb(0, 0, 0);\n"
"border-radius: 5px;\n"
"padding-left:5px;\n"
"text-align: left;"));

        horizontalLayout->addWidget(lblErrColor_Glare_3);

        lblNameProject = new QToolButton(groupTitle);
        lblNameProject->setObjectName(QStringLiteral("lblNameProject"));
        lblNameProject->setGeometry(QRect(-6, 0, 409, 51));
        QFont font2;
        font2.setPointSize(14);
        lblNameProject->setFont(font2);
        lblNameProject->setStyleSheet(QLatin1String("color: rgb(0, 0, 127);\n"
"background-color: rgb(191, 189, 255);\n"
"border-radius: 2px;\n"
""));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(10, 55, 1275, 671));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(600, 100));
        tabWidget->setSizeIncrement(QSize(0, 0));
        tabWidget->setBaseSize(QSize(0, 0));
        QFont font3;
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setItalic(false);
        font3.setUnderline(true);
        font3.setWeight(75);
        font3.setStrikeOut(false);
        tabWidget->setFont(font3);
        tabWidget->setMouseTracking(false);
        tabWidget->setTabletTracking(false);
        tabWidget->setContextMenuPolicy(Qt::NoContextMenu);
        tabWidget->setAcceptDrops(false);
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setStyleSheet(QLatin1String("QTabWidget::pane {\n"
"   border-bottom: 1px solid darkgrey;\n"
"   border-right: 1px solid darkgrey;\n"
" border-top: 1px solid darkgrey;\n"
"   border-left: 1px solid darkgrey;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"  background-color: rgb(255, 255, 255);\n"
"  width: 80px;\n"
"  height: 60px;\n"
"  color:white;\n"
"}"));
        tabWidget->setTabPosition(QTabWidget::South);
        tabWidget->setIconSize(QSize(65, 60));
        tabWidget->setUsesScrollButtons(false);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(false);
        tabAuto = new QWidget();
        tabAuto->setObjectName(QStringLiteral("tabAuto"));
        tabAuto->setEnabled(true);
        tabAuto->setMouseTracking(false);
        tabAuto->setFocusPolicy(Qt::NoFocus);
        tabAuto->setLayoutDirection(Qt::LeftToRight);
        tabAuto->setInputMethodHints(Qt::ImhNone);
        tbwLogLeft = new QTableWidget(tabAuto);
        tbwLogLeft->setObjectName(QStringLiteral("tbwLogLeft"));
        tbwLogLeft->setGeometry(QRect(296, 480, 285, 128));
        tbwLogLeft->setStyleSheet(QStringLiteral("border-radius: 12px;"));
        tbwLogLeft->setEditTriggers(QAbstractItemView::SelectedClicked);
        tbwLogLeft->verticalHeader()->setCascadingSectionResizes(false);
        displayLeft = new QLabel(tabAuto);
        displayLeft->setObjectName(QStringLiteral("displayLeft"));
        displayLeft->setGeometry(QRect(0, 30, 631, 426));
        QFont font4;
        font4.setPointSize(40);
        displayLeft->setFont(font4);
        displayLeft->setLayoutDirection(Qt::LeftToRight);
        displayLeft->setAutoFillBackground(false);
        displayLeft->setStyleSheet(QStringLiteral("background-color: rgb(60, 120, 0);"));
        displayLeft->setAlignment(Qt::AlignCenter);
        displayRight = new QLabel(tabAuto);
        displayRight->setObjectName(QStringLiteral("displayRight"));
        displayRight->setGeometry(QRect(639, 30, 630, 426));
        displayRight->setFont(font4);
        displayRight->setLayoutDirection(Qt::LeftToRight);
        displayRight->setStyleSheet(QStringLiteral("background-color: rgb(60, 120, 0);"));
        displayRight->setAlignment(Qt::AlignCenter);
        lblMouse_3 = new QLabel(tabAuto);
        lblMouse_3->setObjectName(QStringLiteral("lblMouse_3"));
        lblMouse_3->setGeometry(QRect(2, 2, 626, 25));
        QFont font5;
        font5.setPointSize(8);
        font5.setBold(true);
        font5.setWeight(75);
        lblMouse_3->setFont(font5);
        lblMouse_3->setStyleSheet(QLatin1String("background-color: rgb(255, 170, 0);\n"
"color:rgb(0, 0, 0);\n"
"border-radius: 5px;\n"
""));
        lblMouse_3->setAlignment(Qt::AlignCenter);
        btnStart = new QToolButton(tabAuto);
        btnStart->setObjectName(QStringLiteral("btnStart"));
        btnStart->setGeometry(QRect(585, 460, 106, 45));
        btnStart->setFont(font5);
        btnStart->setStyleSheet(QLatin1String("QToolButton{\n"
"		border: 2px green;\n"
"        border-radius: 10px;\n"
"        color:rgb(85, 255, 0);\n"
"	background-color:rgb(13, 154, 51);\n"
"padding-left:30px;\n"
"\n"
"}\n"
"QToolButton:pressed\n"
"{\n"
"background-color:rgb(133, 246, 6);\n"
"  color: black; \n"
"}\n"
""));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Icon/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnStart->setIcon(icon);
        btnStart->setIconSize(QSize(30, 30));
        btnStart->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btnStop = new QToolButton(tabAuto);
        btnStop->setObjectName(QStringLiteral("btnStop"));
        btnStop->setGeometry(QRect(585, 512, 106, 45));
        btnStop->setFont(font5);
        btnStop->setStyleSheet(QLatin1String("QToolButton{\n"
"		border: 2px red;\n"
"        border-radius: 5px;\n"
"        color:white; \n"
"	background-color:rgb(111, 19, 27);\n"
"padding-left:30px\n"
"}\n"
"QToolButton:pressed\n"
"{\n"
"background-color:rgb(255, 0, 0);\n"
"  color: black; \n"
"}"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Icon/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnStop->setIcon(icon1);
        btnStop->setIconSize(QSize(30, 30));
        btnStop->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        tbwLogRight = new QTableWidget(tabAuto);
        tbwLogRight->setObjectName(QStringLiteral("tbwLogRight"));
        tbwLogRight->setGeometry(QRect(695, 482, 276, 126));
        tbwLogRight->setStyleSheet(QStringLiteral("border-radius: 12px;"));
        tbwLogRight->setEditTriggers(QAbstractItemView::SelectedClicked);
        btnInital = new QToolButton(tabAuto);
        btnInital->setObjectName(QStringLiteral("btnInital"));
        btnInital->setGeometry(QRect(585, 562, 106, 45));
        btnInital->setFont(font5);
        btnInital->setStyleSheet(QLatin1String("QToolButton{\n"
"		border: 2px red;\n"
"        border-radius: 5px;\n"
"        color:rgb(255, 170, 0);\n"
"	background-color:rgb(0, 85, 255);\n"
"padding-left:30px\n"
"}\n"
"QToolButton:pressed\n"
"{\n"
"background-color:rgb(0, 0, 255);\n"
"  color: black; \n"
"}"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Icon/reset.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnInital->setIcon(icon2);
        btnInital->setIconSize(QSize(30, 30));
        btnInital->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        lblNameErrorTableLeft = new QLabel(tabAuto);
        lblNameErrorTableLeft->setObjectName(QStringLiteral("lblNameErrorTableLeft"));
        lblNameErrorTableLeft->setGeometry(QRect(0, 460, 290, 16));
        lblNameErrorTableLeft->setFont(font5);
        lblNameErrorTableLeft->setStyleSheet(QLatin1String("background-color: rgb(0, 85, 127);\n"
"color:rgb(255, 255, 255);\n"
"border-radius: 5px;\n"
"padding-left:5px;\n"
"border: 2px solid black;"));
        lblNameErrorTableLeft->setInputMethodHints(Qt::ImhMultiLine);
        lblNameErrorTableLeft->setAlignment(Qt::AlignCenter);
        lblNameErrorTableLeft->setWordWrap(true);
        lblMouse_4 = new QLabel(tabAuto);
        lblMouse_4->setObjectName(QStringLiteral("lblMouse_4"));
        lblMouse_4->setGeometry(QRect(640, 3, 626, 25));
        lblMouse_4->setFont(font5);
        lblMouse_4->setStyleSheet(QLatin1String("background-color: rgb(255, 170, 0);\n"
"color:rgb(0, 0, 0);\n"
"border-radius: 5px;\n"
""));
        lblMouse_4->setAlignment(Qt::AlignCenter);
        lblNameLogTableLeft = new QLabel(tabAuto);
        lblNameLogTableLeft->setObjectName(QStringLiteral("lblNameLogTableLeft"));
        lblNameLogTableLeft->setGeometry(QRect(295, 460, 286, 16));
        lblNameLogTableLeft->setFont(font5);
        lblNameLogTableLeft->setStyleSheet(QLatin1String("background-color: rgb(0, 85, 127);\n"
"color:rgb(255, 255, 255);\n"
"border-radius: 5px;\n"
"padding-left:5px;\n"
"border: 2px solid black;"));
        lblNameLogTableLeft->setInputMethodHints(Qt::ImhMultiLine);
        lblNameLogTableLeft->setAlignment(Qt::AlignCenter);
        lblNameLogTableLeft->setWordWrap(true);
        tbwErrorLeft = new QTableWidget(tabAuto);
        if (tbwErrorLeft->columnCount() < 2)
            tbwErrorLeft->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tbwErrorLeft->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tbwErrorLeft->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tbwErrorLeft->rowCount() < 7)
            tbwErrorLeft->setRowCount(7);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tbwErrorLeft->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tbwErrorLeft->setVerticalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tbwErrorLeft->setVerticalHeaderItem(2, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tbwErrorLeft->setVerticalHeaderItem(3, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tbwErrorLeft->setVerticalHeaderItem(4, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tbwErrorLeft->setVerticalHeaderItem(5, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tbwErrorLeft->setVerticalHeaderItem(6, __qtablewidgetitem8);
        tbwErrorLeft->setObjectName(QStringLiteral("tbwErrorLeft"));
        tbwErrorLeft->setGeometry(QRect(0, 480, 290, 126));
        QFont font6;
        font6.setPointSize(9);
        tbwErrorLeft->setFont(font6);
        tbwErrorLeft->setStyleSheet(QStringLiteral(""));
        tbwErrorLeft->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbwErrorLeft->setDragEnabled(false);
        tbwErrorLeft->setAlternatingRowColors(true);
        tbwErrorLeft->setSelectionMode(QAbstractItemView::NoSelection);
        tbwErrorLeft->verticalHeader()->setCascadingSectionResizes(true);
        lblNameLogTableRight = new QLabel(tabAuto);
        lblNameLogTableRight->setObjectName(QStringLiteral("lblNameLogTableRight"));
        lblNameLogTableRight->setGeometry(QRect(693, 460, 280, 16));
        lblNameLogTableRight->setFont(font5);
        lblNameLogTableRight->setStyleSheet(QLatin1String("background-color: rgb(0, 85, 127);\n"
"color:rgb(255, 255, 255);\n"
"border-radius: 5px;\n"
"padding-left:5px;\n"
"border: 2px solid black;"));
        lblNameLogTableRight->setInputMethodHints(Qt::ImhMultiLine);
        lblNameLogTableRight->setAlignment(Qt::AlignCenter);
        lblNameLogTableRight->setWordWrap(true);
        lblNameErrorTableRight = new QLabel(tabAuto);
        lblNameErrorTableRight->setObjectName(QStringLiteral("lblNameErrorTableRight"));
        lblNameErrorTableRight->setGeometry(QRect(980, 460, 286, 16));
        lblNameErrorTableRight->setFont(font5);
        lblNameErrorTableRight->setStyleSheet(QLatin1String("background-color: rgb(0, 85, 127);\n"
"color:rgb(255, 255, 255);\n"
"border-radius: 5px;\n"
"padding-left:5px;\n"
"border: 2px solid black;"));
        lblNameErrorTableRight->setInputMethodHints(Qt::ImhMultiLine);
        lblNameErrorTableRight->setAlignment(Qt::AlignCenter);
        lblNameErrorTableRight->setWordWrap(true);
        tbwErrorRight = new QTableWidget(tabAuto);
        if (tbwErrorRight->columnCount() < 2)
            tbwErrorRight->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tbwErrorRight->setHorizontalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tbwErrorRight->setHorizontalHeaderItem(1, __qtablewidgetitem10);
        if (tbwErrorRight->rowCount() < 7)
            tbwErrorRight->setRowCount(7);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tbwErrorRight->setVerticalHeaderItem(0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tbwErrorRight->setVerticalHeaderItem(1, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tbwErrorRight->setVerticalHeaderItem(2, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tbwErrorRight->setVerticalHeaderItem(3, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tbwErrorRight->setVerticalHeaderItem(4, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tbwErrorRight->setVerticalHeaderItem(5, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tbwErrorRight->setVerticalHeaderItem(6, __qtablewidgetitem17);
        tbwErrorRight->setObjectName(QStringLiteral("tbwErrorRight"));
        tbwErrorRight->setGeometry(QRect(980, 479, 290, 126));
        tbwErrorRight->setStyleSheet(QStringLiteral("border-radius: 12px;"));
        tbwErrorRight->setEditTriggers(QAbstractItemView::NoEditTriggers);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Icon/Auto.JPG"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabAuto, icon3, QString());
        tabManual = new QWidget();
        tabManual->setObjectName(QStringLiteral("tabManual"));
        groupBox = new QGroupBox(tabManual);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(5, 10, 611, 591));
        groupBox->setStyleSheet(QLatin1String("QGroupBox{\n"
"border-radius: 9px;\n"
"background-color:rgb(234, 234, 234);\n"
"border: 1px solid gray;\n"
"color: blue;\n"
"}\n"
"\n"
"QGroupBox::title\n"
"{\n"
"subcontrol-origin:margin;\n"
"left:10px;\n"
"top:5px\n"
"padding 0 6px 0 6px;\n"
"color: blue;\n"
"}\n"
""));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 140, 571, 141));
        QFont font7;
        font7.setUnderline(true);
        groupBox_2->setFont(font7);
        btnSendCOM = new QPushButton(groupBox_2);
        btnSendCOM->setObjectName(QStringLiteral("btnSendCOM"));
        btnSendCOM->setGeometry(QRect(400, 95, 161, 26));
        btnSendCOM->setFont(font1);
        btnSendCOM->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));
        btnSendCOM->setIcon(icon);
        btnSendCOM->setIconSize(QSize(22, 22));
        cbbListFunction = new QComboBox(groupBox_2);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Icon/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        cbbListFunction->addItem(icon4, QString());
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/Icon/back.png"), QSize(), QIcon::Normal, QIcon::Off);
        cbbListFunction->addItem(icon5, QString());
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/Icon/ico00004.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cbbListFunction->addItem(icon6, QString());
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/Icon/Log_On.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cbbListFunction->addItem(icon7, QString());
        cbbListFunction->addItem(icon6, QString());
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/Icon/Log_Off.png"), QSize(), QIcon::Normal, QIcon::Off);
        cbbListFunction->addItem(icon8, QString());
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/Icon/cap.png"), QSize(), QIcon::Normal, QIcon::Off);
        cbbListFunction->addItem(icon9, QString());
        cbbListFunction->addItem(icon9, QString());
        cbbListFunction->addItem(icon6, QString());
        cbbListFunction->addItem(icon7, QString());
        cbbListFunction->addItem(icon8, QString());
        cbbListFunction->addItem(icon9, QString());
        cbbListFunction->addItem(icon9, QString());
        cbbListFunction->addItem(icon9, QString());
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/Icon/phone.png"), QSize(), QIcon::Normal, QIcon::Off);
        cbbListFunction->addItem(icon10, QString());
        cbbListFunction->addItem(icon6, QString());
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/Icon/ON.png"), QSize(), QIcon::Normal, QIcon::Off);
        cbbListFunction->addItem(icon11, QString());
        cbbListFunction->addItem(icon7, QString());
        cbbListFunction->addItem(icon8, QString());
        cbbListFunction->addItem(icon7, QString());
        cbbListFunction->addItem(icon8, QString());
        cbbListFunction->addItem(icon7, QString());
        cbbListFunction->addItem(icon8, QString());
        cbbListFunction->addItem(icon7, QString());
        cbbListFunction->addItem(icon8, QString());
        cbbListFunction->addItem(icon7, QString());
        cbbListFunction->addItem(icon8, QString());
        cbbListFunction->addItem(icon7, QString());
        cbbListFunction->addItem(icon8, QString());
        cbbListFunction->addItem(icon7, QString());
        cbbListFunction->addItem(icon8, QString());
        cbbListFunction->setObjectName(QStringLiteral("cbbListFunction"));
        cbbListFunction->setGeometry(QRect(65, 40, 321, 31));
        QFont font8;
        font8.setPointSize(10);
        font8.setBold(true);
        font8.setWeight(75);
        cbbListFunction->setFont(font8);
        cbbListFunction->setLayoutDirection(Qt::LeftToRight);
        cbbListFunction->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);padding-left:20px;"));
        edtDataSendCom = new QLineEdit(groupBox_2);
        edtDataSendCom->setObjectName(QStringLiteral("edtDataSendCom"));
        edtDataSendCom->setGeometry(QRect(65, 95, 321, 26));
        edtDataSendCom->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));
        label_20 = new QLabel(groupBox_2);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(15, 55, 47, 13));
        label_20->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        label_21 = new QLabel(groupBox_2);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(15, 100, 36, 16));
        label_21->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 285, 571, 301));
        groupBox_3->setFont(font7);
        btnClearCOM = new QPushButton(groupBox_3);
        btnClearCOM->setObjectName(QStringLiteral("btnClearCOM"));
        btnClearCOM->setGeometry(QRect(485, 25, 80, 26));
        btnClearCOM->setFont(font1);
        btnClearCOM->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));
        tbwReceiverDataCom = new QTableWidget(groupBox_3);
        tbwReceiverDataCom->setObjectName(QStringLiteral("tbwReceiverDataCom"));
        tbwReceiverDataCom->setGeometry(QRect(10, 25, 466, 271));
        tbwReceiverDataCom->setStyleSheet(QStringLiteral("border-radius: 12px;"));
        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(20, 30, 571, 106));
        groupBox_4->setFont(font7);
        btnCoDisComport = new QPushButton(groupBox_4);
        btnCoDisComport->setObjectName(QStringLiteral("btnCoDisComport"));
        btnCoDisComport->setGeometry(QRect(265, 65, 121, 31));
        btnCoDisComport->setFont(font1);
        btnCoDisComport->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));
        cbbListComport = new QComboBox(groupBox_4);
        cbbListComport->setObjectName(QStringLiteral("cbbListComport"));
        cbbListComport->setGeometry(QRect(67, 25, 191, 31));
        QFont font9;
        font9.setPointSize(12);
        font9.setBold(true);
        font9.setWeight(75);
        cbbListComport->setFont(font9);
        cbbListComport->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);padding-left:20px;"));
        label_31 = new QLabel(groupBox_4);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(15, 35, 47, 13));
        label_31->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        cbbListBaudrate = new QComboBox(groupBox_4);
        cbbListBaudrate->setObjectName(QStringLiteral("cbbListBaudrate"));
        cbbListBaudrate->setGeometry(QRect(67, 65, 191, 31));
        cbbListBaudrate->setFont(font9);
        cbbListBaudrate->setLayoutDirection(Qt::RightToLeft);
        cbbListBaudrate->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);padding-left:20px;"));
        cbbListBaudrate->setInsertPolicy(QComboBox::NoInsert);
        cbbListBaudrate->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
        label_32 = new QLabel(groupBox_4);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setGeometry(QRect(15, 75, 47, 13));
        label_32->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        btnScanCOM = new QPushButton(groupBox_4);
        btnScanCOM->setObjectName(QStringLiteral("btnScanCOM"));
        btnScanCOM->setGeometry(QRect(265, 25, 121, 31));
        btnScanCOM->setFont(font1);
        btnScanCOM->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));
        btnDisconnectAll = new QPushButton(groupBox_4);
        btnDisconnectAll->setObjectName(QStringLiteral("btnDisconnectAll"));
        btnDisconnectAll->setGeometry(QRect(400, 25, 166, 71));
        btnDisconnectAll->setFont(font1);
        btnDisconnectAll->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));
        btnDeviceManeger = new QPushButton(groupBox);
        btnDeviceManeger->setObjectName(QStringLiteral("btnDeviceManeger"));
        btnDeviceManeger->setGeometry(QRect(18, 0, 157, 31));
        btnDeviceManeger->setFont(font8);
        btnDeviceManeger->setStyleSheet(QStringLiteral("color: rgb(255, 0, 0);"));
        groupBox_5 = new QGroupBox(tabManual);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(620, 10, 651, 591));
        groupBox_5->setFont(font7);
        groupBox_5->setStyleSheet(QLatin1String("QGroupBox{\n"
"border-radius: 9px;\n"
"background-color:rgb(234, 234, 234);\n"
"border: 1px solid gray;\n"
"color: blue;\n"
"}\n"
"\n"
"QGroupBox::title\n"
"{\n"
"subcontrol-origin:margin;\n"
"left:10px;\n"
"top:5px\n"
"padding 0 6px 0 6px;\n"
"color: blue;\n"
"}\n"
""));
        cbbListDevices = new QComboBox(groupBox_5);
        cbbListDevices->setObjectName(QStringLiteral("cbbListDevices"));
        cbbListDevices->setGeometry(QRect(75, 140, 171, 26));
        cbbListDevices->setFont(font8);
        cbbListDevices->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);padding-left:20px;"));
        label_33 = new QLabel(groupBox_5);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setGeometry(QRect(15, 145, 56, 16));
        label_33->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        btnScanDevices = new QPushButton(groupBox_5);
        btnScanDevices->setObjectName(QStringLiteral("btnScanDevices"));
        btnScanDevices->setGeometry(QRect(255, 140, 171, 26));
        btnScanDevices->setFont(font1);
        btnScanDevices->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));
        btnSendADB = new QPushButton(groupBox_5);
        btnSendADB->setObjectName(QStringLiteral("btnSendADB"));
        btnSendADB->setGeometry(QRect(433, 226, 176, 25));
        btnSendADB->setFont(font1);
        btnSendADB->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));
        edtDataSendADB = new QLineEdit(groupBox_5);
        edtDataSendADB->setObjectName(QStringLiteral("edtDataSendADB"));
        edtDataSendADB->setGeometry(QRect(75, 226, 351, 26));
        edtDataSendADB->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));
        label_26 = new QLabel(groupBox_5);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(15, 230, 36, 16));
        label_26->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        cbbListFunctionADB = new QComboBox(groupBox_5);
        cbbListFunctionADB->addItem(icon4, QString());
        cbbListFunctionADB->addItem(icon5, QString());
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/Icon/step.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        cbbListFunctionADB->addItem(icon12, QString());
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/Icon/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        cbbListFunctionADB->addItem(icon13, QString());
        cbbListFunctionADB->addItem(icon10, QString());
        cbbListFunctionADB->addItem(icon7, QString());
        cbbListFunctionADB->addItem(icon11, QString());
        cbbListFunctionADB->addItem(icon12, QString());
        cbbListFunctionADB->setObjectName(QStringLiteral("cbbListFunctionADB"));
        cbbListFunctionADB->setGeometry(QRect(75, 185, 351, 26));
        cbbListFunctionADB->setFont(font8);
        cbbListFunctionADB->setLayoutDirection(Qt::LeftToRight);
        cbbListFunctionADB->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);padding-left:20px;"));
        label_34 = new QLabel(groupBox_5);
        label_34->setObjectName(QStringLiteral("label_34"));
        label_34->setGeometry(QRect(15, 191, 47, 13));
        label_34->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        horizontalLayoutWidget_4 = new QWidget(groupBox_5);
        horizontalLayoutWidget_4->setObjectName(QStringLiteral("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(75, 55, 526, 31));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        btnOpenATK = new QPushButton(horizontalLayoutWidget_4);
        btnOpenATK->setObjectName(QStringLiteral("btnOpenATK"));
        btnOpenATK->setFont(font1);
        btnOpenATK->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));

        horizontalLayout_5->addWidget(btnOpenATK);

        btnDelATK = new QPushButton(horizontalLayoutWidget_4);
        btnDelATK->setObjectName(QStringLiteral("btnDelATK"));
        btnDelATK->setFont(font1);
        btnDelATK->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));

        horizontalLayout_5->addWidget(btnDelATK);

        btnDelLog = new QPushButton(horizontalLayoutWidget_4);
        btnDelLog->setObjectName(QStringLiteral("btnDelLog"));
        btnDelLog->setFont(font1);
        btnDelLog->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));

        horizontalLayout_5->addWidget(btnDelLog);

        horizontalLayoutWidget_5 = new QWidget(groupBox_5);
        horizontalLayoutWidget_5->setObjectName(QStringLiteral("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(74, 95, 351, 32));
        horizontalLayout_6 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        btnADBKillserver = new QPushButton(horizontalLayoutWidget_5);
        btnADBKillserver->setObjectName(QStringLiteral("btnADBKillserver"));
        btnADBKillserver->setFont(font8);
        btnADBKillserver->setStyleSheet(QStringLiteral("color: rgb(255, 0, 0);"));

        horizontalLayout_6->addWidget(btnADBKillserver);

        btnADBCMD = new QPushButton(horizontalLayoutWidget_5);
        btnADBCMD->setObjectName(QStringLiteral("btnADBCMD"));
        btnADBCMD->setFont(font8);
        btnADBCMD->setStyleSheet(QStringLiteral("color: rgb(255, 0, 0);"));

        horizontalLayout_6->addWidget(btnADBCMD);

        groupBox_6 = new QGroupBox(groupBox_5);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(10, 284, 631, 301));
        tbwReceiverDataCmd = new QTableWidget(groupBox_6);
        tbwReceiverDataCmd->setObjectName(QStringLiteral("tbwReceiverDataCmd"));
        tbwReceiverDataCmd->setGeometry(QRect(10, 30, 521, 261));
        tbwReceiverDataCmd->setStyleSheet(QStringLiteral("border-radius: 12px;"));
        btnClearCMD = new QPushButton(groupBox_6);
        btnClearCMD->setObjectName(QStringLiteral("btnClearCMD"));
        btnClearCMD->setGeometry(QRect(540, 30, 81, 26));
        btnClearCMD->setFont(font1);
        btnClearCMD->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));
        groupBox_6->raise();
        cbbListDevices->raise();
        label_33->raise();
        btnScanDevices->raise();
        btnSendADB->raise();
        edtDataSendADB->raise();
        label_26->raise();
        cbbListFunctionADB->raise();
        label_34->raise();
        horizontalLayoutWidget_4->raise();
        horizontalLayoutWidget_5->raise();
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/Icon/Manual.JPG"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabManual, icon14, QString());
        tabTeach = new QWidget();
        tabTeach->setObjectName(QStringLiteral("tabTeach"));
        tabTeach->setEnabled(true);
        gridLayoutWidget_5 = new QWidget(tabTeach);
        gridLayoutWidget_5->setObjectName(QStringLiteral("gridLayoutWidget_5"));
        gridLayoutWidget_5->setGeometry(QRect(0, 0, 1267, 606));
        gridLayout_5 = new QGridLayout(gridLayoutWidget_5);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        gridLayout_14 = new QGridLayout();
        gridLayout_14->setSpacing(6);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        display = new QLabel(gridLayoutWidget_5);
        display->setObjectName(QStringLiteral("display"));
        display->setStyleSheet(QStringLiteral("background-color: rgb(85, 128, 0);"));

        gridLayout_14->addWidget(display, 0, 0, 1, 1);

        gridLayout_12 = new QGridLayout();
        gridLayout_12->setSpacing(6);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        progressBar = new QProgressBar(gridLayoutWidget_5);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        gridLayout_12->addWidget(progressBar, 0, 2, 1, 1);

        btnStopSimulator = new QPushButton(gridLayoutWidget_5);
        btnStopSimulator->setObjectName(QStringLiteral("btnStopSimulator"));
        btnStopSimulator->setMinimumSize(QSize(0, 35));
        btnStopSimulator->setFont(font8);
        btnStopSimulator->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/Icon/function.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnStopSimulator->setIcon(icon15);
        btnStopSimulator->setIconSize(QSize(45, 45));

        gridLayout_12->addWidget(btnStopSimulator, 0, 1, 1, 1);

        btnStartSimulator = new QPushButton(gridLayoutWidget_5);
        btnStartSimulator->setObjectName(QStringLiteral("btnStartSimulator"));
        btnStartSimulator->setMinimumSize(QSize(0, 35));
        btnStartSimulator->setFont(font8);
        btnStartSimulator->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));
        btnStartSimulator->setIcon(icon15);
        btnStartSimulator->setIconSize(QSize(45, 45));

        gridLayout_12->addWidget(btnStartSimulator, 0, 0, 1, 1);


        gridLayout_14->addLayout(gridLayout_12, 1, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout_14, 1, 0, 1, 1);

        gridLayout_10 = new QGridLayout();
        gridLayout_10->setSpacing(6);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        btnOpenClear = new QPushButton(gridLayoutWidget_5);
        btnOpenClear->setObjectName(QStringLiteral("btnOpenClear"));
        btnOpenClear->setMinimumSize(QSize(0, 35));
        btnOpenClear->setFont(font8);
        btnOpenClear->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));
        btnOpenClear->setIcon(icon13);
        btnOpenClear->setIconSize(QSize(30, 30));

        gridLayout_10->addWidget(btnOpenClear, 0, 1, 1, 1);

        btnOpenDebug = new QPushButton(gridLayoutWidget_5);
        btnOpenDebug->setObjectName(QStringLiteral("btnOpenDebug"));
        btnOpenDebug->setMinimumSize(QSize(0, 35));
        btnOpenDebug->setFont(font8);
        btnOpenDebug->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));
        QIcon icon16;
        icon16.addFile(QStringLiteral("Icon/images.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        btnOpenDebug->setIcon(icon16);
        btnOpenDebug->setIconSize(QSize(30, 30));

        gridLayout_10->addWidget(btnOpenDebug, 0, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout_10, 7, 2, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        tbwLogTestManual = new QTableWidget(gridLayoutWidget_5);
        tbwLogTestManual->setObjectName(QStringLiteral("tbwLogTestManual"));
        tbwLogTestManual->setStyleSheet(QStringLiteral("border-radius: 12px;"));
        tbwLogTestManual->setEditTriggers(QAbstractItemView::SelectedClicked);
        tbwLogTestManual->horizontalHeader()->setDefaultSectionSize(1000);
        tbwLogTestManual->horizontalHeader()->setMinimumSectionSize(500);
        tbwLogTestManual->verticalHeader()->setCascadingSectionResizes(false);

        gridLayout_3->addWidget(tbwLogTestManual, 3, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        lblMouse_7 = new QLabel(gridLayoutWidget_5);
        lblMouse_7->setObjectName(QStringLiteral("lblMouse_7"));
        lblMouse_7->setFont(font5);
        lblMouse_7->setStyleSheet(QLatin1String("background-color: rgb(85, 0, 0);\n"
"color:rgb(255, 255, 255);"));
        lblMouse_7->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lblMouse_7, 1, 0, 1, 1);

        lblMouse_9 = new QLabel(gridLayoutWidget_5);
        lblMouse_9->setObjectName(QStringLiteral("lblMouse_9"));
        lblMouse_9->setFont(font5);
        lblMouse_9->setStyleSheet(QLatin1String("background-color: rgb(85, 0, 0);\n"
"color:rgb(255, 255, 255);"));
        lblMouse_9->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lblMouse_9, 2, 0, 1, 1);

        lblMouse_10 = new QLabel(gridLayoutWidget_5);
        lblMouse_10->setObjectName(QStringLiteral("lblMouse_10"));
        lblMouse_10->setFont(font5);
        lblMouse_10->setStyleSheet(QLatin1String("background-color: rgb(85, 0, 0);\n"
"color:rgb(255, 255, 255);"));
        lblMouse_10->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lblMouse_10, 3, 0, 1, 1);

        cbbSelectParameterCheckManual = new QComboBox(gridLayoutWidget_5);
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/Icon/1.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cbbSelectParameterCheckManual->addItem(icon17, QString());
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/Icon/2.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cbbSelectParameterCheckManual->addItem(icon18, QString());
        cbbSelectParameterCheckManual->setObjectName(QStringLiteral("cbbSelectParameterCheckManual"));
        cbbSelectParameterCheckManual->setFont(font8);
        cbbSelectParameterCheckManual->setLayoutDirection(Qt::LeftToRight);
        cbbSelectParameterCheckManual->setStyleSheet(QLatin1String("color: rgb(255, 0, 0);\n"
""));
        cbbSelectParameterCheckManual->setIconSize(QSize(30, 20));

        gridLayout_2->addWidget(cbbSelectParameterCheckManual, 0, 1, 1, 1);

        cbbSelectCamToCheck = new QComboBox(gridLayoutWidget_5);
        cbbSelectCamToCheck->addItem(icon17, QString());
        cbbSelectCamToCheck->addItem(icon18, QString());
        cbbSelectCamToCheck->setObjectName(QStringLiteral("cbbSelectCamToCheck"));
        cbbSelectCamToCheck->setFont(font8);
        cbbSelectCamToCheck->setLayoutDirection(Qt::LeftToRight);
        cbbSelectCamToCheck->setStyleSheet(QLatin1String("color: rgb(255, 0, 0);\n"
""));
        cbbSelectCamToCheck->setIconSize(QSize(30, 20));

        gridLayout_2->addWidget(cbbSelectCamToCheck, 1, 1, 1, 1);

        lblMouse_11 = new QLabel(gridLayoutWidget_5);
        lblMouse_11->setObjectName(QStringLiteral("lblMouse_11"));
        lblMouse_11->setFont(font5);
        lblMouse_11->setStyleSheet(QLatin1String("background-color: rgb(85, 0, 0);\n"
"color:rgb(255, 255, 255);"));
        lblMouse_11->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lblMouse_11, 4, 0, 1, 1);

        cbbSelectSizeCheckManual = new QComboBox(gridLayoutWidget_5);
        cbbSelectSizeCheckManual->addItem(icon17, QString());
        cbbSelectSizeCheckManual->addItem(icon18, QString());
        cbbSelectSizeCheckManual->setObjectName(QStringLiteral("cbbSelectSizeCheckManual"));
        cbbSelectSizeCheckManual->setFont(font8);
        cbbSelectSizeCheckManual->setLayoutDirection(Qt::LeftToRight);
        cbbSelectSizeCheckManual->setStyleSheet(QLatin1String("color: rgb(255, 0, 0);\n"
""));
        cbbSelectSizeCheckManual->setIconSize(QSize(30, 20));

        gridLayout_2->addWidget(cbbSelectSizeCheckManual, 2, 1, 1, 1);

        lblMouse_12 = new QLabel(gridLayoutWidget_5);
        lblMouse_12->setObjectName(QStringLiteral("lblMouse_12"));
        lblMouse_12->setFont(font5);
        lblMouse_12->setStyleSheet(QLatin1String("background-color: rgb(85, 0, 0);\n"
"color:rgb(255, 255, 255);"));
        lblMouse_12->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lblMouse_12, 0, 0, 1, 1);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));

        gridLayout_2->addLayout(gridLayout_7, 5, 1, 1, 1);

        manualDebug = new QCheckBox(gridLayoutWidget_5);
        manualDebug->setObjectName(QStringLiteral("manualDebug"));
        manualDebug->setFont(font8);
        manualDebug->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));

        gridLayout_2->addWidget(manualDebug, 3, 1, 1, 1);

        gridLayout_9 = new QGridLayout();
        gridLayout_9->setSpacing(6);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        manualSimulation = new QCheckBox(gridLayoutWidget_5);
        manualSimulation->setObjectName(QStringLiteral("manualSimulation"));
        manualSimulation->setFont(font8);
        manualSimulation->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));

        gridLayout_9->addWidget(manualSimulation, 0, 0, 1, 1);

        txt_delay = new QLineEdit(gridLayoutWidget_5);
        txt_delay->setObjectName(QStringLiteral("txt_delay"));

        gridLayout_9->addWidget(txt_delay, 0, 2, 1, 1);

        label = new QLabel(gridLayoutWidget_5);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_9->addWidget(label, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout_9, 4, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout_3, 1, 2, 1, 1);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        edtPath = new QLineEdit(gridLayoutWidget_5);
        edtPath->setObjectName(QStringLiteral("edtPath"));
        QFont font10;
        font10.setPointSize(10);
        font10.setItalic(true);
        edtPath->setFont(font10);
        edtPath->setStyleSheet(QStringLiteral("color: rgb(0, 85, 0);"));

        gridLayout_6->addWidget(edtPath, 0, 2, 1, 1);

        label_2 = new QLabel(gridLayoutWidget_5);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font8);
        label_2->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_2, 0, 1, 1, 1);

        lblMouse = new QLabel(gridLayoutWidget_5);
        lblMouse->setObjectName(QStringLiteral("lblMouse"));
        lblMouse->setFont(font5);
        lblMouse->setStyleSheet(QLatin1String("background-color: rgb(85, 0, 0);\n"
"color:rgb(255, 255, 255);"));
        lblMouse->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(lblMouse, 0, 0, 1, 1);

        btnLoad = new QPushButton(gridLayoutWidget_5);
        btnLoad->setObjectName(QStringLiteral("btnLoad"));
        btnLoad->setFont(font8);
        btnLoad->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));

        gridLayout_6->addWidget(btnLoad, 0, 3, 1, 1);


        gridLayout_5->addLayout(gridLayout_6, 0, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        btnCheckDarkspot = new QPushButton(gridLayoutWidget_5);
        btnCheckDarkspot->setObjectName(QStringLiteral("btnCheckDarkspot"));
        btnCheckDarkspot->setMinimumSize(QSize(0, 35));
        btnCheckDarkspot->setFont(font8);
        btnCheckDarkspot->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));
        btnCheckDarkspot->setIcon(icon15);
        btnCheckDarkspot->setIconSize(QSize(45, 45));

        gridLayout_4->addWidget(btnCheckDarkspot, 0, 5, 1, 1);

        btnCheckWrongColor = new QPushButton(gridLayoutWidget_5);
        btnCheckWrongColor->setObjectName(QStringLiteral("btnCheckWrongColor"));
        btnCheckWrongColor->setMinimumSize(QSize(0, 35));
        btnCheckWrongColor->setFont(font8);
        btnCheckWrongColor->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));
        btnCheckWrongColor->setIcon(icon15);
        btnCheckWrongColor->setIconSize(QSize(45, 45));

        gridLayout_4->addWidget(btnCheckWrongColor, 0, 4, 1, 1);

        btnCheckGlare = new QPushButton(gridLayoutWidget_5);
        btnCheckGlare->setObjectName(QStringLiteral("btnCheckGlare"));
        btnCheckGlare->setMinimumSize(QSize(0, 35));
        btnCheckGlare->setFont(font8);
        btnCheckGlare->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));
        btnCheckGlare->setIcon(icon15);
        btnCheckGlare->setIconSize(QSize(45, 45));

        gridLayout_4->addWidget(btnCheckGlare, 0, 2, 1, 1);

        btnCheckFocus = new QPushButton(gridLayoutWidget_5);
        btnCheckFocus->setObjectName(QStringLiteral("btnCheckFocus"));
        btnCheckFocus->setMinimumSize(QSize(0, 35));
        btnCheckFocus->setFont(font8);
        btnCheckFocus->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));
        btnCheckFocus->setIcon(icon15);
        btnCheckFocus->setIconSize(QSize(45, 45));

        gridLayout_4->addWidget(btnCheckFocus, 0, 3, 1, 1);

        btnCheckWhiteStain = new QPushButton(gridLayoutWidget_5);
        btnCheckWhiteStain->setObjectName(QStringLiteral("btnCheckWhiteStain"));
        btnCheckWhiteStain->setMinimumSize(QSize(0, 35));
        btnCheckWhiteStain->setFont(font8);
        btnCheckWhiteStain->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));
        btnCheckWhiteStain->setIcon(icon15);
        btnCheckWhiteStain->setIconSize(QSize(45, 45));

        gridLayout_4->addWidget(btnCheckWhiteStain, 0, 1, 1, 1);

        btnCheckStain = new QPushButton(gridLayoutWidget_5);
        btnCheckStain->setObjectName(QStringLiteral("btnCheckStain"));
        btnCheckStain->setMinimumSize(QSize(0, 35));
        btnCheckStain->setFont(font8);
        btnCheckStain->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));
        btnCheckStain->setIcon(icon15);
        btnCheckStain->setIconSize(QSize(45, 45));

        gridLayout_4->addWidget(btnCheckStain, 0, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 7, 0, 1, 1);

        QIcon icon19;
        icon19.addFile(QStringLiteral(":/Icon/Teach.JPG"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabTeach, icon19, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        groupBox_12 = new QGroupBox(tab_3);
        groupBox_12->setObjectName(QStringLiteral("groupBox_12"));
        groupBox_12->setGeometry(QRect(5, 5, 721, 596));
        groupBox_12->setStyleSheet(QStringLiteral("border-color: rgb(0, 0, 0);"));
        groupBoxDarkSport_5 = new QGroupBox(groupBox_12);
        groupBoxDarkSport_5->setObjectName(QStringLiteral("groupBoxDarkSport_5"));
        groupBoxDarkSport_5->setGeometry(QRect(4, 170, 356, 426));
        groupBoxDarkSport_5->setFont(font7);
        groupBoxDarkSport_5->setStyleSheet(QStringLiteral("border-color: rgb(0, 0, 0);"));
        checkBoxUseLeft = new QCheckBox(groupBoxDarkSport_5);
        checkBoxUseLeft->setObjectName(QStringLiteral("checkBoxUseLeft"));
        checkBoxUseLeft->setGeometry(QRect(100, 5, 70, 17));
        checkBoxUseLeft->setFont(font1);
        checkBoxUseLeft->setStyleSheet(QStringLiteral("color: green;"));
        edtComLeft = new QLineEdit(groupBoxDarkSport_5);
        edtComLeft->setObjectName(QStringLiteral("edtComLeft"));
        edtComLeft->setGeometry(QRect(86, 21, 104, 20));
        edtComLeft->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        edtIDLeft = new QLineEdit(groupBoxDarkSport_5);
        edtIDLeft->setObjectName(QStringLiteral("edtIDLeft"));
        edtIDLeft->setGeometry(QRect(86, 47, 261, 20));
        edtIDLeft->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        edtKeyStartLeft = new QLineEdit(groupBoxDarkSport_5);
        edtKeyStartLeft->setObjectName(QStringLiteral("edtKeyStartLeft"));
        edtKeyStartLeft->setGeometry(QRect(86, 73, 104, 20));
        edtKeyStartLeft->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        edtInputFolderLeft = new QLineEdit(groupBoxDarkSport_5);
        edtInputFolderLeft->setObjectName(QStringLiteral("edtInputFolderLeft"));
        edtInputFolderLeft->setGeometry(QRect(86, 100, 261, 20));
        edtInputFolderLeft->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        edtOutputFolderLeft = new QLineEdit(groupBoxDarkSport_5);
        edtOutputFolderLeft->setObjectName(QStringLiteral("edtOutputFolderLeft"));
        edtOutputFolderLeft->setGeometry(QRect(86, 126, 261, 20));
        edtOutputFolderLeft->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        edtPhoneFolderLeft = new QLineEdit(groupBoxDarkSport_5);
        edtPhoneFolderLeft->setObjectName(QStringLiteral("edtPhoneFolderLeft"));
        edtPhoneFolderLeft->setGeometry(QRect(86, 152, 261, 20));
        edtPhoneFolderLeft->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        label_107 = new QLabel(groupBoxDarkSport_5);
        label_107->setObjectName(QStringLiteral("label_107"));
        label_107->setGeometry(QRect(11, 21, 60, 16));
        label_107->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        label_108 = new QLabel(groupBoxDarkSport_5);
        label_108->setObjectName(QStringLiteral("label_108"));
        label_108->setGeometry(QRect(11, 48, 16, 16));
        label_108->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        label_109 = new QLabel(groupBoxDarkSport_5);
        label_109->setObjectName(QStringLiteral("label_109"));
        label_109->setGeometry(QRect(11, 74, 60, 16));
        label_109->setStyleSheet(QStringLiteral("color: rgb(170, 0, 0);"));
        lblSk1_folderPhone = new QToolButton(groupBoxDarkSport_5);
        lblSk1_folderPhone->setObjectName(QStringLiteral("lblSk1_folderPhone"));
        lblSk1_folderPhone->setGeometry(QRect(5, 150, 80, 19));
        lblSk1_folderPhone->setStyleSheet(QLatin1String("color: rgb(0, 0, 127);\n"
"background-color: rgb(191, 189, 255);\n"
"border-radius: 2px;\n"
""));
        lblSk1_folderOut = new QToolButton(groupBoxDarkSport_5);
        lblSk1_folderOut->setObjectName(QStringLiteral("lblSk1_folderOut"));
        lblSk1_folderOut->setGeometry(QRect(5, 125, 80, 19));
        lblSk1_folderOut->setStyleSheet(QLatin1String("color: rgb(0, 0, 127);\n"
"background-color: rgb(191, 189, 255);\n"
"border-radius: 2px;\n"
""));
        lblSk1_folderIn = new QToolButton(groupBoxDarkSport_5);
        lblSk1_folderIn->setObjectName(QStringLiteral("lblSk1_folderIn"));
        lblSk1_folderIn->setGeometry(QRect(5, 100, 80, 19));
        lblSk1_folderIn->setStyleSheet(QLatin1String("color: rgb(0, 0, 127);\n"
"background-color: rgb(191, 189, 255);\n"
"border-radius: 2px;\n"
""));
        edtComportIO_Left = new QLineEdit(groupBoxDarkSport_5);
        edtComportIO_Left->setObjectName(QStringLiteral("edtComportIO_Left"));
        edtComportIO_Left->setGeometry(QRect(85, 270, 104, 20));
        edtComportIO_Left->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        label_116 = new QLabel(groupBoxDarkSport_5);
        label_116->setObjectName(QStringLiteral("label_116"));
        label_116->setGeometry(QRect(15, 270, 60, 16));
        label_116->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        checkBoxUseComportIO_Left = new QCheckBox(groupBoxDarkSport_5);
        checkBoxUseComportIO_Left->setObjectName(QStringLiteral("checkBoxUseComportIO_Left"));
        checkBoxUseComportIO_Left->setGeometry(QRect(200, 272, 70, 17));
        checkBoxUseComportIO_Left->setFont(font1);
        checkBoxUseComportIO_Left->setStyleSheet(QStringLiteral("color: green;"));
        label_119 = new QLabel(groupBoxDarkSport_5);
        label_119->setObjectName(QStringLiteral("label_119"));
        label_119->setGeometry(QRect(10, 185, 60, 16));
        label_119->setStyleSheet(QStringLiteral("color: rgb(170, 0, 0);"));
        cbbSelectModel_Left = new QComboBox(groupBoxDarkSport_5);
        cbbSelectModel_Left->setObjectName(QStringLiteral("cbbSelectModel_Left"));
        cbbSelectModel_Left->setGeometry(QRect(85, 185, 261, 21));
        cbbSelectModel_Left->setFont(font9);
        cbbSelectModel_Left->setLayoutDirection(Qt::LeftToRight);
        cbbSelectModel_Left->setStyleSheet(QLatin1String("color: rgb(0, 0, 255);\n"
""));
        cbbSelectModel_Left->setIconSize(QSize(50, 50));
        groupBoxDarkSport_6 = new QGroupBox(groupBox_12);
        groupBoxDarkSport_6->setObjectName(QStringLiteral("groupBoxDarkSport_6"));
        groupBoxDarkSport_6->setGeometry(QRect(362, 170, 356, 426));
        groupBoxDarkSport_6->setFont(font7);
        groupBoxDarkSport_6->setStyleSheet(QStringLiteral("border-color: rgb(0, 0, 0);"));
        checkBoxUseRight = new QCheckBox(groupBoxDarkSport_6);
        checkBoxUseRight->setObjectName(QStringLiteral("checkBoxUseRight"));
        checkBoxUseRight->setGeometry(QRect(105, 5, 70, 17));
        checkBoxUseRight->setFont(font1);
        checkBoxUseRight->setStyleSheet(QStringLiteral("color: green;"));
        edtComRight = new QLineEdit(groupBoxDarkSport_6);
        edtComRight->setObjectName(QStringLiteral("edtComRight"));
        edtComRight->setGeometry(QRect(86, 21, 104, 20));
        edtComRight->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        edtIDRight = new QLineEdit(groupBoxDarkSport_6);
        edtIDRight->setObjectName(QStringLiteral("edtIDRight"));
        edtIDRight->setGeometry(QRect(86, 47, 261, 20));
        edtIDRight->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        edtKeyStartRight = new QLineEdit(groupBoxDarkSport_6);
        edtKeyStartRight->setObjectName(QStringLiteral("edtKeyStartRight"));
        edtKeyStartRight->setGeometry(QRect(86, 73, 104, 20));
        edtKeyStartRight->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        edtInputFolderRight = new QLineEdit(groupBoxDarkSport_6);
        edtInputFolderRight->setObjectName(QStringLiteral("edtInputFolderRight"));
        edtInputFolderRight->setGeometry(QRect(86, 98, 261, 20));
        edtInputFolderRight->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        edtOutputFolderRight = new QLineEdit(groupBoxDarkSport_6);
        edtOutputFolderRight->setObjectName(QStringLiteral("edtOutputFolderRight"));
        edtOutputFolderRight->setGeometry(QRect(86, 124, 261, 20));
        edtOutputFolderRight->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        edtPhoneFolderRight = new QLineEdit(groupBoxDarkSport_6);
        edtPhoneFolderRight->setObjectName(QStringLiteral("edtPhoneFolderRight"));
        edtPhoneFolderRight->setGeometry(QRect(86, 150, 261, 20));
        edtPhoneFolderRight->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        label_110 = new QLabel(groupBoxDarkSport_6);
        label_110->setObjectName(QStringLiteral("label_110"));
        label_110->setGeometry(QRect(11, 21, 60, 16));
        label_110->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        label_111 = new QLabel(groupBoxDarkSport_6);
        label_111->setObjectName(QStringLiteral("label_111"));
        label_111->setGeometry(QRect(11, 48, 16, 16));
        label_111->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        label_112 = new QLabel(groupBoxDarkSport_6);
        label_112->setObjectName(QStringLiteral("label_112"));
        label_112->setGeometry(QRect(11, 74, 60, 16));
        label_112->setStyleSheet(QStringLiteral("color: rgb(170, 0, 0);"));
        lblSk2_folderPhone = new QToolButton(groupBoxDarkSport_6);
        lblSk2_folderPhone->setObjectName(QStringLiteral("lblSk2_folderPhone"));
        lblSk2_folderPhone->setGeometry(QRect(5, 150, 80, 19));
        lblSk2_folderPhone->setStyleSheet(QLatin1String("color: rgb(0, 0, 127);\n"
"background-color: rgb(191, 189, 255);\n"
"border-radius: 2px;\n"
""));
        lblSk2_folderOut = new QToolButton(groupBoxDarkSport_6);
        lblSk2_folderOut->setObjectName(QStringLiteral("lblSk2_folderOut"));
        lblSk2_folderOut->setGeometry(QRect(5, 125, 80, 19));
        lblSk2_folderOut->setStyleSheet(QLatin1String("color: rgb(0, 0, 127);\n"
"background-color: rgb(191, 189, 255);\n"
"border-radius: 2px;\n"
""));
        lblSk2_folderIn = new QToolButton(groupBoxDarkSport_6);
        lblSk2_folderIn->setObjectName(QStringLiteral("lblSk2_folderIn"));
        lblSk2_folderIn->setGeometry(QRect(5, 100, 80, 19));
        lblSk2_folderIn->setStyleSheet(QLatin1String("color: rgb(0, 0, 127);\n"
"background-color: rgb(191, 189, 255);\n"
"border-radius: 2px;\n"
""));
        label_117 = new QLabel(groupBoxDarkSport_6);
        label_117->setObjectName(QStringLiteral("label_117"));
        label_117->setGeometry(QRect(15, 268, 60, 16));
        label_117->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        edtComportIO_Right = new QLineEdit(groupBoxDarkSport_6);
        edtComportIO_Right->setObjectName(QStringLiteral("edtComportIO_Right"));
        edtComportIO_Right->setGeometry(QRect(85, 268, 104, 20));
        edtComportIO_Right->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        checkBoxUseComportIO_Right = new QCheckBox(groupBoxDarkSport_6);
        checkBoxUseComportIO_Right->setObjectName(QStringLiteral("checkBoxUseComportIO_Right"));
        checkBoxUseComportIO_Right->setGeometry(QRect(202, 270, 70, 17));
        checkBoxUseComportIO_Right->setFont(font1);
        checkBoxUseComportIO_Right->setStyleSheet(QStringLiteral("color: green;"));
        label_118 = new QLabel(groupBoxDarkSport_6);
        label_118->setObjectName(QStringLiteral("label_118"));
        label_118->setGeometry(QRect(10, 185, 60, 16));
        label_118->setStyleSheet(QStringLiteral("color: rgb(170, 0, 0);"));
        cbbSelectModel_Right = new QComboBox(groupBoxDarkSport_6);
        cbbSelectModel_Right->setObjectName(QStringLiteral("cbbSelectModel_Right"));
        cbbSelectModel_Right->setGeometry(QRect(85, 185, 261, 21));
        cbbSelectModel_Right->setFont(font9);
        cbbSelectModel_Right->setLayoutDirection(Qt::LeftToRight);
        cbbSelectModel_Right->setStyleSheet(QLatin1String("color: rgb(0, 0, 255);\n"
""));
        cbbSelectModel_Right->setIconSize(QSize(50, 50));
        btnOpenLogFolder = new QToolButton(groupBox_12);
        btnOpenLogFolder->setObjectName(QStringLiteral("btnOpenLogFolder"));
        btnOpenLogFolder->setGeometry(QRect(10, 55, 60, 22));
        btnOpenLogFolder->setStyleSheet(QLatin1String("color: rgb(0, 0, 127);\n"
"background-color: rgb(191, 189, 255);\n"
"border-radius: 2px;\n"
""));
        labelVerSion = new QLabel(groupBox_12);
        labelVerSion->setObjectName(QStringLiteral("labelVerSion"));
        labelVerSion->setGeometry(QRect(15, 25, 51, 16));
        labelVerSion->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        edtVersion = new QLineEdit(groupBox_12);
        edtVersion->setObjectName(QStringLiteral("edtVersion"));
        edtVersion->setGeometry(QRect(80, 25, 636, 20));
        edtVersion->setFont(font1);
        edtVersion->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        edtFolderLog = new QLineEdit(groupBox_12);
        edtFolderLog->setObjectName(QStringLiteral("edtFolderLog"));
        edtFolderLog->setGeometry(QRect(80, 55, 636, 20));
        edtFolderLog->setFont(font1);
        edtFolderLog->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        cbSaveImageResize = new QCheckBox(groupBox_12);
        cbSaveImageResize->setObjectName(QStringLiteral("cbSaveImageResize"));
        cbSaveImageResize->setGeometry(QRect(78, 90, 637, 26));
        groupBox_11 = new QGroupBox(tab_3);
        groupBox_11->setObjectName(QStringLiteral("groupBox_11"));
        groupBox_11->setGeometry(QRect(730, 5, 541, 596));
        treeWidget_Parameter = new QTreeWidget(groupBox_11);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setBackground(1, QColor(0, 0, 127));
        __qtreewidgetitem->setTextAlignment(0, Qt::AlignLeading|Qt::AlignVCenter);
        __qtreewidgetitem->setBackground(0, QColor(89, 15, 200));
        treeWidget_Parameter->setHeaderItem(__qtreewidgetitem);
        QFont font11;
        font11.setStyleStrategy(QFont::PreferAntialias);
        new QTreeWidgetItem(treeWidget_Parameter);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(treeWidget_Parameter);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(treeWidget_Parameter);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(treeWidget_Parameter);
        __qtreewidgetitem3->setFont(0, font11);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem(treeWidget_Parameter);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        QTreeWidgetItem *__qtreewidgetitem5 = new QTreeWidgetItem(treeWidget_Parameter);
        new QTreeWidgetItem(__qtreewidgetitem5);
        new QTreeWidgetItem(__qtreewidgetitem5);
        new QTreeWidgetItem(__qtreewidgetitem5);
        new QTreeWidgetItem(__qtreewidgetitem5);
        new QTreeWidgetItem(__qtreewidgetitem5);
        new QTreeWidgetItem(__qtreewidgetitem5);
        new QTreeWidgetItem(__qtreewidgetitem5);
        new QTreeWidgetItem(__qtreewidgetitem5);
        new QTreeWidgetItem(__qtreewidgetitem5);
        new QTreeWidgetItem(__qtreewidgetitem5);
        new QTreeWidgetItem(__qtreewidgetitem5);
        new QTreeWidgetItem(__qtreewidgetitem5);
        QTreeWidgetItem *__qtreewidgetitem6 = new QTreeWidgetItem(treeWidget_Parameter);
        new QTreeWidgetItem(__qtreewidgetitem6);
        new QTreeWidgetItem(__qtreewidgetitem6);
        new QTreeWidgetItem(__qtreewidgetitem6);
        new QTreeWidgetItem(__qtreewidgetitem6);
        new QTreeWidgetItem(__qtreewidgetitem6);
        new QTreeWidgetItem(__qtreewidgetitem6);
        new QTreeWidgetItem(__qtreewidgetitem6);
        new QTreeWidgetItem(__qtreewidgetitem6);
        new QTreeWidgetItem(__qtreewidgetitem6);
        new QTreeWidgetItem(__qtreewidgetitem6);
        new QTreeWidgetItem(__qtreewidgetitem6);
        new QTreeWidgetItem(__qtreewidgetitem6);
        QTreeWidgetItem *__qtreewidgetitem7 = new QTreeWidgetItem(treeWidget_Parameter);
        new QTreeWidgetItem(__qtreewidgetitem7);
        new QTreeWidgetItem(__qtreewidgetitem7);
        new QTreeWidgetItem(__qtreewidgetitem7);
        new QTreeWidgetItem(__qtreewidgetitem7);
        new QTreeWidgetItem(__qtreewidgetitem7);
        new QTreeWidgetItem(__qtreewidgetitem7);
        new QTreeWidgetItem(__qtreewidgetitem7);
        new QTreeWidgetItem(__qtreewidgetitem7);
        new QTreeWidgetItem(__qtreewidgetitem7);
        new QTreeWidgetItem(__qtreewidgetitem7);
        new QTreeWidgetItem(__qtreewidgetitem7);
        new QTreeWidgetItem(__qtreewidgetitem7);
        new QTreeWidgetItem(__qtreewidgetitem7);
        QTreeWidgetItem *__qtreewidgetitem8 = new QTreeWidgetItem(treeWidget_Parameter);
        new QTreeWidgetItem(__qtreewidgetitem8);
        new QTreeWidgetItem(__qtreewidgetitem8);
        new QTreeWidgetItem(__qtreewidgetitem8);
        new QTreeWidgetItem(__qtreewidgetitem8);
        new QTreeWidgetItem(__qtreewidgetitem8);
        new QTreeWidgetItem(__qtreewidgetitem8);
        new QTreeWidgetItem(__qtreewidgetitem8);
        new QTreeWidgetItem(__qtreewidgetitem8);
        new QTreeWidgetItem(__qtreewidgetitem8);
        new QTreeWidgetItem(__qtreewidgetitem8);
        new QTreeWidgetItem(__qtreewidgetitem8);
        new QTreeWidgetItem(__qtreewidgetitem8);
        QTreeWidgetItem *__qtreewidgetitem9 = new QTreeWidgetItem(treeWidget_Parameter);
        new QTreeWidgetItem(__qtreewidgetitem9);
        new QTreeWidgetItem(__qtreewidgetitem9);
        new QTreeWidgetItem(__qtreewidgetitem9);
        QTreeWidgetItem *__qtreewidgetitem10 = new QTreeWidgetItem(treeWidget_Parameter);
        new QTreeWidgetItem(__qtreewidgetitem10);
        new QTreeWidgetItem(__qtreewidgetitem10);
        new QTreeWidgetItem(__qtreewidgetitem10);
        QTreeWidgetItem *__qtreewidgetitem11 = new QTreeWidgetItem(treeWidget_Parameter);
        QTreeWidgetItem *__qtreewidgetitem12 = new QTreeWidgetItem(__qtreewidgetitem11);
        new QTreeWidgetItem(__qtreewidgetitem12);
        new QTreeWidgetItem(__qtreewidgetitem12);
        QTreeWidgetItem *__qtreewidgetitem13 = new QTreeWidgetItem(__qtreewidgetitem11);
        new QTreeWidgetItem(__qtreewidgetitem13);
        new QTreeWidgetItem(__qtreewidgetitem13);
        QTreeWidgetItem *__qtreewidgetitem14 = new QTreeWidgetItem(__qtreewidgetitem11);
        new QTreeWidgetItem(__qtreewidgetitem14);
        new QTreeWidgetItem(__qtreewidgetitem14);
        QTreeWidgetItem *__qtreewidgetitem15 = new QTreeWidgetItem(__qtreewidgetitem11);
        new QTreeWidgetItem(__qtreewidgetitem15);
        new QTreeWidgetItem(__qtreewidgetitem15);
        QTreeWidgetItem *__qtreewidgetitem16 = new QTreeWidgetItem(__qtreewidgetitem11);
        new QTreeWidgetItem(__qtreewidgetitem16);
        new QTreeWidgetItem(__qtreewidgetitem16);
        QTreeWidgetItem *__qtreewidgetitem17 = new QTreeWidgetItem(__qtreewidgetitem11);
        new QTreeWidgetItem(__qtreewidgetitem17);
        new QTreeWidgetItem(__qtreewidgetitem17);
        QTreeWidgetItem *__qtreewidgetitem18 = new QTreeWidgetItem(__qtreewidgetitem11);
        new QTreeWidgetItem(__qtreewidgetitem18);
        new QTreeWidgetItem(__qtreewidgetitem18);
        QTreeWidgetItem *__qtreewidgetitem19 = new QTreeWidgetItem(__qtreewidgetitem11);
        new QTreeWidgetItem(__qtreewidgetitem19);
        new QTreeWidgetItem(__qtreewidgetitem19);
        QTreeWidgetItem *__qtreewidgetitem20 = new QTreeWidgetItem(__qtreewidgetitem11);
        new QTreeWidgetItem(__qtreewidgetitem20);
        new QTreeWidgetItem(__qtreewidgetitem20);
        QTreeWidgetItem *__qtreewidgetitem21 = new QTreeWidgetItem(__qtreewidgetitem11);
        new QTreeWidgetItem(__qtreewidgetitem21);
        new QTreeWidgetItem(__qtreewidgetitem21);
        QTreeWidgetItem *__qtreewidgetitem22 = new QTreeWidgetItem(__qtreewidgetitem11);
        new QTreeWidgetItem(__qtreewidgetitem22);
        new QTreeWidgetItem(__qtreewidgetitem22);
        QTreeWidgetItem *__qtreewidgetitem23 = new QTreeWidgetItem(treeWidget_Parameter);
        QTreeWidgetItem *__qtreewidgetitem24 = new QTreeWidgetItem(__qtreewidgetitem23);
        new QTreeWidgetItem(__qtreewidgetitem24);
        new QTreeWidgetItem(__qtreewidgetitem24);
        QTreeWidgetItem *__qtreewidgetitem25 = new QTreeWidgetItem(__qtreewidgetitem23);
        new QTreeWidgetItem(__qtreewidgetitem25);
        new QTreeWidgetItem(__qtreewidgetitem25);
        QTreeWidgetItem *__qtreewidgetitem26 = new QTreeWidgetItem(__qtreewidgetitem23);
        new QTreeWidgetItem(__qtreewidgetitem26);
        new QTreeWidgetItem(__qtreewidgetitem26);
        treeWidget_Parameter->setObjectName(QStringLiteral("treeWidget_Parameter"));
        treeWidget_Parameter->setEnabled(true);
        treeWidget_Parameter->setGeometry(QRect(3, 20, 410, 576));
        treeWidget_Parameter->setFocusPolicy(Qt::ClickFocus);
        treeWidget_Parameter->setContextMenuPolicy(Qt::ActionsContextMenu);
        treeWidget_Parameter->setToolTipDuration(1);
        treeWidget_Parameter->setAutoFillBackground(true);
        treeWidget_Parameter->setStyleSheet(QLatin1String("border-color: rgb(255, 255, 127);\n"
"border-top-color: rgb(85, 255, 127);\n"
"border-left-color: rgb(85, 255, 0);"));
        treeWidget_Parameter->setInputMethodHints(Qt::ImhNone);
        treeWidget_Parameter->setFrameShape(QFrame::StyledPanel);
        treeWidget_Parameter->setMidLineWidth(1);
        treeWidget_Parameter->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        treeWidget_Parameter->setAutoScrollMargin(100);
        treeWidget_Parameter->setEditTriggers(QAbstractItemView::NoEditTriggers);
        treeWidget_Parameter->setTabKeyNavigation(false);
        treeWidget_Parameter->setProperty("showDropIndicator", QVariant(true));
        treeWidget_Parameter->setDragEnabled(true);
        treeWidget_Parameter->setDragDropOverwriteMode(false);
        treeWidget_Parameter->setDragDropMode(QAbstractItemView::NoDragDrop);
        treeWidget_Parameter->setDefaultDropAction(Qt::IgnoreAction);
        treeWidget_Parameter->setAlternatingRowColors(true);
        treeWidget_Parameter->setSelectionMode(QAbstractItemView::NoSelection);
        treeWidget_Parameter->setSelectionBehavior(QAbstractItemView::SelectRows);
        treeWidget_Parameter->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
        treeWidget_Parameter->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
        treeWidget_Parameter->setAutoExpandDelay(-1);
        treeWidget_Parameter->setRootIsDecorated(true);
        treeWidget_Parameter->setUniformRowHeights(false);
        treeWidget_Parameter->setAnimated(true);
        treeWidget_Parameter->setAllColumnsShowFocus(true);
        treeWidget_Parameter->setWordWrap(true);
        treeWidget_Parameter->setHeaderHidden(false);
        treeWidget_Parameter->header()->setCascadingSectionResizes(true);
        treeWidget_Parameter->header()->setDefaultSectionSize(250);
        treeWidget_Parameter->header()->setHighlightSections(true);
        treeWidget_Parameter->header()->setMinimumSectionSize(25);
        treeWidget_Parameter->header()->setProperty("showSortIndicator", QVariant(true));
        btnSave = new QPushButton(groupBox_11);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setGeometry(QRect(415, 75, 120, 56));
        btnSave->setMinimumSize(QSize(0, 35));
        QFont font12;
        font12.setPointSize(12);
        btnSave->setFont(font12);
        btnSave->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));
        QIcon icon20;
        icon20.addFile(QStringLiteral(":/Icon/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSave->setIcon(icon20);
        btnSave->setIconSize(QSize(50, 50));
        cbbSelectModel = new QComboBox(groupBox_11);
        cbbSelectModel->setObjectName(QStringLiteral("cbbSelectModel"));
        cbbSelectModel->setGeometry(QRect(415, 20, 120, 51));
        cbbSelectModel->setFont(font9);
        cbbSelectModel->setLayoutDirection(Qt::LeftToRight);
        cbbSelectModel->setStyleSheet(QLatin1String("color: rgb(0, 0, 255);\n"
""));
        cbbSelectModel->setIconSize(QSize(50, 50));
        groupBoxDarkSport_9 = new QGroupBox(groupBox_11);
        groupBoxDarkSport_9->setObjectName(QStringLiteral("groupBoxDarkSport_9"));
        groupBoxDarkSport_9->setGeometry(QRect(416, 140, 121, 456));
        groupBoxDarkSport_9->setFont(font7);
        groupBoxDarkSport_9->setStyleSheet(QLatin1String("QGroupBox{\n"
"border-radius: 9px;\n"
"background-color:rgb(234, 234, 234);\n"
"border: 1px solid gray;\n"
"color: blue;\n"
"}\n"
"\n"
"QGroupBox::title\n"
"{\n"
"subcontrol-origin:margin;\n"
"left:10px;\n"
"top:5px\n"
"padding 0 6px 0 6px;\n"
"color: blue;\n"
"}\n"
""));
        btnClearFolderOutput = new QPushButton(groupBoxDarkSport_9);
        btnClearFolderOutput->setObjectName(QStringLiteral("btnClearFolderOutput"));
        btnClearFolderOutput->setGeometry(QRect(8, 70, 106, 41));
        btnClearFolderOutput->setMinimumSize(QSize(0, 35));
        btnClearFolderOutput->setFont(font5);
        btnClearFolderOutput->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));
        btnClearFolderOutput->setIcon(icon13);
        btnClearFolderOutput->setIconSize(QSize(30, 30));
        btnClearFolderPhone = new QPushButton(groupBoxDarkSport_9);
        btnClearFolderPhone->setObjectName(QStringLiteral("btnClearFolderPhone"));
        btnClearFolderPhone->setGeometry(QRect(8, 125, 106, 41));
        btnClearFolderPhone->setMinimumSize(QSize(0, 35));
        btnClearFolderPhone->setFont(font5);
        btnClearFolderPhone->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));
        btnClearFolderPhone->setIcon(icon13);
        btnClearFolderPhone->setIconSize(QSize(30, 30));
        cbbSelectSideToDel = new QComboBox(groupBoxDarkSport_9);
        cbbSelectSideToDel->addItem(icon5, QString());
        cbbSelectSideToDel->addItem(icon4, QString());
        cbbSelectSideToDel->addItem(icon5, QString());
        cbbSelectSideToDel->addItem(icon4, QString());
        cbbSelectSideToDel->addItem(icon11, QString());
        cbbSelectSideToDel->setObjectName(QStringLiteral("cbbSelectSideToDel"));
        cbbSelectSideToDel->setGeometry(QRect(8, 25, 106, 31));
        cbbSelectSideToDel->setFont(font5);
        cbbSelectSideToDel->setLayoutDirection(Qt::LeftToRight);
        cbbSelectSideToDel->setStyleSheet(QLatin1String("color: rgb(255, 0, 0);\n"
""));
        cbbSelectSideToDel->setIconSize(QSize(30, 20));
        QIcon icon21;
        icon21.addFile(QStringLiteral(":/Icon/Data.JPG"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab_3, icon21, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayoutWidget = new QWidget(tab);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(54, 20, 1159, 561));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        groupBox_7 = new QGroupBox(gridLayoutWidget);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        verticalLayoutWidget = new QWidget(groupBox_7);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(12, 30, 553, 521));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        btn_clynderFWD_left = new QPushButton(verticalLayoutWidget);
        btn_clynderFWD_left->setObjectName(QStringLiteral("btn_clynderFWD_left"));

        verticalLayout->addWidget(btn_clynderFWD_left);

        btn_clynderMID_left = new QPushButton(verticalLayoutWidget);
        btn_clynderMID_left->setObjectName(QStringLiteral("btn_clynderMID_left"));

        verticalLayout->addWidget(btn_clynderMID_left);

        btn_clynderBWD_left = new QPushButton(verticalLayoutWidget);
        btn_clynderBWD_left->setObjectName(QStringLiteral("btn_clynderBWD_left"));

        verticalLayout->addWidget(btn_clynderBWD_left);

        btn_ledON_left = new QPushButton(verticalLayoutWidget);
        btn_ledON_left->setObjectName(QStringLiteral("btn_ledON_left"));

        verticalLayout->addWidget(btn_ledON_left);

        btn_ledOFF_left = new QPushButton(verticalLayoutWidget);
        btn_ledOFF_left->setObjectName(QStringLiteral("btn_ledOFF_left"));

        verticalLayout->addWidget(btn_ledOFF_left);


        gridLayout->addWidget(groupBox_7, 0, 0, 1, 1);

        groupBox_8 = new QGroupBox(gridLayoutWidget);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        verticalLayoutWidget_2 = new QWidget(groupBox_8);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(12, 30, 553, 521));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        btn_clynderFWD_right = new QPushButton(verticalLayoutWidget_2);
        btn_clynderFWD_right->setObjectName(QStringLiteral("btn_clynderFWD_right"));

        verticalLayout_2->addWidget(btn_clynderFWD_right);

        btn_clynderMID_right = new QPushButton(verticalLayoutWidget_2);
        btn_clynderMID_right->setObjectName(QStringLiteral("btn_clynderMID_right"));

        verticalLayout_2->addWidget(btn_clynderMID_right);

        btn_clynderBWD_right = new QPushButton(verticalLayoutWidget_2);
        btn_clynderBWD_right->setObjectName(QStringLiteral("btn_clynderBWD_right"));

        verticalLayout_2->addWidget(btn_clynderBWD_right);

        btn_ledON_right = new QPushButton(verticalLayoutWidget_2);
        btn_ledON_right->setObjectName(QStringLiteral("btn_ledON_right"));

        verticalLayout_2->addWidget(btn_ledON_right);

        btn_ledOFF_right = new QPushButton(verticalLayoutWidget_2);
        btn_ledOFF_right->setObjectName(QStringLiteral("btn_ledOFF_right"));

        verticalLayout_2->addWidget(btn_ledOFF_right);


        gridLayout->addWidget(groupBox_8, 0, 1, 1, 1);

        tabWidget->addTab(tab, icon14, QString());
        MainWindow->setCentralWidget(centralWidget);
        QWidget::setTabOrder(btnSendCOM, cbbListFunction);
        QWidget::setTabOrder(cbbListFunction, edtDataSendCom);
        QWidget::setTabOrder(edtDataSendCom, tabWidget);
        QWidget::setTabOrder(tabWidget, tbwLogLeft);
        QWidget::setTabOrder(tbwLogLeft, btnStart);
        QWidget::setTabOrder(btnStart, btnStop);
        QWidget::setTabOrder(btnStop, tbwLogRight);
        QWidget::setTabOrder(tbwLogRight, btnInital);
        QWidget::setTabOrder(btnInital, cbbListComport);
        QWidget::setTabOrder(cbbListComport, cbbListBaudrate);
        QWidget::setTabOrder(cbbListBaudrate, btnScanCOM);
        QWidget::setTabOrder(btnScanCOM, edtDataSendADB);
        QWidget::setTabOrder(edtDataSendADB, tbwReceiverDataCmd);
        QWidget::setTabOrder(tbwReceiverDataCmd, btnSendADB);
        QWidget::setTabOrder(btnSendADB, btnClearCMD);
        QWidget::setTabOrder(btnClearCMD, btnOpenATK);
        QWidget::setTabOrder(btnOpenATK, btnDelATK);
        QWidget::setTabOrder(btnDelATK, btnDelLog);
        QWidget::setTabOrder(btnDelLog, edtPath);
        QWidget::setTabOrder(edtPath, cbbListFunctionADB);
        QWidget::setTabOrder(cbbListFunctionADB, tbwReceiverDataCom);
        QWidget::setTabOrder(tbwReceiverDataCom, btnCoDisComport);
        QWidget::setTabOrder(btnCoDisComport, btnClearCOM);
        QWidget::setTabOrder(btnClearCOM, btnCheckStain);
        QWidget::setTabOrder(btnCheckStain, btnLoad);
        QWidget::setTabOrder(btnLoad, manualDebug);
        QWidget::setTabOrder(manualDebug, cbbSelectCamToCheck);
        QWidget::setTabOrder(cbbSelectCamToCheck, btnDisconnectAll);
        QWidget::setTabOrder(btnDisconnectAll, cbbListDevices);
        QWidget::setTabOrder(cbbListDevices, btnScanDevices);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(3);
        cbbListBaudrate->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        groupTitle->setTitle(QString());
        lblTime->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt; font-style:italic; color:#ff5500;\">Time</span></p></body></html>", Q_NULLPTR));
        lblErrColorStain->setText(QApplication::translate("MainWindow", "Stain", Q_NULLPTR));
        lblErrColor_WhiteStain->setText(QApplication::translate("MainWindow", "White/Pink Stain", Q_NULLPTR));
        lblErrColorDust->setText(QApplication::translate("MainWindow", "Dust", Q_NULLPTR));
        lblErrColorGray->setText(QApplication::translate("MainWindow", "Color", Q_NULLPTR));
        lblErrColor_Glare->setText(QApplication::translate("MainWindow", "Glare", Q_NULLPTR));
        lblErrColor_Glare_3->setText(QApplication::translate("MainWindow", "Focus", Q_NULLPTR));
        lblNameProject->setText(QApplication::translate("MainWindow", "VISION INSPECTION CAMERA", Q_NULLPTR));
        displayLeft->setText(QString());
        displayRight->setText(QString());
        lblMouse_3->setText(QApplication::translate("MainWindow", "Phone 1 - Left:", Q_NULLPTR));
        btnStart->setText(QApplication::translate("MainWindow", "START", Q_NULLPTR));
        btnStop->setText(QApplication::translate("MainWindow", "STOP", Q_NULLPTR));
        btnInital->setText(QApplication::translate("MainWindow", "Inital", Q_NULLPTR));
        lblNameErrorTableLeft->setText(QApplication::translate("MainWindow", "Error Table", Q_NULLPTR));
        lblMouse_4->setText(QApplication::translate("MainWindow", "Phone 2 - Right:", Q_NULLPTR));
        lblNameLogTableLeft->setText(QApplication::translate("MainWindow", "Log Table", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tbwErrorLeft->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "FW1 RESULT", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tbwErrorLeft->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "FB1 RESULT", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tbwErrorLeft->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "IRIS", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tbwErrorLeft->verticalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "STAIN", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tbwErrorLeft->verticalHeaderItem(2);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "WHITESTAIN", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tbwErrorLeft->verticalHeaderItem(3);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "GLARE", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tbwErrorLeft->verticalHeaderItem(4);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "FOCUS", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tbwErrorLeft->verticalHeaderItem(5);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "COLOR", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = tbwErrorLeft->verticalHeaderItem(6);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "DARKSPORT", Q_NULLPTR));
        lblNameLogTableRight->setText(QApplication::translate("MainWindow", "Log Table", Q_NULLPTR));
        lblNameErrorTableRight->setText(QApplication::translate("MainWindow", "Error Table", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = tbwErrorRight->horizontalHeaderItem(0);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "FW1 RESULT", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem10 = tbwErrorRight->horizontalHeaderItem(1);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "FB1 RESULT", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem11 = tbwErrorRight->verticalHeaderItem(0);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "IRIS", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem12 = tbwErrorRight->verticalHeaderItem(1);
        ___qtablewidgetitem12->setText(QApplication::translate("MainWindow", "STAIN", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem13 = tbwErrorRight->verticalHeaderItem(2);
        ___qtablewidgetitem13->setText(QApplication::translate("MainWindow", "WHITESTAIN", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem14 = tbwErrorRight->verticalHeaderItem(3);
        ___qtablewidgetitem14->setText(QApplication::translate("MainWindow", "GLARE", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem15 = tbwErrorRight->verticalHeaderItem(4);
        ___qtablewidgetitem15->setText(QApplication::translate("MainWindow", "FOCUS", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem16 = tbwErrorRight->verticalHeaderItem(5);
        ___qtablewidgetitem16->setText(QApplication::translate("MainWindow", "COLOR", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem17 = tbwErrorRight->verticalHeaderItem(6);
        ___qtablewidgetitem17->setText(QApplication::translate("MainWindow", "DARKSPORT", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabAuto), QString());
        groupBox->setTitle(QString());
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Transmit", Q_NULLPTR));
        btnSendCOM->setText(QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        cbbListFunction->setItemText(0, QApplication::translate("MainWindow", "Use UART by USB", Q_NULLPTR));
        cbbListFunction->setItemText(1, QApplication::translate("MainWindow", "Use UART by UART", Q_NULLPTR));
        cbbListFunction->setItemText(2, QApplication::translate("MainWindow", "Open Iris", Q_NULLPTR));
        cbbListFunction->setItemText(3, QApplication::translate("MainWindow", "Close Iris", Q_NULLPTR));
        cbbListFunction->setItemText(4, QApplication::translate("MainWindow", "Open Front (Model 1 camera)", Q_NULLPTR));
        cbbListFunction->setItemText(5, QApplication::translate("MainWindow", "Close Front (Model 1 camera)", Q_NULLPTR));
        cbbListFunction->setItemText(6, QApplication::translate("MainWindow", "Capture Front AF (Model 1 camera)", Q_NULLPTR));
        cbbListFunction->setItemText(7, QApplication::translate("MainWindow", "Capture Front uAF (Model 1 camera)", Q_NULLPTR));
        cbbListFunction->setItemText(8, QApplication::translate("MainWindow", "Open FW1 Camera(Model 2 Camera)", Q_NULLPTR));
        cbbListFunction->setItemText(9, QApplication::translate("MainWindow", "Open FB1 Camera(Model 2 Camera)", Q_NULLPTR));
        cbbListFunction->setItemText(10, QApplication::translate("MainWindow", "Close Camera(Model 2 Camera)", Q_NULLPTR));
        cbbListFunction->setItemText(11, QApplication::translate("MainWindow", "Captrue AF(Model 2 Camera)", Q_NULLPTR));
        cbbListFunction->setItemText(12, QApplication::translate("MainWindow", "Capture NOAF(Model 2 Camera)", Q_NULLPTR));
        cbbListFunction->setItemText(13, QApplication::translate("MainWindow", "Capture TRYAF(Model 2 Camera)", Q_NULLPTR));
        cbbListFunction->setItemText(14, QApplication::translate("MainWindow", "Home Screen", Q_NULLPTR));
        cbbListFunction->setItemText(15, QApplication::translate("MainWindow", "Lock Screen", Q_NULLPTR));
        cbbListFunction->setItemText(16, QApplication::translate("MainWindow", "Unlock Screen", Q_NULLPTR));
        cbbListFunction->setItemText(17, QApplication::translate("MainWindow", "On Out_1 Modul IO", Q_NULLPTR));
        cbbListFunction->setItemText(18, QApplication::translate("MainWindow", "Off Out_1 Modul IO", Q_NULLPTR));
        cbbListFunction->setItemText(19, QApplication::translate("MainWindow", "On Out_2 Modul IO", Q_NULLPTR));
        cbbListFunction->setItemText(20, QApplication::translate("MainWindow", "Off Out_2 Modul IO", Q_NULLPTR));
        cbbListFunction->setItemText(21, QApplication::translate("MainWindow", "On Out_3 Modul IO", Q_NULLPTR));
        cbbListFunction->setItemText(22, QApplication::translate("MainWindow", "Off Out_3 Modul IO", Q_NULLPTR));
        cbbListFunction->setItemText(23, QApplication::translate("MainWindow", "On Out_4 Modul IO", Q_NULLPTR));
        cbbListFunction->setItemText(24, QApplication::translate("MainWindow", "Off Out_4 Modul IO", Q_NULLPTR));
        cbbListFunction->setItemText(25, QApplication::translate("MainWindow", "On Out_5 Modul IO", Q_NULLPTR));
        cbbListFunction->setItemText(26, QApplication::translate("MainWindow", "Off Out_5 Modul IO", Q_NULLPTR));
        cbbListFunction->setItemText(27, QApplication::translate("MainWindow", "On Out_6 Modul IO", Q_NULLPTR));
        cbbListFunction->setItemText(28, QApplication::translate("MainWindow", "Off Out_6 Modul IO", Q_NULLPTR));
        cbbListFunction->setItemText(29, QApplication::translate("MainWindow", "On Out_7 Modul IO", Q_NULLPTR));
        cbbListFunction->setItemText(30, QApplication::translate("MainWindow", "Off Out_7 Modul IO", Q_NULLPTR));

        label_20->setText(QApplication::translate("MainWindow", "List Cmd", Q_NULLPTR));
        label_21->setText(QApplication::translate("MainWindow", "Data", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Receiver", Q_NULLPTR));
        btnClearCOM->setText(QApplication::translate("MainWindow", "Clear", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "COMPORT", Q_NULLPTR));
        btnCoDisComport->setText(QApplication::translate("MainWindow", "Open", Q_NULLPTR));
        label_31->setText(QApplication::translate("MainWindow", "COM", Q_NULLPTR));
        cbbListBaudrate->clear();
        cbbListBaudrate->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "9600", Q_NULLPTR)
         << QApplication::translate("MainWindow", "19200", Q_NULLPTR)
         << QApplication::translate("MainWindow", "115200", Q_NULLPTR)
        );
        label_32->setText(QApplication::translate("MainWindow", "Baud rate", Q_NULLPTR));
        btnScanCOM->setText(QApplication::translate("MainWindow", "Scan COM", Q_NULLPTR));
        btnDisconnectAll->setText(QApplication::translate("MainWindow", "Close all \n"
"Comport", Q_NULLPTR));
        btnDeviceManeger->setText(QApplication::translate("MainWindow", "Device manager", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "ADB devices", Q_NULLPTR));
        label_33->setText(QApplication::translate("MainWindow", "ID devices", Q_NULLPTR));
        btnScanDevices->setText(QApplication::translate("MainWindow", "Scan Devices", Q_NULLPTR));
        btnSendADB->setText(QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        label_26->setText(QApplication::translate("MainWindow", "Data", Q_NULLPTR));
        cbbListFunctionADB->setItemText(0, QApplication::translate("MainWindow", "Get List", Q_NULLPTR));
        cbbListFunctionADB->setItemText(1, QApplication::translate("MainWindow", "Pull to PC", Q_NULLPTR));
        cbbListFunctionADB->setItemText(2, QApplication::translate("MainWindow", "Remove folder", Q_NULLPTR));
        cbbListFunctionADB->setItemText(3, QApplication::translate("MainWindow", "Kill-server", Q_NULLPTR));
        cbbListFunctionADB->setItemText(4, QApplication::translate("MainWindow", "Check State Screen", Q_NULLPTR));
        cbbListFunctionADB->setItemText(5, QApplication::translate("MainWindow", "Unlock Phone", Q_NULLPTR));
        cbbListFunctionADB->setItemText(6, QApplication::translate("MainWindow", "Lock Phone", Q_NULLPTR));
        cbbListFunctionADB->setItemText(7, QApplication::translate("MainWindow", "Remove Log", Q_NULLPTR));

        label_34->setText(QApplication::translate("MainWindow", "List Cmd", Q_NULLPTR));
        btnOpenATK->setText(QApplication::translate("MainWindow", "Open img", Q_NULLPTR));
        btnDelATK->setText(QApplication::translate("MainWindow", "Del img", Q_NULLPTR));
        btnDelLog->setText(QApplication::translate("MainWindow", "Del Log", Q_NULLPTR));
        btnADBKillserver->setText(QApplication::translate("MainWindow", "Kill Server", Q_NULLPTR));
        btnADBCMD->setText(QApplication::translate("MainWindow", "ADB cmd", Q_NULLPTR));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "Receiver", Q_NULLPTR));
        btnClearCMD->setText(QApplication::translate("MainWindow", "Clear", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabManual), QString());
        display->setText(QString());
        btnStopSimulator->setText(QApplication::translate("MainWindow", "Stop Simu", Q_NULLPTR));
        btnStartSimulator->setText(QApplication::translate("MainWindow", "Start Simu", Q_NULLPTR));
        btnOpenClear->setText(QApplication::translate("MainWindow", "Clear Log", Q_NULLPTR));
        btnOpenDebug->setText(QApplication::translate("MainWindow", "Debug Folder", Q_NULLPTR));
        lblMouse_7->setText(QApplication::translate("MainWindow", "Camera Check", Q_NULLPTR));
        lblMouse_9->setText(QApplication::translate("MainWindow", "Size Check", Q_NULLPTR));
        lblMouse_10->setText(QApplication::translate("MainWindow", "Save Img handle", Q_NULLPTR));
        cbbSelectParameterCheckManual->setItemText(0, QApplication::translate("MainWindow", "LEFT", Q_NULLPTR));
        cbbSelectParameterCheckManual->setItemText(1, QApplication::translate("MainWindow", "RIGHT", Q_NULLPTR));

        cbbSelectCamToCheck->setItemText(0, QApplication::translate("MainWindow", "FW1", Q_NULLPTR));
        cbbSelectCamToCheck->setItemText(1, QApplication::translate("MainWindow", "FW2", Q_NULLPTR));

        lblMouse_11->setText(QApplication::translate("MainWindow", "Simulation Mode", Q_NULLPTR));
        cbbSelectSizeCheckManual->setItemText(0, QApplication::translate("MainWindow", "Small", Q_NULLPTR));
        cbbSelectSizeCheckManual->setItemText(1, QApplication::translate("MainWindow", "Large", Q_NULLPTR));

        lblMouse_12->setText(QApplication::translate("MainWindow", "Parameter Check", Q_NULLPTR));
        manualDebug->setText(QApplication::translate("MainWindow", "Use/UnUse", Q_NULLPTR));
        manualSimulation->setText(QApplication::translate("MainWindow", "Use/UnUse", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Delay:", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Path", Q_NULLPTR));
        lblMouse->setText(QApplication::translate("MainWindow", "Mouse", Q_NULLPTR));
        btnLoad->setText(QApplication::translate("MainWindow", "LOAD", Q_NULLPTR));
        btnCheckDarkspot->setText(QApplication::translate("MainWindow", "DarkSport", Q_NULLPTR));
        btnCheckWrongColor->setText(QApplication::translate("MainWindow", "Color", Q_NULLPTR));
        btnCheckGlare->setText(QApplication::translate("MainWindow", "Glare", Q_NULLPTR));
        btnCheckFocus->setText(QApplication::translate("MainWindow", "Focus", Q_NULLPTR));
        btnCheckWhiteStain->setText(QApplication::translate("MainWindow", "W.Stain", Q_NULLPTR));
        btnCheckStain->setText(QApplication::translate("MainWindow", "Stain", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabTeach), QString());
        groupBox_12->setTitle(QApplication::translate("MainWindow", "Setting Shocket:", Q_NULLPTR));
        groupBoxDarkSport_5->setTitle(QApplication::translate("MainWindow", "Socket1 - Left", Q_NULLPTR));
        checkBoxUseLeft->setText(QApplication::translate("MainWindow", "Use", Q_NULLPTR));
        label_107->setText(QApplication::translate("MainWindow", "Comport", Q_NULLPTR));
        label_108->setText(QApplication::translate("MainWindow", "ID", Q_NULLPTR));
        label_109->setText(QApplication::translate("MainWindow", "Key Start", Q_NULLPTR));
        lblSk1_folderPhone->setText(QApplication::translate("MainWindow", "Folder Phone", Q_NULLPTR));
        lblSk1_folderOut->setText(QApplication::translate("MainWindow", "Folder Output", Q_NULLPTR));
        lblSk1_folderIn->setText(QApplication::translate("MainWindow", "Folder Input", Q_NULLPTR));
        label_116->setText(QApplication::translate("MainWindow", "Comport IO", Q_NULLPTR));
        checkBoxUseComportIO_Left->setText(QApplication::translate("MainWindow", "Use", Q_NULLPTR));
        label_119->setText(QApplication::translate("MainWindow", "Model", Q_NULLPTR));
        groupBoxDarkSport_6->setTitle(QApplication::translate("MainWindow", "Socket2 - Right", Q_NULLPTR));
        checkBoxUseRight->setText(QApplication::translate("MainWindow", "Use", Q_NULLPTR));
        label_110->setText(QApplication::translate("MainWindow", "Comport", Q_NULLPTR));
        label_111->setText(QApplication::translate("MainWindow", "ID", Q_NULLPTR));
        label_112->setText(QApplication::translate("MainWindow", "Key Start", Q_NULLPTR));
        lblSk2_folderPhone->setText(QApplication::translate("MainWindow", "Folder Phone", Q_NULLPTR));
        lblSk2_folderOut->setText(QApplication::translate("MainWindow", "Folder Output", Q_NULLPTR));
        lblSk2_folderIn->setText(QApplication::translate("MainWindow", "Folder Input", Q_NULLPTR));
        label_117->setText(QApplication::translate("MainWindow", "Comport IO", Q_NULLPTR));
        checkBoxUseComportIO_Right->setText(QApplication::translate("MainWindow", "Use", Q_NULLPTR));
        label_118->setText(QApplication::translate("MainWindow", "Model", Q_NULLPTR));
        btnOpenLogFolder->setText(QApplication::translate("MainWindow", "Log folder", Q_NULLPTR));
        labelVerSion->setText(QApplication::translate("MainWindow", "Version", Q_NULLPTR));
        edtFolderLog->setText(QString());
        edtFolderLog->setPlaceholderText(QString());
        cbSaveImageResize->setText(QApplication::translate("MainWindow", "Save Image ReSize", Q_NULLPTR));
        groupBox_11->setTitle(QApplication::translate("MainWindow", "Parameter: ", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_Parameter->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "Value", Q_NULLPTR));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Property", Q_NULLPTR));

        const bool __sortingEnabled = treeWidget_Parameter->isSortingEnabled();
        treeWidget_Parameter->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget_Parameter->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("MainWindow", "CAMERA SETTING", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem2 = treeWidget_Parameter->topLevelItem(1);
        ___qtreewidgetitem2->setText(0, QApplication::translate("MainWindow", "Option fuction", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem2->child(0);
        ___qtreewidgetitem3->setText(0, QApplication::translate("MainWindow", "Show Image Result", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem2->child(1);
        ___qtreewidgetitem4->setText(0, QApplication::translate("MainWindow", "Save Image Result", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem2->child(2);
        ___qtreewidgetitem5->setText(0, QApplication::translate("MainWindow", "Check Iris", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem2->child(3);
        ___qtreewidgetitem6->setText(0, QApplication::translate("MainWindow", "CheckStain", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem2->child(4);
        ___qtreewidgetitem7->setText(0, QApplication::translate("MainWindow", "Check WhiteStain", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem8 = ___qtreewidgetitem2->child(5);
        ___qtreewidgetitem8->setText(0, QApplication::translate("MainWindow", "Check Glare", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem9 = ___qtreewidgetitem2->child(6);
        ___qtreewidgetitem9->setText(0, QApplication::translate("MainWindow", "Check Focus", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem10 = ___qtreewidgetitem2->child(7);
        ___qtreewidgetitem10->setText(0, QApplication::translate("MainWindow", "Check Color", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem11 = ___qtreewidgetitem2->child(8);
        ___qtreewidgetitem11->setText(0, QApplication::translate("MainWindow", "Check DarkSport", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem12 = ___qtreewidgetitem2->child(9);
        ___qtreewidgetitem12->setText(0, QApplication::translate("MainWindow", "Captrue AF", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem13 = treeWidget_Parameter->topLevelItem(2);
        ___qtreewidgetitem13->setText(0, QApplication::translate("MainWindow", "DELAY TIME", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem14 = ___qtreewidgetitem13->child(0);
        ___qtreewidgetitem14->setText(0, QApplication::translate("MainWindow", "Send UART_USB", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem15 = ___qtreewidgetitem13->child(1);
        ___qtreewidgetitem15->setText(0, QApplication::translate("MainWindow", "Wait_UART_USB", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem16 = ___qtreewidgetitem13->child(2);
        ___qtreewidgetitem16->setText(0, QApplication::translate("MainWindow", "Send Home Screen", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem17 = ___qtreewidgetitem13->child(3);
        ___qtreewidgetitem17->setText(0, QApplication::translate("MainWindow", "Wait Home Screen", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem18 = ___qtreewidgetitem13->child(4);
        ___qtreewidgetitem18->setText(0, QApplication::translate("MainWindow", "Send Open Iris", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem19 = ___qtreewidgetitem13->child(5);
        ___qtreewidgetitem19->setText(0, QApplication::translate("MainWindow", "Wait Open Iris", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem20 = ___qtreewidgetitem13->child(6);
        ___qtreewidgetitem20->setText(0, QApplication::translate("MainWindow", "Send Close Iris", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem21 = ___qtreewidgetitem13->child(7);
        ___qtreewidgetitem21->setText(0, QApplication::translate("MainWindow", "Wait Close Iris", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem22 = ___qtreewidgetitem13->child(8);
        ___qtreewidgetitem22->setText(0, QApplication::translate("MainWindow", "Send Open FW1", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem23 = ___qtreewidgetitem13->child(9);
        ___qtreewidgetitem23->setText(0, QApplication::translate("MainWindow", "Wait Open FW1", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem24 = ___qtreewidgetitem13->child(10);
        ___qtreewidgetitem24->setText(0, QApplication::translate("MainWindow", "Send Close FW1", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem25 = ___qtreewidgetitem13->child(11);
        ___qtreewidgetitem25->setText(0, QApplication::translate("MainWindow", "Wait Close FW1", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem26 = ___qtreewidgetitem13->child(12);
        ___qtreewidgetitem26->setText(0, QApplication::translate("MainWindow", "Send Open FB1", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem27 = ___qtreewidgetitem13->child(13);
        ___qtreewidgetitem27->setText(0, QApplication::translate("MainWindow", "Close Open FB1", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem28 = ___qtreewidgetitem13->child(14);
        ___qtreewidgetitem28->setText(0, QApplication::translate("MainWindow", "Send Close FB1", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem29 = ___qtreewidgetitem13->child(15);
        ___qtreewidgetitem29->setText(0, QApplication::translate("MainWindow", "Wait Close FB1", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem30 = ___qtreewidgetitem13->child(16);
        ___qtreewidgetitem30->setText(0, QApplication::translate("MainWindow", "Send Capture NoAF", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem31 = ___qtreewidgetitem13->child(17);
        ___qtreewidgetitem31->setText(0, QApplication::translate("MainWindow", "Wait Capture NoAF", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem32 = ___qtreewidgetitem13->child(18);
        ___qtreewidgetitem32->setText(0, QApplication::translate("MainWindow", "Send Capture AF", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem33 = ___qtreewidgetitem13->child(19);
        ___qtreewidgetitem33->setText(0, QApplication::translate("MainWindow", "Wait Capture AF", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem34 = ___qtreewidgetitem13->child(20);
        ___qtreewidgetitem34->setText(0, QApplication::translate("MainWindow", "Send Capture TryAF", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem35 = ___qtreewidgetitem13->child(21);
        ___qtreewidgetitem35->setText(0, QApplication::translate("MainWindow", "Wait Capture TryAF", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem36 = ___qtreewidgetitem13->child(22);
        ___qtreewidgetitem36->setText(0, QApplication::translate("MainWindow", "Send Get List", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem37 = ___qtreewidgetitem13->child(23);
        ___qtreewidgetitem37->setText(0, QApplication::translate("MainWindow", "Wait Get List", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem38 = ___qtreewidgetitem13->child(24);
        ___qtreewidgetitem38->setText(0, QApplication::translate("MainWindow", "Send Pull 2 PC", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem39 = ___qtreewidgetitem13->child(25);
        ___qtreewidgetitem39->setText(0, QApplication::translate("MainWindow", "Wait Pull 2 PC", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem40 = ___qtreewidgetitem13->child(26);
        ___qtreewidgetitem40->setText(0, QApplication::translate("MainWindow", "Send Remove Folder", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem41 = ___qtreewidgetitem13->child(27);
        ___qtreewidgetitem41->setText(0, QApplication::translate("MainWindow", "Wait Remove Folder", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem42 = ___qtreewidgetitem13->child(28);
        ___qtreewidgetitem42->setText(0, QApplication::translate("MainWindow", "Clynder ForWard", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem43 = ___qtreewidgetitem13->child(29);
        ___qtreewidgetitem43->setText(0, QApplication::translate("MainWindow", "Clynder BackWard", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem44 = treeWidget_Parameter->topLevelItem(3);
        ___qtreewidgetitem44->setText(0, QApplication::translate("MainWindow", "Parameter Paint", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem45 = ___qtreewidgetitem44->child(0);
        ___qtreewidgetitem45->setText(0, QApplication::translate("MainWindow", "Thickness", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem46 = ___qtreewidgetitem44->child(1);
        ___qtreewidgetitem46->setText(0, QApplication::translate("MainWindow", "Offset", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem47 = treeWidget_Parameter->topLevelItem(4);
        ___qtreewidgetitem47->setText(0, QApplication::translate("MainWindow", "Parameter Normalize", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem48 = ___qtreewidgetitem47->child(0);
        ___qtreewidgetitem48->setText(0, QApplication::translate("MainWindow", "Type", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem49 = ___qtreewidgetitem47->child(1);
        ___qtreewidgetitem49->setText(0, QApplication::translate("MainWindow", "Beta", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem50 = ___qtreewidgetitem47->child(2);
        ___qtreewidgetitem50->setText(0, QApplication::translate("MainWindow", "Alpha", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem51 = treeWidget_Parameter->topLevelItem(5);
        ___qtreewidgetitem51->setText(0, QApplication::translate("MainWindow", "Parameter Check Stain", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem52 = ___qtreewidgetitem51->child(0);
        ___qtreewidgetitem52->setText(0, QApplication::translate("MainWindow", "Threshold", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem53 = ___qtreewidgetitem51->child(1);
        ___qtreewidgetitem53->setText(0, QApplication::translate("MainWindow", "Block Size", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem54 = ___qtreewidgetitem51->child(2);
        ___qtreewidgetitem54->setText(0, QApplication::translate("MainWindow", "Blur Size", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem55 = ___qtreewidgetitem51->child(3);
        ___qtreewidgetitem55->setText(0, QApplication::translate("MainWindow", "Erode Size", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem56 = ___qtreewidgetitem51->child(4);
        ___qtreewidgetitem56->setText(0, QApplication::translate("MainWindow", "Erode Loop", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem57 = ___qtreewidgetitem51->child(5);
        ___qtreewidgetitem57->setText(0, QApplication::translate("MainWindow", "Dilate Size", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem58 = ___qtreewidgetitem51->child(6);
        ___qtreewidgetitem58->setText(0, QApplication::translate("MainWindow", "Dilate Loop", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem59 = ___qtreewidgetitem51->child(7);
        ___qtreewidgetitem59->setText(0, QApplication::translate("MainWindow", "Remove Edge", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem60 = ___qtreewidgetitem51->child(8);
        ___qtreewidgetitem60->setText(0, QApplication::translate("MainWindow", "Remove Conner", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem61 = ___qtreewidgetitem51->child(9);
        ___qtreewidgetitem61->setText(0, QApplication::translate("MainWindow", "Filter Area", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem62 = ___qtreewidgetitem51->child(10);
        ___qtreewidgetitem62->setText(0, QApplication::translate("MainWindow", "Filter Width", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem63 = ___qtreewidgetitem51->child(11);
        ___qtreewidgetitem63->setText(0, QApplication::translate("MainWindow", "Filter Height", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem64 = treeWidget_Parameter->topLevelItem(6);
        ___qtreewidgetitem64->setText(0, QApplication::translate("MainWindow", "Parameter Check WhiteStain", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem65 = ___qtreewidgetitem64->child(0);
        ___qtreewidgetitem65->setText(0, QApplication::translate("MainWindow", "Threshold", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem66 = ___qtreewidgetitem64->child(1);
        ___qtreewidgetitem66->setText(0, QApplication::translate("MainWindow", "Block Size", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem67 = ___qtreewidgetitem64->child(2);
        ___qtreewidgetitem67->setText(0, QApplication::translate("MainWindow", "Blur Size", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem68 = ___qtreewidgetitem64->child(3);
        ___qtreewidgetitem68->setText(0, QApplication::translate("MainWindow", "Erode Size", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem69 = ___qtreewidgetitem64->child(4);
        ___qtreewidgetitem69->setText(0, QApplication::translate("MainWindow", "Erode Loop", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem70 = ___qtreewidgetitem64->child(5);
        ___qtreewidgetitem70->setText(0, QApplication::translate("MainWindow", "Dilate Size", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem71 = ___qtreewidgetitem64->child(6);
        ___qtreewidgetitem71->setText(0, QApplication::translate("MainWindow", "Dilate Loop", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem72 = ___qtreewidgetitem64->child(7);
        ___qtreewidgetitem72->setText(0, QApplication::translate("MainWindow", "Remove Edge", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem73 = ___qtreewidgetitem64->child(8);
        ___qtreewidgetitem73->setText(0, QApplication::translate("MainWindow", "Remove Conner", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem74 = ___qtreewidgetitem64->child(9);
        ___qtreewidgetitem74->setText(0, QApplication::translate("MainWindow", "Filter Area", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem75 = ___qtreewidgetitem64->child(10);
        ___qtreewidgetitem75->setText(0, QApplication::translate("MainWindow", "Filter Width", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem76 = ___qtreewidgetitem64->child(11);
        ___qtreewidgetitem76->setText(0, QApplication::translate("MainWindow", "Filter Height", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem77 = treeWidget_Parameter->topLevelItem(7);
        ___qtreewidgetitem77->setText(0, QApplication::translate("MainWindow", "Parameter Check Glare", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem78 = ___qtreewidgetitem77->child(0);
        ___qtreewidgetitem78->setText(0, QApplication::translate("MainWindow", "Threshold", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem79 = ___qtreewidgetitem77->child(1);
        ___qtreewidgetitem79->setText(0, QApplication::translate("MainWindow", "Blur Size", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem80 = ___qtreewidgetitem77->child(2);
        ___qtreewidgetitem80->setText(0, QApplication::translate("MainWindow", "Roi ", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem81 = ___qtreewidgetitem77->child(3);
        ___qtreewidgetitem81->setText(0, QApplication::translate("MainWindow", "Erode Size", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem82 = ___qtreewidgetitem77->child(4);
        ___qtreewidgetitem82->setText(0, QApplication::translate("MainWindow", "Erode Loop", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem83 = ___qtreewidgetitem77->child(5);
        ___qtreewidgetitem83->setText(0, QApplication::translate("MainWindow", "Dilate Size", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem84 = ___qtreewidgetitem77->child(6);
        ___qtreewidgetitem84->setText(0, QApplication::translate("MainWindow", "Dilate Loop", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem85 = ___qtreewidgetitem77->child(7);
        ___qtreewidgetitem85->setText(0, QApplication::translate("MainWindow", "Remove Edge", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem86 = ___qtreewidgetitem77->child(8);
        ___qtreewidgetitem86->setText(0, QApplication::translate("MainWindow", "Remove Conner", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem87 = ___qtreewidgetitem77->child(9);
        ___qtreewidgetitem87->setText(0, QApplication::translate("MainWindow", "Filter Mean ", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem88 = ___qtreewidgetitem77->child(10);
        ___qtreewidgetitem88->setText(0, QApplication::translate("MainWindow", "Filter Area Roi", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem89 = ___qtreewidgetitem77->child(11);
        ___qtreewidgetitem89->setText(0, QApplication::translate("MainWindow", "Filter Width Roi ", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem90 = ___qtreewidgetitem77->child(12);
        ___qtreewidgetitem90->setText(0, QApplication::translate("MainWindow", "Filter Height Roi ", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem91 = treeWidget_Parameter->topLevelItem(8);
        ___qtreewidgetitem91->setText(0, QApplication::translate("MainWindow", "Parameter Check Focus", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem92 = ___qtreewidgetitem91->child(0);
        ___qtreewidgetitem92->setText(0, QApplication::translate("MainWindow", "Roi Check 1", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem93 = ___qtreewidgetitem91->child(1);
        ___qtreewidgetitem93->setText(0, QApplication::translate("MainWindow", "Roi Check 2", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem94 = ___qtreewidgetitem91->child(2);
        ___qtreewidgetitem94->setText(0, QApplication::translate("MainWindow", "Roi Check 3", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem95 = ___qtreewidgetitem91->child(3);
        ___qtreewidgetitem95->setText(0, QApplication::translate("MainWindow", "Roi Check 4", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem96 = ___qtreewidgetitem91->child(4);
        ___qtreewidgetitem96->setText(0, QApplication::translate("MainWindow", "Roi Check 5", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem97 = ___qtreewidgetitem91->child(5);
        ___qtreewidgetitem97->setText(0, QApplication::translate("MainWindow", "Roi Check 6", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem98 = ___qtreewidgetitem91->child(6);
        ___qtreewidgetitem98->setText(0, QApplication::translate("MainWindow", "Filter Std Roi 1", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem99 = ___qtreewidgetitem91->child(7);
        ___qtreewidgetitem99->setText(0, QApplication::translate("MainWindow", "Filter Std Roi 2", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem100 = ___qtreewidgetitem91->child(8);
        ___qtreewidgetitem100->setText(0, QApplication::translate("MainWindow", "Filter Std Roi 3", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem101 = ___qtreewidgetitem91->child(9);
        ___qtreewidgetitem101->setText(0, QApplication::translate("MainWindow", "Filter Std Roi 4", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem102 = ___qtreewidgetitem91->child(10);
        ___qtreewidgetitem102->setText(0, QApplication::translate("MainWindow", "Filter Std Roi 5", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem103 = ___qtreewidgetitem91->child(11);
        ___qtreewidgetitem103->setText(0, QApplication::translate("MainWindow", "Filter Std Roi 6", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem104 = treeWidget_Parameter->topLevelItem(9);
        ___qtreewidgetitem104->setText(0, QApplication::translate("MainWindow", "Parameter Check Darksport", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem105 = ___qtreewidgetitem104->child(0);
        ___qtreewidgetitem105->setText(0, QApplication::translate("MainWindow", "Threshold", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem106 = ___qtreewidgetitem104->child(1);
        ___qtreewidgetitem106->setText(0, QApplication::translate("MainWindow", "Block Size", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem107 = ___qtreewidgetitem104->child(2);
        ___qtreewidgetitem107->setText(0, QApplication::translate("MainWindow", "Filt Area", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem108 = treeWidget_Parameter->topLevelItem(10);
        ___qtreewidgetitem108->setText(0, QApplication::translate("MainWindow", "Parameter Check Wrong Color", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem109 = ___qtreewidgetitem108->child(0);
        ___qtreewidgetitem109->setText(0, QApplication::translate("MainWindow", "Mean Red", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem110 = ___qtreewidgetitem108->child(1);
        ___qtreewidgetitem110->setText(0, QApplication::translate("MainWindow", "Mean Green", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem111 = ___qtreewidgetitem108->child(2);
        ___qtreewidgetitem111->setText(0, QApplication::translate("MainWindow", "Mean Blue", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem112 = treeWidget_Parameter->topLevelItem(11);
        ___qtreewidgetitem112->setText(0, QApplication::translate("MainWindow", "AT Command", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem113 = ___qtreewidgetitem112->child(0);
        ___qtreewidgetitem113->setText(0, QApplication::translate("MainWindow", "UART_USB", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem114 = ___qtreewidgetitem113->child(0);
        ___qtreewidgetitem114->setText(0, QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem115 = ___qtreewidgetitem113->child(1);
        ___qtreewidgetitem115->setText(0, QApplication::translate("MainWindow", "Respone", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem116 = ___qtreewidgetitem112->child(1);
        ___qtreewidgetitem116->setText(0, QApplication::translate("MainWindow", "HOME_SCREEN", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem117 = ___qtreewidgetitem116->child(0);
        ___qtreewidgetitem117->setText(0, QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem118 = ___qtreewidgetitem116->child(1);
        ___qtreewidgetitem118->setText(0, QApplication::translate("MainWindow", "Respone", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem119 = ___qtreewidgetitem112->child(2);
        ___qtreewidgetitem119->setText(0, QApplication::translate("MainWindow", "OPEN_IRIS", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem120 = ___qtreewidgetitem119->child(0);
        ___qtreewidgetitem120->setText(0, QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem121 = ___qtreewidgetitem119->child(1);
        ___qtreewidgetitem121->setText(0, QApplication::translate("MainWindow", "Respone", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem122 = ___qtreewidgetitem112->child(3);
        ___qtreewidgetitem122->setText(0, QApplication::translate("MainWindow", "CLOSE_IRIS", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem123 = ___qtreewidgetitem122->child(0);
        ___qtreewidgetitem123->setText(0, QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem124 = ___qtreewidgetitem122->child(1);
        ___qtreewidgetitem124->setText(0, QApplication::translate("MainWindow", "Respone", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem125 = ___qtreewidgetitem112->child(4);
        ___qtreewidgetitem125->setText(0, QApplication::translate("MainWindow", "OPEN_FW`1", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem126 = ___qtreewidgetitem125->child(0);
        ___qtreewidgetitem126->setText(0, QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem127 = ___qtreewidgetitem125->child(1);
        ___qtreewidgetitem127->setText(0, QApplication::translate("MainWindow", "Respome", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem128 = ___qtreewidgetitem112->child(5);
        ___qtreewidgetitem128->setText(0, QApplication::translate("MainWindow", "CLOSE_FW1", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem129 = ___qtreewidgetitem128->child(0);
        ___qtreewidgetitem129->setText(0, QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem130 = ___qtreewidgetitem128->child(1);
        ___qtreewidgetitem130->setText(0, QApplication::translate("MainWindow", "Respone", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem131 = ___qtreewidgetitem112->child(6);
        ___qtreewidgetitem131->setText(0, QApplication::translate("MainWindow", "OPEN_FB1", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem132 = ___qtreewidgetitem131->child(0);
        ___qtreewidgetitem132->setText(0, QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem133 = ___qtreewidgetitem131->child(1);
        ___qtreewidgetitem133->setText(0, QApplication::translate("MainWindow", "Respone", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem134 = ___qtreewidgetitem112->child(7);
        ___qtreewidgetitem134->setText(0, QApplication::translate("MainWindow", "CLOSE_FB1", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem135 = ___qtreewidgetitem134->child(0);
        ___qtreewidgetitem135->setText(0, QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem136 = ___qtreewidgetitem134->child(1);
        ___qtreewidgetitem136->setText(0, QApplication::translate("MainWindow", "Respone", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem137 = ___qtreewidgetitem112->child(8);
        ___qtreewidgetitem137->setText(0, QApplication::translate("MainWindow", "CAPTURE_NOAF", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem138 = ___qtreewidgetitem137->child(0);
        ___qtreewidgetitem138->setText(0, QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem139 = ___qtreewidgetitem137->child(1);
        ___qtreewidgetitem139->setText(0, QApplication::translate("MainWindow", "Respone", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem140 = ___qtreewidgetitem112->child(9);
        ___qtreewidgetitem140->setText(0, QApplication::translate("MainWindow", "CAPTURE_AF", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem141 = ___qtreewidgetitem140->child(0);
        ___qtreewidgetitem141->setText(0, QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem142 = ___qtreewidgetitem140->child(1);
        ___qtreewidgetitem142->setText(0, QApplication::translate("MainWindow", "Respone", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem143 = ___qtreewidgetitem112->child(10);
        ___qtreewidgetitem143->setText(0, QApplication::translate("MainWindow", "CAPTURE_TRYAF", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem144 = ___qtreewidgetitem143->child(0);
        ___qtreewidgetitem144->setText(0, QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem145 = ___qtreewidgetitem143->child(1);
        ___qtreewidgetitem145->setText(0, QApplication::translate("MainWindow", "Respone", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem146 = treeWidget_Parameter->topLevelItem(12);
        ___qtreewidgetitem146->setText(0, QApplication::translate("MainWindow", "ADB Command", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem147 = ___qtreewidgetitem146->child(0);
        ___qtreewidgetitem147->setText(0, QApplication::translate("MainWindow", "GET_LIST", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem148 = ___qtreewidgetitem147->child(0);
        ___qtreewidgetitem148->setText(0, QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem149 = ___qtreewidgetitem147->child(1);
        ___qtreewidgetitem149->setText(0, QApplication::translate("MainWindow", "Respone", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem150 = ___qtreewidgetitem146->child(1);
        ___qtreewidgetitem150->setText(0, QApplication::translate("MainWindow", "PULL_2_PC", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem151 = ___qtreewidgetitem150->child(0);
        ___qtreewidgetitem151->setText(0, QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem152 = ___qtreewidgetitem150->child(1);
        ___qtreewidgetitem152->setText(0, QApplication::translate("MainWindow", "Respone", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem153 = ___qtreewidgetitem146->child(2);
        ___qtreewidgetitem153->setText(0, QApplication::translate("MainWindow", "REMOVE_FOLDER", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem154 = ___qtreewidgetitem153->child(0);
        ___qtreewidgetitem154->setText(0, QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem155 = ___qtreewidgetitem153->child(1);
        ___qtreewidgetitem155->setText(0, QApplication::translate("MainWindow", "Respone", Q_NULLPTR));
        treeWidget_Parameter->setSortingEnabled(__sortingEnabled);

        btnSave->setText(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
        groupBoxDarkSport_9->setTitle(QApplication::translate("MainWindow", "Folder Image", Q_NULLPTR));
        btnClearFolderOutput->setText(QApplication::translate("MainWindow", "Folder\n"
"Output", Q_NULLPTR));
        btnClearFolderPhone->setText(QApplication::translate("MainWindow", "Folder\n"
"Phone", Q_NULLPTR));
        cbbSelectSideToDel->setItemText(0, QApplication::translate("MainWindow", "LEFT", Q_NULLPTR));
        cbbSelectSideToDel->setItemText(1, QApplication::translate("MainWindow", "RIGHT", Q_NULLPTR));
        cbbSelectSideToDel->setItemText(2, QApplication::translate("MainWindow", "LEFT2", Q_NULLPTR));
        cbbSelectSideToDel->setItemText(3, QApplication::translate("MainWindow", "RIGHT2", Q_NULLPTR));
        cbbSelectSideToDel->setItemText(4, QApplication::translate("MainWindow", "All folder", Q_NULLPTR));

        tabWidget->setTabText(tabWidget->indexOf(tab_3), QString());
        groupBox_7->setTitle(QApplication::translate("MainWindow", "Left - IO", Q_NULLPTR));
        btn_clynderFWD_left->setText(QApplication::translate("MainWindow", "Clynder FWD", Q_NULLPTR));
        btn_clynderMID_left->setText(QApplication::translate("MainWindow", "Clynder MID", Q_NULLPTR));
        btn_clynderBWD_left->setText(QApplication::translate("MainWindow", "Clynder BWD", Q_NULLPTR));
        btn_ledON_left->setText(QApplication::translate("MainWindow", "Led ON", Q_NULLPTR));
        btn_ledOFF_left->setText(QApplication::translate("MainWindow", "Led OFF", Q_NULLPTR));
        groupBox_8->setTitle(QApplication::translate("MainWindow", "Right - IO", Q_NULLPTR));
        btn_clynderFWD_right->setText(QApplication::translate("MainWindow", "Clynder FWD", Q_NULLPTR));
        btn_clynderMID_right->setText(QApplication::translate("MainWindow", "Clynder MID", Q_NULLPTR));
        btn_clynderBWD_right->setText(QApplication::translate("MainWindow", "Clynder BWD", Q_NULLPTR));
        btn_ledON_right->setText(QApplication::translate("MainWindow", "Led ON", Q_NULLPTR));
        btn_ledOFF_right->setText(QApplication::translate("MainWindow", "Led OFF", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
