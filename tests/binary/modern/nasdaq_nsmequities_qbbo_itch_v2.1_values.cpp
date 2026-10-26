// Nasdaq.NsmEquities.Qbbo.Itch.v2.1 canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/nasdaq/nsmequities/qbbo/itch/v2.1/definitions.hpp"

namespace protocol = ::nasdaq::nsmequities::qbbo::itch::v2_1;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    values["packet.packetheader.session"] = canonical::text(std::string(iterator.packet_header->session.get()), '\0', false);
    values["packet.packetheader.sequencenumber"] = canonical::number(iterator.packet_header->sequence_number.get());
    values["packet.packetheader.messagecount"] = canonical::number(iterator.packet_header->message_count.get());

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(iterator.message_header->message_length.get());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(iterator.message_header->message_type.get()));

        if (iterator.message_type == protocol::SystemEventMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.systemeventmessage";
            [[maybe_unused]] const auto* message = protocol::SystemEventMessage::parse(iterator.message);
            values[entry + ".payload.systemeventmessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.systemeventmessage.timestamp"] = canonical::number(message->time_stamp.get());
            values[entry + ".payload.systemeventmessage.eventcode"] = canonical::text(canonical::character(message->event_code.get()), ' ', false);
        } else if (iterator.message_type == protocol::StockDirectoryMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.stockdirectorymessage";
            [[maybe_unused]] const auto* message = protocol::StockDirectoryMessage::parse(iterator.message);
            values[entry + ".payload.stockdirectorymessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.stockdirectorymessage.timestamp"] = canonical::number(message->time_stamp.get());
            values[entry + ".payload.stockdirectorymessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.marketcategory"] = canonical::text(canonical::character(message->market_category.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.financialstatusindicator"] = canonical::text(canonical::character(message->financial_status_indicator.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.roundlotsize"] = canonical::number(message->round_lot_size.get());
            values[entry + ".payload.stockdirectorymessage.roundlotsonly"] = canonical::text(canonical::character(message->round_lots_only.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.issueclassification"] = canonical::text(canonical::character(message->issue_classification.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.issuesubtype"] = canonical::text(std::string(message->issue_subtype.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.authenticity"] = canonical::text(canonical::character(message->authenticity.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.shortsalethresholdindicator"] = canonical::text(canonical::character(message->short_sale_threshold_indicator.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.ipoflag"] = canonical::text(canonical::character(message->ipo_flag.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.luldreferencepricetier"] = canonical::text(canonical::character(message->luld_reference_price_tier.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.etpflag"] = canonical::text(canonical::character(message->etp_flag.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.etpleveragefactor"] = canonical::number(message->etp_leverage_factor.get());
            values[entry + ".payload.stockdirectorymessage.inverseindicator"] = canonical::text(canonical::character(message->inverse_indicator.get()), ' ', false);
        } else if (iterator.message_type == protocol::StockTradingActionMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.stocktradingactionmessage";
            [[maybe_unused]] const auto* message = protocol::StockTradingActionMessage::parse(iterator.message);
            values[entry + ".payload.stocktradingactionmessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.stocktradingactionmessage.timestamp"] = canonical::number(message->time_stamp.get());
            values[entry + ".payload.stocktradingactionmessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.securityclass"] = canonical::text(canonical::character(message->security_class.get()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.currenttradingstate"] = canonical::text(canonical::character(message->current_trading_state.get()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.reason"] = canonical::text(std::string(message->reason.get()), ' ', false);
        } else if (iterator.message_type == protocol::RegShoRestrictionMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.regshorestrictionmessage";
            [[maybe_unused]] const auto* message = protocol::RegShoRestrictionMessage::parse(iterator.message);
            values[entry + ".payload.regshorestrictionmessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.regshorestrictionmessage.timestamp"] = canonical::number(message->time_stamp.get());
            values[entry + ".payload.regshorestrictionmessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.regshorestrictionmessage.regshoaction"] = canonical::text(canonical::character(message->reg_sho_action.get()), ' ', false);
        } else if (iterator.message_type == protocol::MwcbDeclineLevelMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.mwcbdeclinelevelmessage";
            [[maybe_unused]] const auto* message = protocol::MwcbDeclineLevelMessage::parse(iterator.message);
            values[entry + ".payload.mwcbdeclinelevelmessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.mwcbdeclinelevelmessage.timestamp"] = canonical::number(message->time_stamp.get());
            values[entry + ".payload.mwcbdeclinelevelmessage.level1"] = canonical::scaled(message->level_1.integer(), -8);
            values[entry + ".payload.mwcbdeclinelevelmessage.level2"] = canonical::scaled(message->level_2.integer(), -8);
            values[entry + ".payload.mwcbdeclinelevelmessage.level3"] = canonical::scaled(message->level_3.integer(), -8);
        } else if (iterator.message_type == protocol::MwcbBreachMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.mwcbbreachmessage";
            [[maybe_unused]] const auto* message = protocol::MwcbBreachMessage::parse(iterator.message);
            values[entry + ".payload.mwcbbreachmessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.mwcbbreachmessage.timestamp"] = canonical::number(message->time_stamp.get());
            values[entry + ".payload.mwcbbreachmessage.breachedlevel"] = canonical::text(canonical::character(message->breached_level.get()), ' ', false);
        } else if (iterator.message_type == protocol::OperationalHaltMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.operationalhaltmessage";
            [[maybe_unused]] const auto* message = protocol::OperationalHaltMessage::parse(iterator.message);
            values[entry + ".payload.operationalhaltmessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.operationalhaltmessage.timestamp"] = canonical::number(message->time_stamp.get());
            values[entry + ".payload.operationalhaltmessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.operationalhaltmessage.marketcode"] = canonical::text(canonical::character(message->market_code.get()), ' ', false);
            values[entry + ".payload.operationalhaltmessage.operationalhaltaction"] = canonical::text(canonical::character(message->operational_halt_action.get()), ' ', false);
        } else if (iterator.message_type == protocol::BboQuotationMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.bboquotationmessage";
            [[maybe_unused]] const auto* message = protocol::BboQuotationMessage::parse(iterator.message);
            values[entry + ".payload.bboquotationmessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.bboquotationmessage.timestamp"] = canonical::number(message->time_stamp.get());
            values[entry + ".payload.bboquotationmessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.bboquotationmessage.securityclass"] = canonical::text(canonical::character(message->security_class.get()), ' ', false);
            values[entry + ".payload.bboquotationmessage.bestbidprice"] = canonical::scaled(message->best_bid_price.integer(), -4);
            values[entry + ".payload.bboquotationmessage.bestbidsize"] = canonical::number(message->best_bid_size.get());
            values[entry + ".payload.bboquotationmessage.bestofferprice"] = canonical::scaled(message->best_offer_price.integer(), -4);
            values[entry + ".payload.bboquotationmessage.bestoffersize"] = canonical::number(message->best_offer_size.get());
        } else if (iterator.message_type == protocol::PriceImprovementMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.priceimprovementmessage";
            [[maybe_unused]] const auto* message = protocol::PriceImprovementMessage::parse(iterator.message);
            values[entry + ".payload.priceimprovementmessage.tracking"] = canonical::number(message->tracking.get());
            values[entry + ".payload.priceimprovementmessage.timestamp"] = canonical::number(message->time_stamp.get());
            values[entry + ".payload.priceimprovementmessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.priceimprovementmessage.interestflag"] = canonical::text(canonical::character(message->interest_flag.get()), ' ', false);
        } else if (iterator.message_type == protocol::IpoQuotingPeriodUpdateMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.ipoquotingperiodupdatemessage";
            [[maybe_unused]] const auto* message = protocol::IpoQuotingPeriodUpdateMessage::parse(iterator.message);
            values[entry + ".payload.ipoquotingperiodupdatemessage.tracking"] = canonical::number(message->tracking.get());
            values[entry + ".payload.ipoquotingperiodupdatemessage.timestamp"] = canonical::number(message->time_stamp.get());
            values[entry + ".payload.ipoquotingperiodupdatemessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.ipoquotingperiodupdatemessage.ipoquotationreleasetime"] = canonical::number(message->ipo_quotation_release_time.get());
            values[entry + ".payload.ipoquotingperiodupdatemessage.ipoquotationreleasequalifier"] = canonical::text(canonical::character(message->ipo_quotation_release_qualifier.get()), ' ', false);
            values[entry + ".payload.ipoquotingperiodupdatemessage.ipoprice"] = canonical::scaled(message->ipo_price.integer(), -4);
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
    std::printf("== Nasdaq.NsmEquities.Qbbo.Itch.v2.1 (modern values)\n");
    int failures = 0;
    failures += check("BboQuotationMessage", "Nasdaq/NsmEquities.Qbbo.Itch.v2.1/BboQuotationMessage.pcap", "nasdaq/nsmequities/qbbo/itch/v2.1/BboQuotationMessage.values");
    failures += check("RegShoRestrictionMessage", "Nasdaq/NsmEquities.Qbbo.Itch.v2.1/RegShoRestrictionMessage.pcap", "nasdaq/nsmequities/qbbo/itch/v2.1/RegShoRestrictionMessage.values");
    failures += check("StockTradingActionMessage", "Nasdaq/NsmEquities.Qbbo.Itch.v2.1/StockTradingActionMessage.pcap", "nasdaq/nsmequities/qbbo/itch/v2.1/StockTradingActionMessage.values");
    failures += check("SystemEventMessage", "Nasdaq/NsmEquities.Qbbo.Itch.v2.1/SystemEventMessage.pcap", "nasdaq/nsmequities/qbbo/itch/v2.1/SystemEventMessage.values");
    return failures == 0 ? 0 : 1;
}
