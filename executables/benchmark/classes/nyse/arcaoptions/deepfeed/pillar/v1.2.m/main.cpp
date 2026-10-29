// Nyse.ArcaOptions.DeepFeed.Pillar.v1.2.m benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/nyse/arcaoptions/deepfeed/pillar/v1.2.m.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/definitions.hpp"

namespace protocol = ::nyse::arcaoptions::deepfeed::pillar::v1_2_m;

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

    checksum += bench::digest(packet.packet_header().pkt_size());
    checksum += bench::digest(packet.packet_header().delivery_flag());
    checksum += bench::digest(packet.packet_header().number_msgs());
    checksum += bench::digest(packet.packet_header().seq_num());
    checksum += bench::digest(packet.packet_header().send_time().seconds());
    checksum += bench::digest(packet.packet_header().send_time().nanoseconds());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_header().message_size());
        checksum += bench::digest(each.message_header().message_type());

        if (const auto* message = dynamic_cast<const protocol::SequenceNumberResetMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).product_id());
            checksum += bench::digest((*message).channel_id());
        } else if (const auto* message = dynamic_cast<const protocol::SourceTimeReferenceMessage*>(each.message())) {
            checksum += bench::digest((*message).id());
            checksum += bench::digest((*message).symbol_seq_num());
            checksum += bench::digest((*message).source_time());
        } else if (const auto* message = dynamic_cast<const protocol::SymbolIndexMappingMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol_index());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).market_id());
            checksum += bench::digest((*message).system_id());
            checksum += bench::digest((*message).exchange_code());
            checksum += bench::digest((*message).price_scale_code());
            checksum += bench::digest((*message).security_type());
            checksum += bench::digest((*message).lot_size());
            checksum += bench::digest((*message).prev_close_price());
            checksum += bench::digest((*message).prev_close_volume());
            checksum += bench::digest((*message).price_resolution());
            checksum += bench::digest((*message).round_lot());
        } else if (const auto* message = dynamic_cast<const protocol::SymbolClearMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).symbol_index());
            checksum += bench::digest((*message).next_source_seq_num());
        } else if (const auto* message = dynamic_cast<const protocol::SecurityStatusMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).symbol_index());
            checksum += bench::digest((*message).symbol_seq_num());
            checksum += bench::digest((*message).security_status());
            checksum += bench::digest((*message).halt_condition());
            checksum += bench::digest((*message).price_1());
            checksum += bench::digest((*message).price_2());
            checksum += bench::digest((*message).ssr_triggering_exchange_id());
            checksum += bench::digest((*message).ssr_triggering_volume());
            checksum += ((*message).time().has_value() ? bench::digest((*(*message).time())) : std::uint64_t{0});
            checksum += bench::digest((*message).ssr_state());
            checksum += bench::digest((*message).market_state());
            checksum += bench::digest((*message).session_state());
        } else if (const auto* message = dynamic_cast<const protocol::OutrightSeriesIndexMappingMessage*>(each.message())) {
            checksum += bench::digest((*message).series_index());
            checksum += bench::digest((*message).series_type());
            checksum += bench::digest((*message).market_id());
            checksum += bench::digest((*message).system_id());
            checksum += bench::digest((*message).option_symbol_root());
            checksum += bench::digest((*message).underlying_symbol());
            checksum += bench::digest((*message).underlying_index());
            checksum += bench::digest((*message).price_scale_code());
            checksum += bench::digest((*message).contract_multiplier());
            checksum += bench::digest((*message).maturity_date());
            checksum += bench::digest((*message).put_or_call());
            checksum += bench::digest((*message).strike_price());
            checksum += bench::digest((*message).closing_only_indicator());
        } else if (const auto* message = dynamic_cast<const protocol::OptionsStatusMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).series_index());
            checksum += bench::digest((*message).series_seq_num());
            checksum += bench::digest((*message).series_status());
            checksum += bench::digest((*message).market_state());
            checksum += bench::digest((*message).options_status_halt_condition());
        } else if (const auto* message = dynamic_cast<const protocol::ComplexSeriesIndexMappingMessage*>(each.message())) {
            checksum += bench::digest((*message).series_index());
            checksum += bench::digest((*message).market_id());
            checksum += bench::digest((*message).system_id());
            checksum += bench::digest((*message).no_of_legs());
        } else if (const auto* message = dynamic_cast<const protocol::RetransmissionRequestMessage*>(each.message())) {
            checksum += bench::digest((*message).begin_seq_num());
            checksum += bench::digest((*message).end_seq_num());
            checksum += bench::digest((*message).source_id());
            checksum += bench::digest((*message).product_id());
            checksum += bench::digest((*message).channel_id());
        } else if (const auto* message = dynamic_cast<const protocol::RefreshHeaderMessage*>(each.message())) {
            checksum += bench::digest((*message).current_refresh_pkt());
            checksum += bench::digest((*message).total_refresh_pkts());
        } else if (const auto* message = dynamic_cast<const protocol::RefreshRequestMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol_index());
            checksum += bench::digest((*message).source_id());
            checksum += bench::digest((*message).product_id());
            checksum += bench::digest((*message).channel_id());
        } else if (const auto* message = dynamic_cast<const protocol::SymbolIndexMappingRequestMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol_index());
            checksum += bench::digest((*message).source_id());
            checksum += bench::digest((*message).product_id());
            checksum += bench::digest((*message).channel_id());
            checksum += bench::digest((*message).retransmit_method());
        } else if (const auto* message = dynamic_cast<const protocol::MessageUnavailableMessage*>(each.message())) {
            checksum += bench::digest((*message).begin_seq_num());
            checksum += bench::digest((*message).end_seq_num());
            checksum += bench::digest((*message).product_id());
            checksum += bench::digest((*message).channel_id());
        } else if (const auto* message = dynamic_cast<const protocol::RequestResponseMessage*>(each.message())) {
            checksum += bench::digest((*message).request_seq_num());
            checksum += bench::digest((*message).begin_seq_num());
            checksum += bench::digest((*message).end_seq_num());
            checksum += bench::digest((*message).source_id());
            checksum += bench::digest((*message).product_id());
            checksum += bench::digest((*message).channel_id());
            checksum += bench::digest((*message).status());
        } else if (const auto* message = dynamic_cast<const protocol::HeartbeatResponseMessage*>(each.message())) {
            checksum += bench::digest((*message).source_id());
        } else if (const auto* message = dynamic_cast<const protocol::OptionsAddOrderMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).series_index());
            checksum += bench::digest((*message).series_seq_num());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).price());
            checksum += bench::digest((*message).volume());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).firm_id());
            checksum += bench::digest((*message).cust_indicator());
        } else if (const auto* message = dynamic_cast<const protocol::OptionsModifyOrderMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).series_index());
            checksum += bench::digest((*message).series_seq_num());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).price());
            checksum += bench::digest((*message).volume());
            checksum += bench::digest((*message).position_change());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).cust_indicator());
        } else if (const auto* message = dynamic_cast<const protocol::OptionsDeleteOrderMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).series_index());
            checksum += bench::digest((*message).series_seq_num());
            checksum += bench::digest((*message).order_id());
        } else if (const auto* message = dynamic_cast<const protocol::OptionsOrderExecutionMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).series_index());
            checksum += bench::digest((*message).series_seq_num());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).trade_id());
            checksum += bench::digest((*message).price());
            checksum += bench::digest((*message).volume());
            checksum += bench::digest((*message).printable_flag());
            checksum += bench::digest((*message).trade_cond_1());
        } else if (const auto* message = dynamic_cast<const protocol::OptionsReplaceOrderMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).series_index());
            checksum += bench::digest((*message).series_seq_num());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).new_order_id());
            checksum += bench::digest((*message).price());
            checksum += bench::digest((*message).volume());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).cust_indicator());
        } else if (const auto* message = dynamic_cast<const protocol::OptionsImbalanceMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).series_index());
            checksum += bench::digest((*message).series_seq_num());
            checksum += bench::digest((*message).paired_qty());
            checksum += bench::digest((*message).total_imbalance_qty());
            checksum += bench::digest((*message).market_imbalance_qty());
            checksum += bench::digest((*message).auction_type());
            checksum += bench::digest((*message).imbalance_side());
            checksum += bench::digest((*message).continuous_book_clearing_price());
            checksum += bench::digest((*message).auction_interest_clearing_price());
            checksum += bench::digest((*message).indicative_match_price());
            checksum += bench::digest((*message).upper_collar());
            checksum += bench::digest((*message).lower_collar());
            checksum += bench::digest((*message).auction_status());
        } else if (const auto* message = dynamic_cast<const protocol::OptionsAddOrderRefreshMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).series_index());
            checksum += bench::digest((*message).series_seq_num());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).price());
            checksum += bench::digest((*message).volume());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).firm_id());
            checksum += bench::digest((*message).cust_indicator());
        } else if (const auto* message = dynamic_cast<const protocol::OptionsSeriesRfqMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).series_index());
            checksum += bench::digest((*message).series_seq_num());
            checksum += bench::digest((*message).rfq_side());
            checksum += bench::digest((*message).type_field());
            checksum += bench::digest((*message).capacity());
            checksum += bench::digest((*message).total_quantity());
            checksum += bench::digest((*message).working_price());
            checksum += bench::digest((*message).participant());
            checksum += bench::digest((*message).auction_id());
            checksum += bench::digest((*message).rfq_status());
        } else if (const auto* message = dynamic_cast<const protocol::OptionsNonDisplayedTradeMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).series_index());
            checksum += bench::digest((*message).series_seq_num());
            checksum += bench::digest((*message).trade_id());
            checksum += bench::digest((*message).price());
            checksum += bench::digest((*message).volume());
            checksum += bench::digest((*message).printable_flag());
            checksum += bench::digest((*message).non_displayed_trade_trade_cond_1());
            checksum += bench::digest((*message).price_type());
        } else if (const auto* message = dynamic_cast<const protocol::OptionsCrossTradeMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).series_index());
            checksum += bench::digest((*message).series_seq_num());
            checksum += bench::digest((*message).cross_id());
            checksum += bench::digest((*message).price());
            checksum += bench::digest((*message).volume());
            checksum += bench::digest((*message).cross_type());
        } else if (const auto* message = dynamic_cast<const protocol::OptionsTradeCancelMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).series_index());
            checksum += bench::digest((*message).series_seq_num());
            checksum += bench::digest((*message).trade_id());
        } else if (const auto* message = dynamic_cast<const protocol::OptionsOutrightSeriesSummaryMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).series_index());
            checksum += bench::digest((*message).high_price());
            checksum += bench::digest((*message).low_price());
            checksum += bench::digest((*message).open());
            checksum += bench::digest((*message).close());
            checksum += bench::digest((*message).total_volume());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nyse.ArcaOptions.DeepFeed.Pillar.v1.2.m", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
