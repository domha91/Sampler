/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SamplerAudioProcessorEditor::SamplerAudioProcessorEditor (SamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), mWaveThumbnail (p), mADSR (p), audioProcessor (p)
{
    auto logoImage = ImageCache::getFromMemory(BinaryData::EasyTuneSamplerLogo_png, BinaryData::EasyTuneSamplerLogo_pngSize);

    if(!logoImage.isNull())
        mImageComponent.setImage(logoImage, RectanglePlacement::stretchToFit);
    else
        jassert(!logoImage.isNull());
    
    startTimerHz(30);
    addAndMakeVisible(mWaveThumbnail);
    addAndMakeVisible(mADSR);
    addAndMakeVisible(mImageComponent);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 400);
}

SamplerAudioProcessorEditor::~SamplerAudioProcessorEditor()
{
    stopTimer();
}

//==============================================================================
void SamplerAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(Colours::black); 

    mWaveThumbnail.setBoundsRelative( 0.0f, 0.25f, 1.0f, 0.5f);
    mADSR.setBoundsRelative(0.0f,0.7f, 1.0f, 0.25f);
    mImageComponent.setBoundsRelative(0.0f,0.0f,0.33f,0.33f);

}

void SamplerAudioProcessorEditor::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void SamplerAudioProcessorEditor::timerCallback()
{
    repaint();
}

