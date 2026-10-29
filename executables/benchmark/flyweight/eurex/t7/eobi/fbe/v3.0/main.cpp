// Eurex.T7.Eobi.Fbe.v3.0 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/eurex/t7/eobi/fbe/v3.0.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/eurex/t7/eobi/fbe/v3.0/definitions.hpp"

namespace protocol = ::eurex::t7::eobi::fbe::v3_0;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        checksum += bench::digest(packet.packet_header().eobi_header().body_len());
        checksum += bench::digest(packet.packet_header().eobi_header().template_id());
        checksum += bench::digest(packet.packet_header().eobi_header().msg_seq_num());
        checksum += bench::digest(packet.packet_header().appl_seq_num());
        checksum += (packet.packet_header().market_segment_id().has_value() ? bench::digest((*packet.packet_header().market_segment_id())) : std::uint64_t{0});
        checksum += (packet.packet_header().partition_id().has_value() ? bench::digest((*packet.packet_header().partition_id())) : std::uint64_t{0});
        checksum += (packet.packet_header().completion_indicator().has_value() ? bench::digest((*packet.packet_header().completion_indicator())) : std::uint64_t{0});
        checksum += (packet.packet_header().appl_seq_reset_indicator().has_value() ? bench::digest((*packet.packet_header().appl_seq_reset_indicator())) : std::uint64_t{0});
        checksum += (packet.packet_header().transact_time().has_value() ? bench::digest((*packet.packet_header().transact_time())) : std::uint64_t{0});
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

    void on(const protocol::AddComplexInstrument& message) {
        checksum += index++;
        checksum += (message.security_id().has_value() ? bench::digest((*message.security_id())) : std::uint64_t{0});
        checksum += (message.transact_time().has_value() ? bench::digest((*message.transact_time())) : std::uint64_t{0});
        checksum += (message.security_sub_type().has_value() ? bench::digest((*message.security_sub_type())) : std::uint64_t{0});
        checksum += (message.product_complex().has_value() ? bench::digest((*message.product_complex())) : std::uint64_t{0});
        checksum += (message.implied_market_indicator().has_value() ? bench::digest((*message.implied_market_indicator())) : std::uint64_t{0});
        checksum += (message.no_legs().has_value() ? bench::digest((*message.no_legs())) : std::uint64_t{0});
    }

    void on(const protocol::AuctionBbo& message) {
        checksum += index++;
        checksum += (message.transact_time().has_value() ? bench::digest((*message.transact_time())) : std::uint64_t{0});
        checksum += (message.security_id().has_value() ? bench::digest((*message.security_id())) : std::uint64_t{0});
        checksum += (message.bid_px().has_value() ? bench::digest((*message.bid_px()).mantissa()) : std::uint64_t{0});
        checksum += (message.offer_px().has_value() ? bench::digest((*message.offer_px()).mantissa()) : std::uint64_t{0});
    }

    void on(const protocol::AuctionClearingPrice& message) {
        checksum += index++;
        checksum += (message.transact_time().has_value() ? bench::digest((*message.transact_time())) : std::uint64_t{0});
        checksum += (message.security_id().has_value() ? bench::digest((*message.security_id())) : std::uint64_t{0});
        checksum += (message.last_px().has_value() ? bench::digest((*message.last_px()).mantissa()) : std::uint64_t{0});
    }

    void on(const protocol::CrossRequest& message) {
        checksum += index++;
        checksum += (message.security_id().has_value() ? bench::digest((*message.security_id())) : std::uint64_t{0});
        checksum += (message.last_qty().has_value() ? bench::digest((*message.last_qty())) : std::uint64_t{0});
        checksum += (message.transact_time().has_value() ? bench::digest((*message.transact_time())) : std::uint64_t{0});
    }

    void on(const protocol::ExecutionSummary& message) {
        checksum += index++;
        checksum += (message.security_id().has_value() ? bench::digest((*message.security_id())) : std::uint64_t{0});
        checksum += (message.aggressor_timestamp().has_value() ? bench::digest((*message.aggressor_timestamp())) : std::uint64_t{0});
        checksum += (message.request_time().has_value() ? bench::digest((*message.request_time())) : std::uint64_t{0});
        checksum += (message.exec_id().has_value() ? bench::digest((*message.exec_id())) : std::uint64_t{0});
        checksum += (message.last_qty().has_value() ? bench::digest((*message.last_qty())) : std::uint64_t{0});
        checksum += (message.aggressor_side().has_value() ? bench::digest((*message.aggressor_side())) : std::uint64_t{0});
        checksum += (message.trade_condition().has_value() ? bench::digest((*message.trade_condition())) : std::uint64_t{0});
        checksum += (message.last_px().has_value() ? bench::digest((*message.last_px()).mantissa()) : std::uint64_t{0});
        checksum += (message.resting_hidden_qty().has_value() ? bench::digest((*message.resting_hidden_qty())) : std::uint64_t{0});
        checksum += (message.resting_cxl_qty().has_value() ? bench::digest((*message.resting_cxl_qty())) : std::uint64_t{0});
    }

    void on(const protocol::FullOrderExecution& message) {
        checksum += index++;
        checksum += (message.side().has_value() ? bench::digest((*message.side())) : std::uint64_t{0});
        checksum += (message.price().has_value() ? bench::digest((*message.price()).mantissa()) : std::uint64_t{0});
        checksum += (message.trd_reg_ts_time_priority().has_value() ? bench::digest((*message.trd_reg_ts_time_priority())) : std::uint64_t{0});
        checksum += (message.security_id().has_value() ? bench::digest((*message.security_id())) : std::uint64_t{0});
        checksum += (message.trd_match_id().has_value() ? bench::digest((*message.trd_match_id())) : std::uint64_t{0});
        checksum += (message.last_qty().has_value() ? bench::digest((*message.last_qty())) : std::uint64_t{0});
        checksum += (message.last_px().has_value() ? bench::digest((*message.last_px()).mantissa()) : std::uint64_t{0});
    }

    void on(const protocol::Heartbeat& message) {
        checksum += index++;
        checksum += (message.last_msg_seq_num_processed().has_value() ? bench::digest((*message.last_msg_seq_num_processed())) : std::uint64_t{0});
    }

    void on(const protocol::InstrumentStateChange& message) {
        checksum += index++;
        checksum += (message.security_id().has_value() ? bench::digest((*message.security_id())) : std::uint64_t{0});
        checksum += (message.security_status().has_value() ? bench::digest((*message.security_status())) : std::uint64_t{0});
        checksum += (message.security_trading_status().has_value() ? bench::digest((*message.security_trading_status())) : std::uint64_t{0});
        checksum += (message.fast_market_indicator().has_value() ? bench::digest((*message.fast_market_indicator())) : std::uint64_t{0});
        checksum += (message.transact_time().has_value() ? bench::digest((*message.transact_time())) : std::uint64_t{0});
    }

    void on(const protocol::InstrumentSummary& message) {
        checksum += index++;
        checksum += (message.security_id().has_value() ? bench::digest((*message.security_id())) : std::uint64_t{0});
        checksum += (message.last_update_time().has_value() ? bench::digest((*message.last_update_time())) : std::uint64_t{0});
        checksum += (message.trd_reg_ts_execution_time().has_value() ? bench::digest((*message.trd_reg_ts_execution_time())) : std::uint64_t{0});
        checksum += (message.tot_no_orders().has_value() ? bench::digest((*message.tot_no_orders())) : std::uint64_t{0});
        checksum += (message.security_status().has_value() ? bench::digest((*message.security_status())) : std::uint64_t{0});
        checksum += (message.security_trading_status().has_value() ? bench::digest((*message.security_trading_status())) : std::uint64_t{0});
        checksum += (message.fast_market_indicator().has_value() ? bench::digest((*message.fast_market_indicator())) : std::uint64_t{0});
        checksum += (message.no_md_entries().has_value() ? bench::digest((*message.no_md_entries())) : std::uint64_t{0});
    }

    void on(const protocol::OrderAdd& message) {
        checksum += index++;
        checksum += (message.trd_reg_ts_time_in().has_value() ? bench::digest((*message.trd_reg_ts_time_in())) : std::uint64_t{0});
        checksum += (message.security_id().has_value() ? bench::digest((*message.security_id())) : std::uint64_t{0});
        checksum += (message.order_details_comp().trd_reg_ts_time_priority().has_value() ? bench::digest((*message.order_details_comp().trd_reg_ts_time_priority())) : std::uint64_t{0});
        checksum += (message.order_details_comp().display_qty().has_value() ? bench::digest((*message.order_details_comp().display_qty())) : std::uint64_t{0});
        checksum += (message.order_details_comp().side().has_value() ? bench::digest((*message.order_details_comp().side())) : std::uint64_t{0});
        checksum += (message.order_details_comp().price().has_value() ? bench::digest((*message.order_details_comp().price()).mantissa()) : std::uint64_t{0});
    }

    void on(const protocol::OrderDelete& message) {
        checksum += index++;
        checksum += (message.trd_reg_ts_time_in().has_value() ? bench::digest((*message.trd_reg_ts_time_in())) : std::uint64_t{0});
        checksum += (message.transact_time().has_value() ? bench::digest((*message.transact_time())) : std::uint64_t{0});
        checksum += (message.security_id().has_value() ? bench::digest((*message.security_id())) : std::uint64_t{0});
        checksum += (message.order_details_comp().trd_reg_ts_time_priority().has_value() ? bench::digest((*message.order_details_comp().trd_reg_ts_time_priority())) : std::uint64_t{0});
        checksum += (message.order_details_comp().display_qty().has_value() ? bench::digest((*message.order_details_comp().display_qty())) : std::uint64_t{0});
        checksum += (message.order_details_comp().side().has_value() ? bench::digest((*message.order_details_comp().side())) : std::uint64_t{0});
        checksum += (message.order_details_comp().price().has_value() ? bench::digest((*message.order_details_comp().price()).mantissa()) : std::uint64_t{0});
    }

    void on(const protocol::OrderMassDelete& message) {
        checksum += index++;
        checksum += (message.security_id().has_value() ? bench::digest((*message.security_id())) : std::uint64_t{0});
        checksum += (message.transact_time().has_value() ? bench::digest((*message.transact_time())) : std::uint64_t{0});
    }

    void on(const protocol::OrderModify& message) {
        checksum += index++;
        checksum += (message.trd_reg_ts_time_in().has_value() ? bench::digest((*message.trd_reg_ts_time_in())) : std::uint64_t{0});
        checksum += (message.trd_reg_ts_prev_time_priority().has_value() ? bench::digest((*message.trd_reg_ts_prev_time_priority())) : std::uint64_t{0});
        checksum += (message.prev_price().has_value() ? bench::digest((*message.prev_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.prev_display_qty().has_value() ? bench::digest((*message.prev_display_qty())) : std::uint64_t{0});
        checksum += (message.security_id().has_value() ? bench::digest((*message.security_id())) : std::uint64_t{0});
        checksum += (message.order_details_comp().trd_reg_ts_time_priority().has_value() ? bench::digest((*message.order_details_comp().trd_reg_ts_time_priority())) : std::uint64_t{0});
        checksum += (message.order_details_comp().display_qty().has_value() ? bench::digest((*message.order_details_comp().display_qty())) : std::uint64_t{0});
        checksum += (message.order_details_comp().side().has_value() ? bench::digest((*message.order_details_comp().side())) : std::uint64_t{0});
        checksum += (message.order_details_comp().price().has_value() ? bench::digest((*message.order_details_comp().price()).mantissa()) : std::uint64_t{0});
    }

    void on(const protocol::OrderModifySamePrio& message) {
        checksum += index++;
        checksum += (message.trd_reg_ts_time_in().has_value() ? bench::digest((*message.trd_reg_ts_time_in())) : std::uint64_t{0});
        checksum += (message.transact_time().has_value() ? bench::digest((*message.transact_time())) : std::uint64_t{0});
        checksum += (message.prev_display_qty().has_value() ? bench::digest((*message.prev_display_qty())) : std::uint64_t{0});
        checksum += (message.security_id().has_value() ? bench::digest((*message.security_id())) : std::uint64_t{0});
        checksum += (message.order_details_comp().trd_reg_ts_time_priority().has_value() ? bench::digest((*message.order_details_comp().trd_reg_ts_time_priority())) : std::uint64_t{0});
        checksum += (message.order_details_comp().display_qty().has_value() ? bench::digest((*message.order_details_comp().display_qty())) : std::uint64_t{0});
        checksum += (message.order_details_comp().side().has_value() ? bench::digest((*message.order_details_comp().side())) : std::uint64_t{0});
        checksum += (message.order_details_comp().price().has_value() ? bench::digest((*message.order_details_comp().price()).mantissa()) : std::uint64_t{0});
    }

    void on(const protocol::PartialOrderExecution& message) {
        checksum += index++;
        checksum += (message.side().has_value() ? bench::digest((*message.side())) : std::uint64_t{0});
        checksum += (message.price().has_value() ? bench::digest((*message.price()).mantissa()) : std::uint64_t{0});
        checksum += (message.trd_reg_ts_time_priority().has_value() ? bench::digest((*message.trd_reg_ts_time_priority())) : std::uint64_t{0});
        checksum += (message.security_id().has_value() ? bench::digest((*message.security_id())) : std::uint64_t{0});
        checksum += (message.trd_match_id().has_value() ? bench::digest((*message.trd_match_id())) : std::uint64_t{0});
        checksum += (message.last_qty().has_value() ? bench::digest((*message.last_qty())) : std::uint64_t{0});
        checksum += (message.last_px().has_value() ? bench::digest((*message.last_px()).mantissa()) : std::uint64_t{0});
    }

    void on(const protocol::ProductStateChange& message) {
        checksum += index++;
        checksum += (message.trading_session_id().has_value() ? bench::digest((*message.trading_session_id())) : std::uint64_t{0});
        checksum += (message.trading_session_sub_id().has_value() ? bench::digest((*message.trading_session_sub_id())) : std::uint64_t{0});
        checksum += (message.trad_ses_status().has_value() ? bench::digest((*message.trad_ses_status())) : std::uint64_t{0});
        checksum += (message.fast_market_indicator().has_value() ? bench::digest((*message.fast_market_indicator())) : std::uint64_t{0});
        checksum += (message.transact_time().has_value() ? bench::digest((*message.transact_time())) : std::uint64_t{0});
    }

    void on(const protocol::ProductSummary& message) {
        checksum += index++;
        checksum += (message.last_msg_seq_num_processed().has_value() ? bench::digest((*message.last_msg_seq_num_processed())) : std::uint64_t{0});
        checksum += (message.trading_session_id().has_value() ? bench::digest((*message.trading_session_id())) : std::uint64_t{0});
        checksum += (message.trading_session_sub_id().has_value() ? bench::digest((*message.trading_session_sub_id())) : std::uint64_t{0});
        checksum += (message.trad_ses_status().has_value() ? bench::digest((*message.trad_ses_status())) : std::uint64_t{0});
        checksum += (message.fast_market_indicator().has_value() ? bench::digest((*message.fast_market_indicator())) : std::uint64_t{0});
    }

    void on(const protocol::QuoteRequest& message) {
        checksum += index++;
        checksum += (message.security_id().has_value() ? bench::digest((*message.security_id())) : std::uint64_t{0});
        checksum += (message.last_qty().has_value() ? bench::digest((*message.last_qty())) : std::uint64_t{0});
        checksum += (message.side().has_value() ? bench::digest((*message.side())) : std::uint64_t{0});
        checksum += (message.transact_time().has_value() ? bench::digest((*message.transact_time())) : std::uint64_t{0});
    }

    void on(const protocol::SnapshotOrder& message) {
        checksum += index++;
        checksum += (message.order_details_comp().trd_reg_ts_time_priority().has_value() ? bench::digest((*message.order_details_comp().trd_reg_ts_time_priority())) : std::uint64_t{0});
        checksum += (message.order_details_comp().display_qty().has_value() ? bench::digest((*message.order_details_comp().display_qty())) : std::uint64_t{0});
        checksum += (message.order_details_comp().side().has_value() ? bench::digest((*message.order_details_comp().side())) : std::uint64_t{0});
        checksum += (message.order_details_comp().price().has_value() ? bench::digest((*message.order_details_comp().price()).mantissa()) : std::uint64_t{0});
    }

    void on(const protocol::TopOfBook& message) {
        checksum += index++;
        checksum += (message.transact_time().has_value() ? bench::digest((*message.transact_time())) : std::uint64_t{0});
        checksum += (message.security_id().has_value() ? bench::digest((*message.security_id())) : std::uint64_t{0});
        checksum += (message.bid_px().has_value() ? bench::digest((*message.bid_px()).mantissa()) : std::uint64_t{0});
        checksum += (message.offer_px().has_value() ? bench::digest((*message.offer_px()).mantissa()) : std::uint64_t{0});
    }

    void on(const protocol::TradeReport& message) {
        checksum += index++;
        checksum += (message.security_id().has_value() ? bench::digest((*message.security_id())) : std::uint64_t{0});
        checksum += (message.transact_time().has_value() ? bench::digest((*message.transact_time())) : std::uint64_t{0});
        checksum += (message.trd_match_id().has_value() ? bench::digest((*message.trd_match_id())) : std::uint64_t{0});
        checksum += (message.last_qty().has_value() ? bench::digest((*message.last_qty())) : std::uint64_t{0});
        checksum += (message.last_px().has_value() ? bench::digest((*message.last_px()).mantissa()) : std::uint64_t{0});
        checksum += (message.match_type().has_value() ? bench::digest((*message.match_type())) : std::uint64_t{0});
        checksum += (message.match_sub_type().has_value() ? bench::digest((*message.match_sub_type())) : std::uint64_t{0});
    }

    void on(const protocol::TradeReversal& message) {
        checksum += index++;
        checksum += (message.security_id().has_value() ? bench::digest((*message.security_id())) : std::uint64_t{0});
        checksum += (message.transact_time().has_value() ? bench::digest((*message.transact_time())) : std::uint64_t{0});
        checksum += (message.trd_match_id().has_value() ? bench::digest((*message.trd_match_id())) : std::uint64_t{0});
        checksum += (message.last_qty().has_value() ? bench::digest((*message.last_qty())) : std::uint64_t{0});
        checksum += (message.last_px().has_value() ? bench::digest((*message.last_px()).mantissa()) : std::uint64_t{0});
        checksum += (message.trd_reg_ts_execution_time().has_value() ? bench::digest((*message.trd_reg_ts_execution_time())) : std::uint64_t{0});
        checksum += (message.no_md_entries().has_value() ? bench::digest((*message.no_md_entries())) : std::uint64_t{0});
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
    return bench::run("Eurex.T7.Eobi.Fbe.v3.0", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
