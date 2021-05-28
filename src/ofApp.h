#pragma once

#include "ofMain.h"
#include "ofxPhyllotaxis.h"
#include "ofxPanel.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void drawText();
    void typeKey(int key);

    int nCubes = 400;
    bool hideGui = false;
    ofFloatColor masterColor;
    ofFloatColor secondColor;
    ofMaterial secondMaterial;
    ofEasyCam camera;
    ofLight light;
    vector<ofBoxPrimitive> children;
    string selectedType = "conical";

    ofxPanel gui;
    ofxFloatSlider degree;
    ofxFloatSlider spread;
    ofxFloatSlider extrude;
    
    float degreeFloat;
    float degreeChange;
    
    float spreadFloat;
    float spreadChange;
    
    float extrudeFloat;
    float extrudeChange;
    
    int terminalState = 0;
    int heatState = 0;
    
    
    ofColor heat1;
    ofColor heat2;
    ofColor heat3;
    
    int msgIf;
    
    //terminal
    string text;
    string textCursor;
    string command;
    int position;
    ofTrueTypeFont myFont;
    ofRectangle tw;
    int textWidth;
    //terminal
    
    unsigned long time, timer;
    unsigned int timeDelay;
};
