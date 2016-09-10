#ifndef DATE_H
#define DATE_H

#include <initializer_list>
#include <string>

class Date {
public:
  /**
  * @brief default constructor
  */
  Date();

  /**
  * @brief constructor with arguments
  */
  Date(int t_year, int t_month, int t_day, int t_hour, int t_minute);

  /**
  * @brief constructor with a string
  */
  Date(std::string dateString);
  /**
  * @brief return the year of a Date
  * @return   a integer indicate the year of a date
  */
  int getYear(void) const;

  /**
  * @brief set the year of a date
  * @param a integer indicate the new year of a date
  */
  void setYear(const int t_year);

  /**
  * @brief return the month of a Date
  * @return   a integer indicate the month of a date
  */
  int getMonth(void) const;

  /**
  * @brief set the month of a date
  * @param a integer indicate the new month of a date
  */
  void setMonth(const int t_month);

  /**
  * @brief return the day of a Date
  * @return   a integer indicate the day of a date
  */
  int getDay(void) const;

  /**
  * @brief set the day of a date
  * @param a integer indicate the new day of a date
  */
  void setDay(const int t_day);

  /**
  * @brief return the hour of a Date
  * @return   a integer indicate the hour of a date
  */
  int getHour(void) const;

  /**
  * @brief set the hour of a date
  * @param a integer indicate the new hour of a date
  */
  void setHour(const int t_hour);

  /**
  * @brief return the minute of a Date
  * @return   a integer indicate the minute of a date
  */
  int getMinute(void) const;

  /**
  * @brief set the minute of a date
  * @param a integer indicate the new minute of a date
  */
  void setMinute(const int t_minute);

  /**
  *   @brief check whether the date is valid or not
  *   @return the bool indicate valid or not
  */
  static bool isValid(const Date t_date);

  /**
  * @brief convert a string to date, if the format is not correct return
  * 0000-00-00/00:00
  * @return a date
  */
  static Date stringToDate(const std::string t_dateString);

  /**
  * @brief convert a date to string, if the format is not correct return
  * 0000-00-00/00:00
  */
  static std::string dateToString(Date t_date);

  /**
  *  @brief overload the assign operator
  */
  Date &operator=(const Date &t_date);

  /**
  * @brief check whether the CurrentDate is equal to the t_date
  */
  bool operator==(const Date &t_date) const;

  /**
  * @brief check whether the CurrentDate is  greater than the t_date
  */
  bool operator>(const Date &t_date) const;

  /**
  * @brief check whether the CurrentDate is  less than the t_date
  */
  bool operator<(const Date &t_date) const;

  /**
  * @brief check whether the CurrentDate is  greater or equal than the t_date
  */
  bool operator>=(const Date &t_date) const;

  /**
  * @brief check whether the CurrentDate is  less than or equal to the t_date
  */
  bool operator<=(const Date &t_date) const;

private:
  int m_year;
  int m_month;
  int m_day;
  int m_hour;
  int m_minute;
};

#endif
