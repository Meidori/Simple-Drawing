#pragma once

#include <QObject>
#include <QPainter>
#include <QRectF>

class GraphicObject : public QObject 
{
    Q_OBJECT
    Q_PROPERTY(bool selected READ isSelected WRITE setSelected NOTIFY selectionChanged)

public:
    explicit GraphicObject(QObject* parent = nullptr);
    virtual ~GraphicObject() = default;

    virtual void draw(QPainter* painter) = 0;
    virtual bool contains(const QPointF& point) const = 0;
    virtual QRectF boundingRect() const = 0;

    bool isSelected() const { return m_selected; }
    void setSelected(bool selected);

signals:
    void selectionChanged();

protected:
    bool m_selected = false;
};
