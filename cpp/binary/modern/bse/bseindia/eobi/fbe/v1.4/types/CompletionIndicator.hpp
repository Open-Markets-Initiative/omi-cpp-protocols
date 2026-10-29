#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {


// Indicates whether a unit of work fits into a single datagram, 0 Incomplete and 1 Complete
struct CompletionIndicator {

    static constexpr auto name = "Completion Indicator";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr CompletionIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CompletionIndicator(const std::uint8_t &value)
     : value{ value } {}

    // get value of CompletionIndicator field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
