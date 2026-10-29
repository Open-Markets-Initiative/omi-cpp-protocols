#pragma once

#include <cstddef>

namespace cme::mdp3::v5 {


// Market Data entry type
struct MdEntryType {

    static constexpr auto name = "Md Entry Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MdEntryType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdEntryType(const char &value)
     : value{ value } {}

    // get value of MdEntryType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
