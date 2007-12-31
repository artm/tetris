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

#ifndef slak_glui_hiscore_table_h
#define slak_glui_hiscore_table_h

#include <boost/filesystem/path.hpp>

#include <cstddef>
#include <string>
#include <vector>
#include <iostream>

namespace slak {
	namespace glui {
		struct HiScoreTable {
			struct Record {
				std::string name;
				int score;
				int cursor;
				Record(int s=0) : name("...."), score(s), cursor(0) {}
				bool operator<(const Record& other) const { return score<other.score; }
				void println(std::ostream& os) { os << name << "\n" << score << "\n"; }
				void readln(std::istream& is) { is >> name; is >> score; }
			};

			std::vector<Record> records;
			Record * last_record;
			boost::filesystem::path path;

			HiScoreTable(int i) : records(i),last_record(NULL) {}
			void insertRecord(int score);
			void save();
			void load(boost::filesystem::path path);
		};
	}
}

#endif
