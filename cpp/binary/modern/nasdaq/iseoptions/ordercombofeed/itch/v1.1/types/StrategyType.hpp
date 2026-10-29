#pragma once

#include <cstddef>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {


// StrategyType value
struct StrategyType {

    static constexpr auto name = "Strategy Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr StrategyType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StrategyType(const char &value)
     : value{ value } {}

    // get value of StrategyType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
