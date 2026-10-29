// Nasdaq.NsmEquities.Qbbo.Itch.v2.1 benchmark, through the Modern iterator: every value it reads from every message of the simulated
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
#include "cpp/binary/modern/nasdaq/nsmequities/qbbo/itch/v2.1/definitions.hpp"

namespace protocol = ::nasdaq::nsmequities::qbbo::itch::v2_1;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    checksum += bench::digest(iterator.packet_header->session.get());
    checksum += bench::digest(iterator.packet_header->sequence_number.get());
    checksum += bench::digest(iterator.packet_header->message_count.get());

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.message_header->message_length.get());
        checksum += bench::digest(iterator.message_header->message_type.get());

        if (iterator.message_type == protocol::SystemEventMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SystemEventMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->time_stamp.get());
            checksum += bench::digest(message->event_code.get());
        } else if (iterator.message_type == protocol::StockDirectoryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::StockDirectoryMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->time_stamp.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->market_category.get());
            checksum += bench::digest(message->financial_status_indicator.get());
            checksum += bench::digest(message->round_lot_size.get());
            checksum += bench::digest(message->round_lots_only.get());
            checksum += bench::digest(message->issue_classification.get());
            checksum += bench::digest(message->issue_sub_type.get());
            checksum += bench::digest(message->authenticity.get());
            checksum += bench::digest(message->short_sale_threshold_indicator.get());
            checksum += bench::digest(message->ipo_flag.get());
            checksum += bench::digest(message->luld_reference_price_tier.get());
            checksum += bench::digest(message->etp_flag.get());
            checksum += bench::digest(message->etp_leverage_factor.get());
            checksum += bench::digest(message->inverse_indicator.get());
        } else if (iterator.message_type == protocol::StockTradingActionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::StockTradingActionMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->time_stamp.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->security_class.get());
            checksum += bench::digest(message->current_trading_state.get());
            checksum += bench::digest(message->reason.get());
        } else if (iterator.message_type == protocol::RegShoRestrictionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::RegShoRestrictionMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->time_stamp.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->reg_sho_action.get());
        } else if (iterator.message_type == protocol::MwcbDeclineLevelMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::MwcbDeclineLevelMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->time_stamp.get());
            checksum += bench::digest(message->level_1.integer());
            checksum += bench::digest(message->level_2.integer());
            checksum += bench::digest(message->level_3.integer());
        } else if (iterator.message_type == protocol::MwcbBreachMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::MwcbBreachMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->time_stamp.get());
            checksum += bench::digest(message->breached_level.get());
        } else if (iterator.message_type == protocol::OperationalHaltMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OperationalHaltMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->time_stamp.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->market_code.get());
            checksum += bench::digest(message->operational_halt_action.get());
        } else if (iterator.message_type == protocol::BboQuotationMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::BboQuotationMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->time_stamp.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->security_class.get());
            checksum += bench::digest(message->best_bid_price.integer());
            checksum += bench::digest(message->best_bid_size.get());
            checksum += bench::digest(message->best_offer_price.integer());
            checksum += bench::digest(message->best_offer_size.get());
        } else if (iterator.message_type == protocol::PriceImprovementMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::PriceImprovementMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking.get());
            checksum += bench::digest(message->time_stamp.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->interest_flag.get());
        } else if (iterator.message_type == protocol::IpoQuotingPeriodUpdateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::IpoQuotingPeriodUpdateMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking.get());
            checksum += bench::digest(message->time_stamp.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->ipo_quotation_release_time.get());
            checksum += bench::digest(message->ipo_quotation_release_qualifier.get());
            checksum += bench::digest(message->ipo_price.integer());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nasdaq.NsmEquities.Qbbo.Itch.v2.1", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
