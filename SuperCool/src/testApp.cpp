#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup() {
    receiver.setup(8338);
    ofSetVerticalSync(true);
    ofSetBackgroundColor(255, 255, 255);
	ofSetLogLevel(OF_LOG_NOTICE);


	
	box2d.init();
	box2d.setGravity(0, 10);
	box2d.createBounds();
	box2d.setFPS(30.0);
	box2d.registerGrabbing();
    mrsilly.loadImage("sample.png");
    
    

    	
	
}

//--------------------------------------------------------------
void testApp::update() {
    ofBackground(255,255,255);
        
	box2d.update();
    
	// check for waiting osc messages
	while(receiver.hasWaitingMessages())
	{
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
        // load face from any FaceOSC messages
        face.parseOSC(m);
	}
    
    // found face?
    if(face.found > 0) {
        cout << "---------" << endl
        << face.toString();
    }
}
//--------------------------------------------------------------
void testApp::draw() {
	// draw a face
    if(face.found > 0) {
        
       // mrsilly.draw(0, 0);

        for(int i=0; i<circles.size(); i++) {
            ofFill();
            ofSetColor(255,0,0,127); 
            circles[i].draw();
        }
        
        for(int i=0; i<boxes.size(); i++) {
            ofFill();
            ofSetColor(255,0,0,255);
            boxes[i].draw();
        }
        
        // draw the ground
        box2d.drawGround();
    ofPushMatrix();
        ofTranslate(face.posePosition);
        ofScale(face.poseScale, face.poseScale);

   
   // the face is cry
        if(face.mouthHeight > 5) {
            float r = ofRandom(4, 20);		// a random radius 4px - 20px
            ofxBox2dCircle circle;
            circle.setPhysics(3.0, 0.53, 0.1);
            circle.setup(box2d.getWorld(), face.posePosition.x+200, face.posePosition.y+200, r);
            circles.push_back(circle);
        }
        
        ofSetColor(255,255,255);
        mrsilly.draw(0,0);
        
    ofPopMatrix();

string info = "";
	info += "Press [c] for circles\n";
	info += "Press [b] for blocks\n";
	info += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
	info += "Total Joints: "+ofToString(box2d.getJointCount())+"\n\n";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
	ofSetHexColor(0x444342);
	ofDrawBitmapString(info, 30, 30);
    }
}

//--------------------------------------------------------------
    
void testApp::keyPressed(int key) {
// Cry
	if(key == 'c') {
		float r = ofRandom(4, 20);		// a random radius 4px - 20px
		ofxBox2dCircle circle;
		circle.setPhysics(3.0, 0.53, 0.1);
		circle.setup(box2d.getWorld(), face.posePosition.x, face.posePosition.y, r);
		circles.push_back(circle);
	}
	
	if(key == 'b') {
		float w = ofRandom(4, 20);
		float h = ofRandom(4, 20);
		ofxBox2dRect rect;
		rect.setPhysics(3.0, 0.53, 0.1);
		rect.setup(box2d.getWorld(), mouseX, mouseY, w, h);
		boxes.push_back(rect);
	}
	
	if(key == 't') ofToggleFullscreen();
}


//--------------------------------------------------------------
void testApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::resized(int w, int h){
}

