// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/ReportingStatus.hpp
#pragma once

#include <cstddef>

namespace otcmarkets::linkats::multicast::link::v4_3 {


// Reporting status.
struct ReportingStatus {

    static constexpr auto name = "Reporting Status";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ReportingStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ReportingStatus(const char &value)
     : value{ value } {}

    // get value of ReportingStatus field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
