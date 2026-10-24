#include "PluginEditor.h"
#include "BinaryData.h"
RetroPluggAudioProcessorEditor::RetroPluggAudioProcessorEditor(RetroPluggAudioProcessor& p):juce::AudioProcessorEditor(&p),processor(p){
 artwork=juce::ImageCache::getFromMemory(BinaryData::RetroPlugg_png,BinaryData::RetroPlugg_pngSize);
 const struct {const char* name;int x,y;bool eq;} positions[]={
 {"saturation",133,411,false},{"bitcrush",366,411,false},{"noise",132,601,false},{"vinyl",366,601,false},
 {"delay",1117,340,false},{"delayMix",1432,317,false},{"reverb",1118,486,false},{"reverbMix",1432,463,false},
 {"chorus",1118,626,false},{"chorusMix",1432,609,false},{"tapeSat",912,767,false},{"wow",912,870,false},{"master",1150,827,false},
 {"eq60",108,816,true},{"eq120",156,816,true},{"eq250",202,816,true},{"eq500",249,816,true},{"eq1k",297,816,true},{"eq2k",344,816,true},{"eq4k",389,816,true},{"eq8k",434,816,true},{"eq16k",481,816,true}};
 for(auto& item:positions){
 auto s=std::make_unique<juce::Slider>();
 s->setSliderStyle(item.eq?juce::Slider::LinearVertical:juce::Slider::RotaryVerticalDrag);
 s->setTextBoxStyle(juce::Slider::NoTextBox,false,0,0);
 s->setColour(juce::Slider::thumbColourId,juce::Colours::orange);
 s->setColour(juce::Slider::rotarySliderFillColourId,juce::Colours::orange.withAlpha(.65f));
 int w=item.eq?24:92,h=item.eq?150:92;
 s->setBounds((int)((item.x-w/2)*.75),(int)((item.y-h/2)*.75),(int)(w*.75),(int)(h*.75));
 attachments.push_back(std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters,item.name,*s));
 addAndMakeVisible(*s);sliders.push_back(std::move(s));
 }
 setSize(1152,768);
}
void RetroPluggAudioProcessorEditor::paint(juce::Graphics& g){g.fillAll(juce::Colours::black);if(artwork.isValid())g.drawImage(artwork,getLocalBounds().toFloat());}
void RetroPluggAudioProcessorEditor::resized(){}
