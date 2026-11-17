// Miax.MiaxOptions.TopOfMarket.Mach.v2.5: types/ExpectedEventTimeSecondsPart.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Seconds portion of the expected time of the event. Always use in conjunction with the Nano-seconds part field.
struct ExpectedEventTimeSecondsPart {

    static constexpr const char* name = "Expected Event Time Seconds Part";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr ExpectedEventTimeSecondsPart()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit ExpectedEventTimeSecondsPart(const std::uint32_t value)
     : value{ value } {}

    // get value of ExpectedEventTimeSecondsPart field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
