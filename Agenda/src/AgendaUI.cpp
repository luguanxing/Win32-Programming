


#include "AgendaUI.hpp"
#include <iostream>
#include <string>
#include <list>
#include <memory>
#include <string>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctype.h>
using namespace std;

  
AgendaUI::AgendaUI() {
  startAgenda();
  m_agendaService.startAgenda();
  m_userName = m_userPassword = "";
}

void AgendaUI::OperationLoop() {
  while (executeOperation(getOperation()))
    ;
  quitAgenda();
}

std::string AgendaUI::getOperation() {
  if (m_userName == "")
    cout << "Agenda :  ";
  else
    cout << "Agenda" << m_userName << " : #";
  string command;
  cin >> command;
  return command;
}

bool AgendaUI::executeOperation(std::string command) {
  if (m_userName == "" &&command == "l")
    userLogIn();
  else if (m_userName == "" &&command == "r")
    userRegister();
  else if (m_userName == "" &&command == "q")
    return false;
  else if (m_userName != "" && command == "o")
    userLogOut();
  else if (m_userName != "" && command == "dc")
    deleteUser();
  else if (m_userName != "" && command == "lu")
    listAllUsers();
  else if (m_userName != "" && command == "cm")
    createMeeting();
  else if (m_userName != "" && command == "la")
    listAllMeetings();
  else if (m_userName != "" && command == "las")
    listAllSponsorMeetings();
  else if (m_userName != "" && command == "lap")
    listAllParticipateMeetings();
  else if (m_userName != "" && command == "qm")
    queryMeetingByTitle();
  else if (m_userName != "" && command == "qt")
    queryMeetingByTimeInterval();
  else if (m_userName != "" && command == "dm")
    deleteMeetingByTitle();
  else if (m_userName != "" && command == "da")
    deleteAllMeetings();
  else if (m_userName != "" && command == "cpa")
    changepassword();
  else if (m_userName != "" && command == "ce")
    changeemail();
  else if (m_userName != "" && command == "cph")
    changephone();
  else {
    cout << "Unknown command\n";
    return true;
  }
  return true;
}

void AgendaUI::startAgenda() {
  for (auto i = 0; i < 22; i++) cout << "-";
  cout << " Agenda ";
  for (auto i = 0; i < 22; i++) cout << "-";
  cout << "\nAction:\n";
  cout << "l - log in Agenda by user name and password\n";
  cout << "r - register an Agenda account\n";
  cout << "q - quit Agenda\n";
  for (auto i = 0; i < 52; i++) cout << "-";
  cout << "\n";
}

void AgendaUI::quitAgenda() {
  m_agendaService.quitAgenda();
}

void AgendaUI::userLogIn() {
  cout << "[log in] [user name] [password]\n[log in]";
  string name, password;
  cin >> name >> password;
  if (!m_agendaService.userLogIn(name, password))
    cout << "[error]failed!\n";
  else {
    cout << "[log in]succeed!\n";
    m_userName = name;
    m_userPassword = password;
  for (auto i = 0; i < 22; i++) cout << "-";
  cout << " Agenda ";
  for (auto i = 0; i < 22; i++) cout << "-";
  cout << "\nAction:\n";
  cout << "o - log out Agenda\n";
  cout << "dc - delete Agenda account\n";
  cout << "lu - list all Agenda user\n";
  cout << "cm - create a meeting\n";
  cout << "la - list all meeting\n";
  cout << "las - list all sponsor meeting\n";
  cout << "lap - list all participate meeting\n";
  cout << "qm - query meeting by title\n";
  cout << "qt - query meeting by time interval\n";
  cout << "dm - delete meeting by title\n";
  cout << "da - delete all meeting\n";
  for (auto i = 0; i < 52; i++) cout << "-";
  cout << "\n";
  cout << "cpa - change password\n";
  cout << "ce - change email\n";
  cout << "cph - changephone\n";
  for (auto i = 0; i < 52; i++) cout << "-";
  cout << "\n";
  }
}


void AgendaUI::userLogOut() {
  m_userName = m_userPassword = "";
  startAgenda();
}

void AgendaUI::userRegister() {
  cout << "[register] [user name] [password] [email] [phone]\n[register]";
  string name, password, email, phone;
  cin >> name >> password >> email >> phone;
  if (!m_agendaService.userRegister(name, password, email, phone))
    cout << "[error]failed!\n";
  else {
    cout << "[register]succeed!\n";
    m_userName = name;
    m_userPassword = password;
    for (auto i = 0; i < 22; i++) cout << "-";
    cout << " Agenda ";
    for (auto i = 0; i < 22; i++) cout << "-";
    cout << "\nAction:\n";
    cout << "o - log out Agenda\n";
    cout << "dc - delete Agenda account\n";
    cout << "lu - list all Agenda user\n";
    cout << "cm - create a meeting\n";
    cout << "la - list all meeting\n";
    cout << "las - list all sponsor meeting\n";
    cout << "lap - list all participate meeting\n";
    cout << "qm - query meeting by title\n";
    cout << "qt - query meeting by time interval\n";
    cout << "dm - delete meeting by title\n";
    cout << "da - delete all meeting\n";
    for (auto i = 0; i < 52; i++) cout << "-";
    cout << "\n";
    cout << "cpa - change password\n";
    cout << "ce - change email\n";
    cout << "cph - changephone\n";
    for (auto i = 0; i < 52; i++) cout << "-";
    cout << "\n";
  }
}

void AgendaUI::deleteUser() {
  if (!m_agendaService.deleteUser(m_userName, m_userPassword))
    cout << "[error]failed!\n";
  else {
    cout << "[delete agenda account] succeed!\n";
    m_userName = m_userPassword = "";
    startAgenda();
  }
}

void AgendaUI::listAllUsers() {
  cout << "[list all users]\n\n";
  auto all = m_agendaService.listAllUsers();
  printf("%-10s%-10s%-10s\n", "name", "email", "phone");
  for (auto i: all)
    printf("%-10s%-10s%-10s\n", i.getName().c_str(), i.getEmail().c_str(), i.getPhone().c_str());
}

void AgendaUI::createMeeting() {
  cout << "[create meeting] [the numeber of participators]\n[create meeting]";
  vector<string> participators;
  string name, title, st, ed;
  int n, i;
  cin >> n;
  for (i = 0; i < n; i++) {
    cout << "[create meeting] [please enter the participator" << i + 1 << "]\n[create meeting]";
    cin >> name;
    if (m_userName == name) {
      cout << "[error] failed!\n";
      return;
    }
    participators.push_back(name);
  }
  cout << "[create meeting] [title] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]\n[create meeting]";
  cin >> title >> st >> ed;
  if (!m_agendaService.createMeeting(m_userName, title, st, ed, participators))
    cout << "[error] failed!\n";
  else
    cout << "[create meeting] succeed!\n";
}

void AgendaUI::listAllMeetings() {
  cout << "\n[list all meeting]\n\n";
  list<Meeting> all = m_agendaService.listAllMeetings(m_userName);
    printf("%-10s%-10s%-20s%-20s%-20s\n", "title", "sponsor", "start time", "end time", "participators");
  for (auto i : all) {
    printf("%-10s%-10s%-20s%-20s", i.getTitle().c_str(), i.getSponsor().c_str(), Date::dateToString(i.getStartDate()).c_str(), Date::dateToString(i.getEndDate()).c_str());
    vector<string>::iterator it;
    auto p = i.getParticipator();
    if (i.getParticipator().size() >= 2) {
      for (it = p.begin(); it != p.end() - 1; it++)
        cout << *it << "&";
      cout << *it << "\n";
    }
    else {
      it = p.begin();
      cout << *it << "\n";
    }
  }
}

//////////////////////////////////////continue

void AgendaUI::listAllSponsorMeetings() {
  cout << "\n[list all sponsor meeting]\n\n";
  list<Meeting> all = m_agendaService.listAllSponsorMeetings(m_userName);
    printf("%-10s%-10s%-20s-%20s%-30s\n", "title", "sponsor", "start time", "end time", "participators");
  for (auto i : all) {
    printf("%-10s%-10s%-20s%-20s", i.getTitle().c_str(), i.getSponsor().c_str(), Date::dateToString(i.getStartDate()).c_str(), Date::dateToString(i.getEndDate()).c_str());
    vector<string>::iterator it;
    auto p = i.getParticipator();
    if (i.getParticipator().size() >= 2) {
      for (it = p.begin(); it != p.end() - 1; it++)
        cout << *it << "&";
      cout << *it << "\n";
    }
    else {
      it = p.begin();
      cout << *it << "\n";
    }
  }
}
void AgendaUI::listAllParticipateMeetings(){
  cout << "\n[list all sponsor meeting]\n\n";
  list<Meeting> all = m_agendaService.listAllParticipateMeetings(m_userName);
    printf("%-10s%-10s%-20s%-20s%-30s", "title", "sponsor", "start time", "end time", "participators");
  for (auto i : all) {
    printf("%-10s%-10s%-20s%-20s", i.getTitle().c_str(), i.getSponsor().c_str(), Date::dateToString(i.getStartDate()).c_str(), Date::dateToString(i.getEndDate()).c_str());
    vector<string>::iterator it;
    auto p = i.getParticipator();
    if (i.getParticipator().size() >= 2) {
      for (it = p.begin(); it != p.end() - 1; it++)
        cout << *it << "&";
      cout << *it << "\n";
    }
    else {
      it = p.begin();
      cout << *it << "\n";
    }
  }
}

void AgendaUI::queryMeetingByTitle() {
  cout << "\n[query meeting][title]\n[query]";
  string title;
  cin >> title;
  auto all = m_agendaService.meetingQuery(m_userName, title);
  for (auto i : all) {
    printf("%-10s-%10s%-20s%-20s", i.getTitle().c_str(), i.getSponsor().c_str(), Date::dateToString(i.getStartDate()).c_str(), Date::dateToString(i.getEndDate()).c_str());
    vector<string>::iterator it;
    auto p = i.getParticipator();
    if (i.getParticipator().size() >= 2) {
      for (it = p.begin(); it != p.end() - 1; it++)
        cout << *it << "&";
      cout << *it << "\n";
    }
    else {
      it = p.begin();
      cout << *it << "\n";
    }
  }

}

void AgendaUI::queryMeetingByTimeInterval() {
  cout << "\n[query meeting][start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]\n[query meeting]";
  string checks, checke;
  cin >> checks >> checke;
  if (checks >= checke) {
    cout << "[error]failed!\n";
    return;
  }
  cout << "[query meeting]\n";
  auto all = m_agendaService.meetingQuery(m_userName, checks, checke);
  for (auto i : all) {
    printf("%-10s%-10s%-20s%-20s", i.getTitle().c_str(), i.getSponsor().c_str(), Date::dateToString(i.getStartDate()).c_str(), Date::dateToString(i.getEndDate()).c_str());
    vector<string>::iterator it;
    auto p = i.getParticipator();
    if (i.getParticipator().size() >= 2) {
      for (it = p.begin(); it != p.end() - 1; it++)
        cout << *it << "&";
      cout << *it << "\n";
    }
    else {
      it = p.begin();
      cout << *it << "\n";
    }
  }  
}

void AgendaUI::deleteMeetingByTitle() {
  cout << "\n[delete meeting] [title]\n[delete meeting]";
  string title;
  cin >> title;
  if (!m_agendaService.deleteMeeting(m_userName, title))
    cout << "[error]failed!\n";
  else 
    cout << "[delete meeting]succeed!\n";
}

void AgendaUI::deleteAllMeetings() {
  if (!m_agendaService.deleteAllMeetings(m_userName))
    cout << "[error]failed!\n";
  else 
    cout << "[delete meeting]succeed!\n";
}

void AgendaUI::printMeetings(std::list<Meeting> t_meetings) {
  auto all = t_meetings;
  for (auto i : all) {
    printf("-20s-20s-20s-20s", i.getTitle().c_str(), i.getSponsor().c_str(), Date::dateToString(i.getStartDate()).c_str(), Date::dateToString(i.getEndDate()).c_str() );
    vector<string>::iterator it;
    for (it = i.getParticipator().begin(); it != i.getParticipator().end() - 1; it++)
      cout << *it << ",";
    cout << *it << "\n";
  }    
}


