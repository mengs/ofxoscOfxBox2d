#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

int main() {
	
    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1524, 1200, OF_WINDOW);
	ofRunApp(new testApp());
	
}
