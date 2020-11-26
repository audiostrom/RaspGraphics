/*
  ==============================================================================

    GraphicsElement.h
    Created: 26 Nov 2020 8:27:01am
    Author:  Nikolai Bergstrøm
//This class contains the user data, and manages both the Cut & Fill Widget
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "WidgetBase.h"
#include "RenderArea.h"

class GraphicsElement
{
public:
    GraphicsElement();

    virtual ~GraphicsElement();
    void setGraphicsType(juce::String gfxType=juce::String());
    void animate();
    void fire();
    void addToRenderView(RenderArea& fillArea,RenderArea& cutArea);
private:
    void createWidgets(juce::String gfxType=juce::String());
   std::unique_ptr<WidgetBase> fillWidget;
   std::unique_ptr<WidgetBase> cutWidget;


};