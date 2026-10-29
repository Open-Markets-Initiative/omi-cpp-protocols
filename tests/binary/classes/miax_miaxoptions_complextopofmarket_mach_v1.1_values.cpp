// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1 canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/binary/classes/miax/miaxoptions/complextopofmarket/mach/v1.1/definitions.hpp"

namespace protocol = ::miax::miaxoptions::complextopofmarket::mach::v1_1;

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


    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        const std::string entry = "packet.machmessage[" + std::to_string(index++) + "]";
        values[entry + ".machpacketheader.sequencenumber"] = canonical::number(each.mach_packet_header().sequence_number());
        values[entry + ".machpacketheader.packetlength"] = canonical::number(each.mach_packet_header().packet_length());
        values[entry + ".machpacketheader.packettype"] = canonical::number(each.mach_packet_header().packet_type());
        values[entry + ".machpacketheader.sessionnumber"] = canonical::number(each.mach_packet_header().session_number());

        if (const auto* message = dynamic_cast<const protocol::ApplicationMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.machmessage.payload.applicationmessage";
            values[entry + ".payload.applicationmessage.messagetype"] = canonical::text(canonical::character((*message).message_type_field()));
            if (const auto* message_2 = dynamic_cast<const protocol::SystemTimeMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.systemtimemessage";
                values[entry + ".payload.applicationmessage.data.systemtimemessage.seconds"] = canonical::number((*message_2).seconds());
            } else if (const auto* message_2 = dynamic_cast<const protocol::SeriesUpdate*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.seriesupdate";
                values[entry + ".payload.applicationmessage.data.seriesupdate.nanoseconds"] = canonical::number((*message_2).nanoseconds());
                values[entry + ".payload.applicationmessage.data.seriesupdate.productid"] = canonical::number((*message_2).product_id());
                values[entry + ".payload.applicationmessage.data.seriesupdate.underlyingsymbol"] = canonical::text(std::string((*message_2).underlying_symbol()), ' ', false);
                values[entry + ".payload.applicationmessage.data.seriesupdate.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".payload.applicationmessage.data.seriesupdate.expirationdate"] = canonical::text(std::string((*message_2).expiration_date()), ' ', false);
                values[entry + ".payload.applicationmessage.data.seriesupdate.strikeprice"] = canonical::scaled((*message_2).strike_price().mantissa(), (*message_2).strike_price().exponent());
                values[entry + ".payload.applicationmessage.data.seriesupdate.callorput"] = canonical::text(canonical::character((*message_2).call_or_put()), ' ', false);
                values[entry + ".payload.applicationmessage.data.seriesupdate.openingtime"] = canonical::text(std::string((*message_2).opening_time()), ' ', false);
                values[entry + ".payload.applicationmessage.data.seriesupdate.closingtime"] = canonical::text(std::string((*message_2).closing_time()), ' ', false);
                values[entry + ".payload.applicationmessage.data.seriesupdate.restrictedoption"] = canonical::text(canonical::character((*message_2).restricted_option()), ' ', false);
                values[entry + ".payload.applicationmessage.data.seriesupdate.longtermoption"] = canonical::text(canonical::character((*message_2).long_term_option()), ' ', false);
                values[entry + ".payload.applicationmessage.data.seriesupdate.activeonmiax"] = canonical::text(canonical::character((*message_2).active_on_miax()), ' ', false);
                values[entry + ".payload.applicationmessage.data.seriesupdate.miaxbbopostingincrementindicator"] = canonical::text(canonical::character((*message_2).miax_bbo_posting_increment_indicator()), ' ', false);
                values[entry + ".payload.applicationmessage.data.seriesupdate.liquidityacceptanceincrementindicator"] = canonical::text(canonical::character((*message_2).liquidity_acceptance_increment_indicator()), ' ', false);
                values[entry + ".payload.applicationmessage.data.seriesupdate.openingunderlyingmarketcode"] = canonical::text(canonical::character((*message_2).opening_underlying_market_code()), ' ', false);
                values[entry + ".payload.applicationmessage.data.seriesupdate.priorityquotewidth"] = canonical::scaled((*message_2).priority_quote_width().mantissa(), (*message_2).priority_quote_width().exponent());
            } else if (const auto* message_2 = dynamic_cast<const protocol::ComplexStrategyDefinitionMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.complexstrategydefinitionmessage";
                values[entry + ".payload.applicationmessage.data.complexstrategydefinitionmessage.nanoseconds"] = canonical::number((*message_2).nanoseconds());
                values[entry + ".payload.applicationmessage.data.complexstrategydefinitionmessage.strategyid"] = canonical::number((*message_2).strategy_id());
                values[entry + ".payload.applicationmessage.data.complexstrategydefinitionmessage.underlyingsymbol"] = canonical::text(std::string((*message_2).underlying_symbol()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexstrategydefinitionmessage.activeonmiax"] = canonical::text(canonical::character((*message_2).active_on_miax()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexstrategydefinitionmessage.updatereason"] = canonical::text(canonical::character((*message_2).update_reason()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexstrategydefinitionmessage.numberoflegs"] = canonical::number((*message_2).number_of_legs());
            } else if (const auto* message_2 = dynamic_cast<const protocol::SystemStateMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.systemstatemessage";
                values[entry + ".payload.applicationmessage.data.systemstatemessage.nanoseconds"] = canonical::number((*message_2).nanoseconds());
                values[entry + ".payload.applicationmessage.data.systemstatemessage.ctomversion"] = canonical::text(std::string((*message_2).c_to_m_version()), ' ', false);
                values[entry + ".payload.applicationmessage.data.systemstatemessage.sessionid"] = canonical::number((*message_2).session_id());
                values[entry + ".payload.applicationmessage.data.systemstatemessage.systemstatus"] = canonical::text(canonical::character((*message_2).system_status()), ' ', false);
            } else if (const auto* message_2 = dynamic_cast<const protocol::CompactComplexTopOfMarketBidMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.compactcomplextopofmarketbidmessage";
                values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketbidmessage.nanoseconds"] = canonical::number((*message_2).nanoseconds());
                values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketbidmessage.strategyid"] = canonical::number((*message_2).strategy_id());
                values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketbidmessage.compactprice"] = canonical::scaled((*message_2).compact_price().mantissa(), (*message_2).compact_price().exponent());
                values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketbidmessage.compactsize"] = canonical::number((*message_2).compact_size());
                values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketbidmessage.topofmarketquotecondition"] = canonical::text(canonical::character((*message_2).top_of_market_quote_condition()), ' ', false);
            } else if (const auto* message_2 = dynamic_cast<const protocol::CompactComplexTopOfMarketOfferMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.compactcomplextopofmarketoffermessage";
                values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketoffermessage.nanoseconds"] = canonical::number((*message_2).nanoseconds());
                values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketoffermessage.strategyid"] = canonical::number((*message_2).strategy_id());
                values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketoffermessage.compactprice"] = canonical::scaled((*message_2).compact_price().mantissa(), (*message_2).compact_price().exponent());
                values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketoffermessage.compactsize"] = canonical::number((*message_2).compact_size());
                values[entry + ".payload.applicationmessage.data.compactcomplextopofmarketoffermessage.topofmarketquotecondition"] = canonical::text(canonical::character((*message_2).top_of_market_quote_condition()), ' ', false);
            } else if (const auto* message_2 = dynamic_cast<const protocol::WideComplexTopOfMarketBidMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.widecomplextopofmarketbidmessage";
                values[entry + ".payload.applicationmessage.data.widecomplextopofmarketbidmessage.nanoseconds"] = canonical::number((*message_2).nanoseconds());
                values[entry + ".payload.applicationmessage.data.widecomplextopofmarketbidmessage.strategyid"] = canonical::number((*message_2).strategy_id());
                values[entry + ".payload.applicationmessage.data.widecomplextopofmarketbidmessage.wideprice"] = canonical::scaled((*message_2).wide_price().mantissa(), (*message_2).wide_price().exponent());
                values[entry + ".payload.applicationmessage.data.widecomplextopofmarketbidmessage.widesize"] = canonical::number((*message_2).wide_size());
                values[entry + ".payload.applicationmessage.data.widecomplextopofmarketbidmessage.topofmarketquotecondition"] = canonical::text(canonical::character((*message_2).top_of_market_quote_condition()), ' ', false);
            } else if (const auto* message_2 = dynamic_cast<const protocol::WideComplexTopOfMarketOfferMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.widecomplextopofmarketoffermessage";
                values[entry + ".payload.applicationmessage.data.widecomplextopofmarketoffermessage.nanoseconds"] = canonical::number((*message_2).nanoseconds());
                values[entry + ".payload.applicationmessage.data.widecomplextopofmarketoffermessage.strategyid"] = canonical::number((*message_2).strategy_id());
                values[entry + ".payload.applicationmessage.data.widecomplextopofmarketoffermessage.wideprice"] = canonical::scaled((*message_2).wide_price().mantissa(), (*message_2).wide_price().exponent());
                values[entry + ".payload.applicationmessage.data.widecomplextopofmarketoffermessage.widesize"] = canonical::number((*message_2).wide_size());
                values[entry + ".payload.applicationmessage.data.widecomplextopofmarketoffermessage.topofmarketquotecondition"] = canonical::text(canonical::character((*message_2).top_of_market_quote_condition()), ' ', false);
            } else if (const auto* message_2 = dynamic_cast<const protocol::CompactComplexDoubleSidedTopOfMarketMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage";
                values[entry + ".payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage.nanoseconds"] = canonical::number((*message_2).nanoseconds());
                values[entry + ".payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage.strategyid"] = canonical::number((*message_2).strategy_id());
                values[entry + ".payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage.compactbid.compactbidprice"] = canonical::scaled((*message_2).compact_bid().compact_bid_price().mantissa(), (*message_2).compact_bid().compact_bid_price().exponent());
                values[entry + ".payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage.compactbid.compactbidsize"] = canonical::number((*message_2).compact_bid().compact_bid_size());
                values[entry + ".payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage.compactbid.bidcondition"] = canonical::text(canonical::character((*message_2).compact_bid().bid_condition()), ' ', false);
                values[entry + ".payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage.compactoffer.compactofferprice"] = canonical::scaled((*message_2).compact_offer().compact_offer_price().mantissa(), (*message_2).compact_offer().compact_offer_price().exponent());
                values[entry + ".payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage.compactoffer.compactoffersize"] = canonical::number((*message_2).compact_offer().compact_offer_size());
                values[entry + ".payload.applicationmessage.data.compactcomplexdoublesidedtopofmarketmessage.compactoffer.offercondition"] = canonical::text(canonical::character((*message_2).compact_offer().offer_condition()), ' ', false);
            } else if (const auto* message_2 = dynamic_cast<const protocol::WideComplexDoubleSidedTopOfMarketMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage";
                values[entry + ".payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage.nanoseconds"] = canonical::number((*message_2).nanoseconds());
                values[entry + ".payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage.strategyid"] = canonical::number((*message_2).strategy_id());
                values[entry + ".payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage.widebid.widebidprice"] = canonical::scaled((*message_2).wide_bid().wide_bid_price().mantissa(), (*message_2).wide_bid().wide_bid_price().exponent());
                values[entry + ".payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage.widebid.widebidsize"] = canonical::number((*message_2).wide_bid().wide_bid_size());
                values[entry + ".payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage.widebid.bidcondition"] = canonical::text(canonical::character((*message_2).wide_bid().bid_condition()), ' ', false);
                values[entry + ".payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage.wideoffer.wideofferprice"] = canonical::scaled((*message_2).wide_offer().wide_offer_price().mantissa(), (*message_2).wide_offer().wide_offer_price().exponent());
                values[entry + ".payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage.wideoffer.wideoffersize"] = canonical::number((*message_2).wide_offer().wide_offer_size());
                values[entry + ".payload.applicationmessage.data.widecomplexdoublesidedtopofmarketmessage.wideoffer.offercondition"] = canonical::text(canonical::character((*message_2).wide_offer().offer_condition()), ' ', false);
            } else if (const auto* message_2 = dynamic_cast<const protocol::StrategyTradeMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.strategytrademessage";
                values[entry + ".payload.applicationmessage.data.strategytrademessage.nanoseconds"] = canonical::number((*message_2).nanoseconds());
                values[entry + ".payload.applicationmessage.data.strategytrademessage.strategyid"] = canonical::number((*message_2).strategy_id());
                values[entry + ".payload.applicationmessage.data.strategytrademessage.tradeid"] = canonical::number((*message_2).trade_id());
                values[entry + ".payload.applicationmessage.data.strategytrademessage.netprice"] = canonical::scaled((*message_2).net_price().mantissa(), (*message_2).net_price().exponent());
                values[entry + ".payload.applicationmessage.data.strategytrademessage.tradesize"] = canonical::number((*message_2).trade_size());
                values[entry + ".payload.applicationmessage.data.strategytrademessage.tradecondition"] = canonical::text(canonical::character((*message_2).trade_condition()), ' ', false);
            } else if (const auto* message_2 = dynamic_cast<const protocol::UnderlyingTradingStatusMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.underlyingtradingstatusmessage";
                values[entry + ".payload.applicationmessage.data.underlyingtradingstatusmessage.nanoseconds"] = canonical::number((*message_2).nanoseconds());
                values[entry + ".payload.applicationmessage.data.underlyingtradingstatusmessage.underlyingsymbol"] = canonical::text(std::string((*message_2).underlying_symbol()), ' ', false);
                values[entry + ".payload.applicationmessage.data.underlyingtradingstatusmessage.tradingstatus"] = canonical::text(canonical::character((*message_2).trading_status()), ' ', false);
                values[entry + ".payload.applicationmessage.data.underlyingtradingstatusmessage.eventreason"] = canonical::text(canonical::character((*message_2).event_reason()), ' ', false);
                values[entry + ".payload.applicationmessage.data.underlyingtradingstatusmessage.secondspart"] = canonical::number((*message_2).seconds_part());
                values[entry + ".payload.applicationmessage.data.underlyingtradingstatusmessage.expectedeventtimenanosecondspart"] = canonical::number((*message_2).expected_event_time_nano_seconds_part());
            }
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
    std::printf("== Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1 (classes values)\n");
    int failures = 0;
    failures += check("Heartbeat", "Miax/MiaxOptions.ComplexTopOfMarket.Mach.v1.1/Heartbeat.pcap", "miax/miaxoptions/complextopofmarket/mach/v1.1/Heartbeat.values");
    failures += check("SystemStateMessage", "Miax/MiaxOptions.ComplexTopOfMarket.Mach.v1.1/SystemStateMessage.pcap", "miax/miaxoptions/complextopofmarket/mach/v1.1/SystemStateMessage.values");
    return failures == 0 ? 0 : 1;
}
