/**
 * LFO example
 * ofxTimeline
 *
 * simple example for low frequency oscillator track
 */

#pragma once

#include "ofMain.h"
#include "ofxTimeline.h"
#include "ofxTLLFO.h"
#include "ofxTimer.h"
#include "ofxDfRobotRelayShield.h"
#include "ofxUI.h"
#include "ofxTimer.h"
#include "NanoKontrol2.h"

#define SLIDE_SHOW_TIMER 4000

#define GUI_WIDTH 500
#define GUI_HEIGHT 200

class testApp : public ofBaseApp{

  public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	void bangFired(ofxTLBangEventArgs& args);
	void MoveForward(void);
	void MoveBackward(void);

	void pollNanoKontrol(void);
	ofxTimeline timeline;
	ofxTimer SlideshowTimer;

	ofxDfRobotRelayShield relayShield;
	ofxUICanvas *RelaySheildGui, *TimelineControlGui;
	bool mouseDown;
	vector<ofxTimeline*> sublines;
	void exit(); 
	void guiEvent(ofxUIEventArgs &e);
	void AdvanceSlideShow(void);
	bool SlideShowOn;
	NanoKontrol2 kontrol;

};
