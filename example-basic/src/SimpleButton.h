//
//  SimpleButton.h
//  example-basic
//
//  Created by David Haylock on 15/12/2015.
//
//

#pragma once 
#ifndef SimpleButton_h
#define SimpleButton_h

#include "ofMain.h"
//---------------------------------------------------
class SimpleButton : public ofRectangle {
public:
    //---------------------------------------------------
    SimpleButton(int x,int y,int w, int h,string name,ofColor c)
    {
        this->set(x,y,w,h);
        standardColor = c;
        buttonName = name;
        isActive = false;
        isOver = false;
    }
    //---------------------------------------------------
    ~SimpleButton() {}
    //---------------------------------------------------
    void setupButton(int x,int y,int w, int h,string name,ofColor c)
    {
        this->set(x,y,w,h);
        standardColor = c;
        buttonName = name;
    }
    //---------------------------------------------------
    void draw()
    {
        ofPushStyle();
        if (isOver) {
            ofSetColor(ofColor::ivory);
        }
        else if(isActive) {
            ofSetColor(ofColor::green);
        }
        else {
            ofSetColor(standardColor);
        }
        
        ofDrawRectangle(this->getStandardized());
        ofSetColor(ofColor::black);
        ofDrawBitmapString(buttonName,this->getLeft()-5,this->getBottom()+10);
        ofPopStyle();
    }
    //---------------------------------------------------
    void mouseOver(int x,int y)
    {
        if (inside(x,y)) {
            isOver = true;
        }
        else {
            isOver = false;
        }
    }
    //---------------------------------------------------
    void buttonPressed(int x,int y,int button)
    {
        if (inside(x,y)) {
            isActive = !isActive;
        }
    }
    
private:
    bool isActive = false;
    bool isOver = false;
    ofColor standardColor;
    string buttonName;
    
};
#endif /* SimpleButton_h */
