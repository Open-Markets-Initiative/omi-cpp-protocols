// Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3 canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/memx/memxequities/memoirdepthfeed/sbe/v1.3/definitions.hpp"

namespace protocol = ::memx::memxequities::memoirdepthfeed::sbe::v1_3;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    if (iterator.sequenced_message != nullptr) {
        values["packet.sequencedmessages.sequencedmessage.messagecount"] = canonical::number(iterator.sequenced_message->message_count.get());
    }

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".messagelength"] = canonical::number(iterator.message_header->message_length.get());

        if (iterator.template_id == 1) {
            values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.instrumentdirectorymessage";
            [[maybe_unused]] const auto* message = protocol::InstrumentDirectoryMessage::parse(iterator.message);
            values[entry + ".sbemessage.payload.instrumentdirectorymessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".sbemessage.payload.instrumentdirectorymessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".sbemessage.payload.instrumentdirectorymessage.symbol"] = canonical::text(std::string(message->symbol.get()), '\0', false);
            values[entry + ".sbemessage.payload.instrumentdirectorymessage.symbolsfx"] = canonical::text(std::string(message->symbol_sfx.get()), '\0', false);
            values[entry + ".sbemessage.payload.instrumentdirectorymessage.roundlot"] = canonical::number(message->round_lot.get());
            values[entry + ".sbemessage.payload.instrumentdirectorymessage.istestsymbol"] = canonical::number(message->is_test_symbol.get());
            values[entry + ".sbemessage.payload.instrumentdirectorymessage.mpv"] = canonical::scaled(message->mpv.integer(), -6);
        } else if (iterator.template_id == 2) {
            values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.regshorestrictionmessage";
            [[maybe_unused]] const auto* message = protocol::RegShoRestrictionMessage::parse(iterator.message);
            values[entry + ".sbemessage.payload.regshorestrictionmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".sbemessage.payload.regshorestrictionmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".sbemessage.payload.regshorestrictionmessage.shortsalerestriction"] = canonical::number(message->short_sale_restriction.get());
        } else if (iterator.template_id == 3) {
            values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.securitytradingstatusmessage";
            [[maybe_unused]] const auto* message = protocol::SecurityTradingStatusMessage::parse(iterator.message);
            values[entry + ".sbemessage.payload.securitytradingstatusmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".sbemessage.payload.securitytradingstatusmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".sbemessage.payload.securitytradingstatusmessage.securitytradingstatus"] = canonical::text(canonical::character(message->security_trading_status.get()));
            values[entry + ".sbemessage.payload.securitytradingstatusmessage.securitytradingstatusreason"] = canonical::text(canonical::character(message->security_trading_status_reason.get()));
        } else if (iterator.template_id == 5) {
            values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.tradingsessionstatusmessage";
            [[maybe_unused]] const auto* message = protocol::TradingSessionStatusMessage::parse(iterator.message);
            values[entry + ".sbemessage.payload.tradingsessionstatusmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".sbemessage.payload.tradingsessionstatusmessage.tradingsession"] = canonical::text(canonical::character(message->trading_session.get()));
        } else if (iterator.template_id == 10) {
            values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.orderaddedmessage";
            [[maybe_unused]] const auto* message = protocol::OrderAddedMessage::parse(iterator.message);
            values[entry + ".sbemessage.payload.orderaddedmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".sbemessage.payload.orderaddedmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".sbemessage.payload.orderaddedmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".sbemessage.payload.orderaddedmessage.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".sbemessage.payload.orderaddedmessage.quantity"] = canonical::number(message->quantity.get());
            values[entry + ".sbemessage.payload.orderaddedmessage.price"] = canonical::scaled(message->price.integer(), -6);
        } else if (iterator.template_id == 11) {
            values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.orderdeletedmessage";
            [[maybe_unused]] const auto* message = protocol::OrderDeletedMessage::parse(iterator.message);
            values[entry + ".sbemessage.payload.orderdeletedmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".sbemessage.payload.orderdeletedmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".sbemessage.payload.orderdeletedmessage.orderid"] = canonical::number(message->order_id.get());
        } else if (iterator.template_id == 12) {
            values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.orderreducedmessage";
            [[maybe_unused]] const auto* message = protocol::OrderReducedMessage::parse(iterator.message);
            values[entry + ".sbemessage.payload.orderreducedmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".sbemessage.payload.orderreducedmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".sbemessage.payload.orderreducedmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".sbemessage.payload.orderreducedmessage.quantity"] = canonical::number(message->quantity.get());
        } else if (iterator.template_id == 13) {
            values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.orderexecutedmessage";
            [[maybe_unused]] const auto* message = protocol::OrderExecutedMessage::parse(iterator.message);
            values[entry + ".sbemessage.payload.orderexecutedmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".sbemessage.payload.orderexecutedmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".sbemessage.payload.orderexecutedmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".sbemessage.payload.orderexecutedmessage.tradeid"] = canonical::number(message->trade_id.get());
            values[entry + ".sbemessage.payload.orderexecutedmessage.quantity"] = canonical::number(message->quantity.get());
            values[entry + ".sbemessage.payload.orderexecutedmessage.price"] = canonical::scaled(message->price.integer(), -6);
        } else if (iterator.template_id == 14) {
            values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.trademessage";
            [[maybe_unused]] const auto* message = protocol::TradeMessage::parse(iterator.message);
            values[entry + ".sbemessage.payload.trademessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".sbemessage.payload.trademessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".sbemessage.payload.trademessage.tradeid"] = canonical::number(message->trade_id.get());
            values[entry + ".sbemessage.payload.trademessage.quantity"] = canonical::number(message->quantity.get());
            values[entry + ".sbemessage.payload.trademessage.price"] = canonical::scaled(message->price.integer(), -6);
        } else if (iterator.template_id == 15) {
            values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.brokentrademessage";
            [[maybe_unused]] const auto* message = protocol::BrokenTradeMessage::parse(iterator.message);
            values[entry + ".sbemessage.payload.brokentrademessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".sbemessage.payload.brokentrademessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".sbemessage.payload.brokentrademessage.tradeid"] = canonical::number(message->trade_id.get());
            values[entry + ".sbemessage.payload.brokentrademessage.originalquantity"] = canonical::number(message->original_quantity.get());
            values[entry + ".sbemessage.payload.brokentrademessage.originalprice"] = canonical::scaled(message->original_price.integer(), -6);
        } else if (iterator.template_id == 16) {
            values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.correctedtrademessage";
            [[maybe_unused]] const auto* message = protocol::CorrectedTradeMessage::parse(iterator.message);
            values[entry + ".sbemessage.payload.correctedtrademessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".sbemessage.payload.correctedtrademessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".sbemessage.payload.correctedtrademessage.tradeid"] = canonical::number(message->trade_id.get());
            values[entry + ".sbemessage.payload.correctedtrademessage.originalquantity"] = canonical::number(message->original_quantity.get());
            values[entry + ".sbemessage.payload.correctedtrademessage.originalprice"] = canonical::scaled(message->original_price.integer(), -6);
            values[entry + ".sbemessage.payload.correctedtrademessage.correctedquantity"] = canonical::number(message->corrected_quantity.get());
            values[entry + ".sbemessage.payload.correctedtrademessage.correctedprice"] = canonical::scaled(message->corrected_price.integer(), -6);
        } else if (iterator.template_id == 18) {
            values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.clearbookmessage";
            [[maybe_unused]] const auto* message = protocol::ClearBookMessage::parse(iterator.message);
            values[entry + ".sbemessage.payload.clearbookmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".sbemessage.payload.clearbookmessage.securityid"] = canonical::number(message->security_id.get());
        } else if (iterator.template_id == 100) {
            values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.snapshotcompletemessage";
            [[maybe_unused]] const auto* message = protocol::SnapshotCompleteMessage::parse(iterator.message);
            values[entry + ".sbemessage.payload.snapshotcompletemessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".sbemessage.payload.snapshotcompletemessage.asofsequencenumber"] = canonical::number(message->as_of_sequence_number.get());
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
    std::printf("== Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3 (modern values)\n");
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
