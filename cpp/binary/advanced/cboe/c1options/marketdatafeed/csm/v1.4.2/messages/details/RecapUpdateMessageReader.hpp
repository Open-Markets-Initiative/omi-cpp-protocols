// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: messages/details/RecapUpdateMessageReader.hpp
#pragma once

#include "RecapUpdateMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;


inline external_count_iterator<recap_update_message_recap_update_md_entry_entry> read_recap_update_md_entry(const recap_update_message& msg) {
    return { msg.tail_begin(), msg.fields.no_entries.get().value(), msg.tail_end() };
}

}
