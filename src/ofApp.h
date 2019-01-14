#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxGui.h"
#include "octave.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
		
        // sound setup
        int sampleRate;
        int bufferSize;
        int numChannels;
        void audioOut(float * output, int bufferSize, int nChannels);
        //ofSoundStream soundStream;
        // main oscillator
        maxiOsc oscillator;
        // others
        maxiOsc oscillator2;
        maxiOsc oscillator3;
        maxiOsc oscillator4;
        // envelope object
        maxiEnv envelope;
        // frequency and trigger
        float freq;
        int trigger;

        // for drawing
        float waveform[4096]; //make this bigger, just in case
        int waveIndex;


        // octave visualiser
        ofTrueTypeFont f0;
        std::vector<string> notes;
        std::vector<octave> octaves;
        std::vector<float> noteFreq;
        std::vector<int> noteTrigR;
        float hue;
        ofColor c;
        int o; // variable for controlling the octave

        // GUI sliders
        ofxPanel gui;
        ofxIntSlider attackSlide;
        ofxIntSlider decaySlide;
        ofxIntSlider releaseSlide;
        ofxFloatSlider sustainSlide;


};
