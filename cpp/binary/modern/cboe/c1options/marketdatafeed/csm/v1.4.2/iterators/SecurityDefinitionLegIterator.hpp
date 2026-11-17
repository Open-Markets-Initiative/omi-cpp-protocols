// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: iterators/SecurityDefinitionLegIterator.hpp
#pragma once

#include "../definitions.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {
// SecurityDefinitionLegIterator
struct SecurityDefinitionLegIterator {

    const std::byte* current = nullptr;

    const SecurityDefinitionMessage* security_definition_message = nullptr;

    std::uint8_t no_legs = 0;
    std::uint8_t entry_index = 0;
    const std::byte* entry = nullptr;

    // initialize iterator
    void initialize(const std::byte* data) {

        current = data;

        security_definition_message = SecurityDefinitionMessage::parse(current);
        current += sizeof(SecurityDefinitionMessage);

        no_legs = security_definition_message->no_legs.get();
        entry_index = 0;
        entry = nullptr;
    }

    // next entry
    bool next() {

        if (entry_index >= no_legs) {
            return false;
        }

        entry = current;
        entry_index++;

        return true;
    }

    // advance past processed entry
    void advance(std::size_t bytes) {
        current += bytes;
    }

    // reset iterator
    void reset() {
        current = nullptr;

        security_definition_message = nullptr;

        no_legs = 0;
        entry_index = 0;
        entry = nullptr;
    }
};
}
