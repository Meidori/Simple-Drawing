#include "CanvasItem.h"
#include <QPainter>

CanvasItem::CanvasItem(QQuickItem *parent)
    : QQuickPaintedItem(parent) {}

void CanvasItem::paint(QPainter *painter)
{
    if (!m_image.isNull()) {
        painter->drawImage(0, 0, m_image);
    }
}

QImage CanvasItem::image() const { return m_image; }

void CanvasItem::setImage(const QImage &image)
{
    m_image = image;
    update();
    emit imageChanged();
}
