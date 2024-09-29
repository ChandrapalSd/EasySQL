#pragma once
#include <nanodbc/nanodbc.h>

#include <format>
#include <cstring>
#include <iostream>

namespace esql {


    void getTableData(nanodbc::connection connection, const std::string& tableName, const uint32_t rowCount=0)
    {
        const std::string statement = std::format("select * from {};", tableName);
        nanodbc::result results = execute(connection, statement );
        const short columns = results.columns();
        long rows_displayed = 0;

        std::cout << "\nDisplaying " << results.affected_rows() << " rows "
            << "(" << results.rowset_size() << " fetched at a time):" << std::endl;

        // show the column names
        std::cout << "row\t";
        for (short i = 0; i < columns; ++i)
            std::cout << results.column_name(i) << "\t";
        std::cout << std::endl;

        // show the column data for each row
        while (results.next())
        {
            std::cout << rows_displayed++ << "\t";
            for (short col = 0; col < columns; ++col)
                std::cout << "(" << results.get<nanodbc::string>(col, "null") << ")\t";
            std::cout << std::endl;
        }
    }

    void getAllTables(nanodbc::connection connection) {
        nanodbc::catalog catalog(connection);
        auto tables = catalog.find_tables();
        while (tables.next())
        {
            std::cout << 
                std::format(" table_name: {} \n table_remarks: {} \n table_type: {} \n table_schema: {} \n", 
                            tables.table_name(), 
                            tables.table_remarks(), 
                            tables.table_type(), 
                            tables.table_schema());
        }
    }
}