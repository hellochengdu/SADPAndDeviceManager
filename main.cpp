#include "SADPAndDeviceManager.h"
#include "IPServer.h"
#include <QtWidgets/QApplication>
#include <QtQml/QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	qmlRegisterType<IPServer>("Qt.Ipserver", 1, 0, "IPServer");
	qmlRegisterType<SADPAndDeviceManager>("Qt.Ipserver", 1, 0, "SADPAndDeviceManager");
	qmlRegisterType<ThreadOperEntry>("Qt.Ipserver", 1,0, "ThreadOperEntry");
	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("Resources/main.qml")));
	
	QList<QObject*> rootObjects = engine.rootObjects();
	int count = rootObjects.size();
	QObject *root = NULL;
	for (int i=0;i<count;i++)
	{
		if (rootObjects.at(i)->objectName()=="window")
		{
			root = rootObjects.at(i);
			break;
		}
	}
	if (root)
	{
		QVariant returnedValue;
		QMetaObject::invokeMethod(root, "settool", Q_RETURN_ARG(QVariant, returnedValue));// Q_ARG(QVariant, msg));
	}
	IPServer globalIpserver;
    return a.exec();
}
