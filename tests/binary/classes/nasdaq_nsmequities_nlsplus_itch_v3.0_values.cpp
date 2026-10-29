// Nasdaq.NsmEquities.NlsPlus.Itch.v3.0 canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/binary/classes/nasdaq/nsmequities/nlsplus/itch/v3.0/definitions.hpp"

namespace protocol = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

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
        values[entry + ".messageheader.trackingnumber"] = canonical::number(each.message_header().tracking_number());
        values[entry + ".messageheader.timestamp"] = canonical::number(each.message_header().timestamp());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(each.message_header().message_type()));

        if (const auto* message = dynamic_cast<const protocol::SystemEventMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.systemeventmessage";
            values[entry + ".payload.systemeventmessage.eventcode"] = canonical::text(canonical::character((*message).event_code()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::TradeReportMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradereportmessage";
            values[entry + ".payload.tradereportmessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character((*message).originating_market_center_identifier()), ' ', false);
            values[entry + ".payload.tradereportmessage.issuesymbol"] = canonical::text(std::string((*message).issue_symbol()), ' ', false);
            values[entry + ".payload.tradereportmessage.securityclass"] = canonical::text(canonical::character((*message).security_class()), ' ', false);
            values[entry + ".payload.tradereportmessage.tradecontrolnumber"] = canonical::text(std::string((*message).trade_control_number()), ' ', false);
            values[entry + ".payload.tradereportmessage.tradeprice"] = canonical::scaled((*message).trade_price().mantissa(), (*message).trade_price().exponent());
            values[entry + ".payload.tradereportmessage.tradesize"] = canonical::number((*message).trade_size());
            values[entry + ".payload.tradereportmessage.saleconditionmodifier.settlementtype"] = canonical::text(canonical::character((*message).sale_condition_modifier().settlement_type()), ' ', false);
            values[entry + ".payload.tradereportmessage.saleconditionmodifier.tradethroughexemption"] = canonical::text(canonical::character((*message).sale_condition_modifier().trade_through_exemption()), ' ', false);
            values[entry + ".payload.tradereportmessage.saleconditionmodifier.extendedhoursorsoldcode"] = canonical::text(canonical::character((*message).sale_condition_modifier().extended_hours_or_sold_code()), ' ', false);
            values[entry + ".payload.tradereportmessage.saleconditionmodifier.specialsalecondition"] = canonical::text(canonical::character((*message).sale_condition_modifier().special_sale_condition()), ' ', false);
            values[entry + ".payload.tradereportmessage.consolidatedvolume"] = canonical::number((*message).consolidated_volume());
        } else if (const auto* message = dynamic_cast<const protocol::LongFormTradeReportMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.longformtradereportmessage";
            values[entry + ".payload.longformtradereportmessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character((*message).originating_market_center_identifier()), ' ', false);
            values[entry + ".payload.longformtradereportmessage.issuesymbol"] = canonical::text(std::string((*message).issue_symbol()), ' ', false);
            values[entry + ".payload.longformtradereportmessage.securityclass"] = canonical::text(canonical::character((*message).security_class()), ' ', false);
            values[entry + ".payload.longformtradereportmessage.tradecontrolnumber"] = canonical::text(std::string((*message).trade_control_number()), ' ', false);
            values[entry + ".payload.longformtradereportmessage.tradepricelong"] = canonical::scaled((*message).trade_price_long().mantissa(), (*message).trade_price_long().exponent());
            values[entry + ".payload.longformtradereportmessage.tradesize"] = canonical::number((*message).trade_size());
            values[entry + ".payload.longformtradereportmessage.saleconditionmodifier.settlementtype"] = canonical::text(canonical::character((*message).sale_condition_modifier().settlement_type()), ' ', false);
            values[entry + ".payload.longformtradereportmessage.saleconditionmodifier.tradethroughexemption"] = canonical::text(canonical::character((*message).sale_condition_modifier().trade_through_exemption()), ' ', false);
            values[entry + ".payload.longformtradereportmessage.saleconditionmodifier.extendedhoursorsoldcode"] = canonical::text(canonical::character((*message).sale_condition_modifier().extended_hours_or_sold_code()), ' ', false);
            values[entry + ".payload.longformtradereportmessage.saleconditionmodifier.specialsalecondition"] = canonical::text(canonical::character((*message).sale_condition_modifier().special_sale_condition()), ' ', false);
            values[entry + ".payload.longformtradereportmessage.consolidatedvolume"] = canonical::number((*message).consolidated_volume());
        } else if (const auto* message = dynamic_cast<const protocol::NextSharesTradeReportMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.nextsharestradereportmessage";
            values[entry + ".payload.nextsharestradereportmessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character((*message).originating_market_center_identifier()), ' ', false);
            values[entry + ".payload.nextsharestradereportmessage.nextsharessymbol"] = canonical::text(std::string((*message).next_shares_symbol()), ' ', false);
            values[entry + ".payload.nextsharestradereportmessage.securityclass"] = canonical::text(canonical::character((*message).security_class()), ' ', false);
            values[entry + ".payload.nextsharestradereportmessage.tradecontrolnumber"] = canonical::text(std::string((*message).trade_control_number()), ' ', false);
            values[entry + ".payload.nextsharestradereportmessage.proxyprice"] = canonical::scaled((*message).proxy_price().mantissa(), (*message).proxy_price().exponent());
            values[entry + ".payload.nextsharestradereportmessage.tradesize"] = canonical::number((*message).trade_size());
            values[entry + ".payload.nextsharestradereportmessage.navoffsetamount"] = canonical::scaled((*message).nav_offset_amount().mantissa(), (*message).nav_offset_amount().exponent());
            values[entry + ".payload.nextsharestradereportmessage.saleconditionmodifier.settlementtype"] = canonical::text(canonical::character((*message).sale_condition_modifier().settlement_type()), ' ', false);
            values[entry + ".payload.nextsharestradereportmessage.saleconditionmodifier.tradethroughexemption"] = canonical::text(canonical::character((*message).sale_condition_modifier().trade_through_exemption()), ' ', false);
            values[entry + ".payload.nextsharestradereportmessage.saleconditionmodifier.extendedhoursorsoldcode"] = canonical::text(canonical::character((*message).sale_condition_modifier().extended_hours_or_sold_code()), ' ', false);
            values[entry + ".payload.nextsharestradereportmessage.saleconditionmodifier.specialsalecondition"] = canonical::text(canonical::character((*message).sale_condition_modifier().special_sale_condition()), ' ', false);
            values[entry + ".payload.nextsharestradereportmessage.consolidatedvolume"] = canonical::number((*message).consolidated_volume());
        } else if (const auto* message = dynamic_cast<const protocol::TradeCancelErrorMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradecancelerrormessage";
            values[entry + ".payload.tradecancelerrormessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character((*message).originating_market_center_identifier()), ' ', false);
            values[entry + ".payload.tradecancelerrormessage.issuesymbol"] = canonical::text(std::string((*message).issue_symbol()), ' ', false);
            values[entry + ".payload.tradecancelerrormessage.securityclass"] = canonical::text(canonical::character((*message).security_class()), ' ', false);
            values[entry + ".payload.tradecancelerrormessage.originaltradecontrolnumber"] = canonical::text(std::string((*message).original_trade_control_number()), ' ', false);
            values[entry + ".payload.tradecancelerrormessage.originaltradeprice"] = canonical::scaled((*message).original_trade_price().mantissa(), (*message).original_trade_price().exponent());
            values[entry + ".payload.tradecancelerrormessage.originaltradesize"] = canonical::number((*message).original_trade_size());
            values[entry + ".payload.tradecancelerrormessage.originalsaleconditionmodifier.originalsettlementtype"] = canonical::text(canonical::character((*message).original_sale_condition_modifier().original_settlement_type()), ' ', false);
            values[entry + ".payload.tradecancelerrormessage.originalsaleconditionmodifier.originaltradethroughexemption"] = canonical::text(canonical::character((*message).original_sale_condition_modifier().original_trade_through_exemption()), ' ', false);
            values[entry + ".payload.tradecancelerrormessage.originalsaleconditionmodifier.originalextendedhoursorsoldcode"] = canonical::text(canonical::character((*message).original_sale_condition_modifier().original_extended_hours_or_sold_code()), ' ', false);
            values[entry + ".payload.tradecancelerrormessage.originalsaleconditionmodifier.originalspecialsalecondition"] = canonical::text(canonical::character((*message).original_sale_condition_modifier().original_special_sale_condition()), ' ', false);
            values[entry + ".payload.tradecancelerrormessage.consolidatedvolume"] = canonical::number((*message).consolidated_volume());
        } else if (const auto* message = dynamic_cast<const protocol::LongFormTradeCancelErrorMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.longformtradecancelerrormessage";
            values[entry + ".payload.longformtradecancelerrormessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character((*message).originating_market_center_identifier()), ' ', false);
            values[entry + ".payload.longformtradecancelerrormessage.issuesymbol"] = canonical::text(std::string((*message).issue_symbol()), ' ', false);
            values[entry + ".payload.longformtradecancelerrormessage.securityclass"] = canonical::text(canonical::character((*message).security_class()), ' ', false);
            values[entry + ".payload.longformtradecancelerrormessage.originaltradecontrolnumber"] = canonical::text(std::string((*message).original_trade_control_number()), ' ', false);
            values[entry + ".payload.longformtradecancelerrormessage.originaltradepricelong"] = canonical::scaled((*message).original_trade_price_long().mantissa(), (*message).original_trade_price_long().exponent());
            values[entry + ".payload.longformtradecancelerrormessage.originaltradesize"] = canonical::number((*message).original_trade_size());
            values[entry + ".payload.longformtradecancelerrormessage.originalsaleconditionmodifier.originalsettlementtype"] = canonical::text(canonical::character((*message).original_sale_condition_modifier().original_settlement_type()), ' ', false);
            values[entry + ".payload.longformtradecancelerrormessage.originalsaleconditionmodifier.originaltradethroughexemption"] = canonical::text(canonical::character((*message).original_sale_condition_modifier().original_trade_through_exemption()), ' ', false);
            values[entry + ".payload.longformtradecancelerrormessage.originalsaleconditionmodifier.originalextendedhoursorsoldcode"] = canonical::text(canonical::character((*message).original_sale_condition_modifier().original_extended_hours_or_sold_code()), ' ', false);
            values[entry + ".payload.longformtradecancelerrormessage.originalsaleconditionmodifier.originalspecialsalecondition"] = canonical::text(canonical::character((*message).original_sale_condition_modifier().original_special_sale_condition()), ' ', false);
            values[entry + ".payload.longformtradecancelerrormessage.consolidatedvolume"] = canonical::number((*message).consolidated_volume());
        } else if (const auto* message = dynamic_cast<const protocol::NextSharesTradeCancelErrorMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.nextsharestradecancelerrormessage";
            values[entry + ".payload.nextsharestradecancelerrormessage.marketcenter"] = canonical::text(canonical::character((*message).market_center()), ' ', false);
            values[entry + ".payload.nextsharestradecancelerrormessage.issuesymbol"] = canonical::text(std::string((*message).issue_symbol()), ' ', false);
            values[entry + ".payload.nextsharestradecancelerrormessage.securityclass"] = canonical::text(canonical::character((*message).security_class()), ' ', false);
            values[entry + ".payload.nextsharestradecancelerrormessage.originaltradecontrolnumber"] = canonical::text(std::string((*message).original_trade_control_number()), ' ', false);
            values[entry + ".payload.nextsharestradecancelerrormessage.originalproxyprice"] = canonical::scaled((*message).original_proxy_price().mantissa(), (*message).original_proxy_price().exponent());
            values[entry + ".payload.nextsharestradecancelerrormessage.originalnavoffsetamount"] = canonical::scaled((*message).original_nav_offset_amount().mantissa(), (*message).original_nav_offset_amount().exponent());
            values[entry + ".payload.nextsharestradecancelerrormessage.originaltradesize"] = canonical::number((*message).original_trade_size());
            values[entry + ".payload.nextsharestradecancelerrormessage.originalsaleconditionmodifier.originalsettlementtype"] = canonical::text(canonical::character((*message).original_sale_condition_modifier().original_settlement_type()), ' ', false);
            values[entry + ".payload.nextsharestradecancelerrormessage.originalsaleconditionmodifier.originaltradethroughexemption"] = canonical::text(canonical::character((*message).original_sale_condition_modifier().original_trade_through_exemption()), ' ', false);
            values[entry + ".payload.nextsharestradecancelerrormessage.originalsaleconditionmodifier.originalextendedhoursorsoldcode"] = canonical::text(canonical::character((*message).original_sale_condition_modifier().original_extended_hours_or_sold_code()), ' ', false);
            values[entry + ".payload.nextsharestradecancelerrormessage.originalsaleconditionmodifier.originalspecialsalecondition"] = canonical::text(canonical::character((*message).original_sale_condition_modifier().original_special_sale_condition()), ' ', false);
            values[entry + ".payload.nextsharestradecancelerrormessage.consolidatedvolume"] = canonical::number((*message).consolidated_volume());
        } else if (const auto* message = dynamic_cast<const protocol::TradeCorrectionMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradecorrectionmessage";
            values[entry + ".payload.tradecorrectionmessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character((*message).originating_market_center_identifier()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.issuesymbol"] = canonical::text(std::string((*message).issue_symbol()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.securityclass"] = canonical::text(canonical::character((*message).security_class()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.originaltradecontrolnumber"] = canonical::text(std::string((*message).original_trade_control_number()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.originaltradeprice"] = canonical::scaled((*message).original_trade_price().mantissa(), (*message).original_trade_price().exponent());
            values[entry + ".payload.tradecorrectionmessage.originaltradesize"] = canonical::number((*message).original_trade_size());
            values[entry + ".payload.tradecorrectionmessage.originalsaleconditionmodifier.originalsettlementtype"] = canonical::text(canonical::character((*message).original_sale_condition_modifier().original_settlement_type()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.originalsaleconditionmodifier.originaltradethroughexemption"] = canonical::text(canonical::character((*message).original_sale_condition_modifier().original_trade_through_exemption()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.originalsaleconditionmodifier.originalextendedhoursorsoldcode"] = canonical::text(canonical::character((*message).original_sale_condition_modifier().original_extended_hours_or_sold_code()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.originalsaleconditionmodifier.originalspecialsalecondition"] = canonical::text(canonical::character((*message).original_sale_condition_modifier().original_special_sale_condition()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.correctedtradecontrolnumber"] = canonical::text(std::string((*message).corrected_trade_control_number()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.correctedtradeprice"] = canonical::scaled((*message).corrected_trade_price().mantissa(), (*message).corrected_trade_price().exponent());
            values[entry + ".payload.tradecorrectionmessage.correctedtradesize"] = canonical::number((*message).corrected_trade_size());
            values[entry + ".payload.tradecorrectionmessage.correctedsaleconditionmodifier.correctedsettlementtype"] = canonical::text(canonical::character((*message).corrected_sale_condition_modifier().corrected_settlement_type()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.correctedsaleconditionmodifier.correctedtradethroughexemption"] = canonical::text(canonical::character((*message).corrected_sale_condition_modifier().corrected_trade_through_exemption()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.correctedsaleconditionmodifier.correctedextendedhoursorsoldcode"] = canonical::text(canonical::character((*message).corrected_sale_condition_modifier().corrected_extended_hours_or_sold_code()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.correctedsaleconditionmodifier.correctedspecialsalecondition"] = canonical::text(canonical::character((*message).corrected_sale_condition_modifier().corrected_special_sale_condition()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.consolidatedvolume"] = canonical::number((*message).consolidated_volume());
        } else if (const auto* message = dynamic_cast<const protocol::LongFormTradeCorrectionMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.longformtradecorrectionmessage";
            values[entry + ".payload.longformtradecorrectionmessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character((*message).originating_market_center_identifier()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.issuesymbol"] = canonical::text(std::string((*message).issue_symbol()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.securityclass"] = canonical::text(canonical::character((*message).security_class()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.originaltradecontrolnumber"] = canonical::text(std::string((*message).original_trade_control_number()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.originaltradepricelong"] = canonical::scaled((*message).original_trade_price_long().mantissa(), (*message).original_trade_price_long().exponent());
            values[entry + ".payload.longformtradecorrectionmessage.originaltradesize"] = canonical::number((*message).original_trade_size());
            values[entry + ".payload.longformtradecorrectionmessage.originalsaleconditionmodifier.originalsettlementtype"] = canonical::text(canonical::character((*message).original_sale_condition_modifier().original_settlement_type()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.originalsaleconditionmodifier.originaltradethroughexemption"] = canonical::text(canonical::character((*message).original_sale_condition_modifier().original_trade_through_exemption()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.originalsaleconditionmodifier.originalextendedhoursorsoldcode"] = canonical::text(canonical::character((*message).original_sale_condition_modifier().original_extended_hours_or_sold_code()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.originalsaleconditionmodifier.originalspecialsalecondition"] = canonical::text(canonical::character((*message).original_sale_condition_modifier().original_special_sale_condition()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.correctedtradecontrolnumber"] = canonical::text(std::string((*message).corrected_trade_control_number()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.correctedtradepricelong"] = canonical::scaled((*message).corrected_trade_price_long().mantissa(), (*message).corrected_trade_price_long().exponent());
            values[entry + ".payload.longformtradecorrectionmessage.correctedtradesize"] = canonical::number((*message).corrected_trade_size());
            values[entry + ".payload.longformtradecorrectionmessage.correctedsaleconditionmodifier.correctedsettlementtype"] = canonical::text(canonical::character((*message).corrected_sale_condition_modifier().corrected_settlement_type()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.correctedsaleconditionmodifier.correctedtradethroughexemption"] = canonical::text(canonical::character((*message).corrected_sale_condition_modifier().corrected_trade_through_exemption()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.correctedsaleconditionmodifier.correctedextendedhoursorsoldcode"] = canonical::text(canonical::character((*message).corrected_sale_condition_modifier().corrected_extended_hours_or_sold_code()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.correctedsaleconditionmodifier.correctedspecialsalecondition"] = canonical::text(canonical::character((*message).corrected_sale_condition_modifier().corrected_special_sale_condition()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.consolidatedvolume"] = canonical::number((*message).consolidated_volume());
        } else if (const auto* message = dynamic_cast<const protocol::NextSharesTradeCorrectionMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.nextsharestradecorrectionmessage";
            values[entry + ".payload.nextsharestradecorrectionmessage.marketcenter"] = canonical::text(canonical::character((*message).market_center()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.issuesymbol"] = canonical::text(std::string((*message).issue_symbol()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.securityclass"] = canonical::text(canonical::character((*message).security_class()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.originaltradecontrolnumber"] = canonical::text(std::string((*message).original_trade_control_number()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.originalproxyprice"] = canonical::scaled((*message).original_proxy_price().mantissa(), (*message).original_proxy_price().exponent());
            values[entry + ".payload.nextsharestradecorrectionmessage.originalnavoffsetamount"] = canonical::scaled((*message).original_nav_offset_amount().mantissa(), (*message).original_nav_offset_amount().exponent());
            values[entry + ".payload.nextsharestradecorrectionmessage.originaltradesize"] = canonical::number((*message).original_trade_size());
            values[entry + ".payload.nextsharestradecorrectionmessage.originalsaleconditionmodifier.originalsettlementtype"] = canonical::text(canonical::character((*message).original_sale_condition_modifier().original_settlement_type()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.originalsaleconditionmodifier.originaltradethroughexemption"] = canonical::text(canonical::character((*message).original_sale_condition_modifier().original_trade_through_exemption()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.originalsaleconditionmodifier.originalextendedhoursorsoldcode"] = canonical::text(canonical::character((*message).original_sale_condition_modifier().original_extended_hours_or_sold_code()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.originalsaleconditionmodifier.originalspecialsalecondition"] = canonical::text(canonical::character((*message).original_sale_condition_modifier().original_special_sale_condition()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.correctedtradecontrolnumber"] = canonical::text(std::string((*message).corrected_trade_control_number()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.correctedproxyprice"] = canonical::scaled((*message).corrected_proxy_price().mantissa(), (*message).corrected_proxy_price().exponent());
            values[entry + ".payload.nextsharestradecorrectionmessage.correctednavoffsetamount"] = canonical::scaled((*message).corrected_nav_offset_amount().mantissa(), (*message).corrected_nav_offset_amount().exponent());
            values[entry + ".payload.nextsharestradecorrectionmessage.correctedtradesize"] = canonical::number((*message).corrected_trade_size());
            values[entry + ".payload.nextsharestradecorrectionmessage.correctedsaleconditionmodifier.correctedsettlementtype"] = canonical::text(canonical::character((*message).corrected_sale_condition_modifier().corrected_settlement_type()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.correctedsaleconditionmodifier.correctedtradethroughexemption"] = canonical::text(canonical::character((*message).corrected_sale_condition_modifier().corrected_trade_through_exemption()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.correctedsaleconditionmodifier.correctedextendedhoursorsoldcode"] = canonical::text(canonical::character((*message).corrected_sale_condition_modifier().corrected_extended_hours_or_sold_code()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.correctedsaleconditionmodifier.correctedspecialsalecondition"] = canonical::text(canonical::character((*message).corrected_sale_condition_modifier().corrected_special_sale_condition()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.consolidatedvolume"] = canonical::number((*message).consolidated_volume());
        } else if (const auto* message = dynamic_cast<const protocol::StockTradingActionMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.stocktradingactionmessage";
            values[entry + ".payload.stocktradingactionmessage.reserved"] = canonical::text(canonical::character((*message).reserved()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.issuesymbol"] = canonical::text(std::string((*message).issue_symbol()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.securityclass"] = canonical::text(canonical::character((*message).security_class()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.currenttradingstate"] = canonical::text(canonical::character((*message).current_trading_state()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.reason"] = canonical::text(std::string((*message).reason()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::StockDirectoryMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.stockdirectorymessage";
            values[entry + ".payload.stockdirectorymessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.marketcategory"] = canonical::text(canonical::character((*message).market_category()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.financialstatusindicator"] = canonical::text(canonical::character((*message).financial_status_indicator()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.roundlotsize"] = canonical::number((*message).round_lot_size());
            values[entry + ".payload.stockdirectorymessage.roundlotsonly"] = canonical::text(canonical::character((*message).round_lots_only()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.issueclassification"] = canonical::text(canonical::character((*message).issue_classification()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.issuesubtype"] = canonical::text(std::string((*message).issue_sub_type()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.authenticity"] = canonical::text(canonical::character((*message).authenticity()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.shortsalethresholdindicator"] = canonical::text(canonical::character((*message).short_sale_threshold_indicator()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.ipoflag"] = canonical::text(canonical::character((*message).ipo_flag()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.luldreferencepricetier"] = canonical::text(canonical::character((*message).luld_reference_price_tier()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.etpflag"] = canonical::text(canonical::character((*message).etp_flag()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.etpleveragefactor"] = canonical::number((*message).etp_leverage_factor());
            values[entry + ".payload.stockdirectorymessage.inverseindicator"] = canonical::text(canonical::character((*message).inverse_indicator()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.bloombergid"] = canonical::text(std::string((*message).bloomberg_id()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::RegShoShortSalePriceTestRestrictedIndicatorMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.regshoshortsalepricetestrestrictedindicatormessage";
            values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.issuesymbol"] = canonical::text(std::string((*message).issue_symbol()), ' ', false);
            values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.regshoaction"] = canonical::text(canonical::character((*message).reg_sho_action()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::AdjustedClosingPriceMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.adjustedclosingpricemessage";
            values[entry + ".payload.adjustedclosingpricemessage.issuesymbol"] = canonical::text(std::string((*message).issue_symbol()), ' ', false);
            values[entry + ".payload.adjustedclosingpricemessage.securityclass"] = canonical::text(canonical::character((*message).security_class()), ' ', false);
            values[entry + ".payload.adjustedclosingpricemessage.adjustedclosingprice"] = canonical::scaled((*message).adjusted_closing_price().mantissa(), (*message).adjusted_closing_price().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::LongFormAdjustedClosingPriceMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.longformadjustedclosingpricemessage";
            values[entry + ".payload.longformadjustedclosingpricemessage.issuesymbol"] = canonical::text(std::string((*message).issue_symbol()), ' ', false);
            values[entry + ".payload.longformadjustedclosingpricemessage.securityclass"] = canonical::text(canonical::character((*message).security_class()), ' ', false);
            values[entry + ".payload.longformadjustedclosingpricemessage.adjustedclosingpricelong"] = canonical::scaled((*message).adjusted_closing_price_long().mantissa(), (*message).adjusted_closing_price_long().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::EndOfDayTradeSummaryMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.endofdaytradesummarymessage";
            values[entry + ".payload.endofdaytradesummarymessage.issuesymbol"] = canonical::text(std::string((*message).issue_symbol()), ' ', false);
            values[entry + ".payload.endofdaytradesummarymessage.marketcategory"] = canonical::text(canonical::character((*message).market_category()), ' ', false);
            values[entry + ".payload.endofdaytradesummarymessage.consolidatedhighprice"] = canonical::scaled((*message).consolidated_high_price().mantissa(), (*message).consolidated_high_price().exponent());
            values[entry + ".payload.endofdaytradesummarymessage.consolidatedlowprice"] = canonical::scaled((*message).consolidated_low_price().mantissa(), (*message).consolidated_low_price().exponent());
            values[entry + ".payload.endofdaytradesummarymessage.consolidatedclosingprice"] = canonical::scaled((*message).consolidated_closing_price().mantissa(), (*message).consolidated_closing_price().exponent());
            values[entry + ".payload.endofdaytradesummarymessage.consolidatedvolume"] = canonical::number((*message).consolidated_volume());
            values[entry + ".payload.endofdaytradesummarymessage.consolidatedopenprice"] = canonical::scaled((*message).consolidated_open_price().mantissa(), (*message).consolidated_open_price().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::LongFormEndOfDayTradeSummaryMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.longformendofdaytradesummarymessage";
            values[entry + ".payload.longformendofdaytradesummarymessage.issuesymbol"] = canonical::text(std::string((*message).issue_symbol()), ' ', false);
            values[entry + ".payload.longformendofdaytradesummarymessage.marketcategory"] = canonical::text(canonical::character((*message).market_category()), ' ', false);
            values[entry + ".payload.longformendofdaytradesummarymessage.consolidatedhighpricelong"] = canonical::scaled((*message).consolidated_high_price_long().mantissa(), (*message).consolidated_high_price_long().exponent());
            values[entry + ".payload.longformendofdaytradesummarymessage.consolidatedlowpricelong"] = canonical::scaled((*message).consolidated_low_price_long().mantissa(), (*message).consolidated_low_price_long().exponent());
            values[entry + ".payload.longformendofdaytradesummarymessage.consolidatedclosingpricelong"] = canonical::scaled((*message).consolidated_closing_price_long().mantissa(), (*message).consolidated_closing_price_long().exponent());
            values[entry + ".payload.longformendofdaytradesummarymessage.consolidatedvolume"] = canonical::number((*message).consolidated_volume());
            values[entry + ".payload.longformendofdaytradesummarymessage.consolidatedopenpricelong"] = canonical::scaled((*message).consolidated_open_price_long().mantissa(), (*message).consolidated_open_price_long().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::NextSharesEndOfDayTradeSummaryMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.nextsharesendofdaytradesummarymessage";
            values[entry + ".payload.nextsharesendofdaytradesummarymessage.issuesymbol"] = canonical::text(std::string((*message).issue_symbol()), ' ', false);
            values[entry + ".payload.nextsharesendofdaytradesummarymessage.marketcategory"] = canonical::text(canonical::character((*message).market_category()), ' ', false);
            values[entry + ".payload.nextsharesendofdaytradesummarymessage.consolidatedhighprice"] = canonical::scaled((*message).consolidated_high_price().mantissa(), (*message).consolidated_high_price().exponent());
            values[entry + ".payload.nextsharesendofdaytradesummarymessage.navoffsetamounthigh"] = canonical::scaled((*message).nav_offset_amount_high().mantissa(), (*message).nav_offset_amount_high().exponent());
            values[entry + ".payload.nextsharesendofdaytradesummarymessage.consolidatedlowprice"] = canonical::scaled((*message).consolidated_low_price().mantissa(), (*message).consolidated_low_price().exponent());
            values[entry + ".payload.nextsharesendofdaytradesummarymessage.navoffsetamountlow"] = canonical::scaled((*message).nav_offset_amount_low().mantissa(), (*message).nav_offset_amount_low().exponent());
            values[entry + ".payload.nextsharesendofdaytradesummarymessage.consolidatedclosingprice"] = canonical::scaled((*message).consolidated_closing_price().mantissa(), (*message).consolidated_closing_price().exponent());
            values[entry + ".payload.nextsharesendofdaytradesummarymessage.navoffsetamountclosing"] = canonical::scaled((*message).nav_offset_amount_closing().mantissa(), (*message).nav_offset_amount_closing().exponent());
            values[entry + ".payload.nextsharesendofdaytradesummarymessage.consolidatedvolume"] = canonical::number((*message).consolidated_volume());
            values[entry + ".payload.nextsharesendofdaytradesummarymessage.consolidatedopenprice"] = canonical::scaled((*message).consolidated_open_price().mantissa(), (*message).consolidated_open_price().exponent());
            values[entry + ".payload.nextsharesendofdaytradesummarymessage.navoffsetamountopen"] = canonical::scaled((*message).nav_offset_amount_open().mantissa(), (*message).nav_offset_amount_open().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::IpoInformationMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.ipoinformationmessage";
            values[entry + ".payload.ipoinformationmessage.issuesymbol"] = canonical::text(std::string((*message).issue_symbol()), ' ', false);
            values[entry + ".payload.ipoinformationmessage.securityclass"] = canonical::text(canonical::character((*message).security_class()), ' ', false);
            values[entry + ".payload.ipoinformationmessage.referencefornetchange"] = canonical::text(canonical::character((*message).reference_for_net_change()), ' ', false);
            values[entry + ".payload.ipoinformationmessage.referenceprice"] = canonical::scaled((*message).reference_price().mantissa(), (*message).reference_price().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::MwcbDeclineLevelMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.mwcbdeclinelevelmessage";
            values[entry + ".payload.mwcbdeclinelevelmessage.level1"] = canonical::scaled((*message).level_1().mantissa(), (*message).level_1().exponent());
            values[entry + ".payload.mwcbdeclinelevelmessage.level2"] = canonical::scaled((*message).level_2().mantissa(), (*message).level_2().exponent());
            values[entry + ".payload.mwcbdeclinelevelmessage.level3"] = canonical::scaled((*message).level_3().mantissa(), (*message).level_3().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::MwcbStatusMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.mwcbstatusmessage";
            values[entry + ".payload.mwcbstatusmessage.breachedlevel"] = canonical::text(canonical::character((*message).breached_level()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::IpoQuotingPeriodUpdateMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.ipoquotingperiodupdatemessage";
            values[entry + ".payload.ipoquotingperiodupdatemessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.ipoquotingperiodupdatemessage.ipoquotationreleasetime"] = canonical::number((*message).ipo_quotation_release_time());
            values[entry + ".payload.ipoquotingperiodupdatemessage.ipoquotationreleasequalifier"] = canonical::text(canonical::character((*message).ipo_quotation_release_qualifier()), ' ', false);
            values[entry + ".payload.ipoquotingperiodupdatemessage.ipoprice"] = canonical::scaled((*message).ipo_price().mantissa(), (*message).ipo_price().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::OperationalHaltMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.operationalhaltmessage";
            values[entry + ".payload.operationalhaltmessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.operationalhaltmessage.marketcode"] = canonical::text(canonical::character((*message).market_code()), ' ', false);
            values[entry + ".payload.operationalhaltmessage.operationalhaltaction"] = canonical::text(canonical::character((*message).operational_halt_action()), ' ', false);
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
    std::printf("== Nasdaq.NsmEquities.NlsPlus.Itch.v3.0 (classes values)\n");
    int failures = 0;
    failures += check("LongFormTradeReportMessage", "Nasdaq/NsmEquities.NlsPlus.Itch.v3.0/LongFormTradeReportMessage.pcap", "nasdaq/nsmequities/nlsplus/itch/v3.0/LongFormTradeReportMessage.values");
    failures += check("RegShoShortSalePriceTestRestrictedIndicatorMessage", "Nasdaq/NsmEquities.NlsPlus.Itch.v3.0/RegShoShortSalePriceTestRestrictedIndicatorMessage.pcap", "nasdaq/nsmequities/nlsplus/itch/v3.0/RegShoShortSalePriceTestRestrictedIndicatorMessage.values");
    failures += check("StockTradingActionMessage", "Nasdaq/NsmEquities.NlsPlus.Itch.v3.0/StockTradingActionMessage.pcap", "nasdaq/nsmequities/nlsplus/itch/v3.0/StockTradingActionMessage.values");
    failures += check("SystemEventMessage", "Nasdaq/NsmEquities.NlsPlus.Itch.v3.0/SystemEventMessage.pcap", "nasdaq/nsmequities/nlsplus/itch/v3.0/SystemEventMessage.values");
    failures += check("TradeReportMessage", "Nasdaq/NsmEquities.NlsPlus.Itch.v3.0/TradeReportMessage.pcap", "nasdaq/nsmequities/nlsplus/itch/v3.0/TradeReportMessage.values");
    return failures == 0 ? 0 : 1;
}
