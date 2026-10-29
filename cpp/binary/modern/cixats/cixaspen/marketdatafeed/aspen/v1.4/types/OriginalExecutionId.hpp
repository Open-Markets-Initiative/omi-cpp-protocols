#pragma once

#include <cstddef>
#include <cstdint>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Execution ID of the original trade being corrected
struct OriginalExecutionId {

    static constexpr const char* name = "Original Execution Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr OriginalExecutionId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginalExecutionId(const std::uint64_t value)
     : value{ value } {}

    // get value of OriginalExecutionId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
