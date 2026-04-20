#pragma once
#include <string>

class IAudio {
   public:
    virtual ~IAudio() = default;

    virtual int getId() const = 0;
    virtual std::string getName() const = 0;
    virtual std::string getAuthor() const = 0;
};