// Cboe.C1Options.Complex.Pitch.v2.1.18 canonical values, through the Flyweight reader: every value Flyweight reads
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
#include "cpp/binary/flyweight/cboe/c1options/complex/pitch/v2.1.18/definitions.hpp"

namespace protocol = ::cboe::c1options::complex::pitch::v2_1_18;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        values["packet.packetheader.length"] = canonical::number(packet.packet_header().length());
        values["packet.packetheader.messagecount"] = canonical::number(packet.packet_header().message_count());
        values["packet.packetheader.unit"] = canonical::number(packet.packet_header().unit());
        values["packet.packetheader.sequence"] = canonical::number(packet.packet_header().sequence());
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

    void on(const protocol::TimeMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.timemessage";
        values[entry + ".payload.timemessage.time"] = canonical::number(message.time());
    }

    void on(const protocol::UnitClearMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.unitclearmessage";
        values[entry + ".payload.unitclearmessage.timeoffset"] = canonical::number(message.time_offset());
    }

    void on(const protocol::TransactionBegin& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.transactionbegin";
        values[entry + ".payload.transactionbegin.timeoffset"] = canonical::number(message.time_offset());
    }

    void on(const protocol::TransactionEndMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.transactionendmessage";
        values[entry + ".payload.transactionendmessage.timeoffset"] = canonical::number(message.time_offset());
    }

    void on(const protocol::ComplexInstrumentDefinitionExpandedMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.complexinstrumentdefinitionexpandedmessage";
        values[entry + ".payload.complexinstrumentdefinitionexpandedmessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.complexinstrumentdefinitionexpandedmessage.complexinstrumentid"] = canonical::text(std::string(message.complex_instrument_id()), ' ', false);
        values[entry + ".payload.complexinstrumentdefinitionexpandedmessage.complexinstrumentunderlying"] = canonical::text(std::string(message.complex_instrument_underlying()), ' ', false);
        values[entry + ".payload.complexinstrumentdefinitionexpandedmessage.complexinstrumenttype"] = canonical::text(std::string(message.complex_instrument_type()), ' ', false);
        values[entry + ".payload.complexinstrumentdefinitionexpandedmessage.legcount"] = canonical::number(message.leg_count());
    }

    void on(const protocol::SymbolMappingMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.symbolmappingmessage";
        values[entry + ".payload.symbolmappingmessage.feedsymbol"] = canonical::text(std::string(message.feed_symbol()), ' ', false);
        values[entry + ".payload.symbolmappingmessage.osisymbol"] = canonical::text(std::string(message.osi_symbol()), ' ', false);
        values[entry + ".payload.symbolmappingmessage.symbolcondition"] = canonical::text(canonical::character(message.symbol_condition()), ' ', false);
        values[entry + ".payload.symbolmappingmessage.underlying"] = canonical::text(std::string(message.underlying()), ' ', false);
    }

    void on(const protocol::AddOrderLongMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.addorderlongmessage";
        values[entry + ".payload.addorderlongmessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.addorderlongmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.addorderlongmessage.sideindicator"] = canonical::text(canonical::character(message.side_indicator()), ' ', false);
        values[entry + ".payload.addorderlongmessage.quantity"] = canonical::number(message.quantity());
        values[entry + ".payload.addorderlongmessage.complexinstrumentid"] = canonical::text(std::string(message.complex_instrument_id()), ' ', false);
        values[entry + ".payload.addorderlongmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
    }

    void on(const protocol::AddOrderShortMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.addordershortmessage";
        values[entry + ".payload.addordershortmessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.addordershortmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.addordershortmessage.sideindicator"] = canonical::text(canonical::character(message.side_indicator()), ' ', false);
        values[entry + ".payload.addordershortmessage.quantityshort"] = canonical::number(message.quantity_short());
        values[entry + ".payload.addordershortmessage.complexinstrumentid"] = canonical::text(std::string(message.complex_instrument_id()), ' ', false);
        values[entry + ".payload.addordershortmessage.priceshort"] = canonical::scaled(message.price_short().mantissa(), message.price_short().exponent());
    }

    void on(const protocol::AddOrderExpandedMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.addorderexpandedmessage";
        values[entry + ".payload.addorderexpandedmessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.addorderexpandedmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.addorderexpandedmessage.sideindicator"] = canonical::text(canonical::character(message.side_indicator()), ' ', false);
        values[entry + ".payload.addorderexpandedmessage.quantity"] = canonical::number(message.quantity());
        values[entry + ".payload.addorderexpandedmessage.complexinstrumentid8"] = canonical::text(std::string(message.complex_instrument_id_8()), ' ', false);
        values[entry + ".payload.addorderexpandedmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.addorderexpandedmessage.participantid"] = canonical::text(std::string(message.participant_id()), ' ', false);
        values[entry + ".payload.addorderexpandedmessage.customerindicator"] = canonical::text(canonical::character(message.customer_indicator()), ' ', false);
        values[entry + ".payload.addorderexpandedmessage.clientid"] = canonical::text(std::string(message.client_id()), ' ', false);
    }

    void on(const protocol::OrderExecutedMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedmessage";
        values[entry + ".payload.orderexecutedmessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.orderexecutedmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.orderexecutedmessage.executedquantity"] = canonical::number(message.executed_quantity());
        values[entry + ".payload.orderexecutedmessage.executionid"] = canonical::number(message.execution_id());
        values[entry + ".payload.orderexecutedmessage.tradecondition"] = canonical::text(canonical::character(message.trade_condition()), ' ', false);
    }

    void on(const protocol::OrderExecutedAtPriceSizeMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedatpricesizemessage";
        values[entry + ".payload.orderexecutedatpricesizemessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.orderexecutedatpricesizemessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.orderexecutedatpricesizemessage.executedquantity"] = canonical::number(message.executed_quantity());
        values[entry + ".payload.orderexecutedatpricesizemessage.remainingquantity"] = canonical::number(message.remaining_quantity());
        values[entry + ".payload.orderexecutedatpricesizemessage.executionid"] = canonical::number(message.execution_id());
        values[entry + ".payload.orderexecutedatpricesizemessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.orderexecutedatpricesizemessage.tradecondition"] = canonical::text(canonical::character(message.trade_condition()), ' ', false);
    }

    void on(const protocol::ReduceSizeLongMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.reducesizelongmessage";
        values[entry + ".payload.reducesizelongmessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.reducesizelongmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.reducesizelongmessage.canceledquantity"] = canonical::number(message.canceled_quantity());
    }

    void on(const protocol::ReduceSizeShortMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.reducesizeshortmessage";
        values[entry + ".payload.reducesizeshortmessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.reducesizeshortmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.reducesizeshortmessage.canceledquantityshort"] = canonical::number(message.canceled_quantity_short());
    }

    void on(const protocol::ModifyOrderLongMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.modifyorderlongmessage";
        values[entry + ".payload.modifyorderlongmessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.modifyorderlongmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.modifyorderlongmessage.quantity"] = canonical::number(message.quantity());
        values[entry + ".payload.modifyorderlongmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
    }

    void on(const protocol::ModifyOrderShortMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.modifyordershortmessage";
        values[entry + ".payload.modifyordershortmessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.modifyordershortmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.modifyordershortmessage.quantityshort"] = canonical::number(message.quantity_short());
        values[entry + ".payload.modifyordershortmessage.priceshort"] = canonical::scaled(message.price_short().mantissa(), message.price_short().exponent());
    }

    void on(const protocol::DeleteOrderMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.deleteordermessage";
        values[entry + ".payload.deleteordermessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.deleteordermessage.orderid"] = canonical::number(message.order_id());
    }

    void on(const protocol::TradeLongMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.tradelongmessage";
        values[entry + ".payload.tradelongmessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.tradelongmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.tradelongmessage.sideindicator"] = canonical::text(canonical::character(message.side_indicator()), ' ', false);
        values[entry + ".payload.tradelongmessage.quantity"] = canonical::number(message.quantity());
        values[entry + ".payload.tradelongmessage.complexinstrumentid"] = canonical::text(std::string(message.complex_instrument_id()), ' ', false);
        values[entry + ".payload.tradelongmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.tradelongmessage.executionid"] = canonical::number(message.execution_id());
        values[entry + ".payload.tradelongmessage.tradecondition"] = canonical::text(canonical::character(message.trade_condition()), ' ', false);
    }

    void on(const protocol::TradeShortMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.tradeshortmessage";
        values[entry + ".payload.tradeshortmessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.tradeshortmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.tradeshortmessage.sideindicator"] = canonical::text(canonical::character(message.side_indicator()), ' ', false);
        values[entry + ".payload.tradeshortmessage.quantityshort"] = canonical::number(message.quantity_short());
        values[entry + ".payload.tradeshortmessage.complexinstrumentid"] = canonical::text(std::string(message.complex_instrument_id()), ' ', false);
        values[entry + ".payload.tradeshortmessage.priceshort"] = canonical::scaled(message.price_short().mantissa(), message.price_short().exponent());
        values[entry + ".payload.tradeshortmessage.executionid"] = canonical::number(message.execution_id());
        values[entry + ".payload.tradeshortmessage.tradecondition"] = canonical::text(canonical::character(message.trade_condition()), ' ', false);
    }

    void on(const protocol::AuctionNotificationMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.auctionnotificationmessage";
        values[entry + ".payload.auctionnotificationmessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.auctionnotificationmessage.complexinstrumentid"] = canonical::text(std::string(message.complex_instrument_id()), ' ', false);
        values[entry + ".payload.auctionnotificationmessage.auctionid"] = canonical::number(message.auction_id());
        values[entry + ".payload.auctionnotificationmessage.auctiontype"] = canonical::text(canonical::character(message.auction_type()), ' ', false);
        values[entry + ".payload.auctionnotificationmessage.sideindicator"] = canonical::text(canonical::character(message.side_indicator()), ' ', false);
        values[entry + ".payload.auctionnotificationmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.auctionnotificationmessage.quantity"] = canonical::number(message.quantity());
        values[entry + ".payload.auctionnotificationmessage.customerindicator"] = canonical::text(canonical::character(message.customer_indicator()), ' ', false);
        values[entry + ".payload.auctionnotificationmessage.participantid"] = canonical::text(std::string(message.participant_id()), ' ', false);
        values[entry + ".payload.auctionnotificationmessage.auctionendoffset"] = canonical::number(message.auction_end_offset());
        values[entry + ".payload.auctionnotificationmessage.clientid"] = canonical::text(std::string(message.client_id()), ' ', false);
    }

    void on(const protocol::AuctionCancelMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.auctioncancelmessage";
        values[entry + ".payload.auctioncancelmessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.auctioncancelmessage.auctionid"] = canonical::number(message.auction_id());
    }

    void on(const protocol::AuctionTradeMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.auctiontrademessage";
        values[entry + ".payload.auctiontrademessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.auctiontrademessage.auctionid"] = canonical::number(message.auction_id());
        values[entry + ".payload.auctiontrademessage.executionid"] = canonical::number(message.execution_id());
        values[entry + ".payload.auctiontrademessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.auctiontrademessage.quantity"] = canonical::number(message.quantity());
    }

    void on(const protocol::TradingStatusMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.tradingstatusmessage";
        values[entry + ".payload.tradingstatusmessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.tradingstatusmessage.complexsymbolid"] = canonical::text(std::string(message.complex_symbol_id()), ' ', false);
        values[entry + ".payload.tradingstatusmessage.tradingstatus"] = canonical::text(canonical::character(message.trading_status()), ' ', false);
        values[entry + ".payload.tradingstatusmessage.gthtradingstatus"] = canonical::text(canonical::character(message.gth_trading_status()), ' ', false);
    }

    void on(const protocol::AuctionUpdateMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.auctionupdatemessage";
        values[entry + ".payload.auctionupdatemessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.auctionupdatemessage.complexinstrumentid8"] = canonical::text(std::string(message.complex_instrument_id_8()), ' ', false);
        values[entry + ".payload.auctionupdatemessage.auctionopeningtype"] = canonical::text(canonical::character(message.auction_opening_type()), ' ', false);
        values[entry + ".payload.auctionupdatemessage.referenceprice"] = canonical::scaled(message.reference_price().mantissa(), message.reference_price().exponent());
        values[entry + ".payload.auctionupdatemessage.buycontracts"] = canonical::number(message.buy_contracts());
        values[entry + ".payload.auctionupdatemessage.sellcontracts"] = canonical::number(message.sell_contracts());
        values[entry + ".payload.auctionupdatemessage.indicativeprice"] = canonical::scaled(message.indicative_price().mantissa(), message.indicative_price().exponent());
        values[entry + ".payload.auctionupdatemessage.auctiononlyprice"] = canonical::scaled(message.auction_only_price().mantissa(), message.auction_only_price().exponent());
        values[entry + ".payload.auctionupdatemessage.openingcondition"] = canonical::text(canonical::character(message.opening_condition()), ' ', false);
        values[entry + ".payload.auctionupdatemessage.compositemarketbidprice"] = canonical::scaled(message.composite_market_bid_price().mantissa(), message.composite_market_bid_price().exponent());
        values[entry + ".payload.auctionupdatemessage.compositemarketofferprice"] = canonical::scaled(message.composite_market_offer_price().mantissa(), message.composite_market_offer_price().exponent());
    }

    void on(const protocol::AuctionSummaryMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.auctionsummarymessage";
        values[entry + ".payload.auctionsummarymessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.auctionsummarymessage.complexinstrumentid8"] = canonical::text(std::string(message.complex_instrument_id_8()), ' ', false);
        values[entry + ".payload.auctionsummarymessage.auctionopeningtype"] = canonical::text(canonical::character(message.auction_opening_type()), ' ', false);
        values[entry + ".payload.auctionsummarymessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.auctionsummarymessage.quantity"] = canonical::number(message.quantity());
    }

    void on(const protocol::EndOfSessionMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.endofsessionmessage";
        values[entry + ".payload.endofsessionmessage.timeoffset"] = canonical::number(message.time_offset());
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
    std::printf("== Cboe.C1Options.Complex.Pitch.v2.1.18 (flyweight values)\n");
    int failures = 0;
    failures += check("AuctionCancelMessage", "Cboe/C1Options.Complex.Pitch.v2.1.18/AuctionCancelMessage.pcap", "cboe/c1options/complex/pitch/v2.1.18/AuctionCancelMessage.values");
    failures += check("AuctionNotificationMessage", "Cboe/C1Options.Complex.Pitch.v2.1.18/AuctionNotificationMessage.pcap", "cboe/c1options/complex/pitch/v2.1.18/AuctionNotificationMessage.values");
    failures += check("AuctionUpdateMessage", "Cboe/C1Options.Complex.Pitch.v2.1.18/AuctionUpdateMessage.pcap", "cboe/c1options/complex/pitch/v2.1.18/AuctionUpdateMessage.values");
    failures += check("ComplexInstrumentDefinitionExpandedMessage", "Cboe/C1Options.Complex.Pitch.v2.1.18/ComplexInstrumentDefinitionExpandedMessage.pcap", "cboe/c1options/complex/pitch/v2.1.18/ComplexInstrumentDefinitionExpandedMessage.values");
    failures += check("DeleteOrderMessage", "Cboe/C1Options.Complex.Pitch.v2.1.18/DeleteOrderMessage.pcap", "cboe/c1options/complex/pitch/v2.1.18/DeleteOrderMessage.values");
    failures += check("Heartbeat", "Cboe/C1Options.Complex.Pitch.v2.1.18/Heartbeat.pcap", "cboe/c1options/complex/pitch/v2.1.18/Heartbeat.values");
    failures += check("ModifyOrderShortMessage", "Cboe/C1Options.Complex.Pitch.v2.1.18/ModifyOrderShortMessage.pcap", "cboe/c1options/complex/pitch/v2.1.18/ModifyOrderShortMessage.values");
    failures += check("OrderExecutedMessage", "Cboe/C1Options.Complex.Pitch.v2.1.18/OrderExecutedMessage.pcap", "cboe/c1options/complex/pitch/v2.1.18/OrderExecutedMessage.values");
    failures += check("SymbolMappingMessage", "Cboe/C1Options.Complex.Pitch.v2.1.18/SymbolMappingMessage.pcap", "cboe/c1options/complex/pitch/v2.1.18/SymbolMappingMessage.values");
    failures += check("TimeMessage", "Cboe/C1Options.Complex.Pitch.v2.1.18/TimeMessage.pcap", "cboe/c1options/complex/pitch/v2.1.18/TimeMessage.values");
    return failures == 0 ? 0 : 1;
}
