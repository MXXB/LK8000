/*
   LK8000 Tactical Flight Computer -  WWW.LK8000.IT
   Released under GNU/GPL License v.2
   See CREDITS.TXT file for authors and copyrights

   $Id: dlgAirspaceColours.cpp,v 1.1 2011/12/21 10:29:29 root Exp root $
*/

#include "externs.h"
#include "dlgTools.h"
#include "WindowControls.h"
#include "LKObjects.h"
#include "resource.h"

static WndForm *wf=NULL;
static WndListFrame *wAirspaceColoursList=NULL;
static WndOwnerDrawFrame *wAirspaceColoursListEntry = NULL;

static int ItemIndex = -1;


static void UpdateList(void){
  wAirspaceColoursList->ResetList();
  wAirspaceColoursList->Redraw();
}

static int DrawListIndex=0;

static void OnAirspaceColoursPaintListItem(WindowControl * Sender, LKSurface& Surface){
  (void)Sender;
  if ((DrawListIndex < NUMAIRSPACECOLORS) &&(DrawListIndex>=0)) {
    int i = DrawListIndex;
    Surface.SelectObject(LKBrush_White);
    Surface.SelectObject(LK_BLACK_PEN);
    Surface.SetBkColor(LKColor(0xFF, 0xFF, 0xFF));
    Surface.SelectObject(MapWindow::GetAirspaceSldBrush(i)); // this is the solid brush
    Surface.SetTextColor(MapWindow::GetAirspaceColour(i));
    Surface.Rectangle(
              100*ScreenScale, 
              2*ScreenScale,
              180*ScreenScale,
              22*ScreenScale);
  }
}


static void OnAirspaceColoursListEnter(WindowControl * Sender, 
				WndListFrame::ListInfo_t *ListInfo) {
  (void)Sender;
  ItemIndex = ListInfo->ItemIndex + ListInfo->ScrollIndex;
  if (ItemIndex>=NUMAIRSPACECOLORS) {
    ItemIndex = NUMAIRSPACECOLORS-1;
  }
  if (ItemIndex>=0) {
    wf->SetModalResult(mrOK);
  }
}


static void OnAirspaceColoursListInfo(WindowControl * Sender, 
			       WndListFrame::ListInfo_t *ListInfo){
  (void)Sender;
  if (ListInfo->DrawIndex == -1){
    ListInfo->ItemCount = NUMAIRSPACECOLORS;
  } else {
    DrawListIndex = ListInfo->DrawIndex+ListInfo->ScrollIndex;
    ItemIndex = ListInfo->ItemIndex+ListInfo->ScrollIndex;
  }
}

static void OnCloseClicked(WndButton* pWnd){
  (void)pWnd;
  ItemIndex = -1;
  wf->SetModalResult(mrOK);
}


static CallBackTableEntry_t CallBackTable[]={
  OnPaintCallbackEntry(OnAirspaceColoursPaintListItem),
  OnListCallbackEntry(OnAirspaceColoursListInfo),
  ClickNotifyCallbackEntry(OnCloseClicked),
  EndCallBackEntry()
};


int dlgAirspaceColoursShowModal(void){

  ItemIndex = -1;

    wf = dlgLoadFromXML(CallBackTable, 
                       ScreenLandscape ? TEXT("dlgAirspaceColours_L.xml") : TEXT("dlgAirspaceColours_P.xml"), 
                       ScreenLandscape ? IDR_XML_AIRSPACECOLOURS_L : IDR_XML_AIRSPACECOLOURS_P);
  
  if (!wf) return -1;

  wAirspaceColoursList = (WndListFrame*)wf->FindByName(TEXT("frmAirspaceColoursList"));
  if(wAirspaceColoursList) {
    wAirspaceColoursList->SetEnterCallback(OnAirspaceColoursListEnter);
  }

  wAirspaceColoursListEntry = (WndOwnerDrawFrame*)wf->FindByName(TEXT("frmAirspaceColoursListEntry"));
  if(wAirspaceColoursListEntry) {
    wAirspaceColoursListEntry->SetCanFocus(true);
  }

  UpdateList();

  wf->ShowModal();

  delete wf;

  wf = NULL;

  return ItemIndex;
}


