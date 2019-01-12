#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
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
		

        int sampleRate;
        int bufferSize;
        int numChannels;
        void audioOut(float * output, int bufferSize, int nChannels);
        //ofSoundStream soundStream;

        maxiOsc oscillator;
        maxiOsc oscillator2;
        maxiOsc oscillator3;
        maxiOsc oscillator4;

        maxiEnv envelope;
        float freq;
        int trigger;

        // for drawing
        float waveform[4096]; //make this bigger, just in case
        int waveIndex;


        // octave visualiser
        ofTrueTypeFont f0;
        octave oct_2;
        octave oct_1;
        octave oct0;
        octave oct1;
        octave oct2;
        octave oct3;
        octave oct4;

        std::vector<string> notes;
        std::vector<int> noteTrigR;

        float hue;
        ofColor c;
        float o; // variable for controlling the octave

};
