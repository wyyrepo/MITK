//
// OptionProcessor.cpp
//
// $Id$
//
// Library: Util
// Package: Options
// Module:  OptionProcessor
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


#include "Poco/Util/OptionProcessor.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionException.h"


namespace Poco {
namespace Util {


OptionProcessor::OptionProcessor(const OptionSet& options): 
	_options(options),
	_unixStyle(true),
	_ignore(false)
{
}


OptionProcessor::~OptionProcessor()
{
}


void OptionProcessor::setUnixStyle(bool flag)
{
	_unixStyle = flag;
}


bool OptionProcessor::process(const std::string& argument, std::string& optionName, std::string& optionArg)
{
	if (!_ignore)
	{
		if (_unixStyle)
			return processUnix(argument, optionName, optionArg);
		else
			return processDefault(argument, optionName, optionArg);
	}
	return false;
}


void OptionProcessor::checkRequired() const
{
	for (OptionSet::Iterator it = _options.begin(); it != _options.end(); ++it)
	{
		if (it->required() && _specifiedOptions.find(it->fullName()) == _specifiedOptions.end())
			throw MissingOptionException(it->fullName());
	}
}


bool OptionProcessor::processUnix(const std::string& argument, std::string& optionName, std::string& optionArg)
{
	std::string::const_iterator it  = argument.begin();
	std::string::const_iterator end = argument.end();
	if (it != end)
	{
		if (*it == '-')
		{
			++it;
			if (it != end)
			{
				if (*it == '-')
				{
					++it;
					if (it == end)
					{
						_ignore = true;
						return true;
					}
					else return processCommon(std::string(it, end), false, optionName, optionArg);
				}
				else return processCommon(std::string(it, end), true, optionName, optionArg);
			}
		}
	}
	return false;
}


bool OptionProcessor::processDefault(const std::string& argument, std::string& optionName, std::string& optionArg)
{
	std::string::const_iterator it  = argument.begin();
	std::string::const_iterator end = argument.end();
	if (it != end)
	{
		if (*it == '/')
		{
			++it;
			return processCommon(std::string(it, end), false, optionName, optionArg);
		}
	}
	return false;
}


bool OptionProcessor::processCommon(const std::string& optionStr, bool isShort, std::string& optionName, std::string& optionArg)
{
	if (optionStr.empty()) throw EmptyOptionException();
	const Option& option = _options.getOption(optionStr, isShort);
	const std::string& group = option.group();
	if (!group.empty())
	{
		if (_groups.find(group) != _groups.end())
			throw IncompatibleOptionsException(option.fullName());
		else
			_groups.insert(group);
	}
	if (_specifiedOptions.find(option.fullName()) != _specifiedOptions.end() && !option.repeatable())
		throw DuplicateOptionException(option.fullName());
	_specifiedOptions.insert(option.fullName());
	option.process(optionStr, optionArg);
	optionName = option.fullName();
	return true;
}


} } // namespace Poco::Util
