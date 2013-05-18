//
//  Clipboard.h
//  openNI-3DJ
//
//  Created by Sam Ruberti on 5/16/13.
//
//

#ifndef __openNI_3DJ__Clipboard__
#define __openNI_3DJ__Clipboard__
#include "CWindow_Base.h"

class Clipboard : public CWindow_Base
{
public:
    
    Clipboard(int _x, int _y, ofxUIColor col_canvas, ofxUIColor col_button, ofxUIColor col_fill_highlight, ofxUIColor col_outline, ofxUIColor col_outline_highlight, ofxUIColor col_padded, ofxUIColor col_padded_outline);
    ~Clipboard();
    
    void setupGUI();
    void setupButtons();
    void saveSettings();
    void loadSettings(string filepath);
    void loadSettings();
    void showCanvases(bool show);
    void setColorTheme(int theme);
    void setWidgetColors();
    void moveClipboard(int x, int y );
    bool loadCanvasAssets();
    ofVec2f getCanvasPosition();
    
    ofxUICanvas *m_canvas1;
    
    string m_clipboardTitle;
    int m_posX;
    int m_posY;
    
    ofImage *greenImg;
    ofImage *m_xImg, *m_saveImg, *m_playImg, *m_loadImg;
    
    ofxUIColor m_col_canvas, m_col_button, m_col_fill_highlight, m_col_outline, m_col_outline_highlight, m_col_padded, m_col_padded_outline;
};

#endif /* defined(__openNI_3DJ__Clipboard__) */
