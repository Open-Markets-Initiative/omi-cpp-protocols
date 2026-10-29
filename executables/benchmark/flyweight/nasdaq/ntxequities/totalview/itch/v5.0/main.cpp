// Nasdaq.NtxEquities.TotalView.Itch.v5.0 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/ntxequities/totalview/itch/v5.0.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/nasdaq/ntxequities/totalview/itch/v5.0/definitions.hpp"

namespace protocol = ::nasdaq::ntxequities::totalview::itch::v5_0;

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

    void on(const protocol::SystemEventMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.event_code());
    }

    void on(const protocol::StockDirectoryMessage& message) {
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

    void on(const protocol::StockTradingActionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.trading_state());
        checksum += bench::digest(message.reserved());
        checksum += bench::digest(message.trading_action_reason());
    }

    void on(const protocol::RegShoShortSalePriceTestRestrictedIndicatorMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.locate_code());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.reg_sho_action());
    }

    void on(const protocol::MarketParticipantPositionMessage& message) {
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

    void on(const protocol::MwcbDeclineLevelMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.level_1().mantissa());
        checksum += bench::digest(message.level_2().mantissa());
        checksum += bench::digest(message.level_3().mantissa());
    }

    void on(const protocol::MwcbStatusMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.breached_level());
    }

    void on(const protocol::LuldAuctionCollarMessage& message) {
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

    void on(const protocol::OperationalHaltMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.market_code());
        checksum += bench::digest(message.operational_halt_action());
    }

    void on(const protocol::AddOrderNoMpidAttributionMessage& message) {
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

    void on(const protocol::AddOrderMpidAttributionMessage& message) {
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

    void on(const protocol::OrderExecutedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.order_reference_number());
        checksum += bench::digest(message.executed_shares());
        checksum += bench::digest(message.match_number());
    }

    void on(const protocol::OrderExecutedWithPriceMessage& message) {
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

    void on(const protocol::OrderCancelMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.order_reference_number());
        checksum += bench::digest(message.cancelled_shares());
    }

    void on(const protocol::OrderDeleteMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.order_reference_number());
    }

    void on(const protocol::OrderReplaceMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.original_order_reference_number());
        checksum += bench::digest(message.new_order_reference_number());
        checksum += bench::digest(message.shares());
        checksum += bench::digest(message.price().mantissa());
    }

    void on(const protocol::NonCrossTradeMessage& message) {
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

    void on(const protocol::CrossTradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.shares_long());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.cross_price().mantissa());
        checksum += bench::digest(message.match_number());
        checksum += bench::digest(message.cross_type());
    }

    void on(const protocol::BrokenTradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.match_number());
    }

    void on(const protocol::NetOrderImbalanceIndicatorMessage& message) {
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

    void on(const protocol::RetailInterestMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock_locate());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.interest_flag());
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
    return bench::run("Nasdaq.NtxEquities.TotalView.Itch.v5.0", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
