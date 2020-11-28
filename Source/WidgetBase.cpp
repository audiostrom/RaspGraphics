/*
  ==============================================================================

    WidgetBase.cpp
    Created: 24 Nov 2020 5:44:38pm
    Author:  Nikolai Bergstrøm

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WidgetBase.h"

//==============================================================================
WidgetBase::WidgetBase():
frame(0),
transitionTime(3.0f),
holdTime(5.0f),
currentState(off)
{
    setOpaque(false);
    setGfxSize(juce::Point<float>(300.0f,100.0f));
    setGfxPos(juce::Point<float>(100.0f,100.0f));
    //this->setBufferedToImage(true);
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

WidgetBase::~WidgetBase()
{
}

void WidgetBase::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    g.setColour(juce::Colours::black);
    g.fillAll();
    g.setFont(gfxSize.y*0.5);
    if (currentState==transIn)
    {
        //Steps = pixels pr frame;
        //Frames to move
        float framesToMove = secondsToFrame(transitionTime);
        float time = float(frame)/framesToMove;


        backgroundIn.startPos=gfxPos.withX(0-gfxSize.getX());
        backgroundIn.endPos=gfxPos;

        juce::Point<float> newPos = backgroundIn.getValue(easeOut(time));

        juce::Rectangle<float> back(newPos.getX(),gfxPos.getY(),gfxSize.getX(),gfxSize.getY()); //These need to be set
        g.setColour(getColour(juce::Colours::burlywood));
        g.fillRect(back);

        g.setColour(getColour(juce::Colours::green));
        newPos = textIn.getValue(easeOut(time));
        g.drawText("Testmannen",newPos.getX(),newPos.getY(),gfxSize.getX(),gfxSize.getY(),juce::Justification::centred);
    }
    if (currentState==displaying)
    {
        juce::Rectangle<float> back(gfxPos.getX(),gfxPos.getY(),gfxSize.getX(),gfxSize.getY()); //These need to be set
        g.setColour(getColour(juce::Colours::burlywood));
        g.fillRect(back);

        g.setColour(getColour(juce::Colours::green));

        g.drawText("Testmannen",gfxPos.getX(),gfxPos.getY(),gfxSize.getX(),gfxSize.getY(),juce::Justification::centred);
    }
    if (currentState==transOut)
    {
        float framesToMove = secondsToFrame(transitionTime);
        float time = float(frame-secondsToFrame(holdTime+transitionTime))/framesToMove;

        juce::Point<float> newPos = backgroundOut.getValue(easeOut(time));

        juce::Rectangle<float> back(newPos.getX(),gfxPos.getY(),gfxSize.getX(),gfxSize.getY()); //These need to be set
        g.setColour(getColour(juce::Colours::burlywood));
        g.fillRect(back);

        g.setColour(getColour(juce::Colours::green));
        newPos = textOut.getValue(easeOut(time));
        g.drawText("Testmannen",newPos.getX(),newPos.getY(),gfxSize.getX(),gfxSize.getY(),juce::Justification::centred);
    }

}

void WidgetBase::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    gfxPos.setY(getHeight()-gfxSize.getY()-32);
    gfxPositionOrSizeChanged();
}

void WidgetBase::animate()
{
    frame++;
    if ((transitionTime>0.0f) && currentState==transIn)
    {
      if (frame==secondsToFrame(transitionTime)) setState(displaying); //Switching to static animation
    }
    if (currentState==displaying && (frame==secondsToFrame(transitionTime+holdTime))) //Switch to out
    {
        setState(transOut);
    }
    if (currentState==transOut && (frame>secondsToFrame(transitionTime+holdTime+transitionTime))) setState(off);
    //repaint(0,getHeight()-100,500,100);

    repaint(juce::Rectangle<float>(gfxPos.getX(),gfxPos.getY(),gfxSize.getX(),gfxSize.getY()).toNearestIntEdges());
}

void WidgetBase::setState(WidgetBase::GFXState newState)
{
    currentState = newState;
}

const juce::Point<float> &WidgetBase::getGfxPos() const
{
    return gfxPos;
}

void WidgetBase::setGfxPos(const juce::Point<float> &gfxPos)
{
    WidgetBase::gfxPos = gfxPos;
    gfxPositionOrSizeChanged();
}

const juce::Point<float> &WidgetBase::getGfxSize() const
{
    return gfxSize;

}

void WidgetBase::setGfxSize(const juce::Point<float> &gfxSize)
{
    WidgetBase::gfxSize = gfxSize;
    gfxPositionOrSizeChanged();
}

int WidgetBase::secondsToFrame(float sec)
{
    return juce::roundToInt(sec*frameRate);
}

void WidgetBase::fire()
{
    frame =0;
    if (transitionTime>0.0f) setState(transIn); else setState(displaying);
}

float WidgetBase::easeOut(float time)
{
    return time*(2-time);

    //https://gist.github.com/gre/1650294
}

void WidgetBase::gfxPositionOrSizeChanged()
{
    backgroundIn.startPos=gfxPos.withX(0-gfxSize.getX());
    backgroundIn.endPos=gfxPos;
    backgroundIn.endTime=0.5f;

    textIn.startPos=gfxPos.withX(0-gfxSize.getX());
    textIn.endPos=gfxPos;
    textIn.startTime=0.5f;

    backgroundOut.startPos=gfxPos;
    backgroundOut.endPos=gfxPos.withX(getWidth()+gfxSize.getX());

    textOut.startPos=gfxPos;
    textOut.endPos=gfxPos.withX(getWidth()+gfxSize.getX());
    textOut.endTime=0.5f;
}

bool WidgetBase::isCutMode() const
{
    return cutMode;
}

void WidgetBase::setCutMode(bool cutMode)
{
    WidgetBase::cutMode = cutMode;
}

juce::Colour WidgetBase::getColour(juce::Colour cl)
{
    if (!cutMode) return cl; else return juce::Colours::white;
}

