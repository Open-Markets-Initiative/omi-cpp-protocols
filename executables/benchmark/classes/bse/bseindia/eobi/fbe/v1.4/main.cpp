// Bse.BseIndia.Eobi.Fbe.v1.4 benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/bse/bseindia/eobi/fbe/v1.4.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/bse/bseindia/eobi/fbe/v1.4/definitions.hpp"

namespace protocol = ::bse::bseindia::eobi::fbe::v1_4;

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
    checksum += bench::digest(packet.packet_header().market_segment_id());
    checksum += bench::digest(packet.packet_header().partition_id());
    checksum += bench::digest(packet.packet_header().completion_indicator());
    checksum += bench::digest(packet.packet_header().appl_seq_reset_indicator());
    checksum += bench::digest(packet.packet_header().transact_time());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_header().body_len());
        checksum += bench::digest(each.message_header().template_id());
        checksum += bench::digest(each.message_header().msg_seq_num());

        if (const auto* message = dynamic_cast<const protocol::HeartbeatMessage*>(each.message())) {
            checksum += bench::digest((*message).last_msg_seq_num_processed());
        } else if (const auto* message = dynamic_cast<const protocol::ProductSummaryMessage*>(each.message())) {
            checksum += bench::digest((*message).last_msg_seq_num_processed());
            checksum += bench::digest((*message).trading_session_id());
            checksum += bench::digest((*message).trading_session_sub_id());
            checksum += bench::digest((*message).trad_ses_status());
            checksum += bench::digest((*message).fast_market_indicator());
        } else if (const auto* message = dynamic_cast<const protocol::SnapshotOrderMessage*>(each.message())) {
            checksum += bench::digest((*message).order_details().trd_reg_ts_time_priority());
            checksum += bench::digest((*message).order_details().display_qty());
            checksum += bench::digest((*message).order_details().side());
            checksum += bench::digest((*message).order_details().price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::InstrumentSummaryMessage*>(each.message())) {
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).last_update_time());
            checksum += ((*message).trd_reg_ts_execution_time().has_value() ? bench::digest((*(*message).trd_reg_ts_execution_time())) : std::uint64_t{0});
            checksum += bench::digest((*message).tot_no_orders());
            checksum += bench::digest((*message).security_status());
            checksum += bench::digest((*message).security_trading_status());
            checksum += bench::digest((*message).fast_market_indicator());
            checksum += bench::digest((*message).no_md_entries());
            checksum += bench::digest((*message).trade_volume());
            checksum += bench::digest((*message).no_of_trades());
        } else if (const auto* message = dynamic_cast<const protocol::AuctionBestBidOfferMessage*>(each.message())) {
            checksum += bench::digest((*message).transact_time());
            checksum += bench::digest((*message).security_id());
            checksum += ((*message).bid_px().has_value() ? bench::digest((*(*message).bid_px()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).offer_px().has_value() ? bench::digest((*(*message).offer_px()).mantissa()) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::AuctionClearingPriceMessage*>(each.message())) {
            checksum += bench::digest((*message).transact_time());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).last_px().mantissa());
            checksum += bench::digest((*message).last_qty());
        } else if (const auto* message = dynamic_cast<const protocol::TopOfBookMessage*>(each.message())) {
            checksum += bench::digest((*message).transact_time());
            checksum += bench::digest((*message).security_id());
            checksum += ((*message).bid_px().has_value() ? bench::digest((*(*message).bid_px()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).offer_px().has_value() ? bench::digest((*(*message).offer_px()).mantissa()) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::OrderAddMessage*>(each.message())) {
            checksum += ((*message).trd_reg_ts_time_in().has_value() ? bench::digest((*(*message).trd_reg_ts_time_in())) : std::uint64_t{0});
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).order_details().trd_reg_ts_time_priority());
            checksum += bench::digest((*message).order_details().display_qty());
            checksum += bench::digest((*message).order_details().side());
            checksum += bench::digest((*message).order_details().price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::OrderModifyMessage*>(each.message())) {
            checksum += ((*message).trd_reg_ts_time_in().has_value() ? bench::digest((*(*message).trd_reg_ts_time_in())) : std::uint64_t{0});
            checksum += bench::digest((*message).trd_reg_ts_prev_time_priority());
            checksum += bench::digest((*message).prev_price().mantissa());
            checksum += bench::digest((*message).prev_display_qty());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).order_details().trd_reg_ts_time_priority());
            checksum += bench::digest((*message).order_details().display_qty());
            checksum += bench::digest((*message).order_details().side());
            checksum += bench::digest((*message).order_details().price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::OrderModifySamePriorityMessage*>(each.message())) {
            checksum += ((*message).trd_reg_ts_time_in().has_value() ? bench::digest((*(*message).trd_reg_ts_time_in())) : std::uint64_t{0});
            checksum += bench::digest((*message).transact_time());
            checksum += bench::digest((*message).prev_display_qty());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).order_details().trd_reg_ts_time_priority());
            checksum += bench::digest((*message).order_details().display_qty());
            checksum += bench::digest((*message).order_details().side());
            checksum += bench::digest((*message).order_details().price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::OrderDeleteMessage*>(each.message())) {
            checksum += ((*message).trd_reg_ts_time_in().has_value() ? bench::digest((*(*message).trd_reg_ts_time_in())) : std::uint64_t{0});
            checksum += bench::digest((*message).transact_time());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).order_details().trd_reg_ts_time_priority());
            checksum += bench::digest((*message).order_details().display_qty());
            checksum += bench::digest((*message).order_details().side());
            checksum += bench::digest((*message).order_details().price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::OrderMassDeleteMessage*>(each.message())) {
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).transact_time());
        } else if (const auto* message = dynamic_cast<const protocol::PartialOrderExecutionMessage*>(each.message())) {
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).trd_reg_ts_time_priority());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).trd_match_id());
            checksum += bench::digest((*message).last_qty());
            checksum += bench::digest((*message).last_px().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::FullOrderExecutionMessage*>(each.message())) {
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).trd_reg_ts_time_priority());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).trd_match_id());
            checksum += bench::digest((*message).last_qty());
            checksum += bench::digest((*message).last_px().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::TradeReversalMessage*>(each.message())) {
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).transact_time());
            checksum += bench::digest((*message).trd_match_id());
            checksum += bench::digest((*message).last_qty());
            checksum += bench::digest((*message).last_px().mantissa());
            checksum += ((*message).trd_reg_ts_execution_time().has_value() ? bench::digest((*(*message).trd_reg_ts_execution_time())) : std::uint64_t{0});
            checksum += bench::digest((*message).no_md_entries());
        } else if (const auto* message = dynamic_cast<const protocol::ExecutionSummaryMessage*>(each.message())) {
            checksum += bench::digest((*message).security_id());
            checksum += ((*message).aggressor_timestamp().has_value() ? bench::digest((*(*message).aggressor_timestamp())) : std::uint64_t{0});
            checksum += bench::digest((*message).exec_id());
            checksum += bench::digest((*message).last_qty());
            checksum += bench::digest((*message).aggressor_side());
            checksum += ((*message).trade_condition().has_value() ? bench::digest((*(*message).trade_condition())) : std::uint64_t{0});
            checksum += bench::digest((*message).last_px().mantissa());
            checksum += ((*message).resting_hidden_qty().has_value() ? bench::digest((*(*message).resting_hidden_qty())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::InstrumentInfoMessage*>(each.message())) {
            checksum += bench::digest((*message).security_id());
            checksum += ((*message).close_price().has_value() ? bench::digest((*(*message).close_price()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).prev_close_price().has_value() ? bench::digest((*(*message).prev_close_price()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).upper_ckt_limit().has_value() ? bench::digest((*(*message).upper_ckt_limit()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).lower_ckt_limit().has_value() ? bench::digest((*(*message).lower_ckt_limit()).mantissa()) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::LppRangeMessage*>(each.message())) {
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).upper_exec_limit().mantissa());
            checksum += bench::digest((*message).lower_exec_limit().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::ProductStateChangeMessage*>(each.message())) {
            checksum += bench::digest((*message).trading_session_id());
            checksum += bench::digest((*message).trading_session_sub_id());
            checksum += bench::digest((*message).trad_ses_status());
            checksum += bench::digest((*message).fast_market_indicator());
            checksum += bench::digest((*message).transact_time());
        } else if (const auto* message = dynamic_cast<const protocol::InstrumentStateChangeMessage*>(each.message())) {
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).security_status());
            checksum += bench::digest((*message).security_trading_status());
            checksum += bench::digest((*message).fast_market_indicator());
            checksum += bench::digest((*message).transact_time());
        } else if (const auto* message = dynamic_cast<const protocol::AddComplexInstrumentMessage*>(each.message())) {
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).transact_time());
            checksum += ((*message).security_sub_type().has_value() ? bench::digest((*(*message).security_sub_type())) : std::uint64_t{0});
            checksum += bench::digest((*message).product_complex());
            checksum += bench::digest((*message).implied_market_indicator());
            checksum += bench::digest((*message).no_legs());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Bse.BseIndia.Eobi.Fbe.v1.4", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
