#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nationalequities::trades::pillar::v2_6 {

// The date and time when this Trade occurred at the participant firm, in seconds since Jan 1, 1970 00:00:00 UTC.
struct ExecDayTime {

    static constexpr const char* name = "Exec Day Time";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ExecDayTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExecDayTime(const std::uint32_t value)
     : value{ value } {}

    // get value of ExecDayTime field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
