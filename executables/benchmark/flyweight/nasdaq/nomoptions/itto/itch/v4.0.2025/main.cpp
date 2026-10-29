// Nasdaq.NomOptions.Itto.Itch.v4.0.2025 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/nomoptions/itto/itch/v4.0.2025.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <span>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "executables/benchmark/Benchmark.hpp"
#include "cpp/binary/flyweight/nasdaq/nomoptions/itto/itch/v4.0.2025/definitions.hpp"

namespace protocol = ::nasdaq::nomoptions::itto::itch::v4_0_2025;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        checksum += bench::digest(packet.packet_header().session());
        checksum += bench::digest(packet.packet_header().sequence_number());
        checksum += bench::digest(packet.packet_header().message_count());
    }

    // a message this test prints no values of, or a code no message answers to, still takes its entry
    template <typename Message>
    void on(const Message&) {
        ++index;
    }

    template <typename Code>
    void on_unknown(Code, std::span<const std::byte>) {
        ++index;
    }

    void on(const protocol::UdpPayloadSystemEventMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.event_code());
    }

    void on(const protocol::UdpPayloadOptionsDirectoryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.option_id());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.expiration_year());
        checksum += bench::digest(message.expiration_month());
        checksum += bench::digest(message.expiration_date());
        checksum += bench::digest(message.explicit_strike_price().mantissa());
        checksum += bench::digest(message.option_type());
        checksum += bench::digest(message.source());
        checksum += bench::digest(message.underlying_symbol());
        checksum += bench::digest(message.options_closing_type());
        checksum += bench::digest(message.tradable());
        checksum += bench::digest(message.mpv());
    }

    void on(const protocol::UdpPayloadTradingActionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.option_id());
        checksum += bench::digest(message.current_trading_state());
    }

    void on(const protocol::UdpPayloadSecurityOpenMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.option_id());
        checksum += bench::digest(message.open_state());
    }

    void on(const protocol::UdpPayloadAddOrderMessageShortMessageForm& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.order_reference_number());
        checksum += bench::digest(message.market_side());
        checksum += bench::digest(message.option_id());
        checksum += bench::digest(message.price_short().mantissa());
        checksum += bench::digest(message.volume_short());
    }

    void on(const protocol::UdpPayloadAddOrderMessageLongFormMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.order_reference_number());
        checksum += bench::digest(message.market_side());
        checksum += bench::digest(message.option_id());
        checksum += bench::digest(message.price_long().mantissa());
        checksum += bench::digest(message.volume_long());
    }

    void on(const protocol::UdpPayloadAddQuoteMessageShortFormMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.bid_reference_number());
        checksum += bench::digest(message.ask_reference_number());
        checksum += bench::digest(message.option_id());
        checksum += bench::digest(message.bid_price_short().mantissa());
        checksum += bench::digest(message.bid_size_short());
        checksum += bench::digest(message.ask_price_short().mantissa());
        checksum += bench::digest(message.ask_size_short());
    }

    void on(const protocol::UdpPayloadAddQuoteMessageLongFormMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.bid_reference_number());
        checksum += bench::digest(message.ask_reference_number());
        checksum += bench::digest(message.option_id());
        checksum += bench::digest(message.bid());
        checksum += bench::digest(message.bid_size_long());
        checksum += bench::digest(message.ask());
        checksum += bench::digest(message.ask_size_long());
    }

    void on(const protocol::UdpPayloadSingleSideExecutedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.reference_number());
        checksum += bench::digest(message.executed_contracts());
        checksum += bench::digest(message.cross_number());
        checksum += bench::digest(message.match_number());
    }

    void on(const protocol::UdpPayloadSingleSideExecutedWithPriceMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.reference_number());
        checksum += bench::digest(message.cross_number());
        checksum += bench::digest(message.match_number());
        checksum += bench::digest(message.printable());
        checksum += bench::digest(message.price_long().mantissa());
        checksum += bench::digest(message.volume_long());
    }

    void on(const protocol::UdpPayloadOrderCancelMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.order_reference_number());
        checksum += bench::digest(message.cancelled_contracts());
    }

    void on(const protocol::UdpPayloadSingleSideReplaceMessageShortForm& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.original_reference_number());
        checksum += bench::digest(message.new_reference_number());
        checksum += bench::digest(message.price_short().mantissa());
        checksum += bench::digest(message.volume_short());
    }

    void on(const protocol::UdpPayloadSingleSideReplaceMessageLongForm& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.original_reference_number());
        checksum += bench::digest(message.new_reference_number());
        checksum += bench::digest(message.price_long().mantissa());
        checksum += bench::digest(message.volume_long());
    }

    void on(const protocol::UdpPayloadSingleSideDeleteMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.reference_number());
    }

    void on(const protocol::UdpPayloadSingleSideChangeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.reference_number());
        checksum += bench::digest(message.change_reason());
        checksum += bench::digest(message.price_long().mantissa());
        checksum += bench::digest(message.volume_long());
    }

    void on(const protocol::UdpPayloadQuoteReplaceMessageShortForm& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.original_bid_reference_number());
        checksum += bench::digest(message.bid_reference_number());
        checksum += bench::digest(message.original_ask_reference_number());
        checksum += bench::digest(message.ask_reference_number());
        checksum += bench::digest(message.bid_price_short().mantissa());
        checksum += bench::digest(message.bid_size_short());
        checksum += bench::digest(message.ask_price_short().mantissa());
        checksum += bench::digest(message.ask_size_short());
    }

    void on(const protocol::UdpPayloadQuoteReplaceMessageLongForm& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.original_bid_reference_number());
        checksum += bench::digest(message.bid_reference_number());
        checksum += bench::digest(message.original_ask_reference_number());
        checksum += bench::digest(message.ask_reference_number());
        checksum += bench::digest(message.bid_price_long().mantissa());
        checksum += bench::digest(message.bid_size_long());
        checksum += bench::digest(message.ask_price_long().mantissa());
        checksum += bench::digest(message.ask_size_long());
    }

    void on(const protocol::UdpPayloadQuoteDeleteMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.bid_reference_number());
        checksum += bench::digest(message.ask_reference_number());
    }

    void on(const protocol::UdpPayloadOptionsTradeMessagesNonAuction& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.buy_sell_indicator());
        checksum += bench::digest(message.option_id());
        checksum += bench::digest(message.cross_number());
        checksum += bench::digest(message.match_number());
        checksum += bench::digest(message.price_long().mantissa());
        checksum += bench::digest(message.volume_long());
    }

    void on(const protocol::UdpPayloadOptionsCrossTradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.option_id());
        checksum += bench::digest(message.cross_number());
        checksum += bench::digest(message.match_number());
        checksum += bench::digest(message.cross_type());
        checksum += bench::digest(message.price_long().mantissa());
        checksum += bench::digest(message.volume_long());
    }

    void on(const protocol::UdpPayloadBrokenTradeOrderExecutedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.cross_number());
        checksum += bench::digest(message.match_number());
    }

    void on(const protocol::UdpPayloadNoiiMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.auction_id());
        checksum += bench::digest(message.auction_type());
        checksum += bench::digest(message.paired_contracts());
        checksum += bench::digest(message.imbalance_direction());
        checksum += bench::digest(message.option_id());
        checksum += bench::digest(message.imbalance_price().mantissa());
        checksum += bench::digest(message.imbalance_volume());
        checksum += bench::digest(message.customer_firm_indicator());
    }
};

// The values the Flyweight reader reads from one datagram, folded into a checksum. A datagram it cannot
// read is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::PacketReader::read(std::span<const std::byte>(frame.payload, frame.payload_len), reader);
    } catch (const protocol::DecodeError& error) {
        throw;
    }

    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nasdaq.NomOptions.Itto.Itch.v4.0.2025", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
