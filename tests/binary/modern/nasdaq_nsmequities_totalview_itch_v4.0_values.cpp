// Nasdaq.NsmEquities.TotalView.Itch.v4.0 canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/nasdaq/nsmequities/totalview/itch/v4.0/definitions.hpp"

namespace protocol = ::nasdaq::nsmequities::totalview::itch::v4_0;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    values["packet.packetheader.session"] = canonical::text(std::string(iterator.packet_header->session.get()), '\0', false);
    values["packet.packetheader.sequencenumber"] = canonical::number(iterator.packet_header->sequence_number.get());
    values["packet.packetheader.messagecount"] = canonical::number(iterator.packet_header->message_count.get());

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(iterator.message_header->message_length.get());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(iterator.message_header->message_type.get()));

        if (iterator.message_type == protocol::TimestampMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.timestampmessage";
            [[maybe_unused]] const auto* message = protocol::TimestampMessage::parse(iterator.message);
            values[entry + ".payload.timestampmessage.second"] = canonical::number(message->second.get());
        } else if (iterator.message_type == protocol::SystemEventMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.systemeventmessage";
            [[maybe_unused]] const auto* message = protocol::SystemEventMessage::parse(iterator.message);
            values[entry + ".payload.systemeventmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.systemeventmessage.eventcode"] = canonical::text(canonical::character(message->event_code.get()), ' ', false);
        } else if (iterator.message_type == protocol::StockDirectoryMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.stockdirectorymessage";
            [[maybe_unused]] const auto* message = protocol::StockDirectoryMessage::parse(iterator.message);
            values[entry + ".payload.stockdirectorymessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.stockdirectorymessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.marketcategory"] = canonical::text(canonical::character(message->market_category.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.financialstatusindicator"] = canonical::text(canonical::character(message->financial_status_indicator.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.roundlotsize"] = canonical::number(message->round_lot_size.get());
            values[entry + ".payload.stockdirectorymessage.roundlotsonly"] = canonical::text(canonical::character(message->round_lots_only.get()), ' ', false);
        } else if (iterator.message_type == protocol::StockTradingActionMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.stocktradingactionmessage";
            [[maybe_unused]] const auto* message = protocol::StockTradingActionMessage::parse(iterator.message);
            values[entry + ".payload.stocktradingactionmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.stocktradingactionmessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.tradingstate"] = canonical::text(canonical::character(message->trading_state.get()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.reserved"] = canonical::text(canonical::character(message->reserved.get()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.reason"] = canonical::text(std::string(message->reason.get()), ' ', false);
        } else if (iterator.message_type == protocol::MarketParticipantPositionMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.marketparticipantpositionmessage";
            [[maybe_unused]] const auto* message = protocol::MarketParticipantPositionMessage::parse(iterator.message);
            values[entry + ".payload.marketparticipantpositionmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.marketparticipantpositionmessage.mpid"] = canonical::text(std::string(message->mpid.get()), ' ', false);
            values[entry + ".payload.marketparticipantpositionmessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.marketparticipantpositionmessage.primarymarketmaker"] = canonical::text(canonical::character(message->primary_market_maker.get()), ' ', false);
            values[entry + ".payload.marketparticipantpositionmessage.marketmakermode"] = canonical::text(canonical::character(message->market_maker_mode.get()), ' ', false);
            values[entry + ".payload.marketparticipantpositionmessage.marketparticipantstate"] = canonical::text(canonical::character(message->market_participant_state.get()), ' ', false);
        } else if (iterator.message_type == protocol::AddOrderMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.addordermessage";
            [[maybe_unused]] const auto* message = protocol::AddOrderMessage::parse(iterator.message);
            values[entry + ".payload.addordermessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.addordermessage.orderreferencenumber"] = canonical::number(message->order_reference_number.get());
            values[entry + ".payload.addordermessage.side"] = canonical::text(canonical::character(message->side.get()), ' ', false);
            values[entry + ".payload.addordermessage.shares"] = canonical::number(message->shares.get());
            values[entry + ".payload.addordermessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.addordermessage.price"] = canonical::scaled(message->price.integer(), -4);
        } else if (iterator.message_type == protocol::AddOrderWithMpidMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.addorderwithmpidmessage";
            [[maybe_unused]] const auto* message = protocol::AddOrderWithMpidMessage::parse(iterator.message);
            values[entry + ".payload.addorderwithmpidmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.addorderwithmpidmessage.orderreferencenumber"] = canonical::number(message->order_reference_number.get());
            values[entry + ".payload.addorderwithmpidmessage.side"] = canonical::text(canonical::character(message->side.get()), ' ', false);
            values[entry + ".payload.addorderwithmpidmessage.shares"] = canonical::number(message->shares.get());
            values[entry + ".payload.addorderwithmpidmessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.addorderwithmpidmessage.price"] = canonical::scaled(message->price.integer(), -4);
            values[entry + ".payload.addorderwithmpidmessage.attribution"] = canonical::text(std::string(message->attribution.get()), ' ', false);
        } else if (iterator.message_type == protocol::OrderExecutedMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedmessage";
            [[maybe_unused]] const auto* message = protocol::OrderExecutedMessage::parse(iterator.message);
            values[entry + ".payload.orderexecutedmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.orderexecutedmessage.orderreferencenumber"] = canonical::number(message->order_reference_number.get());
            values[entry + ".payload.orderexecutedmessage.executedshares"] = canonical::number(message->executed_shares.get());
            values[entry + ".payload.orderexecutedmessage.matchnumber"] = canonical::number(message->match_number.get());
        } else if (iterator.message_type == protocol::OrderExecutedWithPriceMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedwithpricemessage";
            [[maybe_unused]] const auto* message = protocol::OrderExecutedWithPriceMessage::parse(iterator.message);
            values[entry + ".payload.orderexecutedwithpricemessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.orderexecutedwithpricemessage.orderreferencenumber"] = canonical::number(message->order_reference_number.get());
            values[entry + ".payload.orderexecutedwithpricemessage.executedshares"] = canonical::number(message->executed_shares.get());
            values[entry + ".payload.orderexecutedwithpricemessage.matchnumber"] = canonical::number(message->match_number.get());
            values[entry + ".payload.orderexecutedwithpricemessage.printable"] = canonical::text(canonical::character(message->printable.get()), ' ', false);
            values[entry + ".payload.orderexecutedwithpricemessage.executionprice"] = canonical::scaled(message->execution_price.integer(), -4);
        } else if (iterator.message_type == protocol::OrderCancelMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.ordercancelmessage";
            [[maybe_unused]] const auto* message = protocol::OrderCancelMessage::parse(iterator.message);
            values[entry + ".payload.ordercancelmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.ordercancelmessage.orderreferencenumber"] = canonical::number(message->order_reference_number.get());
            values[entry + ".payload.ordercancelmessage.canceledshares"] = canonical::number(message->canceled_shares.get());
        } else if (iterator.message_type == protocol::OrderDeleteMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderdeletemessage";
            [[maybe_unused]] const auto* message = protocol::OrderDeleteMessage::parse(iterator.message);
            values[entry + ".payload.orderdeletemessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.orderdeletemessage.orderreferencenumber"] = canonical::number(message->order_reference_number.get());
        } else if (iterator.message_type == protocol::OrderReplaceMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderreplacemessage";
            [[maybe_unused]] const auto* message = protocol::OrderReplaceMessage::parse(iterator.message);
            values[entry + ".payload.orderreplacemessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.orderreplacemessage.originalorderreferencenumber"] = canonical::number(message->original_order_reference_number.get());
            values[entry + ".payload.orderreplacemessage.neworderreferencenumber"] = canonical::number(message->new_order_reference_number.get());
            values[entry + ".payload.orderreplacemessage.shares"] = canonical::number(message->shares.get());
            values[entry + ".payload.orderreplacemessage.price"] = canonical::scaled(message->price.integer(), -4);
        } else if (iterator.message_type == protocol::TradeMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.trademessage";
            [[maybe_unused]] const auto* message = protocol::TradeMessage::parse(iterator.message);
            values[entry + ".payload.trademessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.trademessage.orderreferencenumber"] = canonical::number(message->order_reference_number.get());
            values[entry + ".payload.trademessage.side"] = canonical::text(canonical::character(message->side.get()), ' ', false);
            values[entry + ".payload.trademessage.shares"] = canonical::number(message->shares.get());
            values[entry + ".payload.trademessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.trademessage.price"] = canonical::scaled(message->price.integer(), -4);
            values[entry + ".payload.trademessage.matchnumber"] = canonical::number(message->match_number.get());
        } else if (iterator.message_type == protocol::CrossTradeMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.crosstrademessage";
            [[maybe_unused]] const auto* message = protocol::CrossTradeMessage::parse(iterator.message);
            values[entry + ".payload.crosstrademessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.crosstrademessage.crossshares"] = canonical::number(message->cross_shares.get());
            values[entry + ".payload.crosstrademessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.crosstrademessage.crossprice"] = canonical::scaled(message->cross_price.integer(), -4);
            values[entry + ".payload.crosstrademessage.matchnumber"] = canonical::number(message->match_number.get());
            values[entry + ".payload.crosstrademessage.crosstype"] = canonical::text(canonical::character(message->cross_type.get()), ' ', false);
        } else if (iterator.message_type == protocol::BrokenTradeMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.brokentrademessage";
            [[maybe_unused]] const auto* message = protocol::BrokenTradeMessage::parse(iterator.message);
            values[entry + ".payload.brokentrademessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.brokentrademessage.matchnumber"] = canonical::number(message->match_number.get());
        } else if (iterator.message_type == protocol::NetOrderImbalanceIndicatorMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.netorderimbalanceindicatormessage";
            [[maybe_unused]] const auto* message = protocol::NetOrderImbalanceIndicatorMessage::parse(iterator.message);
            values[entry + ".payload.netorderimbalanceindicatormessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.netorderimbalanceindicatormessage.pairedshares"] = canonical::number(message->paired_shares.get());
            values[entry + ".payload.netorderimbalanceindicatormessage.imbalanceshares"] = canonical::number(message->imbalance_shares.get());
            values[entry + ".payload.netorderimbalanceindicatormessage.imbalancedirection"] = canonical::text(canonical::character(message->imbalance_direction.get()), ' ', false);
            values[entry + ".payload.netorderimbalanceindicatormessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.netorderimbalanceindicatormessage.farprice"] = canonical::scaled(message->far_price.integer(), -4);
            values[entry + ".payload.netorderimbalanceindicatormessage.nearprice"] = canonical::scaled(message->near_price.integer(), -4);
            values[entry + ".payload.netorderimbalanceindicatormessage.currentreferenceprice"] = canonical::scaled(message->current_reference_price.integer(), -4);
            values[entry + ".payload.netorderimbalanceindicatormessage.crosstype"] = canonical::text(canonical::character(message->cross_type.get()), ' ', false);
            values[entry + ".payload.netorderimbalanceindicatormessage.pricevariationindicator"] = canonical::text(canonical::character(message->price_variation_indicator.get()), ' ', false);
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
    std::printf("== Nasdaq.NsmEquities.TotalView.Itch.v4.0 (modern values)\n");
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
