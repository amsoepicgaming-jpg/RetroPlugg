#pragma once
#include "PluginProcessor.h"
class RetroPluggAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
 explicit RetroPluggAudioProcessorEditor(RetroPluggAudioProcessor&);
 void paint(juce::Graphics&) override;
 void resized() override;
private:
 RetroPluggAudioProcessor& processor;
 juce::Image artwork;
 std::vector<std::unique_ptr<juce::Slider>> sliders;
 std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> attachments;
};