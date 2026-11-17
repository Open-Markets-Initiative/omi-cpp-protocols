// Databento.MarketData.Normalized.Dbn.v3: types/InstAttribValue.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// A bitmap of instrument eligibility attributes; venue-specific
struct InstAttribValue {

    static constexpr const char* name = "Inst Attrib Value";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr InstAttribValue()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit InstAttribValue(const std::int32_t value)
     : value{ value } {}

    // get value of InstAttribValue field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
