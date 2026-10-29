#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Time Stamp Assigned By The Trading Engine To Specify Time Priority Of An Order Orders Are Sequenced In The Order Book Based On Symbol Price And Priority Time Stamp
struct PriorityTimeStamp {

    static constexpr const char* name = "Priority Time Stamp";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr PriorityTimeStamp()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PriorityTimeStamp(const std::uint64_t value)
     : value{ value } {}

    // get value of PriorityTimeStamp field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
