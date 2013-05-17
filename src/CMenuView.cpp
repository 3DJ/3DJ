//
//  CMenuView.cpp
//  3DJ
//
//  Created by  on 9/1/12.
//

#include <iostream>
#include "CMenuView.h"

CMenuView::CMenuView()
{
    setupGUI();
}

CMenuView::~CMenuView()
{
    delete m_canvas1;
}

void CMenuView::setupGUI()
{
    int heightOffset = 64;
    int canvas_w = 200;
    int canvas_h = 260;   //ofGetScreenHeight() - heightOffset;
    float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = canvas_w-(xInit*2);
    float buttonLength = length; //(length-xInit)*.5;
    int buttonHeight = 40;
    
    ofColor m_3DJ_Green_Light = ofColor(159,231,101);
    ofColor m_3DJ_Green_Dark = ofColor(108,129,100);
    ofColor buttonGrey = ofColor(61);
    
    // canvas settings
    m_canvas1 = new ofxUICanvas(0,heightOffset,canvas_w, canvas_h);
    m_canvas1->setColorFill(ofColor(0)); //text, etc
    m_canvas1->setColorFillHighlight(m_3DJ_Green_Dark);
    m_canvas1->setDrawBack(false);
    m_canvas1->setWidgetSpacing(1.0f);
    
    //m_canvas1->setPadding(true);
    m_canvas1->setFont("GUI/RopaSans-Regular.ttf");
    m_canvas1->setFontSize(OFX_UI_FONT_SMALL, 7);
    m_canvas1->setFontSize(OFX_UI_FONT_MEDIUM, 9);
    m_canvas1->setFontSize(OFX_UI_FONT_LARGE, 11);
    
    // Add buttons
    ofxUILabelButton *b = (ofxUILabelButton *) m_canvas1->addWidgetDown(
                                new ofxUILabelButton("START SESSION", false, buttonLength, buttonHeight, 0, 0, OFX_UI_FONT_SMALL, false));
    b->setColorBack(m_3DJ_Green_Light);
    b = (ofxUILabelButton *) m_canvas1->addWidgetDown(new ofxUILabelButton("CONFIGURE SESSION", false, buttonLength, buttonHeight,0, 0, OFX_UI_FONT_SMALL, false));
    b->setColorBack(m_3DJ_Green_Light);
    b = (ofxUILabelButton *) m_canvas1->addWidgetDown(new ofxUILabelButton("SAVE SESSION", false, buttonLength, buttonHeight,0, 0, OFX_UI_FONT_SMALL, false));
    b->setColorBack(m_3DJ_Green_Light);
    b = (ofxUILabelButton *) m_canvas1->addWidgetDown(new ofxUILabelButton("GET SOUNDS", false, buttonLength, buttonHeight,0, 0, OFX_UI_FONT_SMALL, false));
    b->setColorBack(m_3DJ_Green_Light);
    
    b = (ofxUILabelButton *) m_canvas1->addWidgetDown(new ofxUILabelButton("HELP", false, buttonLength, buttonHeight,0, 0, OFX_UI_FONT_SMALL, false));
    b->setColorBack(m_3DJ_Green_Light);
}


void CMenuView::saveSettings()
{
    
}

void CMenuView::loadSettings()
{
    
}

void CMenuView::setColorTheme(int theme)
{
    
}

void CMenuView::showCanvases(bool show)
{
    m_canvas1->setVisible(show);
    m_canvasesVisible = show;
}






