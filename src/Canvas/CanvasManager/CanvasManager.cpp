#include "CanvasManager.h"
#include <QPainter>

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


int CanvasManager::width() const { return m_width; }
int CanvasManager::height() const { return m_height; }
QSize CanvasManager::resolution() const { return QSize(m_width, m_height); }
QImage CanvasManager::currentImage() const { return m_canvasImage; }
