#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "nonrestoringdivision.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QCoreApplication::setApplicationName("COA-Simulator");
    QCoreApplication::setOrganizationDomain("geetasoftwarecompany.com");
    QCoreApplication::setOrganizationName("Geeta Software Company");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QQmlContext *ctxt = engine.rootContext();
    ctxt->setContextProperty("nonRestoringDivisionCPP", new NonRestoringDivision());

    engine.load(QUrl(QStringLiteral("qrc:/QML/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
