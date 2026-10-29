// Asx.AsxDerivatives.Ntp.Itch.v1.05 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/asx/asxderivatives/ntp/itch/v1.05.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/asx/asxderivatives/ntp/itch/v1.05/definitions.hpp"

namespace protocol = ::asx::asxderivatives::ntp::itch::v1_05;

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

    void on(const protocol::SecondsMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.second());
    }

    void on(const protocol::EndOfBusinessTradeDateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.event_code());
    }

    void on(const protocol::FutureSymbolDirectoryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.tradeable_instrument_id());
        checksum += bench::digest(message.symbol_name());
        checksum += bench::digest(message.long_name());
        checksum += bench::digest(message.isin());
        checksum += bench::digest(message.exchange());
        checksum += bench::digest(message.instrument());
        checksum += bench::digest(message.cfi_code());
        checksum += bench::digest(message.expiry_year());
        checksum += bench::digest(message.expiry_month());
        checksum += bench::digest(message.price_display_decimals());
        checksum += bench::digest(message.price_fractional_denominator());
        checksum += bench::digest(message.price_minimum_tick());
        checksum += bench::digest(message.last_trading_date());
        checksum += bench::digest(message.prior_day_settlement().mantissa());
        checksum += bench::digest(message.currency());
        checksum += bench::digest(message.lot_size_or_face_value());
        checksum += bench::digest(message.maturity_value());
        checksum += bench::digest(message.coupon_rate());
        checksum += bench::digest(message.payments_per_year());
        checksum += bench::digest(message.block_lot_size());
        checksum += bench::digest(message.expiry_date());
    }

    void on(const protocol::OptionsSymbolDirectoryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.tradeable_instrument_id());
        checksum += bench::digest(message.symbol_name());
        checksum += bench::digest(message.long_name());
        checksum += bench::digest(message.isin());
        checksum += bench::digest(message.exchange());
        checksum += bench::digest(message.instrument());
        checksum += bench::digest(message.cfi_code());
        checksum += bench::digest(message.expiry_year());
        checksum += bench::digest(message.expiry_month());
        checksum += bench::digest(message.option_type());
        checksum += bench::digest(message.strike().mantissa());
        checksum += bench::digest(message.underlying_tradeable_instrument_id());
        checksum += bench::digest(message.price_display_decimals());
        checksum += bench::digest(message.price_fractional_denominator());
        checksum += bench::digest(message.price_minimum_tick());
        checksum += bench::digest(message.strike_price_decimal_position());
        checksum += bench::digest(message.strike_price_fractional_denominator());
        checksum += bench::digest(message.strike_price_minimum_tick());
        checksum += bench::digest(message.last_trading_date());
        checksum += bench::digest(message.prior_day_settlement().mantissa());
        checksum += bench::digest(message.volatility());
        checksum += bench::digest(message.currency());
        checksum += bench::digest(message.lot_size_or_face_value());
        checksum += bench::digest(message.maturity_value());
        checksum += bench::digest(message.coupon_rate());
        checksum += bench::digest(message.payments_per_year());
        checksum += bench::digest(message.block_lot_size());
        checksum += bench::digest(message.expiry_date());
        checksum += bench::digest(message.basis_of_quotation());
    }

    void on(const protocol::CombinationSymbolDirectoryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.tradeable_instrument_id());
        checksum += bench::digest(message.symbol_name());
        checksum += bench::digest(message.long_name());
        checksum += bench::digest(message.cfi_code());
        checksum += bench::digest(message.price_method());
        checksum += bench::digest(message.price_display_decimals());
        checksum += bench::digest(message.price_fractional_denominator());
        checksum += bench::digest(message.price_minimum_tick());
        checksum += bench::digest(message.legs());
    }

    void on(const protocol::BundlesSymbolDirectory& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.tradeable_instrument_id());
        checksum += bench::digest(message.symbol_name());
        checksum += bench::digest(message.long_name());
        checksum += bench::digest(message.cfi_code());
        checksum += bench::digest(message.price_method());
        checksum += bench::digest(message.price_display_decimals());
        checksum += bench::digest(message.price_fractional_denominator());
        checksum += bench::digest(message.price_minimum_tick());
        checksum += bench::digest(message.legs());
    }

    void on(const protocol::OrderBookStateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.tradeable_instrument_id());
        checksum += bench::digest(message.session_state());
    }

    void on(const protocol::AddOrderMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.tradeable_instrument_id());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.order_book_priority());
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.price().mantissa());
    }

    void on(const protocol::OrderVolumeCancelledMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.tradeable_instrument_id());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.quantity());
    }

    void on(const protocol::OrderDeletedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.tradeable_instrument_id());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.order_id());
    }

    void on(const protocol::OrderExecutedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.tradeable_instrument_id());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.quantity_remaining());
        checksum += bench::digest(message.trade_type());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.executed_quantity());
        checksum += bench::digest(message.trade_price().mantissa());
        checksum += bench::digest(message.combination_trade_id());
        checksum += bench::digest(message.counter_party_id());
    }

    void on(const protocol::AuctionOrderExecutedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.tradeable_instrument_id());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.quantity_remaining());
        checksum += bench::digest(message.trade_type());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.executed_quantity());
        checksum += bench::digest(message.trade_price().mantissa());
        checksum += bench::digest(message.opposite_order_id());
    }

    void on(const protocol::CombinationOrderExecutedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.tradeable_instrument_id());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.quantity_remaining());
        checksum += bench::digest(message.trade_type());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.executed_quantity());
        checksum += bench::digest(message.trade_price().mantissa());
        checksum += bench::digest(message.opposite_tradeable_instrument_id());
        checksum += bench::digest(message.opposite_side());
        checksum += bench::digest(message.opposite_order_id());
        checksum += bench::digest(message.combination_trade_id());
    }

    void on(const protocol::ImpliedOrderAddedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.tradeable_instrument_id());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.order_book_priority());
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.price().mantissa());
    }

    void on(const protocol::ImpliedOrderReplacedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.tradeable_instrument_id());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.order_book_priority());
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.price().mantissa());
    }

    void on(const protocol::ImpliedOrderDeletedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.tradeable_instrument_id());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.order_id());
    }

    void on(const protocol::TradeExecutedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.tradeable_instrument_id());
        checksum += bench::digest(message.trade_type());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.executed_quantity());
        checksum += bench::digest(message.trade_price().mantissa());
        checksum += bench::digest(message.combination_trade_id());
        checksum += bench::digest(message.participant_id_buyer());
        checksum += bench::digest(message.participant_id_seller());
    }

    void on(const protocol::CombinationTradeExecutedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.tradeable_instrument_id());
        checksum += bench::digest(message.trade_type());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.executed_quantity());
        checksum += bench::digest(message.trade_price().mantissa());
        checksum += bench::digest(message.buyer_tradeable_instrument_id());
        checksum += bench::digest(message.buyer_side());
        checksum += bench::digest(message.buyer_order_id());
        checksum += bench::digest(message.buyer_combination_trade_id());
        checksum += bench::digest(message.buyer_participant_id());
        checksum += bench::digest(message.seller_tradeable_instrument_id());
        checksum += bench::digest(message.seller_side());
        checksum += bench::digest(message.seller_order_id());
        checksum += bench::digest(message.seller_combination_trade_id());
        checksum += bench::digest(message.seller_participant_id());
    }

    void on(const protocol::TradeCancellationMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.tradeable_instrument_id());
        checksum += bench::digest(message.trade_id());
    }

    void on(const protocol::EquilibriumPriceMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.tradeable_instrument_id());
        checksum += bench::digest(message.equilibrium_price().mantissa());
        checksum += bench::digest(message.matched_quantity());
        checksum += bench::digest(message.bid_quantity());
        checksum += bench::digest(message.ask_quantity());
    }

    void on(const protocol::OpenHighLowLastTradeAdjustmentMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.tradeable_instrument_id());
        checksum += bench::digest(message.opening_trade().mantissa());
        checksum += bench::digest(message.highest_trade().mantissa());
        checksum += bench::digest(message.lowest_trade().mantissa());
        checksum += bench::digest(message.last_trade().mantissa());
        checksum += bench::digest(message.last_volume());
        checksum += bench::digest(message.total_traded_volume());
    }

    void on(const protocol::MarketSettlementMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.tradeable_instrument_id());
        checksum += bench::digest(message.opening_trade().mantissa());
        checksum += bench::digest(message.highest_trade().mantissa());
        checksum += bench::digest(message.lowest_trade().mantissa());
        checksum += bench::digest(message.last_trade().mantissa());
        checksum += bench::digest(message.last_volume());
        checksum += bench::digest(message.total_traded_volume());
    }

    void on(const protocol::TextMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.source_id());
        checksum += bench::digest(message.text());
    }

    void on(const protocol::RequestForQuoteMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.tradeable_instrument_id());
        checksum += bench::digest(message.rfq_side());
        checksum += bench::digest(message.quantity());
    }

    void on(const protocol::AnomalousOrderThresholdPublishMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.tradeable_instrument_id());
        checksum += bench::digest(message.aot_price().mantissa());
        checksum += bench::digest(message.aot_upper_price().mantissa());
        checksum += bench::digest(message.aot_lower_price().mantissa());
        checksum += bench::digest(message.etr_price().mantissa());
        checksum += bench::digest(message.etr_upper_price().mantissa());
        checksum += bench::digest(message.etr_lower_price().mantissa());
    }

    void on(const protocol::VolumeAndOpenInterestMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.tradeable_instrument_id());
        checksum += bench::digest(message.cumulative_volume());
        checksum += bench::digest(message.open_interest());
        checksum += bench::digest(message.voi_trade_date());
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
    return bench::run("Asx.AsxDerivatives.Ntp.Itch.v1.05", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
