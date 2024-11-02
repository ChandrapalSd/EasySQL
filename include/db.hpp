#pragma once
#include <nanodbc/nanodbc.h>
#include <iostream>
#include <memory>
#include <string>

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
		struct Info {
			std::string dbms_name;
			std::string dbms_version;
			std::string driver_name;
			std::string driver_version;
			std::string database_name;
			std::string catalog_name;
		};

		DB(std::string connStr, bool cacheSchema = false);
		DB(const DB&) = delete;
		DB& operator=(const DB&) = delete;
		~DB();

		const std::vector<Table>& getAllTables(bool refreshCache=false);
		std::optional<Table> getTable(std::string_view tableName);
		Info getInfo();
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
