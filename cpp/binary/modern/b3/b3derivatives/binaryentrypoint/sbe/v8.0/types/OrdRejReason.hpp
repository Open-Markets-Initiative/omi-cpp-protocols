#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// ordRejReason
struct OrdRejReason {

    static constexpr const char* name = "Ord Rej Reason";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OrdRejReason()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrdRejReason(const std::uint32_t value)
     : value{ value } {}

    // get value of OrdRejReason field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
