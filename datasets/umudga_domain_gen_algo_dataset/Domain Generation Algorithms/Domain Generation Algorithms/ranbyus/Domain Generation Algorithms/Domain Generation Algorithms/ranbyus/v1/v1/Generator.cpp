// v1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <iostream> 
#include <fstream>
#include <set> 
#include <iterator> 
#include "Generator.h"

template<size_t SIZE, class T> inline size_t array_size(T(&arr)[SIZE]) {
	return SIZE;
}

std::string tlds[] = { "in", "me", "cc", "su", "tw", "net", "com", "pw", "org" };

std::string dga(unsigned int day, unsigned int month, unsigned int year, unsigned int seed)
{
	std::string domain = "";
	int tld_index = day;
	unsigned int i;
	for (i = 0; i < 14; i++)
	{
		day = (day >> 15) ^ 16 * (day & 0x1FFF ^ 4 * (seed ^ day));
		year = ((year & 0xFFFFFFF0) << 17) ^ ((year ^ (7 * year)) >> 11);
		month = 14 * (month & 0xFFFFFFFE) ^ ((month ^ (4 * month)) >> 8);
		seed = (seed >> 6) ^ ((day + 8 * seed) << 8) & 0x3FFFF00;
		int x = ((day ^ month ^ year) % 25) + 97;
		domain += x;
	}
	std::string result = domain + "." + tlds[tld_index++ % array_size(tlds)];
	return result;
}

int getBaseDay(int month, int year) {
	if (month == 2) {
		if (year % 4 == 0) {
			if (year % 100 == 0 && year % 400 != 0) {
				return 29;
			}
			else {
				return 28;
			}
		}
		else {
			return 28;
		}
	}
	else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
		return 31;
	}
	else {
		return 30;
	}
}

struct date {
	unsigned int year;
	unsigned int month;
	unsigned int day;
};

date getRandomDate(int seed) {

	struct tm x_years;
	int how_many_years = 1000;
	int randomYear = ((rand() % 2) == 0 ? -1 : +1) * ((rand() % how_many_years) + 1);
	int randomMonth = (rand() % 12) + 1;
	int randomDays = (rand() % getBaseDay(randomMonth, randomYear)) + 1;

	x_years.tm_hour = 0;
	x_years.tm_min = 0;
	x_years.tm_sec = 0;
	x_years.tm_year = 2018 + randomYear;
	x_years.tm_mon = (1 - randomMonth) <= 0 ? 1 + (12 - randomMonth) : 1 - randomMonth;
	x_years.tm_mday = (1 - randomDays) <= 0 ? 1 + (getBaseDay(x_years.tm_mon, x_years.tm_year) - randomDays) : 1 - randomDays;

	//std::string result = std::to_string(x_years.tm_year) + "-" + std::to_string(x_years.tm_mon) + "-" + std::to_string(x_years.tm_mday);

	date resultdate;
	resultdate.year = x_years.tm_year;
	resultdate.month = x_years.tm_mon;
	resultdate.day = x_years.tm_mday;

	return resultdate;
}

Generator::Generator()
{
	int seed = 548762159;
	srand(seed);
	std::set<std::string> data;

	SYSTEMTIME systemTime;
	GetSystemTime(&systemTime);

	std::ofstream f1000;
	std::ofstream f5000;
	std::ofstream f10000;
	std::ofstream f50000;
	std::ofstream f100000;
	std::ofstream f500000;
	std::ofstream f1000000;
	std::string path = "C:\\Users\\mattia\\Development\\UMU\\DGA-DATA\\data\\ranbyus_v1\\list\\";

	f1000.open(path + "1000.txt");
	f5000.open(path + "5000.txt");
	f10000.open(path + "10000.txt");
	f50000.open(path + "50000.txt");
	f100000.open(path + "100000.txt");
	f500000.open(path + "500000.txt");
	f1000000.open(path + "1000000.txt");

	bool stop = false;
	int forceCloseCounter = 0;
	int counter = 0;

	while(!stop)
	{
		date randomDate = getRandomDate(seed);

		std::string domain = dga(randomDate.day, randomDate.month, randomDate.year, seed);
		
		int datasize = data.size();
		data.insert(domain);

		// If it's a collision ignore it.
		if (data.size() == datasize) {
			forceCloseCounter++;
			if (forceCloseCounter == 10 * counter) {
				f1000.close();
				f5000.close();
				f10000.close();
				f50000.close();
				f100000.close();
				f500000.close();
				f1000000.close();
				stop = true;
			}

			if (forceCloseCounter % 100 == 0) {
				seed = rand();
				srand(seed);
			}

			continue;
		}

		counter = counter + 1;

		if (data.size() <= 1000) {
			f1000 << domain << "\n";
			f5000 << domain << "\n";
			f10000 << domain << "\n";
			f50000 << domain << "\n";
			f100000 << domain << "\n";
			f500000 << domain << "\n";
			f1000000 << domain << "\n";
		}
		else if (data.size() <= 5000) {
			f5000 << domain << "\n";
			f10000 << domain << "\n";
			f50000 << domain << "\n";
			f100000 << domain << "\n";
			f500000 << domain << "\n";
			f1000000 << domain << "\n";
		}
		else if (data.size() <= 10000) {
			f10000 << domain << "\n";
			f50000 << domain << "\n";
			f100000 << domain << "\n";
			f500000 << domain << "\n";
			f1000000 << domain << "\n";
		}
		else if (data.size() <= 50000) {
			f50000 << domain << "\n";
			f100000 << domain << "\n";
			f500000 << domain << "\n";
			f1000000 << domain << "\n";
		}
		else if (data.size() <= 100000) {
			f100000 << domain << "\n";
			f500000 << domain << "\n";
			f1000000 << domain << "\n";
		}
		else if (data.size() <= 500000) {
			f500000 << domain << "\n";
			f1000000 << domain << "\n";
		}
		else if (data.size() <= 1000000) {
			f1000000 << domain << "\n";
		}
		else {
			f1000.close();
			f5000.close();
			f10000.close();
			f50000.close();
			f100000.close();
			f500000.close();
			f1000000.close();
			stop = true;
			break;
		}

	}

}


Generator::~Generator()
{
}

int main(int argc, char* argv[]) {
	Generator x = Generator();

	return 0;
}