#include "LineObject.h"

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

    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    painter->drawLine(m_startPoint.toPointF(), m_endPoint.toPointF());
}

