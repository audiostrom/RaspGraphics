/*
  ==============================================================================

    WidgetBase.h
    Created: 24 Nov 2020 5:44:38pm
    Author:  Nikolai Bergstrøm

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WidgetBase  : public juce::Component
{
public:

    WidgetBase();
    ~WidgetBase() override;

    enum GFXState{off,transIn, transOut, displaying};
    static const int frameRate=50;

    void paint (juce::Graphics&) override;
    void resized() override;
    void animate();
    void setState(GFXState newState);
    void fire();//Shows the widget;

    const juce::Point<float> &getGfxPos() const;
    void setGfxPos(const juce::Point<float> &gfxPos);
    const juce::Point<float> &getGfxSize() const;
    void setGfxSize(const juce::Point<float> &gfxSize);
    bool isCutMode() const;
    void setCutMode(bool cutMode);
private:
    struct KeyFrame{
         juce::Point<float> startPos;
         juce::Point<float> endPos;
         float startTime =0.0f; //A delay on the start in precent
         float endTime =1.0f;
         juce::Point<float> getValue(const float& time)
         {
             float xTravel = abs(endPos.getX()-startPos.getX());
             float yTravel = abs(endPos.getY()-startPos.getY());
             if (time<startTime) return  startPos;
             if (time>endTime) return endPos;
             float newtime = time*1.0f/endTime;
             if (startTime>0.0f)
             {
                 newtime = (newtime-startTime)*1.0f/startTime;
             }

             return juce::Point<float>(startPos.getX()+(xTravel*newtime),startPos.getY()+(yTravel*newtime));
         };
    };

    int frame;
    juce::Point<float> gfxPos; //The static position of the gfx when displayed
    juce::Point<float> gfxSize;
    GFXState currentState;
    float transitionTime;
    float holdTime;
    bool cutMode;

    int secondsToFrame(float sec);
    float easeOut(float time); //Ease out (time 0-1)

    //Keyframes
    KeyFrame backgroundIn;
    KeyFrame backgroundOut;
    KeyFrame textIn;
    KeyFrame textOut;
protected:
    void gfxPositionOrSizeChanged(); //Can be used by subclasses to update keyframes
    juce::Colour getColour(juce::Colour cl);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WidgetBase)
};
