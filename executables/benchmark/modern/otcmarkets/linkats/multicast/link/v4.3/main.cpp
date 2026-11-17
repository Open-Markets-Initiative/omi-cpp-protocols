// OtcMarkets.LinkAts.Multicast.Link.v4.3: main.cpp
// OtcMarkets.LinkAts.Multicast.Link.v4.3 benchmark, through the Modern iterator: every value it reads from every message of the simulated
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
#include "cpp/binary/modern/otcmarkets/linkats/multicast/link/v4.3/definitions.hpp"

namespace protocol = ::otcmarkets::linkats::multicast::link::v4_3;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    checksum += bench::digest(iterator.packet_header->packet_size.get());
    checksum += bench::digest(iterator.packet_header->seq_num.get());
    checksum += bench::digest(iterator.packet_header->packet_flag.Heartbeat());
    checksum += bench::digest(iterator.packet_header->packet_flag.SeqNumReset());
    checksum += bench::digest(iterator.packet_header->packet_flag.Replay());
    checksum += bench::digest(iterator.packet_header->packet_flag.Test());
    checksum += bench::digest(iterator.packet_header->message_count.get());
    checksum += bench::digest(iterator.packet_header->packet_milli.get());

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.message_header->message_size.get());
        checksum += bench::digest(iterator.message_header->message_type.get());

        if (iterator.message_type == protocol::StartOfSpinMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::StartOfSpinMessage::parse(iterator.message);
            checksum += bench::digest(message->channel_seq_num.get());
            checksum += bench::digest(message->spin_type.get());
            checksum += bench::digest(message->spin_start_time_milli.get());
            checksum += bench::digest(message->spin_last_seq_num.get());
        } else if (iterator.message_type == protocol::EndOfSpinMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::EndOfSpinMessage::parse(iterator.message);
            checksum += bench::digest(message->channel_seq_num.get());
            checksum += bench::digest(message->spin_type.get());
            checksum += bench::digest(message->spin_msg_ct.get());
            checksum += bench::digest(message->spin_end_time_milli.get());
            checksum += bench::digest(message->spin_last_seq_num.get());
        } else if (iterator.message_type == protocol::MarketOpenMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::MarketOpenMessage::parse(iterator.message);
            checksum += bench::digest(message->channel_seq_num.get());
            checksum += bench::digest(message->market_open.get());
            checksum += bench::digest(message->market_close.get());
        } else if (iterator.message_type == protocol::MarketCloseMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::MarketCloseMessage::parse(iterator.message);
            checksum += bench::digest(message->channel_seq_num.get());
            checksum += bench::digest(message->market_close_time_milli.get());
            checksum += bench::digest(message->market_msg_ct.get());
        } else if (iterator.message_type == protocol::SecurityMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SecurityMessage::parse(iterator.message);
            checksum += bench::digest(message->channel_seq_num.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->last_update_milli.get());
            checksum += bench::digest(message->security_action.get());
            checksum += bench::digest(message->asset_class.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->security_flags.Piggyback());
            checksum += bench::digest(message->security_flags.CaveatEmptorWarning());
            checksum += bench::digest(message->security_flags.QualifiedInstitutionalBuyersOnly());
            checksum += bench::digest(message->security_flags.UnsolicitedOnly());
            checksum += bench::digest(message->security_flags.BbQuoted());
            checksum += bench::digest(message->security_flags.OtcLinkEcnEligible());
            checksum += bench::digest(message->security_flags.OtcLinkMessagingDisabled());
            checksum += bench::digest(message->security_flags.SaturationEligible());
            checksum += bench::digest(message->tier.get());
            checksum += bench::digest(message->reporting_status.get());
            checksum += bench::digest(message->security_status.get());
        } else if (iterator.message_type == protocol::QuoteMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::QuoteMessage::parse(iterator.message);
            checksum += bench::digest(message->channel_seq_num.get());
            checksum += bench::digest(message->quote_id.get());
            checksum += bench::digest(message->quote_action.get());
            checksum += bench::digest(message->quote_flags.UpdateSide());
            checksum += bench::digest(message->quote_flags.State());
            checksum += bench::digest(message->quote_flags.AskUnsolicited());
            checksum += bench::digest(message->quote_flags.AskPriced());
            checksum += bench::digest(message->quote_flags.AskBidWanted());
            checksum += bench::digest(message->quote_flags.BidUnsolicited());
            checksum += bench::digest(message->quote_flags.BidPriced());
            checksum += bench::digest(message->quote_flags.BidAskWanted());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->mpid.get());
            checksum += bench::digest(message->ask_price.integer());
            checksum += bench::digest(message->ask_size.get());
            checksum += bench::digest(message->ask_qap.get());
            checksum += bench::digest(message->ask_time_milli.get());
            checksum += bench::digest(message->bid_price.integer());
            checksum += bench::digest(message->bid_size.get());
            checksum += bench::digest(message->bid_qap.get());
            checksum += bench::digest(message->bid_time_milli.get());
            checksum += bench::digest(message->quote_reference_id.get());
            checksum += bench::digest(message->extended_quote_flags.QuoteSaturated());
            checksum += bench::digest(message->extended_quote_flags.BidAutoEx());
            checksum += bench::digest(message->extended_quote_flags.OfferAutoEx());
            checksum += bench::digest(message->extended_quote_flags.NmsConditionalQuote());
        } else if (iterator.message_type == protocol::QuoteUpdateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::QuoteUpdateMessage::parse(iterator.message);
            checksum += bench::digest(message->channel_seq_num.get());
            checksum += bench::digest(message->quote_id.get());
            checksum += bench::digest(message->quote_flags.UpdateSide());
            checksum += bench::digest(message->quote_flags.State());
            checksum += bench::digest(message->quote_flags.AskUnsolicited());
            checksum += bench::digest(message->quote_flags.AskPriced());
            checksum += bench::digest(message->quote_flags.AskBidWanted());
            checksum += bench::digest(message->quote_flags.BidUnsolicited());
            checksum += bench::digest(message->quote_flags.BidPriced());
            checksum += bench::digest(message->quote_flags.BidAskWanted());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->size.get());
            checksum += bench::digest(message->qap.get());
            checksum += bench::digest(message->quote_time_milli.get());
            checksum += bench::digest(message->quote_reference_id.get());
            checksum += bench::digest(message->extended_quote_flags.QuoteSaturated());
            checksum += bench::digest(message->extended_quote_flags.BidAutoEx());
            checksum += bench::digest(message->extended_quote_flags.OfferAutoEx());
            checksum += bench::digest(message->extended_quote_flags.NmsConditionalQuote());
        } else if (iterator.message_type == protocol::InsideMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::InsideMessage::parse(iterator.message);
            checksum += bench::digest(message->channel_seq_num.get());
            checksum += bench::digest(message->inside_id.get());
            checksum += bench::digest(message->inside_action.get());
            checksum += bench::digest(message->quote_flags.UpdateSide());
            checksum += bench::digest(message->quote_flags.State());
            checksum += bench::digest(message->quote_flags.AskUnsolicited());
            checksum += bench::digest(message->quote_flags.AskPriced());
            checksum += bench::digest(message->quote_flags.AskBidWanted());
            checksum += bench::digest(message->quote_flags.BidUnsolicited());
            checksum += bench::digest(message->quote_flags.BidPriced());
            checksum += bench::digest(message->quote_flags.BidAskWanted());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->ask_price.integer());
            checksum += bench::digest(message->ask_size.get());
            checksum += bench::digest(message->ask_time_milli.get());
            checksum += bench::digest(message->bid_price.integer());
            checksum += bench::digest(message->bid_size.get());
            checksum += bench::digest(message->bid_time_milli.get());
            checksum += bench::digest(message->ask_num_priced_mp.get());
            checksum += bench::digest(message->bid_num_priced_mp.get());
        } else if (iterator.message_type == protocol::InsideUpdateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::InsideUpdateMessage::parse(iterator.message);
            checksum += bench::digest(message->channel_seq_num.get());
            checksum += bench::digest(message->inside_id.get());
            checksum += bench::digest(message->quote_flags.UpdateSide());
            checksum += bench::digest(message->quote_flags.State());
            checksum += bench::digest(message->quote_flags.AskUnsolicited());
            checksum += bench::digest(message->quote_flags.AskPriced());
            checksum += bench::digest(message->quote_flags.AskBidWanted());
            checksum += bench::digest(message->quote_flags.BidUnsolicited());
            checksum += bench::digest(message->quote_flags.BidPriced());
            checksum += bench::digest(message->quote_flags.BidAskWanted());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->size.get());
            checksum += bench::digest(message->inside_time_milli.get());
            checksum += bench::digest(message->num_priced_mp.get());
        } else if (iterator.message_type == protocol::ReferencePriceMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ReferencePriceMessage::parse(iterator.message);
            checksum += bench::digest(message->channel_seq_num.get());
            checksum += bench::digest(message->reference_price_id.get());
            checksum += bench::digest(message->reference_price_action.get());
            checksum += bench::digest(message->quote_flags.UpdateSide());
            checksum += bench::digest(message->quote_flags.State());
            checksum += bench::digest(message->quote_flags.AskUnsolicited());
            checksum += bench::digest(message->quote_flags.AskPriced());
            checksum += bench::digest(message->quote_flags.AskBidWanted());
            checksum += bench::digest(message->quote_flags.BidUnsolicited());
            checksum += bench::digest(message->quote_flags.BidPriced());
            checksum += bench::digest(message->quote_flags.BidAskWanted());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->ask_price.integer());
            checksum += bench::digest(message->ask_size.get());
            checksum += bench::digest(message->ask_time_milli.get());
            checksum += bench::digest(message->bid_price.integer());
            checksum += bench::digest(message->bid_size.get());
            checksum += bench::digest(message->bid_time_milli.get());
        } else if (iterator.message_type == protocol::ReferencePriceUpdateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ReferencePriceUpdateMessage::parse(iterator.message);
            checksum += bench::digest(message->channel_seq_num.get());
            checksum += bench::digest(message->reference_price_id.get());
            checksum += bench::digest(message->quote_flags.UpdateSide());
            checksum += bench::digest(message->quote_flags.State());
            checksum += bench::digest(message->quote_flags.AskUnsolicited());
            checksum += bench::digest(message->quote_flags.AskPriced());
            checksum += bench::digest(message->quote_flags.AskBidWanted());
            checksum += bench::digest(message->quote_flags.BidUnsolicited());
            checksum += bench::digest(message->quote_flags.BidPriced());
            checksum += bench::digest(message->quote_flags.BidAskWanted());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->size.get());
            checksum += bench::digest(message->time_milli.get());
        } else if (iterator.message_type == protocol::ExtendedSecurityMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ExtendedSecurityMessage::parse(iterator.message);
            checksum += bench::digest(message->channel_seq_num.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->last_update_milli.get());
            checksum += bench::digest(message->security_action.get());
            checksum += bench::digest(message->otc_issuer_id.get());
            checksum += bench::digest(message->security_desc.get());
            checksum += bench::digest(message->short_name.get());
            checksum += bench::digest(message->asset_class.get());
            checksum += bench::digest(message->security_type.get());
            checksum += bench::digest(message->primary_market.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->extended_security_flags.Piggyback());
            checksum += bench::digest(message->extended_security_flags.CaveatEmptorWarning());
            checksum += bench::digest(message->extended_security_flags.QualifiedInstitutionalBuyersOnly());
            checksum += bench::digest(message->extended_security_flags.UnsolicitedOnly());
            checksum += bench::digest(message->extended_security_flags.SponsoredStatus());
            checksum += bench::digest(message->extended_security_flags.OtcLinkEcnEligible());
            checksum += bench::digest(message->extended_security_flags.OtcLinkMessagingDisabled());
            checksum += bench::digest(message->extended_security_flags.SaturationEligible());
            checksum += bench::digest(message->extended_security_flags.InvestmentGrade());
            checksum += bench::digest(message->extended_security_flags.TradingFlat());
            checksum += bench::digest(message->extended_security_flags.Callable());
            checksum += bench::digest(message->tier.get());
            checksum += bench::digest(message->reporting_status.get());
            checksum += bench::digest(message->disclosure_status.get());
            checksum += bench::digest(message->security_status.get());
            checksum += bench::digest(message->par_value.integer());
            checksum += bench::digest(message->coupon.integer());
            checksum += bench::digest(message->maturity_date_milli.get());
            checksum += bench::digest(message->callable_date_milli.get());
            checksum += bench::digest(message->adr_ratio.integer());
            checksum += bench::digest(message->adr_level.get());
        } else if (iterator.message_type == protocol::ExtendedSecurityNoCusipMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ExtendedSecurityNoCusipMessage::parse(iterator.message);
            checksum += bench::digest(message->channel_seq_num.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->last_update_milli.get());
            checksum += bench::digest(message->security_action.get());
            checksum += bench::digest(message->otc_issuer_id.get());
            checksum += bench::digest(message->security_desc.get());
            checksum += bench::digest(message->short_name.get());
            checksum += bench::digest(message->asset_class.get());
            checksum += bench::digest(message->security_type.get());
            checksum += bench::digest(message->primary_market.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->security_flags.Piggyback());
            checksum += bench::digest(message->security_flags.CaveatEmptorWarning());
            checksum += bench::digest(message->security_flags.QualifiedInstitutionalBuyersOnly());
            checksum += bench::digest(message->security_flags.UnsolicitedOnly());
            checksum += bench::digest(message->security_flags.BbQuoted());
            checksum += bench::digest(message->security_flags.OtcLinkEcnEligible());
            checksum += bench::digest(message->security_flags.OtcLinkMessagingDisabled());
            checksum += bench::digest(message->security_flags.SaturationEligible());
            checksum += bench::digest(message->tier.get());
            checksum += bench::digest(message->reporting_status.get());
            checksum += bench::digest(message->disclosure_status.get());
            checksum += bench::digest(message->security_status.get());
            checksum += bench::digest(message->par_value.integer());
            checksum += bench::digest(message->coupon.integer());
            checksum += bench::digest(message->maturity_date_milli.get());
            checksum += bench::digest(message->callable_date_milli.get());
            checksum += bench::digest(message->adr_ratio.integer());
            checksum += bench::digest(message->adr_level.get());
        } else if (iterator.message_type == protocol::TradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeMessage::parse(iterator.message);
            checksum += bench::digest(message->channel_seq_num.get());
            checksum += bench::digest(message->trade_id.get());
            checksum += bench::digest(message->trade_action.get());
            checksum += bench::digest(message->trade_flags.get());
            checksum += bench::digest(message->security_id.get());
            checksum += bench::digest(message->trade_status.Irregular());
            checksum += bench::digest(message->deprecated.get());
            checksum += bench::digest(message->trade_price.integer());
            checksum += bench::digest(message->trade_size.get());
            checksum += bench::digest(message->trade_time_milli.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("OtcMarkets.LinkAts.Multicast.Link.v4.3", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
