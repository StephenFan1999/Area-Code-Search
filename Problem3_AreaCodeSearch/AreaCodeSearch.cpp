////////////////////////////////////////////////////////////////////////////////
//
// Problem #3: Improve Area Code Search program.
//
// Linux & Mac OS X:
//
// Build: g++ AreaCodeSearch.cpp -std=c++11 -o AreaCodeSearch
// Run: ./AreaCodeSearch
//
// Windows:
//
// Create a C++ Solution & Console Project. Add this AreaCodeSearch.cpp into the
// project.
//
// Description:
//
// 1) AreaCodeSearch::search() function should return the full name of a state,
// given an area code;
//
// 2) AreaCodeSearch::search() function complexity best/worst/average should be
// constant, Big-O(1);
//
// 3) Try not to let the data container holding the "hash-table" to store std::string
// object for each area code - this is too much in memory consumption. It is
// recommended to use something more efficient.
//
// Please remove/replace/re-work the "badImpl_" with your better implementation.
//
////////////////////////////////////////////////////////////////////////////////
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class AreaCodeSearch 
{
public:
	//
	// Replace with your better solution here...
	//
	void addAreaCode(int areaCode, std::string state)
	{
		badImpl_[ areaCode ] = state;
	}

	//
	// Replace with your better solution here...
	//
	std::string search(int areaCode)
	{
		auto found = badImpl_.find(areaCode);
		if( found != badImpl_.end() )
		{
			return found->second;
		}
		return "NA";
	}

	//
	// Modify if needed but do not remove or change function signature
	//
	bool load(const char* acFile)
	{
		std::ifstream fin(acFile);
		if(!fin)
		{
			std::cerr << "Failed to open: " << acFile << std::endl;
			return false;
		}
		std::string line;
		while(std::getline(fin,line))
		{
			if(line.empty())
				continue;
			auto nameAreaCodes = split(line, '\t');
			std::string stateFullName = nameAreaCodes[0];
			auto areaCodes = split(nameAreaCodes[1], ',');
			for(int i = 0; i < areaCodes.size(); ++i)
			{
				auto code = areaCodes[i];
				auto num = atoi(code.c_str());
				addAreaCode(num, stateFullName);
			}
		}
		return true;
	}

	// Helper member used by load() - do not modify
	std::vector<std::string> split(std::string text, char delimiter)
	{
		std::vector<std::string> tokens;
		std::istringstream f(text);
		std::string s;
		while(std::getline(f, s, delimiter))
			tokens.push_back(s);
		return tokens;
	}

	//
	// Hint:
	// 1) Use state abbreviations in two capital letters;
	// 2) When implementing approach #1, you will need to load a mapping
	// between a state's full name and its abbreviation.
	//
	void addAbbrState(std::string abbr, std::string full)
	{
	}

	//std::vector<char[2]>		areaCodeToAbbr_;
	//std::vector<std::string>	abbrToFull_;
	std::unordered_map<int,std::string> badImpl_; // You solution should have a better memory usage than this!
};

//
// Helper functions
//

//
// Test suite
//

#define CHECK_PRINT(x,y) {if(x==y) std::cout << "Passed: " << __FUNCTION__ << std::endl; else {std::cout << "Failed: " << __FUNCTION__ << std::endl; exit(-1);}}
#define CHECK_PRINT_NOT_EQ(x,y) {if(x!=y) std::cout << "Passed: " << __FUNCTION__ << std::endl; else {std::cout << "Failed: " << __FUNCTION__ << std::endl; exit(-1);}}

void testMock()
{
	AreaCodeSearch dictionary;
	dictionary.addAreaCode(123, "Hello");
	dictionary.addAreaCode(124, "Yahoo");
	dictionary.addAreaCode(125, "Howdy");
	CHECK_PRINT( dictionary.search(123), "Hello" );
	CHECK_PRINT( dictionary.search(124), "Yahoo" );
	CHECK_PRINT( dictionary.search(125), "Howdy" );
	CHECK_PRINT( dictionary.search(126), "NA" );
}

void testIL()
{
	AreaCodeSearch dictionary;
	bool result = dictionary.load("AreaCode.txt");
	CHECK_PRINT( result, true );
	CHECK_PRINT( dictionary.search(312), "Illinois" );
	CHECK_PRINT( dictionary.search(630), "Illinois" );
	CHECK_PRINT( dictionary.search(847), "Illinois" );
}

void testALL();

int main()
{
	testMock();
	testIL();
	testALL();
	return 0;
}

void testALL()
{
	AreaCodeSearch dictionary;
	const char* acFile = "AreaCode.txt";
	bool result = dictionary.load(acFile);
	CHECK_PRINT( result, true );

	std::ifstream fin(acFile);
	if(!fin)
	{
		std::cerr << "Failed to open: " << acFile << std::endl;
		return;
	}
	std::string line;
	while(std::getline(fin,line))
	{
		if(line.empty())
			continue;
		auto nameAreaCodes = dictionary.split(line, '\t');
		std::string stateFullName = nameAreaCodes[0];
		auto areaCodes = dictionary.split(nameAreaCodes[1], ',');
		for(int i = 0; i < areaCodes.size(); ++i)
		{
			auto code = areaCodes[i];
			auto num = atoi(code.c_str());
			CHECK_PRINT( dictionary.search(num), stateFullName);
		}
	}
}
