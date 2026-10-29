// Nasdaq.NsmEquities.NlsPlus.Itch.v3.0 canonical values, through the Advanced session layer: every value Advanced
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
#include "cpp/binary/advanced/nasdaq/nsmequities/nlsplus/itch/v3.0/messages/session.hpp"

namespace protocol = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

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
        values[entry + ".messageheader.trackingnumber"] = canonical::number(message.header.tracking_number.get().value());
        values[entry + ".messageheader.timestamp"] = canonical::number(message.header.timestamp.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.systemeventmessage";
        values[entry + ".payload.systemeventmessage.eventcode"] = canonical::text(canonical::character(message.fields.event_code.get().value()), ' ', false);
    }

    void on_message(const protocol::trade_report_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.trackingnumber"] = canonical::number(message.header.tracking_number.get().value());
        values[entry + ".messageheader.timestamp"] = canonical::number(message.header.timestamp.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.tradereportmessage";
        values[entry + ".payload.tradereportmessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character(message.fields.originating_market_center_identifier.get().value()), ' ', false);
        values[entry + ".payload.tradereportmessage.issuesymbol"] = canonical::text(std::string(message.fields.issue_symbol.get().value()), ' ', false);
        values[entry + ".payload.tradereportmessage.securityclass"] = canonical::text(canonical::character(message.fields.security_class.get().value()), ' ', false);
        values[entry + ".payload.tradereportmessage.tradecontrolnumber"] = canonical::text(std::string(message.fields.trade_control_number.get().value()), ' ', false);
        values[entry + ".payload.tradereportmessage.tradeprice"] = canonical::scaled(message.fields.trade_price.get().value(), -4);
        values[entry + ".payload.tradereportmessage.tradesize"] = canonical::number(message.fields.trade_size.get().value());
        values[entry + ".payload.tradereportmessage.saleconditionmodifier.settlementtype"] = canonical::text(canonical::character(message.fields.sale_condition_modifier.settlement_type.get().value()), ' ', false);
        values[entry + ".payload.tradereportmessage.saleconditionmodifier.tradethroughexemption"] = canonical::text(canonical::character(message.fields.sale_condition_modifier.trade_through_exemption.get().value()), ' ', false);
        values[entry + ".payload.tradereportmessage.saleconditionmodifier.extendedhoursorsoldcode"] = canonical::text(canonical::character(message.fields.sale_condition_modifier.extended_hours_or_sold_code.get().value()), ' ', false);
        values[entry + ".payload.tradereportmessage.saleconditionmodifier.specialsalecondition"] = canonical::text(canonical::character(message.fields.sale_condition_modifier.special_sale_condition.get().value()), ' ', false);
        values[entry + ".payload.tradereportmessage.consolidatedvolume"] = canonical::number(message.fields.consolidated_volume.get().value());
    }

    void on_message(const protocol::long_form_trade_report_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.trackingnumber"] = canonical::number(message.header.tracking_number.get().value());
        values[entry + ".messageheader.timestamp"] = canonical::number(message.header.timestamp.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.longformtradereportmessage";
        values[entry + ".payload.longformtradereportmessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character(message.fields.originating_market_center_identifier.get().value()), ' ', false);
        values[entry + ".payload.longformtradereportmessage.issuesymbol"] = canonical::text(std::string(message.fields.issue_symbol.get().value()), ' ', false);
        values[entry + ".payload.longformtradereportmessage.securityclass"] = canonical::text(canonical::character(message.fields.security_class.get().value()), ' ', false);
        values[entry + ".payload.longformtradereportmessage.tradecontrolnumber"] = canonical::text(std::string(message.fields.trade_control_number.get().value()), ' ', false);
        values[entry + ".payload.longformtradereportmessage.tradepricelong"] = canonical::scaled(message.fields.trade_price_long.get().value(), -4);
        values[entry + ".payload.longformtradereportmessage.tradesize"] = canonical::number(message.fields.trade_size.get().value());
        values[entry + ".payload.longformtradereportmessage.saleconditionmodifier.settlementtype"] = canonical::text(canonical::character(message.fields.sale_condition_modifier.settlement_type.get().value()), ' ', false);
        values[entry + ".payload.longformtradereportmessage.saleconditionmodifier.tradethroughexemption"] = canonical::text(canonical::character(message.fields.sale_condition_modifier.trade_through_exemption.get().value()), ' ', false);
        values[entry + ".payload.longformtradereportmessage.saleconditionmodifier.extendedhoursorsoldcode"] = canonical::text(canonical::character(message.fields.sale_condition_modifier.extended_hours_or_sold_code.get().value()), ' ', false);
        values[entry + ".payload.longformtradereportmessage.saleconditionmodifier.specialsalecondition"] = canonical::text(canonical::character(message.fields.sale_condition_modifier.special_sale_condition.get().value()), ' ', false);
        values[entry + ".payload.longformtradereportmessage.consolidatedvolume"] = canonical::number(message.fields.consolidated_volume.get().value());
    }

    void on_message(const protocol::next_shares_trade_report_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.trackingnumber"] = canonical::number(message.header.tracking_number.get().value());
        values[entry + ".messageheader.timestamp"] = canonical::number(message.header.timestamp.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.nextsharestradereportmessage";
        values[entry + ".payload.nextsharestradereportmessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character(message.fields.originating_market_center_identifier.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradereportmessage.nextsharessymbol"] = canonical::text(std::string(message.fields.next_shares_symbol.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradereportmessage.securityclass"] = canonical::text(canonical::character(message.fields.security_class.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradereportmessage.tradecontrolnumber"] = canonical::text(std::string(message.fields.trade_control_number.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradereportmessage.proxyprice"] = canonical::scaled(message.fields.proxy_price.get().value(), -4);
        values[entry + ".payload.nextsharestradereportmessage.tradesize"] = canonical::number(message.fields.trade_size.get().value());
        values[entry + ".payload.nextsharestradereportmessage.navoffsetamount"] = canonical::scaled(message.fields.nav_offset_amount.get().value(), -4);
        values[entry + ".payload.nextsharestradereportmessage.saleconditionmodifier.settlementtype"] = canonical::text(canonical::character(message.fields.sale_condition_modifier.settlement_type.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradereportmessage.saleconditionmodifier.tradethroughexemption"] = canonical::text(canonical::character(message.fields.sale_condition_modifier.trade_through_exemption.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradereportmessage.saleconditionmodifier.extendedhoursorsoldcode"] = canonical::text(canonical::character(message.fields.sale_condition_modifier.extended_hours_or_sold_code.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradereportmessage.saleconditionmodifier.specialsalecondition"] = canonical::text(canonical::character(message.fields.sale_condition_modifier.special_sale_condition.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradereportmessage.consolidatedvolume"] = canonical::number(message.fields.consolidated_volume.get().value());
    }

    void on_message(const protocol::trade_cancel_error_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.trackingnumber"] = canonical::number(message.header.tracking_number.get().value());
        values[entry + ".messageheader.timestamp"] = canonical::number(message.header.timestamp.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.tradecancelerrormessage";
        values[entry + ".payload.tradecancelerrormessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character(message.fields.originating_market_center_identifier.get().value()), ' ', false);
        values[entry + ".payload.tradecancelerrormessage.issuesymbol"] = canonical::text(std::string(message.fields.issue_symbol.get().value()), ' ', false);
        values[entry + ".payload.tradecancelerrormessage.securityclass"] = canonical::text(canonical::character(message.fields.security_class.get().value()), ' ', false);
        values[entry + ".payload.tradecancelerrormessage.originaltradecontrolnumber"] = canonical::text(std::string(message.fields.original_trade_control_number.get().value()), ' ', false);
        values[entry + ".payload.tradecancelerrormessage.originaltradeprice"] = canonical::scaled(message.fields.original_trade_price.get().value(), -4);
        values[entry + ".payload.tradecancelerrormessage.originaltradesize"] = canonical::number(message.fields.original_trade_size.get().value());
        values[entry + ".payload.tradecancelerrormessage.originalsaleconditionmodifier.originalsettlementtype"] = canonical::text(canonical::character(message.fields.original_sale_condition_modifier.original_settlement_type.get().value()), ' ', false);
        values[entry + ".payload.tradecancelerrormessage.originalsaleconditionmodifier.originaltradethroughexemption"] = canonical::text(canonical::character(message.fields.original_sale_condition_modifier.original_trade_through_exemption.get().value()), ' ', false);
        values[entry + ".payload.tradecancelerrormessage.originalsaleconditionmodifier.originalextendedhoursorsoldcode"] = canonical::text(canonical::character(message.fields.original_sale_condition_modifier.original_extended_hours_or_sold_code.get().value()), ' ', false);
        values[entry + ".payload.tradecancelerrormessage.originalsaleconditionmodifier.originalspecialsalecondition"] = canonical::text(canonical::character(message.fields.original_sale_condition_modifier.original_special_sale_condition.get().value()), ' ', false);
        values[entry + ".payload.tradecancelerrormessage.consolidatedvolume"] = canonical::number(message.fields.consolidated_volume.get().value());
    }

    void on_message(const protocol::long_form_trade_cancel_error_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.trackingnumber"] = canonical::number(message.header.tracking_number.get().value());
        values[entry + ".messageheader.timestamp"] = canonical::number(message.header.timestamp.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.longformtradecancelerrormessage";
        values[entry + ".payload.longformtradecancelerrormessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character(message.fields.originating_market_center_identifier.get().value()), ' ', false);
        values[entry + ".payload.longformtradecancelerrormessage.issuesymbol"] = canonical::text(std::string(message.fields.issue_symbol.get().value()), ' ', false);
        values[entry + ".payload.longformtradecancelerrormessage.securityclass"] = canonical::text(canonical::character(message.fields.security_class.get().value()), ' ', false);
        values[entry + ".payload.longformtradecancelerrormessage.originaltradecontrolnumber"] = canonical::text(std::string(message.fields.original_trade_control_number.get().value()), ' ', false);
        values[entry + ".payload.longformtradecancelerrormessage.originaltradepricelong"] = canonical::scaled(message.fields.original_trade_price_long.get().value(), -4);
        values[entry + ".payload.longformtradecancelerrormessage.originaltradesize"] = canonical::number(message.fields.original_trade_size.get().value());
        values[entry + ".payload.longformtradecancelerrormessage.originalsaleconditionmodifier.originalsettlementtype"] = canonical::text(canonical::character(message.fields.original_sale_condition_modifier.original_settlement_type.get().value()), ' ', false);
        values[entry + ".payload.longformtradecancelerrormessage.originalsaleconditionmodifier.originaltradethroughexemption"] = canonical::text(canonical::character(message.fields.original_sale_condition_modifier.original_trade_through_exemption.get().value()), ' ', false);
        values[entry + ".payload.longformtradecancelerrormessage.originalsaleconditionmodifier.originalextendedhoursorsoldcode"] = canonical::text(canonical::character(message.fields.original_sale_condition_modifier.original_extended_hours_or_sold_code.get().value()), ' ', false);
        values[entry + ".payload.longformtradecancelerrormessage.originalsaleconditionmodifier.originalspecialsalecondition"] = canonical::text(canonical::character(message.fields.original_sale_condition_modifier.original_special_sale_condition.get().value()), ' ', false);
        values[entry + ".payload.longformtradecancelerrormessage.consolidatedvolume"] = canonical::number(message.fields.consolidated_volume.get().value());
    }

    void on_message(const protocol::next_shares_trade_cancel_error_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.trackingnumber"] = canonical::number(message.header.tracking_number.get().value());
        values[entry + ".messageheader.timestamp"] = canonical::number(message.header.timestamp.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.nextsharestradecancelerrormessage";
        values[entry + ".payload.nextsharestradecancelerrormessage.marketcenter"] = canonical::text(canonical::character(message.fields.market_center.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradecancelerrormessage.issuesymbol"] = canonical::text(std::string(message.fields.issue_symbol.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradecancelerrormessage.securityclass"] = canonical::text(canonical::character(message.fields.security_class.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradecancelerrormessage.originaltradecontrolnumber"] = canonical::text(std::string(message.fields.original_trade_control_number.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradecancelerrormessage.originalproxyprice"] = canonical::scaled(message.fields.original_proxy_price.get().value(), -4);
        values[entry + ".payload.nextsharestradecancelerrormessage.originalnavoffsetamount"] = canonical::scaled(message.fields.original_nav_offset_amount.get().value(), -4);
        values[entry + ".payload.nextsharestradecancelerrormessage.originaltradesize"] = canonical::number(message.fields.original_trade_size.get().value());
        values[entry + ".payload.nextsharestradecancelerrormessage.originalsaleconditionmodifier.originalsettlementtype"] = canonical::text(canonical::character(message.fields.original_sale_condition_modifier.original_settlement_type.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradecancelerrormessage.originalsaleconditionmodifier.originaltradethroughexemption"] = canonical::text(canonical::character(message.fields.original_sale_condition_modifier.original_trade_through_exemption.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradecancelerrormessage.originalsaleconditionmodifier.originalextendedhoursorsoldcode"] = canonical::text(canonical::character(message.fields.original_sale_condition_modifier.original_extended_hours_or_sold_code.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradecancelerrormessage.originalsaleconditionmodifier.originalspecialsalecondition"] = canonical::text(canonical::character(message.fields.original_sale_condition_modifier.original_special_sale_condition.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradecancelerrormessage.consolidatedvolume"] = canonical::number(message.fields.consolidated_volume.get().value());
    }

    void on_message(const protocol::trade_correction_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.trackingnumber"] = canonical::number(message.header.tracking_number.get().value());
        values[entry + ".messageheader.timestamp"] = canonical::number(message.header.timestamp.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.tradecorrectionmessage";
        values[entry + ".payload.tradecorrectionmessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character(message.fields.originating_market_center_identifier.get().value()), ' ', false);
        values[entry + ".payload.tradecorrectionmessage.issuesymbol"] = canonical::text(std::string(message.fields.issue_symbol.get().value()), ' ', false);
        values[entry + ".payload.tradecorrectionmessage.securityclass"] = canonical::text(canonical::character(message.fields.security_class.get().value()), ' ', false);
        values[entry + ".payload.tradecorrectionmessage.originaltradecontrolnumber"] = canonical::text(std::string(message.fields.original_trade_control_number.get().value()), ' ', false);
        values[entry + ".payload.tradecorrectionmessage.originaltradeprice"] = canonical::scaled(message.fields.original_trade_price.get().value(), -4);
        values[entry + ".payload.tradecorrectionmessage.originaltradesize"] = canonical::number(message.fields.original_trade_size.get().value());
        values[entry + ".payload.tradecorrectionmessage.originalsaleconditionmodifier.originalsettlementtype"] = canonical::text(canonical::character(message.fields.original_sale_condition_modifier.original_settlement_type.get().value()), ' ', false);
        values[entry + ".payload.tradecorrectionmessage.originalsaleconditionmodifier.originaltradethroughexemption"] = canonical::text(canonical::character(message.fields.original_sale_condition_modifier.original_trade_through_exemption.get().value()), ' ', false);
        values[entry + ".payload.tradecorrectionmessage.originalsaleconditionmodifier.originalextendedhoursorsoldcode"] = canonical::text(canonical::character(message.fields.original_sale_condition_modifier.original_extended_hours_or_sold_code.get().value()), ' ', false);
        values[entry + ".payload.tradecorrectionmessage.originalsaleconditionmodifier.originalspecialsalecondition"] = canonical::text(canonical::character(message.fields.original_sale_condition_modifier.original_special_sale_condition.get().value()), ' ', false);
        values[entry + ".payload.tradecorrectionmessage.correctedtradecontrolnumber"] = canonical::text(std::string(message.fields.corrected_trade_control_number.get().value()), ' ', false);
        values[entry + ".payload.tradecorrectionmessage.correctedtradeprice"] = canonical::scaled(message.fields.corrected_trade_price.get().value(), -4);
        values[entry + ".payload.tradecorrectionmessage.correctedtradesize"] = canonical::number(message.fields.corrected_trade_size.get().value());
        values[entry + ".payload.tradecorrectionmessage.correctedsaleconditionmodifier.correctedsettlementtype"] = canonical::text(canonical::character(message.fields.corrected_sale_condition_modifier.corrected_settlement_type.get().value()), ' ', false);
        values[entry + ".payload.tradecorrectionmessage.correctedsaleconditionmodifier.correctedtradethroughexemption"] = canonical::text(canonical::character(message.fields.corrected_sale_condition_modifier.corrected_trade_through_exemption.get().value()), ' ', false);
        values[entry + ".payload.tradecorrectionmessage.correctedsaleconditionmodifier.correctedextendedhoursorsoldcode"] = canonical::text(canonical::character(message.fields.corrected_sale_condition_modifier.corrected_extended_hours_or_sold_code.get().value()), ' ', false);
        values[entry + ".payload.tradecorrectionmessage.correctedsaleconditionmodifier.correctedspecialsalecondition"] = canonical::text(canonical::character(message.fields.corrected_sale_condition_modifier.corrected_special_sale_condition.get().value()), ' ', false);
        values[entry + ".payload.tradecorrectionmessage.consolidatedvolume"] = canonical::number(message.fields.consolidated_volume.get().value());
    }

    void on_message(const protocol::long_form_trade_correction_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.trackingnumber"] = canonical::number(message.header.tracking_number.get().value());
        values[entry + ".messageheader.timestamp"] = canonical::number(message.header.timestamp.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.longformtradecorrectionmessage";
        values[entry + ".payload.longformtradecorrectionmessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character(message.fields.originating_market_center_identifier.get().value()), ' ', false);
        values[entry + ".payload.longformtradecorrectionmessage.issuesymbol"] = canonical::text(std::string(message.fields.issue_symbol.get().value()), ' ', false);
        values[entry + ".payload.longformtradecorrectionmessage.securityclass"] = canonical::text(canonical::character(message.fields.security_class.get().value()), ' ', false);
        values[entry + ".payload.longformtradecorrectionmessage.originaltradecontrolnumber"] = canonical::text(std::string(message.fields.original_trade_control_number.get().value()), ' ', false);
        values[entry + ".payload.longformtradecorrectionmessage.originaltradepricelong"] = canonical::scaled(message.fields.original_trade_price_long.get().value(), -4);
        values[entry + ".payload.longformtradecorrectionmessage.originaltradesize"] = canonical::number(message.fields.original_trade_size.get().value());
        values[entry + ".payload.longformtradecorrectionmessage.originalsaleconditionmodifier.originalsettlementtype"] = canonical::text(canonical::character(message.fields.original_sale_condition_modifier.original_settlement_type.get().value()), ' ', false);
        values[entry + ".payload.longformtradecorrectionmessage.originalsaleconditionmodifier.originaltradethroughexemption"] = canonical::text(canonical::character(message.fields.original_sale_condition_modifier.original_trade_through_exemption.get().value()), ' ', false);
        values[entry + ".payload.longformtradecorrectionmessage.originalsaleconditionmodifier.originalextendedhoursorsoldcode"] = canonical::text(canonical::character(message.fields.original_sale_condition_modifier.original_extended_hours_or_sold_code.get().value()), ' ', false);
        values[entry + ".payload.longformtradecorrectionmessage.originalsaleconditionmodifier.originalspecialsalecondition"] = canonical::text(canonical::character(message.fields.original_sale_condition_modifier.original_special_sale_condition.get().value()), ' ', false);
        values[entry + ".payload.longformtradecorrectionmessage.correctedtradecontrolnumber"] = canonical::text(std::string(message.fields.corrected_trade_control_number.get().value()), ' ', false);
        values[entry + ".payload.longformtradecorrectionmessage.correctedtradepricelong"] = canonical::scaled(message.fields.corrected_trade_price_long.get().value(), -4);
        values[entry + ".payload.longformtradecorrectionmessage.correctedtradesize"] = canonical::number(message.fields.corrected_trade_size.get().value());
        values[entry + ".payload.longformtradecorrectionmessage.correctedsaleconditionmodifier.correctedsettlementtype"] = canonical::text(canonical::character(message.fields.corrected_sale_condition_modifier.corrected_settlement_type.get().value()), ' ', false);
        values[entry + ".payload.longformtradecorrectionmessage.correctedsaleconditionmodifier.correctedtradethroughexemption"] = canonical::text(canonical::character(message.fields.corrected_sale_condition_modifier.corrected_trade_through_exemption.get().value()), ' ', false);
        values[entry + ".payload.longformtradecorrectionmessage.correctedsaleconditionmodifier.correctedextendedhoursorsoldcode"] = canonical::text(canonical::character(message.fields.corrected_sale_condition_modifier.corrected_extended_hours_or_sold_code.get().value()), ' ', false);
        values[entry + ".payload.longformtradecorrectionmessage.correctedsaleconditionmodifier.correctedspecialsalecondition"] = canonical::text(canonical::character(message.fields.corrected_sale_condition_modifier.corrected_special_sale_condition.get().value()), ' ', false);
        values[entry + ".payload.longformtradecorrectionmessage.consolidatedvolume"] = canonical::number(message.fields.consolidated_volume.get().value());
    }

    void on_message(const protocol::next_shares_trade_correction_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.trackingnumber"] = canonical::number(message.header.tracking_number.get().value());
        values[entry + ".messageheader.timestamp"] = canonical::number(message.header.timestamp.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.nextsharestradecorrectionmessage";
        values[entry + ".payload.nextsharestradecorrectionmessage.marketcenter"] = canonical::text(canonical::character(message.fields.market_center.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradecorrectionmessage.issuesymbol"] = canonical::text(std::string(message.fields.issue_symbol.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradecorrectionmessage.securityclass"] = canonical::text(canonical::character(message.fields.security_class.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradecorrectionmessage.originaltradecontrolnumber"] = canonical::text(std::string(message.fields.original_trade_control_number.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradecorrectionmessage.originalproxyprice"] = canonical::scaled(message.fields.original_proxy_price.get().value(), -4);
        values[entry + ".payload.nextsharestradecorrectionmessage.originalnavoffsetamount"] = canonical::scaled(message.fields.original_nav_offset_amount.get().value(), -4);
        values[entry + ".payload.nextsharestradecorrectionmessage.originaltradesize"] = canonical::number(message.fields.original_trade_size.get().value());
        values[entry + ".payload.nextsharestradecorrectionmessage.originalsaleconditionmodifier.originalsettlementtype"] = canonical::text(canonical::character(message.fields.original_sale_condition_modifier.original_settlement_type.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradecorrectionmessage.originalsaleconditionmodifier.originaltradethroughexemption"] = canonical::text(canonical::character(message.fields.original_sale_condition_modifier.original_trade_through_exemption.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradecorrectionmessage.originalsaleconditionmodifier.originalextendedhoursorsoldcode"] = canonical::text(canonical::character(message.fields.original_sale_condition_modifier.original_extended_hours_or_sold_code.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradecorrectionmessage.originalsaleconditionmodifier.originalspecialsalecondition"] = canonical::text(canonical::character(message.fields.original_sale_condition_modifier.original_special_sale_condition.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradecorrectionmessage.correctedtradecontrolnumber"] = canonical::text(std::string(message.fields.corrected_trade_control_number.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradecorrectionmessage.correctedproxyprice"] = canonical::scaled(message.fields.corrected_proxy_price.get().value(), -4);
        values[entry + ".payload.nextsharestradecorrectionmessage.correctednavoffsetamount"] = canonical::scaled(message.fields.corrected_nav_offset_amount.get().value(), -4);
        values[entry + ".payload.nextsharestradecorrectionmessage.correctedtradesize"] = canonical::number(message.fields.corrected_trade_size.get().value());
        values[entry + ".payload.nextsharestradecorrectionmessage.correctedsaleconditionmodifier.correctedsettlementtype"] = canonical::text(canonical::character(message.fields.corrected_sale_condition_modifier.corrected_settlement_type.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradecorrectionmessage.correctedsaleconditionmodifier.correctedtradethroughexemption"] = canonical::text(canonical::character(message.fields.corrected_sale_condition_modifier.corrected_trade_through_exemption.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradecorrectionmessage.correctedsaleconditionmodifier.correctedextendedhoursorsoldcode"] = canonical::text(canonical::character(message.fields.corrected_sale_condition_modifier.corrected_extended_hours_or_sold_code.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradecorrectionmessage.correctedsaleconditionmodifier.correctedspecialsalecondition"] = canonical::text(canonical::character(message.fields.corrected_sale_condition_modifier.corrected_special_sale_condition.get().value()), ' ', false);
        values[entry + ".payload.nextsharestradecorrectionmessage.consolidatedvolume"] = canonical::number(message.fields.consolidated_volume.get().value());
    }

    void on_message(const protocol::stock_trading_action_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.trackingnumber"] = canonical::number(message.header.tracking_number.get().value());
        values[entry + ".messageheader.timestamp"] = canonical::number(message.header.timestamp.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.stocktradingactionmessage";
        values[entry + ".payload.stocktradingactionmessage.reserved"] = canonical::text(canonical::character(message.fields.reserved.get().value()), ' ', false);
        values[entry + ".payload.stocktradingactionmessage.issuesymbol"] = canonical::text(std::string(message.fields.issue_symbol.get().value()), ' ', false);
        values[entry + ".payload.stocktradingactionmessage.securityclass"] = canonical::text(canonical::character(message.fields.security_class.get().value()), ' ', false);
        values[entry + ".payload.stocktradingactionmessage.currenttradingstate"] = canonical::text(canonical::character(message.fields.current_trading_state.get().value()), ' ', false);
        values[entry + ".payload.stocktradingactionmessage.reason"] = canonical::text(std::string(message.fields.reason.get().value()), ' ', false);
    }

    void on_message(const protocol::stock_directory_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.trackingnumber"] = canonical::number(message.header.tracking_number.get().value());
        values[entry + ".messageheader.timestamp"] = canonical::number(message.header.timestamp.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.stockdirectorymessage";
        values[entry + ".payload.stockdirectorymessage.stock"] = canonical::text(std::string(message.fields.stock.get().value()), ' ', false);
        values[entry + ".payload.stockdirectorymessage.marketcategory"] = canonical::text(canonical::character(message.fields.market_category.get().value()), ' ', false);
        values[entry + ".payload.stockdirectorymessage.financialstatusindicator"] = canonical::text(canonical::character(message.fields.financial_status_indicator.get().value()), ' ', false);
        values[entry + ".payload.stockdirectorymessage.roundlotsize"] = canonical::number(message.fields.round_lot_size.get().value());
        values[entry + ".payload.stockdirectorymessage.roundlotsonly"] = canonical::text(canonical::character(message.fields.round_lots_only.get().value()), ' ', false);
        values[entry + ".payload.stockdirectorymessage.issueclassification"] = canonical::text(canonical::character(message.fields.issue_classification.get().value()), ' ', false);
        values[entry + ".payload.stockdirectorymessage.issuesubtype"] = canonical::text(std::string(message.fields.issue_sub_type.get().value()), ' ', false);
        values[entry + ".payload.stockdirectorymessage.authenticity"] = canonical::text(canonical::character(message.fields.authenticity.get().value()), ' ', false);
        values[entry + ".payload.stockdirectorymessage.shortsalethresholdindicator"] = canonical::text(canonical::character(message.fields.short_sale_threshold_indicator.get().value()), ' ', false);
        values[entry + ".payload.stockdirectorymessage.ipoflag"] = canonical::text(canonical::character(message.fields.ipo_flag.get().value()), ' ', false);
        values[entry + ".payload.stockdirectorymessage.luldreferencepricetier"] = canonical::text(canonical::character(message.fields.luld_reference_price_tier.get().value()), ' ', false);
        values[entry + ".payload.stockdirectorymessage.etpflag"] = canonical::text(canonical::character(message.fields.etp_flag.get().value()), ' ', false);
        values[entry + ".payload.stockdirectorymessage.etpleveragefactor"] = canonical::number(message.fields.etp_leverage_factor.get().value());
        values[entry + ".payload.stockdirectorymessage.inverseindicator"] = canonical::text(canonical::character(message.fields.inverse_indicator.get().value()), ' ', false);
        values[entry + ".payload.stockdirectorymessage.bloombergid"] = canonical::text(std::string(message.fields.bloomberg_id.get().value()), ' ', false);
    }

    void on_message(const protocol::reg_sho_short_sale_price_test_restricted_indicator_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.trackingnumber"] = canonical::number(message.header.tracking_number.get().value());
        values[entry + ".messageheader.timestamp"] = canonical::number(message.header.timestamp.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.regshoshortsalepricetestrestrictedindicatormessage";
        values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.issuesymbol"] = canonical::text(std::string(message.fields.issue_symbol.get().value()), ' ', false);
        values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.regshoaction"] = canonical::text(canonical::character(message.fields.reg_sho_action.get().value()), ' ', false);
    }

    void on_message(const protocol::adjusted_closing_price_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.trackingnumber"] = canonical::number(message.header.tracking_number.get().value());
        values[entry + ".messageheader.timestamp"] = canonical::number(message.header.timestamp.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.adjustedclosingpricemessage";
        values[entry + ".payload.adjustedclosingpricemessage.issuesymbol"] = canonical::text(std::string(message.fields.issue_symbol.get().value()), ' ', false);
        values[entry + ".payload.adjustedclosingpricemessage.securityclass"] = canonical::text(canonical::character(message.fields.security_class.get().value()), ' ', false);
        values[entry + ".payload.adjustedclosingpricemessage.adjustedclosingprice"] = canonical::scaled(message.fields.adjusted_closing_price.get().value(), -4);
    }

    void on_message(const protocol::long_form_adjusted_closing_price_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.trackingnumber"] = canonical::number(message.header.tracking_number.get().value());
        values[entry + ".messageheader.timestamp"] = canonical::number(message.header.timestamp.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.longformadjustedclosingpricemessage";
        values[entry + ".payload.longformadjustedclosingpricemessage.issuesymbol"] = canonical::text(std::string(message.fields.issue_symbol.get().value()), ' ', false);
        values[entry + ".payload.longformadjustedclosingpricemessage.securityclass"] = canonical::text(canonical::character(message.fields.security_class.get().value()), ' ', false);
        values[entry + ".payload.longformadjustedclosingpricemessage.adjustedclosingpricelong"] = canonical::scaled(message.fields.adjusted_closing_price_long.get().value(), -4);
    }

    void on_message(const protocol::end_of_day_trade_summary_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.trackingnumber"] = canonical::number(message.header.tracking_number.get().value());
        values[entry + ".messageheader.timestamp"] = canonical::number(message.header.timestamp.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.endofdaytradesummarymessage";
        values[entry + ".payload.endofdaytradesummarymessage.issuesymbol"] = canonical::text(std::string(message.fields.issue_symbol.get().value()), ' ', false);
        values[entry + ".payload.endofdaytradesummarymessage.marketcategory"] = canonical::text(canonical::character(message.fields.market_category.get().value()), ' ', false);
        values[entry + ".payload.endofdaytradesummarymessage.consolidatedhighprice"] = canonical::scaled(message.fields.consolidated_high_price.get().value(), -4);
        values[entry + ".payload.endofdaytradesummarymessage.consolidatedlowprice"] = canonical::scaled(message.fields.consolidated_low_price.get().value(), -4);
        values[entry + ".payload.endofdaytradesummarymessage.consolidatedclosingprice"] = canonical::scaled(message.fields.consolidated_closing_price.get().value(), -4);
        values[entry + ".payload.endofdaytradesummarymessage.consolidatedvolume"] = canonical::number(message.fields.consolidated_volume.get().value());
        values[entry + ".payload.endofdaytradesummarymessage.consolidatedopenprice"] = canonical::scaled(message.fields.consolidated_open_price.get().value(), -4);
    }

    void on_message(const protocol::long_form_end_of_day_trade_summary_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.trackingnumber"] = canonical::number(message.header.tracking_number.get().value());
        values[entry + ".messageheader.timestamp"] = canonical::number(message.header.timestamp.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.longformendofdaytradesummarymessage";
        values[entry + ".payload.longformendofdaytradesummarymessage.issuesymbol"] = canonical::text(std::string(message.fields.issue_symbol.get().value()), ' ', false);
        values[entry + ".payload.longformendofdaytradesummarymessage.marketcategory"] = canonical::text(canonical::character(message.fields.market_category.get().value()), ' ', false);
        values[entry + ".payload.longformendofdaytradesummarymessage.consolidatedhighpricelong"] = canonical::scaled(message.fields.consolidated_high_price_long.get().value(), -4);
        values[entry + ".payload.longformendofdaytradesummarymessage.consolidatedlowpricelong"] = canonical::scaled(message.fields.consolidated_low_price_long.get().value(), -4);
        values[entry + ".payload.longformendofdaytradesummarymessage.consolidatedclosingpricelong"] = canonical::scaled(message.fields.consolidated_closing_price_long.get().value(), -4);
        values[entry + ".payload.longformendofdaytradesummarymessage.consolidatedvolume"] = canonical::number(message.fields.consolidated_volume.get().value());
        values[entry + ".payload.longformendofdaytradesummarymessage.consolidatedopenpricelong"] = canonical::scaled(message.fields.consolidated_open_price_long.get().value(), -4);
    }

    void on_message(const protocol::next_shares_end_of_day_trade_summary_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.trackingnumber"] = canonical::number(message.header.tracking_number.get().value());
        values[entry + ".messageheader.timestamp"] = canonical::number(message.header.timestamp.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.nextsharesendofdaytradesummarymessage";
        values[entry + ".payload.nextsharesendofdaytradesummarymessage.issuesymbol"] = canonical::text(std::string(message.fields.issue_symbol.get().value()), ' ', false);
        values[entry + ".payload.nextsharesendofdaytradesummarymessage.marketcategory"] = canonical::text(canonical::character(message.fields.market_category.get().value()), ' ', false);
        values[entry + ".payload.nextsharesendofdaytradesummarymessage.consolidatedhighprice"] = canonical::scaled(message.fields.consolidated_high_price.get().value(), -4);
        values[entry + ".payload.nextsharesendofdaytradesummarymessage.navoffsetamounthigh"] = canonical::scaled(message.fields.nav_offset_amount_high.get().value(), -4);
        values[entry + ".payload.nextsharesendofdaytradesummarymessage.consolidatedlowprice"] = canonical::scaled(message.fields.consolidated_low_price.get().value(), -4);
        values[entry + ".payload.nextsharesendofdaytradesummarymessage.navoffsetamountlow"] = canonical::scaled(message.fields.nav_offset_amount_low.get().value(), -4);
        values[entry + ".payload.nextsharesendofdaytradesummarymessage.consolidatedclosingprice"] = canonical::scaled(message.fields.consolidated_closing_price.get().value(), -4);
        values[entry + ".payload.nextsharesendofdaytradesummarymessage.navoffsetamountclosing"] = canonical::scaled(message.fields.nav_offset_amount_closing.get().value(), -4);
        values[entry + ".payload.nextsharesendofdaytradesummarymessage.consolidatedvolume"] = canonical::number(message.fields.consolidated_volume.get().value());
        values[entry + ".payload.nextsharesendofdaytradesummarymessage.consolidatedopenprice"] = canonical::scaled(message.fields.consolidated_open_price.get().value(), -4);
        values[entry + ".payload.nextsharesendofdaytradesummarymessage.navoffsetamountopen"] = canonical::scaled(message.fields.nav_offset_amount_open.get().value(), -4);
    }

    void on_message(const protocol::ipo_information_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.trackingnumber"] = canonical::number(message.header.tracking_number.get().value());
        values[entry + ".messageheader.timestamp"] = canonical::number(message.header.timestamp.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.ipoinformationmessage";
        values[entry + ".payload.ipoinformationmessage.issuesymbol"] = canonical::text(std::string(message.fields.issue_symbol.get().value()), ' ', false);
        values[entry + ".payload.ipoinformationmessage.securityclass"] = canonical::text(canonical::character(message.fields.security_class.get().value()), ' ', false);
        values[entry + ".payload.ipoinformationmessage.referencefornetchange"] = canonical::text(canonical::character(message.fields.reference_for_net_change.get().value()), ' ', false);
        values[entry + ".payload.ipoinformationmessage.referenceprice"] = canonical::scaled(message.fields.reference_price.get().value(), -4);
    }

    void on_message(const protocol::mwcb_decline_level_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.trackingnumber"] = canonical::number(message.header.tracking_number.get().value());
        values[entry + ".messageheader.timestamp"] = canonical::number(message.header.timestamp.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.mwcbdeclinelevelmessage";
        values[entry + ".payload.mwcbdeclinelevelmessage.level1"] = canonical::scaled(message.fields.level_1.get().value(), -8);
        values[entry + ".payload.mwcbdeclinelevelmessage.level2"] = canonical::scaled(message.fields.level_2.get().value(), -8);
        values[entry + ".payload.mwcbdeclinelevelmessage.level3"] = canonical::scaled(message.fields.level_3.get().value(), -8);
    }

    void on_message(const protocol::mwcb_status_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.trackingnumber"] = canonical::number(message.header.tracking_number.get().value());
        values[entry + ".messageheader.timestamp"] = canonical::number(message.header.timestamp.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.mwcbstatusmessage";
        values[entry + ".payload.mwcbstatusmessage.breachedlevel"] = canonical::text(canonical::character(message.fields.breached_level.get().value()), ' ', false);
    }

    void on_message(const protocol::ipo_quoting_period_update_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.trackingnumber"] = canonical::number(message.header.tracking_number.get().value());
        values[entry + ".messageheader.timestamp"] = canonical::number(message.header.timestamp.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.ipoquotingperiodupdatemessage";
        values[entry + ".payload.ipoquotingperiodupdatemessage.stock"] = canonical::text(std::string(message.fields.stock.get().value()), ' ', false);
        values[entry + ".payload.ipoquotingperiodupdatemessage.ipoquotationreleasetime"] = canonical::number(message.fields.ipo_quotation_release_time.get().value());
        values[entry + ".payload.ipoquotingperiodupdatemessage.ipoquotationreleasequalifier"] = canonical::text(canonical::character(message.fields.ipo_quotation_release_qualifier.get().value()), ' ', false);
        values[entry + ".payload.ipoquotingperiodupdatemessage.ipoprice"] = canonical::scaled(message.fields.ipo_price.get().value(), -4);
    }

    void on_message(const protocol::operational_halt_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.trackingnumber"] = canonical::number(message.header.tracking_number.get().value());
        values[entry + ".messageheader.timestamp"] = canonical::number(message.header.timestamp.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.operationalhaltmessage";
        values[entry + ".payload.operationalhaltmessage.stock"] = canonical::text(std::string(message.fields.stock.get().value()), ' ', false);
        values[entry + ".payload.operationalhaltmessage.marketcode"] = canonical::text(canonical::character(message.fields.market_code.get().value()), ' ', false);
        values[entry + ".payload.operationalhaltmessage.operationalhaltaction"] = canonical::text(canonical::character(message.fields.operational_halt_action.get().value()), ' ', false);
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
    std::printf("== Nasdaq.NsmEquities.NlsPlus.Itch.v3.0 (advanced values)\n");
    int failures = 0;
    failures += check("LongFormTradeReportMessage", "Nasdaq/NsmEquities.NlsPlus.Itch.v3.0/LongFormTradeReportMessage.pcap", "nasdaq/nsmequities/nlsplus/itch/v3.0/LongFormTradeReportMessage.values");
    failures += check("RegShoShortSalePriceTestRestrictedIndicatorMessage", "Nasdaq/NsmEquities.NlsPlus.Itch.v3.0/RegShoShortSalePriceTestRestrictedIndicatorMessage.pcap", "nasdaq/nsmequities/nlsplus/itch/v3.0/RegShoShortSalePriceTestRestrictedIndicatorMessage.values");
    failures += check("StockTradingActionMessage", "Nasdaq/NsmEquities.NlsPlus.Itch.v3.0/StockTradingActionMessage.pcap", "nasdaq/nsmequities/nlsplus/itch/v3.0/StockTradingActionMessage.values");
    failures += check("SystemEventMessage", "Nasdaq/NsmEquities.NlsPlus.Itch.v3.0/SystemEventMessage.pcap", "nasdaq/nsmequities/nlsplus/itch/v3.0/SystemEventMessage.values");
    failures += check("TradeReportMessage", "Nasdaq/NsmEquities.NlsPlus.Itch.v3.0/TradeReportMessage.pcap", "nasdaq/nsmequities/nlsplus/itch/v3.0/TradeReportMessage.values");
    return failures == 0 ? 0 : 1;
}
