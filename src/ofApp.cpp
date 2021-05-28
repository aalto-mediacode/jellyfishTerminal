#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    timeDelay = 4500;
    //camera.setPosition(0, 100, 1000); //507.126, 500.178, 80.3209
    heat1.r=50;
    heat1.g=200;
    heat1.b=0;
    
    heat2.r=100;
    heat2.g=150;
    heat2.b=0;
    
    heat3.r=150;
    heat3.g=100;
    heat3.b=0;
    //terminal
    myFont.load("pixel.ttf", 14);
    textCursor="_";
    text="";
    position=0;
    //terminal
    degreeFloat = 130;
    degreeChange = 0.00001;
    spreadFloat = 11;
    spreadChange = 0.001;
    extrudeFloat = 0.01;
    extrudeChange = 0.0008;
    gui.setup();
    gui.setPosition(5, 40);
    gui.add(degree.setup("degree", degreeFloat, 130.00, 140.00));
    gui.add(spread.setup("spread", spreadFloat, 2, 40));
    gui.add(extrude.setup("extrude", extrudeFloat, 0.01, 0.90));
    light.setup();
    light.setPosition(-100, 200,0);
    masterColor = ofFloatColor::green;
    secondColor = ofFloatColor::floralWhite;
    ofEnableDepthTest();
    for(int i = 0;  i < nCubes;i++){
        children.push_back(ofBoxPrimitive(5,5,5));
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    //terminal
    ofRectangle tw = myFont.getStringBoundingBox(text, 0,0);
    textWidth = tw.width;
    //terminal
    msgIf = ofStringTimesInString(text, "msg");
    float rad = ofDegToRad(degree);
    for (int i = 0;  i < nCubes;i++) {
        glm::vec3 pos;
        if (selectedType == "simple") {
            pos = ofxPhyllotaxis::simple(i, rad, spread);
        }

        if (selectedType == "conical") {
            pos = ofxPhyllotaxis::conical(i, rad, spread, extrude);
        }

        if (selectedType == "apple") {
            pos = ofxPhyllotaxis::apple(i, rad, spread, nCubes);
        }
        if (selectedType == "test") {
            pos = ofxPhyllotaxis::test(i, rad, spread, nCubes);
        }
        children[i].setPosition(pos);
    }
    /* this code makes smooth rotation, floats are defined above in ofApp::setup
    cout << degreeFloat << endl;
    degree.setup(degreeFloat);
    degreeFloat += degreeChange;

    if ((degreeFloat <= 130 && degreeChange < 0) || (degreeFloat >=140 && degreeChange > 0))
        degreeChange = - degreeChange; // reverse direction of motion.
     */
    
    if(terminalState == 1){
        
        
        extrude.setup(extrudeFloat);
        extrudeFloat += extrudeChange;

        if((extrudeFloat <= 0.01 && extrudeChange < 0) || (extrudeFloat >=0.15 && extrudeChange > 0)){
            extrudeChange = - extrudeChange; // reverse direction of motion.
        }
        degreeChange = 0.00001;
        degree.setup(degreeFloat);
        degreeFloat += degreeChange;

        if ((degreeFloat <= 130 && degreeChange < 0) || (degreeFloat >=130.3 && degreeChange > 0)){
            degreeChange = - degreeChange; // reverse direction of motion.
        }
    }
    
    if(terminalState == 3){
        spread.setup(spreadFloat);
        spreadFloat += spreadChange;

        if((spreadFloat <= 1 && spreadChange < 0) || (spreadFloat >=80 && spreadChange > 0)){
            spreadChange = - spreadChange; // reverse direction of motion.
        }
    }
    
    cout << extrudeFloat << endl;
    cout << heatState << endl;
    cout << extrudeChange << endl;
    
    if(heatState<0){
        masterColor = ofFloatColor::skyBlue;
        secondColor = ofFloatColor::floralWhite;
    }
    
    if(heatState==0){
        masterColor = heat1;
        secondColor = ofFloatColor::floralWhite;
        if(extrudeChange>0){
        extrudeChange = 0.0008;
        }
        if(extrudeChange<0){
        extrudeChange = -0.0008;
        }
    }

    if(heatState==1){
        masterColor = heat1;
        secondColor = ofFloatColor::floralWhite;
        if(extrudeChange>0){
        extrudeChange = 0.0005;
        }
        if(extrudeChange<0){
        extrudeChange = -0.0005;
        }
    }
    
    if(heatState==2){
        masterColor = heat2;
        secondColor = ofFloatColor::floralWhite;
        if(extrudeChange>0){
        extrudeChange = 0.0003;
        }
        if(extrudeChange<0){
        extrudeChange = -0.0003;
        }
        
    }
    
    if(heatState>=3){
        masterColor = heat3;
        secondColor = ofFloatColor::floralWhite;
        if(extrudeChange>0){
        extrudeChange = 0.0001;
        }
        if(extrudeChange<0){
        extrudeChange = -0.0001;
        }
        
    }
    
    if(terminalState==4){
        // first get the actual time each cycle
        time = ofGetElapsedTimeMillis();

        // check if enough time has passed after your trigger:
        // actualTime is higher each cycle. successTimer is only changed, when triggered.
        // so deviation of the two is 0, the moment sucessTimer is triggered and then growing
        // if succesTimeDelta is reached 2000, 2 seconds have passed.
        if (time - timer > timeDelay) {
            heatState=heatState+5;
            terminalState=1;
            selectedType="conical";
            degreeFloat = 130;
            degreeChange = 0.001;
            spreadFloat = 11;
            spreadChange = 0.001;
            extrudeFloat = 0.1;
            extrudeChange = 0.0008;
            degree.setup(degreeFloat);
            spread.setup(spreadFloat);
            extrude.setup(extrudeFloat);
        }
        
        
    
    
    
}

}

//--------------------------------------------------------------
void ofApp::draw(){
    //maybeDrawGui();
    if(terminalState!=0){
        camera.begin();

        secondMaterial.setEmissiveColor(masterColor);
        for (int i = 0;  i < nCubes;i++) {
            float lerp = ofMap(i, 0, nCubes, 0.0, 1.0);
            auto interpolatedColor = masterColor.getLerped(secondColor, lerp);
            secondMaterial.setEmissiveColor(interpolatedColor);
            secondMaterial.begin();
            children[i].draw();
            secondMaterial.end();
        }
        camera.end();
    }
    //terminal
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(255); //color is affected by the light!
    drawText();
    myFont.drawString(command, 50, ofGetHeight()-70);
    ofPopStyle();
    ofPopMatrix();
    //terminal
}

void ofApp::drawText() {
    myFont.drawString(text, 50,ofGetHeight()-50);
    
    ofPushStyle();
    float timeFrac = 255.0f * sin(3.0f * ofGetElapsedTimef()*5);
    ofSetColor(timeFrac,timeFrac,timeFrac);
    myFont.drawString(textCursor,50+textWidth+1,ofGetHeight()-50);
    ofPopStyle();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    typeKey(key);
    
}

void ofApp::typeKey(int key) {
    //add character
    if (key >=32 && key <=126) {
        text.insert(text.begin()+position, key);
        position++;
    }
    
    
    if (key==OF_KEY_BACKSPACE) {
        if (position>0) {
            text.erase(text.begin()+position-1);
            --position;
        }
    }
    
    if (key==OF_KEY_DEL) {
        if (text.size() > position) {
            text.erase(text.begin()+position);
        }
    }
    
    if (key==OF_KEY_LEFT)
        if (position>0)
            --position;
    
    if (key==OF_KEY_RIGHT)
        if (position<text.size()+1)
            ++position;
    
    if (key==OF_KEY_RETURN) {
        if (text=="close") {
            terminalState=0;
            degreeFloat = 130;
            degreeChange = 0.001;
            spreadFloat = 11;
            spreadChange = 0.001;
            extrudeFloat = 0.1;
            extrudeChange = 0.0008;
            degree.setup(degreeFloat);
            spread.setup(spreadFloat);
            extrude.setup(extrudeFloat);
        }
        if (text=="run jellyfish") {
            terminalState=1;
            selectedType="conical";
            degreeFloat = 130;
            degreeChange = 0.001;
            spreadFloat = 11;
            spreadChange = 0.001;
            extrudeFloat = 0.1;
            extrudeChange = 0.0008;
            degree.setup(degreeFloat);
            spread.setup(spreadFloat);
            extrude.setup(extrudeFloat);
        }
        if (text=="cam main") {
            terminalState=1;
            selectedType="conical";
            degreeFloat = 130;
            degreeChange = 0.001;
            spreadFloat = 11;
            spreadChange = 0.001;
            extrudeFloat = 0.1;
            extrudeChange = 0.0008;
            degree.setup(degreeFloat);
            spread.setup(spreadFloat);
            extrude.setup(extrudeFloat);
        }
        if (text=="2") {
            terminalState=2;
            selectedType="apple";
            degreeFloat = 130;
            degreeChange = 0.001;
            spreadFloat = 11;
            spreadChange = 0.001;
            extrudeFloat = 0.1;
            extrudeChange = 0.0008;
            degree.setup(degreeFloat);
            spread.setup(spreadFloat);
            extrude.setup(extrudeFloat);
        }
        if (text=="cam microscope") {
            terminalState=3;
            selectedType="simple";
            degreeFloat = 130;
            degreeChange = 0.001;
            spreadFloat = 80;
            spreadChange = 0.3;
            extrudeFloat = 0.1;
            extrudeChange = 0.0008;
            degree.setup(degreeFloat);
            spread.setup(spreadFloat);
            extrude.setup(extrudeFloat);
        }
        if (msgIf>=1 && heatState != 3) {
            heatState=heatState-5;
            timer= ofGetElapsedTimeMillis();
            terminalState=4;
            selectedType="test";
            degreeFloat = 130;
            degreeChange = 0.001;
            spreadFloat = 11;
            spreadChange = 0.001;
            extrudeFloat = 0.1;
            extrudeChange = 0.0008;
            degree.setup(degreeFloat);
            spread.setup(spreadFloat);
            extrude.setup(extrudeFloat);
        }

        if (text=="e") {
           //children.erase(children.begin()+ofRandom(children.size())); //erases but leaves a bigger white box with axis lines in its place
            children.clear();
            
            
        }
        if (text=="temp +" && heatState<3) {
            heatState++;
            text="temp "+ofToString(heatState);
            
            
        }
        if (text=="temp -" && heatState>0) {
            heatState--;
            text="temp "+ofToString(heatState);
            
            
        }
        command=text;
        text="";
        position=0;
        
    }
    
    
}

