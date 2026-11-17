// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/miax/onyxfutures/topofmarket/mach/v1.0.b/definitions.hpp"

namespace protocol = ::miax::onyxfutures::topofmarket::mach::v1_0_b;

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
            values[entry + ".payload.applicationmessage.messagetype"] = canonical::number(message->message_type.get());
            if (message->message_type.get() == protocol::SimpleInstrumentDefinitionMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.simpleinstrumentdefinitionmessage";
                [[maybe_unused]] const auto* message_2 = protocol::SimpleInstrumentDefinitionMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.timestamp"] = canonical::number(message_2->timestamp.get());
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.instrumentid"] = canonical::number(message_2->instrument_id.get());
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.underlyingassettype"] = canonical::text(canonical::character(message_2->underlying_asset_type.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.underlyingasset"] = canonical::text(std::string(message_2->underlying_asset.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.productgroupcode"] = canonical::text(std::string(message_2->product_group_code.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.exchange"] = canonical::text(std::string(message_2->exchange.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.instrumentidsource"] = canonical::text(canonical::character(message_2->instrument_id_source.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.instrumenttype"] = canonical::text(canonical::character(message_2->instrument_type.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.maturitymonthyear"] = canonical::number(message_2->maturity_month_year.get());
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.currency"] = canonical::text(canonical::character(message_2->currency.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.settlementcurrency"] = canonical::text(canonical::character(message_2->settlement_currency.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.matchalgorithm"] = canonical::text(canonical::character(message_2->match_algorithm.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.minimumsize"] = canonical::number(message_2->minimum_size.get());
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.maximumsize"] = canonical::number(message_2->maximum_size.get());
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.tick"] = canonical::scaled(message_2->tick.integer(), -9);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.unitofmeasure"] = canonical::text(std::string(message_2->unit_of_measure.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.unitofmeasurequantity"] = canonical::number(message_2->unit_of_measure_quantity.get());
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.settlementprice"] = canonical::scaled(message_2->settlement_price.integer(), -9);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.settlementpricetypecalcmethod"] = canonical::text(canonical::character(message_2->settlement_price_type_calc_method.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.totalvolume"] = canonical::number(message_2->total_volume.get());
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.openinterestquantity"] = canonical::number(message_2->open_interest_quantity.get());
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.highlimitprice"] = canonical::scaled(message_2->high_limit_price.integer(), -9);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.lowlimitprice"] = canonical::scaled(message_2->low_limit_price.integer(), -9);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.tradingcollarvariationtype"] = canonical::text(canonical::character(message_2->trading_collar_variation_type.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.tradingcollarvariation"] = canonical::scaled(message_2->trading_collar_variation.integer(), -9);
            } else if (message->message_type.get() == protocol::ComplexInstrumentDefinitionMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.complexinstrumentdefinitionmessage";
                [[maybe_unused]] const auto* message_2 = protocol::ComplexInstrumentDefinitionMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.timestamp"] = canonical::number(message_2->timestamp.get());
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.strategyid"] = canonical::number(message_2->strategy_id.get());
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.underlyingassettype"] = canonical::text(canonical::character(message_2->underlying_asset_type.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.underlyingasset"] = canonical::text(std::string(message_2->underlying_asset.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.productgroupcode"] = canonical::text(std::string(message_2->product_group_code.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.spreadtype"] = canonical::text(canonical::character(message_2->spread_type.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.exchange"] = canonical::text(std::string(message_2->exchange.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.instrumentidsource"] = canonical::text(canonical::character(message_2->instrument_id_source.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.instrumenttype"] = canonical::text(canonical::character(message_2->instrument_type.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.currency"] = canonical::text(canonical::character(message_2->currency.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.settlementcurrency"] = canonical::text(canonical::character(message_2->settlement_currency.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.matchalgorithm"] = canonical::text(canonical::character(message_2->match_algorithm.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.minimumsize"] = canonical::number(message_2->minimum_size.get());
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.maximumsize"] = canonical::number(message_2->maximum_size.get());
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.tick"] = canonical::scaled(message_2->tick.integer(), -9);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.unitofmeasure"] = canonical::text(std::string(message_2->unit_of_measure.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.unitofmeasurequantity"] = canonical::number(message_2->unit_of_measure_quantity.get());
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.tradingcollarvariationtype"] = canonical::text(canonical::character(message_2->trading_collar_variation_type.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.tradingcollarvariation"] = canonical::scaled(message_2->trading_collar_variation.integer(), -9);
                values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.numberoflegs"] = canonical::number(message_2->number_of_legs.get());
            } else if (message->message_type.get() == protocol::SystemStateMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.systemstatemessage";
                [[maybe_unused]] const auto* message_2 = protocol::SystemStateMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.systemstatemessage.timestamp"] = canonical::number(message_2->timestamp.get());
                values[entry + ".payload.applicationmessage.data.systemstatemessage.tomversion"] = canonical::text(std::string(message_2->tom_version.get()), ' ', false);
                values[entry + ".payload.applicationmessage.data.systemstatemessage.sessionid"] = canonical::number(message_2->session_id.get());
                values[entry + ".payload.applicationmessage.data.systemstatemessage.systemstatus"] = canonical::text(canonical::character(message_2->system_status.get()), ' ', false);
            } else if (message->message_type.get() == protocol::InstrumentTradingStatusNotificationMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.instrumenttradingstatusnotificationmessage";
                [[maybe_unused]] const auto* message_2 = protocol::InstrumentTradingStatusNotificationMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.instrumenttradingstatusnotificationmessage.timestamp"] = canonical::number(message_2->timestamp.get());
                values[entry + ".payload.applicationmessage.data.instrumenttradingstatusnotificationmessage.instrumentid"] = canonical::number(message_2->instrument_id.get());
                values[entry + ".payload.applicationmessage.data.instrumenttradingstatusnotificationmessage.tradingstatus"] = canonical::number(message_2->trading_status.get());
                values[entry + ".payload.applicationmessage.data.instrumenttradingstatusnotificationmessage.marketstate"] = canonical::number(message_2->market_state.get());
            } else if (message->message_type.get() == protocol::BestBidAndOfferMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.bestbidandoffermessage";
                [[maybe_unused]] const auto* message_2 = protocol::BestBidAndOfferMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.bestbidandoffermessage.timestamp"] = canonical::number(message_2->timestamp.get());
                values[entry + ".payload.applicationmessage.data.bestbidandoffermessage.instrumentid"] = canonical::number(message_2->instrument_id.get());
                values[entry + ".payload.applicationmessage.data.bestbidandoffermessage.mbbprice"] = (static_cast<std::uint64_t>(message_2->mbb_price.integer()) != 0x0F21F494C589C0001ULL ? canonical::scaled(message_2->mbb_price.integer(), -9) : canonical::absent());
                values[entry + ".payload.applicationmessage.data.bestbidandoffermessage.mbbsize"] = canonical::number(message_2->mbb_size.get());
                values[entry + ".payload.applicationmessage.data.bestbidandoffermessage.mboprice"] = (static_cast<std::uint64_t>(message_2->mbo_price.integer()) != 0x0DE0B6B3A763FFFFULL ? canonical::scaled(message_2->mbo_price.integer(), -9) : canonical::absent());
                values[entry + ".payload.applicationmessage.data.bestbidandoffermessage.mbosize"] = canonical::number(message_2->mbo_size.get());
            } else if (message->message_type.get() == protocol::LastSaleMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.lastsalemessage";
                [[maybe_unused]] const auto* message_2 = protocol::LastSaleMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.lastsalemessage.timestamp"] = canonical::number(message_2->timestamp.get());
                values[entry + ".payload.applicationmessage.data.lastsalemessage.instrumentid"] = canonical::number(message_2->instrument_id.get());
                values[entry + ".payload.applicationmessage.data.lastsalemessage.tradeid"] = canonical::number(message_2->trade_id.get());
                values[entry + ".payload.applicationmessage.data.lastsalemessage.price"] = canonical::scaled(message_2->price.integer(), -9);
                values[entry + ".payload.applicationmessage.data.lastsalemessage.size"] = canonical::number(message_2->size.get());
            } else if (message->message_type.get() == protocol::TradeCancelMessage::message_type) {
                values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.tradecancelmessage";
                [[maybe_unused]] const auto* message_2 = protocol::TradeCancelMessage::parse(iterator.message + sizeof(protocol::ApplicationMessage));
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.timestamp"] = canonical::number(message_2->timestamp.get());
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.tradedate"] = canonical::number(message_2->trade_date.get());
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.instrumentid"] = canonical::number(message_2->instrument_id.get());
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.tradeid"] = canonical::number(message_2->trade_id.get());
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.correctionnumber"] = canonical::number(message_2->correction_number.get());
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.price"] = canonical::scaled(message_2->price.integer(), -9);
                values[entry + ".payload.applicationmessage.data.tradecancelmessage.size"] = canonical::number(message_2->size.get());
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
    std::printf("== Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b (modern values)\n");
    int failures = 0;
    failures += check("BestBidAndOfferMessage", "Miax/OnyxFutures.TopOfMarket.Mach.v1.0.b/BestBidAndOfferMessage.pcap", "miax/onyxfutures/topofmarket/mach/v1.0.b/BestBidAndOfferMessage.values");
    failures += check("Heartbeat", "Miax/OnyxFutures.TopOfMarket.Mach.v1.0.b/Heartbeat.pcap", "miax/onyxfutures/topofmarket/mach/v1.0.b/Heartbeat.values");
    failures += check("InstrumentTradingStatusNotificationMessage", "Miax/OnyxFutures.TopOfMarket.Mach.v1.0.b/InstrumentTradingStatusNotificationMessage.pcap", "miax/onyxfutures/topofmarket/mach/v1.0.b/InstrumentTradingStatusNotificationMessage.values");
    failures += check("SystemStateMessage", "Miax/OnyxFutures.TopOfMarket.Mach.v1.0.b/SystemStateMessage.pcap", "miax/onyxfutures/topofmarket/mach/v1.0.b/SystemStateMessage.values");
    return failures == 0 ? 0 : 1;
}
