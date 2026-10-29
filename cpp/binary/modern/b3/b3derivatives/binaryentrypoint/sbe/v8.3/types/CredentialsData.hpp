#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// Credentials data in ASCII.
struct CredentialsData {

    static constexpr auto name = "Credentials Data";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr CredentialsData()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CredentialsData(const char &value)
     : value{ value } {}

    // get value of CredentialsData field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
