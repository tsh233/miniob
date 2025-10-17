#include "sql/stmt/drop_table_stmt.h"
#include "storage/db/db.h"
#include "common/lang/string.h"
#include "common/log/log.h"

RC DropTableStmt::create(Db *db, const DropTableSqlNode &drop_table, Stmt *&stmt)
{
  stmt = nullptr;
  const char *table_name = drop_table.relation_name.c_str();
  if (common::is_blank(table_name)) {
    LOG_WARN("Invalid table name");
    return RC::INVALID_ARGUMENT;
  }

  // We don't need to ensure table exists now; executor will handle
  stmt = new DropTableStmt(drop_table.relation_name);
  return RC::SUCCESS;
}
