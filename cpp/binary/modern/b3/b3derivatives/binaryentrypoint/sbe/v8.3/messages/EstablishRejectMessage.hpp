#pragma once

#include "../types/SessionId.hpp"
#include "../types/SessionVerId.hpp"
#include "../types/RequestTimestamp.hpp"
#include "../types/EstablishmentRejectCode.hpp"
#include "../types/Offset21Padding1.hpp"
#include "../types/LastIncomingSeqNoOptional.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

// EstablishRejectMessage
struct EstablishRejectMessage {

    SessionId session_id;
    SessionVerId session_ver_id;
    RequestTimestamp request_timestamp;
    EstablishmentRejectCode establishment_reject_code;
    Offset21Padding1 offset_21_padding_1;
    LastIncomingSeqNoOptional last_incoming_seq_no_optional;

    // parse method
    static EstablishRejectMessage* parse(std::byte* buffer) {
        return reinterpret_cast<EstablishRejectMessage*>(buffer);
    }

    // parse method const
    static const EstablishRejectMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const EstablishRejectMessage*>(buffer);
    }
};

#pragma pack(pop)
}
