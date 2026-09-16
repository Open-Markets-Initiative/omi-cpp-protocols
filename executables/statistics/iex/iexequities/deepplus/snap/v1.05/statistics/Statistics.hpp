#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <unordered_map>
#include <vector>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "../pcap/TcpReassembler.hpp"
#include "cpp/modern/iex/iexequities/deepplus/snap/v1.05/definitions.hpp"

namespace statistics {

// Iex Snap C++ statistics
struct Statistics {

    iex::iexequities::deepplus::snap::v1_05::MessageIterator message;
    packet::TcpReassembler message_reassembler;
    std::unordered_map<packet::TcpFlowKey, std::vector<std::uint8_t>, packet::TcpFlowKey::hash> message_flows;
    packet::Parser& parser;
    const statistics::Options& options;

    // counters
    uint64_t total_packets = 0;
    uint64_t unknown_packets = 0;
    uint64_t total_messages = 0;
    uint64_t unknown_messages = 0;
    uint64_t heartbeats = 0;

    // message counters
    uint64_t snapshot_request_message = 0;
    uint64_t error_response_message = 0;
    uint64_t snapshot_start_message = 0;
    uint64_t snapshot_data_message = 0;
    uint64_t system_event_message = 0;
    uint64_t security_directory_message = 0;
    uint64_t trading_status_message = 0;
    uint64_t retail_liquidity_indicator_message = 0;
    uint64_t operational_halt_status_message = 0;
    uint64_t short_sale_price_test_status_message = 0;
    uint64_t security_event_message = 0;
    uint64_t add_order_message = 0;
    uint64_t order_modify_message = 0;
    uint64_t order_delete_message = 0;
    uint64_t order_executed_message = 0;
    uint64_t trade_message = 0;
    uint64_t trade_break_message = 0;
    uint64_t clear_book_message = 0;
    uint64_t snapshot_end_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {
        message_reassembler.on_data = [this](const packet::TcpFlowKey& key, const std::byte* data, std::size_t length) { message_flow(key, data, length); };
    }

    // process a frame: every tree carrying its transport reads it
    void udp() {
        const auto& frame = parser.frame();

        if (frame.is_tcp()) {
            message_reassembler.process(frame);
        }
    }

    // walk the Packet tree's reassembled bytes
    void message_flow(const packet::TcpFlowKey& key, const std::byte* data, std::size_t length) {
        auto& bytes = message_flows[key];
        bytes.insert(bytes.end(),
                     reinterpret_cast<const std::uint8_t*>(data),
                     reinterpret_cast<const std::uint8_t*>(data) + length);

        const auto* base = reinterpret_cast<const std::byte*>(bytes.data());
        message.initialize(base, bytes.size());

        std::size_t consumed = 0;

        while (message.next()) {
            if (message.current > message.end) { break; }   // the packet's bytes have not all arrived

            consumed = static_cast<std::size_t>(message.current - base);
            process_message(message.message, message.message_type);
        }

        // drop what was read, keeping the packet that is still arriving
        if (consumed > 0) {
            bytes.erase(bytes.begin(), bytes.begin() + static_cast<std::ptrdiff_t>(consumed));
        }
    }

    // count a message of the Packet tree
    void process_message(const std::byte* pointer, const char message_type) {
        switch (message_type) {
            case 'r':
                ++total_messages;
                ++snapshot_request_message;
                break;
            case 'e':
                ++total_messages;
                ++error_response_message;
                break;
            case 's':
                ++total_messages;
                ++snapshot_start_message;
                break;
            case 'd':
                ++total_messages;
                ++snapshot_data_message;
                {
                    const auto* sub_header = iex::iexequities::deepplus::snap::v1_05::SnapshotDataMessage::parse(pointer);
                    const char iex_tp_message_type = sub_header->iex_tp_message_type.get();
                    switch (iex_tp_message_type) {
                        case 'S':
                            ++system_event_message;
                            break;
                        case 'D':
                            ++security_directory_message;
                            break;
                        case 'H':
                            ++trading_status_message;
                            break;
                        case 'I':
                            ++retail_liquidity_indicator_message;
                            break;
                        case 'O':
                            ++operational_halt_status_message;
                            break;
                        case 'P':
                            ++short_sale_price_test_status_message;
                            break;
                        case 'E':
                            ++security_event_message;
                            break;
                        case 'a':
                            ++add_order_message;
                            break;
                        case 'M':
                            ++order_modify_message;
                            break;
                        case 'R':
                            ++order_delete_message;
                            break;
                        case 'L':
                            ++order_executed_message;
                            break;
                        case 'T':
                            ++trade_message;
                            break;
                        case 'B':
                            ++trade_break_message;
                            break;
                        case 'C':
                            ++clear_book_message;
                            break;
                        default:
                            ++unknown_messages;
                            break;
                    }
                }
                break;
            case 'x':
                ++total_messages;
                ++snapshot_end_message;
                break;

            default:
                ++total_messages;
                ++unknown_messages;
                if (options.verbose) {
                    std::cerr << "Unknown message_type: " << static_cast<int>(message_type) << std::endl;
                }
                break;
        }
    }

    // report statistics
    void report() {
        std::cout << std::endl;
        std::cout << "Statistics Report" << std::endl;
        std::cout << "=================" << std::endl;
        std::cout << "Total packets:   " << total_packets << std::endl;
        std::cout << "Unknown packets: " << unknown_packets << std::endl;
        std::cout << "Total messages:  " << total_messages << std::endl;
        std::cout << "Unknown types:   " << unknown_messages << std::endl;
        std::cout << "Heartbeats:      " << heartbeats << std::endl;

        std::cout << std::endl;
        std::cout << "Message Counts:" << std::endl;
        std::cout << "--------------" << std::endl;
        std::cout << "  SnapshotRequestMessage (r)           " << snapshot_request_message << std::endl;
        std::cout << "  ErrorResponseMessage (e)             " << error_response_message << std::endl;
        std::cout << "  SnapshotStartMessage (s)             " << snapshot_start_message << std::endl;
        std::cout << "  SnapshotDataMessage (d)              " << snapshot_data_message << std::endl;
        std::cout << "  SystemEventMessage (S)               " << system_event_message << std::endl;
        std::cout << "  SecurityDirectoryMessage (D)         " << security_directory_message << std::endl;
        std::cout << "  TradingStatusMessage (H)             " << trading_status_message << std::endl;
        std::cout << "  RetailLiquidityIndicatorMessage (I)  " << retail_liquidity_indicator_message << std::endl;
        std::cout << "  OperationalHaltStatusMessage (O)     " << operational_halt_status_message << std::endl;
        std::cout << "  ShortSalePriceTestStatusMessage (P)  " << short_sale_price_test_status_message << std::endl;
        std::cout << "  SecurityEventMessage (E)             " << security_event_message << std::endl;
        std::cout << "  AddOrderMessage (a)                  " << add_order_message << std::endl;
        std::cout << "  OrderModifyMessage (M)               " << order_modify_message << std::endl;
        std::cout << "  OrderDeleteMessage (R)               " << order_delete_message << std::endl;
        std::cout << "  OrderExecutedMessage (L)             " << order_executed_message << std::endl;
        std::cout << "  TradeMessage (T)                     " << trade_message << std::endl;
        std::cout << "  TradeBreakMessage (B)                " << trade_break_message << std::endl;
        std::cout << "  ClearBookMessage (C)                 " << clear_book_message << std::endl;
        std::cout << "  SnapshotEndMessage (x)               " << snapshot_end_message << std::endl;
    }
};
}
