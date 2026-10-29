// Nyse.NyseEquities.IntegratedFeed.Pillar.v2.5.g benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/nyse/nyseequities/integratedfeed/pillar/v2.5.g.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/nyse/nyseequities/integratedfeed/pillar/v2.5.g/definitions.hpp"

namespace protocol = ::nyse::nyseequities::integratedfeed::pillar::v2_5_g;

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
        } else if (iterator.message_type == protocol::AddOrderMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->price.get());
            checksum += bench::digest(message->volume.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->firm_id.get());
        } else if (iterator.message_type == protocol::ModifyOrderMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ModifyOrderMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->price.get());
            checksum += bench::digest(message->volume.get());
            checksum += bench::digest(message->position_change.get());
            checksum += bench::digest(message->side.get());
        } else if (iterator.message_type == protocol::DeleteOrderMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::DeleteOrderMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->order_id.get());
        } else if (iterator.message_type == protocol::OrderExecutionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderExecutionMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->trade_id.get());
            checksum += bench::digest(message->price.get());
            checksum += bench::digest(message->volume.get());
            checksum += bench::digest(message->printable_flag.get());
            checksum += bench::digest(message->trade_cond_1.get());
            checksum += bench::digest(message->trade_cond_2.get());
            checksum += bench::digest(message->trade_cond_3.get());
            checksum += bench::digest(message->trade_cond_4.get());
        } else if (iterator.message_type == protocol::ReplaceOrderMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ReplaceOrderMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->new_order_id.get());
            checksum += bench::digest(message->price.get());
            checksum += bench::digest(message->volume.get());
            checksum += bench::digest(message->side.get());
        } else if (iterator.message_type == protocol::ImbalanceMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ImbalanceMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->reference_price.get());
            checksum += bench::digest(message->paired_qty.get());
            checksum += bench::digest(message->total_imbalance_qty.get());
            checksum += bench::digest(message->market_imbalance_qty.get());
            checksum += bench::digest(message->auction_time.get());
            checksum += bench::digest(message->auction_type.get());
            checksum += bench::digest(message->imbalance_side.get());
            checksum += bench::digest(message->continuous_book_clearing_price.get());
            checksum += bench::digest(message->auction_interest_clearing_price.get());
            checksum += bench::digest(message->ssr_filing_price.get());
            checksum += bench::digest(message->indicative_match_price.get());
            checksum += bench::digest(message->upper_collar.get());
            checksum += bench::digest(message->lower_collar.get());
            checksum += bench::digest(message->auction_status.get());
            checksum += bench::digest(message->freeze_status.get());
            checksum += bench::digest(message->num_extensions.get());
            checksum += bench::digest(message->unpaired_qty.get());
            checksum += bench::digest(message->unpaired_side.get());
        } else if (iterator.message_type == protocol::AddOrderRefreshMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderRefreshMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->price.get());
            checksum += bench::digest(message->volume.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->firm_id.get());
        } else if (iterator.message_type == protocol::NonDisplayedTradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::NonDisplayedTradeMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->trade_id.get());
            checksum += bench::digest(message->price.get());
            checksum += bench::digest(message->volume.get());
            checksum += bench::digest(message->printable_flag.get());
            checksum += bench::digest(message->trade_cond_1.get());
            checksum += bench::digest(message->trade_cond_2.get());
            checksum += bench::digest(message->trade_cond_3.get());
            checksum += bench::digest(message->trade_cond_4.get());
        } else if (iterator.message_type == protocol::CrossTradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::CrossTradeMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->cross_id.get());
            checksum += bench::digest(message->price.get());
            checksum += bench::digest(message->volume.get());
            checksum += bench::digest(message->cross_type.get());
        } else if (iterator.message_type == protocol::TradeCancelMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeCancelMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->trade_id.get());
        } else if (iterator.message_type == protocol::CrossCorrectionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::CrossCorrectionMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->cross_id.get());
            checksum += bench::digest(message->volume.get());
        } else if (iterator.message_type == protocol::RetailPriceImprovementMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::RetailPriceImprovementMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->symbol_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->rpi_indicator.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nyse.NyseEquities.IntegratedFeed.Pillar.v2.5.g", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
