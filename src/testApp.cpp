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

	posturas.setup();
	//on mac lets you use COMMAND+C and COMMAND+V actions
	ofxTimeline::removeCocoaMenusFromGlut("Empty Templates");
	
	timeline.setup();
	timeline.setLoopType(OF_LOOP_NORMAL);
	timeline.setDurationInSeconds(1000);

	//for(int i = 0; i < 5; i++){
	// add audio locura index 0
        ofxTimeline* t = new ofxTimeline();
		//t->setup();
		//t->setBPM(120.f);
		//t->setShowBPMGrid(false);
		//t->addAudioTrack("Audio Locura","flamenquitoylocuracorto-001.wav");
		//t->setTimecontrolTrack("Audio Locura");
        //t->setSpacebarTogglePlay(false);
        //t->setDurationInSeconds(t->getAudioTrack("Audio Locura")->getDuration());
        //t->setLoopType(OF_LOOP_NORMAL);
        //sublines.push_back(t);
		//delete t;

    // add audio slideshow index 1
	    t = new ofxTimeline();
		t->setup();
		t->setBPM(120.f);
		t->setShowBPMGrid(false);
		t->addAudioTrack("Audio Slideshow","satiex2.wav");
		t->setTimecontrolTrack("Audio Slideshow");
        t->setSpacebarTogglePlay(false);
        t->setDurationInSeconds(t->getAudioTrack("Audio Slideshow")->getDuration());
        t->setLoopType(OF_LOOP_NORMAL);
        sublines.push_back(t);
		//delete t;
	    
	//add audio slideshow index 2
		t = new ofxTimeline();
		t->setup();
		t->setBPM(120.f);
		t->setShowBPMGrid(false);
		t->addAudioTrack("Audio Colador","satiex1.wav");
		t->setTimecontrolTrack("Audio Colador");
        t->setSpacebarTogglePlay(false);
        t->setDurationInSeconds(t->getAudioTrack("Audio Colador")->getDuration());
        t->setLoopType(OF_LOOP_NORMAL);
        sublines.push_back(t);
		//delete t;
	
    timeline.addFlags("1.SeqColadorProjector1","timeline1_colador.xml");
	timeline.addFlags("2.ContraTiempoProjector1","timeline1_contratiempo.xml");
	timeline.addFlags("2.ContraTiempoProjector2","timeline2_contratiempo.xml");
	//timeline.addFlags("3.BlancoProjector2","timeline2_blanco.xml");
	//timeline.addFlags("3.BlancoProjector2","timeline_xls.xml");
	//timeline.addFlags("5.MicroSeccionesLampara","timeline_edl.xml");
	//timeline.addFlags("6.Azar","timeline_azar.xml");
	//timeline.addFlags("6.Azar","timeline_edl.xml");
	ofAddListener(timeline.events().bangFired, this, &testApp::bangFired);


	relayShield.setup();
	RelaySheildGui = new ofxUICanvas(GUI_WIDTH + 10,550,GUI_WIDTH,GUI_HEIGHT);
	ofColor color;
	RelaySheildGui->setColorBack(color.darkKhaki);
	RelaySheildGui->addWidgetDown(new ofxUIToggle(16, 16, false, "FULLSCREEN"));
    RelaySheildGui->addWidgetDown(new ofxUILabel("RelayControl", OFX_UI_FONT_LARGE)); 

    RelaySheildGui->addWidgetDown(new ofxUIButton(16, 16, false, "Relay1Pulse"));
	RelaySheildGui->addWidgetRight(new ofxUIButton(16, 16, false, "Relay2Pulse"));
	RelaySheildGui->addWidgetRight(new ofxUIButton(16, 16, false, "Relay3Pulse"));
	RelaySheildGui->addWidgetDown(new ofxUIToggle(16, 16, false, "Light"));
	RelaySheildGui->addWidgetRight(new ofxUIToggle(16, 16, false, "Projector1"));
	RelaySheildGui->addWidgetRight(new ofxUIToggle(16, 16, false, "Projector2"));
	RelaySheildGui->addWidgetDown(new ofxUIToggle(16, 16, false, "SlideShowOn"));
	//RelaySheildGui->addWidgetRight(new ofxUIButton(16, 16, false, "Relay4Pulse"));

	RelaySheildGui->addWidgetDown(new ofxUIToggle(16, 16, false, "DisableRelays"));


	ofAddListener(RelaySheildGui->newGUIEvent, this, &testApp::guiEvent);

	TimelineControlGui = new ofxUICanvas(0,550,GUI_WIDTH,GUI_HEIGHT);
	TimelineControlGui->setColorBack(color.darkKhaki);
	TimelineControlGui->addWidgetDown(new ofxUILabel("Timeline Control", OFX_UI_FONT_LARGE)); 
	TimelineControlGui->addWidgetDown(new ofxUIButton(16, 16, false, "Start"));
	TimelineControlGui->addWidgetRight(new ofxUIButton(16, 16, false, "Pause"));
	TimelineControlGui->addWidgetRight(new ofxUIButton(16, 16, false, "Stop"));
	TimelineControlGui->addWidgetDown(new ofxUIButton(16, 16, false, "AudioLocuraStart"));
	TimelineControlGui->addWidgetRight(new ofxUIButton(16, 16, false, "AudioLocuraPause"));
	TimelineControlGui->addWidgetRight(new ofxUIButton(16, 16, false, "AudioLocuraStop"));
	TimelineControlGui->addWidgetDown(new ofxUIButton(16, 16, false, "AudioSlideshowStart"));
	TimelineControlGui->addWidgetRight(new ofxUIButton(16, 16, false, "AudioSlideshowPause"));
	TimelineControlGui->addWidgetRight(new ofxUIButton(16, 16, false, "AudioSlideshowStop"));
	TimelineControlGui->addWidgetDown(new ofxUIButton(16, 16, false, "AudioColadorStart"));
	TimelineControlGui->addWidgetRight(new ofxUIButton(16, 16, false, "AudioColadorPause"));
	TimelineControlGui->addWidgetRight(new ofxUIButton(16, 16, false, "AudioColadorStop"));

	ofAddListener(TimelineControlGui->newGUIEvent, this, &testApp::guiEvent);

	SlideshowTimer.setup(SLIDE_SHOW_TIMER,false);
	SlideShowOn = false;


		// open an outgoing connection to HOST:PORT
	sender1.setup( HOST, PORT );

	

}

void testApp::senOSCEvent(){
		ofxOscMessage m;
		m.setAddress( "/movie/position" );		
        m.addFloatArg(2);
        m.addFloatArg(3);
	sender1.sendMessage(m);
}

//--------------------------------------------------------------
void testApp::bangFired(ofxTLBangEventArgs& bang){
	cout << "bang fired!" << bang.flag << endl;
	if (bang.flag == "fwd1")
	{
		cout << "Moving forward projector 1" << endl;
		MoveForward();
		posturas.forward();
	}
	if (bang.flag == "bck1")
	{
		cout << "Moving backward projector 1" << endl;
		MoveBackward();
		posturas.backward();
	}
	if (bang.flag == "fwd2")
	{
		cout << "Moving forward projector 2" << endl;
		relayShield.PulseRelay3();
	}
	/*if (bang.flag == "AudioLocuraOn")
	{
		cout << "AudioLocuraOn" << endl;
		sublines[0]->play();
	}
	if (bang.flag == "AudioLocuraOff")
	{
		cout << "AudioLocuraOff" << endl;
		sublines[0]->stop();
	}*/
	if (bang.flag == "AudioSlideShowOn")
	{
		cout << "AudioSlideShowOn" << endl;
		sublines[0]->play();
	}
	if (bang.flag == "AudioSlideshowOff")
	{
		cout << "AudioSlideshowOff" << endl;
		sublines[0]->stop();
	}
	if (bang.flag == "AudioColadorOn")
	{
		cout << "AudioColadorOn" << endl;
		sublines[1]->play();
	}
	if (bang.flag == "AudioColadorOff")
	{
		cout << "AudioColadorOff" << endl;
		sublines[1]->stop();
	}
	if (bang.flag == "Projector1On")
	{
		cout << "Projector1On" << endl;
		relayShield.Relay5Off();
	}
	if (bang.flag == "Projector1Off")
	{
		cout << "Projector1Off" << endl;
		relayShield.Relay5On();
	}
	if (bang.flag == "Projector2On")
	{
		cout << "Projector2On" << endl;
		relayShield.Relay6Off();
	}
	if (bang.flag == "Projector2Off")
	{
		cout << "Projector2Off" << endl;
		relayShield.Relay6On();
	}
    if (bang.flag == "LightOn")
	{
		cout << "LightOn" << endl;
		relayShield.Relay4On();
	}
	if (bang.flag == "LightOff")
	{
		cout << "LightOff" << endl;
		relayShield.Relay4Off();
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
	posturas.update();
	if (SlideshowTimer.isTimerFinished() && SlideShowOn){
		AdvanceSlideShow();
		SlideshowTimer.reset();
		SlideshowTimer.startTimer();
		
	}
		
}

void testApp::AdvanceSlideShow(void){
	MoveForward();
	cout<<"Move slideshow on";

}
//--------------------------------------------------------------
void testApp::draw(){

	posturas.draw();
	timeline.draw();
	sublines[0]->setOffset(timeline.getBottomLeft());

    //we need to offset all the timelines below the one above it, with a 10 pixel buffer
    for(int i = 0; i < sublines.size(); i++){
        if(i != 0){
            sublines[i]->setOffset(sublines[i-1]->getBottomLeft() + ofVec2f(0, 10));
        }
        sublines[i]->draw();
    }

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
	} else if (key == 'g'){
		RelaySheildGui->toggleVisible();
		TimelineControlGui->toggleVisible();
	} 
	else if (key == 'h'){
		 timeline.hide();
		 sublines[0]->hide();
		 sublines[1]->hide();
		 //sublines[2]->hide();
	}else if (key == 's'){
		 timeline.show();
		 sublines[0]->show();
		 sublines[1]->show();
		 //sublines[2]->show();
	}
	else if (key == 'f'){
		ofSetFullscreen(1);
	}
	else if (key == 'm'){
		ofSetFullscreen(0);
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
	else if(e.widget->getName() == "Light")
    {
		ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        if (toggle->getValue())
			relayShield.Relay4On();
		else
			relayShield.Relay4Off();
    }
		else if(e.widget->getName() == "Projector1")
    {
		ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        if (toggle->getValue())
			relayShield.Relay5On();
		else
			relayShield.Relay5Off();
    }
		else if(e.widget->getName() == "Projector2")
    {
		ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        if (toggle->getValue())
			relayShield.Relay6On();
		else
			relayShield.Relay6Off();
    }
	else if(e.widget->getName() == "SlideShowOn")
    {
		ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        if (toggle->getValue()){

			SlideshowTimer.reset();
			SlideShowOn = true;
			SlideshowTimer.startTimer();
			// start slideshow music
			sublines[0]->togglePlay();
		}
		else
			SlideShowOn = false;
    }
	else if(e.widget->getName() == "Start")
    {
		if (mouseDown){
			timeline.play();
		}
    }
	else if(e.widget->getName() == "Pause")
    {
		if (mouseDown)
			{timeline.togglePlay();
			 //sublines[0]->togglePlay();
		}
    }
	else if(e.widget->getName() == "Stop")
    {
		if (mouseDown){
			timeline.stop();
			timeline.setCurrentFrame(0);
			//sublines[0]->stop();
			//sublines[0]->setCurrentFrame(0);
		}
    }
	/*else if(e.widget->getName() == "AudioLocuraStart")
    {
		if (mouseDown){
			
			sublines[0]->play();
		}
    }
	else if(e.widget->getName() == "AudioLocuraPause")
    {
		if (mouseDown)
			{
			 sublines[0]->togglePlay();
		}
    }
	else if(e.widget->getName() == "AudioLocuraStop")
    {
		if (mouseDown){
			sublines[0]->stop();
			sublines[0]->setCurrentFrame(0);
		}
    }*/
	else if(e.widget->getName() == "AudioSlideshowStart")
    {
		if (mouseDown){
			
			sublines[0]->play();
		}
    }
	else if(e.widget->getName() == "AudioSlideshowPause")
    {
		if (mouseDown)
			{
			 sublines[0]->togglePlay();
		}
    }
	else if(e.widget->getName() == "AudioSlideshowStop")
    {
		if (mouseDown){
			sublines[0]->stop();
			sublines[0]->setCurrentFrame(0);
		}
    }
	else if(e.widget->getName() == "AudioColadorStart")
    {
		if (mouseDown){
			
			sublines[1]->play();
		}
    }
	else if(e.widget->getName() == "AudioColadorPause")
    {
		if (mouseDown)
			{
			 sublines[1]->togglePlay();
		}
    }
	else if(e.widget->getName() == "AudioColadorStop")
    {
		if (mouseDown){
			sublines[1]->stop();
			sublines[1]->setCurrentFrame(0);
		}
    }

	else if(e.widget->getName() == "DisableRelays")
    {
		ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        if (toggle->getValue()) 
			relayShield.DisableRelaysControl = true;
		else
			relayShield.DisableRelaysControl = false;
    }
}
