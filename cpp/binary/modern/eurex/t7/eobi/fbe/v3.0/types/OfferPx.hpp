#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v3_0 {

// 
struct OfferPx {

    static constexpr const char* name = "Offer Px";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::int64_t;
static const type no_value = 0x8000000000000000;
static const type maximum_value = 92233720368.54775807;
static const type minimum_value = -92233720368.54775807;

    // default constructor
    constexpr OfferPx()
     : value{ 0 } {}

    // constructor for OfferPx field
    constexpr explicit OfferPx(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of OfferPx field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of OfferPx field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
