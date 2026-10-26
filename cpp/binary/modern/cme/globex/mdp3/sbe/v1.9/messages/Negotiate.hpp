#pragma once

#include "../types/HmacSignature.hpp"
#include "../types/AccessKeyId.hpp"
#include "../types/Uuid.hpp"
#include "../types/RequestTimestamp.hpp"
#include "../types/Session.hpp"
#include "../types/Firm.hpp"
#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::mdp3::v9 {

#pragma pack(push, 1)

// Negotiate
struct Negotiate {

    HmacSignature hmac_signature;
    AccessKeyId access_key_id;
    Uuid uuid;
    RequestTimestamp request_timestamp;
    Session session;
    Firm firm;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 200;

    // parse method
    static Negotiate* parse(std::byte* buffer) {
        return reinterpret_cast<Negotiate*>(buffer);
    }

    // parse method const
    static const Negotiate* parse(const std::byte* buffer) {
        return reinterpret_cast<const Negotiate*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const Negotiate* parse(const SimpleBinaryHeader* header) {
        return reinterpret_cast<const Negotiate*>(reinterpret_cast<const std::byte*>(header) + sizeof(SimpleBinaryHeader));
    }
};

#pragma pack(pop)
}
