#pragma once

#include "ofMain.h"
#include "ofxPostProcessing.h"
#include "ofxMidi.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp{

	public:
    ofxOscSender sender;
    ofxOscMessage m;

    ofxPostProcessing post;
    ofxMidiOut midiOut;
    int note, velocity;

    long double play;
    long double timeBandit;
    int size_factor;
    int channel;
    long double time;
    float scale;
    float seed1;
    float seed2;
    float seed3;
    float color;

		void setup();
		void update();
		void draw();
    void hex(int x, float y);
};
