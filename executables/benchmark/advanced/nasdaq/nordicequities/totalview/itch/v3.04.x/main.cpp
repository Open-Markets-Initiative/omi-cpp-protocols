// Nasdaq.NordicEquities.TotalView.Itch.v3.04.X benchmark, through the Advanced session layer: every value it reads from every message of the simulated
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
#include "cpp/binary/advanced/nasdaq/nordicequities/totalview/itch/v3.04.x/messages/session.hpp"

namespace protocol = ::nasdaq::nordicequities::totalview::itch::v3_04_x;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::packet_header& header, const packet::Frame&) {
        checksum += bench::digest(header.session.get().value());
        checksum += bench::digest(header.sequence_number.get().value());
        checksum += bench::digest(header.message_count.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::packet_header&) {
        ++index;
    }

    void on_message(const protocol::system_event_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.event_code.get().value());
    }

    void on_message(const protocol::order_book_trading_action_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.order_book.get().value());
        checksum += bench::digest(message.fields.symbol_state.get().value());
        checksum += bench::digest(message.fields.extension.get().value());
        checksum += bench::digest(message.fields.reason.get().value());
    }

    void on_message(const protocol::order_book_directory_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.order_book.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.isin.get().value());
        checksum += bench::digest(message.fields.financial_product.get().value());
        checksum += bench::digest(message.fields.trading_currency.get().value());
        checksum += bench::digest(message.fields.mic.get().value());
        checksum += bench::digest(message.fields.market_segment_id.get().value());
        checksum += bench::digest(message.fields.note_codes_bit_field_1.has_nm_new_market_company());
        checksum += bench::digest(message.fields.note_codes_bit_field_1.has_xr_excluding_participating_in_rights());
        checksum += bench::digest(message.fields.note_codes_bit_field_1.has_sp_excluding_participating_in_split());
        checksum += bench::digest(message.fields.note_codes_bit_field_1.has_po_company_subject_to_public_offer());
        checksum += bench::digest(message.fields.note_codes_bit_field_1.has_ud_under_drawing());
        checksum += bench::digest(message.fields.note_codes_bit_field_1.has_sr_excluding_comb_split_and_issue_rights());
        checksum += bench::digest(message.fields.note_codes_bit_field_1.has_ul_un_listed());
        checksum += bench::digest(message.fields.note_codes_bit_field_1.has_wi_when_issued());
        checksum += bench::digest(message.fields.note_codes_bit_field_2.has_br_company_bankruptcy());
        checksum += bench::digest(message.fields.note_codes_bit_field_2.has_su_suspension());
        checksum += bench::digest(message.fields.note_codes_bit_field_2.has_rl_removal_from_listing_in_process());
        checksum += bench::digest(message.fields.note_codes_bit_field_2.has_sl_other_surveillance_list_reason());
        checksum += bench::digest(message.fields.note_codes_bit_field_2.has_to_a_significant_reverse_takeover_pending());
        checksum += bench::digest(message.fields.note_codes_bit_field_2.has_cs_cent_shares());
        checksum += bench::digest(message.fields.note_codes_bit_field_2.has_rs_reversed_split());
        checksum += bench::digest(message.fields.note_codes_bit_field_2.has_bs_excluding_comb_bonus_split());
        checksum += bench::digest(message.fields.note_codes_bit_field_3.has_ss_excluding_comb_split_redemption_share());
        checksum += bench::digest(message.fields.note_codes_bit_field_3.has_fn_first_north_company());
        checksum += bench::digest(message.fields.note_codes_bit_field_3.has_ob_observation_status());
        checksum += bench::digest(message.fields.note_codes_bit_field_3.has_xd_excluding_dividend());
        checksum += bench::digest(message.fields.note_codes_bit_field_3.has_fe_foreign_non_eueea_entity());
        checksum += bench::digest(message.fields.note_codes_bit_field_3.has_so_sold_out_buy_back());
        checksum += bench::digest(message.fields.note_codes_bit_field_3.has_sk_soft_knock());
        checksum += bench::digest(message.fields.note_codes_bit_field_3.has_kb_knock_out_buy_back());
        checksum += bench::digest(message.fields.note_codes_bit_field_4.has_bb_buy_back());
        checksum += bench::digest(message.fields.note_codes_bit_field_4.has_ce_capped_by_esma());
        checksum += bench::digest(message.fields.note_codes_bit_field_4.has_pd_price_discrepancy_historical_average_share_classes());
        checksum += bench::digest(message.fields.note_codes_bit_field_4.has_sm_stressed_market());
        checksum += bench::digest(message.fields.note_codes_bit_field_4.has_ew_market_wide_exceptional_circumstance());
        checksum += bench::digest(message.fields.note_codes_bit_field_5.has_em_exceptional_circumstances_related_to_market_maker());
        checksum += bench::digest(message.fields.note_codes_bit_field_5.has_un_underlying_not_quoted());
        checksum += bench::digest(message.fields.note_codes_bit_field_5.has_da_digital_asset());
        checksum += bench::digest(message.fields.note_codes_bit_field_5.has_kn_knock_out_buy_back_into_next_trading_day());
        checksum += bench::digest(message.fields.round_lot_size.get().value());
        checksum += bench::digest(message.fields.nordic_mid_mic.get().value());
        checksum += bench::digest(message.fields.aod_mic.get().value());
        checksum += bench::digest(message.fields.notation_of_qty.get().value());
        checksum += bench::digest(message.fields.notional_amount.get().value());
        checksum += bench::digest(message.fields.currency.get().value());
        checksum += bench::digest(message.fields.price_notation.get().value());
        checksum += bench::digest(message.fields.multiplier_for_calculating_quantity_in_measurement_unit.get().value());
        checksum += bench::digest(message.fields.pure_stream_mic.get().value());
    }

    void on_message(const protocol::add_order_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.order_reference_number.get().value());
        checksum += bench::digest(message.fields.buy_sell_indicator.get().value());
        checksum += bench::digest(message.fields.quantity.get().value());
        checksum += bench::digest(message.fields.order_book.get().value());
        checksum += bench::digest(message.fields.price.get().value());
    }

    void on_message(const protocol::add_order_mpid_attribution_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.order_reference_number.get().value());
        checksum += bench::digest(message.fields.buy_sell_indicator.get().value());
        checksum += bench::digest(message.fields.quantity.get().value());
        checksum += bench::digest(message.fields.order_book.get().value());
        checksum += bench::digest(message.fields.price.get().value());
        checksum += bench::digest(message.fields.attribution.get().value());
    }

    void on_message(const protocol::order_executed_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.order_reference_number.get().value());
        checksum += bench::digest(message.fields.executed_quantity.get().value());
        checksum += bench::digest(message.fields.match_number.get().value());
        checksum += bench::digest(message.fields.mpid.get().value());
        checksum += bench::digest(message.fields.mpid_counterparty.get().value());
    }

    void on_message(const protocol::order_executed_with_price_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.order_reference_number.get().value());
        checksum += bench::digest(message.fields.executed_quantity.get().value());
        checksum += bench::digest(message.fields.match_number.get().value());
        checksum += bench::digest(message.fields.printable.get().value());
        checksum += bench::digest(message.fields.trade_price.get().value());
        checksum += bench::digest(message.fields.mpid_owner.get().value());
        checksum += bench::digest(message.fields.mpid_counterparty.get().value());
    }

    void on_message(const protocol::order_cancel_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.order_reference_number.get().value());
        checksum += bench::digest(message.fields.canceled_quantity.get().value());
    }

    void on_message(const protocol::order_delete_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.order_reference_number.get().value());
    }

    void on_message(const protocol::order_book_flush_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.order_book.get().value());
    }

    void on_message(const protocol::order_replace_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.original_order_reference_number.get().value());
        checksum += bench::digest(message.fields.new_order_reference_number.get().value());
        checksum += bench::digest(message.fields.quantity.get().value());
        checksum += bench::digest(message.fields.price.get().value());
    }

    void on_message(const protocol::trade_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.order_reference_number.get().value());
        checksum += bench::digest(message.fields.trade_type.get().value());
        checksum += bench::digest(message.fields.quantity.get().value());
        checksum += bench::digest(message.fields.order_book.get().value());
        checksum += bench::digest(message.fields.match_number.get().value());
        checksum += bench::digest(message.fields.trade_price.get().value());
        checksum += bench::digest(message.fields.participant_id_buyer.get().value());
        checksum += bench::digest(message.fields.participant_id_seller.get().value());
    }

    void on_message(const protocol::cross_trade_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.quantity.get().value());
        checksum += bench::digest(message.fields.order_book.get().value());
        checksum += bench::digest(message.fields.cross_price.get().value());
        checksum += bench::digest(message.fields.match_number.get().value());
        checksum += bench::digest(message.fields.cross_type.get().value());
        checksum += bench::digest(message.fields.number_of_trades.get().value());
    }

    void on_message(const protocol::broken_trade_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.match_number.get().value());
    }

    void on_message(const protocol::noii_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.paired_quantity.get().value());
        checksum += bench::digest(message.fields.imbalance_quantity.get().value());
        checksum += bench::digest(message.fields.imbalance_direction.get().value());
        checksum += bench::digest(message.fields.order_book.get().value());
        checksum += bench::digest(message.fields.equilibrium_price.get().value());
        checksum += bench::digest(message.fields.cross_type.get().value());
        checksum += bench::digest(message.fields.best_bid_price.get().value());
        checksum += bench::digest(message.fields.best_bid_quantity.get().value());
        checksum += bench::digest(message.fields.best_ask_price.get().value());
        checksum += bench::digest(message.fields.best_ask_quantity.get().value());
    }

    void on_message(const protocol::moii_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.paired_quantity.get().value());
        checksum += bench::digest(message.fields.order_book.get().value());
        checksum += bench::digest(message.fields.equilibrium_price.get().value());
        checksum += bench::digest(message.fields.cross_type.get().value());
        checksum += bench::digest(message.fields.cross_level.get().value());
    }

    void on_message(const protocol::execution_summary_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.order_book.get().value());
        checksum += bench::digest(message.fields.aggressing_side.get().value());
        checksum += bench::digest(message.fields.quantity.get().value());
        checksum += bench::digest(message.fields.hidden_quantity.get().value());
        checksum += bench::digest(message.fields.stp_cancel_quantity.get().value());
        checksum += bench::digest(message.fields.far_price.get().value());
        checksum += bench::digest(message.fields.add_quantity.get().value());
        checksum += bench::digest(message.fields.number_of_lit_executions.get().value());
    }
};

// The values Advanced reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;
    protocol::process_segment(reader, frame.payload, frame.payload_len, 0, frame);
    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nasdaq.NordicEquities.TotalView.Itch.v3.04.X", "advanced", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
