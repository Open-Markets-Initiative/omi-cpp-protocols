#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v9 {


// Subscription Request Type indicates to the type of response expected
struct SubscriptionReqType {

    static constexpr auto name = "Subscription Req Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr SubscriptionReqType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SubscriptionReqType(const std::uint8_t &value)
     : value{ value } {}

    // get value of SubscriptionReqType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
