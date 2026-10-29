// Iex.IexEquities.DeepPlus.IexTp.v1.01 canonical values, through the Advanced session layer: every value Advanced
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
#include "cpp/binary/advanced/iex/iexequities/deepplus/iextp/v1.01/messages/session.hpp"

namespace protocol = ::iex::iexequities::deepplus::iextp::v1_01;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::iextp_header& header, const packet::Frame&) {
        values["packet.iextpheader.version"] = canonical::number(header.version.get().value());
        values["packet.iextpheader.messageprotocolid"] = canonical::number(header.message_protocol_id.get().value());
        values["packet.iextpheader.channelid"] = canonical::number(header.channel_id.get().value());
        values["packet.iextpheader.sessionid"] = canonical::number(header.session_id.get().value());
        values["packet.iextpheader.payloadlength"] = canonical::number(header.payload_length.get().value());
        values["packet.iextpheader.messagecount"] = canonical::number(header.message_count.get().value());
        values["packet.iextpheader.streamoffset"] = canonical::number(header.stream_offset.get().value());
        values["packet.iextpheader.firstmessagesequencenumber"] = canonical::number(header.first_message_sequence_number.get().value());
        values["packet.iextpheader.sendtime"] = canonical::number(header.send_time.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::iextp_header&) {
        ++index;
    }

    void on_message(const protocol::system_event_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.systemeventmessage";
        values[entry + ".messagedata.systemeventmessage.systemevent"] = canonical::text(canonical::character(message.fields.system_event.get().value()));
        values[entry + ".messagedata.systemeventmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
    }

    void on_message(const protocol::security_directory_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.securitydirectorymessage";
        values[entry + ".messagedata.securitydirectorymessage.securitydirectoryflags.etp"] = canonical::number(static_cast<std::uint64_t>(message.fields.security_directory_flags.has_etp()));
        values[entry + ".messagedata.securitydirectorymessage.securitydirectoryflags.whenissued"] = canonical::number(static_cast<std::uint64_t>(message.fields.security_directory_flags.has_when_issued()));
        values[entry + ".messagedata.securitydirectorymessage.securitydirectoryflags.testsecurity"] = canonical::number(static_cast<std::uint64_t>(message.fields.security_directory_flags.has_test_security()));
        values[entry + ".messagedata.securitydirectorymessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.securitydirectorymessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
        values[entry + ".messagedata.securitydirectorymessage.roundlotsize"] = canonical::number(message.fields.round_lot_size.get().value());
        values[entry + ".messagedata.securitydirectorymessage.adjustedpocprice"] = canonical::scaled(message.fields.adjusted_poc_price.get().value(), -4);
        values[entry + ".messagedata.securitydirectorymessage.luldtier"] = canonical::number(message.fields.luld_tier.get().value());
    }

    void on_message(const protocol::trading_status_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradingstatusmessage";
        values[entry + ".messagedata.tradingstatusmessage.tradingstatus"] = canonical::text(canonical::character(message.fields.trading_status.get().value()));
        values[entry + ".messagedata.tradingstatusmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.tradingstatusmessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
        values[entry + ".messagedata.tradingstatusmessage.reason"] = canonical::text(std::string(message.fields.reason.get().value()), ' ', false);
    }

    void on_message(const protocol::retail_liquidity_indicator_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.retailliquidityindicatormessage";
        values[entry + ".messagedata.retailliquidityindicatormessage.retailliquidityindicator"] = canonical::text(canonical::character(message.fields.retail_liquidity_indicator.get().value()));
        values[entry + ".messagedata.retailliquidityindicatormessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.retailliquidityindicatormessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
    }

    void on_message(const protocol::operational_halt_status_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.operationalhaltstatusmessage";
        values[entry + ".messagedata.operationalhaltstatusmessage.operationalhaltstatus"] = canonical::text(canonical::character(message.fields.operational_halt_status.get().value()));
        values[entry + ".messagedata.operationalhaltstatusmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.operationalhaltstatusmessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
    }

    void on_message(const protocol::short_sale_price_test_status_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.shortsalepriceteststatusmessage";
        values[entry + ".messagedata.shortsalepriceteststatusmessage.shortsalepriceteststatus"] = canonical::number(message.fields.short_sale_price_test_status.get().value());
        values[entry + ".messagedata.shortsalepriceteststatusmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.shortsalepriceteststatusmessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
        values[entry + ".messagedata.shortsalepriceteststatusmessage.detail"] = canonical::text(canonical::character(message.fields.detail.get().value()));
    }

    void on_message(const protocol::security_event_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.securityeventmessage";
        values[entry + ".messagedata.securityeventmessage.securityevent"] = canonical::text(canonical::character(message.fields.security_event.get().value()));
        values[entry + ".messagedata.securityeventmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.securityeventmessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
    }

    void on_message(const protocol::add_order_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.addordermessage";
        values[entry + ".messagedata.addordermessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()));
        values[entry + ".messagedata.addordermessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.addordermessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
        values[entry + ".messagedata.addordermessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".messagedata.addordermessage.size"] = canonical::number(message.fields.size.get().value());
        values[entry + ".messagedata.addordermessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
    }

    void on_message(const protocol::order_modify_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.ordermodifymessage";
        values[entry + ".messagedata.ordermodifymessage.modifyflags.priority"] = canonical::number(static_cast<std::uint64_t>(message.fields.modify_flags.has_priority()));
        values[entry + ".messagedata.ordermodifymessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.ordermodifymessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
        values[entry + ".messagedata.ordermodifymessage.orderidreference"] = canonical::number(message.fields.order_id_reference.get().value());
        values[entry + ".messagedata.ordermodifymessage.size"] = canonical::number(message.fields.size.get().value());
        values[entry + ".messagedata.ordermodifymessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
    }

    void on_message(const protocol::order_delete_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.orderdeletemessage";
        values[entry + ".messagedata.orderdeletemessage.reserved1"] = canonical::text(canonical::character(message.fields.reserved_1.get().value()));
        values[entry + ".messagedata.orderdeletemessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.orderdeletemessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
        values[entry + ".messagedata.orderdeletemessage.orderidreference"] = canonical::number(message.fields.order_id_reference.get().value());
    }

    void on_message(const protocol::order_executed_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.orderexecutedmessage";
        values[entry + ".messagedata.orderexecutedmessage.saleconditionflags.singlepricecrosstrade"] = canonical::number(static_cast<std::uint64_t>(message.fields.sale_condition_flags.has_single_price_cross_trade()));
        values[entry + ".messagedata.orderexecutedmessage.saleconditionflags.tradethroughexempt"] = canonical::number(static_cast<std::uint64_t>(message.fields.sale_condition_flags.has_trade_through_exempt()));
        values[entry + ".messagedata.orderexecutedmessage.saleconditionflags.oddlot"] = canonical::number(static_cast<std::uint64_t>(message.fields.sale_condition_flags.has_odd_lot()));
        values[entry + ".messagedata.orderexecutedmessage.saleconditionflags.extendedhours"] = canonical::number(static_cast<std::uint64_t>(message.fields.sale_condition_flags.has_extended_hours()));
        values[entry + ".messagedata.orderexecutedmessage.saleconditionflags.intermarketsweep"] = canonical::number(static_cast<std::uint64_t>(message.fields.sale_condition_flags.has_intermarket_sweep()));
        values[entry + ".messagedata.orderexecutedmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.orderexecutedmessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
        values[entry + ".messagedata.orderexecutedmessage.orderidreference"] = canonical::number(message.fields.order_id_reference.get().value());
        values[entry + ".messagedata.orderexecutedmessage.size"] = canonical::number(message.fields.size.get().value());
        values[entry + ".messagedata.orderexecutedmessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".messagedata.orderexecutedmessage.tradeid"] = canonical::number(message.fields.trade_id.get().value());
    }

    void on_message(const protocol::trade_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.trademessage";
        values[entry + ".messagedata.trademessage.saleconditionflags.singlepricecrosstrade"] = canonical::number(static_cast<std::uint64_t>(message.fields.sale_condition_flags.has_single_price_cross_trade()));
        values[entry + ".messagedata.trademessage.saleconditionflags.tradethroughexempt"] = canonical::number(static_cast<std::uint64_t>(message.fields.sale_condition_flags.has_trade_through_exempt()));
        values[entry + ".messagedata.trademessage.saleconditionflags.oddlot"] = canonical::number(static_cast<std::uint64_t>(message.fields.sale_condition_flags.has_odd_lot()));
        values[entry + ".messagedata.trademessage.saleconditionflags.extendedhours"] = canonical::number(static_cast<std::uint64_t>(message.fields.sale_condition_flags.has_extended_hours()));
        values[entry + ".messagedata.trademessage.saleconditionflags.intermarketsweep"] = canonical::number(static_cast<std::uint64_t>(message.fields.sale_condition_flags.has_intermarket_sweep()));
        values[entry + ".messagedata.trademessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.trademessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
        values[entry + ".messagedata.trademessage.size"] = canonical::number(message.fields.size.get().value());
        values[entry + ".messagedata.trademessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".messagedata.trademessage.tradeid"] = canonical::number(message.fields.trade_id.get().value());
    }

    void on_message(const protocol::trade_break_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradebreakmessage";
        values[entry + ".messagedata.tradebreakmessage.saleconditionflags.singlepricecrosstrade"] = canonical::number(static_cast<std::uint64_t>(message.fields.sale_condition_flags.has_single_price_cross_trade()));
        values[entry + ".messagedata.tradebreakmessage.saleconditionflags.tradethroughexempt"] = canonical::number(static_cast<std::uint64_t>(message.fields.sale_condition_flags.has_trade_through_exempt()));
        values[entry + ".messagedata.tradebreakmessage.saleconditionflags.oddlot"] = canonical::number(static_cast<std::uint64_t>(message.fields.sale_condition_flags.has_odd_lot()));
        values[entry + ".messagedata.tradebreakmessage.saleconditionflags.extendedhours"] = canonical::number(static_cast<std::uint64_t>(message.fields.sale_condition_flags.has_extended_hours()));
        values[entry + ".messagedata.tradebreakmessage.saleconditionflags.intermarketsweep"] = canonical::number(static_cast<std::uint64_t>(message.fields.sale_condition_flags.has_intermarket_sweep()));
        values[entry + ".messagedata.tradebreakmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.tradebreakmessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
        values[entry + ".messagedata.tradebreakmessage.size"] = canonical::number(message.fields.size.get().value());
        values[entry + ".messagedata.tradebreakmessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".messagedata.tradebreakmessage.tradeid"] = canonical::number(message.fields.trade_id.get().value());
    }

    void on_message(const protocol::clear_book_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.clearbookmessage";
        values[entry + ".messagedata.clearbookmessage.reserved1"] = canonical::text(canonical::character(message.fields.reserved_1.get().value()));
        values[entry + ".messagedata.clearbookmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.clearbookmessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
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
    std::printf("== Iex.IexEquities.DeepPlus.IexTp.v1.01 (advanced values)\n");
    int failures = 0;
    failures += check("AddOrderMessage", "Iex/IexEquities.DeepPlus.IexTp.v1.01/AddOrderMessage.pcap", "iex/iexequities/deepplus/iextp/v1.01/AddOrderMessage.values");
    failures += check("OperationalHaltStatusMessage", "Iex/IexEquities.DeepPlus.IexTp.v1.01/OperationalHaltStatusMessage.pcap", "iex/iexequities/deepplus/iextp/v1.01/OperationalHaltStatusMessage.values");
    failures += check("OrderDeleteMessage", "Iex/IexEquities.DeepPlus.IexTp.v1.01/OrderDeleteMessage.pcap", "iex/iexequities/deepplus/iextp/v1.01/OrderDeleteMessage.values");
    failures += check("OrderExecutedMessage", "Iex/IexEquities.DeepPlus.IexTp.v1.01/OrderExecutedMessage.pcap", "iex/iexequities/deepplus/iextp/v1.01/OrderExecutedMessage.values");
    failures += check("OrderModifyMessage", "Iex/IexEquities.DeepPlus.IexTp.v1.01/OrderModifyMessage.pcap", "iex/iexequities/deepplus/iextp/v1.01/OrderModifyMessage.values");
    failures += check("RetailLiquidityIndicatorMessage", "Iex/IexEquities.DeepPlus.IexTp.v1.01/RetailLiquidityIndicatorMessage.pcap", "iex/iexequities/deepplus/iextp/v1.01/RetailLiquidityIndicatorMessage.values");
    failures += check("SecurityDirectoryMessage", "Iex/IexEquities.DeepPlus.IexTp.v1.01/SecurityDirectoryMessage.pcap", "iex/iexequities/deepplus/iextp/v1.01/SecurityDirectoryMessage.values");
    failures += check("SecurityEventMessage", "Iex/IexEquities.DeepPlus.IexTp.v1.01/SecurityEventMessage.pcap", "iex/iexequities/deepplus/iextp/v1.01/SecurityEventMessage.values");
    failures += check("ShortSalePriceTestStatusMessage", "Iex/IexEquities.DeepPlus.IexTp.v1.01/ShortSalePriceTestStatusMessage.pcap", "iex/iexequities/deepplus/iextp/v1.01/ShortSalePriceTestStatusMessage.values");
    failures += check("SystemEventMessage", "Iex/IexEquities.DeepPlus.IexTp.v1.01/SystemEventMessage.pcap", "iex/iexequities/deepplus/iextp/v1.01/SystemEventMessage.values");
    failures += check("TradeBreakMessage", "Iex/IexEquities.DeepPlus.IexTp.v1.01/TradeBreakMessage.pcap", "iex/iexequities/deepplus/iextp/v1.01/TradeBreakMessage.values");
    failures += check("TradeMessage", "Iex/IexEquities.DeepPlus.IexTp.v1.01/TradeMessage.pcap", "iex/iexequities/deepplus/iextp/v1.01/TradeMessage.values");
    failures += check("TradingStatusMessage", "Iex/IexEquities.DeepPlus.IexTp.v1.01/TradingStatusMessage.pcap", "iex/iexequities/deepplus/iextp/v1.01/TradingStatusMessage.values");
    return failures == 0 ? 0 : 1;
}
