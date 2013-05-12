//
//  CMenuViewController.h
//  3DJ
//
//  Created by Sam Ruberti on 9/2/12.
//

#ifndef _DJ_UI_CMenuViewController_h
#define _DJ_UI_CMenuViewController_h
#include "CMenuView.h"
#include "ofxUI.h"
#include "CLoopEditorView.h"
#include "CalibrationView.h"
#include "Interface.h"
#include "DataPool.h"
#include "BoxButton.h"

using namespace DataPool;
using namespace Interface;

class CMenuViewController : public IView
{
public:


    CMenuViewController(int red, int blue, int green, int alpha);
    ~CMenuViewController();

    void initViews();
    void setupDelegates();
    void menuEvent(ofxUIEventArgs &e);
    void loopEditorEvent(ofxUIEventArgs &e);
    void visualEditorEvent(ofxUIEventArgs &e);
    void showMenuView(bool _showMenuView);
    void hideAllViews();
    bool draw();
    void saveRadioButtonInfo(string boxID);
    void processOpenFileSelection(ofFileDialogResult openFileResult, string boxID);

    CMenuView               *m_menu;
    CLoopEditorView         *m_loopEditor;
    CalibrationView         *m_calibrationEditor;
    CDataPool         *m_datapool;

    int m_r, m_g, m_b, m_a;
    bool m_exitMenu;

    string originalFileExtension;
};

#endif
