//
//  Clipboard.cpp
//  openNI-3DJ
//
//  Created by Sam Ruberti on 5/16/13.
//
//

#include "Clipboard.h"
#include <iostream>

Clipboard::Clipboard(int _x, int _y, ofxUIColor col_canvas, ofxUIColor col_button, ofxUIColor col_fill_highlight, ofxUIColor col_outline,
                     ofxUIColor col_outline_highlight, ofxUIColor col_padded, ofxUIColor col_padded_outline){
    m_posX = _x;
    m_posY = _y;
    m_col_canvas = col_canvas;
    m_col_button = col_button;
    m_col_fill_highlight = col_fill_highlight;
    m_col_outline = col_outline;
    m_col_outline_highlight = col_outline_highlight;
    m_col_padded = col_padded;
    m_col_padded_outline = col_padded_outline;
    
    setupGUI();
}

Clipboard::~Clipboard(){
    //saveSettings();
    if (m_canvas1) delete m_canvas1;
}

void Clipboard::setupGUI(){
    
    int matrixButtonSize = 54;
    int clipboardWidth = 241;
    int clipboardHeight = 300;
    int moveButtonSize = 28;
    int buttonPadding = 5;
    int controlButtonSize = 44;
    
    //Canvas1 Setup
    m_canvas1 = new ofxUICanvas( m_posX, m_posY, clipboardWidth, clipboardHeight );
    m_canvas1->setColorBack(m_col_canvas);
    m_canvas1->setPadding(buttonPadding);
    m_canvas1->setWidgetSpacing(buttonPadding);
    
    loadCanvasAssets();
    
    ofxUIWidget *w = (ofxUIWidget *) m_canvas1->addWidgetDown(new ofxUIImageToggle(0.0f ,0.0f,moveButtonSize, moveButtonSize, true, "icons/green_bar.png", "move", OFX_UI_FONT_SMALL));
    ofxUIWidget *m = (ofxUIWidget *) m_canvas1->addWidgetRight( new ofxUITextInput("", "NAME", 170, moveButtonSize, 0, 0, OFX_UI_FONT_SMALL ));
    w = m_canvas1->addWidgetDown(new ofxUIToggleMatrix( matrixButtonSize, matrixButtonSize, 3, 4, ""));
    m_canvas1->setWidgetSpacing(10);
    w = m_canvas1->addWidgetDown(new ofxUIImageToggle(0.0f ,0.0f,controlButtonSize,controlButtonSize, true, "icons/play.png", "play", OFX_UI_FONT_SMALL));
    w->setColorBack(m_col_button);
    w = m_canvas1->addWidgetRight(new ofxUIImageToggle(0.0f ,0.0f,controlButtonSize,controlButtonSize, false, "icons/loadFile.png", "load", OFX_UI_FONT_SMALL));
    w = m_canvas1->addWidgetRight(new ofxUIImageToggle(0.0f ,0.0f,controlButtonSize,controlButtonSize, false, "icons/saveFile.png", "save", OFX_UI_FONT_SMALL));
    w = m_canvas1->addWidgetRight(new ofxUIImageToggle(0.0f ,0.0f,controlButtonSize,controlButtonSize, false, "icons/x.png", "close", OFX_UI_FONT_SMALL));
    
    setWidgetColors(); //draw color settings to canvas & all widgets
    m->setDrawBack(false); //overide color settings for certain widgets
}

void Clipboard::setWidgetColors(){
    m_canvas1->setWidgetColor(OFX_UI_WIDGET_COLOR_BACK, m_col_button);
    m_canvas1->setWidgetColor(OFX_UI_WIDGET_COLOR_FILL_HIGHLIGHT, m_col_fill_highlight);
    m_canvas1->setWidgetColor(OFX_UI_WIDGET_COLOR_OUTLINE_HIGHLIGHT, m_col_outline_highlight);
}

bool Clipboard::loadCanvasAssets(){
    //Fonts
    m_canvas1->setFont("GUI/RopaSans-Regular.ttf");
    m_canvas1->setFontSize(OFX_UI_FONT_SMALL, 7);
    m_canvas1->setFontSize(OFX_UI_FONT_MEDIUM, 9);
    m_canvas1->setFontSize(OFX_UI_FONT_LARGE, 11);
    
    //Images
    greenImg = new ofImage();
    greenImg->loadImage("icons/green_bar.png");
    m_xImg = new ofImage();
    m_xImg->loadImage("icons/x.png");
    m_saveImg = new ofImage();
    m_saveImg->loadImage("icons/saveFile.png");
    m_playImg = new ofImage();
    m_playImg->loadImage("icons/play.png");
    m_loadImg = new ofImage();
    m_loadImg->loadImage("icons/loadFile.png");
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

