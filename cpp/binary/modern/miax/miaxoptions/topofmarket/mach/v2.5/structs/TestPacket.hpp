// Miax.MiaxOptions.TopOfMarket.Mach.v2.5: structs/TestPacket.hpp
#pragma once


namespace miax::miaxoptions::topofmarket::mach::v2_5 {

#pragma pack(push, 1)

struct TestPacket {


    // parse method
    static TestPacket* parse(std::byte* buffer) {
        return reinterpret_cast<TestPacket*>(buffer);
    }

    // parse method const
    static const TestPacket* parse(const std::byte* buffer) {
        return reinterpret_cast<const TestPacket*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TestPacket* parse(const SesmPacketHeader* header) {
        return reinterpret_cast<const TestPacket*>(reinterpret_cast<const std::byte*>(header) + sizeof(SesmPacketHeader));
    }
};

#pragma pack(pop)
}
