// Nyse.TexasEquities.IntegratedFeed.Pillar.v2.5.g canonical values, through the Advanced session layer: every value Advanced
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
#include "cpp/binary/advanced/nyse/texasequities/integratedfeed/pillar/v2.5.g/messages/session.hpp"

namespace protocol = ::nyse::texasequities::integratedfeed::pillar::v2_5_g;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::packet_header& header, const packet::Frame&) {
        values["packet.packetheader.pktsize"] = canonical::number(header.pkt_size.get().value());
        values["packet.packetheader.deliveryflag"] = canonical::number(header.delivery_flag.get().value());
        values["packet.packetheader.numbermsgs"] = canonical::number(header.number_msgs.get().value());
        values["packet.packetheader.seqnum"] = canonical::number(header.seq_num.get().value());
        values["packet.packetheader.sendtime.seconds"] = canonical::number(header.send_time.seconds.get().value());
        values["packet.packetheader.sendtime.nanoseconds"] = canonical::number(header.send_time.nanoseconds.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::packet_header&) {
        ++index;
    }

    void on_message(const protocol::sequence_number_reset_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.sequencenumberresetmessage";
        values[entry + ".payload.sequencenumberresetmessage.sourcetime"] = canonical::number(message.fields.source_time.get().value());
        values[entry + ".payload.sequencenumberresetmessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.sequencenumberresetmessage.productid"] = canonical::number(message.fields.product_id.get().value());
        values[entry + ".payload.sequencenumberresetmessage.channelid"] = canonical::number(message.fields.channel_id.get().value());
    }

    void on_message(const protocol::source_time_reference_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.sourcetimereferencemessage";
        values[entry + ".payload.sourcetimereferencemessage.id"] = canonical::number(message.fields.id.get().value());
        values[entry + ".payload.sourcetimereferencemessage.symbolseqnum"] = canonical::number(message.fields.symbol_seq_num.get().value());
        values[entry + ".payload.sourcetimereferencemessage.sourcetime"] = canonical::number(message.fields.source_time.get().value());
    }

    void on_message(const protocol::symbol_index_mapping_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.symbolindexmappingmessage";
        values[entry + ".payload.symbolindexmappingmessage.symbolindex"] = canonical::number(message.fields.symbol_index.get().value());
        values[entry + ".payload.symbolindexmappingmessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), '\0', false);
        values[entry + ".payload.symbolindexmappingmessage.marketid"] = canonical::number(message.fields.market_id.get().value());
        values[entry + ".payload.symbolindexmappingmessage.systemid"] = canonical::number(message.fields.system_id.get().value());
        values[entry + ".payload.symbolindexmappingmessage.exchangecode"] = canonical::text(canonical::character(message.fields.exchange_code.get().value()), '\0', false);
        values[entry + ".payload.symbolindexmappingmessage.pricescalecode"] = canonical::number(message.fields.price_scale_code.get().value());
        values[entry + ".payload.symbolindexmappingmessage.securitytype"] = canonical::text(canonical::character(message.fields.security_type.get().value()), '\0', false);
        values[entry + ".payload.symbolindexmappingmessage.lotsize"] = canonical::number(message.fields.lot_size.get().value());
        values[entry + ".payload.symbolindexmappingmessage.prevcloseprice"] = canonical::number(message.fields.prev_close_price.get().value());
        values[entry + ".payload.symbolindexmappingmessage.prevclosevolume"] = canonical::number(message.fields.prev_close_volume.get().value());
        values[entry + ".payload.symbolindexmappingmessage.priceresolution"] = canonical::number(message.fields.price_resolution.get().value());
        values[entry + ".payload.symbolindexmappingmessage.roundlot"] = canonical::text(canonical::character(message.fields.round_lot.get().value()), '\0', false);
        values[entry + ".payload.symbolindexmappingmessage.mpv"] = canonical::number(message.fields.mpv.get().value());
        values[entry + ".payload.symbolindexmappingmessage.unitoftrade"] = canonical::number(message.fields.unit_of_trade.get().value());
    }

    void on_message(const protocol::symbol_clear_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.symbolclearmessage";
        values[entry + ".payload.symbolclearmessage.sourcetime"] = canonical::number(message.fields.source_time.get().value());
        values[entry + ".payload.symbolclearmessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.symbolclearmessage.symbolindex"] = canonical::number(message.fields.symbol_index.get().value());
        values[entry + ".payload.symbolclearmessage.nextsourceseqnum"] = canonical::number(message.fields.next_source_seq_num.get().value());
    }

    void on_message(const protocol::security_status_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.securitystatusmessage";
        values[entry + ".payload.securitystatusmessage.sourcetime"] = canonical::number(message.fields.source_time.get().value());
        values[entry + ".payload.securitystatusmessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.securitystatusmessage.symbolindex"] = canonical::number(message.fields.symbol_index.get().value());
        values[entry + ".payload.securitystatusmessage.symbolseqnum"] = canonical::number(message.fields.symbol_seq_num.get().value());
        values[entry + ".payload.securitystatusmessage.securitystatus"] = canonical::text(canonical::character(message.fields.security_status.get().value()), '\0', false);
        values[entry + ".payload.securitystatusmessage.haltcondition"] = canonical::text(canonical::character(message.fields.halt_condition.get().value()), '\0', false);
        values[entry + ".payload.securitystatusmessage.price1"] = canonical::number(message.fields.price_1.get().value());
        values[entry + ".payload.securitystatusmessage.price2"] = canonical::number(message.fields.price_2.get().value());
        values[entry + ".payload.securitystatusmessage.ssrtriggeringexchangeid"] = canonical::text(canonical::character(message.fields.ssr_triggering_exchange_id.get().value()), '\0', false);
        values[entry + ".payload.securitystatusmessage.ssrtriggeringvolume"] = canonical::number(message.fields.ssr_triggering_volume.get().value());
        values[entry + ".payload.securitystatusmessage.time"] = (message.fields.time.get().has_value() ? canonical::number(message.fields.time.get().value()) : canonical::absent());
        values[entry + ".payload.securitystatusmessage.ssrstate"] = canonical::text(canonical::character(message.fields.ssr_state.get().value()), '\0', false);
        values[entry + ".payload.securitystatusmessage.marketstate"] = canonical::text(canonical::character(message.fields.market_state.get().value()), '\0', false);
        values[entry + ".payload.securitystatusmessage.sessionstate"] = canonical::text(canonical::character(message.fields.session_state.get().value()), '\0', false);
    }

    void on_message(const protocol::add_order_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.addordermessage";
        values[entry + ".payload.addordermessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.addordermessage.symbolindex"] = canonical::number(message.fields.symbol_index.get().value());
        values[entry + ".payload.addordermessage.symbolseqnum"] = canonical::number(message.fields.symbol_seq_num.get().value());
        values[entry + ".payload.addordermessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.addordermessage.price"] = canonical::number(message.fields.price.get().value());
        values[entry + ".payload.addordermessage.volume"] = canonical::number(message.fields.volume.get().value());
        values[entry + ".payload.addordermessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()), '\0', false);
        values[entry + ".payload.addordermessage.firmid"] = canonical::text(std::string(message.fields.firm_id.get().value()), ' ', false);
    }

    void on_message(const protocol::modify_order_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.modifyordermessage";
        values[entry + ".payload.modifyordermessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.modifyordermessage.symbolindex"] = canonical::number(message.fields.symbol_index.get().value());
        values[entry + ".payload.modifyordermessage.symbolseqnum"] = canonical::number(message.fields.symbol_seq_num.get().value());
        values[entry + ".payload.modifyordermessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.modifyordermessage.price"] = canonical::number(message.fields.price.get().value());
        values[entry + ".payload.modifyordermessage.volume"] = canonical::number(message.fields.volume.get().value());
        values[entry + ".payload.modifyordermessage.positionchange"] = canonical::number(message.fields.position_change.get().value());
        values[entry + ".payload.modifyordermessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()), '\0', false);
    }

    void on_message(const protocol::delete_order_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.deleteordermessage";
        values[entry + ".payload.deleteordermessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.deleteordermessage.symbolindex"] = canonical::number(message.fields.symbol_index.get().value());
        values[entry + ".payload.deleteordermessage.symbolseqnum"] = canonical::number(message.fields.symbol_seq_num.get().value());
        values[entry + ".payload.deleteordermessage.orderid"] = canonical::number(message.fields.order_id.get().value());
    }

    void on_message(const protocol::order_execution_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.orderexecutionmessage";
        values[entry + ".payload.orderexecutionmessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.orderexecutionmessage.symbolindex"] = canonical::number(message.fields.symbol_index.get().value());
        values[entry + ".payload.orderexecutionmessage.symbolseqnum"] = canonical::number(message.fields.symbol_seq_num.get().value());
        values[entry + ".payload.orderexecutionmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.orderexecutionmessage.tradeid"] = canonical::number(message.fields.trade_id.get().value());
        values[entry + ".payload.orderexecutionmessage.price"] = canonical::number(message.fields.price.get().value());
        values[entry + ".payload.orderexecutionmessage.volume"] = canonical::number(message.fields.volume.get().value());
        values[entry + ".payload.orderexecutionmessage.printableflag"] = canonical::number(message.fields.printable_flag.get().value());
        values[entry + ".payload.orderexecutionmessage.tradecond1"] = canonical::text(canonical::character(message.fields.trade_cond_1.get().value()), '\0', false);
        values[entry + ".payload.orderexecutionmessage.tradecond2"] = canonical::text(canonical::character(message.fields.trade_cond_2.get().value()), '\0', false);
        values[entry + ".payload.orderexecutionmessage.tradecond3"] = canonical::text(canonical::character(message.fields.trade_cond_3.get().value()), '\0', false);
        values[entry + ".payload.orderexecutionmessage.tradecond4"] = canonical::text(canonical::character(message.fields.trade_cond_4.get().value()), '\0', false);
    }

    void on_message(const protocol::replace_order_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.replaceordermessage";
        values[entry + ".payload.replaceordermessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.replaceordermessage.symbolindex"] = canonical::number(message.fields.symbol_index.get().value());
        values[entry + ".payload.replaceordermessage.symbolseqnum"] = canonical::number(message.fields.symbol_seq_num.get().value());
        values[entry + ".payload.replaceordermessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.replaceordermessage.neworderid"] = canonical::number(message.fields.new_order_id.get().value());
        values[entry + ".payload.replaceordermessage.price"] = canonical::number(message.fields.price.get().value());
        values[entry + ".payload.replaceordermessage.volume"] = canonical::number(message.fields.volume.get().value());
        values[entry + ".payload.replaceordermessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()), '\0', false);
    }

    void on_message(const protocol::imbalance_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.imbalancemessage";
        values[entry + ".payload.imbalancemessage.sourcetime"] = canonical::number(message.fields.source_time.get().value());
        values[entry + ".payload.imbalancemessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.imbalancemessage.symbolindex"] = canonical::number(message.fields.symbol_index.get().value());
        values[entry + ".payload.imbalancemessage.symbolseqnum"] = canonical::number(message.fields.symbol_seq_num.get().value());
        values[entry + ".payload.imbalancemessage.referenceprice"] = canonical::number(message.fields.reference_price.get().value());
        values[entry + ".payload.imbalancemessage.pairedqty"] = canonical::number(message.fields.paired_qty.get().value());
        values[entry + ".payload.imbalancemessage.totalimbalanceqty"] = canonical::number(message.fields.total_imbalance_qty.get().value());
        values[entry + ".payload.imbalancemessage.marketimbalanceqty"] = canonical::number(message.fields.market_imbalance_qty.get().value());
        values[entry + ".payload.imbalancemessage.auctiontime"] = canonical::number(message.fields.auction_time.get().value());
        values[entry + ".payload.imbalancemessage.auctiontype"] = canonical::text(canonical::character(message.fields.auction_type.get().value()), '\0', false);
        values[entry + ".payload.imbalancemessage.imbalanceside"] = canonical::text(canonical::character(message.fields.imbalance_side.get().value()), '\0', false);
        values[entry + ".payload.imbalancemessage.continuousbookclearingprice"] = canonical::number(message.fields.continuous_book_clearing_price.get().value());
        values[entry + ".payload.imbalancemessage.auctioninterestclearingprice"] = canonical::number(message.fields.auction_interest_clearing_price.get().value());
        values[entry + ".payload.imbalancemessage.ssrfilingprice"] = canonical::number(message.fields.ssr_filing_price.get().value());
        values[entry + ".payload.imbalancemessage.indicativematchprice"] = canonical::number(message.fields.indicative_match_price.get().value());
        values[entry + ".payload.imbalancemessage.uppercollar"] = canonical::number(message.fields.upper_collar.get().value());
        values[entry + ".payload.imbalancemessage.lowercollar"] = canonical::number(message.fields.lower_collar.get().value());
        values[entry + ".payload.imbalancemessage.auctionstatus"] = canonical::number(message.fields.auction_status.get().value());
        values[entry + ".payload.imbalancemessage.freezestatus"] = canonical::number(message.fields.freeze_status.get().value());
        values[entry + ".payload.imbalancemessage.numextensions"] = canonical::number(message.fields.num_extensions.get().value());
        values[entry + ".payload.imbalancemessage.unpairedqty"] = canonical::number(message.fields.unpaired_qty.get().value());
        values[entry + ".payload.imbalancemessage.unpairedside"] = canonical::text(canonical::character(message.fields.unpaired_side.get().value()), '\0', false);
    }

    void on_message(const protocol::add_order_refresh_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.addorderrefreshmessage";
        values[entry + ".payload.addorderrefreshmessage.sourcetime"] = canonical::number(message.fields.source_time.get().value());
        values[entry + ".payload.addorderrefreshmessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.addorderrefreshmessage.symbolindex"] = canonical::number(message.fields.symbol_index.get().value());
        values[entry + ".payload.addorderrefreshmessage.symbolseqnum"] = canonical::number(message.fields.symbol_seq_num.get().value());
        values[entry + ".payload.addorderrefreshmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.addorderrefreshmessage.price"] = canonical::number(message.fields.price.get().value());
        values[entry + ".payload.addorderrefreshmessage.volume"] = canonical::number(message.fields.volume.get().value());
        values[entry + ".payload.addorderrefreshmessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()), '\0', false);
        values[entry + ".payload.addorderrefreshmessage.firmid"] = canonical::text(std::string(message.fields.firm_id.get().value()), ' ', false);
    }

    void on_message(const protocol::non_displayed_trade_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.nondisplayedtrademessage";
        values[entry + ".payload.nondisplayedtrademessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.nondisplayedtrademessage.symbolindex"] = canonical::number(message.fields.symbol_index.get().value());
        values[entry + ".payload.nondisplayedtrademessage.symbolseqnum"] = canonical::number(message.fields.symbol_seq_num.get().value());
        values[entry + ".payload.nondisplayedtrademessage.tradeid"] = canonical::number(message.fields.trade_id.get().value());
        values[entry + ".payload.nondisplayedtrademessage.price"] = canonical::number(message.fields.price.get().value());
        values[entry + ".payload.nondisplayedtrademessage.volume"] = canonical::number(message.fields.volume.get().value());
        values[entry + ".payload.nondisplayedtrademessage.printableflag"] = canonical::number(message.fields.printable_flag.get().value());
        values[entry + ".payload.nondisplayedtrademessage.tradecond1"] = canonical::text(canonical::character(message.fields.trade_cond_1.get().value()), '\0', false);
        values[entry + ".payload.nondisplayedtrademessage.tradecond2"] = canonical::text(canonical::character(message.fields.trade_cond_2.get().value()), '\0', false);
        values[entry + ".payload.nondisplayedtrademessage.tradecond3"] = canonical::text(canonical::character(message.fields.trade_cond_3.get().value()), '\0', false);
        values[entry + ".payload.nondisplayedtrademessage.tradecond4"] = canonical::text(canonical::character(message.fields.trade_cond_4.get().value()), '\0', false);
    }

    void on_message(const protocol::cross_trade_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.crosstrademessage";
        values[entry + ".payload.crosstrademessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.crosstrademessage.symbolindex"] = canonical::number(message.fields.symbol_index.get().value());
        values[entry + ".payload.crosstrademessage.symbolseqnum"] = canonical::number(message.fields.symbol_seq_num.get().value());
        values[entry + ".payload.crosstrademessage.crossid"] = canonical::number(message.fields.cross_id.get().value());
        values[entry + ".payload.crosstrademessage.price"] = canonical::number(message.fields.price.get().value());
        values[entry + ".payload.crosstrademessage.volume"] = canonical::number(message.fields.volume.get().value());
        values[entry + ".payload.crosstrademessage.crosstype"] = canonical::text(canonical::character(message.fields.cross_type.get().value()), '\0', false);
    }

    void on_message(const protocol::trade_cancel_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.tradecancelmessage";
        values[entry + ".payload.tradecancelmessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.tradecancelmessage.symbolindex"] = canonical::number(message.fields.symbol_index.get().value());
        values[entry + ".payload.tradecancelmessage.symbolseqnum"] = canonical::number(message.fields.symbol_seq_num.get().value());
        values[entry + ".payload.tradecancelmessage.tradeid"] = canonical::number(message.fields.trade_id.get().value());
    }

    void on_message(const protocol::cross_correction_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.crosscorrectionmessage";
        values[entry + ".payload.crosscorrectionmessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.crosscorrectionmessage.symbolindex"] = canonical::number(message.fields.symbol_index.get().value());
        values[entry + ".payload.crosscorrectionmessage.symbolseqnum"] = canonical::number(message.fields.symbol_seq_num.get().value());
        values[entry + ".payload.crosscorrectionmessage.crossid"] = canonical::number(message.fields.cross_id.get().value());
        values[entry + ".payload.crosscorrectionmessage.volume"] = canonical::number(message.fields.volume.get().value());
    }

    void on_message(const protocol::retail_price_improvement_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.retailpriceimprovementmessage";
        values[entry + ".payload.retailpriceimprovementmessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.retailpriceimprovementmessage.symbolindex"] = canonical::number(message.fields.symbol_index.get().value());
        values[entry + ".payload.retailpriceimprovementmessage.symbolseqnum"] = canonical::number(message.fields.symbol_seq_num.get().value());
        values[entry + ".payload.retailpriceimprovementmessage.rpiindicator"] = canonical::text(canonical::character(message.fields.rpi_indicator.get().value()), '\0', false);
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
    std::printf("== Nyse.TexasEquities.IntegratedFeed.Pillar.v2.5.g (advanced values)\n");
    int failures = 0;
    failures += check("AddOrderMessage", "Nyse/TexasEquities.IntegratedFeed.Pillar.v2.5.g/AddOrderMessage.pcap", "nyse/texasequities/integratedfeed/pillar/v2.5.g/AddOrderMessage.values");
    failures += check("DeleteOrderMessage", "Nyse/TexasEquities.IntegratedFeed.Pillar.v2.5.g/DeleteOrderMessage.pcap", "nyse/texasequities/integratedfeed/pillar/v2.5.g/DeleteOrderMessage.values");
    failures += check("ModifyOrderMessage", "Nyse/TexasEquities.IntegratedFeed.Pillar.v2.5.g/ModifyOrderMessage.pcap", "nyse/texasequities/integratedfeed/pillar/v2.5.g/ModifyOrderMessage.values");
    failures += check("NonDisplayedTradeMessage", "Nyse/TexasEquities.IntegratedFeed.Pillar.v2.5.g/NonDisplayedTradeMessage.pcap", "nyse/texasequities/integratedfeed/pillar/v2.5.g/NonDisplayedTradeMessage.values");
    failures += check("OrderExecutionMessage", "Nyse/TexasEquities.IntegratedFeed.Pillar.v2.5.g/OrderExecutionMessage.pcap", "nyse/texasequities/integratedfeed/pillar/v2.5.g/OrderExecutionMessage.values");
    failures += check("ReplaceOrderMessage", "Nyse/TexasEquities.IntegratedFeed.Pillar.v2.5.g/ReplaceOrderMessage.pcap", "nyse/texasequities/integratedfeed/pillar/v2.5.g/ReplaceOrderMessage.values");
    failures += check("SecurityStatusMessage", "Nyse/TexasEquities.IntegratedFeed.Pillar.v2.5.g/SecurityStatusMessage.pcap", "nyse/texasequities/integratedfeed/pillar/v2.5.g/SecurityStatusMessage.values");
    failures += check("SourceTimeReferenceMessage", "Nyse/TexasEquities.IntegratedFeed.Pillar.v2.5.g/SourceTimeReferenceMessage.pcap", "nyse/texasequities/integratedfeed/pillar/v2.5.g/SourceTimeReferenceMessage.values");
    return failures == 0 ? 0 : 1;
}
