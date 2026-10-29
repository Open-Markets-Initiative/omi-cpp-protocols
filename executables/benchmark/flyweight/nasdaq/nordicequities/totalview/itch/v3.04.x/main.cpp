// Nasdaq.NordicEquities.TotalView.Itch.v3.04.X benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/nordicequities/totalview/itch/v3.04.x.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/nasdaq/nordicequities/totalview/itch/v3.04.x/definitions.hpp"

namespace protocol = ::nasdaq::nordicequities::totalview::itch::v3_04_x;

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
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.event_code());
    }

    void on(const protocol::OrderBookTradingActionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.order_book());
        checksum += bench::digest(message.symbol_state());
        checksum += bench::digest(message.extension());
        checksum += bench::digest(message.reason());
    }

    void on(const protocol::OrderBookDirectoryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.order_book());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.isin());
        checksum += bench::digest(message.financial_product());
        checksum += bench::digest(message.trading_currency());
        checksum += bench::digest(message.mic());
        checksum += bench::digest(message.market_segment_id());
        checksum += bench::digest(message.note_codes_bit_field_1().nm_new_market_company());
        checksum += bench::digest(message.note_codes_bit_field_1().xr_excluding_participating_in_rights());
        checksum += bench::digest(message.note_codes_bit_field_1().sp_excluding_participating_in_split());
        checksum += bench::digest(message.note_codes_bit_field_1().po_company_subject_to_public_offer());
        checksum += bench::digest(message.note_codes_bit_field_1().ud_under_drawing());
        checksum += bench::digest(message.note_codes_bit_field_1().sr_excluding_comb_split_and_issue_rights());
        checksum += bench::digest(message.note_codes_bit_field_1().ul_un_listed());
        checksum += bench::digest(message.note_codes_bit_field_1().wi_when_issued());
        checksum += bench::digest(message.note_codes_bit_field_2().br_company_bankruptcy());
        checksum += bench::digest(message.note_codes_bit_field_2().su_suspension());
        checksum += bench::digest(message.note_codes_bit_field_2().rl_removal_from_listing_in_process());
        checksum += bench::digest(message.note_codes_bit_field_2().sl_other_surveillance_list_reason());
        checksum += bench::digest(message.note_codes_bit_field_2().to_a_significant_reverse_takeover_pending());
        checksum += bench::digest(message.note_codes_bit_field_2().cs_cent_shares());
        checksum += bench::digest(message.note_codes_bit_field_2().rs_reversed_split());
        checksum += bench::digest(message.note_codes_bit_field_2().bs_excluding_comb_bonus_split());
        checksum += bench::digest(message.note_codes_bit_field_3().ss_excluding_comb_split_redemption_share());
        checksum += bench::digest(message.note_codes_bit_field_3().fn_first_north_company());
        checksum += bench::digest(message.note_codes_bit_field_3().ob_observation_status());
        checksum += bench::digest(message.note_codes_bit_field_3().xd_excluding_dividend());
        checksum += bench::digest(message.note_codes_bit_field_3().fe_foreign_non_eueea_entity());
        checksum += bench::digest(message.note_codes_bit_field_3().so_sold_out_buy_back());
        checksum += bench::digest(message.note_codes_bit_field_3().sk_soft_knock());
        checksum += bench::digest(message.note_codes_bit_field_3().kb_knock_out_buy_back());
        checksum += bench::digest(message.note_codes_bit_field_4().bb_buy_back());
        checksum += bench::digest(message.note_codes_bit_field_4().ce_capped_by_esma());
        checksum += bench::digest(message.note_codes_bit_field_4().pd_price_discrepancy_historical_average_share_classes());
        checksum += bench::digest(message.note_codes_bit_field_4().sm_stressed_market());
        checksum += bench::digest(message.note_codes_bit_field_4().ew_market_wide_exceptional_circumstance());
        checksum += bench::digest(message.note_codes_bit_field_5().em_exceptional_circumstances_related_to_market_maker());
        checksum += bench::digest(message.note_codes_bit_field_5().un_underlying_not_quoted());
        checksum += bench::digest(message.note_codes_bit_field_5().da_digital_asset());
        checksum += bench::digest(message.note_codes_bit_field_5().kn_knock_out_buy_back_into_next_trading_day());
        checksum += bench::digest(message.round_lot_size());
        checksum += bench::digest(message.nordic_mid_mic());
        checksum += bench::digest(message.aod_mic());
        checksum += bench::digest(message.notation_of_qty());
        checksum += bench::digest(message.notional_amount().mantissa());
        checksum += bench::digest(message.currency());
        checksum += bench::digest(message.price_notation());
        checksum += bench::digest(message.multiplier_for_calculating_quantity_in_measurement_unit().mantissa());
        checksum += bench::digest(message.pure_stream_mic());
    }

    void on(const protocol::AddOrderMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.order_reference_number());
        checksum += bench::digest(message.buy_sell_indicator());
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.order_book());
        checksum += bench::digest(message.price().mantissa());
    }

    void on(const protocol::AddOrderMpidAttributionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.order_reference_number());
        checksum += bench::digest(message.buy_sell_indicator());
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.order_book());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.attribution());
    }

    void on(const protocol::OrderExecutedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.order_reference_number());
        checksum += bench::digest(message.executed_quantity());
        checksum += bench::digest(message.match_number());
        checksum += bench::digest(message.mpid());
        checksum += bench::digest(message.mpid_counterparty());
    }

    void on(const protocol::OrderExecutedWithPriceMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.order_reference_number());
        checksum += bench::digest(message.executed_quantity());
        checksum += bench::digest(message.match_number());
        checksum += bench::digest(message.printable());
        checksum += bench::digest(message.trade_price().mantissa());
        checksum += bench::digest(message.mpid_owner());
        checksum += bench::digest(message.mpid_counterparty());
    }

    void on(const protocol::OrderCancelMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.order_reference_number());
        checksum += bench::digest(message.canceled_quantity());
    }

    void on(const protocol::OrderDeleteMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.order_reference_number());
    }

    void on(const protocol::OrderBookFlushMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.order_book());
    }

    void on(const protocol::OrderReplaceMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.original_order_reference_number());
        checksum += bench::digest(message.new_order_reference_number());
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.price().mantissa());
    }

    void on(const protocol::TradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.order_reference_number());
        checksum += bench::digest(message.trade_type());
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.order_book());
        checksum += bench::digest(message.match_number());
        checksum += bench::digest(message.trade_price().mantissa());
        checksum += bench::digest(message.participant_id_buyer());
        checksum += bench::digest(message.participant_id_seller());
    }

    void on(const protocol::CrossTradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.order_book());
        checksum += bench::digest(message.cross_price().mantissa());
        checksum += bench::digest(message.match_number());
        checksum += bench::digest(message.cross_type());
        checksum += bench::digest(message.number_of_trades());
    }

    void on(const protocol::BrokenTradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.match_number());
    }

    void on(const protocol::NoiiMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.paired_quantity());
        checksum += bench::digest(message.imbalance_quantity());
        checksum += bench::digest(message.imbalance_direction());
        checksum += bench::digest(message.order_book());
        checksum += bench::digest(message.equilibrium_price().mantissa());
        checksum += bench::digest(message.cross_type());
        checksum += bench::digest(message.best_bid_price().mantissa());
        checksum += bench::digest(message.best_bid_quantity());
        checksum += bench::digest(message.best_ask_price().mantissa());
        checksum += bench::digest(message.best_ask_quantity());
    }

    void on(const protocol::MoiiMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.paired_quantity());
        checksum += bench::digest(message.order_book());
        checksum += bench::digest(message.equilibrium_price().mantissa());
        checksum += bench::digest(message.cross_type());
        checksum += bench::digest(message.cross_level());
    }

    void on(const protocol::ExecutionSummaryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.tracking_number());
        checksum += bench::digest(message.order_book());
        checksum += bench::digest(message.aggressing_side());
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.hidden_quantity());
        checksum += bench::digest(message.stp_cancel_quantity());
        checksum += bench::digest(message.far_price().mantissa());
        checksum += bench::digest(message.add_quantity());
        checksum += bench::digest(message.number_of_lit_executions());
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
    return bench::run("Nasdaq.NordicEquities.TotalView.Itch.v3.04.X", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
