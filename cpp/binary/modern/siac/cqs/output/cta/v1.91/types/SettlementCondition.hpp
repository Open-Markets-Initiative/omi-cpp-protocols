#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v1_91 {


// Identifies the settlement condition for a security
struct SettlementCondition {

    static constexpr auto name = "Settlement Condition";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SettlementCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SettlementCondition(const char &value)
     : value{ value } {}

    // get value of SettlementCondition field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
