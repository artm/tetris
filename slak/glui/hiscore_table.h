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
