// OtcMarkets.LinkAts.Multicast.Link.v4.3 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/otcmarkets/linkats/multicast/link/v4.3.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/otcmarkets/linkats/multicast/link/v4.3/definitions.hpp"

namespace protocol = ::otcmarkets::linkats::multicast::link::v4_3;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        checksum += bench::digest(packet.packet_header().packet_size());
        checksum += bench::digest(packet.packet_header().seq_num());
        checksum += bench::digest(packet.packet_header().packet_flag().heartbeat());
        checksum += bench::digest(packet.packet_header().packet_flag().seq_num_reset());
        checksum += bench::digest(packet.packet_header().packet_flag().replay());
        checksum += bench::digest(packet.packet_header().packet_flag().test());
        checksum += bench::digest(packet.packet_header().message_count());
        checksum += bench::digest(packet.packet_header().packet_milli());
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

    void on(const protocol::StartOfSpinMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.channel_seq_num());
        checksum += bench::digest(message.spin_type());
        checksum += bench::digest(message.spin_start_time_milli());
        checksum += bench::digest(message.spin_last_seq_num());
    }

    void on(const protocol::EndOfSpinMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.channel_seq_num());
        checksum += bench::digest(message.spin_type());
        checksum += bench::digest(message.spin_msg_ct());
        checksum += bench::digest(message.spin_end_time_milli());
        checksum += bench::digest(message.spin_last_seq_num());
    }

    void on(const protocol::MarketOpenMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.channel_seq_num());
        checksum += bench::digest(message.market_open());
        checksum += bench::digest(message.market_close());
    }

    void on(const protocol::MarketCloseMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.channel_seq_num());
        checksum += bench::digest(message.market_close_time_milli());
        checksum += bench::digest(message.market_msg_ct());
    }

    void on(const protocol::SecurityMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.channel_seq_num());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.last_update_milli());
        checksum += bench::digest(message.security_action());
        checksum += bench::digest(message.asset_class());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.security_flags().piggyback());
        checksum += bench::digest(message.security_flags().caveat_emptor_warning());
        checksum += bench::digest(message.security_flags().qualified_institutional_buyers_only());
        checksum += bench::digest(message.security_flags().unsolicited_only());
        checksum += bench::digest(message.security_flags().bb_quoted());
        checksum += bench::digest(message.security_flags().otc_link_ecn_eligible());
        checksum += bench::digest(message.security_flags().otc_link_messaging_disabled());
        checksum += bench::digest(message.security_flags().saturation_eligible());
        checksum += bench::digest(message.tier());
        checksum += bench::digest(message.reporting_status());
        checksum += bench::digest(message.security_status());
    }

    void on(const protocol::QuoteMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.channel_seq_num());
        checksum += bench::digest(message.quote_id());
        checksum += bench::digest(message.quote_action());
        checksum += bench::digest(message.quote_flags().update_side());
        checksum += bench::digest(message.quote_flags().state());
        checksum += bench::digest(message.quote_flags().ask_unsolicited());
        checksum += bench::digest(message.quote_flags().ask_priced());
        checksum += bench::digest(message.quote_flags().ask_bid_wanted());
        checksum += bench::digest(message.quote_flags().bid_unsolicited());
        checksum += bench::digest(message.quote_flags().bid_priced());
        checksum += bench::digest(message.quote_flags().bid_ask_wanted());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.mpid());
        checksum += bench::digest(message.ask_price().mantissa());
        checksum += bench::digest(message.ask_size());
        checksum += bench::digest(message.ask_qap());
        checksum += bench::digest(message.ask_time_milli());
        checksum += bench::digest(message.bid_price().mantissa());
        checksum += bench::digest(message.bid_size());
        checksum += bench::digest(message.bid_qap());
        checksum += bench::digest(message.bid_time_milli());
        checksum += bench::digest(message.quote_reference_id());
        checksum += bench::digest(message.extended_quote_flags().quote_saturated());
        checksum += bench::digest(message.extended_quote_flags().bid_auto_ex());
        checksum += bench::digest(message.extended_quote_flags().offer_auto_ex());
        checksum += bench::digest(message.extended_quote_flags().nms_conditional_quote());
    }

    void on(const protocol::QuoteUpdateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.channel_seq_num());
        checksum += bench::digest(message.quote_id());
        checksum += bench::digest(message.quote_flags().update_side());
        checksum += bench::digest(message.quote_flags().state());
        checksum += bench::digest(message.quote_flags().ask_unsolicited());
        checksum += bench::digest(message.quote_flags().ask_priced());
        checksum += bench::digest(message.quote_flags().ask_bid_wanted());
        checksum += bench::digest(message.quote_flags().bid_unsolicited());
        checksum += bench::digest(message.quote_flags().bid_priced());
        checksum += bench::digest(message.quote_flags().bid_ask_wanted());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.size());
        checksum += bench::digest(message.qap());
        checksum += bench::digest(message.quote_time_milli());
        checksum += bench::digest(message.quote_reference_id());
        checksum += bench::digest(message.extended_quote_flags().quote_saturated());
        checksum += bench::digest(message.extended_quote_flags().bid_auto_ex());
        checksum += bench::digest(message.extended_quote_flags().offer_auto_ex());
        checksum += bench::digest(message.extended_quote_flags().nms_conditional_quote());
    }

    void on(const protocol::InsideMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.channel_seq_num());
        checksum += bench::digest(message.inside_id());
        checksum += bench::digest(message.inside_action());
        checksum += bench::digest(message.quote_flags().update_side());
        checksum += bench::digest(message.quote_flags().state());
        checksum += bench::digest(message.quote_flags().ask_unsolicited());
        checksum += bench::digest(message.quote_flags().ask_priced());
        checksum += bench::digest(message.quote_flags().ask_bid_wanted());
        checksum += bench::digest(message.quote_flags().bid_unsolicited());
        checksum += bench::digest(message.quote_flags().bid_priced());
        checksum += bench::digest(message.quote_flags().bid_ask_wanted());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.ask_price().mantissa());
        checksum += bench::digest(message.ask_size());
        checksum += bench::digest(message.ask_time_milli());
        checksum += bench::digest(message.bid_price().mantissa());
        checksum += bench::digest(message.bid_size());
        checksum += bench::digest(message.bid_time_milli());
        checksum += bench::digest(message.ask_num_priced_mp());
        checksum += bench::digest(message.bid_num_priced_mp());
    }

    void on(const protocol::InsideUpdateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.channel_seq_num());
        checksum += bench::digest(message.inside_id());
        checksum += bench::digest(message.quote_flags().update_side());
        checksum += bench::digest(message.quote_flags().state());
        checksum += bench::digest(message.quote_flags().ask_unsolicited());
        checksum += bench::digest(message.quote_flags().ask_priced());
        checksum += bench::digest(message.quote_flags().ask_bid_wanted());
        checksum += bench::digest(message.quote_flags().bid_unsolicited());
        checksum += bench::digest(message.quote_flags().bid_priced());
        checksum += bench::digest(message.quote_flags().bid_ask_wanted());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.size());
        checksum += bench::digest(message.inside_time_milli());
        checksum += bench::digest(message.num_priced_mp());
    }

    void on(const protocol::ReferencePriceMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.channel_seq_num());
        checksum += bench::digest(message.reference_price_id());
        checksum += bench::digest(message.reference_price_action());
        checksum += bench::digest(message.quote_flags().update_side());
        checksum += bench::digest(message.quote_flags().state());
        checksum += bench::digest(message.quote_flags().ask_unsolicited());
        checksum += bench::digest(message.quote_flags().ask_priced());
        checksum += bench::digest(message.quote_flags().ask_bid_wanted());
        checksum += bench::digest(message.quote_flags().bid_unsolicited());
        checksum += bench::digest(message.quote_flags().bid_priced());
        checksum += bench::digest(message.quote_flags().bid_ask_wanted());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.ask_price().mantissa());
        checksum += bench::digest(message.ask_size());
        checksum += bench::digest(message.ask_time_milli());
        checksum += bench::digest(message.bid_price().mantissa());
        checksum += bench::digest(message.bid_size());
        checksum += bench::digest(message.bid_time_milli());
    }

    void on(const protocol::ReferencePriceUpdateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.channel_seq_num());
        checksum += bench::digest(message.reference_price_id());
        checksum += bench::digest(message.quote_flags().update_side());
        checksum += bench::digest(message.quote_flags().state());
        checksum += bench::digest(message.quote_flags().ask_unsolicited());
        checksum += bench::digest(message.quote_flags().ask_priced());
        checksum += bench::digest(message.quote_flags().ask_bid_wanted());
        checksum += bench::digest(message.quote_flags().bid_unsolicited());
        checksum += bench::digest(message.quote_flags().bid_priced());
        checksum += bench::digest(message.quote_flags().bid_ask_wanted());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.size());
        checksum += bench::digest(message.time_milli());
    }

    void on(const protocol::ExtendedSecurityMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.channel_seq_num());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.last_update_milli());
        checksum += bench::digest(message.security_action());
        checksum += bench::digest(message.otc_issuer_id());
        checksum += bench::digest(message.security_desc());
        checksum += bench::digest(message.short_name());
        checksum += bench::digest(message.asset_class());
        checksum += bench::digest(message.security_type());
        checksum += bench::digest(message.primary_market());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.extended_security_flags().piggyback());
        checksum += bench::digest(message.extended_security_flags().caveat_emptor_warning());
        checksum += bench::digest(message.extended_security_flags().qualified_institutional_buyers_only());
        checksum += bench::digest(message.extended_security_flags().unsolicited_only());
        checksum += bench::digest(message.extended_security_flags().sponsored_status());
        checksum += bench::digest(message.extended_security_flags().otc_link_ecn_eligible());
        checksum += bench::digest(message.extended_security_flags().otc_link_messaging_disabled());
        checksum += bench::digest(message.extended_security_flags().saturation_eligible());
        checksum += bench::digest(message.extended_security_flags().investment_grade());
        checksum += bench::digest(message.extended_security_flags().trading_flat());
        checksum += bench::digest(message.extended_security_flags().callable());
        checksum += bench::digest(message.tier());
        checksum += bench::digest(message.reporting_status());
        checksum += bench::digest(message.disclosure_status());
        checksum += bench::digest(message.security_status());
        checksum += bench::digest(message.par_value().mantissa());
        checksum += bench::digest(message.coupon().mantissa());
        checksum += bench::digest(message.maturity_date_milli());
        checksum += bench::digest(message.callable_date_milli());
        checksum += bench::digest(message.adr_ratio().mantissa());
        checksum += bench::digest(message.adr_level());
    }

    void on(const protocol::ExtendedSecurityNoCusipMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.channel_seq_num());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.last_update_milli());
        checksum += bench::digest(message.security_action());
        checksum += bench::digest(message.otc_issuer_id());
        checksum += bench::digest(message.security_desc());
        checksum += bench::digest(message.short_name());
        checksum += bench::digest(message.asset_class());
        checksum += bench::digest(message.security_type());
        checksum += bench::digest(message.primary_market());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.security_flags().piggyback());
        checksum += bench::digest(message.security_flags().caveat_emptor_warning());
        checksum += bench::digest(message.security_flags().qualified_institutional_buyers_only());
        checksum += bench::digest(message.security_flags().unsolicited_only());
        checksum += bench::digest(message.security_flags().bb_quoted());
        checksum += bench::digest(message.security_flags().otc_link_ecn_eligible());
        checksum += bench::digest(message.security_flags().otc_link_messaging_disabled());
        checksum += bench::digest(message.security_flags().saturation_eligible());
        checksum += bench::digest(message.tier());
        checksum += bench::digest(message.reporting_status());
        checksum += bench::digest(message.disclosure_status());
        checksum += bench::digest(message.security_status());
        checksum += bench::digest(message.par_value().mantissa());
        checksum += bench::digest(message.coupon().mantissa());
        checksum += bench::digest(message.maturity_date_milli());
        checksum += bench::digest(message.callable_date_milli());
        checksum += bench::digest(message.adr_ratio().mantissa());
        checksum += bench::digest(message.adr_level());
    }

    void on(const protocol::TradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.channel_seq_num());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.trade_action());
        checksum += bench::digest(message.trade_flags());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.trade_status().irregular());
        checksum += bench::digest(message.deprecated());
        checksum += bench::digest(message.trade_price().mantissa());
        checksum += bench::digest(message.trade_size());
        checksum += bench::digest(message.trade_time_milli());
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
    return bench::run("OtcMarkets.LinkAts.Multicast.Link.v4.3", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
