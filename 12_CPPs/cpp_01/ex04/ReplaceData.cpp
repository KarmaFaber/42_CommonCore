/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReplaceData.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 11:09:33 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/04 09:23:50 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReplaceData.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/

ReplaceData::ReplaceData(const std::string& filename,
				 const std::string& s1,
				 const std::string& s2)
		: _filename(filename), _s1(s1), _s2(s2)
{
	_replaced_filename = _filename + ".replace";
}

ReplaceData::~ReplaceData() {}

/******************************************************************************/
/*								GETTERS										  */
/******************************************************************************/

const std::ifstream& ReplaceData::getIfs( void ) const
{
	return (_ifs);
}

const std::ofstream& ReplaceData::getOfs( void ) const
{
	return (_ofs);
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

bool ReplaceData::openStreams()
{
	_ifs.open(_filename.c_str(), std::ifstream::in);
	if (!_ifs.is_open())
	{
		showMsg(CRED,"Error opening file.", CRESET);
		return (false);
	}
	_ofs.open(_replaced_filename.c_str(), std::ofstream::out | std::ofstream::trunc);
	if (!_ofs.is_open())
	{
		_ifs.close();
		showMsg(CRED,"Error opening file.", CRESET);
		return (false);
	}
	return (true);
}

void ReplaceData::relpaceBuffer()
{
	size_t pos;
	
	pos = 0;
	if (_s1.empty())
		return ;
	while (pos != std::string::npos)
	{
		pos = _buffer.find(_s1.c_str(), 0, _s1.length());
		if (pos == std::string::npos)
			break ;
		_buffer.erase(pos, _s1.length());
		if (!_s2.empty())
			_buffer.insert(pos, _s2);
	}
}

bool ReplaceData::copyContent()
{
	while (std::getline(_ifs, _buffer))
	{
		if (_ifs.fail())
			return false;
		relpaceBuffer();
		_ofs << _buffer;
		if (!_ifs.eof())
			_ofs << std::endl;
	}
	return true;
}

void ReplaceData::closeStreams()
{
	if (_ifs.is_open())
		_ifs.close();
	if (_ofs.is_open())
		_ofs.close();
}

bool ReplaceData::replaceFile()
{
	if (!openStreams())
		return (false);
	if (!copyContent())
	{
		closeStreams();
		return (false);
	}
	closeStreams();
	return (true);
}

void ReplaceData::showMsg(std::string color,std::string msg, std::string end_color)const
{
	std::cerr << color << msg << end_color << std::endl;
}
