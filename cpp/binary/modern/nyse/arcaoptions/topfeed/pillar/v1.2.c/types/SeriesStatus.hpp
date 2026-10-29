#pragma once

#include <cstddef>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {


// The new status that this series is transitioning to
struct SeriesStatus {

    static constexpr auto name = "Series Status";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SeriesStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SeriesStatus(const char &value)
     : value{ value } {}

    // get value of SeriesStatus field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
