#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Best offer at the time the execution processing finishes; set to 0 at market close
struct BestOffer {

    static constexpr const char* name = "Best Offer";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr BestOffer()
     : value{ 0 } {}

    // constructor for BestOffer field
    constexpr explicit BestOffer(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of BestOffer field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // does BestOffer hold a value, rather than the one reserved for none
    [[nodiscard]] bool has_value() const {
        return integer() != no_value;
    }

    // decimal value of BestOffer field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
