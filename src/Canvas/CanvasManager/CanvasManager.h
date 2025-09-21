#pragma once

#include <QObject>
#include <QSize>
#include <QImage>

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
    
    int width() const;
    int height() const;
    QSize resolution() const;

    QImage currentImage() const;

signals:
    void canvasCreated();

private:
    int m_width = 0;
    int m_height = 0;
    QImage m_canvasImage;
};
