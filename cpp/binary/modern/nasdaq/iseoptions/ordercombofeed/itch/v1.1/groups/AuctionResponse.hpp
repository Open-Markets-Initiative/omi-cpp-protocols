#pragma once

#include "../types/ResponsePrice.hpp"
#include "../types/ResponseSize.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

#pragma pack(push, 1)

struct AuctionResponse {

    ResponsePrice response_price;
    ResponseSize response_size;

    // parse method
    static AuctionResponse* parse(std::byte* buffer) {
        return reinterpret_cast<AuctionResponse*>(buffer);
    }

    // parse method const
    static const AuctionResponse* parse(const std::byte* buffer) {
        return reinterpret_cast<const AuctionResponse*>(buffer);
    }
};

#pragma pack(pop)
}
