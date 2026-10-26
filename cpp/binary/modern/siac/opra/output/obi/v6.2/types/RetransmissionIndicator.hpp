#pragma once

#include <cstddef>

namespace siac::opra::output::obi::v6_2 {


// Contains either a space; not a retransmitted message or V; indicating a retransmission of the block.
struct RetransmissionIndicator {

    static constexpr auto name = "Retransmission Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr RetransmissionIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RetransmissionIndicator(const char &value)
     : value{ value } {}

    // get value of RetransmissionIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
