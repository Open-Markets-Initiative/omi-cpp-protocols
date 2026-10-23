#pragma once

#include <cstddef>

namespace cme::mdp3::v8 {


// Market Data entry type
struct MdEntryTypeBook {

    static constexpr auto name = "Md Entry Type Book";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MdEntryTypeBook()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdEntryTypeBook(const char &value)
     : value{ value } {}

    // get value of MdEntryTypeBook field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
