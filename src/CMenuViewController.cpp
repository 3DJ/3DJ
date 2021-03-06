//
//  CMenuViewController.cpp
//  3DJ
//
//  Created by Sam Ruberti on 9/2/12.
//

#include "CMenuViewController.h"
#include "CWorld.h"

CMenuViewController::CMenuViewController(int red, int green, int blue, int alpha )
{
    m_datapool = &CDataPool::getInstance();
    m_r = red;
    m_g = green;
    m_b = blue;
    m_a = alpha;
    m_exitMenu = false;

    initViews();
    setupDelegates(); //adds ofAddListener for each ofxUICanvas in views
    hideAllViews(); //hide all views at start
    showMenuView(true); //Start with menu
    m_clipboard->showCanvases(true);
    
    m_bg.loadImage("textures/scratch_tile.png");
}

CMenuViewController::~CMenuViewController()
{
    delete m_menu;
    delete m_calibrationEditor;
    delete m_datapool;
    delete m_clipboard;
}

void CMenuViewController::initViews()
{
    
    ofColor green_light = ofColor(159,231,101);
    ofColor green_dark = ofColor(108,129,100);
    ofColor button_grey = ofColor(61);
    ofColor canvas_grey = ofColor(20);
    ofColor white = ofColor(255);
    
    m_menu = new CMenuView;
    m_calibrationEditor = new CalibrationView();
    m_clipboard = new Clipboard( 232, 64, canvas_grey, button_grey, white, green_dark, green_light, canvas_grey, green_dark);
}

void CMenuViewController::update()
{
    m_clipboard->update();
}

void CMenuViewController::menuEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    int kind = e.widget->getKind();

    //Main Menu
    if(name == "START SESSION"){
        static string val = "testThread"; // for testing the datapool communicating between threads
        CDataPool::getInstance().createRef("testDataPool", &val);
        m_exitMenu = true;
        hideAllViews();
        g_currentState = ST_BOX_STATE;
    }else if(name == "CONFIGURE SESSION"){
        m_clipboard->showCanvases(true);
        m_calibrationEditor->m_canvas1->setVisible(false);
    }else if(name == "GET SOUNDS"){
        m_clipboard->showCanvases(false);
        m_calibrationEditor->m_canvas1->setVisible(false);
    }else if(name == "HELP"){
        m_clipboard->showCanvases(false);
        m_calibrationEditor->m_canvas1->setVisible(false);
    }else if(name == "SAVE SESSION"){
        string saveFileName = "config.3dj";
        CDataPool::getInstance().saveToFile( saveFileName );
    }
}

void CMenuViewController::clipboardEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    int kind = e.widget->getKind();
    int parent = e.widget->getParent()->getKind();
    m_clipboard->changeState(name);
    ofLogVerbose(ofToString(name));

    if(m_clipboard->m_state == ST_MENU_LOAD && parent == OFX_UI_WIDGET_TOGGLEMATRIX){
        loopEditorEvent(ofToString(name));
    }
}

void CMenuViewController::loopEditorEvent(string name)
{
    if(name == "matrix(0,0)"){
        saveRadioButtonInfo("A1");
    }else if(name == "matrix(1,0)"){
        saveRadioButtonInfo("A2");
    }else if(name == "matrix(2,0)"){
        saveRadioButtonInfo("A3");
    }else if(name == "matrix(3,0)"){
        saveRadioButtonInfo("A4");
    }else if(name == "matrix(0,1)"){
        saveRadioButtonInfo("B1");
    }else if(name == "matrix(1,1)"){
        saveRadioButtonInfo("B2");
    }else if(name == "matrix(2,1)"){
        saveRadioButtonInfo("B3");
    }else if(name == "matrix(3,1)"){
        saveRadioButtonInfo("B4");
    }else if(name == "matrix(0,2)"){
        saveRadioButtonInfo("C1");
    }else if(name == "matrix(1,2)"){
        saveRadioButtonInfo("C2");
    }else if(name == "matrix(2,2)"){
        saveRadioButtonInfo("C3");
    }else if(name == "matrix(3,2)"){
        saveRadioButtonInfo("C4");
    }
}

void CMenuViewController::visualEditorEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();

    if(name == "") {

    }else if(name == ""){

    }
}

void CMenuViewController::setupDelegates()
{
    ofAddListener(m_menu->m_canvas1->newGUIEvent, this, &CMenuViewController::menuEvent);
    ofAddListener(m_clipboard->m_canvas1->newGUIEvent, this, &CMenuViewController::clipboardEvent);

}

void CMenuViewController::showMenuView(bool _showMenuView)
{
    if(_showMenuView){
        m_menu->m_canvas1->setVisible(_showMenuView);
    }else {
        //hideallViews();
    }
}

void CMenuViewController::hideAllViews()
{
    m_menu->m_canvas1->setVisible(false);
    m_clipboard->m_canvas1->setVisible(false);
    m_calibrationEditor->m_canvas1->setVisible(false);
}

bool CMenuViewController::draw()
{
    int h = m_bg.height;
    int w = m_bg.width;
    for (int x = 0; x < ofGetScreenWidth(); x += w) {
        for (int y = 0; y < ofGetScreenHeight(); y += h ) {
            m_bg.draw(x,y);
        }
        
    }
    showMenuView(true);
    return true;
}

void CMenuViewController::saveRadioButtonInfo(string boxID) {

    //Open the Open File Dialog
    ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a wav or mp3 audio file");

    //Check if the user opened a file
    if (openFileResult.bSuccess){

        ofLogVerbose("User selected a file");

        //We have a file, check it and process it
        processOpenFileSelection(openFileResult,boxID);

    }else {
        ofLogVerbose("User hit cancel");
    }    
}

void CMenuViewController::processOpenFileSelection(ofFileDialogResult openFileResult, string boxID){

	ofLogVerbose("getName(): "  + openFileResult.getName());
	ofLogVerbose("getPath(): "  + openFileResult.getPath());

	ofFile file (openFileResult.getPath());

	if (file.exists()){

		ofLogVerbose("The file exists - now checking the type via file extension");
		string fileExtension = ofToUpper(file.getExtension());

		//Only WAV or MP3 Files
		if (fileExtension == "WAV" || fileExtension == "MP3") {

            //====================================================================
            //Load sound files into Datapool XML File
            //====================================================================
            //string fileName = "sounds/" + file.getFileName();
            string key;
            key.resize(boxID.size());
            transform(boxID.begin(), boxID.end(), key.begin(), ::tolower);
            key = key + "Button";

            //reload sound file.
            void *val;
            if ( m_datapool->getRefByName("boxButtons", val) ) {
                vector<CBoxButton*> *vecBoxes = (vector<CBoxButton*> *)val;
                for ( vector<CBoxButton*>::iterator iter = vecBoxes->begin(); iter!=vecBoxes->end(); iter ++){
                    if ( (*iter)->getBoxName() == boxID ){
                        cout<<"reload sound:"<<file.getAbsolutePath();
                        (*iter)->reloadSound(file.getAbsolutePath());
                        m_datapool->setValue( boxID, file.getAbsolutePath(), true );
                        break;
                    }
                }                                
            }else{
                ofLogVerbose("cannot get the reference of box vector");
            }
		}
	}

    file.close();
}


