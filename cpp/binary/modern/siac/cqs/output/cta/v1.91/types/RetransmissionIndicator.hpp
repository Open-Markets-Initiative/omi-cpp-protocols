#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v1_91 {


// Indicates an original message or a retransmitted block
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
