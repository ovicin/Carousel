/**
 * LFO example
 * ofxTimeline
 *
 * simple example for low frequency oscillator track
 */

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	mouseDown = false;

	ofBackground(255*.15);
	ofSetFrameRate(30);
	ofSetVerticalSync(true);
	
	ofEnableSmoothing();
	ofEnableAlphaBlending();

	//on mac lets you use COMMAND+C and COMMAND+V actions
	ofxTimeline::removeCocoaMenusFromGlut("Empty Templates");
	
	timeline.setup();
	timeline.setLoopType(OF_LOOP_NORMAL);
	timeline.setDurationInSeconds(30);
    
	//this is the simplest example and is really flexible
	//timeline.addLFO("LFO");
	//timeline.addSwitches("Switches");
	//timeline.addBangs("Slides","timeline0_bangs.xml");
	timeline.addFlags("Slides","timeline0_bangs.xml");
	ofAddListener(timeline.events().bangFired, this, &testApp::bangFired);


	relayShield.setup();
	RelaySheildGui = new ofxUICanvas(GUI_WIDTH + 10,ofGetHeight()-GUI_HEIGHT,GUI_WIDTH,GUI_HEIGHT);
	ofColor color;
	RelaySheildGui->setColorBack(color.darkKhaki);
	RelaySheildGui->addWidgetDown(new ofxUIToggle(16, 16, false, "FULLSCREEN"));
    RelaySheildGui->addWidgetDown(new ofxUILabel("DfRobotRelayShieldControl", OFX_UI_FONT_LARGE)); 

    RelaySheildGui->addWidgetDown(new ofxUIButton(16, 16, false, "Relay1Pulse"));
	RelaySheildGui->addWidgetRight(new ofxUIButton(16, 16, false, "Relay2Pulse"));
	RelaySheildGui->addWidgetRight(new ofxUIButton(16, 16, false, "Relay3Pulse"));
	RelaySheildGui->addWidgetRight(new ofxUIButton(16, 16, false, "Relay4Pulse"));

	ofAddListener(RelaySheildGui->newGUIEvent, this, &testApp::guiEvent);

	TimelineControlGui = new ofxUICanvas(0,ofGetHeight()-GUI_HEIGHT,GUI_WIDTH,GUI_HEIGHT);
	TimelineControlGui->setColorBack(color.darkKhaki);
	TimelineControlGui->addWidgetDown(new ofxUILabel("Timeline Control", OFX_UI_FONT_LARGE)); 
	TimelineControlGui->addWidgetDown(new ofxUIButton(16, 16, false, "Start"));
	TimelineControlGui->addWidgetRight(new ofxUIButton(16, 16, false, "Pause"));
	TimelineControlGui->addWidgetRight(new ofxUIButton(16, 16, false, "Stop"));

	ofAddListener(TimelineControlGui->newGUIEvent, this, &testApp::guiEvent);
}

//--------------------------------------------------------------
void testApp::bangFired(ofxTLBangEventArgs& bang){
	cout << "bang fired!" << bang.flag << endl;
	if (bang.flag == "forward")
	{
		cout << "Moving forward" << endl;
		MoveForward();
	}
	if (bang.flag == "backward")
	{
		cout << "Moving backward" << endl;
		MoveBackward();
	}
		
}



//-------------------------------------------------------------
void testApp::MoveForward(){
	relayShield.PulseRelay1();
		
}



//-------------------------------------------------------------
void testApp::MoveBackward(){
	relayShield.PulseRelay2();
		
}

//-------------------------------------------------------------
void testApp::update(){

		
}

//--------------------------------------------------------------
void testApp::draw(){

	timeline.draw();
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key == '1'){
		relayShield.PulseRelay1();
	} else if (key == '2'){
			relayShield.PulseRelay2();
	} else if (key == '3'){
			relayShield.PulseRelay3();
	} else if (key == '4'){
			relayShield.PulseRelay4();
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	mouseDown = true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	mouseDown = false;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

void testApp::exit()
{
    //gui->saveSettings("GUI/guiSettings.xml"); 
    delete RelaySheildGui; 
}

//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{	
	if(e.widget->getName() == "FULLSCREEN")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        ofSetFullscreen(toggle->getValue());   
    }
	else if(e.widget->getName() == "Relay1Pulse")
    {
		if (mouseDown) relayShield.PulseRelay1();
    }
	else if(e.widget->getName() == "Relay2Pulse")
    {
		if (mouseDown)relayShield.PulseRelay2();
    }
	else if(e.widget->getName() == "Relay3Pulse")
    {
		if (mouseDown)relayShield.PulseRelay3();
    }
	else if(e.widget->getName() == "Relay4Pulse")
    {
		if (mouseDown)relayShield.PulseRelay4();
    }
	else if(e.widget->getName() == "Start")
    {
		if (mouseDown)timeline.play();
    }
	else if(e.widget->getName() == "Pause")
    {
		if (mouseDown)timeline.togglePlay();
    }
	else if(e.widget->getName() == "Stop")
    {
		if (mouseDown){
			timeline.stop();
			timeline.setCurrentFrame(0);
		}
    }
}
