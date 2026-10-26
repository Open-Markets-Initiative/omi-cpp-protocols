#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

// lastSequenceVersion
struct LastSequenceVersion {

    static constexpr const char* name = "Last Sequence Version";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 0;

    // default constructor
    constexpr LastSequenceVersion()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LastSequenceVersion(const std::uint16_t value)
     : value{ value } {}

    // get value of LastSequenceVersion field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
