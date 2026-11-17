// Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3 canonical values, through the Advanced session layer: every value Advanced
// reads from each sample, at its address, held to what the model reads.

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
#include "cpp/binary/advanced/memx/memxequities/memoirdepthfeed/sbe/v1.3/messages/session.hpp"

namespace protocol = ::memx::memxequities::memoirdepthfeed::sbe::v1_3;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::common_header& header, const packet::Frame&) {
        values["packet.commonheader.messagetype"] = canonical::number(header.message_type.get().value());
        values["packet.commonheader.headerlength"] = canonical::number(header.header_length.get().value());
        values["packet.commonheader.sessionid"] = canonical::number(header.session_id.get().value());
        values["packet.commonheader.sequencenumber"] = canonical::number(header.sequence_number.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::common_header&) {
        ++index;
    }

    void on_message(const protocol::instrument_directory_message& message, std::uint64_t, const protocol::common_header&) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.sbeheader.blocklength"] = canonical::number(message.header.block_length.get().value());
        values[entry + ".sbemessage.sbeheader.templateid"] = canonical::number(message.header.template_id.get().value());
        values[entry + ".sbemessage.sbeheader.schemaid"] = canonical::number(message.header.schema_id.get().value());
        values[entry + ".sbemessage.sbeheader.version"] = canonical::number(message.header.version.get().value());
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.instrumentdirectorymessage";
        values[entry + ".sbemessage.payload.instrumentdirectorymessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".sbemessage.payload.instrumentdirectorymessage.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".sbemessage.payload.instrumentdirectorymessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), '\0', false);
        values[entry + ".sbemessage.payload.instrumentdirectorymessage.symbolsfx"] = canonical::text(std::string(message.fields.symbol_sfx.get().value()), '\0', false);
        values[entry + ".sbemessage.payload.instrumentdirectorymessage.roundlot"] = canonical::number(message.fields.round_lot.get().value());
        values[entry + ".sbemessage.payload.instrumentdirectorymessage.istestsymbol"] = canonical::number(message.fields.is_test_symbol.get().value());
        values[entry + ".sbemessage.payload.instrumentdirectorymessage.mpv"] = canonical::scaled(message.fields.mpv.get().value(), -6);
    }

    void on_message(const protocol::reg_sho_restriction_message& message, std::uint64_t, const protocol::common_header&) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.sbeheader.blocklength"] = canonical::number(message.header.block_length.get().value());
        values[entry + ".sbemessage.sbeheader.templateid"] = canonical::number(message.header.template_id.get().value());
        values[entry + ".sbemessage.sbeheader.schemaid"] = canonical::number(message.header.schema_id.get().value());
        values[entry + ".sbemessage.sbeheader.version"] = canonical::number(message.header.version.get().value());
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.regshorestrictionmessage";
        values[entry + ".sbemessage.payload.regshorestrictionmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".sbemessage.payload.regshorestrictionmessage.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".sbemessage.payload.regshorestrictionmessage.shortsalerestriction"] = canonical::number(message.fields.short_sale_restriction.get().value());
    }

    void on_message(const protocol::security_trading_status_message& message, std::uint64_t, const protocol::common_header&) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.sbeheader.blocklength"] = canonical::number(message.header.block_length.get().value());
        values[entry + ".sbemessage.sbeheader.templateid"] = canonical::number(message.header.template_id.get().value());
        values[entry + ".sbemessage.sbeheader.schemaid"] = canonical::number(message.header.schema_id.get().value());
        values[entry + ".sbemessage.sbeheader.version"] = canonical::number(message.header.version.get().value());
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.securitytradingstatusmessage";
        values[entry + ".sbemessage.payload.securitytradingstatusmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".sbemessage.payload.securitytradingstatusmessage.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".sbemessage.payload.securitytradingstatusmessage.securitytradingstatus"] = canonical::text(canonical::character(message.fields.security_trading_status.get().value()));
        values[entry + ".sbemessage.payload.securitytradingstatusmessage.securitytradingstatusreason"] = canonical::text(canonical::character(message.fields.security_trading_status_reason.get().value()));
    }

    void on_message(const protocol::trading_session_status_message& message, std::uint64_t, const protocol::common_header&) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.sbeheader.blocklength"] = canonical::number(message.header.block_length.get().value());
        values[entry + ".sbemessage.sbeheader.templateid"] = canonical::number(message.header.template_id.get().value());
        values[entry + ".sbemessage.sbeheader.schemaid"] = canonical::number(message.header.schema_id.get().value());
        values[entry + ".sbemessage.sbeheader.version"] = canonical::number(message.header.version.get().value());
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.tradingsessionstatusmessage";
        values[entry + ".sbemessage.payload.tradingsessionstatusmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".sbemessage.payload.tradingsessionstatusmessage.tradingsession"] = canonical::text(canonical::character(message.fields.trading_session.get().value()));
    }

    void on_message(const protocol::order_added_message& message, std::uint64_t, const protocol::common_header&) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.sbeheader.blocklength"] = canonical::number(message.header.block_length.get().value());
        values[entry + ".sbemessage.sbeheader.templateid"] = canonical::number(message.header.template_id.get().value());
        values[entry + ".sbemessage.sbeheader.schemaid"] = canonical::number(message.header.schema_id.get().value());
        values[entry + ".sbemessage.sbeheader.version"] = canonical::number(message.header.version.get().value());
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.orderaddedmessage";
        values[entry + ".sbemessage.payload.orderaddedmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".sbemessage.payload.orderaddedmessage.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".sbemessage.payload.orderaddedmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".sbemessage.payload.orderaddedmessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()));
        values[entry + ".sbemessage.payload.orderaddedmessage.quantity"] = canonical::number(message.fields.quantity.get().value());
        values[entry + ".sbemessage.payload.orderaddedmessage.price"] = canonical::scaled(message.fields.price.get().value(), -6);
    }

    void on_message(const protocol::order_deleted_message& message, std::uint64_t, const protocol::common_header&) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.sbeheader.blocklength"] = canonical::number(message.header.block_length.get().value());
        values[entry + ".sbemessage.sbeheader.templateid"] = canonical::number(message.header.template_id.get().value());
        values[entry + ".sbemessage.sbeheader.schemaid"] = canonical::number(message.header.schema_id.get().value());
        values[entry + ".sbemessage.sbeheader.version"] = canonical::number(message.header.version.get().value());
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.orderdeletedmessage";
        values[entry + ".sbemessage.payload.orderdeletedmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".sbemessage.payload.orderdeletedmessage.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".sbemessage.payload.orderdeletedmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
    }

    void on_message(const protocol::order_reduced_message& message, std::uint64_t, const protocol::common_header&) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.sbeheader.blocklength"] = canonical::number(message.header.block_length.get().value());
        values[entry + ".sbemessage.sbeheader.templateid"] = canonical::number(message.header.template_id.get().value());
        values[entry + ".sbemessage.sbeheader.schemaid"] = canonical::number(message.header.schema_id.get().value());
        values[entry + ".sbemessage.sbeheader.version"] = canonical::number(message.header.version.get().value());
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.orderreducedmessage";
        values[entry + ".sbemessage.payload.orderreducedmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".sbemessage.payload.orderreducedmessage.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".sbemessage.payload.orderreducedmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".sbemessage.payload.orderreducedmessage.quantity"] = canonical::number(message.fields.quantity.get().value());
    }

    void on_message(const protocol::order_executed_message& message, std::uint64_t, const protocol::common_header&) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.sbeheader.blocklength"] = canonical::number(message.header.block_length.get().value());
        values[entry + ".sbemessage.sbeheader.templateid"] = canonical::number(message.header.template_id.get().value());
        values[entry + ".sbemessage.sbeheader.schemaid"] = canonical::number(message.header.schema_id.get().value());
        values[entry + ".sbemessage.sbeheader.version"] = canonical::number(message.header.version.get().value());
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.orderexecutedmessage";
        values[entry + ".sbemessage.payload.orderexecutedmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".sbemessage.payload.orderexecutedmessage.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".sbemessage.payload.orderexecutedmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".sbemessage.payload.orderexecutedmessage.tradeid"] = canonical::number(message.fields.trade_id.get().value());
        values[entry + ".sbemessage.payload.orderexecutedmessage.quantity"] = canonical::number(message.fields.quantity.get().value());
        values[entry + ".sbemessage.payload.orderexecutedmessage.price"] = canonical::scaled(message.fields.price.get().value(), -6);
    }

    void on_message(const protocol::trade_message& message, std::uint64_t, const protocol::common_header&) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.sbeheader.blocklength"] = canonical::number(message.header.block_length.get().value());
        values[entry + ".sbemessage.sbeheader.templateid"] = canonical::number(message.header.template_id.get().value());
        values[entry + ".sbemessage.sbeheader.schemaid"] = canonical::number(message.header.schema_id.get().value());
        values[entry + ".sbemessage.sbeheader.version"] = canonical::number(message.header.version.get().value());
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.trademessage";
        values[entry + ".sbemessage.payload.trademessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".sbemessage.payload.trademessage.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".sbemessage.payload.trademessage.tradeid"] = canonical::number(message.fields.trade_id.get().value());
        values[entry + ".sbemessage.payload.trademessage.quantity"] = canonical::number(message.fields.quantity.get().value());
        values[entry + ".sbemessage.payload.trademessage.price"] = canonical::scaled(message.fields.price.get().value(), -6);
    }

    void on_message(const protocol::broken_trade_message& message, std::uint64_t, const protocol::common_header&) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.sbeheader.blocklength"] = canonical::number(message.header.block_length.get().value());
        values[entry + ".sbemessage.sbeheader.templateid"] = canonical::number(message.header.template_id.get().value());
        values[entry + ".sbemessage.sbeheader.schemaid"] = canonical::number(message.header.schema_id.get().value());
        values[entry + ".sbemessage.sbeheader.version"] = canonical::number(message.header.version.get().value());
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.brokentrademessage";
        values[entry + ".sbemessage.payload.brokentrademessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".sbemessage.payload.brokentrademessage.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".sbemessage.payload.brokentrademessage.tradeid"] = canonical::number(message.fields.trade_id.get().value());
        values[entry + ".sbemessage.payload.brokentrademessage.originalquantity"] = canonical::number(message.fields.original_quantity.get().value());
        values[entry + ".sbemessage.payload.brokentrademessage.originalprice"] = canonical::scaled(message.fields.original_price.get().value(), -6);
    }

    void on_message(const protocol::corrected_trade_message& message, std::uint64_t, const protocol::common_header&) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.sbeheader.blocklength"] = canonical::number(message.header.block_length.get().value());
        values[entry + ".sbemessage.sbeheader.templateid"] = canonical::number(message.header.template_id.get().value());
        values[entry + ".sbemessage.sbeheader.schemaid"] = canonical::number(message.header.schema_id.get().value());
        values[entry + ".sbemessage.sbeheader.version"] = canonical::number(message.header.version.get().value());
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.correctedtrademessage";
        values[entry + ".sbemessage.payload.correctedtrademessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".sbemessage.payload.correctedtrademessage.securityid"] = canonical::number(message.fields.security_id.get().value());
        values[entry + ".sbemessage.payload.correctedtrademessage.tradeid"] = canonical::number(message.fields.trade_id.get().value());
        values[entry + ".sbemessage.payload.correctedtrademessage.originalquantity"] = canonical::number(message.fields.original_quantity.get().value());
        values[entry + ".sbemessage.payload.correctedtrademessage.originalprice"] = canonical::scaled(message.fields.original_price.get().value(), -6);
        values[entry + ".sbemessage.payload.correctedtrademessage.correctedquantity"] = canonical::number(message.fields.corrected_quantity.get().value());
        values[entry + ".sbemessage.payload.correctedtrademessage.correctedprice"] = canonical::scaled(message.fields.corrected_price.get().value(), -6);
    }

    void on_message(const protocol::clear_book_message& message, std::uint64_t, const protocol::common_header&) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.sbeheader.blocklength"] = canonical::number(message.header.block_length.get().value());
        values[entry + ".sbemessage.sbeheader.templateid"] = canonical::number(message.header.template_id.get().value());
        values[entry + ".sbemessage.sbeheader.schemaid"] = canonical::number(message.header.schema_id.get().value());
        values[entry + ".sbemessage.sbeheader.version"] = canonical::number(message.header.version.get().value());
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.clearbookmessage";
        values[entry + ".sbemessage.payload.clearbookmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".sbemessage.payload.clearbookmessage.securityid"] = canonical::number(message.fields.security_id.get().value());
    }

    void on_message(const protocol::snapshot_complete_message& message, std::uint64_t, const protocol::common_header&) {
        const std::string entry = "packet.sequencedmessages.sequencedmessage.message[" + std::to_string(index++) + "]";
        values[entry + ".sbemessage.sbeheader.blocklength"] = canonical::number(message.header.block_length.get().value());
        values[entry + ".sbemessage.sbeheader.templateid"] = canonical::number(message.header.template_id.get().value());
        values[entry + ".sbemessage.sbeheader.schemaid"] = canonical::number(message.header.schema_id.get().value());
        values[entry + ".sbemessage.sbeheader.version"] = canonical::number(message.header.version.get().value());
        values[entry + ".sbemessage.payload"] = "packet.sequencedmessages.sequencedmessage.message.sbemessage.payload.snapshotcompletemessage";
        values[entry + ".sbemessage.payload.snapshotcompletemessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".sbemessage.payload.snapshotcompletemessage.asofsequencenumber"] = canonical::number(message.fields.as_of_sequence_number.get().value());
    }
};

// The values Advanced reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    Reader reader;
    protocol::process_segment(reader, frame.payload, frame.payload_len, 0, frame);
    return reader.values;
}

// Read each datagram of a sample with Advanced and hold it to the model's values
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
    std::printf("== Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3 (advanced values)\n");
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
