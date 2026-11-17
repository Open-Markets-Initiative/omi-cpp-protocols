// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: main.cpp
// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/miax/onyxfutures/topofmarket/mach/v1.0.b.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/miax/onyxfutures/topofmarket/mach/v1.0.b/definitions.hpp"

namespace protocol = ::miax::onyxfutures::topofmarket::mach::v1_0_b;

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
        checksum += bench::digest(iterator.mach_packet_header->packet_length.get());
        checksum += bench::digest(iterator.mach_packet_header->packet_type.get());
        checksum += bench::digest(iterator.mach_packet_header->session_number.get());

        if (iterator.packet_type == 3) {
            [[maybe_unused]] const auto* message = protocol::ApplicationMessage::parse(iterator.message);
            checksum += bench::digest(message->message_type.get());
            if (message->message_type.get() == protocol::SimpleInstrumentDefinitionMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::SimpleInstrumentDefinitionMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->timestamp.get());
                checksum += bench::digest(message_2->instrument_id.get());
                checksum += bench::digest(message_2->underlying_asset_type.get());
                checksum += bench::digest(message_2->underlying_asset.get());
                checksum += bench::digest(message_2->product_group_code.get());
                checksum += bench::digest(message_2->exchange.get());
                checksum += bench::digest(message_2->instrument_id_source.get());
                checksum += bench::digest(message_2->instrument_type.get());
                checksum += bench::digest(message_2->maturity_month_year.get());
                checksum += bench::digest(message_2->currency.get());
                checksum += bench::digest(message_2->settlement_currency.get());
                checksum += bench::digest(message_2->match_algorithm.get());
                checksum += bench::digest(message_2->minimum_size.get());
                checksum += bench::digest(message_2->maximum_size.get());
                checksum += bench::digest(message_2->tick.integer());
                checksum += bench::digest(message_2->unit_of_measure.get());
                checksum += bench::digest(message_2->unit_of_measure_quantity.get());
                checksum += bench::digest(message_2->settlement_price.integer());
                checksum += bench::digest(message_2->settlement_price_type_calc_method.get());
                checksum += bench::digest(message_2->total_volume.get());
                checksum += bench::digest(message_2->open_interest_quantity.get());
                checksum += bench::digest(message_2->high_limit_price.integer());
                checksum += bench::digest(message_2->low_limit_price.integer());
                checksum += bench::digest(message_2->trading_collar_variation_type.get());
                checksum += bench::digest(message_2->trading_collar_variation.integer());
            } else if (message->message_type.get() == protocol::ComplexInstrumentDefinitionMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::ComplexInstrumentDefinitionMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->timestamp.get());
                checksum += bench::digest(message_2->strategy_id.get());
                checksum += bench::digest(message_2->underlying_asset_type.get());
                checksum += bench::digest(message_2->underlying_asset.get());
                checksum += bench::digest(message_2->product_group_code.get());
                checksum += bench::digest(message_2->spread_type.get());
                checksum += bench::digest(message_2->exchange.get());
                checksum += bench::digest(message_2->instrument_id_source.get());
                checksum += bench::digest(message_2->instrument_type.get());
                checksum += bench::digest(message_2->currency.get());
                checksum += bench::digest(message_2->settlement_currency.get());
                checksum += bench::digest(message_2->match_algorithm.get());
                checksum += bench::digest(message_2->minimum_size.get());
                checksum += bench::digest(message_2->maximum_size.get());
                checksum += bench::digest(message_2->tick.integer());
                checksum += bench::digest(message_2->unit_of_measure.get());
                checksum += bench::digest(message_2->unit_of_measure_quantity.get());
                checksum += bench::digest(message_2->trading_collar_variation_type.get());
                checksum += bench::digest(message_2->trading_collar_variation.integer());
                checksum += bench::digest(message_2->number_of_legs.get());
            } else if (message->message_type.get() == protocol::SystemStateMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::SystemStateMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->timestamp.get());
                checksum += bench::digest(message_2->tom_version.get());
                checksum += bench::digest(message_2->session_id.get());
                checksum += bench::digest(message_2->system_status.get());
            } else if (message->message_type.get() == protocol::InstrumentTradingStatusNotificationMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::InstrumentTradingStatusNotificationMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->timestamp.get());
                checksum += bench::digest(message_2->instrument_id.get());
                checksum += bench::digest(message_2->trading_status.get());
                checksum += bench::digest(message_2->market_state.get());
            } else if (message->message_type.get() == protocol::BestBidAndOfferMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::BestBidAndOfferMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->timestamp.get());
                checksum += bench::digest(message_2->instrument_id.get());
                checksum += (static_cast<std::uint64_t>(message_2->mbb_price.integer()) != 0x0F21F494C589C0001ULL ? bench::digest(message_2->mbb_price.integer()) : std::uint64_t{0});
                checksum += bench::digest(message_2->mbb_size.get());
                checksum += (static_cast<std::uint64_t>(message_2->mbo_price.integer()) != 0x0DE0B6B3A763FFFFULL ? bench::digest(message_2->mbo_price.integer()) : std::uint64_t{0});
                checksum += bench::digest(message_2->mbo_size.get());
            } else if (message->message_type.get() == protocol::LastSaleMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::LastSaleMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->timestamp.get());
                checksum += bench::digest(message_2->instrument_id.get());
                checksum += bench::digest(message_2->trade_id.get());
                checksum += bench::digest(message_2->price.integer());
                checksum += bench::digest(message_2->size.get());
            } else if (message->message_type.get() == protocol::TradeCancelMessage::message_type) {
                [[maybe_unused]] const auto* message_2 = protocol::TradeCancelMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                checksum += bench::digest(message_2->timestamp.get());
                checksum += bench::digest(message_2->trade_date.get());
                checksum += bench::digest(message_2->instrument_id.get());
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
    return bench::run("Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
