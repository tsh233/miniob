#include "sql/executor/drop_table_executor.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "session/session.h"
#include "sql/stmt/drop_table_stmt.h"
#include "storage/db/db.h"
#include "common/log/log.h"

RC DropTableExecutor::execute(SQLStageEvent *sql_event)
{
  Stmt *stmt = sql_event->stmt();
  Session *session = sql_event->session_event()->session();
  ASSERT(stmt->type() == StmtType::DROP_TABLE,
      "drop table executor can not run this command: %d",
      static_cast<int>(stmt->type()));

  DropTableStmt *drop_stmt = static_cast<DropTableStmt *>(stmt);
  const char *table_name = drop_stmt->table_name().c_str();
  Db *db = session->get_current_db();
  if (db == nullptr) {
    return RC::SCHEMA_DB_NOT_OPENED;
  }
  return db->drop_table(table_name);
}
