// Nasdaq.NsmEquities.Qbbo.Itch.v2.1 canonical values, through the Advanced session layer: every value Advanced
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
#include "cpp/advanced/nasdaq/nsmequities/qbbo/itch/v2.1/messages/session.hpp"

namespace protocol = ::nasdaq::nsmequities::qbbo::itch::v2_1;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::packet_header& header, const packet::Frame&) {
        values["packet.packetheader.session"] = canonical::text(std::string(header.session.get().value()), '\0', false);
        values["packet.packetheader.sequencenumber"] = canonical::number(header.sequence_number.get().value());
        values["packet.packetheader.messagecount"] = canonical::number(header.message_count.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::packet_header&) {
        ++index;
    }

    void on_message(const protocol::system_event_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.systemeventmessage";
        values[entry + ".payload.systemeventmessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.systemeventmessage.timestamp"] = canonical::number(message.fields.time_stamp.get().value());
        values[entry + ".payload.systemeventmessage.eventcode"] = canonical::text(canonical::character(message.fields.event_code.get().value()), ' ', false);
    }

    void on_message(const protocol::stock_directory_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.stockdirectorymessage";
        values[entry + ".payload.stockdirectorymessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.stockdirectorymessage.timestamp"] = canonical::number(message.fields.time_stamp.get().value());
        values[entry + ".payload.stockdirectorymessage.stock"] = canonical::text(std::string(message.fields.stock.get().value()), ' ', false);
        values[entry + ".payload.stockdirectorymessage.marketcategory"] = canonical::text(canonical::character(message.fields.market_category.get().value()), ' ', false);
        values[entry + ".payload.stockdirectorymessage.financialstatusindicator"] = canonical::text(canonical::character(message.fields.financial_status_indicator.get().value()), ' ', false);
        values[entry + ".payload.stockdirectorymessage.roundlotsize"] = canonical::number(message.fields.round_lot_size.get().value());
        values[entry + ".payload.stockdirectorymessage.roundlotsonly"] = canonical::text(canonical::character(message.fields.round_lots_only.get().value()), ' ', false);
        values[entry + ".payload.stockdirectorymessage.issueclassification"] = canonical::text(canonical::character(message.fields.issue_classification.get().value()), ' ', false);
        values[entry + ".payload.stockdirectorymessage.issuesubtype"] = canonical::text(std::string(message.fields.issue_subtype.get().value()), ' ', false);
        values[entry + ".payload.stockdirectorymessage.authenticity"] = canonical::text(canonical::character(message.fields.authenticity.get().value()), ' ', false);
        values[entry + ".payload.stockdirectorymessage.shortsalethresholdindicator"] = canonical::text(canonical::character(message.fields.short_sale_threshold_indicator.get().value()), ' ', false);
        values[entry + ".payload.stockdirectorymessage.ipoflag"] = canonical::text(canonical::character(message.fields.ipo_flag.get().value()), ' ', false);
        values[entry + ".payload.stockdirectorymessage.luldreferencepricetier"] = canonical::text(canonical::character(message.fields.luld_reference_price_tier.get().value()), ' ', false);
        values[entry + ".payload.stockdirectorymessage.etpflag"] = canonical::text(canonical::character(message.fields.etp_flag.get().value()), ' ', false);
        values[entry + ".payload.stockdirectorymessage.etpleveragefactor"] = canonical::number(message.fields.etp_leverage_factor.get().value());
        values[entry + ".payload.stockdirectorymessage.inverseindicator"] = canonical::text(canonical::character(message.fields.inverse_indicator.get().value()), ' ', false);
    }

    void on_message(const protocol::stock_trading_action_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.stocktradingactionmessage";
        values[entry + ".payload.stocktradingactionmessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.stocktradingactionmessage.timestamp"] = canonical::number(message.fields.time_stamp.get().value());
        values[entry + ".payload.stocktradingactionmessage.stock"] = canonical::text(std::string(message.fields.stock.get().value()), ' ', false);
        values[entry + ".payload.stocktradingactionmessage.securityclass"] = canonical::text(canonical::character(message.fields.security_class.get().value()), ' ', false);
        values[entry + ".payload.stocktradingactionmessage.currenttradingstate"] = canonical::text(canonical::character(message.fields.current_trading_state.get().value()), ' ', false);
        values[entry + ".payload.stocktradingactionmessage.reason"] = canonical::text(std::string(message.fields.reason.get().value()), ' ', false);
    }

    void on_message(const protocol::reg_sho_restriction_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.regshorestrictionmessage";
        values[entry + ".payload.regshorestrictionmessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.regshorestrictionmessage.timestamp"] = canonical::number(message.fields.time_stamp.get().value());
        values[entry + ".payload.regshorestrictionmessage.stock"] = canonical::text(std::string(message.fields.stock.get().value()), ' ', false);
        values[entry + ".payload.regshorestrictionmessage.regshoaction"] = canonical::text(canonical::character(message.fields.reg_sho_action.get().value()), ' ', false);
    }

    void on_message(const protocol::mwcb_decline_level_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.mwcbdeclinelevelmessage";
        values[entry + ".payload.mwcbdeclinelevelmessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.mwcbdeclinelevelmessage.timestamp"] = canonical::number(message.fields.time_stamp.get().value());
        values[entry + ".payload.mwcbdeclinelevelmessage.level1"] = canonical::scaled(message.fields.level_1.get().value(), -8);
        values[entry + ".payload.mwcbdeclinelevelmessage.level2"] = canonical::scaled(message.fields.level_2.get().value(), -8);
        values[entry + ".payload.mwcbdeclinelevelmessage.level3"] = canonical::scaled(message.fields.level_3.get().value(), -8);
    }

    void on_message(const protocol::mwcb_breach_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.mwcbbreachmessage";
        values[entry + ".payload.mwcbbreachmessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.mwcbbreachmessage.timestamp"] = canonical::number(message.fields.time_stamp.get().value());
        values[entry + ".payload.mwcbbreachmessage.breachedlevel"] = canonical::text(canonical::character(message.fields.breached_level.get().value()), ' ', false);
    }

    void on_message(const protocol::operational_halt_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.operationalhaltmessage";
        values[entry + ".payload.operationalhaltmessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.operationalhaltmessage.timestamp"] = canonical::number(message.fields.time_stamp.get().value());
        values[entry + ".payload.operationalhaltmessage.stock"] = canonical::text(std::string(message.fields.stock.get().value()), ' ', false);
        values[entry + ".payload.operationalhaltmessage.marketcode"] = canonical::text(canonical::character(message.fields.market_code.get().value()), ' ', false);
        values[entry + ".payload.operationalhaltmessage.operationalhaltaction"] = canonical::text(canonical::character(message.fields.operational_halt_action.get().value()), ' ', false);
    }

    void on_message(const protocol::bbo_quotation_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.bboquotationmessage";
        values[entry + ".payload.bboquotationmessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.bboquotationmessage.timestamp"] = canonical::number(message.fields.time_stamp.get().value());
        values[entry + ".payload.bboquotationmessage.stock"] = canonical::text(std::string(message.fields.stock.get().value()), ' ', false);
        values[entry + ".payload.bboquotationmessage.securityclass"] = canonical::text(canonical::character(message.fields.security_class.get().value()), ' ', false);
        values[entry + ".payload.bboquotationmessage.bestbidprice"] = canonical::scaled(message.fields.best_bid_price.get().value(), -4);
        values[entry + ".payload.bboquotationmessage.bestbidsize"] = canonical::number(message.fields.best_bid_size.get().value());
        values[entry + ".payload.bboquotationmessage.bestofferprice"] = canonical::scaled(message.fields.best_offer_price.get().value(), -4);
        values[entry + ".payload.bboquotationmessage.bestoffersize"] = canonical::number(message.fields.best_offer_size.get().value());
    }

    void on_message(const protocol::price_improvement_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.priceimprovementmessage";
        values[entry + ".payload.priceimprovementmessage.tracking"] = canonical::number(message.fields.tracking.get().value());
        values[entry + ".payload.priceimprovementmessage.timestamp"] = canonical::number(message.fields.time_stamp.get().value());
        values[entry + ".payload.priceimprovementmessage.stock"] = canonical::text(std::string(message.fields.stock.get().value()), ' ', false);
        values[entry + ".payload.priceimprovementmessage.interestflag"] = canonical::text(canonical::character(message.fields.interest_flag.get().value()), ' ', false);
    }

    void on_message(const protocol::ipo_quoting_period_update_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.ipoquotingperiodupdatemessage";
        values[entry + ".payload.ipoquotingperiodupdatemessage.tracking"] = canonical::number(message.fields.tracking.get().value());
        values[entry + ".payload.ipoquotingperiodupdatemessage.timestamp"] = canonical::number(message.fields.time_stamp.get().value());
        values[entry + ".payload.ipoquotingperiodupdatemessage.stock"] = canonical::text(std::string(message.fields.stock.get().value()), ' ', false);
        values[entry + ".payload.ipoquotingperiodupdatemessage.ipoquotationreleasetime"] = canonical::number(message.fields.ipo_quotation_release_time.get().value());
        values[entry + ".payload.ipoquotingperiodupdatemessage.ipoquotationreleasequalifier"] = canonical::text(canonical::character(message.fields.ipo_quotation_release_qualifier.get().value()), ' ', false);
        values[entry + ".payload.ipoquotingperiodupdatemessage.ipoprice"] = canonical::scaled(message.fields.ipo_price.get().value(), -4);
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
    std::printf("== Nasdaq.NsmEquities.Qbbo.Itch.v2.1 (advanced values)\n");
    int failures = 0;
    failures += check("BboQuotationMessage", "Nasdaq/NsmEquities.Qbbo.Itch.v2.1/BboQuotationMessage.pcap", "nasdaq/nsmequities/qbbo/itch/v2.1/BboQuotationMessage.values");
    failures += check("RegShoRestrictionMessage", "Nasdaq/NsmEquities.Qbbo.Itch.v2.1/RegShoRestrictionMessage.pcap", "nasdaq/nsmequities/qbbo/itch/v2.1/RegShoRestrictionMessage.values");
    failures += check("StockTradingActionMessage", "Nasdaq/NsmEquities.Qbbo.Itch.v2.1/StockTradingActionMessage.pcap", "nasdaq/nsmequities/qbbo/itch/v2.1/StockTradingActionMessage.values");
    failures += check("SystemEventMessage", "Nasdaq/NsmEquities.Qbbo.Itch.v2.1/SystemEventMessage.pcap", "nasdaq/nsmequities/qbbo/itch/v2.1/SystemEventMessage.values");
    return failures == 0 ? 0 : 1;
}