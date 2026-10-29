// Cboe.BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4 canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/definitions.hpp"

namespace protocol = ::cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    values["packet.packetheader.length"] = canonical::number(iterator.packet_header->length.get());
    values["packet.packetheader.messagecount"] = canonical::number(iterator.packet_header->message_count.get());
    values["packet.packetheader.unit"] = canonical::number(iterator.packet_header->unit.get());
    values["packet.packetheader.sequence"] = canonical::number(iterator.packet_header->sequence.get());

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(iterator.message_header->message_length.get());
        values[entry + ".messageheader.messagetype"] = canonical::number(iterator.message_header->message_type.get());

        if (iterator.message_type == protocol::TimeMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.timemessage";
            [[maybe_unused]] const auto* message = protocol::TimeMessage::parse(iterator.message);
            values[entry + ".payload.timemessage.time"] = canonical::number(message->time.get());
        } else if (iterator.message_type == protocol::UnitClearMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.unitclearmessage";
            [[maybe_unused]] const auto* message = protocol::UnitClearMessage::parse(iterator.message);
            values[entry + ".payload.unitclearmessage.timeoffset"] = canonical::number(message->time_offset.get());
        } else if (iterator.message_type == protocol::AddOrderLongMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.addorderlongmessage";
            [[maybe_unused]] const auto* message = protocol::AddOrderLongMessage::parse(iterator.message);
            values[entry + ".payload.addorderlongmessage.timeoffset"] = canonical::number(message->time_offset.get());
            values[entry + ".payload.addorderlongmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.addorderlongmessage.sideindicator"] = canonical::text(canonical::character(message->side_indicator.get()), ' ', false);
            values[entry + ".payload.addorderlongmessage.quantitybinary4"] = canonical::number(message->quantity_binary_4.get());
            values[entry + ".payload.addorderlongmessage.symbolshort"] = canonical::text(std::string(message->symbol_short.get()), ' ', false);
            values[entry + ".payload.addorderlongmessage.pricebinarylongprice8"] = canonical::scaled(message->price_binary_long_price_8.integer(), -4);
            values[entry + ".payload.addorderlongmessage.addflags.display"] = canonical::number(static_cast<std::uint64_t>(message->add_flags.Display()));
        } else if (iterator.message_type == protocol::AddOrderShortMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.addordershortmessage";
            [[maybe_unused]] const auto* message = protocol::AddOrderShortMessage::parse(iterator.message);
            values[entry + ".payload.addordershortmessage.timeoffset"] = canonical::number(message->time_offset.get());
            values[entry + ".payload.addordershortmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.addordershortmessage.sideindicator"] = canonical::text(canonical::character(message->side_indicator.get()), ' ', false);
            values[entry + ".payload.addordershortmessage.quantitybinary2"] = canonical::number(message->quantity_binary_2.get());
            values[entry + ".payload.addordershortmessage.symbolshort"] = canonical::text(std::string(message->symbol_short.get()), ' ', false);
            values[entry + ".payload.addordershortmessage.pricebinaryshortprice2"] = canonical::scaled(message->price_binary_short_price_2.integer(), -2);
            values[entry + ".payload.addordershortmessage.addflags.display"] = canonical::number(static_cast<std::uint64_t>(message->add_flags.Display()));
        } else if (iterator.message_type == protocol::AddOrderExpandedMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.addorderexpandedmessage";
            [[maybe_unused]] const auto* message = protocol::AddOrderExpandedMessage::parse(iterator.message);
            values[entry + ".payload.addorderexpandedmessage.timeoffset"] = canonical::number(message->time_offset.get());
            values[entry + ".payload.addorderexpandedmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.addorderexpandedmessage.sideindicator"] = canonical::text(canonical::character(message->side_indicator.get()), ' ', false);
            values[entry + ".payload.addorderexpandedmessage.quantitybinary4"] = canonical::number(message->quantity_binary_4.get());
            values[entry + ".payload.addorderexpandedmessage.symbollong"] = canonical::text(std::string(message->symbol_long.get()), ' ', false);
            values[entry + ".payload.addorderexpandedmessage.pricebinarylongprice8"] = canonical::scaled(message->price_binary_long_price_8.integer(), -4);
            values[entry + ".payload.addorderexpandedmessage.addflags.display"] = canonical::number(static_cast<std::uint64_t>(message->add_flags.Display()));
            values[entry + ".payload.addorderexpandedmessage.participantid"] = canonical::text(std::string(message->participant_id.get()), ' ', false);
        } else if (iterator.message_type == protocol::OrderExecutedMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedmessage";
            [[maybe_unused]] const auto* message = protocol::OrderExecutedMessage::parse(iterator.message);
            values[entry + ".payload.orderexecutedmessage.timeoffset"] = canonical::number(message->time_offset.get());
            values[entry + ".payload.orderexecutedmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.orderexecutedmessage.executedquantity"] = canonical::number(message->executed_quantity.get());
            values[entry + ".payload.orderexecutedmessage.executionid"] = canonical::number(message->execution_id.get());
        } else if (iterator.message_type == protocol::OrderExecutedAtPriceSizeMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedatpricesizemessage";
            [[maybe_unused]] const auto* message = protocol::OrderExecutedAtPriceSizeMessage::parse(iterator.message);
            values[entry + ".payload.orderexecutedatpricesizemessage.timeoffset"] = canonical::number(message->time_offset.get());
            values[entry + ".payload.orderexecutedatpricesizemessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.orderexecutedatpricesizemessage.executedquantity"] = canonical::number(message->executed_quantity.get());
            values[entry + ".payload.orderexecutedatpricesizemessage.remainingquantity"] = canonical::number(message->remaining_quantity.get());
            values[entry + ".payload.orderexecutedatpricesizemessage.executionid"] = canonical::number(message->execution_id.get());
            values[entry + ".payload.orderexecutedatpricesizemessage.pricebinarylongprice8"] = canonical::scaled(message->price_binary_long_price_8.integer(), -4);
        } else if (iterator.message_type == protocol::ReduceSizeLongMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.reducesizelongmessage";
            [[maybe_unused]] const auto* message = protocol::ReduceSizeLongMessage::parse(iterator.message);
            values[entry + ".payload.reducesizelongmessage.timeoffset"] = canonical::number(message->time_offset.get());
            values[entry + ".payload.reducesizelongmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.reducesizelongmessage.canceledquantitybinary4"] = canonical::number(message->canceled_quantity_binary_4.get());
        } else if (iterator.message_type == protocol::ReduceSizeShortMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.reducesizeshortmessage";
            [[maybe_unused]] const auto* message = protocol::ReduceSizeShortMessage::parse(iterator.message);
            values[entry + ".payload.reducesizeshortmessage.timeoffset"] = canonical::number(message->time_offset.get());
            values[entry + ".payload.reducesizeshortmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.reducesizeshortmessage.canceledquantitybinary2"] = canonical::number(message->canceled_quantity_binary_2.get());
        } else if (iterator.message_type == protocol::ModifyOrderLongMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.modifyorderlongmessage";
            [[maybe_unused]] const auto* message = protocol::ModifyOrderLongMessage::parse(iterator.message);
            values[entry + ".payload.modifyorderlongmessage.timeoffset"] = canonical::number(message->time_offset.get());
            values[entry + ".payload.modifyorderlongmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.modifyorderlongmessage.quantitybinary4"] = canonical::number(message->quantity_binary_4.get());
            values[entry + ".payload.modifyorderlongmessage.pricebinarylongprice8"] = canonical::scaled(message->price_binary_long_price_8.integer(), -4);
            values[entry + ".payload.modifyorderlongmessage.modifyflags.display"] = canonical::number(static_cast<std::uint64_t>(message->modify_flags.Display()));
            values[entry + ".payload.modifyorderlongmessage.modifyflags.maintainpriority"] = canonical::number(static_cast<std::uint64_t>(message->modify_flags.MaintainPriority()));
        } else if (iterator.message_type == protocol::ModifyOrderShortMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.modifyordershortmessage";
            [[maybe_unused]] const auto* message = protocol::ModifyOrderShortMessage::parse(iterator.message);
            values[entry + ".payload.modifyordershortmessage.timeoffset"] = canonical::number(message->time_offset.get());
            values[entry + ".payload.modifyordershortmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.modifyordershortmessage.quantitybinary2"] = canonical::number(message->quantity_binary_2.get());
            values[entry + ".payload.modifyordershortmessage.pricebinaryshortprice2"] = canonical::scaled(message->price_binary_short_price_2.integer(), -2);
            values[entry + ".payload.modifyordershortmessage.modifyflags.display"] = canonical::number(static_cast<std::uint64_t>(message->modify_flags.Display()));
            values[entry + ".payload.modifyordershortmessage.modifyflags.maintainpriority"] = canonical::number(static_cast<std::uint64_t>(message->modify_flags.MaintainPriority()));
        } else if (iterator.message_type == protocol::DeleteOrderMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.deleteordermessage";
            [[maybe_unused]] const auto* message = protocol::DeleteOrderMessage::parse(iterator.message);
            values[entry + ".payload.deleteordermessage.timeoffset"] = canonical::number(message->time_offset.get());
            values[entry + ".payload.deleteordermessage.orderid"] = canonical::number(message->order_id.get());
        } else if (iterator.message_type == protocol::TradeLongMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradelongmessage";
            [[maybe_unused]] const auto* message = protocol::TradeLongMessage::parse(iterator.message);
            values[entry + ".payload.tradelongmessage.timeoffset"] = canonical::number(message->time_offset.get());
            values[entry + ".payload.tradelongmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.tradelongmessage.sideindicator"] = canonical::text(canonical::character(message->side_indicator.get()), ' ', false);
            values[entry + ".payload.tradelongmessage.quantitybinary4"] = canonical::number(message->quantity_binary_4.get());
            values[entry + ".payload.tradelongmessage.symbolshort"] = canonical::text(std::string(message->symbol_short.get()), ' ', false);
            values[entry + ".payload.tradelongmessage.pricebinarylongprice8"] = canonical::scaled(message->price_binary_long_price_8.integer(), -4);
            values[entry + ".payload.tradelongmessage.executionid"] = canonical::number(message->execution_id.get());
        } else if (iterator.message_type == protocol::TradeShortMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradeshortmessage";
            [[maybe_unused]] const auto* message = protocol::TradeShortMessage::parse(iterator.message);
            values[entry + ".payload.tradeshortmessage.timeoffset"] = canonical::number(message->time_offset.get());
            values[entry + ".payload.tradeshortmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.tradeshortmessage.sideindicator"] = canonical::text(canonical::character(message->side_indicator.get()), ' ', false);
            values[entry + ".payload.tradeshortmessage.quantitybinary2"] = canonical::number(message->quantity_binary_2.get());
            values[entry + ".payload.tradeshortmessage.symbolshort"] = canonical::text(std::string(message->symbol_short.get()), ' ', false);
            values[entry + ".payload.tradeshortmessage.pricebinaryshortprice2"] = canonical::scaled(message->price_binary_short_price_2.integer(), -2);
            values[entry + ".payload.tradeshortmessage.executionid"] = canonical::number(message->execution_id.get());
        } else if (iterator.message_type == protocol::TradeExpandedMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradeexpandedmessage";
            [[maybe_unused]] const auto* message = protocol::TradeExpandedMessage::parse(iterator.message);
            values[entry + ".payload.tradeexpandedmessage.timeoffset"] = canonical::number(message->time_offset.get());
            values[entry + ".payload.tradeexpandedmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.tradeexpandedmessage.sideindicator"] = canonical::text(canonical::character(message->side_indicator.get()), ' ', false);
            values[entry + ".payload.tradeexpandedmessage.quantitybinary4"] = canonical::number(message->quantity_binary_4.get());
            values[entry + ".payload.tradeexpandedmessage.symbollong"] = canonical::text(std::string(message->symbol_long.get()), ' ', false);
            values[entry + ".payload.tradeexpandedmessage.pricebinarylongprice8"] = canonical::scaled(message->price_binary_long_price_8.integer(), -4);
            values[entry + ".payload.tradeexpandedmessage.executionid"] = canonical::number(message->execution_id.get());
        } else if (iterator.message_type == protocol::TradeBreakMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradebreakmessage";
            [[maybe_unused]] const auto* message = protocol::TradeBreakMessage::parse(iterator.message);
            values[entry + ".payload.tradebreakmessage.timeoffset"] = canonical::number(message->time_offset.get());
            values[entry + ".payload.tradebreakmessage.executionid"] = canonical::number(message->execution_id.get());
        } else if (iterator.message_type == protocol::EndOfSessionMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.endofsessionmessage";
            [[maybe_unused]] const auto* message = protocol::EndOfSessionMessage::parse(iterator.message);
            values[entry + ".payload.endofsessionmessage.timestamp"] = canonical::number(message->timestamp.get());
        } else if (iterator.message_type == protocol::SymbolMappingMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.symbolmappingmessage";
            [[maybe_unused]] const auto* message = protocol::SymbolMappingMessage::parse(iterator.message);
            values[entry + ".payload.symbolmappingmessage.feedsymbol"] = canonical::text(std::string(message->feed_symbol.get()), ' ', false);
            values[entry + ".payload.symbolmappingmessage.osisymbol"] = canonical::text(std::string(message->osi_symbol.get()), ' ', false);
            values[entry + ".payload.symbolmappingmessage.symbolcondition"] = canonical::text(canonical::character(message->symbol_condition.get()), ' ', false);
        } else if (iterator.message_type == protocol::TradingStatusMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradingstatusmessage";
            [[maybe_unused]] const auto* message = protocol::TradingStatusMessage::parse(iterator.message);
            values[entry + ".payload.tradingstatusmessage.timeoffset"] = canonical::number(message->time_offset.get());
            values[entry + ".payload.tradingstatusmessage.symbollong"] = canonical::text(std::string(message->symbol_long.get()), ' ', false);
            values[entry + ".payload.tradingstatusmessage.tradingstatus"] = canonical::text(canonical::character(message->trading_status.get()), ' ', false);
            values[entry + ".payload.tradingstatusmessage.regshoaction"] = canonical::text(canonical::character(message->reg_sho_action.get()), ' ', false);
            values[entry + ".payload.tradingstatusmessage.reserved1"] = canonical::text(canonical::character(message->reserved_1.get()), ' ', false);
            values[entry + ".payload.tradingstatusmessage.secondreserved1"] = canonical::text(canonical::character(message->second_reserved_1.get()), ' ', false);
        } else if (iterator.message_type == protocol::AuctionUpdateMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.auctionupdatemessage";
            [[maybe_unused]] const auto* message = protocol::AuctionUpdateMessage::parse(iterator.message);
            values[entry + ".payload.auctionupdatemessage.timeoffset"] = canonical::number(message->time_offset.get());
            values[entry + ".payload.auctionupdatemessage.stocksymbol"] = canonical::text(std::string(message->stock_symbol.get()), ' ', false);
            values[entry + ".payload.auctionupdatemessage.auctiontype"] = canonical::text(canonical::character(message->auction_type.get()), ' ', false);
            values[entry + ".payload.auctionupdatemessage.referenceprice"] = canonical::number(message->reference_price.get());
            values[entry + ".payload.auctionupdatemessage.buyshares"] = canonical::number(message->buy_shares.get());
            values[entry + ".payload.auctionupdatemessage.sellshares"] = canonical::number(message->sell_shares.get());
            values[entry + ".payload.auctionupdatemessage.indicativeprice"] = canonical::number(message->indicative_price.get());
            values[entry + ".payload.auctionupdatemessage.auctiononlyprice"] = canonical::number(message->auction_only_price.get());
        } else if (iterator.message_type == protocol::AuctionSummaryMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.auctionsummarymessage";
            [[maybe_unused]] const auto* message = protocol::AuctionSummaryMessage::parse(iterator.message);
            values[entry + ".payload.auctionsummarymessage.timeoffset"] = canonical::number(message->time_offset.get());
            values[entry + ".payload.auctionsummarymessage.stocksymbol"] = canonical::text(std::string(message->stock_symbol.get()), ' ', false);
            values[entry + ".payload.auctionsummarymessage.auctiontype"] = canonical::text(canonical::character(message->auction_type.get()), ' ', false);
            values[entry + ".payload.auctionsummarymessage.pricebinary8"] = canonical::number(message->price_binary_8.get());
            values[entry + ".payload.auctionsummarymessage.shares"] = canonical::number(message->shares.get());
        } else if (iterator.message_type == protocol::RetailPriceImprovementMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.retailpriceimprovementmessage";
            [[maybe_unused]] const auto* message = protocol::RetailPriceImprovementMessage::parse(iterator.message);
            values[entry + ".payload.retailpriceimprovementmessage.timeoffset"] = canonical::number(message->time_offset.get());
            values[entry + ".payload.retailpriceimprovementmessage.symbollong"] = canonical::text(std::string(message->symbol_long.get()), ' ', false);
            values[entry + ".payload.retailpriceimprovementmessage.retailpriceimprovement"] = canonical::text(canonical::character(message->retail_price_improvement.get()), ' ', false);
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
    std::printf("== Cboe.BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4 (modern values)\n");
    int failures = 0;
    failures += check("AddOrderLongMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4/AddOrderLongMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/AddOrderLongMessage.values");
    failures += check("AddOrderShortMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4/AddOrderShortMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/AddOrderShortMessage.values");
    failures += check("DeleteOrderMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4/DeleteOrderMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/DeleteOrderMessage.values");
    failures += check("ModifyOrderLongMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4/ModifyOrderLongMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/ModifyOrderLongMessage.values");
    failures += check("ModifyOrderShortMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4/ModifyOrderShortMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/ModifyOrderShortMessage.values");
    failures += check("OrderExecutedMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4/OrderExecutedMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/OrderExecutedMessage.values");
    failures += check("ReduceSizeShortMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4/ReduceSizeShortMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/ReduceSizeShortMessage.values");
    failures += check("TimeMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4/TimeMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/TimeMessage.values");
    failures += check("TradeLongMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4/TradeLongMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/TradeLongMessage.values");
    failures += check("TradeShortMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4/TradeShortMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/TradeShortMessage.values");
    return failures == 0 ? 0 : 1;
}
