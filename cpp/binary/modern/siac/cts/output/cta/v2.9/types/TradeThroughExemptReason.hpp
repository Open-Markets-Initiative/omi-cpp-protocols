#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_9 {


// Category 2: Reason for Trade-Through Exemption / Other Reason
struct TradeThroughExemptReason {

    static constexpr auto name = "Trade Through Exempt Reason";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr TradeThroughExemptReason()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeThroughExemptReason(const char &value)
     : value{ value } {}

    // get value of TradeThroughExemptReason field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
