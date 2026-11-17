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
};

#pragma pack(pop)
}
