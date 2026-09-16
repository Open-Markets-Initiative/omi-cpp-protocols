#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Indicates when a firm is not in compliance with NASDAQ continued listing requirements
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
