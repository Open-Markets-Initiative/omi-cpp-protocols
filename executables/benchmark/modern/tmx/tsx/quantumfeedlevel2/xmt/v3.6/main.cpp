// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: main.cpp
// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/tmx/tsx/quantumfeedlevel2/xmt/v3.6.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/tmx/tsx/quantumfeedlevel2/xmt/v3.6/definitions.hpp"

namespace protocol = ::tmx::tsx::quantumfeedlevel2::xmt::v3_6;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::BodyIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    checksum += bench::digest(iterator.frame_header->start_of_frame.get());
    checksum += bench::digest(iterator.frame_header->protocol_name.get());
    checksum += bench::digest(iterator.frame_header->protocol_version.get());
    checksum += bench::digest(iterator.frame_header->message_length.get());
    checksum += bench::digest(iterator.frame_header->session_id.get());
    checksum += bench::digest(iterator.frame_header->ack_required_poss_dup.get());
    checksum += bench::digest(iterator.frame_header->num_body.get());

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.body_header->msg_length.get());
        checksum += bench::digest(iterator.body_header->msg_type.get());

        if (iterator.msg_type == 'J') {
            [[maybe_unused]] const auto* message = protocol::SymbolStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol.get());
            checksum += (static_cast<std::uint8_t>(message->stock_group.get()) != 0x0U ? bench::digest(message->stock_group.get()) : std::uint64_t{0});
            checksum += bench::digest(message->cusip.get());
            checksum += (static_cast<std::uint16_t>(message->board_lot.get()) != 0x0U ? bench::digest(message->board_lot.get()) : std::uint64_t{0});
            checksum += bench::digest(message->currency.get());
            checksum += (static_cast<std::uint64_t>(message->face_value.integer()) != 0x0ULL ? bench::digest(message->face_value.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->last_sale.integer()) != 0x0ULL ? bench::digest(message->last_sale.integer()) : std::uint64_t{0});
            checksum += bench::digest(message->listing_market.get());
            checksum += bench::digest(message->product_type.get());
            checksum += (static_cast<std::uint32_t>(message->buy_maximum_quantity.get()) != 0x0U ? bench::digest(message->buy_maximum_quantity.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->buy_minimum_quantity.get()) != 0x0U ? bench::digest(message->buy_minimum_quantity.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->sell_maximum_quantity.get()) != 0x0U ? bench::digest(message->sell_maximum_quantity.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->sell_minimum_quantity.get()) != 0x0U ? bench::digest(message->sell_minimum_quantity.get()) : std::uint64_t{0});
            checksum += bench::digest(message->stock_state.get());
            checksum += bench::digest(message->test_symbol.get());
            checksum += bench::digest(message->moc_eligible.get());
        } else if (iterator.msg_type == 'G') {
            [[maybe_unused]] const auto* message = protocol::OrderBookMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol.get());
            checksum += (static_cast<std::uint16_t>(message->broker_number.get()) != 0x0U ? bench::digest(message->broker_number.get()) : std::uint64_t{0});
            checksum += bench::digest(message->order_side.get());
            checksum += (static_cast<std::uint64_t>(message->order_id.get()) != 0x0ULL ? bench::digest(message->order_id.get()) : std::uint64_t{0});
            checksum += bench::digest(message->order_price.integer());
            checksum += (static_cast<std::uint32_t>(message->volume.get()) != 0x0U ? bench::digest(message->volume.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->priority_time_stamp.get()) != 0x0ULL ? bench::digest(message->priority_time_stamp.get()) : std::uint64_t{0});
        } else if (iterator.msg_type == 'j') {
            [[maybe_unused]] const auto* message = protocol::OrderBookTermsMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol.get());
            checksum += (static_cast<std::uint16_t>(message->broker_number.get()) != 0x0U ? bench::digest(message->broker_number.get()) : std::uint64_t{0});
            checksum += bench::digest(message->order_side.get());
            checksum += (static_cast<std::uint64_t>(message->order_id.get()) != 0x0ULL ? bench::digest(message->order_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->price.integer()) != 0x0ULL ? bench::digest(message->price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->volume.get()) != 0x0U ? bench::digest(message->volume.get()) : std::uint64_t{0});
            checksum += bench::digest(message->non_resident.get());
            checksum += bench::digest(message->settlement_terms.get());
            checksum += (static_cast<std::uint32_t>(message->settlement_date.get()) != 0x0U ? bench::digest(message->settlement_date.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->priority_time_stamp.get()) != 0x0ULL ? bench::digest(message->priority_time_stamp.get()) : std::uint64_t{0});
        } else if (iterator.msg_type == 'A') {
            [[maybe_unused]] const auto* message = protocol::AssignCopOrdersMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol.get());
            checksum += (static_cast<std::uint64_t>(message->calculated_opening_price.integer()) != 0x0ULL ? bench::digest(message->calculated_opening_price.integer()) : std::uint64_t{0});
            checksum += bench::digest(message->order_side.get());
            for (std::size_t cop_order_index = 0; const auto& cop_order_entry : message->cop_order) {
                checksum += cop_order_index++;
                checksum += (static_cast<std::uint16_t>(cop_order_entry.broker_number.get()) != 0x0U ? bench::digest(cop_order_entry.broker_number.get()) : std::uint64_t{0});
                checksum += (static_cast<std::uint64_t>(cop_order_entry.order_id.get()) != 0x0ULL ? bench::digest(cop_order_entry.order_id.get()) : std::uint64_t{0});
            }
            checksum += (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? bench::digest(message->trading_system_time_stamp.get()) : std::uint64_t{0});
        } else if (iterator.msg_type == 'B') {
            [[maybe_unused]] const auto* message = protocol::AssignCopNoOrdersMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol.get());
            checksum += (static_cast<std::uint64_t>(message->calculated_opening_price.integer()) != 0x0ULL ? bench::digest(message->calculated_opening_price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? bench::digest(message->trading_system_time_stamp.get()) : std::uint64_t{0});
        } else if (iterator.msg_type == 'C') {
            [[maybe_unused]] const auto* message = protocol::AssignLimitMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol.get());
            checksum += (static_cast<std::uint64_t>(message->calculated_opening_price.integer()) != 0x0ULL ? bench::digest(message->calculated_opening_price.integer()) : std::uint64_t{0});
            checksum += bench::digest(message->order_side.get());
            for (std::size_t cop_limit_index = 0; const auto& cop_limit_entry : message->cop_limit) {
                checksum += cop_limit_index++;
                checksum += (static_cast<std::uint16_t>(cop_limit_entry.broker_number.get()) != 0x0U ? bench::digest(cop_limit_entry.broker_number.get()) : std::uint64_t{0});
                checksum += (static_cast<std::uint64_t>(cop_limit_entry.order_id.get()) != 0x0ULL ? bench::digest(cop_limit_entry.order_id.get()) : std::uint64_t{0});
                checksum += (static_cast<std::uint64_t>(cop_limit_entry.price.integer()) != 0x0ULL ? bench::digest(cop_limit_entry.price.integer()) : std::uint64_t{0});
            }
            checksum += (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? bench::digest(message->trading_system_time_stamp.get()) : std::uint64_t{0});
        } else if (iterator.msg_type == 'E') {
            [[maybe_unused]] const auto* message = protocol::MarketStateUpdateMessage::parse(iterator.message);
            checksum += bench::digest(message->market_state.get());
            checksum += (static_cast<std::uint8_t>(message->stock_group.get()) != 0x0U ? bench::digest(message->stock_group.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? bench::digest(message->trading_system_time_stamp.get()) : std::uint64_t{0});
        } else if (iterator.msg_type == 'F') {
            [[maybe_unused]] const auto* message = protocol::MocImbalanceMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->imbalance_side.get());
            checksum += (static_cast<std::uint32_t>(message->imbalance_volume.get()) != 0x0U ? bench::digest(message->imbalance_volume.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? bench::digest(message->trading_system_time_stamp.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->imbalance_reference_price.integer()) != 0x0ULL ? bench::digest(message->imbalance_reference_price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->paired_volume.get()) != 0x0U ? bench::digest(message->paired_volume.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->market_order_imbalance_volume.get()) != 0x0U ? bench::digest(message->market_order_imbalance_volume.get()) : std::uint64_t{0});
            checksum += bench::digest(message->market_order_imbalance_side.get());
            checksum += (static_cast<std::uint64_t>(message->near_indicative_closing_price.integer()) != 0x0ULL ? bench::digest(message->near_indicative_closing_price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->far_indicative_closing_price.integer()) != 0x0ULL ? bench::digest(message->far_indicative_closing_price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->price_variation.integer()) != 0x0U ? bench::digest(message->price_variation.integer()) : std::uint64_t{0});
        } else if (iterator.msg_type == 'P') {
            [[maybe_unused]] const auto* message = protocol::OrderBookedMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol.get());
            checksum += (static_cast<std::uint16_t>(message->broker_number.get()) != 0x0U ? bench::digest(message->broker_number.get()) : std::uint64_t{0});
            checksum += bench::digest(message->order_side.get());
            checksum += (static_cast<std::uint64_t>(message->order_id.get()) != 0x0ULL ? bench::digest(message->order_id.get()) : std::uint64_t{0});
            checksum += bench::digest(message->order_price.integer());
            checksum += (static_cast<std::uint32_t>(message->volume.get()) != 0x0U ? bench::digest(message->volume.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->priority_time_stamp.get()) != 0x0ULL ? bench::digest(message->priority_time_stamp.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? bench::digest(message->trading_system_time_stamp.get()) : std::uint64_t{0});
        } else if (iterator.msg_type == 'm') {
            [[maybe_unused]] const auto* message = protocol::OrderBookedTermsMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol.get());
            checksum += (static_cast<std::uint16_t>(message->broker_number.get()) != 0x0U ? bench::digest(message->broker_number.get()) : std::uint64_t{0});
            checksum += bench::digest(message->order_side.get());
            checksum += (static_cast<std::uint64_t>(message->order_id.get()) != 0x0ULL ? bench::digest(message->order_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->price.integer()) != 0x0ULL ? bench::digest(message->price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->volume.get()) != 0x0U ? bench::digest(message->volume.get()) : std::uint64_t{0});
            checksum += bench::digest(message->non_resident.get());
            checksum += bench::digest(message->settlement_terms.get());
            checksum += (static_cast<std::uint32_t>(message->settlement_date.get()) != 0x0U ? bench::digest(message->settlement_date.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->priority_time_stamp.get()) != 0x0ULL ? bench::digest(message->priority_time_stamp.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? bench::digest(message->trading_system_time_stamp.get()) : std::uint64_t{0});
        } else if (iterator.msg_type == 'Q') {
            [[maybe_unused]] const auto* message = protocol::OrderCancelledMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol.get());
            checksum += (static_cast<std::uint16_t>(message->broker_number.get()) != 0x0U ? bench::digest(message->broker_number.get()) : std::uint64_t{0});
            checksum += bench::digest(message->order_side.get());
            checksum += (static_cast<std::uint64_t>(message->order_id.get()) != 0x0ULL ? bench::digest(message->order_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? bench::digest(message->trading_system_time_stamp.get()) : std::uint64_t{0});
        } else if (iterator.msg_type == 'n') {
            [[maybe_unused]] const auto* message = protocol::OrderCancelledTermsMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol.get());
            checksum += (static_cast<std::uint16_t>(message->broker_number.get()) != 0x0U ? bench::digest(message->broker_number.get()) : std::uint64_t{0});
            checksum += bench::digest(message->order_side.get());
            checksum += (static_cast<std::uint64_t>(message->order_id.get()) != 0x0ULL ? bench::digest(message->order_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? bench::digest(message->trading_system_time_stamp.get()) : std::uint64_t{0});
        } else if (iterator.msg_type == 'R') {
            [[maybe_unused]] const auto* message = protocol::OrderPriceTimeAssignedMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol.get());
            checksum += (static_cast<std::uint16_t>(message->broker_number.get()) != 0x0U ? bench::digest(message->broker_number.get()) : std::uint64_t{0});
            checksum += bench::digest(message->order_side.get());
            checksum += (static_cast<std::uint64_t>(message->order_id.get()) != 0x0ULL ? bench::digest(message->order_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->price.integer()) != 0x0ULL ? bench::digest(message->price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->volume.get()) != 0x0U ? bench::digest(message->volume.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->priority_time_stamp.get()) != 0x0ULL ? bench::digest(message->priority_time_stamp.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? bench::digest(message->trading_system_time_stamp.get()) : std::uint64_t{0});
        } else if (iterator.msg_type == 'o') {
            [[maybe_unused]] const auto* message = protocol::OrderPriceTimeAssignedTermsMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol.get());
            checksum += (static_cast<std::uint16_t>(message->broker_number.get()) != 0x0U ? bench::digest(message->broker_number.get()) : std::uint64_t{0});
            checksum += bench::digest(message->order_side.get());
            checksum += (static_cast<std::uint64_t>(message->order_id.get()) != 0x0ULL ? bench::digest(message->order_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->price.integer()) != 0x0ULL ? bench::digest(message->price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->volume.get()) != 0x0U ? bench::digest(message->volume.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->priority_time_stamp.get()) != 0x0ULL ? bench::digest(message->priority_time_stamp.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? bench::digest(message->trading_system_time_stamp.get()) : std::uint64_t{0});
        } else if (iterator.msg_type == 'I') {
            [[maybe_unused]] const auto* message = protocol::StockStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->comment.get());
            checksum += bench::digest(message->stock_state.get());
            checksum += (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? bench::digest(message->trading_system_time_stamp.get()) : std::uint64_t{0});
            checksum += bench::digest(message->listing_market.get());
            checksum += bench::digest(message->product_type.get());
        } else if (iterator.msg_type == 'S') {
            [[maybe_unused]] const auto* message = protocol::TradeReportMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol.get());
            checksum += (static_cast<std::uint32_t>(message->trade_number.get()) != 0x0U ? bench::digest(message->trade_number.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->price.integer()) != 0x0ULL ? bench::digest(message->price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->volume.get()) != 0x0U ? bench::digest(message->volume.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->buy_broker_number.get()) != 0x0U ? bench::digest(message->buy_broker_number.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->buy_order_id.get()) != 0x0ULL ? bench::digest(message->buy_order_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->buy_display_volume.get()) != 0x0U ? bench::digest(message->buy_display_volume.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->sell_broker_number.get()) != 0x0U ? bench::digest(message->sell_broker_number.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->sell_order_id.get()) != 0x0ULL ? bench::digest(message->sell_order_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->sell_display_volume.get()) != 0x0U ? bench::digest(message->sell_display_volume.get()) : std::uint64_t{0});
            checksum += bench::digest(message->bypass.get());
            checksum += (static_cast<std::uint32_t>(message->trade_time_stamp.get()) != 0x0U ? bench::digest(message->trade_time_stamp.get()) : std::uint64_t{0});
            checksum += bench::digest(message->cross_type.get());
            checksum += (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? bench::digest(message->trading_system_time_stamp.get()) : std::uint64_t{0});
            checksum += bench::digest(message->listing_market.get());
            checksum += bench::digest(message->product_type.get());
            checksum += (static_cast<std::uint32_t>(message->trade_date.get()) != 0x0U ? bench::digest(message->trade_date.get()) : std::uint64_t{0});
            checksum += bench::digest(message->is_mid_only.get());
            checksum += bench::digest(message->is_dark.get());
            checksum += bench::digest(message->is_conditional.get());
        } else if (iterator.msg_type == 'p') {
            [[maybe_unused]] const auto* message = protocol::TradeReportTermsMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol.get());
            checksum += (static_cast<std::uint32_t>(message->trade_number.get()) != 0x0U ? bench::digest(message->trade_number.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->price.integer()) != 0x0ULL ? bench::digest(message->price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->volume.get()) != 0x0U ? bench::digest(message->volume.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->buy_broker_number.get()) != 0x0U ? bench::digest(message->buy_broker_number.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->buy_order_id.get()) != 0x0ULL ? bench::digest(message->buy_order_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->buy_display_volume.get()) != 0x0U ? bench::digest(message->buy_display_volume.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->sell_broker_number.get()) != 0x0U ? bench::digest(message->sell_broker_number.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->sell_order_id.get()) != 0x0ULL ? bench::digest(message->sell_order_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->sell_display_volume.get()) != 0x0U ? bench::digest(message->sell_display_volume.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->trade_time_stamp.get()) != 0x0U ? bench::digest(message->trade_time_stamp.get()) : std::uint64_t{0});
            checksum += bench::digest(message->non_resident.get());
            checksum += bench::digest(message->settlement_terms.get());
            checksum += (static_cast<std::uint32_t>(message->settlement_date.get()) != 0x0U ? bench::digest(message->settlement_date.get()) : std::uint64_t{0});
            checksum += bench::digest(message->cross_type.get());
            checksum += (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? bench::digest(message->trading_system_time_stamp.get()) : std::uint64_t{0});
        } else if (iterator.msg_type == 'T') {
            [[maybe_unused]] const auto* message = protocol::TradeCancelledMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol.get());
            checksum += (static_cast<std::uint32_t>(message->trade_number.get()) != 0x0U ? bench::digest(message->trade_number.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? bench::digest(message->trading_system_time_stamp.get()) : std::uint64_t{0});
            checksum += bench::digest(message->listing_market.get());
            checksum += bench::digest(message->product_type.get());
            checksum += (static_cast<std::uint32_t>(message->trade_date.get()) != 0x0U ? bench::digest(message->trade_date.get()) : std::uint64_t{0});
        } else if (iterator.msg_type == 'q') {
            [[maybe_unused]] const auto* message = protocol::TradeCancelledTermsMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol.get());
            checksum += (static_cast<std::uint32_t>(message->trade_number.get()) != 0x0U ? bench::digest(message->trade_number.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? bench::digest(message->trading_system_time_stamp.get()) : std::uint64_t{0});
        } else if (iterator.msg_type == 'U') {
            [[maybe_unused]] const auto* message = protocol::TradeCorrectionMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol.get());
            checksum += (static_cast<std::uint32_t>(message->trade_number.get()) != 0x0U ? bench::digest(message->trade_number.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->price.integer()) != 0x0ULL ? bench::digest(message->price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->volume.get()) != 0x0U ? bench::digest(message->volume.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->buy_broker_number.get()) != 0x0U ? bench::digest(message->buy_broker_number.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->sell_broker_number.get()) != 0x0U ? bench::digest(message->sell_broker_number.get()) : std::uint64_t{0});
            checksum += bench::digest(message->initiated_by.get());
            checksum += (static_cast<std::uint32_t>(message->orig_trade_number.get()) != 0x0U ? bench::digest(message->orig_trade_number.get()) : std::uint64_t{0});
            checksum += bench::digest(message->bypass.get());
            checksum += (static_cast<std::uint32_t>(message->trade_time_stamp.get()) != 0x0U ? bench::digest(message->trade_time_stamp.get()) : std::uint64_t{0});
            checksum += bench::digest(message->cross_type.get());
            checksum += (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? bench::digest(message->trading_system_time_stamp.get()) : std::uint64_t{0});
            checksum += bench::digest(message->listing_market.get());
            checksum += bench::digest(message->product_type.get());
            checksum += (static_cast<std::uint32_t>(message->trade_date.get()) != 0x0U ? bench::digest(message->trade_date.get()) : std::uint64_t{0});
            checksum += bench::digest(message->is_mid_only.get());
            checksum += bench::digest(message->is_dark.get());
            checksum += bench::digest(message->is_conditional.get());
        } else if (iterator.msg_type == 'r') {
            [[maybe_unused]] const auto* message = protocol::TradeCorrectionTermsMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol.get());
            checksum += (static_cast<std::uint32_t>(message->trade_number.get()) != 0x0U ? bench::digest(message->trade_number.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->price.integer()) != 0x0ULL ? bench::digest(message->price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->volume.get()) != 0x0U ? bench::digest(message->volume.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->buy_broker_number.get()) != 0x0U ? bench::digest(message->buy_broker_number.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->sell_broker_number.get()) != 0x0U ? bench::digest(message->sell_broker_number.get()) : std::uint64_t{0});
            checksum += bench::digest(message->initiated_by.get());
            checksum += (static_cast<std::uint32_t>(message->orig_trade_number.get()) != 0x0U ? bench::digest(message->orig_trade_number.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->trade_time_stamp.get()) != 0x0U ? bench::digest(message->trade_time_stamp.get()) : std::uint64_t{0});
            checksum += bench::digest(message->non_resident.get());
            checksum += bench::digest(message->settlement_terms.get());
            checksum += (static_cast<std::uint32_t>(message->settlement_date.get()) != 0x0U ? bench::digest(message->settlement_date.get()) : std::uint64_t{0});
            checksum += bench::digest(message->cross_type.get());
            checksum += (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? bench::digest(message->trading_system_time_stamp.get()) : std::uint64_t{0});
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
