// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: main.cpp
// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/miax/pearlequities/depthofmarket/mach/v1.3.d.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/miax/pearlequities/depthofmarket/mach/v1.3.d/definitions.hpp"

namespace protocol = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MachMessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.mach_packet_header->sequence_number.get());
        checksum += bench::digest(iterator.mach_packet_header->mach_packet_length.get());
        checksum += bench::digest(iterator.mach_packet_header->mach_packet_type.get());
        checksum += bench::digest(iterator.mach_packet_header->session_number.get());

        if (iterator.mach_packet_type == 3) {
            [[maybe_unused]] const auto* message = protocol::ApplicationMessage::parse(iterator.message);
            checksum += bench::digest(message->message_type.get());
            if (message->message_type.get() == protocol::SystemTimeMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::SystemTimeMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->seconds.get());
            } else if (message->message_type.get() == protocol::SymbolUpdateMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::SymbolUpdateMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->symbol_id.get());
                checksum += bench::digest(message_2->ticker_symbol.get());
                checksum += bench::digest(message_2->test_security_indicator.get());
                checksum += bench::digest(message_2->lot_size.get());
                checksum += bench::digest(message_2->opening_time.get());
                checksum += bench::digest(message_2->closing_time.get());
                checksum += bench::digest(message_2->primary_market_code.get());
            } else if (message->message_type.get() == protocol::SystemStateMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::SystemStateMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->do_m_version.get());
                checksum += bench::digest(message_2->session_id.get());
                checksum += bench::digest(message_2->system_status.get());
            } else if (message->message_type.get() == protocol::SecurityTradingStatusNotificationMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::SecurityTradingStatusNotificationMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->symbol_id.get());
                checksum += bench::digest(message_2->trading_status.get());
                checksum += bench::digest(message_2->market_state.get());
                checksum += bench::digest(message_2->short_sale_restriction.get());
            } else if (message->message_type.get() == protocol::SymbolClearMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::SymbolClearMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->symbol_id.get());
            } else if (message->message_type.get() == protocol::AddOrderMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::AddOrderMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->symbol_id.get());
                checksum += bench::digest(message_2->order_id.get());
                checksum += bench::digest(message_2->order_side.get());
                checksum += bench::digest(message_2->price.integer());
                checksum += bench::digest(message_2->size.get());
                checksum += bench::digest(message_2->attributable_id.get());
            } else if (message->message_type.get() == protocol::ModifyOrderMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::ModifyOrderMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->symbol_id.get());
                checksum += bench::digest(message_2->order_id.get());
                checksum += bench::digest(message_2->price.integer());
                checksum += bench::digest(message_2->size.get());
                checksum += bench::digest(message_2->modify_order_flags.OrderPosition());
            } else if (message->message_type.get() == protocol::DeleteOrderMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::DeleteOrderMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->symbol_id.get());
                checksum += bench::digest(message_2->order_id.get());
            } else if (message->message_type.get() == protocol::OrderExecutionMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::OrderExecutionMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->symbol_id.get());
                checksum += bench::digest(message_2->order_id.get());
                checksum += bench::digest(message_2->trade_id.get());
                checksum += bench::digest(message_2->price.integer());
                checksum += bench::digest(message_2->size.get());
                checksum += bench::digest(message_2->order_execution_flags.SipReporting());
                checksum += bench::digest(message_2->order_execution_flags.TradedAgainstRetail());
            } else if (message->message_type.get() == protocol::TradeMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::TradeMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->symbol_id.get());
                checksum += bench::digest(message_2->trade_id.get());
                checksum += bench::digest(message_2->correction_number.get());
                checksum += bench::digest(message_2->price.integer());
                checksum += bench::digest(message_2->size.get());
                checksum += bench::digest(message_2->trade_flags.SipReporting());
                checksum += bench::digest(message_2->trade_flags.RetailTradeIndicator());
            } else if (message->message_type.get() == protocol::TradeCancelMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::TradeCancelMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->nanoseconds.get());
                checksum += bench::digest(message_2->symbol_id.get());
                checksum += bench::digest(message_2->trade_id.get());
                checksum += bench::digest(message_2->correction_number.get());
                checksum += bench::digest(message_2->price.integer());
                checksum += bench::digest(message_2->size.get());
            }
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
