// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/TemplateId.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// The Template ID is for decoding the message.
struct TemplateId {

    static constexpr auto name = "Template Id";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr TemplateId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TemplateId(const std::uint8_t &value)
     : value{ value } {}

    // get value of TemplateId field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
