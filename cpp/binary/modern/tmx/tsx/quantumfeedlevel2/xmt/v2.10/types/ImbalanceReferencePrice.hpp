#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// The Price That Determines If A Given Limit Priced Market On Close Loc Order Can Contribute To The Moc Imbalance All Loc Orders That Are Priced Equal To Or More Aggressively Than This Price Will Contribute To The Moc Imbalance
struct ImbalanceReferencePrice {

    static constexpr const char* name = "Imbalance Reference Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr ImbalanceReferencePrice()
     : value{ 0 } {}

    // constructor for ImbalanceReferencePrice field
    constexpr explicit ImbalanceReferencePrice(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of ImbalanceReferencePrice field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of ImbalanceReferencePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
