// Nasdaq.PsxEquities.TotalView.Itch.v5.0 canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/binary/classes/nasdaq/psxequities/totalview/itch/v5.0/definitions.hpp"

namespace protocol = ::nasdaq::psxequities::totalview::itch::v5_0;

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
            values[entry + ".payload.systemeventmessage.stocklocate"] = canonical::number((*message).stock_locate());
            values[entry + ".payload.systemeventmessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.systemeventmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.systemeventmessage.eventcode"] = canonical::text(canonical::character((*message).event_code()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::StockDirectoryMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.stockdirectorymessage";
            values[entry + ".payload.stockdirectorymessage.stocklocate"] = canonical::number((*message).stock_locate());
            values[entry + ".payload.stockdirectorymessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.stockdirectorymessage.timestamp"] = canonical::number((*message).timestamp());
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
        } else if (const auto* message = dynamic_cast<const protocol::StockTradingActionMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.stocktradingactionmessage";
            values[entry + ".payload.stocktradingactionmessage.stocklocate"] = canonical::number((*message).stock_locate());
            values[entry + ".payload.stocktradingactionmessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.stocktradingactionmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.stocktradingactionmessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.tradingstate"] = canonical::text(canonical::character((*message).trading_state()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.reserved"] = canonical::text(canonical::character((*message).reserved()), ' ', false);
            values[entry + ".payload.stocktradingactionmessage.reason"] = canonical::text(std::string((*message).reason()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::RegShoShortSalePriceTestRestrictedIndicatorMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.regshoshortsalepricetestrestrictedindicatormessage";
            values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.locatecode"] = canonical::number((*message).locate_code());
            values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.regshoshortsalepricetestrestrictedindicatormessage.regshoaction"] = canonical::text(canonical::character((*message).reg_sho_action()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::MarketParticipantPositionMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.marketparticipantpositionmessage";
            values[entry + ".payload.marketparticipantpositionmessage.stocklocate"] = canonical::number((*message).stock_locate());
            values[entry + ".payload.marketparticipantpositionmessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.marketparticipantpositionmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.marketparticipantpositionmessage.mpid"] = canonical::text(std::string((*message).mpid()), ' ', false);
            values[entry + ".payload.marketparticipantpositionmessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.marketparticipantpositionmessage.primarymarketmaker"] = canonical::text(canonical::character((*message).primary_market_maker()), ' ', false);
            values[entry + ".payload.marketparticipantpositionmessage.marketmakermode"] = canonical::text(canonical::character((*message).market_maker_mode()), ' ', false);
            values[entry + ".payload.marketparticipantpositionmessage.marketparticipantstate"] = canonical::text(canonical::character((*message).market_participant_state()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::MwcbDeclineLevelMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.mwcbdeclinelevelmessage";
            values[entry + ".payload.mwcbdeclinelevelmessage.stocklocate"] = canonical::number((*message).stock_locate());
            values[entry + ".payload.mwcbdeclinelevelmessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.mwcbdeclinelevelmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.mwcbdeclinelevelmessage.level1"] = canonical::scaled((*message).level_1().mantissa(), (*message).level_1().exponent());
            values[entry + ".payload.mwcbdeclinelevelmessage.level2"] = canonical::scaled((*message).level_2().mantissa(), (*message).level_2().exponent());
            values[entry + ".payload.mwcbdeclinelevelmessage.level3"] = canonical::scaled((*message).level_3().mantissa(), (*message).level_3().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::MwcbStatusLevelMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.mwcbstatuslevelmessage";
            values[entry + ".payload.mwcbstatuslevelmessage.stocklocate"] = canonical::number((*message).stock_locate());
            values[entry + ".payload.mwcbstatuslevelmessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.mwcbstatuslevelmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.mwcbstatuslevelmessage.breachedlevel"] = canonical::text(canonical::character((*message).breached_level()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::LuldAuctionCollarMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.luldauctioncollarmessage";
            values[entry + ".payload.luldauctioncollarmessage.stocklocate"] = canonical::number((*message).stock_locate());
            values[entry + ".payload.luldauctioncollarmessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.luldauctioncollarmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.luldauctioncollarmessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.luldauctioncollarmessage.auctioncollarreferenceprice"] = canonical::scaled((*message).auction_collar_reference_price().mantissa(), (*message).auction_collar_reference_price().exponent());
            values[entry + ".payload.luldauctioncollarmessage.upperauctioncollarprice"] = canonical::scaled((*message).upper_auction_collar_price().mantissa(), (*message).upper_auction_collar_price().exponent());
            values[entry + ".payload.luldauctioncollarmessage.lowerauctioncollarprice"] = canonical::scaled((*message).lower_auction_collar_price().mantissa(), (*message).lower_auction_collar_price().exponent());
            values[entry + ".payload.luldauctioncollarmessage.auctioncollarextension"] = canonical::number((*message).auction_collar_extension());
        } else if (const auto* message = dynamic_cast<const protocol::OperationalHaltMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.operationalhaltmessage";
            values[entry + ".payload.operationalhaltmessage.stocklocate"] = canonical::number((*message).stock_locate());
            values[entry + ".payload.operationalhaltmessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.operationalhaltmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.operationalhaltmessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.operationalhaltmessage.marketcode"] = canonical::text(canonical::character((*message).market_code()), ' ', false);
            values[entry + ".payload.operationalhaltmessage.operationalhaltaction"] = canonical::text(canonical::character((*message).operational_halt_action()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderNoMpidAttributionMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.addordernompidattributionmessage";
            values[entry + ".payload.addordernompidattributionmessage.stocklocate"] = canonical::number((*message).stock_locate());
            values[entry + ".payload.addordernompidattributionmessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.addordernompidattributionmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.addordernompidattributionmessage.orderreferencenumber"] = canonical::number((*message).order_reference_number());
            values[entry + ".payload.addordernompidattributionmessage.buysellindicator"] = canonical::text(canonical::character((*message).buy_sell_indicator()), ' ', false);
            values[entry + ".payload.addordernompidattributionmessage.shares"] = canonical::number((*message).shares());
            values[entry + ".payload.addordernompidattributionmessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.addordernompidattributionmessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderWithMpidAttributionMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.addorderwithmpidattributionmessage";
            values[entry + ".payload.addorderwithmpidattributionmessage.stocklocate"] = canonical::number((*message).stock_locate());
            values[entry + ".payload.addorderwithmpidattributionmessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.addorderwithmpidattributionmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.addorderwithmpidattributionmessage.orderreferencenumber"] = canonical::number((*message).order_reference_number());
            values[entry + ".payload.addorderwithmpidattributionmessage.buysellindicator"] = canonical::text(canonical::character((*message).buy_sell_indicator()), ' ', false);
            values[entry + ".payload.addorderwithmpidattributionmessage.shares"] = canonical::number((*message).shares());
            values[entry + ".payload.addorderwithmpidattributionmessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.addorderwithmpidattributionmessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
            values[entry + ".payload.addorderwithmpidattributionmessage.attribution"] = canonical::text(std::string((*message).attribution()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedmessage";
            values[entry + ".payload.orderexecutedmessage.stocklocate"] = canonical::number((*message).stock_locate());
            values[entry + ".payload.orderexecutedmessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.orderexecutedmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.orderexecutedmessage.orderreferencenumber"] = canonical::number((*message).order_reference_number());
            values[entry + ".payload.orderexecutedmessage.executedshares"] = canonical::number((*message).executed_shares());
            values[entry + ".payload.orderexecutedmessage.matchnumber"] = canonical::number((*message).match_number());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedWithPriceMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedwithpricemessage";
            values[entry + ".payload.orderexecutedwithpricemessage.stocklocate"] = canonical::number((*message).stock_locate());
            values[entry + ".payload.orderexecutedwithpricemessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.orderexecutedwithpricemessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.orderexecutedwithpricemessage.orderreferencenumber"] = canonical::number((*message).order_reference_number());
            values[entry + ".payload.orderexecutedwithpricemessage.executedshares"] = canonical::number((*message).executed_shares());
            values[entry + ".payload.orderexecutedwithpricemessage.matchnumber"] = canonical::number((*message).match_number());
            values[entry + ".payload.orderexecutedwithpricemessage.printable"] = canonical::text(canonical::character((*message).printable()), ' ', false);
            values[entry + ".payload.orderexecutedwithpricemessage.executionprice"] = canonical::scaled((*message).execution_price().mantissa(), (*message).execution_price().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::OrderCancelMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.ordercancelmessage";
            values[entry + ".payload.ordercancelmessage.stocklocate"] = canonical::number((*message).stock_locate());
            values[entry + ".payload.ordercancelmessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.ordercancelmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.ordercancelmessage.orderreferencenumber"] = canonical::number((*message).order_reference_number());
            values[entry + ".payload.ordercancelmessage.cancelledshares"] = canonical::number((*message).cancelled_shares());
        } else if (const auto* message = dynamic_cast<const protocol::OrderDeleteMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderdeletemessage";
            values[entry + ".payload.orderdeletemessage.stocklocate"] = canonical::number((*message).stock_locate());
            values[entry + ".payload.orderdeletemessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.orderdeletemessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.orderdeletemessage.orderreferencenumber"] = canonical::number((*message).order_reference_number());
        } else if (const auto* message = dynamic_cast<const protocol::OrderReplaceMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderreplacemessage";
            values[entry + ".payload.orderreplacemessage.stocklocate"] = canonical::number((*message).stock_locate());
            values[entry + ".payload.orderreplacemessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.orderreplacemessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.orderreplacemessage.originalorderreferencenumber"] = canonical::number((*message).original_order_reference_number());
            values[entry + ".payload.orderreplacemessage.neworderreferencenumber"] = canonical::number((*message).new_order_reference_number());
            values[entry + ".payload.orderreplacemessage.shares"] = canonical::number((*message).shares());
            values[entry + ".payload.orderreplacemessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::TradeMessageNonCross*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.trademessagenoncross";
            values[entry + ".payload.trademessagenoncross.stocklocate"] = canonical::number((*message).stock_locate());
            values[entry + ".payload.trademessagenoncross.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.trademessagenoncross.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.trademessagenoncross.orderreferencenumber"] = canonical::number((*message).order_reference_number());
            values[entry + ".payload.trademessagenoncross.buysellindicator"] = canonical::text(canonical::character((*message).buy_sell_indicator()), ' ', false);
            values[entry + ".payload.trademessagenoncross.shares"] = canonical::number((*message).shares());
            values[entry + ".payload.trademessagenoncross.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.trademessagenoncross.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
            values[entry + ".payload.trademessagenoncross.matchnumber"] = canonical::number((*message).match_number());
        } else if (const auto* message = dynamic_cast<const protocol::CrossTradeMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.crosstrademessage";
            values[entry + ".payload.crosstrademessage.stocklocate"] = canonical::number((*message).stock_locate());
            values[entry + ".payload.crosstrademessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.crosstrademessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.crosstrademessage.crossshares"] = canonical::number((*message).cross_shares());
            values[entry + ".payload.crosstrademessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.crosstrademessage.crossprice"] = canonical::scaled((*message).cross_price().mantissa(), (*message).cross_price().exponent());
            values[entry + ".payload.crosstrademessage.matchnumber"] = canonical::number((*message).match_number());
            values[entry + ".payload.crosstrademessage.crosstype"] = canonical::text(canonical::character((*message).cross_type()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::BrokenTradeMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.brokentrademessage";
            values[entry + ".payload.brokentrademessage.stocklocate"] = canonical::number((*message).stock_locate());
            values[entry + ".payload.brokentrademessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.brokentrademessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.brokentrademessage.matchnumber"] = canonical::number((*message).match_number());
        } else if (const auto* message = dynamic_cast<const protocol::NetOrderImbalanceIndicatorMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.netorderimbalanceindicatormessage";
            values[entry + ".payload.netorderimbalanceindicatormessage.stocklocate"] = canonical::number((*message).stock_locate());
            values[entry + ".payload.netorderimbalanceindicatormessage.trackingnumber"] = canonical::number((*message).tracking_number());
            values[entry + ".payload.netorderimbalanceindicatormessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.netorderimbalanceindicatormessage.pairedshares"] = canonical::number((*message).paired_shares());
            values[entry + ".payload.netorderimbalanceindicatormessage.imbalanceshares"] = canonical::number((*message).imbalance_shares());
            values[entry + ".payload.netorderimbalanceindicatormessage.imbalancedirection"] = canonical::text(canonical::character((*message).imbalance_direction()), ' ', false);
            values[entry + ".payload.netorderimbalanceindicatormessage.stock"] = canonical::text(std::string((*message).stock()), ' ', false);
            values[entry + ".payload.netorderimbalanceindicatormessage.farprice"] = canonical::scaled((*message).far_price().mantissa(), (*message).far_price().exponent());
            values[entry + ".payload.netorderimbalanceindicatormessage.nearprice"] = canonical::scaled((*message).near_price().mantissa(), (*message).near_price().exponent());
            values[entry + ".payload.netorderimbalanceindicatormessage.currentreferenceprice"] = canonical::scaled((*message).current_reference_price().mantissa(), (*message).current_reference_price().exponent());
            values[entry + ".payload.netorderimbalanceindicatormessage.crosstype"] = canonical::text(canonical::character((*message).cross_type()), ' ', false);
            values[entry + ".payload.netorderimbalanceindicatormessage.pricevariationindicator"] = canonical::text(canonical::character((*message).price_variation_indicator()), ' ', false);
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
    std::printf("== Nasdaq.PsxEquities.TotalView.Itch.v5.0 (classes values)\n");
    int failures = 0;
    failures += check("AddOrderNoMpidAttributionMessage", "Nasdaq/PsxEquities.TotalView.Itch.v5.0/AddOrderNoMpidAttributionMessage.pcap", "nasdaq/psxequities/totalview/itch/v5.0/AddOrderNoMpidAttributionMessage.values");
    failures += check("AddOrderWithMpidAttributionMessage", "Nasdaq/PsxEquities.TotalView.Itch.v5.0/AddOrderWithMpidAttributionMessage.pcap", "nasdaq/psxequities/totalview/itch/v5.0/AddOrderWithMpidAttributionMessage.values");
    failures += check("OrderCancelMessage", "Nasdaq/PsxEquities.TotalView.Itch.v5.0/OrderCancelMessage.pcap", "nasdaq/psxequities/totalview/itch/v5.0/OrderCancelMessage.values");
    failures += check("OrderDeleteMessage", "Nasdaq/PsxEquities.TotalView.Itch.v5.0/OrderDeleteMessage.pcap", "nasdaq/psxequities/totalview/itch/v5.0/OrderDeleteMessage.values");
    failures += check("OrderExecutedMessage", "Nasdaq/PsxEquities.TotalView.Itch.v5.0/OrderExecutedMessage.pcap", "nasdaq/psxequities/totalview/itch/v5.0/OrderExecutedMessage.values");
    failures += check("OrderExecutedWithPriceMessage", "Nasdaq/PsxEquities.TotalView.Itch.v5.0/OrderExecutedWithPriceMessage.pcap", "nasdaq/psxequities/totalview/itch/v5.0/OrderExecutedWithPriceMessage.values");
    failures += check("OrderReplaceMessage", "Nasdaq/PsxEquities.TotalView.Itch.v5.0/OrderReplaceMessage.pcap", "nasdaq/psxequities/totalview/itch/v5.0/OrderReplaceMessage.values");
    failures += check("RegShoShortSalePriceTestRestrictedIndicatorMessage", "Nasdaq/PsxEquities.TotalView.Itch.v5.0/RegShoShortSalePriceTestRestrictedIndicatorMessage.pcap", "nasdaq/psxequities/totalview/itch/v5.0/RegShoShortSalePriceTestRestrictedIndicatorMessage.values");
    failures += check("StockTradingActionMessage", "Nasdaq/PsxEquities.TotalView.Itch.v5.0/StockTradingActionMessage.pcap", "nasdaq/psxequities/totalview/itch/v5.0/StockTradingActionMessage.values");
    failures += check("SystemEventMessage", "Nasdaq/PsxEquities.TotalView.Itch.v5.0/SystemEventMessage.pcap", "nasdaq/psxequities/totalview/itch/v5.0/SystemEventMessage.values");
    failures += check("TradeMessageNonCross", "Nasdaq/PsxEquities.TotalView.Itch.v5.0/TradeMessageNonCross.pcap", "nasdaq/psxequities/totalview/itch/v5.0/TradeMessageNonCross.values");
    return failures == 0 ? 0 : 1;
}
