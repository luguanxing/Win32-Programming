#ifndef USER_H
#define USER_H

#include <initializer_list>
#include <string>
class User {
public:
  /**
  * @brief the default constructor
  */
  User() = default;

  /**
  * constructor with arguments
  */
  User(std::string t_userName, std::string t_userPassword,
       std::string t_userEmail, std::string t_userPhone);

  /**
  * @brief copy constructor
  */
  User(const User &t_user);

  /**
  * @brief get the name of the user
  * @return   return a string indicate the name of the user
  */
  std::string getName() const;

  /**
  * @brief set the name of the user
  * @param   a string indicate the new name of the user
  */
  void setName(std::string t_name);

  /**
  * @brief get the password of the user
  * @return   return a string indicate the password of the user
  */
  std::string getPassword() const;

  /**
  * @brief set the password of the user
  * @param   a string indicate the new password of the user
  */
  void setPassword(std::string t_password);

  /**
  * @brief get the email of the user
  * @return   return a string indicate the email of the user
  */
  std::string getEmail() const;

  /**
  * @brief set the email of the user
  * @param   a string indicate the new email of the user
  */
  void setEmail(std::string t_email);

  /**
  * @brief get the phone of the user
  * @return   return a string indicate the phone of the user
  */
  std::string getPhone() const;

  /**
  * @brief set the phone of the user
  * @param   a string indicate the new phone of the user
  */
  void setPhone(std::string t_phone);

private:
  std::string m_name;
  std::string m_password;
  std::string m_email;
  std::string m_phone;
};

#endif
