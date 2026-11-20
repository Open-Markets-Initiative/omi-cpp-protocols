// B3.B3Derivatives.BinaryUmdf.Sbe.v1.8: main.cpp
// B3.B3Derivatives.BinaryUmdf.Sbe.v1.8 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/b3/b3derivatives/binaryumdf/sbe/v1.8.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/b3/b3derivatives/binaryumdf/sbe/v1.8/definitions.hpp"

namespace protocol = ::b3::b3derivatives::binaryumdf::sbe::v1_8;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    checksum += bench::digest(iterator.packet_header->channel_id.get());
    checksum += bench::digest(iterator.packet_header->packet_reserved.get());
    checksum += bench::digest(iterator.packet_header->sequence_version.get());
    checksum += bench::digest(iterator.packet_header->sequence_number.get());
    checksum += bench::digest(iterator.packet_header->sending_time.get());

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.framing_header->message_length.get());
        checksum += bench::digest(iterator.framing_header->encoding_type.get());
        checksum += bench::digest(iterator.message_header->block_length.get());
        checksum += bench::digest(iterator.message_header->template_id.get());
        checksum += bench::digest(iterator.message_header->schema_id.get());
        checksum += bench::digest(iterator.message_header->version.get());

        if (iterator.template_id == 2) {
            [[maybe_unused]] const auto* message = protocol::SequenceMessage::parse(iterator.message);
            checksum += bench::digest(message->next_seq_no.get());
        } else if (iterator.template_id == 9) {
            [[maybe_unused]] const auto* message = protocol::EmptyBookMessage::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->match_event_indicator.LastTradeMsg());
            checksum += bench::digest(message->match_event_indicator.LastVolumeMsg());
            checksum += bench::digest(message->match_event_indicator.LastQuoteMsg());
            checksum += bench::digest(message->match_event_indicator.LastStatsMsg());
            checksum += bench::digest(message->match_event_indicator.LastImpliedMsg());
            checksum += bench::digest(message->match_event_indicator.RecoveryMsg());
            checksum += bench::digest(message->match_event_indicator.EndOfEvent());
            checksum += (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? bench::digest(message->md_entry_timestamp.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 11) {
            [[maybe_unused]] const auto* message = protocol::ChannelReset11Message::parse(iterator.message);
            checksum += bench::digest(message->match_event_indicator.LastTradeMsg());
            checksum += bench::digest(message->match_event_indicator.LastVolumeMsg());
            checksum += bench::digest(message->match_event_indicator.LastQuoteMsg());
            checksum += bench::digest(message->match_event_indicator.LastStatsMsg());
            checksum += bench::digest(message->match_event_indicator.LastImpliedMsg());
            checksum += bench::digest(message->match_event_indicator.RecoveryMsg());
            checksum += bench::digest(message->match_event_indicator.EndOfEvent());
            checksum += (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? bench::digest(message->md_entry_timestamp.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 3) {
            [[maybe_unused]] const auto* message = protocol::SecurityStatus3Message::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->match_event_indicator.LastTradeMsg());
            checksum += bench::digest(message->match_event_indicator.LastVolumeMsg());
            checksum += bench::digest(message->match_event_indicator.LastQuoteMsg());
            checksum += bench::digest(message->match_event_indicator.LastStatsMsg());
            checksum += bench::digest(message->match_event_indicator.LastImpliedMsg());
            checksum += bench::digest(message->match_event_indicator.RecoveryMsg());
            checksum += bench::digest(message->match_event_indicator.EndOfEvent());
            checksum += bench::digest(message->trading_session_id.get());
            checksum += bench::digest(message->security_trading_status.get());
            checksum += (static_cast<std::uint8_t>(message->security_trading_event.get()) != 0x0FFU ? bench::digest(message->security_trading_event.get()) : std::uint64_t{0});
            checksum += bench::digest(message->trade_date.get());
            checksum += (static_cast<std::uint64_t>(message->trad_ses_open_time.get()) != 0x0ULL ? bench::digest(message->trad_ses_open_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0ULL ? bench::digest(message->transact_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? bench::digest(message->rpt_seq.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 10) {
            [[maybe_unused]] const auto* message = protocol::SecurityGroupPhase10Message::parse(iterator.message);
            checksum += bench::digest(message->security_group.get());
            checksum += bench::digest(message->match_event_indicator.LastTradeMsg());
            checksum += bench::digest(message->match_event_indicator.LastVolumeMsg());
            checksum += bench::digest(message->match_event_indicator.LastQuoteMsg());
            checksum += bench::digest(message->match_event_indicator.LastStatsMsg());
            checksum += bench::digest(message->match_event_indicator.LastImpliedMsg());
            checksum += bench::digest(message->match_event_indicator.RecoveryMsg());
            checksum += bench::digest(message->match_event_indicator.EndOfEvent());
            checksum += bench::digest(message->trading_session_id.get());
            checksum += bench::digest(message->trading_session_sub_id.get());
            checksum += (static_cast<std::uint8_t>(message->security_trading_event.get()) != 0x0FFU ? bench::digest(message->security_trading_event.get()) : std::uint64_t{0});
            checksum += bench::digest(message->trade_date.get());
            checksum += (static_cast<std::uint64_t>(message->trad_ses_open_time.get()) != 0x0ULL ? bench::digest(message->trad_ses_open_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0ULL ? bench::digest(message->transact_time.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 4) {
            [[maybe_unused]] const auto* message = protocol::DeprecatedSecurityDefinitionMessage::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->security_exchange.get());
            checksum += bench::digest(message->security_id_source.get());
            checksum += bench::digest(message->security_group.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->security_update_action.get());
            checksum += bench::digest(message->security_type.get());
            checksum += bench::digest(message->security_sub_type.get());
            checksum += bench::digest(message->tot_no_related_sym.get());
            checksum += (static_cast<std::uint64_t>(message->min_price_increment_legacy.integer()) != 0x08000000000000000ULL ? bench::digest(message->min_price_increment_legacy.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->strike_price.integer()) != 0x08000000000000000ULL ? bench::digest(message->strike_price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->contract_multiplier.integer()) != 0x08000000000000000ULL ? bench::digest(message->contract_multiplier.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->price_divisor.integer()) != 0x08000000000000000ULL ? bench::digest(message->price_divisor.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->security_validity_timestamp.get()) != 0x08000000000000000ULL ? bench::digest(message->security_validity_timestamp.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->no_shares_issued.get()) != 0x0ULL ? bench::digest(message->no_shares_issued.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->clearing_house_id.get()) != 0x0ULL ? bench::digest(message->clearing_house_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->min_order_qty.get()) != 0x08000000000000000ULL ? bench::digest(message->min_order_qty.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->max_order_qty.get()) != 0x08000000000000000ULL ? bench::digest(message->max_order_qty.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->min_lot_size.get()) != 0x08000000000000000ULL ? bench::digest(message->min_lot_size.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->min_trade_vol.get()) != 0x08000000000000000ULL ? bench::digest(message->min_trade_vol.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->corporate_action_event_id.get()) != 0x0U ? bench::digest(message->corporate_action_event_id.get()) : std::uint64_t{0});
            checksum += bench::digest(message->issue_date.get());
            checksum += (static_cast<std::uint32_t>(message->maturity_date.get()) != 0x0U ? bench::digest(message->maturity_date.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->start_date.get()) != 0x0U ? bench::digest(message->start_date.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->end_date.get()) != 0x0U ? bench::digest(message->end_date.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->settl_type.get()) != 0x0FFFFU ? bench::digest(message->settl_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->settl_date.get()) != 0x0U ? bench::digest(message->settl_date.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->dated_date.get()) != 0x0U ? bench::digest(message->dated_date.get()) : std::uint64_t{0});
            checksum += bench::digest(message->asset.get());
            checksum += bench::digest(message->cfi_code.get());
            checksum += (static_cast<std::uint16_t>(message->maturity_month_year.year.get()) != 0x0U ? bench::digest(message->maturity_month_year.year.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->maturity_month_year.month.get()) != 0x0U ? bench::digest(message->maturity_month_year.month.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->maturity_month_year.day.get()) != 0x0U ? bench::digest(message->maturity_month_year.day.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->maturity_month_year.week.get()) != 0x0U ? bench::digest(message->maturity_month_year.week.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->contract_settl_month.year.get()) != 0x0U ? bench::digest(message->contract_settl_month.year.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->contract_settl_month.month.get()) != 0x0U ? bench::digest(message->contract_settl_month.month.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->contract_settl_month.day.get()) != 0x0U ? bench::digest(message->contract_settl_month.day.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->contract_settl_month.week.get()) != 0x0U ? bench::digest(message->contract_settl_month.week.get()) : std::uint64_t{0});
            checksum += bench::digest(message->currency.get());
            checksum += (static_cast<std::uint8_t>(message->lot_type.get()) != 0x0FFU ? bench::digest(message->lot_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->tick_size_denominator.get()) != 0x0FFU ? bench::digest(message->tick_size_denominator.get()) : std::uint64_t{0});
            checksum += bench::digest(message->product.get());
            checksum += (static_cast<std::uint8_t>(message->exercise_style.get()) != 0x0FFU ? bench::digest(message->exercise_style.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->put_or_call.get()) != 0x0FFU ? bench::digest(message->put_or_call.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->price_type_optional.get()) != 0x0U ? bench::digest(message->price_type_optional.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->market_segment_id.get()) != 0x0U ? bench::digest(message->market_segment_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->governance_indicator.get()) != 0x0FFU ? bench::digest(message->governance_indicator.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->security_match_type.get()) != 0x0FFU ? bench::digest(message->security_match_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->last_fragment.get()) != 0x0FFU ? bench::digest(message->last_fragment.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->multi_leg_model.get()) != 0x0FFU ? bench::digest(message->multi_leg_model.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->multi_leg_price_method.get()) != 0x0FFU ? bench::digest(message->multi_leg_price_method.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->min_cross_qty.get()) != 0x08000000000000000ULL ? bench::digest(message->min_cross_qty.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 12) {
            [[maybe_unused]] const auto* message = protocol::SecurityDefinitionMessage::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->security_exchange.get());
            checksum += bench::digest(message->security_id_source.get());
            checksum += bench::digest(message->security_group.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->security_update_action.get());
            checksum += bench::digest(message->security_type.get());
            checksum += bench::digest(message->security_sub_type.get());
            checksum += bench::digest(message->tot_no_related_sym.get());
            checksum += (static_cast<std::uint64_t>(message->min_price_increment_optional.integer()) != 0x08000000000000000ULL ? bench::digest(message->min_price_increment_optional.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->strike_price.integer()) != 0x08000000000000000ULL ? bench::digest(message->strike_price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->contract_multiplier.integer()) != 0x08000000000000000ULL ? bench::digest(message->contract_multiplier.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->price_divisor.integer()) != 0x08000000000000000ULL ? bench::digest(message->price_divisor.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->security_validity_timestamp.get()) != 0x08000000000000000ULL ? bench::digest(message->security_validity_timestamp.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->no_shares_issued.get()) != 0x0ULL ? bench::digest(message->no_shares_issued.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->clearing_house_id.get()) != 0x0ULL ? bench::digest(message->clearing_house_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->min_order_qty.get()) != 0x08000000000000000ULL ? bench::digest(message->min_order_qty.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->max_order_qty.get()) != 0x08000000000000000ULL ? bench::digest(message->max_order_qty.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->min_lot_size.get()) != 0x08000000000000000ULL ? bench::digest(message->min_lot_size.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->min_trade_vol.get()) != 0x08000000000000000ULL ? bench::digest(message->min_trade_vol.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->corporate_action_event_id.get()) != 0x0U ? bench::digest(message->corporate_action_event_id.get()) : std::uint64_t{0});
            checksum += bench::digest(message->issue_date.get());
            checksum += (static_cast<std::uint32_t>(message->maturity_date.get()) != 0x0U ? bench::digest(message->maturity_date.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->start_date.get()) != 0x0U ? bench::digest(message->start_date.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->end_date.get()) != 0x0U ? bench::digest(message->end_date.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->settl_type.get()) != 0x0FFFFU ? bench::digest(message->settl_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->settl_date.get()) != 0x0U ? bench::digest(message->settl_date.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->dated_date.get()) != 0x0U ? bench::digest(message->dated_date.get()) : std::uint64_t{0});
            checksum += bench::digest(message->asset.get());
            checksum += bench::digest(message->cfi_code.get());
            checksum += (static_cast<std::uint16_t>(message->maturity_month_year.year.get()) != 0x0U ? bench::digest(message->maturity_month_year.year.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->maturity_month_year.month.get()) != 0x0U ? bench::digest(message->maturity_month_year.month.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->maturity_month_year.day.get()) != 0x0U ? bench::digest(message->maturity_month_year.day.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->maturity_month_year.week.get()) != 0x0U ? bench::digest(message->maturity_month_year.week.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->contract_settl_month.year.get()) != 0x0U ? bench::digest(message->contract_settl_month.year.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->contract_settl_month.month.get()) != 0x0U ? bench::digest(message->contract_settl_month.month.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->contract_settl_month.day.get()) != 0x0U ? bench::digest(message->contract_settl_month.day.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->contract_settl_month.week.get()) != 0x0U ? bench::digest(message->contract_settl_month.week.get()) : std::uint64_t{0});
            checksum += bench::digest(message->currency.get());
            checksum += (static_cast<std::uint8_t>(message->lot_type.get()) != 0x0FFU ? bench::digest(message->lot_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->tick_size_denominator.get()) != 0x0FFU ? bench::digest(message->tick_size_denominator.get()) : std::uint64_t{0});
            checksum += bench::digest(message->product.get());
            checksum += (static_cast<std::uint8_t>(message->exercise_style.get()) != 0x0FFU ? bench::digest(message->exercise_style.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->put_or_call.get()) != 0x0FFU ? bench::digest(message->put_or_call.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->price_type_optional.get()) != 0x0U ? bench::digest(message->price_type_optional.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->market_segment_id.get()) != 0x0U ? bench::digest(message->market_segment_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->governance_indicator.get()) != 0x0FFU ? bench::digest(message->governance_indicator.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->security_match_type.get()) != 0x0FFU ? bench::digest(message->security_match_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->last_fragment.get()) != 0x0FFU ? bench::digest(message->last_fragment.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->multi_leg_model.get()) != 0x0FFU ? bench::digest(message->multi_leg_model.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->multi_leg_price_method.get()) != 0x0FFU ? bench::digest(message->multi_leg_price_method.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->min_cross_qty.get()) != 0x08000000000000000ULL ? bench::digest(message->min_cross_qty.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 5) {
            [[maybe_unused]] const auto* message = protocol::News5Message::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->security_id_optional.get()) != 0x0ULL ? bench::digest(message->security_id_optional.get()) : std::uint64_t{0});
            checksum += bench::digest(message->match_event_indicator.LastTradeMsg());
            checksum += bench::digest(message->match_event_indicator.LastVolumeMsg());
            checksum += bench::digest(message->match_event_indicator.LastQuoteMsg());
            checksum += bench::digest(message->match_event_indicator.LastStatsMsg());
            checksum += bench::digest(message->match_event_indicator.LastImpliedMsg());
            checksum += bench::digest(message->match_event_indicator.RecoveryMsg());
            checksum += bench::digest(message->match_event_indicator.EndOfEvent());
            checksum += bench::digest(message->news_source.get());
            checksum += bench::digest(message->part_count.get());
            checksum += bench::digest(message->part_number.get());
            checksum += (static_cast<std::uint64_t>(message->news_id.get()) != 0x0ULL ? bench::digest(message->news_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->orig_time.get()) != 0x0ULL ? bench::digest(message->orig_time.get()) : std::uint64_t{0});
            checksum += bench::digest(message->total_text_length.get());
        } else if (iterator.template_id == 15) {
            [[maybe_unused]] const auto* message = protocol::OpeningPrice15Message::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->match_event_indicator.LastTradeMsg());
            checksum += bench::digest(message->match_event_indicator.LastVolumeMsg());
            checksum += bench::digest(message->match_event_indicator.LastQuoteMsg());
            checksum += bench::digest(message->match_event_indicator.LastStatsMsg());
            checksum += bench::digest(message->match_event_indicator.LastImpliedMsg());
            checksum += bench::digest(message->match_event_indicator.RecoveryMsg());
            checksum += bench::digest(message->match_event_indicator.EndOfEvent());
            checksum += bench::digest(message->md_update_action.get());
            checksum += bench::digest(message->open_close_settl_flag.get());
            checksum += bench::digest(message->md_future_price.integer());
            checksum += (static_cast<std::uint64_t>(message->net_chg_prev_day.integer()) != 0x08000000000000000ULL ? bench::digest(message->net_chg_prev_day.integer()) : std::uint64_t{0});
            checksum += bench::digest(message->trade_date.get());
            checksum += (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? bench::digest(message->md_entry_timestamp.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? bench::digest(message->rpt_seq.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 16) {
            [[maybe_unused]] const auto* message = protocol::TheoreticalOpeningPrice16Message::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->match_event_indicator.LastTradeMsg());
            checksum += bench::digest(message->match_event_indicator.LastVolumeMsg());
            checksum += bench::digest(message->match_event_indicator.LastQuoteMsg());
            checksum += bench::digest(message->match_event_indicator.LastStatsMsg());
            checksum += bench::digest(message->match_event_indicator.LastImpliedMsg());
            checksum += bench::digest(message->match_event_indicator.RecoveryMsg());
            checksum += bench::digest(message->match_event_indicator.EndOfEvent());
            checksum += bench::digest(message->md_update_action.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += (static_cast<std::uint64_t>(message->md_corporate_offset_price_optional.integer()) != 0x08000000000000000ULL ? bench::digest(message->md_corporate_offset_price_optional.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->md_entry_size_optional.get()) != 0x08000000000000000ULL ? bench::digest(message->md_entry_size_optional.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? bench::digest(message->md_entry_timestamp.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? bench::digest(message->rpt_seq.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 17) {
            [[maybe_unused]] const auto* message = protocol::ClosingPrice17Message::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->match_event_indicator.LastTradeMsg());
            checksum += bench::digest(message->match_event_indicator.LastVolumeMsg());
            checksum += bench::digest(message->match_event_indicator.LastQuoteMsg());
            checksum += bench::digest(message->match_event_indicator.LastStatsMsg());
            checksum += bench::digest(message->match_event_indicator.LastImpliedMsg());
            checksum += bench::digest(message->match_event_indicator.RecoveryMsg());
            checksum += bench::digest(message->match_event_indicator.EndOfEvent());
            checksum += bench::digest(message->open_close_settl_flag.get());
            checksum += bench::digest(message->md_corporate_price.integer());
            checksum += (static_cast<std::uint16_t>(message->last_trade_date.get()) != 0x0U ? bench::digest(message->last_trade_date.get()) : std::uint64_t{0});
            checksum += bench::digest(message->trade_date.get());
            checksum += (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? bench::digest(message->md_entry_timestamp.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? bench::digest(message->rpt_seq.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 19) {
            [[maybe_unused]] const auto* message = protocol::AuctionImbalance19Message::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->match_event_indicator.LastTradeMsg());
            checksum += bench::digest(message->match_event_indicator.LastVolumeMsg());
            checksum += bench::digest(message->match_event_indicator.LastQuoteMsg());
            checksum += bench::digest(message->match_event_indicator.LastStatsMsg());
            checksum += bench::digest(message->match_event_indicator.LastImpliedMsg());
            checksum += bench::digest(message->match_event_indicator.RecoveryMsg());
            checksum += bench::digest(message->match_event_indicator.EndOfEvent());
            checksum += bench::digest(message->md_update_action.get());
            checksum += bench::digest(message->imbalance_condition.ImbalanceMoreBuyers());
            checksum += bench::digest(message->imbalance_condition.ImbalanceMoreSellers());
            checksum += (static_cast<std::uint64_t>(message->md_entry_size_optional.get()) != 0x08000000000000000ULL ? bench::digest(message->md_entry_size_optional.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? bench::digest(message->md_entry_timestamp.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? bench::digest(message->rpt_seq.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 20) {
            [[maybe_unused]] const auto* message = protocol::PriceBand20Message::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->match_event_indicator.LastTradeMsg());
            checksum += bench::digest(message->match_event_indicator.LastVolumeMsg());
            checksum += bench::digest(message->match_event_indicator.LastQuoteMsg());
            checksum += bench::digest(message->match_event_indicator.LastStatsMsg());
            checksum += bench::digest(message->match_event_indicator.LastImpliedMsg());
            checksum += bench::digest(message->match_event_indicator.RecoveryMsg());
            checksum += bench::digest(message->match_event_indicator.EndOfEvent());
            checksum += (static_cast<std::uint8_t>(message->price_band_type.get()) != 0x0FFU ? bench::digest(message->price_band_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->price_limit_type.get()) != 0x0FFU ? bench::digest(message->price_limit_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->price_band_midpoint_price_type.get()) != 0x0FFU ? bench::digest(message->price_band_midpoint_price_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->low_limit_price.integer()) != 0x08000000000000000ULL ? bench::digest(message->low_limit_price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->high_limit_price.integer()) != 0x08000000000000000ULL ? bench::digest(message->high_limit_price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->trading_reference_price_legacy.integer()) != 0x08000000000000000ULL ? bench::digest(message->trading_reference_price_legacy.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? bench::digest(message->md_entry_timestamp.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? bench::digest(message->rpt_seq.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 21) {
            [[maybe_unused]] const auto* message = protocol::QuantityBand21Message::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->match_event_indicator.LastTradeMsg());
            checksum += bench::digest(message->match_event_indicator.LastVolumeMsg());
            checksum += bench::digest(message->match_event_indicator.LastQuoteMsg());
            checksum += bench::digest(message->match_event_indicator.LastStatsMsg());
            checksum += bench::digest(message->match_event_indicator.LastImpliedMsg());
            checksum += bench::digest(message->match_event_indicator.RecoveryMsg());
            checksum += bench::digest(message->match_event_indicator.EndOfEvent());
            checksum += (static_cast<std::uint64_t>(message->avg_daily_traded_qty.get()) != 0x08000000000000000ULL ? bench::digest(message->avg_daily_traded_qty.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->max_trade_vol.get()) != 0x08000000000000000ULL ? bench::digest(message->max_trade_vol.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? bench::digest(message->md_entry_timestamp.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? bench::digest(message->rpt_seq.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 22) {
            [[maybe_unused]] const auto* message = protocol::PriceBand22Message::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->match_event_indicator.LastTradeMsg());
            checksum += bench::digest(message->match_event_indicator.LastVolumeMsg());
            checksum += bench::digest(message->match_event_indicator.LastQuoteMsg());
            checksum += bench::digest(message->match_event_indicator.LastStatsMsg());
            checksum += bench::digest(message->match_event_indicator.LastImpliedMsg());
            checksum += bench::digest(message->match_event_indicator.RecoveryMsg());
            checksum += bench::digest(message->match_event_indicator.EndOfEvent());
            checksum += (static_cast<std::uint8_t>(message->price_band_type.get()) != 0x0FFU ? bench::digest(message->price_band_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->price_limit_type.get()) != 0x0FFU ? bench::digest(message->price_limit_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->price_band_midpoint_price_type.get()) != 0x0FFU ? bench::digest(message->price_band_midpoint_price_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->low_limit_price.integer()) != 0x08000000000000000ULL ? bench::digest(message->low_limit_price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->high_limit_price.integer()) != 0x08000000000000000ULL ? bench::digest(message->high_limit_price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->trading_reference_price_optional.integer()) != 0x08000000000000000ULL ? bench::digest(message->trading_reference_price_optional.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? bench::digest(message->md_entry_timestamp.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? bench::digest(message->rpt_seq.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 24) {
            [[maybe_unused]] const auto* message = protocol::HighPrice24Message::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->match_event_indicator.LastTradeMsg());
            checksum += bench::digest(message->match_event_indicator.LastVolumeMsg());
            checksum += bench::digest(message->match_event_indicator.LastQuoteMsg());
            checksum += bench::digest(message->match_event_indicator.LastStatsMsg());
            checksum += bench::digest(message->match_event_indicator.LastImpliedMsg());
            checksum += bench::digest(message->match_event_indicator.RecoveryMsg());
            checksum += bench::digest(message->match_event_indicator.EndOfEvent());
            checksum += bench::digest(message->md_update_action.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->md_future_price.integer());
            checksum += (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? bench::digest(message->md_entry_timestamp.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? bench::digest(message->rpt_seq.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 25) {
            [[maybe_unused]] const auto* message = protocol::LowPrice25Message::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->match_event_indicator.LastTradeMsg());
            checksum += bench::digest(message->match_event_indicator.LastVolumeMsg());
            checksum += bench::digest(message->match_event_indicator.LastQuoteMsg());
            checksum += bench::digest(message->match_event_indicator.LastStatsMsg());
            checksum += bench::digest(message->match_event_indicator.LastImpliedMsg());
            checksum += bench::digest(message->match_event_indicator.RecoveryMsg());
            checksum += bench::digest(message->match_event_indicator.EndOfEvent());
            checksum += bench::digest(message->md_update_action.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->md_future_price.integer());
            checksum += (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? bench::digest(message->md_entry_timestamp.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? bench::digest(message->rpt_seq.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 27) {
            [[maybe_unused]] const auto* message = protocol::LastTradePrice27Message::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->match_event_indicator.LastTradeMsg());
            checksum += bench::digest(message->match_event_indicator.LastVolumeMsg());
            checksum += bench::digest(message->match_event_indicator.LastQuoteMsg());
            checksum += bench::digest(message->match_event_indicator.LastStatsMsg());
            checksum += bench::digest(message->match_event_indicator.LastImpliedMsg());
            checksum += bench::digest(message->match_event_indicator.RecoveryMsg());
            checksum += bench::digest(message->match_event_indicator.EndOfEvent());
            checksum += bench::digest(message->trading_session_id.get());
            checksum += bench::digest(message->trade_condition.OpeningPrice());
            checksum += bench::digest(message->trade_condition.Crossed());
            checksum += bench::digest(message->trade_condition.LastTradeAtTheSamePrice());
            checksum += bench::digest(message->trade_condition.OutOfSequence());
            checksum += bench::digest(message->trade_condition.TradeOnBehalf());
            checksum += bench::digest(message->trade_condition.RegularTrade());
            checksum += bench::digest(message->trade_condition.BlockTrade());
            checksum += bench::digest(message->md_future_price.integer());
            checksum += bench::digest(message->md_entry_size.get());
            checksum += bench::digest(message->trade_id.get());
            checksum += (static_cast<std::uint32_t>(message->md_entry_buyer.get()) != 0x0U ? bench::digest(message->md_entry_buyer.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->md_entry_seller.get()) != 0x0U ? bench::digest(message->md_entry_seller.get()) : std::uint64_t{0});
            checksum += bench::digest(message->trade_date.get());
            checksum += (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? bench::digest(message->md_entry_timestamp.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? bench::digest(message->rpt_seq.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->seller_days.get()) != 0x0U ? bench::digest(message->seller_days.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->md_entry_interest_rate.integer()) != 0x0ULL ? bench::digest(message->md_entry_interest_rate.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->trd_sub_type.get()) != 0x0U ? bench::digest(message->trd_sub_type.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 28) {
            [[maybe_unused]] const auto* message = protocol::SettlementPrice28Message::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->match_event_indicator.LastTradeMsg());
            checksum += bench::digest(message->match_event_indicator.LastVolumeMsg());
            checksum += bench::digest(message->match_event_indicator.LastQuoteMsg());
            checksum += bench::digest(message->match_event_indicator.LastStatsMsg());
            checksum += bench::digest(message->match_event_indicator.LastImpliedMsg());
            checksum += bench::digest(message->match_event_indicator.RecoveryMsg());
            checksum += bench::digest(message->match_event_indicator.EndOfEvent());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->md_future_price.integer());
            checksum += (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? bench::digest(message->md_entry_timestamp.get()) : std::uint64_t{0});
            checksum += bench::digest(message->open_close_settl_flag.get());
            checksum += bench::digest(message->price_type.get());
            checksum += bench::digest(message->settl_price_type.get());
            checksum += (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? bench::digest(message->rpt_seq.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 29) {
            [[maybe_unused]] const auto* message = protocol::OpenInterest29Message::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->match_event_indicator.LastTradeMsg());
            checksum += bench::digest(message->match_event_indicator.LastVolumeMsg());
            checksum += bench::digest(message->match_event_indicator.LastQuoteMsg());
            checksum += bench::digest(message->match_event_indicator.LastStatsMsg());
            checksum += bench::digest(message->match_event_indicator.LastImpliedMsg());
            checksum += bench::digest(message->match_event_indicator.RecoveryMsg());
            checksum += bench::digest(message->match_event_indicator.EndOfEvent());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->md_entry_size.get());
            checksum += (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? bench::digest(message->md_entry_timestamp.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? bench::digest(message->rpt_seq.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 30) {
            [[maybe_unused]] const auto* message = protocol::SnapshotFullRefreshHeader30Message::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->last_msg_seq_num_processed.get());
            checksum += bench::digest(message->tot_num_reports.get());
            checksum += bench::digest(message->tot_num_bids.get());
            checksum += bench::digest(message->tot_num_offers.get());
            checksum += bench::digest(message->tot_num_stats.get());
            checksum += (static_cast<std::uint32_t>(message->last_rpt_seq.get()) != 0x0U ? bench::digest(message->last_rpt_seq.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 50) {
            [[maybe_unused]] const auto* message = protocol::OrderMbO50Message::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->match_event_indicator.LastTradeMsg());
            checksum += bench::digest(message->match_event_indicator.LastVolumeMsg());
            checksum += bench::digest(message->match_event_indicator.LastQuoteMsg());
            checksum += bench::digest(message->match_event_indicator.LastStatsMsg());
            checksum += bench::digest(message->match_event_indicator.LastImpliedMsg());
            checksum += bench::digest(message->match_event_indicator.RecoveryMsg());
            checksum += bench::digest(message->match_event_indicator.EndOfEvent());
            checksum += bench::digest(message->md_update_action.get());
            checksum += bench::digest(message->md_entry_type.get());
            checksum += (static_cast<std::uint64_t>(message->md_corporate_offset_price_optional.integer()) != 0x08000000000000000ULL ? bench::digest(message->md_corporate_offset_price_optional.integer()) : std::uint64_t{0});
            checksum += bench::digest(message->md_entry_size.get());
            checksum += bench::digest(message->md_entry_position_no.get());
            checksum += (static_cast<std::uint32_t>(message->entering_firm.get()) != 0x0U ? bench::digest(message->entering_firm.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->md_insert_timestamp.get()) != 0x0ULL ? bench::digest(message->md_insert_timestamp.get()) : std::uint64_t{0});
            checksum += bench::digest(message->secondary_order_id.get());
            checksum += (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? bench::digest(message->rpt_seq.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? bench::digest(message->md_entry_timestamp.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 51) {
            [[maybe_unused]] const auto* message = protocol::DeleteOrderMbO51Message::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->match_event_indicator.LastTradeMsg());
            checksum += bench::digest(message->match_event_indicator.LastVolumeMsg());
            checksum += bench::digest(message->match_event_indicator.LastQuoteMsg());
            checksum += bench::digest(message->match_event_indicator.LastStatsMsg());
            checksum += bench::digest(message->match_event_indicator.LastImpliedMsg());
            checksum += bench::digest(message->match_event_indicator.RecoveryMsg());
            checksum += bench::digest(message->match_event_indicator.EndOfEvent());
            checksum += bench::digest(message->md_entry_type.get());
            checksum += bench::digest(message->md_entry_position_no.get());
            checksum += (static_cast<std::uint64_t>(message->md_entry_size_optional.get()) != 0x08000000000000000ULL ? bench::digest(message->md_entry_size_optional.get()) : std::uint64_t{0});
            checksum += bench::digest(message->secondary_order_id.get());
            checksum += (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? bench::digest(message->md_entry_timestamp.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? bench::digest(message->rpt_seq.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 52) {
            [[maybe_unused]] const auto* message = protocol::MassDeleteOrdersMbO52Message::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->match_event_indicator.LastTradeMsg());
            checksum += bench::digest(message->match_event_indicator.LastVolumeMsg());
            checksum += bench::digest(message->match_event_indicator.LastQuoteMsg());
            checksum += bench::digest(message->match_event_indicator.LastStatsMsg());
            checksum += bench::digest(message->match_event_indicator.LastImpliedMsg());
            checksum += bench::digest(message->match_event_indicator.RecoveryMsg());
            checksum += bench::digest(message->match_event_indicator.EndOfEvent());
            checksum += bench::digest(message->md_update_action.get());
            checksum += bench::digest(message->md_entry_type.get());
            checksum += bench::digest(message->md_entry_position_no.get());
            checksum += (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? bench::digest(message->md_entry_timestamp.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? bench::digest(message->rpt_seq.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 53) {
            [[maybe_unused]] const auto* message = protocol::Trade53Message::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->match_event_indicator.LastTradeMsg());
            checksum += bench::digest(message->match_event_indicator.LastVolumeMsg());
            checksum += bench::digest(message->match_event_indicator.LastQuoteMsg());
            checksum += bench::digest(message->match_event_indicator.LastStatsMsg());
            checksum += bench::digest(message->match_event_indicator.LastImpliedMsg());
            checksum += bench::digest(message->match_event_indicator.RecoveryMsg());
            checksum += bench::digest(message->match_event_indicator.EndOfEvent());
            checksum += bench::digest(message->trading_session_id.get());
            checksum += bench::digest(message->trade_condition.OpeningPrice());
            checksum += bench::digest(message->trade_condition.Crossed());
            checksum += bench::digest(message->trade_condition.LastTradeAtTheSamePrice());
            checksum += bench::digest(message->trade_condition.OutOfSequence());
            checksum += bench::digest(message->trade_condition.TradeOnBehalf());
            checksum += bench::digest(message->trade_condition.RegularTrade());
            checksum += bench::digest(message->trade_condition.BlockTrade());
            checksum += bench::digest(message->md_future_price.integer());
            checksum += bench::digest(message->md_entry_size.get());
            checksum += bench::digest(message->trade_id.get());
            checksum += (static_cast<std::uint32_t>(message->md_entry_buyer.get()) != 0x0U ? bench::digest(message->md_entry_buyer.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->md_entry_seller.get()) != 0x0U ? bench::digest(message->md_entry_seller.get()) : std::uint64_t{0});
            checksum += bench::digest(message->trade_date.get());
            checksum += (static_cast<std::uint8_t>(message->trd_sub_type.get()) != 0x0U ? bench::digest(message->trd_sub_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? bench::digest(message->md_entry_timestamp.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? bench::digest(message->rpt_seq.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 54) {
            [[maybe_unused]] const auto* message = protocol::ForwardTrade54Message::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->match_event_indicator.LastTradeMsg());
            checksum += bench::digest(message->match_event_indicator.LastVolumeMsg());
            checksum += bench::digest(message->match_event_indicator.LastQuoteMsg());
            checksum += bench::digest(message->match_event_indicator.LastStatsMsg());
            checksum += bench::digest(message->match_event_indicator.LastImpliedMsg());
            checksum += bench::digest(message->match_event_indicator.RecoveryMsg());
            checksum += bench::digest(message->match_event_indicator.EndOfEvent());
            checksum += bench::digest(message->trading_session_id.get());
            checksum += bench::digest(message->trade_condition.OpeningPrice());
            checksum += bench::digest(message->trade_condition.Crossed());
            checksum += bench::digest(message->trade_condition.LastTradeAtTheSamePrice());
            checksum += bench::digest(message->trade_condition.OutOfSequence());
            checksum += bench::digest(message->trade_condition.TradeOnBehalf());
            checksum += bench::digest(message->trade_condition.RegularTrade());
            checksum += bench::digest(message->trade_condition.BlockTrade());
            checksum += bench::digest(message->md_future_price.integer());
            checksum += bench::digest(message->md_entry_size.get());
            checksum += bench::digest(message->trade_id.get());
            checksum += (static_cast<std::uint32_t>(message->md_entry_buyer.get()) != 0x0U ? bench::digest(message->md_entry_buyer.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->md_entry_seller.get()) != 0x0U ? bench::digest(message->md_entry_seller.get()) : std::uint64_t{0});
            checksum += bench::digest(message->trade_date.get());
            checksum += (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? bench::digest(message->md_entry_timestamp.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? bench::digest(message->rpt_seq.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->seller_days.get()) != 0x0U ? bench::digest(message->seller_days.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->md_entry_interest_rate.integer()) != 0x0ULL ? bench::digest(message->md_entry_interest_rate.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->trd_sub_type.get()) != 0x0U ? bench::digest(message->trd_sub_type.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 55) {
            [[maybe_unused]] const auto* message = protocol::ExecutionSummary55Message::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->aggressor_side.get());
            checksum += bench::digest(message->last_px.integer());
            checksum += bench::digest(message->fill_qty.get());
            checksum += (static_cast<std::uint64_t>(message->traded_hidden_qty.get()) != 0x08000000000000000ULL ? bench::digest(message->traded_hidden_qty.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->cxl_qty.get()) != 0x08000000000000000ULL ? bench::digest(message->cxl_qty.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->aggressor_time.get()) != 0x0ULL ? bench::digest(message->aggressor_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? bench::digest(message->rpt_seq.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? bench::digest(message->md_entry_timestamp.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 56) {
            [[maybe_unused]] const auto* message = protocol::ExecutionStatistics56Message::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->match_event_indicator.LastTradeMsg());
            checksum += bench::digest(message->match_event_indicator.LastVolumeMsg());
            checksum += bench::digest(message->match_event_indicator.LastQuoteMsg());
            checksum += bench::digest(message->match_event_indicator.LastStatsMsg());
            checksum += bench::digest(message->match_event_indicator.LastImpliedMsg());
            checksum += bench::digest(message->match_event_indicator.RecoveryMsg());
            checksum += bench::digest(message->match_event_indicator.EndOfEvent());
            checksum += bench::digest(message->trading_session_id.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->trade_volume.get());
            checksum += (static_cast<std::uint64_t>(message->vwap_px.integer()) != 0x08000000000000000ULL ? bench::digest(message->vwap_px.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->net_chg_prev_day.integer()) != 0x08000000000000000ULL ? bench::digest(message->net_chg_prev_day.integer()) : std::uint64_t{0});
            checksum += bench::digest(message->number_of_trades.get());
            checksum += (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? bench::digest(message->md_entry_timestamp.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? bench::digest(message->rpt_seq.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 57) {
            [[maybe_unused]] const auto* message = protocol::TradeBust57Message::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->match_event_indicator.LastTradeMsg());
            checksum += bench::digest(message->match_event_indicator.LastVolumeMsg());
            checksum += bench::digest(message->match_event_indicator.LastQuoteMsg());
            checksum += bench::digest(message->match_event_indicator.LastStatsMsg());
            checksum += bench::digest(message->match_event_indicator.LastImpliedMsg());
            checksum += bench::digest(message->match_event_indicator.RecoveryMsg());
            checksum += bench::digest(message->match_event_indicator.EndOfEvent());
            checksum += bench::digest(message->trading_session_id.get());
            checksum += bench::digest(message->md_future_price.integer());
            checksum += bench::digest(message->md_entry_size.get());
            checksum += bench::digest(message->trade_id.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? bench::digest(message->md_entry_timestamp.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? bench::digest(message->rpt_seq.get()) : std::uint64_t{0});
        } else if (iterator.template_id == 71) {
            [[maybe_unused]] const auto* message = protocol::SnapshotFullRefreshOrdersMbO71Message::parse(iterator.message);
            checksum += bench::digest(message->security_id.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("B3.B3Derivatives.BinaryUmdf.Sbe.v1.8", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
