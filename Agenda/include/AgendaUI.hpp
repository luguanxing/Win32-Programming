#ifndef AGENDAUI_H
#define AGENDAUI_H

#include "AgendaService.hpp"
#include <iostream>
#include <string>

using namespace std;

class AgendaUI {
   public:

    void changepassword() {
        string newpassword;
        cout << "[new password]";
        cin >> newpassword;
        if (!m_agendaService.gaipassword(newpassword, m_userName))
            cout << "[error]failed!\n";
        else
            cout << "[change password]succeed!\n";
    }

    void changeemail() {
        string newemail;
        cout << "[new email]";
        cin >> newemail;
        if (!m_agendaService.gaiemail(newemail, m_userName))
            cout << "[error]failed!\n";
        else
            cout << "[change email]succeed!\n";
    }

    void changephone() {
        string newphone;
        cout << "[new phone]";
        cin >> newphone;
        if (!m_agendaService.gaiphone(newphone, m_userName))
            cout << "[error]failed!\n";
        else
            cout << "[change phone]succeed!\n";
    }

    AgendaUI();
    void OperationLoop(void);


    /**
     * constructor
     */
    void startAgenda(void);

    /**
     * catch user's operation
     * @return the operation
     */
    std::string getOperation();

    /**
     * execute the operation
     * @return if the operationloop continue
     */
    bool executeOperation(std::string t_operation);

    /**
     * user Login
     */
    void userLogIn(void);

    /**
     * user regist
     */
    void userRegister(void);

    /**
     * quit the Agenda
     */
    void quitAgenda(void);

    /**
     * user logout
     */
    void userLogOut(void);

    /**
     * delete a user from storage
     */
    void deleteUser(void);

    /**
     * list all users from storage
     */
    void listAllUsers(void);

    /**
     * user create a meeting with someone else
     */
    void createMeeting(void);

    /**
     * list all meetings from storage
     */
    void listAllMeetings(void);

    /**
     * list all meetings that this user sponsored
     */
    void listAllSponsorMeetings(void);

    /**
     * list all meetings that this user take part in
     */
    void listAllParticipateMeetings(void);

    /**
     * search meetings by title from storage
     */
    void queryMeetingByTitle(void);

    /**
     * search meetings by timeinterval from storage
     */
    void queryMeetingByTimeInterval(void);

    /**
     * delete meetings by title from storage
     */
    void deleteMeetingByTitle(void);

    /**
     * delete all meetings that this user sponsored
     */
    void deleteAllMeetings(void);

    /**
     * show the meetings in the screen
     */
    void printMeetings(std::list<Meeting> t_meetings);
    // dates
    std::string m_userName;
    std::string m_userPassword;
    AgendaService m_agendaService;
};

#endif
