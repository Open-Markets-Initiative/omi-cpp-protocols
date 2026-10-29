// Bse.BseIndia.Eobi.Fbe.v1.4 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/bse/bseindia/eobi/fbe/v1.4.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/bse/bseindia/eobi/fbe/v1.4/definitions.hpp"

namespace protocol = ::bse::bseindia::eobi::fbe::v1_4;

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
        checksum += bench::digest(packet.packet_header().market_segment_id());
        checksum += bench::digest(packet.packet_header().partition_id());
        checksum += bench::digest(packet.packet_header().completion_indicator());
        checksum += bench::digest(packet.packet_header().appl_seq_reset_indicator());
        checksum += bench::digest(packet.packet_header().transact_time());
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

    void on(const protocol::HeartbeatMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.last_msg_seq_num_processed());
    }

    void on(const protocol::ProductSummaryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.last_msg_seq_num_processed());
        checksum += bench::digest(message.trading_session_id());
        checksum += bench::digest(message.trading_session_sub_id());
        checksum += bench::digest(message.trad_ses_status());
        checksum += bench::digest(message.fast_market_indicator());
    }

    void on(const protocol::SnapshotOrderMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.order_details().trd_reg_ts_time_priority());
        checksum += bench::digest(message.order_details().display_qty());
        checksum += bench::digest(message.order_details().side());
        checksum += bench::digest(message.order_details().price().mantissa());
    }

    void on(const protocol::InstrumentSummaryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.last_update_time());
        checksum += (message.trd_reg_ts_execution_time().has_value() ? bench::digest((*message.trd_reg_ts_execution_time())) : std::uint64_t{0});
        checksum += bench::digest(message.tot_no_orders());
        checksum += bench::digest(message.security_status());
        checksum += bench::digest(message.security_trading_status());
        checksum += bench::digest(message.fast_market_indicator());
        checksum += bench::digest(message.no_md_entries());
        checksum += bench::digest(message.trade_volume());
        checksum += bench::digest(message.no_of_trades());
    }

    void on(const protocol::AuctionBestBidOfferMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.security_id());
        checksum += (message.bid_px().has_value() ? bench::digest((*message.bid_px()).mantissa()) : std::uint64_t{0});
        checksum += (message.offer_px().has_value() ? bench::digest((*message.offer_px()).mantissa()) : std::uint64_t{0});
    }

    void on(const protocol::AuctionClearingPriceMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.last_px().mantissa());
        checksum += bench::digest(message.last_qty());
    }

    void on(const protocol::TopOfBookMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.security_id());
        checksum += (message.bid_px().has_value() ? bench::digest((*message.bid_px()).mantissa()) : std::uint64_t{0});
        checksum += (message.offer_px().has_value() ? bench::digest((*message.offer_px()).mantissa()) : std::uint64_t{0});
    }

    void on(const protocol::OrderAddMessage& message) {
        checksum += index++;
        checksum += (message.trd_reg_ts_time_in().has_value() ? bench::digest((*message.trd_reg_ts_time_in())) : std::uint64_t{0});
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.order_details().trd_reg_ts_time_priority());
        checksum += bench::digest(message.order_details().display_qty());
        checksum += bench::digest(message.order_details().side());
        checksum += bench::digest(message.order_details().price().mantissa());
    }

    void on(const protocol::OrderModifyMessage& message) {
        checksum += index++;
        checksum += (message.trd_reg_ts_time_in().has_value() ? bench::digest((*message.trd_reg_ts_time_in())) : std::uint64_t{0});
        checksum += bench::digest(message.trd_reg_ts_prev_time_priority());
        checksum += bench::digest(message.prev_price().mantissa());
        checksum += bench::digest(message.prev_display_qty());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.order_details().trd_reg_ts_time_priority());
        checksum += bench::digest(message.order_details().display_qty());
        checksum += bench::digest(message.order_details().side());
        checksum += bench::digest(message.order_details().price().mantissa());
    }

    void on(const protocol::OrderModifySamePriorityMessage& message) {
        checksum += index++;
        checksum += (message.trd_reg_ts_time_in().has_value() ? bench::digest((*message.trd_reg_ts_time_in())) : std::uint64_t{0});
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.prev_display_qty());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.order_details().trd_reg_ts_time_priority());
        checksum += bench::digest(message.order_details().display_qty());
        checksum += bench::digest(message.order_details().side());
        checksum += bench::digest(message.order_details().price().mantissa());
    }

    void on(const protocol::OrderDeleteMessage& message) {
        checksum += index++;
        checksum += (message.trd_reg_ts_time_in().has_value() ? bench::digest((*message.trd_reg_ts_time_in())) : std::uint64_t{0});
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.order_details().trd_reg_ts_time_priority());
        checksum += bench::digest(message.order_details().display_qty());
        checksum += bench::digest(message.order_details().side());
        checksum += bench::digest(message.order_details().price().mantissa());
    }

    void on(const protocol::OrderMassDeleteMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.transact_time());
    }

    void on(const protocol::PartialOrderExecutionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.trd_reg_ts_time_priority());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.trd_match_id());
        checksum += bench::digest(message.last_qty());
        checksum += bench::digest(message.last_px().mantissa());
    }

    void on(const protocol::FullOrderExecutionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.trd_reg_ts_time_priority());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.trd_match_id());
        checksum += bench::digest(message.last_qty());
        checksum += bench::digest(message.last_px().mantissa());
    }

    void on(const protocol::TradeReversalMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.trd_match_id());
        checksum += bench::digest(message.last_qty());
        checksum += bench::digest(message.last_px().mantissa());
        checksum += (message.trd_reg_ts_execution_time().has_value() ? bench::digest((*message.trd_reg_ts_execution_time())) : std::uint64_t{0});
        checksum += bench::digest(message.no_md_entries());
    }

    void on(const protocol::ExecutionSummaryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += (message.aggressor_timestamp().has_value() ? bench::digest((*message.aggressor_timestamp())) : std::uint64_t{0});
        checksum += bench::digest(message.exec_id());
        checksum += bench::digest(message.last_qty());
        checksum += bench::digest(message.aggressor_side());
        checksum += (message.trade_condition().has_value() ? bench::digest((*message.trade_condition())) : std::uint64_t{0});
        checksum += bench::digest(message.last_px().mantissa());
        checksum += (message.resting_hidden_qty().has_value() ? bench::digest((*message.resting_hidden_qty())) : std::uint64_t{0});
    }

    void on(const protocol::InstrumentInfoMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += (message.close_price().has_value() ? bench::digest((*message.close_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.prev_close_price().has_value() ? bench::digest((*message.prev_close_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.upper_ckt_limit().has_value() ? bench::digest((*message.upper_ckt_limit()).mantissa()) : std::uint64_t{0});
        checksum += (message.lower_ckt_limit().has_value() ? bench::digest((*message.lower_ckt_limit()).mantissa()) : std::uint64_t{0});
    }

    void on(const protocol::LppRangeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.upper_exec_limit().mantissa());
        checksum += bench::digest(message.lower_exec_limit().mantissa());
    }

    void on(const protocol::ProductStateChangeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.trading_session_id());
        checksum += bench::digest(message.trading_session_sub_id());
        checksum += bench::digest(message.trad_ses_status());
        checksum += bench::digest(message.fast_market_indicator());
        checksum += bench::digest(message.transact_time());
    }

    void on(const protocol::InstrumentStateChangeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.security_status());
        checksum += bench::digest(message.security_trading_status());
        checksum += bench::digest(message.fast_market_indicator());
        checksum += bench::digest(message.transact_time());
    }

    void on(const protocol::AddComplexInstrumentMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.transact_time());
        checksum += (message.security_sub_type().has_value() ? bench::digest((*message.security_sub_type())) : std::uint64_t{0});
        checksum += bench::digest(message.product_complex());
        checksum += bench::digest(message.implied_market_indicator());
        checksum += bench::digest(message.no_legs());
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
    return bench::run("Bse.BseIndia.Eobi.Fbe.v1.4", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
