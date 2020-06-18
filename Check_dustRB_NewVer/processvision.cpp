#include "processvision.h"
#include "mainwindow.h"


  processVision::processVision(QObject *parent) : QThread(parent) {
      m_bRun = false;

  }
  processVision::~processVision() {
      this->StopThread();
      this->terminate();
      this->wait(10);
  }

  void processVision::StartThread() {
      m_bRun = true;
      this->start(QThread::HighPriority);
  }

  void processVision::StopThread() {
      m_bRun = false;
      usleep(10000);
      this->quit();
  }

  void processVision::run() {
      while (m_bRun) {
         emit ProcessLoop();
           msleep(100);
      }
      return;
  }


