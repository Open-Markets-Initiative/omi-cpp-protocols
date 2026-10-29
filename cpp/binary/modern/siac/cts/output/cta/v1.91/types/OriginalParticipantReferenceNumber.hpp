#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v1_91 {

// Contains the Participant Reference Number of transaction to be corrected, cancelled or error
struct OriginalParticipantReferenceNumber {

    static constexpr const char* name = "Original Participant Reference Number";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;

    // default constructor
    constexpr OriginalParticipantReferenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginalParticipantReferenceNumber(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get value of OriginalParticipantReferenceNumber field
    [[nodiscard]] std::int64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::int64_t value;
};
}
