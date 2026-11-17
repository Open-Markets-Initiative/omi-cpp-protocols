// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: messages/HeartbeatMessage.hpp
#pragma once


namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

// This message contains only a standard header. The heartbeat will repeat at a regular interval
struct HeartbeatMessage {


    // parse method
    static HeartbeatMessage* parse(std::byte* buffer) {
        return reinterpret_cast<HeartbeatMessage*>(buffer);
    }

    // parse method const
    static const HeartbeatMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const HeartbeatMessage*>(buffer);
    }
};

#pragma pack(pop)
}
