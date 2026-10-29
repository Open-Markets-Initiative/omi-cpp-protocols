// Nyse.NationalEquities.Trades.Pillar.v2.6 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/nyse/nationalequities/trades/pillar/v2.6.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/nyse/nationalequities/trades/pillar/v2.6/definitions.hpp"

namespace protocol = ::nyse::nationalequities::trades::pillar::v2_6;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    checksum += bench::digest(iterator.packet_header->pkt_size.get());
    checksum += bench::digest(iterator.packet_header->delivery_flag.get());
    checksum += bench::digest(iterator.packet_header->number_msgs.get());
    checksum += bench::digest(iterator.packet_header->seq_num.get());
    checksum += bench::digest(iterator.packet_header->send_time.seconds.get());
    checksum += bench::digest(iterator.packet_header->send_time.nanoseconds.get());

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.message_header->message_size.get());
        checksum += bench::digest(iterator.message_header->message_type.get());

        if (iterator.message_type == protocol::SequenceNumberResetMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SequenceNumberResetMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->product_id.get());
            checksum += bench::digest(message->channel_id.get());
        } else if (iterator.message_type == protocol::SourceTimeReferenceMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SourceTimeReferenceMessage::parse(iterator.message);
            checksum += bench::digest(message->id.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->source_time.get());
        } else if (iterator.message_type == protocol::SymbolIndexMappingMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SymbolIndexMappingMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->market_id.get());
            checksum += bench::digest(message->system_id.get());
            checksum += bench::digest(message->exchange_code.get());
            checksum += bench::digest(message->price_scale_code.get());
            checksum += bench::digest(message->security_type.get());
            checksum += bench::digest(message->lot_size.get());
            checksum += bench::digest(message->prev_close_price.get());
            checksum += bench::digest(message->prev_close_volume.get());
            checksum += bench::digest(message->price_resolution.get());
            checksum += bench::digest(message->round_lot.get());
            checksum += bench::digest(message->mpv.get());
            checksum += bench::digest(message->unit_of_trade.get());
        } else if (iterator.message_type == protocol::SymbolClearMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SymbolClearMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->next_source_seq_num.get());
        } else if (iterator.message_type == protocol::SecurityStatusMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SecurityStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->security_status.get());
            checksum += bench::digest(message->halt_condition.get());
            checksum += bench::digest(message->price_1.get());
            checksum += bench::digest(message->price_2.get());
            checksum += bench::digest(message->ssr_triggering_exchange_id.get());
            checksum += bench::digest(message->ssr_triggering_volume.get());
            checksum += (static_cast<std::uint32_t>(message->time.get()) != 0x0U ? bench::digest(message->time.get()) : std::uint64_t{0});
            checksum += bench::digest(message->ssr_state.get());
            checksum += bench::digest(message->market_state.get());
            checksum += bench::digest(message->session_state.get());
        } else if (iterator.message_type == protocol::RetransmissionRequestMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::RetransmissionRequestMessage::parse(iterator.message);
            checksum += bench::digest(message->begin_seq_num.get());
            checksum += bench::digest(message->end_seq_num.get());
            checksum += bench::digest(message->source_id.get());
            checksum += bench::digest(message->product_id.get());
            checksum += bench::digest(message->channel_id.get());
        } else if (iterator.message_type == protocol::SymbolIndexMappingRequestMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SymbolIndexMappingRequestMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->source_id.get());
            checksum += bench::digest(message->product_id.get());
            checksum += bench::digest(message->channel_id.get());
            checksum += bench::digest(message->retransmit_method.get());
        } else if (iterator.message_type == protocol::RefreshRequestMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::RefreshRequestMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->source_id.get());
            checksum += bench::digest(message->product_id.get());
            checksum += bench::digest(message->channel_id.get());
        } else if (iterator.message_type == protocol::MessageUnavailableMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::MessageUnavailableMessage::parse(iterator.message);
            checksum += bench::digest(message->begin_seq_num.get());
            checksum += bench::digest(message->end_seq_num.get());
            checksum += bench::digest(message->product_id.get());
            checksum += bench::digest(message->channel_id.get());
        } else if (iterator.message_type == protocol::RefreshHeaderMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::RefreshHeaderMessage::parse(iterator.message);
            checksum += bench::digest(message->current_refresh_pkt.get());
            checksum += bench::digest(message->total_refresh_pkts.get());
        } else if (iterator.message_type == protocol::RequestResponseMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::RequestResponseMessage::parse(iterator.message);
            checksum += bench::digest(message->request_seq_num.get());
            checksum += bench::digest(message->begin_seq_num.get());
            checksum += bench::digest(message->end_seq_num.get());
            checksum += bench::digest(message->source_id.get());
            checksum += bench::digest(message->product_id.get());
            checksum += bench::digest(message->channel_id.get());
            checksum += bench::digest(message->status.get());
        } else if (iterator.message_type == protocol::HeartbeatResponseMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::HeartbeatResponseMessage::parse(iterator.message);
            checksum += bench::digest(message->source_id.get());
        } else if (iterator.message_type == protocol::TradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->trade_id.get());
            checksum += bench::digest(message->price.get());
            checksum += bench::digest(message->volume.get());
            checksum += bench::digest(message->trade_cond_1.get());
            checksum += bench::digest(message->trade_cond_2.get());
            checksum += bench::digest(message->trade_cond_3.get());
            checksum += bench::digest(message->trade_cond_4.get());
        } else if (iterator.message_type == protocol::TradeCancelMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeCancelMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->original_trade_id.get());
        } else if (iterator.message_type == protocol::TradeCorrectionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeCorrectionMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->original_trade_id.get());
            checksum += bench::digest(message->trade_id.get());
            checksum += bench::digest(message->price.get());
            checksum += bench::digest(message->volume.get());
            checksum += bench::digest(message->trade_cond_1.get());
            checksum += bench::digest(message->trade_cond_2.get());
            checksum += bench::digest(message->trade_cond_3.get());
            checksum += bench::digest(message->trade_cond_4.get());
        } else if (iterator.message_type == protocol::StockSummaryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::StockSummaryMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->high_price.get());
            checksum += bench::digest(message->low_price.get());
            checksum += bench::digest(message->open.get());
            checksum += bench::digest(message->close.get());
            checksum += bench::digest(message->total_volume.get());
        } else if (iterator.message_type == protocol::TrfFractionalTradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TrfFractionalTradeMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->trade_id.get());
            checksum += bench::digest(message->price.get());
            checksum += bench::digest(message->fractional_volume.get());
            checksum += bench::digest(message->trade_cond_1.get());
            checksum += bench::digest(message->trade_cond_2.get());
            checksum += bench::digest(message->trade_cond_3.get());
            checksum += bench::digest(message->trade_cond_4.get());
            checksum += bench::digest(message->exec_day_time.get());
            checksum += bench::digest(message->exec_day_time_ns.get());
        } else if (iterator.message_type == protocol::TrfTradeCancelMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TrfTradeCancelMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->original_trade_id.get());
        } else if (iterator.message_type == protocol::TrfFractionalTradeCorrectionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TrfFractionalTradeCorrectionMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->original_trade_id.get());
            checksum += bench::digest(message->trade_id.get());
            checksum += bench::digest(message->price.get());
            checksum += bench::digest(message->fractional_volume.get());
            checksum += bench::digest(message->trade_cond_1.get());
            checksum += bench::digest(message->trade_cond_2.get());
            checksum += bench::digest(message->trade_cond_3.get());
            checksum += bench::digest(message->trade_cond_4.get());
            checksum += bench::digest(message->exec_day_time.get());
            checksum += bench::digest(message->exec_day_time_ns.get());
        } else if (iterator.message_type == protocol::TrfFractionalPriorDayTradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TrfFractionalPriorDayTradeMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->trade_id.get());
            checksum += bench::digest(message->price.get());
            checksum += bench::digest(message->fractional_volume.get());
            checksum += bench::digest(message->trade_cond_1.get());
            checksum += bench::digest(message->trade_cond_2.get());
            checksum += bench::digest(message->trade_cond_3.get());
            checksum += bench::digest(message->trade_cond_4.get());
            checksum += bench::digest(message->prior_day_time.get());
            checksum += bench::digest(message->prior_day_time_ns.get());
        } else if (iterator.message_type == protocol::TrfFractionalPriorDayTradeCancelMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TrfFractionalPriorDayTradeCancelMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->trade_id.get());
            checksum += bench::digest(message->price.get());
            checksum += bench::digest(message->fractional_volume.get());
            checksum += bench::digest(message->prior_day_time.get());
            checksum += bench::digest(message->prior_day_time_ns.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nyse.NationalEquities.Trades.Pillar.v2.6", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
