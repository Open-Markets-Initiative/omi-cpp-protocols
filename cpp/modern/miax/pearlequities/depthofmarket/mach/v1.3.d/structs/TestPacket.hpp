#pragma once


namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

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
