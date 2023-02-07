#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

namespace cs3520 {
    // A custom exception class for our library.
    class InvalidUserInputException: public std::exception {
    public:
        InvalidUserInputException(const std::string& msg): m_msg(msg) {}

        // Returns the message passed in when instantiating this class.
        const char* what() const noexcept override {
            return m_msg.c_str();
        }
    private:
        std::string m_msg;
    };
}

#endif // EXCEPTIONS_HPP
