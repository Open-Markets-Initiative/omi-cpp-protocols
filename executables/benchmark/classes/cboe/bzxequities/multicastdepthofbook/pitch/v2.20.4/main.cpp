// Cboe.BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4 benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/definitions.hpp"

namespace protocol = ::cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4;

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

    checksum += bench::digest(packet.packet_header().length());
    checksum += bench::digest(packet.packet_header().message_count());
    checksum += bench::digest(packet.packet_header().unit());
    checksum += bench::digest(packet.packet_header().sequence());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_header().message_length());
        checksum += bench::digest(each.message_header().message_type());

        if (const auto* message = dynamic_cast<const protocol::TimeMessage*>(each.message())) {
            checksum += bench::digest((*message).time());
        } else if (const auto* message = dynamic_cast<const protocol::UnitClearMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderLongMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).side_indicator());
            checksum += bench::digest((*message).quantity_binary_4());
            checksum += bench::digest((*message).symbol_short());
            checksum += bench::digest((*message).price_binary_long_price_8().mantissa());
            checksum += bench::digest((*message).add_flags().display());
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderShortMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).side_indicator());
            checksum += bench::digest((*message).quantity_binary_2());
            checksum += bench::digest((*message).symbol_short());
            checksum += bench::digest((*message).price_binary_short_price_2().mantissa());
            checksum += bench::digest((*message).add_flags().display());
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderExpandedMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).side_indicator());
            checksum += bench::digest((*message).quantity_binary_4());
            checksum += bench::digest((*message).symbol_long());
            checksum += bench::digest((*message).price_binary_long_price_8().mantissa());
            checksum += bench::digest((*message).add_flags().display());
            checksum += bench::digest((*message).participant_id());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).executed_quantity());
            checksum += bench::digest((*message).execution_id());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedAtPriceSizeMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).executed_quantity());
            checksum += bench::digest((*message).remaining_quantity());
            checksum += bench::digest((*message).execution_id());
            checksum += bench::digest((*message).price_binary_long_price_8().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::ReduceSizeLongMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).canceled_quantity_binary_4());
        } else if (const auto* message = dynamic_cast<const protocol::ReduceSizeShortMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).canceled_quantity_binary_2());
        } else if (const auto* message = dynamic_cast<const protocol::ModifyOrderLongMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).quantity_binary_4());
            checksum += bench::digest((*message).price_binary_long_price_8().mantissa());
            checksum += bench::digest((*message).modify_flags().display());
            checksum += bench::digest((*message).modify_flags().maintain_priority());
        } else if (const auto* message = dynamic_cast<const protocol::ModifyOrderShortMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).quantity_binary_2());
            checksum += bench::digest((*message).price_binary_short_price_2().mantissa());
            checksum += bench::digest((*message).modify_flags().display());
            checksum += bench::digest((*message).modify_flags().maintain_priority());
        } else if (const auto* message = dynamic_cast<const protocol::DeleteOrderMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
        } else if (const auto* message = dynamic_cast<const protocol::TradeLongMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).side_indicator());
            checksum += bench::digest((*message).quantity_binary_4());
            checksum += bench::digest((*message).symbol_short());
            checksum += bench::digest((*message).price_binary_long_price_8().mantissa());
            checksum += bench::digest((*message).execution_id());
        } else if (const auto* message = dynamic_cast<const protocol::TradeShortMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).side_indicator());
            checksum += bench::digest((*message).quantity_binary_2());
            checksum += bench::digest((*message).symbol_short());
            checksum += bench::digest((*message).price_binary_short_price_2().mantissa());
            checksum += bench::digest((*message).execution_id());
        } else if (const auto* message = dynamic_cast<const protocol::TradeExpandedMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).side_indicator());
            checksum += bench::digest((*message).quantity_binary_4());
            checksum += bench::digest((*message).symbol_long());
            checksum += bench::digest((*message).price_binary_long_price_8().mantissa());
            checksum += bench::digest((*message).execution_id());
        } else if (const auto* message = dynamic_cast<const protocol::TradeBreakMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).execution_id());
        } else if (const auto* message = dynamic_cast<const protocol::EndOfSessionMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
        } else if (const auto* message = dynamic_cast<const protocol::SymbolMappingMessage*>(each.message())) {
            checksum += bench::digest((*message).feed_symbol());
            checksum += bench::digest((*message).osi_symbol());
            checksum += bench::digest((*message).symbol_condition());
        } else if (const auto* message = dynamic_cast<const protocol::TradingStatusMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).symbol_long());
            checksum += bench::digest((*message).trading_status());
            checksum += bench::digest((*message).reg_sho_action());
            checksum += bench::digest((*message).reserved_1());
            checksum += bench::digest((*message).second_reserved_1());
        } else if (const auto* message = dynamic_cast<const protocol::AuctionUpdateMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).stock_symbol());
            checksum += bench::digest((*message).auction_type());
            checksum += bench::digest((*message).reference_price());
            checksum += bench::digest((*message).buy_shares());
            checksum += bench::digest((*message).sell_shares());
            checksum += bench::digest((*message).indicative_price());
            checksum += bench::digest((*message).auction_only_price());
        } else if (const auto* message = dynamic_cast<const protocol::AuctionSummaryMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).stock_symbol());
            checksum += bench::digest((*message).auction_type());
            checksum += bench::digest((*message).price_binary_8());
            checksum += bench::digest((*message).shares());
        } else if (const auto* message = dynamic_cast<const protocol::RetailPriceImprovementMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).symbol_long());
            checksum += bench::digest((*message).retail_price_improvement());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Cboe.BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
