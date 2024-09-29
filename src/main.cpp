#include "example_unicode_utils.hpp"
#include "ESQL.h"
#include <nanodbc/nanodbc.h>

#include <algorithm>
#include <cstring>
#include <iostream>

void usage(std::ostream& out, const std::string& binary_name)
{
    out << "usage: " << binary_name << " connection_string" << std::endl;
}


void show(nanodbc::result& results)
{
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

int main(int argc, char* argv[])
{
    std::string conStr = "Driver={MySQL ODBC 8.0 Unicode Driver};Server=localhost;Database=testdb;UID=root;PWD=3690;Port=3306;";
    if (argc != 2)
    {
        std::cout << "Using default connection string : " << conStr;
        //usage(std::cerr, argv[0]);
        //return EXIT_FAILURE;
    }
    else {
        conStr = argv[1];
    }

    try
    {
        auto const connection_string(convert(conStr));
        nanodbc::connection connection(connection_string);
        std::cout << "Connected with driver " << connection.driver_name() << std::endl;
        //nanodbc::result results = execute(connection, NANODBC_TEXT("select * from chan;"));
        //show(results);

        //esql::getTableData(connection, "chan1");
        esql::getAllTables(connection);
        /*results.next();
        auto const value = results.get<nanodbc::string>(1);
        std::cout << std::endl << results.get<int>(NANODBC_TEXT("first")) << ", " << convert(value) << std::endl;
        */
        return EXIT_SUCCESS;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_FAILURE;
}
