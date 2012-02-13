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
