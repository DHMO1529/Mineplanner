/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-11 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

#ifndef __JUCE_CHANNELREMAPPINGAUDIOSOURCE_JUCEHEADER__
#define __JUCE_CHANNELREMAPPINGAUDIOSOURCE_JUCEHEADER__

#include "juce_AudioSource.h"
#include "../../text/juce_XmlElement.h"
#include "../../containers/juce_Array.h"
#include "../../memory/juce_OptionalScopedPointer.h"


//==============================================================================
/**
    An AudioSource that takes the audio from another source, and re-maps its
    input and output channels to a different arrangement.

    You can use this to increase or decrease the number of channels that an
    audio source uses, or to re-order those channels.

    Call the reset() method before using it to set up a default mapping, and then
    the setInputChannelMapping() and setOutputChannelMapping() methods to
    create an appropriate mapping, otherwise no channels will be connected and
    it'll produce silence.

    @see AudioSource
*/
class ChannelRemappingAudioSource  : public AudioSource
{
public:
    //==============================================================================
    /** Creates a remapping source that will pass on audio from the given input.

        @param source       the input source to use. Make sure that this doesn't
                            get deleted before the ChannelRemappingAudioSource object
        @param deleteSourceWhenDeleted  if true, the input source will be deleted
                            when this object is deleted, if false, the caller is
                            responsible for its deletion
    */
    ChannelRemappingAudioSource (AudioSource* source,
                                 bool deleteSourceWhenDeleted);

    /** Destructor. */
    ~ChannelRemappingAudioSource();

    //==============================================================================
    /** Specifies a number of channels that this audio source must produce from its
        getNextAudioBlock() callback.
    */
    void setNumberOfChannelsToProduce (int requiredNumberOfChannels);

    /** Clears any mapped channels.

        After this, no channels are mapped, so this object will produce silence. Create
        some mappings with setInputChannelMapping() and setOutputChannelMapping().
    */
    void clearAllMappings();

    /** Creates an input channel mapping.

        When the getNextAudioBlock() method is called, the data in channel sourceChannelIndex of the incoming
        data will be sent to destChannelIndex of our input source.

        @param destChannelIndex     the index of an input channel in our input audio source (i.e. the
                                    source specified when this object was created).
        @param sourceChannelIndex   the index of the input channel in the incoming audio data buffer
                                    during our getNextAudioBlock() callback
    */
    void setInputChannelMapping (int destChannelIndex,
                                 int sourceChannelIndex);

    /** Creates an output channel mapping.

        When the getNextAudioBlock() method is called, the data returned in channel sourceChannelIndex by
        our input audio source will be copied to channel destChannelIndex of the final buffer.

        @param sourceChannelIndex   the index of an output channel coming from our input audio source
                                    (i.e. the source specified when this object was created).
        @param destChannelIndex     the index of the output channel in the incoming audio data buffer
                                    during our getNextAudioBlock() callback
    */
    void setOutputChannelMapping (int sourceChannelIndex,
                                  int destChannelIndex);

    /** Returns the channel from our input that will be sent to channel inputChannelIndex of
        our input audio source.
    */
    int getRemappedInputChannel (int inputChannelIndex) const;

    /** Returns the output channel to which channel outputChannelIndex of our input audio
        source will be sent to.
    */
    int getRemappedOutputChannel (int outputChannelIndex) const;


    //==============================================================================
    /** Returns an XML object to encapsulate the state of the mappings.

        @see restoreFromXml
    */
    XmlElement* createXml() const;

    /** Restores the mappings from an XML object created by createXML().

        @see createXml
    */
    void restoreFromXml (const XmlElement& e);

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate);
    void releaseResources();
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill);


private:
    //==============================================================================
    OptionalScopedPointer<AudioSource> source;
    Array <int> remappedInputs, remappedOutputs;
    int requiredNumberOfChannels;

    AudioSampleBuffer buffer;
    AudioSourceChannelInfo remappedInfo;

    CriticalSection lock;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelRemappingAudioSource);
};


#endif   // __JUCE_CHANNELREMAPPINGAUDIOSOURCE_JUCEHEADER__
