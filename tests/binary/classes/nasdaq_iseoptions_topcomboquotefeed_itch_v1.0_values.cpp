// Nasdaq.IseOptions.TopComboQuoteFeed.Itch.v1.0 canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/binary/classes/nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/definitions.hpp"

namespace protocol = ::nasdaq::iseoptions::topcomboquotefeed::itch::v1_0;

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

    values["packet.packetheader.session"] = canonical::text(std::string(packet.packet_header().session()), '\0', false);
    values["packet.packetheader.sequencenumber"] = canonical::number(packet.packet_header().sequence_number());
    values["packet.packetheader.messagecount"] = canonical::number(packet.packet_header().message_count());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(each.message_header().message_length());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(each.message_header().message_type()));

        if (const auto* message = dynamic_cast<const protocol::SystemEventMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.systemeventmessage";
            values[entry + ".payload.systemeventmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.systemeventmessage.eventcode"] = canonical::text(canonical::character((*message).event_code()), ' ', false);
            values[entry + ".payload.systemeventmessage.currentyear"] = canonical::number((*message).current_year());
            values[entry + ".payload.systemeventmessage.currentmonth"] = canonical::number((*message).current_month());
            values[entry + ".payload.systemeventmessage.currentday"] = canonical::number((*message).current_day());
            values[entry + ".payload.systemeventmessage.version"] = canonical::number((*message).version());
            values[entry + ".payload.systemeventmessage.subversion"] = canonical::number((*message).sub_version());
        } else if (const auto* message = dynamic_cast<const protocol::ComplexStrategyDirectoryMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.complexstrategydirectorymessage";
            values[entry + ".payload.complexstrategydirectorymessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.complexstrategydirectorymessage.strategyid"] = canonical::number((*message).strategy_id());
            values[entry + ".payload.complexstrategydirectorymessage.strategytype"] = canonical::text(canonical::character((*message).strategy_type()), ' ', false);
            values[entry + ".payload.complexstrategydirectorymessage.source"] = canonical::number((*message).source());
            values[entry + ".payload.complexstrategydirectorymessage.underlyingsymbol"] = canonical::text(std::string((*message).underlying_symbol()), ' ', false);
            values[entry + ".payload.complexstrategydirectorymessage.numberoflegs"] = canonical::number((*message).number_of_legs());
        } else if (const auto* message = dynamic_cast<const protocol::StrategyOpenClosedMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.strategyopenclosedmessage";
            values[entry + ".payload.strategyopenclosedmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.strategyopenclosedmessage.strategyid"] = canonical::number((*message).strategy_id());
            values[entry + ".payload.strategyopenclosedmessage.openstate"] = canonical::text(canonical::character((*message).open_state()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::StrategyTradingActionMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.strategytradingactionmessage";
            values[entry + ".payload.strategytradingactionmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.strategytradingactionmessage.strategyid"] = canonical::number((*message).strategy_id());
            values[entry + ".payload.strategytradingactionmessage.currenttradingstate"] = canonical::text(canonical::character((*message).current_trading_state()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::StrategyBestBidAndAskUpdate*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.strategybestbidandaskupdate";
            values[entry + ".payload.strategybestbidandaskupdate.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.strategybestbidandaskupdate.strategyid"] = canonical::number((*message).strategy_id());
            values[entry + ".payload.strategybestbidandaskupdate.quotecondition"] = canonical::text(canonical::character((*message).quote_condition()), ' ', false);
            values[entry + ".payload.strategybestbidandaskupdate.bidprice"] = canonical::scaled((*message).bid_price().mantissa(), (*message).bid_price().exponent());
            values[entry + ".payload.strategybestbidandaskupdate.bidsize"] = canonical::number((*message).bid_size());
            values[entry + ".payload.strategybestbidandaskupdate.bidcustsize"] = canonical::number((*message).bid_cust_size());
            values[entry + ".payload.strategybestbidandaskupdate.bidprocustsize"] = canonical::number((*message).bid_pro_cust_size());
            values[entry + ".payload.strategybestbidandaskupdate.bidnttsize"] = canonical::number((*message).bid_ntt_size());
            values[entry + ".payload.strategybestbidandaskupdate.bidmarketsize"] = canonical::number((*message).bid_market_size());
            values[entry + ".payload.strategybestbidandaskupdate.bidnttmarketsize"] = canonical::number((*message).bid_ntt_market_size());
            values[entry + ".payload.strategybestbidandaskupdate.askprice"] = canonical::scaled((*message).ask_price().mantissa(), (*message).ask_price().exponent());
            values[entry + ".payload.strategybestbidandaskupdate.asksize"] = canonical::number((*message).ask_size());
            values[entry + ".payload.strategybestbidandaskupdate.askcustsize"] = canonical::number((*message).ask_cust_size());
            values[entry + ".payload.strategybestbidandaskupdate.askprocustsize"] = canonical::number((*message).ask_pro_cust_size());
            values[entry + ".payload.strategybestbidandaskupdate.asknttsize"] = canonical::number((*message).ask_ntt_size());
            values[entry + ".payload.strategybestbidandaskupdate.askmarketsize"] = canonical::number((*message).ask_market_size());
            values[entry + ".payload.strategybestbidandaskupdate.asknttmarketsize"] = canonical::number((*message).ask_ntt_market_size());
        } else if (const auto* message = dynamic_cast<const protocol::StrategyBestBidUpdate*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.strategybestbidupdate";
            values[entry + ".payload.strategybestbidupdate.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.strategybestbidupdate.strategyid"] = canonical::number((*message).strategy_id());
            values[entry + ".payload.strategybestbidupdate.quotecondition"] = canonical::text(canonical::character((*message).quote_condition()), ' ', false);
            values[entry + ".payload.strategybestbidupdate.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
            values[entry + ".payload.strategybestbidupdate.size"] = canonical::number((*message).size());
            values[entry + ".payload.strategybestbidupdate.custsize"] = canonical::number((*message).cust_size());
            values[entry + ".payload.strategybestbidupdate.procustsize"] = canonical::number((*message).pro_cust_size());
            values[entry + ".payload.strategybestbidupdate.nttsize"] = canonical::number((*message).ntt_size());
            values[entry + ".payload.strategybestbidupdate.marketsize"] = canonical::number((*message).market_size());
            values[entry + ".payload.strategybestbidupdate.nttmarketsize"] = canonical::number((*message).ntt_market_size());
        } else if (const auto* message = dynamic_cast<const protocol::StrategyBestAskUpdate*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.strategybestaskupdate";
            values[entry + ".payload.strategybestaskupdate.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.strategybestaskupdate.strategyid"] = canonical::number((*message).strategy_id());
            values[entry + ".payload.strategybestaskupdate.quotecondition"] = canonical::text(canonical::character((*message).quote_condition()), ' ', false);
            values[entry + ".payload.strategybestaskupdate.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
            values[entry + ".payload.strategybestaskupdate.size"] = canonical::number((*message).size());
            values[entry + ".payload.strategybestaskupdate.custsize"] = canonical::number((*message).cust_size());
            values[entry + ".payload.strategybestaskupdate.procustsize"] = canonical::number((*message).pro_cust_size());
            values[entry + ".payload.strategybestaskupdate.nttsize"] = canonical::number((*message).ntt_size());
            values[entry + ".payload.strategybestaskupdate.marketsize"] = canonical::number((*message).market_size());
            values[entry + ".payload.strategybestaskupdate.nttmarketsize"] = canonical::number((*message).ntt_market_size());
        } else if (const auto* message = dynamic_cast<const protocol::ComplexStrategyTickerMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.complexstrategytickermessage";
            values[entry + ".payload.complexstrategytickermessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.complexstrategytickermessage.strategyid"] = canonical::number((*message).strategy_id());
            values[entry + ".payload.complexstrategytickermessage.lastprice"] = canonical::scaled((*message).last_price().mantissa(), (*message).last_price().exponent());
            values[entry + ".payload.complexstrategytickermessage.size"] = canonical::number((*message).size());
            values[entry + ".payload.complexstrategytickermessage.volume"] = canonical::number((*message).volume());
            values[entry + ".payload.complexstrategytickermessage.high"] = canonical::number((*message).high());
            values[entry + ".payload.complexstrategytickermessage.low"] = canonical::number((*message).low());
            values[entry + ".payload.complexstrategytickermessage.first"] = canonical::number((*message).first());
            values[entry + ".payload.complexstrategytickermessage.tradecondition"] = canonical::text(canonical::character((*message).trade_condition()), ' ', false);
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
    std::printf("== Nasdaq.IseOptions.TopComboQuoteFeed.Itch.v1.0 (classes values)\n");
    int failures = 0;
    failures += check("ComplexStrategyDirectoryMessage", "Nasdaq/IseOptions.TopComboQuoteFeed.Itch.v1.0/ComplexStrategyDirectoryMessage.pcap", "nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/ComplexStrategyDirectoryMessage.values");
    failures += check("ComplexStrategyTickerMessage", "Nasdaq/IseOptions.TopComboQuoteFeed.Itch.v1.0/ComplexStrategyTickerMessage.pcap", "nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/ComplexStrategyTickerMessage.values");
    failures += check("Heartbeat", "Nasdaq/IseOptions.TopComboQuoteFeed.Itch.v1.0/Heartbeat.pcap", "nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/Heartbeat.values");
    failures += check("StrategyBestAskUpdate", "Nasdaq/IseOptions.TopComboQuoteFeed.Itch.v1.0/StrategyBestAskUpdate.pcap", "nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/StrategyBestAskUpdate.values");
    failures += check("StrategyBestBidAndAskUpdate", "Nasdaq/IseOptions.TopComboQuoteFeed.Itch.v1.0/StrategyBestBidAndAskUpdate.pcap", "nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/StrategyBestBidAndAskUpdate.values");
    failures += check("StrategyBestBidUpdate", "Nasdaq/IseOptions.TopComboQuoteFeed.Itch.v1.0/StrategyBestBidUpdate.pcap", "nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/StrategyBestBidUpdate.values");
    failures += check("StrategyOpenClosedMessage", "Nasdaq/IseOptions.TopComboQuoteFeed.Itch.v1.0/StrategyOpenClosedMessage.pcap", "nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/StrategyOpenClosedMessage.values");
    failures += check("StrategyTradingActionMessage", "Nasdaq/IseOptions.TopComboQuoteFeed.Itch.v1.0/StrategyTradingActionMessage.pcap", "nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/StrategyTradingActionMessage.values");
    return failures == 0 ? 0 : 1;
}
