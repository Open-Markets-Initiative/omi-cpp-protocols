#pragma once

#include <cstddef>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {


// Set to the result code of the login request
struct ResultCode {

    static constexpr auto name = "Result Code";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ResultCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ResultCode(const char &value)
     : value{ value } {}

    // get value of ResultCode field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
