#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuickControls2>
#include <bpptablemodel.h>
#include <bppfontawesome.h>
#include "confighandler.h"
#include "proxyhandler.h"
#include "common.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    app.setOrganizationName("somename");
    app.setOrganizationDomain("somename");
    QQuickStyle::setStyle("Material");

    WORKER = new Worker;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("worker", WORKER);

    bpp::TableModel::registerQml();
    bpp::FontAwesome::registerQml(engine);
    engine.addImportPath("qrc:/");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    qmlRegisterType<ConfigHandler>("mycpp", 1, 0, "ConfigHandler");
    qmlRegisterType<ProxyHandler>("mycpp", 1, 0, "ProxyHandler");

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
