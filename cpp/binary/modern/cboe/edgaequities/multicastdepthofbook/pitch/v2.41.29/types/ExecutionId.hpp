#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29 {

// Cboe generated day-unique execution identifier of this execution. Execution Id is also referenced in the Trade Break message
struct ExecutionId {

    static constexpr const char* name = "Execution Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr ExecutionId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExecutionId(const std::uint64_t value)
     : value{ value } {}

    // get value of ExecutionId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
