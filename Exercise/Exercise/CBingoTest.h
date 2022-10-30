#ifndef __BINGO_TEST_H__
#define __BINGO_TEST_H__

#include <vector>
#include <array>

#pragma once

struct tagBingo
{
public:
	tagBingo() 
	{
		Bingo.fill(false);
	}

public:
	void		SetBingoNumber(int Number) {
		Bingo[Number] = true;
	}

	int			GetBingo() const {
		/* *
		0	1	2
		3	4	5
		6	7	8
		*/
		int Cnt = 0;

		if (Bingo[0] && Bingo[1] && Bingo[2]) ++Cnt;
		if (Bingo[0] && Bingo[3] && Bingo[6]) ++Cnt;
		if (Bingo[0] && Bingo[4] && Bingo[8]) ++Cnt;
		if (Bingo[1] && Bingo[4] && Bingo[7]) ++Cnt;
		if (Bingo[3] && Bingo[4] && Bingo[5]) ++Cnt;
		if (Bingo[2] && Bingo[5] && Bingo[8]) ++Cnt;
		if (Bingo[6] && Bingo[7] && Bingo[8]) ++Cnt;
		if (Bingo[2] && Bingo[4] && Bingo[6]) ++Cnt;

		return Cnt;
	}

private:
	std::array<bool, 9>		Bingo;
};


class CBingoTest
{
	
public:
	int		Insert(std::vector<std::vector<int>> data);

private:
	std::vector<std::pair<int, tagBingo>>			DailyBingo;
	std::vector<std::pair<int, tagBingo>>			WeeklyBingo;
	tagBingo										MonthlyBingo;
};

#endif