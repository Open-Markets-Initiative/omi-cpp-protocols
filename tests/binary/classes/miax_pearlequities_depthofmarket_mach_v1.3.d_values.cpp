// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/binary/classes/miax/pearlequities/depthofmarket/mach/v1.3.d/definitions.hpp"

namespace protocol = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

namespace {

// The values the Classes Packet decodes from one datagram, by indexed address. A datagram it cannot
// decode is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::UdpPacket packet;

    try {
        packet.decode(frame.payload, frame.payload_len);
    } catch (const protocol::DecodeError& error) {
        values["(does not decode)"] = error.what();
        return values;
    }


    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        const std::string entry = "udppacket.machmessage[" + std::to_string(index++) + "]";
        values[entry + ".machpacketheader.sequencenumber"] = canonical::number(each.mach_packet_header().sequence_number());
        values[entry + ".machpacketheader.machpacketlength"] = canonical::number(each.mach_packet_header().mach_packet_length());
        values[entry + ".machpacketheader.machpackettype"] = canonical::number(each.mach_packet_header().mach_packet_type());
        values[entry + ".machpacketheader.sessionnumber"] = canonical::number(each.mach_packet_header().session_number());

        if (const auto* message = dynamic_cast<const protocol::ApplicationMessage*>(each.message())) {
            values[entry + ".payload"] = "udppacket.machmessage.payload.applicationmessage";
            values[entry + ".payload.applicationmessage.messagetype"] = canonical::number((*message).message_type_field());
            if (const auto* message_2 = dynamic_cast<const protocol::SystemTimeMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.systemtimemessage";
                values[entry + ".payload.applicationmessage.data.systemtimemessage.seconds"] = canonical::number((*message_2).seconds());
            } else if (const auto* message_2 = dynamic_cast<const protocol::SymbolUpdateMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.symbolupdatemessage";
                values[entry + ".payload.applicationmessage.data.symbolupdatemessage.nanoseconds"] = canonical::number((*message_2).nanoseconds());
                values[entry + ".payload.applicationmessage.data.symbolupdatemessage.symbolid"] = canonical::number((*message_2).symbol_id());
                values[entry + ".payload.applicationmessage.data.symbolupdatemessage.tickersymbol"] = canonical::text(std::string((*message_2).ticker_symbol()), ' ', false);
                values[entry + ".payload.applicationmessage.data.symbolupdatemessage.testsecurityindicator"] = canonical::text(canonical::character((*message_2).test_security_indicator()), ' ', false);
                values[entry + ".payload.applicationmessage.data.symbolupdatemessage.lotsize"] = canonical::number((*message_2).lot_size());
                values[entry + ".payload.applicationmessage.data.symbolupdatemessage.openingtime"] = canonical::text(std::string((*message_2).opening_time()), ' ', false);
                values[entry + ".payload.applicationmessage.data.symbolupdatemessage.closingtime"] = canonical::text(std::string((*message_2).closing_time()), ' ', false);
                values[entry + ".payload.applicationmessage.data.symbolupdatemessage.primarymarketcode"] = canonical::text(canonical::character((*message_2).primary_market_code()), ' ', false);
            } else if (const auto* message_2 = dynamic_cast<const protocol::SystemStateMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.systemstatemessage";
                values[entry + ".payload.applicationmessage.data.systemstatemessage.nanoseconds"] = canonical::number((*message_2).nanoseconds());
                values[entry + ".payload.applicationmessage.data.systemstatemessage.domversion"] = canonical::text(std::string((*message_2).do_m_version()), ' ', false);
                values[entry + ".payload.applicationmessage.data.systemstatemessage.sessionid"] = canonical::number((*message_2).session_id());
                values[entry + ".payload.applicationmessage.data.systemstatemessage.systemstatus"] = canonical::text(canonical::character((*message_2).system_status()), ' ', false);
            } else if (const auto* message_2 = dynamic_cast<const protocol::SecurityTradingStatusNotificationMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.securitytradingstatusnotificationmessage";
                values[entry + ".payload.applicationmessage.data.securitytradingstatusnotificationmessage.nanoseconds"] = canonical::number((*message_2).nanoseconds());
                values[entry + ".payload.applicationmessage.data.securitytradingstatusnotificationmessage.symbolid"] = canonical::number((*message_2).symbol_id());
                values[entry + ".payload.applicationmessage.data.securitytradingstatusnotificationmessage.tradingstatus"] = canonical::number((*message_2).trading_status());
                values[entry + ".payload.applicationmessage.data.securitytradingstatusnotificationmessage.marketstate"] = canonical::number((*message_2).market_state());
                values[entry + ".payload.applicationmessage.data.securitytradingstatusnotificationmessage.shortsalerestriction"] = canonical::text(canonical::character((*message_2).short_sale_restriction()), ' ', false);
            } else if (const auto* message_2 = dynamic_cast<const protocol::SymbolClearMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.symbolclearmessage";
                values[entry + ".payload.applicationmessage.data.symbolclearmessage.nanoseconds"] = canonical::number((*message_2).nanoseconds());
                values[entry + ".payload.applicationmessage.data.symbolclearmessage.symbolid"] = canonical::number((*message_2).symbol_id());
            } else if (const auto* message_2 = dynamic_cast<const protocol::AddOrderMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.addordermessage";
                values[entry + ".payload.applicationmessage.data.addordermessage.nanoseconds"] = canonical::number((*message_2).nanoseconds());
                values[entry + ".payload.applicationmessage.data.addordermessage.symbolid"] = canonical::number((*message_2).symbol_id());
                values[entry + ".payload.applicationmessage.data.addordermessage.orderid"] = canonical::number((*message_2).order_id());
                values[entry + ".payload.applicationmessage.data.addordermessage.orderside"] = canonical::text(canonical::character((*message_2).order_side()), ' ', false);
                values[entry + ".payload.applicationmessage.data.addordermessage.price"] = canonical::scaled((*message_2).price().mantissa(), (*message_2).price().exponent());
                values[entry + ".payload.applicationmessage.data.addordermessage.size"] = canonical::number((*message_2).size());
                values[entry + ".payload.applicationmessage.data.addordermessage.attributableid"] = canonical::text(std::string((*message_2).attributable_id()), ' ', false);
            } else if (const auto* message_2 = dynamic_cast<const protocol::ModifyOrderMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.modifyordermessage";
                values[entry + ".payload.applicationmessage.data.modifyordermessage.nanoseconds"] = canonical::number((*message_2).nanoseconds());
                values[entry + ".payload.applicationmessage.data.modifyordermessage.symbolid"] = canonical::number((*message_2).symbol_id());
                values[entry + ".payload.applicationmessage.data.modifyordermessage.orderid"] = canonical::number((*message_2).order_id());
                values[entry + ".payload.applicationmessage.data.modifyordermessage.price"] = canonical::scaled((*message_2).price().mantissa(), (*message_2).price().exponent());
                values[entry + ".payload.applicationmessage.data.modifyordermessage.size"] = canonical::number((*message_2).size());
                values[entry + ".payload.applicationmessage.data.modifyordermessage.modifyorderflags.orderposition"] = canonical::number(static_cast<std::uint64_t>((*message_2).modify_order_flags().order_position()));
            } else if (const auto* message_2 = dynamic_cast<const protocol::DeleteOrderMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.deleteordermessage";
                values[entry + ".payload.applicationmessage.data.deleteordermessage.nanoseconds"] = canonical::number((*message_2).nanoseconds());
                values[entry + ".payload.applicationmessage.data.deleteordermessage.symbolid"] = canonical::number((*message_2).symbol_id());
                values[entry + ".payload.applicationmessage.data.deleteordermessage.orderid"] = canonical::number((*message_2).order_id());
            } else if (const auto* message_2 = dynamic_cast<const protocol::OrderExecutionMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.orderexecutionmessage";
                values[entry + ".payload.applicationmessage.data.orderexecutionmessage.nanoseconds"] = canonical::number((*message_2).nanoseconds());
                values[entry + ".payload.applicationmessage.data.orderexecutionmessage.symbolid"] = canonical::number((*message_2).symbol_id());
                values[entry + ".payload.applicationmessage.data.orderexecutionmessage.orderid"] = canonical::number((*message_2).order_id());
                values[entry + ".payload.applicationmessage.data.orderexecutionmessage.tradeid"] = canonical::number((*message_2).trade_id());
                values[entry + ".payload.applicationmessage.data.orderexecutionmessage.price"] = canonical::scaled((*message_2).price().mantissa(), (*message_2).price().exponent());
                values[entry + ".payload.applicationmessage.data.orderexecutionmessage.size"] = canonical::number((*message_2).size());
                values[entry + ".payload.applicationmessage.data.orderexecutionmessage.orderexecutionflags.sipreporting"] = canonical::number(static_cast<std::uint64_t>((*message_2).order_execution_flags().sip_reporting()));
                values[entry + ".payload.applicationmessage.data.orderexecutionmessage.orderexecutionflags.tradedagainstretail"] = canonical::number(static_cast<std::uint64_t>((*message_2).order_execution_flags().traded_against_retail()));
            } else if (const auto* message_2 = dynamic_cast<const protocol::TradeMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.trademessage";
                values[entry + ".payload.applicationmessage.data.trademessage.nanoseconds"] = canonical::number((*message_2).nanoseconds());
                values[entry + ".payload.applicationmessage.data.trademessage.symbolid"] = canonical::number((*message_2).symbol_id());
                values[entry + ".payload.applicationmessage.data.trademessage.tradeid"] = canonical::number((*message_2).trade_id());
                values[entry + ".payload.applicationmessage.data.trademessage.correctionnumber"] = canonical::number((*message_2).correction_number());
                values[entry + ".payload.applicationmessage.data.trademessage.price"] = canonical::scaled((*message_2).price().mantissa(), (*message_2).price().exponent());
                values[entry + ".payload.applicationmessage.data.trademessage.size"] = canonical::number((*message_2).size());
                values[entry + ".payload.applicationmessage.data.trademessage.tradeflags.sipreporting"] = canonical::number(static_cast<std::uint64_t>((*message_2).trade_flags().sip_reporting()));
                values[entry + ".payload.applicationmessage.data.trademessage.tradeflags.retailtradeindicator"] = canonical::number(static_cast<std::uint64_t>((*message_2).trade_flags().retail_trade_indicator()));
            } else if (const auto* message_2 = dynamic_cast<const protocol::TradeCancelMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "udppacket.machmessage.payload.applicationmessage.data.tradecancelmessage";
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.nanoseconds"] = canonical::number((*message_2).nanoseconds());
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.symbolid"] = canonical::number((*message_2).symbol_id());
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.tradeid"] = canonical::number((*message_2).trade_id());
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.correctionnumber"] = canonical::number((*message_2).correction_number());
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.price"] = canonical::scaled((*message_2).price().mantissa(), (*message_2).price().exponent());
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.size"] = canonical::number((*message_2).size());
            }
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
    std::printf("== Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d (classes values)\n");
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
