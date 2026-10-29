// Nasdaq.NsmEquities.TotalView.Itch.v5.0.2026 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/nsmequities/totalview/itch/v5.0.2026.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <span>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "executables/benchmark/Benchmark.hpp"
#include "cpp/binary/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/definitions.hpp"

namespace protocol = ::nasdaq::nsmequities::totalview::itch::v5_0_2026;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        checksum += bench::digest(packet.packet_header().session());
        checksum += bench::digest(packet.packet_header().sequence_number());
        checksum += bench::digest(packet.packet_header().message_count());
    }

    // a message this test prints no values of, or a code no message answers to, still takes its entry
    template <typename Message>
    void on(const Message&) {
        ++index;
    }

    template <typename Code>
    void on_unknown(Code, std::span<const std::byte>) {
        ++index;
    }

    void on(const protocol::PayloadSystemEventMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.event_code());
    }

    void on(const protocol::PayloadStockDirectoryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.market_category());
        checksum += bench::digest(message.financial_status_indicator());
        checksum += bench::digest(message.round_lot_size());
        checksum += bench::digest(message.round_lots_only());
        checksum += bench::digest(message.issue_classification());
        checksum += bench::digest(message.issue_sub_type());
        checksum += bench::digest(message.authenticity());
        checksum += bench::digest(message.short_sale_threshold_indicator());
        checksum += bench::digest(message.ipo_flag());
        checksum += bench::digest(message.luld_reference_price_tier());
        checksum += bench::digest(message.etp_flag());
        checksum += bench::digest(message.etp_leverage_factor());
        checksum += bench::digest(message.inverse_indicator());
    }

    void on(const protocol::PayloadStockTradingActionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.trading_state());
        checksum += bench::digest(message.reserved());
        checksum += bench::digest(message.reason_code());
    }

    void on(const protocol::PayloadRegShoShortSalePriceTestRestrictedIndicatorMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.locate_code());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.reg_sho_action());
    }

    void on(const protocol::PayloadMarketParticipantPositionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.mpid());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.primary_market_maker());
        checksum += bench::digest(message.market_maker_mode());
        checksum += bench::digest(message.market_participant_state());
    }

    void on(const protocol::PayloadMwcbDeclineLevelMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.level_1().mantissa());
        checksum += bench::digest(message.level_2().mantissa());
        checksum += bench::digest(message.level_3().mantissa());
    }

    void on(const protocol::PayloadMwcbStatusLevelMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.breached_level());
    }

    void on(const protocol::PayloadIpoQuotingPeriodUpdate& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.ipo_quotation_release_time());
        checksum += bench::digest(message.ipo_quotation_release_qualifier());
        checksum += bench::digest(message.ipo_price().mantissa());
    }

    void on(const protocol::PayloadLuldAuctionCollarMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.auction_collar_reference_price().mantissa());
        checksum += bench::digest(message.upper_auction_collar_price().mantissa());
        checksum += bench::digest(message.lower_auction_collar_price().mantissa());
        checksum += bench::digest(message.auction_collar_extension());
    }

    void on(const protocol::PayloadOperationalHaltMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.market_code());
        checksum += bench::digest(message.operational_halt_action());
    }

    void on(const protocol::PayloadAddOrderNoMpidAttributionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.order_reference_number());
        checksum += bench::digest(message.buy_sell_indicator());
        checksum += bench::digest(message.shares());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.price().mantissa());
    }

    void on(const protocol::PayloadAddOrderWithMpidAttributionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.order_reference_number());
        checksum += bench::digest(message.buy_sell_indicator());
        checksum += bench::digest(message.shares());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.attribution());
    }

    void on(const protocol::PayloadOrderExecutedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.order_reference_number());
        checksum += bench::digest(message.executed_shares());
        checksum += bench::digest(message.match_number());
    }

    void on(const protocol::PayloadOrderExecutedWithPriceMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.order_reference_number());
        checksum += bench::digest(message.executed_shares());
        checksum += bench::digest(message.match_number());
        checksum += bench::digest(message.printable());
        checksum += bench::digest(message.execution_price().mantissa());
    }

    void on(const protocol::PayloadOrderCancelMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.order_reference_number());
        checksum += bench::digest(message.canceled_shares());
    }

    void on(const protocol::PayloadOrderDeleteMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.order_reference_number());
    }

    void on(const protocol::PayloadOrderReplaceMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.original_order_reference_number());
        checksum += bench::digest(message.new_order_reference_number());
        checksum += bench::digest(message.shares());
        checksum += bench::digest(message.price().mantissa());
    }

    void on(const protocol::PayloadNonCrossTradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.order_reference_number());
        checksum += bench::digest(message.buy_sell_indicator());
        checksum += bench::digest(message.shares());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.match_number());
    }

    void on(const protocol::PayloadCrossTradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.cross_shares());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.cross_price().mantissa());
        checksum += bench::digest(message.match_number());
        checksum += bench::digest(message.cross_type());
    }

    void on(const protocol::PayloadBrokenTradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.match_number());
    }

    void on(const protocol::PayloadNetOrderImbalanceIndicatorMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.paired_shares());
        checksum += bench::digest(message.imbalance_shares());
        checksum += bench::digest(message.imbalance_direction());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.far_price().mantissa());
        checksum += bench::digest(message.near_price().mantissa());
        checksum += bench::digest(message.current_reference_price().mantissa());
        checksum += bench::digest(message.cross_type());
        checksum += bench::digest(message.price_variation_indicator());
    }

    void on(const protocol::PayloadRetailPriceImprovementIndicatorMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.interest_flag());
    }

    void on(const protocol::PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.open_eligibility_status());
        checksum += bench::digest(message.minimum_allowable_price().mantissa());
        checksum += bench::digest(message.maximum_allowable_price().mantissa());
        checksum += bench::digest(message.near_execution_price().mantissa());
        checksum += bench::digest(message.near_execution_time());
        checksum += bench::digest(message.lower_price_range_collar().mantissa());
        checksum += bench::digest(message.upper_price_range_collar().mantissa());
    }
};

// The values the Flyweight reader reads from one datagram, folded into a checksum. A datagram it cannot
// read is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::PacketReader::read(std::span<const std::byte>(frame.payload, frame.payload_len), reader);
    } catch (const protocol::DecodeError& error) {
        throw;
    }

    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nasdaq.NsmEquities.TotalView.Itch.v5.0.2026", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
