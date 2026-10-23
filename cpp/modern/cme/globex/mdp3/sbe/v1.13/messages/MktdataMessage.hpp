#pragma once


namespace cme::mdp3::v13 {

#pragma pack(push, 1)

// Message of sbe schema mktdata (schema id 1)
struct MktdataMessage {


    // parse method
    static MktdataMessage* parse(std::byte* buffer) {
        return reinterpret_cast<MktdataMessage*>(buffer);
    }

    // parse method const
    static const MktdataMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const MktdataMessage*>(buffer);
    }
};

#pragma pack(pop)
}
