#pragma once

#include "../../GraphicObject/LineObject/LineObject.h"
#include "../../GraphicObject/GraphicObject.h"

#include <QObject>
#include <QSize>
#include <QImage>
#include <QPainter>
#include <QList>
#include <QDebug>

class CanvasManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int width READ width NOTIFY canvasCreated)
    Q_PROPERTY(int height READ height NOTIFY canvasCreated)
    Q_PROPERTY(QSize resolution READ resolution NOTIFY canvasCreated)
    Q_PROPERTY(QImage currentImage READ currentImage NOTIFY canvasCreated)
    Q_PROPERTY(Tool activeTool READ activeTool WRITE setActiveTool NOTIFY activeToolChanged)

public:
    enum Tool {
        ToolNone,
        ToolLine,
        ToolSelect
    };

    Q_ENUM(Tool)
    explicit CanvasManager(QObject* parent = nullptr);
    
    Q_INVOKABLE void createCanvas(int width, int height);
    Q_INVOKABLE void clearCanvas();

    Q_INVOKABLE Tool activeTool() const { return m_activeTool; }
    Q_INVOKABLE void setActiveTool(Tool tool);

    Q_INVOKABLE void addLine(const QVector3D& start, const QVector3D& end);
    Q_INVOKABLE void startDrawingLine(const QVector3D& point);
    Q_INVOKABLE void updateDrawingLine(const QVector3D& point);
    Q_INVOKABLE void finishDrawingLine(const QVector3D& point);

    Q_INVOKABLE void selectObjectAt(const QVector3D& point);
    Q_INVOKABLE void clearSelection();
    
    int width() const;
    int height() const;
    QSize resolution() const;

    QImage currentImage() const;

signals:
    void canvasCreated();
    void activeToolChanged();

private:
    void redrawCanvas();
    GraphicObject* findObjectAt(const QPointF& point);

private:
    int m_width = 0;
    int m_height = 0;
    QImage m_canvasImage;
    
    QList<GraphicObject*> m_objects;
    Tool m_activeTool = ToolNone;
    
    QVector3D m_tempStartPoint;
    bool m_isDrawing = false;
};
