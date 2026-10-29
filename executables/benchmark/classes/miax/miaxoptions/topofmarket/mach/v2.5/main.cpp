// Miax.MiaxOptions.TopOfMarket.Mach.v2.5 benchmark, through the Classes Packet: every value it reads from every message of the simulated
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
#include "cpp/binary/classes/miax/miaxoptions/topofmarket/mach/v2.5/definitions.hpp"

namespace protocol = ::miax::miaxoptions::topofmarket::mach::v2_5;

namespace {

// The values the Classes Packet decodes from one datagram, folded into a checksum. A datagram it cannot
// decode is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::UdpPacket packet;

    try {
        packet.decode(frame.payload, frame.payload_len);
    } catch (const protocol::DecodeError& error) {
        throw;
        return checksum;
    }


    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.mach_packet_header().sequence_number());
        checksum += bench::digest(each.mach_packet_header().packet_length());
        checksum += bench::digest(each.mach_packet_header().packet_type());
        checksum += bench::digest(each.mach_packet_header().session_number());

        if (const auto* message = dynamic_cast<const protocol::ApplicationMessage*>(each.message())) {
            checksum += bench::digest((*message).message_type_field());
            if (const auto* message_2 = dynamic_cast<const protocol::SystemTimeMessage*>(message->data())) {
                checksum += bench::digest((*message_2).seconds());
            } else if (const auto* message_2 = dynamic_cast<const protocol::SimpleSeriesUpdateMessage*>(message->data())) {
                checksum += bench::digest((*message_2).nanoseconds());
                checksum += bench::digest((*message_2).product_id());
                checksum += bench::digest((*message_2).underlying_symbol());
                checksum += bench::digest((*message_2).security_symbol());
                checksum += bench::digest((*message_2).expiration_date());
                checksum += bench::digest((*message_2).strike_price().mantissa());
                checksum += bench::digest((*message_2).call_or_put());
                checksum += bench::digest((*message_2).opening_time());
                checksum += bench::digest((*message_2).closing_time());
                checksum += bench::digest((*message_2).restricted_option());
                checksum += bench::digest((*message_2).long_term_option());
                checksum += bench::digest((*message_2).active_on_miax());
                checksum += bench::digest((*message_2).miax_bbo_posting_increment_indicator());
                checksum += bench::digest((*message_2).liquidity_acceptance_increment_indicator());
                checksum += bench::digest((*message_2).opening_underlying_market_code());
                checksum += bench::digest((*message_2).priority_quote_width().mantissa());
            } else if (const auto* message_2 = dynamic_cast<const protocol::SystemStateMessage*>(message->data())) {
                checksum += bench::digest((*message_2).nanoseconds());
                checksum += bench::digest((*message_2).to_m_version());
                checksum += bench::digest((*message_2).session_id());
                checksum += bench::digest((*message_2).system_status());
            } else if (const auto* message_2 = dynamic_cast<const protocol::SimpleTopOfMarketBestBidOrOfferCompactBidMessage*>(message->data())) {
                checksum += bench::digest((*message_2).nanoseconds());
                checksum += bench::digest((*message_2).product_id());
                checksum += bench::digest((*message_2).mbbo_price_short().mantissa());
                checksum += bench::digest((*message_2).mbbo_size_short());
                checksum += bench::digest((*message_2).mbbo_priority_customer_size_short());
                checksum += bench::digest((*message_2).mbbo_condition());
            } else if (const auto* message_2 = dynamic_cast<const protocol::SimpleTopOfMarketBestBidOrOfferCompactOfferMessage*>(message->data())) {
                checksum += bench::digest((*message_2).nanoseconds());
                checksum += bench::digest((*message_2).product_id());
                checksum += bench::digest((*message_2).mbbo_price_short().mantissa());
                checksum += bench::digest((*message_2).mbbo_size_short());
                checksum += bench::digest((*message_2).mbbo_priority_customer_size_short());
                checksum += bench::digest((*message_2).mbbo_condition());
            } else if (const auto* message_2 = dynamic_cast<const protocol::SimpleTopOfMarketBestBidOrOfferWideBidMessage*>(message->data())) {
                checksum += bench::digest((*message_2).nanoseconds());
                checksum += bench::digest((*message_2).product_id());
                checksum += bench::digest((*message_2).mbbo_price_long().mantissa());
                checksum += bench::digest((*message_2).mbbo_size_long());
                checksum += bench::digest((*message_2).mbbo_priority_customer_size_long());
                checksum += bench::digest((*message_2).mbbo_condition());
            } else if (const auto* message_2 = dynamic_cast<const protocol::SimpleTopOfMarketBestBidOrOfferWideOfferMessage*>(message->data())) {
                checksum += bench::digest((*message_2).nanoseconds());
                checksum += bench::digest((*message_2).product_id());
                checksum += bench::digest((*message_2).mbbo_price_long().mantissa());
                checksum += bench::digest((*message_2).mbbo_size_long());
                checksum += bench::digest((*message_2).mbbo_priority_customer_size_long());
                checksum += bench::digest((*message_2).mbbo_condition());
            } else if (const auto* message_2 = dynamic_cast<const protocol::SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage*>(message->data())) {
                checksum += bench::digest((*message_2).nanoseconds());
                checksum += bench::digest((*message_2).product_id());
                checksum += bench::digest((*message_2).bid_price_short().mantissa());
                checksum += bench::digest((*message_2).bid_size_short());
                checksum += bench::digest((*message_2).bid_priority_customer_size_short());
                checksum += bench::digest((*message_2).bid_condition());
                checksum += bench::digest((*message_2).offer_price_short().mantissa());
                checksum += bench::digest((*message_2).offer_size_short());
                checksum += bench::digest((*message_2).offer_priority_customer_size_short());
                checksum += bench::digest((*message_2).offer_condition());
            } else if (const auto* message_2 = dynamic_cast<const protocol::SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage*>(message->data())) {
                checksum += bench::digest((*message_2).nanoseconds());
                checksum += bench::digest((*message_2).product_id());
                checksum += bench::digest((*message_2).bid_price_long().mantissa());
                checksum += bench::digest((*message_2).bid_size_long());
                checksum += bench::digest((*message_2).bid_priority_customer_size_long());
                checksum += bench::digest((*message_2).bid_condition());
                checksum += bench::digest((*message_2).offer_price_long().mantissa());
                checksum += bench::digest((*message_2).offer_size_long());
                checksum += bench::digest((*message_2).offer_priority_customer_size_long());
                checksum += bench::digest((*message_2).offer_condition());
            } else if (const auto* message_2 = dynamic_cast<const protocol::LastSaleMessage*>(message->data())) {
                checksum += bench::digest((*message_2).nanoseconds());
                checksum += bench::digest((*message_2).product_id());
                checksum += bench::digest((*message_2).trade_id());
                checksum += bench::digest((*message_2).correction_number());
                checksum += bench::digest((*message_2).reference_trade_id());
                checksum += bench::digest((*message_2).reference_correction_number());
                checksum += bench::digest((*message_2).trade_price().mantissa());
                checksum += bench::digest((*message_2).trade_size());
                checksum += bench::digest((*message_2).trade_condition());
            } else if (const auto* message_2 = dynamic_cast<const protocol::TradeCancelMessage*>(message->data())) {
                checksum += bench::digest((*message_2).nanoseconds());
                checksum += bench::digest((*message_2).product_id());
                checksum += bench::digest((*message_2).trade_id());
                checksum += bench::digest((*message_2).correction_number());
                checksum += bench::digest((*message_2).trade_price().mantissa());
                checksum += bench::digest((*message_2).trade_size());
                checksum += bench::digest((*message_2).trade_condition());
            } else if (const auto* message_2 = dynamic_cast<const protocol::UnderlyingTradingStatusNotificationMessage*>(message->data())) {
                checksum += bench::digest((*message_2).nanoseconds());
                checksum += bench::digest((*message_2).underlying_symbol());
                checksum += bench::digest((*message_2).trading_status());
                checksum += bench::digest((*message_2).event_reason());
                checksum += bench::digest((*message_2).expected_event_time_seconds_part());
                checksum += bench::digest((*message_2).expected_event_time_nano_seconds_part());
            }
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Miax.MiaxOptions.TopOfMarket.Mach.v2.5", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
