#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Quantity that is eligible to be matched at the indicative price but will not be matched.
struct ImbalanceQuantity {

    static constexpr const char* name = "Imbalance Quantity";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::uint64_t;

    // default constructor
    constexpr ImbalanceQuantity()
     : value{ 0 } {}

    // constructor for ImbalanceQuantity field
    constexpr explicit ImbalanceQuantity(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of ImbalanceQuantity field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of ImbalanceQuantity field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
