// Iex.IexEquities.DeepPlus.IexTp.v1.01 canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/iex/iexequities/deepplus/iextp/v1.01/definitions.hpp"

namespace protocol = ::iex::iexequities::deepplus::iextp::v1_01;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    values["packet.iextpheader.version"] = canonical::number(iterator.iextp_header->version.get());
    values["packet.iextpheader.messageprotocolid"] = canonical::number(iterator.iextp_header->message_protocol_id.get());
    values["packet.iextpheader.channelid"] = canonical::number(iterator.iextp_header->channel_id.get());
    values["packet.iextpheader.sessionid"] = canonical::number(iterator.iextp_header->session_id.get());
    values["packet.iextpheader.payloadlength"] = canonical::number(iterator.iextp_header->payload_length.get());
    values["packet.iextpheader.messagecount"] = canonical::number(iterator.iextp_header->message_count.get());
    values["packet.iextpheader.streamoffset"] = canonical::number(iterator.iextp_header->stream_offset.get());
    values["packet.iextpheader.firstmessagesequencenumber"] = canonical::number(iterator.iextp_header->first_message_sequence_number.get());
    values["packet.iextpheader.sendtime"] = canonical::number(iterator.iextp_header->send_time.get());

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(iterator.message_header->message_length.get());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(iterator.message_header->message_type.get()));

        if (iterator.message_type == protocol::SystemEventMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.systemeventmessage";
            [[maybe_unused]] const auto* message = protocol::SystemEventMessage::parse(iterator.message);
            values[entry + ".messagedata.systemeventmessage.systemevent"] = canonical::text(canonical::character(message->system_event.get()));
            values[entry + ".messagedata.systemeventmessage.timestamp"] = canonical::number(message->timestamp.get());
        } else if (iterator.message_type == protocol::SecurityDirectoryMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.securitydirectorymessage";
            [[maybe_unused]] const auto* message = protocol::SecurityDirectoryMessage::parse(iterator.message);
            values[entry + ".messagedata.securitydirectorymessage.securitydirectoryflags.etp"] = canonical::number(static_cast<std::uint64_t>(message->security_directory_flags.Etp()));
            values[entry + ".messagedata.securitydirectorymessage.securitydirectoryflags.whenissued"] = canonical::number(static_cast<std::uint64_t>(message->security_directory_flags.WhenIssued()));
            values[entry + ".messagedata.securitydirectorymessage.securitydirectoryflags.testsecurity"] = canonical::number(static_cast<std::uint64_t>(message->security_directory_flags.TestSecurity()));
            values[entry + ".messagedata.securitydirectorymessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.securitydirectorymessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".messagedata.securitydirectorymessage.roundlotsize"] = canonical::number(message->round_lot_size.get());
            values[entry + ".messagedata.securitydirectorymessage.adjustedpocprice"] = canonical::scaled(message->adjusted_poc_price.integer(), -4);
            values[entry + ".messagedata.securitydirectorymessage.luldtier"] = canonical::number(message->luld_tier.get());
        } else if (iterator.message_type == protocol::TradingStatusMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradingstatusmessage";
            [[maybe_unused]] const auto* message = protocol::TradingStatusMessage::parse(iterator.message);
            values[entry + ".messagedata.tradingstatusmessage.tradingstatus"] = canonical::text(canonical::character(message->trading_status.get()));
            values[entry + ".messagedata.tradingstatusmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.tradingstatusmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".messagedata.tradingstatusmessage.reason"] = canonical::text(std::string(message->reason.get()), ' ', false);
        } else if (iterator.message_type == protocol::RetailLiquidityIndicatorMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.retailliquidityindicatormessage";
            [[maybe_unused]] const auto* message = protocol::RetailLiquidityIndicatorMessage::parse(iterator.message);
            values[entry + ".messagedata.retailliquidityindicatormessage.retailliquidityindicator"] = canonical::text(canonical::character(message->retail_liquidity_indicator.get()));
            values[entry + ".messagedata.retailliquidityindicatormessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.retailliquidityindicatormessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
        } else if (iterator.message_type == protocol::OperationalHaltStatusMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.operationalhaltstatusmessage";
            [[maybe_unused]] const auto* message = protocol::OperationalHaltStatusMessage::parse(iterator.message);
            values[entry + ".messagedata.operationalhaltstatusmessage.operationalhaltstatus"] = canonical::text(canonical::character(message->operational_halt_status.get()));
            values[entry + ".messagedata.operationalhaltstatusmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.operationalhaltstatusmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
        } else if (iterator.message_type == protocol::ShortSalePriceTestStatusMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.shortsalepriceteststatusmessage";
            [[maybe_unused]] const auto* message = protocol::ShortSalePriceTestStatusMessage::parse(iterator.message);
            values[entry + ".messagedata.shortsalepriceteststatusmessage.shortsalepriceteststatus"] = canonical::number(message->short_sale_price_test_status.get());
            values[entry + ".messagedata.shortsalepriceteststatusmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.shortsalepriceteststatusmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".messagedata.shortsalepriceteststatusmessage.detail"] = canonical::text(canonical::character(message->detail.get()));
        } else if (iterator.message_type == protocol::SecurityEventMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.securityeventmessage";
            [[maybe_unused]] const auto* message = protocol::SecurityEventMessage::parse(iterator.message);
            values[entry + ".messagedata.securityeventmessage.securityevent"] = canonical::text(canonical::character(message->security_event.get()));
            values[entry + ".messagedata.securityeventmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.securityeventmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
        } else if (iterator.message_type == protocol::AddOrderMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.addordermessage";
            [[maybe_unused]] const auto* message = protocol::AddOrderMessage::parse(iterator.message);
            values[entry + ".messagedata.addordermessage.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".messagedata.addordermessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.addordermessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".messagedata.addordermessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".messagedata.addordermessage.size"] = canonical::number(message->size.get());
            values[entry + ".messagedata.addordermessage.price"] = canonical::scaled(message->price.integer(), -4);
        } else if (iterator.message_type == protocol::OrderModifyMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.ordermodifymessage";
            [[maybe_unused]] const auto* message = protocol::OrderModifyMessage::parse(iterator.message);
            values[entry + ".messagedata.ordermodifymessage.modifyflags.priority"] = canonical::number(static_cast<std::uint64_t>(message->modify_flags.Priority()));
            values[entry + ".messagedata.ordermodifymessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.ordermodifymessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".messagedata.ordermodifymessage.orderidreference"] = canonical::number(message->order_id_reference.get());
            values[entry + ".messagedata.ordermodifymessage.size"] = canonical::number(message->size.get());
            values[entry + ".messagedata.ordermodifymessage.price"] = canonical::scaled(message->price.integer(), -4);
        } else if (iterator.message_type == protocol::OrderDeleteMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.orderdeletemessage";
            [[maybe_unused]] const auto* message = protocol::OrderDeleteMessage::parse(iterator.message);
            values[entry + ".messagedata.orderdeletemessage.reserved1"] = canonical::text(canonical::character(message->reserved_1.get()));
            values[entry + ".messagedata.orderdeletemessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.orderdeletemessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".messagedata.orderdeletemessage.orderidreference"] = canonical::number(message->order_id_reference.get());
        } else if (iterator.message_type == protocol::OrderExecutedMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.orderexecutedmessage";
            [[maybe_unused]] const auto* message = protocol::OrderExecutedMessage::parse(iterator.message);
            values[entry + ".messagedata.orderexecutedmessage.saleconditionflags.singlepricecrosstrade"] = canonical::number(static_cast<std::uint64_t>(message->sale_condition_flags.SinglePriceCrossTrade()));
            values[entry + ".messagedata.orderexecutedmessage.saleconditionflags.tradethroughexempt"] = canonical::number(static_cast<std::uint64_t>(message->sale_condition_flags.TradeThroughExempt()));
            values[entry + ".messagedata.orderexecutedmessage.saleconditionflags.oddlot"] = canonical::number(static_cast<std::uint64_t>(message->sale_condition_flags.OddLot()));
            values[entry + ".messagedata.orderexecutedmessage.saleconditionflags.extendedhours"] = canonical::number(static_cast<std::uint64_t>(message->sale_condition_flags.ExtendedHours()));
            values[entry + ".messagedata.orderexecutedmessage.saleconditionflags.intermarketsweep"] = canonical::number(static_cast<std::uint64_t>(message->sale_condition_flags.IntermarketSweep()));
            values[entry + ".messagedata.orderexecutedmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.orderexecutedmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".messagedata.orderexecutedmessage.orderidreference"] = canonical::number(message->order_id_reference.get());
            values[entry + ".messagedata.orderexecutedmessage.size"] = canonical::number(message->size.get());
            values[entry + ".messagedata.orderexecutedmessage.price"] = canonical::scaled(message->price.integer(), -4);
            values[entry + ".messagedata.orderexecutedmessage.tradeid"] = canonical::number(message->trade_id.get());
        } else if (iterator.message_type == protocol::TradeMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.trademessage";
            [[maybe_unused]] const auto* message = protocol::TradeMessage::parse(iterator.message);
            values[entry + ".messagedata.trademessage.saleconditionflags.singlepricecrosstrade"] = canonical::number(static_cast<std::uint64_t>(message->sale_condition_flags.SinglePriceCrossTrade()));
            values[entry + ".messagedata.trademessage.saleconditionflags.tradethroughexempt"] = canonical::number(static_cast<std::uint64_t>(message->sale_condition_flags.TradeThroughExempt()));
            values[entry + ".messagedata.trademessage.saleconditionflags.oddlot"] = canonical::number(static_cast<std::uint64_t>(message->sale_condition_flags.OddLot()));
            values[entry + ".messagedata.trademessage.saleconditionflags.extendedhours"] = canonical::number(static_cast<std::uint64_t>(message->sale_condition_flags.ExtendedHours()));
            values[entry + ".messagedata.trademessage.saleconditionflags.intermarketsweep"] = canonical::number(static_cast<std::uint64_t>(message->sale_condition_flags.IntermarketSweep()));
            values[entry + ".messagedata.trademessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.trademessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".messagedata.trademessage.size"] = canonical::number(message->size.get());
            values[entry + ".messagedata.trademessage.price"] = canonical::scaled(message->price.integer(), -4);
            values[entry + ".messagedata.trademessage.tradeid"] = canonical::number(message->trade_id.get());
        } else if (iterator.message_type == protocol::TradeBreakMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradebreakmessage";
            [[maybe_unused]] const auto* message = protocol::TradeBreakMessage::parse(iterator.message);
            values[entry + ".messagedata.tradebreakmessage.saleconditionflags.singlepricecrosstrade"] = canonical::number(static_cast<std::uint64_t>(message->sale_condition_flags.SinglePriceCrossTrade()));
            values[entry + ".messagedata.tradebreakmessage.saleconditionflags.tradethroughexempt"] = canonical::number(static_cast<std::uint64_t>(message->sale_condition_flags.TradeThroughExempt()));
            values[entry + ".messagedata.tradebreakmessage.saleconditionflags.oddlot"] = canonical::number(static_cast<std::uint64_t>(message->sale_condition_flags.OddLot()));
            values[entry + ".messagedata.tradebreakmessage.saleconditionflags.extendedhours"] = canonical::number(static_cast<std::uint64_t>(message->sale_condition_flags.ExtendedHours()));
            values[entry + ".messagedata.tradebreakmessage.saleconditionflags.intermarketsweep"] = canonical::number(static_cast<std::uint64_t>(message->sale_condition_flags.IntermarketSweep()));
            values[entry + ".messagedata.tradebreakmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.tradebreakmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".messagedata.tradebreakmessage.size"] = canonical::number(message->size.get());
            values[entry + ".messagedata.tradebreakmessage.price"] = canonical::scaled(message->price.integer(), -4);
            values[entry + ".messagedata.tradebreakmessage.tradeid"] = canonical::number(message->trade_id.get());
        } else if (iterator.message_type == protocol::ClearBookMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.clearbookmessage";
            [[maybe_unused]] const auto* message = protocol::ClearBookMessage::parse(iterator.message);
            values[entry + ".messagedata.clearbookmessage.reserved1"] = canonical::text(canonical::character(message->reserved_1.get()));
            values[entry + ".messagedata.clearbookmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.clearbookmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
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
    std::printf("== Iex.IexEquities.DeepPlus.IexTp.v1.01 (modern values)\n");
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
