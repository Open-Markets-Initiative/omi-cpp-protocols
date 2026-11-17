// OtcMarkets.LinkAts.Multicast.Link.v4.3 canonical values, through the Modern iterator: every value Modern reads from
// each sample, at its address, held to what the model reads.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "tests/canonical/Canonical.hpp"
#include "cpp/binary/modern/otcmarkets/linkats/multicast/link/v4.3/definitions.hpp"

namespace protocol = ::otcmarkets::linkats::multicast::link::v4_3;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    values["packet.packetheader.packetsize"] = canonical::number(iterator.packet_header->packet_size.get());
    values["packet.packetheader.seqnum"] = canonical::number(iterator.packet_header->seq_num.get());
    values["packet.packetheader.packetflag.heartbeat"] = canonical::number(static_cast<std::uint64_t>(iterator.packet_header->packet_flag.Heartbeat()));
    values["packet.packetheader.packetflag.seqnumreset"] = canonical::number(static_cast<std::uint64_t>(iterator.packet_header->packet_flag.SeqNumReset()));
    values["packet.packetheader.packetflag.replay"] = canonical::number(static_cast<std::uint64_t>(iterator.packet_header->packet_flag.Replay()));
    values["packet.packetheader.packetflag.test"] = canonical::number(static_cast<std::uint64_t>(iterator.packet_header->packet_flag.Test()));
    values["packet.packetheader.messagecount"] = canonical::number(iterator.packet_header->message_count.get());
    values["packet.packetheader.packetmilli"] = canonical::number(iterator.packet_header->packet_milli.get());

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(iterator.message_header->message_size.get());
        values[entry + ".messageheader.messagetype"] = canonical::number(iterator.message_header->message_type.get());

        if (iterator.message_type == protocol::StartOfSpinMessage::message_type) {
            values[entry + ".payload"] = "packet.messageblock.message.payload.startofspinmessage";
            [[maybe_unused]] const auto* message = protocol::StartOfSpinMessage::parse(iterator.message);
            values[entry + ".payload.startofspinmessage.channelseqnum"] = canonical::number(message->channel_seq_num.get());
            values[entry + ".payload.startofspinmessage.spintype"] = canonical::number(message->spin_type.get());
            values[entry + ".payload.startofspinmessage.spinstarttimemilli"] = canonical::number(message->spin_start_time_milli.get());
            values[entry + ".payload.startofspinmessage.spinlastseqnum"] = canonical::number(message->spin_last_seq_num.get());
        } else if (iterator.message_type == protocol::EndOfSpinMessage::message_type) {
            values[entry + ".payload"] = "packet.messageblock.message.payload.endofspinmessage";
            [[maybe_unused]] const auto* message = protocol::EndOfSpinMessage::parse(iterator.message);
            values[entry + ".payload.endofspinmessage.channelseqnum"] = canonical::number(message->channel_seq_num.get());
            values[entry + ".payload.endofspinmessage.spintype"] = canonical::number(message->spin_type.get());
            values[entry + ".payload.endofspinmessage.spinmsgct"] = canonical::number(message->spin_msg_ct.get());
            values[entry + ".payload.endofspinmessage.spinendtimemilli"] = canonical::number(message->spin_end_time_milli.get());
            values[entry + ".payload.endofspinmessage.spinlastseqnum"] = canonical::number(message->spin_last_seq_num.get());
        } else if (iterator.message_type == protocol::MarketOpenMessage::message_type) {
            values[entry + ".payload"] = "packet.messageblock.message.payload.marketopenmessage";
            [[maybe_unused]] const auto* message = protocol::MarketOpenMessage::parse(iterator.message);
            values[entry + ".payload.marketopenmessage.channelseqnum"] = canonical::number(message->channel_seq_num.get());
            values[entry + ".payload.marketopenmessage.marketopen"] = canonical::number(message->market_open.get());
            values[entry + ".payload.marketopenmessage.marketclose"] = canonical::number(message->market_close.get());
        } else if (iterator.message_type == protocol::MarketCloseMessage::message_type) {
            values[entry + ".payload"] = "packet.messageblock.message.payload.marketclosemessage";
            [[maybe_unused]] const auto* message = protocol::MarketCloseMessage::parse(iterator.message);
            values[entry + ".payload.marketclosemessage.channelseqnum"] = canonical::number(message->channel_seq_num.get());
            values[entry + ".payload.marketclosemessage.marketclosetimemilli"] = canonical::number(message->market_close_time_milli.get());
            values[entry + ".payload.marketclosemessage.marketmsgct"] = canonical::number(message->market_msg_ct.get());
        } else if (iterator.message_type == protocol::SecurityMessage::message_type) {
            values[entry + ".payload"] = "packet.messageblock.message.payload.securitymessage";
            [[maybe_unused]] const auto* message = protocol::SecurityMessage::parse(iterator.message);
            values[entry + ".payload.securitymessage.channelseqnum"] = canonical::number(message->channel_seq_num.get());
            values[entry + ".payload.securitymessage.symbol"] = canonical::text(std::string(message->symbol.get()));
            values[entry + ".payload.securitymessage.lastupdatemilli"] = canonical::number(message->last_update_milli.get());
            values[entry + ".payload.securitymessage.securityaction"] = canonical::number(message->security_action.get());
            values[entry + ".payload.securitymessage.assetclass"] = canonical::number(message->asset_class.get());
            values[entry + ".payload.securitymessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.securitymessage.securityflags.piggyback"] = canonical::number(static_cast<std::uint64_t>(message->security_flags.Piggyback()));
            values[entry + ".payload.securitymessage.securityflags.caveatemptorwarning"] = canonical::number(static_cast<std::uint64_t>(message->security_flags.CaveatEmptorWarning()));
            values[entry + ".payload.securitymessage.securityflags.qualifiedinstitutionalbuyersonly"] = canonical::number(static_cast<std::uint64_t>(message->security_flags.QualifiedInstitutionalBuyersOnly()));
            values[entry + ".payload.securitymessage.securityflags.unsolicitedonly"] = canonical::number(static_cast<std::uint64_t>(message->security_flags.UnsolicitedOnly()));
            values[entry + ".payload.securitymessage.securityflags.bbquoted"] = canonical::number(static_cast<std::uint64_t>(message->security_flags.BbQuoted()));
            values[entry + ".payload.securitymessage.securityflags.otclinkecneligible"] = canonical::number(static_cast<std::uint64_t>(message->security_flags.OtcLinkEcnEligible()));
            values[entry + ".payload.securitymessage.securityflags.otclinkmessagingdisabled"] = canonical::number(static_cast<std::uint64_t>(message->security_flags.OtcLinkMessagingDisabled()));
            values[entry + ".payload.securitymessage.securityflags.saturationeligible"] = canonical::number(static_cast<std::uint64_t>(message->security_flags.SaturationEligible()));
            values[entry + ".payload.securitymessage.tier"] = canonical::number(message->tier.get());
            values[entry + ".payload.securitymessage.reportingstatus"] = canonical::text(canonical::character(message->reporting_status.get()));
            values[entry + ".payload.securitymessage.securitystatus"] = canonical::text(canonical::character(message->security_status.get()));
        } else if (iterator.message_type == protocol::QuoteMessage::message_type) {
            values[entry + ".payload"] = "packet.messageblock.message.payload.quotemessage";
            [[maybe_unused]] const auto* message = protocol::QuoteMessage::parse(iterator.message);
            values[entry + ".payload.quotemessage.channelseqnum"] = canonical::number(message->channel_seq_num.get());
            values[entry + ".payload.quotemessage.quoteid"] = canonical::number(message->quote_id.get());
            values[entry + ".payload.quotemessage.quoteaction"] = canonical::number(message->quote_action.get());
            values[entry + ".payload.quotemessage.quoteflags.updateside"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.UpdateSide()));
            values[entry + ".payload.quotemessage.quoteflags.state"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.State()));
            values[entry + ".payload.quotemessage.quoteflags.askunsolicited"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.AskUnsolicited()));
            values[entry + ".payload.quotemessage.quoteflags.askpriced"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.AskPriced()));
            values[entry + ".payload.quotemessage.quoteflags.askbidwanted"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.AskBidWanted()));
            values[entry + ".payload.quotemessage.quoteflags.bidunsolicited"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.BidUnsolicited()));
            values[entry + ".payload.quotemessage.quoteflags.bidpriced"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.BidPriced()));
            values[entry + ".payload.quotemessage.quoteflags.bidaskwanted"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.BidAskWanted()));
            values[entry + ".payload.quotemessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.quotemessage.mpid"] = canonical::text(std::string(message->mpid.get()));
            values[entry + ".payload.quotemessage.askprice"] = canonical::scaled(message->ask_price.integer(), -6);
            values[entry + ".payload.quotemessage.asksize"] = canonical::number(message->ask_size.get());
            values[entry + ".payload.quotemessage.askqap"] = canonical::number(message->ask_qap.get());
            values[entry + ".payload.quotemessage.asktimemilli"] = canonical::number(message->ask_time_milli.get());
            values[entry + ".payload.quotemessage.bidprice"] = canonical::scaled(message->bid_price.integer(), -6);
            values[entry + ".payload.quotemessage.bidsize"] = canonical::number(message->bid_size.get());
            values[entry + ".payload.quotemessage.bidqap"] = canonical::number(message->bid_qap.get());
            values[entry + ".payload.quotemessage.bidtimemilli"] = canonical::number(message->bid_time_milli.get());
            values[entry + ".payload.quotemessage.quotereferenceid"] = canonical::number(message->quote_reference_id.get());
            values[entry + ".payload.quotemessage.extendedquoteflags.quotesaturated"] = canonical::number(static_cast<std::uint64_t>(message->extended_quote_flags.QuoteSaturated()));
            values[entry + ".payload.quotemessage.extendedquoteflags.bidautoex"] = canonical::number(static_cast<std::uint64_t>(message->extended_quote_flags.BidAutoEx()));
            values[entry + ".payload.quotemessage.extendedquoteflags.offerautoex"] = canonical::number(static_cast<std::uint64_t>(message->extended_quote_flags.OfferAutoEx()));
            values[entry + ".payload.quotemessage.extendedquoteflags.nmsconditionalquote"] = canonical::number(static_cast<std::uint64_t>(message->extended_quote_flags.NmsConditionalQuote()));
        } else if (iterator.message_type == protocol::QuoteUpdateMessage::message_type) {
            values[entry + ".payload"] = "packet.messageblock.message.payload.quoteupdatemessage";
            [[maybe_unused]] const auto* message = protocol::QuoteUpdateMessage::parse(iterator.message);
            values[entry + ".payload.quoteupdatemessage.channelseqnum"] = canonical::number(message->channel_seq_num.get());
            values[entry + ".payload.quoteupdatemessage.quoteid"] = canonical::number(message->quote_id.get());
            values[entry + ".payload.quoteupdatemessage.quoteflags.updateside"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.UpdateSide()));
            values[entry + ".payload.quoteupdatemessage.quoteflags.state"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.State()));
            values[entry + ".payload.quoteupdatemessage.quoteflags.askunsolicited"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.AskUnsolicited()));
            values[entry + ".payload.quoteupdatemessage.quoteflags.askpriced"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.AskPriced()));
            values[entry + ".payload.quoteupdatemessage.quoteflags.askbidwanted"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.AskBidWanted()));
            values[entry + ".payload.quoteupdatemessage.quoteflags.bidunsolicited"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.BidUnsolicited()));
            values[entry + ".payload.quoteupdatemessage.quoteflags.bidpriced"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.BidPriced()));
            values[entry + ".payload.quoteupdatemessage.quoteflags.bidaskwanted"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.BidAskWanted()));
            values[entry + ".payload.quoteupdatemessage.price"] = canonical::scaled(message->price.integer(), -6);
            values[entry + ".payload.quoteupdatemessage.size"] = canonical::number(message->size.get());
            values[entry + ".payload.quoteupdatemessage.qap"] = canonical::number(message->qap.get());
            values[entry + ".payload.quoteupdatemessage.quotetimemilli"] = canonical::number(message->quote_time_milli.get());
            values[entry + ".payload.quoteupdatemessage.quotereferenceid"] = canonical::number(message->quote_reference_id.get());
            values[entry + ".payload.quoteupdatemessage.extendedquoteflags.quotesaturated"] = canonical::number(static_cast<std::uint64_t>(message->extended_quote_flags.QuoteSaturated()));
            values[entry + ".payload.quoteupdatemessage.extendedquoteflags.bidautoex"] = canonical::number(static_cast<std::uint64_t>(message->extended_quote_flags.BidAutoEx()));
            values[entry + ".payload.quoteupdatemessage.extendedquoteflags.offerautoex"] = canonical::number(static_cast<std::uint64_t>(message->extended_quote_flags.OfferAutoEx()));
            values[entry + ".payload.quoteupdatemessage.extendedquoteflags.nmsconditionalquote"] = canonical::number(static_cast<std::uint64_t>(message->extended_quote_flags.NmsConditionalQuote()));
        } else if (iterator.message_type == protocol::InsideMessage::message_type) {
            values[entry + ".payload"] = "packet.messageblock.message.payload.insidemessage";
            [[maybe_unused]] const auto* message = protocol::InsideMessage::parse(iterator.message);
            values[entry + ".payload.insidemessage.channelseqnum"] = canonical::number(message->channel_seq_num.get());
            values[entry + ".payload.insidemessage.insideid"] = canonical::number(message->inside_id.get());
            values[entry + ".payload.insidemessage.insideaction"] = canonical::number(message->inside_action.get());
            values[entry + ".payload.insidemessage.quoteflags.updateside"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.UpdateSide()));
            values[entry + ".payload.insidemessage.quoteflags.state"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.State()));
            values[entry + ".payload.insidemessage.quoteflags.askunsolicited"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.AskUnsolicited()));
            values[entry + ".payload.insidemessage.quoteflags.askpriced"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.AskPriced()));
            values[entry + ".payload.insidemessage.quoteflags.askbidwanted"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.AskBidWanted()));
            values[entry + ".payload.insidemessage.quoteflags.bidunsolicited"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.BidUnsolicited()));
            values[entry + ".payload.insidemessage.quoteflags.bidpriced"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.BidPriced()));
            values[entry + ".payload.insidemessage.quoteflags.bidaskwanted"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.BidAskWanted()));
            values[entry + ".payload.insidemessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.insidemessage.askprice"] = canonical::scaled(message->ask_price.integer(), -6);
            values[entry + ".payload.insidemessage.asksize"] = canonical::number(message->ask_size.get());
            values[entry + ".payload.insidemessage.asktimemilli"] = canonical::number(message->ask_time_milli.get());
            values[entry + ".payload.insidemessage.bidprice"] = canonical::scaled(message->bid_price.integer(), -6);
            values[entry + ".payload.insidemessage.bidsize"] = canonical::number(message->bid_size.get());
            values[entry + ".payload.insidemessage.bidtimemilli"] = canonical::number(message->bid_time_milli.get());
            values[entry + ".payload.insidemessage.asknumpricedmp"] = canonical::number(message->ask_num_priced_mp.get());
            values[entry + ".payload.insidemessage.bidnumpricedmp"] = canonical::number(message->bid_num_priced_mp.get());
        } else if (iterator.message_type == protocol::InsideUpdateMessage::message_type) {
            values[entry + ".payload"] = "packet.messageblock.message.payload.insideupdatemessage";
            [[maybe_unused]] const auto* message = protocol::InsideUpdateMessage::parse(iterator.message);
            values[entry + ".payload.insideupdatemessage.channelseqnum"] = canonical::number(message->channel_seq_num.get());
            values[entry + ".payload.insideupdatemessage.insideid"] = canonical::number(message->inside_id.get());
            values[entry + ".payload.insideupdatemessage.quoteflags.updateside"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.UpdateSide()));
            values[entry + ".payload.insideupdatemessage.quoteflags.state"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.State()));
            values[entry + ".payload.insideupdatemessage.quoteflags.askunsolicited"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.AskUnsolicited()));
            values[entry + ".payload.insideupdatemessage.quoteflags.askpriced"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.AskPriced()));
            values[entry + ".payload.insideupdatemessage.quoteflags.askbidwanted"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.AskBidWanted()));
            values[entry + ".payload.insideupdatemessage.quoteflags.bidunsolicited"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.BidUnsolicited()));
            values[entry + ".payload.insideupdatemessage.quoteflags.bidpriced"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.BidPriced()));
            values[entry + ".payload.insideupdatemessage.quoteflags.bidaskwanted"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.BidAskWanted()));
            values[entry + ".payload.insideupdatemessage.price"] = canonical::scaled(message->price.integer(), -6);
            values[entry + ".payload.insideupdatemessage.size"] = canonical::number(message->size.get());
            values[entry + ".payload.insideupdatemessage.insidetimemilli"] = canonical::number(message->inside_time_milli.get());
            values[entry + ".payload.insideupdatemessage.numpricedmp"] = canonical::number(message->num_priced_mp.get());
        } else if (iterator.message_type == protocol::ReferencePriceMessage::message_type) {
            values[entry + ".payload"] = "packet.messageblock.message.payload.referencepricemessage";
            [[maybe_unused]] const auto* message = protocol::ReferencePriceMessage::parse(iterator.message);
            values[entry + ".payload.referencepricemessage.channelseqnum"] = canonical::number(message->channel_seq_num.get());
            values[entry + ".payload.referencepricemessage.referencepriceid"] = canonical::number(message->reference_price_id.get());
            values[entry + ".payload.referencepricemessage.referencepriceaction"] = canonical::number(message->reference_price_action.get());
            values[entry + ".payload.referencepricemessage.quoteflags.updateside"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.UpdateSide()));
            values[entry + ".payload.referencepricemessage.quoteflags.state"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.State()));
            values[entry + ".payload.referencepricemessage.quoteflags.askunsolicited"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.AskUnsolicited()));
            values[entry + ".payload.referencepricemessage.quoteflags.askpriced"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.AskPriced()));
            values[entry + ".payload.referencepricemessage.quoteflags.askbidwanted"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.AskBidWanted()));
            values[entry + ".payload.referencepricemessage.quoteflags.bidunsolicited"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.BidUnsolicited()));
            values[entry + ".payload.referencepricemessage.quoteflags.bidpriced"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.BidPriced()));
            values[entry + ".payload.referencepricemessage.quoteflags.bidaskwanted"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.BidAskWanted()));
            values[entry + ".payload.referencepricemessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.referencepricemessage.askprice"] = canonical::scaled(message->ask_price.integer(), -6);
            values[entry + ".payload.referencepricemessage.asksize"] = canonical::number(message->ask_size.get());
            values[entry + ".payload.referencepricemessage.asktimemilli"] = canonical::number(message->ask_time_milli.get());
            values[entry + ".payload.referencepricemessage.bidprice"] = canonical::scaled(message->bid_price.integer(), -6);
            values[entry + ".payload.referencepricemessage.bidsize"] = canonical::number(message->bid_size.get());
            values[entry + ".payload.referencepricemessage.bidtimemilli"] = canonical::number(message->bid_time_milli.get());
        } else if (iterator.message_type == protocol::ReferencePriceUpdateMessage::message_type) {
            values[entry + ".payload"] = "packet.messageblock.message.payload.referencepriceupdatemessage";
            [[maybe_unused]] const auto* message = protocol::ReferencePriceUpdateMessage::parse(iterator.message);
            values[entry + ".payload.referencepriceupdatemessage.channelseqnum"] = canonical::number(message->channel_seq_num.get());
            values[entry + ".payload.referencepriceupdatemessage.referencepriceid"] = canonical::number(message->reference_price_id.get());
            values[entry + ".payload.referencepriceupdatemessage.quoteflags.updateside"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.UpdateSide()));
            values[entry + ".payload.referencepriceupdatemessage.quoteflags.state"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.State()));
            values[entry + ".payload.referencepriceupdatemessage.quoteflags.askunsolicited"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.AskUnsolicited()));
            values[entry + ".payload.referencepriceupdatemessage.quoteflags.askpriced"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.AskPriced()));
            values[entry + ".payload.referencepriceupdatemessage.quoteflags.askbidwanted"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.AskBidWanted()));
            values[entry + ".payload.referencepriceupdatemessage.quoteflags.bidunsolicited"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.BidUnsolicited()));
            values[entry + ".payload.referencepriceupdatemessage.quoteflags.bidpriced"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.BidPriced()));
            values[entry + ".payload.referencepriceupdatemessage.quoteflags.bidaskwanted"] = canonical::number(static_cast<std::uint64_t>(message->quote_flags.BidAskWanted()));
            values[entry + ".payload.referencepriceupdatemessage.price"] = canonical::scaled(message->price.integer(), -6);
            values[entry + ".payload.referencepriceupdatemessage.size"] = canonical::number(message->size.get());
            values[entry + ".payload.referencepriceupdatemessage.timemilli"] = canonical::number(message->time_milli.get());
        } else if (iterator.message_type == protocol::ExtendedSecurityMessage::message_type) {
            values[entry + ".payload"] = "packet.messageblock.message.payload.extendedsecuritymessage";
            [[maybe_unused]] const auto* message = protocol::ExtendedSecurityMessage::parse(iterator.message);
            values[entry + ".payload.extendedsecuritymessage.channelseqnum"] = canonical::number(message->channel_seq_num.get());
            values[entry + ".payload.extendedsecuritymessage.symbol"] = canonical::text(std::string(message->symbol.get()));
            values[entry + ".payload.extendedsecuritymessage.lastupdatemilli"] = canonical::number(message->last_update_milli.get());
            values[entry + ".payload.extendedsecuritymessage.securityaction"] = canonical::number(message->security_action.get());
            values[entry + ".payload.extendedsecuritymessage.otcissuerid"] = canonical::number(message->otc_issuer_id.get());
            values[entry + ".payload.extendedsecuritymessage.securitydesc"] = canonical::text(std::string(message->security_desc.get()));
            values[entry + ".payload.extendedsecuritymessage.shortname"] = canonical::text(std::string(message->short_name.get()));
            values[entry + ".payload.extendedsecuritymessage.assetclass"] = canonical::number(message->asset_class.get());
            values[entry + ".payload.extendedsecuritymessage.securitytype"] = canonical::text(std::string(message->security_type.get()));
            values[entry + ".payload.extendedsecuritymessage.primarymarket"] = canonical::text(std::string(message->primary_market.get()));
            values[entry + ".payload.extendedsecuritymessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.piggyback"] = canonical::number(static_cast<std::uint64_t>(message->extended_security_flags.Piggyback()));
            values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.caveatemptorwarning"] = canonical::number(static_cast<std::uint64_t>(message->extended_security_flags.CaveatEmptorWarning()));
            values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.qualifiedinstitutionalbuyersonly"] = canonical::number(static_cast<std::uint64_t>(message->extended_security_flags.QualifiedInstitutionalBuyersOnly()));
            values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.unsolicitedonly"] = canonical::number(static_cast<std::uint64_t>(message->extended_security_flags.UnsolicitedOnly()));
            values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.sponsoredstatus"] = canonical::number(static_cast<std::uint64_t>(message->extended_security_flags.SponsoredStatus()));
            values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.otclinkecneligible"] = canonical::number(static_cast<std::uint64_t>(message->extended_security_flags.OtcLinkEcnEligible()));
            values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.otclinkmessagingdisabled"] = canonical::number(static_cast<std::uint64_t>(message->extended_security_flags.OtcLinkMessagingDisabled()));
            values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.saturationeligible"] = canonical::number(static_cast<std::uint64_t>(message->extended_security_flags.SaturationEligible()));
            values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.investmentgrade"] = canonical::number(static_cast<std::uint64_t>(message->extended_security_flags.InvestmentGrade()));
            values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.tradingflat"] = canonical::number(static_cast<std::uint64_t>(message->extended_security_flags.TradingFlat()));
            values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.callable"] = canonical::number(static_cast<std::uint64_t>(message->extended_security_flags.Callable()));
            values[entry + ".payload.extendedsecuritymessage.tier"] = canonical::number(message->tier.get());
            values[entry + ".payload.extendedsecuritymessage.reportingstatus"] = canonical::text(canonical::character(message->reporting_status.get()));
            values[entry + ".payload.extendedsecuritymessage.disclosurestatus"] = canonical::number(message->disclosure_status.get());
            values[entry + ".payload.extendedsecuritymessage.securitystatus"] = canonical::text(canonical::character(message->security_status.get()));
            values[entry + ".payload.extendedsecuritymessage.parvalue"] = canonical::scaled(message->par_value.integer(), -6);
            values[entry + ".payload.extendedsecuritymessage.coupon"] = canonical::scaled(message->coupon.integer(), -6);
            values[entry + ".payload.extendedsecuritymessage.maturitydatemilli"] = canonical::number(message->maturity_date_milli.get());
            values[entry + ".payload.extendedsecuritymessage.callabledatemilli"] = canonical::number(message->callable_date_milli.get());
            values[entry + ".payload.extendedsecuritymessage.adrratio"] = canonical::scaled(message->adr_ratio.integer(), -6);
            values[entry + ".payload.extendedsecuritymessage.adrlevel"] = canonical::text(std::string(message->adr_level.get()));
        } else if (iterator.message_type == protocol::ExtendedSecurityNoCusipMessage::message_type) {
            values[entry + ".payload"] = "packet.messageblock.message.payload.extendedsecuritynocusipmessage";
            [[maybe_unused]] const auto* message = protocol::ExtendedSecurityNoCusipMessage::parse(iterator.message);
            values[entry + ".payload.extendedsecuritynocusipmessage.channelseqnum"] = canonical::number(message->channel_seq_num.get());
            values[entry + ".payload.extendedsecuritynocusipmessage.symbol"] = canonical::text(std::string(message->symbol.get()));
            values[entry + ".payload.extendedsecuritynocusipmessage.lastupdatemilli"] = canonical::number(message->last_update_milli.get());
            values[entry + ".payload.extendedsecuritynocusipmessage.securityaction"] = canonical::number(message->security_action.get());
            values[entry + ".payload.extendedsecuritynocusipmessage.otcissuerid"] = canonical::number(message->otc_issuer_id.get());
            values[entry + ".payload.extendedsecuritynocusipmessage.securitydesc"] = canonical::text(std::string(message->security_desc.get()));
            values[entry + ".payload.extendedsecuritynocusipmessage.shortname"] = canonical::text(std::string(message->short_name.get()));
            values[entry + ".payload.extendedsecuritynocusipmessage.assetclass"] = canonical::number(message->asset_class.get());
            values[entry + ".payload.extendedsecuritynocusipmessage.securitytype"] = canonical::text(std::string(message->security_type.get()));
            values[entry + ".payload.extendedsecuritynocusipmessage.primarymarket"] = canonical::text(std::string(message->primary_market.get()));
            values[entry + ".payload.extendedsecuritynocusipmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.extendedsecuritynocusipmessage.securityflags.piggyback"] = canonical::number(static_cast<std::uint64_t>(message->security_flags.Piggyback()));
            values[entry + ".payload.extendedsecuritynocusipmessage.securityflags.caveatemptorwarning"] = canonical::number(static_cast<std::uint64_t>(message->security_flags.CaveatEmptorWarning()));
            values[entry + ".payload.extendedsecuritynocusipmessage.securityflags.qualifiedinstitutionalbuyersonly"] = canonical::number(static_cast<std::uint64_t>(message->security_flags.QualifiedInstitutionalBuyersOnly()));
            values[entry + ".payload.extendedsecuritynocusipmessage.securityflags.unsolicitedonly"] = canonical::number(static_cast<std::uint64_t>(message->security_flags.UnsolicitedOnly()));
            values[entry + ".payload.extendedsecuritynocusipmessage.securityflags.bbquoted"] = canonical::number(static_cast<std::uint64_t>(message->security_flags.BbQuoted()));
            values[entry + ".payload.extendedsecuritynocusipmessage.securityflags.otclinkecneligible"] = canonical::number(static_cast<std::uint64_t>(message->security_flags.OtcLinkEcnEligible()));
            values[entry + ".payload.extendedsecuritynocusipmessage.securityflags.otclinkmessagingdisabled"] = canonical::number(static_cast<std::uint64_t>(message->security_flags.OtcLinkMessagingDisabled()));
            values[entry + ".payload.extendedsecuritynocusipmessage.securityflags.saturationeligible"] = canonical::number(static_cast<std::uint64_t>(message->security_flags.SaturationEligible()));
            values[entry + ".payload.extendedsecuritynocusipmessage.tier"] = canonical::number(message->tier.get());
            values[entry + ".payload.extendedsecuritynocusipmessage.reportingstatus"] = canonical::text(canonical::character(message->reporting_status.get()));
            values[entry + ".payload.extendedsecuritynocusipmessage.disclosurestatus"] = canonical::number(message->disclosure_status.get());
            values[entry + ".payload.extendedsecuritynocusipmessage.securitystatus"] = canonical::text(canonical::character(message->security_status.get()));
            values[entry + ".payload.extendedsecuritynocusipmessage.parvalue"] = canonical::scaled(message->par_value.integer(), -6);
            values[entry + ".payload.extendedsecuritynocusipmessage.coupon"] = canonical::scaled(message->coupon.integer(), -6);
            values[entry + ".payload.extendedsecuritynocusipmessage.maturitydatemilli"] = canonical::number(message->maturity_date_milli.get());
            values[entry + ".payload.extendedsecuritynocusipmessage.callabledatemilli"] = canonical::number(message->callable_date_milli.get());
            values[entry + ".payload.extendedsecuritynocusipmessage.adrratio"] = canonical::scaled(message->adr_ratio.integer(), -6);
            values[entry + ".payload.extendedsecuritynocusipmessage.adrlevel"] = canonical::text(std::string(message->adr_level.get()));
        } else if (iterator.message_type == protocol::TradeMessage::message_type) {
            values[entry + ".payload"] = "packet.messageblock.message.payload.trademessage";
            [[maybe_unused]] const auto* message = protocol::TradeMessage::parse(iterator.message);
            values[entry + ".payload.trademessage.channelseqnum"] = canonical::number(message->channel_seq_num.get());
            values[entry + ".payload.trademessage.tradeid"] = canonical::number(message->trade_id.get());
            values[entry + ".payload.trademessage.tradeaction"] = canonical::number(message->trade_action.get());
            values[entry + ".payload.trademessage.tradeflags"] = canonical::number(message->trade_flags.get());
            values[entry + ".payload.trademessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.trademessage.tradestatus.irregular"] = canonical::number(static_cast<std::uint64_t>(message->trade_status.Irregular()));
            values[entry + ".payload.trademessage.deprecated"] = canonical::text(std::string(message->deprecated.get()));
            values[entry + ".payload.trademessage.tradeprice"] = canonical::scaled(message->trade_price.integer(), -6);
            values[entry + ".payload.trademessage.tradesize"] = canonical::number(message->trade_size.get());
            values[entry + ".payload.trademessage.tradetimemilli"] = canonical::number(message->trade_time_milli.get());
        }
    }

    return values;
}

// Read each datagram of a sample with Modern and hold it to the model's values
int check(const char* name, const char* capture, const char* expected) {
    const char* packets = std::getenv("OMI_PACKETS_DIR");

    if (packets == nullptr) {
        std::printf("FAIL: OMI_PACKETS_DIR is not set\n");
        return 1;
    }

    const auto model = canonical::load(canonical::root() + "/" + expected);
    std::vector<std::pair<std::string, std::int64_t>> sources;
    sources.emplace_back(std::string{packets} + "/" + capture, 0);

    packet::PcapIterator captures(sources);
    std::size_t datagram = 0;
    int differences = 0;

    while (captures.advance()) {
        const packet::Frame frame(captures.data(), captures.length());

        if (!frame.valid() || !frame.is_udp()) { continue; }

        if (datagram >= model.size()) {
            std::printf("FAIL %s: more datagrams than the model read\n", name);
            return 1;
        }

        differences += canonical::compare(name, datagram, model[datagram], read(frame));
        ++datagram;
    }

    if (datagram != model.size()) {
        std::printf("FAIL %s: %zu datagrams, the model read %zu\n", name, datagram, model.size());
        return 1;
    }

    if (differences == 0) {
        std::printf("ok   %s: %zu datagrams\n", name, datagram);
    }

    return differences == 0 ? 0 : 1;
}

}

int main() {
    std::printf("== OtcMarkets.LinkAts.Multicast.Link.v4.3 (modern values)\n");
    int failures = 0;
    failures += check("EndOfSpinMessage", "OtcMarkets/LinkAts.Multicast.Link.v4.3/EndOfSpinMessage.pcap", "otcmarkets/linkats/multicast/link/v4.3/EndOfSpinMessage.values");
    failures += check("Heartbeat", "OtcMarkets/LinkAts.Multicast.Link.v4.3/Heartbeat.pcap", "otcmarkets/linkats/multicast/link/v4.3/Heartbeat.values");
    failures += check("MarketCloseMessage", "OtcMarkets/LinkAts.Multicast.Link.v4.3/MarketCloseMessage.pcap", "otcmarkets/linkats/multicast/link/v4.3/MarketCloseMessage.values");
    failures += check("MarketOpenMessage", "OtcMarkets/LinkAts.Multicast.Link.v4.3/MarketOpenMessage.pcap", "otcmarkets/linkats/multicast/link/v4.3/MarketOpenMessage.values");
    failures += check("QuoteMessage", "OtcMarkets/LinkAts.Multicast.Link.v4.3/QuoteMessage.pcap", "otcmarkets/linkats/multicast/link/v4.3/QuoteMessage.values");
    failures += check("QuoteUpdateMessage", "OtcMarkets/LinkAts.Multicast.Link.v4.3/QuoteUpdateMessage.pcap", "otcmarkets/linkats/multicast/link/v4.3/QuoteUpdateMessage.values");
    failures += check("SecurityMessage", "OtcMarkets/LinkAts.Multicast.Link.v4.3/SecurityMessage.pcap", "otcmarkets/linkats/multicast/link/v4.3/SecurityMessage.values");
    failures += check("StartOfSpinMessage", "OtcMarkets/LinkAts.Multicast.Link.v4.3/StartOfSpinMessage.pcap", "otcmarkets/linkats/multicast/link/v4.3/StartOfSpinMessage.values");
    return failures == 0 ? 0 : 1;
}
