#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "./Canvas/CanvasManager/CanvasManager.h"
#include "./Canvas/CanvasItem/CanvasItem.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    
    CanvasManager manager;
    
    qmlRegisterType<CanvasManager>("CanvasUtils", 1, 0, "CanvasManager");
    qmlRegisterType<CanvasItem>("CanvasUtils", 1, 0, "CanvasItem");
    
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("canvasManager", &manager);
    
    const QUrl url(u"qml/main.qml"_qs);
    engine.load(url);
    
    return app.exec();
}
