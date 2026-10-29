#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// securityID
struct SecurityIdOptional {

    static constexpr const char* name = "Security Id Optional";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr SecurityIdOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityIdOptional(const std::uint64_t value)
     : value{ value } {}

    // get value of SecurityIdOptional field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
