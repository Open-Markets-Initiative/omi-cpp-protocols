// Nasdaq.NsmEquities.TotalView.Itch.v5.0.2023 canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/modern/nasdaq/nsmequities/totalview/itch/v5.0.2023/definitions.hpp"

namespace protocol = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;

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
            values[entry + ".payload.systemeventmessage.stocklocate"] = canonical::number(message->stock_locate.get());
            values[entry + ".payload.systemeventmessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.systemeventmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.systemeventmessage.eventcode"] = canonical::text(canonical::character(message->event_code.get()), ' ', false);
        } else if (iterator.message_type == protocol::StockDirectoryMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.stockdirectorymessage";
            [[maybe_unused]] const auto* message = protocol::StockDirectoryMessage::parse(iterator.message);
            values[entry + ".payload.stockdirectorymessage.stocklocate"] = canonical::number(message->stock_locate.get());
            values[entry + ".payload.stockdirectorymessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.stockdirectorymessage.timestamp"] = canonical::number(message->timestamp.get());
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
        } else if (iterator.message_type == protocol::StockTradingActionMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.stocktradingactionmessage";
            [[maybe_unused]] const auto* message = protocol::StockTradingActionMessage::parse(iterator.message);
            values[entry + ".payload.stocktradingactionmessage.stocklocate"] = canonical::number(message->stock_locate.get());
            values[entry + ".payload.stocktradingactionmessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.stocktradingactionmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.stocktradingactionmessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.tradingstate"] = canonical::text(canonical::character(message->trading_state.get()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.reserved"] = canonical::text(canonical::character(message->reserved.get()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.reasoncode"] = canonical::text(std::string(message->reason_code.get()), ' ', false);
        } else if (iterator.message_type == protocol::RegShoShortSalePriceTestRestrictedIndicatorMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.regshoshortsalepricetestrestrictedindicatormessage";
            [[maybe_unused]] const auto* message = protocol::RegShoShortSalePriceTestRestrictedIndicatorMessage::parse(iterator.message);
            values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.locatecode"] = canonical::number(message->locate_code.get());
            values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.regshoaction"] = canonical::text(canonical::character(message->reg_sho_action.get()), ' ', false);
        } else if (iterator.message_type == protocol::MarketParticipantPositionMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.marketparticipantpositionmessage";
            [[maybe_unused]] const auto* message = protocol::MarketParticipantPositionMessage::parse(iterator.message);
            values[entry + ".payload.marketparticipantpositionmessage.stocklocate"] = canonical::number(message->stock_locate.get());
            values[entry + ".payload.marketparticipantpositionmessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.marketparticipantpositionmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.marketparticipantpositionmessage.mpid"] = canonical::text(std::string(message->mpid.get()), ' ', false);
            values[entry + ".payload.marketparticipantpositionmessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.marketparticipantpositionmessage.primarymarketmaker"] = canonical::text(canonical::character(message->primary_market_maker.get()), ' ', false);
            values[entry + ".payload.marketparticipantpositionmessage.marketmakermode"] = canonical::text(canonical::character(message->market_maker_mode.get()), ' ', false);
            values[entry + ".payload.marketparticipantpositionmessage.marketparticipantstate"] = canonical::text(canonical::character(message->market_participant_state.get()), ' ', false);
        } else if (iterator.message_type == protocol::MwcbDeclineLevelMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.mwcbdeclinelevelmessage";
            [[maybe_unused]] const auto* message = protocol::MwcbDeclineLevelMessage::parse(iterator.message);
            values[entry + ".payload.mwcbdeclinelevelmessage.stocklocate"] = canonical::number(message->stock_locate.get());
            values[entry + ".payload.mwcbdeclinelevelmessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.mwcbdeclinelevelmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.mwcbdeclinelevelmessage.level1"] = canonical::scaled(message->level_1.integer(), -8);
            values[entry + ".payload.mwcbdeclinelevelmessage.level2"] = canonical::scaled(message->level_2.integer(), -8);
            values[entry + ".payload.mwcbdeclinelevelmessage.level3"] = canonical::scaled(message->level_3.integer(), -8);
        } else if (iterator.message_type == protocol::MwcbStatusLevelMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.mwcbstatuslevelmessage";
            [[maybe_unused]] const auto* message = protocol::MwcbStatusLevelMessage::parse(iterator.message);
            values[entry + ".payload.mwcbstatuslevelmessage.stocklocate"] = canonical::number(message->stock_locate.get());
            values[entry + ".payload.mwcbstatuslevelmessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.mwcbstatuslevelmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.mwcbstatuslevelmessage.breachedlevel"] = canonical::text(canonical::character(message->breached_level.get()), ' ', false);
        } else if (iterator.message_type == protocol::IpoQuotingPeriodUpdate::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.ipoquotingperiodupdate";
            [[maybe_unused]] const auto* message = protocol::IpoQuotingPeriodUpdate::parse(iterator.message);
            values[entry + ".payload.ipoquotingperiodupdate.stocklocate"] = canonical::number(message->stock_locate.get());
            values[entry + ".payload.ipoquotingperiodupdate.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.ipoquotingperiodupdate.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.ipoquotingperiodupdate.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.ipoquotingperiodupdate.ipoquotationreleasetime"] = canonical::number(message->ipo_quotation_release_time.get());
            values[entry + ".payload.ipoquotingperiodupdate.ipoquotationreleasequalifier"] = canonical::text(canonical::character(message->ipo_quotation_release_qualifier.get()), ' ', false);
            values[entry + ".payload.ipoquotingperiodupdate.ipoprice"] = canonical::scaled(message->ipo_price.integer(), -4);
        } else if (iterator.message_type == protocol::LuldAuctionCollarMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.luldauctioncollarmessage";
            [[maybe_unused]] const auto* message = protocol::LuldAuctionCollarMessage::parse(iterator.message);
            values[entry + ".payload.luldauctioncollarmessage.stocklocate"] = canonical::number(message->stock_locate.get());
            values[entry + ".payload.luldauctioncollarmessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.luldauctioncollarmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.luldauctioncollarmessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.luldauctioncollarmessage.auctioncollarreferenceprice"] = canonical::scaled(message->auction_collar_reference_price.integer(), -4);
            values[entry + ".payload.luldauctioncollarmessage.upperauctioncollarprice"] = canonical::scaled(message->upper_auction_collar_price.integer(), -4);
            values[entry + ".payload.luldauctioncollarmessage.lowerauctioncollarprice"] = canonical::scaled(message->lower_auction_collar_price.integer(), -4);
            values[entry + ".payload.luldauctioncollarmessage.auctioncollarextension"] = canonical::number(message->auction_collar_extension.get());
        } else if (iterator.message_type == protocol::OperationalHaltMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.operationalhaltmessage";
            [[maybe_unused]] const auto* message = protocol::OperationalHaltMessage::parse(iterator.message);
            values[entry + ".payload.operationalhaltmessage.stocklocate"] = canonical::number(message->stock_locate.get());
            values[entry + ".payload.operationalhaltmessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.operationalhaltmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.operationalhaltmessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.operationalhaltmessage.marketcode"] = canonical::text(canonical::character(message->market_code.get()), ' ', false);
            values[entry + ".payload.operationalhaltmessage.operationalhaltaction"] = canonical::text(canonical::character(message->operational_halt_action.get()), ' ', false);
        } else if (iterator.message_type == protocol::AddOrderNoMpidAttributionMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.addordernompidattributionmessage";
            [[maybe_unused]] const auto* message = protocol::AddOrderNoMpidAttributionMessage::parse(iterator.message);
            values[entry + ".payload.addordernompidattributionmessage.stocklocate"] = canonical::number(message->stock_locate.get());
            values[entry + ".payload.addordernompidattributionmessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.addordernompidattributionmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.addordernompidattributionmessage.orderreferencenumber"] = canonical::number(message->order_reference_number.get());
            values[entry + ".payload.addordernompidattributionmessage.buysellindicator"] = canonical::text(canonical::character(message->buy_sell_indicator.get()), ' ', false);
            values[entry + ".payload.addordernompidattributionmessage.shares"] = canonical::number(message->shares.get());
            values[entry + ".payload.addordernompidattributionmessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.addordernompidattributionmessage.price"] = canonical::scaled(message->price.integer(), -4);
        } else if (iterator.message_type == protocol::AddOrderWithMpidAttributionMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.addorderwithmpidattributionmessage";
            [[maybe_unused]] const auto* message = protocol::AddOrderWithMpidAttributionMessage::parse(iterator.message);
            values[entry + ".payload.addorderwithmpidattributionmessage.stocklocate"] = canonical::number(message->stock_locate.get());
            values[entry + ".payload.addorderwithmpidattributionmessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.addorderwithmpidattributionmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.addorderwithmpidattributionmessage.orderreferencenumber"] = canonical::number(message->order_reference_number.get());
            values[entry + ".payload.addorderwithmpidattributionmessage.buysellindicator"] = canonical::text(canonical::character(message->buy_sell_indicator.get()), ' ', false);
            values[entry + ".payload.addorderwithmpidattributionmessage.shares"] = canonical::number(message->shares.get());
            values[entry + ".payload.addorderwithmpidattributionmessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.addorderwithmpidattributionmessage.price"] = canonical::scaled(message->price.integer(), -4);
            values[entry + ".payload.addorderwithmpidattributionmessage.attribution"] = canonical::text(std::string(message->attribution.get()), ' ', false);
        } else if (iterator.message_type == protocol::OrderExecutedMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedmessage";
            [[maybe_unused]] const auto* message = protocol::OrderExecutedMessage::parse(iterator.message);
            values[entry + ".payload.orderexecutedmessage.stocklocate"] = canonical::number(message->stock_locate.get());
            values[entry + ".payload.orderexecutedmessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.orderexecutedmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.orderexecutedmessage.orderreferencenumber"] = canonical::number(message->order_reference_number.get());
            values[entry + ".payload.orderexecutedmessage.executedshares"] = canonical::number(message->executed_shares.get());
            values[entry + ".payload.orderexecutedmessage.matchnumber"] = canonical::number(message->match_number.get());
        } else if (iterator.message_type == protocol::OrderExecutedWithPriceMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedwithpricemessage";
            [[maybe_unused]] const auto* message = protocol::OrderExecutedWithPriceMessage::parse(iterator.message);
            values[entry + ".payload.orderexecutedwithpricemessage.stocklocate"] = canonical::number(message->stock_locate.get());
            values[entry + ".payload.orderexecutedwithpricemessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.orderexecutedwithpricemessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.orderexecutedwithpricemessage.orderreferencenumber"] = canonical::number(message->order_reference_number.get());
            values[entry + ".payload.orderexecutedwithpricemessage.executedshares"] = canonical::number(message->executed_shares.get());
            values[entry + ".payload.orderexecutedwithpricemessage.matchnumber"] = canonical::number(message->match_number.get());
            values[entry + ".payload.orderexecutedwithpricemessage.printable"] = canonical::text(canonical::character(message->printable.get()), ' ', false);
            values[entry + ".payload.orderexecutedwithpricemessage.executionprice"] = canonical::scaled(message->execution_price.integer(), -4);
        } else if (iterator.message_type == protocol::OrderCancelMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.ordercancelmessage";
            [[maybe_unused]] const auto* message = protocol::OrderCancelMessage::parse(iterator.message);
            values[entry + ".payload.ordercancelmessage.stocklocate"] = canonical::number(message->stock_locate.get());
            values[entry + ".payload.ordercancelmessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.ordercancelmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.ordercancelmessage.orderreferencenumber"] = canonical::number(message->order_reference_number.get());
            values[entry + ".payload.ordercancelmessage.canceledshares"] = canonical::number(message->canceled_shares.get());
        } else if (iterator.message_type == protocol::OrderDeleteMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderdeletemessage";
            [[maybe_unused]] const auto* message = protocol::OrderDeleteMessage::parse(iterator.message);
            values[entry + ".payload.orderdeletemessage.stocklocate"] = canonical::number(message->stock_locate.get());
            values[entry + ".payload.orderdeletemessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.orderdeletemessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.orderdeletemessage.orderreferencenumber"] = canonical::number(message->order_reference_number.get());
        } else if (iterator.message_type == protocol::OrderReplaceMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderreplacemessage";
            [[maybe_unused]] const auto* message = protocol::OrderReplaceMessage::parse(iterator.message);
            values[entry + ".payload.orderreplacemessage.stocklocate"] = canonical::number(message->stock_locate.get());
            values[entry + ".payload.orderreplacemessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.orderreplacemessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.orderreplacemessage.originalorderreferencenumber"] = canonical::number(message->original_order_reference_number.get());
            values[entry + ".payload.orderreplacemessage.neworderreferencenumber"] = canonical::number(message->new_order_reference_number.get());
            values[entry + ".payload.orderreplacemessage.shares"] = canonical::number(message->shares.get());
            values[entry + ".payload.orderreplacemessage.price"] = canonical::scaled(message->price.integer(), -4);
        } else if (iterator.message_type == protocol::NonCrossTradeMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.noncrosstrademessage";
            [[maybe_unused]] const auto* message = protocol::NonCrossTradeMessage::parse(iterator.message);
            values[entry + ".payload.noncrosstrademessage.stocklocate"] = canonical::number(message->stock_locate.get());
            values[entry + ".payload.noncrosstrademessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.noncrosstrademessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.noncrosstrademessage.orderreferencenumber"] = canonical::number(message->order_reference_number.get());
            values[entry + ".payload.noncrosstrademessage.buysellindicator"] = canonical::text(canonical::character(message->buy_sell_indicator.get()), ' ', false);
            values[entry + ".payload.noncrosstrademessage.shares"] = canonical::number(message->shares.get());
            values[entry + ".payload.noncrosstrademessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.noncrosstrademessage.price"] = canonical::scaled(message->price.integer(), -4);
            values[entry + ".payload.noncrosstrademessage.matchnumber"] = canonical::number(message->match_number.get());
        } else if (iterator.message_type == protocol::CrossTradeMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.crosstrademessage";
            [[maybe_unused]] const auto* message = protocol::CrossTradeMessage::parse(iterator.message);
            values[entry + ".payload.crosstrademessage.stocklocate"] = canonical::number(message->stock_locate.get());
            values[entry + ".payload.crosstrademessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.crosstrademessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.crosstrademessage.crossshares"] = canonical::number(message->cross_shares.get());
            values[entry + ".payload.crosstrademessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.crosstrademessage.crossprice"] = canonical::scaled(message->cross_price.integer(), -4);
            values[entry + ".payload.crosstrademessage.matchnumber"] = canonical::number(message->match_number.get());
            values[entry + ".payload.crosstrademessage.crosstype"] = canonical::text(canonical::character(message->cross_type.get()), ' ', false);
        } else if (iterator.message_type == protocol::BrokenTradeMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.brokentrademessage";
            [[maybe_unused]] const auto* message = protocol::BrokenTradeMessage::parse(iterator.message);
            values[entry + ".payload.brokentrademessage.stocklocate"] = canonical::number(message->stock_locate.get());
            values[entry + ".payload.brokentrademessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.brokentrademessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.brokentrademessage.matchnumber"] = canonical::number(message->match_number.get());
        } else if (iterator.message_type == protocol::NetOrderImbalanceIndicatorMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.netorderimbalanceindicatormessage";
            [[maybe_unused]] const auto* message = protocol::NetOrderImbalanceIndicatorMessage::parse(iterator.message);
            values[entry + ".payload.netorderimbalanceindicatormessage.stocklocate"] = canonical::number(message->stock_locate.get());
            values[entry + ".payload.netorderimbalanceindicatormessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.netorderimbalanceindicatormessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.netorderimbalanceindicatormessage.pairedshares"] = canonical::number(message->paired_shares.get());
            values[entry + ".payload.netorderimbalanceindicatormessage.imbalanceshares"] = canonical::number(message->imbalance_shares.get());
            values[entry + ".payload.netorderimbalanceindicatormessage.imbalancedirection"] = canonical::text(canonical::character(message->imbalance_direction.get()), ' ', false);
            values[entry + ".payload.netorderimbalanceindicatormessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.netorderimbalanceindicatormessage.farprice"] = canonical::scaled(message->far_price.integer(), -4);
            values[entry + ".payload.netorderimbalanceindicatormessage.nearprice"] = canonical::scaled(message->near_price.integer(), -4);
            values[entry + ".payload.netorderimbalanceindicatormessage.currentreferenceprice"] = canonical::scaled(message->current_reference_price.integer(), -4);
            values[entry + ".payload.netorderimbalanceindicatormessage.crosstype"] = canonical::text(canonical::character(message->cross_type.get()), ' ', false);
            values[entry + ".payload.netorderimbalanceindicatormessage.pricevariationindicator"] = canonical::text(canonical::character(message->price_variation_indicator.get()), ' ', false);
        } else if (iterator.message_type == protocol::RetailPriceImprovementIndicatorMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.retailpriceimprovementindicatormessage";
            [[maybe_unused]] const auto* message = protocol::RetailPriceImprovementIndicatorMessage::parse(iterator.message);
            values[entry + ".payload.retailpriceimprovementindicatormessage.stocklocate"] = canonical::number(message->stock_locate.get());
            values[entry + ".payload.retailpriceimprovementindicatormessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.retailpriceimprovementindicatormessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.retailpriceimprovementindicatormessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.retailpriceimprovementindicatormessage.interestflag"] = canonical::text(canonical::character(message->interest_flag.get()), ' ', false);
        } else if (iterator.message_type == protocol::DirectListingWithCapitalRaisePriceDiscoveryMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.directlistingwithcapitalraisepricediscoverymessage";
            [[maybe_unused]] const auto* message = protocol::DirectListingWithCapitalRaisePriceDiscoveryMessage::parse(iterator.message);
            values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.stocklocate"] = canonical::number(message->stock_locate.get());
            values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.trackingnumber"] = canonical::number(message->tracking_number.get());
            values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.stock"] = canonical::text(std::string(message->stock.get()), ' ', false);
            values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.openeligibilitystatus"] = canonical::text(canonical::character(message->open_eligibility_status.get()), ' ', false);
            values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.minimumallowableprice"] = canonical::scaled(message->minimum_allowable_price.integer(), -4);
            values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.maximumallowableprice"] = canonical::scaled(message->maximum_allowable_price.integer(), -4);
            values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.nearexecutionprice"] = canonical::scaled(message->near_execution_price.integer(), -4);
            values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.nearexecutiontime"] = canonical::number(message->near_execution_time.get());
            values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.lowerpricerangecollar"] = canonical::scaled(message->lower_price_range_collar.integer(), -4);
            values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.upperpricerangecollar"] = canonical::scaled(message->upper_price_range_collar.integer(), -4);
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
    std::printf("== Nasdaq.NsmEquities.TotalView.Itch.v5.0.2023 (modern values)\n");
    int failures = 0;
    failures += check("AddOrderNoMpidAttributionMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2023/AddOrderNoMpidAttributionMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2023/AddOrderNoMpidAttributionMessage.values");
    failures += check("AddOrderWithMpidAttributionMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2023/AddOrderWithMpidAttributionMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2023/AddOrderWithMpidAttributionMessage.values");
    failures += check("CrossTradeMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2023/CrossTradeMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2023/CrossTradeMessage.values");
    failures += check("LuldAuctionCollarMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2023/LuldAuctionCollarMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2023/LuldAuctionCollarMessage.values");
    failures += check("MarketParticipantPositionMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2023/MarketParticipantPositionMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2023/MarketParticipantPositionMessage.values");
    failures += check("NetOrderImbalanceIndicatorMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2023/NetOrderImbalanceIndicatorMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2023/NetOrderImbalanceIndicatorMessage.values");
    failures += check("NonCrossTradeMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2023/NonCrossTradeMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2023/NonCrossTradeMessage.values");
    failures += check("OrderCancelMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2023/OrderCancelMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2023/OrderCancelMessage.values");
    failures += check("OrderDeleteMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2023/OrderDeleteMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2023/OrderDeleteMessage.values");
    failures += check("OrderExecutedMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2023/OrderExecutedMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2023/OrderExecutedMessage.values");
    failures += check("OrderExecutedWithPriceMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2023/OrderExecutedWithPriceMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2023/OrderExecutedWithPriceMessage.values");
    failures += check("OrderReplaceMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2023/OrderReplaceMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2023/OrderReplaceMessage.values");
    failures += check("RegShoShortSalePriceTestRestrictedIndicatorMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2023/RegShoShortSalePriceTestRestrictedIndicatorMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2023/RegShoShortSalePriceTestRestrictedIndicatorMessage.values");
    failures += check("StockTradingActionMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2023/StockTradingActionMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2023/StockTradingActionMessage.values");
    failures += check("SystemEventMessage", "Nasdaq/NsmEquities.TotalView.Itch.v5.0.2023/SystemEventMessage.pcap", "nasdaq/nsmequities/totalview/itch/v5.0.2023/SystemEventMessage.values");
    return failures == 0 ? 0 : 1;
}