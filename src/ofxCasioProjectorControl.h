//--------------------------------------------------------------
//* Name: ofxCasioProjectorControl.h
//* Author: David Haylock, Stewart Morgan
//* Creation Date: 15-12-2015
//--------------------------------------------------------------
#include "ofMain.h"
#include <stdlib.h>

#define TIMEOUT_STEP_DURATION      250000   // In uSeconds
#define TIMEOUT_DURATION           20       // In iterations of TIMEOUT_STEP_DURATION, 20 ~5s
#define NUM_BYTES 1
#define BAUD 19200

#define POWER_ON                "PWR1\r"
#define POWER_OFF               "PWR0\r"

#define SET_INPUT_RGB_1         "SRC0\r"
#define SET_INPUT_COMPONENT_1   "SRC1\r"
#define SET_INPUT_VIDEO         "SRC2\r"
#define SET_INPUT_RGB_2          "SRC3\r"
#define SET_INPUT_COMPONENT_2   "SRC4\r"
#define SET_INPUT_AUTO_1        "SRC6\r"
#define SET_INPUT_HDMI          "SRC7\r"
#define SET_INPUT_NETWORK       "SRC8\r"
#define SET_INPUT_S_VIDEO       "SRC9\r"
#define SET_INPUT_AUTO_2        "SRC10\r"
#define SET_INPUT_FILE_VIEWER   "SRC11\r"
#define SET_INPUT_USB_DISPLAY   "SRC12\r"
#define SET_INPUT_CASIO_USB     "SRC13\r"

#define SET_BLANK_SCREEN_OFF    "BLK0\r"
#define SET_BLANK_SCREEN_ON     "BLK1\r"

#define SET_COLOR_MODE_1        "PST1\r"
#define SET_COLOR_MODE_2        "PST2\r"
#define SET_COLOR_MODE_3        "PST3\r"
#define SET_COLOR_MODE_4        "PST4\r"
#define SET_COLOR_MODE_5        "PST5\r"

#define SET_ASPECT_NORMAL       "ARZ0\r"
#define SET_ASPECT_16_9         "ARZ1\r"
#define SET_ASPECT_4_3          "ARZ2\r"
#define SET_ASPECT_LETTERBOX    "ARZ3\r"
#define SET_ASPECT_FULL         "ARZ4\r"
#define SET_ASPECT_TRUE         "ARZ5\r"
#define SET_ASPECT_4_3_FORCED   "ARZ6\r"

#define GET_LAMP_HOURS          "LMP\r"

#define SET_FREEZE_ON           "FRZ1\r"
#define SET_FREEZE_OFF          "FRZ2\r"

#define MODE_FRONT              "POS0\r"
#define MODE_REAR               "POS1\r"
#define MODE_FRONT_CEILING      "POS2\r"
#define MODE_REAR_CEILING       "POS3\r"

#define SET_BLANK_SCREEN_OFF    "BLK0\r"
#define SET_BLANK_SCREEN_ON     "BLK1\r"

#define GET_ERROR_MESSAGE       "STS\r"

//--------------------------------------------------------------
class ofxCasioProjectorControl : public ofSerial {
public:
    void openProjectorConnection(string serialName,int baud = BAUD);
    void closeConnection();
    
    bool isConnected();
    void reconnect();

    bool doCommand(const char *command, unsigned int command_length, unsigned char *reply = NULL, unsigned int reply_size = 0);
    
    bool resyncProjector();
    bool resetProjector();
    bool turnProjectorOn();
    bool turnProjectorOff();
    bool setProjectionMode(int mode);
    bool setProjectionAspect(int mode);
    bool setProjectorInput(int mode);
    
    string getProjectorStatus();
    int getLampHours();
    
protected:
    unsigned char returnValue;
    unsigned char	bytesReturned[NUM_BYTES];
    string  messageBuffer;
    string message;
    
private:
    string currentSerialName;
    int currentBaud;
};