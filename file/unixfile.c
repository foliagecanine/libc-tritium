#include <unixfile.h>

// Unix-like file functions (open/fopen, read/fread, etc.)

#define STDIO_FLAG_USED (1 << 0)
#define STDIO_FLAG_READ (1 << 1)
#define STDIO_FLAG_WRITE (1 << 2)
#define STDIO_FLAG_STDIN (1 << 5)
#define STDIO_FLAG_STDOUT (1 << 6)
#define STDIO_FLAG_STDERR (1 << 7)

typedef struct
{
    FILE *  file;
    uint8_t flags;
    off_t   ptr;
} unixfile;

FILE _stdin = {.desc = 0};

FILE _stdout = {.desc = 1};

FILE _stderr = {.desc = 2};

FILE *stdin  = &_stdin;
FILE *stdout = &_stdout;
FILE *stderr = &_stderr;

bool      _unixfile_initialized = false;
unixfile *_filedesc;

void _init_unixfile()
{
    _filedesc = calloc(FOPEN_MAX, sizeof(unixfile));
    if (!_filedesc) exit(139);
    _filedesc[0].file     = stdin;
    _filedesc[0].flags    = STDIO_FLAG_STDIN | STDIO_FLAG_READ;
    _filedesc[1].file     = stdout;
    _filedesc[1].flags    = STDIO_FLAG_STDOUT | STDIO_FLAG_WRITE;
    _filedesc[2].file     = stderr;
    _filedesc[2].flags    = STDIO_FLAG_STDERR | STDIO_FLAG_WRITE;
    _unixfile_initialized = true;
}

void _check_unixfile()
{
    if (_unixfile_initialized)
        return;
    else
        _init_unixfile();
}

int _get_avail_desc()
{
    for (int i = 1; i < FOPEN_MAX; i++)
    {
        if (!(_filedesc[i].flags & STDIO_FLAG_USED)) return i;
    }
    return -1;
}

int open(const char *path, int flags, ...)
{
    _check_unixfile();
    va_list args;
    va_start(args, flags);
    if (!path) return -1;

    FILE *fp = NULL;

    if (flags & O_CREAT && !existfile(path))
    {
        mode_t mode = va_arg(args, int);
        fp          = createfile(path);
        if (!fp->valid)
        {
            closefile(fp);
            _set_errno(EINVAL);
            return -1;
        }
    }

    if (flags & O_TRUNC)
    {
        if (!existfile(path))
        {
            if (fp) closefile(fp);
            _set_errno(ENOENT);
            return -1;
        }
        if (deletefile(path))
        {
            if (fp) closefile(fp);
            _set_errno(EINVAL);
            return -1;
        }
        fp = createfile(path);
        if (!fp->valid)
        {
            closefile(fp);
            _set_errno(EINVAL);
            return -1;
        }
    }

    int desc = _get_avail_desc();
    if (desc < 0)
    {
        if (fp) closefile(fp);
        _set_errno(EMFILE);
        return -1;
    }

    if (fp == NULL) fp = openfile(path, "a");

    fp->desc  = desc;
    fp->flags = 0;

    if (!fp->valid)
    {
        closefile(fp);
        _set_errno(ENOENT);
        return -1;
    }

    _filedesc[desc].flags = STDIO_FLAG_USED;
    _filedesc[desc].file  = fp;

    if (flags & O_APPEND)
        _filedesc[desc].ptr = fp->size;
    else
        _filedesc[desc].ptr = 0;

    if (flags & O_RDONLY) _filedesc[desc].flags |= STDIO_FLAG_READ;
    if (flags & O_WRONLY) _filedesc[desc].flags |= STDIO_FLAG_WRITE;

    va_end(args);
    return desc;
}

int close(int fd)
{
    _check_unixfile();
    if (!_filedesc[fd].flags & STDIO_FLAG_USED)
    {
        _set_errno(EBADF);
        return -1;
    }

    if (closefile(_filedesc[fd].file))
    {
        _set_errno(EIO);
        return -1;
    }

    _filedesc[fd].flags = 0;

    return 0;
}

int creat(const char *path, mode_t mode)
{
    return open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);
}

int read(int fd, void *buf, size_t count)
{
    _check_unixfile();
    if (!_filedesc[fd].flags & STDIO_FLAG_USED)
    {
        _set_errno(EBADF);
        return -1;
    }

    if (!_filedesc[fd].flags & STDIO_FLAG_READ)
    {
        _set_errno(EPERM);
        return -1;
    }

    if (fd == STDIN_FILENO) return 0; // No STDIN :(

    if (_filedesc[fd].ptr > _filedesc[fd].file->size) return 0;

    if (_filedesc[fd].file->directory)
    {
        _set_errno(EISDIR);
        return -1;
    }

    long int size_remain = (long int)(_filedesc[fd].file->size) - _filedesc[fd].ptr;
    if (size_remain < count)
    {
        if (readfile(_filedesc[fd].file, buf, _filedesc[fd].ptr, size_remain))
        {
            _set_errno(EIO);
            return -1;
        }
        _filedesc[fd].ptr += size_remain;
        return size_remain;
    }

    if (readfile(_filedesc[fd].file, buf, _filedesc[fd].ptr, count))
    {
        _set_errno(EIO);
        return -1;
    }
    _filedesc[fd].ptr += count;
    return count;
}

int write(int fd, const void *buf, size_t count)
{
    _check_unixfile();
    if (!_filedesc[fd].flags & STDIO_FLAG_USED)
    {
        _set_errno(EBADF);
        return -1;
    }

    if (!_filedesc[fd].flags & STDIO_FLAG_WRITE)
    {
        _set_errno(EPERM);
        return -1;
    }

    if (fd == STDOUT_FILENO || fd == STDERR_FILENO)
    {
        char *cbuf = (char *)buf;
        for (size_t i = 0; i < count; i++)
        {
            putchar(cbuf[i]);
        }
    }

    if (_filedesc[fd].file->directory)
    {
        _set_errno(EISDIR);
        return -1;
    }

    if (writefile(_filedesc[fd].file, (char *)buf, _filedesc[fd].ptr, count))
    {
        _set_errno(EIO);
        return -1;
    }
    _filedesc[fd].ptr += count;
    return count;
}

off_t lseek(int fd, off_t offset, int whence)
{
    _check_unixfile();
    if (!_filedesc[fd].flags & STDIO_FLAG_USED)
    {
        _set_errno(EBADF);
        return -1;
    }

    switch (whence)
    {
        case SEEK_CUR:
            if (-offset > _filedesc[fd].ptr)
            {
                _set_errno(EINVAL);
                return -1;
            }
            if (_filedesc[fd].ptr + offset < 0)
            {
                _set_errno(EOVERFLOW);
                return -1;
            }
            _filedesc[fd].ptr += offset;
            return _filedesc[fd].ptr;
        case SEEK_SET:
            if (offset < 0)
            {
                _set_errno(EINVAL);
                return -1;
            }
            _filedesc[fd].ptr = offset;
            return _filedesc[fd].ptr;
        case SEEK_END:
            if (-offset > _filedesc[fd].file->size)
            {
                _set_errno(EINVAL);
                return -1;
            }
            if (_filedesc[fd].file->size + offset < 0)
            {
                _set_errno(EOVERFLOW);
                return -1;
            }
            _filedesc[fd].ptr = _filedesc[fd].file->size + offset;
            return _filedesc[fd].ptr;
        default:
            _set_errno(EINVAL);
            return -1;
    }
}

int remove(const char *filename)
{
    uint8_t retval = deletefile(filename);
    if (retval)
    {
        _set_errno(EIO);
        return -1;
    }

    return 0;
}

void _set_fileerr(FILE *fp, int e)
{
    _set_errno(e);
    fp->flags |= _FILE_FLAGS_ERR;
}

int ferror(FILE *fp)
{
    return fp->flags & _FILE_FLAGS_ERR;
}

int feof(FILE *fp)
{
    return fp->flags & _FILE_FLAGS_EOF;
}

FILE *fopen(const char *filename, const char *mode)
{
    if (!mode || !filename)
    {
        _set_errno(EINVAL);
        return NULL;
    }

    int   flags = 0;
    char *cchr  = (char *)mode;
    if (*cchr == 'r')
    {
        flags |= O_RDONLY;
        cchr++;
    }
    else if (*cchr == 'w')
    {
        flags |= O_WRONLY | O_CREAT | O_TRUNC;
        cchr++;
    }
    else if (*cchr == 'a')
    {
        flags |= O_WRONLY | O_CREAT | O_APPEND;
    }
    else
    {
        _set_errno(EINVAL);
        return NULL;
    }

    if (*cchr == 'b')
    {
        cchr++; // We don't do anything differently
    }

    if (*cchr == '+')
    {
        flags |= O_RDWR;
    }

    int desc;
    if (flags & O_CREAT)
        desc = open(filename, flags, 0);
    else
        desc = open(filename, flags);

    if (desc < 0) return NULL;

    return _filedesc[desc].file;
}

int fclose(FILE *fp)
{
    if (!fp)
    {
        _set_errno(EBADF);
        return -1;
    }

    bool del_tmp = fp->flags & _FILE_FLAGS_TMP;

    if (close(fp->desc) < 0) return -1;

    if (del_tmp) remove("TEMPFILE.TMP");

    return 0;
}

int fflush(FILE *fp)
{
    return 0; // We don't support buffering
}

FILE *freopen(const char *filename, const char *mode, FILE *fp)
{
    fclose(fp);
    return fopen(filename, mode);
}

long int ftell(FILE *fp)
{
    return _filedesc[fp->desc].ptr;
}

int fseek(FILE *fp, off_t offset, int whence)
{
    lseek(fp->desc, offset, whence);
}

void rewind(FILE *fp)
{
    fseek(fp, 0, SEEK_SET);
    fp->flags &= ~(fp->flags & _FILE_FLAGS_ERR);
}

int fputc(int c, FILE *fp)
{
    if (!fp)
    {
        _set_errno(EBADF);
        return -1;
    }

    if (c < 0) return -1;

    if (write(fp->desc, &c, 1) < 1)
    {
        fp->flags |= _FILE_FLAGS_ERR; // Write can't return anything other than count or error
        return -1;
    }

    return c;
}

int fputs(const char *s, FILE *fp)
{
    if (!fp)
    {
        _set_errno(EBADF);
        return -1;
    }

    if (write(fp->desc, s, strlen(s)) < strlen(s))
    {
        fp->flags |= _FILE_FLAGS_ERR;
        return -1;
    }

    return 0;
}

int fgetc(FILE *fp)
{
    if (!fp)
    {
        _set_errno(EBADF);
        return -1;
    }

    int c;
    int retval = read(fp->desc, &c, 1);
    if (retval < 1)
    {
        if (retval == -1)
        {
            fp->flags |= _FILE_FLAGS_ERR;
        }
        else
        {
            fp->flags |= _FILE_FLAGS_EOF;
        }
        return -1;
    }

    return c;
}

char *fgets(char *buf, int n, FILE *fp)
{
    if (!fp)
    {
        _set_errno(EBADF);
        return NULL;
    }

    int i;
    for (i = 0; i < n - 1; i++)
    {
        int c = fgetc(fp);
        if (c < 0) return NULL; // Indicators already set by fgetc
        buf[i] = (char)c;
        if (c == 0 || c == '\n') break;
    }

    buf[i] = 0;

    return buf;
}

int ungetc(int c, FILE *fp)
{
    if (!fp)
    {
        _set_errno(EBADF);
        return -1;
    }

    if (!_filedesc[fp->desc].ptr)
    {
        _set_fileerr(fp, EINVAL);
        return -1;
    }

    _filedesc[fp->desc].ptr--;

    if (fputc(c, fp) < 0) return -1;

    _filedesc[fp->desc].ptr--;

    return c;
}

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *fp)
{
    size_t amt_read = 0;

    if (!fp)
    {
        _set_errno(EBADF);
        return amt_read;
    }

    if (!(size) || !(nmemb)) return 0;

    int retval = read(fp->desc, ptr, size * nmemb);

    if (retval < 0)
    {
        fp->flags |= _FILE_FLAGS_ERR;
        return amt_read;
    }

    if (retval < size * nmemb) fp->flags |= _FILE_FLAGS_EOF;

    amt_read += retval;

    return amt_read;
}

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *fp)
{
    size_t amt_written = 0;

    if (!fp)
    {
        _set_errno(EBADF);
        return amt_written;
    }

    if (!(size) || !(nmemb)) return 0;

    int retval = write(fp->desc, ptr, size * nmemb);

    if (retval < 0)
    {
        fp->flags |= _FILE_FLAGS_ERR;
        return amt_written;
    }

    amt_written += retval;

    return amt_written;
}

FILE *_current_fp;
bool  _write_current_fp(const char *s, size_t n)
{
    if (fwrite(s, 1, n, _current_fp) < n) return false;
    return true;
}

int vfprintf(FILE *fp, const char *format, va_list parameters)
{
    _current_fp = fp;
    return __print_formatted(_write_current_fp, format, parameters);
}

int fprintf(FILE *fp, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int retval = vfprintf(fp, format, args);
    va_end(args);
    return retval;
}

int fileno(FILE *fp)
{
    return fp->desc;
}

int setvbuf(FILE *fp, char *buf, int mode, size_t size)
{
    (void)fp;
    (void)buf;
    (void)mode;
    (void)size;
    return 0; // We don't have buffering
}

FILE *tmpfile()
{
    FILE *fp = fopen("TEMPFILE.TMP", "w+");
    fp->flags |= _FILE_FLAGS_TMP;
    return fp;
}