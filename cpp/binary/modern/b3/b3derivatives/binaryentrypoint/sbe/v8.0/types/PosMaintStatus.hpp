#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// posMaintStatus
struct PosMaintStatus {

    static constexpr auto name = "Pos Maint Status";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr PosMaintStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PosMaintStatus(const char &value)
     : value{ value } {}

    // get value of PosMaintStatus field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
