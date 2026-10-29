// Nasdaq.NordicEquities.TotalView.Itch.v3.04.X benchmark, through the Classes Packet: every value it reads from every message of the simulated
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
#include "cpp/binary/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/definitions.hpp"

namespace protocol = ::nasdaq::nordicequities::totalview::itch::v3_04_x;

namespace {

// The values the Classes Packet decodes from one datagram, folded into a checksum. A datagram it cannot
// decode is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::Packet packet;

    try {
        packet.decode(frame.payload, frame.payload_len);
    } catch (const protocol::DecodeError& error) {
        throw;
        return checksum;
    }

    checksum += bench::digest(packet.packet_header().session());
    checksum += bench::digest(packet.packet_header().sequence_number());
    checksum += bench::digest(packet.packet_header().message_count());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_header().message_length());
        checksum += bench::digest(each.message_header().message_type());

        if (const auto* message = dynamic_cast<const protocol::SystemEventMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).event_code());
        } else if (const auto* message = dynamic_cast<const protocol::OrderBookTradingActionMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).order_book());
            checksum += bench::digest((*message).symbol_state());
            checksum += bench::digest((*message).extension());
            checksum += bench::digest((*message).reason());
        } else if (const auto* message = dynamic_cast<const protocol::OrderBookDirectoryMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).order_book());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).isin());
            checksum += bench::digest((*message).financial_product());
            checksum += bench::digest((*message).trading_currency());
            checksum += bench::digest((*message).mic());
            checksum += bench::digest((*message).market_segment_id());
            checksum += bench::digest((*message).note_codes_bit_field_1().nm_new_market_company());
            checksum += bench::digest((*message).note_codes_bit_field_1().xr_excluding_participating_in_rights());
            checksum += bench::digest((*message).note_codes_bit_field_1().sp_excluding_participating_in_split());
            checksum += bench::digest((*message).note_codes_bit_field_1().po_company_subject_to_public_offer());
            checksum += bench::digest((*message).note_codes_bit_field_1().ud_under_drawing());
            checksum += bench::digest((*message).note_codes_bit_field_1().sr_excluding_comb_split_and_issue_rights());
            checksum += bench::digest((*message).note_codes_bit_field_1().ul_un_listed());
            checksum += bench::digest((*message).note_codes_bit_field_1().wi_when_issued());
            checksum += bench::digest((*message).note_codes_bit_field_2().br_company_bankruptcy());
            checksum += bench::digest((*message).note_codes_bit_field_2().su_suspension());
            checksum += bench::digest((*message).note_codes_bit_field_2().rl_removal_from_listing_in_process());
            checksum += bench::digest((*message).note_codes_bit_field_2().sl_other_surveillance_list_reason());
            checksum += bench::digest((*message).note_codes_bit_field_2().to_a_significant_reverse_takeover_pending());
            checksum += bench::digest((*message).note_codes_bit_field_2().cs_cent_shares());
            checksum += bench::digest((*message).note_codes_bit_field_2().rs_reversed_split());
            checksum += bench::digest((*message).note_codes_bit_field_2().bs_excluding_comb_bonus_split());
            checksum += bench::digest((*message).note_codes_bit_field_3().ss_excluding_comb_split_redemption_share());
            checksum += bench::digest((*message).note_codes_bit_field_3().fn_first_north_company());
            checksum += bench::digest((*message).note_codes_bit_field_3().ob_observation_status());
            checksum += bench::digest((*message).note_codes_bit_field_3().xd_excluding_dividend());
            checksum += bench::digest((*message).note_codes_bit_field_3().fe_foreign_non_eueea_entity());
            checksum += bench::digest((*message).note_codes_bit_field_3().so_sold_out_buy_back());
            checksum += bench::digest((*message).note_codes_bit_field_3().sk_soft_knock());
            checksum += bench::digest((*message).note_codes_bit_field_3().kb_knock_out_buy_back());
            checksum += bench::digest((*message).note_codes_bit_field_4().bb_buy_back());
            checksum += bench::digest((*message).note_codes_bit_field_4().ce_capped_by_esma());
            checksum += bench::digest((*message).note_codes_bit_field_4().pd_price_discrepancy_historical_average_share_classes());
            checksum += bench::digest((*message).note_codes_bit_field_4().sm_stressed_market());
            checksum += bench::digest((*message).note_codes_bit_field_4().ew_market_wide_exceptional_circumstance());
            checksum += bench::digest((*message).note_codes_bit_field_5().em_exceptional_circumstances_related_to_market_maker());
            checksum += bench::digest((*message).note_codes_bit_field_5().un_underlying_not_quoted());
            checksum += bench::digest((*message).note_codes_bit_field_5().da_digital_asset());
            checksum += bench::digest((*message).note_codes_bit_field_5().kn_knock_out_buy_back_into_next_trading_day());
            checksum += bench::digest((*message).round_lot_size());
            checksum += bench::digest((*message).nordic_mid_mic());
            checksum += bench::digest((*message).aod_mic());
            checksum += bench::digest((*message).notation_of_qty());
            checksum += bench::digest((*message).notional_amount().mantissa());
            checksum += bench::digest((*message).currency());
            checksum += bench::digest((*message).price_notation());
            checksum += bench::digest((*message).multiplier_for_calculating_quantity_in_measurement_unit().mantissa());
            checksum += bench::digest((*message).pure_stream_mic());
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).buy_sell_indicator());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).order_book());
            checksum += bench::digest((*message).price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderMpidAttributionMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).buy_sell_indicator());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).order_book());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).attribution());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).executed_quantity());
            checksum += bench::digest((*message).match_number());
            checksum += bench::digest((*message).mpid());
            checksum += bench::digest((*message).mpid_counterparty());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedWithPriceMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).executed_quantity());
            checksum += bench::digest((*message).match_number());
            checksum += bench::digest((*message).printable());
            checksum += bench::digest((*message).trade_price().mantissa());
            checksum += bench::digest((*message).mpid_owner());
            checksum += bench::digest((*message).mpid_counterparty());
        } else if (const auto* message = dynamic_cast<const protocol::OrderCancelMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).canceled_quantity());
        } else if (const auto* message = dynamic_cast<const protocol::OrderDeleteMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).order_reference_number());
        } else if (const auto* message = dynamic_cast<const protocol::OrderBookFlushMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).order_book());
        } else if (const auto* message = dynamic_cast<const protocol::OrderReplaceMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).original_order_reference_number());
            checksum += bench::digest((*message).new_order_reference_number());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::TradeMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).trade_type());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).order_book());
            checksum += bench::digest((*message).match_number());
            checksum += bench::digest((*message).trade_price().mantissa());
            checksum += bench::digest((*message).participant_id_buyer());
            checksum += bench::digest((*message).participant_id_seller());
        } else if (const auto* message = dynamic_cast<const protocol::CrossTradeMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).order_book());
            checksum += bench::digest((*message).cross_price().mantissa());
            checksum += bench::digest((*message).match_number());
            checksum += bench::digest((*message).cross_type());
            checksum += bench::digest((*message).number_of_trades());
        } else if (const auto* message = dynamic_cast<const protocol::BrokenTradeMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).match_number());
        } else if (const auto* message = dynamic_cast<const protocol::NoiiMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).paired_quantity());
            checksum += bench::digest((*message).imbalance_quantity());
            checksum += bench::digest((*message).imbalance_direction());
            checksum += bench::digest((*message).order_book());
            checksum += bench::digest((*message).equilibrium_price().mantissa());
            checksum += bench::digest((*message).cross_type());
            checksum += bench::digest((*message).best_bid_price().mantissa());
            checksum += bench::digest((*message).best_bid_quantity());
            checksum += bench::digest((*message).best_ask_price().mantissa());
            checksum += bench::digest((*message).best_ask_quantity());
        } else if (const auto* message = dynamic_cast<const protocol::MoiiMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).paired_quantity());
            checksum += bench::digest((*message).order_book());
            checksum += bench::digest((*message).equilibrium_price().mantissa());
            checksum += bench::digest((*message).cross_type());
            checksum += bench::digest((*message).cross_level());
        } else if (const auto* message = dynamic_cast<const protocol::ExecutionSummaryMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).order_book());
            checksum += bench::digest((*message).aggressing_side());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).hidden_quantity());
            checksum += bench::digest((*message).stp_cancel_quantity());
            checksum += bench::digest((*message).far_price().mantissa());
            checksum += bench::digest((*message).add_quantity());
            checksum += bench::digest((*message).number_of_lit_executions());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nasdaq.NordicEquities.TotalView.Itch.v3.04.X", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
