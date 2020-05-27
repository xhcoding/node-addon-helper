#pragma once

#include <stdexcept>



namespace Nhelper {

class MethodExecuteException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

}
