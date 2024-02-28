#include "mckits/core/encoding/mckits_encoding_iniparser.h"

#include <stdlib.h>

#include "mckits/core/mckits_mfile.h"
#include "mckits/mlibc/mckits_malloc.h"
#include "mckits/mstl/mckits_list.h"
#include "mckits/mstl/mckits_strconv.h"
#include "mckits/mstl/mckits_string.h"

// name = value
struct MckitsIniParserEntry {
  struct MckitsString name;
  struct MckitsString value;
};

// [section_name]
// entry_name1 = entry_value1
// entry_name2 = entry_value2
struct MckitsIniParserSection {
  struct MckitsString name;
  struct MckitsList* entries;  // MckitsIniParserEntry[], store entry array
};

struct MckitsIniParser {
  struct MckitsList* sections;  // MckitsIniParserSection[], store section array
  struct MckitsString delimiters;       // '=', ':'
  struct MckitsString comment_prefixs;  // '#', ';'
};

/*
@brief: Create a new entry with name and value.
@param name[in]: New entry name.
@param value[in]: New entry value.
@return: Pointer to new entry instance.
*/
static struct MckitsIniParserEntry* iniparser_entry_new(const char* name,
                                                        const char* value) {
  struct MckitsIniParserEntry* entry =
      (struct MckitsIniParserEntry*)mckits_malloc(
          sizeof(struct MckitsIniParserEntry));
  mckits_string_init(&entry->name, name);
  mckits_string_init(&entry->value, value);
  return entry;
}

/*
@brief: Drop the entry.
*/
static void iniparser_entry_drop(struct MckitsIniParserEntry* entry) {
  mckits_string_drop_data(&entry->name);
  mckits_string_drop_data(&entry->value);
  mckits_free(entry);
}

/*
@brief: Create a new section with name.
@param name[in]: New section name.
@return: Pointer to new section instance.
*/
static struct MckitsIniParserSection* iniparser_section_new(const char* name) {
  struct MckitsIniParserSection* section =
      (struct MckitsIniParserSection*)mckits_malloc(
          sizeof(struct MckitsIniParserSection));
  mckits_string_init(&section->name, name);
  section->entries = mckits_list_new();
  return section;
}

/*
@brief: List free node callback used in section drop.
@param entry[in]: Entry will be drop.
*/
static void iniparser_section_free_entry_callback(void* entry) {
  iniparser_entry_drop((struct MckitsIniParserEntry*)entry);
}

/*
@brief: Drop the section.
*/
static void iniparser_section_drop(struct MckitsIniParserSection* section) {
  mckits_string_drop_data(&section->name);
  mckits_list_drop(section->entries, iniparser_section_free_entry_callback);
  mckits_free(section);
}

/*
@brief: Add entry to section.
*/
static void iniparser_section_add_entry(struct MckitsIniParserSection* section,
                                        struct MckitsIniParserEntry* entry) {
  mckits_list_push_back(section->entries, entry);
}

/*
@brief: Find entry_name in section.
@return:
  If found, return pointer to entry node.
  Else, return NULL.
*/
static struct MckitsListNode* iniparser_section_find_entry_node(
    struct MckitsIniParserSection* section, const char* entry_name) {
  struct MckitsListNode* node = mckits_list_front(section->entries);
  while (node != NULL) {
    struct MckitsIniParserEntry* entry =
        (struct MckitsIniParserEntry*)node->value;
    if (mckits_strcmp(entry->name.data, entry_name) == 0) {
      return node;
    }
    node = mckits_list_node_next(node);
  }
  return NULL;
}

/*
@brief: Find entry_name in section.
@return:
  If found, return pointer to entry.
  Else, return NULL.
*/
static struct MckitsIniParserEntry* iniparser_section_find_entry(
    struct MckitsIniParserSection* section, const char* entry_name) {
  struct MckitsListNode* node = mckits_list_front(section->entries);
  while (node != NULL) {
    struct MckitsIniParserEntry* entry =
        (struct MckitsIniParserEntry*)node->value;
    if (mckits_strcmp(entry->name.data, entry_name) == 0) {
      return entry;
    }
    node = mckits_list_node_next(node);
  }
  return NULL;
}

/*
@brief: Find section_name in iniparser.
@return:
  If found, return pointer to section list node.
  Else, return NULL.
*/
static struct MckitsListNode* iniparser_find_section_node(
    struct MckitsIniParser* iniparser, const char* section_name) {
  struct MckitsListNode* node = mckits_list_front(iniparser->sections);
  while (node != NULL) {
    struct MckitsIniParserSection* section =
        (struct MckitsIniParserSection*)node->value;
    if (mckits_strcmp(section->name.data, section_name) == 0) {
      return node;
    }
    node = mckits_list_node_next(node);
  }
  return NULL;
}

/*
@brief: Find section_name in iniparser.
@return:
  If found, return pointer to section.
  Else, return NULL.
*/
static struct MckitsIniParserSection* iniparser_find_section(
    struct MckitsIniParser* iniparser, const char* section_name) {
  struct MckitsListNode* node = mckits_list_front(iniparser->sections);
  while (node != NULL) {
    struct MckitsIniParserSection* section =
        (struct MckitsIniParserSection*)node->value;
    if (mckits_strcmp(section->name.data, section_name) == 0) {
      return section;
    }
    node = mckits_list_node_next(node);
  }
  return NULL;
}

/*
@brief: Append new empty section to iniparser tail.
@return: Pointer to new section.
*/
static struct MckitsIniParserSection* iniparser_add_new_section(
    struct MckitsIniParser* iniparser, const char* section_name) {
  struct MckitsIniParserSection* section = iniparser_section_new(section_name);
  mckits_list_push_back(iniparser->sections, section);
  return section;
}

/*
@brief: Find section_name in iniparser. If not found, add new section to
  iniparser tail.
@return: Pointer to section.
*/
static struct MckitsIniParserSection* iniparser_find_add_section(
    struct MckitsIniParser* iniparser, const char* section_name) {
  struct MckitsIniParserSection* section =
      iniparser_find_section(iniparser, section_name);
  if (section == NULL) {
    section = iniparser_add_new_section(iniparser, section_name);
  }
  return section;
}

struct MckitsIniParser* mckits_iniparser_new(const char* delimiters,
                                             const char* comment_prefixs) {
  struct MckitsIniParser* iniparser =
      (struct MckitsIniParser*)mckits_malloc(sizeof(struct MckitsIniParser));

  iniparser->sections = mckits_list_new();

  if (delimiters == NULL || strlen(delimiters) <= 0) {
    mckits_string_init(&iniparser->delimiters,
                       MCKITS_INIPARSER_DEFAULT_DELIMITERS);
  } else {
    mckits_string_init(&iniparser->delimiters, delimiters);
  }

  if (comment_prefixs == NULL || strlen(comment_prefixs) <= 0) {
    mckits_string_init(&iniparser->comment_prefixs,
                       MCKITS_INIPARSER_DEFAULT_COMMENT_PREFIXS);
  } else {
    mckits_string_init(&iniparser->comment_prefixs, comment_prefixs);
  }

  return iniparser;
}

int mckits_iniparser_from_cstring(struct MckitsIniParser* iniparser,
                                  const char* data) {
  size_t data_len = strlen(data);

  struct MckitsString line;
  mckits_string_init(&line, NULL);

  struct MckitsIniParserSection* section = NULL;

  for (size_t idx = 0; idx <= data_len; ++idx) {
    char c = data[idx];

    if (c == '\n' || c == '\0' || idx == data_len) {
      // one line finish, process one line

      mckits_string_trim(&line, " \r\n\t");

      if (line.len == 0) {
        // empty line, do nothing
        continue;
      }

      if (line.data[0] == '[') {
        // [section_name], process section line

        mckits_string_trim(&line, "[] \t");
        if (line.len == 0) {
          // empty section name, invalid
          mckits_string_drop_data(&line);
          return -1;
        }

        section = iniparser_add_new_section(iniparser, (const char*)line.data);
        mckits_string_clear(&line);
        continue;
      }

      // process comments
      for (int i = 0; i < iniparser->comment_prefixs.len; ++i) {
        if (line.data[i] == iniparser->comment_prefixs.data[i]) {
          // comment line, do nothing
          mckits_string_clear(&line);
          continue;
        }
      }

      // process entry line
      int found_delimiter = 0;
      for (int i = 0; i < iniparser->delimiters.len; ++i) {
        char* delimiter =
            mckits_strchr(line.data, iniparser->delimiters.data[i]);
        if (delimiter != NULL) {
          // found entry delimiter
          size_t entry_name_len = (uint8_t*)delimiter - line.data;
          size_t entry_value_len = line.len - entry_name_len - 1;

          struct MckitsString entry_name;
          struct MckitsString entry_value;
          mckits_string_init_from_bytes(&entry_name, line.data, entry_name_len);
          mckits_string_init_from_bytes(
              &entry_value, (const uint8_t*)(delimiter + 1), entry_value_len);
          mckits_string_trim(&entry_name, " \t");
          mckits_string_trim(&entry_value, " \t");

          struct MckitsIniParserEntry* entry = iniparser_entry_new(
              (const char*)entry_name.data, (const char*)entry_value.data);

          if (section == NULL) {
            section = iniparser_add_new_section(
                iniparser, MCKITS_INIPARSER_DEFAULT_SECTION);
          }
          iniparser_section_add_entry(section, entry);

          mckits_string_drop_data(&entry_name);
          mckits_string_drop_data(&entry_value);
          mckits_string_clear(&line);
          found_delimiter = 1;
          break;
        }
      }

      if (found_delimiter) {
        continue;
      }

      // entry not found delimiter, invalid
      mckits_string_drop_data(&line);
      return -2;

    } else {
      // append c to line
      mckits_string_push_char(&line, c);
    }
  }

  mckits_string_drop_data(&line);
  return 0;
}

char* mckits_iniparser_to_cstring(const struct MckitsIniParser* iniparser) {
  struct MckitsString result;
  mckits_string_init(&result, NULL);

  int first_section = 1;

  // process sections
  struct MckitsListNode* section_node = mckits_list_front(iniparser->sections);
  while (section_node != NULL) {
    struct MckitsIniParserSection* section =
        (struct MckitsIniParserSection*)section_node->value;

    if (first_section) {
      first_section = 0;
    } else {
      mckits_string_push_char(&result, '\n');
    }

    mckits_string_push_char(&result, '[');
    mckits_string_push_cstring(&result, (const char*)section->name.data);
    mckits_string_push_char(&result, ']');
    mckits_string_push_char(&result, '\n');

    // process entryies
    struct MckitsListNode* entry_node = mckits_list_front(section->entries);
    while (entry_node != NULL) {
      struct MckitsIniParserEntry* entry =
          (struct MckitsIniParserEntry*)entry_node->value;
      mckits_string_push_mstring(&result, &entry->name);
      mckits_string_push_char(&result, (char)iniparser->delimiters.data[0]);
      mckits_string_push_mstring(&result, &entry->value);
      mckits_string_push_char(&result, '\n');
      entry_node = mckits_list_node_next(entry_node);
    }

    section_node = mckits_list_node_next(section_node);
  }

  return mckits_string_take(&result);
}

int mckits_iniparser_from_file(struct MckitsIniParser* iniparser,
                               const char* filename) {
  char* data = NULL;
  ssize_t bytes_readed = mckits_read_whole_file_cstring(filename, &data);
  if (bytes_readed < 0) {
    return -1;
  }

  int ret = mckits_iniparser_from_cstring(iniparser, data);
  mckits_free(data);
  return ret;
}

int mckits_iniparser_save_to_file(const struct MckitsIniParser* iniparser,
                                  const char* filename) {
  char* data = mckits_iniparser_to_cstring(iniparser);
  size_t data_len = strlen(data);
  int ret = (int)mckits_write_to_file(filename, data, data_len);
  free(data);
  return ret;
}

static void iniparser_free_section_callback(void* section) {
  iniparser_section_drop((struct MckitsIniParserSection*)section);
}

void mckits_iniparser_drop(struct MckitsIniParser* iniparser) {
  mckits_list_drop(iniparser->sections, iniparser_free_section_callback);
  mckits_string_drop_data(&iniparser->delimiters);
  mckits_string_drop_data(&iniparser->comment_prefixs);
  mckits_free(iniparser);
}

int mckits_iniparser_has_section(struct MckitsIniParser* iniparser,
                                 const char* section_name) {
  return iniparser_find_section(iniparser, section_name) == NULL ? 0 : 1;
}

int mckits_iniparser_has_entry(struct MckitsIniParser* iniparser,
                               const char* section_name,
                               const char* entry_name) {
  struct MckitsIniParserSection* section =
      iniparser_find_section(iniparser, section_name);
  if (section == NULL) {
    return 0;
  }

  struct MckitsIniParserEntry* entry =
      iniparser_section_find_entry(section, entry_name);
  if (entry == NULL) {
    return 0;
  }

  return 1;
}

int mckits_iniparser_get(struct MckitsIniParser* iniparser,
                         const char* section_name, const char* entry_name,
                         char** entry_value) {
  struct MckitsIniParserSection* section =
      iniparser_find_section(iniparser, section_name);
  if (section == NULL) {
    return -1;
  }

  struct MckitsIniParserEntry* entry =
      iniparser_section_find_entry(section, entry_name);
  if (entry == NULL) {
    return -1;
  }

  *entry_value = (char*)entry->value.data;

  return 0;
}

int mckits_iniparser_get_int(struct MckitsIniParser* iniparser,
                             const char* section_name, const char* entry_name,
                             int* entry_value) {
  struct MckitsIniParserSection* section =
      iniparser_find_section(iniparser, section_name);
  if (section == NULL) {
    return -1;
  }

  struct MckitsIniParserEntry* entry =
      iniparser_section_find_entry(section, entry_name);
  if (entry == NULL) {
    return -1;
  }

  *entry_value = mckits_char_string_to_int((const char*)entry->value.data);

  return 0;
}

int mckits_iniparser_get_float(struct MckitsIniParser* iniparser,
                               const char* section_name, const char* entry_name,
                               float* entry_value) {
  struct MckitsIniParserSection* section =
      iniparser_find_section(iniparser, section_name);
  if (section == NULL) {
    return -1;
  }

  struct MckitsIniParserEntry* entry =
      iniparser_section_find_entry(section, entry_name);
  if (entry == NULL) {
    return -1;
  }

  *entry_value = mckits_char_string_to_float((const char*)entry->value.data);

  return 0;
}

int mckits_iniparser_get_boolean(struct MckitsIniParser* iniparser,
                                 const char* section_name,
                                 const char* entry_name, int* entry_value) {
  struct MckitsIniParserSection* section =
      iniparser_find_section(iniparser, section_name);
  if (section == NULL) {
    return -1;
  }

  struct MckitsIniParserEntry* entry =
      iniparser_section_find_entry(section, entry_name);
  if (entry == NULL) {
    return -1;
  }

  char* value = (char*)entry->value.data;

  if (mckits_strcmp(value, "0") == 0 || mckits_strcmp(value, "false") == 0 ||
      mckits_strcmp(value, "no") == 0 || mckits_strcmp(value, "off") == 0) {
    *entry_value = 0;
    return 0;
  }

  if (mckits_strcmp(value, "1") == 0 || mckits_strcmp(value, "true") == 0 ||
      mckits_strcmp(value, "yes") == 0 || mckits_strcmp(value, "on") == 0) {
    *entry_value = 1;
    return 0;
  }

  return -2;
}

void mckits_iniparser_set(struct MckitsIniParser* iniparser,
                          const char* section_name, const char* entry_name,
                          const char* entry_value) {
  // find section, if not found, add new section
  struct MckitsIniParserSection* section =
      iniparser_find_add_section(iniparser, section_name);

  // find entry
  struct MckitsIniParserEntry* entry =
      iniparser_section_find_entry(section, entry_name);

  if (entry == NULL) {
    // not found entry
    struct MckitsIniParserEntry* new_entry =
        iniparser_entry_new(entry_name, entry_value);
    iniparser_section_add_entry(section, new_entry);
    return;
  }

  // found entry, update entry value
  mckits_string_drop_data(&entry->value);
  mckits_string_init(&entry->value, entry_value);
}

void mckits_iniparser_remove_section(struct MckitsIniParser* iniparser,
                                     const char* section_name) {
  struct MckitsListNode* section_node =
      iniparser_find_section_node(iniparser, section_name);
  if (section_node == NULL) {
    // not found section
    return;
  }

  // remove section from list
  struct MckitsIniParserSection* section =
      (struct MckitsIniParserSection*)mckits_list_remove(iniparser->sections,
                                                         section_node);

  // free section
  iniparser_section_drop(section);
  // free section node
  mckits_list_node_drop(section_node);
}

void mckits_iniparser_remove_entry(struct MckitsIniParser* iniparser,
                                   const char* section_name,
                                   const char* entry_name) {
  struct MckitsIniParserSection* section =
      iniparser_find_section(iniparser, section_name);
  if (section == NULL) {
    // not found section
    return;
  }

  struct MckitsListNode* entry_node =
      iniparser_section_find_entry_node(section, entry_name);
  if (entry_node == NULL) {
    // not found entry
    return;
  }

  // remove entry from section
  struct MckitsIniParserEntry* entry =
      (struct MckitsIniParserEntry*)mckits_list_remove(section->entries,
                                                       entry_node);

  // free entry
  iniparser_entry_drop(entry);
  // free entry node
  mckits_list_node_drop(entry_node);
}
