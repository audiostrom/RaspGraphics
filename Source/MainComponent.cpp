#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{

    
    setOpaque (true);

    if (auto* peer = getPeer())
        peer->setCurrentRenderingEngine (0);

    openGLContext.attachTo (*getTopLevelComponent());
    
    fillArea = engine.getFillArea().get();
    cutArea = engine.getCutArea().get();
    addAndMakeVisible(fillArea);
    addAndMakeVisible(cutArea);

    testElement = engine.createNewGraphics("");

   /* fillTest = std::make_unique<WidgetBase>();
    cutTest = std::make_unique<WidgetBase>();



    fillTest->setGfxSize(juce::Point<float>(300.0f,100.0f));
    fillTest->setGfxPos(juce::Point<float>(100.0f,100.0f));

    cutTest->setGfxSize(juce::Point<float>(300.0f,100.0f));
    cutTest->setGfxPos(juce::Point<float>(100.0f,100.0f));*/




    setSize (600, 400);

    //this is not solved, who has/owns/creates the widgets, how do you create them etc, etc

    // engine.addElement(testComp.get());
}

MainComponent::~MainComponent()
{
    openGLContext.detach();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::green);

   
}

void MainComponent::resized()
{
   /* testComp->setBounds(0,32,getWidth(),getHeight()-32); //The widget has access to the entire canvas
    testComp->setGfxPos(juce::Point<float>(getWidth()*0.1,getHeight()-100));
    testComp->setGfxSize(juce::Point<float>(getWidth()*0.25,getHeight()*0.1));*/

   fillArea->setBounds(0,32,getWidth()/2,getHeight()-32);
   cutArea->setBounds(getWidth()/2,32,getWidth()/2,getHeight()-32);

    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainComponent::mouseUp(const juce::MouseEvent &event)
{
    Component::mouseUp(event);
    if (event.mods.isRightButtonDown())
    {
        juce::DocumentWindow *wind = dynamic_cast<juce::DocumentWindow *>(getTopLevelComponent());
        if (wind != nullptr)
        {
         wind->setFullScreen(!wind->isFullScreen());
         wind->setMouseCursor(juce::MouseCursor::NoCursor);
        }
    }
    else
    {
        testElement->fire();
    }

}
