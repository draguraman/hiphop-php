/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010- Facebook, Inc. (http://www.facebook.com)         |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/
/*
 * server_scoreboard.cpp
 *
 *  Created on: Jan 25, 2012
 *      Author: wli
 */

#include <runtime/base/server/server_scoreboard.h>
#include <runtime/base/server/server_stats.h>
#include <runtime/base/runtime_option.h>
#include <util/logger.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

namespace HPHP {

///////////////////////////////////////////////////////////////////////////////
// static

Mutex ServerScoreboard::s_lock;
long ServerScoreboard::s_startTime = time(NULL);
int64 ServerScoreboard::s_totalAccess = 0;
int64 ServerScoreboard::s_totalBytes = 0;

long ServerScoreboard::s_prevReportTime = 0;
int64 ServerScoreboard::s_prevTotalAccess = 0;
int64 ServerScoreboard::s_prevTotalBytes = 0;

void ServerScoreboard::Init() {
}

bool ServerScoreboard::IsEnabled() {
	return RuntimeOption::EnableScoreboard;
}

/**
 * Log one access with bytes
 */
void ServerScoreboard::LogAccess(int64 bytes) {
	Lock lock(s_lock, false);

	s_totalAccess++;
	s_totalBytes += bytes;
}

void ServerScoreboard::Report(std::string &out) {
	Lock lock(s_lock, false);

	long now = time(NULL);
	long uptime = getUptime();

	float reqPerSec = uptime == 0 ? 0 : s_totalAccess / uptime;
	float bytesPerSec = uptime == 0 ? 0 : s_totalBytes / uptime;
	float bytesPerReq = s_totalAccess == 0 ? 0 : (s_totalBytes/s_totalAccess);

	int busyWorkers, idleWorkers;
	std::string cards;

	ServerStats::ReportScorecard(busyWorkers, idleWorkers, cards);

	char buff[4096];
	sprintf(buff,
	  "Total Accesses: %Ld\n"
	  "Total kBytes: %Ld\n"
	  "CPULoad: %f\n"
	  "Uptime: %ld\n"
	  "ReqPerSec: %f\n"
	  "BytesPerSec: %f\n"
	  "BytesPerReq: %f\n"
	  "BusyWorkers: %d\n"
	  "IdleWorkers: %d\n"
	  "Scoreboard: %s\n",
	  s_totalAccess, s_totalBytes/1024, getCPULoad(), uptime,
	  reqPerSec, bytesPerSec, bytesPerReq, busyWorkers, idleWorkers, cards.c_str()
	  );

	out = buff;

	Logger::Verbose("Generated scoreboard size=%d", out.length());

	// Update prev
	s_prevTotalAccess = s_totalAccess;
	s_prevTotalBytes = s_totalBytes;
	s_prevReportTime = now;
}

double ServerScoreboard::getCPULoad() {
	double loads[1];
	getloadavg(loads, 1);

	return loads[0];
}

long ServerScoreboard::getUptime() {
	return time(NULL) - s_startTime;
}

} /* namespace HPHP */
