#pragma once

#include "../types/MdEntrySize.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/Padding3.hpp"

namespace cme::mdp3::v8 {

#pragma pack(push, 1)

struct IncrementalRefreshVolumeGroup {

    MdEntrySize md_entry_size;
    SecurityId security_id;
    RptSeq rpt_seq;
    MdUpdateAction md_update_action;
    Padding3 padding_3;

    // parse method
    static IncrementalRefreshVolumeGroup* parse(std::byte* buffer) {
        return reinterpret_cast<IncrementalRefreshVolumeGroup*>(buffer);
    }

    // parse method const
    static const IncrementalRefreshVolumeGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const IncrementalRefreshVolumeGroup*>(buffer);
    }
};

#pragma pack(pop)
}
