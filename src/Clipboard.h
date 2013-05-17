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
    
    Clipboard();
    ~Clipboard();
    
    void setupGUI();
    void setupButtons();
    void saveSettings();
    void loadSettings(string filepath);
    void loadSettings();
    void showCanvases(bool show);
    void setColorTheme(int theme);
    void moveClipboard(int x, int y );
    ofVec2f getCanvasPosition();
    
    ofxUICanvas *m_canvas1;
    
    string m_clipboardTitle;
    int m_posX;
    int m_posY;
    
    ofImage *greenImg;
    ofImage *xImg;
};

#endif /* defined(__openNI_3DJ__Clipboard__) */
