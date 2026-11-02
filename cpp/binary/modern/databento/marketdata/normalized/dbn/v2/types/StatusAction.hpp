#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {

// The type of status change
struct StatusAction {

    static constexpr const char* name = "Status Action";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr StatusAction()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StatusAction(const std::uint16_t value)
     : value{ value } {}

    // get value of StatusAction field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
