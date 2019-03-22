#pragma once

#include <QtWidgets/QMainWindow>

#include "ui_SADPAndDeviceManager.h"

class SADPAndDeviceManager : public QMainWindow
{
    Q_OBJECT

public:
    SADPAndDeviceManager(QWidget *parent = Q_NULLPTR);
 private slots:
	void DeviceManager_slot();
	void DeviceLayout_slot();
	void VideoSetting_slot();
	void LogManagement_slot();

private:
    Ui::SADPAndDeviceManagerClass ui;
};
