#include "octave.h"
#include "ofMain.h"

octave::octave()
{
    size = 480;
    index = 0;
    dotSize = 3;
    timer = 0;
    noteTrig = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    noteHue = 0;
}
octave::~octave(){}

void octave::draw(float x, float y)
{
    ofPushMatrix();
    ofSetColor(100);
    ofTranslate(x, y);
    ofDrawRectangle(0, 0, size, 40);
    ofSetColor(0);

    for(int i = 0; i < 12; i++){
        noteHue = ofMap(i, 0, 12, 0, 255);
        ofColor color1;
        color1.setHsb(noteHue, 255, 230);
        ofSetColor(color1);
        ofDrawEllipse(i*(size/12) + (size/24), 20, noteTrig[i]/100 + 3, noteTrig[i]/100 + 3);
    }
    ofPopMatrix();

}

void octave::update(){
    this->triggered();
}

std::vector<int> octave::getNoteTrigs(){
    return noteTrig;
}

void octave::triggered(){
    for(int i = 0; i < noteTrig.size(); i++){
        if(noteTrig[i] > 0){
            noteTrig[i] -= 10;
        }
    }
}

void octave::trigger(int note){
    noteTrig[note] = 1000;
}
