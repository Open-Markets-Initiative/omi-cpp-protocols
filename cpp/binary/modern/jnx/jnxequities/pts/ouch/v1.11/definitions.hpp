#pragma once

#include "structs/ClientPacketHeader.hpp"
#include "structs/ServerPacketHeader.hpp"

#include "messages/DebugPacket.hpp"
#include "messages/LoginRequestPacket.hpp"
#include "messages/UnsequencedDataPacket.hpp"
#include "messages/EnterOrderMessage.hpp"
#include "messages/ReplaceOrderMessage.hpp"
#include "messages/CancelOrderMessage.hpp"
#include "messages/LoginAcceptedPacket.hpp"
#include "messages/LoginRejectedPacket.hpp"
#include "messages/SequencedDataPacket.hpp"
#include "messages/SystemEventMessage.hpp"
#include "messages/OrderAcceptedMessage.hpp"
#include "messages/OrderReplacedMessage.hpp"
#include "messages/OrderCanceledMessage.hpp"
#include "messages/OrderAiqCanceledMessage.hpp"
#include "messages/OrderExecutedMessage.hpp"
#include "messages/OrderRejectedMessage.hpp"

#include "actions/ClientHeartbeat.hpp"
#include "actions/LogoutRequest.hpp"
#include "actions/ServerHeartbeat.hpp"
#include "actions/EndOfSession.hpp"

#include "iterators/ClientSoupBinTcpPacketIterator.hpp"
#include "iterators/ServerSoupBinTcpPacketIterator.hpp"
