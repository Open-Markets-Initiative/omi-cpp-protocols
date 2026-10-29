// Nasdaq.NomOptions.Itto.Itch.v4.0.2025 benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/nomoptions/itto/itch/v4.0.2025.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/definitions.hpp"

namespace protocol = ::nasdaq::nomoptions::itto::itch::v4_0_2025;

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

    checksum += bench::digest(packet.packet_header().session());
    checksum += bench::digest(packet.packet_header().sequence_number());
    checksum += bench::digest(packet.packet_header().message_count());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_header().message_length());
        checksum += bench::digest(each.message_header().message_type());

        if (const auto* message = dynamic_cast<const protocol::UdpPayloadSystemEventMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).event_code());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadOptionsDirectoryMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).option_id());
            checksum += bench::digest((*message).security_symbol());
            checksum += bench::digest((*message).expiration_year());
            checksum += bench::digest((*message).expiration_month());
            checksum += bench::digest((*message).expiration_date());
            checksum += bench::digest((*message).explicit_strike_price().mantissa());
            checksum += bench::digest((*message).option_type());
            checksum += bench::digest((*message).source());
            checksum += bench::digest((*message).underlying_symbol());
            checksum += bench::digest((*message).options_closing_type());
            checksum += bench::digest((*message).tradable());
            checksum += bench::digest((*message).mpv());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadTradingActionMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).option_id());
            checksum += bench::digest((*message).current_trading_state());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadSecurityOpenMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).option_id());
            checksum += bench::digest((*message).open_state());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadAddOrderMessageShortMessageForm*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).market_side());
            checksum += bench::digest((*message).option_id());
            checksum += bench::digest((*message).price_short().mantissa());
            checksum += bench::digest((*message).volume_short());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadAddOrderMessageLongFormMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).market_side());
            checksum += bench::digest((*message).option_id());
            checksum += bench::digest((*message).price_long().mantissa());
            checksum += bench::digest((*message).volume_long());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadAddQuoteMessageShortFormMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).bid_reference_number());
            checksum += bench::digest((*message).ask_reference_number());
            checksum += bench::digest((*message).option_id());
            checksum += bench::digest((*message).bid_price_short().mantissa());
            checksum += bench::digest((*message).bid_size_short());
            checksum += bench::digest((*message).ask_price_short().mantissa());
            checksum += bench::digest((*message).ask_size_short());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadAddQuoteMessageLongFormMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).bid_reference_number());
            checksum += bench::digest((*message).ask_reference_number());
            checksum += bench::digest((*message).option_id());
            checksum += bench::digest((*message).bid());
            checksum += bench::digest((*message).bid_size_long());
            checksum += bench::digest((*message).ask());
            checksum += bench::digest((*message).ask_size_long());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadSingleSideExecutedMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).reference_number());
            checksum += bench::digest((*message).executed_contracts());
            checksum += bench::digest((*message).cross_number());
            checksum += bench::digest((*message).match_number());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadSingleSideExecutedWithPriceMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).reference_number());
            checksum += bench::digest((*message).cross_number());
            checksum += bench::digest((*message).match_number());
            checksum += bench::digest((*message).printable());
            checksum += bench::digest((*message).price_long().mantissa());
            checksum += bench::digest((*message).volume_long());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadOrderCancelMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).cancelled_contracts());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadSingleSideReplaceMessageShortForm*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).original_reference_number());
            checksum += bench::digest((*message).new_reference_number());
            checksum += bench::digest((*message).price_short().mantissa());
            checksum += bench::digest((*message).volume_short());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadSingleSideReplaceMessageLongForm*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).original_reference_number());
            checksum += bench::digest((*message).new_reference_number());
            checksum += bench::digest((*message).price_long().mantissa());
            checksum += bench::digest((*message).volume_long());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadSingleSideDeleteMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).reference_number());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadSingleSideChangeMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).reference_number());
            checksum += bench::digest((*message).change_reason());
            checksum += bench::digest((*message).price_long().mantissa());
            checksum += bench::digest((*message).volume_long());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadQuoteReplaceMessageShortForm*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).original_bid_reference_number());
            checksum += bench::digest((*message).bid_reference_number());
            checksum += bench::digest((*message).original_ask_reference_number());
            checksum += bench::digest((*message).ask_reference_number());
            checksum += bench::digest((*message).bid_price_short().mantissa());
            checksum += bench::digest((*message).bid_size_short());
            checksum += bench::digest((*message).ask_price_short().mantissa());
            checksum += bench::digest((*message).ask_size_short());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadQuoteReplaceMessageLongForm*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).original_bid_reference_number());
            checksum += bench::digest((*message).bid_reference_number());
            checksum += bench::digest((*message).original_ask_reference_number());
            checksum += bench::digest((*message).ask_reference_number());
            checksum += bench::digest((*message).bid_price_long().mantissa());
            checksum += bench::digest((*message).bid_size_long());
            checksum += bench::digest((*message).ask_price_long().mantissa());
            checksum += bench::digest((*message).ask_size_long());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadQuoteDeleteMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).bid_reference_number());
            checksum += bench::digest((*message).ask_reference_number());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadOptionsTradeMessagesNonAuction*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).buy_sell_indicator());
            checksum += bench::digest((*message).option_id());
            checksum += bench::digest((*message).cross_number());
            checksum += bench::digest((*message).match_number());
            checksum += bench::digest((*message).price_long().mantissa());
            checksum += bench::digest((*message).volume_long());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadOptionsCrossTradeMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).option_id());
            checksum += bench::digest((*message).cross_number());
            checksum += bench::digest((*message).match_number());
            checksum += bench::digest((*message).cross_type());
            checksum += bench::digest((*message).price_long().mantissa());
            checksum += bench::digest((*message).volume_long());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadBrokenTradeOrderExecutedMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).cross_number());
            checksum += bench::digest((*message).match_number());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadNoiiMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).auction_id());
            checksum += bench::digest((*message).auction_type());
            checksum += bench::digest((*message).paired_contracts());
            checksum += bench::digest((*message).imbalance_direction());
            checksum += bench::digest((*message).option_id());
            checksum += bench::digest((*message).imbalance_price().mantissa());
            checksum += bench::digest((*message).imbalance_volume());
            checksum += bench::digest((*message).customer_firm_indicator());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nasdaq.NomOptions.Itto.Itch.v4.0.2025", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
