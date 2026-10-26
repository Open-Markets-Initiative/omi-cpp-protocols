#pragma once

#include "../types/SecurityId.hpp"
#include "../types/LastPx.hpp"
#include "../types/LastQty.hpp"
#include "../types/Side.hpp"
#include "../types/CrossRequestType.hpp"
#include "../types/InputSource.hpp"
#include "../types/Pad5.hpp"
#include "../types/TransactTime.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

#pragma pack(push, 1)

// 
struct CrossRequest {

    SecurityId security_id;
    LastPx last_px;
    LastQty last_qty;
    Side side;
    CrossRequestType cross_request_type;
    InputSource input_source;
    Pad5 pad5;
    TransactTime transact_time;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13502;

    // parse method
    static CrossRequest* parse(std::byte* buffer) {
        return reinterpret_cast<CrossRequest*>(buffer);
    }

    // parse method const
    static const CrossRequest* parse(const std::byte* buffer) {
        return reinterpret_cast<const CrossRequest*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const CrossRequest* parse(const MessageHeaderComp* header) {
        return reinterpret_cast<const CrossRequest*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeaderComp));
    }
};

#pragma pack(pop)
}
