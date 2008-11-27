//
// Process.cpp
//
// $Id$
//
// Library: Foundation
// Package: Processes
// Module:  Process
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "Poco/Process.h"


#if defined(POCO_OS_FAMILY_WINDOWS) && defined(POCO_WIN32_UTF8)
#include "Process_WIN32U.cpp"
#elif defined(POCO_OS_FAMILY_WINDOWS)
#include "Process_WIN32.cpp"
#elif defined(POCO_OS_FAMILY_UNIX)
#include "Process_UNIX.cpp"
#else
#include "Process_VMS.cpp"
#endif


namespace Poco {


//
// ProcessHandle
//
ProcessHandle::ProcessHandle(const ProcessHandle& handle):
	_pImpl(handle._pImpl)
{
	_pImpl->duplicate();
}

	
ProcessHandle::~ProcessHandle()
{
	_pImpl->release();
}


ProcessHandle::ProcessHandle(ProcessHandleImpl* pImpl):
	_pImpl(pImpl)
{
	poco_check_ptr (_pImpl);
}


ProcessHandle& ProcessHandle::operator = (const ProcessHandle& handle)
{
	if (&handle != this)
	{
		_pImpl->release();
		_pImpl = handle._pImpl;
		_pImpl->duplicate();
	}
	return *this;
}

	
ProcessHandle::PID ProcessHandle::id() const
{
	return _pImpl->id();
}

	
int ProcessHandle::wait() const
{
	return _pImpl->wait();
}


//
// Process
//
ProcessHandle Process::launch(const std::string& command, const Args& args)
{
	return ProcessHandle(launchImpl(command, args, 0, 0, 0));
}


ProcessHandle Process::launch(const std::string& command, const Args& args, Pipe* inPipe, Pipe* outPipe, Pipe* errPipe)
{
	poco_assert (inPipe == 0 || inPipe != outPipe && inPipe != errPipe);

	return ProcessHandle(launchImpl(command, args, inPipe, outPipe, errPipe));
}

	
int Process::wait(const ProcessHandle& handle)
{
	return handle.wait();
}


void Process::kill(PID pid)
{
	killImpl(pid);
}


void Process::requestTermination(PID pid)
{
	requestTerminationImpl(pid);
}


} // namespace Poco
