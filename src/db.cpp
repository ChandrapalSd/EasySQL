#include "db.hpp"
#include "datatype.hpp"
#include "log.hpp"
#include <format>

namespace esql {

	DB::DB(std::string connStr, bool cacheSchema)
		:_connectionString(connStr)
	{
		_connection = nanodbc::connection(_connectionString);
		LOG(INFO) << "Connected with driver " << _connection.driver_name();

        if (cacheSchema) {
            getAllTables(true);
        }
	}

	DB::~DB()
	{
		_connection.disconnect();
		_connection.deallocate();
		LOG(INFO) << "Database connection freed";
	}

	std::vector<Table> DB::getAllTables(bool refreshCache) {
        if (refreshCache || this->tables.size() == 0) {
            nanodbc::catalog catalog(_connection);
            auto tables = catalog.find_tables();
            std::vector<Table> tableVec;
            while (tables.next())
            {
                tableVec.emplace_back(*this, tables.table_name());
            }
            this->tables = tableVec;
        }
        return this->tables;
	}

	DB::Info DB::getInfo()
	{
		return 
		{
			.dbms_name = _connection.dbms_name(),
			.dbms_version = _connection.dbms_version(),
			.driver_name = _connection.driver_name(),
			.driver_version = _connection.driver_version(),
			.database_name = _connection.database_name(),
			.catalog_name = _connection.catalog_name(),
		};
	}

	nanodbc::result DB::executeSql(const std::string statement)
	{
		if (traceSql)
			LOG(INFO) << "Executing SQL : " << statement;
		return execute(_connection, statement);
	}

    

	Table::Table(DB& db, const std::string table_name)
		: name(table_name)
	{
		nanodbc::catalog cat(db._connection);
		auto cols = cat.find_columns(nanodbc::string(), table_name);
        
		while (cols.next()) {
            this->columns.emplace_back(cols.column_name(), data_type_identifier(cols.data_type()), cols.nullable());
		}

	}

	Column::Column(const std::string name, const std::string type, bool nullable)
		: name(name), type(type), nullable(nullable)
	{
	}

}