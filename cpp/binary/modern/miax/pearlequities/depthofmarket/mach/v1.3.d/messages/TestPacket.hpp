// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/TestPacket.hpp
#pragma once

#include "../structs/EsesmPacketHeader.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

// Test packets are intended to provide human readable text that may aid in debugging problems
struct TestPacket {


    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'T';

    // parse method
    static TestPacket* parse(std::byte* buffer) {
        return reinterpret_cast<TestPacket*>(buffer);
    }

    // parse method const
    static const TestPacket* parse(const std::byte* buffer) {
        return reinterpret_cast<const TestPacket*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TestPacket* parse(const EsesmPacketHeader* header) {
        return reinterpret_cast<const TestPacket*>(reinterpret_cast<const std::byte*>(header) + sizeof(EsesmPacketHeader));
    }
};

#pragma pack(pop)
}
