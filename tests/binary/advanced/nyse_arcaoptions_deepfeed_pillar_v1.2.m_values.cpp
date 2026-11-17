// Nyse.ArcaOptions.DeepFeed.Pillar.v1.2.m canonical values, through the Advanced session layer: every value Advanced
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
#include "cpp/binary/advanced/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/session.hpp"

namespace protocol = ::nyse::arcaoptions::deepfeed::pillar::v1_2_m;

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

    void on_message(const protocol::outright_series_index_mapping_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.outrightseriesindexmappingmessage";
        values[entry + ".payload.outrightseriesindexmappingmessage.seriesindex"] = canonical::number(message.fields.series_index.get().value());
        values[entry + ".payload.outrightseriesindexmappingmessage.seriestype"] = canonical::number(message.fields.series_type.get().value());
        values[entry + ".payload.outrightseriesindexmappingmessage.marketid"] = canonical::number(message.fields.market_id.get().value());
        values[entry + ".payload.outrightseriesindexmappingmessage.systemid"] = canonical::number(message.fields.system_id.get().value());
        values[entry + ".payload.outrightseriesindexmappingmessage.optionsymbolroot"] = canonical::text(std::string(message.fields.option_symbol_root.get().value()), '\0', false);
        values[entry + ".payload.outrightseriesindexmappingmessage.underlyingsymbol"] = canonical::text(std::string(message.fields.underlying_symbol.get().value()), '\0', false);
        values[entry + ".payload.outrightseriesindexmappingmessage.underlyingindex"] = canonical::number(message.fields.underlying_index.get().value());
        values[entry + ".payload.outrightseriesindexmappingmessage.pricescalecode"] = canonical::number(message.fields.price_scale_code.get().value());
        values[entry + ".payload.outrightseriesindexmappingmessage.contractmultiplier"] = canonical::number(message.fields.contract_multiplier.get().value());
        values[entry + ".payload.outrightseriesindexmappingmessage.maturitydate"] = canonical::text(std::string(message.fields.maturity_date.get().value()), '\0', false);
        values[entry + ".payload.outrightseriesindexmappingmessage.putorcall"] = canonical::number(message.fields.put_or_call.get().value());
        values[entry + ".payload.outrightseriesindexmappingmessage.strikeprice"] = canonical::text(std::string(message.fields.strike_price.get().value()), '\0', false);
        values[entry + ".payload.outrightseriesindexmappingmessage.closingonlyindicator"] = canonical::text(canonical::character(message.fields.closing_only_indicator.get().value()), '\0', false);
    }

    void on_message(const protocol::options_status_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.optionsstatusmessage";
        values[entry + ".payload.optionsstatusmessage.sourcetime"] = canonical::number(message.fields.source_time.get().value());
        values[entry + ".payload.optionsstatusmessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.optionsstatusmessage.seriesindex"] = canonical::number(message.fields.series_index.get().value());
        values[entry + ".payload.optionsstatusmessage.seriesseqnum"] = canonical::number(message.fields.series_seq_num.get().value());
        values[entry + ".payload.optionsstatusmessage.seriesstatus"] = canonical::text(canonical::character(message.fields.series_status.get().value()), '\0', false);
        values[entry + ".payload.optionsstatusmessage.marketstate"] = canonical::text(canonical::character(message.fields.market_state.get().value()), '\0', false);
        values[entry + ".payload.optionsstatusmessage.optionsstatushaltcondition"] = canonical::text(canonical::character(message.fields.options_status_halt_condition.get().value()), '\0', false);
    }

    void on_message(const protocol::complex_series_index_mapping_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.complexseriesindexmappingmessage";
        values[entry + ".payload.complexseriesindexmappingmessage.seriesindex"] = canonical::number(message.fields.series_index.get().value());
        values[entry + ".payload.complexseriesindexmappingmessage.marketid"] = canonical::number(message.fields.market_id.get().value());
        values[entry + ".payload.complexseriesindexmappingmessage.systemid"] = canonical::number(message.fields.system_id.get().value());
        values[entry + ".payload.complexseriesindexmappingmessage.nooflegs"] = canonical::number(message.fields.no_of_legs.get().value());
    }

    void on_message(const protocol::retransmission_request_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.retransmissionrequestmessage";
        values[entry + ".payload.retransmissionrequestmessage.beginseqnum"] = canonical::number(message.fields.begin_seq_num.get().value());
        values[entry + ".payload.retransmissionrequestmessage.endseqnum"] = canonical::number(message.fields.end_seq_num.get().value());
        values[entry + ".payload.retransmissionrequestmessage.sourceid"] = canonical::text(std::string(message.fields.source_id.get().value()), '\0', false);
        values[entry + ".payload.retransmissionrequestmessage.productid"] = canonical::number(message.fields.product_id.get().value());
        values[entry + ".payload.retransmissionrequestmessage.channelid"] = canonical::number(message.fields.channel_id.get().value());
    }

    void on_message(const protocol::refresh_header_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.refreshheadermessage";
        values[entry + ".payload.refreshheadermessage.currentrefreshpkt"] = canonical::number(message.fields.current_refresh_pkt.get().value());
        values[entry + ".payload.refreshheadermessage.totalrefreshpkts"] = canonical::number(message.fields.total_refresh_pkts.get().value());
    }

    void on_message(const protocol::refresh_request_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.refreshrequestmessage";
        values[entry + ".payload.refreshrequestmessage.symbolindex"] = canonical::number(message.fields.symbol_index.get().value());
        values[entry + ".payload.refreshrequestmessage.sourceid"] = canonical::text(std::string(message.fields.source_id.get().value()), '\0', false);
        values[entry + ".payload.refreshrequestmessage.productid"] = canonical::number(message.fields.product_id.get().value());
        values[entry + ".payload.refreshrequestmessage.channelid"] = canonical::number(message.fields.channel_id.get().value());
    }

    void on_message(const protocol::symbol_index_mapping_request_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.symbolindexmappingrequestmessage";
        values[entry + ".payload.symbolindexmappingrequestmessage.symbolindex"] = canonical::number(message.fields.symbol_index.get().value());
        values[entry + ".payload.symbolindexmappingrequestmessage.sourceid"] = canonical::text(std::string(message.fields.source_id.get().value()), '\0', false);
        values[entry + ".payload.symbolindexmappingrequestmessage.productid"] = canonical::number(message.fields.product_id.get().value());
        values[entry + ".payload.symbolindexmappingrequestmessage.channelid"] = canonical::number(message.fields.channel_id.get().value());
        values[entry + ".payload.symbolindexmappingrequestmessage.retransmitmethod"] = canonical::number(message.fields.retransmit_method.get().value());
    }

    void on_message(const protocol::message_unavailable_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.messageunavailablemessage";
        values[entry + ".payload.messageunavailablemessage.beginseqnum"] = canonical::number(message.fields.begin_seq_num.get().value());
        values[entry + ".payload.messageunavailablemessage.endseqnum"] = canonical::number(message.fields.end_seq_num.get().value());
        values[entry + ".payload.messageunavailablemessage.productid"] = canonical::number(message.fields.product_id.get().value());
        values[entry + ".payload.messageunavailablemessage.channelid"] = canonical::number(message.fields.channel_id.get().value());
    }

    void on_message(const protocol::request_response_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.requestresponsemessage";
        values[entry + ".payload.requestresponsemessage.requestseqnum"] = canonical::number(message.fields.request_seq_num.get().value());
        values[entry + ".payload.requestresponsemessage.beginseqnum"] = canonical::number(message.fields.begin_seq_num.get().value());
        values[entry + ".payload.requestresponsemessage.endseqnum"] = canonical::number(message.fields.end_seq_num.get().value());
        values[entry + ".payload.requestresponsemessage.sourceid"] = canonical::text(std::string(message.fields.source_id.get().value()), '\0', false);
        values[entry + ".payload.requestresponsemessage.productid"] = canonical::number(message.fields.product_id.get().value());
        values[entry + ".payload.requestresponsemessage.channelid"] = canonical::number(message.fields.channel_id.get().value());
        values[entry + ".payload.requestresponsemessage.status"] = canonical::text(canonical::character(message.fields.status.get().value()), '\0', false);
    }

    void on_message(const protocol::heartbeat_response_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.heartbeatresponsemessage";
        values[entry + ".payload.heartbeatresponsemessage.sourceid"] = canonical::text(std::string(message.fields.source_id.get().value()), '\0', false);
    }

    void on_message(const protocol::options_add_order_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.optionsaddordermessage";
        values[entry + ".payload.optionsaddordermessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.optionsaddordermessage.seriesindex"] = canonical::number(message.fields.series_index.get().value());
        values[entry + ".payload.optionsaddordermessage.seriesseqnum"] = canonical::number(message.fields.series_seq_num.get().value());
        values[entry + ".payload.optionsaddordermessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.optionsaddordermessage.price"] = canonical::number(message.fields.price.get().value());
        values[entry + ".payload.optionsaddordermessage.volume"] = canonical::number(message.fields.volume.get().value());
        values[entry + ".payload.optionsaddordermessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()), '\0', false);
        values[entry + ".payload.optionsaddordermessage.firmid"] = canonical::text(std::string(message.fields.firm_id.get().value()), ' ', false);
        values[entry + ".payload.optionsaddordermessage.custindicator"] = canonical::text(canonical::character(message.fields.cust_indicator.get().value()), '\0', false);
    }

    void on_message(const protocol::options_modify_order_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.optionsmodifyordermessage";
        values[entry + ".payload.optionsmodifyordermessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.optionsmodifyordermessage.seriesindex"] = canonical::number(message.fields.series_index.get().value());
        values[entry + ".payload.optionsmodifyordermessage.seriesseqnum"] = canonical::number(message.fields.series_seq_num.get().value());
        values[entry + ".payload.optionsmodifyordermessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.optionsmodifyordermessage.price"] = canonical::number(message.fields.price.get().value());
        values[entry + ".payload.optionsmodifyordermessage.volume"] = canonical::number(message.fields.volume.get().value());
        values[entry + ".payload.optionsmodifyordermessage.positionchange"] = canonical::number(message.fields.position_change.get().value());
        values[entry + ".payload.optionsmodifyordermessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()), '\0', false);
        values[entry + ".payload.optionsmodifyordermessage.custindicator"] = canonical::text(canonical::character(message.fields.cust_indicator.get().value()), '\0', false);
    }

    void on_message(const protocol::options_delete_order_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.optionsdeleteordermessage";
        values[entry + ".payload.optionsdeleteordermessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.optionsdeleteordermessage.seriesindex"] = canonical::number(message.fields.series_index.get().value());
        values[entry + ".payload.optionsdeleteordermessage.seriesseqnum"] = canonical::number(message.fields.series_seq_num.get().value());
        values[entry + ".payload.optionsdeleteordermessage.orderid"] = canonical::number(message.fields.order_id.get().value());
    }

    void on_message(const protocol::options_order_execution_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.optionsorderexecutionmessage";
        values[entry + ".payload.optionsorderexecutionmessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.optionsorderexecutionmessage.seriesindex"] = canonical::number(message.fields.series_index.get().value());
        values[entry + ".payload.optionsorderexecutionmessage.seriesseqnum"] = canonical::number(message.fields.series_seq_num.get().value());
        values[entry + ".payload.optionsorderexecutionmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.optionsorderexecutionmessage.tradeid"] = canonical::number(message.fields.trade_id.get().value());
        values[entry + ".payload.optionsorderexecutionmessage.price"] = canonical::number(message.fields.price.get().value());
        values[entry + ".payload.optionsorderexecutionmessage.volume"] = canonical::number(message.fields.volume.get().value());
        values[entry + ".payload.optionsorderexecutionmessage.printableflag"] = canonical::number(message.fields.printable_flag.get().value());
        values[entry + ".payload.optionsorderexecutionmessage.tradecond1"] = canonical::text(canonical::character(message.fields.trade_cond_1.get().value()), '\0', false);
    }

    void on_message(const protocol::options_replace_order_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.optionsreplaceordermessage";
        values[entry + ".payload.optionsreplaceordermessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.optionsreplaceordermessage.seriesindex"] = canonical::number(message.fields.series_index.get().value());
        values[entry + ".payload.optionsreplaceordermessage.seriesseqnum"] = canonical::number(message.fields.series_seq_num.get().value());
        values[entry + ".payload.optionsreplaceordermessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.optionsreplaceordermessage.neworderid"] = canonical::number(message.fields.new_order_id.get().value());
        values[entry + ".payload.optionsreplaceordermessage.price"] = canonical::number(message.fields.price.get().value());
        values[entry + ".payload.optionsreplaceordermessage.volume"] = canonical::number(message.fields.volume.get().value());
        values[entry + ".payload.optionsreplaceordermessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()), '\0', false);
        values[entry + ".payload.optionsreplaceordermessage.custindicator"] = canonical::text(canonical::character(message.fields.cust_indicator.get().value()), '\0', false);
    }

    void on_message(const protocol::options_imbalance_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.optionsimbalancemessage";
        values[entry + ".payload.optionsimbalancemessage.sourcetime"] = canonical::number(message.fields.source_time.get().value());
        values[entry + ".payload.optionsimbalancemessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.optionsimbalancemessage.seriesindex"] = canonical::number(message.fields.series_index.get().value());
        values[entry + ".payload.optionsimbalancemessage.seriesseqnum"] = canonical::number(message.fields.series_seq_num.get().value());
        values[entry + ".payload.optionsimbalancemessage.pairedqty"] = canonical::number(message.fields.paired_qty.get().value());
        values[entry + ".payload.optionsimbalancemessage.totalimbalanceqty"] = canonical::number(message.fields.total_imbalance_qty.get().value());
        values[entry + ".payload.optionsimbalancemessage.marketimbalanceqty"] = canonical::number(message.fields.market_imbalance_qty.get().value());
        values[entry + ".payload.optionsimbalancemessage.auctiontype"] = canonical::text(canonical::character(message.fields.auction_type.get().value()), '\0', false);
        values[entry + ".payload.optionsimbalancemessage.imbalanceside"] = canonical::text(canonical::character(message.fields.imbalance_side.get().value()), '\0', false);
        values[entry + ".payload.optionsimbalancemessage.continuousbookclearingprice"] = canonical::number(message.fields.continuous_book_clearing_price.get().value());
        values[entry + ".payload.optionsimbalancemessage.auctioninterestclearingprice"] = canonical::number(message.fields.auction_interest_clearing_price.get().value());
        values[entry + ".payload.optionsimbalancemessage.indicativematchprice"] = canonical::number(message.fields.indicative_match_price.get().value());
        values[entry + ".payload.optionsimbalancemessage.uppercollar"] = canonical::number(message.fields.upper_collar.get().value());
        values[entry + ".payload.optionsimbalancemessage.lowercollar"] = canonical::number(message.fields.lower_collar.get().value());
        values[entry + ".payload.optionsimbalancemessage.auctionstatus"] = canonical::number(message.fields.auction_status.get().value());
    }

    void on_message(const protocol::options_add_order_refresh_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.optionsaddorderrefreshmessage";
        values[entry + ".payload.optionsaddorderrefreshmessage.sourcetime"] = canonical::number(message.fields.source_time.get().value());
        values[entry + ".payload.optionsaddorderrefreshmessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.optionsaddorderrefreshmessage.seriesindex"] = canonical::number(message.fields.series_index.get().value());
        values[entry + ".payload.optionsaddorderrefreshmessage.seriesseqnum"] = canonical::number(message.fields.series_seq_num.get().value());
        values[entry + ".payload.optionsaddorderrefreshmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.optionsaddorderrefreshmessage.price"] = canonical::number(message.fields.price.get().value());
        values[entry + ".payload.optionsaddorderrefreshmessage.volume"] = canonical::number(message.fields.volume.get().value());
        values[entry + ".payload.optionsaddorderrefreshmessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()), '\0', false);
        values[entry + ".payload.optionsaddorderrefreshmessage.firmid"] = canonical::text(std::string(message.fields.firm_id.get().value()), ' ', false);
        values[entry + ".payload.optionsaddorderrefreshmessage.custindicator"] = canonical::text(canonical::character(message.fields.cust_indicator.get().value()), '\0', false);
    }

    void on_message(const protocol::options_series_rfq_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.optionsseriesrfqmessage";
        values[entry + ".payload.optionsseriesrfqmessage.sourcetime"] = canonical::number(message.fields.source_time.get().value());
        values[entry + ".payload.optionsseriesrfqmessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.optionsseriesrfqmessage.seriesindex"] = canonical::number(message.fields.series_index.get().value());
        values[entry + ".payload.optionsseriesrfqmessage.seriesseqnum"] = canonical::number(message.fields.series_seq_num.get().value());
        values[entry + ".payload.optionsseriesrfqmessage.rfqside"] = canonical::text(canonical::character(message.fields.rfq_side.get().value()), '\0', false);
        values[entry + ".payload.optionsseriesrfqmessage.type"] = canonical::text(canonical::character(message.fields.type.get().value()), '\0', false);
        values[entry + ".payload.optionsseriesrfqmessage.capacity"] = canonical::text(canonical::character(message.fields.capacity.get().value()), '\0', false);
        values[entry + ".payload.optionsseriesrfqmessage.totalquantity"] = canonical::number(message.fields.total_quantity.get().value());
        values[entry + ".payload.optionsseriesrfqmessage.workingprice"] = canonical::number(message.fields.working_price.get().value());
        values[entry + ".payload.optionsseriesrfqmessage.participant"] = canonical::number(message.fields.participant.get().value());
        values[entry + ".payload.optionsseriesrfqmessage.auctionid"] = canonical::number(message.fields.auction_id.get().value());
        values[entry + ".payload.optionsseriesrfqmessage.rfqstatus"] = canonical::text(canonical::character(message.fields.rfq_status.get().value()), '\0', false);
    }

    void on_message(const protocol::options_non_displayed_trade_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.optionsnondisplayedtrademessage";
        values[entry + ".payload.optionsnondisplayedtrademessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.optionsnondisplayedtrademessage.seriesindex"] = canonical::number(message.fields.series_index.get().value());
        values[entry + ".payload.optionsnondisplayedtrademessage.seriesseqnum"] = canonical::number(message.fields.series_seq_num.get().value());
        values[entry + ".payload.optionsnondisplayedtrademessage.tradeid"] = canonical::number(message.fields.trade_id.get().value());
        values[entry + ".payload.optionsnondisplayedtrademessage.price"] = canonical::number(message.fields.price.get().value());
        values[entry + ".payload.optionsnondisplayedtrademessage.volume"] = canonical::number(message.fields.volume.get().value());
        values[entry + ".payload.optionsnondisplayedtrademessage.printableflag"] = canonical::number(message.fields.printable_flag.get().value());
        values[entry + ".payload.optionsnondisplayedtrademessage.nondisplayedtradetradecond1"] = canonical::text(canonical::character(message.fields.non_displayed_trade_trade_cond_1.get().value()), '\0', false);
        values[entry + ".payload.optionsnondisplayedtrademessage.pricetype"] = canonical::number(message.fields.price_type.get().value());
    }

    void on_message(const protocol::options_cross_trade_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.optionscrosstrademessage";
        values[entry + ".payload.optionscrosstrademessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.optionscrosstrademessage.seriesindex"] = canonical::number(message.fields.series_index.get().value());
        values[entry + ".payload.optionscrosstrademessage.seriesseqnum"] = canonical::number(message.fields.series_seq_num.get().value());
        values[entry + ".payload.optionscrosstrademessage.crossid"] = canonical::number(message.fields.cross_id.get().value());
        values[entry + ".payload.optionscrosstrademessage.price"] = canonical::number(message.fields.price.get().value());
        values[entry + ".payload.optionscrosstrademessage.volume"] = canonical::number(message.fields.volume.get().value());
        values[entry + ".payload.optionscrosstrademessage.crosstype"] = canonical::text(canonical::character(message.fields.cross_type.get().value()), '\0', false);
    }

    void on_message(const protocol::options_trade_cancel_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.optionstradecancelmessage";
        values[entry + ".payload.optionstradecancelmessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.optionstradecancelmessage.seriesindex"] = canonical::number(message.fields.series_index.get().value());
        values[entry + ".payload.optionstradecancelmessage.seriesseqnum"] = canonical::number(message.fields.series_seq_num.get().value());
        values[entry + ".payload.optionstradecancelmessage.tradeid"] = canonical::number(message.fields.trade_id.get().value());
    }

    void on_message(const protocol::options_outright_series_summary_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.optionsoutrightseriessummarymessage";
        values[entry + ".payload.optionsoutrightseriessummarymessage.sourcetime"] = canonical::number(message.fields.source_time.get().value());
        values[entry + ".payload.optionsoutrightseriessummarymessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.optionsoutrightseriessummarymessage.seriesindex"] = canonical::number(message.fields.series_index.get().value());
        values[entry + ".payload.optionsoutrightseriessummarymessage.highprice"] = canonical::number(message.fields.high_price.get().value());
        values[entry + ".payload.optionsoutrightseriessummarymessage.lowprice"] = canonical::number(message.fields.low_price.get().value());
        values[entry + ".payload.optionsoutrightseriessummarymessage.open"] = canonical::number(message.fields.open.get().value());
        values[entry + ".payload.optionsoutrightseriessummarymessage.close"] = canonical::number(message.fields.close.get().value());
        values[entry + ".payload.optionsoutrightseriessummarymessage.totalvolume"] = canonical::number(message.fields.total_volume.get().value());
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
    std::printf("== Nyse.ArcaOptions.DeepFeed.Pillar.v1.2.m (advanced values)\n");
    int failures = 0;
    failures += check("OptionsAddOrderMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/OptionsAddOrderMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/OptionsAddOrderMessage.values");
    failures += check("OptionsCrossTradeMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/OptionsCrossTradeMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/OptionsCrossTradeMessage.values");
    failures += check("OptionsDeleteOrderMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/OptionsDeleteOrderMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/OptionsDeleteOrderMessage.values");
    failures += check("OptionsImbalanceMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/OptionsImbalanceMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/OptionsImbalanceMessage.values");
    failures += check("OptionsModifyOrderMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/OptionsModifyOrderMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/OptionsModifyOrderMessage.values");
    failures += check("OptionsNonDisplayedTradeMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/OptionsNonDisplayedTradeMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/OptionsNonDisplayedTradeMessage.values");
    failures += check("OptionsOrderExecutionMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/OptionsOrderExecutionMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/OptionsOrderExecutionMessage.values");
    failures += check("OptionsReplaceOrderMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/OptionsReplaceOrderMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/OptionsReplaceOrderMessage.values");
    failures += check("OptionsStatusMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/OptionsStatusMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/OptionsStatusMessage.values");
    failures += check("OutrightSeriesIndexMappingMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/OutrightSeriesIndexMappingMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/OutrightSeriesIndexMappingMessage.values");
    failures += check("SecurityStatusMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/SecurityStatusMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/SecurityStatusMessage.values");
    failures += check("SequenceNumberResetMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/SequenceNumberResetMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/SequenceNumberResetMessage.values");
    failures += check("SourceTimeReferenceMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/SourceTimeReferenceMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/SourceTimeReferenceMessage.values");
    failures += check("SymbolClearMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/SymbolClearMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/SymbolClearMessage.values");
    failures += check("SymbolIndexMappingMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/SymbolIndexMappingMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/SymbolIndexMappingMessage.values");
    return failures == 0 ? 0 : 1;
}
