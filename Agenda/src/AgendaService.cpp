#include "AgendaService.hpp"
#include <functional>
#include <list>
#include <memory>
#include <string>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctype.h>
#include <algorithm>
using namespace std;


AgendaService::AgendaService() {
  startAgenda();
}

AgendaService::~AgendaService() {
  quitAgenda();
}

bool alluser(const User&) {return true;}

bool AgendaService::userLogIn(const std::string userName, const std::string password) {
  if (userName == "" || password == "")
    return false;
  list<User> all = m_storage->queryUser(alluser);
  for (auto i = all.begin(); i != all.end(); i++)
    if ((*i).getName() == userName && (*i).getPassword() == password)
      return true;
    return false;
}

bool AgendaService::userRegister(const std::string userName, const std::string password, const std::string email, const std::string phone) {
  list<User> all = m_storage->queryUser(alluser);
  for (auto i = all.begin(); i != all.end(); i++)
    if ((*i).getName() == userName)
      return false;
  User person(userName, password, email, phone);
  m_storage->createUser(person);
  return true;
}

bool allmeeting(const Meeting&) { return true; }

bool AgendaService::deleteUser(const std::string userName, const std::string password) {
  list<Meeting> all = m_storage->queryMeeting(allmeeting);
  list<User> t = m_storage->queryUser( [userName](const User p)->bool{return(p.getName() == userName);});
  for (auto i : t) {
    if (i.getPassword() == password) {
      m_storage->deleteMeeting( [userName](const Meeting meet)->bool{return(meet.getSponsor() == userName);});
      m_storage->deleteMeeting( [userName](const Meeting meet)->bool{return(meet.isParticipator(userName));});
      m_storage->deleteUser( [userName](const User p)->bool{return(p.getName() == userName);} );
      return true;  
    }
  }
  return false;
}

std::list<User> AgendaService::listAllUsers() const {
  return m_storage->queryUser(alluser);
}

bool AgendaService::createMeeting(const std::string userName, const std::string title,const std::string startDate, const std::string endDate,const std::vector<std::string> participator) {
  Date s(startDate), e(endDate);
  //check date
  if (!Date::isValid(s) || !Date::isValid(e))
    return false;
  if (s >= e)
    return false;
  //check same person
  std::vector<std::string> participators = participator;
  sort(participators.begin(), participators.end());
  auto check = unique(participators.begin() ,participators.end());
  if (check != participators.end())
    return false;
  // check sponsor not in participator
  for (auto i :participator)
    if (i == userName)
      return false;
  //check same title
  auto titles = m_storage->queryMeeting([title](Meeting m)->bool {return (m.getTitle() == title);});
    if (titles.size() != 0)
      return false;
  // check sponsor and participator in userlist
  list<User> all = listAllUsers();
  int flag1, flag2;
  flag1 = flag2 = 0;
  for (auto i: all)
    if (i.getName() == userName) {
      flag1 = 1;
      break;
    }
  if (flag1 == 0)
    return false;
  for (auto i: participator) {
    flag2 = 0;
    for (auto j: all)
      if (i == j.getName()) {
        flag2 = 1;
        break;
      }
    if (flag2 == 0)
      return false;
  }
  //check sponsor and participators' fenshenshu
  list<Meeting> allsponsormeet = listAllMeetings(userName);
  for (auto i : allsponsormeet) {
    if (!(s >= i.getEndDate() || e <= i.getStartDate()))
      return false;
  }

  for (auto par : participator) {
    list<Meeting> allparticipatormeet = listAllMeetings(par);
    for (auto i : allparticipatormeet) {
      if (!(s >= i.getEndDate() || e <= i.getStartDate()))
          return false;
    }
  }

  Meeting meet(userName, participator, s, e, title);
  m_storage->createMeeting(meet);
  return true;

}

std::list<Meeting> AgendaService::meetingQuery(const std::string userName,const std::string title) const {
  list<Meeting> all = m_storage->queryMeeting(allmeeting);
  list<Meeting> result;
  for (auto i: all)
    if (i.getTitle() == title && (i.getSponsor() == userName || i.isParticipator(userName)))
      result.push_back(i);
  return result;
}

std::list<Meeting> AgendaService::meetingQuery(const std::string userName,const std::string startDate,const std::string endDate) const {
  list<Meeting> all = m_storage->queryMeeting(allmeeting);
  list<Meeting> result;
  for (auto i: all) {
    Date front(startDate), back(endDate);
    if (!Date::isValid(front) || !Date::isValid(back))
      return result;
    Date meets = i.getStartDate(), meete = i.getEndDate();
    if ((i.getSponsor() == userName || i.isParticipator(userName)) && ( !(meets > back || meete < front ) ) )
      result.push_back(i);
  }
  return result;
}


std::list<Meeting> AgendaService::listAllMeetings(const std::string userName) const {
  list<Meeting> all = m_storage->queryMeeting(allmeeting);
  list<Meeting> result;
  for (auto i: all)
    if (i.getSponsor() == userName || i.isParticipator(userName))
      result.push_back(i);
  return result;  
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(const std::string userName) const {
  list<Meeting> all = m_storage->queryMeeting(allmeeting);
  list<Meeting> result;
  for (auto i: all)
    if (i.getSponsor() == userName)
      result.push_back(i);
  return result;  
}
std::list<Meeting> AgendaService::listAllParticipateMeetings(const std::string userName) const {
  list<Meeting> all = m_storage->queryMeeting(allmeeting);
  list<Meeting> result;
  for (auto i: all)
    if (i.isParticipator(userName))
      result.push_back(i);
  return result;  
}

bool AgendaService::deleteMeeting(const std::string userName, const std::string title) {
  return m_storage->deleteMeeting([userName, title](const Meeting meet)->bool {return (meet.getSponsor() == userName && meet.getTitle() == title); });
}

bool AgendaService::deleteAllMeetings(const std::string userName) {
  return m_storage->deleteMeeting([userName](const Meeting meet)->bool {return (meet.getSponsor() == userName); });
}
void AgendaService::startAgenda() {
  m_storage = Storage::getInstance();
}
void AgendaService::quitAgenda() {
  m_storage->sync();
}





