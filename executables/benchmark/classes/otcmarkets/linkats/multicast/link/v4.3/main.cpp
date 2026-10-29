// OtcMarkets.LinkAts.Multicast.Link.v4.3 benchmark, through the Classes Packet: every value it reads from every message of the simulated
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
#include "cpp/binary/classes/otcmarkets/linkats/multicast/link/v4.3/definitions.hpp"

namespace protocol = ::otcmarkets::linkats::multicast::link::v4_3;

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

    checksum += bench::digest(packet.packet_header().packet_size());
    checksum += bench::digest(packet.packet_header().seq_num());
    checksum += bench::digest(packet.packet_header().packet_flag().heartbeat());
    checksum += bench::digest(packet.packet_header().packet_flag().seq_num_reset());
    checksum += bench::digest(packet.packet_header().packet_flag().replay());
    checksum += bench::digest(packet.packet_header().packet_flag().test());
    checksum += bench::digest(packet.packet_header().message_count());
    checksum += bench::digest(packet.packet_header().packet_milli());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_header().message_size());
        checksum += bench::digest(each.message_header().message_type());

        if (const auto* message = dynamic_cast<const protocol::StartOfSpinMessage*>(each.message())) {
            checksum += bench::digest((*message).channel_seq_num());
            checksum += bench::digest((*message).spin_type());
            checksum += bench::digest((*message).spin_start_time_milli());
            checksum += bench::digest((*message).spin_last_seq_num());
        } else if (const auto* message = dynamic_cast<const protocol::EndOfSpinMessage*>(each.message())) {
            checksum += bench::digest((*message).channel_seq_num());
            checksum += bench::digest((*message).spin_type());
            checksum += bench::digest((*message).spin_msg_ct());
            checksum += bench::digest((*message).spin_end_time_milli());
            checksum += bench::digest((*message).spin_last_seq_num());
        } else if (const auto* message = dynamic_cast<const protocol::MarketOpenMessage*>(each.message())) {
            checksum += bench::digest((*message).channel_seq_num());
            checksum += bench::digest((*message).market_open());
            checksum += bench::digest((*message).market_close());
        } else if (const auto* message = dynamic_cast<const protocol::MarketCloseMessage*>(each.message())) {
            checksum += bench::digest((*message).channel_seq_num());
            checksum += bench::digest((*message).market_close_time_milli());
            checksum += bench::digest((*message).market_msg_ct());
        } else if (const auto* message = dynamic_cast<const protocol::SecurityMessage*>(each.message())) {
            checksum += bench::digest((*message).channel_seq_num());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).last_update_milli());
            checksum += bench::digest((*message).security_action());
            checksum += bench::digest((*message).asset_class());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).security_flags().piggyback());
            checksum += bench::digest((*message).security_flags().caveat_emptor_warning());
            checksum += bench::digest((*message).security_flags().qualified_institutional_buyers_only());
            checksum += bench::digest((*message).security_flags().unsolicited_only());
            checksum += bench::digest((*message).security_flags().bb_quoted());
            checksum += bench::digest((*message).security_flags().otc_link_ecn_eligible());
            checksum += bench::digest((*message).security_flags().otc_link_messaging_disabled());
            checksum += bench::digest((*message).security_flags().saturation_eligible());
            checksum += bench::digest((*message).tier());
            checksum += bench::digest((*message).reporting_status());
            checksum += bench::digest((*message).security_status());
        } else if (const auto* message = dynamic_cast<const protocol::QuoteMessage*>(each.message())) {
            checksum += bench::digest((*message).channel_seq_num());
            checksum += bench::digest((*message).quote_id());
            checksum += bench::digest((*message).quote_action());
            checksum += bench::digest((*message).quote_flags().update_side());
            checksum += bench::digest((*message).quote_flags().state());
            checksum += bench::digest((*message).quote_flags().ask_unsolicited());
            checksum += bench::digest((*message).quote_flags().ask_priced());
            checksum += bench::digest((*message).quote_flags().ask_bid_wanted());
            checksum += bench::digest((*message).quote_flags().bid_unsolicited());
            checksum += bench::digest((*message).quote_flags().bid_priced());
            checksum += bench::digest((*message).quote_flags().bid_ask_wanted());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).mpid());
            checksum += bench::digest((*message).ask_price().mantissa());
            checksum += bench::digest((*message).ask_size());
            checksum += bench::digest((*message).ask_qap());
            checksum += bench::digest((*message).ask_time_milli());
            checksum += bench::digest((*message).bid_price().mantissa());
            checksum += bench::digest((*message).bid_size());
            checksum += bench::digest((*message).bid_qap());
            checksum += bench::digest((*message).bid_time_milli());
            checksum += bench::digest((*message).quote_reference_id());
            checksum += bench::digest((*message).extended_quote_flags().quote_saturated());
            checksum += bench::digest((*message).extended_quote_flags().bid_auto_ex());
            checksum += bench::digest((*message).extended_quote_flags().offer_auto_ex());
            checksum += bench::digest((*message).extended_quote_flags().nms_conditional_quote());
        } else if (const auto* message = dynamic_cast<const protocol::QuoteUpdateMessage*>(each.message())) {
            checksum += bench::digest((*message).channel_seq_num());
            checksum += bench::digest((*message).quote_id());
            checksum += bench::digest((*message).quote_flags().update_side());
            checksum += bench::digest((*message).quote_flags().state());
            checksum += bench::digest((*message).quote_flags().ask_unsolicited());
            checksum += bench::digest((*message).quote_flags().ask_priced());
            checksum += bench::digest((*message).quote_flags().ask_bid_wanted());
            checksum += bench::digest((*message).quote_flags().bid_unsolicited());
            checksum += bench::digest((*message).quote_flags().bid_priced());
            checksum += bench::digest((*message).quote_flags().bid_ask_wanted());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).size());
            checksum += bench::digest((*message).qap());
            checksum += bench::digest((*message).quote_time_milli());
            checksum += bench::digest((*message).quote_reference_id());
            checksum += bench::digest((*message).extended_quote_flags().quote_saturated());
            checksum += bench::digest((*message).extended_quote_flags().bid_auto_ex());
            checksum += bench::digest((*message).extended_quote_flags().offer_auto_ex());
            checksum += bench::digest((*message).extended_quote_flags().nms_conditional_quote());
        } else if (const auto* message = dynamic_cast<const protocol::InsideMessage*>(each.message())) {
            checksum += bench::digest((*message).channel_seq_num());
            checksum += bench::digest((*message).inside_id());
            checksum += bench::digest((*message).inside_action());
            checksum += bench::digest((*message).quote_flags().update_side());
            checksum += bench::digest((*message).quote_flags().state());
            checksum += bench::digest((*message).quote_flags().ask_unsolicited());
            checksum += bench::digest((*message).quote_flags().ask_priced());
            checksum += bench::digest((*message).quote_flags().ask_bid_wanted());
            checksum += bench::digest((*message).quote_flags().bid_unsolicited());
            checksum += bench::digest((*message).quote_flags().bid_priced());
            checksum += bench::digest((*message).quote_flags().bid_ask_wanted());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).ask_price().mantissa());
            checksum += bench::digest((*message).ask_size());
            checksum += bench::digest((*message).ask_time_milli());
            checksum += bench::digest((*message).bid_price().mantissa());
            checksum += bench::digest((*message).bid_size());
            checksum += bench::digest((*message).bid_time_milli());
            checksum += bench::digest((*message).ask_num_priced_mp());
            checksum += bench::digest((*message).bid_num_priced_mp());
        } else if (const auto* message = dynamic_cast<const protocol::InsideUpdateMessage*>(each.message())) {
            checksum += bench::digest((*message).channel_seq_num());
            checksum += bench::digest((*message).inside_id());
            checksum += bench::digest((*message).quote_flags().update_side());
            checksum += bench::digest((*message).quote_flags().state());
            checksum += bench::digest((*message).quote_flags().ask_unsolicited());
            checksum += bench::digest((*message).quote_flags().ask_priced());
            checksum += bench::digest((*message).quote_flags().ask_bid_wanted());
            checksum += bench::digest((*message).quote_flags().bid_unsolicited());
            checksum += bench::digest((*message).quote_flags().bid_priced());
            checksum += bench::digest((*message).quote_flags().bid_ask_wanted());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).size());
            checksum += bench::digest((*message).inside_time_milli());
            checksum += bench::digest((*message).num_priced_mp());
        } else if (const auto* message = dynamic_cast<const protocol::ReferencePriceMessage*>(each.message())) {
            checksum += bench::digest((*message).channel_seq_num());
            checksum += bench::digest((*message).reference_price_id());
            checksum += bench::digest((*message).reference_price_action());
            checksum += bench::digest((*message).quote_flags().update_side());
            checksum += bench::digest((*message).quote_flags().state());
            checksum += bench::digest((*message).quote_flags().ask_unsolicited());
            checksum += bench::digest((*message).quote_flags().ask_priced());
            checksum += bench::digest((*message).quote_flags().ask_bid_wanted());
            checksum += bench::digest((*message).quote_flags().bid_unsolicited());
            checksum += bench::digest((*message).quote_flags().bid_priced());
            checksum += bench::digest((*message).quote_flags().bid_ask_wanted());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).ask_price().mantissa());
            checksum += bench::digest((*message).ask_size());
            checksum += bench::digest((*message).ask_time_milli());
            checksum += bench::digest((*message).bid_price().mantissa());
            checksum += bench::digest((*message).bid_size());
            checksum += bench::digest((*message).bid_time_milli());
        } else if (const auto* message = dynamic_cast<const protocol::ReferencePriceUpdateMessage*>(each.message())) {
            checksum += bench::digest((*message).channel_seq_num());
            checksum += bench::digest((*message).reference_price_id());
            checksum += bench::digest((*message).quote_flags().update_side());
            checksum += bench::digest((*message).quote_flags().state());
            checksum += bench::digest((*message).quote_flags().ask_unsolicited());
            checksum += bench::digest((*message).quote_flags().ask_priced());
            checksum += bench::digest((*message).quote_flags().ask_bid_wanted());
            checksum += bench::digest((*message).quote_flags().bid_unsolicited());
            checksum += bench::digest((*message).quote_flags().bid_priced());
            checksum += bench::digest((*message).quote_flags().bid_ask_wanted());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).size());
            checksum += bench::digest((*message).time_milli());
        } else if (const auto* message = dynamic_cast<const protocol::ExtendedSecurityMessage*>(each.message())) {
            checksum += bench::digest((*message).channel_seq_num());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).last_update_milli());
            checksum += bench::digest((*message).security_action());
            checksum += bench::digest((*message).otc_issuer_id());
            checksum += bench::digest((*message).security_desc());
            checksum += bench::digest((*message).short_name());
            checksum += bench::digest((*message).asset_class());
            checksum += bench::digest((*message).security_type());
            checksum += bench::digest((*message).primary_market());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).extended_security_flags().piggyback());
            checksum += bench::digest((*message).extended_security_flags().caveat_emptor_warning());
            checksum += bench::digest((*message).extended_security_flags().qualified_institutional_buyers_only());
            checksum += bench::digest((*message).extended_security_flags().unsolicited_only());
            checksum += bench::digest((*message).extended_security_flags().sponsored_status());
            checksum += bench::digest((*message).extended_security_flags().otc_link_ecn_eligible());
            checksum += bench::digest((*message).extended_security_flags().otc_link_messaging_disabled());
            checksum += bench::digest((*message).extended_security_flags().saturation_eligible());
            checksum += bench::digest((*message).extended_security_flags().investment_grade());
            checksum += bench::digest((*message).extended_security_flags().trading_flat());
            checksum += bench::digest((*message).extended_security_flags().callable());
            checksum += bench::digest((*message).tier());
            checksum += bench::digest((*message).reporting_status());
            checksum += bench::digest((*message).disclosure_status());
            checksum += bench::digest((*message).security_status());
            checksum += bench::digest((*message).par_value().mantissa());
            checksum += bench::digest((*message).coupon().mantissa());
            checksum += bench::digest((*message).maturity_date_milli());
            checksum += bench::digest((*message).callable_date_milli());
            checksum += bench::digest((*message).adr_ratio().mantissa());
            checksum += bench::digest((*message).adr_level());
        } else if (const auto* message = dynamic_cast<const protocol::ExtendedSecurityNoCusipMessage*>(each.message())) {
            checksum += bench::digest((*message).channel_seq_num());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).last_update_milli());
            checksum += bench::digest((*message).security_action());
            checksum += bench::digest((*message).otc_issuer_id());
            checksum += bench::digest((*message).security_desc());
            checksum += bench::digest((*message).short_name());
            checksum += bench::digest((*message).asset_class());
            checksum += bench::digest((*message).security_type());
            checksum += bench::digest((*message).primary_market());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).security_flags().piggyback());
            checksum += bench::digest((*message).security_flags().caveat_emptor_warning());
            checksum += bench::digest((*message).security_flags().qualified_institutional_buyers_only());
            checksum += bench::digest((*message).security_flags().unsolicited_only());
            checksum += bench::digest((*message).security_flags().bb_quoted());
            checksum += bench::digest((*message).security_flags().otc_link_ecn_eligible());
            checksum += bench::digest((*message).security_flags().otc_link_messaging_disabled());
            checksum += bench::digest((*message).security_flags().saturation_eligible());
            checksum += bench::digest((*message).tier());
            checksum += bench::digest((*message).reporting_status());
            checksum += bench::digest((*message).disclosure_status());
            checksum += bench::digest((*message).security_status());
            checksum += bench::digest((*message).par_value().mantissa());
            checksum += bench::digest((*message).coupon().mantissa());
            checksum += bench::digest((*message).maturity_date_milli());
            checksum += bench::digest((*message).callable_date_milli());
            checksum += bench::digest((*message).adr_ratio().mantissa());
            checksum += bench::digest((*message).adr_level());
        } else if (const auto* message = dynamic_cast<const protocol::TradeMessage*>(each.message())) {
            checksum += bench::digest((*message).channel_seq_num());
            checksum += bench::digest((*message).trade_id());
            checksum += bench::digest((*message).trade_action());
            checksum += bench::digest((*message).trade_flags());
            checksum += bench::digest((*message).security_id());
            checksum += bench::digest((*message).trade_status().irregular());
            checksum += bench::digest((*message).deprecated());
            checksum += bench::digest((*message).trade_price().mantissa());
            checksum += bench::digest((*message).trade_size());
            checksum += bench::digest((*message).trade_time_milli());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("OtcMarkets.LinkAts.Multicast.Link.v4.3", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
