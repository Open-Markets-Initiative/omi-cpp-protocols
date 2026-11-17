// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: messages/details/TickerMessageReader.hpp
#pragma once

#include "TickerMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;


inline external_count_iterator<ticker_message_ticker_md_entry_entry> read_ticker_md_entry(const ticker_message& msg) {
    return { msg.tail_begin(), msg.fields.no_entries.get().value(), msg.tail_end() };
}

}
