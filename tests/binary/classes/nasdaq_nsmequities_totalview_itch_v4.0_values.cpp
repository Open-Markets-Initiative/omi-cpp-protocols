// Nasdaq.NsmEquities.TotalView.Itch.v4.0 canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/binary/classes/nasdaq/nsmequities/totalview/itch/v4.0/definitions.hpp"

namespace protocol = ::nasdaq::nsmequities::totalview::itch::v4_0;

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

    values["packet.packetheader.session"] = canonical::text(std::string(packet.packet_header().session()), '\0', false);
    values["packet.packetheader.sequencenumber"] = canonical::number(packet.packet_header().sequence_number());
    values["packet.packetheader.messagecount"] = canonical::number(packet.packet_header().message_count());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(each.message_header().message_length());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(each.message_header().message_type()));

        if (const auto* message = dynamic_cast<const protocol::PayloadTimestampMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.timestampmessage";
            values[entry + ".payload.timestampmessage.second"] = canonical::number((*message).second());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadSystemEventMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.systemeventmessage";
            values[entry + ".payload.systemeventmessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.systemeventmessage.eventcode"] = canonical::text(canonical::character((*message).event_code()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::PayloadStockDirectoryMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.stockdirectorymessage";
            values[entry + ".payload.stockdirectorymessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.stockdirectorymessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.marketcategory"] = canonical::text(canonical::character((*message).market_category()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.financialstatusindicator"] = canonical::text(canonical::character((*message).financial_status_indicator()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.roundlotsize"] = canonical::number((*message).round_lot_size());
            values[entry + ".payload.stockdirectorymessage.roundlotsonly"] = canonical::text(canonical::character((*message).round_lots_only()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::PayloadStockTradingActionMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.stocktradingactionmessage";
            values[entry + ".payload.stocktradingactionmessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.stocktradingactionmessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.tradingstate"] = canonical::text(canonical::character((*message).trading_state()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.reserved"] = canonical::text(canonical::character((*message).reserved()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.reason"] = canonical::text(std::string((*message).reason()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::PayloadMarketParticipantPositionMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.marketparticipantpositionmessage";
            values[entry + ".payload.marketparticipantpositionmessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.marketparticipantpositionmessage.mpid"] = canonical::text(std::string((*message).mpid()), ' ', false);
            values[entry + ".payload.marketparticipantpositionmessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.marketparticipantpositionmessage.primarymarketmaker"] = canonical::text(canonical::character((*message).primary_market_maker()), ' ', false);
            values[entry + ".payload.marketparticipantpositionmessage.marketmakermode"] = canonical::text(canonical::character((*message).market_maker_mode()), ' ', false);
            values[entry + ".payload.marketparticipantpositionmessage.marketparticipantstate"] = canonical::text(canonical::character((*message).market_participant_state()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::PayloadAddOrderMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.addordermessage";
            values[entry + ".payload.addordermessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.addordermessage.orderreferencenumber"] = canonical::number((*message).order_reference_number());
            values[entry + ".payload.addordermessage.side"] = canonical::text(canonical::character((*message).side()), ' ', false);
            values[entry + ".payload.addordermessage.shares"] = canonical::number((*message).shares());
            values[entry + ".payload.addordermessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.addordermessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadAddOrderWithMpidMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.addorderwithmpidmessage";
            values[entry + ".payload.addorderwithmpidmessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.addorderwithmpidmessage.orderreferencenumber"] = canonical::number((*message).order_reference_number());
            values[entry + ".payload.addorderwithmpidmessage.side"] = canonical::text(canonical::character((*message).side()), ' ', false);
            values[entry + ".payload.addorderwithmpidmessage.shares"] = canonical::number((*message).shares());
            values[entry + ".payload.addorderwithmpidmessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.addorderwithmpidmessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
            values[entry + ".payload.addorderwithmpidmessage.attribution"] = canonical::text(std::string((*message).attribution()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::PayloadOrderExecutedMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedmessage";
            values[entry + ".payload.orderexecutedmessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.orderexecutedmessage.orderreferencenumber"] = canonical::number((*message).order_reference_number());
            values[entry + ".payload.orderexecutedmessage.executedshares"] = canonical::number((*message).executed_shares());
            values[entry + ".payload.orderexecutedmessage.matchnumber"] = canonical::number((*message).match_number());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadOrderExecutedWithPriceMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedwithpricemessage";
            values[entry + ".payload.orderexecutedwithpricemessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.orderexecutedwithpricemessage.orderreferencenumber"] = canonical::number((*message).order_reference_number());
            values[entry + ".payload.orderexecutedwithpricemessage.executedshares"] = canonical::number((*message).executed_shares());
            values[entry + ".payload.orderexecutedwithpricemessage.matchnumber"] = canonical::number((*message).match_number());
            values[entry + ".payload.orderexecutedwithpricemessage.printable"] = canonical::text(canonical::character((*message).printable()), ' ', false);
            values[entry + ".payload.orderexecutedwithpricemessage.executionprice"] = canonical::scaled((*message).execution_price().mantissa(), (*message).execution_price().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadOrderCancelMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.ordercancelmessage";
            values[entry + ".payload.ordercancelmessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.ordercancelmessage.orderreferencenumber"] = canonical::number((*message).order_reference_number());
            values[entry + ".payload.ordercancelmessage.canceledshares"] = canonical::number((*message).canceled_shares());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadOrderDeleteMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderdeletemessage";
            values[entry + ".payload.orderdeletemessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.orderdeletemessage.orderreferencenumber"] = canonical::number((*message).order_reference_number());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadOrderReplaceMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderreplacemessage";
            values[entry + ".payload.orderreplacemessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.orderreplacemessage.originalorderreferencenumber"] = canonical::number((*message).original_order_reference_number());
            values[entry + ".payload.orderreplacemessage.neworderreferencenumber"] = canonical::number((*message).new_order_reference_number());
            values[entry + ".payload.orderreplacemessage.shares"] = canonical::number((*message).shares());
            values[entry + ".payload.orderreplacemessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadTradeMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.trademessage";
            values[entry + ".payload.trademessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.trademessage.orderreferencenumber"] = canonical::number((*message).order_reference_number());
            values[entry + ".payload.trademessage.side"] = canonical::text(canonical::character((*message).side()), ' ', false);
            values[entry + ".payload.trademessage.shares"] = canonical::number((*message).shares());
            values[entry + ".payload.trademessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.trademessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
            values[entry + ".payload.trademessage.matchnumber"] = canonical::number((*message).match_number());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadCrossTradeMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.crosstrademessage";
            values[entry + ".payload.crosstrademessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.crosstrademessage.crossshares"] = canonical::number((*message).cross_shares());
            values[entry + ".payload.crosstrademessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.crosstrademessage.crossprice"] = canonical::scaled((*message).cross_price().mantissa(), (*message).cross_price().exponent());
            values[entry + ".payload.crosstrademessage.matchnumber"] = canonical::number((*message).match_number());
            values[entry + ".payload.crosstrademessage.crosstype"] = canonical::text(canonical::character((*message).cross_type()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::PayloadBrokenTradeMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.brokentrademessage";
            values[entry + ".payload.brokentrademessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.brokentrademessage.matchnumber"] = canonical::number((*message).match_number());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadNetOrderImbalanceIndicatorMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.netorderimbalanceindicatormessage";
            values[entry + ".payload.netorderimbalanceindicatormessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.netorderimbalanceindicatormessage.pairedshares"] = canonical::number((*message).paired_shares());
            values[entry + ".payload.netorderimbalanceindicatormessage.imbalanceshares"] = canonical::number((*message).imbalance_shares());
            values[entry + ".payload.netorderimbalanceindicatormessage.imbalancedirection"] = canonical::text(canonical::character((*message).imbalance_direction()), ' ', false);
            values[entry + ".payload.netorderimbalanceindicatormessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.netorderimbalanceindicatormessage.farprice"] = canonical::scaled((*message).far_price().mantissa(), (*message).far_price().exponent());
            values[entry + ".payload.netorderimbalanceindicatormessage.nearprice"] = canonical::scaled((*message).near_price().mantissa(), (*message).near_price().exponent());
            values[entry + ".payload.netorderimbalanceindicatormessage.currentreferenceprice"] = canonical::scaled((*message).current_reference_price().mantissa(), (*message).current_reference_price().exponent());
            values[entry + ".payload.netorderimbalanceindicatormessage.crosstype"] = canonical::text(canonical::character((*message).cross_type()), ' ', false);
            values[entry + ".payload.netorderimbalanceindicatormessage.pricevariationindicator"] = canonical::text(canonical::character((*message).price_variation_indicator()), ' ', false);
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
    std::printf("== Nasdaq.NsmEquities.TotalView.Itch.v4.0 (classes values)\n");
    int failures = 0;
    failures += check("AddOrderMessage", "Nasdaq/NsmEquities.TotalView.Itch.v4.0/AddOrderMessage.pcap", "nasdaq/nsmequities/totalview/itch/v4.0/AddOrderMessage.values");
    failures += check("AddOrderWithMpidMessage", "Nasdaq/NsmEquities.TotalView.Itch.v4.0/AddOrderWithMpidMessage.pcap", "nasdaq/nsmequities/totalview/itch/v4.0/AddOrderWithMpidMessage.values");
    failures += check("BrokenTradeMessage", "Nasdaq/NsmEquities.TotalView.Itch.v4.0/BrokenTradeMessage.pcap", "nasdaq/nsmequities/totalview/itch/v4.0/BrokenTradeMessage.values");
    failures += check("CrossTradeMessage", "Nasdaq/NsmEquities.TotalView.Itch.v4.0/CrossTradeMessage.pcap", "nasdaq/nsmequities/totalview/itch/v4.0/CrossTradeMessage.values");
    failures += check("MarketParticipantPositionMessage", "Nasdaq/NsmEquities.TotalView.Itch.v4.0/MarketParticipantPositionMessage.pcap", "nasdaq/nsmequities/totalview/itch/v4.0/MarketParticipantPositionMessage.values");
    failures += check("NetOrderImbalanceIndicatorMessage", "Nasdaq/NsmEquities.TotalView.Itch.v4.0/NetOrderImbalanceIndicatorMessage.pcap", "nasdaq/nsmequities/totalview/itch/v4.0/NetOrderImbalanceIndicatorMessage.values");
    failures += check("OrderCancelMessage", "Nasdaq/NsmEquities.TotalView.Itch.v4.0/OrderCancelMessage.pcap", "nasdaq/nsmequities/totalview/itch/v4.0/OrderCancelMessage.values");
    failures += check("OrderDeleteMessage", "Nasdaq/NsmEquities.TotalView.Itch.v4.0/OrderDeleteMessage.pcap", "nasdaq/nsmequities/totalview/itch/v4.0/OrderDeleteMessage.values");
    failures += check("OrderExecutedMessage", "Nasdaq/NsmEquities.TotalView.Itch.v4.0/OrderExecutedMessage.pcap", "nasdaq/nsmequities/totalview/itch/v4.0/OrderExecutedMessage.values");
    failures += check("OrderExecutedWithPriceMessage", "Nasdaq/NsmEquities.TotalView.Itch.v4.0/OrderExecutedWithPriceMessage.pcap", "nasdaq/nsmequities/totalview/itch/v4.0/OrderExecutedWithPriceMessage.values");
    failures += check("StockDirectoryMessage", "Nasdaq/NsmEquities.TotalView.Itch.v4.0/StockDirectoryMessage.pcap", "nasdaq/nsmequities/totalview/itch/v4.0/StockDirectoryMessage.values");
    failures += check("StockTradingActionMessage", "Nasdaq/NsmEquities.TotalView.Itch.v4.0/StockTradingActionMessage.pcap", "nasdaq/nsmequities/totalview/itch/v4.0/StockTradingActionMessage.values");
    failures += check("SystemEventMessage", "Nasdaq/NsmEquities.TotalView.Itch.v4.0/SystemEventMessage.pcap", "nasdaq/nsmequities/totalview/itch/v4.0/SystemEventMessage.values");
    failures += check("TimestampMessage", "Nasdaq/NsmEquities.TotalView.Itch.v4.0/TimestampMessage.pcap", "nasdaq/nsmequities/totalview/itch/v4.0/TimestampMessage.values");
    failures += check("TradeMessage", "Nasdaq/NsmEquities.TotalView.Itch.v4.0/TradeMessage.pcap", "nasdaq/nsmequities/totalview/itch/v4.0/TradeMessage.values");
    return failures == 0 ? 0 : 1;
}
