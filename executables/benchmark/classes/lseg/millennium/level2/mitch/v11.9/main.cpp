// Lseg.Millennium.Level2.Mitch.v11.9 benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/lseg/millennium/level2/mitch/v11.9.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "executables/benchmark/Benchmark.hpp"
#include "cpp/binary/classes/lseg/millennium/level2/mitch/v11.9/definitions.hpp"

namespace protocol = ::lseg::millennium::level2::mitch::v11_9;

namespace {

// The values the Classes Packet decodes from one datagram, folded into a checksum. A datagram it cannot
// decode is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::Packet packet;

    try {
        packet.decode(frame.payload, frame.payload_len);
    } catch (const protocol::DecodeError& error) {
        throw;
        return checksum;
    }

    checksum += bench::digest(packet.unit_header().length());
    checksum += bench::digest(packet.unit_header().message_count());
    checksum += bench::digest(packet.unit_header().market_data_group());
    checksum += bench::digest(packet.unit_header().sequence_number());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_header().message_length());
        checksum += bench::digest(each.message_header().message_type());

        if (const auto* message = dynamic_cast<const protocol::TimeMessage*>(each.message())) {
            checksum += bench::digest((*message).seconds());
        } else if (const auto* message = dynamic_cast<const protocol::SystemEventMessage*>(each.message())) {
            checksum += bench::digest((*message).nanosecond());
            checksum += bench::digest((*message).event_code());
        } else if (const auto* message = dynamic_cast<const protocol::SymbolDirectoryMessage*>(each.message())) {
            checksum += bench::digest((*message).nanosecond());
            checksum += bench::digest((*message).instrument_id());
            checksum += bench::digest((*message).symbol_status());
            checksum += bench::digest((*message).isin());
            checksum += bench::digest((*message).sedol());
            checksum += bench::digest((*message).segment());
            checksum += bench::digest((*message).underlying());
            checksum += bench::digest((*message).currency());
            checksum += bench::digest((*message).previous_close_price());
        } else if (const auto* message = dynamic_cast<const protocol::SymbolStatusMessage*>(each.message())) {
            checksum += bench::digest((*message).nanosecond());
            checksum += bench::digest((*message).instrument_id());
            checksum += bench::digest((*message).trading_status());
            checksum += bench::digest((*message).symbol_status_flags().unused_5());
            checksum += bench::digest((*message).symbol_status_flags().firm_quote());
            checksum += bench::digest((*message).symbol_status_flags().unused_2());
            checksum += bench::digest((*message).reason());
            checksum += bench::digest((*message).session_change_reason());
            checksum += bench::digest((*message).new_end_time());
            checksum += bench::digest((*message).book_type());
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderMessage*>(each.message())) {
            checksum += bench::digest((*message).nanosecond());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).instrument_id());
            checksum += bench::digest((*message).price());
            checksum += bench::digest((*message).add_order_flags().unused_4());
            checksum += bench::digest((*message).add_order_flags().market_order());
            checksum += bench::digest((*message).add_order_flags().unused_1());
            checksum += bench::digest((*message).add_order_flags().private_rfq());
            checksum += bench::digest((*message).add_order_flags().second_unused_1());
        } else if (const auto* message = dynamic_cast<const protocol::AddAttributedOrderMessage*>(each.message())) {
            checksum += bench::digest((*message).nanosecond());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).instrument_id());
            checksum += bench::digest((*message).price());
            checksum += bench::digest((*message).attribution());
            checksum += bench::digest((*message).add_attributed_order_flags().unused_4());
            checksum += bench::digest((*message).add_attributed_order_flags().named_market_order());
            checksum += bench::digest((*message).add_attributed_order_flags().firm_quote());
            checksum += bench::digest((*message).add_attributed_order_flags().unused_2());
        } else if (const auto* message = dynamic_cast<const protocol::OrderDeletedMessage*>(each.message())) {
            checksum += bench::digest((*message).nanosecond());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).order_deleted_flags().unused_5());
            checksum += bench::digest((*message).order_deleted_flags().firm_quote());
            checksum += bench::digest((*message).order_deleted_flags().unused_2());
            checksum += bench::digest((*message).instrument_id());
        } else if (const auto* message = dynamic_cast<const protocol::OrderModifiedMessage*>(each.message())) {
            checksum += bench::digest((*message).nanosecond());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).new_quantity());
            checksum += bench::digest((*message).new_price());
            checksum += bench::digest((*message).order_modified_flags().priority_flag());
            checksum += bench::digest((*message).order_modified_flags().unused_4());
            checksum += bench::digest((*message).order_modified_flags().firm_quote());
            checksum += bench::digest((*message).order_modified_flags().unused_2());
        } else if (const auto* message = dynamic_cast<const protocol::OrderBookClearMessage*>(each.message())) {
            checksum += bench::digest((*message).nanosecond());
            checksum += bench::digest((*message).instrument_id());
            checksum += bench::digest((*message).order_book_clear_flags().unused_5());
            checksum += bench::digest((*message).order_book_clear_flags().firm_quote());
            checksum += bench::digest((*message).order_book_clear_flags().private_rfq());
            checksum += bench::digest((*message).order_book_clear_flags().unused_1());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedMessage*>(each.message())) {
            checksum += bench::digest((*message).nanosecond());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).executed_quantity());
            checksum += bench::digest((*message).trade_match_id());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedWithPriceSizeMessage*>(each.message())) {
            checksum += bench::digest((*message).nanosecond());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).executed_quantity());
            checksum += bench::digest((*message).display_quantity());
            checksum += bench::digest((*message).trade_match_id());
            checksum += bench::digest((*message).printable());
            checksum += bench::digest((*message).price());
        } else if (const auto* message = dynamic_cast<const protocol::TradeMessage*>(each.message())) {
            checksum += bench::digest((*message).nanosecond());
            checksum += bench::digest((*message).executed_quantity());
            checksum += bench::digest((*message).instrument_id());
            checksum += bench::digest((*message).price());
            checksum += bench::digest((*message).trade_match_id());
            checksum += ((*message).cross_type().has_value() ? bench::digest((*(*message).cross_type())) : std::uint64_t{0});
            checksum += bench::digest((*message).sub_book());
            checksum += bench::digest((*message).pt_mod_flags().canc());
            checksum += bench::digest((*message).pt_mod_flags().amnd());
            checksum += bench::digest((*message).pt_mod_flags().unused_6());
        } else if (const auto* message = dynamic_cast<const protocol::AuctionTradeMessage*>(each.message())) {
            checksum += bench::digest((*message).nanosecond());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).instrument_id());
            checksum += bench::digest((*message).price());
            checksum += bench::digest((*message).trade_match_id());
            checksum += bench::digest((*message).auction_type());
            checksum += bench::digest((*message).pt_mod_flags().canc());
            checksum += bench::digest((*message).pt_mod_flags().amnd());
            checksum += bench::digest((*message).pt_mod_flags().unused_6());
        } else if (const auto* message = dynamic_cast<const protocol::AuctionInfoMessage*>(each.message())) {
            checksum += bench::digest((*message).nanosecond());
            checksum += bench::digest((*message).paired_quantity());
            checksum += bench::digest((*message).instrument_id());
            checksum += bench::digest((*message).price());
            checksum += bench::digest((*message).auction_type());
        } else if (const auto* message = dynamic_cast<const protocol::StatisticsMessage*>(each.message())) {
            checksum += bench::digest((*message).nanosecond());
            checksum += bench::digest((*message).instrument_id());
            checksum += bench::digest((*message).statistic_type());
            checksum += bench::digest((*message).price());
            checksum += bench::digest((*message).open_close_price_indicator());
            checksum += bench::digest((*message).statistics_reserved().unused_8());
        } else if (const auto* message = dynamic_cast<const protocol::TopOfBookMessage*>(each.message())) {
            checksum += bench::digest((*message).nanosecond());
            checksum += bench::digest((*message).instrument_id());
            checksum += bench::digest((*message).buy_limit_price());
            checksum += bench::digest((*message).buy_limit_size());
            checksum += bench::digest((*message).sell_limit_price());
            checksum += bench::digest((*message).sell_limit_size());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Lseg.Millennium.Level2.Mitch.v11.9", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
