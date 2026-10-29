#pragma once

#include "ComplexStrategyAuctionMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

namespace itch_ordercombofeed = ::nasdaq::iseoptions::ordercombofeed::itch::v1_1;


inline external_count_iterator<complex_strategy_auction_message_auction_response_entry> read_auction_response(const complex_strategy_auction_message& msg) {
    return { msg.tail_begin(), msg.fields.number_of_responses.get().value(), msg.tail_end() };
}

}
