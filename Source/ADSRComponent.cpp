/*
  ==============================================================================

    ADSRComponent.cpp
    Created: 10 May 2021 10:51:56am
    Author:  domha91

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSRComponent.h"

//==============================================================================
ADSRComponent::ADSRComponent(SamplerAudioProcessor& p) : audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

     //Set up ADSR sliders and attachments to audioProcessor
    mAttackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    mAttackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
    mAttackSlider.setColour(Slider::ColourIds::thumbColourId, Colours::aliceblue);
    addAndMakeVisible(mAttackSlider);

    mAttackLabel.setFont(10.0f);
    mAttackLabel.setText("Attack",NotificationType::dontSendNotification);
    mAttackLabel.setJustificationType(Justification::centredTop);
    mAttackLabel.setColour(Label::ColourIds::textColourId, Colours::aliceblue);
    mAttackLabel.attachToComponent(&mAttackSlider, false);
    addAndMakeVisible(mAttackLabel);

    mAttackAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),"ATTACK", mAttackSlider);


    mDecaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    mDecaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
    mDecaySlider.setColour(Slider::ColourIds::thumbColourId, Colours::aliceblue);
    addAndMakeVisible(mDecaySlider);

    mDecayLabel.setFont(10.0f);
    mDecayLabel.setText("Decay",NotificationType::dontSendNotification);
    mDecayLabel.setJustificationType(Justification::centredTop);
    mDecayLabel.setColour(Label::ColourIds::textColourId, Colours::aliceblue);
    mDecayLabel.attachToComponent(&mDecaySlider, false);
    addAndMakeVisible(mDecayLabel);

    mDecayAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),"DECAY", mDecaySlider);

    mSustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    mSustainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
    mSustainSlider.setColour(Slider::ColourIds::thumbColourId, Colours::aliceblue);
    addAndMakeVisible(mSustainSlider);

    mSustainLabel.setFont(10.0f);
    mSustainLabel.setText("Sustain",NotificationType::dontSendNotification);
    mSustainLabel.setJustificationType(Justification::centredTop);
    mSustainLabel.setColour(Label::ColourIds::textColourId, Colours::aliceblue);
    mSustainLabel.attachToComponent(&mSustainSlider, false);
    addAndMakeVisible(mSustainLabel);

    mSustainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),"SUSTAIN", mSustainSlider);

    mReleaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    mReleaseSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
    mReleaseSlider.setColour(Slider::ColourIds::thumbColourId, Colours::aliceblue);
    addAndMakeVisible(mReleaseSlider);

    mReleaseLabel.setFont(10.0f);
    mReleaseLabel.setText("Release",NotificationType::dontSendNotification);
    mReleaseLabel.setJustificationType(Justification::centredTop);
    mReleaseLabel.setColour(Label::ColourIds::textColourId, Colours::aliceblue);
    mReleaseLabel.attachToComponent(&mReleaseSlider, false);
    addAndMakeVisible(mReleaseLabel);

    mReleaseAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),"RELEASE", mReleaseSlider);
}

ADSRComponent::~ADSRComponent()
{
}

void ADSRComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(Colours::black);  
}

void ADSRComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    const auto ADSRStartX = 0.6f;
    const auto ADSRStartY = 0.2f;
    const auto ADSRSliderWidth = 0.1f;
    const auto ADSRSliderHeight = 0.75f;

    mAttackSlider.setBoundsRelative(ADSRStartX,ADSRStartY,ADSRSliderWidth,ADSRSliderHeight);
    mDecaySlider.setBoundsRelative(ADSRStartX + ADSRSliderWidth, ADSRStartY,ADSRSliderWidth,ADSRSliderHeight);
    mSustainSlider.setBoundsRelative(ADSRStartX + (ADSRSliderWidth * 2),ADSRStartY,ADSRSliderWidth,ADSRSliderHeight);
    mReleaseSlider.setBoundsRelative(ADSRStartX + (ADSRSliderWidth * 3),ADSRStartY,ADSRSliderWidth,ADSRSliderHeight);

}
