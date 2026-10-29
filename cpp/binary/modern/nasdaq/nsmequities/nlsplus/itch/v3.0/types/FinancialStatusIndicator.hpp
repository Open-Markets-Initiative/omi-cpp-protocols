#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// For Nasdaq listed issues, denotes when an issue is flagged as deficient, delinquent, bankrupt or in a compliance period
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
