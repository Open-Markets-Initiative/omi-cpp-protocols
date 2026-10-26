#pragma once

#include "../types/MdEntrySize.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/Padding7.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct IncrementalRefreshVolumeLongGroup {

    MdEntrySize md_entry_size;
    SecurityId security_id;
    RptSeq rpt_seq;
    MdUpdateAction md_update_action;
    Padding7 padding_7;

    // parse method
    static IncrementalRefreshVolumeLongGroup* parse(std::byte* buffer) {
        return reinterpret_cast<IncrementalRefreshVolumeLongGroup*>(buffer);
    }

    // parse method const
    static const IncrementalRefreshVolumeLongGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const IncrementalRefreshVolumeLongGroup*>(buffer);
    }
};

#pragma pack(pop)
}
