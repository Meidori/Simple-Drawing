#pragma once

#include "../GraphicObject.h"
#include <QVector3D>
#include <QPainter>
#include <QPointF>

class LineObject : public GraphicObject 
{
    Q_OBJECT
    Q_PROPERTY(QVector3D startPoint READ startPoint WRITE setStartPoint NOTIFY pointsChanged)
    Q_PROPERTY(QVector3D endPoint READ endPoint WRITE setEndPoint NOTIFY pointsChanged)

public:
    LineObject(QObject* parent = nullptr);
    LineObject(const QVector3D& start, const QVector3D& end, QObject* parent = nullptr);

    QVector3D startPoint() { return m_startPoint; }
    QVector3D endPoint() { return m_endPoint; }

    void setStartPoint(const QVector3D& point);
    void setEndPoint(const QVector3D& point);

    void draw(QPainter* painter) override;

signals:
    void pointsChanged();

private:
    QVector3D m_startPoint;
    QVector3D m_endPoint;
};
