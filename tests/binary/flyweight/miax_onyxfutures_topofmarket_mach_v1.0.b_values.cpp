// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b canonical values, through the Flyweight reader: every value Flyweight reads
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
#include "cpp/binary/flyweight/miax/onyxfutures/topofmarket/mach/v1.0.b/definitions.hpp"

namespace protocol = ::miax::onyxfutures::topofmarket::mach::v1_0_b;

namespace {

// The messages Data selects, their values set in the entry of the message holding it
struct DataHandler {
    canonical::Listing& values;
    const std::string& entry;

    void on(const protocol::SimpleInstrumentDefinitionMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.simpleinstrumentdefinitionmessage";
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.instrumentid"] = canonical::number(message.instrument_id());
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.underlyingassettype"] = canonical::text(canonical::character(message.underlying_asset_type()), ' ', false);
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.underlyingasset"] = canonical::text(std::string(message.underlying_asset()), ' ', false);
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.productgroupcode"] = canonical::text(std::string(message.product_group_code()), ' ', false);
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.exchange"] = canonical::text(std::string(message.exchange()), ' ', false);
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.instrumentidsource"] = canonical::text(canonical::character(message.instrument_id_source()), ' ', false);
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.instrumenttype"] = canonical::text(canonical::character(message.instrument_type()), ' ', false);
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.maturitymonthyear"] = canonical::number(message.maturity_month_year());
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.currency"] = canonical::text(canonical::character(message.currency()), ' ', false);
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.settlementcurrency"] = canonical::text(canonical::character(message.settlement_currency()), ' ', false);
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.matchalgorithm"] = canonical::text(canonical::character(message.match_algorithm()), ' ', false);
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.minimumsize"] = canonical::number(message.minimum_size_field());
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.maximumsize"] = canonical::number(message.maximum_size());
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.tick"] = canonical::scaled(message.tick().mantissa(), message.tick().exponent());
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.unitofmeasure"] = canonical::text(std::string(message.unit_of_measure()), ' ', false);
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.unitofmeasurequantity"] = canonical::number(message.unit_of_measure_quantity());
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.settlementprice"] = canonical::scaled(message.settlement_price().mantissa(), message.settlement_price().exponent());
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.settlementpricetypecalcmethod"] = canonical::text(canonical::character(message.settlement_price_type_calc_method()), ' ', false);
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.totalvolume"] = canonical::number(message.total_volume());
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.openinterestquantity"] = canonical::number(message.open_interest_quantity());
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.highlimitprice"] = canonical::scaled(message.high_limit_price().mantissa(), message.high_limit_price().exponent());
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.lowlimitprice"] = canonical::scaled(message.low_limit_price().mantissa(), message.low_limit_price().exponent());
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.tradingcollarvariationtype"] = canonical::text(canonical::character(message.trading_collar_variation_type()), ' ', false);
        values[entry + ".payload.applicationmessage.data.simpleinstrumentdefinitionmessage.tradingcollarvariation"] = canonical::scaled(message.trading_collar_variation().mantissa(), message.trading_collar_variation().exponent());
    }

    void on(const protocol::ComplexInstrumentDefinitionMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.complexinstrumentdefinitionmessage";
        values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.strategyid"] = canonical::number(message.strategy_id());
        values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.underlyingassettype"] = canonical::text(canonical::character(message.underlying_asset_type()), ' ', false);
        values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.underlyingasset"] = canonical::text(std::string(message.underlying_asset()), ' ', false);
        values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.productgroupcode"] = canonical::text(std::string(message.product_group_code()), ' ', false);
        values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.spreadtype"] = canonical::text(canonical::character(message.spread_type()), ' ', false);
        values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.exchange"] = canonical::text(std::string(message.exchange()), ' ', false);
        values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.instrumentidsource"] = canonical::text(canonical::character(message.instrument_id_source()), ' ', false);
        values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.instrumenttype"] = canonical::text(canonical::character(message.instrument_type()), ' ', false);
        values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.currency"] = canonical::text(canonical::character(message.currency()), ' ', false);
        values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.settlementcurrency"] = canonical::text(canonical::character(message.settlement_currency()), ' ', false);
        values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.matchalgorithm"] = canonical::text(canonical::character(message.match_algorithm()), ' ', false);
        values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.minimumsize"] = canonical::number(message.minimum_size_field());
        values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.maximumsize"] = canonical::number(message.maximum_size());
        values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.tick"] = canonical::scaled(message.tick().mantissa(), message.tick().exponent());
        values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.unitofmeasure"] = canonical::text(std::string(message.unit_of_measure()), ' ', false);
        values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.unitofmeasurequantity"] = canonical::number(message.unit_of_measure_quantity());
        values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.tradingcollarvariationtype"] = canonical::text(canonical::character(message.trading_collar_variation_type()), ' ', false);
        values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.tradingcollarvariation"] = canonical::scaled(message.trading_collar_variation().mantissa(), message.trading_collar_variation().exponent());
        values[entry + ".payload.applicationmessage.data.complexinstrumentdefinitionmessage.numberoflegs"] = canonical::number(message.number_of_legs());
    }

    void on(const protocol::SystemStateMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.systemstatemessage";
        values[entry + ".payload.applicationmessage.data.systemstatemessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.applicationmessage.data.systemstatemessage.tomversion"] = canonical::text(std::string(message.tom_version()), ' ', false);
        values[entry + ".payload.applicationmessage.data.systemstatemessage.sessionid"] = canonical::number(message.session_id());
        values[entry + ".payload.applicationmessage.data.systemstatemessage.systemstatus"] = canonical::text(canonical::character(message.system_status()), ' ', false);
    }

    void on(const protocol::InstrumentTradingStatusNotificationMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.instrumenttradingstatusnotificationmessage";
        values[entry + ".payload.applicationmessage.data.instrumenttradingstatusnotificationmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.applicationmessage.data.instrumenttradingstatusnotificationmessage.instrumentid"] = canonical::number(message.instrument_id());
        values[entry + ".payload.applicationmessage.data.instrumenttradingstatusnotificationmessage.tradingstatus"] = canonical::number(message.trading_status());
        values[entry + ".payload.applicationmessage.data.instrumenttradingstatusnotificationmessage.marketstate"] = canonical::number(message.market_state());
    }

    void on(const protocol::BestBidAndOfferMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.bestbidandoffermessage";
        values[entry + ".payload.applicationmessage.data.bestbidandoffermessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.applicationmessage.data.bestbidandoffermessage.instrumentid"] = canonical::number(message.instrument_id());
        values[entry + ".payload.applicationmessage.data.bestbidandoffermessage.mbbprice"] = (message.mbb_price().has_value() ? canonical::scaled((*message.mbb_price()).mantissa(), (*message.mbb_price()).exponent()) : canonical::absent());
        values[entry + ".payload.applicationmessage.data.bestbidandoffermessage.mbbsize"] = canonical::number(message.mbb_size());
        values[entry + ".payload.applicationmessage.data.bestbidandoffermessage.mboprice"] = (message.mbo_price().has_value() ? canonical::scaled((*message.mbo_price()).mantissa(), (*message.mbo_price()).exponent()) : canonical::absent());
        values[entry + ".payload.applicationmessage.data.bestbidandoffermessage.mbosize"] = canonical::number(message.mbo_size());
    }

    void on(const protocol::LastSaleMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.lastsalemessage";
        values[entry + ".payload.applicationmessage.data.lastsalemessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.applicationmessage.data.lastsalemessage.instrumentid"] = canonical::number(message.instrument_id());
        values[entry + ".payload.applicationmessage.data.lastsalemessage.tradeid"] = canonical::number(message.trade_id());
        values[entry + ".payload.applicationmessage.data.lastsalemessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.applicationmessage.data.lastsalemessage.size"] = canonical::number(message.size());
    }

    void on(const protocol::TradeCancelMessage& message) {
        values[entry + ".payload.applicationmessage.data"] = "packet.machmessage.payload.applicationmessage.data.tradecancelmessage";
        values[entry + ".payload.applicationmessage.data.tradecancelmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.applicationmessage.data.tradecancelmessage.tradedate"] = canonical::number(message.trade_date());
        values[entry + ".payload.applicationmessage.data.tradecancelmessage.instrumentid"] = canonical::number(message.instrument_id());
        values[entry + ".payload.applicationmessage.data.tradecancelmessage.tradeid"] = canonical::number(message.trade_id());
        values[entry + ".payload.applicationmessage.data.tradecancelmessage.correctionnumber"] = canonical::number(message.correction_number());
        values[entry + ".payload.applicationmessage.data.tradecancelmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.applicationmessage.data.tradecancelmessage.size"] = canonical::number(message.size());
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
        values[entry + ".payload.applicationmessage.messagetype"] = canonical::number(message.message_type());
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
    std::printf("== Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b (flyweight values)\n");
    int failures = 0;
    failures += check("BestBidAndOfferMessage", "Miax/OnyxFutures.TopOfMarket.Mach.v1.0.b/BestBidAndOfferMessage.pcap", "miax/onyxfutures/topofmarket/mach/v1.0.b/BestBidAndOfferMessage.values");
    failures += check("Heartbeat", "Miax/OnyxFutures.TopOfMarket.Mach.v1.0.b/Heartbeat.pcap", "miax/onyxfutures/topofmarket/mach/v1.0.b/Heartbeat.values");
    failures += check("InstrumentTradingStatusNotificationMessage", "Miax/OnyxFutures.TopOfMarket.Mach.v1.0.b/InstrumentTradingStatusNotificationMessage.pcap", "miax/onyxfutures/topofmarket/mach/v1.0.b/InstrumentTradingStatusNotificationMessage.values");
    failures += check("SystemStateMessage", "Miax/OnyxFutures.TopOfMarket.Mach.v1.0.b/SystemStateMessage.pcap", "miax/onyxfutures/topofmarket/mach/v1.0.b/SystemStateMessage.values");
    return failures == 0 ? 0 : 1;
}
