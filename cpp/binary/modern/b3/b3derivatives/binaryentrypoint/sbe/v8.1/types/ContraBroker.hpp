#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// contraBroker
struct ContraBroker {

    static constexpr const char* name = "Contra Broker";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ContraBroker()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ContraBroker(const std::uint32_t value)
     : value{ value } {}

    // get value of ContraBroker field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
