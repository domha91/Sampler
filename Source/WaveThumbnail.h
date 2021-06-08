/*
  ==============================================================================

    WaveThumbnail.h
    Created: 10 May 2021 8:55:09am
    Author:  domha91

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class WaveThumbnail  : public juce::Component,
                       public juce::FileDragAndDropTarget  
{
public:
    WaveThumbnail (SamplerAudioProcessor& p);
    ~WaveThumbnail() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void buttonPressed();
    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped( const StringArray& files, int x, int y) override;
    

private:

    //Add Load Button
    TextButton mLoadButton {"Load"};
    //Add vector to display sample waveform 
    std::vector<float> mAudioPoints;
    

    SamplerAudioProcessor& audioProcessor;

    String mFileName{""};

    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveThumbnail)
};
