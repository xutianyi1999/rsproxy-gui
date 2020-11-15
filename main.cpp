#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuickControls2>
#include <bpptablemodel.h>
#include <bppfontawesome.h>
#include <qmlcppbridge.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    app.setOrganizationName("somename");
    app.setOrganizationDomain("somename");
    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;

    bpp::TableModel::registerQml();
    bpp::FontAwesome::registerQml(engine);
    engine.addImportPath("qrc:/");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    qmlRegisterType<QmlCppBridge>("mycpp", 1, 0, "QmlCppBridge");

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
