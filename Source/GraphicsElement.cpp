/*
  ==============================================================================

    GraphicsElement.cpp
    Created: 26 Nov 2020 8:27:01am
    Author:  Nikolai Bergstrøm

  ==============================================================================
*/

#include "GraphicsElement.h"

GraphicsElement::GraphicsElement()
{
    setGraphicsType();
}

GraphicsElement::~GraphicsElement()
{

}

void GraphicsElement::createWidgets(juce::String gfxType)
{
        if (gfxType==juce::String()){
            fillWidget = std::make_unique<WidgetBase>();
            cutWidget = std::make_unique<WidgetBase>();
        }
}

void GraphicsElement::setGraphicsType(juce::String gfxType)
{
    createWidgets(gfxType);
}

void GraphicsElement::animate()
{
    fillWidget->animate();
    cutWidget->animate();
}

void GraphicsElement::fire()
{
    fillWidget->fire();
    cutWidget->fire();
}

void GraphicsElement::addToRenderView(RenderArea& fillArea,RenderArea& cutArea)
{
    fillArea.addWidget(fillWidget.get());
    cutArea.addWidget(cutWidget.get());
}