// Iex.IexEquities.DeepPlus.IexTp.v1.01 canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/binary/classes/iex/iexequities/deepplus/iextp/v1.01/definitions.hpp"

namespace protocol = ::iex::iexequities::deepplus::iextp::v1_01;

namespace {

// The values the Classes Packet decodes from one datagram, by indexed address. A datagram it cannot
// decode is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::Packet packet;

    try {
        packet.decode(frame.payload, frame.payload_len);
    } catch (const protocol::DecodeError& error) {
        values["(does not decode)"] = error.what();
        return values;
    }

    values["packet.iextpheader.version"] = canonical::number(packet.iextp_header().version());
    values["packet.iextpheader.messageprotocolid"] = canonical::number(packet.iextp_header().message_protocol_id());
    values["packet.iextpheader.channelid"] = canonical::number(packet.iextp_header().channel_id());
    values["packet.iextpheader.sessionid"] = canonical::number(packet.iextp_header().session_id());
    values["packet.iextpheader.payloadlength"] = canonical::number(packet.iextp_header().payload_length());
    values["packet.iextpheader.messagecount"] = canonical::number(packet.iextp_header().message_count());
    values["packet.iextpheader.streamoffset"] = canonical::number(packet.iextp_header().stream_offset());
    values["packet.iextpheader.firstmessagesequencenumber"] = canonical::number(packet.iextp_header().first_message_sequence_number());
    values["packet.iextpheader.sendtime"] = canonical::number(packet.iextp_header().send_time());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(each.message_header().message_length());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(each.message_header().message_type()));

        if (const auto* message = dynamic_cast<const protocol::SystemEventMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.systemeventmessage";
            values[entry + ".messagedata.systemeventmessage.systemevent"] = canonical::text(canonical::character((*message).system_event()));
            values[entry + ".messagedata.systemeventmessage.timestamp"] = canonical::number((*message).timestamp());
        } else if (const auto* message = dynamic_cast<const protocol::SecurityDirectoryMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.securitydirectorymessage";
            values[entry + ".messagedata.securitydirectorymessage.securitydirectoryflags.etp"] = canonical::number(static_cast<std::uint64_t>((*message).security_directory_flags().etp()));
            values[entry + ".messagedata.securitydirectorymessage.securitydirectoryflags.whenissued"] = canonical::number(static_cast<std::uint64_t>((*message).security_directory_flags().when_issued()));
            values[entry + ".messagedata.securitydirectorymessage.securitydirectoryflags.testsecurity"] = canonical::number(static_cast<std::uint64_t>((*message).security_directory_flags().test_security()));
            values[entry + ".messagedata.securitydirectorymessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.securitydirectorymessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".messagedata.securitydirectorymessage.roundlotsize"] = canonical::number((*message).round_lot_size());
            values[entry + ".messagedata.securitydirectorymessage.adjustedpocprice"] = canonical::scaled((*message).adjusted_poc_price().mantissa(), (*message).adjusted_poc_price().exponent());
            values[entry + ".messagedata.securitydirectorymessage.luldtier"] = canonical::number((*message).luld_tier());
        } else if (const auto* message = dynamic_cast<const protocol::TradingStatusMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradingstatusmessage";
            values[entry + ".messagedata.tradingstatusmessage.tradingstatus"] = canonical::text(canonical::character((*message).trading_status()));
            values[entry + ".messagedata.tradingstatusmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.tradingstatusmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".messagedata.tradingstatusmessage.reason"] = canonical::text(std::string((*message).reason()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::RetailLiquidityIndicatorMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.retailliquidityindicatormessage";
            values[entry + ".messagedata.retailliquidityindicatormessage.retailliquidityindicator"] = canonical::text(canonical::character((*message).retail_liquidity_indicator()));
            values[entry + ".messagedata.retailliquidityindicatormessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.retailliquidityindicatormessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::OperationalHaltStatusMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.operationalhaltstatusmessage";
            values[entry + ".messagedata.operationalhaltstatusmessage.operationalhaltstatus"] = canonical::text(canonical::character((*message).operational_halt_status()));
            values[entry + ".messagedata.operationalhaltstatusmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.operationalhaltstatusmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::ShortSalePriceTestStatusMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.shortsalepriceteststatusmessage";
            values[entry + ".messagedata.shortsalepriceteststatusmessage.shortsalepriceteststatus"] = canonical::number((*message).short_sale_price_test_status());
            values[entry + ".messagedata.shortsalepriceteststatusmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.shortsalepriceteststatusmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".messagedata.shortsalepriceteststatusmessage.detail"] = canonical::text(canonical::character((*message).detail()));
        } else if (const auto* message = dynamic_cast<const protocol::SecurityEventMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.securityeventmessage";
            values[entry + ".messagedata.securityeventmessage.securityevent"] = canonical::text(canonical::character((*message).security_event()));
            values[entry + ".messagedata.securityeventmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.securityeventmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.addordermessage";
            values[entry + ".messagedata.addordermessage.side"] = canonical::text(canonical::character((*message).side()));
            values[entry + ".messagedata.addordermessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.addordermessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".messagedata.addordermessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".messagedata.addordermessage.size"] = canonical::number((*message).size());
            values[entry + ".messagedata.addordermessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::OrderModifyMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.ordermodifymessage";
            values[entry + ".messagedata.ordermodifymessage.modifyflags.priority"] = canonical::number(static_cast<std::uint64_t>((*message).modify_flags().priority()));
            values[entry + ".messagedata.ordermodifymessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.ordermodifymessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".messagedata.ordermodifymessage.orderidreference"] = canonical::number((*message).order_id_reference());
            values[entry + ".messagedata.ordermodifymessage.size"] = canonical::number((*message).size());
            values[entry + ".messagedata.ordermodifymessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::OrderDeleteMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.orderdeletemessage";
            values[entry + ".messagedata.orderdeletemessage.reserved1"] = canonical::text(canonical::character((*message).reserved_1()));
            values[entry + ".messagedata.orderdeletemessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.orderdeletemessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".messagedata.orderdeletemessage.orderidreference"] = canonical::number((*message).order_id_reference());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.orderexecutedmessage";
            values[entry + ".messagedata.orderexecutedmessage.saleconditionflags.singlepricecrosstrade"] = canonical::number(static_cast<std::uint64_t>((*message).sale_condition_flags().singleprice_cross_trade()));
            values[entry + ".messagedata.orderexecutedmessage.saleconditionflags.tradethroughexempt"] = canonical::number(static_cast<std::uint64_t>((*message).sale_condition_flags().trade_through_exempt()));
            values[entry + ".messagedata.orderexecutedmessage.saleconditionflags.oddlot"] = canonical::number(static_cast<std::uint64_t>((*message).sale_condition_flags().odd_lot()));
            values[entry + ".messagedata.orderexecutedmessage.saleconditionflags.extendedhours"] = canonical::number(static_cast<std::uint64_t>((*message).sale_condition_flags().extended_hours()));
            values[entry + ".messagedata.orderexecutedmessage.saleconditionflags.intermarketsweep"] = canonical::number(static_cast<std::uint64_t>((*message).sale_condition_flags().intermarket_sweep()));
            values[entry + ".messagedata.orderexecutedmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.orderexecutedmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".messagedata.orderexecutedmessage.orderidreference"] = canonical::number((*message).order_id_reference());
            values[entry + ".messagedata.orderexecutedmessage.size"] = canonical::number((*message).size());
            values[entry + ".messagedata.orderexecutedmessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
            values[entry + ".messagedata.orderexecutedmessage.tradeid"] = canonical::number((*message).trade_id());
        } else if (const auto* message = dynamic_cast<const protocol::TradeMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.trademessage";
            values[entry + ".messagedata.trademessage.saleconditionflags.singlepricecrosstrade"] = canonical::number(static_cast<std::uint64_t>((*message).sale_condition_flags().singleprice_cross_trade()));
            values[entry + ".messagedata.trademessage.saleconditionflags.tradethroughexempt"] = canonical::number(static_cast<std::uint64_t>((*message).sale_condition_flags().trade_through_exempt()));
            values[entry + ".messagedata.trademessage.saleconditionflags.oddlot"] = canonical::number(static_cast<std::uint64_t>((*message).sale_condition_flags().odd_lot()));
            values[entry + ".messagedata.trademessage.saleconditionflags.extendedhours"] = canonical::number(static_cast<std::uint64_t>((*message).sale_condition_flags().extended_hours()));
            values[entry + ".messagedata.trademessage.saleconditionflags.intermarketsweep"] = canonical::number(static_cast<std::uint64_t>((*message).sale_condition_flags().intermarket_sweep()));
            values[entry + ".messagedata.trademessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.trademessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".messagedata.trademessage.size"] = canonical::number((*message).size());
            values[entry + ".messagedata.trademessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
            values[entry + ".messagedata.trademessage.tradeid"] = canonical::number((*message).trade_id());
        } else if (const auto* message = dynamic_cast<const protocol::TradeBreakMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradebreakmessage";
            values[entry + ".messagedata.tradebreakmessage.saleconditionflags.singlepricecrosstrade"] = canonical::number(static_cast<std::uint64_t>((*message).sale_condition_flags().singleprice_cross_trade()));
            values[entry + ".messagedata.tradebreakmessage.saleconditionflags.tradethroughexempt"] = canonical::number(static_cast<std::uint64_t>((*message).sale_condition_flags().trade_through_exempt()));
            values[entry + ".messagedata.tradebreakmessage.saleconditionflags.oddlot"] = canonical::number(static_cast<std::uint64_t>((*message).sale_condition_flags().odd_lot()));
            values[entry + ".messagedata.tradebreakmessage.saleconditionflags.extendedhours"] = canonical::number(static_cast<std::uint64_t>((*message).sale_condition_flags().extended_hours()));
            values[entry + ".messagedata.tradebreakmessage.saleconditionflags.intermarketsweep"] = canonical::number(static_cast<std::uint64_t>((*message).sale_condition_flags().intermarket_sweep()));
            values[entry + ".messagedata.tradebreakmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.tradebreakmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".messagedata.tradebreakmessage.size"] = canonical::number((*message).size());
            values[entry + ".messagedata.tradebreakmessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
            values[entry + ".messagedata.tradebreakmessage.tradeid"] = canonical::number((*message).trade_id());
        } else if (const auto* message = dynamic_cast<const protocol::ClearBookMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.clearbookmessage";
            values[entry + ".messagedata.clearbookmessage.reserved1"] = canonical::text(canonical::character((*message).reserved_1()));
            values[entry + ".messagedata.clearbookmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.clearbookmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
        }
    }

    return values;
}

// Read each datagram of a sample with Classes and hold it to the model's values
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
    std::printf("== Iex.IexEquities.DeepPlus.IexTp.v1.01 (classes values)\n");
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
