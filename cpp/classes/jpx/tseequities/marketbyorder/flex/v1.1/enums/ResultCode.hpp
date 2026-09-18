#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Set to the result code of the login request
enum class ResultCode : char {
    Accepted = 'A',                // Accepted
    OutOfService = 'O',            // Out Of Service
    IncorrectUserId = 'U',         // Incorrect User Id
    IncorrectSequenceNumber = 'S', // Incorrect Sequence Number
    IncorrectPacketType = 'T',     // Incorrect Packet Type
    IncorrectMcgNumber = 'M',      // Incorrect Mcg Number
    OtherError = 'Z',              // Other Error
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ResultCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ResultCode value);

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
