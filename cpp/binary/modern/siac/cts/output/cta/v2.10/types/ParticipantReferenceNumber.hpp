#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_10 {

// Participant Reference Number is a pass-thru of the inbound Participant Reference number assigned to a transaction
struct ParticipantReferenceNumber {

    static constexpr const char* name = "Participant Reference Number";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;

    // default constructor
    constexpr ParticipantReferenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ParticipantReferenceNumber(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get value of ParticipantReferenceNumber field
    [[nodiscard]] std::int64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::int64_t value;
};
}
