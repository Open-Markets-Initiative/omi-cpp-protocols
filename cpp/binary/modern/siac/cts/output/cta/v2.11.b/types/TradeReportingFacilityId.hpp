#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Identifies the Participant with whom a Trade Reporting Facility (TRF) has been formed. Space-filled
struct TradeReportingFacilityId {

    static constexpr auto name = "Trade Reporting Facility Id";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr TradeReportingFacilityId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeReportingFacilityId(const char &value)
     : value{ value } {}

    // get value of TradeReportingFacilityId field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
