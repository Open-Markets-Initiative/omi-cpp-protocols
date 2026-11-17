// OtcMarkets.LinkAts.Multicast.Link.v4.3: main.cpp
// OtcMarkets.LinkAts.Multicast.Link.v4.3 benchmark, through the Advanced session layer: every value it reads from every message of the simulated
// sequence (tests/simulated/otcmarkets/linkats/multicast/link/v4.3.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/advanced/otcmarkets/linkats/multicast/link/v4.3/messages/session.hpp"

namespace protocol = ::otcmarkets::linkats::multicast::link::v4_3;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::packet_header& header, const packet::Frame&) {
        checksum += bench::digest(header.packet_size.get().value());
        checksum += bench::digest(header.seq_num.get().value());
        checksum += bench::digest(header.packet_flag.has_heartbeat());
        checksum += bench::digest(header.packet_flag.has_seq_num_reset());
        checksum += bench::digest(header.packet_flag.has_replay());
        checksum += bench::digest(header.packet_flag.has_test());
        checksum += bench::digest(header.message_count.get().value());
        checksum += bench::digest(header.packet_milli.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::packet_header&) {
        ++index;
    }

    void on_message(const protocol::start_of_spin_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.channel_seq_num.get().value());
        checksum += bench::digest(message.fields.spin_type.get().value());
        checksum += bench::digest(message.fields.spin_start_time_milli.get().value());
        checksum += bench::digest(message.fields.spin_last_seq_num.get().value());
    }

    void on_message(const protocol::end_of_spin_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.channel_seq_num.get().value());
        checksum += bench::digest(message.fields.spin_type.get().value());
        checksum += bench::digest(message.fields.spin_msg_ct.get().value());
        checksum += bench::digest(message.fields.spin_end_time_milli.get().value());
        checksum += bench::digest(message.fields.spin_last_seq_num.get().value());
    }

    void on_message(const protocol::market_open_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.channel_seq_num.get().value());
        checksum += bench::digest(message.fields.market_open.get().value());
        checksum += bench::digest(message.fields.market_close.get().value());
    }

    void on_message(const protocol::market_close_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.channel_seq_num.get().value());
        checksum += bench::digest(message.fields.market_close_time_milli.get().value());
        checksum += bench::digest(message.fields.market_msg_ct.get().value());
    }

    void on_message(const protocol::security_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.channel_seq_num.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.last_update_milli.get().value());
        checksum += bench::digest(message.fields.security_action.get().value());
        checksum += bench::digest(message.fields.asset_class.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.security_flags.has_piggyback());
        checksum += bench::digest(message.fields.security_flags.has_caveat_emptor_warning());
        checksum += bench::digest(message.fields.security_flags.has_qualified_institutional_buyers_only());
        checksum += bench::digest(message.fields.security_flags.has_unsolicited_only());
        checksum += bench::digest(message.fields.security_flags.has_bb_quoted());
        checksum += bench::digest(message.fields.security_flags.has_otc_link_ecn_eligible());
        checksum += bench::digest(message.fields.security_flags.has_otc_link_messaging_disabled());
        checksum += bench::digest(message.fields.security_flags.has_saturation_eligible());
        checksum += bench::digest(message.fields.tier.get().value());
        checksum += bench::digest(message.fields.reporting_status.get().value());
        checksum += bench::digest(message.fields.security_status.get().value());
    }

    void on_message(const protocol::quote_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.channel_seq_num.get().value());
        checksum += bench::digest(message.fields.quote_id.get().value());
        checksum += bench::digest(message.fields.quote_action.get().value());
        checksum += bench::digest(message.fields.quote_flags.has_update_side());
        checksum += bench::digest(message.fields.quote_flags.has_state());
        checksum += bench::digest(message.fields.quote_flags.has_ask_unsolicited());
        checksum += bench::digest(message.fields.quote_flags.has_ask_priced());
        checksum += bench::digest(message.fields.quote_flags.has_ask_bid_wanted());
        checksum += bench::digest(message.fields.quote_flags.has_bid_unsolicited());
        checksum += bench::digest(message.fields.quote_flags.has_bid_priced());
        checksum += bench::digest(message.fields.quote_flags.has_bid_ask_wanted());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.mpid.get().value());
        checksum += bench::digest(message.fields.ask_price.get().value());
        checksum += bench::digest(message.fields.ask_size.get().value());
        checksum += bench::digest(message.fields.ask_qap.get().value());
        checksum += bench::digest(message.fields.ask_time_milli.get().value());
        checksum += bench::digest(message.fields.bid_price.get().value());
        checksum += bench::digest(message.fields.bid_size.get().value());
        checksum += bench::digest(message.fields.bid_qap.get().value());
        checksum += bench::digest(message.fields.bid_time_milli.get().value());
        checksum += bench::digest(message.fields.quote_reference_id.get().value());
        checksum += bench::digest(message.fields.extended_quote_flags.has_quote_saturated());
        checksum += bench::digest(message.fields.extended_quote_flags.has_bid_auto_ex());
        checksum += bench::digest(message.fields.extended_quote_flags.has_offer_auto_ex());
        checksum += bench::digest(message.fields.extended_quote_flags.has_nms_conditional_quote());
    }

    void on_message(const protocol::quote_update_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.channel_seq_num.get().value());
        checksum += bench::digest(message.fields.quote_id.get().value());
        checksum += bench::digest(message.fields.quote_flags.has_update_side());
        checksum += bench::digest(message.fields.quote_flags.has_state());
        checksum += bench::digest(message.fields.quote_flags.has_ask_unsolicited());
        checksum += bench::digest(message.fields.quote_flags.has_ask_priced());
        checksum += bench::digest(message.fields.quote_flags.has_ask_bid_wanted());
        checksum += bench::digest(message.fields.quote_flags.has_bid_unsolicited());
        checksum += bench::digest(message.fields.quote_flags.has_bid_priced());
        checksum += bench::digest(message.fields.quote_flags.has_bid_ask_wanted());
        checksum += bench::digest(message.fields.price.get().value());
        checksum += bench::digest(message.fields.size.get().value());
        checksum += bench::digest(message.fields.qap.get().value());
        checksum += bench::digest(message.fields.quote_time_milli.get().value());
        checksum += bench::digest(message.fields.quote_reference_id.get().value());
        checksum += bench::digest(message.fields.extended_quote_flags.has_quote_saturated());
        checksum += bench::digest(message.fields.extended_quote_flags.has_bid_auto_ex());
        checksum += bench::digest(message.fields.extended_quote_flags.has_offer_auto_ex());
        checksum += bench::digest(message.fields.extended_quote_flags.has_nms_conditional_quote());
    }

    void on_message(const protocol::inside_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.channel_seq_num.get().value());
        checksum += bench::digest(message.fields.inside_id.get().value());
        checksum += bench::digest(message.fields.inside_action.get().value());
        checksum += bench::digest(message.fields.quote_flags.has_update_side());
        checksum += bench::digest(message.fields.quote_flags.has_state());
        checksum += bench::digest(message.fields.quote_flags.has_ask_unsolicited());
        checksum += bench::digest(message.fields.quote_flags.has_ask_priced());
        checksum += bench::digest(message.fields.quote_flags.has_ask_bid_wanted());
        checksum += bench::digest(message.fields.quote_flags.has_bid_unsolicited());
        checksum += bench::digest(message.fields.quote_flags.has_bid_priced());
        checksum += bench::digest(message.fields.quote_flags.has_bid_ask_wanted());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.ask_price.get().value());
        checksum += bench::digest(message.fields.ask_size.get().value());
        checksum += bench::digest(message.fields.ask_time_milli.get().value());
        checksum += bench::digest(message.fields.bid_price.get().value());
        checksum += bench::digest(message.fields.bid_size.get().value());
        checksum += bench::digest(message.fields.bid_time_milli.get().value());
        checksum += bench::digest(message.fields.ask_num_priced_mp.get().value());
        checksum += bench::digest(message.fields.bid_num_priced_mp.get().value());
    }

    void on_message(const protocol::inside_update_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.channel_seq_num.get().value());
        checksum += bench::digest(message.fields.inside_id.get().value());
        checksum += bench::digest(message.fields.quote_flags.has_update_side());
        checksum += bench::digest(message.fields.quote_flags.has_state());
        checksum += bench::digest(message.fields.quote_flags.has_ask_unsolicited());
        checksum += bench::digest(message.fields.quote_flags.has_ask_priced());
        checksum += bench::digest(message.fields.quote_flags.has_ask_bid_wanted());
        checksum += bench::digest(message.fields.quote_flags.has_bid_unsolicited());
        checksum += bench::digest(message.fields.quote_flags.has_bid_priced());
        checksum += bench::digest(message.fields.quote_flags.has_bid_ask_wanted());
        checksum += bench::digest(message.fields.price.get().value());
        checksum += bench::digest(message.fields.size.get().value());
        checksum += bench::digest(message.fields.inside_time_milli.get().value());
        checksum += bench::digest(message.fields.num_priced_mp.get().value());
    }

    void on_message(const protocol::reference_price_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.channel_seq_num.get().value());
        checksum += bench::digest(message.fields.reference_price_id.get().value());
        checksum += bench::digest(message.fields.reference_price_action.get().value());
        checksum += bench::digest(message.fields.quote_flags.has_update_side());
        checksum += bench::digest(message.fields.quote_flags.has_state());
        checksum += bench::digest(message.fields.quote_flags.has_ask_unsolicited());
        checksum += bench::digest(message.fields.quote_flags.has_ask_priced());
        checksum += bench::digest(message.fields.quote_flags.has_ask_bid_wanted());
        checksum += bench::digest(message.fields.quote_flags.has_bid_unsolicited());
        checksum += bench::digest(message.fields.quote_flags.has_bid_priced());
        checksum += bench::digest(message.fields.quote_flags.has_bid_ask_wanted());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.ask_price.get().value());
        checksum += bench::digest(message.fields.ask_size.get().value());
        checksum += bench::digest(message.fields.ask_time_milli.get().value());
        checksum += bench::digest(message.fields.bid_price.get().value());
        checksum += bench::digest(message.fields.bid_size.get().value());
        checksum += bench::digest(message.fields.bid_time_milli.get().value());
    }

    void on_message(const protocol::reference_price_update_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.channel_seq_num.get().value());
        checksum += bench::digest(message.fields.reference_price_id.get().value());
        checksum += bench::digest(message.fields.quote_flags.has_update_side());
        checksum += bench::digest(message.fields.quote_flags.has_state());
        checksum += bench::digest(message.fields.quote_flags.has_ask_unsolicited());
        checksum += bench::digest(message.fields.quote_flags.has_ask_priced());
        checksum += bench::digest(message.fields.quote_flags.has_ask_bid_wanted());
        checksum += bench::digest(message.fields.quote_flags.has_bid_unsolicited());
        checksum += bench::digest(message.fields.quote_flags.has_bid_priced());
        checksum += bench::digest(message.fields.quote_flags.has_bid_ask_wanted());
        checksum += bench::digest(message.fields.price.get().value());
        checksum += bench::digest(message.fields.size.get().value());
        checksum += bench::digest(message.fields.time_milli.get().value());
    }

    void on_message(const protocol::extended_security_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.channel_seq_num.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.last_update_milli.get().value());
        checksum += bench::digest(message.fields.security_action.get().value());
        checksum += bench::digest(message.fields.otc_issuer_id.get().value());
        checksum += bench::digest(message.fields.security_desc.get().value());
        checksum += bench::digest(message.fields.short_name.get().value());
        checksum += bench::digest(message.fields.asset_class.get().value());
        checksum += bench::digest(message.fields.security_type.get().value());
        checksum += bench::digest(message.fields.primary_market.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.extended_security_flags.has_piggyback());
        checksum += bench::digest(message.fields.extended_security_flags.has_caveat_emptor_warning());
        checksum += bench::digest(message.fields.extended_security_flags.has_qualified_institutional_buyers_only());
        checksum += bench::digest(message.fields.extended_security_flags.has_unsolicited_only());
        checksum += bench::digest(message.fields.extended_security_flags.has_sponsored_status());
        checksum += bench::digest(message.fields.extended_security_flags.has_otc_link_ecn_eligible());
        checksum += bench::digest(message.fields.extended_security_flags.has_otc_link_messaging_disabled());
        checksum += bench::digest(message.fields.extended_security_flags.has_saturation_eligible());
        checksum += bench::digest(message.fields.extended_security_flags.has_investment_grade());
        checksum += bench::digest(message.fields.extended_security_flags.has_trading_flat());
        checksum += bench::digest(message.fields.extended_security_flags.has_callable());
        checksum += bench::digest(message.fields.tier.get().value());
        checksum += bench::digest(message.fields.reporting_status.get().value());
        checksum += bench::digest(message.fields.disclosure_status.get().value());
        checksum += bench::digest(message.fields.security_status.get().value());
        checksum += bench::digest(message.fields.par_value.get().value());
        checksum += bench::digest(message.fields.coupon.get().value());
        checksum += bench::digest(message.fields.maturity_date_milli.get().value());
        checksum += bench::digest(message.fields.callable_date_milli.get().value());
        checksum += bench::digest(message.fields.adr_ratio.get().value());
        checksum += bench::digest(message.fields.adr_level.get().value());
    }

    void on_message(const protocol::extended_security_no_cusip_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.channel_seq_num.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.last_update_milli.get().value());
        checksum += bench::digest(message.fields.security_action.get().value());
        checksum += bench::digest(message.fields.otc_issuer_id.get().value());
        checksum += bench::digest(message.fields.security_desc.get().value());
        checksum += bench::digest(message.fields.short_name.get().value());
        checksum += bench::digest(message.fields.asset_class.get().value());
        checksum += bench::digest(message.fields.security_type.get().value());
        checksum += bench::digest(message.fields.primary_market.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.security_flags.has_piggyback());
        checksum += bench::digest(message.fields.security_flags.has_caveat_emptor_warning());
        checksum += bench::digest(message.fields.security_flags.has_qualified_institutional_buyers_only());
        checksum += bench::digest(message.fields.security_flags.has_unsolicited_only());
        checksum += bench::digest(message.fields.security_flags.has_bb_quoted());
        checksum += bench::digest(message.fields.security_flags.has_otc_link_ecn_eligible());
        checksum += bench::digest(message.fields.security_flags.has_otc_link_messaging_disabled());
        checksum += bench::digest(message.fields.security_flags.has_saturation_eligible());
        checksum += bench::digest(message.fields.tier.get().value());
        checksum += bench::digest(message.fields.reporting_status.get().value());
        checksum += bench::digest(message.fields.disclosure_status.get().value());
        checksum += bench::digest(message.fields.security_status.get().value());
        checksum += bench::digest(message.fields.par_value.get().value());
        checksum += bench::digest(message.fields.coupon.get().value());
        checksum += bench::digest(message.fields.maturity_date_milli.get().value());
        checksum += bench::digest(message.fields.callable_date_milli.get().value());
        checksum += bench::digest(message.fields.adr_ratio.get().value());
        checksum += bench::digest(message.fields.adr_level.get().value());
    }

    void on_message(const protocol::trade_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.channel_seq_num.get().value());
        checksum += bench::digest(message.fields.trade_id.get().value());
        checksum += bench::digest(message.fields.trade_action.get().value());
        checksum += bench::digest(message.fields.trade_flags.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.trade_status.has_irregular());
        checksum += bench::digest(message.fields.deprecated.get().value());
        checksum += bench::digest(message.fields.trade_price.get().value());
        checksum += bench::digest(message.fields.trade_size.get().value());
        checksum += bench::digest(message.fields.trade_time_milli.get().value());
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
    return bench::run("OtcMarkets.LinkAts.Multicast.Link.v4.3", "advanced", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
