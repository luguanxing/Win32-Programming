#ifndef MEETING_H
#define MEETING_H

#include "Date.hpp"
#include <vector>

class Meeting {
public:
  /**
  * @brief default constructor
  */
  Meeting() = default;

  /**
  *   @brief constructor with argument
  */
  Meeting(std::string t_sponsor, std::vector<std::string> t_participator, Date t_startTime,
          Date t_endTime, std::string t_title);

  /**
  * @brief copy constructor of left value
  */
  Meeting(const Meeting &t_meeting);

  /**
  *   @brief get the meeting's sponsor
  *   @return a string indicate sponsor
  */
  std::string getSponsor(void) const;

  /**
  * @brief set the sponsor of a meeting
  * @param  the new sponsor string
  */
  void setSponsor(const std::string t_sponsor);

  /**
  * @brief  get the participators of a meeting
  * @return return a string vector indicate participators
  */
  std::vector<std::string> getParticipator(void) const;

  /**
  *   @brief set the new participators of a meeting
  *   @param the new participators vector
  */
  void setParticipator(const std::vector<std::string> t_participators);

  /**
  * @brief get the startDate of a meeting
  * @return return a string indicate startDate
  */
  Date getStartDate(void) const;

  /**
  * @brief  set the startDate of a meeting
  * @param  the new startdate of a meeting
  */
  void setStartDate(const Date t_startTime);

  /**
  * @brief get the endDate of a meeting
  * @return a date indicate the endDate
  */
  Date getEndDate(void) const;

  /**
  * @brief  set the endDate of a meeting
  * @param  the new enddate of a meeting
  */
  void setEndDate(const Date t_endTime);

  /**
  * @brief get the title of a meeting
  * @return a date title the endDate
  */
  std::string getTitle(void) const;

  /**
  * @brief  set the title of a meeting
  * @param  the new title of a meeting
  */
  void setTitle(const std::string t_title);


  /**
  * @brief check if the user take part in this meeting
  * @param t_username the source username
  * @return if the user take part in this meeting
  */
  bool isParticipator(const std::string t_username) const;
private:
  std::string m_sponsor;
  std::vector<std::string> m_participators;
  Date m_startDate;
  Date m_endDate;
  std::string m_title;
};

#endif
