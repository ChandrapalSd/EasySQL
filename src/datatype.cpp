#include "datatype.hpp"
#include <glog/logging.h>

#ifdef _WIN32
	#ifndef __MINGW32__
		#define NOMINMAX
	#endif
	#include <windows.h> // SQLLEN, SQLULEN, SQLHWND
#endif

#include <sql.h>
#include <sqlext.h>

namespace esql {

	std::string data_type_identifier(int t)
	{

		// List based on https://msdn.microsoft.com/en-us/library/ms710150.aspx
		switch (t)
		{
		case SQL_UNKNOWN_TYPE:
			return "SQL_UNKNOWN_TYPE";
		case SQL_CHAR:
			return "SQL_CHAR";
		case SQL_VARCHAR:
			return "SQL_VARCHAR";
		case SQL_LONGVARCHAR:
			return "SQL_LONGVARCHAR";
		case SQL_WCHAR:
			return "SQL_WCHAR";
		case SQL_WVARCHAR:
			return "SQL_WVARCHAR";
		case SQL_WLONGVARCHAR:
			return "SQL_WLONGVARCHAR";
		case SQL_BINARY:
			return "SQL_BINARY";
		case SQL_VARBINARY:
			return "SQL_VARBINARY";
		case SQL_LONGVARBINARY:
			return "SQL_LONGVARBINARY";
		case SQL_DECIMAL:
			return "SQL_DECIMAL";
		case SQL_NUMERIC:
			return "SQL_NUMERIC";
		case SQL_TINYINT:
			return "SQL_TINYINT";
		case SQL_SMALLINT:
			return "SQL_SMALLINT";
		case SQL_INTEGER:
			return "SQL_INTEGER";
		case SQL_BIGINT:
			return "SQL_BIGINT";
		case SQL_FLOAT:
			return "SQL_FLOAT";
		case SQL_REAL:
			return "SQL_REAL";
		case SQL_DOUBLE:
			return "SQL_DOUBLE";
		case SQL_BIT:
			return "SQL_BIT";
		case SQL_TIMESTAMP:
			return "SQL_TIMESTAMP";
		case SQL_DATETIME:
			return "SQL_DATETIME";
		case SQL_TYPE_DATE:
			return "SQL_TYPE_DATE";
		case SQL_TYPE_TIME:
			return "SQL_TYPE_TIME";
		case SQL_TYPE_TIMESTAMP:
			return "SQL_TYPE_TIMESTAMP";
			// case SQL_TYPE_UTCDATETIME:
			//     return "SQL_TYPE_UTCDATETIME";
			// case SQL_TYPE_UTCTIME:
			//     return "SQL_TYPE_UTCTIME";
		case SQL_INTERVAL_MONTH:
			return "SQL_INTERVAL_MONTH";
		case SQL_INTERVAL_YEAR:
			return "SQL_INTERVAL_YEAR";
		case SQL_INTERVAL_YEAR_TO_MONTH:
			return "SQL_INTERVAL_YEAR_TO_MONTH";
		case SQL_INTERVAL_DAY:
			return "SQL_INTERVAL_DAY";
		case SQL_INTERVAL_HOUR:
			return "SQL_INTERVAL_HOUR";
		case SQL_INTERVAL_MINUTE:
			return "SQL_INTERVAL_MINUTE";
		case SQL_INTERVAL_SECOND:
			return "SQL_INTERVAL_SECOND";
		case SQL_INTERVAL_DAY_TO_HOUR:
			return "SQL_INTERVAL_DAY_TO_HOUR";
		case SQL_INTERVAL_DAY_TO_MINUTE:
			return "SQL_INTERVAL_DAY_TO_MINUTE";
		case SQL_INTERVAL_DAY_TO_SECOND:
			return "SQL_INTERVAL_DAY_TO_SECOND";
		case SQL_INTERVAL_HOUR_TO_MINUTE:
			return "SQL_INTERVAL_HOUR_TO_MINUTE";
		case SQL_INTERVAL_HOUR_TO_SECOND:
			return "SQL_INTERVAL_HOUR_TO_SECOND";
		case SQL_INTERVAL_MINUTE_TO_SECOND:
			return "SQL_INTERVAL_MINUTE_TO_SECOND";
		case SQL_GUID:
			return "SQL_GUID";
		default:
			LOG(ERROR) << "UNKNOWN SQL TYPE : " << t;
			return std::to_string(t);
		}
	}

}