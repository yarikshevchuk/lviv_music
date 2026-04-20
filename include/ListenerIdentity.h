#include <string>

#include "interface/IIdentity.h"

class ListenerIdentity : public IIdentity {
   private:
    std::string username_;
    std::string email_;
    int id_;
    int age_;

   public:
    ListenerIdentity(std::string username, std::string email, int id, int age);
    std::string getUsername() override;
    std::string getEmail() override;
    int getId() override;
    int getAge() override;
};