// Nyse.ArcaOptions.DeepFeed.Pillar.v1.2.m benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/nyse/arcaoptions/deepfeed/pillar/v1.2.m.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/definitions.hpp"

namespace protocol = ::nyse::arcaoptions::deepfeed::pillar::v1_2_m;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        checksum += bench::digest(packet.packet_header().pkt_size());
        checksum += bench::digest(packet.packet_header().delivery_flag());
        checksum += bench::digest(packet.packet_header().number_msgs());
        checksum += bench::digest(packet.packet_header().seq_num());
        checksum += bench::digest(packet.packet_header().send_time().seconds());
        checksum += bench::digest(packet.packet_header().send_time().nanoseconds());
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

    void on(const protocol::SequenceNumberResetMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time());
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.product_id());
        checksum += bench::digest(message.channel_id());
    }

    void on(const protocol::SourceTimeReferenceMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.id());
        checksum += bench::digest(message.symbol_seq_num());
        checksum += bench::digest(message.source_time());
    }

    void on(const protocol::SymbolIndexMappingMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol_index());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.market_id());
        checksum += bench::digest(message.system_id());
        checksum += bench::digest(message.exchange_code());
        checksum += bench::digest(message.price_scale_code());
        checksum += bench::digest(message.security_type());
        checksum += bench::digest(message.lot_size());
        checksum += bench::digest(message.prev_close_price());
        checksum += bench::digest(message.prev_close_volume());
        checksum += bench::digest(message.price_resolution());
        checksum += bench::digest(message.round_lot());
    }

    void on(const protocol::SymbolClearMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time());
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.symbol_index());
        checksum += bench::digest(message.next_source_seq_num());
    }

    void on(const protocol::SecurityStatusMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time());
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.symbol_index());
        checksum += bench::digest(message.symbol_seq_num());
        checksum += bench::digest(message.security_status());
        checksum += bench::digest(message.halt_condition());
        checksum += bench::digest(message.price_1());
        checksum += bench::digest(message.price_2());
        checksum += bench::digest(message.ssr_triggering_exchange_id());
        checksum += bench::digest(message.ssr_triggering_volume());
        checksum += (message.time().has_value() ? bench::digest((*message.time())) : std::uint64_t{0});
        checksum += bench::digest(message.ssr_state());
        checksum += bench::digest(message.market_state());
        checksum += bench::digest(message.session_state());
    }

    void on(const protocol::OutrightSeriesIndexMappingMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.series_index());
        checksum += bench::digest(message.series_type());
        checksum += bench::digest(message.market_id());
        checksum += bench::digest(message.system_id());
        checksum += bench::digest(message.option_symbol_root());
        checksum += bench::digest(message.underlying_symbol());
        checksum += bench::digest(message.underlying_index());
        checksum += bench::digest(message.price_scale_code());
        checksum += bench::digest(message.contract_multiplier());
        checksum += bench::digest(message.maturity_date());
        checksum += bench::digest(message.put_or_call());
        checksum += bench::digest(message.strike_price());
        checksum += bench::digest(message.closing_only_indicator());
    }

    void on(const protocol::OptionsStatusMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time());
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.series_index());
        checksum += bench::digest(message.series_seq_num());
        checksum += bench::digest(message.series_status());
        checksum += bench::digest(message.market_state());
        checksum += bench::digest(message.options_status_halt_condition());
    }

    void on(const protocol::ComplexSeriesIndexMappingMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.series_index());
        checksum += bench::digest(message.market_id());
        checksum += bench::digest(message.system_id());
        checksum += bench::digest(message.no_of_legs());
    }

    void on(const protocol::RetransmissionRequestMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.begin_seq_num());
        checksum += bench::digest(message.end_seq_num());
        checksum += bench::digest(message.source_id());
        checksum += bench::digest(message.product_id());
        checksum += bench::digest(message.channel_id());
    }

    void on(const protocol::RefreshHeaderMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.current_refresh_pkt());
        checksum += bench::digest(message.total_refresh_pkts());
    }

    void on(const protocol::RefreshRequestMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol_index());
        checksum += bench::digest(message.source_id());
        checksum += bench::digest(message.product_id());
        checksum += bench::digest(message.channel_id());
    }

    void on(const protocol::SymbolIndexMappingRequestMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol_index());
        checksum += bench::digest(message.source_id());
        checksum += bench::digest(message.product_id());
        checksum += bench::digest(message.channel_id());
        checksum += bench::digest(message.retransmit_method());
    }

    void on(const protocol::MessageUnavailableMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.begin_seq_num());
        checksum += bench::digest(message.end_seq_num());
        checksum += bench::digest(message.product_id());
        checksum += bench::digest(message.channel_id());
    }

    void on(const protocol::RequestResponseMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.request_seq_num());
        checksum += bench::digest(message.begin_seq_num());
        checksum += bench::digest(message.end_seq_num());
        checksum += bench::digest(message.source_id());
        checksum += bench::digest(message.product_id());
        checksum += bench::digest(message.channel_id());
        checksum += bench::digest(message.status());
    }

    void on(const protocol::HeartbeatResponseMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_id());
    }

    void on(const protocol::OptionsAddOrderMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.series_index());
        checksum += bench::digest(message.series_seq_num());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.price());
        checksum += bench::digest(message.volume());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.firm_id());
        checksum += bench::digest(message.cust_indicator());
    }

    void on(const protocol::OptionsModifyOrderMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.series_index());
        checksum += bench::digest(message.series_seq_num());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.price());
        checksum += bench::digest(message.volume());
        checksum += bench::digest(message.position_change());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.cust_indicator());
    }

    void on(const protocol::OptionsDeleteOrderMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.series_index());
        checksum += bench::digest(message.series_seq_num());
        checksum += bench::digest(message.order_id());
    }

    void on(const protocol::OptionsOrderExecutionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.series_index());
        checksum += bench::digest(message.series_seq_num());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.price());
        checksum += bench::digest(message.volume());
        checksum += bench::digest(message.printable_flag());
        checksum += bench::digest(message.trade_cond_1());
    }

    void on(const protocol::OptionsReplaceOrderMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.series_index());
        checksum += bench::digest(message.series_seq_num());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.new_order_id());
        checksum += bench::digest(message.price());
        checksum += bench::digest(message.volume());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.cust_indicator());
    }

    void on(const protocol::OptionsImbalanceMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time());
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.series_index());
        checksum += bench::digest(message.series_seq_num());
        checksum += bench::digest(message.paired_qty());
        checksum += bench::digest(message.total_imbalance_qty());
        checksum += bench::digest(message.market_imbalance_qty());
        checksum += bench::digest(message.auction_type());
        checksum += bench::digest(message.imbalance_side());
        checksum += bench::digest(message.continuous_book_clearing_price());
        checksum += bench::digest(message.auction_interest_clearing_price());
        checksum += bench::digest(message.indicative_match_price());
        checksum += bench::digest(message.upper_collar());
        checksum += bench::digest(message.lower_collar());
        checksum += bench::digest(message.auction_status());
    }

    void on(const protocol::OptionsAddOrderRefreshMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time());
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.series_index());
        checksum += bench::digest(message.series_seq_num());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.price());
        checksum += bench::digest(message.volume());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.firm_id());
        checksum += bench::digest(message.cust_indicator());
    }

    void on(const protocol::OptionsSeriesRfqMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time());
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.series_index());
        checksum += bench::digest(message.series_seq_num());
        checksum += bench::digest(message.rfq_side());
        checksum += bench::digest(message.type_field());
        checksum += bench::digest(message.capacity());
        checksum += bench::digest(message.total_quantity());
        checksum += bench::digest(message.working_price());
        checksum += bench::digest(message.participant());
        checksum += bench::digest(message.auction_id());
        checksum += bench::digest(message.rfq_status());
    }

    void on(const protocol::OptionsNonDisplayedTradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.series_index());
        checksum += bench::digest(message.series_seq_num());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.price());
        checksum += bench::digest(message.volume());
        checksum += bench::digest(message.printable_flag());
        checksum += bench::digest(message.non_displayed_trade_trade_cond_1());
        checksum += bench::digest(message.price_type());
    }

    void on(const protocol::OptionsCrossTradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.series_index());
        checksum += bench::digest(message.series_seq_num());
        checksum += bench::digest(message.cross_id());
        checksum += bench::digest(message.price());
        checksum += bench::digest(message.volume());
        checksum += bench::digest(message.cross_type());
    }

    void on(const protocol::OptionsTradeCancelMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.series_index());
        checksum += bench::digest(message.series_seq_num());
        checksum += bench::digest(message.trade_id());
    }

    void on(const protocol::OptionsOutrightSeriesSummaryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time());
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.series_index());
        checksum += bench::digest(message.high_price());
        checksum += bench::digest(message.low_price());
        checksum += bench::digest(message.open());
        checksum += bench::digest(message.close());
        checksum += bench::digest(message.total_volume());
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
    return bench::run("Nyse.ArcaOptions.DeepFeed.Pillar.v1.2.m", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
