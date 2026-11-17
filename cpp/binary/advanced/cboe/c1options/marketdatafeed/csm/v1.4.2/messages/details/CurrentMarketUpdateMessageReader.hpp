// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: messages/details/CurrentMarketUpdateMessageReader.hpp
#pragma once

#include "CurrentMarketUpdateMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;


inline external_count_iterator<current_market_update_message_md_entry_entry> read_md_entry(const current_market_update_message& msg) {
    return { msg.tail_begin(), msg.fields.no_entries.get().value(), msg.tail_end() };
}

}
