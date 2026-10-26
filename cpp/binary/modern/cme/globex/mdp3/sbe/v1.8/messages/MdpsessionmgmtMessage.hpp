#pragma once


namespace cme::mdp3::v8 {

#pragma pack(push, 1)

// Message of sbe schema mdpsessionmgmt (schema id 2)
struct MdpsessionmgmtMessage {


    // parse method
    static MdpsessionmgmtMessage* parse(std::byte* buffer) {
        return reinterpret_cast<MdpsessionmgmtMessage*>(buffer);
    }

    // parse method const
    static const MdpsessionmgmtMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const MdpsessionmgmtMessage*>(buffer);
    }
};

#pragma pack(pop)
}
