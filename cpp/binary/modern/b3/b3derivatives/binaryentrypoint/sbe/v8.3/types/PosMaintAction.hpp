#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// posMaintAction
struct PosMaintAction {

    static constexpr auto name = "Pos Maint Action";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr PosMaintAction()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PosMaintAction(const char &value)
     : value{ value } {}

    // get value of PosMaintAction field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
