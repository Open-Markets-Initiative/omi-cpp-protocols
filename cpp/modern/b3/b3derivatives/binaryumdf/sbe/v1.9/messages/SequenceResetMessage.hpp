#pragma once


namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

#pragma pack(push, 1)

// Action
struct SequenceResetMessage {


    // parse method
    static SequenceResetMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SequenceResetMessage*>(buffer);
    }

    // parse method const
    static const SequenceResetMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SequenceResetMessage*>(buffer);
    }
};

#pragma pack(pop)
}
