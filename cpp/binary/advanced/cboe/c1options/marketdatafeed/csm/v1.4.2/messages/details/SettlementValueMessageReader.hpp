// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: messages/details/SettlementValueMessageReader.hpp
#pragma once

#include "SettlementValueMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;


inline external_count_iterator<settlement_value_message_settlement_value_md_entry_entry> read_settlement_value_md_entry(const settlement_value_message& msg) {
    return { msg.tail_begin(), msg.fields.no_entries.get().value(), msg.tail_end() };
}

}
