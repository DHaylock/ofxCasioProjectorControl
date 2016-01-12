#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    vector<string> operations;
    operations.push_back("Power On");
    operations.push_back("Power Off");
    
    operations.push_back("Get Lamp Life");
    operations.push_back("Blank Screen On");
    operations.push_back("Blank Screen Off");
    
    for (int i = 0; i < operations.size(); i++) {
        operationButtons.push_back(SimpleButton(10,10+i*70,50,50,operations[i],ofColor::blueSteel));
    }
    
    
//    button1.setupButton(10, 10, 50, 50,"test",ofColor::blueSteel);
}
//--------------------------------------------------------------
void ofApp::update()
{

}
//--------------------------------------------------------------
void ofApp::draw()
{
    for (auto button : operationButtons) {
        button.draw();
    }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

}
//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
    for (int i = 0; i < operationButtons.size(); i++) {
        operationButtons[i].mouseOver(x, y);
    }
}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    for (int i = 0; i < operationButtons.size(); i++) {
        operationButtons[i].buttonPressed(x, y, button);
    }
}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}
//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{

}
//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
    
}
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}