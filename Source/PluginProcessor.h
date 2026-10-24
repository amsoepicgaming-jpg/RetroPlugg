#pragma once
#include <JuceHeader.h>
class RetroPluggAudioProcessor : public juce::AudioProcessor {
public:
 RetroPluggAudioProcessor();
 void prepareToPlay(double,int) override;
 void releaseResources() override {}
 bool isBusesLayoutSupported(const BusesLayout& l) const override;
 void processBlock(juce::AudioBuffer<float>&,juce::MidiBuffer&) override;
 juce::AudioProcessorEditor* createEditor() override;
 bool hasEditor() const override {return true;}
 const juce::String getName() const override{return "RetroPlugg";}
 bool acceptsMidi() const override{return false;}
 bool producesMidi() const override{return false;}
 double getTailLengthSeconds() const override{return 2.0;}
 int getNumPrograms() override{return 1;}
 int getCurrentProgram() override{return 0;}
 void setCurrentProgram(int) override{}
 const juce::String getProgramName(int) override{return "Default";}
 void changeProgramName(int,const juce::String&) override{}
 void getStateInformation(juce::MemoryBlock&) override;
 void setStateInformation(const void*,int) override;
 static juce::AudioProcessorValueTreeState::ParameterLayout createLayout();
 juce::AudioProcessorValueTreeState parameters;
private:
 juce::AudioBuffer<float> echo;
 int writePosition=0;
 juce::Random random;
};