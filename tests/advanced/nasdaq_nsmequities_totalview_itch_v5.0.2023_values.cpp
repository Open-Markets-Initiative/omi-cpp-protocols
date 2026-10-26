// Nasdaq.NsmEquities.TotalView.Itch.v5.0.2023 canonical values, through the Advanced session layer: every value Advanced
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
#include "cpp/advanced/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/session.hpp"

namespace protocol = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;

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
        values[entry + ".payload.systemeventmessage.stocklocate"] = canonical::number(message.fields.stock_locate.get().value());
        values[entry + ".payload.systemeventmessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.systemeventmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.systemeventmessage.eventcode"] = canonical::text(canonical::character(message.fields.event_code.get().value()), ' ', false);
    }

    void on_message(const protocol::stock_directory_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.stockdirectorymessage";
        values[entry + ".payload.stockdirectorymessage.stocklocate"] = canonical::number(message.fields.stock_locate.get().value());
        values[entry + ".payload.stockdirectorymessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.stockdirectorymessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
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
    }

    void on_message(const protocol::stock_trading_action_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.stocktradingactionmessage";
        values[entry + ".payload.stocktradingactionmessage.stocklocate"] = canonical::number(message.fields.stock_locate.get().value());
        values[entry + ".payload.stocktradingactionmessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.stocktradingactionmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.stocktradingactionmessage.stock"] = canonical::text(std::string(message.fields.stock.get().value()), ' ', false);
        values[entry + ".payload.stocktradingactionmessage.tradingstate"] = canonical::text(canonical::character(message.fields.trading_state.get().value()), ' ', false);
        values[entry + ".payload.stocktradingactionmessage.reserved"] = canonical::text(canonical::character(message.fields.reserved.get().value()), ' ', false);
        values[entry + ".payload.stocktradingactionmessage.reasoncode"] = canonical::text(std::string(message.fields.reason_code.get().value()), ' ', false);
    }

    void on_message(const protocol::reg_sho_short_sale_price_test_restricted_indicator_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.regshoshortsalepricetestrestrictedindicatormessage";
        values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.locatecode"] = canonical::number(message.fields.locate_code.get().value());
        values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.stock"] = canonical::text(std::string(message.fields.stock.get().value()), ' ', false);
        values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.regshoaction"] = canonical::text(canonical::character(message.fields.reg_sho_action.get().value()), ' ', false);
    }

    void on_message(const protocol::market_participant_position_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.marketparticipantpositionmessage";
        values[entry + ".payload.marketparticipantpositionmessage.stocklocate"] = canonical::number(message.fields.stock_locate.get().value());
        values[entry + ".payload.marketparticipantpositionmessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.marketparticipantpositionmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.marketparticipantpositionmessage.mpid"] = canonical::text(std::string(message.fields.mpid.get().value()), ' ', false);
        values[entry + ".payload.marketparticipantpositionmessage.stock"] = canonical::text(std::string(message.fields.stock.get().value()), ' ', false);
        values[entry + ".payload.marketparticipantpositionmessage.primarymarketmaker"] = canonical::text(canonical::character(message.fields.primary_market_maker.get().value()), ' ', false);
        values[entry + ".payload.marketparticipantpositionmessage.marketmakermode"] = canonical::text(canonical::character(message.fields.market_maker_mode.get().value()), ' ', false);
        values[entry + ".payload.marketparticipantpositionmessage.marketparticipantstate"] = canonical::text(canonical::character(message.fields.market_participant_state.get().value()), ' ', false);
    }

    void on_message(const protocol::mwcb_decline_level_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.mwcbdeclinelevelmessage";
        values[entry + ".payload.mwcbdeclinelevelmessage.stocklocate"] = canonical::number(message.fields.stock_locate.get().value());
        values[entry + ".payload.mwcbdeclinelevelmessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.mwcbdeclinelevelmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.mwcbdeclinelevelmessage.level1"] = canonical::scaled(message.fields.level_1.get().value(), -8);
        values[entry + ".payload.mwcbdeclinelevelmessage.level2"] = canonical::scaled(message.fields.level_2.get().value(), -8);
        values[entry + ".payload.mwcbdeclinelevelmessage.level3"] = canonical::scaled(message.fields.level_3.get().value(), -8);
    }

    void on_message(const protocol::mwcb_status_level_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.mwcbstatuslevelmessage";
        values[entry + ".payload.mwcbstatuslevelmessage.stocklocate"] = canonical::number(message.fields.stock_locate.get().value());
        values[entry + ".payload.mwcbstatuslevelmessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.mwcbstatuslevelmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.mwcbstatuslevelmessage.breachedlevel"] = canonical::text(canonical::character(message.fields.breached_level.get().value()), ' ', false);
    }

    void on_message(const protocol::ipo_quoting_period_update& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.ipoquotingperiodupdate";
        values[entry + ".payload.ipoquotingperiodupdate.stocklocate"] = canonical::number(message.fields.stock_locate.get().value());
        values[entry + ".payload.ipoquotingperiodupdate.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.ipoquotingperiodupdate.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.ipoquotingperiodupdate.stock"] = canonical::text(std::string(message.fields.stock.get().value()), ' ', false);
        values[entry + ".payload.ipoquotingperiodupdate.ipoquotationreleasetime"] = canonical::number(message.fields.ipo_quotation_release_time.get().value());
        values[entry + ".payload.ipoquotingperiodupdate.ipoquotationreleasequalifier"] = canonical::text(canonical::character(message.fields.ipo_quotation_release_qualifier.get().value()), ' ', false);
        values[entry + ".payload.ipoquotingperiodupdate.ipoprice"] = canonical::scaled(message.fields.ipo_price.get().value(), -4);
    }

    void on_message(const protocol::luld_auction_collar_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.luldauctioncollarmessage";
        values[entry + ".payload.luldauctioncollarmessage.stocklocate"] = canonical::number(message.fields.stock_locate.get().value());
        values[entry + ".payload.luldauctioncollarmessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.luldauctioncollarmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.luldauctioncollarmessage.stock"] = canonical::text(std::string(message.fields.stock.get().value()), ' ', false);
        values[entry + ".payload.luldauctioncollarmessage.auctioncollarreferenceprice"] = canonical::scaled(message.fields.auction_collar_reference_price.get().value(), -4);
        values[entry + ".payload.luldauctioncollarmessage.upperauctioncollarprice"] = canonical::scaled(message.fields.upper_auction_collar_price.get().value(), -4);
        values[entry + ".payload.luldauctioncollarmessage.lowerauctioncollarprice"] = canonical::scaled(message.fields.lower_auction_collar_price.get().value(), -4);
        values[entry + ".payload.luldauctioncollarmessage.auctioncollarextension"] = canonical::number(message.fields.auction_collar_extension.get().value());
    }

    void on_message(const protocol::operational_halt_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.operationalhaltmessage";
        values[entry + ".payload.operationalhaltmessage.stocklocate"] = canonical::number(message.fields.stock_locate.get().value());
        values[entry + ".payload.operationalhaltmessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.operationalhaltmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.operationalhaltmessage.stock"] = canonical::text(std::string(message.fields.stock.get().value()), ' ', false);
        values[entry + ".payload.operationalhaltmessage.marketcode"] = canonical::text(canonical::character(message.fields.market_code.get().value()), ' ', false);
        values[entry + ".payload.operationalhaltmessage.operationalhaltaction"] = canonical::text(canonical::character(message.fields.operational_halt_action.get().value()), ' ', false);
    }

    void on_message(const protocol::add_order_no_mpid_attribution_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.addordernompidattributionmessage";
        values[entry + ".payload.addordernompidattributionmessage.stocklocate"] = canonical::number(message.fields.stock_locate.get().value());
        values[entry + ".payload.addordernompidattributionmessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.addordernompidattributionmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.addordernompidattributionmessage.orderreferencenumber"] = canonical::number(message.fields.order_reference_number.get().value());
        values[entry + ".payload.addordernompidattributionmessage.buysellindicator"] = canonical::text(canonical::character(message.fields.buy_sell_indicator.get().value()), ' ', false);
        values[entry + ".payload.addordernompidattributionmessage.shares"] = canonical::number(message.fields.shares.get().value());
        values[entry + ".payload.addordernompidattributionmessage.stock"] = canonical::text(std::string(message.fields.stock.get().value()), ' ', false);
        values[entry + ".payload.addordernompidattributionmessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
    }

    void on_message(const protocol::add_order_with_mpid_attribution_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.addorderwithmpidattributionmessage";
        values[entry + ".payload.addorderwithmpidattributionmessage.stocklocate"] = canonical::number(message.fields.stock_locate.get().value());
        values[entry + ".payload.addorderwithmpidattributionmessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.addorderwithmpidattributionmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.addorderwithmpidattributionmessage.orderreferencenumber"] = canonical::number(message.fields.order_reference_number.get().value());
        values[entry + ".payload.addorderwithmpidattributionmessage.buysellindicator"] = canonical::text(canonical::character(message.fields.buy_sell_indicator.get().value()), ' ', false);
        values[entry + ".payload.addorderwithmpidattributionmessage.shares"] = canonical::number(message.fields.shares.get().value());
        values[entry + ".payload.addorderwithmpidattributionmessage.stock"] = canonical::text(std::string(message.fields.stock.get().value()), ' ', false);
        values[entry + ".payload.addorderwithmpidattributionmessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".payload.addorderwithmpidattributionmessage.attribution"] = canonical::text(std::string(message.fields.attribution.get().value()), ' ', false);
    }

    void on_message(const protocol::order_executed_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedmessage";
        values[entry + ".payload.orderexecutedmessage.stocklocate"] = canonical::number(message.fields.stock_locate.get().value());
        values[entry + ".payload.orderexecutedmessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.orderexecutedmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.orderexecutedmessage.orderreferencenumber"] = canonical::number(message.fields.order_reference_number.get().value());
        values[entry + ".payload.orderexecutedmessage.executedshares"] = canonical::number(message.fields.executed_shares.get().value());
        values[entry + ".payload.orderexecutedmessage.matchnumber"] = canonical::number(message.fields.match_number.get().value());
    }

    void on_message(const protocol::order_executed_with_price_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedwithpricemessage";
        values[entry + ".payload.orderexecutedwithpricemessage.stocklocate"] = canonical::number(message.fields.stock_locate.get().value());
        values[entry + ".payload.orderexecutedwithpricemessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.orderexecutedwithpricemessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.orderexecutedwithpricemessage.orderreferencenumber"] = canonical::number(message.fields.order_reference_number.get().value());
        values[entry + ".payload.orderexecutedwithpricemessage.executedshares"] = canonical::number(message.fields.executed_shares.get().value());
        values[entry + ".payload.orderexecutedwithpricemessage.matchnumber"] = canonical::number(message.fields.match_number.get().value());
        values[entry + ".payload.orderexecutedwithpricemessage.printable"] = canonical::text(canonical::character(message.fields.printable.get().value()), ' ', false);
        values[entry + ".payload.orderexecutedwithpricemessage.executionprice"] = canonical::scaled(message.fields.execution_price.get().value(), -4);
    }

    void on_message(const protocol::order_cancel_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.ordercancelmessage";
        values[entry + ".payload.ordercancelmessage.stocklocate"] = canonical::number(message.fields.stock_locate.get().value());
        values[entry + ".payload.ordercancelmessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.ordercancelmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.ordercancelmessage.orderreferencenumber"] = canonical::number(message.fields.order_reference_number.get().value());
        values[entry + ".payload.ordercancelmessage.canceledshares"] = canonical::number(message.fields.canceled_shares.get().value());
    }

    void on_message(const protocol::order_delete_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.orderdeletemessage";
        values[entry + ".payload.orderdeletemessage.stocklocate"] = canonical::number(message.fields.stock_locate.get().value());
        values[entry + ".payload.orderdeletemessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.orderdeletemessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.orderdeletemessage.orderreferencenumber"] = canonical::number(message.fields.order_reference_number.get().value());
    }

    void on_message(const protocol::order_replace_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.orderreplacemessage";
        values[entry + ".payload.orderreplacemessage.stocklocate"] = canonical::number(message.fields.stock_locate.get().value());
        values[entry + ".payload.orderreplacemessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.orderreplacemessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.orderreplacemessage.originalorderreferencenumber"] = canonical::number(message.fields.original_order_reference_number.get().value());
        values[entry + ".payload.orderreplacemessage.neworderreferencenumber"] = canonical::number(message.fields.new_order_reference_number.get().value());
        values[entry + ".payload.orderreplacemessage.shares"] = canonical::number(message.fields.shares.get().value());
        values[entry + ".payload.orderreplacemessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
    }

    void on_message(const protocol::non_cross_trade_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.noncrosstrademessage";
        values[entry + ".payload.noncrosstrademessage.stocklocate"] = canonical::number(message.fields.stock_locate.get().value());
        values[entry + ".payload.noncrosstrademessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.noncrosstrademessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.noncrosstrademessage.orderreferencenumber"] = canonical::number(message.fields.order_reference_number.get().value());
        values[entry + ".payload.noncrosstrademessage.buysellindicator"] = canonical::text(canonical::character(message.fields.buy_sell_indicator.get().value()), ' ', false);
        values[entry + ".payload.noncrosstrademessage.shares"] = canonical::number(message.fields.shares.get().value());
        values[entry + ".payload.noncrosstrademessage.stock"] = canonical::text(std::string(message.fields.stock.get().value()), ' ', false);
        values[entry + ".payload.noncrosstrademessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".payload.noncrosstrademessage.matchnumber"] = canonical::number(message.fields.match_number.get().value());
    }

    void on_message(const protocol::cross_trade_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.crosstrademessage";
        values[entry + ".payload.crosstrademessage.stocklocate"] = canonical::number(message.fields.stock_locate.get().value());
        values[entry + ".payload.crosstrademessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.crosstrademessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.crosstrademessage.crossshares"] = canonical::number(message.fields.cross_shares.get().value());
        values[entry + ".payload.crosstrademessage.stock"] = canonical::text(std::string(message.fields.stock.get().value()), ' ', false);
        values[entry + ".payload.crosstrademessage.crossprice"] = canonical::scaled(message.fields.cross_price.get().value(), -4);
        values[entry + ".payload.crosstrademessage.matchnumber"] = canonical::number(message.fields.match_number.get().value());
        values[entry + ".payload.crosstrademessage.crosstype"] = canonical::text(canonical::character(message.fields.cross_type.get().value()), ' ', false);
    }

    void on_message(const protocol::broken_trade_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.brokentrademessage";
        values[entry + ".payload.brokentrademessage.stocklocate"] = canonical::number(message.fields.stock_locate.get().value());
        values[entry + ".payload.brokentrademessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.brokentrademessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.brokentrademessage.matchnumber"] = canonical::number(message.fields.match_number.get().value());
    }

    void on_message(const protocol::net_order_imbalance_indicator_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.netorderimbalanceindicatormessage";
        values[entry + ".payload.netorderimbalanceindicatormessage.stocklocate"] = canonical::number(message.fields.stock_locate.get().value());
        values[entry + ".payload.netorderimbalanceindicatormessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.netorderimbalanceindicatormessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.netorderimbalanceindicatormessage.pairedshares"] = canonical::number(message.fields.paired_shares.get().value());
        values[entry + ".payload.netorderimbalanceindicatormessage.imbalanceshares"] = canonical::number(message.fields.imbalance_shares.get().value());
        values[entry + ".payload.netorderimbalanceindicatormessage.imbalancedirection"] = canonical::text(canonical::character(message.fields.imbalance_direction.get().value()), ' ', false);
        values[entry + ".payload.netorderimbalanceindicatormessage.stock"] = canonical::text(std::string(message.fields.stock.get().value()), ' ', false);
        values[entry + ".payload.netorderimbalanceindicatormessage.farprice"] = canonical::scaled(message.fields.far_price.get().value(), -4);
        values[entry + ".payload.netorderimbalanceindicatormessage.nearprice"] = canonical::scaled(message.fields.near_price.get().value(), -4);
        values[entry + ".payload.netorderimbalanceindicatormessage.currentreferenceprice"] = canonical::scaled(message.fields.current_reference_price.get().value(), -4);
        values[entry + ".payload.netorderimbalanceindicatormessage.crosstype"] = canonical::text(canonical::character(message.fields.cross_type.get().value()), ' ', false);
        values[entry + ".payload.netorderimbalanceindicatormessage.pricevariationindicator"] = canonical::text(canonical::character(message.fields.price_variation_indicator.get().value()), ' ', false);
    }

    void on_message(const protocol::retail_price_improvement_indicator_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.retailpriceimprovementindicatormessage";
        values[entry + ".payload.retailpriceimprovementindicatormessage.stocklocate"] = canonical::number(message.fields.stock_locate.get().value());
        values[entry + ".payload.retailpriceimprovementindicatormessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.retailpriceimprovementindicatormessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.retailpriceimprovementindicatormessage.stock"] = canonical::text(std::string(message.fields.stock.get().value()), ' ', false);
        values[entry + ".payload.retailpriceimprovementindicatormessage.interestflag"] = canonical::text(canonical::character(message.fields.interest_flag.get().value()), ' ', false);
    }

    void on_message(const protocol::direct_listing_with_capital_raise_price_discovery_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.directlistingwithcapitalraisepricediscoverymessage";
        values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.stocklocate"] = canonical::number(message.fields.stock_locate.get().value());
        values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.trackingnumber"] = canonical::number(message.fields.tracking_number.get().value());
        values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.stock"] = canonical::text(std::string(message.fields.stock.get().value()), ' ', false);
        values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.openeligibilitystatus"] = canonical::text(canonical::character(message.fields.open_eligibility_status.get().value()), ' ', false);
        values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.minimumallowableprice"] = canonical::scaled(message.fields.minimum_allowable_price.get().value(), -4);
        values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.maximumallowableprice"] = canonical::scaled(message.fields.maximum_allowable_price.get().value(), -4);
        values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.nearexecutionprice"] = canonical::scaled(message.fields.near_execution_price.get().value(), -4);
        values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.nearexecutiontime"] = canonical::number(message.fields.near_execution_time.get().value());
        values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.lowerpricerangecollar"] = canonical::scaled(message.fields.lower_price_range_collar.get().value(), -4);
        values[entry + ".payload.directlistingwithcapitalraisepricediscoverymessage.upperpricerangecollar"] = canonical::scaled(message.fields.upper_price_range_collar.get().value(), -4);
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
    std::printf("== Nasdaq.NsmEquities.TotalView.Itch.v5.0.2023 (advanced values)\n");
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