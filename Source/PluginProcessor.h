/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


// MTS-ESP Support
// #include <libMTSClient.h>
// #include <libMTSClient.cpp>

//==============================================================================
/**
*/
class SamplerAudioProcessor  : public juce::AudioProcessor,
                               public juce::ValueTree::Listener
{
public:
    //==============================================================================
    SamplerAudioProcessor();
    ~SamplerAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    bool loadFileDialog();
    void loadFile(const String& path);

    int getNumSamplerSounds(){return mSampler.getNumSounds();}
    AudioBuffer<float>& getWaveForm() { return mWaveForm;}

    void updateADSR();
    ADSR::Parameters& getADSRParams(){return mADSRParams;};
    AudioProcessorValueTreeState& getAPVTS() {return mAPVTS;}
    std::atomic<bool>& isNotePlayed() {return mIsNotePlayed;}
    std::atomic<int>& getSampleCount() {return mSampleCount;}


private:
    // Add sampler
    Synthesiser mSampler;
    // Number of Sampler voices
    const int mNumVoices{3};
    // Add audio buffer
    AudioBuffer<float> mWaveForm;

    ADSR::Parameters mADSRParams;

    AudioFormatManager mFormatManager;
    AudioFormatReader* mFormatReader {nullptr};
    
    AudioProcessorValueTreeState mAPVTS;
    AudioProcessorValueTreeState::ParameterLayout createParameters();
    void valueTreePropertyChanged(ValueTree& treeWhosPropertyHasChanged, const Identifier& property) override;

    std::atomic<bool> mShouldUpdate {false};
    std::atomic<bool> mIsNotePlayed {false};
    // Number of samples that have already been played
    std::atomic<int> mSampleCount {0};

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplerAudioProcessor)
};
