// Nasdaq.NordicEquities.TotalView.Itch.v3.04.X benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/nordicequities/totalview/itch/v3.04.x.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/nasdaq/nordicequities/totalview/itch/v3.04.x/definitions.hpp"

namespace protocol = ::nasdaq::nordicequities::totalview::itch::v3_04_x;

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
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->event_code.get());
        } else if (iterator.message_type == protocol::OrderBookTradingActionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderBookTradingActionMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->order_book.get());
            checksum += bench::digest(message->symbol_state.get());
            checksum += bench::digest(message->extension.get());
            checksum += bench::digest(message->reason.get());
        } else if (iterator.message_type == protocol::OrderBookDirectoryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderBookDirectoryMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->order_book.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->isin.get());
            checksum += bench::digest(message->financial_product.get());
            checksum += bench::digest(message->trading_currency.get());
            checksum += bench::digest(message->mic.get());
            checksum += bench::digest(message->market_segment_id.get());
            checksum += bench::digest(message->note_codes_bit_field_1.NmNewMarketCompany());
            checksum += bench::digest(message->note_codes_bit_field_1.XrExcludingParticipatingInRights());
            checksum += bench::digest(message->note_codes_bit_field_1.SpExcludingParticipatingInSplit());
            checksum += bench::digest(message->note_codes_bit_field_1.PoCompanySubjectToPublicOffer());
            checksum += bench::digest(message->note_codes_bit_field_1.UdUnderDrawing());
            checksum += bench::digest(message->note_codes_bit_field_1.SrExcludingCombSplitAndIssueRights());
            checksum += bench::digest(message->note_codes_bit_field_1.UlUnListed());
            checksum += bench::digest(message->note_codes_bit_field_1.WiWhenIssued());
            checksum += bench::digest(message->note_codes_bit_field_2.BrCompanyBankruptcy());
            checksum += bench::digest(message->note_codes_bit_field_2.SuSuspension());
            checksum += bench::digest(message->note_codes_bit_field_2.RlRemovalFromListingInProcess());
            checksum += bench::digest(message->note_codes_bit_field_2.SlOtherSurveillanceListReason());
            checksum += bench::digest(message->note_codes_bit_field_2.ToASignificantReverseTakeoverPending());
            checksum += bench::digest(message->note_codes_bit_field_2.CsCentShares());
            checksum += bench::digest(message->note_codes_bit_field_2.RsReversedSplit());
            checksum += bench::digest(message->note_codes_bit_field_2.BsExcludingCombBonusSplit());
            checksum += bench::digest(message->note_codes_bit_field_3.SsExcludingCombSplitRedemptionShare());
            checksum += bench::digest(message->note_codes_bit_field_3.FnFirstNorthCompany());
            checksum += bench::digest(message->note_codes_bit_field_3.ObObservationStatus());
            checksum += bench::digest(message->note_codes_bit_field_3.XdExcludingDividend());
            checksum += bench::digest(message->note_codes_bit_field_3.FeForeignNonEueeaEntity());
            checksum += bench::digest(message->note_codes_bit_field_3.SoSoldOutBuyBack());
            checksum += bench::digest(message->note_codes_bit_field_3.SkSoftKnock());
            checksum += bench::digest(message->note_codes_bit_field_3.KbKnockOutBuyBack());
            checksum += bench::digest(message->note_codes_bit_field_4.BbBuyBack());
            checksum += bench::digest(message->note_codes_bit_field_4.CeCappedByEsma());
            checksum += bench::digest(message->note_codes_bit_field_4.PdPriceDiscrepancyHistoricalAverageShareClasses());
            checksum += bench::digest(message->note_codes_bit_field_4.SmStressedMarket());
            checksum += bench::digest(message->note_codes_bit_field_4.EwMarketWideExceptionalCircumstance());
            checksum += bench::digest(message->note_codes_bit_field_5.EmExceptionalCircumstancesRelatedToMarketMaker());
            checksum += bench::digest(message->note_codes_bit_field_5.UnUnderlyingNotQuoted());
            checksum += bench::digest(message->note_codes_bit_field_5.DaDigitalAsset());
            checksum += bench::digest(message->note_codes_bit_field_5.KnKnockOutBuyBackIntoNextTradingDay());
            checksum += bench::digest(message->round_lot_size.get());
            checksum += bench::digest(message->nordic_mid_mic.get());
            checksum += bench::digest(message->aod_mic.get());
            checksum += bench::digest(message->notation_of_qty.get());
            checksum += bench::digest(message->notional_amount.integer());
            checksum += bench::digest(message->currency.get());
            checksum += bench::digest(message->price_notation.get());
            checksum += bench::digest(message->multiplier_for_calculating_quantity_in_measurement_unit.integer());
            checksum += bench::digest(message->pure_stream_mic.get());
        } else if (iterator.message_type == protocol::AddOrderMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->order_reference_number.get());
            checksum += bench::digest(message->buy_sell_indicator.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->order_book.get());
            checksum += bench::digest(message->price.integer());
        } else if (iterator.message_type == protocol::AddOrderMpidAttributionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderMpidAttributionMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->order_reference_number.get());
            checksum += bench::digest(message->buy_sell_indicator.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->order_book.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->attribution.get());
        } else if (iterator.message_type == protocol::OrderExecutedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderExecutedMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->order_reference_number.get());
            checksum += bench::digest(message->executed_quantity.get());
            checksum += bench::digest(message->match_number.get());
            checksum += bench::digest(message->mpid.get());
            checksum += bench::digest(message->mpid_counterparty.get());
        } else if (iterator.message_type == protocol::OrderExecutedWithPriceMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderExecutedWithPriceMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->order_reference_number.get());
            checksum += bench::digest(message->executed_quantity.get());
            checksum += bench::digest(message->match_number.get());
            checksum += bench::digest(message->printable.get());
            checksum += bench::digest(message->trade_price.integer());
            checksum += bench::digest(message->mpid_owner.get());
            checksum += bench::digest(message->mpid_counterparty.get());
        } else if (iterator.message_type == protocol::OrderCancelMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderCancelMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->order_reference_number.get());
            checksum += bench::digest(message->canceled_quantity.get());
        } else if (iterator.message_type == protocol::OrderDeleteMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderDeleteMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->order_reference_number.get());
        } else if (iterator.message_type == protocol::OrderBookFlushMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderBookFlushMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->order_book.get());
        } else if (iterator.message_type == protocol::OrderReplaceMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderReplaceMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->original_order_reference_number.get());
            checksum += bench::digest(message->new_order_reference_number.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->price.integer());
        } else if (iterator.message_type == protocol::TradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->order_reference_number.get());
            checksum += bench::digest(message->trade_type.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->order_book.get());
            checksum += bench::digest(message->match_number.get());
            checksum += bench::digest(message->trade_price.integer());
            checksum += bench::digest(message->participant_id_buyer.get());
            checksum += bench::digest(message->participant_id_seller.get());
        } else if (iterator.message_type == protocol::CrossTradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::CrossTradeMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->order_book.get());
            checksum += bench::digest(message->cross_price.integer());
            checksum += bench::digest(message->match_number.get());
            checksum += bench::digest(message->cross_type.get());
            checksum += bench::digest(message->number_of_trades.get());
        } else if (iterator.message_type == protocol::BrokenTradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::BrokenTradeMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->match_number.get());
        } else if (iterator.message_type == protocol::NoiiMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::NoiiMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->paired_quantity.get());
            checksum += bench::digest(message->imbalance_quantity.get());
            checksum += bench::digest(message->imbalance_direction.get());
            checksum += bench::digest(message->order_book.get());
            checksum += bench::digest(message->equilibrium_price.integer());
            checksum += bench::digest(message->cross_type.get());
            checksum += bench::digest(message->best_bid_price.integer());
            checksum += bench::digest(message->best_bid_quantity.get());
            checksum += bench::digest(message->best_ask_price.integer());
            checksum += bench::digest(message->best_ask_quantity.get());
        } else if (iterator.message_type == protocol::MoiiMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::MoiiMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->paired_quantity.get());
            checksum += bench::digest(message->order_book.get());
            checksum += bench::digest(message->equilibrium_price.integer());
            checksum += bench::digest(message->cross_type.get());
            checksum += bench::digest(message->cross_level.get());
        } else if (iterator.message_type == protocol::ExecutionSummaryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ExecutionSummaryMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->order_book.get());
            checksum += bench::digest(message->aggressing_side.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->hidden_quantity.get());
            checksum += bench::digest(message->stp_cancel_quantity.get());
            checksum += bench::digest(message->far_price.integer());
            checksum += bench::digest(message->add_quantity.get());
            checksum += bench::digest(message->number_of_lit_executions.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nasdaq.NordicEquities.TotalView.Itch.v3.04.X", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
