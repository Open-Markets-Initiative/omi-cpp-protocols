#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v6_0 {


// End-of-event marker (0 = more to follow, 1 = last packet of event)
struct CompletionIndicator {

    static constexpr auto name = "Completion Indicator";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0xFF;
static const type maximum_value = 1;
static const type minimum_value = 0;

    // default constructor
    constexpr CompletionIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CompletionIndicator(const std::uint8_t &value)
     : value{ value } {}

    // get value of CompletionIndicator field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
