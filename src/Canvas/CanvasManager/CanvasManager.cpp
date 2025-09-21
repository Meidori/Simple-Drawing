#include "CanvasManager.h"

CanvasManager::CanvasManager(QObject* parent) 
    : QObject(parent)
{
}

void CanvasManager::createCanvas(int width, int height)
{
    m_width = width;
    m_height = height;
    emit canvasCreated();
}

int CanvasManager::width() const 
{ 
    return m_width; 
}

int CanvasManager::height() const 
{ 
    return m_height; 
}

QSize CanvasManager::resolution() const 
{ 
    return QSize(m_width, m_height); 
}
