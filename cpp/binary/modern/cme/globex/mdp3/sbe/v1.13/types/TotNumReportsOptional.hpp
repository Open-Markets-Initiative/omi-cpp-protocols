#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Total number of instruments in the Replay loop. Used on Replay Feed only
struct TotNumReportsOptional {

    static constexpr const char* name = "Tot Num Reports Optional";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 4294967295;

    // default constructor
    constexpr TotNumReportsOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TotNumReportsOptional(const std::uint32_t value)
     : value{ value } {}

    // get value of TotNumReportsOptional field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
