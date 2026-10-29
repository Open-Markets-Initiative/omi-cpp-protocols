#pragma once

#include <cstddef>
#include <cstdint>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Reserved for future use
struct Reserved8 {

    static constexpr const char* name = "Reserved 8";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr Reserved8()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Reserved8(const std::uint64_t value)
     : value{ value } {}

    // get value of Reserved8 field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
