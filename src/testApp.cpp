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
	timeline.setDurationInSeconds(800);

	//for(int i = 0; i < 5; i++){
	// add audio locura index 0
        ofxTimeline* t = new ofxTimeline();
		t->setup();
		t->setBPM(120.f);
		t->setShowBPMGrid(false);
		t->addAudioTrack("Audio Locura","solomartinete-004.wav");
		t->setTimecontrolTrack("Audio Locura");
        t->setSpacebarTogglePlay(false);
        t->setDurationInSeconds(t->getAudioTrack("Audio Locura")->getDuration());
        t->setLoopType(OF_LOOP_NORMAL);
        sublines.push_back(t);
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
	//timeline.addFlags("2.ContraTiempoProjector1","timeline1_contratiempo.xml");
	//timeline.addFlags("2.ContraTiempoProjector2","timeline2_contratiempo.xml");
	//timeline.addFlags("3.BlancoProjector2","timeline2_blanco.xml");
	//timeline.addFlags("3.BlancoProjector2","timeline_xls.xml");
	timeline.addFlags("2.MicroSeccionesLampara","timeline_edl.xml");
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
    TimelineControlGui->addWidgetDown(new ofxUIButton(16, 16, false, "NextDLightSequence"));
	ofAddListener(TimelineControlGui->newGUIEvent, this, &testApp::guiEvent);

	SlideshowTimer.setup(SLIDE_SHOW_TIMER,false);
	SlideShowOn = false;
    
    
    // open an outgoing connection to HOST:PORT
	sender1.setup( HOST, PORT );
    
    
    /* MIDI STUFF*/
    
    // print the available output ports to the console
	midiOut.listPorts(); // via instance
	//ofxMidiOut::listPorts(); // via static too
	
	// connect
	midiOut.openPort(0);	// by number
	//midiOut.openPort("IAC Driver Pure Data In");	// by name
	//midiOut.openVirtualPort("ofxMidiOut");		// open a virtual port
	
	channel = 1;
	currentPgm = 0;
	note = 0;
	velocity = 128;
	pan = 0;
	bend = 0;
	touch = 0;
	polytouch = 0;

}

void testApp::senOSCEvent(){
    ofxOscMessage m;
    m.setAddress( "/sub/14 255" );
    m.addFloatArg(255);
    //m.addFloatArg(3);
	sender1.sendMessage(m);
}

void testApp::SendMidiNote(int MidiNote){
    velocity = 64;
    midiOut.sendNoteOn(channel, MidiNote,  velocity);
    cout<< "send MIDI note" << endl;
}

//--------------------------------------------------------------
void testApp::bangFired(ofxTLBangEventArgs& bang){
	cout << "bang fired!" << bang.flag << endl;
	if (bang.flag == "fwd1")
	{
		cout << "Moving forward projector 1" << endl;
		MoveForward();
        //relayShield.PulseRelay3();
        //cout<< "Flash ON CC48" << endl;
	}
	if (bang.flag == "bck1")
	{
		cout << "Moving backward projector 1" << endl;
		MoveBackward();
	}
	if (bang.flag == "fwd2")
	{
		cout << "Moving forward projector 2" << endl;

        midiOut.sendControlChange(1, 48, 127);
		relayShield.PulseRelay3();
        cout<< "Flash ON CC48" << endl;
	}
    if (bang.flag == "bck2")
	{
		cout << "Moving forward projector 2" << endl;

        midiOut.sendControlChange(1, 48, 0);
        cout<< "Flash OFF CC48" << endl;

	}
	if (bang.flag == "AudioLocuraOn")
	{
		cout << "AudioLocuraOn" << endl;
		sublines[0]->play();
	}
	if (bang.flag == "AudioLocuraOff")
	{
		cout << "AudioLocuraOff" << endl;
		sublines[0]->stop();
	}
	if (bang.flag == "AudioSlideShowOn")
	{
		cout << "AudioSlideShowOn" << endl;
		sublines[1]->play();
	}
	if (bang.flag == "AudioSlideshowOff")
	{
		cout << "AudioSlideshowOff" << endl;
		sublines[1]->stop();
	}
	if (bang.flag == "AudioColadorOn")
	{
		cout << "AudioColadorOn" << endl;
		sublines[2]->play();
	}
	if (bang.flag == "AudioColadorOff")
	{
		cout << "AudioColadorOff" << endl;
		sublines[2]->stop();
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
	if (SlideshowTimer.isTimerFinished() && SlideShowOn && (SlideShowCounter<=SlideShowPhotos)){
		AdvanceSlideShow();
		SlideshowTimer.reset();
		SlideshowTimer.startTimer();
		SlideShowCounter++;
	}
		
}

void testApp::AdvanceSlideShow(void){
	MoveForward();
	cout<<"Move slideshow on";

}
//--------------------------------------------------------------
void testApp::draw(){

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
	} else if (key == 'b'){
        ofxOscMessage m;
        m.setAddress( "/sub/14/" );
        m.addFloatArg(0);
        //m.addFloatArg(3);
        sender1.sendMessage(m);
        SendMidiNote(52);
	} else if (key == 'w'){
        ofxOscMessage m;
        m.setAddress( "/sub/14/" );
        m.addFloatArg(255);
        //m.addFloatArg(3);
        sender1.sendMessage(m);
        SendMidiNote(1);
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
    
    
    // clean up
	midiOut.closePort();
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
			sublines[1]->togglePlay();
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
	else if(e.widget->getName() == "AudioLocuraStart")
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
    }
	else if(e.widget->getName() == "AudioSlideshowStart")
    {
		if (mouseDown){
			
			sublines[1]->play();
		}
    }
	else if(e.widget->getName() == "AudioSlideshowPause")
    {
		if (mouseDown)
			{
			 sublines[1]->togglePlay();
		}
    }
	else if(e.widget->getName() == "AudioSlideshowStop")
    {
		if (mouseDown){
			sublines[1]->stop();
			sublines[1]->setCurrentFrame(0);
		}
    }
	else if(e.widget->getName() == "AudioColadorStart")
    {
		if (mouseDown){
			
			sublines[2]->play();
		}
    }
	else if(e.widget->getName() == "AudioColadorPause")
    {
		if (mouseDown)
			{
			 sublines[2]->togglePlay();
		}
    }
	else if(e.widget->getName() == "AudioColadorStop")
    {
		if (mouseDown){
			sublines[2]->stop();
			sublines[2]->setCurrentFrame(0);
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
    else if(e.widget->getName() == "NextDLightSequence")
    {
		if (mouseDown)
        {
            SendMidiNote(1);
		}
        
        
    }
    
    
}
