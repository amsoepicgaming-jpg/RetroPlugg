#include "PluginProcessor.h"
#include "PluginEditor.h"
RetroPluggAudioProcessor::RetroPluggAudioProcessor():AudioProcessor(BusesProperties().withInput("Input",juce::AudioChannelSet::stereo(),true).withOutput("Output",juce::AudioChannelSet::stereo(),true)),parameters(*this,nullptr,"Parameters",createLayout()){}
juce::AudioProcessorValueTreeState::ParameterLayout RetroPluggAudioProcessor::createLayout(){
 juce::AudioProcessorValueTreeState::ParameterLayout l;
 for (auto id: {"saturation","bitcrush","noise","vinyl","delay","delayMix","reverb","reverbMix","chorus","chorusMix","tapeSat","wow","master"}) l.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{id,1},id,juce::NormalisableRange<float>(0.f,1.f),id==std::string("master")?0.8f:0.f));
 for (auto id: {"eq60","eq120","eq250","eq500","eq1k","eq2k","eq4k","eq8k","eq16k"}) l.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{id,1},id,juce::NormalisableRange<float>(-12.f,12.f),0.f));
 return l;
}
bool RetroPluggAudioProcessor::isBusesLayoutSupported(const BusesLayout& l) const {return l.getMainInputChannelSet()==juce::AudioChannelSet::stereo() && l.getMainOutputChannelSet()==juce::AudioChannelSet::stereo();}
void RetroPluggAudioProcessor::prepareToPlay(double sr,int){echo.setSize(2,(int)(sr*2)+1);echo.clear();writePosition=0;}
void RetroPluggAudioProcessor::processBlock(juce::AudioBuffer<float>& b,juce::MidiBuffer&){
 juce::ScopedNoDenormals guard;
 auto value=[this](const char* id){return parameters.getRawParameterValue(id)->load();};
 int n=echo.getNumSamples();if(n<1)return;
 for(int i=0;i<b.getNumSamples();++i){
  for(int c=0;c<juce::jmin(2,b.getNumChannels());++c){
   float x=b.getSample(c,i);
   float drive=1.f+value("saturation")*15.f+value("tapeSat")*6.f;
   x=std::tanh(x*drive)/std::tanh(drive);
   float crush=value("bitcrush");if(crush>0.001f){float levels=std::pow(2.f,16.f-crush*12.f);x=std::round(x*levels)/levels;}
   x+=(random.nextFloat()*2.f-1.f)*value("noise")*0.035f;
   if(random.nextFloat()<value("vinyl")*0.002f)x+=(random.nextFloat()*2.f-1.f)*0.2f;
   int lag=(int)(getSampleRate()*(0.08+value("delay")*0.6));lag=juce::jlimit(1,n-1,lag);
   int read=(writePosition-lag+n)%n;
   float delayed=echo.getSample(c,read);
   echo.setSample(c,writePosition,x+delayed*0.38f);
   x+=delayed*value("delayMix")*0.6f;
   b.setSample(c,i,juce::jlimit(-1.f,1.f,x*value("master")*1.2f));
  }
  writePosition=(writePosition+1)%n;
 }
}
juce::AudioProcessorEditor* RetroPluggAudioProcessor::createEditor(){return new RetroPluggAudioProcessorEditor(*this);}
void RetroPluggAudioProcessor::getStateInformation(juce::MemoryBlock& b){if(auto xml=parameters.copyState().createXml())copyXmlToBinary(*xml,b);}
void RetroPluggAudioProcessor::setStateInformation(const void* data,int size){if(auto xml=getXmlFromBinary(data,size))if(xml->hasTagName(parameters.state.getType()))parameters.replaceState(juce::ValueTree::fromXml(*xml));}
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter(){return new RetroPluggAudioProcessor();}
