#pragma once

#include <cstddef>

namespace jnx::jnxequities::pts::ouch::v1_11 {


// Login Reject Codes
struct RejectReasonCode {

    static constexpr auto name = "Reject Reason Code";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr RejectReasonCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RejectReasonCode(const char &value)
     : value{ value } {}

    // get value of RejectReasonCode field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
