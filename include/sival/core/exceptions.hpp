#pragma once

// #include <stdexcept>
#include <string>
#include <sival/libsival.hpp>

namespace SiVAL {

class Exception : public std::exception {
public:
    const char* what() const noexcept override {
        return m_message.c_str();
    }
    const std::string errorMsg() const {
        return m_message;
    }
    const SiVAL::ErrorCode errorCode() const {
        return m_err;
    }

protected:
    Exception(const std::string &msg, SiVAL::ErrorCode err)
        : m_message(msg), m_err(err) {
    }
    std::string m_message;
    SiVAL::ErrorCode m_err;
};

namespace Exceptions {
class OutOfRange : public Exception {
public:
    OutOfRange(const std::string &msg)
        : Exception(msg, SiVAL::ErrorCode::OutOfRange) {
    }
};

class FileAccessError : public Exception {
public:
    FileAccessError(const std::string &msg)
        :Exception(msg, SiVAL::ErrorCode::FileAccessError) {
    }
};
} // namespace Exception
} // namespace SiVAL
