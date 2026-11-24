#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  openlog(NULL, 0, LOG_USER);

  if (argc != 3) {
    syslog(LOG_ERR, "Invalid number of arguments: %d (expected 2)", argc - 1);
    syslog(LOG_ERR, "Usage: %s <file_path> <string_to_write>", argv[0]);
    closelog();
    return 1;
  }

  const char *writefile = argv[1];
  const char *writestr = argv[2];
  size_t len = strlen(writestr);

  int fd = open(writefile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd == -1) {
    syslog(LOG_ERR, "Error opening file %s: %s", writefile, strerror(errno));
    closelog();
    return 1;
  }

  syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

  const char *buf = writestr;
  while (len > 0) {
    ssize_t ret = write(fd, buf, len);
    if (ret == -1) {
      if (errno == EINTR)
        continue;
      syslog(LOG_ERR, "Error writing to file %s: %s", writefile,
             strerror(errno));
      close(fd);
      closelog();
      return 1;
    }
    len -= ret;
    buf += ret;
  }

  if (close(fd) == -1) {
    syslog(LOG_ERR, "Error closing file %s: %s", writefile, strerror(errno));
    closelog();
    return 1;
  }

  closelog();
  return 0;
}
