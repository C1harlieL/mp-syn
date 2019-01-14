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
    o = 3;
    f0.load("arial.ttf", 12);

    // soundstream setup
    ofSoundStreamSetup(2,0,this, sampleRate, bufferSize, 4);

    // note names
    notes = {"A", "Bb", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
    //noteTrigR = oct1.getNoteTrigs();


    // attempted maths to calculate all the semitone's frequencies in HZ
    // but was inaccurate so used precalculated values found online and
    // stored them in the a vector
    // set lowest f
    //    float low = 27.500;
    //    noteFreq.push_back(low);
    //    for(int i = 0; i < 84; i ++){
    //        low*= 1.041666667;
    //        noteFreq.push_back(low);
    //        std::cout << low << std::endl;
    //    }
    // frequencies A0 to A6
    noteFreq = {27.50,29.14,30.87,32.70,34.65,36.71,38.89,41.20,43.65,46.25,49.00,51.91,55.00,58.27,61.74,65.41  ,69.30  ,73.42  ,77.78  ,82.41  ,87.31  ,92.50  ,98.00  ,103.83 ,110.00 ,116.54 ,123.47 ,130.81 ,138.59 ,146.83 ,155.56 ,164.81 ,174.61 ,185.00 ,196.00 ,207.65 ,220.00 ,233.08 ,246.94 ,261.63 ,277.18 ,293.66 ,311.13 ,329.63 ,349.23 ,369.99 ,392.00 ,415.30 ,440.00 ,466.16 ,493.88 ,523.25 ,554.37 ,587.33 ,622.25 ,659.26 ,698.46 ,739.99 ,783.99 ,830.61 ,880.00 ,932.33 ,987.77 ,1046.50,1108.73,1174.66,1244.51,1318.51,1396.91,1479.98,1567.98,1661.22,1760.00,1864.66,1975.53,2093.00,2217.46,2349.32,2489.02,2637.02,2793.83,2959.96,3135.96,3322.44};

    std::cout << noteFreq.size() << std::endl;
    // create 7 octaves
    for(int i = 0; i < 7; i ++){
        octave _oct;
        octaves.push_back(_oct);
    }
    std::cout << octaves.size() << std::endl;

    // asdr controllers
    gui.setup();
    gui.add(attackSlide.setup("attack", 10, 5, 1000));
    gui.add(decaySlide.setup("decay", 1000, 10, 2000));
    gui.add(sustainSlide.setup("sustain", 0.5, 0.1, 2.0));
    gui.add(releaseSlide.setup("release", 500, 10, 2000));

}

//--------------------------------------------------------------
void ofApp::update(){

    // set envelope parameters
    envelope.setAttack(attackSlide);
    envelope.setDecay(decaySlide);
    envelope.setRelease(releaseSlide);
    envelope.setSustain(sustainSlide);

    // Map the hue of the colour to the same range
    // as the frequency and set this value to colour
    // c
//    hue = ofMap(freq, 170, 350, 0, 255);
//    c.setHsb(hue, 255, 255);

    // update method of octave visual
    for(int i = 0; i < octaves.size(); i ++){
        octaves[i].update();
    }


}

//--------------------------------------------------------------
void ofApp::draw(){
    // background
    ofPushMatrix();
    ofBackgroundGradient(ofColor(0), ofColor(200));
    // move stuff to the center
    ofTranslate(200, 200);
    // Draw the octaves and back section
    ofSetColor(150);
    ofDrawRectangle(40, 0, 480, 320);
    ofPushMatrix();
    for(int i = 0; i < octaves.size(); i ++){
        octaves[i].draw(40, 40 + i*40);
    }
    ofPopMatrix();

    // Set the colour to the mapped hue value
    // and draw ellipse of that colour
    // ofTranslate(0, ofGetHeight()/2);
    // ofSetColor(c);
    // ofDrawEllipse(ofGetWidth()/2., 0, 100, 100);

    //    Draw wave form of the sound
    //    ofFill();
    //    int oldX = 0;
    //    int oldY = 0;
    //    for(int i = 0; i < ofGetWidth(); ++i) {
    //        ofDrawLine(oldX, oldY, i, waveform[i] * ofGetHeight()/2.);
    //        oldX = i;
    //        oldY = waveform[i] * ofGetHeight()/2.;
    //    }

    // draw the note names
    ofSetColor(0);
    for (int i = 0; i < notes.size(); i ++ ){
        f0.drawString(notes[i], 50 + i * 40, 20);
    }
    ofPopMatrix();

    gui.draw();

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
    // are for A through to G#
    // (a full octave)
    if(key==97){

//        std::cout << "dlsjfl" << std::endl;
        if(o==0){
            freq = noteFreq[0];
            trigger = 1;
            octaves[0].trigger(0);
        } else if(o==1){
            freq = noteFreq[12];
            trigger = 1;
            octaves[1].trigger(0);
        } else if(o==2){
            freq = noteFreq[24];
            trigger = 1;
            octaves[2].trigger(0);
        } else if(o==3){
            freq = noteFreq[36];
            trigger = 1;
            octaves[3].trigger(0);
        } else if(o==4){
            freq = noteFreq[48];
            trigger = 1;
            octaves[4].trigger(0);
        } else if(o==5){
            freq = noteFreq[60];
            trigger = 1;
            octaves[5].trigger(0);
        } else if(o=6){
            freq = noteFreq[72];
            trigger = 1;
            octaves[6].trigger(0);
        }
    }
    if(key==115){
        if(o==0){
            freq = noteFreq[1];
            trigger = 1;
            octaves[0].trigger(1);
        } else if(o==1){
            freq = noteFreq[13];
            trigger = 1;
            octaves[1].trigger(1);
        } else if(o==2){
            freq = noteFreq[25];
            trigger = 1;
            octaves[2].trigger(1);
        } else if(o==3){
            freq = noteFreq[37];
            trigger = 1;
            octaves[3].trigger(1);
        } else if(o==4){
            freq = noteFreq[49];
            trigger = 1;
            octaves[4].trigger(1);
        } else if(o==5){
            freq = noteFreq[61];
            trigger = 1;
            octaves[5].trigger(1);
        } else if(o=6){
            freq = noteFreq[73];
            trigger = 1;
            octaves[6].trigger(1);
        }
    }
    if(key==100){
        if(o==0){
            freq = noteFreq[2];
            trigger = 1;
            octaves[0].trigger(2);
        } else if(o==1){
            freq = noteFreq[14];
            trigger = 1;
            octaves[1].trigger(2);
        } else if(o==2){
            freq = noteFreq[26];
            trigger = 1;
            octaves[2].trigger(2);
        } else if(o==3){
            freq = noteFreq[38];
            trigger = 1;
            octaves[3].trigger(2);
        } else if(o==4){
            freq = noteFreq[50];
            trigger = 1;
            octaves[4].trigger(2);
        } else if(o==5){
            freq = noteFreq[62];
            trigger = 1;
            octaves[5].trigger(2);
        } else if(o=6){
            freq = noteFreq[74];
            trigger = 1;
            octaves[6].trigger(2);
        }

    }
    if(key==102){
        if(o==0){
            freq = noteFreq[3];
            trigger = 1;
            octaves[0].trigger(3);
        } else if(o==1){
            freq = noteFreq[15];
            trigger = 1;
            octaves[1].trigger(3);
        } else if(o==2){
            freq = noteFreq[27];
            trigger = 1;
            octaves[2].trigger(3);
        } else if(o==3){
            freq = noteFreq[39];
            trigger = 1;
            octaves[3].trigger(3);
        } else if(o==4){
            freq = noteFreq[51];
            trigger = 1;
            octaves[4].trigger(3);
        } else if(o==5){
            freq = noteFreq[63];
            trigger = 1;
            octaves[5].trigger(3);
        } else if(o=6){
            freq = noteFreq[75];
            trigger = 1;
            octaves[6].trigger(3);
        }
    }
    if(key==103){
        if(o==0){
            freq = noteFreq[4];
            trigger = 1;
            octaves[0].trigger(4);
        } else if(o==1){
            freq = noteFreq[16];
            trigger = 1;
            octaves[1].trigger(4);
        } else if(o==2){
            freq = noteFreq[28];
            trigger = 1;
            octaves[2].trigger(4);
        } else if(o==3){
            freq = noteFreq[40];
            trigger = 1;
            octaves[3].trigger(4);
        } else if(o==4){
            freq = noteFreq[52];
            trigger = 1;
            octaves[4].trigger(4);
        } else if(o==5){
            freq = noteFreq[64];
            trigger = 1;
            octaves[5].trigger(4);
        } else if(o=6){
            freq = noteFreq[76];
            trigger = 1;
            octaves[6].trigger(4);
        }
    }
    if(key==104){
        if(o==0){
            freq = noteFreq[5];
            trigger = 1;
            octaves[0].trigger(5);
        } else if(o==1){
            freq = noteFreq[17];
            trigger = 1;
            octaves[1].trigger(5);
        } else if(o==2){
            freq = noteFreq[29];
            trigger = 1;
            octaves[2].trigger(5);
        } else if(o==3){
            freq = noteFreq[41];
            trigger = 1;
            octaves[3].trigger(5);
        } else if(o==4){
            freq = noteFreq[53];
            trigger = 1;
            octaves[4].trigger(5);
        } else if(o==5){
            freq = noteFreq[65];
            trigger = 1;
            octaves[5].trigger(5);
        } else if(o=6){
            freq = noteFreq[77];
            trigger = 1;
            octaves[6].trigger(5);
        }
    }
    if(key==106){
        if(o==0){
            freq = noteFreq[6];
            trigger = 1;
            octaves[0].trigger(6);
        } else if(o==1){
            freq = noteFreq[18];
            trigger = 1;
            octaves[1].trigger(6);
        } else if(o==2){
            freq = noteFreq[30];
            trigger = 1;
            octaves[2].trigger(6);
        } else if(o==3){
            freq = noteFreq[42];
            trigger = 1;
            octaves[3].trigger(6);
        } else if(o==4){
            freq = noteFreq[54];
            trigger = 1;
            octaves[4].trigger(6);
        } else if(o==5){
            freq = noteFreq[66];
            trigger = 1;
            octaves[5].trigger(6);
        } else if(o=6){
            freq = noteFreq[78];
            trigger = 1;
            octaves[6].trigger(6);
        }
    }
    if(key==107){
        if(o==0){
            freq = noteFreq[7];
            trigger = 1;
            octaves[0].trigger(7);
        } else if(o==1){
            freq = noteFreq[19];
            trigger = 1;
            octaves[1].trigger(7);
        } else if(o==2){
            freq = noteFreq[31];
            trigger = 1;
            octaves[2].trigger(7);
        } else if(o==3){
            freq = noteFreq[43];
            trigger = 1;
            octaves[3].trigger(7);
        } else if(o==4){
            freq = noteFreq[55];
            trigger = 1;
            octaves[4].trigger(7);
        } else if(o==5){
            freq = noteFreq[67];
            trigger = 1;
            octaves[5].trigger(7);
        } else if(o=6){
            freq = noteFreq[79];
            trigger = 1;
            octaves[6].trigger(7);
        }
    }
    if(key==108){
        if(o==0){
            freq = noteFreq[8];
            trigger = 1;
            octaves[0].trigger(8);
        } else if(o==1){
            freq = noteFreq[20];
            trigger = 1;
            octaves[1].trigger(8);
        } else if(o==2){
            freq = noteFreq[32];
            trigger = 1;
            octaves[2].trigger(8);
        } else if(o==3){
            freq = noteFreq[44];
            trigger = 1;
            octaves[3].trigger(8);
        } else if(o==4){
            freq = noteFreq[56];
            trigger = 1;
            octaves[4].trigger(8);
        } else if(o==5){
            freq = noteFreq[68];
            trigger = 1;
            octaves[5].trigger(8);
        } else if(o=6){
            freq = noteFreq[80];
            trigger = 1;
            octaves[6].trigger(8);
        }
    }
    if(key==59){
        if(o==0){
            freq = noteFreq[9];
            trigger = 1;
            octaves[0].trigger(9);
        } else if(o==1){
            freq = noteFreq[21];
            trigger = 1;
            octaves[1].trigger(9);
        } else if(o==2){
            freq = noteFreq[33];
            trigger = 1;
            octaves[2].trigger(9);
        } else if(o==3){
            freq = noteFreq[45];
            trigger = 1;
            octaves[3].trigger(9);
        } else if(o==4){
            freq = noteFreq[57];
            trigger = 1;
            octaves[4].trigger(9);
        } else if(o==5){
            freq = noteFreq[69];
            trigger = 1;
            octaves[5].trigger(9);
        } else if(o=6){
            freq = noteFreq[81];
            trigger = 1;
            octaves[6].trigger(9);
        }
    }

    if(key==39){
        if(o==0){
            freq = noteFreq[10];
            trigger = 1;
            octaves[0].trigger(10);
        } else if(o==1){
            freq = noteFreq[22];
            trigger = 1;
            octaves[1].trigger(10);
        } else if(o==2){
            freq = noteFreq[34];
            trigger = 1;
            octaves[2].trigger(10);
        } else if(o==3){
            freq = noteFreq[46];
            trigger = 1;
            octaves[3].trigger(10);
        } else if(o==4){
            freq = noteFreq[58];
            trigger = 1;
            octaves[4].trigger(10);
        } else if(o==5){
            freq = noteFreq[70];
            trigger = 1;
            octaves[5].trigger(10);
        } else if(o=6){
            freq = noteFreq[82];
            trigger = 1;
            octaves[6].trigger(10);
        }
    }
    if(key==35){
        if(o==0){
            freq = noteFreq[11];
            trigger = 1;
            octaves[0].trigger(11);
        } else if(o==1){
            freq = noteFreq[23];
            trigger = 1;
            octaves[1].trigger(11);
        } else if(o==2){
            freq = noteFreq[35];
            trigger = 1;
            octaves[2].trigger(11);
        } else if(o==3){
            freq = noteFreq[47];
            trigger = 1;
            octaves[3].trigger(11);
        } else if(o==4){
            freq = noteFreq[59];
            trigger = 1;
            octaves[4].trigger(11);
        } else if(o==5){
            freq = noteFreq[71];
            trigger = 1;
            octaves[5].trigger(11);
        } else if(o=6){
            freq = noteFreq[83];
            trigger = 1;
            octaves[6].trigger(11);
        }
    }


    ////////////


    if(key==46){
        o+=1;
    }
    if(key==44){
        o-=1;
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

    trigger = 1;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    trigger = 0;
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

