// ���ø����̼� �ش�

#include "CCXApplication.h"
#include "CCXEGLView.h"

class  AppDelegate  :  public cocos2d::CCXApplication{
public:
	AppDelegate();
	~AppDelegate();

	virtual bool    applicationDidFinishLaunching();
    virtual void    applicationDidEnterBackground();
    virtual void    applicationWillEnterForeground();

protected:
    cocos2d::CCXEGLView *   m_pMainWnd;
};