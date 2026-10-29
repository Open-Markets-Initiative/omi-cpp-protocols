// Cboe.EdgxEquities.MulticastDepthOfBook.Pitch.v2.41.29 canonical values, through the Flyweight reader: every value Flyweight reads
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
#include "cpp/binary/flyweight/cboe/edgxequities/multicastdepthofbook/pitch/v2.41.29/definitions.hpp"

namespace protocol = ::cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29;

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

    void on(const protocol::AddOrderLongMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.addorderlongmessage";
        values[entry + ".payload.addorderlongmessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.addorderlongmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.addorderlongmessage.sideindicator"] = canonical::text(canonical::character(message.side_indicator()), ' ', false);
        values[entry + ".payload.addorderlongmessage.quantity"] = canonical::number(message.quantity());
        values[entry + ".payload.addorderlongmessage.symbolshort"] = canonical::text(std::string(message.symbol_short()), ' ', false);
        values[entry + ".payload.addorderlongmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.addorderlongmessage.addorderflags.display"] = canonical::number(static_cast<std::uint64_t>(message.add_order_flags().display()));
    }

    void on(const protocol::AddOrderShortMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.addordershortmessage";
        values[entry + ".payload.addordershortmessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.addordershortmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.addordershortmessage.sideindicator"] = canonical::text(canonical::character(message.side_indicator()), ' ', false);
        values[entry + ".payload.addordershortmessage.quantityshort"] = canonical::number(message.quantity_short());
        values[entry + ".payload.addordershortmessage.symbolshort"] = canonical::text(std::string(message.symbol_short()), ' ', false);
        values[entry + ".payload.addordershortmessage.priceshort"] = canonical::scaled(message.price_short().mantissa(), message.price_short().exponent());
        values[entry + ".payload.addordershortmessage.addorderflags.display"] = canonical::number(static_cast<std::uint64_t>(message.add_order_flags().display()));
    }

    void on(const protocol::AddOrderExpandedMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.addorderexpandedmessage";
        values[entry + ".payload.addorderexpandedmessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.addorderexpandedmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.addorderexpandedmessage.sideindicator"] = canonical::text(canonical::character(message.side_indicator()), ' ', false);
        values[entry + ".payload.addorderexpandedmessage.quantity"] = canonical::number(message.quantity());
        values[entry + ".payload.addorderexpandedmessage.symbollong"] = canonical::text(std::string(message.symbol_long()), ' ', false);
        values[entry + ".payload.addorderexpandedmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.addorderexpandedmessage.addorderflags.display"] = canonical::number(static_cast<std::uint64_t>(message.add_order_flags().display()));
        values[entry + ".payload.addorderexpandedmessage.participantid"] = canonical::text(std::string(message.participant_id()), ' ', false);
        values[entry + ".payload.addorderexpandedmessage.customerindicator"] = canonical::text(canonical::character(message.customer_indicator()), ' ', false);
    }

    void on(const protocol::OrderExecutedMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedmessage";
        values[entry + ".payload.orderexecutedmessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.orderexecutedmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.orderexecutedmessage.executedquantity"] = canonical::number(message.executed_quantity());
        values[entry + ".payload.orderexecutedmessage.executionid"] = canonical::number(message.execution_id());
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
        values[entry + ".payload.modifyorderlongmessage.modifyorderflags.display"] = canonical::number(static_cast<std::uint64_t>(message.modify_order_flags().display()));
        values[entry + ".payload.modifyorderlongmessage.modifyorderflags.priority"] = canonical::number(static_cast<std::uint64_t>(message.modify_order_flags().priority()));
    }

    void on(const protocol::ModifyOrderShortMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.modifyordershortmessage";
        values[entry + ".payload.modifyordershortmessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.modifyordershortmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.modifyordershortmessage.quantityshort"] = canonical::number(message.quantity_short());
        values[entry + ".payload.modifyordershortmessage.priceshort"] = canonical::scaled(message.price_short().mantissa(), message.price_short().exponent());
        values[entry + ".payload.modifyordershortmessage.modifyorderflags.display"] = canonical::number(static_cast<std::uint64_t>(message.modify_order_flags().display()));
        values[entry + ".payload.modifyordershortmessage.modifyorderflags.priority"] = canonical::number(static_cast<std::uint64_t>(message.modify_order_flags().priority()));
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
        values[entry + ".payload.tradelongmessage.symbolshort"] = canonical::text(std::string(message.symbol_short()), ' ', false);
        values[entry + ".payload.tradelongmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.tradelongmessage.executionid"] = canonical::number(message.execution_id());
    }

    void on(const protocol::TradeShortMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.tradeshortmessage";
        values[entry + ".payload.tradeshortmessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.tradeshortmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.tradeshortmessage.sideindicator"] = canonical::text(canonical::character(message.side_indicator()), ' ', false);
        values[entry + ".payload.tradeshortmessage.quantityshort"] = canonical::number(message.quantity_short());
        values[entry + ".payload.tradeshortmessage.symbolshort"] = canonical::text(std::string(message.symbol_short()), ' ', false);
        values[entry + ".payload.tradeshortmessage.priceshort"] = canonical::scaled(message.price_short().mantissa(), message.price_short().exponent());
        values[entry + ".payload.tradeshortmessage.executionid"] = canonical::number(message.execution_id());
    }

    void on(const protocol::TradeExpandedMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.tradeexpandedmessage";
        values[entry + ".payload.tradeexpandedmessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.tradeexpandedmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.tradeexpandedmessage.sideindicator"] = canonical::text(canonical::character(message.side_indicator()), ' ', false);
        values[entry + ".payload.tradeexpandedmessage.quantity"] = canonical::number(message.quantity());
        values[entry + ".payload.tradeexpandedmessage.symbollong"] = canonical::text(std::string(message.symbol_long()), ' ', false);
        values[entry + ".payload.tradeexpandedmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.tradeexpandedmessage.executionid"] = canonical::number(message.execution_id());
    }

    void on(const protocol::TradeBreakMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.tradebreakmessage";
        values[entry + ".payload.tradebreakmessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.tradebreakmessage.executionid"] = canonical::number(message.execution_id());
    }

    void on(const protocol::EndOfSession& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.endofsession";
        values[entry + ".payload.endofsession.lasttimestamp"] = canonical::number(message.last_timestamp());
    }

    void on(const protocol::TradingStatusMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.tradingstatusmessage";
        values[entry + ".payload.tradingstatusmessage.timeoffset"] = canonical::number(message.time_offset());
        values[entry + ".payload.tradingstatusmessage.symbollong"] = canonical::text(std::string(message.symbol_long()), ' ', false);
        values[entry + ".payload.tradingstatusmessage.tradingstatus"] = canonical::text(canonical::character(message.trading_status()), ' ', false);
        values[entry + ".payload.tradingstatusmessage.regshoaction"] = canonical::text(canonical::character(message.reg_sho_action()), ' ', false);
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
    std::printf("== Cboe.EdgxEquities.MulticastDepthOfBook.Pitch.v2.41.29 (flyweight values)\n");
    int failures = 0;
    failures += check("AddOrderExpandedMessage", "Cboe/EdgxEquities.MulticastDepthOfBook.Pitch.v2.41.29/AddOrderExpandedMessage.pcap", "cboe/edgxequities/multicastdepthofbook/pitch/v2.41.29/AddOrderExpandedMessage.values");
    failures += check("AddOrderLongMessage", "Cboe/EdgxEquities.MulticastDepthOfBook.Pitch.v2.41.29/AddOrderLongMessage.pcap", "cboe/edgxequities/multicastdepthofbook/pitch/v2.41.29/AddOrderLongMessage.values");
    failures += check("AddOrderShortMessage", "Cboe/EdgxEquities.MulticastDepthOfBook.Pitch.v2.41.29/AddOrderShortMessage.pcap", "cboe/edgxequities/multicastdepthofbook/pitch/v2.41.29/AddOrderShortMessage.values");
    failures += check("DeleteOrderMessage", "Cboe/EdgxEquities.MulticastDepthOfBook.Pitch.v2.41.29/DeleteOrderMessage.pcap", "cboe/edgxequities/multicastdepthofbook/pitch/v2.41.29/DeleteOrderMessage.values");
    failures += check("ModifyOrderLongMessage", "Cboe/EdgxEquities.MulticastDepthOfBook.Pitch.v2.41.29/ModifyOrderLongMessage.pcap", "cboe/edgxequities/multicastdepthofbook/pitch/v2.41.29/ModifyOrderLongMessage.values");
    failures += check("ModifyOrderShortMessage", "Cboe/EdgxEquities.MulticastDepthOfBook.Pitch.v2.41.29/ModifyOrderShortMessage.pcap", "cboe/edgxequities/multicastdepthofbook/pitch/v2.41.29/ModifyOrderShortMessage.values");
    failures += check("OrderExecutedAtPriceSizeMessage", "Cboe/EdgxEquities.MulticastDepthOfBook.Pitch.v2.41.29/OrderExecutedAtPriceSizeMessage.pcap", "cboe/edgxequities/multicastdepthofbook/pitch/v2.41.29/OrderExecutedAtPriceSizeMessage.values");
    failures += check("OrderExecutedMessage", "Cboe/EdgxEquities.MulticastDepthOfBook.Pitch.v2.41.29/OrderExecutedMessage.pcap", "cboe/edgxequities/multicastdepthofbook/pitch/v2.41.29/OrderExecutedMessage.values");
    failures += check("ReduceSizeShortMessage", "Cboe/EdgxEquities.MulticastDepthOfBook.Pitch.v2.41.29/ReduceSizeShortMessage.pcap", "cboe/edgxequities/multicastdepthofbook/pitch/v2.41.29/ReduceSizeShortMessage.values");
    failures += check("TimeMessage", "Cboe/EdgxEquities.MulticastDepthOfBook.Pitch.v2.41.29/TimeMessage.pcap", "cboe/edgxequities/multicastdepthofbook/pitch/v2.41.29/TimeMessage.values");
    failures += check("TradeLongMessage", "Cboe/EdgxEquities.MulticastDepthOfBook.Pitch.v2.41.29/TradeLongMessage.pcap", "cboe/edgxequities/multicastdepthofbook/pitch/v2.41.29/TradeLongMessage.values");
    failures += check("TradeShortMessage", "Cboe/EdgxEquities.MulticastDepthOfBook.Pitch.v2.41.29/TradeShortMessage.pcap", "cboe/edgxequities/multicastdepthofbook/pitch/v2.41.29/TradeShortMessage.values");
    failures += check("TradingStatusMessage", "Cboe/EdgxEquities.MulticastDepthOfBook.Pitch.v2.41.29/TradingStatusMessage.pcap", "cboe/edgxequities/multicastdepthofbook/pitch/v2.41.29/TradingStatusMessage.values");
    return failures == 0 ? 0 : 1;
}
