// Nasdaq.NsmEquities.NlsPlus.Itch.v3.0 canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/nasdaq/nsmequities/nlsplus/itch/v3.0/definitions.hpp"

namespace protocol = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

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
        values[entry + ".messageheader.trackingnumber"] = canonical::number(iterator.message_header->tracking_number.get());
        values[entry + ".messageheader.timestamp"] = canonical::number(iterator.message_header->timestamp.get());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(iterator.message_header->message_type.get()));

        if (iterator.message_type == protocol::SystemEventMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.systemeventmessage";
            [[maybe_unused]] const auto* message = protocol::SystemEventMessage::parse(iterator.message);
            values[entry + ".payload.systemeventmessage.eventcode"] = canonical::text(canonical::character(message->event_code.get()), ' ', false);
        } else if (iterator.message_type == protocol::TradeReportMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradereportmessage";
            [[maybe_unused]] const auto* message = protocol::TradeReportMessage::parse(iterator.message);
            values[entry + ".payload.tradereportmessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character(message->originating_market_center_identifier.get()), ' ', false);
            values[entry + ".payload.tradereportmessage.issuesymbol"] = canonical::text(std::string(message->issue_symbol.get()), ' ', false);
            values[entry + ".payload.tradereportmessage.securityclass"] = canonical::text(canonical::character(message->security_class.get()), ' ', false);
            values[entry + ".payload.tradereportmessage.tradecontrolnumber"] = canonical::text(std::string(message->trade_control_number.get()), ' ', false);
            values[entry + ".payload.tradereportmessage.tradeprice"] = canonical::scaled(message->trade_price.integer(), -4);
            values[entry + ".payload.tradereportmessage.tradesize"] = canonical::number(message->trade_size.get());
            values[entry + ".payload.tradereportmessage.saleconditionmodifier.settlementtype"] = canonical::text(canonical::character(message->sale_condition_modifier.settlement_type.get()), ' ', false);
            values[entry + ".payload.tradereportmessage.saleconditionmodifier.tradethroughexemption"] = canonical::text(canonical::character(message->sale_condition_modifier.trade_through_exemption.get()), ' ', false);
            values[entry + ".payload.tradereportmessage.saleconditionmodifier.extendedhoursorsoldcode"] = canonical::text(canonical::character(message->sale_condition_modifier.extended_hours_or_sold_code.get()), ' ', false);
            values[entry + ".payload.tradereportmessage.saleconditionmodifier.specialsalecondition"] = canonical::text(canonical::character(message->sale_condition_modifier.special_sale_condition.get()), ' ', false);
            values[entry + ".payload.tradereportmessage.consolidatedvolume"] = canonical::number(message->consolidated_volume.get());
        } else if (iterator.message_type == protocol::LongFormTradeReportMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.longformtradereportmessage";
            [[maybe_unused]] const auto* message = protocol::LongFormTradeReportMessage::parse(iterator.message);
            values[entry + ".payload.longformtradereportmessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character(message->originating_market_center_identifier.get()), ' ', false);
            values[entry + ".payload.longformtradereportmessage.issuesymbol"] = canonical::text(std::string(message->issue_symbol.get()), ' ', false);
            values[entry + ".payload.longformtradereportmessage.securityclass"] = canonical::text(canonical::character(message->security_class.get()), ' ', false);
            values[entry + ".payload.longformtradereportmessage.tradecontrolnumber"] = canonical::text(std::string(message->trade_control_number.get()), ' ', false);
            values[entry + ".payload.longformtradereportmessage.tradepricelong"] = canonical::scaled(message->trade_price_long.integer(), -4);
            values[entry + ".payload.longformtradereportmessage.tradesize"] = canonical::number(message->trade_size.get());
            values[entry + ".payload.longformtradereportmessage.saleconditionmodifier.settlementtype"] = canonical::text(canonical::character(message->sale_condition_modifier.settlement_type.get()), ' ', false);
            values[entry + ".payload.longformtradereportmessage.saleconditionmodifier.tradethroughexemption"] = canonical::text(canonical::character(message->sale_condition_modifier.trade_through_exemption.get()), ' ', false);
            values[entry + ".payload.longformtradereportmessage.saleconditionmodifier.extendedhoursorsoldcode"] = canonical::text(canonical::character(message->sale_condition_modifier.extended_hours_or_sold_code.get()), ' ', false);
            values[entry + ".payload.longformtradereportmessage.saleconditionmodifier.specialsalecondition"] = canonical::text(canonical::character(message->sale_condition_modifier.special_sale_condition.get()), ' ', false);
            values[entry + ".payload.longformtradereportmessage.consolidatedvolume"] = canonical::number(message->consolidated_volume.get());
        } else if (iterator.message_type == protocol::NextSharesTradeReportMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.nextsharestradereportmessage";
            [[maybe_unused]] const auto* message = protocol::NextSharesTradeReportMessage::parse(iterator.message);
            values[entry + ".payload.nextsharestradereportmessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character(message->originating_market_center_identifier.get()), ' ', false);
            values[entry + ".payload.nextsharestradereportmessage.nextsharessymbol"] = canonical::text(std::string(message->next_shares_symbol.get()), ' ', false);
            values[entry + ".payload.nextsharestradereportmessage.securityclass"] = canonical::text(canonical::character(message->security_class.get()), ' ', false);
            values[entry + ".payload.nextsharestradereportmessage.tradecontrolnumber"] = canonical::text(std::string(message->trade_control_number.get()), ' ', false);
            values[entry + ".payload.nextsharestradereportmessage.proxyprice"] = canonical::scaled(message->proxy_price.integer(), -4);
            values[entry + ".payload.nextsharestradereportmessage.tradesize"] = canonical::number(message->trade_size.get());
            values[entry + ".payload.nextsharestradereportmessage.navoffsetamount"] = canonical::scaled(message->nav_offset_amount.integer(), -4);
            values[entry + ".payload.nextsharestradereportmessage.saleconditionmodifier.settlementtype"] = canonical::text(canonical::character(message->sale_condition_modifier.settlement_type.get()), ' ', false);
            values[entry + ".payload.nextsharestradereportmessage.saleconditionmodifier.tradethroughexemption"] = canonical::text(canonical::character(message->sale_condition_modifier.trade_through_exemption.get()), ' ', false);
            values[entry + ".payload.nextsharestradereportmessage.saleconditionmodifier.extendedhoursorsoldcode"] = canonical::text(canonical::character(message->sale_condition_modifier.extended_hours_or_sold_code.get()), ' ', false);
            values[entry + ".payload.nextsharestradereportmessage.saleconditionmodifier.specialsalecondition"] = canonical::text(canonical::character(message->sale_condition_modifier.special_sale_condition.get()), ' ', false);
            values[entry + ".payload.nextsharestradereportmessage.consolidatedvolume"] = canonical::number(message->consolidated_volume.get());
        } else if (iterator.message_type == protocol::TradeCancelErrorMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradecancelerrormessage";
            [[maybe_unused]] const auto* message = protocol::TradeCancelErrorMessage::parse(iterator.message);
            values[entry + ".payload.tradecancelerrormessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character(message->originating_market_center_identifier.get()), ' ', false);
            values[entry + ".payload.tradecancelerrormessage.issuesymbol"] = canonical::text(std::string(message->issue_symbol.get()), ' ', false);
            values[entry + ".payload.tradecancelerrormessage.securityclass"] = canonical::text(canonical::character(message->security_class.get()), ' ', false);
            values[entry + ".payload.tradecancelerrormessage.originaltradecontrolnumber"] = canonical::text(std::string(message->original_trade_control_number.get()), ' ', false);
            values[entry + ".payload.tradecancelerrormessage.originaltradeprice"] = canonical::scaled(message->original_trade_price.integer(), -4);
            values[entry + ".payload.tradecancelerrormessage.originaltradesize"] = canonical::number(message->original_trade_size.get());
            values[entry + ".payload.tradecancelerrormessage.originalsaleconditionmodifier.originalsettlementtype"] = canonical::text(canonical::character(message->original_sale_condition_modifier.original_settlement_type.get()), ' ', false);
            values[entry + ".payload.tradecancelerrormessage.originalsaleconditionmodifier.originaltradethroughexemption"] = canonical::text(canonical::character(message->original_sale_condition_modifier.original_trade_through_exemption.get()), ' ', false);
            values[entry + ".payload.tradecancelerrormessage.originalsaleconditionmodifier.originalextendedhoursorsoldcode"] = canonical::text(canonical::character(message->original_sale_condition_modifier.original_extended_hours_or_sold_code.get()), ' ', false);
            values[entry + ".payload.tradecancelerrormessage.originalsaleconditionmodifier.originalspecialsalecondition"] = canonical::text(canonical::character(message->original_sale_condition_modifier.original_special_sale_condition.get()), ' ', false);
            values[entry + ".payload.tradecancelerrormessage.consolidatedvolume"] = canonical::number(message->consolidated_volume.get());
        } else if (iterator.message_type == protocol::LongFormTradeCancelErrorMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.longformtradecancelerrormessage";
            [[maybe_unused]] const auto* message = protocol::LongFormTradeCancelErrorMessage::parse(iterator.message);
            values[entry + ".payload.longformtradecancelerrormessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character(message->originating_market_center_identifier.get()), ' ', false);
            values[entry + ".payload.longformtradecancelerrormessage.issuesymbol"] = canonical::text(std::string(message->issue_symbol.get()), ' ', false);
            values[entry + ".payload.longformtradecancelerrormessage.securityclass"] = canonical::text(canonical::character(message->security_class.get()), ' ', false);
            values[entry + ".payload.longformtradecancelerrormessage.originaltradecontrolnumber"] = canonical::text(std::string(message->original_trade_control_number.get()), ' ', false);
            values[entry + ".payload.longformtradecancelerrormessage.originaltradepricelong"] = canonical::scaled(message->original_trade_price_long.integer(), -4);
            values[entry + ".payload.longformtradecancelerrormessage.originaltradesize"] = canonical::number(message->original_trade_size.get());
            values[entry + ".payload.longformtradecancelerrormessage.originalsaleconditionmodifier.originalsettlementtype"] = canonical::text(canonical::character(message->original_sale_condition_modifier.original_settlement_type.get()), ' ', false);
            values[entry + ".payload.longformtradecancelerrormessage.originalsaleconditionmodifier.originaltradethroughexemption"] = canonical::text(canonical::character(message->original_sale_condition_modifier.original_trade_through_exemption.get()), ' ', false);
            values[entry + ".payload.longformtradecancelerrormessage.originalsaleconditionmodifier.originalextendedhoursorsoldcode"] = canonical::text(canonical::character(message->original_sale_condition_modifier.original_extended_hours_or_sold_code.get()), ' ', false);
            values[entry + ".payload.longformtradecancelerrormessage.originalsaleconditionmodifier.originalspecialsalecondition"] = canonical::text(canonical::character(message->original_sale_condition_modifier.original_special_sale_condition.get()), ' ', false);
            values[entry + ".payload.longformtradecancelerrormessage.consolidatedvolume"] = canonical::number(message->consolidated_volume.get());
        } else if (iterator.message_type == protocol::NextSharesTradeCancelErrorMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.nextsharestradecancelerrormessage";
            [[maybe_unused]] const auto* message = protocol::NextSharesTradeCancelErrorMessage::parse(iterator.message);
            values[entry + ".payload.nextsharestradecancelerrormessage.marketcenter"] = canonical::text(canonical::character(message->market_center.get()), ' ', false);
            values[entry + ".payload.nextsharestradecancelerrormessage.issuesymbol"] = canonical::text(std::string(message->issue_symbol.get()), ' ', false);
            values[entry + ".payload.nextsharestradecancelerrormessage.securityclass"] = canonical::text(canonical::character(message->security_class.get()), ' ', false);
            values[entry + ".payload.nextsharestradecancelerrormessage.originaltradecontrolnumber"] = canonical::text(std::string(message->original_trade_control_number.get()), ' ', false);
            values[entry + ".payload.nextsharestradecancelerrormessage.originalproxyprice"] = canonical::scaled(message->original_proxy_price.integer(), -4);
            values[entry + ".payload.nextsharestradecancelerrormessage.originalnavoffsetamount"] = canonical::scaled(message->original_nav_offset_amount.integer(), -4);
            values[entry + ".payload.nextsharestradecancelerrormessage.originaltradesize"] = canonical::number(message->original_trade_size.get());
            values[entry + ".payload.nextsharestradecancelerrormessage.originalsaleconditionmodifier.originalsettlementtype"] = canonical::text(canonical::character(message->original_sale_condition_modifier.original_settlement_type.get()), ' ', false);
            values[entry + ".payload.nextsharestradecancelerrormessage.originalsaleconditionmodifier.originaltradethroughexemption"] = canonical::text(canonical::character(message->original_sale_condition_modifier.original_trade_through_exemption.get()), ' ', false);
            values[entry + ".payload.nextsharestradecancelerrormessage.originalsaleconditionmodifier.originalextendedhoursorsoldcode"] = canonical::text(canonical::character(message->original_sale_condition_modifier.original_extended_hours_or_sold_code.get()), ' ', false);
            values[entry + ".payload.nextsharestradecancelerrormessage.originalsaleconditionmodifier.originalspecialsalecondition"] = canonical::text(canonical::character(message->original_sale_condition_modifier.original_special_sale_condition.get()), ' ', false);
            values[entry + ".payload.nextsharestradecancelerrormessage.consolidatedvolume"] = canonical::number(message->consolidated_volume.get());
        } else if (iterator.message_type == protocol::TradeCorrectionMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradecorrectionmessage";
            [[maybe_unused]] const auto* message = protocol::TradeCorrectionMessage::parse(iterator.message);
            values[entry + ".payload.tradecorrectionmessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character(message->originating_market_center_identifier.get()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.issuesymbol"] = canonical::text(std::string(message->issue_symbol.get()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.securityclass"] = canonical::text(canonical::character(message->security_class.get()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.originaltradecontrolnumber"] = canonical::text(std::string(message->original_trade_control_number.get()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.originaltradeprice"] = canonical::scaled(message->original_trade_price.integer(), -4);
            values[entry + ".payload.tradecorrectionmessage.originaltradesize"] = canonical::number(message->original_trade_size.get());
            values[entry + ".payload.tradecorrectionmessage.originalsaleconditionmodifier.originalsettlementtype"] = canonical::text(canonical::character(message->original_sale_condition_modifier.original_settlement_type.get()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.originalsaleconditionmodifier.originaltradethroughexemption"] = canonical::text(canonical::character(message->original_sale_condition_modifier.original_trade_through_exemption.get()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.originalsaleconditionmodifier.originalextendedhoursorsoldcode"] = canonical::text(canonical::character(message->original_sale_condition_modifier.original_extended_hours_or_sold_code.get()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.originalsaleconditionmodifier.originalspecialsalecondition"] = canonical::text(canonical::character(message->original_sale_condition_modifier.original_special_sale_condition.get()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.correctedtradecontrolnumber"] = canonical::text(std::string(message->corrected_trade_control_number.get()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.correctedtradeprice"] = canonical::scaled(message->corrected_trade_price.integer(), -4);
            values[entry + ".payload.tradecorrectionmessage.correctedtradesize"] = canonical::number(message->corrected_trade_size.get());
            values[entry + ".payload.tradecorrectionmessage.correctedsaleconditionmodifier.correctedsettlementtype"] = canonical::text(canonical::character(message->corrected_sale_condition_modifier.corrected_settlement_type.get()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.correctedsaleconditionmodifier.correctedtradethroughexemption"] = canonical::text(canonical::character(message->corrected_sale_condition_modifier.corrected_trade_through_exemption.get()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.correctedsaleconditionmodifier.correctedextendedhoursorsoldcode"] = canonical::text(canonical::character(message->corrected_sale_condition_modifier.corrected_extended_hours_or_sold_code.get()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.correctedsaleconditionmodifier.correctedspecialsalecondition"] = canonical::text(canonical::character(message->corrected_sale_condition_modifier.corrected_special_sale_condition.get()), ' ', false);
            values[entry + ".payload.tradecorrectionmessage.consolidatedvolume"] = canonical::number(message->consolidated_volume.get());
        } else if (iterator.message_type == protocol::LongFormTradeCorrectionMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.longformtradecorrectionmessage";
            [[maybe_unused]] const auto* message = protocol::LongFormTradeCorrectionMessage::parse(iterator.message);
            values[entry + ".payload.longformtradecorrectionmessage.originatingmarketcenteridentifier"] = canonical::text(canonical::character(message->originating_market_center_identifier.get()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.issuesymbol"] = canonical::text(std::string(message->issue_symbol.get()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.securityclass"] = canonical::text(canonical::character(message->security_class.get()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.originaltradecontrolnumber"] = canonical::text(std::string(message->original_trade_control_number.get()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.originaltradepricelong"] = canonical::scaled(message->original_trade_price_long.integer(), -4);
            values[entry + ".payload.longformtradecorrectionmessage.originaltradesize"] = canonical::number(message->original_trade_size.get());
            values[entry + ".payload.longformtradecorrectionmessage.originalsaleconditionmodifier.originalsettlementtype"] = canonical::text(canonical::character(message->original_sale_condition_modifier.original_settlement_type.get()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.originalsaleconditionmodifier.originaltradethroughexemption"] = canonical::text(canonical::character(message->original_sale_condition_modifier.original_trade_through_exemption.get()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.originalsaleconditionmodifier.originalextendedhoursorsoldcode"] = canonical::text(canonical::character(message->original_sale_condition_modifier.original_extended_hours_or_sold_code.get()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.originalsaleconditionmodifier.originalspecialsalecondition"] = canonical::text(canonical::character(message->original_sale_condition_modifier.original_special_sale_condition.get()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.correctedtradecontrolnumber"] = canonical::text(std::string(message->corrected_trade_control_number.get()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.correctedtradepricelong"] = canonical::scaled(message->corrected_trade_price_long.integer(), -4);
            values[entry + ".payload.longformtradecorrectionmessage.correctedtradesize"] = canonical::number(message->corrected_trade_size.get());
            values[entry + ".payload.longformtradecorrectionmessage.correctedsaleconditionmodifier.correctedsettlementtype"] = canonical::text(canonical::character(message->corrected_sale_condition_modifier.corrected_settlement_type.get()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.correctedsaleconditionmodifier.correctedtradethroughexemption"] = canonical::text(canonical::character(message->corrected_sale_condition_modifier.corrected_trade_through_exemption.get()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.correctedsaleconditionmodifier.correctedextendedhoursorsoldcode"] = canonical::text(canonical::character(message->corrected_sale_condition_modifier.corrected_extended_hours_or_sold_code.get()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.correctedsaleconditionmodifier.correctedspecialsalecondition"] = canonical::text(canonical::character(message->corrected_sale_condition_modifier.corrected_special_sale_condition.get()), ' ', false);
            values[entry + ".payload.longformtradecorrectionmessage.consolidatedvolume"] = canonical::number(message->consolidated_volume.get());
        } else if (iterator.message_type == protocol::NextSharesTradeCorrectionMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.nextsharestradecorrectionmessage";
            [[maybe_unused]] const auto* message = protocol::NextSharesTradeCorrectionMessage::parse(iterator.message);
            values[entry + ".payload.nextsharestradecorrectionmessage.marketcenter"] = canonical::text(canonical::character(message->market_center.get()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.issuesymbol"] = canonical::text(std::string(message->issue_symbol.get()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.securityclass"] = canonical::text(canonical::character(message->security_class.get()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.originaltradecontrolnumber"] = canonical::text(std::string(message->original_trade_control_number.get()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.originalproxyprice"] = canonical::scaled(message->original_proxy_price.integer(), -4);
            values[entry + ".payload.nextsharestradecorrectionmessage.originalnavoffsetamount"] = canonical::scaled(message->original_nav_offset_amount.integer(), -4);
            values[entry + ".payload.nextsharestradecorrectionmessage.originaltradesize"] = canonical::number(message->original_trade_size.get());
            values[entry + ".payload.nextsharestradecorrectionmessage.originalsaleconditionmodifier.originalsettlementtype"] = canonical::text(canonical::character(message->original_sale_condition_modifier.original_settlement_type.get()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.originalsaleconditionmodifier.originaltradethroughexemption"] = canonical::text(canonical::character(message->original_sale_condition_modifier.original_trade_through_exemption.get()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.originalsaleconditionmodifier.originalextendedhoursorsoldcode"] = canonical::text(canonical::character(message->original_sale_condition_modifier.original_extended_hours_or_sold_code.get()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.originalsaleconditionmodifier.originalspecialsalecondition"] = canonical::text(canonical::character(message->original_sale_condition_modifier.original_special_sale_condition.get()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.correctedtradecontrolnumber"] = canonical::text(std::string(message->corrected_trade_control_number.get()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.correctedproxyprice"] = canonical::scaled(message->corrected_proxy_price.integer(), -4);
            values[entry + ".payload.nextsharestradecorrectionmessage.correctednavoffsetamount"] = canonical::scaled(message->corrected_nav_offset_amount.integer(), -4);
            values[entry + ".payload.nextsharestradecorrectionmessage.correctedtradesize"] = canonical::number(message->corrected_trade_size.get());
            values[entry + ".payload.nextsharestradecorrectionmessage.correctedsaleconditionmodifier.correctedsettlementtype"] = canonical::text(canonical::character(message->corrected_sale_condition_modifier.corrected_settlement_type.get()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.correctedsaleconditionmodifier.correctedtradethroughexemption"] = canonical::text(canonical::character(message->corrected_sale_condition_modifier.corrected_trade_through_exemption.get()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.correctedsaleconditionmodifier.correctedextendedhoursorsoldcode"] = canonical::text(canonical::character(message->corrected_sale_condition_modifier.corrected_extended_hours_or_sold_code.get()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.correctedsaleconditionmodifier.correctedspecialsalecondition"] = canonical::text(canonical::character(message->corrected_sale_condition_modifier.corrected_special_sale_condition.get()), ' ', false);
            values[entry + ".payload.nextsharestradecorrectionmessage.consolidatedvolume"] = canonical::number(message->consolidated_volume.get());
        } else if (iterator.message_type == protocol::StockTradingActionMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.stocktradingactionmessage";
            [[maybe_unused]] const auto* message = protocol::StockTradingActionMessage::parse(iterator.message);
            values[entry + ".payload.stocktradingactionmessage.reserved"] = canonical::text(canonical::character(message->reserved.get()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.issuesymbol"] = canonical::text(std::string(message->issue_symbol.get()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.securityclass"] = canonical::text(canonical::character(message->security_class.get()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.currenttradingstate"] = canonical::text(canonical::character(message->current_trading_state.get()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.reason"] = canonical::text(std::string(message->reason.get()), ' ', false);
        } else if (iterator.message_type == protocol::StockDirectoryMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.stockdirectorymessage";
            [[maybe_unused]] const auto* message = protocol::StockDirectoryMessage::parse(iterator.message);
            values[entry + ".payload.stockdirectorymessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.marketcategory"] = canonical::text(canonical::character(message->market_category.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.financialstatusindicator"] = canonical::text(canonical::character(message->financial_status_indicator.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.roundlotsize"] = canonical::number(message->round_lot_size.get());
            values[entry + ".payload.stockdirectorymessage.roundlotsonly"] = canonical::text(canonical::character(message->round_lots_only.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.issueclassification"] = canonical::text(canonical::character(message->issue_classification.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.issuesubtype"] = canonical::text(std::string(message->issue_sub_type.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.authenticity"] = canonical::text(canonical::character(message->authenticity.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.shortsalethresholdindicator"] = canonical::text(canonical::character(message->short_sale_threshold_indicator.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.ipoflag"] = canonical::text(canonical::character(message->ipo_flag.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.luldreferencepricetier"] = canonical::text(canonical::character(message->luld_reference_price_tier.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.etpflag"] = canonical::text(canonical::character(message->etp_flag.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.etpleveragefactor"] = canonical::number(message->etp_leverage_factor.get());
            values[entry + ".payload.stockdirectorymessage.inverseindicator"] = canonical::text(canonical::character(message->inverse_indicator.get()), ' ', false);
            values[entry + ".payload.stockdirectorymessage.bloombergid"] = canonical::text(std::string(message->bloomberg_id.get()), ' ', false);
        } else if (iterator.message_type == protocol::RegShoShortSalePriceTestRestrictedIndicatorMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.regshoshortsalepricetestrestrictedindicatormessage";
            [[maybe_unused]] const auto* message = protocol::RegShoShortSalePriceTestRestrictedIndicatorMessage::parse(iterator.message);
            values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.issuesymbol"] = canonical::text(std::string(message->issue_symbol.get()), ' ', false);
            values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.regshoaction"] = canonical::text(canonical::character(message->reg_sho_action.get()), ' ', false);
        } else if (iterator.message_type == protocol::AdjustedClosingPriceMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.adjustedclosingpricemessage";
            [[maybe_unused]] const auto* message = protocol::AdjustedClosingPriceMessage::parse(iterator.message);
            values[entry + ".payload.adjustedclosingpricemessage.issuesymbol"] = canonical::text(std::string(message->issue_symbol.get()), ' ', false);
            values[entry + ".payload.adjustedclosingpricemessage.securityclass"] = canonical::text(canonical::character(message->security_class.get()), ' ', false);
            values[entry + ".payload.adjustedclosingpricemessage.adjustedclosingprice"] = canonical::scaled(message->adjusted_closing_price.integer(), -4);
        } else if (iterator.message_type == protocol::LongFormAdjustedClosingPriceMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.longformadjustedclosingpricemessage";
            [[maybe_unused]] const auto* message = protocol::LongFormAdjustedClosingPriceMessage::parse(iterator.message);
            values[entry + ".payload.longformadjustedclosingpricemessage.issuesymbol"] = canonical::text(std::string(message->issue_symbol.get()), ' ', false);
            values[entry + ".payload.longformadjustedclosingpricemessage.securityclass"] = canonical::text(canonical::character(message->security_class.get()), ' ', false);
            values[entry + ".payload.longformadjustedclosingpricemessage.adjustedclosingpricelong"] = canonical::scaled(message->adjusted_closing_price_long.integer(), -4);
        } else if (iterator.message_type == protocol::EndOfDayTradeSummaryMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.endofdaytradesummarymessage";
            [[maybe_unused]] const auto* message = protocol::EndOfDayTradeSummaryMessage::parse(iterator.message);
            values[entry + ".payload.endofdaytradesummarymessage.issuesymbol"] = canonical::text(std::string(message->issue_symbol.get()), ' ', false);
            values[entry + ".payload.endofdaytradesummarymessage.marketcategory"] = canonical::text(canonical::character(message->market_category.get()), ' ', false);
            values[entry + ".payload.endofdaytradesummarymessage.consolidatedhighprice"] = canonical::scaled(message->consolidated_high_price.integer(), -4);
            values[entry + ".payload.endofdaytradesummarymessage.consolidatedlowprice"] = canonical::scaled(message->consolidated_low_price.integer(), -4);
            values[entry + ".payload.endofdaytradesummarymessage.consolidatedclosingprice"] = canonical::scaled(message->consolidated_closing_price.integer(), -4);
            values[entry + ".payload.endofdaytradesummarymessage.consolidatedvolume"] = canonical::number(message->consolidated_volume.get());
            values[entry + ".payload.endofdaytradesummarymessage.consolidatedopenprice"] = canonical::scaled(message->consolidated_open_price.integer(), -4);
        } else if (iterator.message_type == protocol::LongFormEndOfDayTradeSummaryMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.longformendofdaytradesummarymessage";
            [[maybe_unused]] const auto* message = protocol::LongFormEndOfDayTradeSummaryMessage::parse(iterator.message);
            values[entry + ".payload.longformendofdaytradesummarymessage.issuesymbol"] = canonical::text(std::string(message->issue_symbol.get()), ' ', false);
            values[entry + ".payload.longformendofdaytradesummarymessage.marketcategory"] = canonical::text(canonical::character(message->market_category.get()), ' ', false);
            values[entry + ".payload.longformendofdaytradesummarymessage.consolidatedhighpricelong"] = canonical::scaled(message->consolidated_high_price_long.integer(), -4);
            values[entry + ".payload.longformendofdaytradesummarymessage.consolidatedlowpricelong"] = canonical::scaled(message->consolidated_low_price_long.integer(), -4);
            values[entry + ".payload.longformendofdaytradesummarymessage.consolidatedclosingpricelong"] = canonical::scaled(message->consolidated_closing_price_long.integer(), -4);
            values[entry + ".payload.longformendofdaytradesummarymessage.consolidatedvolume"] = canonical::number(message->consolidated_volume.get());
            values[entry + ".payload.longformendofdaytradesummarymessage.consolidatedopenpricelong"] = canonical::scaled(message->consolidated_open_price_long.integer(), -4);
        } else if (iterator.message_type == protocol::NextSharesEndOfDayTradeSummaryMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.nextsharesendofdaytradesummarymessage";
            [[maybe_unused]] const auto* message = protocol::NextSharesEndOfDayTradeSummaryMessage::parse(iterator.message);
            values[entry + ".payload.nextsharesendofdaytradesummarymessage.issuesymbol"] = canonical::text(std::string(message->issue_symbol.get()), ' ', false);
            values[entry + ".payload.nextsharesendofdaytradesummarymessage.marketcategory"] = canonical::text(canonical::character(message->market_category.get()), ' ', false);
            values[entry + ".payload.nextsharesendofdaytradesummarymessage.consolidatedhighprice"] = canonical::scaled(message->consolidated_high_price.integer(), -4);
            values[entry + ".payload.nextsharesendofdaytradesummarymessage.navoffsetamounthigh"] = canonical::scaled(message->nav_offset_amount_high.integer(), -4);
            values[entry + ".payload.nextsharesendofdaytradesummarymessage.consolidatedlowprice"] = canonical::scaled(message->consolidated_low_price.integer(), -4);
            values[entry + ".payload.nextsharesendofdaytradesummarymessage.navoffsetamountlow"] = canonical::scaled(message->nav_offset_amount_low.integer(), -4);
            values[entry + ".payload.nextsharesendofdaytradesummarymessage.consolidatedclosingprice"] = canonical::scaled(message->consolidated_closing_price.integer(), -4);
            values[entry + ".payload.nextsharesendofdaytradesummarymessage.navoffsetamountclosing"] = canonical::scaled(message->nav_offset_amount_closing.integer(), -4);
            values[entry + ".payload.nextsharesendofdaytradesummarymessage.consolidatedvolume"] = canonical::number(message->consolidated_volume.get());
            values[entry + ".payload.nextsharesendofdaytradesummarymessage.consolidatedopenprice"] = canonical::scaled(message->consolidated_open_price.integer(), -4);
            values[entry + ".payload.nextsharesendofdaytradesummarymessage.navoffsetamountopen"] = canonical::scaled(message->nav_offset_amount_open.integer(), -4);
        } else if (iterator.message_type == protocol::IpoInformationMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.ipoinformationmessage";
            [[maybe_unused]] const auto* message = protocol::IpoInformationMessage::parse(iterator.message);
            values[entry + ".payload.ipoinformationmessage.issuesymbol"] = canonical::text(std::string(message->issue_symbol.get()), ' ', false);
            values[entry + ".payload.ipoinformationmessage.securityclass"] = canonical::text(canonical::character(message->security_class.get()), ' ', false);
            values[entry + ".payload.ipoinformationmessage.referencefornetchange"] = canonical::text(canonical::character(message->reference_for_net_change.get()), ' ', false);
            values[entry + ".payload.ipoinformationmessage.referenceprice"] = canonical::scaled(message->reference_price.integer(), -4);
        } else if (iterator.message_type == protocol::MwcbDeclineLevelMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.mwcbdeclinelevelmessage";
            [[maybe_unused]] const auto* message = protocol::MwcbDeclineLevelMessage::parse(iterator.message);
            values[entry + ".payload.mwcbdeclinelevelmessage.level1"] = canonical::scaled(message->level_1.integer(), -8);
            values[entry + ".payload.mwcbdeclinelevelmessage.level2"] = canonical::scaled(message->level_2.integer(), -8);
            values[entry + ".payload.mwcbdeclinelevelmessage.level3"] = canonical::scaled(message->level_3.integer(), -8);
        } else if (iterator.message_type == protocol::MwcbStatusMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.mwcbstatusmessage";
            [[maybe_unused]] const auto* message = protocol::MwcbStatusMessage::parse(iterator.message);
            values[entry + ".payload.mwcbstatusmessage.breachedlevel"] = canonical::text(canonical::character(message->breached_level.get()), ' ', false);
        } else if (iterator.message_type == protocol::IpoQuotingPeriodUpdateMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.ipoquotingperiodupdatemessage";
            [[maybe_unused]] const auto* message = protocol::IpoQuotingPeriodUpdateMessage::parse(iterator.message);
            values[entry + ".payload.ipoquotingperiodupdatemessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.ipoquotingperiodupdatemessage.ipoquotationreleasetime"] = canonical::number(message->ipo_quotation_release_time.get());
            values[entry + ".payload.ipoquotingperiodupdatemessage.ipoquotationreleasequalifier"] = canonical::text(canonical::character(message->ipo_quotation_release_qualifier.get()), ' ', false);
            values[entry + ".payload.ipoquotingperiodupdatemessage.ipoprice"] = canonical::scaled(message->ipo_price.integer(), -4);
        } else if (iterator.message_type == protocol::OperationalHaltMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.operationalhaltmessage";
            [[maybe_unused]] const auto* message = protocol::OperationalHaltMessage::parse(iterator.message);
            values[entry + ".payload.operationalhaltmessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.operationalhaltmessage.marketcode"] = canonical::text(canonical::character(message->market_code.get()), ' ', false);
            values[entry + ".payload.operationalhaltmessage.operationalhaltaction"] = canonical::text(canonical::character(message->operational_halt_action.get()), ' ', false);
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
    std::printf("== Nasdaq.NsmEquities.NlsPlus.Itch.v3.0 (modern values)\n");
    int failures = 0;
    failures += check("LongFormTradeReportMessage", "Nasdaq/NsmEquities.NlsPlus.Itch.v3.0/LongFormTradeReportMessage.pcap", "nasdaq/nsmequities/nlsplus/itch/v3.0/LongFormTradeReportMessage.values");
    failures += check("RegShoShortSalePriceTestRestrictedIndicatorMessage", "Nasdaq/NsmEquities.NlsPlus.Itch.v3.0/RegShoShortSalePriceTestRestrictedIndicatorMessage.pcap", "nasdaq/nsmequities/nlsplus/itch/v3.0/RegShoShortSalePriceTestRestrictedIndicatorMessage.values");
    failures += check("StockTradingActionMessage", "Nasdaq/NsmEquities.NlsPlus.Itch.v3.0/StockTradingActionMessage.pcap", "nasdaq/nsmequities/nlsplus/itch/v3.0/StockTradingActionMessage.values");
    failures += check("SystemEventMessage", "Nasdaq/NsmEquities.NlsPlus.Itch.v3.0/SystemEventMessage.pcap", "nasdaq/nsmequities/nlsplus/itch/v3.0/SystemEventMessage.values");
    failures += check("TradeReportMessage", "Nasdaq/NsmEquities.NlsPlus.Itch.v3.0/TradeReportMessage.pcap", "nasdaq/nsmequities/nlsplus/itch/v3.0/TradeReportMessage.values");
    return failures == 0 ? 0 : 1;
}
