# Wtl Note

----


## ATL
<b>ATL Windowing-class Hierarchy</b>

> ![img](./wtlpic/atl_he.png)

<b>Wtl Windowing-class Hierarchy</b>

>![img](./wtlpic/wtl_he.png)

## ALL

![imag](./wtlpic/wtl_all.png)
----

##CMessageMap

<pre><code>
class ATL_NO_VTABLE CMessageMap
{
public:
	virtual BOOL ProcessWindowMessage(
		_In_ HWND hWnd,
		_In_ UINT uMsg,
		_In_ WPARAM wParam,
		_In_ LPARAM lParam,
		_Inout_ LRESULT& lResult,
		_In_ DWORD dwMsgMapID) = 0;
};

#define <B>BEGIN_MSG_MAP(theClass)</B> \
public: \
	BOOL ProcessWindowMessage(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam,\
		_In_ LPARAM lParam, _Inout_ LRESULT& lResult, _In_ DWORD dwMsgMapID = 0) \
	{ \
		BOOL bHandled = TRUE; \
		(hWnd); \
		(uMsg); \
		(wParam); \
		(lParam); \
		(lResult); \
		(bHandled); \
		switch(dwMsgMapID) \
		{ \
		case 0:


#define <B>END_MSG_MAP()</B> \
			break; \
		default: \
			ATLTRACE(ATL::atlTraceWindowing, 0, _T("Invalid message map ID (%i)\n"), dwMsgMapID); \
			ATLASSERT(FALSE); \
			break; \
		} \
		return FALSE; \
	}
</code></pre>

## 3. custum controls
1. <pre>
class MyListView : public CWindowImpl< MyListView, CListViewCtrl >,
                       public CCustomDraw< MyListView >     
</pre>

2. <pre><code>
`#if (_WTL_VER >= 0x0700)
	BOOL m_bHandledCD;
	BOOL IsMsgHandled() const
	{
		return m_bHandledCD;
	}
	void SetMsgHandled(BOOL bHandled)
	{
		m_bHandledCD = bHandled;
	}
`#if (_WTL_VER > 0x0700)
`#pragma message("WTL > 7.0 Revisit WTL Bug Kludge:  Is IsMsgHandled, " \
	`"SetMsgHandled still required in derived class when "  \
	`"using CCustomDraw?");
`#endif //(_WTL_VER > 0x0700)
`#endif //(_WTL_VER >= 0x0700)
`#endif</code></pre>

<b>or</b>
> 
<font color="#ff00000">`BEGIN_MSG_MAP_EX`</font>

<b>or</b>
> 
IN PARENT HWND : </br>
> <font color="#ff00000"><b>`REFLECT_NOTIFICATIONS()`</font></b></br>
in this CLASS: </br>
> <font color="#ff00000"><b>`CHAIN_MSG_MAP_ALT(CCustomDraw< THIS >,1)`</font></b>

###3.  realize 
   * DWORD OnPrePaint(int /\*idCtrl\*/, LPNMCUSTOMDRAW /\*lpNMCustomDraw\*/)
   * DWORD OnItemPrePaint(int /\*idCtrl\*/, LPNMCUSTOMDRAW lpNMCustomDraw)
> IN:  <font color="#3322ff"><b>`DWORD OnItemPrePaint(int /\*idCtrl\*/, LPNMCUSTOMDRAW lpNMCustomDraw)`</b></font>
> 
<pre><code> <font color="#337700"><b> NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( lpNMCustomDraw );</b></font>
     // This is the prepaint stage for an item. Here's where we set the
     // item's text color. Our return value will tell Windows to draw the
     // item itself, but it will use the new color we set here for the background
     COLORREF crText;
     if ( (pLVCD->nmcd.dwItemSpec % 2) == 0 )
	 {
       		<font color="#ff0000"><b>pLVCD->crText = RGB(255,0,255);
	   		pLVCD->clrText  = RGB(0,125,255);</b></font>
	 }
     else 
	 {
      		<font color="#ff0000"><b>pLVCD->crText = RGB(255,255,255); 
	  		pLVCD->clrText  = RGB(255,125,0);</b></font>
	 }</code> <pre>

----

# wtl docking class


1. <h2>pre-build set-up</h2>	
	* Make sure all header files are placed in the appropriate location and compiler can reach it.
	* Add DockImpl.cpp to the project. Probably the best way to do it is to add <font color="#ff0000"><b>`#include< DockImpl.cpp>`</b></font> to the `stdafx.cpp`.
	* Docking Windows use STL so it's requires to enable exception handling (/GX or /EH compiler options) and remove <font color="#ff0000"><b>`_ATL_MIN_CRT`</b></font> from the list the preprocessor defines in release configuration. If you use standard HP's STL you can leave default project setting intact, but I don't think it is a good idea.
	* If you use boost library define <font color="#ff0000"><b>USE_BOOST</b></font>.
	
	* I use some private message in range `WM_USER to WM_USER + 2`
		</br>
		WMDF_FIRST = WM_USER </br>
		WMDF_LAST = WM_USER + 2  </br>
	So if you define your own private messages please use WMDF_LAST+1 or if it is impossible redefine WMDF_FIRST.
2. <h2>Add to Main Frame Support for Docking Window Features</h2>	

	* Create a new project with ATL/WTL AppWizard (MDI or SDI as you like)
	* Add <font color="#ff00ff"><b>#include < DockingFrame.h > </b></font>to CMainFrame header.
	* Change the base of your <b>CMainFrame</b> class to <font color="#ff00ff"><b>dockwins::CDockingFrameImpl< CMainFrame ></b></font> for <b>SDI</b> applications or to <font color="#ff00ff"><b>dockwins::CMDIDockingFrameImpl< CMainFrame > </b></font>for <b>MDI applications</b>. All references to previous base class should be replaced by new one.

	* Add to the OnCreate method of your <b>CMainFrame</b> class <b>InitializeDockingFrame()</b>; it's the best place to change windows behavior of <b>docking window</b>. By default it is depend on system setting (Show window contents while dragging) if you for some reason need to change it you should use the following flags:</br>
	<font color="#ff00ff">CDockingBarStyle::sUseSysSettings</font> — depend on system setting, default. 					</br>
	<font color="#ff00ff">CDockingBarStyle::sIgnoreSysSettings</font> | <font color="#ff00ff">CDockingBarStyle::sFullDrag</font> — full drag			</br>
	<font color="#ff00ff">CDockingBarStyle::sIgnoreSysSettings</font> | <font color="#ff00ff">CDockingBarStyle::sGhostDrag</font> — ghost drag.		</br>
	If you use auto-hiding features you also can use the following flags:					</br>
	<font color="#ff00ff">CDockingBarStyle::sAnimation</font> — animate auto-hiding windows.								</br>
	<font color="#ff00ff">CDockingBarStyle::sNoAnimation</font> — do not animate auto-hiding windows.						</br>

3. <h2>Implement a Docking Window</h2>	
	* Add <font color="#ff00ff">#include < ExtDockingWindow.h > </font>to header file of your docking window.
	* Create new class <font color="#ff00ff">CSampleDockingWindow</font> for example. Derive it from <font color="#ff00ff">dockwins::CTitleDockingWindowImpl</font>.
	* Add message map and <font color="#ff00ff">`DECLARE_WND_CLASS`</font> macro The <b>CSampleDockingWindow</b> class should look like this:
		<pre><code>class CSampleDockingWindow :
         public dockwins::CTitleDockingWindowImpl< SampleDockingWindow,
                CWindow, dockwins::COutlookLikeTitleDockingWindowTraits >
{
        	`typedef CSampleDockingWindow    thisClass;`
        	`typedef dockwins::CTitleDockingWindowImpl< CSAMPLEDOCKINGWINDOW,
         		CWINDOW,`
         	`dockwins::COutlookLikeTitleDockingWindowTraits >  baseClass;`
	public:
        	`DECLARE_WND_CLASS(_T("CSampleDockingWindow"))`
        	`BEGIN_MSG_MAP(thisClass)`
               	 `CHAIN_MSG_MAP(baseClass)`
       	 	`END_MSG_MAP()`
};</code></pre>

	* Instantiate an object of the <font color="#ff00ff">CSampleDockingWindow</font> class as a member of the <b>CMainFrame</b>
	* In the <font color="#ff00ff">CMainFrame::OnCreate(...)</font> method, call the Create(...) method of the instantiated docking window class.
		> <pre><code>
LRESULT <b>OnCreate</b>(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, 
                 BOOL& /*bHandled*/)
{
        ...
        <font color="#ff000f"><b>InitializeDockingFrame();</b></font>
        ...
        CRect rcBar(0,0,100,100);
        m_sampleDockWnd.Create(m_hWnd,rcBar,_T("Sample docking window"));
        ...
}
		</code></pre>
		Do not use empty rect even if you dock the window. When window start dragging it use previously stored floating rect size.
4. 	<h2>Add to Generic Window Support for Docking Window Features</h2>
	To implement a window with docking window features, derive a class from <font color="#ff000f"><b>dockwins::CDockingSiteImpl</b></font>. In derived class chain default message map to the base class. </br>
	> <pre><code>
class CDockSiteSampleWnd : public dockwins::CDockingSiteImpl < CDockSiteSampleWnd >
{
        typedef dockwins::CDockingSiteImpl < CDockSiteSampleWnd > baseClass;
public:
        DECLARE_WND_CLASS(_T("CDockSiteSampleWnd"))
        BEGIN_MSG_MAP(CDockSiteSampleWnd)
                CHAIN_MSG_MAP(baseClass)
        END_MSG_MAP()
};
	</code></pre>


5. <h2>Add Support for Tabbed Docking Window</h2>
	* The tabbed docking window depend on [Daniel Bowen's The Codeproject article "Custom Tab Controls,Tabbed Frame and Tabbed MDI"](http://www.codeproject.com/KB/wtl/TabbingFramework.asp), Please download the source code for this article.
	* Change the base class of your docking window from <font color="#ff000f">dockwins::CTitleDockingWindowImpl</font> to <font color="#f000ff"><b>dockwins::CBoxedDockingWindowImpl</b></font>.
	* Use the following classes as traits for the <font color="#f000ff"><b>dockwins::CBoxedDockingWindowImpl</b></font>:
> <pre><code><font color="#ff000f"><b>COutlookLikeBoxedDockingWindowTraits, 
		COutlookLikeExBoxedDockingWindowTraits</b></font> or <font color="#ff000f"><b>
		CVC6LikeBoxedDockingWindowTraits.</b></font>
</code></pre>

	* To add tabbed docking features support to the previous <font color="#ff000f"><b>CSampleDockingWindow</b></font> class, the code should look like this:
	> <pre><code>
		class CSampleTabDockingWindow :
         public dockwins::CBoxedDockingWindowImpl< SampleDockingWindow,
                CWindow, dockwins::COutlookLikeBoxedDockingWindowTraits >
{
        typedef CSampleTabDockingWindow    thisClass;
        typedef dockwins::CBoxedDockingWindowImpl<CSAMPLEDOCKINGWINDOW,
         CWINDOW,
         dockwins::COutlookLikeBoxedDockingWindowTraits>  baseClass;
public:
        DECLARE_WND_CLASS(_T("CSampleTabDockingWindow"))
        BEGIN_MSG_MAP(thisClass)
                CHAIN_MSG_MAP(baseClass)
        END_MSG_MAP()
};
	</code></pre>

6. <H2>Add Support for Auto-Hiding Features</H2>
	* To add auto-hiding features to your project just include a <font color="#ff000f"><b>DWAutoHide.h</b></font> header before any other docking windows headers.

7. <h2>Dock a Docking Window</h2>
	* Call the **DockWindow** methods from your frame window class.
	> <PRE><CODE>
		template< class T >
bool DockWindow(T& dockWnd,CDockingSide side,
                unsigned long nBar,float fPctPos,
                unsigned long nWidth, unsigned long nHeight);
	</CODE><PRE> 

	* dockWnd: Docking window.
	* side
		* Sides of the frame window to dock to	<font color="#ff000f">CDockingSide::sSingle</font> force docking window to occupy the fulll width of the docking bar, combine this style with one of the following:<PRE><CODE>
	<font color="#ff000f">CDockingSide::sRight</font> 	Dock to the right side of the frame window.
	<font color="#ff000f">CDockingSide::sLeft</font> 	Dock to the left side of the frame window.
	<font color="#ff000f">CDockingSide::sTop</font> 	Dock to the top side of the frame window.
	<font color="#ff000f">CDockingSide::sBottom</font> 	Dock to the bottom side of the frame window.
			</CODE></PRE>
	* nBar : Index of dockbar to dock to, it's zero-based.
	* fPctPos: The percent of the dock bar's width that the docking window should use as top point.
	* nWidth: </BR>
		The requested width (in pixels) of the docking window. If the docking window is vertical, this parameter actually represents the control bar height.	
	* nHeight:</BR>
		The requested height (in pixels) of the docking window. If the docking window is vertical, this parameter actually represents the control bar width.

8. <H2>Dock One Tabbed Docking Window to Another</H2>
Call the <FONT color="#ff000f"><b>DockTo</b></font> method of the tabbed docking window.
> bool DockTo(HWND hWnd,int index=0);
> <pre><b>hWnd</b>
	    Tabbed docking window to dock to.
<b>index</b>
	    Zero-based index.</pre>

9. <h2>Float a Docking Window that is Docked</h2>
Call the <FONT color="#ff000f"><b>Float()</b></font> methods from your docking window class.
> bool Float() - restore previous floating position</br>
> `bool Float(LPCRECT pRc, UINT flags=SWP_SHOWWINDOW | SWP_NOACTIVATE,HWND hWndInsertAfter=HWND_TOP)`
> - float docking window and move to a specified location.

10. <h2>Pin-up Docking Window</h2>
Call the one of the <FONT color="#ff000f"><b>PinUp</b></font>  methods of the tabbed docking window.

	`bool PinUp(const CDockingSide& side);`

	`bool PinUp(const CDockingSide& side, unsigned long width, 
    bool bVisualize=false);`

	<b>side:</b><br>
		Sides of the frame window to pin-up to:	
* CDockingSide::sRight Pin-up to the right side of the frame window.
* CDockingSide::sLeft Pin-up to the left side of the frame window.
* CDockingSide::sTop Pin-up to the top side of the frame window.
* CDockingSide::sBottom Pin-up to the bottom side of the frame window.

	<b>width:</b></br>The requested width (in pixels) of the docking window.</br>
	<b>bVisualize</b></br>Specifies the show state of the docking window after pinning.

11. <H2>Unpin Pinned Docking Window</H2>
* Call Hide then Show methods of the pinned window to emulate the pin button press,
* or call Float method to float a pinned docking window,
* or call Hide method then call any functions that set docking window position.

12. <h2>Receive Notifications when the Docked State of a Docking Window Changes</h2>
Override the following member functions of your docking window class

	`void OnDocked(HDOCKBAR hBar,bool bHorizontal)`</br>
	`void OnUndocked(HDOCKBAR hBar)`</br>
	<b>hBar</b> </br>Handle to the dockbar to docking to.

	<b>bHorizontal</b> </br>
	Docking window orientation.


13. <h2>Hide/Show a Docking Window</h2>

* To hide/show a docking window simply call <FONT color="#ff000f"><b>Hide()</b></font>/ <FONT color="#ff000f"><b>Show()</b></font> or <FONT color="#ff000f"><b>Togle()</b></font> methods of the <FONT color="#ff000f"><b>CTitleDockingWindowImpl</b></font> class.

14. <h2>Specify Minimum Docking Window Size</h2>
You can specify minimum docking window size by overriding GetMinMaxInfo method of your docking window, like this:
> <pre><code>
 void GetMinMaxInfo(LPMINMAXINFO pMinMaxInfo) const
  {
     pMinMaxInfo->ptMinTrackSize.y=100;
     pMinMaxInfo->ptMinTrackSize.x=100;
  }
</code></pre>

15. <h2>Preserve Docking Window Position</h2>
You can use following member functions of the <font color="#ff000f"><b>CDockingWindowBaseImpl</b></font> class:
> <pre><code>
bool GetDockingWindowPlacement(DFDOCKPOSEX* pHdr) const
bool SetDockingWindowPlacement(DFDOCKPOSEX* pHdr)
</code></pre>

16. <h2>Replace Splitter Bar</h2>
If you do not like splitter bar you can make your own. If you just want to change it's appearance probably the best way to derive it from <FONT color="#ff000f"><b>CSimpleSplitterBar</b></font>. And override <FONT color="#ff000f"><b>Draw()</b></font>,<FONT color="#ff000f"><b>DrawGhostBar()</b></font> etc. Then define your traits
> <pre><code> 
typedef CDockingFrameTraitsT < CMySplitterBar,
                  WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                  WS_EX_APPWINDOW | WS_EX_WINDOWEDGE >  CMyDockingFrameTraits;
</code></pre>
and apply it to base class of CMainFrame.

17. <h2>Make Custom Caption</h2>
Create a new caption class. You can derive it from <FONT color="#ff000f"><b>CCaptionBase</b></font> or from other available Caption classes. Then define DockingWindowTraits
> <pre><code>
 typedef CDockingWindowTraits< CMyCaption,
                        WS_OVERLAPPEDWINDOW | WS_POPUP | WS_VISIBLE |
                        WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                        WS_EX_TOOLWINDOW > CMyTitleDockingWindowTraits;
</code></pre>
and apply it to <FONT color="#ff000f"><b>CTitleDockingWindowImpl</b></font>.

18. <h2>Docking Window Classes</h2>
- <FONT color="#0000ff"><b>Docking Windows Frame Classes</b></font>
		* <FONT color="#ff000f"><b>CDockingFrameImplBase	[DockingFrame.h] </b></font>— this class provides basic docking window features.
		* <FONT color="#ff000f"><b>CDockingFrameImpl 	[DockingFrame.h] </b></font>— base class for a single document interface (SDI) frame window.
		* <FONT color="#ff000f"><b>CMDIDockingFrameImpl [DockingFrame.h]</b></font> — base class for a multiple document interface (MDI) frame window.
		* <FONT color="#ff000f"><b>CDockingSiteImpl [DockingFrame.h]</b></font> — base class for a generic window with docking window features.
		* <FONT color="#ff000f"><b>CDockingFrameTraitsT [DockMisc.h] </b></font>— traits of docking frame it's derived from CWinTraits class and add TSplitterBar parameter.

- <FONT color="#0000ff"><b>Docking Windows Classes</b></font>
		* <FONT color="#ff000f"><b>CDockingWindowBaseImpl [DockingWindow.h]</b></font> — base class for docking windows. The <FONT color="#ff000f"><b>CDockingWindowBaseImpl</b></font> class derives from <FONT color="#ff000f"><b>CWindowImpl</b></font> and has the same parameters except <FONT color="#ff000f"><b>TWinTraits</b></font>. Instead, it is uses <FONT color="#ff000f"><b>CDockingWindowTraits</b></font>.
		* <FONT color="#ff000f"><b>CTitleDockingWindowImpl [DockingWindow.h]</b></font> — titled docking window.
		* <FONT color="#ff000f"><b>CBoxedDockingWindowImpl [DockingBox.h]</b></font> — titled docking window which support tabbed docking.
		* <FONT color="#ff000f"><b>CDockingWindowTraits [DockingWindow.h]</b></font> — traits of docking window it's derived from <FONT color="#ff000f"><b>CWinTraits</b></font> class and add <FONT color="#ff000f"><b>TCaption</b></font> parameter. If you need to customize the docking window caption, make new caption class and use <FONT color="#ff000f"><b>CDockingWindowTraits</b></font> with new class as <FONT color="#ff000f"><b>TCaption</b></font> parameter. 
- <FONT color="#0000ff"><b>Docking Windows Captions Classes</b></font>
		*  <FONT color="#ff000f"><b>CCaptionBase[DockingWindow.h]</b></font> — base class for other caption class
		*  <FONT color="#ff000f"><b>COutlookLikeExCaption</b></font> and <FONT color="#ff000f"><b>COutlookLikeCaption</b></font> [ExtDockingWindow.h] — Microsoft Outlook™ likes caption.    
			*  <FONT color="#ff000f"><b>COutlookLikeCaption</b></font> — always horizontal caption.
			*  <FONT color="#ff000f"><b>COutlookLikeExCaption</b></font> — orientation of the caption depends on docking position.
		*  <FONT color="#ff000f"><b>CVC6LikeCaption [ExtDockingWindow.h]</b></font> — Microsoft Visual C++ 6™ IDE like caption.

19. <h2>Docking Windows Traits Classes</h2>
* <FONT color="#ff000f"><b>COutlookLikeTitleDockingWindowTraits [ExtDockingWindow.h]</b></font> traits for COutlookLikeCaption, use this class with CTitleDockingWindowImpl
* <FONT color="#ff000f"><b>COutlookLikeExTitleDockingWindowTraits [ExtDockingWindow.h]</b></font> traits for COutlookLikeExCaption, use this class with CTitleDockingWindowImpl
* <FONT color="#ff000f"><b>CVC6LikeTitleDockingWindowTraits [ExtDockingWindow.h]</b></font> traits forCVC6LikeCaption, use this class with CTitleDockingWindowImpl
* <FONT color="#ff000f"><b>COutlookLikeBoxedDockingWindowTraits [TabDockingBox.h]</b></font> traits for COutlookLikeCaption, use this class with CBoxedDockingWindowImpl
* <FONT color="#ff000f"><b>COutlookLikeExBoxedDockingWindowTraits [TabDockingBox.h]</b></font> traits for COutlookLikeExCaption, use this class with CBoxedDockingWindowImpl
* <FONT color="#ff000f"><b>CVC6LikeBoxedDockingWindowTraits[TabDockingBox.h]</b></font> traits for CVC6LikeCaption, use this class with CBoxedDockingWindowImpl

20. <h2>Docking Windows Splitter Bar Classes</h2>

* <FONT color="#ff000f"><b>CSimpleSplitterBar[SimpleSplitterBar.h]</b></font> - Very simple splitter bar.
* <FONT color="#ff000f"><b>CSimpleSplitterBarEx[SimpleSplitterBar.h]</b></font> - another simple splitter bar.

------------
