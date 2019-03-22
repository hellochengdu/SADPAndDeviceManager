#include "SADPAndDeviceManager.h"
#include <QMenuBar>
#include <QLabel>
#include <QPushButton>
#include <QDockWidget>
#include <QStackedLayout>
#include <QVBoxLayout>
#include "IPServer.h"
SADPAndDeviceManager::SADPAndDeviceManager(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//setWindowIcon(QIcon(":/Resources/JF-NAS.ico"));
	//setWindowTitle(QStringLiteral("设备管理器"));
	//QWidget* backWidget = takeCentralWidget();
	//if (backWidget)
	//{
	//	delete backWidget;
	//}
	///*QLayout* backLayout = this->layout();
	//if (backLayout)
	//{
	//	delete backLayout;
	//}*/
	//QMenuBar* MenuofMain = this->menuBar();
	//if (MenuofMain)
	//{
	//	delete MenuofMain;
	//}
	////QWidget* WidgetofMain = this->menuWidget();
	////WidgetofMain->setStyleSheet("background-color:grey");
	//
	////MenuofMain->addAction(QStringLiteral("控制面板"));
	////控制面板的按钮
	//MainWidget = new QDockWidget();
	//DeviceManager = new QPushButton(MainWidget);
	//DeviceManager->setGeometry(this->width()/2-150,this->height()/2-50,100,30);
	//DeviceManager->setText(QStringLiteral("设备管理"));
	//
	//DeviceLayout = new QPushButton(MainWidget);
	//DeviceLayout->setGeometry(this->width()/2-150, this->height()/2+50, 100, 30);
	//DeviceLayout->setText(QStringLiteral("设备配置"));
	//VideoSetting = new QPushButton(MainWidget);
	//VideoSetting->setGeometry(this->width()/2+50,this->height()/2-50, 100, 30);
	//VideoSetting->setText(QStringLiteral("录像计划"));
	//LogManagement = new QPushButton(MainWidget);
	//LogManagement->setGeometry(this->width()/2+50, this->height()/2+50, 100, 30);
	//LogManagement->setText(QStringLiteral("日志管理"));
	//MainWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
	//addDockWidget(Qt::LeftDockWidgetArea,MainWidget);
	////按钮背景设置
	//QString button_style = "QPushButton{background-color:blue;color: white;border-radius:10px;border: 2px groove gray;border-style: outset;}" "QPushButton:hover{background-color:white; color: black;}" "QPushButton:pressed{background-color:rgb(85, 170, 255);border - style: inset; }";
	//DeviceManager->setStyleSheet(button_style);
	//DeviceLayout->setStyleSheet(button_style);
	//VideoSetting->setStyleSheet(button_style);
	//LogManagement->setStyleSheet(button_style);
	////按钮对应的槽函数
	//connect(this->DeviceManager, SIGNAL(clicked()),this, SLOT(DeviceManager_slot()));
	//connect(this->DeviceLayout, SIGNAL(clicked()),this, SLOT(DeviceLayout_slot()));
	//connect(this->VideoSetting, SIGNAL(clicked()),this, SLOT(VideoSetting_slot()));
	//connect(this->LogManagement, SIGNAL(clicked()),this, SLOT(LogManagement_slot()));
}
void SADPAndDeviceManager::DeviceManager_slot()
{
	/*MainWidget->hide();
	DeviceManagerWidget = new QDockWidget();
	addDockWidget(Qt::LeftDockWidgetArea, DeviceManagerWidget);
	DeviceManagerWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
	IPServer* DeviceManager_ip=new IPServer(DeviceManagerWidget);*/
}
void SADPAndDeviceManager::DeviceLayout_slot()
{

}
void SADPAndDeviceManager::VideoSetting_slot()
{

}
void SADPAndDeviceManager::LogManagement_slot()
{

}
