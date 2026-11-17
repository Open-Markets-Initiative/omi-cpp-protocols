// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1 canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/miax/miaxoptions/complextopofmarket/mach/v1.1/definitions.hpp"

namespace protocol = ::miax::miaxoptions::complextopofmarket::mach::v1_1;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MachMessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.machmessage[" + std::to_string(index++) + "]";
        values[entry + ".machpacketheader.sequencenumber"] = canonical::number(iterator.mach_packet_header->sequence_number.get());
        values[entry + ".machpacketheader.packetlength"] = canonical::number(iterator.mach_packet_header->packet_length.get());
        values[entry + ".machpacketheader.packettype"] = canonical::number(iterator.mach_packet_header->packet_type.get());
        values[entry + ".machpacketheader.sessionnumber"] = canonical::number(iterator.mach_packet_header->session_number.get());

        if (iterator.packet_type == 3) {
            values[entry + ".payload"] = "packet.machmessage.payload.applicationmessage";
            [[maybe_unused]] const auto* message = protocol::ApplicationMessage::parse(iterator.message);
            values[entry + ".payload.applicationmessage.messagetype"] = canonical::text(canonical::character(message->message_type.get()));
            if (message->message_type.get() == protocol::SystemTimeMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.systemtimemessage";
                [[maybe_unused]] const auto* message_2 = protocol::SystemTimeMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.systemtimemessage.seconds"] = canonical::number(message_2->seconds.get());
            } else if (message->message_type.get() == protocol::SeriesUpdate::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.seriesupdate";
                [[maybe_unused]] const auto* message_2 = protocol::SeriesUpdate::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.seriesupdate.nanoseconds"] = canonical::number(message_2->nanoseconds.get());
                values[entry + ".payload.applicationmessage.data.seriesupdate.productid"] = canonical::number(message_2->product_id.get());
                values[entry + ".payload.applicationmessage.data.seriesupdate.underlyingsymbol"] = canonical::text(std::string(message_2->underlying_symbol.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.seriesupdate.securitysymbol"] = canonical::text(std::string(message_2->security_symbol.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.seriesupdate.expirationdate"] = canonical::text(std::string(message_2->expiration_date.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.seriesupdate.strikeprice"] = canonical::scaled(message_2->strike_price.integer(), -4);
                values[entry + ".payload.applicationmessage.data.seriesupdate.callorput"] = canonical::text(canonical::character(message_2->call_or_put.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.seriesupdate.openingtime"] = canonical::text(std::string(message_2->opening_time.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.seriesupdate.closingtime"] = canonical::text(std::string(message_2->closing_time.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.seriesupdate.restrictedoption"] = canonical::text(canonical::character(message_2->restricted_option.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.seriesupdate.longtermoption"] = canonical::text(canonical::character(message_2->long_term_option.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.seriesupdate.activeonmiax"] = canonical::text(canonical::character(message_2->active_on_miax.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.seriesupdate.miaxbbopostingincrementindicator"] = canonical::text(canonical::character(message_2->miax_bbo_posting_increment_indicator.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.seriesupdate.liquidityacceptanceincrementindicator"] = canonical::text(canonical::character(message_2->liquidity_acceptance_increment_indicator.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.seriesupdate.openingunderlyingmarketcode"] = canonical::text(canonical::character(message_2->opening_underlying_market_code.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.seriesupdate.priorityquotewidth"] = canonical::scaled(message_2->priority_quote_width.integer(), -4);
            } else if (message->message_type.get() == protocol::ComplexStrategyDefinitionMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.complexstrategydefinitionmessage";
                [[maybe_unused]] const auto* message_2 = protocol::ComplexStrategyDefinitionMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.complexstrategydefinitionmessage.nanoseconds"] = canonical::number(message_2->nanoseconds.get());
                values[entry + ".payload.applicationmessage.data.complexstrategydefinitionmessage.strategyid"] = canonical::number(message_2->strategy_id.get());
                values[entry + ".payload.applicationmessage.data.complexstrategydefinitionmessage.underlyingsymbol"] = canonical::text(std::string(message_2->underlying_symbol.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexstrategydefinitionmessage.activeonmiax"] = canonical::text(canonical::character(message_2->active_on_miax.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexstrategydefinitionmessage.updatereason"] = canonical::text(canonical::character(message_2->update_reason.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexstrategydefinitionmessage.numberoflegs"] = canonical::number(message_2->number_of_legs.get());
            } else if (message->message_type.get() == protocol::SystemStateMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.systemstatemessage";
                [[maybe_unused]] const auto* message_2 = protocol::SystemStateMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.systemstatemessage.nanoseconds"] = canonical::number(message_2->nanoseconds.get());
                values[entry + ".payload.applicationmessage.data.systemstatemessage.ctomversion"] = canonical::text(std::string(message_2->c_to_m_version.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.systemstatemessage.sessionid"] = canonical::number(message_2->session_id.get());
                values[entry + ".payload.applicationmessage.data.systemstatemessage.systemstatus"] = canonical::text(canonical::character(message_2->system_status.get()), ' ', false);
            } else if (message->message_type.get() == protocol::CompactComplexTopOfMarketBidMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.compactcomplextopofmarketbidmessage";
                [[maybe_unused]] const auto* message_2 = protocol::CompactComplexTopOfMarketBidMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketbidmessage.nanoseconds"] = canonical::number(message_2->nanoseconds.get());
                values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketbidmessage.strategyid"] = canonical::number(message_2->strategy_id.get());
                values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketbidmessage.compactprice"] = canonical::scaled(message_2->compact_price.integer(), -2);
                values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketbidmessage.compactsize"] = canonical::number(message_2->compact_size.get());
                values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketbidmessage.topofmarketquotecondition"] = canonical::text(canonical::character(message_2->top_of_market_quote_condition.get()), ' ', false);
            } else if (message->message_type.get() == protocol::CompactComplexTopOfMarketOfferMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.compactcomplextopofmarketoffermessage";
                [[maybe_unused]] const auto* message_2 = protocol::CompactComplexTopOfMarketOfferMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketoffermessage.nanoseconds"] = canonical::number(message_2->nanoseconds.get());
                values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketoffermessage.strategyid"] = canonical::number(message_2->strategy_id.get());
                values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketoffermessage.compactprice"] = canonical::scaled(message_2->compact_price.integer(), -2);
                values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketoffermessage.compactsize"] = canonical::number(message_2->compact_size.get());
                values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketoffermessage.topofmarketquotecondition"] = canonical::text(canonical::character(message_2->top_of_market_quote_condition.get()), ' ', false);
            } else if (message->message_type.get() == protocol::WideComplexTopOfMarketBidMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.widecomplextopofmarketbidmessage";
                [[maybe_unused]] const auto* message_2 = protocol::WideComplexTopOfMarketBidMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.widecomplextopofmarketbidmessage.nanoseconds"] = canonical::number(message_2->nanoseconds.get());
                values[entry + ".payload.applicationmessage.data.widecomplextopofmarketbidmessage.strategyid"] = canonical::number(message_2->strategy_id.get());
                values[entry + ".payload.applicationmessage.data.widecomplextopofmarketbidmessage.wideprice"] = canonical::scaled(message_2->wide_price.integer(), -4);
                values[entry + ".payload.applicationmessage.data.widecomplextopofmarketbidmessage.widesize"] = canonical::number(message_2->wide_size.get());
                values[entry + ".payload.applicationmessage.data.widecomplextopofmarketbidmessage.topofmarketquotecondition"] = canonical::text(canonical::character(message_2->top_of_market_quote_condition.get()), ' ', false);
            } else if (message->message_type.get() == protocol::WideComplexTopOfMarketOfferMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.widecomplextopofmarketoffermessage";
                [[maybe_unused]] const auto* message_2 = protocol::WideComplexTopOfMarketOfferMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.widecomplextopofmarketoffermessage.nanoseconds"] = canonical::number(message_2->nanoseconds.get());
                values[entry + ".payload.applicationmessage.data.widecomplextopofmarketoffermessage.strategyid"] = canonical::number(message_2->strategy_id.get());
                values[entry + ".payload.applicationmessage.data.widecomplextopofmarketoffermessage.wideprice"] = canonical::scaled(message_2->wide_price.integer(), -4);
                values[entry + ".payload.applicationmessage.data.widecomplextopofmarketoffermessage.widesize"] = canonical::number(message_2->wide_size.get());
                values[entry + ".payload.applicationmessage.data.widecomplextopofmarketoffermessage.topofmarketquotecondition"] = canonical::text(canonical::character(message_2->top_of_market_quote_condition.get()), ' ', false);
            } else if (message->message_type.get() == protocol::CompactComplexDoubleSidedTopOfMarketMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage";
                [[maybe_unused]] const auto* message_2 = protocol::CompactComplexDoubleSidedTopOfMarketMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage.nanoseconds"] = canonical::number(message_2->nanoseconds.get());
                values[entry + ".payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage.strategyid"] = canonical::number(message_2->strategy_id.get());
                values[entry + ".payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage.compactbid.compactbidprice"] = canonical::scaled(message_2->compact_bid.compact_bid_price.integer(), -2);
                values[entry + ".payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage.compactbid.compactbidsize"] = canonical::number(message_2->compact_bid.compact_bid_size.get());
                values[entry + ".payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage.compactbid.bidcondition"] = canonical::text(canonical::character(message_2->compact_bid.bid_condition.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage.compactoffer.compactofferprice"] = canonical::scaled(message_2->compact_offer.compact_offer_price.integer(), -2);
                values[entry + ".payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage.compactoffer.compactoffersize"] = canonical::number(message_2->compact_offer.compact_offer_size.get());
                values[entry + ".payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage.compactoffer.offercondition"] = canonical::text(canonical::character(message_2->compact_offer.offer_condition.get()), ' ', false);
            } else if (message->message_type.get() == protocol::WideComplexDoubleSidedTopOfMarketMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage";
                [[maybe_unused]] const auto* message_2 = protocol::WideComplexDoubleSidedTopOfMarketMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage.nanoseconds"] = canonical::number(message_2->nanoseconds.get());
                values[entry + ".payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage.strategyid"] = canonical::number(message_2->strategy_id.get());
                values[entry + ".payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage.widebid.widebidprice"] = canonical::scaled(message_2->wide_bid.wide_bid_price.integer(), -4);
                values[entry + ".payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage.widebid.widebidsize"] = canonical::number(message_2->wide_bid.wide_bid_size.get());
                values[entry + ".payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage.widebid.bidcondition"] = canonical::text(canonical::character(message_2->wide_bid.bid_condition.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage.wideoffer.wideofferprice"] = canonical::scaled(message_2->wide_offer.wide_offer_price.integer(), -4);
                values[entry + ".payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage.wideoffer.wideoffersize"] = canonical::number(message_2->wide_offer.wide_offer_size.get());
                values[entry + ".payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage.wideoffer.offercondition"] = canonical::text(canonical::character(message_2->wide_offer.offer_condition.get()), ' ', false);
            } else if (message->message_type.get() == protocol::StrategyTradeMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.strategytrademessage";
                [[maybe_unused]] const auto* message_2 = protocol::StrategyTradeMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.strategytrademessage.nanoseconds"] = canonical::number(message_2->nanoseconds.get());
                values[entry + ".payload.applicationmessage.data.strategytrademessage.strategyid"] = canonical::number(message_2->strategy_id.get());
                values[entry + ".payload.applicationmessage.data.strategytrademessage.tradeid"] = canonical::number(message_2->trade_id.get());
                values[entry + ".payload.applicationmessage.data.strategytrademessage.netprice"] = canonical::scaled(message_2->net_price.integer(), -4);
                values[entry + ".payload.applicationmessage.data.strategytrademessage.tradesize"] = canonical::number(message_2->trade_size.get());
                values[entry + ".payload.applicationmessage.data.strategytrademessage.tradecondition"] = canonical::text(canonical::character(message_2->trade_condition.get()), ' ', false);
            } else if (message->message_type.get() == protocol::UnderlyingTradingStatusMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.underlyingtradingstatusmessage";
                [[maybe_unused]] const auto* message_2 = protocol::UnderlyingTradingStatusMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.underlyingtradingstatusmessage.nanoseconds"] = canonical::number(message_2->nanoseconds.get());
                values[entry + ".payload.applicationmessage.data.underlyingtradingstatusmessage.underlyingsymbol"] = canonical::text(std::string(message_2->underlying_symbol.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.underlyingtradingstatusmessage.tradingstatus"] = canonical::text(canonical::character(message_2->trading_status.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.underlyingtradingstatusmessage.eventreason"] = canonical::text(canonical::character(message_2->event_reason.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.underlyingtradingstatusmessage.expectedeventtimesecondspart"] = (static_cast<std::uint32_t>(message_2->expected_event_time_seconds_part.get()) != 0x0U ? canonical::number(message_2->expected_event_time_seconds_part.get()) : canonical::absent());
                values[entry + ".payload.applicationmessage.data.underlyingtradingstatusmessage.expectedeventtimenanosecondspart"] = canonical::number(message_2->expected_event_time_nano_seconds_part.get());
            }
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
    std::printf("== Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1 (modern values)\n");
    int failures = 0;
    failures += check("Heartbeat", "Miax/MiaxOptions.ComplexTopOfMarket.Mach.v1.1/Heartbeat.pcap", "miax/miaxoptions/complextopofmarket/mach/v1.1/Heartbeat.values");
    failures += check("SystemStateMessage", "Miax/MiaxOptions.ComplexTopOfMarket.Mach.v1.1/SystemStateMessage.pcap", "miax/miaxoptions/complextopofmarket/mach/v1.1/SystemStateMessage.values");
    return failures == 0 ? 0 : 1;
}
