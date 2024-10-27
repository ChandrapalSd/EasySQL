#pragma once
#include <nanodbc/nanodbc.h>
#include <iostream>
#include <memory>

#include "datatype.hpp"

namespace esql{
	class DB;

	class Column
	{
	public:
		Column(const std::string name, const std::string type, bool nullable=false);
		std::string name;
		std::string type;
		bool nullable;
	};

	class Table
	{
	public:
		Table(DB& db, const std::string name);
		std::string name;
		std::vector<Column> columns;
	};

	class DB
	{
	public:
		DB(std::string connStr, bool cacheSchema = false);
		~DB();

		std::vector<Table> getAllTables(bool refreshCache=false);
	private:
		[[nodiscard]] nanodbc::result executeSql(const std::string statement);
	public:
		bool traceSql = true;
	private:
		const std::string _connectionString;
		nanodbc::connection _connection;
		std::vector<Table> tables;
	
		friend Table;
	};

}
