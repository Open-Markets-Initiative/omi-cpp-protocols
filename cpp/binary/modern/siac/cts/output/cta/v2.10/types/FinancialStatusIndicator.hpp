#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_10 {


// Identifies the financial status of the security.
struct FinancialStatusIndicator {

    static constexpr auto name = "Financial Status Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr FinancialStatusIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FinancialStatusIndicator(const char &value)
     : value{ value } {}

    // get value of FinancialStatusIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
