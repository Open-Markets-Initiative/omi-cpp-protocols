// Bse.BseIndia.Eobi.Fbe.v1.4: main.cpp
// Bse.BseIndia.Eobi.Fbe.v1.4 benchmark, through the Modern iterator: every value it reads from every message of the simulated
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
#include "cpp/binary/modern/bse/bseindia/eobi/fbe/v1.4/definitions.hpp"

namespace protocol = ::bse::bseindia::eobi::fbe::v1_4;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    checksum += bench::digest(iterator.packet_header->eobi_header.body_len.get());
    checksum += bench::digest(iterator.packet_header->eobi_header.template_id.get());
    checksum += bench::digest(iterator.packet_header->eobi_header.msg_seq_num.get());
    checksum += bench::digest(iterator.packet_header->appl_seq_num.get());
    checksum += bench::digest(iterator.packet_header->market_segment_id.get());
    checksum += bench::digest(iterator.packet_header->partition_id.get());
    checksum += bench::digest(iterator.packet_header->completion_indicator.get());
    checksum += bench::digest(iterator.packet_header->appl_seq_reset_indicator.get());
    checksum += bench::digest(iterator.packet_header->transact_time.get());

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.message_header->body_len.get());
        checksum += bench::digest(iterator.message_header->template_id.get());
        checksum += bench::digest(iterator.message_header->msg_seq_num.get());

        if (iterator.template_id == protocol::HeartbeatMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::HeartbeatMessage::parse(iterator.message);
            checksum += bench::digest(message->last_msg_seq_num_processed.get());
        } else if (iterator.template_id == protocol::ProductSummaryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ProductSummaryMessage::parse(iterator.message);
            checksum += bench::digest(message->last_msg_seq_num_processed.get());
            checksum += bench::digest(message->trading_session_id.get());
            checksum += bench::digest(message->trading_session_sub_id.get());
            checksum += bench::digest(message->trad_ses_status.get());
            checksum += bench::digest(message->fast_market_indicator.get());
        } else if (iterator.template_id == protocol::SnapshotOrderMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SnapshotOrderMessage::parse(iterator.message);
            checksum += bench::digest(message->order_details.trd_reg_ts_time_priority.get());
            checksum += bench::digest(message->order_details.display_qty.get());
            checksum += bench::digest(message->order_details.side.get());
            checksum += bench::digest(message->order_details.price.integer());
        } else if (iterator.template_id == protocol::InstrumentSummaryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::InstrumentSummaryMessage::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->last_update_time.get());
            checksum += (static_cast<std::uint64_t>(message->trd_reg_ts_execution_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->trd_reg_ts_execution_time.get()) : std::uint64_t{0});
            checksum += bench::digest(message->tot_no_orders.get());
            checksum += bench::digest(message->security_status.get());
            checksum += bench::digest(message->security_trading_status.get());
            checksum += bench::digest(message->fast_market_indicator.get());
            checksum += bench::digest(message->no_md_entries.get());
            checksum += bench::digest(message->trade_volume.get());
            checksum += bench::digest(message->no_of_trades.get());
        } else if (iterator.template_id == protocol::AuctionBestBidOfferMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AuctionBestBidOfferMessage::parse(iterator.message);
            checksum += bench::digest(message->transact_time.get());
            checksum += bench::digest(message->security_id.get());
            checksum += (static_cast<std::uint64_t>(message->bid_px.integer()) != 0x08000000000000000ULL ? bench::digest(message->bid_px.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->offer_px.integer()) != 0x08000000000000000ULL ? bench::digest(message->offer_px.integer()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::AuctionClearingPriceMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AuctionClearingPriceMessage::parse(iterator.message);
            checksum += bench::digest(message->transact_time.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->last_px.integer());
            checksum += bench::digest(message->last_qty.get());
        } else if (iterator.template_id == protocol::TopOfBookMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TopOfBookMessage::parse(iterator.message);
            checksum += bench::digest(message->transact_time.get());
            checksum += bench::digest(message->security_id.get());
            checksum += (static_cast<std::uint64_t>(message->bid_px.integer()) != 0x08000000000000000ULL ? bench::digest(message->bid_px.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->offer_px.integer()) != 0x08000000000000000ULL ? bench::digest(message->offer_px.integer()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::OrderAddMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderAddMessage::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->trd_reg_ts_time_in.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->trd_reg_ts_time_in.get()) : std::uint64_t{0});
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->order_details.trd_reg_ts_time_priority.get());
            checksum += bench::digest(message->order_details.display_qty.get());
            checksum += bench::digest(message->order_details.side.get());
            checksum += bench::digest(message->order_details.price.integer());
        } else if (iterator.template_id == protocol::OrderModifyMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderModifyMessage::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->trd_reg_ts_time_in.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->trd_reg_ts_time_in.get()) : std::uint64_t{0});
            checksum += bench::digest(message->trd_reg_ts_prev_time_priority.get());
            checksum += bench::digest(message->prev_price.integer());
            checksum += bench::digest(message->prev_display_qty.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->order_details.trd_reg_ts_time_priority.get());
            checksum += bench::digest(message->order_details.display_qty.get());
            checksum += bench::digest(message->order_details.side.get());
            checksum += bench::digest(message->order_details.price.integer());
        } else if (iterator.template_id == protocol::OrderModifySamePriorityMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderModifySamePriorityMessage::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->trd_reg_ts_time_in.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->trd_reg_ts_time_in.get()) : std::uint64_t{0});
            checksum += bench::digest(message->transact_time.get());
            checksum += bench::digest(message->prev_display_qty.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->order_details.trd_reg_ts_time_priority.get());
            checksum += bench::digest(message->order_details.display_qty.get());
            checksum += bench::digest(message->order_details.side.get());
            checksum += bench::digest(message->order_details.price.integer());
        } else if (iterator.template_id == protocol::OrderDeleteMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderDeleteMessage::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->trd_reg_ts_time_in.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->trd_reg_ts_time_in.get()) : std::uint64_t{0});
            checksum += bench::digest(message->transact_time.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->order_details.trd_reg_ts_time_priority.get());
            checksum += bench::digest(message->order_details.display_qty.get());
            checksum += bench::digest(message->order_details.side.get());
            checksum += bench::digest(message->order_details.price.integer());
        } else if (iterator.template_id == protocol::OrderMassDeleteMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderMassDeleteMessage::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->transact_time.get());
        } else if (iterator.template_id == protocol::PartialOrderExecutionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::PartialOrderExecutionMessage::parse(iterator.message);
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->trd_reg_ts_time_priority.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->trd_match_id.get());
            checksum += bench::digest(message->last_qty.get());
            checksum += bench::digest(message->last_px.integer());
        } else if (iterator.template_id == protocol::FullOrderExecutionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::FullOrderExecutionMessage::parse(iterator.message);
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->trd_reg_ts_time_priority.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->trd_match_id.get());
            checksum += bench::digest(message->last_qty.get());
            checksum += bench::digest(message->last_px.integer());
        } else if (iterator.template_id == protocol::TradeReversalMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeReversalMessage::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->transact_time.get());
            checksum += bench::digest(message->trd_match_id.get());
            checksum += bench::digest(message->last_qty.get());
            checksum += bench::digest(message->last_px.integer());
            checksum += (static_cast<std::uint64_t>(message->trd_reg_ts_execution_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->trd_reg_ts_execution_time.get()) : std::uint64_t{0});
            checksum += bench::digest(message->no_md_entries.get());
        } else if (iterator.template_id == protocol::ExecutionSummaryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ExecutionSummaryMessage::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += (static_cast<std::uint64_t>(message->aggressor_timestamp.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->aggressor_timestamp.get()) : std::uint64_t{0});
            checksum += bench::digest(message->exec_id.get());
            checksum += bench::digest(message->last_qty.get());
            checksum += bench::digest(message->aggressor_side.get());
            checksum += (static_cast<std::uint8_t>(message->trade_condition.get()) != 0x0FFU ? bench::digest(message->trade_condition.get()) : std::uint64_t{0});
            checksum += bench::digest(message->last_px.integer());
            checksum += (static_cast<std::uint64_t>(message->resting_hidden_qty.get()) != 0x08000000000000000ULL ? bench::digest(message->resting_hidden_qty.get()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::InstrumentInfoMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::InstrumentInfoMessage::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += (static_cast<std::uint64_t>(message->close_price.integer()) != 0x08000000000000000ULL ? bench::digest(message->close_price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->prev_close_price.integer()) != 0x08000000000000000ULL ? bench::digest(message->prev_close_price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->upper_ckt_limit.integer()) != 0x08000000000000000ULL ? bench::digest(message->upper_ckt_limit.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->lower_ckt_limit.integer()) != 0x08000000000000000ULL ? bench::digest(message->lower_ckt_limit.integer()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::LppRangeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::LppRangeMessage::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->upper_exec_limit.integer());
            checksum += bench::digest(message->lower_exec_limit.integer());
        } else if (iterator.template_id == protocol::ProductStateChangeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ProductStateChangeMessage::parse(iterator.message);
            checksum += bench::digest(message->trading_session_id.get());
            checksum += bench::digest(message->trading_session_sub_id.get());
            checksum += bench::digest(message->trad_ses_status.get());
            checksum += bench::digest(message->fast_market_indicator.get());
            checksum += bench::digest(message->transact_time.get());
        } else if (iterator.template_id == protocol::InstrumentStateChangeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::InstrumentStateChangeMessage::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->security_status.get());
            checksum += bench::digest(message->security_trading_status.get());
            checksum += bench::digest(message->fast_market_indicator.get());
            checksum += bench::digest(message->transact_time.get());
        } else if (iterator.template_id == protocol::AddComplexInstrumentMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddComplexInstrumentMessage::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->transact_time.get());
            checksum += (static_cast<std::uint32_t>(message->security_sub_type.get()) != 0x080000000U ? bench::digest(message->security_sub_type.get()) : std::uint64_t{0});
            checksum += bench::digest(message->product_complex.get());
            checksum += bench::digest(message->implied_market_indicator.get());
            checksum += bench::digest(message->no_legs.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Bse.BseIndia.Eobi.Fbe.v1.4", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
