/*
  ==============================================================================

    RenderArea.h
    Created: 25 Nov 2020 11:32:44am
    Author:  Nikolai Bergstrøm

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "WidgetBase.h"

//==============================================================================
/*
*/
class RenderArea  : public juce::Component
{
public:
    RenderArea();
    ~RenderArea() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void addWidget(WidgetBase* newWidget);
    void removeWidget(WidgetBase* wid);
private:
    juce::Array<WidgetBase*> widgets;
    bool cutMode;
public:
    bool isCutMode() const;

    void setCutMode(bool cutMode);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RenderArea)
};
