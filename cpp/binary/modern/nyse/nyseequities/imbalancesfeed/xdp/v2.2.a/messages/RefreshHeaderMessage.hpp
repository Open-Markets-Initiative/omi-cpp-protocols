#pragma once

#include "../types/CurrentRefreshPkt.hpp"
#include "../types/TotalRefreshPkts.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

#pragma pack(push, 1)

// The first message in each packet of refresh messages published over the Refresh multicast channels is of this type.
struct RefreshHeaderMessage {

    CurrentRefreshPkt current_refresh_pkt;
    TotalRefreshPkts total_refresh_pkts;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 35;

    // parse method
    static RefreshHeaderMessage* parse(std::byte* buffer) {
        return reinterpret_cast<RefreshHeaderMessage*>(buffer);
    }

    // parse method const
    static const RefreshHeaderMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const RefreshHeaderMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const RefreshHeaderMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const RefreshHeaderMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
