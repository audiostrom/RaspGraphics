/*
  ==============================================================================

    GFXEngine.cpp
    Created: 24 Nov 2020 5:50:46pm
    Author:  Nikolai Bergstrøm

  ==============================================================================
*/

#include "GFXEngine.h"

void GFXEngine::timerCallback()
{
    for (auto &element : gfxElements)
    {
        element->animate();
    }
}

GFXEngine::GFXEngine()
{
    fillArea = std::make_unique<RenderArea>();
    cutArea = std::make_unique<RenderArea>();
    cutArea->setCutMode(true);
    startTimerHz(50);
}

GFXEngine::~GFXEngine()
{

}

GraphicsElement *GFXEngine::createNewGraphics(juce::String gfxType)
{
    GraphicsElement* element = new GraphicsElement();
    element->setGraphicsType(gfxType);
    element->addToRenderView(*fillArea,*cutArea);
    gfxElements.add(element);

    return element;
}

const std::unique_ptr<RenderArea> &GFXEngine::getFillArea() const
{
    return fillArea;
}

const std::unique_ptr<RenderArea> &GFXEngine::getCutArea() const
{
    return cutArea;
}
