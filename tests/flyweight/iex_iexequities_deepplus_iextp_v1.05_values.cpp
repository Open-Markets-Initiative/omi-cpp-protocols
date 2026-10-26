// Iex.IexEquities.DeepPlus.IexTp.v1.05 canonical values, through the Flyweight reader: every value Flyweight reads
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
#include "cpp/flyweight/iex/iexequities/deepplus/iextp/v1.05/definitions.hpp"

namespace protocol = ::iex::iexequities::deepplus::iextp::v1_05;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        values["packet.iextpheader.version"] = canonical::number(packet.iextp_header().version());
        values["packet.iextpheader.messageprotocolid"] = canonical::number(packet.iextp_header().message_protocol_id());
        values["packet.iextpheader.channelid"] = canonical::number(packet.iextp_header().channel_id());
        values["packet.iextpheader.sessionid"] = canonical::number(packet.iextp_header().session_id());
        values["packet.iextpheader.payloadlength"] = canonical::number(packet.iextp_header().payload_length());
        values["packet.iextpheader.messagecount"] = canonical::number(packet.iextp_header().message_count());
        values["packet.iextpheader.streamoffset"] = canonical::number(packet.iextp_header().stream_offset());
        values["packet.iextpheader.firstmessagesequencenumber"] = canonical::number(packet.iextp_header().first_message_sequence_number());
        values["packet.iextpheader.sendtime"] = canonical::number(packet.iextp_header().send_time());
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

    void on(const protocol::SystemEventMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.systemeventmessage";
        values[entry + ".messagedata.systemeventmessage.systemevent"] = canonical::text(canonical::character(message.system_event()));
        values[entry + ".messagedata.systemeventmessage.timestamp"] = canonical::number(message.timestamp());
    }

    void on(const protocol::SecurityDirectoryMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.securitydirectorymessage";
        values[entry + ".messagedata.securitydirectorymessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.securitydirectorymessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".messagedata.securitydirectorymessage.roundlotsize"] = canonical::number(message.round_lot_size());
        values[entry + ".messagedata.securitydirectorymessage.adjustedpocprice"] = canonical::scaled(message.adjusted_poc_price().mantissa(), message.adjusted_poc_price().exponent());
        values[entry + ".messagedata.securitydirectorymessage.luldtier"] = canonical::number(message.luld_tier());
    }

    void on(const protocol::TradingStatusMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradingstatusmessage";
        values[entry + ".messagedata.tradingstatusmessage.tradingstatus"] = canonical::text(canonical::character(message.trading_status()));
        values[entry + ".messagedata.tradingstatusmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.tradingstatusmessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".messagedata.tradingstatusmessage.reason"] = canonical::text(std::string(message.reason()), ' ', false);
    }

    void on(const protocol::RetailLiquidityIndicatorMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.retailliquidityindicatormessage";
        values[entry + ".messagedata.retailliquidityindicatormessage.retailliquidityindicator"] = canonical::text(canonical::character(message.retail_liquidity_indicator()));
        values[entry + ".messagedata.retailliquidityindicatormessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.retailliquidityindicatormessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
    }

    void on(const protocol::OperationalHaltStatusMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.operationalhaltstatusmessage";
        values[entry + ".messagedata.operationalhaltstatusmessage.operationalhaltstatus"] = canonical::text(canonical::character(message.operational_halt_status()));
        values[entry + ".messagedata.operationalhaltstatusmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.operationalhaltstatusmessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
    }

    void on(const protocol::ShortSalePriceTestStatusMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.shortsalepriceteststatusmessage";
        values[entry + ".messagedata.shortsalepriceteststatusmessage.shortsalepriceteststatus"] = canonical::number(message.short_sale_price_test_status());
        values[entry + ".messagedata.shortsalepriceteststatusmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.shortsalepriceteststatusmessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".messagedata.shortsalepriceteststatusmessage.detail"] = canonical::text(canonical::character(message.detail()));
    }

    void on(const protocol::SecurityEventMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.securityeventmessage";
        values[entry + ".messagedata.securityeventmessage.securityevent"] = canonical::text(canonical::character(message.security_event()));
        values[entry + ".messagedata.securityeventmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.securityeventmessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
    }

    void on(const protocol::AddOrderMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.addordermessage";
        values[entry + ".messagedata.addordermessage.side"] = canonical::text(canonical::character(message.side()));
        values[entry + ".messagedata.addordermessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.addordermessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".messagedata.addordermessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".messagedata.addordermessage.size"] = canonical::number(message.size());
        values[entry + ".messagedata.addordermessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
    }

    void on(const protocol::OrderModifyMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.ordermodifymessage";
        values[entry + ".messagedata.ordermodifymessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.ordermodifymessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".messagedata.ordermodifymessage.orderidreference"] = canonical::number(message.order_id_reference());
        values[entry + ".messagedata.ordermodifymessage.size"] = canonical::number(message.size());
        values[entry + ".messagedata.ordermodifymessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
    }

    void on(const protocol::OrderDeleteMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.orderdeletemessage";
        values[entry + ".messagedata.orderdeletemessage.reserved1"] = canonical::text(canonical::character(message.reserved_1()));
        values[entry + ".messagedata.orderdeletemessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.orderdeletemessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".messagedata.orderdeletemessage.orderidreference"] = canonical::number(message.order_id_reference());
    }

    void on(const protocol::OrderExecutedMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.orderexecutedmessage";
        values[entry + ".messagedata.orderexecutedmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.orderexecutedmessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".messagedata.orderexecutedmessage.orderidreference"] = canonical::number(message.order_id_reference());
        values[entry + ".messagedata.orderexecutedmessage.size"] = canonical::number(message.size());
        values[entry + ".messagedata.orderexecutedmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".messagedata.orderexecutedmessage.tradeid"] = canonical::number(message.trade_id());
    }

    void on(const protocol::TradeMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.trademessage";
        values[entry + ".messagedata.trademessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.trademessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".messagedata.trademessage.size"] = canonical::number(message.size());
        values[entry + ".messagedata.trademessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".messagedata.trademessage.tradeid"] = canonical::number(message.trade_id());
    }

    void on(const protocol::TradeBreakMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradebreakmessage";
        values[entry + ".messagedata.tradebreakmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.tradebreakmessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".messagedata.tradebreakmessage.size"] = canonical::number(message.size());
        values[entry + ".messagedata.tradebreakmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".messagedata.tradebreakmessage.tradeid"] = canonical::number(message.trade_id());
    }

    void on(const protocol::ClearBookMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.clearbookmessage";
        values[entry + ".messagedata.clearbookmessage.reserved1"] = canonical::text(canonical::character(message.reserved_1()));
        values[entry + ".messagedata.clearbookmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.clearbookmessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
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
    std::printf("== Iex.IexEquities.DeepPlus.IexTp.v1.05 (flyweight values)\n");
    int failures = 0;
    failures += check("AddOrderMessage", "Iex/IexEquities.DeepPlus.IexTp.v1.05/AddOrderMessage.pcap", "iex/iexequities/deepplus/iextp/v1.05/AddOrderMessage.values");
    failures += check("OperationalHaltStatusMessage", "Iex/IexEquities.DeepPlus.IexTp.v1.05/OperationalHaltStatusMessage.pcap", "iex/iexequities/deepplus/iextp/v1.05/OperationalHaltStatusMessage.values");
    failures += check("OrderDeleteMessage", "Iex/IexEquities.DeepPlus.IexTp.v1.05/OrderDeleteMessage.pcap", "iex/iexequities/deepplus/iextp/v1.05/OrderDeleteMessage.values");
    failures += check("OrderExecutedMessage", "Iex/IexEquities.DeepPlus.IexTp.v1.05/OrderExecutedMessage.pcap", "iex/iexequities/deepplus/iextp/v1.05/OrderExecutedMessage.values");
    failures += check("OrderModifyMessage", "Iex/IexEquities.DeepPlus.IexTp.v1.05/OrderModifyMessage.pcap", "iex/iexequities/deepplus/iextp/v1.05/OrderModifyMessage.values");
    failures += check("RetailLiquidityIndicatorMessage", "Iex/IexEquities.DeepPlus.IexTp.v1.05/RetailLiquidityIndicatorMessage.pcap", "iex/iexequities/deepplus/iextp/v1.05/RetailLiquidityIndicatorMessage.values");
    failures += check("SecurityEventMessage", "Iex/IexEquities.DeepPlus.IexTp.v1.05/SecurityEventMessage.pcap", "iex/iexequities/deepplus/iextp/v1.05/SecurityEventMessage.values");
    failures += check("ShortSalePriceTestStatusMessage", "Iex/IexEquities.DeepPlus.IexTp.v1.05/ShortSalePriceTestStatusMessage.pcap", "iex/iexequities/deepplus/iextp/v1.05/ShortSalePriceTestStatusMessage.values");
    failures += check("SystemEventMessage", "Iex/IexEquities.DeepPlus.IexTp.v1.05/SystemEventMessage.pcap", "iex/iexequities/deepplus/iextp/v1.05/SystemEventMessage.values");
    failures += check("TradeMessage", "Iex/IexEquities.DeepPlus.IexTp.v1.05/TradeMessage.pcap", "iex/iexequities/deepplus/iextp/v1.05/TradeMessage.values");
    failures += check("TradingStatusMessage", "Iex/IexEquities.DeepPlus.IexTp.v1.05/TradingStatusMessage.pcap", "iex/iexequities/deepplus/iextp/v1.05/TradingStatusMessage.values");
    return failures == 0 ? 0 : 1;
}