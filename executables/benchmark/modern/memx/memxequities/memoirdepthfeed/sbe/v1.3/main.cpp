// Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3: main.cpp
// Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/memx/memxequities/memoirdepthfeed/sbe/v1.3.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/memx/memxequities/memoirdepthfeed/sbe/v1.3/definitions.hpp"

namespace protocol = ::memx::memxequities::memoirdepthfeed::sbe::v1_3;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    if (iterator.sequenced_message != nullptr) {
        checksum += bench::digest(iterator.sequenced_message->message_count.get());
    }

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.message_header->message_length.get());

        if (iterator.template_id == 1) {
            [[maybe_unused]] const auto* message = protocol::InstrumentDirectoryMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->symbol_sfx.get());
            checksum += bench::digest(message->round_lot.get());
            checksum += bench::digest(message->is_test_symbol.get());
            checksum += bench::digest(message->mpv.integer());
        } else if (iterator.template_id == 2) {
            [[maybe_unused]] const auto* message = protocol::RegShoRestrictionMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->short_sale_restriction.get());
        } else if (iterator.template_id == 3) {
            [[maybe_unused]] const auto* message = protocol::SecurityTradingStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->security_trading_status.get());
            checksum += bench::digest(message->security_trading_status_reason.get());
        } else if (iterator.template_id == 5) {
            [[maybe_unused]] const auto* message = protocol::TradingSessionStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->trading_session.get());
        } else if (iterator.template_id == 10) {
            [[maybe_unused]] const auto* message = protocol::OrderAddedMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->price.integer());
        } else if (iterator.template_id == 11) {
            [[maybe_unused]] const auto* message = protocol::OrderDeletedMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->order_id.get());
        } else if (iterator.template_id == 12) {
            [[maybe_unused]] const auto* message = protocol::OrderReducedMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->quantity.get());
        } else if (iterator.template_id == 13) {
            [[maybe_unused]] const auto* message = protocol::OrderExecutedMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->trade_id.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->price.integer());
        } else if (iterator.template_id == 14) {
            [[maybe_unused]] const auto* message = protocol::TradeMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->trade_id.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->price.integer());
        } else if (iterator.template_id == 15) {
            [[maybe_unused]] const auto* message = protocol::BrokenTradeMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->trade_id.get());
            checksum += bench::digest(message->original_quantity.get());
            checksum += bench::digest(message->original_price.integer());
        } else if (iterator.template_id == 16) {
            [[maybe_unused]] const auto* message = protocol::CorrectedTradeMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->trade_id.get());
            checksum += bench::digest(message->original_quantity.get());
            checksum += bench::digest(message->original_price.integer());
            checksum += bench::digest(message->corrected_quantity.get());
            checksum += bench::digest(message->corrected_price.integer());
        } else if (iterator.template_id == 18) {
            [[maybe_unused]] const auto* message = protocol::ClearBookMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->security_id.get());
        } else if (iterator.template_id == 100) {
            [[maybe_unused]] const auto* message = protocol::SnapshotCompleteMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->as_of_sequence_number.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
