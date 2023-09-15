import sys
import sqlite3

if __name__ == "__main__":
    PREP_RESULT = sys.argv[1]
    print(PREP_RESULT)
    con = sqlite3.connect(PREP_RESULT)
    cur = con.cursor()
    preprocessed_files = cur.execute("SELECT absolute_name FROM SourceFile WHERE type = 'PREPROCESSED'").fetchall()
    for (absolute_name,) in preprocessed_files:
        (src_file_id,) = cur.execute("SELECT id FROM src_file WHERE abs_path = '{}'".format(absolute_name)).fetchone()
        (orig_file_id,) = cur.execute("SELECT orig_file_id FROM src_object WHERE object_kind = 'OK_FILE_DECL' AND file_id = '{}'".format(src_file_id)).fetchone()
        (src_abs_path,) = cur.execute("SELECT abs_path FROM src_file WHERE id = '{}'".format(orig_file_id)).fetchone()
        (source_file_id,) = cur.execute("SELECT id FROM SourceFile WHERE absolute_name = '{}'".format(src_abs_path)).fetchone()
        cur.execute("UPDATE SourceFile SET src_id = '{}' WHERE absolute_name = '{}'".format(source_file_id, absolute_name))
        print("UPDATE SourceFile SET src_id = '{}' WHERE absolute_name = '{}'".format(source_file_id, absolute_name))
    con.commit()
    con.close()