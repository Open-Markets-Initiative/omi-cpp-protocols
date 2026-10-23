#pragma once

#include <cstddef>

namespace siac::opra::output::obi::v6_2 {


// Equity and Index End of Day Summary Message Type
struct EquityAndIndexEndOfDaySummaryMessageType {

    static constexpr auto name = "Equity And Index End Of Day Summary Message Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr EquityAndIndexEndOfDaySummaryMessageType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EquityAndIndexEndOfDaySummaryMessageType(const char &value)
     : value{ value } {}

    // get value of EquityAndIndexEndOfDaySummaryMessageType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
