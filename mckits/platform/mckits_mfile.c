#include "mckits_mfile.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "mckits_mlog.h"
#include "mckits_mstl_utils.h"

int mckits_is_file_exists(const char* pathname) {
  return access(pathname, F_OK) == 0 ? 1 : 0;
}

int mckits_is_dir_exists(const char* pathname) {
  DIR* dir = opendir(pathname);
  if (dir != NULL) {
    closedir(dir);
    return 1;
  } else {
    return 0;
  }
}

ssize_t mckits_file_size(const char* pathname) {
  struct stat st;
  return stat(pathname, &st) == 0 ? st.st_size : -1;
}

void mckits_remove_file(const char* pathname) { remove(pathname); }

void mckits_remove_dir(const char* pathname) {
  DIR* dir = opendir(pathname);
  if (!dir) {
    errlog("Failed to open directory: %s\n", pathname);
    return;
  }

  struct dirent* entry = NULL;
  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    char path[1024] = {0};
    snprintf(path, sizeof(path), "%s/%s", pathname, entry->d_name);
    struct stat statbuf;
    if (stat(path, &statbuf) == -1) {
      errlog("Failed to get file status: %s\n", path);
      continue;
    }

    if (S_ISDIR(statbuf.st_mode)) {
      mckits_remove_dir(path);
    } else {
      mckits_remove_file(path);
    }
  }

  closedir(dir);

  if (rmdir(pathname) != 0) {
    errlog("Failed to remove directory: %s\n", pathname);
  }
}

void mckits_mkdir_all(const char* pathname) {
  char* path = strdup(pathname);
  char* p = path;
  while (*p) {
    if (*p == '/' && (p > path)) {
      *p = '\0';
      if (mckits_is_dir_exists(path) == 0 && mkdir(path, 0777) != 0) {
        errlog("Failed to create directory: %s\n", path);
        free(path);
        return;
      }
      *p = '/';
    }
    p++;
  }
  if (mckits_is_dir_exists(path) == 0 && mkdir(path, 0777) != 0) {
    errlog("Failed to create directory: %s\n", path);
  }
  free(path);
}

ssize_t mckits_path_dir(const char* pathname, char* dirpath, size_t count) {
  if (dirpath == NULL || count < 2) {
    return -1;
  }

  const char* last_separator = strrchr(pathname, '/');

  if (last_separator == NULL) {
    dirpath[0] = '.';
    dirpath[1] = '\0';
    return 1;
  }

  size_t length = last_separator - pathname;
  if (count <= length) {
    return -1;
  }

  memcpy(dirpath, pathname, length);
  dirpath[length] = '\0';

  return length;
}

ssize_t mckits_path_base(const char* pathname, char* basename, size_t count) {
  if (basename == NULL || count < 2) {
    return -1;
  }

  size_t pathname_size = strlen(pathname);
  if (pathname == NULL || pathname_size == 0) {
    basename[0] = '.';
    basename[1] = '\0';
    return 1;
  }

  const char* last_separator = strrchr(pathname, '/');
  if (last_separator == NULL) {
    if (count <= pathname_size) {
      return -1;
    }

    memcpy(basename, pathname, pathname_size);
    basename[pathname_size] = '\0';
    return pathname_size;
  }

  const char* last_element = last_separator + 1;
  size_t last_element_size = strlen(last_element);
  if (last_element_size == 0) {
    basename[0] = '.';
    basename[1] = '\0';
    return 1;
  }
  if (count <= last_element_size) {
    return -1;
  }

  memcpy(basename, last_element, last_element_size);
  basename[last_element_size] = '\0';
  return last_element_size;
}

ssize_t mckits_read_whole_file(const char* pathname, void* buf, size_t count) {
  FILE* file = fopen(pathname, "rb");
  if (file == NULL) {
    return -1;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  if (file_size < 0) {
    fclose(file);
    return -2;
  }

  if (file_size > count) {
    fclose(file);
    return -3;
  }

  size_t read_size = fread(buf, 1, file_size, file);
  fclose(file);

  if (read_size != file_size) {
    return -4;
  }

  return read_size;
}

ssize_t mckits_write_to_file(const char* pathname, const void* buf,
                             size_t count) {
  char dirpath[1024] = {0};
  mckits_path_dir(pathname, dirpath, sizeof(dirpath));
  mckits_mkdir_all(dirpath);

  FILE* file = fopen(pathname, "w");
  if (file == NULL) {
    return -1;
  }
  size_t bytes_written = fwrite(buf, 1, count, file);
  fclose(file);
  return bytes_written;
}
