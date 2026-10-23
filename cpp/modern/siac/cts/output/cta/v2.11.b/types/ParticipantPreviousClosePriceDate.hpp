#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Participant date the security last traded. Represented in seconds since Epoch
struct ParticipantPreviousClosePriceDate {

    static constexpr const char* name = "Participant Previous Close Price Date";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ParticipantPreviousClosePriceDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ParticipantPreviousClosePriceDate(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of ParticipantPreviousClosePriceDate field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
