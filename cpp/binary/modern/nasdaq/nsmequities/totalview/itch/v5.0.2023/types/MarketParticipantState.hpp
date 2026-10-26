#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Indicates the market participant's current registration status in the issue
struct MarketParticipantState {

    static constexpr auto name = "Market Participant State";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MarketParticipantState()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketParticipantState(const char &value)
     : value{ value } {}

    // get value of MarketParticipantState field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
