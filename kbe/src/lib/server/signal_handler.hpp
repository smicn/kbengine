/*
This source file is part of KBEngine
For the latest info, see http://www.kbengine.org/

Copyright (c) 2008-2012 kbegine Software Ltd
Also see acknowledgements in Readme.html

You may use this sample code for anything you like, it is not covered by the
same license as the rest of the engine.
*/
#ifndef __SIGNAL_HANDLER_H__
#define __SIGNAL_HANDLER_H__

// common include
#include "cstdkbe/cstdkbe.hpp"
#include "cstdkbe/tasks.hpp"
#include "cstdkbe/singleton.hpp"
// windows include	
#if KBE_PLATFORM == PLATFORM_WIN32
#else
// linux include
#endif
	
namespace KBEngine{

class SignalHandler
{
public:
	virtual void onHandle(int sigNum) = 0;
};

class SignalHandlers : public Singleton<SignalHandlers>, public Task
{
public:
	SignalHandlers();
	~SignalHandlers();
	
	SignalHandler* addSignal(int sigNum, 
		SignalHandler* pSignalHandler);
	
	SignalHandler* delSignal(int sigNum);
	
	void clear();
	
	void onSignalled(int sigNum);
	
	virtual void process();
private:
	typedef std::map<int, SignalHandler*> SignalHandlerMap;
	SignalHandlerMap singnalHandlerMap_;
	
	std::vector<int> signalledVec_;
};

#define g_kbeSignal SignalHandlers::getSingleton()
}
#endif
