// Jnx.JnxEquities.Pts.Ouch.v1.11 canonical values of 'serverpacket', through the Modern iterator: every value
// Modern reads from each side of each connection the tree is sent from, at its address, held to what the model reads.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "TcpReassembler.hpp"
#include "tests/canonical/Canonical.hpp"
#include "cpp/binary/modern/jnx/jnxequities/pts/ouch/v1.11/definitions.hpp"

namespace protocol = ::jnx::jnxequities::pts::ouch::v1_11;

namespace {

// The values the Modern iterator reads from one stream of 'serverpacket', by indexed address
canonical::Listing read(const std::byte* data, std::size_t length) {
    canonical::Listing values;
    protocol::ServerSoupBinTcpPacketIterator iterator;
    iterator.initialize(data, length);

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "serverpacket.serversoupbintcppacket[" + std::to_string(index++) + "]";

        // the iterator steps past a record the bytes end inside; its values are not read
        if (iterator.current > iterator.end) {
            values[entry] = "(ends inside the record)";
            break;
        }

        values[entry + ".serverpacketheader.packetlength"] = canonical::number(iterator.server_packet_header->packet_length.get());
        values[entry + ".serverpacketheader.serverpackettype"] = canonical::text(canonical::character(iterator.server_packet_header->server_packet_type.get()));

        if (iterator.server_packet_type == '+') {
            values[entry + ".serverpayload"] = "serverpacket.serversoupbintcppacket.serverpayload.debugpacket";
            [[maybe_unused]] const auto* message = protocol::DebugPacket::parse(iterator.message);
        } else if (iterator.server_packet_type == 'A') {
            values[entry + ".serverpayload"] = "serverpacket.serversoupbintcppacket.serverpayload.loginacceptedpacket";
            [[maybe_unused]] const auto* message = protocol::LoginAcceptedPacket::parse(iterator.message);
            values[entry + ".serverpayload.loginacceptedpacket.acceptedsession"] = canonical::text(std::string(message->accepted_session.get()), ' ', true);
            values[entry + ".serverpayload.loginacceptedpacket.acceptedsequencenumber"] = canonical::numeric(std::string(message->accepted_sequence_number.get()));
        } else if (iterator.server_packet_type == 'J') {
            values[entry + ".serverpayload"] = "serverpacket.serversoupbintcppacket.serverpayload.loginrejectedpacket";
            [[maybe_unused]] const auto* message = protocol::LoginRejectedPacket::parse(iterator.message);
            values[entry + ".serverpayload.loginrejectedpacket.rejectreasoncode"] = canonical::text(canonical::character(message->reject_reason_code.get()));
        } else if (iterator.server_packet_type == 'S') {
            values[entry + ".serverpayload"] = "serverpacket.serversoupbintcppacket.serverpayload.sequenceddatapacket";
            [[maybe_unused]] const auto* message = protocol::SequencedDataPacket::parse(iterator.message);
            values[entry + ".serverpayload.sequenceddatapacket.sequencedmessagetype"] = canonical::text(canonical::character(message->sequenced_message_type.get()));
            if (message->sequenced_message_type.get() == protocol::SystemEventMessage::message_type) {
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage"] = "serverpacket.serversoupbintcppacket.serverpayload.sequenceddatapacket.sequencedmessage.systemeventmessage";
                [[maybe_unused]] const auto* message_2 = protocol::SystemEventMessage::parse(iterator.message + sizeof(protocol::SequencedDataPacket));
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.systemeventmessage.timestamp"] = canonical::number(message_2->timestamp.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.systemeventmessage.systemevent"] = canonical::text(canonical::character(message_2->system_event.get()), ' ', false);
            } else if (message->sequenced_message_type.get() == protocol::OrderAcceptedMessage::message_type) {
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage"] = "serverpacket.serversoupbintcppacket.serverpayload.sequenceddatapacket.sequencedmessage.orderacceptedmessage";
                [[maybe_unused]] const auto* message_2 = protocol::OrderAcceptedMessage::parse(iterator.message + sizeof(protocol::SequencedDataPacket));
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderacceptedmessage.timestamp"] = canonical::number(message_2->timestamp.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderacceptedmessage.ordertoken"] = canonical::number(message_2->order_token.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderacceptedmessage.clientreference"] = canonical::text(std::string(message_2->client_reference.get()), ' ', false);
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderacceptedmessage.buysellindicator"] = canonical::text(canonical::character(message_2->buy_sell_indicator.get()), ' ', false);
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderacceptedmessage.quantity"] = canonical::number(message_2->quantity.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderacceptedmessage.orderbookid"] = canonical::number(message_2->orderbook_id.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderacceptedmessage.group"] = canonical::text(std::string(message_2->group.get()), ' ', false);
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderacceptedmessage.price"] = canonical::scaled(message_2->price.integer(), -1);
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderacceptedmessage.timeinforce"] = canonical::number(message_2->time_in_force.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderacceptedmessage.firmid"] = canonical::number(message_2->firm_id.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderacceptedmessage.display"] = canonical::text(canonical::character(message_2->display.get()), ' ', false, {std::string_view(" ", 1), std::string_view("", 0)});
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderacceptedmessage.capacity"] = canonical::text(canonical::character(message_2->capacity.get()), ' ', false);
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderacceptedmessage.ordernumber"] = canonical::number(message_2->order_number.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderacceptedmessage.minimumquantity"] = canonical::number(message_2->minimum_quantity.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderacceptedmessage.orderstate"] = canonical::text(canonical::character(message_2->order_state.get()), ' ', false);
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderacceptedmessage.orderclassification"] = canonical::text(canonical::character(message_2->order_classification.get()), ' ', false);
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderacceptedmessage.cashmargintype"] = canonical::text(canonical::character(message_2->cash_margin_type.get()), ' ', false);
            } else if (message->sequenced_message_type.get() == protocol::OrderReplacedMessage::message_type) {
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage"] = "serverpacket.serversoupbintcppacket.serverpayload.sequenceddatapacket.sequencedmessage.orderreplacedmessage";
                [[maybe_unused]] const auto* message_2 = protocol::OrderReplacedMessage::parse(iterator.message + sizeof(protocol::SequencedDataPacket));
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderreplacedmessage.timestamp"] = canonical::number(message_2->timestamp.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderreplacedmessage.replacementordertoken"] = canonical::number(message_2->replacement_order_token.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderreplacedmessage.buysellindicator"] = canonical::text(canonical::character(message_2->buy_sell_indicator.get()), ' ', false);
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderreplacedmessage.quantity"] = canonical::number(message_2->quantity.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderreplacedmessage.orderbookid"] = canonical::number(message_2->orderbook_id.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderreplacedmessage.group"] = canonical::text(std::string(message_2->group.get()), ' ', false);
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderreplacedmessage.price"] = canonical::scaled(message_2->price.integer(), -1);
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderreplacedmessage.timeinforce"] = canonical::number(message_2->time_in_force.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderreplacedmessage.display"] = canonical::text(canonical::character(message_2->display.get()), ' ', false, {std::string_view(" ", 1), std::string_view("", 0)});
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderreplacedmessage.ordernumber"] = canonical::number(message_2->order_number.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderreplacedmessage.minimumquantity"] = canonical::number(message_2->minimum_quantity.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderreplacedmessage.orderstate"] = canonical::text(canonical::character(message_2->order_state.get()), ' ', false);
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderreplacedmessage.previousordertoken"] = canonical::number(message_2->previous_order_token.get());
            } else if (message->sequenced_message_type.get() == protocol::OrderCanceledMessage::message_type) {
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage"] = "serverpacket.serversoupbintcppacket.serverpayload.sequenceddatapacket.sequencedmessage.ordercanceledmessage";
                [[maybe_unused]] const auto* message_2 = protocol::OrderCanceledMessage::parse(iterator.message + sizeof(protocol::SequencedDataPacket));
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.ordercanceledmessage.timestamp"] = canonical::number(message_2->timestamp.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.ordercanceledmessage.ordertoken"] = canonical::number(message_2->order_token.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.ordercanceledmessage.decrementquantity"] = canonical::number(message_2->decrement_quantity.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.ordercanceledmessage.ordercanceledreason"] = canonical::text(canonical::character(message_2->order_canceled_reason.get()), ' ', false);
            } else if (message->sequenced_message_type.get() == protocol::OrderAiqCanceledMessage::message_type) {
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage"] = "serverpacket.serversoupbintcppacket.serverpayload.sequenceddatapacket.sequencedmessage.orderaiqcanceledmessage";
                [[maybe_unused]] const auto* message_2 = protocol::OrderAiqCanceledMessage::parse(iterator.message + sizeof(protocol::SequencedDataPacket));
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderaiqcanceledmessage.timestamp"] = canonical::number(message_2->timestamp.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderaiqcanceledmessage.ordertoken"] = canonical::number(message_2->order_token.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderaiqcanceledmessage.decrementquantity"] = canonical::number(message_2->decrement_quantity.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderaiqcanceledmessage.ordercanceledreason"] = canonical::text(canonical::character(message_2->order_canceled_reason.get()), ' ', false);
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderaiqcanceledmessage.quantitypreventedfromtrading"] = canonical::number(message_2->quantity_prevented_from_trading.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderaiqcanceledmessage.executionprice"] = canonical::scaled(message_2->execution_price.integer(), -1);
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderaiqcanceledmessage.liquidityindicator"] = canonical::text(canonical::character(message_2->liquidity_indicator.get()), ' ', false);
            } else if (message->sequenced_message_type.get() == protocol::OrderExecutedMessage::message_type) {
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage"] = "serverpacket.serversoupbintcppacket.serverpayload.sequenceddatapacket.sequencedmessage.orderexecutedmessage";
                [[maybe_unused]] const auto* message_2 = protocol::OrderExecutedMessage::parse(iterator.message + sizeof(protocol::SequencedDataPacket));
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderexecutedmessage.timestamp"] = canonical::number(message_2->timestamp.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderexecutedmessage.ordertoken"] = canonical::number(message_2->order_token.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderexecutedmessage.executedquantity"] = canonical::number(message_2->executed_quantity.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderexecutedmessage.executionprice"] = canonical::scaled(message_2->execution_price.integer(), -1);
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderexecutedmessage.liquidityindicator"] = canonical::text(canonical::character(message_2->liquidity_indicator.get()), ' ', false);
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderexecutedmessage.matchnumber"] = canonical::number(message_2->match_number.get());
            } else if (message->sequenced_message_type.get() == protocol::OrderRejectedMessage::message_type) {
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage"] = "serverpacket.serversoupbintcppacket.serverpayload.sequenceddatapacket.sequencedmessage.orderrejectedmessage";
                [[maybe_unused]] const auto* message_2 = protocol::OrderRejectedMessage::parse(iterator.message + sizeof(protocol::SequencedDataPacket));
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderrejectedmessage.timestamp"] = canonical::number(message_2->timestamp.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderrejectedmessage.ordertoken"] = canonical::number(message_2->order_token.get());
                values[entry + ".serverpayload.sequenceddatapacket.sequencedmessage.orderrejectedmessage.orderrejectedreason"] = canonical::text(canonical::character(message_2->order_rejected_reason.get()), ' ', false);
            }
        }
    }

    return values;
}

// Reassemble each side of a sample's connections, read each side the server sends with Modern and hold it to the model's values
int check(const char* name, const char* capture, const char* expected, const char* origin) {
    const char* packets = std::getenv("OMI_PACKETS_DIR");

    if (packets == nullptr) {
        std::printf("FAIL: OMI_PACKETS_DIR is not set\n");
        return 1;
    }

    const auto model = canonical::load(canonical::root() + "/" + expected);

    std::vector<packet::TcpFlowKey> order;
    std::unordered_map<packet::TcpFlowKey, std::vector<std::byte>, packet::TcpFlowKey::hash> sides;
    packet::TcpReassembler reassembler;
    bool dialled = false;
    std::uint32_t client_ip = 0;
    std::uint16_t client_port = 0;

    reassembler.on_data = [&](const packet::TcpFlowKey& key, const std::byte* data, std::size_t length) {
        auto& side = sides[key];
        side.insert(side.end(), data, data + length);
    };

    bool carried = false;
    packet::TcpFlowKey first{};

    std::vector<std::pair<std::string, std::int64_t>> sources;
    sources.emplace_back(std::string{packets} + "/" + capture, 0);
    packet::PcapIterator captures(sources);

    while (captures.advance()) {
        const packet::Frame frame(captures.data(), captures.length());

        if (!frame.valid() || !frame.is_tcp()) { continue; }

        const packet::TcpFlowKey key{ frame.src_ip, frame.dst_ip, frame.src_port, frame.dst_port };

        if (sides.find(key) == sides.end()) {
            sides[key];
            order.push_back(key);
        }

        if (!dialled && (frame.tcp_flags & 0x02) != 0 && (frame.tcp_flags & 0x10) == 0) {
            dialled = true;
            client_ip = frame.src_ip;
            client_port = frame.src_port;
        }

        if (!carried && frame.payload_len > 0) {
            carried = true;
            first = key;
        }

        reassembler.process(frame);
    }

    const std::string stated{origin};

    if (carried && (stated == "Client" || stated == "Server")) {
        const std::uint32_t stated_ip = stated == "Client" ? first.src_ip : first.dst_ip;
        const std::uint16_t stated_port = stated == "Client" ? first.src_port : first.dst_port;

        if (!dialled) {
            dialled = true;
            client_ip = stated_ip;
            client_port = stated_port;
        } else if (client_ip != stated_ip || client_port != stated_port) {
            std::printf("note %s: its handshake tells the sides apart against its manifest's Origin=\"%s\"; the handshake is taken\n", name, origin);
        }
    } else if (!stated.empty()) {
        std::printf("FAIL %s: Origin=\"%s\" names no side of a connection, or no segment carries a payload\n", name, origin);
        return 1;
    }

    std::size_t stream = 0;
    std::size_t read_values = 0;
    int differences = 0;

    for (const auto& key : order) {
        [[maybe_unused]] const bool from_client = dialled && key.src_ip == client_ip && key.src_port == client_port;
        [[maybe_unused]] const bool to_client = dialled && key.dst_ip == client_ip && key.dst_port == client_port;

        if (!(to_client)) { continue; }

        if (stream >= model.size()) {
            std::printf("FAIL %s: more streams than the model read\n", name);
            return 1;
        }

        const auto& bytes = sides[key];
        const auto values = read(bytes.data(), bytes.size());

        if (values.empty() && !model[stream].empty()) {
            std::printf("FAIL %s: no value read from stream %zu, %zu bytes\n", name, stream, bytes.size());
            return 1;
        }

        read_values += values.size();
        differences += canonical::compare(name, stream, model[stream], values);
        ++stream;
    }

    if (stream != model.size()) {
        std::printf("FAIL %s: %zu streams, the model read %zu\n", name, stream, model.size());
        return 1;
    }

    if (differences == 0) {
        std::printf("ok   %s: %zu values of %zu streams\n", name, read_values, stream);
    }

    return differences == 0 ? 0 : 1;
}

}

int main() {
    std::printf("== Jnx.JnxEquities.Pts.Ouch.v1.11 (modern 'serverpacket' values)\n");
    int failures = 0;
    failures += check("LoginAcceptedPacket", "Jnx/JnxEquities.Pts.Ouch.v1.11/LoginAcceptedPacket.pcap", "jnx/jnxequities/pts/ouch/v1.11/serverpacket/LoginAcceptedPacket.values", "Server");
    failures += check("OrderAcceptedMessage", "Jnx/JnxEquities.Pts.Ouch.v1.11/OrderAcceptedMessage.pcap", "jnx/jnxequities/pts/ouch/v1.11/serverpacket/OrderAcceptedMessage.values", "Server");
    failures += check("OrderCanceledMessage", "Jnx/JnxEquities.Pts.Ouch.v1.11/OrderCanceledMessage.pcap", "jnx/jnxequities/pts/ouch/v1.11/serverpacket/OrderCanceledMessage.values", "Server");
    failures += check("OrderExecutedMessage", "Jnx/JnxEquities.Pts.Ouch.v1.11/OrderExecutedMessage.pcap", "jnx/jnxequities/pts/ouch/v1.11/serverpacket/OrderExecutedMessage.values", "Server");
    failures += check("OrderRejectedMessage", "Jnx/JnxEquities.Pts.Ouch.v1.11/OrderRejectedMessage.pcap", "jnx/jnxequities/pts/ouch/v1.11/serverpacket/OrderRejectedMessage.values", "Server");
    return failures == 0 ? 0 : 1;
}
