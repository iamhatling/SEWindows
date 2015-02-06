#ifndef _SEWINDOWS_H_
#define _SEWINDOWS_H_

#include <Windows.h>

#ifdef SEWINDOWS_EXPORTS
#define SEWINDOWS_API  __declspec(dllexport)
#else
#define SEWINDOWS_API  __declspec(dllimport)
#endif

#define SEWIN_MODE_INTERCEPT      1    // Intercept mode
#define SEWIN_MODE_NOTIFY         2    // Notify    mode

#define SEWIN_TYPE_FILE         0x1    // File    operations
#define SEWIN_TYPE_FROC         0x2    // Process operations
#define SEWIN_TYPE_REG          0x4    // Regedit operations

// File (dir) Attribute
typedef struct _FILE_BASIC_INFORMATION {
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    ULONG         FileAttributes;
} FILE_BASIC_INFORMATION, *PFILE_BASIC_INFORMATION;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * callback functions
 * 
 *  1.In SEWIN_MODE_INTERCEPT mode:
 *      if sewin_operations.func() return TRUE, the operation will be allowed,
 *      else the operation will be intercepted.
 *  2.In SEWIN_MODE_NOTIFY mode:
 *      the operation will be allowed all the time
 */
struct sewin_operations {
    // File(Dir) operations
    BOOLEAN(*file_create)           (WCHAR *user_name, WCHAR *process, WCHAR *file_path);
    BOOLEAN(*file_unlink)           (WCHAR *user_name, WCHAR *process, WCHAR *file_path);
    BOOLEAN(*file_set_attr)         (WCHAR *user_name, WCHAR *process, WCHAR *file_path, PFILE_BASIC_INFORMATION pfbi);
    BOOLEAN(*file_read)             (WCHAR *user_name, WCHAR *process, WCHAR *file_path);
    BOOLEAN(*file_write)            (WCHAR *user_name, WCHAR *process, WCHAR *file_path);
    BOOLEAN(*file_rename)           (WCHAR *user_name, WCHAR *process, WCHAR *src_file, WCHAR *new_name);
    BOOLEAN(*file_execute)          (WCHAR *user_name, WCHAR *process, WCHAR *file_path);

    BOOLEAN(*dir_create)            (WCHAR *user_name, WCHAR *process, WCHAR *dir_path);
    BOOLEAN(*dir_unlink)            (WCHAR *user_name, WCHAR *process, WCHAR *dir_path);
    BOOLEAN(*dir_set_attr)          (WCHAR *user_name, WCHAR *process, WCHAR *dir_path, PFILE_BASIC_INFORMATION pfbi);
    BOOLEAN(*dir_write)             (WCHAR *user_name, WCHAR *process, WCHAR *dir_path);
    BOOLEAN(*dir_rename)            (WCHAR *user_name, WCHAR *process, WCHAR *src_dir, WCHAR *new_name);

    // Process operations
    BOOLEAN(*process_create)        (WCHAR *user_name, WCHAR *process, WCHAR *dst_proc);
    BOOLEAN(*process_create_thread) (WCHAR *user_name, WCHAR *process, WCHAR *dst_proc);
    BOOLEAN(*process_kill)          (WCHAR *user_name, WCHAR *process, WCHAR *dst_proc);
    BOOLEAN(*process_read_mem)      (WCHAR *user_name, WCHAR *process, WCHAR *dst_proc);
    BOOLEAN(*process_write_mem)     (WCHAR *user_name, WCHAR *process, WCHAR *dst_proc);
    BOOLEAN(*process_set_mem_attr)  (WCHAR *user_name, WCHAR *process, WCHAR *dst_proc);
    BOOLEAN(*process_copy_handle)   (WCHAR *user_name, WCHAR *process, WCHAR *dst_proc);
    BOOLEAN(*process_suspend)       (WCHAR *user_name, WCHAR *process, WCHAR *dst_proc);
    BOOLEAN(*process_thread_suspend)(WCHAR *user_name, WCHAR *process, WCHAR *dst_proc);
    BOOLEAN(*process_thread_kill)   (WCHAR *user_name, WCHAR *process, WCHAR *dst_proc);

    // Regedit operations
    BOOLEAN(*reg_create_key)        (WCHAR *user_name, WCHAR *process, WCHAR *reg_path);
    BOOLEAN(*reg_delete_key)        (WCHAR *user_name, WCHAR *process, WCHAR *reg_path);
    BOOLEAN(*reg_enum_key)          (WCHAR *user_name, WCHAR *process, WCHAR *reg_path);
    BOOLEAN(*reg_rename_key)        (WCHAR *user_name, WCHAR *process, WCHAR *src_path, WCHAR *new_name);
    BOOLEAN(*reg_set_value)         (WCHAR *user_name, WCHAR *process, WCHAR *reg_path, WCHAR *reg_value);
    BOOLEAN(*reg_delete_value)      (WCHAR *user_name, WCHAR *process, WCHAR *reg_path);
    BOOLEAN(*reg_read_key)          (WCHAR *user_name, WCHAR *process, WCHAR *reg_path);
    BOOLEAN(*reg_enum_value)        (WCHAR *user_name, WCHAR *process, WCHAR *reg_path);
    BOOLEAN(*reg_save_key)          (WCHAR *user_name, WCHAR *process, WCHAR *reg_path);
    BOOLEAN(*reg_restore_key)       (WCHAR *user_name, WCHAR *process, WCHAR *reg_path);
    BOOLEAN(*reg_replace)           (WCHAR *user_name, WCHAR *process, WCHAR *reg_path);
    BOOLEAN(*reg_load_key)          (WCHAR *user_name, WCHAR *process, WCHAR *reg_path);
    BOOLEAN(*reg_unload_key)        (WCHAR *user_name, WCHAR *process, WCHAR *reg_path);
    BOOLEAN(*reg_set_key_attr)      (WCHAR *user_name, WCHAR *process, WCHAR *reg_path);
};

/**
 * sewin_init : init sewindows
 *
 * return :  TRUE  - success
 *           FALSE - Failed
 */
SEWINDOWS_API BOOLEAN sewin_init(void);

/**
 * sewin_setoption : set working mode
 *
 * @param mode : SEWIN_MODE_INTERCEPT or SEWIN_MODE_NOTIFY
 * @param type : SEWIN_TYPE_FILE | SEWIN_TYPE_FROC | SEWIN_TYPE_REG
 *
 * return :  TRUE  - success
 *           FALSE - Failed
 */
SEWINDOWS_API BOOLEAN sewin_setoption(int mode, int type);

/**
 * sewin_register_opt : register callback functions
 *
 * @param ops : sewin_operations
 *
 * return :  TRUE  - success
 *           FALSE - Failed
 */
SEWINDOWS_API BOOLEAN sewin_register_opt(struct sewin_operations *ops);

#ifdef __cplusplus
}
#endif

#endif  // _SEWINDOWS_H_