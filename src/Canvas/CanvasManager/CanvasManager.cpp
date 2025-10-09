#include "CanvasManager.h"

CanvasManager::CanvasManager(QObject* parent) 
    : QObject(parent)
{
    m_canvasImage = QImage(0, 0, QImage::Format_ARGB32);
    m_canvasImage.fill(Qt::transparent);
}

void CanvasManager::createCanvas(int width, int height)
{
    m_width = width;
    m_height = height;
    
    m_canvasImage = QImage(m_width, m_height, QImage::Format_ARGB32);
    m_canvasImage.fill(Qt::white);
    
    emit canvasCreated();
}

void CanvasManager::clearCanvas()
{
    if (!m_canvasImage.isNull() && m_canvasImage.size().isValid()) {
        m_canvasImage.fill(Qt::white);
        emit canvasCreated();
    }
}

void CanvasManager::setActiveTool(Tool tool)
{
    if (m_activeTool != tool) {
        m_activeTool = tool;
        
        if (tool != ToolSelect) {
            clearSelection();
        }
        
        emit activeToolChanged();
    }
}

void CanvasManager::addLine(const QVector3D& start, const QVector3D& end)
{
    auto* line = new LineObject(start, end, this);
    m_objects.append(line);
    
    redrawCanvas();
}

void CanvasManager::startDrawingLine(const QVector3D& point)
{
    if (m_activeTool != ToolLine) return;

    m_isDrawing = true;
    m_tempStartPoint = point;
}

void CanvasManager::updateDrawingLine(const QVector3D& point)
{
    if (!m_isDrawing || m_activeTool != ToolLine) return;
    
    redrawCanvas();
    
    if (!m_canvasImage.isNull()) {
        QImage tempImage = m_canvasImage;
        QPainter painter(&tempImage);
        painter.setPen(QPen(Qt::gray, 2, Qt::DotLine, Qt::RoundCap));
        painter.drawLine(m_tempStartPoint.toPointF(), point.toPointF());
        
        m_canvasImage = tempImage;
        emit canvasCreated();
    }
}

void CanvasManager::finishDrawingLine(const QVector3D& point)
{
    if (!m_isDrawing || m_activeTool != ToolLine) return;
    
    m_isDrawing = false;
    addLine(m_tempStartPoint, point);
}

void CanvasManager::redrawCanvas()
{
    if (m_canvasImage.isNull()) return;
    
    m_canvasImage.fill(Qt::white);
    QPainter painter(&m_canvasImage);
    
    for (auto* object : m_objects) {
        object->draw(&painter);
    }
    
    emit canvasCreated();
}

void CanvasManager::selectObjectAt(const QVector3D& point)
{
    if (m_activeTool != ToolSelect) return;
    
    GraphicObject* clickedObject = findObjectAt(point.toPointF());
    
    for (auto* object : m_objects) {
        object->setSelected(false);
    }
    
    if (clickedObject) {
        clickedObject->setSelected(true);
        qDebug() << "Object selected";
    }
    
    redrawCanvas();
}

void CanvasManager::clearSelection()
{
    for (auto* object : m_objects) {
        object->setSelected(false);
    }
    redrawCanvas();
}

GraphicObject* CanvasManager::findObjectAt(const QPointF& point)
{
    for (int i = m_objects.size() - 1; i >= 0; --i) {
        GraphicObject* obj = m_objects[i];
        if (obj->contains(point)) {
            return obj;
        }
    }
    return nullptr;
}

int CanvasManager::width() const { return m_width; }
int CanvasManager::height() const { return m_height; }
QSize CanvasManager::resolution() const { return QSize(m_width, m_height); }
QImage CanvasManager::currentImage() const { return m_canvasImage; }




