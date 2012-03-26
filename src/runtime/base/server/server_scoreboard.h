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
 * server_scoreboard.h
 *
 *  Created on: Jan 25, 2012
 *      Author: wli
 */

#ifndef SERVER_SCOREBOARD_H_
#define SERVER_SCOREBOARD_H_

#include <util/base.h>
#include <runtime/base/types.h>

namespace HPHP {

class ServerScoreboard {
public:

	static void Init();

	static bool IsEnabled();

	static void LogAccess(int64 bytes);

	static void Report(std::string &out);

private:

	static Mutex s_lock;
	static int64 s_totalAccess;
	static int64 s_totalBytes;

	static long s_prevReportTime;
	static int64 s_prevTotalAccess;
	static int64 s_prevTotalBytes;

	// Server start time
	static long s_startTime;

	static double getCPULoad();
	static long getUptime();
};

} /* namespace HPHP */
#endif /* SERVER_SCOREBOARD_H_ */
