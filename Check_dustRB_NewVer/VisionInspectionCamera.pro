#-------------------------------------------------
#
# Project created by QtCreator nvs credit
#
#-------------------------------------------------

QT       += core gui
QT       += core gui serialport
#QT += core
#CONFIG += staticlib c++11
#CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VisionInspectionCamera
TEMPLATE = app

RESOURCES += \
    Icon.qrc

SOURCES += main.cpp\
    mainwindow.cpp \
    myvision.cpp \
    process.cpp \
    MTickTimer.cpp \
    processvision.cpp \
    processcam.cpp \
    teachcheckglare.cpp \
    processcheckauto.cpp

HEADERS  += mainwindow.h \
    myvision.h \
    myDefine.h \
    process.h \
    MTickTimer.h \
    processvision.h \
    processcam.h \
    teachcheckglare.h \
    processcheckauto.h

FORMS    += mainwindow.ui

unix {
    DEFINES += UNIX
    INCLUDEPATH += /usr/local/include/
    LIBS += -L/usr/local/lib -lopencv_world
    LIBS += -L/usr/lib -lwiringPi
}


#win32:CONFIG(release, debug|release): {
#    DEFINES += WIN32
#    DEFINES += QT_NO_DEBUG_OUTPUT

#    # Add OpenCv libary
#    INCLUDEPATH += "C:\opencv_330\include"
#    LIBS += -L"C:\opencv_330\x86\vc14\lib"
#    SHARED_LIB_FILES = $$files(C:\opencv_330\x86\vc14\lib\*330.lib)
#    for(FILE, SHARED_LIB_FILES) {
#        BASENAME = $$basename(FILE)
#        LIBS += -l$$replace(BASENAME,330.lib,330)
#    }


#    LIBS += -lKernel32
#    message($$LIBS)

#}
#else:win32:CONFIG(debug, debug|release): {
#    DEFINES += WIN32

#    # Add OpenCv libary
#    INCLUDEPATH += "C:\opencv_330\include"
#    LIBS += -L"C:\opencv_330\x86\vc14\lib"
#    SHARED_LIB_FILES = $$files(C:\opencv_330\x86\vc14\lib\*330d.lib)
#    for(FILE, SHARED_LIB_FILES) {
#        BASENAME = $$basename(FILE)
#        LIBS += -l$$replace(BASENAME,330d.lib,330d)
#    }

#    LIBS += -lKernel32
#    message($$LIBS)
#}


win64:CONFIG(release, debug|release): {
    DEFINES += WIN64
    DEFINES += QT_NO_DEBUG_OUTPUT

    # Add OpenCv libary
    INCLUDEPATH += "C:\opencv_330\include"
    LIBS += -L"C:\opencv_330\x64\vc14\lib"
    SHARED_LIB_FILES = $$files(C:\opencv_330\x64\vc14\lib\*330.lib)
    for(FILE, SHARED_LIB_FILES) {
        BASENAME = $$basename(FILE)
        LIBS += -l$$replace(BASENAME,330.lib,330)
    }


    LIBS += -lKernel64
    message($$LIBS)

}
else:win64:CONFIG(debug, debug|release): {
    DEFINES += WIN64
    # Add OpenCv libary
    INCLUDEPATH += "C:\opencv_330\include"
    LIBS += -L"C:\opencv_330\x64\vc14\lib"
    SHARED_LIB_FILES = $$files(C:\opencv_330\x64\vc14\lib\*330d.lib)
    for(FILE, SHARED_LIB_FILES) {
        BASENAME = $$basename(FILE)
        LIBS += -l$$replace(BASENAME,330d.lib,330d)
    }

    LIBS += -lKernel64
    message($$LIBS)
}













































































































































































































































































































































































































































































































































































#-------------------------------------------------
#
# Project created by QtCreator 2018-07-24T12:13:07
#
#-------------------------------------------------

QT       += core gui
QT       += core gui serialport
#QT += core
#CONFIG += staticlib c++11
#CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VisionInspectionCamera
TEMPLATE = app

RESOURCES += \
    Icon.qrc


SOURCES += main.cpp\
        mainwindow.cpp \
    myvision.cpp \
    process.cpp \
    MTickTimer.cpp \
    processvision.cpp \
    processcam.cpp \
    teachcheckglare.cpp



HEADERS  += mainwindow.h \
    myvision.h \
    myDefine.h \
    process.h \
    MTickTimer.h \
    processvision.h \
    processcam.h \
    teachcheckglare.h


FORMS    += mainwindow.ui \
    teachcheckglare.ui



unix {
    DEFINES += UNIX
    INCLUDEPATH += /usr/local/include/
    LIBS += -L/usr/local/lib -lopencv_world
    LIBS += -L/usr/lib -lwiringPi
}





win32:CONFIG(release, debug|release): {
    DEFINES += WIN32
    DEFINES += QT_NO_DEBUG_OUTPUT

    # Add OpenCv libary
    INCLUDEPATH += "C:\opencv_330\include"
    LIBS += -L"C:\opencv_330\x64\vc14\lib"
    SHARED_LIB_FILES = $$files(C:\opencv_330\x64\vc14\lib\*330.lib)
    for(FILE, SHARED_LIB_FILES) {
        BASENAME = $$basename(FILE)
        LIBS += -l$$replace(BASENAME,330.lib,330)
    }


    LIBS += -lKernel32
    message($$LIBS)

}
else:win32:CONFIG(debug, debug|release): {
    DEFINES += WIN32

    # Add OpenCv libary
    INCLUDEPATH += "C:\opencv_330\include"
    LIBS += -L"C:\opencv_330\x64\vc14\lib"
    SHARED_LIB_FILES = $$files(C:\opencv_330\x64\vc14\lib\*330d.lib)
    for(FILE, SHARED_LIB_FILES) {
        BASENAME = $$basename(FILE)
        LIBS += -l$$replace(BASENAME,330d.lib,330d)
    }

    LIBS += -lKernel32
    message($$LIBS)
}

DISTFILES += \
    Parameter/ParamGeneral.json \
    Parameter/J5/ParamModel.json \
    Parameter/J5/Readme.txt.txt \
    Parameter/J7/ParamModel.json \
    Parameter/J7/Readme.txt.txt \
    Parameter/Note9/ParamModel.json \
    Parameter/Note9/Readme.txt.txt \
    Parameter/Note10/ParamModel.json \
    Parameter/Note10/Readme.txt.txt \
    Parameter/S8/ParamModel.json \
    Parameter/S8/Readme.txt.txt \
    Parameter/S8+/ParamModel.json \
    Parameter/S8+/Readme.txt.txt \
    Parameter/S9/ParamModel.json \
    Parameter/S9/Readme.txt.txt \
    Parameter/S9/ParamModel.json \
    Parameter/S9/Readme.txt.txt \
    Parameter/S10/ParamModel.json \
    Parameter/S10/Readme.txt.txt \
    Parameter/S9+/ParamModel.json \
    Parameter/S9+/Readme.txt.txt




