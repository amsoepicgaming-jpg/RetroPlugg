#include "PluginEditor.h"

RetroPluggAudioProcessorEditor::RetroPluggAudioProcessorEditor(RetroPluggAudioProcessor& p):juce::AudioProcessorEditor(&p),processor(p){
 
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
void RetroPluggAudioProcessorEditor::paint(juce::Graphics& g){g.fillAll(juce::Colour(0xff181616));g.setColour(juce::Colours::orange);g.setFont(36.f);g.drawText("RETROPLUGG",20,12,500,56,juce::Justification::centredLeft);g.setColour(juce::Colours::silver);g.setFont(18.f);g.drawText("Temporary UI — reference artwork awaiting upload",25,70,950,36,juce::Justification::centredLeft);if(artwork.isValid())g.drawImage(artwork,getLocalBounds().toFloat());}
void RetroPluggAudioProcessorEditor::resized(){}
