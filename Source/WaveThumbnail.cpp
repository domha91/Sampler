/*
  ==============================================================================

    WaveThumbnail.cpp
    Created: 10 May 2021 8:55:09am
    Author:  domha91

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveThumbnail.h"


//==============================================================================
WaveThumbnail::WaveThumbnail(SamplerAudioProcessor& p) : audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    //Set up functionality of load button and make waveform visible
    mLoadButton.onClick = [&](){  buttonPressed(); };
    addAndMakeVisible(mLoadButton);

    
}

WaveThumbnail::~WaveThumbnail()
{
}

void WaveThumbnail::paint (juce::Graphics& g)
{
    g.fillAll(Colours::cadetblue.darker());

    mLoadButton.setBounds(0, getHeight()/3 + 50,50,50);
    auto waveform = audioProcessor.getWaveForm();
    
    if(waveform.getNumSamples() > 0)
    {
        Path p;
        mAudioPoints.clear();
    
        auto ratio = waveform.getNumSamples()/getWidth();
        auto buffer = waveform.getReadPointer(0);
        //Scale on X axis
        for (int sample = 0; sample < waveform.getNumSamples(); sample+=ratio)
        {
            mAudioPoints.push_back(buffer[sample]);
        }
        g.setColour(Colours::white);
        p.startNewSubPath(0,getHeight()/2);

        //Scale on Y axis
        for (int sample = 0; sample < mAudioPoints.size(); ++sample)
        {
            auto point = jmap<float>(mAudioPoints[sample],-1.0f, 1.0f, getHeight(), 0);
            // Set path as waveform
            p.lineTo(sample,point);
        }
        // Paint waveform path
        g.strokePath(p, PathStrokeType(2));

        
        g.setFont(15.0f);

        auto textBounds = getLocalBounds().reduced(10,10);
        g.drawFittedText(mFileName,textBounds, Justification::topRight, 1);

        auto playHeadPosition = jmap<int>(audioProcessor.getSampleCount(), 0, audioProcessor.getWaveForm().getNumSamples(),0,getWidth());

        g.setColour(Colours::white);
        g.drawLine(playHeadPosition, 0, playHeadPosition,getHeight(), 2.0f);

        g.setColour(Colours::black.withAlpha(0.2f));
        g.fillRect(0, 0, playHeadPosition, getHeight());
    }
    else 
    {
        g.setColour(Colours::white);
        g.setFont(40.f);
        g.drawFittedText("Drop an audio file to load", getLocalBounds(), Justification::centred, 1);
    }
}

void WaveThumbnail::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}


// Determine whether the file is an audio file
bool WaveThumbnail::isInterestedInFileDrag(const StringArray& files)
{
    for (auto file : files){
      if (file.contains (".wav") || file.contains (".mp3") || file.contains (".aif")){
          return true;
      }
    }
    
    return false;
}

//Drag & Drop functionality
//Doesn't work in Reaper.
void WaveThumbnail::filesDropped(const StringArray& files, int x, int y){

    for (auto file : files){
      if (isInterestedInFileDrag(file))
      {
          auto myFile = std::make_unique<File> (file);

          mFileName = myFile->getFileNameWithoutExtension();
          // Load this file
          audioProcessor.loadFile(file);
      }
    }
    repaint();
}

void WaveThumbnail::buttonPressed()
{

    if(audioProcessor.loadFileDialog())
    {
        repaint();
    }
   
}
