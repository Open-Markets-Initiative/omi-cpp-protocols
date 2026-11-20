// Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3 canonical values, through the Flyweight reader: every value Flyweight reads
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
#include "cpp/binary/flyweight/memx/memxequities/memoirdepthfeed/sbe/v1.3/definitions.hpp"

namespace protocol = ::memx::memxequities::memoirdepthfeed::sbe::v1_3;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        values["packet.commonheader.messagetype"] = canonical::number(packet.common_header().message_type());
        values["packet.commonheader.headerlength"] = canonical::number(packet.common_header().header_length());
        values["packet.commonheader.sessionid"] = canonical::number(packet.common_header().session_id());
        values["packet.commonheader.sequencenumber"] = canonical::number(packet.common_header().sequence_number());
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

    void on(const protocol::InstrumentDirectoryMessage& message) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.instrumentdirectorymessage";
        values[entry + ".sbemessage.payload.instrumentdirectorymessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".sbemessage.payload.instrumentdirectorymessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".sbemessage.payload.instrumentdirectorymessage.symbol"] = canonical::text(std::string(message.symbol()), '\0', false);
        values[entry + ".sbemessage.payload.instrumentdirectorymessage.symbolsfx"] = canonical::text(std::string(message.symbol_sfx()), '\0', false);
        values[entry + ".sbemessage.payload.instrumentdirectorymessage.roundlot"] = canonical::number(message.round_lot());
        values[entry + ".sbemessage.payload.instrumentdirectorymessage.istestsymbol"] = canonical::number(message.is_test_symbol());
        values[entry + ".sbemessage.payload.instrumentdirectorymessage.mpv"] = canonical::scaled(message.mpv().mantissa(), message.mpv().exponent());
    }

    void on(const protocol::RegShoRestrictionMessage& message) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.regshorestrictionmessage";
        values[entry + ".sbemessage.payload.regshorestrictionmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".sbemessage.payload.regshorestrictionmessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".sbemessage.payload.regshorestrictionmessage.shortsalerestriction"] = canonical::number(message.short_sale_restriction());
    }

    void on(const protocol::SecurityTradingStatusMessage& message) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.securitytradingstatusmessage";
        values[entry + ".sbemessage.payload.securitytradingstatusmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".sbemessage.payload.securitytradingstatusmessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".sbemessage.payload.securitytradingstatusmessage.securitytradingstatus"] = canonical::text(canonical::character(message.security_trading_status()));
        values[entry + ".sbemessage.payload.securitytradingstatusmessage.securitytradingstatusreason"] = canonical::text(canonical::character(message.security_trading_status_reason()));
    }

    void on(const protocol::TradingSessionStatusMessage& message) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.tradingsessionstatusmessage";
        values[entry + ".sbemessage.payload.tradingsessionstatusmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".sbemessage.payload.tradingsessionstatusmessage.tradingsession"] = canonical::text(canonical::character(message.trading_session()));
    }

    void on(const protocol::OrderAddedMessage& message) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.orderaddedmessage";
        values[entry + ".sbemessage.payload.orderaddedmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".sbemessage.payload.orderaddedmessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".sbemessage.payload.orderaddedmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".sbemessage.payload.orderaddedmessage.side"] = canonical::text(canonical::character(message.side()));
        values[entry + ".sbemessage.payload.orderaddedmessage.quantity"] = canonical::number(message.quantity());
        values[entry + ".sbemessage.payload.orderaddedmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
    }

    void on(const protocol::OrderDeletedMessage& message) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.orderdeletedmessage";
        values[entry + ".sbemessage.payload.orderdeletedmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".sbemessage.payload.orderdeletedmessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".sbemessage.payload.orderdeletedmessage.orderid"] = canonical::number(message.order_id());
    }

    void on(const protocol::OrderReducedMessage& message) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.orderreducedmessage";
        values[entry + ".sbemessage.payload.orderreducedmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".sbemessage.payload.orderreducedmessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".sbemessage.payload.orderreducedmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".sbemessage.payload.orderreducedmessage.quantity"] = canonical::number(message.quantity());
    }

    void on(const protocol::OrderExecutedMessage& message) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.orderexecutedmessage";
        values[entry + ".sbemessage.payload.orderexecutedmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".sbemessage.payload.orderexecutedmessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".sbemessage.payload.orderexecutedmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".sbemessage.payload.orderexecutedmessage.tradeid"] = canonical::number(message.trade_id());
        values[entry + ".sbemessage.payload.orderexecutedmessage.quantity"] = canonical::number(message.quantity());
        values[entry + ".sbemessage.payload.orderexecutedmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
    }

    void on(const protocol::TradeMessage& message) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.trademessage";
        values[entry + ".sbemessage.payload.trademessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".sbemessage.payload.trademessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".sbemessage.payload.trademessage.tradeid"] = canonical::number(message.trade_id());
        values[entry + ".sbemessage.payload.trademessage.quantity"] = canonical::number(message.quantity());
        values[entry + ".sbemessage.payload.trademessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
    }

    void on(const protocol::BrokenTradeMessage& message) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.brokentrademessage";
        values[entry + ".sbemessage.payload.brokentrademessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".sbemessage.payload.brokentrademessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".sbemessage.payload.brokentrademessage.tradeid"] = canonical::number(message.trade_id());
        values[entry + ".sbemessage.payload.brokentrademessage.originalquantity"] = canonical::number(message.original_quantity());
        values[entry + ".sbemessage.payload.brokentrademessage.originalprice"] = canonical::scaled(message.original_price().mantissa(), message.original_price().exponent());
    }

    void on(const protocol::CorrectedTradeMessage& message) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.correctedtrademessage";
        values[entry + ".sbemessage.payload.correctedtrademessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".sbemessage.payload.correctedtrademessage.securityid"] = canonical::number(message.security_id());
        values[entry + ".sbemessage.payload.correctedtrademessage.tradeid"] = canonical::number(message.trade_id());
        values[entry + ".sbemessage.payload.correctedtrademessage.originalquantity"] = canonical::number(message.original_quantity());
        values[entry + ".sbemessage.payload.correctedtrademessage.originalprice"] = canonical::scaled(message.original_price().mantissa(), message.original_price().exponent());
        values[entry + ".sbemessage.payload.correctedtrademessage.correctedquantity"] = canonical::number(message.corrected_quantity());
        values[entry + ".sbemessage.payload.correctedtrademessage.correctedprice"] = canonical::scaled(message.corrected_price().mantissa(), message.corrected_price().exponent());
    }

    void on(const protocol::ClearBookMessage& message) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.clearbookmessage";
        values[entry + ".sbemessage.payload.clearbookmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".sbemessage.payload.clearbookmessage.securityid"] = canonical::number(message.security_id());
    }

    void on(const protocol::SnapshotCompleteMessage& message) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.snapshotcompletemessage";
        values[entry + ".sbemessage.payload.snapshotcompletemessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".sbemessage.payload.snapshotcompletemessage.asofsequencenumber"] = canonical::number(message.as_of_sequence_number());
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
    std::printf("== Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3 (flyweight values)\n");
    int failures = 0;
    failures += check("Heartbeat", "Memx/MemxEquities.MemoirDepthFeed.Sbe.v1.3/Heartbeat.pcap", "memx/memxequities/memoirdepthfeed/sbe/v1.3/Heartbeat.values");
    failures += check("InstrumentDirectoryMessage", "Memx/MemxEquities.MemoirDepthFeed.Sbe.v1.3/InstrumentDirectoryMessage.pcap", "memx/memxequities/memoirdepthfeed/sbe/v1.3/InstrumentDirectoryMessage.values");
    failures += check("OrderAddedMessage", "Memx/MemxEquities.MemoirDepthFeed.Sbe.v1.3/OrderAddedMessage.pcap", "memx/memxequities/memoirdepthfeed/sbe/v1.3/OrderAddedMessage.values");
    failures += check("OrderDeletedMessage", "Memx/MemxEquities.MemoirDepthFeed.Sbe.v1.3/OrderDeletedMessage.pcap", "memx/memxequities/memoirdepthfeed/sbe/v1.3/OrderDeletedMessage.values");
    failures += check("OrderExecutedMessage", "Memx/MemxEquities.MemoirDepthFeed.Sbe.v1.3/OrderExecutedMessage.pcap", "memx/memxequities/memoirdepthfeed/sbe/v1.3/OrderExecutedMessage.values");
    failures += check("OrderReducedMessage", "Memx/MemxEquities.MemoirDepthFeed.Sbe.v1.3/OrderReducedMessage.pcap", "memx/memxequities/memoirdepthfeed/sbe/v1.3/OrderReducedMessage.values");
    failures += check("RegShoRestrictionMessage", "Memx/MemxEquities.MemoirDepthFeed.Sbe.v1.3/RegShoRestrictionMessage.pcap", "memx/memxequities/memoirdepthfeed/sbe/v1.3/RegShoRestrictionMessage.values");
    failures += check("SecurityTradingStatusMessage", "Memx/MemxEquities.MemoirDepthFeed.Sbe.v1.3/SecurityTradingStatusMessage.pcap", "memx/memxequities/memoirdepthfeed/sbe/v1.3/SecurityTradingStatusMessage.values");
    failures += check("SessionShutdown", "Memx/MemxEquities.MemoirDepthFeed.Sbe.v1.3/SessionShutdown.pcap", "memx/memxequities/memoirdepthfeed/sbe/v1.3/SessionShutdown.values");
    failures += check("TradeMessage", "Memx/MemxEquities.MemoirDepthFeed.Sbe.v1.3/TradeMessage.pcap", "memx/memxequities/memoirdepthfeed/sbe/v1.3/TradeMessage.values");
    failures += check("TradingSessionStatusMessage", "Memx/MemxEquities.MemoirDepthFeed.Sbe.v1.3/TradingSessionStatusMessage.pcap", "memx/memxequities/memoirdepthfeed/sbe/v1.3/TradingSessionStatusMessage.values");
    return failures == 0 ? 0 : 1;
}
