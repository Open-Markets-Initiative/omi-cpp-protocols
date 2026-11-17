// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: messages/details/IndexValueMessageReader.hpp
#pragma once

#include "IndexValueMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;


inline sbe_var_data<std::uint8_t> read_symbol(const index_value_message& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

template<typename CountT>
inline external_count_iterator<index_value_message_index_value_md_entry_entry> read_index_value_md_entry(const std::byte* pos, CountT count, const index_value_message& msg) {
    return { pos, count, msg.tail_end() };
}

}
