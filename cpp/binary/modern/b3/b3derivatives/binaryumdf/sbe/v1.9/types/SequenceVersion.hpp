#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// Packet Sequence Version
struct SequenceVersion {

    static constexpr const char* name = "Sequence Version";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr SequenceVersion()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SequenceVersion(const std::uint16_t value)
     : value{ value } {}

    // get value of SequenceVersion field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
