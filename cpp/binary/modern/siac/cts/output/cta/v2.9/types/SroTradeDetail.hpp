#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_9 {


// Category 4: SRO Trade Detail
struct SroTradeDetail {

    static constexpr auto name = "Sro Trade Detail";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SroTradeDetail()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SroTradeDetail(const char &value)
     : value{ value } {}

    // get value of SroTradeDetail field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
