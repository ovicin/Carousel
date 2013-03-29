/**
 * LFO example
 * ofxTimeline
 *
 * simple example for low frequency oscillator track
 */

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
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
	timeline.togglePlay();

	relayShield.setup();
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

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

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
