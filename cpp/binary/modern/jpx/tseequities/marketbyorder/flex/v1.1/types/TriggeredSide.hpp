#pragma once

#include <cstddef>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {


// Indicates the side whose order triggered the execution
struct TriggeredSide {

    static constexpr auto name = "Triggered Side";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr TriggeredSide()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TriggeredSide(const char &value)
     : value{ value } {}

    // get value of TriggeredSide field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
