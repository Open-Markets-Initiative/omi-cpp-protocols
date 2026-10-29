// Iex.IexEquities.DeepPlus.IexTp.v1.05 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/iex/iexequities/deepplus/iextp/v1.05.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/iex/iexequities/deepplus/iextp/v1.05/definitions.hpp"

namespace protocol = ::iex::iexequities::deepplus::iextp::v1_05;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    checksum += bench::digest(iterator.iextp_header->version.get());
    checksum += bench::digest(iterator.iextp_header->message_protocol_id.get());
    checksum += bench::digest(iterator.iextp_header->channel_id.get());
    checksum += bench::digest(iterator.iextp_header->session_id.get());
    checksum += bench::digest(iterator.iextp_header->payload_length.get());
    checksum += bench::digest(iterator.iextp_header->message_count.get());
    checksum += bench::digest(iterator.iextp_header->stream_offset.get());
    checksum += bench::digest(iterator.iextp_header->first_message_sequence_number.get());
    checksum += bench::digest(iterator.iextp_header->send_time.get());

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.message_header->message_length.get());
        checksum += bench::digest(iterator.message_header->message_type.get());

        if (iterator.message_type == protocol::SystemEventMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SystemEventMessage::parse(iterator.message);
            checksum += bench::digest(message->system_event.get());
            checksum += bench::digest(message->timestamp.get());
        } else if (iterator.message_type == protocol::SecurityDirectoryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SecurityDirectoryMessage::parse(iterator.message);
            checksum += bench::digest(message->security_directory_flags.Etp());
            checksum += bench::digest(message->security_directory_flags.WhenIssued());
            checksum += bench::digest(message->security_directory_flags.TestSecurity());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->round_lot_size.get());
            checksum += bench::digest(message->adjusted_poc_price.integer());
            checksum += bench::digest(message->luld_tier.get());
        } else if (iterator.message_type == protocol::TradingStatusMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradingStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->trading_status.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->reason.get());
        } else if (iterator.message_type == protocol::RetailLiquidityIndicatorMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::RetailLiquidityIndicatorMessage::parse(iterator.message);
            checksum += bench::digest(message->retail_liquidity_indicator.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
        } else if (iterator.message_type == protocol::OperationalHaltStatusMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OperationalHaltStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->operational_halt_status.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
        } else if (iterator.message_type == protocol::ShortSalePriceTestStatusMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ShortSalePriceTestStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->short_sale_price_test_status.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->detail.get());
        } else if (iterator.message_type == protocol::SecurityEventMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SecurityEventMessage::parse(iterator.message);
            checksum += bench::digest(message->security_event.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
        } else if (iterator.message_type == protocol::AddOrderMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderMessage::parse(iterator.message);
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->size.get());
            checksum += bench::digest(message->price.integer());
        } else if (iterator.message_type == protocol::OrderModifyMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderModifyMessage::parse(iterator.message);
            checksum += bench::digest(message->modify_flags.Priority());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->order_id_reference.get());
            checksum += bench::digest(message->size.get());
            checksum += bench::digest(message->price.integer());
        } else if (iterator.message_type == protocol::OrderDeleteMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderDeleteMessage::parse(iterator.message);
            checksum += bench::digest(message->reserved_1.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->order_id_reference.get());
        } else if (iterator.message_type == protocol::OrderExecutedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderExecutedMessage::parse(iterator.message);
            checksum += bench::digest(message->sale_condition_flags.SinglePriceCrossTrade());
            checksum += bench::digest(message->sale_condition_flags.TradeThroughExempt());
            checksum += bench::digest(message->sale_condition_flags.OddLot());
            checksum += bench::digest(message->sale_condition_flags.ExtendedHours());
            checksum += bench::digest(message->sale_condition_flags.IntermarketSweep());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->order_id_reference.get());
            checksum += bench::digest(message->size.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->trade_id.get());
        } else if (iterator.message_type == protocol::TradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeMessage::parse(iterator.message);
            checksum += bench::digest(message->sale_condition_flags.SinglePriceCrossTrade());
            checksum += bench::digest(message->sale_condition_flags.TradeThroughExempt());
            checksum += bench::digest(message->sale_condition_flags.OddLot());
            checksum += bench::digest(message->sale_condition_flags.ExtendedHours());
            checksum += bench::digest(message->sale_condition_flags.IntermarketSweep());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->size.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->trade_id.get());
        } else if (iterator.message_type == protocol::TradeBreakMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeBreakMessage::parse(iterator.message);
            checksum += bench::digest(message->sale_condition_flags.SinglePriceCrossTrade());
            checksum += bench::digest(message->sale_condition_flags.TradeThroughExempt());
            checksum += bench::digest(message->sale_condition_flags.OddLot());
            checksum += bench::digest(message->sale_condition_flags.ExtendedHours());
            checksum += bench::digest(message->sale_condition_flags.IntermarketSweep());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->size.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->trade_id.get());
        } else if (iterator.message_type == protocol::ClearBookMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ClearBookMessage::parse(iterator.message);
            checksum += bench::digest(message->reserved_1.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Iex.IexEquities.DeepPlus.IexTp.v1.05", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
