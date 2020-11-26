/*
  ==============================================================================

    RenderArea.cpp
    Created: 25 Nov 2020 11:32:44am
    Author:  Nikolai Bergstrøm

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RenderArea.h"

//==============================================================================
RenderArea::RenderArea():
cutMode(false)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setOpaque (true);
}

RenderArea::~RenderArea()
{
}

void RenderArea::paint (juce::Graphics& g)
{

    g.fillAll (juce::Colours::black);   // clear the background

}

void RenderArea::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    for (auto &wid : widgets)
    {
        wid->setBounds(getLocalBounds());
    }
}

void RenderArea::addWidget(WidgetBase *newWidget)
{
    widgets.addIfNotAlreadyThere(newWidget);
    newWidget->setCutMode(cutMode);
    addAndMakeVisible(newWidget);
    newWidget->setBounds(getLocalBounds());
}

void RenderArea::removeWidget(WidgetBase *wid)
{
    removeChildComponent(wid);
    widgets.remove(widgets.indexOf(wid));
}

bool RenderArea::isCutMode() const
{
    return cutMode;
}

void RenderArea::setCutMode(bool cutMode)
{
    RenderArea::cutMode = cutMode;
}
