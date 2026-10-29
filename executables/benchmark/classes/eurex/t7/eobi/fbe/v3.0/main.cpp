// Eurex.T7.Eobi.Fbe.v3.0 benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/eurex/t7/eobi/fbe/v3.0.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/eurex/t7/eobi/fbe/v3.0/definitions.hpp"

namespace protocol = ::eurex::t7::eobi::fbe::v3_0;

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

    checksum += bench::digest(packet.packet_header().eobi_header().body_len());
    checksum += bench::digest(packet.packet_header().eobi_header().template_id());
    checksum += bench::digest(packet.packet_header().eobi_header().msg_seq_num());
    checksum += bench::digest(packet.packet_header().appl_seq_num());
    checksum += (packet.packet_header().market_segment_id().has_value() ? bench::digest((*packet.packet_header().market_segment_id())) : std::uint64_t{0});
    checksum += (packet.packet_header().partition_id().has_value() ? bench::digest((*packet.packet_header().partition_id())) : std::uint64_t{0});
    checksum += (packet.packet_header().completion_indicator().has_value() ? bench::digest((*packet.packet_header().completion_indicator())) : std::uint64_t{0});
    checksum += (packet.packet_header().appl_seq_reset_indicator().has_value() ? bench::digest((*packet.packet_header().appl_seq_reset_indicator())) : std::uint64_t{0});
    checksum += (packet.packet_header().transact_time().has_value() ? bench::digest((*packet.packet_header().transact_time())) : std::uint64_t{0});

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_header_comp().body_len());
        checksum += bench::digest(each.message_header_comp().template_id());
        checksum += bench::digest(each.message_header_comp().msg_seq_num());

        if (const auto* message = dynamic_cast<const protocol::AddComplexInstrument*>(each.message())) {
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
            checksum += ((*message).security_sub_type().has_value() ? bench::digest((*(*message).security_sub_type())) : std::uint64_t{0});
            checksum += ((*message).product_complex().has_value() ? bench::digest((*(*message).product_complex())) : std::uint64_t{0});
            checksum += ((*message).implied_market_indicator().has_value() ? bench::digest((*(*message).implied_market_indicator())) : std::uint64_t{0});
            checksum += ((*message).no_legs().has_value() ? bench::digest((*(*message).no_legs())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::AuctionBbo*>(each.message())) {
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).bid_px().has_value() ? bench::digest((*(*message).bid_px()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).offer_px().has_value() ? bench::digest((*(*message).offer_px()).mantissa()) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::AuctionClearingPrice*>(each.message())) {
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).last_px().has_value() ? bench::digest((*(*message).last_px()).mantissa()) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::CrossRequest*>(each.message())) {
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).last_qty().has_value() ? bench::digest((*(*message).last_qty())) : std::uint64_t{0});
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::ExecutionSummary*>(each.message())) {
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).aggressor_timestamp().has_value() ? bench::digest((*(*message).aggressor_timestamp())) : std::uint64_t{0});
            checksum += ((*message).request_time().has_value() ? bench::digest((*(*message).request_time())) : std::uint64_t{0});
            checksum += ((*message).exec_id().has_value() ? bench::digest((*(*message).exec_id())) : std::uint64_t{0});
            checksum += ((*message).last_qty().has_value() ? bench::digest((*(*message).last_qty())) : std::uint64_t{0});
            checksum += ((*message).aggressor_side().has_value() ? bench::digest((*(*message).aggressor_side())) : std::uint64_t{0});
            checksum += ((*message).trade_condition().has_value() ? bench::digest((*(*message).trade_condition())) : std::uint64_t{0});
            checksum += ((*message).last_px().has_value() ? bench::digest((*(*message).last_px()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).resting_hidden_qty().has_value() ? bench::digest((*(*message).resting_hidden_qty())) : std::uint64_t{0});
            checksum += ((*message).resting_cxl_qty().has_value() ? bench::digest((*(*message).resting_cxl_qty())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::FullOrderExecution*>(each.message())) {
            checksum += ((*message).side().has_value() ? bench::digest((*(*message).side())) : std::uint64_t{0});
            checksum += ((*message).price().has_value() ? bench::digest((*(*message).price()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).trd_reg_ts_time_priority().has_value() ? bench::digest((*(*message).trd_reg_ts_time_priority())) : std::uint64_t{0});
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).trd_match_id().has_value() ? bench::digest((*(*message).trd_match_id())) : std::uint64_t{0});
            checksum += ((*message).last_qty().has_value() ? bench::digest((*(*message).last_qty())) : std::uint64_t{0});
            checksum += ((*message).last_px().has_value() ? bench::digest((*(*message).last_px()).mantissa()) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::Heartbeat*>(each.message())) {
            checksum += ((*message).last_msg_seq_num_processed().has_value() ? bench::digest((*(*message).last_msg_seq_num_processed())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::InstrumentStateChange*>(each.message())) {
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).security_status().has_value() ? bench::digest((*(*message).security_status())) : std::uint64_t{0});
            checksum += ((*message).security_trading_status().has_value() ? bench::digest((*(*message).security_trading_status())) : std::uint64_t{0});
            checksum += ((*message).fast_market_indicator().has_value() ? bench::digest((*(*message).fast_market_indicator())) : std::uint64_t{0});
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::InstrumentSummary*>(each.message())) {
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).last_update_time().has_value() ? bench::digest((*(*message).last_update_time())) : std::uint64_t{0});
            checksum += ((*message).trd_reg_ts_execution_time().has_value() ? bench::digest((*(*message).trd_reg_ts_execution_time())) : std::uint64_t{0});
            checksum += ((*message).tot_no_orders().has_value() ? bench::digest((*(*message).tot_no_orders())) : std::uint64_t{0});
            checksum += ((*message).security_status().has_value() ? bench::digest((*(*message).security_status())) : std::uint64_t{0});
            checksum += ((*message).security_trading_status().has_value() ? bench::digest((*(*message).security_trading_status())) : std::uint64_t{0});
            checksum += ((*message).fast_market_indicator().has_value() ? bench::digest((*(*message).fast_market_indicator())) : std::uint64_t{0});
            checksum += ((*message).no_md_entries().has_value() ? bench::digest((*(*message).no_md_entries())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::OrderAdd*>(each.message())) {
            checksum += ((*message).trd_reg_ts_time_in().has_value() ? bench::digest((*(*message).trd_reg_ts_time_in())) : std::uint64_t{0});
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().trd_reg_ts_time_priority().has_value() ? bench::digest((*(*message).order_details_comp().trd_reg_ts_time_priority())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().display_qty().has_value() ? bench::digest((*(*message).order_details_comp().display_qty())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().side().has_value() ? bench::digest((*(*message).order_details_comp().side())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().price().has_value() ? bench::digest((*(*message).order_details_comp().price()).mantissa()) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::OrderDelete*>(each.message())) {
            checksum += ((*message).trd_reg_ts_time_in().has_value() ? bench::digest((*(*message).trd_reg_ts_time_in())) : std::uint64_t{0});
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().trd_reg_ts_time_priority().has_value() ? bench::digest((*(*message).order_details_comp().trd_reg_ts_time_priority())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().display_qty().has_value() ? bench::digest((*(*message).order_details_comp().display_qty())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().side().has_value() ? bench::digest((*(*message).order_details_comp().side())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().price().has_value() ? bench::digest((*(*message).order_details_comp().price()).mantissa()) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::OrderMassDelete*>(each.message())) {
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::OrderModify*>(each.message())) {
            checksum += ((*message).trd_reg_ts_time_in().has_value() ? bench::digest((*(*message).trd_reg_ts_time_in())) : std::uint64_t{0});
            checksum += ((*message).trd_reg_ts_prev_time_priority().has_value() ? bench::digest((*(*message).trd_reg_ts_prev_time_priority())) : std::uint64_t{0});
            checksum += ((*message).prev_price().has_value() ? bench::digest((*(*message).prev_price()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).prev_display_qty().has_value() ? bench::digest((*(*message).prev_display_qty())) : std::uint64_t{0});
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().trd_reg_ts_time_priority().has_value() ? bench::digest((*(*message).order_details_comp().trd_reg_ts_time_priority())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().display_qty().has_value() ? bench::digest((*(*message).order_details_comp().display_qty())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().side().has_value() ? bench::digest((*(*message).order_details_comp().side())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().price().has_value() ? bench::digest((*(*message).order_details_comp().price()).mantissa()) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::OrderModifySamePrio*>(each.message())) {
            checksum += ((*message).trd_reg_ts_time_in().has_value() ? bench::digest((*(*message).trd_reg_ts_time_in())) : std::uint64_t{0});
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
            checksum += ((*message).prev_display_qty().has_value() ? bench::digest((*(*message).prev_display_qty())) : std::uint64_t{0});
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().trd_reg_ts_time_priority().has_value() ? bench::digest((*(*message).order_details_comp().trd_reg_ts_time_priority())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().display_qty().has_value() ? bench::digest((*(*message).order_details_comp().display_qty())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().side().has_value() ? bench::digest((*(*message).order_details_comp().side())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().price().has_value() ? bench::digest((*(*message).order_details_comp().price()).mantissa()) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::PartialOrderExecution*>(each.message())) {
            checksum += ((*message).side().has_value() ? bench::digest((*(*message).side())) : std::uint64_t{0});
            checksum += ((*message).price().has_value() ? bench::digest((*(*message).price()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).trd_reg_ts_time_priority().has_value() ? bench::digest((*(*message).trd_reg_ts_time_priority())) : std::uint64_t{0});
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).trd_match_id().has_value() ? bench::digest((*(*message).trd_match_id())) : std::uint64_t{0});
            checksum += ((*message).last_qty().has_value() ? bench::digest((*(*message).last_qty())) : std::uint64_t{0});
            checksum += ((*message).last_px().has_value() ? bench::digest((*(*message).last_px()).mantissa()) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::ProductStateChange*>(each.message())) {
            checksum += ((*message).trading_session_id().has_value() ? bench::digest((*(*message).trading_session_id())) : std::uint64_t{0});
            checksum += ((*message).trading_session_sub_id().has_value() ? bench::digest((*(*message).trading_session_sub_id())) : std::uint64_t{0});
            checksum += ((*message).trad_ses_status().has_value() ? bench::digest((*(*message).trad_ses_status())) : std::uint64_t{0});
            checksum += ((*message).fast_market_indicator().has_value() ? bench::digest((*(*message).fast_market_indicator())) : std::uint64_t{0});
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::ProductSummary*>(each.message())) {
            checksum += ((*message).last_msg_seq_num_processed().has_value() ? bench::digest((*(*message).last_msg_seq_num_processed())) : std::uint64_t{0});
            checksum += ((*message).trading_session_id().has_value() ? bench::digest((*(*message).trading_session_id())) : std::uint64_t{0});
            checksum += ((*message).trading_session_sub_id().has_value() ? bench::digest((*(*message).trading_session_sub_id())) : std::uint64_t{0});
            checksum += ((*message).trad_ses_status().has_value() ? bench::digest((*(*message).trad_ses_status())) : std::uint64_t{0});
            checksum += ((*message).fast_market_indicator().has_value() ? bench::digest((*(*message).fast_market_indicator())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::QuoteRequest*>(each.message())) {
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).last_qty().has_value() ? bench::digest((*(*message).last_qty())) : std::uint64_t{0});
            checksum += ((*message).side().has_value() ? bench::digest((*(*message).side())) : std::uint64_t{0});
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::SnapshotOrder*>(each.message())) {
            checksum += ((*message).order_details_comp().trd_reg_ts_time_priority().has_value() ? bench::digest((*(*message).order_details_comp().trd_reg_ts_time_priority())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().display_qty().has_value() ? bench::digest((*(*message).order_details_comp().display_qty())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().side().has_value() ? bench::digest((*(*message).order_details_comp().side())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().price().has_value() ? bench::digest((*(*message).order_details_comp().price()).mantissa()) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::TopOfBook*>(each.message())) {
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).bid_px().has_value() ? bench::digest((*(*message).bid_px()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).offer_px().has_value() ? bench::digest((*(*message).offer_px()).mantissa()) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::TradeReport*>(each.message())) {
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
            checksum += ((*message).trd_match_id().has_value() ? bench::digest((*(*message).trd_match_id())) : std::uint64_t{0});
            checksum += ((*message).last_qty().has_value() ? bench::digest((*(*message).last_qty())) : std::uint64_t{0});
            checksum += ((*message).last_px().has_value() ? bench::digest((*(*message).last_px()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).match_type().has_value() ? bench::digest((*(*message).match_type())) : std::uint64_t{0});
            checksum += ((*message).match_sub_type().has_value() ? bench::digest((*(*message).match_sub_type())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::TradeReversal*>(each.message())) {
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
            checksum += ((*message).trd_match_id().has_value() ? bench::digest((*(*message).trd_match_id())) : std::uint64_t{0});
            checksum += ((*message).last_qty().has_value() ? bench::digest((*(*message).last_qty())) : std::uint64_t{0});
            checksum += ((*message).last_px().has_value() ? bench::digest((*(*message).last_px()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).trd_reg_ts_execution_time().has_value() ? bench::digest((*(*message).trd_reg_ts_execution_time())) : std::uint64_t{0});
            checksum += ((*message).no_md_entries().has_value() ? bench::digest((*(*message).no_md_entries())) : std::uint64_t{0});
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Eurex.T7.Eobi.Fbe.v3.0", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
