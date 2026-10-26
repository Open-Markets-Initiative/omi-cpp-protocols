#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Identifies the type of Administrative message
struct AdministrativeMessageType {

    static constexpr auto name = "Administrative Message Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr AdministrativeMessageType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AdministrativeMessageType(const char &value)
     : value{ value } {}

    // get value of AdministrativeMessageType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
