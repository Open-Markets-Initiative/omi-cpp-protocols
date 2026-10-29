// Nasdaq.NsmEquities.TotalView.Itch.v5.0.2017 benchmark, through the Advanced session layer: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/nsmequities/totalview/itch/v5.0.2017.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/advanced/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/session.hpp"

namespace protocol = ::nasdaq::nsmequities::totalview::itch::v5_0_2017;

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
        checksum += bench::digest(message.fields.stock_locate.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.event_code.get().value());
    }

    void on_message(const protocol::stock_directory_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.stock_locate.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.market_category.get().value());
        checksum += bench::digest(message.fields.financial_status_indicator.get().value());
        checksum += bench::digest(message.fields.round_lot_size.get().value());
        checksum += bench::digest(message.fields.round_lots_only.get().value());
        checksum += bench::digest(message.fields.issue_classification.get().value());
        checksum += bench::digest(message.fields.issue_sub_type.get().value());
        checksum += bench::digest(message.fields.authenticity.get().value());
        checksum += bench::digest(message.fields.short_sale_threshold_indicator.get().value());
        checksum += bench::digest(message.fields.ipo_flag.get().value());
        checksum += bench::digest(message.fields.luld_reference_price_tier.get().value());
        checksum += bench::digest(message.fields.etp_flag.get().value());
        checksum += bench::digest(message.fields.etp_leverage_factor.get().value());
        checksum += bench::digest(message.fields.inverse_indicator.get().value());
    }

    void on_message(const protocol::stock_trading_action_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.stock_locate.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.trading_state.get().value());
        checksum += bench::digest(message.fields.reserved.get().value());
        checksum += bench::digest(message.fields.reason_code.get().value());
    }

    void on_message(const protocol::reg_sho_short_sale_price_test_restricted_indicator_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.locate_code.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.reg_sho_action.get().value());
    }

    void on_message(const protocol::market_participant_position_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.stock_locate.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.mpid.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.primary_market_maker.get().value());
        checksum += bench::digest(message.fields.market_maker_mode.get().value());
        checksum += bench::digest(message.fields.market_participant_state.get().value());
    }

    void on_message(const protocol::mwcb_decline_level_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.stock_locate.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.level_1.get().value());
        checksum += bench::digest(message.fields.level_2.get().value());
        checksum += bench::digest(message.fields.level_3.get().value());
    }

    void on_message(const protocol::mwcb_status_level_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.stock_locate.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.breached_level.get().value());
    }

    void on_message(const protocol::ipo_quoting_period_update& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.stock_locate.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.ipo_quotation_release_time.get().value());
        checksum += bench::digest(message.fields.ipo_quotation_release_qualifier.get().value());
        checksum += bench::digest(message.fields.ipo_price.get().value());
    }

    void on_message(const protocol::luld_auction_collar_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.stock_locate.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.auction_collar_reference_price.get().value());
        checksum += bench::digest(message.fields.upper_auction_collar_price.get().value());
        checksum += bench::digest(message.fields.lower_auction_collar_price.get().value());
        checksum += bench::digest(message.fields.auction_collar_extension.get().value());
    }

    void on_message(const protocol::add_order_no_mpid_attribution_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.stock_locate.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.order_reference_number.get().value());
        checksum += bench::digest(message.fields.buy_sell_indicator.get().value());
        checksum += bench::digest(message.fields.shares.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.price.get().value());
    }

    void on_message(const protocol::add_order_with_mpid_attribution_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.stock_locate.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.order_reference_number.get().value());
        checksum += bench::digest(message.fields.buy_sell_indicator.get().value());
        checksum += bench::digest(message.fields.shares.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.price.get().value());
        checksum += bench::digest(message.fields.attribution.get().value());
    }

    void on_message(const protocol::order_executed_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.stock_locate.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.order_reference_number.get().value());
        checksum += bench::digest(message.fields.executed_shares.get().value());
        checksum += bench::digest(message.fields.match_number.get().value());
    }

    void on_message(const protocol::order_executed_with_price_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.stock_locate.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.order_reference_number.get().value());
        checksum += bench::digest(message.fields.executed_shares.get().value());
        checksum += bench::digest(message.fields.match_number.get().value());
        checksum += bench::digest(message.fields.printable.get().value());
        checksum += bench::digest(message.fields.execution_price.get().value());
    }

    void on_message(const protocol::order_cancel_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.stock_locate.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.order_reference_number.get().value());
        checksum += bench::digest(message.fields.canceled_shares.get().value());
    }

    void on_message(const protocol::order_delete_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.stock_locate.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.order_reference_number.get().value());
    }

    void on_message(const protocol::order_replace_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.stock_locate.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.original_order_reference_number.get().value());
        checksum += bench::digest(message.fields.new_order_reference_number.get().value());
        checksum += bench::digest(message.fields.shares.get().value());
        checksum += bench::digest(message.fields.price.get().value());
    }

    void on_message(const protocol::non_cross_trade_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.stock_locate.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.order_reference_number.get().value());
        checksum += bench::digest(message.fields.buy_sell_indicator.get().value());
        checksum += bench::digest(message.fields.shares.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.price.get().value());
        checksum += bench::digest(message.fields.match_number.get().value());
    }

    void on_message(const protocol::cross_trade_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.stock_locate.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.cross_shares.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.cross_price.get().value());
        checksum += bench::digest(message.fields.match_number.get().value());
        checksum += bench::digest(message.fields.cross_type.get().value());
    }

    void on_message(const protocol::broken_trade_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.stock_locate.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.match_number.get().value());
    }

    void on_message(const protocol::net_order_imbalance_indicator_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.stock_locate.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.paired_shares.get().value());
        checksum += bench::digest(message.fields.imbalance_shares.get().value());
        checksum += bench::digest(message.fields.imbalance_direction.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.far_price.get().value());
        checksum += bench::digest(message.fields.near_price.get().value());
        checksum += bench::digest(message.fields.current_reference_price.get().value());
        checksum += bench::digest(message.fields.cross_type.get().value());
        checksum += bench::digest(message.fields.price_variation_indicator.get().value());
    }

    void on_message(const protocol::retail_interest_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.stock_locate.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.interest_flag.get().value());
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
    return bench::run("Nasdaq.NsmEquities.TotalView.Itch.v5.0.2017", "advanced", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
