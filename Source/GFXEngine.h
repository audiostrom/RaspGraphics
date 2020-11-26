/*
  ==============================================================================

    GFXEngine.h
    Created: 24 Nov 2020 5:50:46pm
    Author:  Nikolai Bergstrøm

  ==============================================================================
*/
#include <JuceHeader.h>
#include "WidgetBase.h"
#include "GraphicsElement.h"
#include "RenderArea.h"

class GFXEngine:juce::Timer
{
public:
    GFXEngine();
    ~GFXEngine() override;

    GraphicsElement* createNewGraphics(juce::String gfxType);
private:

    void timerCallback() override;
    juce::OwnedArray<GraphicsElement> gfxElements;

    std::unique_ptr<RenderArea> fillArea;
public:
    const std::unique_ptr<RenderArea> &getFillArea() const;

    const std::unique_ptr<RenderArea> &getCutArea() const;

private:
    std::unique_ptr<RenderArea> cutArea;

};
#pragma once
