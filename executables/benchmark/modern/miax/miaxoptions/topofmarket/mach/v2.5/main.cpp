// Miax.MiaxOptions.TopOfMarket.Mach.v2.5: main.cpp
// Miax.MiaxOptions.TopOfMarket.Mach.v2.5 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/miax/miaxoptions/topofmarket/mach/v2.5.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/miax/miaxoptions/topofmarket/mach/v2.5/definitions.hpp"

namespace protocol = ::miax::miaxoptions::topofmarket::mach::v2_5;

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
            } else if (message->message_type.get() == protocol::SimpleSeriesUpdateMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::SimpleSeriesUpdateMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
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
            } else if (message->message_type.get() == protocol::SystemStateMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::SystemStateMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->to_m_version.get());
                checksum += bench::digest(message_2->session_id.get());
                checksum += bench::digest(message_2->system_status.get());
            } else if (message->message_type.get() == protocol::SimpleTopOfMarketBestBidOrOfferCompactBidMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::SimpleTopOfMarketBestBidOrOfferCompactBidMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->product_id.get());
                checksum += bench::digest(message_2->mbbo_price_short.integer());
                checksum += bench::digest(message_2->mbbo_size_short.get());
                checksum += bench::digest(message_2->mbbo_priority_customer_size_short.get());
                checksum += bench::digest(message_2->mbbo_condition.get());
            } else if (message->message_type.get() == protocol::SimpleTopOfMarketBestBidOrOfferCompactOfferMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::SimpleTopOfMarketBestBidOrOfferCompactOfferMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->product_id.get());
                checksum += bench::digest(message_2->mbbo_price_short.integer());
                checksum += bench::digest(message_2->mbbo_size_short.get());
                checksum += bench::digest(message_2->mbbo_priority_customer_size_short.get());
                checksum += bench::digest(message_2->mbbo_condition.get());
            } else if (message->message_type.get() == protocol::SimpleTopOfMarketBestBidOrOfferWideBidMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::SimpleTopOfMarketBestBidOrOfferWideBidMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->product_id.get());
                checksum += bench::digest(message_2->mbbo_price_long.integer());
                checksum += bench::digest(message_2->mbbo_size_long.get());
                checksum += bench::digest(message_2->mbbo_priority_customer_size_long.get());
                checksum += bench::digest(message_2->mbbo_condition.get());
            } else if (message->message_type.get() == protocol::SimpleTopOfMarketBestBidOrOfferWideOfferMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::SimpleTopOfMarketBestBidOrOfferWideOfferMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->product_id.get());
                checksum += bench::digest(message_2->mbbo_price_long.integer());
                checksum += bench::digest(message_2->mbbo_size_long.get());
                checksum += bench::digest(message_2->mbbo_priority_customer_size_long.get());
                checksum += bench::digest(message_2->mbbo_condition.get());
            } else if (message->message_type.get() == protocol::SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->product_id.get());
                checksum += bench::digest(message_2->bid_price_short.integer());
                checksum += bench::digest(message_2->bid_size_short.get());
                checksum += bench::digest(message_2->bid_priority_customer_size_short.get());
                checksum += bench::digest(message_2->bid_condition.get());
                checksum += bench::digest(message_2->offer_price_short.integer());
                checksum += bench::digest(message_2->offer_size_short.get());
                checksum += bench::digest(message_2->offer_priority_customer_size_short.get());
                checksum += bench::digest(message_2->offer_condition.get());
            } else if (message->message_type.get() == protocol::SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->product_id.get());
                checksum += bench::digest(message_2->bid_price_long.integer());
                checksum += bench::digest(message_2->bid_size_long.get());
                checksum += bench::digest(message_2->bid_priority_customer_size_long.get());
                checksum += bench::digest(message_2->bid_condition.get());
                checksum += bench::digest(message_2->offer_price_long.integer());
                checksum += bench::digest(message_2->offer_size_long.get());
                checksum += bench::digest(message_2->offer_priority_customer_size_long.get());
                checksum += bench::digest(message_2->offer_condition.get());
            } else if (message->message_type.get() == protocol::LastSaleMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::LastSaleMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->product_id.get());
                checksum += bench::digest(message_2->trade_id.get());
                checksum += bench::digest(message_2->correction_number.get());
                checksum += bench::digest(message_2->reference_trade_id.get());
                checksum += bench::digest(message_2->reference_correction_number.get());
                checksum += bench::digest(message_2->trade_price.integer());
                checksum += bench::digest(message_2->trade_size.get());
                checksum += bench::digest(message_2->trade_condition.get());
            } else if (message->message_type.get() == protocol::TradeCancelMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::TradeCancelMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->product_id.get());
                checksum += bench::digest(message_2->trade_id.get());
                checksum += bench::digest(message_2->correction_number.get());
                checksum += bench::digest(message_2->trade_price.integer());
                checksum += bench::digest(message_2->trade_size.get());
                checksum += bench::digest(message_2->trade_condition.get());
            } else if (message->message_type.get() == protocol::UnderlyingTradingStatusNotificationMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::UnderlyingTradingStatusNotificationMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
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
    return bench::run("Miax.MiaxOptions.TopOfMarket.Mach.v2.5", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
