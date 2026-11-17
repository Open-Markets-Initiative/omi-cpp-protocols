// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: messages/details/MarketDataRefreshMessageReader.hpp
#pragma once

#include "MarketDataRefreshMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;


inline external_count_iterator<market_data_refresh_message_md_entry_entry> read_md_entry(const market_data_refresh_message& msg) {
    return { msg.tail_begin(), msg.fields.no_entries.get().value(), msg.tail_end() };
}

}
