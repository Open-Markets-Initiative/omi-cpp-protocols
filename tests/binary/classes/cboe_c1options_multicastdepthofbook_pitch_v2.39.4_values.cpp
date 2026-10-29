// Cboe.C1Options.MulticastDepthOfBook.Pitch.v2.39.4 canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/binary/classes/cboe/c1options/multicastdepthofbook/pitch/v2.39.4/definitions.hpp"

namespace protocol = ::cboe::c1options::multicastdepthofbook::pitch::v2_39_4;

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

    values["packet.packetheader.length"] = canonical::number(packet.packet_header().length());
    values["packet.packetheader.messagecount"] = canonical::number(packet.packet_header().message_count());
    values["packet.packetheader.unit"] = canonical::number(packet.packet_header().unit());
    values["packet.packetheader.sequence"] = canonical::number(packet.packet_header().sequence());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(each.message_header().message_length());
        values[entry + ".messageheader.messagetype"] = canonical::number(each.message_header().message_type());

        if (const auto* message = dynamic_cast<const protocol::TimeMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.timemessage";
            values[entry + ".payload.timemessage.time"] = canonical::number((*message).time());
        } else if (const auto* message = dynamic_cast<const protocol::UnitClearMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.unitclearmessage";
            values[entry + ".payload.unitclearmessage.timeoffset"] = canonical::number((*message).time_offset());
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderLongMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.addorderlongmessage";
            values[entry + ".payload.addorderlongmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.addorderlongmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.addorderlongmessage.sideindicator"] = canonical::text(canonical::character((*message).side_indicator()), ' ', false);
            values[entry + ".payload.addorderlongmessage.longquantity"] = canonical::number((*message).long_quantity());
            values[entry + ".payload.addorderlongmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".payload.addorderlongmessage.longprice"] = canonical::scaled((*message).long_price().mantissa(), (*message).long_price().exponent());
            values[entry + ".payload.addorderlongmessage.addflags.display"] = canonical::number(static_cast<std::uint64_t>((*message).add_flags().display()));
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderShortMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.addordershortmessage";
            values[entry + ".payload.addordershortmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.addordershortmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.addordershortmessage.sideindicator"] = canonical::text(canonical::character((*message).side_indicator()), ' ', false);
            values[entry + ".payload.addordershortmessage.shortquantity"] = canonical::number((*message).short_quantity());
            values[entry + ".payload.addordershortmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".payload.addordershortmessage.shortprice"] = canonical::scaled((*message).short_price().mantissa(), (*message).short_price().exponent());
            values[entry + ".payload.addordershortmessage.addflags.display"] = canonical::number(static_cast<std::uint64_t>((*message).add_flags().display()));
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderExpandedMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.addorderexpandedmessage";
            values[entry + ".payload.addorderexpandedmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.addorderexpandedmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.addorderexpandedmessage.sideindicator"] = canonical::text(canonical::character((*message).side_indicator()), ' ', false);
            values[entry + ".payload.addorderexpandedmessage.longquantity"] = canonical::number((*message).long_quantity());
            values[entry + ".payload.addorderexpandedmessage.expandedsymbol"] = canonical::text(std::string((*message).expanded_symbol()), ' ', false);
            values[entry + ".payload.addorderexpandedmessage.longprice"] = canonical::scaled((*message).long_price().mantissa(), (*message).long_price().exponent());
            values[entry + ".payload.addorderexpandedmessage.addflags.display"] = canonical::number(static_cast<std::uint64_t>((*message).add_flags().display()));
            values[entry + ".payload.addorderexpandedmessage.participantid"] = canonical::text(std::string((*message).participant_id()), ' ', false);
            values[entry + ".payload.addorderexpandedmessage.customerindicator"] = canonical::text(canonical::character((*message).customer_indicator()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedmessage";
            values[entry + ".payload.orderexecutedmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.orderexecutedmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.orderexecutedmessage.executedquantity"] = canonical::number((*message).executed_quantity());
            values[entry + ".payload.orderexecutedmessage.executionid"] = canonical::number((*message).execution_id());
            values[entry + ".payload.orderexecutedmessage.tradecondition"] = canonical::text(canonical::character((*message).trade_condition()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedAtPriceSizeMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedatpricesizemessage";
            values[entry + ".payload.orderexecutedatpricesizemessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.orderexecutedatpricesizemessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.orderexecutedatpricesizemessage.executedquantity"] = canonical::number((*message).executed_quantity());
            values[entry + ".payload.orderexecutedatpricesizemessage.remainingquantity"] = canonical::number((*message).remaining_quantity());
            values[entry + ".payload.orderexecutedatpricesizemessage.executionid"] = canonical::number((*message).execution_id());
            values[entry + ".payload.orderexecutedatpricesizemessage.longprice"] = canonical::scaled((*message).long_price().mantissa(), (*message).long_price().exponent());
            values[entry + ".payload.orderexecutedatpricesizemessage.tradecondition"] = canonical::text(canonical::character((*message).trade_condition()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::ReduceSizeLongMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.reducesizelongmessage";
            values[entry + ".payload.reducesizelongmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.reducesizelongmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.reducesizelongmessage.canceledlongquantity"] = canonical::number((*message).canceled_long_quantity());
        } else if (const auto* message = dynamic_cast<const protocol::ReduceSizeShortMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.reducesizeshortmessage";
            values[entry + ".payload.reducesizeshortmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.reducesizeshortmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.reducesizeshortmessage.canceledshortquantity"] = canonical::number((*message).canceled_short_quantity());
        } else if (const auto* message = dynamic_cast<const protocol::ModifyOrderLongMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.modifyorderlongmessage";
            values[entry + ".payload.modifyorderlongmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.modifyorderlongmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.modifyorderlongmessage.longquantity"] = canonical::number((*message).long_quantity());
            values[entry + ".payload.modifyorderlongmessage.longprice"] = canonical::scaled((*message).long_price().mantissa(), (*message).long_price().exponent());
            values[entry + ".payload.modifyorderlongmessage.modifyflags.display"] = canonical::number(static_cast<std::uint64_t>((*message).modify_flags().display()));
            values[entry + ".payload.modifyorderlongmessage.modifyflags.maintainpriority"] = canonical::number(static_cast<std::uint64_t>((*message).modify_flags().maintain_priority()));
        } else if (const auto* message = dynamic_cast<const protocol::ModifyOrderShortMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.modifyordershortmessage";
            values[entry + ".payload.modifyordershortmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.modifyordershortmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.modifyordershortmessage.shortquantity"] = canonical::number((*message).short_quantity());
            values[entry + ".payload.modifyordershortmessage.shortprice"] = canonical::scaled((*message).short_price().mantissa(), (*message).short_price().exponent());
            values[entry + ".payload.modifyordershortmessage.modifyflags.display"] = canonical::number(static_cast<std::uint64_t>((*message).modify_flags().display()));
            values[entry + ".payload.modifyordershortmessage.modifyflags.maintainpriority"] = canonical::number(static_cast<std::uint64_t>((*message).modify_flags().maintain_priority()));
        } else if (const auto* message = dynamic_cast<const protocol::DeleteOrderMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.deleteordermessage";
            values[entry + ".payload.deleteordermessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.deleteordermessage.orderid"] = canonical::number((*message).order_id());
        } else if (const auto* message = dynamic_cast<const protocol::TradeLongMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradelongmessage";
            values[entry + ".payload.tradelongmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.tradelongmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.tradelongmessage.sideindicator"] = canonical::text(canonical::character((*message).side_indicator()), ' ', false);
            values[entry + ".payload.tradelongmessage.longquantity"] = canonical::number((*message).long_quantity());
            values[entry + ".payload.tradelongmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".payload.tradelongmessage.longprice"] = canonical::scaled((*message).long_price().mantissa(), (*message).long_price().exponent());
            values[entry + ".payload.tradelongmessage.executionid"] = canonical::number((*message).execution_id());
            values[entry + ".payload.tradelongmessage.tradecondition"] = canonical::text(canonical::character((*message).trade_condition()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::TradeShortMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradeshortmessage";
            values[entry + ".payload.tradeshortmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.tradeshortmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.tradeshortmessage.sideindicator"] = canonical::text(canonical::character((*message).side_indicator()), ' ', false);
            values[entry + ".payload.tradeshortmessage.shortquantity"] = canonical::number((*message).short_quantity());
            values[entry + ".payload.tradeshortmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".payload.tradeshortmessage.shortprice"] = canonical::scaled((*message).short_price().mantissa(), (*message).short_price().exponent());
            values[entry + ".payload.tradeshortmessage.executionid"] = canonical::number((*message).execution_id());
            values[entry + ".payload.tradeshortmessage.tradecondition"] = canonical::text(canonical::character((*message).trade_condition()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::TradeExpandedMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradeexpandedmessage";
            values[entry + ".payload.tradeexpandedmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.tradeexpandedmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.tradeexpandedmessage.sideindicator"] = canonical::text(canonical::character((*message).side_indicator()), ' ', false);
            values[entry + ".payload.tradeexpandedmessage.longquantity"] = canonical::number((*message).long_quantity());
            values[entry + ".payload.tradeexpandedmessage.expandedsymbol"] = canonical::text(std::string((*message).expanded_symbol()), ' ', false);
            values[entry + ".payload.tradeexpandedmessage.longprice"] = canonical::scaled((*message).long_price().mantissa(), (*message).long_price().exponent());
            values[entry + ".payload.tradeexpandedmessage.executionid"] = canonical::number((*message).execution_id());
            values[entry + ".payload.tradeexpandedmessage.tradecondition"] = canonical::text(canonical::character((*message).trade_condition()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::TradeBreakMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradebreakmessage";
            values[entry + ".payload.tradebreakmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.tradebreakmessage.executionid"] = canonical::number((*message).execution_id());
        } else if (const auto* message = dynamic_cast<const protocol::EndOfSessionMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.endofsessionmessage";
            values[entry + ".payload.endofsessionmessage.timeoffset"] = canonical::number((*message).time_offset());
        } else if (const auto* message = dynamic_cast<const protocol::SymbolMappingMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.symbolmappingmessage";
            values[entry + ".payload.symbolmappingmessage.feedsymbol"] = canonical::text(std::string((*message).feed_symbol()), ' ', false);
            values[entry + ".payload.symbolmappingmessage.osisymbol"] = canonical::text(std::string((*message).osi_symbol()), ' ', false);
            values[entry + ".payload.symbolmappingmessage.symbolcondition"] = canonical::text(canonical::character((*message).symbol_condition()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::TradingStatusMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradingstatusmessage";
            values[entry + ".payload.tradingstatusmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.tradingstatusmessage.expandedsymbol"] = canonical::text(std::string((*message).expanded_symbol()), ' ', false);
            values[entry + ".payload.tradingstatusmessage.tradingstatus"] = canonical::text(canonical::character((*message).trading_status()), ' ', false);
            values[entry + ".payload.tradingstatusmessage.regshoaction"] = canonical::text(canonical::character((*message).reg_sho_action()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::AuctionUpdateMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.auctionupdatemessage";
            values[entry + ".payload.auctionupdatemessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.auctionupdatemessage.stocksymbol"] = canonical::text(std::string((*message).stock_symbol()), ' ', false);
            values[entry + ".payload.auctionupdatemessage.auctiontype"] = canonical::text(canonical::character((*message).auction_type()), ' ', false);
            values[entry + ".payload.auctionupdatemessage.referenceprice"] = canonical::scaled((*message).reference_price().mantissa(), (*message).reference_price().exponent());
            values[entry + ".payload.auctionupdatemessage.buyshares"] = canonical::number((*message).buy_shares());
            values[entry + ".payload.auctionupdatemessage.sellshares"] = canonical::number((*message).sell_shares());
            values[entry + ".payload.auctionupdatemessage.indicativeprice"] = canonical::scaled((*message).indicative_price().mantissa(), (*message).indicative_price().exponent());
            values[entry + ".payload.auctionupdatemessage.auctiononlyprice"] = canonical::scaled((*message).auction_only_price().mantissa(), (*message).auction_only_price().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::AuctionSummaryMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.auctionsummarymessage";
            values[entry + ".payload.auctionsummarymessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.auctionsummarymessage.stocksymbol"] = canonical::text(std::string((*message).stock_symbol()), ' ', false);
            values[entry + ".payload.auctionsummarymessage.auctiontype"] = canonical::text(canonical::character((*message).auction_type()), ' ', false);
            values[entry + ".payload.auctionsummarymessage.longprice"] = canonical::scaled((*message).long_price().mantissa(), (*message).long_price().exponent());
            values[entry + ".payload.auctionsummarymessage.shares"] = canonical::number((*message).shares());
        } else if (const auto* message = dynamic_cast<const protocol::AuctionNotificationMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.auctionnotificationmessage";
            values[entry + ".payload.auctionnotificationmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.auctionnotificationmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".payload.auctionnotificationmessage.auctionid"] = canonical::number((*message).auction_id());
            values[entry + ".payload.auctionnotificationmessage.auctiontype"] = canonical::text(canonical::character((*message).auction_type()), ' ', false);
            values[entry + ".payload.auctionnotificationmessage.sideindicator"] = canonical::text(canonical::character((*message).side_indicator()), ' ', false);
            values[entry + ".payload.auctionnotificationmessage.longprice"] = canonical::scaled((*message).long_price().mantissa(), (*message).long_price().exponent());
            values[entry + ".payload.auctionnotificationmessage.contracts"] = canonical::number((*message).contracts());
            values[entry + ".payload.auctionnotificationmessage.customerindicator"] = canonical::text(canonical::character((*message).customer_indicator()), ' ', false);
            values[entry + ".payload.auctionnotificationmessage.participantid"] = canonical::text(std::string((*message).participant_id()), ' ', false);
            values[entry + ".payload.auctionnotificationmessage.auctionendoffset"] = canonical::number((*message).auction_end_offset());
        } else if (const auto* message = dynamic_cast<const protocol::AuctionCancelMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.auctioncancelmessage";
            values[entry + ".payload.auctioncancelmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.auctioncancelmessage.auctionid"] = canonical::number((*message).auction_id());
        } else if (const auto* message = dynamic_cast<const protocol::AuctionTradeMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.auctiontrademessage";
            values[entry + ".payload.auctiontrademessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.auctiontrademessage.auctionid"] = canonical::number((*message).auction_id());
            values[entry + ".payload.auctiontrademessage.executionid"] = canonical::number((*message).execution_id());
            values[entry + ".payload.auctiontrademessage.longprice"] = canonical::scaled((*message).long_price().mantissa(), (*message).long_price().exponent());
            values[entry + ".payload.auctiontrademessage.contracts"] = canonical::number((*message).contracts());
        } else if (const auto* message = dynamic_cast<const protocol::RetailPriceImprovementMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.retailpriceimprovementmessage";
            values[entry + ".payload.retailpriceimprovementmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.retailpriceimprovementmessage.expandedsymbol"] = canonical::text(std::string((*message).expanded_symbol()), ' ', false);
            values[entry + ".payload.retailpriceimprovementmessage.retailpriceimprovement"] = canonical::text(canonical::character((*message).retail_price_improvement()), ' ', false);
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
    std::printf("== Cboe.C1Options.MulticastDepthOfBook.Pitch.v2.39.4 (classes values)\n");
    int failures = 0;
    failures += check("AddOrderLongMessage", "Cboe/C1Options.MulticastDepthOfBook.Pitch.v2.39.4/AddOrderLongMessage.pcap", "cboe/c1options/multicastdepthofbook/pitch/v2.39.4/AddOrderLongMessage.values");
    failures += check("DeleteOrderMessage", "Cboe/C1Options.MulticastDepthOfBook.Pitch.v2.39.4/DeleteOrderMessage.pcap", "cboe/c1options/multicastdepthofbook/pitch/v2.39.4/DeleteOrderMessage.values");
    failures += check("Heartbeat", "Cboe/C1Options.MulticastDepthOfBook.Pitch.v2.39.4/Heartbeat.pcap", "cboe/c1options/multicastdepthofbook/pitch/v2.39.4/Heartbeat.values");
    failures += check("ModifyOrderLongMessage", "Cboe/C1Options.MulticastDepthOfBook.Pitch.v2.39.4/ModifyOrderLongMessage.pcap", "cboe/c1options/multicastdepthofbook/pitch/v2.39.4/ModifyOrderLongMessage.values");
    return failures == 0 ? 0 : 1;
}
