#pragma once

#include <stdexcept>



namespace Nhelper {

class WorkerExecuteException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

}
