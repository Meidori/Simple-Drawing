#pragma once

#include "../../GraphicObject/LineObject/LineObject.h"
#include "../../GraphicObject/GraphicObject.h"

#include <QObject>
#include <QSize>
#include <QImage>
#include <QPainter>
#include <QList>

class CanvasManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int width READ width NOTIFY canvasCreated)
    Q_PROPERTY(int height READ height NOTIFY canvasCreated)
    Q_PROPERTY(QSize resolution READ resolution NOTIFY canvasCreated)
    Q_PROPERTY(QImage currentImage READ currentImage NOTIFY canvasCreated)
    

public:
    explicit CanvasManager(QObject* parent = nullptr);
    
    Q_INVOKABLE void createCanvas(int width, int height);
    Q_INVOKABLE void clearCanvas();
    Q_INVOKABLE void addLine(const QVector3D& start, const QVector3D& end);
    
    int width() const;
    int height() const;
    QSize resolution() const;

    QImage currentImage() const;

signals:
    void canvasCreated();

private:
    void redrawCanvas();

private:
    int m_width = 0;
    int m_height = 0;
    QImage m_canvasImage;
    QList<GraphicObject*> m_objects;
};
