// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: main.cpp
// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/tmx/tsx/quantumfeedlevel2/xmt/v3.6.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/tmx/tsx/quantumfeedlevel2/xmt/v3.6/definitions.hpp"

namespace protocol = ::tmx::tsx::quantumfeedlevel2::xmt::v3_6;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        checksum += bench::digest(packet.frame_header().start_of_frame());
        checksum += bench::digest(packet.frame_header().protocol_name());
        checksum += bench::digest(packet.frame_header().protocol_version());
        checksum += bench::digest(packet.frame_header().message_length());
        checksum += bench::digest(packet.frame_header().session_id());
        checksum += bench::digest(packet.frame_header().ack_required_poss_dup());
        checksum += bench::digest(packet.frame_header().num_body());
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

    void on(const protocol::SymbolStatusMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol());
        checksum += (message.stock_group().has_value() ? bench::digest((*message.stock_group())) : std::uint64_t{0});
        checksum += bench::digest(message.cusip());
        checksum += (message.board_lot().has_value() ? bench::digest((*message.board_lot())) : std::uint64_t{0});
        checksum += bench::digest(message.currency());
        checksum += (message.face_value().has_value() ? bench::digest((*message.face_value()).mantissa()) : std::uint64_t{0});
        checksum += (message.last_sale().has_value() ? bench::digest((*message.last_sale()).mantissa()) : std::uint64_t{0});
        checksum += bench::digest(message.listing_market());
        checksum += bench::digest(message.product_type());
        checksum += (message.buy_maximum_quantity().has_value() ? bench::digest((*message.buy_maximum_quantity())) : std::uint64_t{0});
        checksum += (message.buy_minimum_quantity().has_value() ? bench::digest((*message.buy_minimum_quantity())) : std::uint64_t{0});
        checksum += (message.sell_maximum_quantity().has_value() ? bench::digest((*message.sell_maximum_quantity())) : std::uint64_t{0});
        checksum += (message.sell_minimum_quantity().has_value() ? bench::digest((*message.sell_minimum_quantity())) : std::uint64_t{0});
        checksum += bench::digest(message.stock_state());
        checksum += bench::digest(message.test_symbol());
        checksum += bench::digest(message.moc_eligible());
    }

    void on(const protocol::OrderBookMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol());
        checksum += (message.broker_number().has_value() ? bench::digest((*message.broker_number())) : std::uint64_t{0});
        checksum += bench::digest(message.order_side());
        checksum += (message.order_id().has_value() ? bench::digest((*message.order_id())) : std::uint64_t{0});
        checksum += bench::digest(message.order_price().mantissa());
        checksum += (message.volume().has_value() ? bench::digest((*message.volume())) : std::uint64_t{0});
        checksum += (message.priority_time_stamp().has_value() ? bench::digest((*message.priority_time_stamp())) : std::uint64_t{0});
    }

    void on(const protocol::OrderBookTermsMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol());
        checksum += (message.broker_number().has_value() ? bench::digest((*message.broker_number())) : std::uint64_t{0});
        checksum += bench::digest(message.order_side());
        checksum += (message.order_id().has_value() ? bench::digest((*message.order_id())) : std::uint64_t{0});
        checksum += (message.price().has_value() ? bench::digest((*message.price()).mantissa()) : std::uint64_t{0});
        checksum += (message.volume().has_value() ? bench::digest((*message.volume())) : std::uint64_t{0});
        checksum += bench::digest(message.non_resident());
        checksum += bench::digest(message.settlement_terms());
        checksum += (message.settlement_date().has_value() ? bench::digest((*message.settlement_date())) : std::uint64_t{0});
        checksum += (message.priority_time_stamp().has_value() ? bench::digest((*message.priority_time_stamp())) : std::uint64_t{0});
    }

    void on(const protocol::AssignCopOrdersMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol());
        checksum += (message.calculated_opening_price().has_value() ? bench::digest((*message.calculated_opening_price()).mantissa()) : std::uint64_t{0});
        checksum += bench::digest(message.order_side());
        for (std::size_t cop_order_index = 0; const auto& cop_order_entry : message.cop_order()) {
            checksum += cop_order_index++;
            checksum += (cop_order_entry.broker_number().has_value() ? bench::digest((*cop_order_entry.broker_number())) : std::uint64_t{0});
            checksum += (cop_order_entry.order_id().has_value() ? bench::digest((*cop_order_entry.order_id())) : std::uint64_t{0});
        }
        checksum += (message.trading_system_time_stamp().has_value() ? bench::digest((*message.trading_system_time_stamp())) : std::uint64_t{0});
    }

    void on(const protocol::AssignCopNoOrdersMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol());
        checksum += (message.calculated_opening_price().has_value() ? bench::digest((*message.calculated_opening_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.trading_system_time_stamp().has_value() ? bench::digest((*message.trading_system_time_stamp())) : std::uint64_t{0});
    }

    void on(const protocol::AssignLimitMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol());
        checksum += (message.calculated_opening_price().has_value() ? bench::digest((*message.calculated_opening_price()).mantissa()) : std::uint64_t{0});
        checksum += bench::digest(message.order_side());
        for (std::size_t cop_limit_index = 0; const auto& cop_limit_entry : message.cop_limit()) {
            checksum += cop_limit_index++;
            checksum += (cop_limit_entry.broker_number().has_value() ? bench::digest((*cop_limit_entry.broker_number())) : std::uint64_t{0});
            checksum += (cop_limit_entry.order_id().has_value() ? bench::digest((*cop_limit_entry.order_id())) : std::uint64_t{0});
            checksum += (cop_limit_entry.price().has_value() ? bench::digest((*cop_limit_entry.price()).mantissa()) : std::uint64_t{0});
        }
        checksum += (message.trading_system_time_stamp().has_value() ? bench::digest((*message.trading_system_time_stamp())) : std::uint64_t{0});
    }

    void on(const protocol::MarketStateUpdateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.market_state());
        checksum += (message.stock_group().has_value() ? bench::digest((*message.stock_group())) : std::uint64_t{0});
        checksum += (message.trading_system_time_stamp().has_value() ? bench::digest((*message.trading_system_time_stamp())) : std::uint64_t{0});
    }

    void on(const protocol::MocImbalanceMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.imbalance_side());
        checksum += (message.imbalance_volume().has_value() ? bench::digest((*message.imbalance_volume())) : std::uint64_t{0});
        checksum += (message.trading_system_time_stamp().has_value() ? bench::digest((*message.trading_system_time_stamp())) : std::uint64_t{0});
        checksum += (message.imbalance_reference_price().has_value() ? bench::digest((*message.imbalance_reference_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.paired_volume().has_value() ? bench::digest((*message.paired_volume())) : std::uint64_t{0});
        checksum += (message.market_order_imbalance_volume().has_value() ? bench::digest((*message.market_order_imbalance_volume())) : std::uint64_t{0});
        checksum += bench::digest(message.market_order_imbalance_side());
        checksum += (message.near_indicative_closing_price().has_value() ? bench::digest((*message.near_indicative_closing_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.far_indicative_closing_price().has_value() ? bench::digest((*message.far_indicative_closing_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.price_variation().has_value() ? bench::digest((*message.price_variation()).mantissa()) : std::uint64_t{0});
    }

    void on(const protocol::OrderBookedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol());
        checksum += (message.broker_number().has_value() ? bench::digest((*message.broker_number())) : std::uint64_t{0});
        checksum += bench::digest(message.order_side());
        checksum += (message.order_id().has_value() ? bench::digest((*message.order_id())) : std::uint64_t{0});
        checksum += bench::digest(message.order_price().mantissa());
        checksum += (message.volume().has_value() ? bench::digest((*message.volume())) : std::uint64_t{0});
        checksum += (message.priority_time_stamp().has_value() ? bench::digest((*message.priority_time_stamp())) : std::uint64_t{0});
        checksum += (message.trading_system_time_stamp().has_value() ? bench::digest((*message.trading_system_time_stamp())) : std::uint64_t{0});
    }

    void on(const protocol::OrderBookedTermsMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol());
        checksum += (message.broker_number().has_value() ? bench::digest((*message.broker_number())) : std::uint64_t{0});
        checksum += bench::digest(message.order_side());
        checksum += (message.order_id().has_value() ? bench::digest((*message.order_id())) : std::uint64_t{0});
        checksum += (message.price().has_value() ? bench::digest((*message.price()).mantissa()) : std::uint64_t{0});
        checksum += (message.volume().has_value() ? bench::digest((*message.volume())) : std::uint64_t{0});
        checksum += bench::digest(message.non_resident());
        checksum += bench::digest(message.settlement_terms());
        checksum += (message.settlement_date().has_value() ? bench::digest((*message.settlement_date())) : std::uint64_t{0});
        checksum += (message.priority_time_stamp().has_value() ? bench::digest((*message.priority_time_stamp())) : std::uint64_t{0});
        checksum += (message.trading_system_time_stamp().has_value() ? bench::digest((*message.trading_system_time_stamp())) : std::uint64_t{0});
    }

    void on(const protocol::OrderCancelledMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol());
        checksum += (message.broker_number().has_value() ? bench::digest((*message.broker_number())) : std::uint64_t{0});
        checksum += bench::digest(message.order_side());
        checksum += (message.order_id().has_value() ? bench::digest((*message.order_id())) : std::uint64_t{0});
        checksum += (message.trading_system_time_stamp().has_value() ? bench::digest((*message.trading_system_time_stamp())) : std::uint64_t{0});
    }

    void on(const protocol::OrderCancelledTermsMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol());
        checksum += (message.broker_number().has_value() ? bench::digest((*message.broker_number())) : std::uint64_t{0});
        checksum += bench::digest(message.order_side());
        checksum += (message.order_id().has_value() ? bench::digest((*message.order_id())) : std::uint64_t{0});
        checksum += (message.trading_system_time_stamp().has_value() ? bench::digest((*message.trading_system_time_stamp())) : std::uint64_t{0});
    }

    void on(const protocol::OrderPriceTimeAssignedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol());
        checksum += (message.broker_number().has_value() ? bench::digest((*message.broker_number())) : std::uint64_t{0});
        checksum += bench::digest(message.order_side());
        checksum += (message.order_id().has_value() ? bench::digest((*message.order_id())) : std::uint64_t{0});
        checksum += (message.price().has_value() ? bench::digest((*message.price()).mantissa()) : std::uint64_t{0});
        checksum += (message.volume().has_value() ? bench::digest((*message.volume())) : std::uint64_t{0});
        checksum += (message.priority_time_stamp().has_value() ? bench::digest((*message.priority_time_stamp())) : std::uint64_t{0});
        checksum += (message.trading_system_time_stamp().has_value() ? bench::digest((*message.trading_system_time_stamp())) : std::uint64_t{0});
    }

    void on(const protocol::OrderPriceTimeAssignedTermsMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol());
        checksum += (message.broker_number().has_value() ? bench::digest((*message.broker_number())) : std::uint64_t{0});
        checksum += bench::digest(message.order_side());
        checksum += (message.order_id().has_value() ? bench::digest((*message.order_id())) : std::uint64_t{0});
        checksum += (message.price().has_value() ? bench::digest((*message.price()).mantissa()) : std::uint64_t{0});
        checksum += (message.volume().has_value() ? bench::digest((*message.volume())) : std::uint64_t{0});
        checksum += (message.priority_time_stamp().has_value() ? bench::digest((*message.priority_time_stamp())) : std::uint64_t{0});
        checksum += (message.trading_system_time_stamp().has_value() ? bench::digest((*message.trading_system_time_stamp())) : std::uint64_t{0});
    }

    void on(const protocol::StockStatusMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.comment());
        checksum += bench::digest(message.stock_state());
        checksum += (message.trading_system_time_stamp().has_value() ? bench::digest((*message.trading_system_time_stamp())) : std::uint64_t{0});
        checksum += bench::digest(message.listing_market());
        checksum += bench::digest(message.product_type());
    }

    void on(const protocol::TradeReportMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol());
        checksum += (message.trade_number().has_value() ? bench::digest((*message.trade_number())) : std::uint64_t{0});
        checksum += (message.price().has_value() ? bench::digest((*message.price()).mantissa()) : std::uint64_t{0});
        checksum += (message.volume().has_value() ? bench::digest((*message.volume())) : std::uint64_t{0});
        checksum += (message.buy_broker_number().has_value() ? bench::digest((*message.buy_broker_number())) : std::uint64_t{0});
        checksum += (message.buy_order_id().has_value() ? bench::digest((*message.buy_order_id())) : std::uint64_t{0});
        checksum += (message.buy_display_volume().has_value() ? bench::digest((*message.buy_display_volume())) : std::uint64_t{0});
        checksum += (message.sell_broker_number().has_value() ? bench::digest((*message.sell_broker_number())) : std::uint64_t{0});
        checksum += (message.sell_order_id().has_value() ? bench::digest((*message.sell_order_id())) : std::uint64_t{0});
        checksum += (message.sell_display_volume().has_value() ? bench::digest((*message.sell_display_volume())) : std::uint64_t{0});
        checksum += bench::digest(message.bypass());
        checksum += (message.trade_time_stamp().has_value() ? bench::digest((*message.trade_time_stamp())) : std::uint64_t{0});
        checksum += bench::digest(message.cross_type());
        checksum += (message.trading_system_time_stamp().has_value() ? bench::digest((*message.trading_system_time_stamp())) : std::uint64_t{0});
        checksum += bench::digest(message.listing_market());
        checksum += bench::digest(message.product_type());
        checksum += (message.trade_date().has_value() ? bench::digest((*message.trade_date())) : std::uint64_t{0});
        checksum += bench::digest(message.is_mid_only());
        checksum += bench::digest(message.is_dark());
        checksum += bench::digest(message.is_conditional());
    }

    void on(const protocol::TradeReportTermsMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol());
        checksum += (message.trade_number().has_value() ? bench::digest((*message.trade_number())) : std::uint64_t{0});
        checksum += (message.price().has_value() ? bench::digest((*message.price()).mantissa()) : std::uint64_t{0});
        checksum += (message.volume().has_value() ? bench::digest((*message.volume())) : std::uint64_t{0});
        checksum += (message.buy_broker_number().has_value() ? bench::digest((*message.buy_broker_number())) : std::uint64_t{0});
        checksum += (message.buy_order_id().has_value() ? bench::digest((*message.buy_order_id())) : std::uint64_t{0});
        checksum += (message.buy_display_volume().has_value() ? bench::digest((*message.buy_display_volume())) : std::uint64_t{0});
        checksum += (message.sell_broker_number().has_value() ? bench::digest((*message.sell_broker_number())) : std::uint64_t{0});
        checksum += (message.sell_order_id().has_value() ? bench::digest((*message.sell_order_id())) : std::uint64_t{0});
        checksum += (message.sell_display_volume().has_value() ? bench::digest((*message.sell_display_volume())) : std::uint64_t{0});
        checksum += (message.trade_time_stamp().has_value() ? bench::digest((*message.trade_time_stamp())) : std::uint64_t{0});
        checksum += bench::digest(message.non_resident());
        checksum += bench::digest(message.settlement_terms());
        checksum += (message.settlement_date().has_value() ? bench::digest((*message.settlement_date())) : std::uint64_t{0});
        checksum += bench::digest(message.cross_type());
        checksum += (message.trading_system_time_stamp().has_value() ? bench::digest((*message.trading_system_time_stamp())) : std::uint64_t{0});
    }

    void on(const protocol::TradeCancelledMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol());
        checksum += (message.trade_number().has_value() ? bench::digest((*message.trade_number())) : std::uint64_t{0});
        checksum += (message.trading_system_time_stamp().has_value() ? bench::digest((*message.trading_system_time_stamp())) : std::uint64_t{0});
        checksum += bench::digest(message.listing_market());
        checksum += bench::digest(message.product_type());
        checksum += (message.trade_date().has_value() ? bench::digest((*message.trade_date())) : std::uint64_t{0});
    }

    void on(const protocol::TradeCancelledTermsMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol());
        checksum += (message.trade_number().has_value() ? bench::digest((*message.trade_number())) : std::uint64_t{0});
        checksum += (message.trading_system_time_stamp().has_value() ? bench::digest((*message.trading_system_time_stamp())) : std::uint64_t{0});
    }

    void on(const protocol::TradeCorrectionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol());
        checksum += (message.trade_number().has_value() ? bench::digest((*message.trade_number())) : std::uint64_t{0});
        checksum += (message.price().has_value() ? bench::digest((*message.price()).mantissa()) : std::uint64_t{0});
        checksum += (message.volume().has_value() ? bench::digest((*message.volume())) : std::uint64_t{0});
        checksum += (message.buy_broker_number().has_value() ? bench::digest((*message.buy_broker_number())) : std::uint64_t{0});
        checksum += (message.sell_broker_number().has_value() ? bench::digest((*message.sell_broker_number())) : std::uint64_t{0});
        checksum += bench::digest(message.initiated_by());
        checksum += (message.orig_trade_number().has_value() ? bench::digest((*message.orig_trade_number())) : std::uint64_t{0});
        checksum += bench::digest(message.bypass());
        checksum += (message.trade_time_stamp().has_value() ? bench::digest((*message.trade_time_stamp())) : std::uint64_t{0});
        checksum += bench::digest(message.cross_type());
        checksum += (message.trading_system_time_stamp().has_value() ? bench::digest((*message.trading_system_time_stamp())) : std::uint64_t{0});
        checksum += bench::digest(message.listing_market());
        checksum += bench::digest(message.product_type());
        checksum += (message.trade_date().has_value() ? bench::digest((*message.trade_date())) : std::uint64_t{0});
        checksum += bench::digest(message.is_mid_only());
        checksum += bench::digest(message.is_dark());
        checksum += bench::digest(message.is_conditional());
    }

    void on(const protocol::TradeCorrectionTermsMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol());
        checksum += (message.trade_number().has_value() ? bench::digest((*message.trade_number())) : std::uint64_t{0});
        checksum += (message.price().has_value() ? bench::digest((*message.price()).mantissa()) : std::uint64_t{0});
        checksum += (message.volume().has_value() ? bench::digest((*message.volume())) : std::uint64_t{0});
        checksum += (message.buy_broker_number().has_value() ? bench::digest((*message.buy_broker_number())) : std::uint64_t{0});
        checksum += (message.sell_broker_number().has_value() ? bench::digest((*message.sell_broker_number())) : std::uint64_t{0});
        checksum += bench::digest(message.initiated_by());
        checksum += (message.orig_trade_number().has_value() ? bench::digest((*message.orig_trade_number())) : std::uint64_t{0});
        checksum += (message.trade_time_stamp().has_value() ? bench::digest((*message.trade_time_stamp())) : std::uint64_t{0});
        checksum += bench::digest(message.non_resident());
        checksum += bench::digest(message.settlement_terms());
        checksum += (message.settlement_date().has_value() ? bench::digest((*message.settlement_date())) : std::uint64_t{0});
        checksum += bench::digest(message.cross_type());
        checksum += (message.trading_system_time_stamp().has_value() ? bench::digest((*message.trading_system_time_stamp())) : std::uint64_t{0});
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
    return bench::run("Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
