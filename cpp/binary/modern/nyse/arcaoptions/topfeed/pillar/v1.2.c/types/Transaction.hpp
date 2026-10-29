#pragma once

#include <cstddef>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {


// Settlement related conditions. Valid values:
struct Transaction {

    static constexpr auto name = "Transaction";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Transaction()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Transaction(const char &value)
     : value{ value } {}

    // get value of Transaction field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
