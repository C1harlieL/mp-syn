#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //ofBackground(0,0,0);


    sampleRate = 44100; /* Sampling Rate */
    bufferSize= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    numChannels = 2;

    trigger = 0;
    freq = 220;



    // initiliaze draw variablesz
    for (int i = 0; i < ofGetWidth(); ++i) {
        waveform[i] = 0;
    }
    waveIndex = 0;
    c = ofColor(0);
    o = 1;
    f0.load("arial.ttf", 12);

    // soundstream setup
    ofSoundStreamSetup(2,0,this, sampleRate, bufferSize, 4);

    //oscillator2.square(200);

    notes = {"F", "F#", "G", "G#", "A", "Bb", "B", "C", "C#", "D", "D#", "E"};
    noteTrigR = oct1.getNoteTrigs();


}

//--------------------------------------------------------------
void ofApp::update(){

    // set envelope parameters
    envelope.setAttack(10);
    envelope.setDecay(1000);
    envelope.setRelease(2000);
    envelope.setSustain(0.5);

    // Map the hue of the colour to the same range
    // as the frequency and set this value to colour
    // c
    hue = ofMap(freq, 170, 350, 0, 255);
    c.setHsb(hue, 255, 255);

    // update method of oct1ave visual
    oct_2.update();
    oct_1.update();
    oct0.update();
    oct1.update();
    oct2.update();
    oct3.update();
    oct4.update();


}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(0), ofColor(200));

    // Draw the oct1ave
    ofPushMatrix();
    oct_2.draw(40, 40);
    oct_1.draw(40, 80);
    oct0.draw(40, 120);
    oct1.draw(40, 160);
    oct2.draw(40, 200);
    oct3.draw(40, 240);
    oct4.draw(40, 280);
    ofPopMatrix();

    // Set the colour to the mapped hue value
    // and draw ellipse of that colour
    // ofTranslate(0, ofGetHeight()/2);
    ofSetColor(c);
    //ofDrawEllipse(ofGetWidth()/2., 0, 100, 100);

//    Draw wave form of the sound
//    ofFill();
//    int oldX = 0;
//    int oldY = 0;
//    for(int i = 0; i < ofGetWidth(); ++i) {
//        ofDrawLine(oldX, oldY, i, waveform[i] * ofGetHeight()/2.);
//        oldX = i;
//        oldY = waveform[i] * ofGetHeight()/2.;
//    }

    ofSetColor(0);
    for (int i = 0; i < notes.size(); i ++ ){
        f0.drawString(notes[i], 50 + i * 40, 20);
    }

}

//--------------------------------------------------------------

void ofApp::audioOut(float * output, int bufferSize, int nChannels){
    for(int i = 0; i < bufferSize; i ++){
        //  oscillator
        double sound = oscillator.sinewave(freq*2);
        float oscOutput = envelope.adsr(sound, trigger);

        //std::cout << oscOutput << std::endl;
        //std::cout << output[10] << std::endl;

        output[i * numChannels]  = oscOutput * 0.3;
        output[i * numChannels + 1] = oscOutput * 0.3;

        // use audio ouput numbers to draw
        waveform[waveIndex] =  output[i * nChannels];
        ++waveIndex;
        if (waveIndex > (ofGetWidth() - 1))
            waveIndex = 0;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(key==32){
        freq = 440;
        trigger = 1;
    }

    // keys a s d f g h j k l ; ' #
    // are for f through to e
    // (a full oct1ave)
    if(key==97){
        freq = 174.61 * o;
        trigger = 1;

        if(o==0.125){
            oct_2.trigger(0);
        } else if(o==0.25){
            oct_1.trigger(0);
        } else if(o==0.5){
            oct0.trigger(0);
        } else if(o==1){
            oct1.trigger(0);
        } else if(o==2){
            oct2.trigger(0);
        } else if(o==4){
            oct3.trigger(0);
        } else if(o=8){
            oct4.trigger(0);
        }
    }
    if(key==115){
        freq = 185.0 * o;
        trigger = 1;

        if(o==0.125){
            oct_2.trigger(1);
        } else if(o==0.25){
            oct_1.trigger(1);
        } else if(o==0.5){
            oct0.trigger(1);
        } else if(o==1){
            oct1.trigger(1);
        } else if(o==2){
            oct2.trigger(1);
        } else if(o==4){
            oct3.trigger(1);
        } else if(o=8){
            oct4.trigger(1);
        }
    }
    if(key==100){
        freq = 196.0 * o;
        trigger = 1;

        if(o==0.125){
            oct_2.trigger(2);
        } else if(o==0.25){
            oct_1.trigger(2);
        } else if(o==0.5){
            oct0.trigger(2);
        } else if(o==1){
            oct1.trigger(2);
        } else if(o==2){
            oct2.trigger(2);
        } else if(o==4){
            oct3.trigger(2);
        } else if(o=8){
            oct4.trigger(2);
        }
    }
    if(key==102){
        freq = 207.65 * o;
        trigger = 1;

        if(o==0.125){
            oct_2.trigger(3);
        } else if(o==0.25){
            oct_1.trigger(3);
        } else if(o==0.5){
            oct0.trigger(3);
        } else if(o==1){
            oct1.trigger(3);
        } else if(o==2){
            oct2.trigger(3);
        } else if(o==4){
            oct3.trigger(3);
        } else if(o=8){
            oct4.trigger(3);
        }
    }
    if(key==103){
        freq = 220 * o;
        trigger = 1;

        if(o==0.125){
            oct_2.trigger(4);
        } else if(o==0.25){
            oct_1.trigger(4);
        } else if(o==0.5){
            oct0.trigger(4);
        } else if(o==1){
            oct1.trigger(4);
        } else if(o==2){
            oct2.trigger(4);
        } else if(o==4){
            oct3.trigger(4);
        } else if(o=8){
            oct4.trigger(4);
        }
    }
    if(key==104){
        freq = 233.08 * o;
        trigger = 1;

        if(o==0.125){
            oct_2.trigger(5);
        } else if(o==0.25){
            oct_1.trigger(5);
        } else if(o==0.5){
            oct0.trigger(5);
        } else if(o==1){
            oct1.trigger(5);
        } else if(o==2){
            oct2.trigger(5);
        } else if(o==4){
            oct3.trigger(5);
        } else if(o=8){
            oct4.trigger(5);
        }
    }
    if(key==106){
        freq = 246.94 * o;
        trigger = 1;

        if(o==0.125){
            oct_2.trigger(6);
        } else if(o==0.25){
            oct_1.trigger(6);
        } else if(o==0.5){
            oct0.trigger(6);
        } else if(o==1){
            oct1.trigger(6);
        } else if(o==2){
            oct2.trigger(6);
        } else if(o==4){
            oct3.trigger(6);
        } else if(o=8){
            oct4.trigger(6);
        }
    }
    if(key==107){
        freq = 261.63 * o;
        trigger = 1;

        if(o==0.125){
            oct_2.trigger(7);
        } else if(o==0.25){
            oct_1.trigger(7);
        } else if(o==0.5){
            oct0.trigger(7);
        } else if(o==1){
            oct1.trigger(7);
        } else if(o==2){
            oct2.trigger(7);
        } else if(o==4){
            oct3.trigger(7);
        } else if(o=8){
            oct4.trigger(7);
        }
    }
    if(key==108){
        freq = 277.18 * o;
        trigger = 1;

        if(o==0.125){
            oct_2.trigger(8);
        } else if(o==0.25){
            oct_1.trigger(8);
        } else if(o==0.5){
            oct0.trigger(8);
        } else if(o==1){
            oct1.trigger(8);
        } else if(o==2){
            oct2.trigger(8);
        } else if(o==4){
            oct3.trigger(8);
        } else if(o=8){
            oct4.trigger(8);
        }
    }
    if(key==59){
        freq = 293.67 * o;
        trigger = 1;

        if(o==0.125){
            oct_2.trigger(9);
        } else if(o==0.25){
            oct_1.trigger(9);
        } else if(o==0.5){
            oct0.trigger(9);
        } else if(o==1){
            oct1.trigger(9);
        } else if(o==2){
            oct2.trigger(9);
        } else if(o==4){
            oct3.trigger(9);
        } else if(o=8){
            oct4.trigger(9);
        }
    }
    if(key==39){
        freq = 311.13 * o;
        trigger = 1;

        if(o==0.125){
            oct_2.trigger(10);
        } else if(o==0.25){
            oct_1.trigger(10);
        } else if(o==0.5){
            oct0.trigger(10);
        } else if(o==1){
            oct1.trigger(10);
        } else if(o==2){
            oct2.trigger(10);
        } else if(o==4){
            oct3.trigger(10);
        } else if(o=8){
            oct4.trigger(10);
        }
    }
    if(key==35){
        freq = 329.63 * o;
        trigger = 1;

        if(o==0.125){
            oct_2.trigger(11);
        } else if(o==0.25){
            oct_1.trigger(11);
        } else if(o==0.5){
            oct0.trigger(11);
        } else if(o==1){
            oct1.trigger(11);
        } else if(o==2){
            oct2.trigger(11);
        } else if(o==4){
            oct3.trigger(11);
        } else if(o=8){
            oct4.trigger(11);
        }
    }

    //std::cout << key << std::endl;

    if(key==46){
        o*=2;
    }
    if(key==44){
        o/=2;
    }

}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){
//    if(key==32 || key==99 || 9){
//        trigger = 0;
//    }

    trigger = 0;

}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


///////////////////////////////////
//    // key is a
//    if(key==97){
//        freq = 220; // a3 frequency
//        trigger = 1;
//        std::cout << "a" << std::endl;
//    }
//    // key is b
//    if(key==98){
//        freq = 246.96; // b3 frequency
//        trigger = 1;
//        std::cout << "b" << std::endl;
//    }
//    // key is c
//    if(key==99){
//        freq = 261.63; // c4 frequency
//        trigger = 1;
//        std::cout << "c" << std::endl;
//    }
//    // key is d
//    if(key==100){
//        freq = 293.67; // d4 frequency
//        trigger = 1;
//        std::cout << "d" << std::endl;
//    }
//    // key is e
//    if(key==101){
//        freq = 329.63; // e4 frequency
//        trigger = 1;
//        std::cout << "e" << std::endl;
//    }
//    // key is f
//    if(key==102){
//        freq = 349.23; // f4 frequency
//        trigger = 1;
//        std::cout << "f" << std::endl;
//    }
//    // key is g
//    if(key==103){
//        freq = 392.0; // g4 frequency
//        trigger = 1;
//        std::cout << "g" << std::endl;
//    }
//    // key is r
//    if(key==114){
//        freq = ofRandom(0, 800);
//        trigger = 1;
//    }
////////////////////////////////////
