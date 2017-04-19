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

#include <gtest/gtest.h>

#include "App/tc-exception.h"
#include "App/utils.h"
#include "App/Enclave_u.h"
#include "App/key-utils.h"

class TransactionSuiteTest : public ::testing::Test {
 protected:
  sgx_enclave_id_t eid;
  virtual void SetUp() {
    initialize_enclave(ENCLAVE_FILENAME, &eid);
  }

  virtual void TearDown() {
    sgx_destroy_enclave(eid);
  }
};

TEST_F(TransactionSuiteTest, All) {
  int ret;

#ifdef TC_SGX_IN_HW_MODE
#define SEALED_KEY "BAACAAAAAAAEBP//AQEAAAAAAAAAAAAAy/////////8AAAAAAAAAAIa71A2C4RxqN1TCMWB49meKY6OUlfyuqEYkvZtj4Mhm/v///wAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAgAAAAAAAAAAAAAAAAAAAAIAAAAAAAAAAAAAAAAAAAAJ3NxMA/M54C7uweBmKPqTUJSFCt1O6vCsiYZcObv7otR9SBbys0xvEvTLHR68lDj3EGIJgAAAAAGYBgAgAAAAAxAAAAAAAAAHBaxOz+fwAAyFJRMU1/AAD4VE8xTX8AAJRZxOz+fwAAYFrE7P5/AAAgwXUyTX8AAAAAAAD+fwAADwAAAAAAAABEPFUyTX8AAAAAAAAAAAAAFgUAAAAAAAAA4HUyTX8AAIAd8TBNfwAA+O/xME1/AAB7RFUyTX8AABYFAAAAAAAA+O/xME1/AAAA4HUyTX8AAHhaxOz+fwAAdFrE7P5/AAARPlUyTX8AAAEAAAAAAAAAzG3pMU1/AADITekxTX8AAHhaxOz+fwAAIXSwAgAAAADQwQoAAAAAACEAAABNfwAAUFvE7P5/AAD47/EwTX8AAIAd8TBNfwAAdFrE7P5/AABAW8Ts/n8AACDBdTJNfwAAAAAAAE1/AAAPAAAAAAAAAAAAAAAAAAAAeHBQMQAAAAAAAAAAAAAAAOglQAAAAAAARDxVMk1/AADgW8Ts/n8AAHcEAAAAAAAAAOB1Mk1/AACAHfEwTX8AAPjv8TBNfwAAe0RVMk1/AAB3BAAAAAAAAPjv8TBNfwAAAOB1Mk1/AAB4W8Ts/n8AAA=="
#else
#define SEALED_KEY "BAACAAAAAABIIPM3auay8gNNO3pLSKd4y/////////8AAAAAAAAAAMmTv7tkyuQ34fpQ5VRNOjwHX7dBwsi8VdLR3IB4FljF/v///wAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAgAAAAAAAAAAAAAAAAAAAAIAAAAAAAAAAAAAAAAAAAANURSkg1WgSuijoRD8ziZfVA27eypCN2RKglKGjY9vPDz636xSK/N2K9M8oyYySNGmBloTT+fwAAoGShNP5/AAAAMIDdAAAAAAAAAAAAAAAAAAAAAAAAAADYzYHdoX8AAEBgoTT+fwAAQFVY3KF/AACQZKE0/n8AADONTAAAAAAAqGShNP5/AAAt4yDcoX8AAAYAAAAAAAAAkBCA3aF/AAABAAAAAAAAAAAAAAAAAAAAAQAAAAAAAACAyoHdoX8AAAAAAAAAAAAAawQAAAAAAACAyoHdoX8AAAAAAAAAAAAA2M2B3aF/AACwX6E0/n8AAGsEAAABAAAAoF+hNP5/AABxBiCYAAAAALfdFd2hfwAA/////wAAAAAgAAAAAAAAAHige9yhfwAAADCA3aF/AADogkAAAAAAADhgoTT+fwAAmYRYXAAAAAASYnEBAAAAABkAAAAAAAAARBxg3QIAAAAw+RTdoX8AAHcEAAAAAAAA4DmA3aF/AABEHGDdoX8AAPgfHdyhfwAABAEAAAAAAAAQRYDdoX8AABhv0tyhfwAA+I7S3KF/AAB7JGDdoX8AAAQBAAAAAAAA+I7S3KF/AAAQRYDdoX8AAPhgoTT+fwAA9GChNP5/AABEHGDdoX8AAA=="
#endif

  try {
    provision_key(eid, SEALED_KEY);
    transaction_rlp_test(eid, &ret);
    EXPECT_EQ(0, ret);
  }
  catch (tc::EcallException &e) {
    LL_CRITICAL(e.what());
    FAIL();
  }
}
