//--------------------------------------------------------------
//* Name: ofxCasioProjectorControl.cpp
//* Author: David Haylock, Stewart Morgan
//* Creation Date: 15-12-2015
//--------------------------------------------------------------
#include "ofxCasioProjectorControl.h"

//--------------------------------------------------------------
void ofxCasioProjectorControl::openProjectorConnection(string serialName,int baud)
{
    currentSerialName = serialName;
    currentBaud = baud;
    ofSerial::listDevices();
    ofSerial::setup(serialName, baud);
    ofSerial::flush();
    ofSerial::drain();
}
//--------------------------------------------------------------
void ofxCasioProjectorControl::closeConnection()
{
    ofSerial::flush();
    ofSerial::drain();
    ofSerial::close();
}
//--------------------------------------------------------------
void ofxCasioProjectorControl::reconnect() {
    if(ofSerial::isInitialized()) {
        cout << "Reconnecting to projector..." << endl;
        ofSerial::close();
        ofSerial::setup(currentSerialName, currentBaud);
        ofSerial::flush();
        ofSerial::drain();
    }
}
//--------------------------------------------------------------
bool ofxCasioProjectorControl::isConnected()
{
    return ofSerial::isInitialized();
}
//--------------------------------------------------------------
bool ofxCasioProjectorControl::doCommand(const char *command, unsigned int command_length, unsigned char *reply, unsigned int reply_size)
{
    bool            free_reply = false;
    bool            return_value = false;
    unsigned int    reply_length = 0;
    unsigned int    timeout = TIMEOUT_DURATION;
    
    if(reply == NULL && reply_size == 0) {
        free_reply = true;
        reply_size = 1024;
        reply = (unsigned char*)malloc(reply_size);
        memset(reply, 0, reply_size);
        
    } else if(reply_size == 0) {
        cout << "Projector reply buffer size cannot be zero!" << endl;
        return false;
        
    } else {
        free_reply = false;
        memset(reply, 0, reply_size);
    }
    
    // Drop off the trailing NULL
    command_length--;
    
    cout << "Sending " << command_length << " bytes to the projector: " << command << endl;
    ofSerial::writeBytes((unsigned char *)command, command_length);
    
    // Give the projector a quarter of a second to reply
    usleep(TIMEOUT_STEP_DURATION);
    
    while(timeout != 0) {
        switch(int byte = ofSerial::readByte()) {
                
            case OF_SERIAL_NO_DATA:
                cout << "Projector has no data; waiting (" << timeout << " retries remaining)..." << endl;
                timeout--;
                usleep(TIMEOUT_STEP_DURATION);
                continue;
                
            case OF_SERIAL_ERROR:
                cout << "Projector returned error" << endl;
                return false;
                
            case '\r':
                cout << "Projector replied: " << reply << endl;
                ofSerial::drain();
                return_value = (reply_length > 0) && (reply[0] == 'P');
                if(free_reply) {
                    free(reply);
                }
                return return_value;
                
            default:
                if(reply_length == reply_size) {
                    cout << "Read too much from the projector for the buffer!!" << endl;
                    return false;
                }
                
                //cout << "Projector sent: " << byte << " AKA " << (unsigned char)byte << endl;
                reply[ reply_length++ ] = (unsigned char)byte;
                break;
        }
    }
    
    cout << "Timed-out waiting for data from the projector!" << endl;
    if(free_reply) {
        free(reply);
    }
    return false;
}
//--------------------------------------------------------------
bool ofxCasioProjectorControl::setProjectorInput(int mode)
{
    switch(mode) {
        case 0:
            cout << "Projector Input is RGB1..." << endl;
            return doCommand(SET_INPUT_RGB_1, sizeof(SET_INPUT_RGB_1));
        case 1:
            cout << "Projector Input is Component 1..." << endl;
            return doCommand(SET_INPUT_COMPONENT_1, sizeof(SET_INPUT_COMPONENT_1));
        case 2:
            cout << "Projector Input is Video..." << endl;
            return doCommand(SET_INPUT_VIDEO, sizeof(SET_INPUT_VIDEO));
        case 3:
            cout << "Projector Input is RGB2..." << endl;
            return doCommand(SET_INPUT_RGB_2, sizeof(SET_INPUT_RGB_2));
        case 4:
            cout << "Projector Input is Component 2..." << endl;
            return doCommand(SET_INPUT_COMPONENT_2, sizeof(SET_INPUT_COMPONENT_2));
        case 6:
            cout << "Projector Input is Auto 1..." << endl;
            return doCommand(SET_INPUT_AUTO_1, sizeof(SET_INPUT_AUTO_1));
        case 7:
            cout << "Projector Input is HDMI..." << endl;
            return doCommand(SET_INPUT_HDMI, sizeof(SET_INPUT_HDMI));
        case 8:
            cout << "Projector Input is Network..." << endl;
            return doCommand(SET_INPUT_NETWORK, sizeof(SET_INPUT_NETWORK));
        case 9:
            cout << "Projector Input is Auto 2..." << endl;
            return doCommand(SET_INPUT_AUTO_2, sizeof(SET_INPUT_AUTO_2));
        case 10:
            cout << "Projector Input is File Manager..." << endl;
            return doCommand(SET_INPUT_FILE_VIEWER, sizeof(SET_INPUT_FILE_VIEWER));
        case 11:
            cout << "Projector Input is USB DISPLAY..." << endl;
            return doCommand(SET_INPUT_USB_DISPLAY, sizeof(SET_INPUT_USB_DISPLAY));
        case 12:
            cout << "Projector Input is Casio Usb..." << endl;
            return doCommand(SET_INPUT_CASIO_USB, sizeof(SET_INPUT_CASIO_USB));
        default:
            cout << "Unknown mode to project in!" << endl;
            return false;
    }
}
//--------------------------------------------------------------
bool ofxCasioProjectorControl::setProjectionMode(int mode)
{
    switch(mode) {
        case 0:
            cout << "Projecting in Front Mode..." << endl;
            return doCommand(MODE_FRONT, sizeof(MODE_FRONT));
            
        case 1:
            cout << "Projecting in Rear Mode..." << endl;
            return doCommand(MODE_REAR, sizeof(MODE_REAR));
            
        case 2:
            cout << "Projecting in Ceiling Mode..." << endl;
            return doCommand(MODE_FRONT_CEILING, sizeof(MODE_FRONT_CEILING));
            
        case 3:
            cout << "Projecting in Rear/Ceiling Mode..." << endl;
            return doCommand(MODE_REAR_CEILING, sizeof(MODE_REAR_CEILING));
            
        default:
            cout << "Unknown mode to project in!" << endl;
            return false;
    }
}
//--------------------------------------------------------------
bool ofxCasioProjectorControl::setProjectionAspect(int mode)
{
    switch(mode) {
        case 0:
            cout << "Projection is Normal.." << endl;
            return doCommand(SET_ASPECT_NORMAL, sizeof(SET_ASPECT_NORMAL));
        case 1:
            cout << "Projection is 16:9..." << endl;
            return doCommand(SET_ASPECT_16_9  , sizeof(SET_ASPECT_16_9 ));
        case 2:
            cout << "Projection is 4:3..." << endl;
            return doCommand(SET_ASPECT_4_3, sizeof(SET_ASPECT_4_3));
        case 3:
            cout << "Projection is Letterbox..." << endl;
            return doCommand(SET_ASPECT_LETTERBOX, sizeof(SET_ASPECT_LETTERBOX));
        case 4:
            cout << "Projection is Full..." << endl;
            return doCommand(SET_ASPECT_FULL, sizeof(SET_ASPECT_FULL));
        case 5:
            cout << "Projection is True..." << endl;
            return doCommand(SET_ASPECT_TRUE, sizeof(SET_ASPECT_TRUE));
        case 6:
            cout << "Projection is 4:3 Forced..." << endl;
            return doCommand(SET_ASPECT_4_3_FORCED, sizeof(SET_ASPECT_4_3_FORCED));
        default:
            cout << "Unknown Aspect!" << endl;
            return false;
    }
}
//--------------------------------------------------------------
bool ofxCasioProjectorControl::resetProjector()
{
    cout << "Projector is resetting..." << endl;
//    return doCommand(COMMAND_SYSTEM_RESET, sizeof(COMMAND_SYSTEM_RESET));
}

//--------------------------------------------------------------
bool ofxCasioProjectorControl::resyncProjector()
{
    cout << "Projector is resyncing..." << endl;
//    return doCommand(COMMAND_RESYNC, sizeof(COMMAND_RESYNC));
}

//--------------------------------------------------------------
bool ofxCasioProjectorControl::turnProjectorOn()
{
    cout << "Projector is Turning On..." << endl;
    return doCommand(POWER_ON, sizeof(POWER_ON));
}
//--------------------------------------------------------------
bool ofxCasioProjectorControl::turnProjectorOff()
{
    cout << "Projector is Turning Off..." << endl;
    return doCommand(POWER_OFF, sizeof(POWER_OFF));
}
//--------------------------------------------------------------
string ofxCasioProjectorControl::getProjectorStatus()
{
//    cout << "Getting System Status..." << endl;
//    unsigned char reply[1024];
//    if(doCommand(COMMAND_SYSTEM_STATUS, sizeof(COMMAND_SYSTEM_STATUS), reply, sizeof(reply))) {
//        return ofToString(reply);
//    }
//    return "";
}
//--------------------------------------------------------------
int ofxCasioProjectorControl::getLampHours()
{
    cout << "Getting lmap-hours..." << endl;
    unsigned char reply[1024];
    if(doCommand(GET_LAMP_HOURS, sizeof(GET_LAMP_HOURS), reply, sizeof(reply))) {
        return (int)std::strtol((const char *)(reply + 1), (char **)NULL, 10);
    }
    return -1;
}