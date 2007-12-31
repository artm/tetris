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

