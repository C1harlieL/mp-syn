#ifndef OCTAVE_H
#define OCTAVE_H
#include <vector>

class octave
{
public:
    octave();
    ~octave();
    void draw(float, float);
    void triggered();
    void trigger(int);
    void update();
    std::vector<int> getNoteTrigs();

    float size;
    float dotSize;
    int index;
    float timer;
    float noteHue;
    std::vector<int> noteTrig;

};

#endif // OCTAVE_H
