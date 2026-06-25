#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <chrono>
#include <ctime>  
#include <string>
#include <iostream>

///////////////////////////////////////////////////////////////////////////
/////////////////////     DateTime Utility Library     ////////////////////
///////////////////////////////////////////////////////////////////////////

/*stDate                    IsDate1BeforeDate2
IsLeapYear                  NumberOfDaysInMonth
IsLastDayInMonth            IsLastMonthInYear
IncreaseDateByOneDay        GetDifferenceInDays                 
GetSystemDate				ReadFullDate
DayOfWeekOrder				IsItEndOfWeek
IsWeekEnd					IsBusinessDay
*/

namespace MyTimeUtilsLib
{
	struct stDate
	{
		short Year;
		short Month;
		short Day;
	};

	bool IsDate1BeforeDate2(stDate Date1, stDate Date2)
	{
		return (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ?
			(Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
	}

	bool IsLeapYear(short Year)
	{
		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
	}

	short NumberOfDaysInMonth(short Year, short Month)
	{
		if (Month < 1 || Month > 12)
			return 0;

		int NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];
	}

	bool IsLastDayInMonth(stDate Date)
	{
		return (Date.Day == NumberOfDaysInMonth(Date.Year, Date.Month)) ? true : false;
	}

	bool IsLastMonthInYear(short Month)
	{
		return (Month == 12);
	}

	stDate IncreaseDateByOneDay(stDate Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date.Month))
			{
				Date.Month = 1;
				Date.Day = 1;
				Date.Year++;
			}
			else
			{
				Date.Day = 1;
				Date.Month++;
			}

		}
		else
		{
			Date.Day++;
		}
		return Date;
	}

	int GetDifferenceInDays(stDate Date1, stDate Date2, bool IncludeEndDay = false)
	{
		int Days = 0;
		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = IncreaseDateByOneDay(Date1);

		}

		return IncludeEndDay ? ++Days : Days;
	}

	stDate GetSystemDate()
	{
		stDate Date;
		time_t t = time(0); // get time now
		tm* now = localtime(&t);
		Date.Year = now->tm_year + 1900;
		Date.Month = now->tm_mon + 1;
		Date.Day = now->tm_mday;

		return Date;
	}

	short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a, y, m, d;
		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + 12 * a - 2;
		// Gregorian:
		//0:sun, 1:Mon, 2:Tue...etc
		d = (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

		return d;
	}

	short DayOfWeekOrder(stDate Date)
	{
		return DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
	}

	short DaysUntilTheEndOfWeek(stDate Date)
	{
		return 6 - DayOfWeekOrder(Date);
	}

	short DaysUntilTheEndOfMonth(stDate Date)
	{
		stDate EndOfMonthDate;
		EndOfMonthDate.Day = NumberOfDaysInMonth(Date.Month, Date.Year);
		EndOfMonthDate.Month = Date.Month;
		EndOfMonthDate.Year = Date.Year;

		return GetDifferenceInDays(Date, EndOfMonthDate, true);
	}

	short DaysUntilTheEndOfYear(stDate Date)
	{
		stDate EndOfYearDate;
		EndOfYearDate.Day = 31;
		EndOfYearDate.Month = 12;
		EndOfYearDate.Year = Date.Year;

		return GetDifferenceInDays(Date, EndOfYearDate, true);
	}

	short CalculateVacationDays(stDate DateForm, stDate Date2)
	{
		short DaysCount = 0;
		while (IsDate1BeforeDate2(DateForm, Date2))
		{
			if (IsBusinessDay(DateForm))
				DaysCount++;

			DateForm = IncreaseDateByOneDay(DateForm);
		}
		return DaysCount;
	}

	bool IsItEndOfWeek(stDate  Date)
	{
		return DayOfWeekOrder(Date) == 6;
	}

	bool IsWeekEnd(stDate Date)
	{
		//Weekends are Fri and Sat
		short DayIndex = DayOfWeekOrder(Date);
		return (DayIndex == 5 || DayIndex == 6);
	}

	bool IsBusinessDay(stDate Date)
	{
		//Weekends are Sun,Mon,Tue,Wed and Thur
	/* short DayIndex = DayOfWeekOrder(Date);
	return (DayIndex >= 5 && DayIndex <= 4);
	*/
	//shorter method is to invert the IsWeekEnd: this will save updating code.
		return !IsWeekEnd(Date);
	}

//A set of functions for manipulating dates by incrementing them (day, week, month, year, decade, century, millennium)
// while properly handling month/year transitions and ensuring the day stays valid within each month.

	stDate IncreaseDateByOneDay(stDate Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date.Month))
			{
				Date.Month = 1;
				Date.Day = 1;
				Date.Year++;
			}
			else
			{
				Date.Day = 1;
				Date.Month++;
			}

		}
		else
		{
			Date.Day++;
		}
		return Date;
	}

	stDate IncreaseDateByXDays(short Days, stDate Date)
	{
		for (int i = 1; i <= Days; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}

	stDate IncreaseDateByOneWeek(stDate Date)
	{
		for (int i = 0; i < 7; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}

	stDate IncreaseDateByXWeeks(short Weeks, stDate Date)
	{
		for (int i = 1; i <= Weeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}

	stDate IncreaseDateByOneMonth(stDate Date)
	{
		if (Date.Month == 12)
		{
			Date.Month = 1;
			Date.Year++;

		}
		else
		{
			Date.Month++;
		}
		//last check day in date should not exceed max days in thecurrent month
		// example if date is 31/1/2022 increasing one month should not be 31 / 2 / 2022, it should
		// be 28/2/2022

		short NumberOfDayInCurrentMonth = NumberOfDaysInMonth(Date.Year, Date.Month);
		if (Date.Day > NumberOfDayInCurrentMonth)
		{
			Date.Day = NumberOfDayInCurrentMonth;
		}

		return Date;
	}

	stDate IncreaseDateByXMonths(short Months, stDate Date)
	{
		for (int i = 1; i <= Months; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}

	stDate IncreaseDateByOneYear(stDate Date)
	{
		Date.Year++;
		return Date;
	}

	stDate IncreaseDateByXYears(short Years, stDate Date)
	{
		for (int i = 1; i <= Years; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}
		return Date;
	}

	stDate IncreaseDateByXYearsFaster(short Years, stDate Date)
	{
		Date.Year += Years;
		return Date;
	}

	stDate IncreaseDateByOneDecade(stDate Date)
	{
		Date.Year += 10;
		return Date;
	}

	stDate IncreaseDateByXDecades(short Decade, stDate Date)
	{
		for (int i = 1; i <= Decade * 10; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}
		return Date;
	}

	stDate IncreaseDateByXDecadesFaster(short Decade, stDate Date)
	{
		Date.Year += Decade * 10;
		return Date;
	}

	stDate IncreaseDateByOneCentury(stDate Date)
	{
		//Period of 1000 years
		Date.Year += 100;
		return Date;
	}

	stDate IncreaseDateByOneMillennium(stDate Date)
	{
		//Period of 1000 years
		Date.Year += 1000;
		return Date;
	}

	//A set of functions for decrementing dates(day, week, month, year, decade, century, millennium) 
	// while correctly handling month / year boundaries and adjusting the day to the valid number of
	// days in the target month.

	stDate DecreaseDateByOneDay(stDate Date)
	{
		if (Date.Day == 1)
		{
			if (Date.Month == 1)
			{
				Date.Month = 12;
				Date.Day = 31;
				Date.Year--;
			}
			else
			{
				Date.Month--;
				Date.Day = NumberOfDaysInMonth(Date.Year, Date.Month);
			}
		}
		else
		{
			Date.Day--;
		}
		return Date;
	}

	stDate DecreaseDateByXDays(short Days, stDate Date)
	{
		for (int i = 1; i <= Days; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	stDate DecreaseDateByOneWeek(stDate Date)
	{
		for (int i = 0; i < 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	stDate DecreaseDateByXWeeks(short Weeks, stDate Date)
	{
		for (int i = 1; i <= Weeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}

	stDate DecreaseDateByOneMonth(stDate Date)
	{
		if (Date.Month == 1)
		{
			Date.Month = 12;
			Date.Year--;
		}
		else
		{
			Date.Month--;
		}

		short NumberOfDayInCurrentMonth = NumberOfDaysInMonth(Date.Year, Date.Month);

		if (Date.Day > NumberOfDayInCurrentMonth)
		{
			Date.Day = NumberOfDayInCurrentMonth;
		}
		return Date;

	}

	stDate DecreaseDateByXMonth(short Months, stDate Date)
	{
		for (int i = 1; i <= Months; i++)
		{
			Date = DecreaseDateByOneMonth(Date);

		}
		return Date;
	}

	stDate DecreaseDateByOneYear(stDate Date)
	{
		Date.Year--;
		return Date;
	}

	stDate DecreaseDateByXYears(short Years, stDate Date)
	{
		for (int i = 1; i <= Years; i++)
		{
			Date = DecreaseDateByOneYear(Date);
		}
		return Date;
	}

	stDate DecreaseDateByXYearsFaster(short Years, stDate Date)
	{
		Date.Year -= Years;
		return Date;
	}

	stDate DecreaseDateByOneDecades(stDate Date)
	{
		Date.Year -= 10;
		return Date;
	}

	stDate DecreaseDateByXDecades(short Decades, stDate Date)
	{
		for (int i = 1; i <= Decades; i++)
		{
			Date = DecreaseDateByOneDecades(Date);
		}
		return Date;
	}

	stDate IncreaseDateByXDecadesFaster(short Decade, stDate Date)
	{
		Date.Year -= Decade * 10;
		return Date;
	}

	stDate IncreaseDateByOneCentury(stDate Date)
	{
		Date.Year -= 100;
		return Date;
	}

	stDate IncreaseDateByOneMillennium(stDate Date)
	{
		Date.Year -= 1000;
		return Date;
	}


}