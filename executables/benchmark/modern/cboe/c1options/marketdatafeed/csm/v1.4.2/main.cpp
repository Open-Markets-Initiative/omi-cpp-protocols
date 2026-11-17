// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: main.cpp
// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2 benchmark, through the Modern iterator: every value it reads from every message of the simulated
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
#include "cpp/binary/modern/cboe/c1options/marketdatafeed/csm/v1.4.2/definitions.hpp"

namespace protocol = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    checksum += bench::digest(iterator.packet_header->version.get());
    checksum += bench::digest(iterator.packet_header->packet_length.get());
    checksum += bench::digest(iterator.packet_header->sending_time.get());
    checksum += bench::digest(iterator.packet_header->message_count.get());
    checksum += bench::digest(iterator.packet_header->first_msg_seq_num.get());

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.message_header->message_length.get());
        checksum += bench::digest(iterator.message_header->template_id.get());
        checksum += bench::digest(iterator.message_header->message_type.get());
        checksum += bench::digest(iterator.message_header->msg_seq_num.get());

        if (iterator.template_id == protocol::SecurityDefinitionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SecurityDefinitionMessage::parse(iterator.message);
        } else if (iterator.template_id == protocol::CurrentMarketRefreshMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::CurrentMarketRefreshMessage::parse(iterator.message);
            checksum += bench::digest(message->class_key.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->security_trading_status.get());
            checksum += bench::digest(message->price_type.get());
            checksum += bench::digest(message->appl_seq_num.get());
            checksum += bench::digest(message->no_entries.get());
        } else if (iterator.template_id == protocol::MarketDataRefreshMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::MarketDataRefreshMessage::parse(iterator.message);
            checksum += bench::digest(message->class_key.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->security_trading_status.get());
            checksum += bench::digest(message->price_type.get());
            checksum += bench::digest(message->appl_seq_num.get());
            checksum += bench::digest(message->prev_close_px.prev_close_px_exponent.get());
            checksum += bench::digest(message->prev_close_px.prev_close_px_mantissa.get());
            checksum += bench::digest(message->trade_volume.get());
            checksum += bench::digest(message->no_entries.get());
        } else if (iterator.template_id == protocol::CurrentMarketUpdateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::CurrentMarketUpdateMessage::parse(iterator.message);
            checksum += bench::digest(message->class_key.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->security_trading_status.get());
            checksum += bench::digest(message->price_type.get());
            checksum += bench::digest(message->no_entries.get());
        } else if (iterator.template_id == protocol::RecapUpdateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::RecapUpdateMessage::parse(iterator.message);
            checksum += bench::digest(message->class_key.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->price_type.get());
            checksum += bench::digest(message->prev_close_px.prev_close_px_exponent.get());
            checksum += bench::digest(message->prev_close_px.prev_close_px_mantissa.get());
            checksum += bench::digest(message->trade_volume.get());
            checksum += bench::digest(message->no_entries.get());
        } else if (iterator.template_id == protocol::TickerMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TickerMessage::parse(iterator.message);
            checksum += bench::digest(message->class_key.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->price_type.get());
            checksum += bench::digest(message->no_entries.get());
        } else if (iterator.template_id == protocol::ExpectedOpeningPriceAndSizeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ExpectedOpeningPriceAndSizeMessage::parse(iterator.message);
            checksum += bench::digest(message->class_key.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->eop.eop_exponent.get());
            checksum += bench::digest(message->eop.eop_mantissa.get());
            checksum += bench::digest(message->eos.get());
            checksum += bench::digest(message->eop_type.get());
            checksum += bench::digest(message->legal_market.get());
        } else if (iterator.template_id == protocol::IndexValueMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::IndexValueMessage::parse(iterator.message);
        } else if (iterator.template_id == protocol::SettlementValueMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SettlementValueMessage::parse(iterator.message);
            checksum += bench::digest(message->class_key.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->price_type.get());
            checksum += bench::digest(message->no_entries.get());
        } else if (iterator.template_id == protocol::SummaryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SummaryMessage::parse(iterator.message);
            checksum += bench::digest(message->class_key.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->price_type.get());
            checksum += bench::digest(message->trade_volume.get());
            checksum += bench::digest(message->open_interest.get());
            checksum += bench::digest(message->net_chg_prev_day.net_chg_prev_day_exponent.get());
            checksum += bench::digest(message->net_chg_prev_day.net_chg_prev_day_mantissa.get());
            checksum += bench::digest(message->underlying_px.underlying_px_exponent.get());
            checksum += bench::digest(message->underlying_px.underlying_px_mantissa.get());
            checksum += bench::digest(message->no_entries.get());
        } else if (iterator.template_id == protocol::MarketDataControlMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::MarketDataControlMessage::parse(iterator.message);
            checksum += bench::digest(message->md_control_type.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Cboe.C1Options.MarketDataFeed.Csm.v1.4.2", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
