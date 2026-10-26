// Cboe.BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29 canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/binary/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/definitions.hpp"

namespace protocol = ::cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29;

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
            values[entry + ".payload.addorderlongmessage.quantity"] = canonical::number((*message).quantity());
            values[entry + ".payload.addorderlongmessage.symbolshort"] = canonical::text(std::string((*message).symbol_short()), ' ', false);
            values[entry + ".payload.addorderlongmessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
            values[entry + ".payload.addorderlongmessage.addorderflags.display"] = canonical::number(static_cast<std::uint64_t>((*message).add_order_flags().display()));
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderShortMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.addordershortmessage";
            values[entry + ".payload.addordershortmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.addordershortmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.addordershortmessage.sideindicator"] = canonical::text(canonical::character((*message).side_indicator()), ' ', false);
            values[entry + ".payload.addordershortmessage.quantityshort"] = canonical::number((*message).quantity_short());
            values[entry + ".payload.addordershortmessage.symbolshort"] = canonical::text(std::string((*message).symbol_short()), ' ', false);
            values[entry + ".payload.addordershortmessage.priceshort"] = canonical::scaled((*message).price_short().mantissa(), (*message).price_short().exponent());
            values[entry + ".payload.addordershortmessage.addorderflags.display"] = canonical::number(static_cast<std::uint64_t>((*message).add_order_flags().display()));
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderExpandedMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.addorderexpandedmessage";
            values[entry + ".payload.addorderexpandedmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.addorderexpandedmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.addorderexpandedmessage.sideindicator"] = canonical::text(canonical::character((*message).side_indicator()), ' ', false);
            values[entry + ".payload.addorderexpandedmessage.quantity"] = canonical::number((*message).quantity());
            values[entry + ".payload.addorderexpandedmessage.symbollong"] = canonical::text(std::string((*message).symbol_long()), ' ', false);
            values[entry + ".payload.addorderexpandedmessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
            values[entry + ".payload.addorderexpandedmessage.addorderflags.display"] = canonical::number(static_cast<std::uint64_t>((*message).add_order_flags().display()));
            values[entry + ".payload.addorderexpandedmessage.participantid"] = canonical::text(std::string((*message).participant_id()), ' ', false);
            values[entry + ".payload.addorderexpandedmessage.customerindicator"] = canonical::text(canonical::character((*message).customer_indicator()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedmessage";
            values[entry + ".payload.orderexecutedmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.orderexecutedmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.orderexecutedmessage.executedquantity"] = canonical::number((*message).executed_quantity());
            values[entry + ".payload.orderexecutedmessage.executionid"] = canonical::number((*message).execution_id());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedAtPriceSizeMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedatpricesizemessage";
            values[entry + ".payload.orderexecutedatpricesizemessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.orderexecutedatpricesizemessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.orderexecutedatpricesizemessage.executedquantity"] = canonical::number((*message).executed_quantity());
            values[entry + ".payload.orderexecutedatpricesizemessage.remainingquantity"] = canonical::number((*message).remaining_quantity());
            values[entry + ".payload.orderexecutedatpricesizemessage.executionid"] = canonical::number((*message).execution_id());
            values[entry + ".payload.orderexecutedatpricesizemessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::ReduceSizeLongMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.reducesizelongmessage";
            values[entry + ".payload.reducesizelongmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.reducesizelongmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.reducesizelongmessage.canceledquantity"] = canonical::number((*message).canceled_quantity());
        } else if (const auto* message = dynamic_cast<const protocol::ReduceSizeShortMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.reducesizeshortmessage";
            values[entry + ".payload.reducesizeshortmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.reducesizeshortmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.reducesizeshortmessage.canceledquantityshort"] = canonical::number((*message).canceled_quantity_short());
        } else if (const auto* message = dynamic_cast<const protocol::ModifyOrderLongMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.modifyorderlongmessage";
            values[entry + ".payload.modifyorderlongmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.modifyorderlongmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.modifyorderlongmessage.quantity"] = canonical::number((*message).quantity());
            values[entry + ".payload.modifyorderlongmessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
            values[entry + ".payload.modifyorderlongmessage.modifyorderflags.display"] = canonical::number(static_cast<std::uint64_t>((*message).modify_order_flags().display()));
            values[entry + ".payload.modifyorderlongmessage.modifyorderflags.priority"] = canonical::number(static_cast<std::uint64_t>((*message).modify_order_flags().priority()));
        } else if (const auto* message = dynamic_cast<const protocol::ModifyOrderShortMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.modifyordershortmessage";
            values[entry + ".payload.modifyordershortmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.modifyordershortmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.modifyordershortmessage.quantityshort"] = canonical::number((*message).quantity_short());
            values[entry + ".payload.modifyordershortmessage.priceshort"] = canonical::scaled((*message).price_short().mantissa(), (*message).price_short().exponent());
            values[entry + ".payload.modifyordershortmessage.modifyorderflags.display"] = canonical::number(static_cast<std::uint64_t>((*message).modify_order_flags().display()));
            values[entry + ".payload.modifyordershortmessage.modifyorderflags.priority"] = canonical::number(static_cast<std::uint64_t>((*message).modify_order_flags().priority()));
        } else if (const auto* message = dynamic_cast<const protocol::DeleteOrderMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.deleteordermessage";
            values[entry + ".payload.deleteordermessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.deleteordermessage.orderid"] = canonical::number((*message).order_id());
        } else if (const auto* message = dynamic_cast<const protocol::TradeLongMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradelongmessage";
            values[entry + ".payload.tradelongmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.tradelongmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.tradelongmessage.sideindicator"] = canonical::text(canonical::character((*message).side_indicator()), ' ', false);
            values[entry + ".payload.tradelongmessage.quantity"] = canonical::number((*message).quantity());
            values[entry + ".payload.tradelongmessage.symbolshort"] = canonical::text(std::string((*message).symbol_short()), ' ', false);
            values[entry + ".payload.tradelongmessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
            values[entry + ".payload.tradelongmessage.executionid"] = canonical::number((*message).execution_id());
        } else if (const auto* message = dynamic_cast<const protocol::TradeShortMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradeshortmessage";
            values[entry + ".payload.tradeshortmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.tradeshortmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.tradeshortmessage.sideindicator"] = canonical::text(canonical::character((*message).side_indicator()), ' ', false);
            values[entry + ".payload.tradeshortmessage.quantityshort"] = canonical::number((*message).quantity_short());
            values[entry + ".payload.tradeshortmessage.symbolshort"] = canonical::text(std::string((*message).symbol_short()), ' ', false);
            values[entry + ".payload.tradeshortmessage.priceshort"] = canonical::scaled((*message).price_short().mantissa(), (*message).price_short().exponent());
            values[entry + ".payload.tradeshortmessage.executionid"] = canonical::number((*message).execution_id());
        } else if (const auto* message = dynamic_cast<const protocol::TradeExpandedMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradeexpandedmessage";
            values[entry + ".payload.tradeexpandedmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.tradeexpandedmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.tradeexpandedmessage.sideindicator"] = canonical::text(canonical::character((*message).side_indicator()), ' ', false);
            values[entry + ".payload.tradeexpandedmessage.quantity"] = canonical::number((*message).quantity());
            values[entry + ".payload.tradeexpandedmessage.symbollong"] = canonical::text(std::string((*message).symbol_long()), ' ', false);
            values[entry + ".payload.tradeexpandedmessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
            values[entry + ".payload.tradeexpandedmessage.executionid"] = canonical::number((*message).execution_id());
        } else if (const auto* message = dynamic_cast<const protocol::TradeBreakMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradebreakmessage";
            values[entry + ".payload.tradebreakmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.tradebreakmessage.executionid"] = canonical::number((*message).execution_id());
        } else if (const auto* message = dynamic_cast<const protocol::EndOfSession*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.endofsession";
            values[entry + ".payload.endofsession.lasttimestamp"] = canonical::number((*message).last_timestamp());
        } else if (const auto* message = dynamic_cast<const protocol::TradingStatusMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradingstatusmessage";
            values[entry + ".payload.tradingstatusmessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.tradingstatusmessage.symbollong"] = canonical::text(std::string((*message).symbol_long()), ' ', false);
            values[entry + ".payload.tradingstatusmessage.tradingstatus"] = canonical::text(canonical::character((*message).trading_status()), ' ', false);
            values[entry + ".payload.tradingstatusmessage.regshoaction"] = canonical::text(canonical::character((*message).reg_sho_action()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::AuctionUpdateMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.auctionupdatemessage";
            values[entry + ".payload.auctionupdatemessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.auctionupdatemessage.symbollong"] = canonical::text(std::string((*message).symbol_long()), ' ', false);
            values[entry + ".payload.auctionupdatemessage.auctiontype"] = canonical::text(canonical::character((*message).auction_type()), ' ', false);
            values[entry + ".payload.auctionupdatemessage.referenceprice"] = canonical::number((*message).reference_price());
            values[entry + ".payload.auctionupdatemessage.buyshares"] = canonical::number((*message).buy_shares());
            values[entry + ".payload.auctionupdatemessage.sellshares"] = canonical::number((*message).sell_shares());
            values[entry + ".payload.auctionupdatemessage.indicativeprice"] = canonical::number((*message).indicative_price());
            values[entry + ".payload.auctionupdatemessage.auctiononlyprice"] = canonical::number((*message).auction_only_price());
        } else if (const auto* message = dynamic_cast<const protocol::AuctionSummaryMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.auctionsummarymessage";
            values[entry + ".payload.auctionsummarymessage.timeoffset"] = canonical::number((*message).time_offset());
            values[entry + ".payload.auctionsummarymessage.symbollong"] = canonical::text(std::string((*message).symbol_long()), ' ', false);
            values[entry + ".payload.auctionsummarymessage.auctionopeningtype"] = canonical::text(canonical::character((*message).auction_opening_type()), ' ', false);
            values[entry + ".payload.auctionsummarymessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
            values[entry + ".payload.auctionsummarymessage.sharescontracts"] = canonical::number((*message).shares_contracts());
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
    std::printf("== Cboe.BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29 (classes values)\n");
    int failures = 0;
    failures += check("AddOrderExpandedMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/AddOrderExpandedMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/AddOrderExpandedMessage.values");
    failures += check("AddOrderLongMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/AddOrderLongMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/AddOrderLongMessage.values");
    failures += check("AddOrderShortMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/AddOrderShortMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/AddOrderShortMessage.values");
    failures += check("AuctionSummaryMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/AuctionSummaryMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/AuctionSummaryMessage.values");
    failures += check("AuctionUpdateMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/AuctionUpdateMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/AuctionUpdateMessage.values");
    failures += check("DeleteOrderMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/DeleteOrderMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/DeleteOrderMessage.values");
    failures += check("ModifyOrderLongMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/ModifyOrderLongMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/ModifyOrderLongMessage.values");
    failures += check("ModifyOrderShortMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/ModifyOrderShortMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/ModifyOrderShortMessage.values");
    failures += check("OrderExecutedAtPriceSizeMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/OrderExecutedAtPriceSizeMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/OrderExecutedAtPriceSizeMessage.values");
    failures += check("OrderExecutedMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/OrderExecutedMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/OrderExecutedMessage.values");
    failures += check("ReduceSizeShortMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/ReduceSizeShortMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/ReduceSizeShortMessage.values");
    failures += check("TimeMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/TimeMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/TimeMessage.values");
    failures += check("TradeLongMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/TradeLongMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/TradeLongMessage.values");
    failures += check("TradeShortMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/TradeShortMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/TradeShortMessage.values");
    failures += check("TradingStatusMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/TradingStatusMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/TradingStatusMessage.values");
    return failures == 0 ? 0 : 1;
}
