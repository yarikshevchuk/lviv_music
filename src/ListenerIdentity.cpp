#include "../include/ListenerIdentity.h"

#include <string>
using namespace std;

ListenerIdentity::ListenerIdentity(std::string username, std::string email, int id, int age) : username_(username), email_(email), id_(id), age_(age) {};
int ListenerIdentity::getId() { return id_; };
string ListenerIdentity::getUsername() { return username_; };
string ListenerIdentity::getEmail() { return email_; };
int ListenerIdentity::getAge() { return age_; };