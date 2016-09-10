
#include "Path.hpp"
#include "Storage.hpp"
#include "Meeting.hpp"
#include "User.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

std::shared_ptr<Storage> Storage::m_instance = nullptr;

Storage::Storage() {
  m_dirty = false;
  if (m_dirty == false)
    readFromFile();
}

bool Storage::readFromFile() {
  string r, s, ss;
  ifstream in(Path::userPath);
  if (in.fail())
    return false;
  else {
    string username, email, password, phone;
    while (getline(in, r)) {
      istringstream inss(r);
      getline(inss, username, ',');
      getline(inss, password, ',');
      getline(inss, email, ',');    
      getline(inss, phone, ',');
      username = username.substr(1, username.end() - username.begin() - 2);
      password = password.substr(1, password.end() - password.begin() - 2);    
      email = email.substr(1, email.end() - email.begin() - 2);
      phone = phone.substr(1, phone.end() - phone.begin() - 2);
      User person(username, password, email, phone);
      m_userList.push_back(person);
    }
  }
  in.close();
  in.open(Path::meetingPath);
  if (!in)
    return false;
  else {
    string sponsor, title, start, end;
    while(getline(in, r)) {
      vector<string> participator;
      istringstream inss(r);
      getline(inss, s, ',');
      sponsor = s.substr(1, s.end() - s.begin() - 2);
      getline(inss, s, ',');
      ss = s.substr(1, s.end() - s.begin() - 2);
      ss += '&';
      istringstream temp(ss);
      while (getline(temp, s, '&'))
        participator.push_back(s);
      getline(inss, s, ',');
      s = s.substr(1, s.end() - s.begin() - 2);
      Date startdate(s);
      getline(inss, s, ',');
      s = s.substr(1, s.end() - s.begin() - 2);
      Date enddate(s);  
      getline(inss, s, ',');
      title = s.substr(1, s.end() - s.begin() - 2);
      Meeting meet(sponsor, participator, startdate, enddate, title);
      m_meetingList.push_back(meet);
    }
  }
  return true;
}

bool Storage::writeToFile() {
  std::ofstream out(Path::userPath);
  if (!out)
    return false;
  else {
    for (auto i: m_userList) {
      out << "\"" + i.getName() + "\"" << "," << "\"" + i.getPassword() + "\"" << ",";
      out << "\"" + i.getEmail() + "\"" << "," << "\"" + i.getPhone() + "\"" << "\n";
    }
  }
  out.close();
  out.open(Path::meetingPath);
  if (!out)
    return false;
  else {
    for (auto i: m_meetingList) {
      out << "\"" + i.getSponsor() + "\"" << "," << "\"";
      vector<string> p = i.getParticipator();
      for (auto j = p.begin(); j < p.end()-1; j++)
        out << *j << "&";
      out << *(p.end()-1) << "\",";
      out << "\"" + Date::dateToString(i.getStartDate()) + "\",";
      out << "\"" + Date::dateToString(i.getEndDate()) + "\",";
      out << "\"" + i.getTitle() + "\"\n";      
    }
  }
  m_dirty = false;
  return true;
}

std::shared_ptr<Storage> Storage::getInstance() {
  if (!m_instance)
    m_instance.reset(new Storage());
  return m_instance;
}

Storage::~Storage() {
  sync();//
}

void Storage::createUser(const User & t_user) {
  m_userList.push_back(t_user);//////////
  m_dirty = true;
}

std::list<User> Storage::queryUser(std::function<bool(const User &)> filter) const {
  list<User> result;
  for (auto i = m_userList.begin(); i != m_userList.end(); i++)
    if (filter(*i))
      result.push_back(*i);
  return result;
}

int Storage::updateUser(std::function<bool(const User &)> filter, std::function<void(User &)> switcher) {
  int sum = 0;
  int num = m_userList.size();
  list<User>::iterator it;
  for (it = m_userList.begin(); it != m_userList.end(); it++) {
    if (filter(*it)) {
      sum++;
      switcher(*it);
    }
  }
  if (sum > 0)
    m_dirty = true;
  else
    m_dirty = false;
  return sum;
}

int Storage::deleteUser(std::function<bool(const User &)> filter) {
  int sum = 0;
  int num = m_meetingList.size();
  list<User>::iterator it;
  for (it = m_userList.begin(); it != m_userList.end();) {
    if (filter(*it)) {
      sum++;
      m_dirty = true;
      it = m_userList.erase(it);
    } else {
      it++;
    }
  }
  return sum;  
}

void Storage::createMeeting(const Meeting & t_meeting) {
  m_meetingList.push_back(t_meeting);
  m_dirty = true;
}

std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting &)> filter) const {
  list<Meeting> result;
  for (auto i : m_meetingList)
    if (filter(i))
      result.push_back(i);
  return result;
}

int Storage::updateMeeting(std::function<bool(const Meeting &)> filter, std::function<void(Meeting &)> switcher) {
  int sum = 0;
  int num = m_meetingList.size();
  list<Meeting>::iterator it;
  for (it = m_meetingList.begin(); it != m_meetingList.end(); it++) {
    if (filter(*it)) {
      sum++;
      switcher(*it);
    }
  }
  if (sum > 0)
    m_dirty = true;
  else
    m_dirty = false;
  return sum;
}

int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter) {
  int sum = 0;
  int num = m_meetingList.size();
  list<Meeting>::iterator it;
  for (it = m_meetingList.begin(); it != m_meetingList.end();) {
    if (filter(*it)) {
      sum++;
      m_dirty = true;
      it = m_meetingList.erase(it);
    } else {
      it++;
    }
  }
  return sum;  
  
}

bool Storage::sync() {
  if (!m_dirty)
    return false;
  writeToFile();
  return true;
}


