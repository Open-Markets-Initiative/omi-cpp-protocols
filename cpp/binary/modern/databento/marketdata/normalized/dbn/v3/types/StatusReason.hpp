#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// Additional details about the cause of the status change
struct StatusReason {

    static constexpr const char* name = "Status Reason";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr StatusReason()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StatusReason(const std::uint16_t value)
     : value{ value } {}

    // get value of StatusReason field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
