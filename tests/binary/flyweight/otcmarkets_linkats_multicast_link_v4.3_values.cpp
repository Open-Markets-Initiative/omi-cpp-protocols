// OtcMarkets.LinkAts.Multicast.Link.v4.3 canonical values, through the Flyweight reader: every value Flyweight reads
// from each sample, at its address, held to what the model reads.

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
#include "tests/canonical/Canonical.hpp"
#include "cpp/binary/flyweight/otcmarkets/linkats/multicast/link/v4.3/definitions.hpp"

namespace protocol = ::otcmarkets::linkats::multicast::link::v4_3;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        values["packet.packetheader.packetsize"] = canonical::number(packet.packet_header().packet_size());
        values["packet.packetheader.seqnum"] = canonical::number(packet.packet_header().seq_num());
        values["packet.packetheader.packetflag.heartbeat"] = canonical::number(static_cast<std::uint64_t>(packet.packet_header().packet_flag().heartbeat()));
        values["packet.packetheader.packetflag.seqnumreset"] = canonical::number(static_cast<std::uint64_t>(packet.packet_header().packet_flag().seq_num_reset()));
        values["packet.packetheader.packetflag.replay"] = canonical::number(static_cast<std::uint64_t>(packet.packet_header().packet_flag().replay()));
        values["packet.packetheader.packetflag.test"] = canonical::number(static_cast<std::uint64_t>(packet.packet_header().packet_flag().test()));
        values["packet.packetheader.messagecount"] = canonical::number(packet.packet_header().message_count());
        values["packet.packetheader.packetmilli"] = canonical::number(packet.packet_header().packet_milli());
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
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messageblock.message.payload.startofspinmessage";
        values[entry + ".payload.startofspinmessage.channelseqnum"] = canonical::number(message.channel_seq_num());
        values[entry + ".payload.startofspinmessage.spintype"] = canonical::number(message.spin_type());
        values[entry + ".payload.startofspinmessage.spinstarttimemilli"] = canonical::number(message.spin_start_time_milli());
        values[entry + ".payload.startofspinmessage.spinlastseqnum"] = canonical::number(message.spin_last_seq_num());
    }

    void on(const protocol::EndOfSpinMessage& message) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messageblock.message.payload.endofspinmessage";
        values[entry + ".payload.endofspinmessage.channelseqnum"] = canonical::number(message.channel_seq_num());
        values[entry + ".payload.endofspinmessage.spintype"] = canonical::number(message.spin_type());
        values[entry + ".payload.endofspinmessage.spinmsgct"] = canonical::number(message.spin_msg_ct());
        values[entry + ".payload.endofspinmessage.spinendtimemilli"] = canonical::number(message.spin_end_time_milli());
        values[entry + ".payload.endofspinmessage.spinlastseqnum"] = canonical::number(message.spin_last_seq_num());
    }

    void on(const protocol::MarketOpenMessage& message) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messageblock.message.payload.marketopenmessage";
        values[entry + ".payload.marketopenmessage.channelseqnum"] = canonical::number(message.channel_seq_num());
        values[entry + ".payload.marketopenmessage.marketopen"] = canonical::number(message.market_open());
        values[entry + ".payload.marketopenmessage.marketclose"] = canonical::number(message.market_close());
    }

    void on(const protocol::MarketCloseMessage& message) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messageblock.message.payload.marketclosemessage";
        values[entry + ".payload.marketclosemessage.channelseqnum"] = canonical::number(message.channel_seq_num());
        values[entry + ".payload.marketclosemessage.marketclosetimemilli"] = canonical::number(message.market_close_time_milli());
        values[entry + ".payload.marketclosemessage.marketmsgct"] = canonical::number(message.market_msg_ct());
    }

    void on(const protocol::SecurityMessage& message) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messageblock.message.payload.securitymessage";
        values[entry + ".payload.securitymessage.channelseqnum"] = canonical::number(message.channel_seq_num());
        values[entry + ".payload.securitymessage.symbol"] = canonical::text(std::string(message.symbol()));
        values[entry + ".payload.securitymessage.lastupdatemilli"] = canonical::number(message.last_update_milli());
        values[entry + ".payload.securitymessage.securityaction"] = canonical::number(message.security_action());
        values[entry + ".payload.securitymessage.assetclass"] = canonical::number(message.asset_class());
        values[entry + ".payload.securitymessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.securitymessage.securityflags.piggyback"] = canonical::number(static_cast<std::uint64_t>(message.security_flags().piggyback()));
        values[entry + ".payload.securitymessage.securityflags.caveatemptorwarning"] = canonical::number(static_cast<std::uint64_t>(message.security_flags().caveat_emptor_warning()));
        values[entry + ".payload.securitymessage.securityflags.qualifiedinstitutionalbuyersonly"] = canonical::number(static_cast<std::uint64_t>(message.security_flags().qualified_institutional_buyers_only()));
        values[entry + ".payload.securitymessage.securityflags.unsolicitedonly"] = canonical::number(static_cast<std::uint64_t>(message.security_flags().unsolicited_only()));
        values[entry + ".payload.securitymessage.securityflags.bbquoted"] = canonical::number(static_cast<std::uint64_t>(message.security_flags().bb_quoted()));
        values[entry + ".payload.securitymessage.securityflags.otclinkecneligible"] = canonical::number(static_cast<std::uint64_t>(message.security_flags().otc_link_ecn_eligible()));
        values[entry + ".payload.securitymessage.securityflags.otclinkmessagingdisabled"] = canonical::number(static_cast<std::uint64_t>(message.security_flags().otc_link_messaging_disabled()));
        values[entry + ".payload.securitymessage.securityflags.saturationeligible"] = canonical::number(static_cast<std::uint64_t>(message.security_flags().saturation_eligible()));
        values[entry + ".payload.securitymessage.tier"] = canonical::number(message.tier());
        values[entry + ".payload.securitymessage.reportingstatus"] = canonical::text(canonical::character(message.reporting_status()));
        values[entry + ".payload.securitymessage.securitystatus"] = canonical::text(canonical::character(message.security_status()));
    }

    void on(const protocol::QuoteMessage& message) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messageblock.message.payload.quotemessage";
        values[entry + ".payload.quotemessage.channelseqnum"] = canonical::number(message.channel_seq_num());
        values[entry + ".payload.quotemessage.quoteid"] = canonical::number(message.quote_id());
        values[entry + ".payload.quotemessage.quoteaction"] = canonical::number(message.quote_action());
        values[entry + ".payload.quotemessage.quoteflags.updateside"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().update_side()));
        values[entry + ".payload.quotemessage.quoteflags.state"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().state()));
        values[entry + ".payload.quotemessage.quoteflags.askunsolicited"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().ask_unsolicited()));
        values[entry + ".payload.quotemessage.quoteflags.askpriced"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().ask_priced()));
        values[entry + ".payload.quotemessage.quoteflags.askbidwanted"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().ask_bid_wanted()));
        values[entry + ".payload.quotemessage.quoteflags.bidunsolicited"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().bid_unsolicited()));
        values[entry + ".payload.quotemessage.quoteflags.bidpriced"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().bid_priced()));
        values[entry + ".payload.quotemessage.quoteflags.bidaskwanted"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().bid_ask_wanted()));
        values[entry + ".payload.quotemessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.quotemessage.mpid"] = canonical::text(std::string(message.mpid()));
        values[entry + ".payload.quotemessage.askprice"] = canonical::scaled(message.ask_price().mantissa(), message.ask_price().exponent());
        values[entry + ".payload.quotemessage.asksize"] = canonical::number(message.ask_size());
        values[entry + ".payload.quotemessage.askqap"] = canonical::number(message.ask_qap());
        values[entry + ".payload.quotemessage.asktimemilli"] = canonical::number(message.ask_time_milli());
        values[entry + ".payload.quotemessage.bidprice"] = canonical::scaled(message.bid_price().mantissa(), message.bid_price().exponent());
        values[entry + ".payload.quotemessage.bidsize"] = canonical::number(message.bid_size());
        values[entry + ".payload.quotemessage.bidqap"] = canonical::number(message.bid_qap());
        values[entry + ".payload.quotemessage.bidtimemilli"] = canonical::number(message.bid_time_milli());
        values[entry + ".payload.quotemessage.quotereferenceid"] = canonical::number(message.quote_reference_id());
        values[entry + ".payload.quotemessage.extendedquoteflags.quotesaturated"] = canonical::number(static_cast<std::uint64_t>(message.extended_quote_flags().quote_saturated()));
        values[entry + ".payload.quotemessage.extendedquoteflags.bidautoex"] = canonical::number(static_cast<std::uint64_t>(message.extended_quote_flags().bid_auto_ex()));
        values[entry + ".payload.quotemessage.extendedquoteflags.offerautoex"] = canonical::number(static_cast<std::uint64_t>(message.extended_quote_flags().offer_auto_ex()));
        values[entry + ".payload.quotemessage.extendedquoteflags.nmsconditionalquote"] = canonical::number(static_cast<std::uint64_t>(message.extended_quote_flags().nms_conditional_quote()));
    }

    void on(const protocol::QuoteUpdateMessage& message) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messageblock.message.payload.quoteupdatemessage";
        values[entry + ".payload.quoteupdatemessage.channelseqnum"] = canonical::number(message.channel_seq_num());
        values[entry + ".payload.quoteupdatemessage.quoteid"] = canonical::number(message.quote_id());
        values[entry + ".payload.quoteupdatemessage.quoteflags.updateside"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().update_side()));
        values[entry + ".payload.quoteupdatemessage.quoteflags.state"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().state()));
        values[entry + ".payload.quoteupdatemessage.quoteflags.askunsolicited"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().ask_unsolicited()));
        values[entry + ".payload.quoteupdatemessage.quoteflags.askpriced"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().ask_priced()));
        values[entry + ".payload.quoteupdatemessage.quoteflags.askbidwanted"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().ask_bid_wanted()));
        values[entry + ".payload.quoteupdatemessage.quoteflags.bidunsolicited"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().bid_unsolicited()));
        values[entry + ".payload.quoteupdatemessage.quoteflags.bidpriced"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().bid_priced()));
        values[entry + ".payload.quoteupdatemessage.quoteflags.bidaskwanted"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().bid_ask_wanted()));
        values[entry + ".payload.quoteupdatemessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.quoteupdatemessage.size"] = canonical::number(message.size());
        values[entry + ".payload.quoteupdatemessage.qap"] = canonical::number(message.qap());
        values[entry + ".payload.quoteupdatemessage.quotetimemilli"] = canonical::number(message.quote_time_milli());
        values[entry + ".payload.quoteupdatemessage.quotereferenceid"] = canonical::number(message.quote_reference_id());
        values[entry + ".payload.quoteupdatemessage.extendedquoteflags.quotesaturated"] = canonical::number(static_cast<std::uint64_t>(message.extended_quote_flags().quote_saturated()));
        values[entry + ".payload.quoteupdatemessage.extendedquoteflags.bidautoex"] = canonical::number(static_cast<std::uint64_t>(message.extended_quote_flags().bid_auto_ex()));
        values[entry + ".payload.quoteupdatemessage.extendedquoteflags.offerautoex"] = canonical::number(static_cast<std::uint64_t>(message.extended_quote_flags().offer_auto_ex()));
        values[entry + ".payload.quoteupdatemessage.extendedquoteflags.nmsconditionalquote"] = canonical::number(static_cast<std::uint64_t>(message.extended_quote_flags().nms_conditional_quote()));
    }

    void on(const protocol::InsideMessage& message) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messageblock.message.payload.insidemessage";
        values[entry + ".payload.insidemessage.channelseqnum"] = canonical::number(message.channel_seq_num());
        values[entry + ".payload.insidemessage.insideid"] = canonical::number(message.inside_id());
        values[entry + ".payload.insidemessage.insideaction"] = canonical::number(message.inside_action());
        values[entry + ".payload.insidemessage.quoteflags.updateside"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().update_side()));
        values[entry + ".payload.insidemessage.quoteflags.state"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().state()));
        values[entry + ".payload.insidemessage.quoteflags.askunsolicited"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().ask_unsolicited()));
        values[entry + ".payload.insidemessage.quoteflags.askpriced"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().ask_priced()));
        values[entry + ".payload.insidemessage.quoteflags.askbidwanted"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().ask_bid_wanted()));
        values[entry + ".payload.insidemessage.quoteflags.bidunsolicited"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().bid_unsolicited()));
        values[entry + ".payload.insidemessage.quoteflags.bidpriced"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().bid_priced()));
        values[entry + ".payload.insidemessage.quoteflags.bidaskwanted"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().bid_ask_wanted()));
        values[entry + ".payload.insidemessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.insidemessage.askprice"] = canonical::scaled(message.ask_price().mantissa(), message.ask_price().exponent());
        values[entry + ".payload.insidemessage.asksize"] = canonical::number(message.ask_size());
        values[entry + ".payload.insidemessage.asktimemilli"] = canonical::number(message.ask_time_milli());
        values[entry + ".payload.insidemessage.bidprice"] = canonical::scaled(message.bid_price().mantissa(), message.bid_price().exponent());
        values[entry + ".payload.insidemessage.bidsize"] = canonical::number(message.bid_size());
        values[entry + ".payload.insidemessage.bidtimemilli"] = canonical::number(message.bid_time_milli());
        values[entry + ".payload.insidemessage.asknumpricedmp"] = canonical::number(message.ask_num_priced_mp());
        values[entry + ".payload.insidemessage.bidnumpricedmp"] = canonical::number(message.bid_num_priced_mp());
    }

    void on(const protocol::InsideUpdateMessage& message) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messageblock.message.payload.insideupdatemessage";
        values[entry + ".payload.insideupdatemessage.channelseqnum"] = canonical::number(message.channel_seq_num());
        values[entry + ".payload.insideupdatemessage.insideid"] = canonical::number(message.inside_id());
        values[entry + ".payload.insideupdatemessage.quoteflags.updateside"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().update_side()));
        values[entry + ".payload.insideupdatemessage.quoteflags.state"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().state()));
        values[entry + ".payload.insideupdatemessage.quoteflags.askunsolicited"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().ask_unsolicited()));
        values[entry + ".payload.insideupdatemessage.quoteflags.askpriced"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().ask_priced()));
        values[entry + ".payload.insideupdatemessage.quoteflags.askbidwanted"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().ask_bid_wanted()));
        values[entry + ".payload.insideupdatemessage.quoteflags.bidunsolicited"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().bid_unsolicited()));
        values[entry + ".payload.insideupdatemessage.quoteflags.bidpriced"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().bid_priced()));
        values[entry + ".payload.insideupdatemessage.quoteflags.bidaskwanted"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().bid_ask_wanted()));
        values[entry + ".payload.insideupdatemessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.insideupdatemessage.size"] = canonical::number(message.size());
        values[entry + ".payload.insideupdatemessage.insidetimemilli"] = canonical::number(message.inside_time_milli());
        values[entry + ".payload.insideupdatemessage.numpricedmp"] = canonical::number(message.num_priced_mp());
    }

    void on(const protocol::ReferencePriceMessage& message) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messageblock.message.payload.referencepricemessage";
        values[entry + ".payload.referencepricemessage.channelseqnum"] = canonical::number(message.channel_seq_num());
        values[entry + ".payload.referencepricemessage.referencepriceid"] = canonical::number(message.reference_price_id());
        values[entry + ".payload.referencepricemessage.referencepriceaction"] = canonical::number(message.reference_price_action());
        values[entry + ".payload.referencepricemessage.quoteflags.updateside"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().update_side()));
        values[entry + ".payload.referencepricemessage.quoteflags.state"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().state()));
        values[entry + ".payload.referencepricemessage.quoteflags.askunsolicited"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().ask_unsolicited()));
        values[entry + ".payload.referencepricemessage.quoteflags.askpriced"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().ask_priced()));
        values[entry + ".payload.referencepricemessage.quoteflags.askbidwanted"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().ask_bid_wanted()));
        values[entry + ".payload.referencepricemessage.quoteflags.bidunsolicited"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().bid_unsolicited()));
        values[entry + ".payload.referencepricemessage.quoteflags.bidpriced"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().bid_priced()));
        values[entry + ".payload.referencepricemessage.quoteflags.bidaskwanted"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().bid_ask_wanted()));
        values[entry + ".payload.referencepricemessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.referencepricemessage.askprice"] = canonical::scaled(message.ask_price().mantissa(), message.ask_price().exponent());
        values[entry + ".payload.referencepricemessage.asksize"] = canonical::number(message.ask_size());
        values[entry + ".payload.referencepricemessage.asktimemilli"] = canonical::number(message.ask_time_milli());
        values[entry + ".payload.referencepricemessage.bidprice"] = canonical::scaled(message.bid_price().mantissa(), message.bid_price().exponent());
        values[entry + ".payload.referencepricemessage.bidsize"] = canonical::number(message.bid_size());
        values[entry + ".payload.referencepricemessage.bidtimemilli"] = canonical::number(message.bid_time_milli());
    }

    void on(const protocol::ReferencePriceUpdateMessage& message) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messageblock.message.payload.referencepriceupdatemessage";
        values[entry + ".payload.referencepriceupdatemessage.channelseqnum"] = canonical::number(message.channel_seq_num());
        values[entry + ".payload.referencepriceupdatemessage.referencepriceid"] = canonical::number(message.reference_price_id());
        values[entry + ".payload.referencepriceupdatemessage.quoteflags.updateside"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().update_side()));
        values[entry + ".payload.referencepriceupdatemessage.quoteflags.state"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().state()));
        values[entry + ".payload.referencepriceupdatemessage.quoteflags.askunsolicited"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().ask_unsolicited()));
        values[entry + ".payload.referencepriceupdatemessage.quoteflags.askpriced"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().ask_priced()));
        values[entry + ".payload.referencepriceupdatemessage.quoteflags.askbidwanted"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().ask_bid_wanted()));
        values[entry + ".payload.referencepriceupdatemessage.quoteflags.bidunsolicited"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().bid_unsolicited()));
        values[entry + ".payload.referencepriceupdatemessage.quoteflags.bidpriced"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().bid_priced()));
        values[entry + ".payload.referencepriceupdatemessage.quoteflags.bidaskwanted"] = canonical::number(static_cast<std::uint64_t>(message.quote_flags().bid_ask_wanted()));
        values[entry + ".payload.referencepriceupdatemessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.referencepriceupdatemessage.size"] = canonical::number(message.size());
        values[entry + ".payload.referencepriceupdatemessage.timemilli"] = canonical::number(message.time_milli());
    }

    void on(const protocol::ExtendedSecurityMessage& message) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messageblock.message.payload.extendedsecuritymessage";
        values[entry + ".payload.extendedsecuritymessage.channelseqnum"] = canonical::number(message.channel_seq_num());
        values[entry + ".payload.extendedsecuritymessage.symbol"] = canonical::text(std::string(message.symbol()));
        values[entry + ".payload.extendedsecuritymessage.lastupdatemilli"] = canonical::number(message.last_update_milli());
        values[entry + ".payload.extendedsecuritymessage.securityaction"] = canonical::number(message.security_action());
        values[entry + ".payload.extendedsecuritymessage.otcissuerid"] = canonical::number(message.otc_issuer_id());
        values[entry + ".payload.extendedsecuritymessage.securitydesc"] = canonical::text(std::string(message.security_desc()));
        values[entry + ".payload.extendedsecuritymessage.shortname"] = canonical::text(std::string(message.short_name()));
        values[entry + ".payload.extendedsecuritymessage.assetclass"] = canonical::number(message.asset_class());
        values[entry + ".payload.extendedsecuritymessage.securitytype"] = canonical::text(std::string(message.security_type()));
        values[entry + ".payload.extendedsecuritymessage.primarymarket"] = canonical::text(std::string(message.primary_market()));
        values[entry + ".payload.extendedsecuritymessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.piggyback"] = canonical::number(static_cast<std::uint64_t>(message.extended_security_flags().piggyback()));
        values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.caveatemptorwarning"] = canonical::number(static_cast<std::uint64_t>(message.extended_security_flags().caveat_emptor_warning()));
        values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.qualifiedinstitutionalbuyersonly"] = canonical::number(static_cast<std::uint64_t>(message.extended_security_flags().qualified_institutional_buyers_only()));
        values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.unsolicitedonly"] = canonical::number(static_cast<std::uint64_t>(message.extended_security_flags().unsolicited_only()));
        values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.sponsoredstatus"] = canonical::number(static_cast<std::uint64_t>(message.extended_security_flags().sponsored_status()));
        values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.otclinkecneligible"] = canonical::number(static_cast<std::uint64_t>(message.extended_security_flags().otc_link_ecn_eligible()));
        values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.otclinkmessagingdisabled"] = canonical::number(static_cast<std::uint64_t>(message.extended_security_flags().otc_link_messaging_disabled()));
        values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.saturationeligible"] = canonical::number(static_cast<std::uint64_t>(message.extended_security_flags().saturation_eligible()));
        values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.investmentgrade"] = canonical::number(static_cast<std::uint64_t>(message.extended_security_flags().investment_grade()));
        values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.tradingflat"] = canonical::number(static_cast<std::uint64_t>(message.extended_security_flags().trading_flat()));
        values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.callable"] = canonical::number(static_cast<std::uint64_t>(message.extended_security_flags().callable()));
        values[entry + ".payload.extendedsecuritymessage.tier"] = canonical::number(message.tier());
        values[entry + ".payload.extendedsecuritymessage.reportingstatus"] = canonical::text(canonical::character(message.reporting_status()));
        values[entry + ".payload.extendedsecuritymessage.disclosurestatus"] = canonical::number(message.disclosure_status());
        values[entry + ".payload.extendedsecuritymessage.securitystatus"] = canonical::text(canonical::character(message.security_status()));
        values[entry + ".payload.extendedsecuritymessage.parvalue"] = canonical::scaled(message.par_value().mantissa(), message.par_value().exponent());
        values[entry + ".payload.extendedsecuritymessage.coupon"] = canonical::scaled(message.coupon().mantissa(), message.coupon().exponent());
        values[entry + ".payload.extendedsecuritymessage.maturitydatemilli"] = canonical::number(message.maturity_date_milli());
        values[entry + ".payload.extendedsecuritymessage.callabledatemilli"] = canonical::number(message.callable_date_milli());
        values[entry + ".payload.extendedsecuritymessage.adrratio"] = canonical::scaled(message.adr_ratio().mantissa(), message.adr_ratio().exponent());
        values[entry + ".payload.extendedsecuritymessage.adrlevel"] = canonical::text(std::string(message.adr_level()));
    }

    void on(const protocol::ExtendedSecurityNoCusipMessage& message) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messageblock.message.payload.extendedsecuritynocusipmessage";
        values[entry + ".payload.extendedsecuritynocusipmessage.channelseqnum"] = canonical::number(message.channel_seq_num());
        values[entry + ".payload.extendedsecuritynocusipmessage.symbol"] = canonical::text(std::string(message.symbol()));
        values[entry + ".payload.extendedsecuritynocusipmessage.lastupdatemilli"] = canonical::number(message.last_update_milli());
        values[entry + ".payload.extendedsecuritynocusipmessage.securityaction"] = canonical::number(message.security_action());
        values[entry + ".payload.extendedsecuritynocusipmessage.otcissuerid"] = canonical::number(message.otc_issuer_id());
        values[entry + ".payload.extendedsecuritynocusipmessage.securitydesc"] = canonical::text(std::string(message.security_desc()));
        values[entry + ".payload.extendedsecuritynocusipmessage.shortname"] = canonical::text(std::string(message.short_name()));
        values[entry + ".payload.extendedsecuritynocusipmessage.assetclass"] = canonical::number(message.asset_class());
        values[entry + ".payload.extendedsecuritynocusipmessage.securitytype"] = canonical::text(std::string(message.security_type()));
        values[entry + ".payload.extendedsecuritynocusipmessage.primarymarket"] = canonical::text(std::string(message.primary_market()));
        values[entry + ".payload.extendedsecuritynocusipmessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.extendedsecuritynocusipmessage.securityflags.piggyback"] = canonical::number(static_cast<std::uint64_t>(message.security_flags().piggyback()));
        values[entry + ".payload.extendedsecuritynocusipmessage.securityflags.caveatemptorwarning"] = canonical::number(static_cast<std::uint64_t>(message.security_flags().caveat_emptor_warning()));
        values[entry + ".payload.extendedsecuritynocusipmessage.securityflags.qualifiedinstitutionalbuyersonly"] = canonical::number(static_cast<std::uint64_t>(message.security_flags().qualified_institutional_buyers_only()));
        values[entry + ".payload.extendedsecuritynocusipmessage.securityflags.unsolicitedonly"] = canonical::number(static_cast<std::uint64_t>(message.security_flags().unsolicited_only()));
        values[entry + ".payload.extendedsecuritynocusipmessage.securityflags.bbquoted"] = canonical::number(static_cast<std::uint64_t>(message.security_flags().bb_quoted()));
        values[entry + ".payload.extendedsecuritynocusipmessage.securityflags.otclinkecneligible"] = canonical::number(static_cast<std::uint64_t>(message.security_flags().otc_link_ecn_eligible()));
        values[entry + ".payload.extendedsecuritynocusipmessage.securityflags.otclinkmessagingdisabled"] = canonical::number(static_cast<std::uint64_t>(message.security_flags().otc_link_messaging_disabled()));
        values[entry + ".payload.extendedsecuritynocusipmessage.securityflags.saturationeligible"] = canonical::number(static_cast<std::uint64_t>(message.security_flags().saturation_eligible()));
        values[entry + ".payload.extendedsecuritynocusipmessage.tier"] = canonical::number(message.tier());
        values[entry + ".payload.extendedsecuritynocusipmessage.reportingstatus"] = canonical::text(canonical::character(message.reporting_status()));
        values[entry + ".payload.extendedsecuritynocusipmessage.disclosurestatus"] = canonical::number(message.disclosure_status());
        values[entry + ".payload.extendedsecuritynocusipmessage.securitystatus"] = canonical::text(canonical::character(message.security_status()));
        values[entry + ".payload.extendedsecuritynocusipmessage.parvalue"] = canonical::scaled(message.par_value().mantissa(), message.par_value().exponent());
        values[entry + ".payload.extendedsecuritynocusipmessage.coupon"] = canonical::scaled(message.coupon().mantissa(), message.coupon().exponent());
        values[entry + ".payload.extendedsecuritynocusipmessage.maturitydatemilli"] = canonical::number(message.maturity_date_milli());
        values[entry + ".payload.extendedsecuritynocusipmessage.callabledatemilli"] = canonical::number(message.callable_date_milli());
        values[entry + ".payload.extendedsecuritynocusipmessage.adrratio"] = canonical::scaled(message.adr_ratio().mantissa(), message.adr_ratio().exponent());
        values[entry + ".payload.extendedsecuritynocusipmessage.adrlevel"] = canonical::text(std::string(message.adr_level()));
    }

    void on(const protocol::TradeMessage& message) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messageblock.message.payload.trademessage";
        values[entry + ".payload.trademessage.channelseqnum"] = canonical::number(message.channel_seq_num());
        values[entry + ".payload.trademessage.tradeid"] = canonical::number(message.trade_id());
        values[entry + ".payload.trademessage.tradeaction"] = canonical::number(message.trade_action());
        values[entry + ".payload.trademessage.tradeflags"] = canonical::number(message.trade_flags());
        values[entry + ".payload.trademessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.trademessage.tradestatus.irregular"] = canonical::number(static_cast<std::uint64_t>(message.trade_status().irregular()));
        values[entry + ".payload.trademessage.deprecated"] = canonical::text(std::string(message.deprecated()));
        values[entry + ".payload.trademessage.tradeprice"] = canonical::scaled(message.trade_price().mantissa(), message.trade_price().exponent());
        values[entry + ".payload.trademessage.tradesize"] = canonical::number(message.trade_size());
        values[entry + ".payload.trademessage.tradetimemilli"] = canonical::number(message.trade_time_milli());
    }
};

// The values the Flyweight reader reads from one datagram, by indexed address. A datagram it cannot
// read is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::PacketReader::read(std::span<const std::byte>(frame.payload, frame.payload_len), reader);
    } catch (const protocol::DecodeError& error) {
        reader.values["(does not decode)"] = error.what();
    }

    return reader.values;
}

// Read each datagram of a sample with Flyweight and hold it to the model's values
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
    std::printf("== OtcMarkets.LinkAts.Multicast.Link.v4.3 (flyweight values)\n");
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
