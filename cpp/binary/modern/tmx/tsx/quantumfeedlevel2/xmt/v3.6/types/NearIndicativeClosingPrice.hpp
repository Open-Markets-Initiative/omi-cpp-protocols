// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/NearIndicativeClosingPrice.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// The Calculated Closing Price That Will Maximize The Number Of Shares Matched Based On On Close Orders Moc Loc And Visible Continuous Market Orders Effectively This Is The Price At Which The Closing Print Would Occur At The Time Of Publication
struct NearIndicativeClosingPrice {

    static constexpr const char* name = "Near Indicative Closing Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr NearIndicativeClosingPrice()
     : value{ no_value } {}

    // constructor for NearIndicativeClosingPrice field
    constexpr explicit NearIndicativeClosingPrice(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of NearIndicativeClosingPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // does NearIndicativeClosingPrice hold a value, rather than the one reserved for none
    [[nodiscard]] bool has_value() const {
        return integer() != no_value;
    }

    // decimal value of NearIndicativeClosingPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
