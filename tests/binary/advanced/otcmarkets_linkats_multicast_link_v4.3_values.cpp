// OtcMarkets.LinkAts.Multicast.Link.v4.3 canonical values, through the Advanced session layer: every value Advanced
// reads from each sample, at its address, held to what the model reads.

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
#include "cpp/binary/advanced/otcmarkets/linkats/multicast/link/v4.3/messages/session.hpp"

namespace protocol = ::otcmarkets::linkats::multicast::link::v4_3;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::packet_header& header, const packet::Frame&) {
        values["packet.packetheader.packetsize"] = canonical::number(header.packet_size.get().value());
        values["packet.packetheader.seqnum"] = canonical::number(header.seq_num.get().value());
        values["packet.packetheader.packetflag.heartbeat"] = canonical::number(static_cast<std::uint64_t>(header.packet_flag.has_heartbeat()));
        values["packet.packetheader.packetflag.seqnumreset"] = canonical::number(static_cast<std::uint64_t>(header.packet_flag.has_seq_num_reset()));
        values["packet.packetheader.packetflag.replay"] = canonical::number(static_cast<std::uint64_t>(header.packet_flag.has_replay()));
        values["packet.packetheader.packetflag.test"] = canonical::number(static_cast<std::uint64_t>(header.packet_flag.has_test()));
        values["packet.packetheader.messagecount"] = canonical::number(header.message_count.get().value());
        values["packet.packetheader.packetmilli"] = canonical::number(header.packet_milli.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::packet_header&) {
        ++index;
    }

    void on_message(const protocol::start_of_spin_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messageblock.message.payload.startofspinmessage";
        values[entry + ".payload.startofspinmessage.channelseqnum"] = canonical::number(message.fields.channel_seq_num.get().value());
        values[entry + ".payload.startofspinmessage.spintype"] = canonical::number(message.fields.spin_type.get().value());
        values[entry + ".payload.startofspinmessage.spinstarttimemilli"] = canonical::number(message.fields.spin_start_time_milli.get().value());
        values[entry + ".payload.startofspinmessage.spinlastseqnum"] = canonical::number(message.fields.spin_last_seq_num.get().value());
    }

    void on_message(const protocol::end_of_spin_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messageblock.message.payload.endofspinmessage";
        values[entry + ".payload.endofspinmessage.channelseqnum"] = canonical::number(message.fields.channel_seq_num.get().value());
        values[entry + ".payload.endofspinmessage.spintype"] = canonical::number(message.fields.spin_type.get().value());
        values[entry + ".payload.endofspinmessage.spinmsgct"] = canonical::number(message.fields.spin_msg_ct.get().value());
        values[entry + ".payload.endofspinmessage.spinendtimemilli"] = canonical::number(message.fields.spin_end_time_milli.get().value());
        values[entry + ".payload.endofspinmessage.spinlastseqnum"] = canonical::number(message.fields.spin_last_seq_num.get().value());
    }

    void on_message(const protocol::market_open_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messageblock.message.payload.marketopenmessage";
        values[entry + ".payload.marketopenmessage.channelseqnum"] = canonical::number(message.fields.channel_seq_num.get().value());
        values[entry + ".payload.marketopenmessage.marketopen"] = canonical::number(message.fields.market_open.get().value());
        values[entry + ".payload.marketopenmessage.marketclose"] = canonical::number(message.fields.market_close.get().value());
    }

    void on_message(const protocol::market_close_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messageblock.message.payload.marketclosemessage";
        values[entry + ".payload.marketclosemessage.channelseqnum"] = canonical::number(message.fields.channel_seq_num.get().value());
        values[entry + ".payload.marketclosemessage.marketclosetimemilli"] = canonical::number(message.fields.market_close_time_milli.get().value());
        values[entry + ".payload.marketclosemessage.marketmsgct"] = canonical::number(message.fields.market_msg_ct.get().value());
    }

    void on_message(const protocol::security_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messageblock.message.payload.securitymessage";
        values[entry + ".payload.securitymessage.channelseqnum"] = canonical::number(message.fields.channel_seq_num.get().value());
        values[entry + ".payload.securitymessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()));
        values[entry + ".payload.securitymessage.lastupdatemilli"] = canonical::number(message.fields.last_update_milli.get().value());
        values[entry + ".payload.securitymessage.securityaction"] = canonical::number(message.fields.security_action.get().value());
        values[entry + ".payload.securitymessage.assetclass"] = canonical::number(message.fields.asset_class.get().value());
        values[entry + ".payload.securitymessage.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.securitymessage.securityflags.piggyback"] = canonical::number(static_cast<std::uint64_t>(message.fields.security_flags.has_piggyback()));
        values[entry + ".payload.securitymessage.securityflags.caveatemptorwarning"] = canonical::number(static_cast<std::uint64_t>(message.fields.security_flags.has_caveat_emptor_warning()));
        values[entry + ".payload.securitymessage.securityflags.qualifiedinstitutionalbuyersonly"] = canonical::number(static_cast<std::uint64_t>(message.fields.security_flags.has_qualified_institutional_buyers_only()));
        values[entry + ".payload.securitymessage.securityflags.unsolicitedonly"] = canonical::number(static_cast<std::uint64_t>(message.fields.security_flags.has_unsolicited_only()));
        values[entry + ".payload.securitymessage.securityflags.bbquoted"] = canonical::number(static_cast<std::uint64_t>(message.fields.security_flags.has_bb_quoted()));
        values[entry + ".payload.securitymessage.securityflags.otclinkecneligible"] = canonical::number(static_cast<std::uint64_t>(message.fields.security_flags.has_otc_link_ecn_eligible()));
        values[entry + ".payload.securitymessage.securityflags.otclinkmessagingdisabled"] = canonical::number(static_cast<std::uint64_t>(message.fields.security_flags.has_otc_link_messaging_disabled()));
        values[entry + ".payload.securitymessage.securityflags.saturationeligible"] = canonical::number(static_cast<std::uint64_t>(message.fields.security_flags.has_saturation_eligible()));
        values[entry + ".payload.securitymessage.tier"] = canonical::number(message.fields.tier.get().value());
        values[entry + ".payload.securitymessage.reportingstatus"] = canonical::text(canonical::character(message.fields.reporting_status.get().value()));
        values[entry + ".payload.securitymessage.securitystatus"] = canonical::text(canonical::character(message.fields.security_status.get().value()));
    }

    void on_message(const protocol::quote_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messageblock.message.payload.quotemessage";
        values[entry + ".payload.quotemessage.channelseqnum"] = canonical::number(message.fields.channel_seq_num.get().value());
        values[entry + ".payload.quotemessage.quoteid"] = canonical::number(message.fields.quote_id.get().value());
        values[entry + ".payload.quotemessage.quoteaction"] = canonical::number(message.fields.quote_action.get().value());
        values[entry + ".payload.quotemessage.quoteflags.updateside"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_update_side()));
        values[entry + ".payload.quotemessage.quoteflags.state"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_state()));
        values[entry + ".payload.quotemessage.quoteflags.askunsolicited"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_ask_unsolicited()));
        values[entry + ".payload.quotemessage.quoteflags.askpriced"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_ask_priced()));
        values[entry + ".payload.quotemessage.quoteflags.askbidwanted"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_ask_bid_wanted()));
        values[entry + ".payload.quotemessage.quoteflags.bidunsolicited"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_bid_unsolicited()));
        values[entry + ".payload.quotemessage.quoteflags.bidpriced"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_bid_priced()));
        values[entry + ".payload.quotemessage.quoteflags.bidaskwanted"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_bid_ask_wanted()));
        values[entry + ".payload.quotemessage.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.quotemessage.mpid"] = canonical::text(std::string(message.fields.mpid.get().value()));
        values[entry + ".payload.quotemessage.askprice"] = canonical::scaled(message.fields.ask_price.get().value(), -6);
        values[entry + ".payload.quotemessage.asksize"] = canonical::number(message.fields.ask_size.get().value());
        values[entry + ".payload.quotemessage.askqap"] = canonical::number(message.fields.ask_qap.get().value());
        values[entry + ".payload.quotemessage.asktimemilli"] = canonical::number(message.fields.ask_time_milli.get().value());
        values[entry + ".payload.quotemessage.bidprice"] = canonical::scaled(message.fields.bid_price.get().value(), -6);
        values[entry + ".payload.quotemessage.bidsize"] = canonical::number(message.fields.bid_size.get().value());
        values[entry + ".payload.quotemessage.bidqap"] = canonical::number(message.fields.bid_qap.get().value());
        values[entry + ".payload.quotemessage.bidtimemilli"] = canonical::number(message.fields.bid_time_milli.get().value());
        values[entry + ".payload.quotemessage.quotereferenceid"] = canonical::number(message.fields.quote_reference_id.get().value());
        values[entry + ".payload.quotemessage.extendedquoteflags.quotesaturated"] = canonical::number(static_cast<std::uint64_t>(message.fields.extended_quote_flags.has_quote_saturated()));
        values[entry + ".payload.quotemessage.extendedquoteflags.bidautoex"] = canonical::number(static_cast<std::uint64_t>(message.fields.extended_quote_flags.has_bid_auto_ex()));
        values[entry + ".payload.quotemessage.extendedquoteflags.offerautoex"] = canonical::number(static_cast<std::uint64_t>(message.fields.extended_quote_flags.has_offer_auto_ex()));
        values[entry + ".payload.quotemessage.extendedquoteflags.nmsconditionalquote"] = canonical::number(static_cast<std::uint64_t>(message.fields.extended_quote_flags.has_nms_conditional_quote()));
    }

    void on_message(const protocol::quote_update_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messageblock.message.payload.quoteupdatemessage";
        values[entry + ".payload.quoteupdatemessage.channelseqnum"] = canonical::number(message.fields.channel_seq_num.get().value());
        values[entry + ".payload.quoteupdatemessage.quoteid"] = canonical::number(message.fields.quote_id.get().value());
        values[entry + ".payload.quoteupdatemessage.quoteflags.updateside"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_update_side()));
        values[entry + ".payload.quoteupdatemessage.quoteflags.state"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_state()));
        values[entry + ".payload.quoteupdatemessage.quoteflags.askunsolicited"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_ask_unsolicited()));
        values[entry + ".payload.quoteupdatemessage.quoteflags.askpriced"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_ask_priced()));
        values[entry + ".payload.quoteupdatemessage.quoteflags.askbidwanted"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_ask_bid_wanted()));
        values[entry + ".payload.quoteupdatemessage.quoteflags.bidunsolicited"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_bid_unsolicited()));
        values[entry + ".payload.quoteupdatemessage.quoteflags.bidpriced"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_bid_priced()));
        values[entry + ".payload.quoteupdatemessage.quoteflags.bidaskwanted"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_bid_ask_wanted()));
        values[entry + ".payload.quoteupdatemessage.price"] = canonical::scaled(message.fields.price.get().value(), -6);
        values[entry + ".payload.quoteupdatemessage.size"] = canonical::number(message.fields.size.get().value());
        values[entry + ".payload.quoteupdatemessage.qap"] = canonical::number(message.fields.qap.get().value());
        values[entry + ".payload.quoteupdatemessage.quotetimemilli"] = canonical::number(message.fields.quote_time_milli.get().value());
        values[entry + ".payload.quoteupdatemessage.quotereferenceid"] = canonical::number(message.fields.quote_reference_id.get().value());
        values[entry + ".payload.quoteupdatemessage.extendedquoteflags.quotesaturated"] = canonical::number(static_cast<std::uint64_t>(message.fields.extended_quote_flags.has_quote_saturated()));
        values[entry + ".payload.quoteupdatemessage.extendedquoteflags.bidautoex"] = canonical::number(static_cast<std::uint64_t>(message.fields.extended_quote_flags.has_bid_auto_ex()));
        values[entry + ".payload.quoteupdatemessage.extendedquoteflags.offerautoex"] = canonical::number(static_cast<std::uint64_t>(message.fields.extended_quote_flags.has_offer_auto_ex()));
        values[entry + ".payload.quoteupdatemessage.extendedquoteflags.nmsconditionalquote"] = canonical::number(static_cast<std::uint64_t>(message.fields.extended_quote_flags.has_nms_conditional_quote()));
    }

    void on_message(const protocol::inside_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messageblock.message.payload.insidemessage";
        values[entry + ".payload.insidemessage.channelseqnum"] = canonical::number(message.fields.channel_seq_num.get().value());
        values[entry + ".payload.insidemessage.insideid"] = canonical::number(message.fields.inside_id.get().value());
        values[entry + ".payload.insidemessage.insideaction"] = canonical::number(message.fields.inside_action.get().value());
        values[entry + ".payload.insidemessage.quoteflags.updateside"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_update_side()));
        values[entry + ".payload.insidemessage.quoteflags.state"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_state()));
        values[entry + ".payload.insidemessage.quoteflags.askunsolicited"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_ask_unsolicited()));
        values[entry + ".payload.insidemessage.quoteflags.askpriced"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_ask_priced()));
        values[entry + ".payload.insidemessage.quoteflags.askbidwanted"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_ask_bid_wanted()));
        values[entry + ".payload.insidemessage.quoteflags.bidunsolicited"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_bid_unsolicited()));
        values[entry + ".payload.insidemessage.quoteflags.bidpriced"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_bid_priced()));
        values[entry + ".payload.insidemessage.quoteflags.bidaskwanted"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_bid_ask_wanted()));
        values[entry + ".payload.insidemessage.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.insidemessage.askprice"] = canonical::scaled(message.fields.ask_price.get().value(), -6);
        values[entry + ".payload.insidemessage.asksize"] = canonical::number(message.fields.ask_size.get().value());
        values[entry + ".payload.insidemessage.asktimemilli"] = canonical::number(message.fields.ask_time_milli.get().value());
        values[entry + ".payload.insidemessage.bidprice"] = canonical::scaled(message.fields.bid_price.get().value(), -6);
        values[entry + ".payload.insidemessage.bidsize"] = canonical::number(message.fields.bid_size.get().value());
        values[entry + ".payload.insidemessage.bidtimemilli"] = canonical::number(message.fields.bid_time_milli.get().value());
        values[entry + ".payload.insidemessage.asknumpricedmp"] = canonical::number(message.fields.ask_num_priced_mp.get().value());
        values[entry + ".payload.insidemessage.bidnumpricedmp"] = canonical::number(message.fields.bid_num_priced_mp.get().value());
    }

    void on_message(const protocol::inside_update_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messageblock.message.payload.insideupdatemessage";
        values[entry + ".payload.insideupdatemessage.channelseqnum"] = canonical::number(message.fields.channel_seq_num.get().value());
        values[entry + ".payload.insideupdatemessage.insideid"] = canonical::number(message.fields.inside_id.get().value());
        values[entry + ".payload.insideupdatemessage.quoteflags.updateside"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_update_side()));
        values[entry + ".payload.insideupdatemessage.quoteflags.state"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_state()));
        values[entry + ".payload.insideupdatemessage.quoteflags.askunsolicited"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_ask_unsolicited()));
        values[entry + ".payload.insideupdatemessage.quoteflags.askpriced"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_ask_priced()));
        values[entry + ".payload.insideupdatemessage.quoteflags.askbidwanted"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_ask_bid_wanted()));
        values[entry + ".payload.insideupdatemessage.quoteflags.bidunsolicited"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_bid_unsolicited()));
        values[entry + ".payload.insideupdatemessage.quoteflags.bidpriced"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_bid_priced()));
        values[entry + ".payload.insideupdatemessage.quoteflags.bidaskwanted"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_bid_ask_wanted()));
        values[entry + ".payload.insideupdatemessage.price"] = canonical::scaled(message.fields.price.get().value(), -6);
        values[entry + ".payload.insideupdatemessage.size"] = canonical::number(message.fields.size.get().value());
        values[entry + ".payload.insideupdatemessage.insidetimemilli"] = canonical::number(message.fields.inside_time_milli.get().value());
        values[entry + ".payload.insideupdatemessage.numpricedmp"] = canonical::number(message.fields.num_priced_mp.get().value());
    }

    void on_message(const protocol::reference_price_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messageblock.message.payload.referencepricemessage";
        values[entry + ".payload.referencepricemessage.channelseqnum"] = canonical::number(message.fields.channel_seq_num.get().value());
        values[entry + ".payload.referencepricemessage.referencepriceid"] = canonical::number(message.fields.reference_price_id.get().value());
        values[entry + ".payload.referencepricemessage.referencepriceaction"] = canonical::number(message.fields.reference_price_action.get().value());
        values[entry + ".payload.referencepricemessage.quoteflags.updateside"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_update_side()));
        values[entry + ".payload.referencepricemessage.quoteflags.state"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_state()));
        values[entry + ".payload.referencepricemessage.quoteflags.askunsolicited"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_ask_unsolicited()));
        values[entry + ".payload.referencepricemessage.quoteflags.askpriced"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_ask_priced()));
        values[entry + ".payload.referencepricemessage.quoteflags.askbidwanted"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_ask_bid_wanted()));
        values[entry + ".payload.referencepricemessage.quoteflags.bidunsolicited"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_bid_unsolicited()));
        values[entry + ".payload.referencepricemessage.quoteflags.bidpriced"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_bid_priced()));
        values[entry + ".payload.referencepricemessage.quoteflags.bidaskwanted"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_bid_ask_wanted()));
        values[entry + ".payload.referencepricemessage.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.referencepricemessage.askprice"] = canonical::scaled(message.fields.ask_price.get().value(), -6);
        values[entry + ".payload.referencepricemessage.asksize"] = canonical::number(message.fields.ask_size.get().value());
        values[entry + ".payload.referencepricemessage.asktimemilli"] = canonical::number(message.fields.ask_time_milli.get().value());
        values[entry + ".payload.referencepricemessage.bidprice"] = canonical::scaled(message.fields.bid_price.get().value(), -6);
        values[entry + ".payload.referencepricemessage.bidsize"] = canonical::number(message.fields.bid_size.get().value());
        values[entry + ".payload.referencepricemessage.bidtimemilli"] = canonical::number(message.fields.bid_time_milli.get().value());
    }

    void on_message(const protocol::reference_price_update_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messageblock.message.payload.referencepriceupdatemessage";
        values[entry + ".payload.referencepriceupdatemessage.channelseqnum"] = canonical::number(message.fields.channel_seq_num.get().value());
        values[entry + ".payload.referencepriceupdatemessage.referencepriceid"] = canonical::number(message.fields.reference_price_id.get().value());
        values[entry + ".payload.referencepriceupdatemessage.quoteflags.updateside"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_update_side()));
        values[entry + ".payload.referencepriceupdatemessage.quoteflags.state"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_state()));
        values[entry + ".payload.referencepriceupdatemessage.quoteflags.askunsolicited"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_ask_unsolicited()));
        values[entry + ".payload.referencepriceupdatemessage.quoteflags.askpriced"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_ask_priced()));
        values[entry + ".payload.referencepriceupdatemessage.quoteflags.askbidwanted"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_ask_bid_wanted()));
        values[entry + ".payload.referencepriceupdatemessage.quoteflags.bidunsolicited"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_bid_unsolicited()));
        values[entry + ".payload.referencepriceupdatemessage.quoteflags.bidpriced"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_bid_priced()));
        values[entry + ".payload.referencepriceupdatemessage.quoteflags.bidaskwanted"] = canonical::number(static_cast<std::uint64_t>(message.fields.quote_flags.has_bid_ask_wanted()));
        values[entry + ".payload.referencepriceupdatemessage.price"] = canonical::scaled(message.fields.price.get().value(), -6);
        values[entry + ".payload.referencepriceupdatemessage.size"] = canonical::number(message.fields.size.get().value());
        values[entry + ".payload.referencepriceupdatemessage.timemilli"] = canonical::number(message.fields.time_milli.get().value());
    }

    void on_message(const protocol::extended_security_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messageblock.message.payload.extendedsecuritymessage";
        values[entry + ".payload.extendedsecuritymessage.channelseqnum"] = canonical::number(message.fields.channel_seq_num.get().value());
        values[entry + ".payload.extendedsecuritymessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()));
        values[entry + ".payload.extendedsecuritymessage.lastupdatemilli"] = canonical::number(message.fields.last_update_milli.get().value());
        values[entry + ".payload.extendedsecuritymessage.securityaction"] = canonical::number(message.fields.security_action.get().value());
        values[entry + ".payload.extendedsecuritymessage.otcissuerid"] = canonical::number(message.fields.otc_issuer_id.get().value());
        values[entry + ".payload.extendedsecuritymessage.securitydesc"] = canonical::text(std::string(message.fields.security_desc.get().value()));
        values[entry + ".payload.extendedsecuritymessage.shortname"] = canonical::text(std::string(message.fields.short_name.get().value()));
        values[entry + ".payload.extendedsecuritymessage.assetclass"] = canonical::number(message.fields.asset_class.get().value());
        values[entry + ".payload.extendedsecuritymessage.securitytype"] = canonical::text(std::string(message.fields.security_type.get().value()));
        values[entry + ".payload.extendedsecuritymessage.primarymarket"] = canonical::text(std::string(message.fields.primary_market.get().value()));
        values[entry + ".payload.extendedsecuritymessage.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.piggyback"] = canonical::number(static_cast<std::uint64_t>(message.fields.extended_security_flags.has_piggyback()));
        values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.caveatemptorwarning"] = canonical::number(static_cast<std::uint64_t>(message.fields.extended_security_flags.has_caveat_emptor_warning()));
        values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.qualifiedinstitutionalbuyersonly"] = canonical::number(static_cast<std::uint64_t>(message.fields.extended_security_flags.has_qualified_institutional_buyers_only()));
        values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.unsolicitedonly"] = canonical::number(static_cast<std::uint64_t>(message.fields.extended_security_flags.has_unsolicited_only()));
        values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.sponsoredstatus"] = canonical::number(static_cast<std::uint64_t>(message.fields.extended_security_flags.has_sponsored_status()));
        values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.otclinkecneligible"] = canonical::number(static_cast<std::uint64_t>(message.fields.extended_security_flags.has_otc_link_ecn_eligible()));
        values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.otclinkmessagingdisabled"] = canonical::number(static_cast<std::uint64_t>(message.fields.extended_security_flags.has_otc_link_messaging_disabled()));
        values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.saturationeligible"] = canonical::number(static_cast<std::uint64_t>(message.fields.extended_security_flags.has_saturation_eligible()));
        values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.investmentgrade"] = canonical::number(static_cast<std::uint64_t>(message.fields.extended_security_flags.has_investment_grade()));
        values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.tradingflat"] = canonical::number(static_cast<std::uint64_t>(message.fields.extended_security_flags.has_trading_flat()));
        values[entry + ".payload.extendedsecuritymessage.extendedsecurityflags.callable"] = canonical::number(static_cast<std::uint64_t>(message.fields.extended_security_flags.has_callable()));
        values[entry + ".payload.extendedsecuritymessage.tier"] = canonical::number(message.fields.tier.get().value());
        values[entry + ".payload.extendedsecuritymessage.reportingstatus"] = canonical::text(canonical::character(message.fields.reporting_status.get().value()));
        values[entry + ".payload.extendedsecuritymessage.disclosurestatus"] = canonical::number(message.fields.disclosure_status.get().value());
        values[entry + ".payload.extendedsecuritymessage.securitystatus"] = canonical::text(canonical::character(message.fields.security_status.get().value()));
        values[entry + ".payload.extendedsecuritymessage.parvalue"] = canonical::scaled(message.fields.par_value.get().value(), -6);
        values[entry + ".payload.extendedsecuritymessage.coupon"] = canonical::scaled(message.fields.coupon.get().value(), -6);
        values[entry + ".payload.extendedsecuritymessage.maturitydatemilli"] = canonical::number(message.fields.maturity_date_milli.get().value());
        values[entry + ".payload.extendedsecuritymessage.callabledatemilli"] = canonical::number(message.fields.callable_date_milli.get().value());
        values[entry + ".payload.extendedsecuritymessage.adrratio"] = canonical::scaled(message.fields.adr_ratio.get().value(), -6);
        values[entry + ".payload.extendedsecuritymessage.adrlevel"] = canonical::text(std::string(message.fields.adr_level.get().value()));
    }

    void on_message(const protocol::extended_security_no_cusip_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messageblock.message.payload.extendedsecuritynocusipmessage";
        values[entry + ".payload.extendedsecuritynocusipmessage.channelseqnum"] = canonical::number(message.fields.channel_seq_num.get().value());
        values[entry + ".payload.extendedsecuritynocusipmessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()));
        values[entry + ".payload.extendedsecuritynocusipmessage.lastupdatemilli"] = canonical::number(message.fields.last_update_milli.get().value());
        values[entry + ".payload.extendedsecuritynocusipmessage.securityaction"] = canonical::number(message.fields.security_action.get().value());
        values[entry + ".payload.extendedsecuritynocusipmessage.otcissuerid"] = canonical::number(message.fields.otc_issuer_id.get().value());
        values[entry + ".payload.extendedsecuritynocusipmessage.securitydesc"] = canonical::text(std::string(message.fields.security_desc.get().value()));
        values[entry + ".payload.extendedsecuritynocusipmessage.shortname"] = canonical::text(std::string(message.fields.short_name.get().value()));
        values[entry + ".payload.extendedsecuritynocusipmessage.assetclass"] = canonical::number(message.fields.asset_class.get().value());
        values[entry + ".payload.extendedsecuritynocusipmessage.securitytype"] = canonical::text(std::string(message.fields.security_type.get().value()));
        values[entry + ".payload.extendedsecuritynocusipmessage.primarymarket"] = canonical::text(std::string(message.fields.primary_market.get().value()));
        values[entry + ".payload.extendedsecuritynocusipmessage.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.extendedsecuritynocusipmessage.securityflags.piggyback"] = canonical::number(static_cast<std::uint64_t>(message.fields.security_flags.has_piggyback()));
        values[entry + ".payload.extendedsecuritynocusipmessage.securityflags.caveatemptorwarning"] = canonical::number(static_cast<std::uint64_t>(message.fields.security_flags.has_caveat_emptor_warning()));
        values[entry + ".payload.extendedsecuritynocusipmessage.securityflags.qualifiedinstitutionalbuyersonly"] = canonical::number(static_cast<std::uint64_t>(message.fields.security_flags.has_qualified_institutional_buyers_only()));
        values[entry + ".payload.extendedsecuritynocusipmessage.securityflags.unsolicitedonly"] = canonical::number(static_cast<std::uint64_t>(message.fields.security_flags.has_unsolicited_only()));
        values[entry + ".payload.extendedsecuritynocusipmessage.securityflags.bbquoted"] = canonical::number(static_cast<std::uint64_t>(message.fields.security_flags.has_bb_quoted()));
        values[entry + ".payload.extendedsecuritynocusipmessage.securityflags.otclinkecneligible"] = canonical::number(static_cast<std::uint64_t>(message.fields.security_flags.has_otc_link_ecn_eligible()));
        values[entry + ".payload.extendedsecuritynocusipmessage.securityflags.otclinkmessagingdisabled"] = canonical::number(static_cast<std::uint64_t>(message.fields.security_flags.has_otc_link_messaging_disabled()));
        values[entry + ".payload.extendedsecuritynocusipmessage.securityflags.saturationeligible"] = canonical::number(static_cast<std::uint64_t>(message.fields.security_flags.has_saturation_eligible()));
        values[entry + ".payload.extendedsecuritynocusipmessage.tier"] = canonical::number(message.fields.tier.get().value());
        values[entry + ".payload.extendedsecuritynocusipmessage.reportingstatus"] = canonical::text(canonical::character(message.fields.reporting_status.get().value()));
        values[entry + ".payload.extendedsecuritynocusipmessage.disclosurestatus"] = canonical::number(message.fields.disclosure_status.get().value());
        values[entry + ".payload.extendedsecuritynocusipmessage.securitystatus"] = canonical::text(canonical::character(message.fields.security_status.get().value()));
        values[entry + ".payload.extendedsecuritynocusipmessage.parvalue"] = canonical::scaled(message.fields.par_value.get().value(), -6);
        values[entry + ".payload.extendedsecuritynocusipmessage.coupon"] = canonical::scaled(message.fields.coupon.get().value(), -6);
        values[entry + ".payload.extendedsecuritynocusipmessage.maturitydatemilli"] = canonical::number(message.fields.maturity_date_milli.get().value());
        values[entry + ".payload.extendedsecuritynocusipmessage.callabledatemilli"] = canonical::number(message.fields.callable_date_milli.get().value());
        values[entry + ".payload.extendedsecuritynocusipmessage.adrratio"] = canonical::scaled(message.fields.adr_ratio.get().value(), -6);
        values[entry + ".payload.extendedsecuritynocusipmessage.adrlevel"] = canonical::text(std::string(message.fields.adr_level.get().value()));
    }

    void on_message(const protocol::trade_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messageblock.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messageblock.message.payload.trademessage";
        values[entry + ".payload.trademessage.channelseqnum"] = canonical::number(message.fields.channel_seq_num.get().value());
        values[entry + ".payload.trademessage.tradeid"] = canonical::number(message.fields.trade_id.get().value());
        values[entry + ".payload.trademessage.tradeaction"] = canonical::number(message.fields.trade_action.get().value());
        values[entry + ".payload.trademessage.tradeflags"] = canonical::number(message.fields.trade_flags.get().value());
        values[entry + ".payload.trademessage.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".payload.trademessage.tradestatus.irregular"] = canonical::number(static_cast<std::uint64_t>(message.fields.trade_status.has_irregular()));
        values[entry + ".payload.trademessage.deprecated"] = canonical::text(std::string(message.fields.deprecated.get().value()));
        values[entry + ".payload.trademessage.tradeprice"] = canonical::scaled(message.fields.trade_price.get().value(), -6);
        values[entry + ".payload.trademessage.tradesize"] = canonical::number(message.fields.trade_size.get().value());
        values[entry + ".payload.trademessage.tradetimemilli"] = canonical::number(message.fields.trade_time_milli.get().value());
    }
};

// The values Advanced reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    Reader reader;
    protocol::process_segment(reader, frame.payload, frame.payload_len, 0, frame);
    return reader.values;
}

// Read each datagram of a sample with Advanced and hold it to the model's values
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
    std::printf("== OtcMarkets.LinkAts.Multicast.Link.v4.3 (advanced values)\n");
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
