// Cboe.BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29 canonical values, through the Advanced session layer: every value Advanced
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
#include "cpp/binary/advanced/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/messages/session.hpp"

namespace protocol = ::cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::packet_header& header, const packet::Frame&) {
        values["packet.packetheader.length"] = canonical::number(header.length.get().value());
        values["packet.packetheader.messagecount"] = canonical::number(header.message_count.get().value());
        values["packet.packetheader.unit"] = canonical::number(header.unit.get().value());
        values["packet.packetheader.sequence"] = canonical::number(header.sequence.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::packet_header&) {
        ++index;
    }

    void on_message(const protocol::time_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.timemessage";
        values[entry + ".payload.timemessage.time"] = canonical::number(message.fields.time.get().value());
    }

    void on_message(const protocol::unit_clear_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.unitclearmessage";
        values[entry + ".payload.unitclearmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
    }

    void on_message(const protocol::add_order_long_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.addorderlongmessage";
        values[entry + ".payload.addorderlongmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.addorderlongmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.addorderlongmessage.sideindicator"] = canonical::text(canonical::character(message.fields.side_indicator.get().value()), ' ', false);
        values[entry + ".payload.addorderlongmessage.quantity"] = canonical::number(message.fields.quantity.get().value());
        values[entry + ".payload.addorderlongmessage.symbolshort"] = canonical::text(std::string(message.fields.symbol_short.get().value()), ' ', false);
        values[entry + ".payload.addorderlongmessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".payload.addorderlongmessage.addorderflags.display"] = canonical::number(static_cast<std::uint64_t>(message.fields.add_order_flags.has_display()));
    }

    void on_message(const protocol::add_order_short_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.addordershortmessage";
        values[entry + ".payload.addordershortmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.addordershortmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.addordershortmessage.sideindicator"] = canonical::text(canonical::character(message.fields.side_indicator.get().value()), ' ', false);
        values[entry + ".payload.addordershortmessage.quantityshort"] = canonical::number(message.fields.quantity_short.get().value());
        values[entry + ".payload.addordershortmessage.symbolshort"] = canonical::text(std::string(message.fields.symbol_short.get().value()), ' ', false);
        values[entry + ".payload.addordershortmessage.priceshort"] = canonical::scaled(message.fields.price_short.get().value(), -2);
        values[entry + ".payload.addordershortmessage.addorderflags.display"] = canonical::number(static_cast<std::uint64_t>(message.fields.add_order_flags.has_display()));
    }

    void on_message(const protocol::add_order_expanded_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.addorderexpandedmessage";
        values[entry + ".payload.addorderexpandedmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.addorderexpandedmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.addorderexpandedmessage.sideindicator"] = canonical::text(canonical::character(message.fields.side_indicator.get().value()), ' ', false);
        values[entry + ".payload.addorderexpandedmessage.quantity"] = canonical::number(message.fields.quantity.get().value());
        values[entry + ".payload.addorderexpandedmessage.symbollong"] = canonical::text(std::string(message.fields.symbol_long.get().value()), ' ', false);
        values[entry + ".payload.addorderexpandedmessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".payload.addorderexpandedmessage.addorderflags.display"] = canonical::number(static_cast<std::uint64_t>(message.fields.add_order_flags.has_display()));
        values[entry + ".payload.addorderexpandedmessage.participantid"] = canonical::text(std::string(message.fields.participant_id.get().value()), ' ', false);
        values[entry + ".payload.addorderexpandedmessage.customerindicator"] = canonical::text(canonical::character(message.fields.customer_indicator.get().value()), ' ', false);
    }

    void on_message(const protocol::order_executed_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedmessage";
        values[entry + ".payload.orderexecutedmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.orderexecutedmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.orderexecutedmessage.executedquantity"] = canonical::number(message.fields.executed_quantity.get().value());
        values[entry + ".payload.orderexecutedmessage.executionid"] = canonical::number(message.fields.execution_id.get().value());
    }

    void on_message(const protocol::order_executed_at_price_size_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedatpricesizemessage";
        values[entry + ".payload.orderexecutedatpricesizemessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.orderexecutedatpricesizemessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.orderexecutedatpricesizemessage.executedquantity"] = canonical::number(message.fields.executed_quantity.get().value());
        values[entry + ".payload.orderexecutedatpricesizemessage.remainingquantity"] = canonical::number(message.fields.remaining_quantity.get().value());
        values[entry + ".payload.orderexecutedatpricesizemessage.executionid"] = canonical::number(message.fields.execution_id.get().value());
        values[entry + ".payload.orderexecutedatpricesizemessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
    }

    void on_message(const protocol::reduce_size_long_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.reducesizelongmessage";
        values[entry + ".payload.reducesizelongmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.reducesizelongmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.reducesizelongmessage.canceledquantity"] = canonical::number(message.fields.canceled_quantity.get().value());
    }

    void on_message(const protocol::reduce_size_short_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.reducesizeshortmessage";
        values[entry + ".payload.reducesizeshortmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.reducesizeshortmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.reducesizeshortmessage.canceledquantityshort"] = canonical::number(message.fields.canceled_quantity_short.get().value());
    }

    void on_message(const protocol::modify_order_long_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.modifyorderlongmessage";
        values[entry + ".payload.modifyorderlongmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.modifyorderlongmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.modifyorderlongmessage.quantity"] = canonical::number(message.fields.quantity.get().value());
        values[entry + ".payload.modifyorderlongmessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".payload.modifyorderlongmessage.modifyorderflags.display"] = canonical::number(static_cast<std::uint64_t>(message.fields.modify_order_flags.has_display()));
        values[entry + ".payload.modifyorderlongmessage.modifyorderflags.priority"] = canonical::number(static_cast<std::uint64_t>(message.fields.modify_order_flags.has_priority()));
    }

    void on_message(const protocol::modify_order_short_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.modifyordershortmessage";
        values[entry + ".payload.modifyordershortmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.modifyordershortmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.modifyordershortmessage.quantityshort"] = canonical::number(message.fields.quantity_short.get().value());
        values[entry + ".payload.modifyordershortmessage.priceshort"] = canonical::scaled(message.fields.price_short.get().value(), -2);
        values[entry + ".payload.modifyordershortmessage.modifyorderflags.display"] = canonical::number(static_cast<std::uint64_t>(message.fields.modify_order_flags.has_display()));
        values[entry + ".payload.modifyordershortmessage.modifyorderflags.priority"] = canonical::number(static_cast<std::uint64_t>(message.fields.modify_order_flags.has_priority()));
    }

    void on_message(const protocol::delete_order_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.deleteordermessage";
        values[entry + ".payload.deleteordermessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.deleteordermessage.orderid"] = canonical::number(message.fields.order_id.get().value());
    }

    void on_message(const protocol::trade_long_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.tradelongmessage";
        values[entry + ".payload.tradelongmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.tradelongmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.tradelongmessage.sideindicator"] = canonical::text(canonical::character(message.fields.side_indicator.get().value()), ' ', false);
        values[entry + ".payload.tradelongmessage.quantity"] = canonical::number(message.fields.quantity.get().value());
        values[entry + ".payload.tradelongmessage.symbolshort"] = canonical::text(std::string(message.fields.symbol_short.get().value()), ' ', false);
        values[entry + ".payload.tradelongmessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".payload.tradelongmessage.executionid"] = canonical::number(message.fields.execution_id.get().value());
    }

    void on_message(const protocol::trade_short_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.tradeshortmessage";
        values[entry + ".payload.tradeshortmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.tradeshortmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.tradeshortmessage.sideindicator"] = canonical::text(canonical::character(message.fields.side_indicator.get().value()), ' ', false);
        values[entry + ".payload.tradeshortmessage.quantityshort"] = canonical::number(message.fields.quantity_short.get().value());
        values[entry + ".payload.tradeshortmessage.symbolshort"] = canonical::text(std::string(message.fields.symbol_short.get().value()), ' ', false);
        values[entry + ".payload.tradeshortmessage.priceshort"] = canonical::scaled(message.fields.price_short.get().value(), -2);
        values[entry + ".payload.tradeshortmessage.executionid"] = canonical::number(message.fields.execution_id.get().value());
    }

    void on_message(const protocol::trade_expanded_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.tradeexpandedmessage";
        values[entry + ".payload.tradeexpandedmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.tradeexpandedmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.tradeexpandedmessage.sideindicator"] = canonical::text(canonical::character(message.fields.side_indicator.get().value()), ' ', false);
        values[entry + ".payload.tradeexpandedmessage.quantity"] = canonical::number(message.fields.quantity.get().value());
        values[entry + ".payload.tradeexpandedmessage.symbollong"] = canonical::text(std::string(message.fields.symbol_long.get().value()), ' ', false);
        values[entry + ".payload.tradeexpandedmessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".payload.tradeexpandedmessage.executionid"] = canonical::number(message.fields.execution_id.get().value());
    }

    void on_message(const protocol::trade_break_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.tradebreakmessage";
        values[entry + ".payload.tradebreakmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.tradebreakmessage.executionid"] = canonical::number(message.fields.execution_id.get().value());
    }

    void on_message(const protocol::end_of_session& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.endofsession";
        values[entry + ".payload.endofsession.lasttimestamp"] = canonical::number(message.fields.last_timestamp.get().value());
    }

    void on_message(const protocol::trading_status_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.tradingstatusmessage";
        values[entry + ".payload.tradingstatusmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.tradingstatusmessage.symbollong"] = canonical::text(std::string(message.fields.symbol_long.get().value()), ' ', false);
        values[entry + ".payload.tradingstatusmessage.tradingstatus"] = canonical::text(canonical::character(message.fields.trading_status.get().value()), ' ', false);
        values[entry + ".payload.tradingstatusmessage.regshoaction"] = canonical::text(canonical::character(message.fields.reg_sho_action.get().value()), ' ', false);
    }

    void on_message(const protocol::auction_update_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.auctionupdatemessage";
        values[entry + ".payload.auctionupdatemessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.auctionupdatemessage.symbollong"] = canonical::text(std::string(message.fields.symbol_long.get().value()), ' ', false);
        values[entry + ".payload.auctionupdatemessage.auctiontype"] = canonical::text(canonical::character(message.fields.auction_type.get().value()), ' ', false);
        values[entry + ".payload.auctionupdatemessage.referenceprice"] = canonical::number(message.fields.reference_price.get().value());
        values[entry + ".payload.auctionupdatemessage.buyshares"] = canonical::number(message.fields.buy_shares.get().value());
        values[entry + ".payload.auctionupdatemessage.sellshares"] = canonical::number(message.fields.sell_shares.get().value());
        values[entry + ".payload.auctionupdatemessage.indicativeprice"] = canonical::number(message.fields.indicative_price.get().value());
        values[entry + ".payload.auctionupdatemessage.auctiononlyprice"] = canonical::number(message.fields.auction_only_price.get().value());
    }

    void on_message(const protocol::auction_summary_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.auctionsummarymessage";
        values[entry + ".payload.auctionsummarymessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.auctionsummarymessage.symbollong"] = canonical::text(std::string(message.fields.symbol_long.get().value()), ' ', false);
        values[entry + ".payload.auctionsummarymessage.auctionopeningtype"] = canonical::text(canonical::character(message.fields.auction_opening_type.get().value()), ' ', false);
        values[entry + ".payload.auctionsummarymessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".payload.auctionsummarymessage.sharescontracts"] = canonical::number(message.fields.shares_contracts.get().value());
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
    std::printf("== Cboe.BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29 (advanced values)\n");
    int failures = 0;
    failures += check("AddOrderExpandedMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/AddOrderExpandedMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/AddOrderExpandedMessage.values");
    failures += check("AddOrderLongMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/AddOrderLongMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/AddOrderLongMessage.values");
    failures += check("AddOrderShortMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/AddOrderShortMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/AddOrderShortMessage.values");
    failures += check("AuctionSummaryMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/AuctionSummaryMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/AuctionSummaryMessage.values");
    failures += check("AuctionUpdateMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/AuctionUpdateMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/AuctionUpdateMessage.values");
    failures += check("DeleteOrderMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/DeleteOrderMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/DeleteOrderMessage.values");
    failures += check("ModifyOrderLongMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/ModifyOrderLongMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/ModifyOrderLongMessage.values");
    failures += check("ModifyOrderShortMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/ModifyOrderShortMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/ModifyOrderShortMessage.values");
    failures += check("OrderExecutedAtPriceSizeMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/OrderExecutedAtPriceSizeMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/OrderExecutedAtPriceSizeMessage.values");
    failures += check("OrderExecutedMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/OrderExecutedMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/OrderExecutedMessage.values");
    failures += check("ReduceSizeShortMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/ReduceSizeShortMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/ReduceSizeShortMessage.values");
    failures += check("TimeMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/TimeMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/TimeMessage.values");
    failures += check("TradeLongMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/TradeLongMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/TradeLongMessage.values");
    failures += check("TradeShortMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/TradeShortMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/TradeShortMessage.values");
    failures += check("TradingStatusMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29/TradingStatusMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/TradingStatusMessage.values");
    return failures == 0 ? 0 : 1;
}
