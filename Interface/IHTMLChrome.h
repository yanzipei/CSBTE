#ifndef IHTMLCHROME_H
#define IHTMLCHROME_H

#ifdef _WIN32
#pragma once
#endif

#include "HTMLMessages.h"
#include "tier1/utlbuffer.h"

class CMsgBrowserReady;
class CMsgNeedsPaint;
class CMsgStartRequest;
class CMsgURLChanged;
class CMsgFinishedRequest;
class CMsgShowPopup;
class CMsgHidePopup;
class CMsgOpenNewTab;
class CMsgPopupHTMLWindow;
class CMsgSetHTMLTitle;
class CMsgLoadingResource;
class CMsgStatusText;
class CMsgSetCursor;
class CMsgFileLoadDialog;
class CMsgShowToolTip;
class CMsgUpdateToolTip;
class CMsgHideToolTip;
class CMsgSearchResults;
class CMsgClose;
class CMsgHorizontalScrollBarSizeResponse;
class CMsgVerticalScrollBarSizeResponse;
class CMsgGetZoomResponse;
class CMsgLinkAtPositionResponse;
class CMsgZoomToElementAtPositionResponse;
class CMsgJSAlert;
class CMsgJSConfirm;
class CMsgCanGoBackAndForward;
class CMsgOpenSteamURL;
class CMsgSizePopup;
class CMsgScalePageToValueResponse;
class CMsgRequestFullScreen;
class CMsgExitFullScreen;
class CMsgGetCookiesForURLResponse;
class CMsgNodeHasFocus;
class CMsgSavePageToJPEGResponse;
class CMsgFocusedNodeTextResponse;

struct HTMLCommandBuffer_t
{
	EHTMLCommands m_eCmd;
	int m_iBrowser;
	CUtlBuffer m_Buffer;
#ifdef DBGFLAG_VALIDATE
	virtual void Validate(CValidator &validator, const tchar *pchName)
	{
		VALIDATE_SCOPE();
		ValidateObj(m_Buffer);
	}
#endif
};

class IHTMLResponses
{
public:
	virtual ~IHTMLResponses(void) {}

public:
	virtual void BrowserSetIndex(int idx) = 0;
	virtual int BrowserGetIndex(void) = 0;
	virtual void BrowserReady(const CMsgBrowserReady *pCmd) = 0;
	virtual void BrowserNeedsPaint(const CMsgNeedsPaint *pCmd) = 0;
	virtual void BrowserStartRequest(const CMsgStartRequest *pCmd) = 0;
	virtual void BrowserURLChanged(const CMsgURLChanged *pCmd) = 0;
	virtual void BrowserFinishedRequest(const CMsgFinishedRequest *pCmd) = 0;
	virtual void BrowserShowPopup(const CMsgShowPopup *pCmd) = 0;
	virtual void BrowserHidePopup(const CMsgHidePopup *pCmd) = 0;
	virtual void BrowserOpenNewTab(const CMsgOpenNewTab *pCmd) = 0;
	virtual void BrowserPopupHTMLWindow(const CMsgPopupHTMLWindow *pCmd) = 0;
	virtual void BrowserSetHTMLTitle(const CMsgSetHTMLTitle *pCmd) = 0;
	virtual void BrowserLoadingResource(const CMsgLoadingResource *pCmd) = 0;
	virtual void BrowserStatusText(const CMsgStatusText *pCmd) = 0;
	virtual void BrowserSetCursor(const CMsgSetCursor *pCmd) = 0;
	virtual void BrowserFileLoadDialog(const CMsgFileLoadDialog *pCmd) = 0;
	virtual void BrowserShowToolTip(const CMsgShowToolTip *pCmd) = 0;
	virtual void BrowserUpdateToolTip(const CMsgUpdateToolTip *pCmd) = 0;
	virtual void BrowserHideToolTip(const CMsgHideToolTip *pCmd) = 0;
	virtual void BrowserSearchResults(const CMsgSearchResults *pCmd) = 0;
	virtual void BrowserClose(const CMsgClose *pCmd) = 0;
	virtual void BrowserHorizontalScrollBarSizeResponse(const CMsgHorizontalScrollBarSizeResponse *pCmd) = 0;
	virtual void BrowserVerticalScrollBarSizeResponse(const CMsgVerticalScrollBarSizeResponse *pCmd) = 0;
	virtual void BrowserGetZoomResponse(const CMsgGetZoomResponse *pCmd) = 0;
	virtual void BrowserLinkAtPositionResponse(const CMsgLinkAtPositionResponse *pCmd) = 0;
	virtual void BrowserZoomToElementAtPositionResponse(const CMsgZoomToElementAtPositionResponse *pCmd) = 0;
	virtual void BrowserJSAlert(const CMsgJSAlert *pCmd) = 0;
	virtual void BrowserJSConfirm(const CMsgJSConfirm *pCmd) = 0;
	virtual void BrowserCanGoBackandForward(const CMsgCanGoBackAndForward *pCmd) = 0;
	virtual void BrowserOpenSteamURL(const CMsgOpenSteamURL *pCmd) = 0;
	virtual void BrowserSizePopup(const CMsgSizePopup *pCmd) = 0;
	virtual void BrowserScalePageToValueResponse(const CMsgScalePageToValueResponse *pCmd) = 0;
	virtual void BrowserRequestFullScreen(const CMsgRequestFullScreen *pCmd) = 0;
	virtual void BrowserExitFullScreen(const CMsgExitFullScreen *pCmd) = 0;
	virtual void BrowserGetCookiesForURLResponse(const CMsgGetCookiesForURLResponse *pCmd) = 0;
	virtual void BrowserNodeGotFocus(const CMsgNodeHasFocus *pCmd) = 0;
	virtual void BrowserSavePageToJPEGResponse(const CMsgSavePageToJPEGResponse *pCmd) = 0;
	virtual void BrowserFocusedNodeValueResponse(const CMsgFocusedNodeTextResponse *pCmd) = 0;
};

class IHTMLResponses_HL1
{
public:
	virtual void BrowserReady(void) = 0;
	virtual void BrowserNeedsPaint(int textureid, int wide, int tall, const unsigned char *rgba, int updatex, int updatey, int updatewide, int updatetall, int combobox_wide, int combobox_tall, const unsigned char *combobox_rgba) = 0;
	virtual void BrowserStartRequest(const char *url, const char *target, const char *postdata, bool isredirect) = 0;
	virtual void BrowserURLChanged(const char *url, const char *postdata, bool isredirect) = 0;
	virtual void BrowserFinishedRequest(const char *url, const char *pagetitle) = 0;
	virtual void BrowserShowPopup(void) = 0;
	virtual void BrowserHidePopup(void) = 0;
	virtual void BrowserSizePopup(int x, int y, int wide, int tall) = 0;
	virtual void BrowserHorizontalScrollBarSizeResponse(int x, int y, int wide, int tall, int scroll, int scroll_max, float zoom) = 0;
	virtual void BrowserVerticalScrollBarSizeResponse(int x, int y, int wide, int tall, int scroll, int scroll_max, float zoom) = 0;
	virtual void BrowserGetZoomResponse(float flZoom) = 0;
	virtual void BrowserCanGoBackandForward(bool bgoback, bool bgoforward) = 0;
	virtual void BrowserJSAlert(const char *message) = 0;
	virtual void BrowserJSConfirm(const char *message) = 0;
	virtual void BrowserPopupHTMLWindow(const char *url, int wide, int tall, int x, int y) = 0;
	virtual void BrowserSetHTMLTitle(const char *title) = 0;
	virtual void BrowserLoadingResource(void) = 0;
	virtual void BrowserStatusText(const char *text) = 0;
	virtual void BrowserSetCursor(int in_cursor) = 0;
	virtual void BrowserFileLoadDialog(void) = 0;
	virtual void BrowserShowToolTip(const char *text) = 0;
	virtual void BrowserUpdateToolTip(const char *text) = 0;
	virtual void BrowserHideToolTip(void) = 0;
	virtual void BrowserClose(void) = 0;
	virtual void BrowserLinkAtPositionResponse(const char *url, int x, int y) = 0;
};

class IHTMLSerializer
{
public:
	virtual IHTMLResponses *GetResponseTarget(void) = 0;
	virtual int BrowserGetIndex(void) = 0;
	virtual void BrowserPosition(int x, int y) = 0;
	virtual void PostURL(const char *pchURL, const char *pchPostData) = 0;
	virtual void BrowserErrorStrings(const char *pchTitle, const char *pchHeader, const char *pchDetailCacheMiss, const char *pchDetailBadUURL, const char *pchDetailConnectionProblem, const char *pchDetailProxyProblem, const char *pchDetailUnknown) = 0;
	virtual void StopLoad(void) = 0;
	virtual void Reload(void) = 0;
	virtual void GoBack(void) = 0;
	virtual void GoForward(void) = 0;
	virtual void MouseDown(int code) = 0;
	virtual void MouseUp(int code) = 0;
	virtual void MouseWheel(int delta) = 0;
	virtual void MouseMove(int x, int y) = 0;
	virtual void MouseDoubleClick(int code) = 0;
	virtual void BrowserSize(int wide, int tall) = 0;
	virtual void KeyUp(int key, int mods) = 0;
	virtual void KeyDown(int key, int mods) = 0;
	virtual void KeyChar(int unichar) = 0;
	virtual void RunJavaScript(const char *pchScript) = 0;
	virtual void SetHorizontalScroll(int scroll) = 0;
	virtual void SetVerticalScroll(int scroll) = 0;
	virtual void SetFocus(bool focus) = 0;
	virtual void AddHeader(const char *pchHeader, const char *pchValue) = 0;
	virtual void NeedsPaintResponse(int tex) = 0;
	virtual void StartRequestResponse(bool bRes) = 0;
	virtual void RequestBrowserSizes(void) = 0;
	virtual void JSDialogResponse(int res) = 0;
	virtual void GetLinkAtPosition(int x, int y) = 0;
};

#endif
