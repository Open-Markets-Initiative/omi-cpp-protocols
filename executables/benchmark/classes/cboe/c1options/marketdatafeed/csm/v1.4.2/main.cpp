// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2 benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/cboe/c1options/marketdatafeed/csm/v1.4.2.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/cboe/c1options/marketdatafeed/csm/v1.4.2/definitions.hpp"

namespace protocol = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

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

    checksum += bench::digest(packet.packet_header().version());
    checksum += bench::digest(packet.packet_header().packet_length());
    checksum += bench::digest(packet.packet_header().sending_time());
    checksum += bench::digest(packet.packet_header().message_count());
    checksum += bench::digest(packet.packet_header().first_msg_seq_num());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_header().message_length());
        checksum += bench::digest(each.message_header().template_id());
        checksum += bench::digest(each.message_header().message_type());
        checksum += bench::digest(each.message_header().msg_seq_num());

        if (dynamic_cast<const protocol::SecurityDefinitionMessage*>(each.message()) != nullptr) {
        } else if (const auto* message = dynamic_cast<const protocol::CurrentMarketRefreshMessage*>(each.message())) {
            checksum += bench::digest((*message).class_key());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).security_trading_status());
            checksum += bench::digest((*message).price_type());
            checksum += bench::digest((*message).appl_seq_num());
            checksum += bench::digest((*message).no_entries());
        } else if (const auto* message = dynamic_cast<const protocol::MarketDataRefreshMessage*>(each.message())) {
            checksum += bench::digest((*message).class_key());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).security_trading_status());
            checksum += bench::digest((*message).price_type());
            checksum += bench::digest((*message).appl_seq_num());
            checksum += bench::digest((*message).prev_close_px().prev_close_px_exponent());
            checksum += bench::digest((*message).prev_close_px().prev_close_px_mantissa());
            checksum += bench::digest((*message).trade_volume());
            checksum += bench::digest((*message).no_entries());
        } else if (const auto* message = dynamic_cast<const protocol::CurrentMarketUpdateMessage*>(each.message())) {
            checksum += bench::digest((*message).class_key());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).security_trading_status());
            checksum += bench::digest((*message).price_type());
            checksum += bench::digest((*message).no_entries());
        } else if (const auto* message = dynamic_cast<const protocol::RecapUpdateMessage*>(each.message())) {
            checksum += bench::digest((*message).class_key());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).price_type());
            checksum += bench::digest((*message).prev_close_px().prev_close_px_exponent());
            checksum += bench::digest((*message).prev_close_px().prev_close_px_mantissa());
            checksum += bench::digest((*message).trade_volume());
            checksum += bench::digest((*message).no_entries());
        } else if (const auto* message = dynamic_cast<const protocol::TickerMessage*>(each.message())) {
            checksum += bench::digest((*message).class_key());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).price_type());
            checksum += bench::digest((*message).no_entries());
        } else if (const auto* message = dynamic_cast<const protocol::ExpectedOpeningPriceAndSizeMessage*>(each.message())) {
            checksum += bench::digest((*message).class_key());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).eop().eop_exponent());
            checksum += bench::digest((*message).eop().eop_mantissa());
            checksum += bench::digest((*message).eos());
            checksum += bench::digest((*message).eop_type());
            checksum += bench::digest((*message).legal_market());
        } else if (dynamic_cast<const protocol::IndexValueMessage*>(each.message()) != nullptr) {
        } else if (const auto* message = dynamic_cast<const protocol::SettlementValueMessage*>(each.message())) {
            checksum += bench::digest((*message).class_key());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).price_type());
            checksum += bench::digest((*message).no_entries());
        } else if (const auto* message = dynamic_cast<const protocol::SummaryMessage*>(each.message())) {
            checksum += bench::digest((*message).class_key());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).price_type());
            checksum += bench::digest((*message).trade_volume());
            checksum += bench::digest((*message).open_interest());
            checksum += bench::digest((*message).net_chg_prev_day().net_chg_prev_day_exponent());
            checksum += bench::digest((*message).net_chg_prev_day().net_chg_prev_day_mantissa());
            checksum += bench::digest((*message).underlying_px().underlying_px_exponent());
            checksum += bench::digest((*message).underlying_px().underlying_px_mantissa());
            checksum += bench::digest((*message).no_entries());
        } else if (const auto* message = dynamic_cast<const protocol::MarketDataControlMessage*>(each.message())) {
            checksum += bench::digest((*message).md_control_type());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Cboe.C1Options.MarketDataFeed.Csm.v1.4.2", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
