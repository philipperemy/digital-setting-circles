#include <iostream>
#include <sstream>
#include <exception>
#include <string>

class TestException : public std::exception
{
public:

    TestException(std::string str)
    {
        this->msg = std::string(str);
    }

    virtual ~TestException() throw()
    {

    }

    virtual const char * what() const throw()
    {
        return this->msg.c_str();
    }

private:
    std::string msg;
};
