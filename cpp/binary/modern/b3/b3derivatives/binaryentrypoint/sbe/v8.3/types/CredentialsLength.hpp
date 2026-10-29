#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// Length of credentials data.
struct CredentialsLength {

    static constexpr auto name = "Credentials Length";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr CredentialsLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CredentialsLength(const std::uint8_t &value)
     : value{ value } {}

    // get value of CredentialsLength field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
