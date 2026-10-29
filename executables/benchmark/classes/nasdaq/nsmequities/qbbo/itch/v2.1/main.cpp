// Nasdaq.NsmEquities.Qbbo.Itch.v2.1 benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/nsmequities/qbbo/itch/v2.1.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/nasdaq/nsmequities/qbbo/itch/v2.1/definitions.hpp"

namespace protocol = ::nasdaq::nsmequities::qbbo::itch::v2_1;

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
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).time_stamp());
            checksum += bench::digest((*message).event_code());
        } else if (const auto* message = dynamic_cast<const protocol::StockDirectoryMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).time_stamp());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).market_category());
            checksum += bench::digest((*message).financial_status_indicator());
            checksum += bench::digest((*message).round_lot_size());
            checksum += bench::digest((*message).round_lots_only());
            checksum += bench::digest((*message).issue_classification());
            checksum += bench::digest((*message).issue_sub_type());
            checksum += bench::digest((*message).authenticity());
            checksum += bench::digest((*message).short_sale_threshold_indicator());
            checksum += bench::digest((*message).ipo_flag());
            checksum += bench::digest((*message).luld_reference_price_tier());
            checksum += bench::digest((*message).etp_flag());
            checksum += bench::digest((*message).etp_leverage_factor());
            checksum += bench::digest((*message).inverse_indicator());
        } else if (const auto* message = dynamic_cast<const protocol::StockTradingActionMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).time_stamp());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).security_class());
            checksum += bench::digest((*message).current_trading_state());
            checksum += bench::digest((*message).reason());
        } else if (const auto* message = dynamic_cast<const protocol::RegShoRestrictionMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).time_stamp());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).reg_sho_action());
        } else if (const auto* message = dynamic_cast<const protocol::MwcbDeclineLevelMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).time_stamp());
            checksum += bench::digest((*message).level_1().mantissa());
            checksum += bench::digest((*message).level_2().mantissa());
            checksum += bench::digest((*message).level_3().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::MwcbBreachMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).time_stamp());
            checksum += bench::digest((*message).breached_level());
        } else if (const auto* message = dynamic_cast<const protocol::OperationalHaltMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).time_stamp());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).market_code());
            checksum += bench::digest((*message).operational_halt_action());
        } else if (const auto* message = dynamic_cast<const protocol::BboQuotationMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).time_stamp());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).security_class());
            checksum += bench::digest((*message).best_bid_price().mantissa());
            checksum += bench::digest((*message).best_bid_size());
            checksum += bench::digest((*message).best_offer_price().mantissa());
            checksum += bench::digest((*message).best_offer_size());
        } else if (const auto* message = dynamic_cast<const protocol::PriceImprovementMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking());
            checksum += bench::digest((*message).time_stamp());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).interest_flag());
        } else if (const auto* message = dynamic_cast<const protocol::IpoQuotingPeriodUpdateMessage*>(each.message())) {
            checksum += bench::digest((*message).tracking());
            checksum += bench::digest((*message).time_stamp());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).ipo_quotation_release_time());
            checksum += bench::digest((*message).ipo_quotation_release_qualifier());
            checksum += bench::digest((*message).ipo_price().mantissa());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nasdaq.NsmEquities.Qbbo.Itch.v2.1", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
