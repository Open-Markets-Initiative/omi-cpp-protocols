#pragma once

#include <cstddef>

namespace lseg::lse::level2mbo::gtp::v26_2 {


// Start or end of day event code.
struct EventCode {

    static constexpr auto name = "Event Code";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr EventCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EventCode(const char &value)
     : value{ value } {}

    // get value of EventCode field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
