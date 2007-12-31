/*
 * slak-games: simple SDL+OpenGL based games
 * Copyright (C) 2006-2008 Artem Baguinski <femistofel@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "boost/filesystem/fstream.hpp"
#include "hiscore_table.h"

namespace fs = boost::filesystem;
using namespace slak::glui;

void HiScoreTable::load(boost::filesystem::path path)
{
	this->path = path;
	fs::ifstream f(path);
	if (!f) return;
	std::vector<Record>::iterator i;
	for(i = records.begin(); i != records.end(); i++)
		(*i).readln(f);
}

void HiScoreTable::save()
{
	fs::ofstream f(path);
	if (!f) return;
	std::vector<Record>::iterator i;
	for(i = records.begin(); i != records.end(); i++)
		(*i).println(f);
}

void HiScoreTable::insertRecord(int score)
{
	Record r(score);
	std::vector<Record>::iterator where =
		std::lower_bound(records.begin(), records.end(), r,
				 std::not2(std::less<Record>()));
	if (where != records.end()) {
		where = records.insert(where,r);
		records.pop_back();
		last_record = &(*where);
	} else
		last_record = NULL;
}

