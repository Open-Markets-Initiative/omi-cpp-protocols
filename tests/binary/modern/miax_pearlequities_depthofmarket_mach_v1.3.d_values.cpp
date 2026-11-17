// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/miax/pearlequities/depthofmarket/mach/v1.3.d/definitions.hpp"

namespace protocol = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MachMessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "udppacket.machmessage[" + std::to_string(index++) + "]";
        values[entry + ".machpacketheader.sequencenumber"] = canonical::number(iterator.mach_packet_header->sequence_number.get());
        values[entry + ".machpacketheader.machpacketlength"] = canonical::number(iterator.mach_packet_header->mach_packet_length.get());
        values[entry + ".machpacketheader.machpackettype"] = canonical::number(iterator.mach_packet_header->mach_packet_type.get());
        values[entry + ".machpacketheader.sessionnumber"] = canonical::number(iterator.mach_packet_header->session_number.get());

        if (iterator.mach_packet_type == 3) {
            values[entry + ".payload"] = "udppacket.machmessage.payload.applicationmessage";
            [[maybe_unused]] const auto* message = protocol::ApplicationMessage::parse(iterator.message);
            values[entry + ".payload.applicationmessage.messagetype"] = canonical::number(message->message_type.get());
            if (message->message_type.get() == protocol::SystemTimeMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.systemtimemessage";
                [[maybe_unused]] const auto* message_2 = protocol::SystemTimeMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.systemtimemessage.seconds"] = canonical::number(message_2->seconds.get());
            } else if (message->message_type.get() == protocol::SymbolUpdateMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.symbolupdatemessage";
                [[maybe_unused]] const auto* message_2 = protocol::SymbolUpdateMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.symbolupdatemessage.nanoseconds"] = canonical::number(message_2->nanoseconds.get());
                values[entry + ".payload.applicationmessage.data.symbolupdatemessage.symbolid"] = canonical::number(message_2->symbol_id.get());
                values[entry + ".payload.applicationmessage.data.symbolupdatemessage.tickersymbol"] = canonical::text(std::string(message_2->ticker_symbol.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.symbolupdatemessage.testsecurityindicator"] = canonical::text(canonical::character(message_2->test_security_indicator.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.symbolupdatemessage.lotsize"] = canonical::number(message_2->lot_size.get());
                values[entry + ".payload.applicationmessage.data.symbolupdatemessage.openingtime"] = canonical::text(std::string(message_2->opening_time.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.symbolupdatemessage.closingtime"] = canonical::text(std::string(message_2->closing_time.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.symbolupdatemessage.primarymarketcode"] = canonical::text(canonical::character(message_2->primary_market_code.get()), ' ', false);
            } else if (message->message_type.get() == protocol::SystemStateMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.systemstatemessage";
                [[maybe_unused]] const auto* message_2 = protocol::SystemStateMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.systemstatemessage.nanoseconds"] = canonical::number(message_2->nanoseconds.get());
                values[entry + ".payload.applicationmessage.data.systemstatemessage.domversion"] = canonical::text(std::string(message_2->do_m_version.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.systemstatemessage.sessionid"] = canonical::number(message_2->session_id.get());
                values[entry + ".payload.applicationmessage.data.systemstatemessage.systemstatus"] = canonical::text(canonical::character(message_2->system_status.get()), ' ', false);
            } else if (message->message_type.get() == protocol::SecurityTradingStatusNotificationMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.securitytradingstatusnotificationmessage";
                [[maybe_unused]] const auto* message_2 = protocol::SecurityTradingStatusNotificationMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.securitytradingstatusnotificationmessage.nanoseconds"] = canonical::number(message_2->nanoseconds.get());
                values[entry + ".payload.applicationmessage.data.securitytradingstatusnotificationmessage.symbolid"] = canonical::number(message_2->symbol_id.get());
                values[entry + ".payload.applicationmessage.data.securitytradingstatusnotificationmessage.tradingstatus"] = canonical::number(message_2->trading_status.get());
                values[entry + ".payload.applicationmessage.data.securitytradingstatusnotificationmessage.marketstate"] = canonical::number(message_2->market_state.get());
                values[entry + ".payload.applicationmessage.data.securitytradingstatusnotificationmessage.shortsalerestriction"] = canonical::text(canonical::character(message_2->short_sale_restriction.get()), ' ', false);
            } else if (message->message_type.get() == protocol::SymbolClearMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.symbolclearmessage";
                [[maybe_unused]] const auto* message_2 = protocol::SymbolClearMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.symbolclearmessage.nanoseconds"] = canonical::number(message_2->nanoseconds.get());
                values[entry + ".payload.applicationmessage.data.symbolclearmessage.symbolid"] = canonical::number(message_2->symbol_id.get());
            } else if (message->message_type.get() == protocol::AddOrderMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.addordermessage";
                [[maybe_unused]] const auto* message_2 = protocol::AddOrderMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.addordermessage.nanoseconds"] = canonical::number(message_2->nanoseconds.get());
                values[entry + ".payload.applicationmessage.data.addordermessage.symbolid"] = canonical::number(message_2->symbol_id.get());
                values[entry + ".payload.applicationmessage.data.addordermessage.orderid"] = canonical::number(message_2->order_id.get());
                values[entry + ".payload.applicationmessage.data.addordermessage.orderside"] = canonical::text(canonical::character(message_2->order_side.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.addordermessage.price"] = canonical::scaled(message_2->price.integer(), -6);
                values[entry + ".payload.applicationmessage.data.addordermessage.size"] = canonical::number(message_2->size.get());
                values[entry + ".payload.applicationmessage.data.addordermessage.attributableid"] = canonical::text(std::string(message_2->attributable_id.get()), ' ', false);
            } else if (message->message_type.get() == protocol::ModifyOrderMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.modifyordermessage";
                [[maybe_unused]] const auto* message_2 = protocol::ModifyOrderMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.modifyordermessage.nanoseconds"] = canonical::number(message_2->nanoseconds.get());
                values[entry + ".payload.applicationmessage.data.modifyordermessage.symbolid"] = canonical::number(message_2->symbol_id.get());
                values[entry + ".payload.applicationmessage.data.modifyordermessage.orderid"] = canonical::number(message_2->order_id.get());
                values[entry + ".payload.applicationmessage.data.modifyordermessage.price"] = canonical::scaled(message_2->price.integer(), -6);
                values[entry + ".payload.applicationmessage.data.modifyordermessage.size"] = canonical::number(message_2->size.get());
                values[entry + ".payload.applicationmessage.data.modifyordermessage.modifyorderflags.orderposition"] = canonical::number(static_cast<std::uint64_t>(message_2->modify_order_flags.OrderPosition()));
            } else if (message->message_type.get() == protocol::DeleteOrderMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.deleteordermessage";
                [[maybe_unused]] const auto* message_2 = protocol::DeleteOrderMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.deleteordermessage.nanoseconds"] = canonical::number(message_2->nanoseconds.get());
                values[entry + ".payload.applicationmessage.data.deleteordermessage.symbolid"] = canonical::number(message_2->symbol_id.get());
                values[entry + ".payload.applicationmessage.data.deleteordermessage.orderid"] = canonical::number(message_2->order_id.get());
            } else if (message->message_type.get() == protocol::OrderExecutionMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.orderexecutionmessage";
                [[maybe_unused]] const auto* message_2 = protocol::OrderExecutionMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.orderexecutionmessage.nanoseconds"] = canonical::number(message_2->nanoseconds.get());
                values[entry + ".payload.applicationmessage.data.orderexecutionmessage.symbolid"] = canonical::number(message_2->symbol_id.get());
                values[entry + ".payload.applicationmessage.data.orderexecutionmessage.orderid"] = canonical::number(message_2->order_id.get());
                values[entry + ".payload.applicationmessage.data.orderexecutionmessage.tradeid"] = canonical::number(message_2->trade_id.get());
                values[entry + ".payload.applicationmessage.data.orderexecutionmessage.price"] = canonical::scaled(message_2->price.integer(), -6);
                values[entry + ".payload.applicationmessage.data.orderexecutionmessage.size"] = canonical::number(message_2->size.get());
                values[entry + ".payload.applicationmessage.data.orderexecutionmessage.orderexecutionflags.sipreporting"] = canonical::number(static_cast<std::uint64_t>(message_2->order_execution_flags.SipReporting()));
                values[entry + ".payload.applicationmessage.data.orderexecutionmessage.orderexecutionflags.tradedagainstretail"] = canonical::number(static_cast<std::uint64_t>(message_2->order_execution_flags.TradedAgainstRetail()));
            } else if (message->message_type.get() == protocol::TradeMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.trademessage";
                [[maybe_unused]] const auto* message_2 = protocol::TradeMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.trademessage.nanoseconds"] = canonical::number(message_2->nanoseconds.get());
                values[entry + ".payload.applicationmessage.data.trademessage.symbolid"] = canonical::number(message_2->symbol_id.get());
                values[entry + ".payload.applicationmessage.data.trademessage.tradeid"] = canonical::number(message_2->trade_id.get());
                values[entry + ".payload.applicationmessage.data.trademessage.correctionnumber"] = canonical::number(message_2->correction_number.get());
                values[entry + ".payload.applicationmessage.data.trademessage.price"] = canonical::scaled(message_2->price.integer(), -6);
                values[entry + ".payload.applicationmessage.data.trademessage.size"] = canonical::number(message_2->size.get());
                values[entry + ".payload.applicationmessage.data.trademessage.tradeflags.sipreporting"] = canonical::number(static_cast<std::uint64_t>(message_2->trade_flags.SipReporting()));
                values[entry + ".payload.applicationmessage.data.trademessage.tradeflags.retailtradeindicator"] = canonical::number(static_cast<std::uint64_t>(message_2->trade_flags.RetailTradeIndicator()));
            } else if (message->message_type.get() == protocol::TradeCancelMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.tradecancelmessage";
                [[maybe_unused]] const auto* message_2 = protocol::TradeCancelMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.nanoseconds"] = canonical::number(message_2->nanoseconds.get());
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.symbolid"] = canonical::number(message_2->symbol_id.get());
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.tradeid"] = canonical::number(message_2->trade_id.get());
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.correctionnumber"] = canonical::number(message_2->correction_number.get());
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.price"] = canonical::scaled(message_2->price.integer(), -6);
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.size"] = canonical::number(message_2->size.get());
            }
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
    std::printf("== Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d (modern values)\n");
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
