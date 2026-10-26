// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d canonical values, through the Flyweight reader: every value Flyweight reads
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
#include "cpp/binary/flyweight/miax/pearlequities/depthofmarket/mach/v1.3.d/definitions.hpp"

namespace protocol = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

namespace {

// The messages Data selects, their values set in the entry of the message holding it
struct DataHandler {
    canonical::Listing& values;
    const std::string& entry;

    void on(const protocol::SystemTimeMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.systemtimemessage";
        values[entry + ".payload.applicationmessage.data.systemtimemessage.seconds"] = canonical::number(message.seconds());
    }

    void on(const protocol::SymbolUpdateMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.symbolupdatemessage";
        values[entry + ".payload.applicationmessage.data.symbolupdatemessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".payload.applicationmessage.data.symbolupdatemessage.symbolid"] = canonical::number(message.symbol_id());
        values[entry + ".payload.applicationmessage.data.symbolupdatemessage.tickersymbol"] = canonical::text(std::string(message.ticker_symbol()), ' ', false);
        values[entry + ".payload.applicationmessage.data.symbolupdatemessage.testsecurityindicator"] = canonical::text(canonical::character(message.test_security_indicator()), ' ', false);
        values[entry + ".payload.applicationmessage.data.symbolupdatemessage.lotsize"] = canonical::number(message.lot_size());
        values[entry + ".payload.applicationmessage.data.symbolupdatemessage.openingtime"] = canonical::text(std::string(message.opening_time()), ' ', false);
        values[entry + ".payload.applicationmessage.data.symbolupdatemessage.closingtime"] = canonical::text(std::string(message.closing_time()), ' ', false);
        values[entry + ".payload.applicationmessage.data.symbolupdatemessage.primarymarketcode"] = canonical::text(canonical::character(message.primary_market_code()), ' ', false);
    }

    void on(const protocol::SystemStateMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.systemstatemessage";
        values[entry + ".payload.applicationmessage.data.systemstatemessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".payload.applicationmessage.data.systemstatemessage.domversion"] = canonical::text(std::string(message.do_m_version()), ' ', false);
        values[entry + ".payload.applicationmessage.data.systemstatemessage.sessionid"] = canonical::number(message.session_id());
        values[entry + ".payload.applicationmessage.data.systemstatemessage.systemstatus"] = canonical::text(canonical::character(message.system_status()), ' ', false);
    }

    void on(const protocol::SecurityTradingStatusNotificationMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.securitytradingstatusnotificationmessage";
        values[entry + ".payload.applicationmessage.data.securitytradingstatusnotificationmessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".payload.applicationmessage.data.securitytradingstatusnotificationmessage.symbolid"] = canonical::number(message.symbol_id());
        values[entry + ".payload.applicationmessage.data.securitytradingstatusnotificationmessage.tradingstatus"] = canonical::number(message.trading_status());
        values[entry + ".payload.applicationmessage.data.securitytradingstatusnotificationmessage.marketstate"] = canonical::number(message.market_state());
        values[entry + ".payload.applicationmessage.data.securitytradingstatusnotificationmessage.shortsalerestriction"] = canonical::text(canonical::character(message.short_sale_restriction()), ' ', false);
    }

    void on(const protocol::SymbolClearMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.symbolclearmessage";
        values[entry + ".payload.applicationmessage.data.symbolclearmessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".payload.applicationmessage.data.symbolclearmessage.symbolid"] = canonical::number(message.symbol_id());
    }

    void on(const protocol::AddOrderMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.addordermessage";
        values[entry + ".payload.applicationmessage.data.addordermessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".payload.applicationmessage.data.addordermessage.symbolid"] = canonical::number(message.symbol_id());
        values[entry + ".payload.applicationmessage.data.addordermessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.applicationmessage.data.addordermessage.orderside"] = canonical::text(canonical::character(message.order_side()), ' ', false);
        values[entry + ".payload.applicationmessage.data.addordermessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.applicationmessage.data.addordermessage.size"] = canonical::number(message.size());
        values[entry + ".payload.applicationmessage.data.addordermessage.attributableid"] = canonical::text(std::string(message.attributable_id()), ' ', false);
    }

    void on(const protocol::ModifyOrderMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.modifyordermessage";
        values[entry + ".payload.applicationmessage.data.modifyordermessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".payload.applicationmessage.data.modifyordermessage.symbolid"] = canonical::number(message.symbol_id());
        values[entry + ".payload.applicationmessage.data.modifyordermessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.applicationmessage.data.modifyordermessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.applicationmessage.data.modifyordermessage.size"] = canonical::number(message.size());
        values[entry + ".payload.applicationmessage.data.modifyordermessage.modifyorderflags.orderposition"] = canonical::number(static_cast<std::uint64_t>(message.modify_order_flags().order_position()));
    }

    void on(const protocol::DeleteOrderMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.deleteordermessage";
        values[entry + ".payload.applicationmessage.data.deleteordermessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".payload.applicationmessage.data.deleteordermessage.symbolid"] = canonical::number(message.symbol_id());
        values[entry + ".payload.applicationmessage.data.deleteordermessage.orderid"] = canonical::number(message.order_id());
    }

    void on(const protocol::OrderExecutionMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.orderexecutionmessage";
        values[entry + ".payload.applicationmessage.data.orderexecutionmessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".payload.applicationmessage.data.orderexecutionmessage.symbolid"] = canonical::number(message.symbol_id());
        values[entry + ".payload.applicationmessage.data.orderexecutionmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.applicationmessage.data.orderexecutionmessage.tradeid"] = canonical::number(message.trade_id());
        values[entry + ".payload.applicationmessage.data.orderexecutionmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.applicationmessage.data.orderexecutionmessage.size"] = canonical::number(message.size());
        values[entry + ".payload.applicationmessage.data.orderexecutionmessage.orderexecutionflags.sipreporting"] = canonical::number(static_cast<std::uint64_t>(message.order_execution_flags().sip_reporting()));
        values[entry + ".payload.applicationmessage.data.orderexecutionmessage.orderexecutionflags.tradedagainstretail"] = canonical::number(static_cast<std::uint64_t>(message.order_execution_flags().traded_against_retail()));
    }

    void on(const protocol::TradeMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.trademessage";
        values[entry + ".payload.applicationmessage.data.trademessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".payload.applicationmessage.data.trademessage.symbolid"] = canonical::number(message.symbol_id());
        values[entry + ".payload.applicationmessage.data.trademessage.tradeid"] = canonical::number(message.trade_id());
        values[entry + ".payload.applicationmessage.data.trademessage.correctionnumber"] = canonical::number(message.correction_number());
        values[entry + ".payload.applicationmessage.data.trademessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.applicationmessage.data.trademessage.size"] = canonical::number(message.size());
        values[entry + ".payload.applicationmessage.data.trademessage.tradeflags.sipreporting"] = canonical::number(static_cast<std::uint64_t>(message.trade_flags().sip_reporting()));
        values[entry + ".payload.applicationmessage.data.trademessage.tradeflags.retailtradeindicator"] = canonical::number(static_cast<std::uint64_t>(message.trade_flags().retail_trade_indicator()));
    }

    void on(const protocol::TradeCancelMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.tradecancelmessage";
        values[entry + ".payload.applicationmessage.data.tradecancelmessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".payload.applicationmessage.data.tradecancelmessage.symbolid"] = canonical::number(message.symbol_id());
        values[entry + ".payload.applicationmessage.data.tradecancelmessage.tradeid"] = canonical::number(message.trade_id());
        values[entry + ".payload.applicationmessage.data.tradecancelmessage.correctionnumber"] = canonical::number(message.correction_number());
        values[entry + ".payload.applicationmessage.data.tradecancelmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.applicationmessage.data.tradecancelmessage.size"] = canonical::number(message.size());
    }
};

// The handler the reader hands each datagram's views to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    void on(const protocol::UdpPacket&) {
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

    void on(const protocol::ApplicationMessage& message) {
        const std::string entry = "udppacket.machmessage[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "udppacket.machmessage.payload.applicationmessage";
        values[entry + ".payload.applicationmessage.messagetype"] = canonical::number(message.message_type());
        DataHandler selected{ values, entry };
        message.data(selected);
    }
};

// The values the Flyweight reader reads from one datagram, by indexed address. A datagram it cannot
// read is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::UdpPacketReader::read(std::span<const std::byte>(frame.payload, frame.payload_len), reader);
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
    std::printf("== Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d (flyweight values)\n");
    int failures = 0;
    failures += check("AddOrderMessage", "Miax/PearlEquities.DepthOfMarket.Mach.v1.3.d/AddOrderMessage.pcap", "miax/pearlequities/depthofmarket/mach/v1.3.d/AddOrderMessage.values");
    failures += check("DeleteOrderMessage", "Miax/PearlEquities.DepthOfMarket.Mach.v1.3.d/DeleteOrderMessage.pcap", "miax/pearlequities/depthofmarket/mach/v1.3.d/DeleteOrderMessage.values");
    failures += check("ModifyOrderMessage", "Miax/PearlEquities.DepthOfMarket.Mach.v1.3.d/ModifyOrderMessage.pcap", "miax/pearlequities/depthofmarket/mach/v1.3.d/ModifyOrderMessage.values");
    failures += check("OrderExecutionMessage", "Miax/PearlEquities.DepthOfMarket.Mach.v1.3.d/OrderExecutionMessage.pcap", "miax/pearlequities/depthofmarket/mach/v1.3.d/OrderExecutionMessage.values");
    failures += check("SecurityTradingStatusNotificationMessage", "Miax/PearlEquities.DepthOfMarket.Mach.v1.3.d/SecurityTradingStatusNotificationMessage.pcap", "miax/pearlequities/depthofmarket/mach/v1.3.d/SecurityTradingStatusNotificationMessage.values");
    failures += check("SystemTimeMessage", "Miax/PearlEquities.DepthOfMarket.Mach.v1.3.d/SystemTimeMessage.pcap", "miax/pearlequities/depthofmarket/mach/v1.3.d/SystemTimeMessage.values");
    failures += check("TradeMessage", "Miax/PearlEquities.DepthOfMarket.Mach.v1.3.d/TradeMessage.pcap", "miax/pearlequities/depthofmarket/mach/v1.3.d/TradeMessage.values");
    return failures == 0 ? 0 : 1;
}
