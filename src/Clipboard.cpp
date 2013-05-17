//
//  Clipboard.cpp
//  openNI-3DJ
//
//  Created by Sam Ruberti on 5/16/13.
//
//

#include "Clipboard.h"
#include <iostream>

Clipboard::Clipboard(){
    setupGUI();
}

Clipboard::~Clipboard(){
    //saveSettings();
    if (m_canvas1) delete m_canvas1;
}

void Clipboard::setupGUI(){
    
    int dim = 48 + 6;
    int m_posX = 232;
    int m_posY = 64;
    int clipboardWidth = 217+24;
    int clipboardHeight = 300;
    int spacerHeight = 15;
    int buttonHeight = 28;
    int buttonWidth  = 28;
    int buttonPadding = 5;
    
    int controlButtonWidth = 102;
    int controlButtonHeight = 24;
    
    ofColor m_3DJ_Green_Light = ofColor(159,231,101);
    ofColor m_3DJ_Green_Dark = ofColor(108,129,100);
    ofColor buttonGrey = ofColor(61);
    ofColor canvasGrey = ofColor(20);
    ofColor col = ofColor(20);
    
    //Canvas One Setup
    m_canvas1 = new ofxUICanvas( m_posX, m_posY, clipboardWidth, clipboardHeight );
    m_canvas1->setColorFill(buttonGrey); //color for text
    m_canvas1->setWidgetSpacing(1.0f);
    m_canvas1->setColorFill(ofColor(255)); //text, etc
    m_canvas1->setColorPadded(canvasGrey);
    m_canvas1->setColorBack(canvasGrey);
    m_canvas1->setPadding(buttonPadding);
    m_canvas1->setWidgetSpacing(buttonPadding);

    //Fonts
    m_canvas1->setFont("GUI/RopaSans-Regular.ttf");
    m_canvas1->setFontSize(OFX_UI_FONT_SMALL, 7);
    m_canvas1->setFontSize(OFX_UI_FONT_MEDIUM, 9);
    m_canvas1->setFontSize(OFX_UI_FONT_LARGE, 11);
    
    //Images
    greenImg = new ofImage();
    greenImg->loadImage("icons/green_bar.png");
    xImg = new ofImage();
    xImg->loadImage("icons/x.png");
    
    //Add buttons
    m_canvas1->addWidgetDown(new ofxUIImage(buttonWidth, buttonHeight, greenImg, ""));
    m_canvas1->setWidgetSpacing(18); //Move next button to right
    m_canvas1->addWidgetRight( new ofxUITextInput("", "NAME", 170, buttonHeight, 0, 0, OFX_UI_FONT_SMALL ));
    m_canvas1->setWidgetSpacing(buttonPadding); //reset spaceing
    
    //Matrix Buttons
    ofxUIWidget *w = (ofxUIWidget *) m_canvas1->addWidgetDown(new ofxUIToggleMatrix(dim, dim, 3, 4, ""));
    w->setColorFill(buttonGrey);
    
    //Control Buttons: Play Save Load
    w = m_canvas1->addWidgetDown( new ofxUILabelButton
                           ("PLAY", false, controlButtonWidth, controlButtonHeight,0, 0, OFX_UI_FONT_SMALL, false));
    w->setColorBack(buttonGrey);
    w = m_canvas1->addWidgetRight(new ofxUILabelButton("LOAD", false, controlButtonWidth,
                                                                             controlButtonHeight, 0, 0, OFX_UI_FONT_SMALL, false));
    w->setColorBack(buttonGrey);
    w = m_canvas1->addWidgetDown(new ofxUILabelButton("SAVE", false, controlButtonWidth,
                                                                             controlButtonHeight, 0, 0, OFX_UI_FONT_SMALL, false));
    w->setColorBack(buttonGrey);
    
    w = m_canvas1->addWidgetRight(new ofxUIImage(buttonWidth, buttonHeight, xImg, ""));
}

void Clipboard::setupButtons(){
    
}

void Clipboard::moveClipboard(int x, int y ){
    m_canvas1->setPosition(x, y);
    m_posX = x;
    m_posY = y;
}

ofVec2f Clipboard::getCanvasPosition(){
    return ofVec2f( m_posX, m_posY);
}

void Clipboard::saveSettings(){

}

void Clipboard::loadSettings(string filepath){
    m_canvas1->loadSettings(filepath);
}

void Clipboard::loadSettings(){

}

void Clipboard::showCanvases(bool show){
    m_canvas1->setVisible(show);
}

void Clipboard::setColorTheme(int theme){

}

