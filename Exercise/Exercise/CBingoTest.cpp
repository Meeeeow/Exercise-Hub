#include "CBingoTest.h"
#include <algorithm>

class CDateFinder {
public:
	CDateFinder(int x) 
		: date(x)
	{
	}

	template<typename T>
	bool operator()(T& Pair) {
		return (Pair.first == date) ? true : false;
	}
private:
	int date = 0;
};


int CBingoTest::Insert(std::vector<std::vector<int>> data)
{
	int answer = 0;

	for (auto& values : data) {
		auto date = values[0];
		auto missions = values[1];

		if (missions >= 1 && missions <= 9) {

			auto iter = std::find_if(DailyBingo.begin(), DailyBingo.end(), CDateFinder(date));

			if (iter != DailyBingo.end()) {
				iter->second.SetBingoNumber(missions - 1);
			}
			else {
				tagBingo tmp;
				tmp.SetBingoNumber(missions - 1);
				DailyBingo.push_back(std::make_pair(date, tmp));
			}
		}
		else if (missions >= 10 && missions <= 18) {

			auto iter = std::find_if(WeeklyBingo.begin(), WeeklyBingo.end(), CDateFinder(date / 7));

			if (iter != WeeklyBingo.end()) {
				iter->second.SetBingoNumber((missions - 10));
			}
			else {
				tagBingo tmp;
				tmp.SetBingoNumber(missions - 10);
				WeeklyBingo.push_back(std::make_pair(date / 7, tmp));
			}
		}
		else {
			MonthlyBingo.SetBingoNumber(missions - 19);
		}
	}

	for (auto& daily : DailyBingo) {
		answer += daily.second.GetBingo();
	}
	for (auto& weekly : WeeklyBingo) {
		answer += weekly.second.GetBingo();
	}
	answer += MonthlyBingo.GetBingo();

	return answer;
}
