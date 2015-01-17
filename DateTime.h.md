```
#ifndef _date_time_h_
#define _date_time_h_
#include <time.h>
#include <string>

#if defined(_MSC_VER) || defined(__MINGW32__)
#include <WinSock2.h>
#include <windows.h>

struct timezone
{
	int tz_minuteswest;
	int tz_dsttime;
};
#endif

struct DateTime_YearToSec
{
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;
};




class DateTime
{
public:
	static DateTime_YearToSec getDate()
	{
		time_t rawtime;
		time(&rawtime);
		struct tm* tmPtr =  localtime(&rawtime);
		DateTime_YearToSec info;
		info.year = tmPtr->tm_year + 1900;
		info.month = tmPtr->tm_mon+1;
		info.day = tmPtr->tm_mday;
		info.hour = tmPtr->tm_hour;
		info.min = tmPtr->tm_min;
		info.sec = tmPtr->tm_sec;
		return info;
	}

	// http://www.cplusplus.com/reference/ctime/strftime/
	static std::string getDateString(std::string fmt)
	{
		time_t rawtime;
		time(&rawtime);
		struct tm*pTm;
		pTm = localtime(&rawtime);
		char buff[1024];
		strftime(buff,1024,fmt.c_str(),pTm);
		return std::string(buff);
	}	

	static int getTimeOfDay(struct timeval*val,struct timezone*)
	{
#ifdef _MSC_VER
		if (val)
		{
			LARGE_INTEGER liTime, liFreq;
			QueryPerformanceFrequency( &liFreq );
			QueryPerformanceCounter( &liTime );
			val->tv_sec     = (long)( liTime.QuadPart / liFreq.QuadPart );
			val->tv_usec    = (long)( liTime.QuadPart * 1000000.0 / liFreq.QuadPart - val->tv_sec * 1000000.0 ); // 微秒
		}
		return 0;
#else
		gettimeofday(val,0);
		return 0;
#endif
	}

	static double getTick()
	{
		struct timeval val;
		getTimeOfDay(&val,0);
		return val.tv_sec*1000 + val.tv_usec / 1000.0;
	}
};
#endif
```
