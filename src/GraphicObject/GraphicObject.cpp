#include "GraphicObject.h"

GraphicObject::GraphicObject(QObject* parent) 
    : QObject(parent) 
{
}

void GraphicObject::setSelected(bool selected)
{
    if (m_selected != selected) {
        m_selected = selected;
        emit selectionChanged();
    }
}
