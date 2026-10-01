/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReplaceData.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 11:09:37 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/16 08:46:30 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLACEDATA_HPP
# define REPLACEDATA_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>

# define CRED			"\033[0;31m"
# define CRESET			"\033[0m"

class ReplaceData{
	private:
		std::string		_filename;
		std::string		_s1;
		std::string		_s2;
		std::string		_replaced_filename;
		std::string		_buffer;
		std::ifstream	_ifs;
		std::ofstream	_ofs;

	public:
		ReplaceData(const std::string& filename,
					const std::string& s1,
					const std::string& s2);
		~ReplaceData();

		const			std::ifstream& getIfs (void) const;
		const			std::ofstream& getOfs (void) const;

		bool			openStreams();
		void			relpaceBuffer();
		bool			copyContent();
		void			closeStreams();
		bool			replaceFile();
		void			showMsg(std::string color,std::string msg, std::string end_color)const;
};

#endif
