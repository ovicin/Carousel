#include "slide.h"

#define SWITCH_SPEED 16000;

//--------------------------------------------------------------
void slide::setup(){
    //ofSetWindowTitle("OpenFrameworks Slideshow");
    //ofSetVerticalSync(true);
    //ofSetFrameRate(60.0);
    dir.allowExt("jpg");
    dir.allowExt("png");
    dir.allowExt("gif");
	img01   = 0;
    img02   = 0;
    alpha01 = 255;
    alpha02 = 0;
    //ofEnableAlphaBlending();
    help = true;
    anim = false;
	blackTransition = true;
    goingUp = true;
    reload = false;
    timeline = 0;
    path = SLIDES_PATH;
	loadDir();
	//carouselSound.loadSound("carousel.waw");
}

//--------------------------------------------------------------
void slide::update(){
	//ofBackground(255);


        timeline = ofGetElapsedTimeMillis();
        timeline %= SWITCH_SPEED;
        //cout <<timeline << endl;

        if(timeline < 500){
            goingUp = true;
            reload = true;
            anim = true;
        }

        if (timeline > 1200 && reload == true) {
            if (!path.empty()) {
            loadDir();
            reload = false;
            }
        }

}

//--------------------------------------------------------------
void slide::draw(){
	if (dir.size() > 0 && help == false){
		transitionTime =  ofGetElapsedTimeMillis() - initTransitionTime; 
		if ((blackTransition)&&(transitionTime < TRANSITION_TIME))
		{
			ofBackground(0);
		}
		else
		{
	    if (anim)
            setAlpha();
		//ofSetColor(255,255,255,alpha01);
		images[img01].resize(ofGetWidth(),ofGetHeight());
		images[img01].draw(0,0);  //TODO: set size of image to size of window
        //ofSetColor(255,255,255,alpha02);
        //images[img02].resize(ofGetWidth(),ofGetHeight());
        //images[img02].draw(0,0);

        //DEBUG
        //string fps = ofToString(ofGetFrameRate(),2);
        //ofSetColor(0,255,0,255);
        //ofDrawBitmapString(fps, 10, 10);
		}
	} else {
        showHelp();
	}
}

void slide::forward()
{
	img01++;
    img01%=images.size();
    img02++;
    img02%=images.size();
	initTransitionTime = ofGetElapsedTimeMillis();
	if (!carouselSound.getIsPlaying())
		carouselSound.play();
}

void slide::backward()
{
	img01--;
    img01%=images.size();
    img02--;
    img02%=images.size();
	initTransitionTime = ofGetElapsedTimeMillis();
	if (!carouselSound.getIsPlaying())
		carouselSound.play();
}

#if 0
//--------------------------------------------------------------
void slide::keyPressed  (int key){
   // cout << key << endl;
    switch(key){
        case (32):
            // next image with space bar
            if(images.size() > 0){
                anim = false;
                img01++;
                img01%=images.size();
                img02++;
                img02%=images.size();
                alpha01 = 255;
                alpha02 =0;
            }
            break;
        case (98):
            // back one image if 'b' is pressed
            if(images.size() > 0){
                anim = false;
                img01--;
                img01%=images.size();
                img02--;
                img02%=images.size();
                alpha01 = 255;
                alpha02 =0;
            }
            break;
        case (66):
            break;
        case (102):
            //fullscreen toggle if 'f' is pressed
            ofToggleFullscreen() ;
            break;
        case (70):
            //fullscreen toggle if 'f' is pressed CAPS
            ofToggleFullscreen() ;
            break;
        case (111):
            //open folder command if 'o' is pressed
            fScreen();
            chooseDir();
            break;
        case (79):
            //open folder command if 'o' is pressed CAPS
            fScreen();
            chooseDir();
            break;
        case(104):
            //show help info if 'h' is pressed
            if (help)
                help = false;
            else
                help = true;
            break;
        case(72):
            //show help info if 'h' is pressed CAPS
            showHelp();
            break;
    }

}
#endif

void slide::showHelp(){
    ofBackground(ofColor::black);
    ofSetColor(200,100,144,255);
    string pathInfo = "Use keyboard to control this thing..\n\n";
    pathInfo.append("Choose which folder to view images from by hitting 'o' key\n" );
    pathInfo.append("Note you cannot perform this action when you are fullscreen (at least not on my linux notebook w/o 2nd monitor attached)\n\n");
    pathInfo.append("Move this window to the projector screen and hit 'f' key to go fullscreen\n\n");
    pathInfo.append("Hit Space Bar to switch through images\n\n");
    pathInfo.append("and 'b' to go back one image\n\n");
    pathInfo.append("and 'esc' to close the program\n\n");
    pathInfo.append("To View this help file hit 'h'\n\n");
    ofDrawBitmapString(pathInfo, 60, 50);
}

void slide::loadDir(){


    if(!dir.isDirectoryEmpty(path)){
        int imgSize = images.size();
        dir.listDir(path);
        if(dir.size() > imgSize || dir.size() < imgSize) {
            //dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order

            //allocate the vector to have as many ofImages as files
            if( dir.size() ){
                images.assign(dir.size(), ofImage());
            }

            // you can now iterate through the files and load them into the ofImage vector
            for(int i = 0; i < (int)dir.size(); i++){
                images[i].loadImage(dir.getPath(i));
            }
            help = false;
        }
    } else {
        help = true;
    }

}

void slide::chooseDir(){
    if(ofGetWindowMode() == 0){
        ofBackground(0);
        ofFileDialogResult result = ofSystemLoadDialog("Folder To Watch...", true);
        if(result.bSuccess) {
            path = result.getPath();
           // img01   = 0;
            //img02   = 1;
           // alpha01 = 255;
            //alpha02 = 0;
            loadDir();
            //cout << "path:  " << path << endl;
        }
    }else {
    help = true;
    }
}

void slide::fScreen(){
 //   int wm = ofGetWindowMode();
    //cout << "window state: " << wm << endl;
//    if (wm == 1){
//        ofToggleFullscreen();      //TODO: when fullscreen, doesnt go back to windowed mode to open file browser
//        cout << "just toggled...";
       // float resume = ofGetElapsedTimef() + 3.0;
       // do {
       //     cout << "fuck" << endl;
       // } while(ofGetElapsedTimef() < resume);
 //   }
}

void slide::setAlpha(){

    //cout <<"goingUp:" << goingUp << endl;
    if (alpha02 ==255) {
        img01++;
        img01%=images.size();
        goingUp = false;
    }
    if (alpha02 == 0) {
        img02 = img01 + 1;
        img02%=images.size();
    }

    if(goingUp == true) {
        alpha02++;      //count up
    } else {
        if (alpha02 > 0)
            alpha02=0;
            anim = false;
    }
}