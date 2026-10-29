#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v3_0 {


// Indicates whether Application Sequence Number was reset for this Market Segment
struct ApplSeqResetIndicator {

    static constexpr auto name = "Appl Seq Reset Indicator";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0xFF;
static const type maximum_value = 1;
static const type minimum_value = 0;

    // default constructor
    constexpr ApplSeqResetIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ApplSeqResetIndicator(const std::uint8_t &value)
     : value{ value } {}

    // get value of ApplSeqResetIndicator field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
