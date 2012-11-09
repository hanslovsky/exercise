#include <iostream>

using namespace std;

/* struct WeekDay {
  WeekDay *next_;
  int number_ = 0;
  static int days = 0;
  WeekDay(next, number) : next_(next), number_(number) {days += 1}
  ~WeekDay();
};

WeekDay::~WeekDay() {
  if (number_ < days) {
    
} */

bool ifLeap(int n) {
  if (n % 400 == 0)
    return true;
  else if (n % 100 == 0)
    return false;
  else if (n % 4 == 0)
    return true;
  else
    return false;
}

int main() {

  // first day in yr 1901 was a Tuesday
  int weekDay = 2;
  int numberOfSundays = 0;
  int yr = 1901;
  int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int monthsLeap[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  int *month;


  while (yr <= 2000) {
    if(ifLeap(yr))
      month = monthsLeap;
    else
      month = months;
    for(int m = 0; m < 12; m++) {
      for(int d = 0; d < *(month + m); d++) {
	if (weekDay % 7 == 0 && d == 0)
	  numberOfSundays++;
	weekDay++;
      }
    } 
    yr++;
  }
  cout << numberOfSundays << "\n";
  return 0;
}
