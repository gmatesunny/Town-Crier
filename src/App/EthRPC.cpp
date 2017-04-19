//
// Copyright (c) 2016-2017 by Cornell University.  All Rights Reserved.
//
// Permission to use the "TownCrier" software ("TownCrier"), officially
// docketed at the Center for Technology Licensing at Cornell University
// as D-7364, developed through research conducted at Cornell University,
// and its associated copyrights solely for educational, research and
// non-profit purposes without fee is hereby granted, provided that the
// user agrees as follows:
//
// The permission granted herein is solely for the purpose of compiling
// the TowCrier source code. No other rights to use TownCrier and its
// associated copyrights for any other purpose are granted herein,
// whether commercial or non-commercial.
//
// Those desiring to incorporate TownCrier software into commercial
// products or use TownCrier and its associated copyrights for commercial
// purposes must contact the Center for Technology Licensing at Cornell
// University at 395 Pine Tree Road, Suite 310, Ithaca, NY 14850; email:
// ctl-connect@cornell.edu; Tel: 607-254-4698; FAX: 607-254-5454 for a
// commercial license.
//
// IN NO EVENT SHALL CORNELL UNIVERSITY BE LIABLE TO ANY PARTY FOR
// DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES,
// INCLUDING LOST PROFITS, ARISING OUT OF THE USE OF TOWNCRIER AND ITS
// ASSOCIATED COPYRIGHTS, EVEN IF CORNELL UNIVERSITY MAY HAVE BEEN
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// THE WORK PROVIDED HEREIN IS ON AN "AS IS" BASIS, AND CORNELL
// UNIVERSITY HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,
// ENHANCEMENTS, OR MODIFICATIONS.  CORNELL UNIVERSITY MAKES NO
// REPRESENTATIONS AND EXTENDS NO WARRANTIES OF ANY KIND, EITHER IMPLIED
// OR EXPRESS, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, OR THAT THE USE
// OF TOWNCRIER AND ITS ASSOCIATED COPYRIGHTS WILL NOT INFRINGE ANY
// PATENT, TRADEMARK OR OTHER RIGHTS.
//
// TownCrier was developed with funding in part by the National Science
// Foundation (NSF grants CNS-1314857, CNS-1330599, CNS-1453634,
// CNS-1518765, CNS-1514261), a Packard Fellowship, a Sloan Fellowship,
// Google Faculty Research Awards, and a VMWare Research Award.
//

#include "Enclave_u.h"
#include "Log.h"
#include "App/EthRPC.h"
#include "Constants.h"

#include <jsonrpccpp/client/connectors/httpclient.h>

#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <map>
#include <string>

#include "json/json.h"
#include "types.h"

ethRPCClient *rpc_client;

using std::invalid_argument;

/*!
 * Send raw transactions to geth
 * @param raw encoded transaction
 * @return the tx hash
 * See https://github.com/ethereum/wiki/wiki/JSON-RPC#eth_sendrawtransaction
 */
string send_transaction(const std::string &rawTransaction) {
  std::string param(rawTransaction);

  std::string res = rpc_client->eth_sendRawTransaction(param);
  LL_INFO("response recorded (%s)", res.c_str());

  return res;
}

/*!
 * @remark How to get topic id?
 *  > https://asecuritysite.com/encryption/sha3
 *  > https://github.com/ethereum/wiki/wiki/Ethereum-Contract-ABI
 *  $ sha3(RequestInfo(uint64,uint8,address,uint256,address,bytes32,uint256,bytes32[]))
 * Returns a filter from block [from] to block [to], writes the value of the filter into [id]
 * Postcondition: [id] is a valid id that can be used with eth_get_filter_logs
 */
string eth_new_filter(blocknum_t from, blocknum_t to) {
  if (from < 0 || to < 0) {
    throw invalid_argument("from or to is smaller than 0");
  }

  Json::Value filter_opt;
  filter_opt["address"] = TC_ADDRESS;

  filter_opt["topics"][0] =
      "0x295780EA261767C398D062898E5648587D7B8CA371FFD203BE8B4F9A43454FFA";
  filter_opt["fromBlock"] = static_cast<Json::Value::UInt64 >(from);
  filter_opt["toBlock"] = static_cast<Json::Value::UInt64 >(to);

  return rpc_client->eth_newFilter(filter_opt);
}

/* eth_getfilterlogs [hostname] [port] [filter_id] [result] returns the logged events of [filter_id]
 * Given the [filter_id] writes to [result] an array containing the required data
 */
void eth_getfilterlogs(const string &filter_id, Json::Value *txnContainer) {
  txnContainer->clear();
  if (filter_id.empty()) {
    throw invalid_argument("filter_id is empty");
  }
  *txnContainer = rpc_client->eth_getFilterLogs(filter_id);
}

/*!
 * @return the highest block number that geth has seen so far
 */
blocknum_t eth_blockNumber() {
  blocknum_t ret;
  std::string blk = rpc_client->eth_blockNumber();
  LL_DEBUG("eth_blockNumber returns %s", blk.c_str());
  std::stringstream ss;
  ss << std::hex << blk;
  ss >> ret;
  return ret;
}

uint64_t eth_getTransactionCount() {
  uint64_t ret;
  std::string txn_count = rpc_client->eth_getTransactionCount(
      SGX_ADDRESS, "pending");
  std::stringstream ss;
  ss << std::hex << txn_count;
  ss >> ret;
  return ret;
}

