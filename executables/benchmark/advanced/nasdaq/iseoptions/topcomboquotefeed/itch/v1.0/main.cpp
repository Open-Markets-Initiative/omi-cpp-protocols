// Nasdaq.IseOptions.TopComboQuoteFeed.Itch.v1.0: main.cpp
// Nasdaq.IseOptions.TopComboQuoteFeed.Itch.v1.0 benchmark, through the Advanced session layer: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/iseoptions/topcomboquotefeed/itch/v1.0.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/advanced/nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/messages/session.hpp"

namespace protocol = ::nasdaq::iseoptions::topcomboquotefeed::itch::v1_0;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::packet_header& header, const packet::Frame&) {
        checksum += bench::digest(header.session.get().value());
        checksum += bench::digest(header.sequence_number.get().value());
        checksum += bench::digest(header.message_count.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::packet_header&) {
        ++index;
    }

    void on_message(const protocol::system_event_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.event_code.get().value());
        checksum += bench::digest(message.fields.current_year.get().value());
        checksum += bench::digest(message.fields.current_month.get().value());
        checksum += bench::digest(message.fields.current_day.get().value());
        checksum += bench::digest(message.fields.version.get().value());
        checksum += bench::digest(message.fields.sub_version.get().value());
    }

    void on_message(const protocol::complex_strategy_directory_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.strategy_id.get().value());
        checksum += bench::digest(message.fields.strategy_type.get().value());
        checksum += bench::digest(message.fields.source.get().value());
        checksum += bench::digest(message.fields.underlying_symbol.get().value());
        checksum += bench::digest(message.fields.number_of_legs.get().value());
    }

    void on_message(const protocol::strategy_open_closed_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.strategy_id.get().value());
        checksum += bench::digest(message.fields.open_state.get().value());
    }

    void on_message(const protocol::strategy_trading_action_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.strategy_id.get().value());
        checksum += bench::digest(message.fields.current_trading_state.get().value());
    }

    void on_message(const protocol::strategy_best_bid_and_ask_update& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.strategy_id.get().value());
        checksum += bench::digest(message.fields.quote_condition.get().value());
        checksum += bench::digest(message.fields.bid_price.get().value());
        checksum += bench::digest(message.fields.bid_size.get().value());
        checksum += bench::digest(message.fields.bid_cust_size.get().value());
        checksum += bench::digest(message.fields.bid_pro_cust_size.get().value());
        checksum += bench::digest(message.fields.bid_ntt_size.get().value());
        checksum += bench::digest(message.fields.bid_market_size.get().value());
        checksum += bench::digest(message.fields.bid_ntt_market_size.get().value());
        checksum += bench::digest(message.fields.ask_price.get().value());
        checksum += bench::digest(message.fields.ask_size.get().value());
        checksum += bench::digest(message.fields.ask_cust_size.get().value());
        checksum += bench::digest(message.fields.ask_pro_cust_size.get().value());
        checksum += bench::digest(message.fields.ask_ntt_size.get().value());
        checksum += bench::digest(message.fields.ask_market_size.get().value());
        checksum += bench::digest(message.fields.ask_ntt_market_size.get().value());
    }

    void on_message(const protocol::strategy_best_bid_update& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.strategy_id.get().value());
        checksum += bench::digest(message.fields.quote_condition.get().value());
        checksum += bench::digest(message.fields.price.get().value());
        checksum += bench::digest(message.fields.size.get().value());
        checksum += bench::digest(message.fields.cust_size.get().value());
        checksum += bench::digest(message.fields.pro_cust_size.get().value());
        checksum += bench::digest(message.fields.ntt_size.get().value());
        checksum += bench::digest(message.fields.market_size.get().value());
        checksum += bench::digest(message.fields.ntt_market_size.get().value());
    }

    void on_message(const protocol::strategy_best_ask_update& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.strategy_id.get().value());
        checksum += bench::digest(message.fields.quote_condition.get().value());
        checksum += bench::digest(message.fields.price.get().value());
        checksum += bench::digest(message.fields.size.get().value());
        checksum += bench::digest(message.fields.cust_size.get().value());
        checksum += bench::digest(message.fields.pro_cust_size.get().value());
        checksum += bench::digest(message.fields.ntt_size.get().value());
        checksum += bench::digest(message.fields.market_size.get().value());
        checksum += bench::digest(message.fields.ntt_market_size.get().value());
    }

    void on_message(const protocol::complex_strategy_ticker_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.strategy_id.get().value());
        checksum += bench::digest(message.fields.last_price.get().value());
        checksum += bench::digest(message.fields.size.get().value());
        checksum += bench::digest(message.fields.volume.get().value());
        checksum += bench::digest(message.fields.high.get().value());
        checksum += bench::digest(message.fields.low.get().value());
        checksum += bench::digest(message.fields.first.get().value());
        checksum += bench::digest(message.fields.trade_condition.get().value());
    }
};

// The values Advanced reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;
    protocol::process_segment(reader, frame.payload, frame.payload_len, 0, frame);
    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nasdaq.IseOptions.TopComboQuoteFeed.Itch.v1.0", "advanced", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
