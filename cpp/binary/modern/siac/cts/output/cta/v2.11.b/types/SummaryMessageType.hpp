#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Identifies the type of Summary message
struct SummaryMessageType {

    static constexpr auto name = "Summary Message Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SummaryMessageType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SummaryMessageType(const char &value)
     : value{ value } {}

    // get value of SummaryMessageType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
