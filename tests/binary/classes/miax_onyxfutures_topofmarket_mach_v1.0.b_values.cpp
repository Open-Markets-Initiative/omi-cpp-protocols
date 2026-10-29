// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/binary/classes/miax/onyxfutures/topofmarket/mach/v1.0.b/definitions.hpp"

namespace protocol = ::miax::onyxfutures::topofmarket::mach::v1_0_b;

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
            values[entry + ".payload.applicationmessage.messagetype"] = canonical::number((*message).message_type_field());
            if (const auto* message_2 = dynamic_cast<const protocol::SimpleInstrumentDefinitionMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.simpleinstrumentdefinitionmessage";
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.timestamp"] = canonical::number((*message_2).timestamp());
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.instrumentid"] = canonical::number((*message_2).instrument_id());
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.underlyingassettype"] = canonical::text(canonical::character((*message_2).underlying_asset_type()), ' ', false);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.underlyingasset"] = canonical::text(std::string((*message_2).underlying_asset()), ' ', false);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.productgroupcode"] = canonical::text(std::string((*message_2).product_group_code()), ' ', false);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.exchange"] = canonical::text(std::string((*message_2).exchange()), ' ', false);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.instrumentidsource"] = canonical::text(canonical::character((*message_2).instrument_id_source()), ' ', false);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.instrumenttype"] = canonical::text(canonical::character((*message_2).instrument_type()), ' ', false);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.maturitymonthyear"] = canonical::number((*message_2).maturity_month_year());
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.currency"] = canonical::text(canonical::character((*message_2).currency()), ' ', false);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.settlementcurrency"] = canonical::text(canonical::character((*message_2).settlement_currency()), ' ', false);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.matchalgorithm"] = canonical::text(canonical::character((*message_2).match_algorithm()), ' ', false);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.minimumsize"] = canonical::number((*message_2).minimum_size());
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.maximumsize"] = canonical::number((*message_2).maximum_size());
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.tick"] = canonical::scaled((*message_2).tick().mantissa(), (*message_2).tick().exponent());
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.unitofmeasure"] = canonical::text(std::string((*message_2).unit_of_measure()), ' ', false);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.unitofmeasurequantity"] = canonical::number((*message_2).unit_of_measure_quantity());
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.settlementprice"] = canonical::scaled((*message_2).settlement_price().mantissa(), (*message_2).settlement_price().exponent());
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.settlementpricetypecalcmethod"] = canonical::text(canonical::character((*message_2).settlement_price_type_calc_method()), ' ', false);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.totalvolume"] = canonical::number((*message_2).total_volume());
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.openinterestquantity"] = canonical::number((*message_2).open_interest_quantity());
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.highlimitprice"] = canonical::scaled((*message_2).high_limit_price().mantissa(), (*message_2).high_limit_price().exponent());
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.lowlimitprice"] = canonical::scaled((*message_2).low_limit_price().mantissa(), (*message_2).low_limit_price().exponent());
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.tradingcollarvariationtype"] = canonical::text(canonical::character((*message_2).trading_collar_variation_type()), ' ', false);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.tradingcollarvariation"] = canonical::scaled((*message_2).trading_collar_variation().mantissa(), (*message_2).trading_collar_variation().exponent());
            } else if (const auto* message_2 = dynamic_cast<const protocol::ComplexInstrumentDefinitionMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.complexinstrumentdefinitionmessage";
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.timestamp"] = canonical::number((*message_2).timestamp());
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.strategyid"] = canonical::number((*message_2).strategy_id());
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.underlyingassettype"] = canonical::text(canonical::character((*message_2).underlying_asset_type()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.underlyingasset"] = canonical::text(std::string((*message_2).underlying_asset()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.productgroupcode"] = canonical::text(std::string((*message_2).product_group_code()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.spreadtype"] = canonical::text(canonical::character((*message_2).spread_type()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.exchange"] = canonical::text(std::string((*message_2).exchange()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.instrumentidsource"] = canonical::text(canonical::character((*message_2).instrument_id_source()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.instrumenttype"] = canonical::text(canonical::character((*message_2).instrument_type()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.currency"] = canonical::text(canonical::character((*message_2).currency()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.settlementcurrency"] = canonical::text(canonical::character((*message_2).settlement_currency()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.matchalgorithm"] = canonical::text(canonical::character((*message_2).match_algorithm()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.minimumsize"] = canonical::number((*message_2).minimum_size());
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.maximumsize"] = canonical::number((*message_2).maximum_size());
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.tick"] = canonical::scaled((*message_2).tick().mantissa(), (*message_2).tick().exponent());
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.unitofmeasure"] = canonical::text(std::string((*message_2).unit_of_measure()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.unitofmeasurequantity"] = canonical::number((*message_2).unit_of_measure_quantity());
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.tradingcollarvariationtype"] = canonical::text(canonical::character((*message_2).trading_collar_variation_type()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.tradingcollarvariation"] = canonical::scaled((*message_2).trading_collar_variation().mantissa(), (*message_2).trading_collar_variation().exponent());
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.numberoflegs"] = canonical::number((*message_2).number_of_legs());
            } else if (const auto* message_2 = dynamic_cast<const protocol::SystemStateMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.systemstatemessage";
                values[entry + ".payload.applicationmessage.data.systemstatemessage.timestamp"] = canonical::number((*message_2).timestamp());
                values[entry + ".payload.applicationmessage.data.systemstatemessage.tomversion"] = canonical::text(std::string((*message_2).tom_version()), ' ', false);
                values[entry + ".payload.applicationmessage.data.systemstatemessage.sessionid"] = canonical::number((*message_2).session_id());
                values[entry + ".payload.applicationmessage.data.systemstatemessage.systemstatus"] = canonical::text(canonical::character((*message_2).system_status()), ' ', false);
            } else if (const auto* message_2 = dynamic_cast<const protocol::InstrumentTradingStatusNotificationMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.instrumenttradingstatusnotificationmessage";
                values[entry + ".payload.applicationmessage.data.instrumenttradingstatusnotificationmessage.timestamp"] = canonical::number((*message_2).timestamp());
                values[entry + ".payload.applicationmessage.data.instrumenttradingstatusnotificationmessage.instrumentid"] = canonical::number((*message_2).instrument_id());
                values[entry + ".payload.applicationmessage.data.instrumenttradingstatusnotificationmessage.tradingstatus"] = canonical::number((*message_2).trading_status());
                values[entry + ".payload.applicationmessage.data.instrumenttradingstatusnotificationmessage.marketstate"] = canonical::number((*message_2).market_state());
            } else if (const auto* message_2 = dynamic_cast<const protocol::BestBidAndOfferMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.bestbidandoffermessage";
                values[entry + ".payload.applicationmessage.data.bestbidandoffermessage.timestamp"] = canonical::number((*message_2).timestamp());
                values[entry + ".payload.applicationmessage.data.bestbidandoffermessage.instrumentid"] = canonical::number((*message_2).instrument_id());
                values[entry + ".payload.applicationmessage.data.bestbidandoffermessage.mbbprice"] = canonical::scaled((*message_2).mbb_price().mantissa(), (*message_2).mbb_price().exponent());
                values[entry + ".payload.applicationmessage.data.bestbidandoffermessage.mbbsize"] = canonical::number((*message_2).mbb_size());
                values[entry + ".payload.applicationmessage.data.bestbidandoffermessage.mboprice"] = canonical::scaled((*message_2).mbo_price().mantissa(), (*message_2).mbo_price().exponent());
                values[entry + ".payload.applicationmessage.data.bestbidandoffermessage.mbosize"] = canonical::number((*message_2).mbo_size());
            } else if (const auto* message_2 = dynamic_cast<const protocol::LastSaleMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.lastsalemessage";
                values[entry + ".payload.applicationmessage.data.lastsalemessage.timestamp"] = canonical::number((*message_2).timestamp());
                values[entry + ".payload.applicationmessage.data.lastsalemessage.instrumentid"] = canonical::number((*message_2).instrument_id());
                values[entry + ".payload.applicationmessage.data.lastsalemessage.tradeid"] = canonical::number((*message_2).trade_id());
                values[entry + ".payload.applicationmessage.data.lastsalemessage.price"] = canonical::scaled((*message_2).price().mantissa(), (*message_2).price().exponent());
                values[entry + ".payload.applicationmessage.data.lastsalemessage.size"] = canonical::number((*message_2).size());
            } else if (const auto* message_2 = dynamic_cast<const protocol::TradeCancelMessage*>(message->data())) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.tradecancelmessage";
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.timestamp"] = canonical::number((*message_2).timestamp());
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.tradedate"] = canonical::number((*message_2).trade_date());
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.instrumentid"] = canonical::number((*message_2).instrument_id());
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.tradeid"] = canonical::number((*message_2).trade_id());
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.correctionnumber"] = canonical::number((*message_2).correction_number());
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.price"] = canonical::scaled((*message_2).price().mantissa(), (*message_2).price().exponent());
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.size"] = canonical::number((*message_2).size());
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
    std::printf("== Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b (classes values)\n");
    int failures = 0;
    failures += check("BestBidAndOfferMessage", "Miax/OnyxFutures.TopOfMarket.Mach.v1.0.b/BestBidAndOfferMessage.pcap", "miax/onyxfutures/topofmarket/mach/v1.0.b/BestBidAndOfferMessage.values");
    failures += check("Heartbeat", "Miax/OnyxFutures.TopOfMarket.Mach.v1.0.b/Heartbeat.pcap", "miax/onyxfutures/topofmarket/mach/v1.0.b/Heartbeat.values");
    failures += check("InstrumentTradingStatusNotificationMessage", "Miax/OnyxFutures.TopOfMarket.Mach.v1.0.b/InstrumentTradingStatusNotificationMessage.pcap", "miax/onyxfutures/topofmarket/mach/v1.0.b/InstrumentTradingStatusNotificationMessage.values");
    failures += check("SystemStateMessage", "Miax/OnyxFutures.TopOfMarket.Mach.v1.0.b/SystemStateMessage.pcap", "miax/onyxfutures/topofmarket/mach/v1.0.b/SystemStateMessage.values");
    return failures == 0 ? 0 : 1;
}
