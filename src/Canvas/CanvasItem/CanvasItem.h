#pragma once

#include <QQuickPaintedItem>
#include <QImage>

class CanvasItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)

public:
    CanvasItem(QQuickItem *parent = nullptr);
    
    void paint(QPainter *painter) override;
    
    QImage image() const;
    void setImage(const QImage &image);

signals:
    void imageChanged();

private:
    QImage m_image;
};
