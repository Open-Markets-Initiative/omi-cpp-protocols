#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v4_0 {


// For NASDAQ-listed issues, this field indicates when a firm is not in compliance with NASDAQ continued listing requirements. For CQS issues, this field will also be space-filled. Redistributors should refer to SIAC feeds for code if needed.
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
