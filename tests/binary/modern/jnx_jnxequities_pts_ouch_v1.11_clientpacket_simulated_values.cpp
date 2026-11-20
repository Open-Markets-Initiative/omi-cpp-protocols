// Jnx.JnxEquities.Pts.Ouch.v1.11 canonical values of 'clientpacket', through the Modern iterator: every value
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

// The values the Modern iterator reads from one stream of 'clientpacket', by indexed address
canonical::Listing read(const std::byte* data, std::size_t length) {
    canonical::Listing values;
    protocol::ClientSoupBinTcpPacketIterator iterator;
    iterator.initialize(data, length);

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "clientpacket.clientsoupbintcppacket[" + std::to_string(index++) + "]";

        // the iterator steps past a record the bytes end inside; its values are not read
        if (iterator.current > iterator.end) {
            values[entry] = "(ends inside the record)";
            break;
        }

        values[entry + ".clientpacketheader.packetlength"] = canonical::number(iterator.client_packet_header->packet_length.get());
        values[entry + ".clientpacketheader.clientpackettype"] = canonical::text(canonical::character(iterator.client_packet_header->client_packet_type.get()));

        if (iterator.client_packet_type == '+') {
            values[entry + ".clientpayload"] = "clientpacket.clientsoupbintcppacket.clientpayload.debugpacket";
            [[maybe_unused]] const auto* message = protocol::DebugPacket::parse(iterator.message);
        } else if (iterator.client_packet_type == protocol::LoginRequestPacket::message_type) {
            values[entry + ".clientpayload"] = "clientpacket.clientsoupbintcppacket.clientpayload.loginrequestpacket";
            [[maybe_unused]] const auto* message = protocol::LoginRequestPacket::parse(iterator.message);
            values[entry + ".clientpayload.loginrequestpacket.username"] = canonical::text(std::string(message->username.get()), ' ', false);
            values[entry + ".clientpayload.loginrequestpacket.password"] = canonical::text(std::string(message->password.get()), ' ', false);
            values[entry + ".clientpayload.loginrequestpacket.requestedsession"] = canonical::text(std::string(message->requested_session.get()), ' ', true);
            values[entry + ".clientpayload.loginrequestpacket.requestedsequencenumber"] = canonical::numeric(std::string(message->requested_sequence_number.get()));
        } else if (iterator.client_packet_type == 'U') {
            values[entry + ".clientpayload"] = "clientpacket.clientsoupbintcppacket.clientpayload.unsequenceddatapacket";
            [[maybe_unused]] const auto* message = protocol::UnsequencedDataPacket::parse(iterator.message);
            values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessagetype"] = canonical::text(canonical::character(message->unsequenced_message_type.get()));
            if (message->unsequenced_message_type.get() == protocol::EnterOrderMessage::message_type) {
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage"] = "clientpacket.clientsoupbintcppacket.clientpayload.unsequenceddatapacket.unsequencedmessage.enterordermessage";
                [[maybe_unused]] const auto* message_2 = protocol::EnterOrderMessage::parse(iterator.message + sizeof(protocol::UnsequencedDataPacket));
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage.enterordermessage.ordertoken"] = canonical::number(message_2->order_token.get());
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage.enterordermessage.clientreference"] = canonical::text(std::string(message_2->client_reference.get()), ' ', false);
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage.enterordermessage.buysellindicator"] = canonical::text(canonical::character(message_2->buy_sell_indicator.get()), ' ', false);
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage.enterordermessage.quantity"] = canonical::number(message_2->quantity.get());
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage.enterordermessage.orderbookid"] = canonical::number(message_2->orderbook_id.get());
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage.enterordermessage.group"] = canonical::text(std::string(message_2->group.get()), ' ', false);
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage.enterordermessage.price"] = canonical::scaled(message_2->price.integer(), -1);
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage.enterordermessage.timeinforce"] = canonical::number(message_2->time_in_force.get());
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage.enterordermessage.firmid"] = canonical::number(message_2->firm_id.get());
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage.enterordermessage.display"] = canonical::text(canonical::character(message_2->display.get()), ' ', false, {std::string_view(" ", 1), std::string_view("", 0)});
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage.enterordermessage.capacity"] = canonical::text(canonical::character(message_2->capacity.get()), ' ', false);
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage.enterordermessage.minimumquantity"] = canonical::number(message_2->minimum_quantity.get());
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage.enterordermessage.orderclassification"] = canonical::text(canonical::character(message_2->order_classification.get()), ' ', false);
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage.enterordermessage.cashmargintype"] = canonical::text(canonical::character(message_2->cash_margin_type.get()), ' ', false);
            } else if (message->unsequenced_message_type.get() == protocol::ReplaceOrderMessage::message_type) {
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage"] = "clientpacket.clientsoupbintcppacket.clientpayload.unsequenceddatapacket.unsequencedmessage.replaceordermessage";
                [[maybe_unused]] const auto* message_2 = protocol::ReplaceOrderMessage::parse(iterator.message + sizeof(protocol::UnsequencedDataPacket));
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage.replaceordermessage.existingordertoken"] = canonical::number(message_2->existing_order_token.get());
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage.replaceordermessage.replacementordertoken"] = canonical::number(message_2->replacement_order_token.get());
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage.replaceordermessage.quantity"] = canonical::number(message_2->quantity.get());
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage.replaceordermessage.price"] = canonical::scaled(message_2->price.integer(), -1);
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage.replaceordermessage.timeinforce"] = canonical::number(message_2->time_in_force.get());
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage.replaceordermessage.display"] = canonical::text(canonical::character(message_2->display.get()), ' ', false, {std::string_view(" ", 1), std::string_view("", 0)});
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage.replaceordermessage.minimumquantity"] = canonical::number(message_2->minimum_quantity.get());
            } else if (message->unsequenced_message_type.get() == protocol::CancelOrderMessage::message_type) {
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage"] = "clientpacket.clientsoupbintcppacket.clientpayload.unsequenceddatapacket.unsequencedmessage.cancelordermessage";
                [[maybe_unused]] const auto* message_2 = protocol::CancelOrderMessage::parse(iterator.message + sizeof(protocol::UnsequencedDataPacket));
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage.cancelordermessage.ordertoken"] = canonical::number(message_2->order_token.get());
                values[entry + ".clientpayload.unsequenceddatapacket.unsequencedmessage.cancelordermessage.quantity"] = canonical::number(message_2->quantity.get());
            }
        }
    }

    return values;
}

// Reassemble each side of a sample's connections, read each side the client sends with Modern and hold it to the model's values
int check(const char* name, const char* capture, const char* expected) {
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

        reassembler.process(frame);
    }

    std::size_t stream = 0;
    std::size_t read_values = 0;
    int differences = 0;

    for (const auto& key : order) {
        [[maybe_unused]] const bool from_client = dialled && key.src_ip == client_ip && key.src_port == client_port;
        [[maybe_unused]] const bool to_client = dialled && key.dst_ip == client_ip && key.dst_port == client_port;

        if (!(from_client)) { continue; }

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
    std::printf("== Jnx.JnxEquities.Pts.Ouch.v1.11 (modern 'clientpacket' values)\n");
    int failures = 0;
    failures += check("Simulated", "tests/simulated/jnx/jnxequities/pts/ouch/v1.11.pcap", "jnx/jnxequities/pts/ouch/v1.11/clientpacket/Simulated.values");
    return failures == 0 ? 0 : 1;
}
