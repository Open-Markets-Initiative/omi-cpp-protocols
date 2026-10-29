#pragma once

#include <cstddef>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {


// Settlement Terms Associated With The Order
struct SettlementTerms {

    static constexpr auto name = "Settlement Terms";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SettlementTerms()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SettlementTerms(const char &value)
     : value{ value } {}

    // get value of SettlementTerms field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
