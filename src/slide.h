#pragma once

#include "ofMain.h"

#define SLIDES_PATH "data/PerformanceSequence"
#define TRANSITION_TIME 200

class slide {

	public:


		void setup();
		void update();
		void draw();

		void forward();
		void backward();
		void showHelp();
		void loadDir();
		void chooseDir();
		void fScreen();
		void setAlpha();

		ofDirectory dir;
		string path;
		vector<ofImage> images;

		bool help;

		int img01;
		int img02;
		int alpha01;
		int alpha02;
		int transitionTime,initTransitionTime;
		bool anim,blackTransition;
		bool goingUp;   // bool used to keep track of 2 states of up and down
        bool reload;
        unsigned int timeline;
		ofSoundPlayer carouselSound;
};