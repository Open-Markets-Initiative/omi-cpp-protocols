#pragma once

#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/BreachedLevel.hpp"
#include "../messages/SequencedDataPacket.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

#pragma pack(push, 1)

// Informs data recipients when a MWCB has breached one of the established levels
struct MwcbStatusLevelMessage {

    StockLocate stock_locate;
    TrackingNumber tracking_number;
    Timestamp timestamp;
    BreachedLevel breached_level;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'W';

    // parse method
    static MwcbStatusLevelMessage* parse(std::byte* buffer) {
        return reinterpret_cast<MwcbStatusLevelMessage*>(buffer);
    }

    // parse method const
    static const MwcbStatusLevelMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const MwcbStatusLevelMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MwcbStatusLevelMessage* parse(const SequencedDataPacket* header) {
        return reinterpret_cast<const MwcbStatusLevelMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(SequencedDataPacket));
    }
};

#pragma pack(pop)
}
