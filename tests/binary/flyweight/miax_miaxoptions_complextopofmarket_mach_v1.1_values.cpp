// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1 canonical values, through the Flyweight reader: every value Flyweight reads
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
#include "cpp/binary/flyweight/miax/miaxoptions/complextopofmarket/mach/v1.1/definitions.hpp"

namespace protocol = ::miax::miaxoptions::complextopofmarket::mach::v1_1;

namespace {

// The messages Data selects, their values set in the entry of the message holding it
struct DataHandler {
    canonical::Listing& values;
    const std::string& entry;

    void on(const protocol::SystemTimeMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.systemtimemessage";
        values[entry + ".payload.applicationmessage.data.systemtimemessage.seconds"] = canonical::number(message.seconds());
    }

    void on(const protocol::SeriesUpdate& message) {
        values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.seriesupdate";
        values[entry + ".payload.applicationmessage.data.seriesupdate.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".payload.applicationmessage.data.seriesupdate.productid"] = canonical::number(message.product_id());
        values[entry + ".payload.applicationmessage.data.seriesupdate.underlyingsymbol"] = canonical::text(std::string(message.underlying_symbol()), ' ', false);
        values[entry + ".payload.applicationmessage.data.seriesupdate.securitysymbol"] = canonical::text(std::string(message.security_symbol()), ' ', false);
        values[entry + ".payload.applicationmessage.data.seriesupdate.expirationdate"] = canonical::text(std::string(message.expiration_date()), ' ', false);
        values[entry + ".payload.applicationmessage.data.seriesupdate.strikeprice"] = canonical::scaled(message.strike_price().mantissa(), message.strike_price().exponent());
        values[entry + ".payload.applicationmessage.data.seriesupdate.callorput"] = canonical::text(canonical::character(message.call_or_put()), ' ', false);
        values[entry + ".payload.applicationmessage.data.seriesupdate.openingtime"] = canonical::text(std::string(message.opening_time()), ' ', false);
        values[entry + ".payload.applicationmessage.data.seriesupdate.closingtime"] = canonical::text(std::string(message.closing_time()), ' ', false);
        values[entry + ".payload.applicationmessage.data.seriesupdate.restrictedoption"] = canonical::text(canonical::character(message.restricted_option()), ' ', false);
        values[entry + ".payload.applicationmessage.data.seriesupdate.longtermoption"] = canonical::text(canonical::character(message.long_term_option()), ' ', false);
        values[entry + ".payload.applicationmessage.data.seriesupdate.activeonmiax"] = canonical::text(canonical::character(message.active_on_miax()), ' ', false);
        values[entry + ".payload.applicationmessage.data.seriesupdate.miaxbbopostingincrementindicator"] = canonical::text(canonical::character(message.miax_bbo_posting_increment_indicator()), ' ', false);
        values[entry + ".payload.applicationmessage.data.seriesupdate.liquidityacceptanceincrementindicator"] = canonical::text(canonical::character(message.liquidity_acceptance_increment_indicator()), ' ', false);
        values[entry + ".payload.applicationmessage.data.seriesupdate.openingunderlyingmarketcode"] = canonical::text(canonical::character(message.opening_underlying_market_code()), ' ', false);
        values[entry + ".payload.applicationmessage.data.seriesupdate.priorityquotewidth"] = canonical::scaled(message.priority_quote_width().mantissa(), message.priority_quote_width().exponent());
    }

    void on(const protocol::ComplexStrategyDefinitionMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.complexstrategydefinitionmessage";
        values[entry + ".payload.applicationmessage.data.complexstrategydefinitionmessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".payload.applicationmessage.data.complexstrategydefinitionmessage.strategyid"] = canonical::number(message.strategy_id());
        values[entry + ".payload.applicationmessage.data.complexstrategydefinitionmessage.underlyingsymbol"] = canonical::text(std::string(message.underlying_symbol()), ' ', false);
        values[entry + ".payload.applicationmessage.data.complexstrategydefinitionmessage.activeonmiax"] = canonical::text(canonical::character(message.active_on_miax()), ' ', false);
        values[entry + ".payload.applicationmessage.data.complexstrategydefinitionmessage.updatereason"] = canonical::text(canonical::character(message.update_reason()), ' ', false);
        values[entry + ".payload.applicationmessage.data.complexstrategydefinitionmessage.numberoflegs"] = canonical::number(message.number_of_legs());
    }

    void on(const protocol::SystemStateMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.systemstatemessage";
        values[entry + ".payload.applicationmessage.data.systemstatemessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".payload.applicationmessage.data.systemstatemessage.ctomversion"] = canonical::text(std::string(message.c_to_m_version()), ' ', false);
        values[entry + ".payload.applicationmessage.data.systemstatemessage.sessionid"] = canonical::number(message.session_id());
        values[entry + ".payload.applicationmessage.data.systemstatemessage.systemstatus"] = canonical::text(canonical::character(message.system_status()), ' ', false);
    }

    void on(const protocol::CompactComplexTopOfMarketBidMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.compactcomplextopofmarketbidmessage";
        values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketbidmessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketbidmessage.strategyid"] = canonical::number(message.strategy_id());
        values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketbidmessage.compactprice"] = canonical::scaled(message.compact_price().mantissa(), message.compact_price().exponent());
        values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketbidmessage.compactsize"] = canonical::number(message.compact_size());
        values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketbidmessage.topofmarketquotecondition"] = canonical::text(canonical::character(message.top_of_market_quote_condition()), ' ', false);
    }

    void on(const protocol::CompactComplexTopOfMarketOfferMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.compactcomplextopofmarketoffermessage";
        values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketoffermessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketoffermessage.strategyid"] = canonical::number(message.strategy_id());
        values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketoffermessage.compactprice"] = canonical::scaled(message.compact_price().mantissa(), message.compact_price().exponent());
        values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketoffermessage.compactsize"] = canonical::number(message.compact_size());
        values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketoffermessage.topofmarketquotecondition"] = canonical::text(canonical::character(message.top_of_market_quote_condition()), ' ', false);
    }

    void on(const protocol::WideComplexTopOfMarketBidMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.widecomplextopofmarketbidmessage";
        values[entry + ".payload.applicationmessage.data.widecomplextopofmarketbidmessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".payload.applicationmessage.data.widecomplextopofmarketbidmessage.strategyid"] = canonical::number(message.strategy_id());
        values[entry + ".payload.applicationmessage.data.widecomplextopofmarketbidmessage.wideprice"] = canonical::scaled(message.wide_price().mantissa(), message.wide_price().exponent());
        values[entry + ".payload.applicationmessage.data.widecomplextopofmarketbidmessage.widesize"] = canonical::number(message.wide_size());
        values[entry + ".payload.applicationmessage.data.widecomplextopofmarketbidmessage.topofmarketquotecondition"] = canonical::text(canonical::character(message.top_of_market_quote_condition()), ' ', false);
    }

    void on(const protocol::WideComplexTopOfMarketOfferMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.widecomplextopofmarketoffermessage";
        values[entry + ".payload.applicationmessage.data.widecomplextopofmarketoffermessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".payload.applicationmessage.data.widecomplextopofmarketoffermessage.strategyid"] = canonical::number(message.strategy_id());
        values[entry + ".payload.applicationmessage.data.widecomplextopofmarketoffermessage.wideprice"] = canonical::scaled(message.wide_price().mantissa(), message.wide_price().exponent());
        values[entry + ".payload.applicationmessage.data.widecomplextopofmarketoffermessage.widesize"] = canonical::number(message.wide_size());
        values[entry + ".payload.applicationmessage.data.widecomplextopofmarketoffermessage.topofmarketquotecondition"] = canonical::text(canonical::character(message.top_of_market_quote_condition()), ' ', false);
    }

    void on(const protocol::CompactComplexDoubleSidedTopOfMarketMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage";
        values[entry + ".payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage.strategyid"] = canonical::number(message.strategy_id());
        values[entry + ".payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage.compactbid.compactbidprice"] = canonical::scaled(message.compact_bid().compact_bid_price().mantissa(), message.compact_bid().compact_bid_price().exponent());
        values[entry + ".payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage.compactbid.compactbidsize"] = canonical::number(message.compact_bid().compact_bid_size());
        values[entry + ".payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage.compactbid.bidcondition"] = canonical::text(canonical::character(message.compact_bid().bid_condition()), ' ', false);
        values[entry + ".payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage.compactoffer.compactofferprice"] = canonical::scaled(message.compact_offer().compact_offer_price().mantissa(), message.compact_offer().compact_offer_price().exponent());
        values[entry + ".payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage.compactoffer.compactoffersize"] = canonical::number(message.compact_offer().compact_offer_size());
        values[entry + ".payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage.compactoffer.offercondition"] = canonical::text(canonical::character(message.compact_offer().offer_condition()), ' ', false);
    }

    void on(const protocol::WideComplexDoubleSidedTopOfMarketMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage";
        values[entry + ".payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage.strategyid"] = canonical::number(message.strategy_id());
        values[entry + ".payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage.widebid.widebidprice"] = canonical::scaled(message.wide_bid().wide_bid_price().mantissa(), message.wide_bid().wide_bid_price().exponent());
        values[entry + ".payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage.widebid.widebidsize"] = canonical::number(message.wide_bid().wide_bid_size());
        values[entry + ".payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage.widebid.bidcondition"] = canonical::text(canonical::character(message.wide_bid().bid_condition()), ' ', false);
        values[entry + ".payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage.wideoffer.wideofferprice"] = canonical::scaled(message.wide_offer().wide_offer_price().mantissa(), message.wide_offer().wide_offer_price().exponent());
        values[entry + ".payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage.wideoffer.wideoffersize"] = canonical::number(message.wide_offer().wide_offer_size());
        values[entry + ".payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage.wideoffer.offercondition"] = canonical::text(canonical::character(message.wide_offer().offer_condition()), ' ', false);
    }

    void on(const protocol::StrategyTradeMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.strategytrademessage";
        values[entry + ".payload.applicationmessage.data.strategytrademessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".payload.applicationmessage.data.strategytrademessage.strategyid"] = canonical::number(message.strategy_id());
        values[entry + ".payload.applicationmessage.data.strategytrademessage.tradeid"] = canonical::number(message.trade_id());
        values[entry + ".payload.applicationmessage.data.strategytrademessage.netprice"] = canonical::scaled(message.net_price().mantissa(), message.net_price().exponent());
        values[entry + ".payload.applicationmessage.data.strategytrademessage.tradesize"] = canonical::number(message.trade_size());
        values[entry + ".payload.applicationmessage.data.strategytrademessage.tradecondition"] = canonical::text(canonical::character(message.trade_condition()), ' ', false);
    }

    void on(const protocol::UnderlyingTradingStatusMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.underlyingtradingstatusmessage";
        values[entry + ".payload.applicationmessage.data.underlyingtradingstatusmessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".payload.applicationmessage.data.underlyingtradingstatusmessage.underlyingsymbol"] = canonical::text(std::string(message.underlying_symbol()), ' ', false);
        values[entry + ".payload.applicationmessage.data.underlyingtradingstatusmessage.tradingstatus"] = canonical::text(canonical::character(message.trading_status()), ' ', false);
        values[entry + ".payload.applicationmessage.data.underlyingtradingstatusmessage.eventreason"] = canonical::text(canonical::character(message.event_reason()), ' ', false);
        values[entry + ".payload.applicationmessage.data.underlyingtradingstatusmessage.secondspart"] = canonical::number(message.seconds_part());
        values[entry + ".payload.applicationmessage.data.underlyingtradingstatusmessage.expectedeventtimenanosecondspart"] = canonical::number(message.expected_event_time_nano_seconds_part());
    }
};

// The handler the reader hands each datagram's views to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    void on(const protocol::Packet&) {
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

    void on(const protocol::ApplicationMessage& message) {
        const std::string entry = "packet.machmessage[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.machmessage.payload.applicationmessage";
        values[entry + ".payload.applicationmessage.messagetype"] = canonical::text(canonical::character(message.message_type()));
        DataHandler selected{ values, entry };
        message.data(selected);
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
    std::printf("== Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1 (flyweight values)\n");
    int failures = 0;
    failures += check("Heartbeat", "Miax/MiaxOptions.ComplexTopOfMarket.Mach.v1.1/Heartbeat.pcap", "miax/miaxoptions/complextopofmarket/mach/v1.1/Heartbeat.values");
    failures += check("SystemStateMessage", "Miax/MiaxOptions.ComplexTopOfMarket.Mach.v1.1/SystemStateMessage.pcap", "miax/miaxoptions/complextopofmarket/mach/v1.1/SystemStateMessage.values");
    return failures == 0 ? 0 : 1;
}
