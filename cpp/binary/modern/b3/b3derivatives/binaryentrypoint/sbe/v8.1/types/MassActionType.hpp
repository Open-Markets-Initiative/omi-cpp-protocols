#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {


// massActionType
struct MassActionType {

    static constexpr auto name = "Mass Action Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MassActionType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MassActionType(const std::uint8_t &value)
     : value{ value } {}

    // get value of MassActionType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
