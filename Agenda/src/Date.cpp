#include "Date.hpp"
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctype.h>
Date::Date() {
  m_year= m_month = m_day = m_hour = m_minute = 0;
}
Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute) {
  m_year = t_year;
  m_month = t_month;
  m_day = t_day;
  m_hour = t_hour;
  m_minute = t_minute;
}
Date::Date(std::string dateString) {
  int flag = 1;
  if(dateString.length() > 16)
    flag = 0;
  for (auto i = 0; i <= 3; i++)
    if (!isdigit(dateString[i]))
      flag = 0;
  if (dateString[4] != '-')
      flag = 0;
  for (auto i = 5; i <= 6; i++)
    if (!isdigit(dateString[i]))
      flag = 0;
  if (dateString[7] != '-')
      flag = 0;
  for (auto i = 8; i <= 9; i++)
    if (!isdigit(dateString[i]))
      flag = 0;
  if (dateString[10] != '/')
      flag = 0;
  for (auto i = 11; i <= 12; i++)
    if (!isdigit(dateString[i]))
      flag = 0;
  if (dateString[13] != ':')
      flag = 0;
  for (auto i = 14; i <= 15; i++)
    if (!isdigit(dateString[i]))
      flag = 0;    
  m_year = (dateString[0]-'0')*1000 + (dateString[1]-'0')*100 + (dateString[2]-'0')*10 + dateString[3]-'0';
  m_month = (dateString[5]-'0')*10 + dateString[6]-'0';
  m_day = (dateString[8]-'0')*10 + dateString[9]-'0';
  m_hour = (dateString[11]-'0')*10 + dateString[12]-'0';
  m_minute = (dateString[14]-'0')*10 + dateString[15]-'0';
  if (flag == 0 || !isValid(*this))
    m_year = m_month = m_day = m_hour = m_minute = 0;
}
int Date::getYear(void) const {
  return m_year;
}
void Date::setYear(const int t_year) {
  m_year = t_year;;
}
int Date::getMonth(void) const {
  return m_month;
}
void Date::setMonth(const int t_month) {
  m_month = t_month;
}
int Date::getDay(void) const {
  return  m_day;
}
void Date::setDay(const int t_day) {
  m_day = t_day;
}
int Date::getHour(void) const {
  return m_hour;
}
void Date::setHour(const int t_hour) {
  m_hour = t_hour;
}
int Date::getMinute(void) const {
  return m_minute;;
}
void Date::setMinute(const int t_minute) {
  m_minute = t_minute;
}
bool Date::isValid(const Date t_date) {
  if (t_date.m_month > 12 || t_date.m_day > 31 ||  t_date.m_month < 1 ||  t_date.m_day  < 1 )
    return false;
  if ((t_date.m_month == 1 || t_date.m_month == 3 || t_date.m_month == 5 || t_date.m_month == 7 || t_date.m_month == 8 || t_date.m_month == 10 || t_date.m_month == 12) && (t_date.m_day > 31))
    return false;
  if ((t_date.m_month == 4 || t_date.m_month == 6 || t_date.m_month == 9 || t_date.m_month == 10 || t_date.m_month == 11 ) && (t_date.m_day > 30))
    return false;
  if (t_date.m_month == 2) {
    if ((t_date.m_year % 4 == 0 && t_date.m_year % 100 != 0) || (t_date.m_year % 400 == 0)) {
      if (t_date.m_day > 29)
        return false;
     } else {
      if (t_date.m_day > 28)
        return false;
     }
  }
  if (t_date.m_hour >= 24 || t_date.m_minute >= 60 || t_date.m_hour < 0 || t_date.m_minute < 0)
    return false;
  if (t_date.m_year < 1000 || t_date.m_year > 9999)
    return false;
  return true;
}
Date Date::stringToDate(const std::string t_dateString) {
  Date temp(t_dateString);
  return temp;
}
std::string Date::dateToString(Date t_date) {
  std::string result = "";
  char str[20];
  if (isValid(t_date))
    sprintf(str, "%04d-%02d-%02d/%02d:%02d", t_date.m_year, t_date.m_month, t_date.m_day, t_date.m_hour,t_date.m_minute);
  else
    sprintf(str, "0000-00-00/00:00");
  result = str;
  return str;
}
Date& Date::operator=(const Date &t_date) {
  m_year = t_date.m_year;
  m_month = t_date.m_month;
  m_day = t_date.m_day;
  m_hour = t_date.m_hour;
  m_minute = t_date.m_minute;
  return *this;
}
bool Date::operator==(const Date &t_date) const {
  if (m_year != t_date.m_year || m_month != t_date.m_month || m_day != t_date.m_day || m_hour != t_date.m_hour || m_minute != t_date.m_minute)
    return false;
  return true;
}
bool Date::operator>(const Date &t_date) const {
  if (m_year > t_date.m_year)
    return true;
  if (m_year < t_date.m_year)
    return false;

  if (m_month > t_date.m_month)
    return true;
  if (m_month < t_date.m_month)
    return false;

  if (m_day > t_date.m_day)
    return true;
  if (m_day < t_date.m_day)
    return false;

  if (m_hour > t_date.m_hour)
    return true;
  if (m_hour < t_date.m_hour)
    return false;

  if (m_minute > t_date.m_minute)
    return true;

  return false;
}
bool Date::operator<(const Date &t_date) const {
  if (m_year < t_date.m_year)
    return true;
  if (m_year > t_date.m_year)
    return false;

  if (m_month < t_date.m_month)
    return true;
  if (m_month > t_date.m_month)
    return false;

  if (m_day < t_date.m_day)
    return true;
  if (m_day > t_date.m_day)
    return false;

  if (m_hour < t_date.m_hour)
    return true;
  if (m_hour > t_date.m_hour)
    return false;

  if (m_minute < t_date.m_minute)
    return true;

  return false;
}
bool Date::operator>=(const Date &t_date) const {
  if (*this > t_date || *this == t_date)
    return true;
  return false;
}
bool Date::operator<=(const Date &t_date) const {
  if (*this < t_date || *this == t_date)
    return true;
  return false;
}