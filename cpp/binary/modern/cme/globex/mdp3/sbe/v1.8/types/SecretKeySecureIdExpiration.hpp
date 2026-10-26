#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v8 {

// This indicates in how many days the HMAC secret key will expire
struct SecretKeySecureIdExpiration {

    static constexpr const char* name = "Secret Key Secure Id Expiration";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 65535;

    // default constructor
    constexpr SecretKeySecureIdExpiration()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecretKeySecureIdExpiration(const std::uint16_t value)
     : value{ value } {}

    // get value of SecretKeySecureIdExpiration field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
