// Cboe.C1Options.Complex.Pitch.v2.1.18 benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/cboe/c1options/complex/pitch/v2.1.18.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/cboe/c1options/complex/pitch/v2.1.18/definitions.hpp"

namespace protocol = ::cboe::c1options::complex::pitch::v2_1_18;

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
        } else if (const auto* message = dynamic_cast<const protocol::TransactionBegin*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
        } else if (const auto* message = dynamic_cast<const protocol::TransactionEndMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
        } else if (const auto* message = dynamic_cast<const protocol::ComplexInstrumentDefinitionExpandedMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).complex_instrument_id());
            checksum += bench::digest((*message).complex_instrument_underlying());
            checksum += bench::digest((*message).complex_instrument_type());
            checksum += bench::digest((*message).leg_count());
        } else if (const auto* message = dynamic_cast<const protocol::SymbolMappingMessage*>(each.message())) {
            checksum += bench::digest((*message).feed_symbol());
            checksum += bench::digest((*message).osi_symbol());
            checksum += bench::digest((*message).symbol_condition());
            checksum += bench::digest((*message).underlying());
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderLongMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).side_indicator());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).complex_instrument_id());
            checksum += bench::digest((*message).price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderShortMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).side_indicator());
            checksum += bench::digest((*message).quantity_short());
            checksum += bench::digest((*message).complex_instrument_id());
            checksum += bench::digest((*message).price_short().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderExpandedMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).side_indicator());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).complex_instrument_id_8());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).participant_id());
            checksum += bench::digest((*message).customer_indicator());
            checksum += bench::digest((*message).client_id());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).executed_quantity());
            checksum += bench::digest((*message).execution_id());
            checksum += bench::digest((*message).trade_condition());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedAtPriceSizeMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).executed_quantity());
            checksum += bench::digest((*message).remaining_quantity());
            checksum += bench::digest((*message).execution_id());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).trade_condition());
        } else if (const auto* message = dynamic_cast<const protocol::ReduceSizeLongMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).canceled_quantity());
        } else if (const auto* message = dynamic_cast<const protocol::ReduceSizeShortMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).canceled_quantity_short());
        } else if (const auto* message = dynamic_cast<const protocol::ModifyOrderLongMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::ModifyOrderShortMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).quantity_short());
            checksum += bench::digest((*message).price_short().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::DeleteOrderMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
        } else if (const auto* message = dynamic_cast<const protocol::TradeLongMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).side_indicator());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).complex_instrument_id());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).execution_id());
            checksum += bench::digest((*message).trade_condition());
        } else if (const auto* message = dynamic_cast<const protocol::TradeShortMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).side_indicator());
            checksum += bench::digest((*message).quantity_short());
            checksum += bench::digest((*message).complex_instrument_id());
            checksum += bench::digest((*message).price_short().mantissa());
            checksum += bench::digest((*message).execution_id());
            checksum += bench::digest((*message).trade_condition());
        } else if (const auto* message = dynamic_cast<const protocol::AuctionNotificationMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).complex_instrument_id());
            checksum += bench::digest((*message).auction_id());
            checksum += bench::digest((*message).auction_type());
            checksum += bench::digest((*message).side_indicator());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).customer_indicator());
            checksum += bench::digest((*message).participant_id());
            checksum += bench::digest((*message).auction_end_offset());
            checksum += bench::digest((*message).client_id());
        } else if (const auto* message = dynamic_cast<const protocol::AuctionCancelMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).auction_id());
        } else if (const auto* message = dynamic_cast<const protocol::AuctionTradeMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).auction_id());
            checksum += bench::digest((*message).execution_id());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).quantity());
        } else if (const auto* message = dynamic_cast<const protocol::TradingStatusMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).complex_symbol_id());
            checksum += bench::digest((*message).trading_status());
            checksum += bench::digest((*message).gth_trading_status());
        } else if (const auto* message = dynamic_cast<const protocol::AuctionUpdateMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).complex_instrument_id_8());
            checksum += bench::digest((*message).auction_opening_type());
            checksum += bench::digest((*message).reference_price().mantissa());
            checksum += bench::digest((*message).buy_contracts());
            checksum += bench::digest((*message).sell_contracts());
            checksum += bench::digest((*message).indicative_price().mantissa());
            checksum += bench::digest((*message).auction_only_price().mantissa());
            checksum += bench::digest((*message).opening_condition());
            checksum += bench::digest((*message).composite_market_bid_price().mantissa());
            checksum += bench::digest((*message).composite_market_offer_price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::AuctionSummaryMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).complex_instrument_id_8());
            checksum += bench::digest((*message).auction_opening_type());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).quantity());
        } else if (const auto* message = dynamic_cast<const protocol::EndOfSessionMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Cboe.C1Options.Complex.Pitch.v2.1.18", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
