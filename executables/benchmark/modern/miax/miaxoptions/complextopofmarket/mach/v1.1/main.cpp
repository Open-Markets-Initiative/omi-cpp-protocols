// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: main.cpp
// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/miax/miaxoptions/complextopofmarket/mach/v1.1.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/miax/miaxoptions/complextopofmarket/mach/v1.1/definitions.hpp"

namespace protocol = ::miax::miaxoptions::complextopofmarket::mach::v1_1;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MachMessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.mach_packet_header->sequence_number.get());
        checksum += bench::digest(iterator.mach_packet_header->packet_length.get());
        checksum += bench::digest(iterator.mach_packet_header->packet_type.get());
        checksum += bench::digest(iterator.mach_packet_header->session_number.get());

        if (iterator.packet_type == 3) {
            [[maybe_unused]] const auto* message = protocol::ApplicationMessage::parse(iterator.message);
            checksum += bench::digest(message->message_type.get());
            if (message->message_type.get() == protocol::SystemTimeMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::SystemTimeMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->seconds.get());
            } else if (message->message_type.get() == protocol::SeriesUpdate::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::SeriesUpdate::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->product_id.get());
                checksum += bench::digest(message_2->underlying_symbol.get());
                checksum += bench::digest(message_2->security_symbol.get());
                checksum += bench::digest(message_2->expiration_date.get());
                checksum += bench::digest(message_2->strike_price.integer());
                checksum += bench::digest(message_2->call_or_put.get());
                checksum += bench::digest(message_2->opening_time.get());
                checksum += bench::digest(message_2->closing_time.get());
                checksum += bench::digest(message_2->restricted_option.get());
                checksum += bench::digest(message_2->long_term_option.get());
                checksum += bench::digest(message_2->active_on_miax.get());
                checksum += bench::digest(message_2->miax_bbo_posting_increment_indicator.get());
                checksum += bench::digest(message_2->liquidity_acceptance_increment_indicator.get());
                checksum += bench::digest(message_2->opening_underlying_market_code.get());
                checksum += bench::digest(message_2->priority_quote_width.integer());
            } else if (message->message_type.get() == protocol::ComplexStrategyDefinitionMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::ComplexStrategyDefinitionMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->strategy_id.get());
                checksum += bench::digest(message_2->underlying_symbol.get());
                checksum += bench::digest(message_2->active_on_miax.get());
                checksum += bench::digest(message_2->update_reason.get());
                checksum += bench::digest(message_2->number_of_legs.get());
            } else if (message->message_type.get() == protocol::SystemStateMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::SystemStateMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->c_to_m_version.get());
                checksum += bench::digest(message_2->session_id.get());
                checksum += bench::digest(message_2->system_status.get());
            } else if (message->message_type.get() == protocol::CompactComplexTopOfMarketBidMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::CompactComplexTopOfMarketBidMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->strategy_id.get());
                checksum += bench::digest(message_2->compact_price.integer());
                checksum += bench::digest(message_2->compact_size.get());
                checksum += bench::digest(message_2->top_of_market_quote_condition.get());
            } else if (message->message_type.get() == protocol::CompactComplexTopOfMarketOfferMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::CompactComplexTopOfMarketOfferMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->strategy_id.get());
                checksum += bench::digest(message_2->compact_price.integer());
                checksum += bench::digest(message_2->compact_size.get());
                checksum += bench::digest(message_2->top_of_market_quote_condition.get());
            } else if (message->message_type.get() == protocol::WideComplexTopOfMarketBidMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::WideComplexTopOfMarketBidMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->strategy_id.get());
                checksum += bench::digest(message_2->wide_price.integer());
                checksum += bench::digest(message_2->wide_size.get());
                checksum += bench::digest(message_2->top_of_market_quote_condition.get());
            } else if (message->message_type.get() == protocol::WideComplexTopOfMarketOfferMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::WideComplexTopOfMarketOfferMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->strategy_id.get());
                checksum += bench::digest(message_2->wide_price.integer());
                checksum += bench::digest(message_2->wide_size.get());
                checksum += bench::digest(message_2->top_of_market_quote_condition.get());
            } else if (message->message_type.get() == protocol::CompactComplexDoubleSidedTopOfMarketMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::CompactComplexDoubleSidedTopOfMarketMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->strategy_id.get());
                checksum += bench::digest(message_2->compact_bid.compact_bid_price.integer());
                checksum += bench::digest(message_2->compact_bid.compact_bid_size.get());
                checksum += bench::digest(message_2->compact_bid.bid_condition.get());
                checksum += bench::digest(message_2->compact_offer.compact_offer_price.integer());
                checksum += bench::digest(message_2->compact_offer.compact_offer_size.get());
                checksum += bench::digest(message_2->compact_offer.offer_condition.get());
            } else if (message->message_type.get() == protocol::WideComplexDoubleSidedTopOfMarketMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::WideComplexDoubleSidedTopOfMarketMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->strategy_id.get());
                checksum += bench::digest(message_2->wide_bid.wide_bid_price.integer());
                checksum += bench::digest(message_2->wide_bid.wide_bid_size.get());
                checksum += bench::digest(message_2->wide_bid.bid_condition.get());
                checksum += bench::digest(message_2->wide_offer.wide_offer_price.integer());
                checksum += bench::digest(message_2->wide_offer.wide_offer_size.get());
                checksum += bench::digest(message_2->wide_offer.offer_condition.get());
            } else if (message->message_type.get() == protocol::StrategyTradeMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::StrategyTradeMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->strategy_id.get());
                checksum += bench::digest(message_2->trade_id.get());
                checksum += bench::digest(message_2->net_price.integer());
                checksum += bench::digest(message_2->trade_size.get());
                checksum += bench::digest(message_2->trade_condition.get());
            } else if (message->message_type.get() == protocol::UnderlyingTradingStatusMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::UnderlyingTradingStatusMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->underlying_symbol.get());
                checksum += bench::digest(message_2->trading_status.get());
                checksum += bench::digest(message_2->event_reason.get());
                checksum += (static_cast<std::uint32_t>(message_2->expected_event_time_seconds_part.get()) != 0x0U ? bench::digest(message_2->expected_event_time_seconds_part.get()) : std::uint64_t{0});
                checksum += bench::digest(message_2->expected_event_time_nano_seconds_part.get());
            }
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
