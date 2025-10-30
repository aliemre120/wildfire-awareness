// db.c
#include "db.h" // Include the declarations from db.h
#include <stdio.h> // for printf, fprintf
#include <string.h> // for string functions
#include <time.h> // for time functions
#include <sqlite3.h> // SQLite C library

// Global database connection
static sqlite3 *g_db = NULL;

// Get current datetime in "YYYY-MM-DD HH:MM" format
static void datetime_now(char out[20]) {
    time_t t = time(NULL);
    struct tm tmv;

    
    localtime_s(&tmv, &t);

    strftime(out, 20, "%Y-%m-%d %H:%M", &tmv);
}

// Initialize the database and create table if not exists
bool db_init(void) {
    if (sqlite3_open(DB_PATH, &g_db) != SQLITE_OK) {
        fprintf(stderr, "DB open error: %s\n", sqlite3_errmsg(g_db));
        return false;
    }

    //SQL command
    const char *sql =
        "CREATE TABLE IF NOT EXISTS fires ("
        " id INTEGER PRIMARY KEY AUTOINCREMENT,"
        " datetime TEXT NOT NULL,"
        " location TEXT NOT NULL,"
        " status TEXT NOT NULL CHECK(status IN('active','extinguished'))"
        ");";

    //to run the sql command
    char *errmsg = NULL;
    if (sqlite3_exec(g_db, sql, NULL, NULL, &errmsg) != SQLITE_OK) {
        fprintf(stderr, "DB schema error: %s\n", errmsg);
        sqlite3_free(errmsg);
        return false;
    }
    return true;
}

int db_add_fire(const char *location) {
    if (!g_db && !db_init()) return 0;

    char dt[20];
    datetime_now(dt);

    const char *sql = "INSERT INTO fires(datetime, location, status) VALUES(?,?, 'active');";
    sqlite3_stmt *st = NULL;

    //SQL query
    if (sqlite3_prepare_v2(g_db, sql, -1, &st, NULL) != SQLITE_OK) {
        fprintf(stderr, "Prepare error: %s\n", sqlite3_errmsg(g_db));
        return 0;
    }
    sqlite3_bind_text(st, 1, dt, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(st, 2, location, -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(st);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Insert error: %s\n", sqlite3_errmsg(g_db));
        sqlite3_finalize(st);
        return 0;
    }
    sqlite3_finalize(st);
    return (int)sqlite3_last_insert_rowid(g_db);
}

bool db_extinguish_fire(int id) {
    if (!g_db && !db_init()) return false;

    const char *sql = "UPDATE fires SET status='extinguished' WHERE id=? AND status='active';";
    sqlite3_stmt *st = NULL;

    if (sqlite3_prepare_v2(g_db, sql, -1, &st, NULL) != SQLITE_OK) {
        fprintf(stderr, "Prepare error: %s\n", sqlite3_errmsg(g_db));
        return false;
    }
    sqlite3_bind_int(st, 1, id);

    int rc = sqlite3_step(st);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Update error: %s\n", sqlite3_errmsg(g_db));
        sqlite3_finalize(st);
        return false;
    }
    int changes = sqlite3_changes(g_db);
    sqlite3_finalize(st);
    return changes > 0;
}
static const char* map_status(const char* s, int english) {
    if (english) {
        if (strcmp(s, "active")==0) return "Active";
        if (strcmp(s, "extinguished")==0) return "Extinguished";
    } else {
        if (strcmp(s, "active")==0) return "Aktif";
        if (strcmp(s, "extinguished")==0) return "Sonduruldu";
    }
    return s; 
}

static int print_rows_cb(void *arg, int colc, char **colv, char **coln) {
    (void)coln; (void)colc;
    int english = *(int*)arg;
    // Sütunlar: id, datetime, location, status
    if (english) {
        printf("%-4s %-16s %-22s %-13s\n", colv[0], colv[1], colv[2],  map_status(colv[3], english));
    } else {
        printf("%-4s %-16s %-22s %-13s\n", colv[0], colv[1], colv[2],  map_status(colv[3], english));
    }
    return 0;
}

void db_list_active(int english) {
    if (!g_db && !db_init()) return;

    if (english) {
        printf("\n--- ACTIVE WILDFIRES ---\n");
        printf("%-4s %-16s %-22s %-13s\n", "ID", "DateTime", "Location", "Status");
    } else {
        printf("\n--- AKTIF YANGINLAR ---\n");
        printf("%-4s %-16s %-22s %-13s\n", "ID", "TarihSaat", "Konum", "Durum");
    }
    printf("-------------------------------------------------------------\n");

    char *errmsg = NULL;
    int lang = english;
    const char *sql = "SELECT id, datetime, location, status FROM fires WHERE status='active' ORDER BY id DESC;";
    if (sqlite3_exec(g_db, sql, print_rows_cb, &lang, &errmsg) != SQLITE_OK) {
        fprintf(stderr, "Query error: %s\n", errmsg);
        sqlite3_free(errmsg);
    }
    printf("\n");
}

void db_list_all(int english) {
    if (!g_db && !db_init()) return;

    if (english) {
        printf("\n--- ALL REPORTED WILDFIRES ---\n");
        printf("%-4s %-16s %-22s %-13s\n", "ID", "DateTime", "Location", "Status");
    } else {
        printf("\n--- TUM BILDIRILEN YANGINLAR ---\n");
        printf("%-4s %-16s %-22s %-13s\n", "ID", "TarihSaat", "Konum", "Durum");
    }
    printf("-------------------------------------------------------------\n");

    char *errmsg = NULL;
    int lang = english;
    const char *sql = "SELECT id, datetime, location, status FROM fires ORDER BY id DESC;";
    if (sqlite3_exec(g_db, sql, print_rows_cb, &lang, &errmsg) != SQLITE_OK) {
        fprintf(stderr, "Query error: %s\n", errmsg);
        sqlite3_free(errmsg);
    }
    printf("\n");
}
