// Nyse.NyseEquities.ImbalancesFeed.Xdp.v2.2.a benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/nyse/nyseequities/imbalancesfeed/xdp/v2.2.a.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/nyse/nyseequities/imbalancesfeed/xdp/v2.2.a/definitions.hpp"

namespace protocol = ::nyse::nyseequities::imbalancesfeed::xdp::v2_2_a;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    checksum += bench::digest(iterator.packet_header->packet_size.get());
    checksum += bench::digest(iterator.packet_header->delivery_flag.get());
    checksum += bench::digest(iterator.packet_header->message_count.get());
    checksum += bench::digest(iterator.packet_header->sequence_number.get());
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
        } else if (iterator.message_type == protocol::RetransmissionRequestMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::RetransmissionRequestMessage::parse(iterator.message);
            checksum += bench::digest(message->begin_seq_num.get());
            checksum += bench::digest(message->end_seq_num.get());
            checksum += bench::digest(message->source_id.get());
            checksum += bench::digest(message->product_id.get());
            checksum += bench::digest(message->channel_id.get());
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
        } else if (iterator.message_type == protocol::RefreshHeaderMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::RefreshHeaderMessage::parse(iterator.message);
            checksum += bench::digest(message->current_refresh_pkt.get());
            checksum += bench::digest(message->total_refresh_pkts.get());
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
            checksum += bench::digest(message->closing_only_clearing_price.get());
            checksum += bench::digest(message->ssr_filing_price.get());
            checksum += bench::digest(message->indicative_match_price.get());
            checksum += bench::digest(message->upper_collar.get());
            checksum += bench::digest(message->lower_collar.get());
            checksum += bench::digest(message->auction_status.get());
            checksum += bench::digest(message->freeze_status.get());
            checksum += bench::digest(message->num_extensions.get());
            checksum += bench::digest(message->unpaired_qty.get());
            checksum += bench::digest(message->unpaired_side.get());
            checksum += bench::digest(message->significant_imbalance.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nyse.NyseEquities.ImbalancesFeed.Xdp.v2.2.a", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
