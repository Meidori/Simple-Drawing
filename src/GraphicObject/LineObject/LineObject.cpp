#include "LineObject.h"
#include <QLineF>
#include <cmath>

LineObject::LineObject(QObject* parent)
    : GraphicObject(parent), m_startPoint(0,0,1), m_endPoint(0,0,1) {}

LineObject::LineObject(const QVector3D& start, const QVector3D& end, QObject* parent)
    : GraphicObject(parent), m_startPoint(start), m_endPoint(end) {}

void LineObject::setStartPoint(const QVector3D& point) {
    if (m_startPoint == point) return;
    m_startPoint = point;
    emit pointsChanged();
}

void LineObject::setEndPoint(const QVector3D& point) {
    if (m_endPoint == point) return;
    m_endPoint = point;
    emit pointsChanged();
}

void LineObject::draw(QPainter* painter) {
    if (!painter) return;

    if (m_selected) {
        painter->setPen(QPen(Qt::blue, 3, Qt::SolidLine, Qt::RoundCap));
    } else {
        painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    }
    
    painter->drawLine(m_startPoint.toPointF(), m_endPoint.toPointF());
}

bool LineObject::contains(const QPointF& point) const {
    QLineF line(m_startPoint.toPointF(), m_endPoint.toPointF());
    
    qreal distance = std::abs((line.dy() * point.x() - line.dx() * point.y() + line.x2() * line.y1() - line.y2() * line.x1()) 
                             / std::sqrt(line.dx() * line.dx() + line.dy() * line.dy()));
    
    const qreal threshold = 5.0;
    
    QRectF rect = boundingRect().adjusted(-threshold, -threshold, threshold, threshold);
    
    return rect.contains(point) && distance <= threshold;
}

QRectF LineObject::boundingRect() const {
    QPointF start = m_startPoint.toPointF();
    QPointF end = m_endPoint.toPointF();
    
    return QRectF(
        QPointF(std::min(start.x(), end.x()), std::min(start.y(), end.y())),
        QPointF(std::max(start.x(), end.x()), std::max(start.y(), end.y()))
    );
}
