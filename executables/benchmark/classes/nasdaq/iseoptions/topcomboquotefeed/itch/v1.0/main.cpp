// Nasdaq.IseOptions.TopComboQuoteFeed.Itch.v1.0 benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/iseoptions/topcomboquotefeed/itch/v1.0.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/definitions.hpp"

namespace protocol = ::nasdaq::iseoptions::topcomboquotefeed::itch::v1_0;

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

    checksum += bench::digest(packet.packet_header().session());
    checksum += bench::digest(packet.packet_header().sequence_number());
    checksum += bench::digest(packet.packet_header().message_count());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_header().message_length());
        checksum += bench::digest(each.message_header().message_type());

        if (const auto* message = dynamic_cast<const protocol::SystemEventMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).event_code());
            checksum += bench::digest((*message).current_year());
            checksum += bench::digest((*message).current_month());
            checksum += bench::digest((*message).current_day());
            checksum += bench::digest((*message).version());
            checksum += bench::digest((*message).sub_version());
        } else if (const auto* message = dynamic_cast<const protocol::ComplexStrategyDirectoryMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).strategy_id());
            checksum += bench::digest((*message).strategy_type());
            checksum += bench::digest((*message).source());
            checksum += bench::digest((*message).underlying_symbol());
            checksum += bench::digest((*message).number_of_legs());
        } else if (const auto* message = dynamic_cast<const protocol::StrategyOpenClosedMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).strategy_id());
            checksum += bench::digest((*message).open_state());
        } else if (const auto* message = dynamic_cast<const protocol::StrategyTradingActionMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).strategy_id());
            checksum += bench::digest((*message).current_trading_state());
        } else if (const auto* message = dynamic_cast<const protocol::StrategyBestBidAndAskUpdate*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).strategy_id());
            checksum += bench::digest((*message).quote_condition());
            checksum += bench::digest((*message).bid_price().mantissa());
            checksum += bench::digest((*message).bid_size());
            checksum += bench::digest((*message).bid_cust_size());
            checksum += bench::digest((*message).bid_pro_cust_size());
            checksum += bench::digest((*message).bid_ntt_size());
            checksum += bench::digest((*message).bid_market_size());
            checksum += bench::digest((*message).bid_ntt_market_size());
            checksum += bench::digest((*message).ask_price().mantissa());
            checksum += bench::digest((*message).ask_size());
            checksum += bench::digest((*message).ask_cust_size());
            checksum += bench::digest((*message).ask_pro_cust_size());
            checksum += bench::digest((*message).ask_ntt_size());
            checksum += bench::digest((*message).ask_market_size());
            checksum += bench::digest((*message).ask_ntt_market_size());
        } else if (const auto* message = dynamic_cast<const protocol::StrategyBestBidUpdate*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).strategy_id());
            checksum += bench::digest((*message).quote_condition());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).size());
            checksum += bench::digest((*message).cust_size());
            checksum += bench::digest((*message).pro_cust_size());
            checksum += bench::digest((*message).ntt_size());
            checksum += bench::digest((*message).market_size());
            checksum += bench::digest((*message).ntt_market_size());
        } else if (const auto* message = dynamic_cast<const protocol::StrategyBestAskUpdate*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).strategy_id());
            checksum += bench::digest((*message).quote_condition());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).size());
            checksum += bench::digest((*message).cust_size());
            checksum += bench::digest((*message).pro_cust_size());
            checksum += bench::digest((*message).ntt_size());
            checksum += bench::digest((*message).market_size());
            checksum += bench::digest((*message).ntt_market_size());
        } else if (const auto* message = dynamic_cast<const protocol::ComplexStrategyTickerMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).strategy_id());
            checksum += bench::digest((*message).last_price().mantissa());
            checksum += bench::digest((*message).size());
            checksum += bench::digest((*message).volume());
            checksum += bench::digest((*message).high());
            checksum += bench::digest((*message).low());
            checksum += bench::digest((*message).first());
            checksum += bench::digest((*message).trade_condition());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nasdaq.IseOptions.TopComboQuoteFeed.Itch.v1.0", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
