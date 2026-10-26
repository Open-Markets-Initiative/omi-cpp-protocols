// Nasdaq.NsmEquities.Qbbo.Itch.v2.1 canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/definitions.hpp"

namespace protocol = ::nasdaq::nsmequities::qbbo::itch::v2_1;

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
            values[entry + ".payload.systemeventmessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.systemeventmessage.timestamp"] = canonical::number((*message).time_stamp());
            values[entry + ".payload.systemeventmessage.eventcode"] = canonical::text(canonical::character((*message).event_code()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::StockDirectoryMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.stockdirectorymessage";
            values[entry + ".payload.stockdirectorymessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.stockdirectorymessage.timestamp"] = canonical::number((*message).time_stamp());
            values[entry + ".payload.stockdirectorymessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.marketcategory"] = canonical::text(canonical::character((*message).market_category()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.financialstatusindicator"] = canonical::text(canonical::character((*message).financial_status_indicator()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.roundlotsize"] = canonical::number((*message).round_lot_size());
            values[entry + ".payload.stockdirectorymessage.roundlotsonly"] = canonical::text(canonical::character((*message).round_lots_only()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.issueclassification"] = canonical::text(canonical::character((*message).issue_classification()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.issuesubtype"] = canonical::text(std::string((*message).issue_subtype()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.authenticity"] = canonical::text(canonical::character((*message).authenticity()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.shortsalethresholdindicator"] = canonical::text(canonical::character((*message).short_sale_threshold_indicator()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.ipoflag"] = canonical::text(canonical::character((*message).ipo_flag()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.luldreferencepricetier"] = canonical::text(canonical::character((*message).luld_reference_price_tier()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.etpflag"] = canonical::text(canonical::character((*message).etp_flag()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.etpleveragefactor"] = canonical::number((*message).etp_leverage_factor());
            values[entry + ".payload.stockdirectorymessage.inverseindicator"] = canonical::text(canonical::character((*message).inverse_indicator()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::StockTradingActionMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.stocktradingactionmessage";
            values[entry + ".payload.stocktradingactionmessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.stocktradingactionmessage.timestamp"] = canonical::number((*message).time_stamp());
            values[entry + ".payload.stocktradingactionmessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.securityclass"] = canonical::text(canonical::character((*message).security_class()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.currenttradingstate"] = canonical::text(canonical::character((*message).current_trading_state()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.reason"] = canonical::text(std::string((*message).reason()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::RegShoRestrictionMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.regshorestrictionmessage";
            values[entry + ".payload.regshorestrictionmessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.regshorestrictionmessage.timestamp"] = canonical::number((*message).time_stamp());
            values[entry + ".payload.regshorestrictionmessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.regshorestrictionmessage.regshoaction"] = canonical::text(canonical::character((*message).reg_sho_action()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::MwcbDeclineLevelMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.mwcbdeclinelevelmessage";
            values[entry + ".payload.mwcbdeclinelevelmessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.mwcbdeclinelevelmessage.timestamp"] = canonical::number((*message).time_stamp());
            values[entry + ".payload.mwcbdeclinelevelmessage.level1"] = canonical::scaled((*message).level_1().mantissa(), (*message).level_1().exponent());
            values[entry + ".payload.mwcbdeclinelevelmessage.level2"] = canonical::scaled((*message).level_2().mantissa(), (*message).level_2().exponent());
            values[entry + ".payload.mwcbdeclinelevelmessage.level3"] = canonical::scaled((*message).level_3().mantissa(), (*message).level_3().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::MwcbBreachMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.mwcbbreachmessage";
            values[entry + ".payload.mwcbbreachmessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.mwcbbreachmessage.timestamp"] = canonical::number((*message).time_stamp());
            values[entry + ".payload.mwcbbreachmessage.breachedlevel"] = canonical::text(canonical::character((*message).breached_level()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::OperationalHaltMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.operationalhaltmessage";
            values[entry + ".payload.operationalhaltmessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.operationalhaltmessage.timestamp"] = canonical::number((*message).time_stamp());
            values[entry + ".payload.operationalhaltmessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.operationalhaltmessage.marketcode"] = canonical::text(canonical::character((*message).market_code()), ' ', false);
            values[entry + ".payload.operationalhaltmessage.operationalhaltaction"] = canonical::text(canonical::character((*message).operational_halt_action()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::BboQuotationMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.bboquotationmessage";
            values[entry + ".payload.bboquotationmessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.bboquotationmessage.timestamp"] = canonical::number((*message).time_stamp());
            values[entry + ".payload.bboquotationmessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.bboquotationmessage.securityclass"] = canonical::text(canonical::character((*message).security_class()), ' ', false);
            values[entry + ".payload.bboquotationmessage.bestbidprice"] = canonical::scaled((*message).best_bid_price().mantissa(), (*message).best_bid_price().exponent());
            values[entry + ".payload.bboquotationmessage.bestbidsize"] = canonical::number((*message).best_bid_size());
            values[entry + ".payload.bboquotationmessage.bestofferprice"] = canonical::scaled((*message).best_offer_price().mantissa(), (*message).best_offer_price().exponent());
            values[entry + ".payload.bboquotationmessage.bestoffersize"] = canonical::number((*message).best_offer_size());
        } else if (const auto* message = dynamic_cast<const protocol::PriceImprovementMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.priceimprovementmessage";
            values[entry + ".payload.priceimprovementmessage.tracking"] = canonical::number((*message).tracking());
            values[entry + ".payload.priceimprovementmessage.timestamp"] = canonical::number((*message).time_stamp());
            values[entry + ".payload.priceimprovementmessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.priceimprovementmessage.interestflag"] = canonical::text(canonical::character((*message).interest_flag()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::IpoQuotingPeriodUpdateMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.ipoquotingperiodupdatemessage";
            values[entry + ".payload.ipoquotingperiodupdatemessage.tracking"] = canonical::number((*message).tracking());
            values[entry + ".payload.ipoquotingperiodupdatemessage.timestamp"] = canonical::number((*message).time_stamp());
            values[entry + ".payload.ipoquotingperiodupdatemessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.ipoquotingperiodupdatemessage.ipoquotationreleasetime"] = canonical::number((*message).ipo_quotation_release_time());
            values[entry + ".payload.ipoquotingperiodupdatemessage.ipoquotationreleasequalifier"] = canonical::text(canonical::character((*message).ipo_quotation_release_qualifier()), ' ', false);
            values[entry + ".payload.ipoquotingperiodupdatemessage.ipoprice"] = canonical::scaled((*message).ipo_price().mantissa(), (*message).ipo_price().exponent());
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
    std::printf("== Nasdaq.NsmEquities.Qbbo.Itch.v2.1 (classes values)\n");
    int failures = 0;
    failures += check("BboQuotationMessage", "Nasdaq/NsmEquities.Qbbo.Itch.v2.1/BboQuotationMessage.pcap", "nasdaq/nsmequities/qbbo/itch/v2.1/BboQuotationMessage.values");
    failures += check("RegShoRestrictionMessage", "Nasdaq/NsmEquities.Qbbo.Itch.v2.1/RegShoRestrictionMessage.pcap", "nasdaq/nsmequities/qbbo/itch/v2.1/RegShoRestrictionMessage.values");
    failures += check("StockTradingActionMessage", "Nasdaq/NsmEquities.Qbbo.Itch.v2.1/StockTradingActionMessage.pcap", "nasdaq/nsmequities/qbbo/itch/v2.1/StockTradingActionMessage.values");
    failures += check("SystemEventMessage", "Nasdaq/NsmEquities.Qbbo.Itch.v2.1/SystemEventMessage.pcap", "nasdaq/nsmequities/qbbo/itch/v2.1/SystemEventMessage.values");
    return failures == 0 ? 0 : 1;
}