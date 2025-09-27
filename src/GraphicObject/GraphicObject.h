#pragma once

#include <QObject>
#include <QPainter>

class GraphicObject : public QObject 
{
    Q_OBJECT

public:
    explicit GraphicObject(QObject* parent = nullptr);
    virtual ~GraphicObject() = default;

    virtual void draw(QPainter* painter) = 0;
};
