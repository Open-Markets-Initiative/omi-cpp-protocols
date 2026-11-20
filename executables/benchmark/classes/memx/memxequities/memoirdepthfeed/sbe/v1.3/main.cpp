// Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3: main.cpp
// Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3 benchmark, through the Classes Packet: every value it reads from every message of the simulated
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
#include "cpp/binary/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/definitions.hpp"

namespace protocol = ::memx::memxequities::memoirdepthfeed::sbe::v1_3;

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

    checksum += bench::digest(packet.common_header().message_type());
    checksum += bench::digest(packet.common_header().header_length());
    checksum += bench::digest(packet.common_header().session_id());
    checksum += bench::digest(packet.common_header().sequence_number());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_length());
        checksum += bench::digest(each.sbe_header().block_length());
        checksum += bench::digest(each.sbe_header().template_id());
        checksum += bench::digest(each.sbe_header().schema_id());
        checksum += bench::digest(each.sbe_header().version());

        if (const auto* message = dynamic_cast<const protocol::InstrumentDirectoryMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).symbol_sfx());
            checksum += bench::digest((*message).round_lot());
            checksum += bench::digest((*message).is_test_symbol());
            checksum += bench::digest((*message).mpv().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::RegShoRestrictionMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).short_sale_restriction());
        } else if (const auto* message = dynamic_cast<const protocol::SecurityTradingStatusMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).security_trading_status());
            checksum += bench::digest((*message).security_trading_status_reason());
        } else if (const auto* message = dynamic_cast<const protocol::TradingSessionStatusMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).trading_session());
        } else if (const auto* message = dynamic_cast<const protocol::OrderAddedMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::OrderDeletedMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).order_id());
        } else if (const auto* message = dynamic_cast<const protocol::OrderReducedMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).quantity());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).trade_id());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::TradeMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).trade_id());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::BrokenTradeMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).trade_id());
            checksum += bench::digest((*message).original_quantity());
            checksum += bench::digest((*message).original_price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::CorrectedTradeMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).trade_id());
            checksum += bench::digest((*message).original_quantity());
            checksum += bench::digest((*message).original_price().mantissa());
            checksum += bench::digest((*message).corrected_quantity());
            checksum += bench::digest((*message).corrected_price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::ClearBookMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).security_id());
        } else if (const auto* message = dynamic_cast<const protocol::SnapshotCompleteMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).as_of_sequence_number());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
