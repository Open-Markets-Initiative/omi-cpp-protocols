// Nasdaq.NsmEquities.Qbbo.Itch.v2.1 benchmark, through the Advanced session layer: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/nsmequities/qbbo/itch/v2.1.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/advanced/nasdaq/nsmequities/qbbo/itch/v2.1/messages/session.hpp"

namespace protocol = ::nasdaq::nsmequities::qbbo::itch::v2_1;

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
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.time_stamp.get().value());
        checksum += bench::digest(message.fields.event_code.get().value());
    }

    void on_message(const protocol::stock_directory_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.time_stamp.get().value());
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
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.time_stamp.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.security_class.get().value());
        checksum += bench::digest(message.fields.current_trading_state.get().value());
        checksum += bench::digest(message.fields.reason.get().value());
    }

    void on_message(const protocol::reg_sho_restriction_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.time_stamp.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.reg_sho_action.get().value());
    }

    void on_message(const protocol::mwcb_decline_level_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.time_stamp.get().value());
        checksum += bench::digest(message.fields.level_1.get().value());
        checksum += bench::digest(message.fields.level_2.get().value());
        checksum += bench::digest(message.fields.level_3.get().value());
    }

    void on_message(const protocol::mwcb_breach_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.time_stamp.get().value());
        checksum += bench::digest(message.fields.breached_level.get().value());
    }

    void on_message(const protocol::operational_halt_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.time_stamp.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.market_code.get().value());
        checksum += bench::digest(message.fields.operational_halt_action.get().value());
    }

    void on_message(const protocol::bbo_quotation_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.time_stamp.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.security_class.get().value());
        checksum += bench::digest(message.fields.best_bid_price.get().value());
        checksum += bench::digest(message.fields.best_bid_size.get().value());
        checksum += bench::digest(message.fields.best_offer_price.get().value());
        checksum += bench::digest(message.fields.best_offer_size.get().value());
    }

    void on_message(const protocol::price_improvement_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking.get().value());
        checksum += bench::digest(message.fields.time_stamp.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.interest_flag.get().value());
    }

    void on_message(const protocol::ipo_quoting_period_update_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking.get().value());
        checksum += bench::digest(message.fields.time_stamp.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.ipo_quotation_release_time.get().value());
        checksum += bench::digest(message.fields.ipo_quotation_release_qualifier.get().value());
        checksum += bench::digest(message.fields.ipo_price.get().value());
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
    return bench::run("Nasdaq.NsmEquities.Qbbo.Itch.v2.1", "advanced", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
