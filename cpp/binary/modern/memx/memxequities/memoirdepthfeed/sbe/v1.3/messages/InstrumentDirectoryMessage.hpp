#pragma once

#include "../types/Timestamp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/Symbol.hpp"
#include "../types/SymbolSfx.hpp"
#include "../types/RoundLot.hpp"
#include "../types/Reserved.hpp"
#include "../types/IsTestSymbol.hpp"
#include "../types/Mpv.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

#pragma pack(push, 1)

// InstrumentDirectoryMessage
struct InstrumentDirectoryMessage {

    Timestamp timestamp;
    SecurityId security_id;
    Symbol symbol;
    SymbolSfx symbol_sfx;
    RoundLot round_lot;
    Reserved reserved;
    IsTestSymbol is_test_symbol;
    Mpv mpv;

    // parse method
    static InstrumentDirectoryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<InstrumentDirectoryMessage*>(buffer);
    }

    // parse method const
    static const InstrumentDirectoryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const InstrumentDirectoryMessage*>(buffer);
    }
};

#pragma pack(pop)
}
