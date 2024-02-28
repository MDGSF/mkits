#ifndef MKITS_INCLUDE_MCKITS_CORE_ENCODING_MCKITS_ENCODING_INIPARSER_H_
#define MKITS_INCLUDE_MCKITS_CORE_ENCODING_MCKITS_ENCODING_INIPARSER_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MCKITS_INIPARSER_DEFAULT_SECTION "DEFAULT"
#define MCKITS_INIPARSER_DEFAULT_DELIMITERS "=:"
#define MCKITS_INIPARSER_DEFAULT_COMMENT_PREFIXS "#;"

/*
[section_name]
entry_name1 = entry_value1
entry_name2 = entry_value2
*/
struct MckitsIniParser;

/*
@brief: Create a new iniparser.
@param delimiters[in]: If pass NULL, default is "=:".
@param comment_prefixs[in]: If pass NULL, default is "#;".
@return: Pointer to new iniparser instance.
*/
struct MckitsIniParser* mckits_iniparser_new(const char* delimiters,
                                             const char* comment_prefixs);

/*
@brief: Parser ini from null-terminated c-string.
@param iniparser[in]: iniparser instance.
@param data[in]: null-terminated c-string.
@return: On success, 0 is returned. Else means failed.
*/
int mckits_iniparser_from_cstring(struct MckitsIniParser* iniparser,
                                  const char* data);

/*
@brief: Change ini to null-terminated c-string.
@param iniparser[in]: iniparser instance.
@return: pointer to null-terminated c-string, need free manually.
*/
char* mckits_iniparser_to_cstring(const struct MckitsIniParser* iniparser);

/*
@brief: Parser ini from file.
@param filename[in]: file content will be read.
@return: On success, 0 is returned. Else means failed.
*/
int mckits_iniparser_from_file(struct MckitsIniParser* iniparser,
                               const char* filename);

/*
@brief: Save ini to file.
@param iniparser[in]: iniparser instance.
@param filename[in]: ini will be save to filename.
@return:
  On success, 0 is returned.
  On error, -1 is returned.
*/
int mckits_iniparser_save_to_file(const struct MckitsIniParser* iniparser,
                                  const char* filename);

/*
@brief: Drop the iniparser.
@param iniparser[in]: iniparser instance.
*/
void mckits_iniparser_drop(struct MckitsIniParser* iniparser);

/*
@brief: Check if section_name exists.
@param iniparser[in]: iniparser instance.
@return:
  1: means section_name exists.
  0: means section_name not exists.
*/
int mckits_iniparser_has_section(struct MckitsIniParser* iniparser,
                                 const char* section_name);

/*
@brief: Check if entry_name exists under section_name.
@param iniparser[in]: iniparser instance.
@param section_name[in]: section name.
@param entry_name[in]: entry name.
@return:
  1: means entry_name exists under section_name.
  0: means entry_name not exists.
*/
int mckits_iniparser_has_entry(struct MckitsIniParser* iniparser,
                               const char* section_name,
                               const char* entry_name);

/*
@brief: Qeury entry_value from ini.
@param iniparser[in]: iniparser instance.
@param section_name[in]: section name.
@param entry_name[in]: entry name.
@param entry_value[out]: pass `char*` address to hold the output pointer,
  pointer will point to ini inner memory buffer, there is no need to free.
@return:
  On success, 0 is returned.
  On error, -1 means section_name or entry_name is invalid.
*/
int mckits_iniparser_get(struct MckitsIniParser* iniparser,
                         const char* section_name, const char* entry_name,
                         char** entry_value);

/*
@brief: Get entry value as int.
@param iniparser[in]: iniparser instance.
@param section_name[in]: section name.
@param entry_name[in]: entry name.
@param entry_value[out]: pass `int` address to hold the output number.
@return:
  On success, 0 is returned.
  On error, -1 means section_name or entry_name is invalid.
*/
int mckits_iniparser_get_int(struct MckitsIniParser* iniparser,
                             const char* section_name, const char* entry_name,
                             int* entry_value);

/*
@brief: Get entry value as float.
@param iniparser[in]: iniparser instance.
@param section_name[in]: section name.
@param entry_name[in]: entry name.
@param entry_value[out]: pass `float` address to hold the output number.
@return:
  On success, 0 is returned.
  On error, -1 means section_name or entry_name is invalid.
*/
int mckits_iniparser_get_float(struct MckitsIniParser* iniparser,
                               const char* section_name, const char* entry_name,
                               float* entry_value);

/*
@brief: Get entry value as boolean.
@param iniparser[in]: iniparser instance.
@param section_name[in]: section name.
@param entry_name[in]: entry name.
@param entry_value[out]: it will only be `1` or `0`.
  "0", "false", "no", "off" --> false --> `0`
  "1", "true", "yes", "on"  --> true --> `1`
@return:
  On success, 0 is returned.
  On error,
    -1 means section_name or entry_name is invalid.
    -2 mean value can't be convert to true or false.
*/
int mckits_iniparser_get_boolean(struct MckitsIniParser* iniparser,
                                 const char* section_name,
                                 const char* entry_name, int* entry_value);

/*
@brief: Add or update entry. If entry not exists, it will add new entry to ini.
  If entry already exists, it will update entry with new entry_value.
@param iniparser[in]: iniparser instance.
@param section_name[in]: section name.
@param entry_name[in]: entry name.
@param entry_value[in]: entry value.
*/
void mckits_iniparser_set(struct MckitsIniParser* iniparser,
                          const char* section_name, const char* entry_name,
                          const char* entry_value);

/*
@brief: Remove section from ini. If section_name not exists, it will do nothing.
@param iniparser[in]: iniparser instance.
@param section_name[in]: section name.
*/
void mckits_iniparser_remove_section(struct MckitsIniParser* iniparser,
                                     const char* section_name);

/*
@brief: Remove entry from ini. If section_name or entry_name not exists,
  it will do nothing.
@param iniparser[in]: iniparser instance.
@param section_name[in]: section name.
@param entry_name[in]: entry name.
*/
void mckits_iniparser_remove_entry(struct MckitsIniParser* iniparser,
                                   const char* section_name,
                                   const char* entry_name);

#ifdef __cplusplus
}
#endif

#endif  // MKITS_INCLUDE_MCKITS_CORE_ENCODING_MCKITS_ENCODING_INIPARSER_H_
