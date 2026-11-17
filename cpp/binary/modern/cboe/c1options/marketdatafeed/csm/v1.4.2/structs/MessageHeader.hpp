// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: structs/MessageHeader.hpp
#pragma once

#include "../types/MessageLength.hpp"
#include "../types/TemplateId.hpp"
#include "../types/MessageType.hpp"
#include "../types/MsgSeqNum.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct MessageHeader {

    MessageLength message_length;
    TemplateId template_id;
    MessageType message_type;
    MsgSeqNum msg_seq_num;

    // parse method
    static MessageHeader* parse(std::byte* buffer) {
        return reinterpret_cast<MessageHeader*>(buffer);
    }

    // parse method const
    static const MessageHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const MessageHeader*>(buffer);
    }
};

#pragma pack(pop)
}
