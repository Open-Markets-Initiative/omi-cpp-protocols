// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: iterators/RequestedMatchingEngineIterator.hpp
#pragma once

#include "../definitions.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {
// RequestedMatchingEngineIterator
struct RequestedMatchingEngineIterator {

    const std::byte* current = nullptr;

    const LoginRequest* login_request = nullptr;

    std::uint8_t number_of_matching_engines = 0;
    std::uint8_t entry_index = 0;
    const std::byte* entry = nullptr;

    // initialize iterator
    void initialize(const std::byte* data) {

        current = data;

        login_request = LoginRequest::parse(current);
        current += sizeof(LoginRequest);

        number_of_matching_engines = login_request->number_of_matching_engines.get();
        entry_index = 0;
        entry = nullptr;
    }

    // next entry
    bool next() {

        if (entry_index >= number_of_matching_engines) {
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

        login_request = nullptr;

        number_of_matching_engines = 0;
        entry_index = 0;
        entry = nullptr;
    }
};
}
