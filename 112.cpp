#include <iostream>
#include <string>
#include <set>
using namespace std;
bool m31, m30, february;
bool subY, subM, subD, subH, subMin, subS;//для условия цикла
bool delY, delM, delD, delH, delMin, delS;// для избежания двойного вычитания
bool specialYears; /*флаг для учета високосного года*/
string sh, ss, sm,smh,sd; /*сюда пишутся строчкой нули (корректный вывод времени)*/
string era, infa;
bool isOurEra = 0;
set <int> M31 = { 1,3,5,7,8,10,12 };
set <int> M30 = { 4,6,9,11 };
class Date
{
public:
	int year = 1960;
	int month, day, hour, minute, second;
	Date()
	{
		year = 1960;
		isOurEra = 1;
		month = 1;
		day = 1;
		hour = 0;
		minute = 0;
		second = 0;
		
	};
	Date(int y, int mnth, int d, int h, int m, int s)
	{
		if (y >= 0)
			isOurEra = 1;
		else
			isOurEra = 0;
		year = y;
		month = mnth;
		day = d;
		hour = h;
		minute = m; 
		second = s;
		convert(*this);
		flagOut(*this);
		
	}
	static void spyears(int year)
	{
		if ((year % 4 == 0 && year % 100 != 0) or (year % 400 == 0)) 
			specialYears = 1;
		else 
			specialYears = 0;
		
	}
	void subFlagDefault()
	{
		subY = subM = subD = subH = subMin = subS = delY = delM = delD = delH = delMin = delS = 0;
	}

	static Date flagSet(Date d)
	{// подумать над обратной конвертацией, мб сшить их в одну конвертацию
		 if (M31.find(d.month) != M31.end())
			 m31 = 1;
		 else if (M30.find(d.month) != M30.end())
			 m30 = 1;
		 else
			 february = 1;
		 return (d);
		 spyears(d.year);
	} 
	static void flagOut(Date d)
	{
			if (d.hour < 10)
				sh = "0";
			else sh = "";
			
			if (d.minute < 10)
				sm = "0";
			else sm = "";
		
			if (d.second < 10)
				ss = "0";		
			else ss = "";
			
			if (d.day < 10) 
				sd = "0";
			else sd = "";
			
			if (d.month < 10) 
				smh = "0";
			else smh = "";
			if (d.year > 0)
				isOurEra = true;
			else
				isOurEra = false;

	};
	friend ostream& operator<<(ostream& os, const Date& d) {
		flagOut(d);
		if (d.year < 0) 
			isOurEra = 0;
		else
			isOurEra = 1;
			if ((d.day <= 0) || (d.month <= 0))
				infa = "Дата некорректная, но подойдет для прибавления к какой-либо: ";
			else
				infa = "Дата корректна: ";
			if (isOurEra == true)
				era = "нашей эры";
			else
				era = "до нашей эры";
			return os << infa << endl << "Дата: " << sd << d.day << '.' << smh << d.month << '.' << abs(d.year) << endl
				<< "время: " << sh << d.hour << ":" << sm << d.minute << ":" << ss << d.second << endl
				<< era << endl;

	}
	void convert(Date d) {
		while ((second >= 60) && (minute >= 60) && (hour >= 24))
		{
			if (second >= 60)
			{
				second -= 60;
				minute++;
			}
			if (minute >= 60)
			{
				minute -= 60;
				hour++;
			}
			if (hour >= 24)
			{
				hour -= 24;
				day++;
			}
			flagSet(d);
		}
		flagOut(d);
		while ((m31 == 1 && day > 31) || (m30 == 1 && day > 30) || (february == 1 && day > 28 && specialYears == 0) || (february == 1 && day > 29 && specialYears == 1) || (month > 12))
		{
			if (m31 == 1 && day > 31)
			{
				month++;
				day -= 31;
			}
			if (m30 == 1 && day > 30)
			{
				month++;
				day -= 30;
			}
			if (february == 1 && day > 28 && specialYears == 0)
			{
				month++;
				day -= 28;
			}
			else if (february == 1 && day > 29 && specialYears == 1)
			{
				month++;
				day -= 29;
			}
			if (month > 12)
			{
				year++;
				month -= 12;
			}
			flagSet(d);
		}
		if (day <= 0) // я хз че с этим делать
			day = 1;
		if (month <= 0)
			month = 1;

		flagOut(d);

	}
	Date add(int year1, int month1, int day1, int  hour1, int minute1, int second1)
	{
		Date result(1, 1, 1, 0, 0, 0);
		Date adler(year1, month1, day1, hour1, minute1, second1);
		result = *this + adler;

		convert(result);// и тут
		flagOut(result);// и тут
		return result;
	}
	Date subtract(int year1, int month1, int day1, int  hour1, int minute1, int second1)
	{
		Date result(1,1,0,0,0,0);
		Date deleter(year1, month1, day1, hour1, minute1, second1);
		convert(deleter);

		if (deleter == *this)
		{
			Date happi(1, 1, 1, 0, 0, 0);
			result = happi;
		}
		else
		{
			while (subY && subM && subD && subH && subMin && subS)
			{   ////////////////////////////////// YEARS //////////////////////////////////  
				if (subY == 0) {
					if (result.year == 0)
					{
						result.year = -1;
					}
					else if ((this->year - deleter.year) == 0 && this->year > 0 && delY==0) 
					{
						result.year = -1;
						delY = 1;
					}
					else if ((this->year - deleter.year) == 0 && this->year < 0 && delY == 0)
					{
						result.year = 1;
						delY = 1;
					}
					if (delY == 0)
					{
						if (this->year > deleter.year && this->year > 0)
						{
							result.year = this->year - deleter.year;
							isOurEra = 1;
						}
						else if (this->year > deleter.year && this->year < 0)
						{
							result.year = this->year - deleter.year;
							isOurEra = 1;
						}
						else if (this->year < deleter.year && this->year > 0)
						{
							result.year = this->year - deleter.year;
							isOurEra = 0;
						}
						else if (this->year < deleter.year && this->year < 0)
						{
							result.year = this->year - deleter.year;
							isOurEra = 0;
						}
						delY = 1;
					}
					spyears(result.year);
					subY = 1;
				}
				////////////////////////////////// MONTHS ////////////////////////////////// 
				else if (subM == 0)
				{
					if (result.month == 0)
					{
						result.year--;
						result.month = 12;
						result.day += 31;
						subY = 0;
					}
					else if ((this->month - deleter.month) == 0)
					{
						result.year--;
						result.month = 12;
						result.day += 31;
						subY = 0;
						delM == 1;
					}


					if (delM == 0)
					{
						if (this->month < deleter.month)
						{
							result.year--;
							result.month = (12 - deleter.month) + this->month;
							subY = 0;
						}
						else if (this->month > deleter.month)
							result.month = this->month - deleter.month;
						convert(result);
						delM = 1;
					}
					subM = 1;
				}
				//////////////////////////////////    DAY   ////////////////////////////////// 
				else if (subD == 0) {
					if (result.month == 1)
					{
						result.year--;
						result.month = 12;
						subY = 0;
						if (result.day == 0 ) 
							result.day = 31;
						else if (this->day - deleter.day == 0)
						{
							result.day = 31;
							delD = 1;
						}

						else if (this->day < deleter.day && delD == 0)
						{
							result.day = (31 - deleter.month) + this->day;
							delD = 1;
						}

					}
					else if ((M31.find((result.month) - 1) != M31.end()) && result.month != 1)
					{
						result.month--;
						subM = 0;
						if (result.day == 0) 
							result.day = 31;
						else if (this->day - deleter.day == 0 && delD == 0)
						{
							result.day = 31;
							delD = 1;
						}
						else if (this->day < deleter.day && delD == 0)
						{
							result.day = (31 - deleter.month) + this->day;
							delD = 1;
						}
					}
					else if ((M30.find((result.month) - 1) != M30.end()))
					{
						result.month--;
						subM = 0;
						if (result.day == 0) 
							result.day = 30;
						else if (this->day - deleter.day == 0 && delD == 0)
						{
							result.day = 30;
							delD = 1;
						}
						else if (this->day < deleter.day && delD == 0)
						{
							result.day = (30 - deleter.day) + this->day;
							delD = 1;
						}
					}
					else if ((result.month == 3) && specialYears == 0)
					{
						result.month--;
						subM = 0;
						if (result.day == 0) 
							result.day = 28;
						else if (this->day - deleter.day == 0 && delD == 0)
						{
							result.day = 28;
							delD = 1;
						}
						else if (this->day < deleter.day && delD == 0)
						{
							result.day = (28 - deleter.day) + this->day;
							delD = 1;
						}

					}
					else if ((result.month == 3) && specialYears == 1)
					{
						result.month--;
						subM = 0;
						if (result.day == 0)
							result.day = 29;
						else if (this->day - deleter.day == 0 && delD == 0)
						{
							result.day = 29;
							delD = 1;
						}
						else if (this->day < deleter.day && delD == 0)
						{
							result.day = (29 - deleter.day) + this->day;
							delD = 1;
						}
					}
					else if (this->day > deleter.day && delD == 0)
					{
						result.day = this->day - deleter.day;//here
						delD = 1;
					}
					convert(result);
					subD = 1;
				}
				////////////////////////////////// HOURS ////////////////////////////////// 
				else if (subH == 0) {
					if (result.hour == -1)
					{
						result.day--;
						result.hour = 23;
						subD = 0;

					}
					else if (result.hour == 0) 
					{
						result.day--;
						result.hour = 24;
						subD = 0;
					}
					else if (this->hour - deleter.hour == 0 && delH == 0)
					{
						result.day--;
						result.hour = 24;
						subD = 0;
						delH = 1;
					}
					else if (this->hour < deleter.hour && delH == 0)
					{
						result.day--;
						result.hour = (24 - deleter.hour) + this->hour;
						subD = 0;
						delH = 1;
					}
					else if (this->hour < deleter.hour && delH == 0)
					{
						result.hour = result.hour - deleter.hour;
						delH = 1;
					}
					convert(result);
					subH = 1;
				}
				////////////////////////////////// MINUTE ////////////////////////////////// 
				else if (subMin == 0) {
					if (result.minute == -1)
					{
						result.hour--;
						subH = 0;
						result.minute = 59;

					}
					else if (result.minute == 0) 
					{
						result.hour--;
						subH = 0;
						result.minute = 60;
					}
					else if (this->minute - deleter.minute == 0 && delMin == 0)
					{
						result.hour--;
						subH = 0;
						result.minute = 60;
						delMin = 1;
					}
					else if (this->minute < deleter.minute && delMin == 0)
					{
						result.hour--;
						subH = 0;
						result.minute = (60 - deleter.minute) + this->minute;
						delMin = 1;
					}
					else if (this->minute > deleter.minute && delMin == 0)
					{
						result.minute =this->minute - deleter.minute;
						delMin = 1;
					}
					convert(result);
					subMin = 1;
				}
				//////////////////////////////////  SECOND ////////////////////////////////// 
				else if (subS == 0)
				{
					if (result.second == 0 )
					{
						result.minute--;
						subMin = 0;
						result.second = 60;
					}
					else if (this->second - deleter.second == 0 && delS == 0)
					{
						result.minute--;
						subMin = 0;
						result.second = 60;
						delS = 1;
					}
					else if (this->second < deleter.second && delS == 0)
					{
						result.minute--;
						subMin = 0;
						result.second = (60 - deleter.second) + this->second;
						delS = 1;
					}
					else if (this->second > deleter.second && delS == 0)
					{
						result.second -= deleter.second;
						delS = 1;
					}
					subS = 1;
				}
				convert(result);
				spyears(result.year);
				flagOut(result);
			}
			
		}
		subFlagDefault();
		return result;
	}
	////////////////////////////////////////////////////кто - то сказал ОПЕРАТОР? ///////////////////////////////////////////////////
	Date(const Date& d)
	{
		this->day = d.day;
		this->year = d.year;
		this->hour = d.hour;
		this->minute = d.minute;
		this->second = d.second;
		this->month = d.month;
	}
	Date& operator= (const Date& d)
	{
		this->day = d.day;
		this->year =  d.year;
		this->hour =  d.hour;
		this->minute =  d.minute;
		this->second =  d.second;
		this->month = d.month;

		return *this;
	}
	Date operator+(const Date& d)
	{
		Date res;
		convert(d);
		res.day = this->day + d.day;
		res.month = this->month + d.month;
		res.hour = this->hour + d.hour;
		res.minute = this->minute + d.minute;
		res.second = this->second + d.second;
		res.year = this->year + d.year;
		convert(res);
		return res;
	}
	Date& operator+= (const Date& d)
	{
		convert(d);
		this->day = this->day + d.day;
		this->year = this->year + d.year;
		this->month = this->month + d.month;
		this->hour = this->hour + d.hour;
		this->minute = this->minute + d.minute;
		this->second = this->second + d.second;
		convert(*this);
		return *this;
	}
	Date operator-(const Date& d)
	{
		Date res;
		convert(d);
		res.day = this->day - d.day;
		res.month = this->month - d.month;
		res.hour = this->hour - d.hour;
		res.minute = this->minute - d.minute;
		res.second = this->second - d.second;
		res.year = this->year - d.year;
		convert(res);
		return res;
	}
	Date& operator-= (const Date& d)
	{
		convert(d);
		this->day = this->day - d.day;
		this->year = this->year - d.year;
		this->month = this->month - d.month;
		this->hour = this->hour - d.hour;
		this->minute = this->minute - d.minute;
		this->second = this->second - d.second;
		convert(*this);
		return *this;
	}
	friend bool operator> (const Date d, const Date other)
	{
		if ((d.year>=other.year)&& (d.month >= other.month) && (d.day >= other.day) && (d.hour >= other.hour) && (d.minute >= other.minute) && (d.second >= other.second))
			return 1;
		else
			return 0;
	}
	friend bool operator< (const Date d, const Date other)
	{
		if ((d.year <= other.year) && (d.month <= other.month) && (d.day <= other.day) && (d.hour <= other.hour) && (d.minute <= other.minute) && (d.second <= other.second))
			return 1;
		else
			return 0;
	}
	friend bool operator== (const Date& d, const Date& other)
	{
		if ((d.year == other.year) && (d.month == other.month) && (d.day == other.day) && (d.hour == other.hour) && (d.minute == other.minute) && (d.second == other.second))
			return 1;
		else
			return 0;
	}
	
	//////////////////////////////////////////////////// КОНЕЦ ///////////////////////////////////////////////////
};

int main()
{
	setlocale(0, "");
		Date d1;
		cout <<"d1: " << d1 << endl;
		Date d2(2060, 1, 1, 0, 0, 0);
		cout << (d1 > d2) << endl;
		cout <<(d1 < d2) << endl;
		cout <<(d1 == d2) << endl;
		Date d3 = d2.subtract(2060, 1, 1, 0, 0, 0);
		Date d4((d3 + d2) - d1);
		cout << d4;
		Date d5(d4);
		d4 += d5 - (d4.add(40, 1, 1, 0, 0, 0));

		cout << d3 << endl;
		cout << d4 << endl;
		cout << d5 << endl;

		return 0;
	}
	/*Date d1();
	Date d2(200, 1, 1, 0, 0, 0);
	Date d3 (-1800, 1,1,0,0,0);
	cout << d2;
	cout << d2 + d3;*/
	//Date date(1000,9,9,9,9,9);
	//Date date(1000, 10, 10, 10, 10, 10);
	//cout << date;
	//date.add(date, 13, 0, 32, 26, 63, 63);
	//date.add(0, 0, 0, 0, 0, 1);
	//cout << date;
//}
/* В классе Date должны быть реализованы методы со следующей сигнатурой:
add/subtract(year, month, day, hour, minute, second),
которые должны возвращать новый объект класса Date.

Должно учитываться, что год может быть високосным.
Нарисовать UML диаграмму.*/