#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/wait.h>
#include <libgen.h>
#include <cups/ppd.h>
#include <cups/raster.h>

#define RCFILE      "/tmp/brparam.rc"
#define PAPERINF    "/tmp/brpaper.inf"

#define OUT_BUFFER_SIZE 10000

#ifndef O_BINARY
#define O_BINARY 0
#endif

volatile sig_atomic_t interrupted = 0;
cups_raster_t *ras;
int pages = 0;

void sigterm_handler(int sig)
{
    interrupted = 1;
}

const char *write_br_option(int fd, ppd_file_t *ppd, 
                     const char *name,
                     const char *label,
                     const char **map,
                     char *def)
{
   ppd_choice_t	key, *c;
   ppd_option_t   *option;
   char           *value = 0;

   if (label)
      write(fd, label, strlen(label));
   else
      write(fd, name, strlen(name));
   write(fd, "=", 1);

   if ((key.option = ppdFindOption(ppd, name))) {
      if ((c = (ppd_choice_t *)cupsArrayFind(ppd->marked, &key))) {
         value = c->choice;
      }
   }

   if (!value) {
      value = def;
      fprintf(stderr, "NOTICE: " PACKAGE ": Option %s not found\n", name);
   } else if (map) {
      while (*map) {
         if (0 == strcasecmp(value, *map)) {
            value = (char*)map[1];
            break;
         }
         map += 2;
      }
   }

   write(fd, value, strlen(value));
   write(fd, "\n", 1);
   return value;
}

void write_paper_inf(const char* pageSizeName, int width, int height)
{
    char    buffer[256];
    int     len, pifd;

    unlink(PAPERINF);
    pifd = open(PAPERINF, O_WRONLY | O_APPEND | O_CREAT, 0666);

    fprintf(stderr, "NOTICE: " PACKAGE ": Writing Brother PageSize Info file %s, %s:%d %d\n",
                    PAPERINF, pageSizeName, width, height);
    len = snprintf(buffer, sizeof(buffer),
                    "paper type:\twidth\theight\n%s:\t%d\t%d\n", 
                    pageSizeName, width, height);
    write(pifd, buffer, len);
    close(pifd);
}


static void
ppd_debug_marked(ppd_file_t *ppd,		/* I - PPD file data */
             const char *title)		/* I - Title for list */
{
  ppd_choice_t	*c;			/* Current choice */

  fprintf(stderr, "DEBUG: " PACKAGE ": gscupsMarkOptions: %s\n", title);

  for (c = (ppd_choice_t *)cupsArrayFirst(ppd->marked);
       c;
       c = (ppd_choice_t *)cupsArrayNext(ppd->marked))
    fprintf(stderr, "DEBUG: " PACKAGE ": gscupsMarkOptions: %s=%s\n", c->option->keyword, c->choice);
}

static const char *MapInputSlot[] = { "Auto",  "AutoSelect", 0 };

static const char *MapBRMonoColor[] = {
   "RGB",   "FullColor",
   "Gray",  "Mono", 0
};

static const char *MapPageSize[] = {
   "B5",    "JISB5",
   "B6",    "JISB6",
   "ISOB5", "B5",
   "ISOB6", "B6", 0
};

static const char *MapPrintQuality[] = {
   "Normal",   "OFF",
   "Draft",    "ON", 0
};

void write_br_config(ppd_file_t *ppd, cups_page_header2_t header,
                     cups_option_t *options, int num_options)
{
    ppd_attr_t *attr;
    char       *printer;
    int        rcfilefd;

   char     *product, buffer[256];
   int      plen;
   size_t   len;

   const char*    pageSizeName;
      
    if (!(attr = ppdFindAttr(ppd,"Product", 0))) {
        fprintf(stderr, "ERROR: " PACKAGE ": Did not find product name\n");
        return;
    }

   product = attr->value;
   if (*product == '(')
      product++;
   for (plen = 0; product[plen] && product[plen] != ')'; plen++);
   fprintf(stderr, "INFO: " PACKAGE ": Writing Brother %.*s Parameter file %s\n", plen, product, RCFILE);

   unlink(RCFILE);
   rcfilefd = open(RCFILE, O_WRONLY | O_APPEND | O_CREAT, 0666);

   len = snprintf(buffer, sizeof(buffer), "[%.*s]\n", plen, product);
   write(rcfilefd, buffer, len);

   pageSizeName = write_br_option(rcfilefd, ppd, "PageSize", 0, MapPageSize, "A4");

   write_br_option(rcfilefd, ppd, "ColorModel", "BRMonoColor", MapBRMonoColor, "Auto");
   write_br_option(rcfilefd, ppd, "InputSlot", 0, MapInputSlot, "AutoSelect");
   write_br_option(rcfilefd, ppd, "BRResolution", 0, 0, "Normal");
   write_br_option(rcfilefd, ppd, "BRReverse", 0, 0, "OFF");
   write_br_option(rcfilefd, ppd, "BRColorMatching", 0, 0, "Normal");
   write_br_option(rcfilefd, ppd, "BRGray", 0, 0, "OFF");
   write_br_option(rcfilefd, ppd, "BREnhanceBlkPrt", 0, 0, "OFF");
   write_br_option(rcfilefd, ppd, "BRImproveOutput", 0, 0, "OFF");
   write_br_option(rcfilefd, ppd, "BRSaturation", "Saturation", 0, "0");
   write_br_option(rcfilefd, ppd, "BRBrightness", "Brightness", 0, "0");
   write_br_option(rcfilefd, ppd, "BRContrast", "Contrast", 0, "0");
   write_br_option(rcfilefd, ppd, "BRRed", "RedKey", 0, "0");
   write_br_option(rcfilefd, ppd, "BRGreen", "GreenKey", 0, "0,");
   write_br_option(rcfilefd, ppd, "BRBlue", "BlueKey", 0, "0");

   write_br_option(rcfilefd, ppd, "MediaType", 0, 0, "Plan");
   write_br_option(rcfilefd, ppd, "Copies", 0, 0, "1");
   write_br_option(rcfilefd, ppd, "Collate", 0, 0, "OFF");
   write_br_option(rcfilefd, ppd, "TonerSaveMode", "TonerSaveMode", 0, "OFF");

   write_paper_inf(pageSizeName, header.cupsWidth, header.cupsHeight);

   close(rcfilefd);
}


#define PBMRAW '4'
#define PGMRAW '5'
#define PPMRAW '6'

int main(int argc, char *argv[])
{
    fprintf(stderr, "INFO: %s version %s\n", PACKAGE, VERSION);

    if (argc != 6 && argc != 7) {
        fprintf(stderr, "ERROR: " PACKAGE " job-id user title copies options [file]\n");
        fprintf(stderr, "INFO: This program is a CUPS filter. It is not intended to be run manually.\n");
        return 1;
    }

    const char *job_id          = argv[1];
    const char *job_user        = argv[2];
    const char *job_name        = argv[3];
    const int job_copies        = atoi(argv[4]);
    const char *job_filename    = argv[6];
    const char *job_charset     = getenv("CHARSET");
    int         brfilter_started = 0;
    int         pfd[2];
    int         stat_loc;
    pid_t       pid = 0;
    ppd_file_t  *ppd = NULL;
    ppd_attr_t  *attr;
    const char  *ppdfile    = getenv("PPD");
    int         num_options;
    cups_option_t *options = NULL;

    char            magic;

    ssize_t         bytes_read, bytes_written = 0;
    size_t          line_in_len = 0, line_out_len = 0;
    unsigned char   *line_in = 0, *line_out = 0, data, val;
    unsigned int    line, pos_out, pos_in, x, len;

    char            ppmheader[256];

    num_options = cupsParseOptions(argv[5], 0, &options);

    if (!ppdfile || !ppdfile[0] != '\0' || !(ppd = ppdOpenFile(ppdfile))) {
        fprintf(stderr, "ERROR: " PACKAGE ": Failed to open PPD %s (%d:%s)\n",
                ppdfile, errno, strerror(errno));
        return 1;
    }

    ppdMarkDefaults (ppd);
    ppd_debug_marked(ppd, "Before...");
    cupsMarkOptions (ppd, num_options, options);
    ppd_debug_marked(ppd, "After markoptions ...");

    signal(SIGTERM, sigterm_handler);
    signal(SIGPIPE, SIG_IGN);

    int fd = STDIN_FILENO;
    if (job_filename) {
        fd = open(job_filename, O_RDONLY | O_BINARY);
        if (fd < 0) {
            fprintf(stderr, "ERROR: " PACKAGE ": Unable to open raster file\n");
            return 1;
        }
    }

    ras = cupsRasterOpen(fd, CUPS_RASTER_READ);
    if (!ras) { 
        fprintf(stderr, "ERROR: " PACKAGE ": Cannot read raster data. Most likely an earlier filter in the pipeline failed.\n");
        return 1;
    }

    cups_page_header2_t header;
    while (!interrupted && cupsRasterReadHeader2(ras, &header)) {
        if (brfilter_started == 0) {
            brfilter_started = 1;

            write_br_config(ppd, header, options, num_options);

             pipe(pfd);
             pid = fork();

             if (pid < 0) {
                fprintf(stderr, "ERROR: " PACKAGE ": Fork failed (%d:%s)\n",
                                errno, strerror(errno));
                break;
             }

             if (0 == pid) {
                 /* Child process */
                 static const char brfilter[] = "/opt/brother/Printers/hl3040cn/brhl3040cnfilter";
                 
                 close(pfd[1]);
                 dup2(pfd[0], STDIN_FILENO);    /* Set STDIN to read end of the pipe */
                 fprintf(stderr, "NOTICE: " PACKAGE ": Launchning %s -pi %s - rc %s\n",
                           brfilter, PAPERINF, RCFILE);
                 
                 execlp(brfilter, 
                        brfilter,
                        "-pi", PAPERINF,
                        "-rc", RCFILE,
                        NULL);
                /* If we got here then execlp failed */
                fprintf(stderr, "ERROR: " PACKAGE ": failed to launch %s %d:%s\n",
                                brfilter, errno, strerror(errno));
                exit(1);

             } else
                 close(pfd[0]);
        }

        if (interrupted)
            break;

        /* Make sure line_in is big enough */
        if (line_in && line_in_len < header.cupsBytesPerLine) {
            free(line_in);
            line_in = 0;
        }

        if (!line_in) {
            line_in_len = header.cupsBytesPerLine;
            line_in = malloc(line_in_len);
        }

        fprintf(stderr, "NOTICE: " PACKAGE ": page %d, colorspace %d, %d bits, dimensions %d x %d\n",
                pages + 1,
                header.cupsColorSpace, header.cupsBitsPerColor,
                header.cupsWidth, header.cupsHeight);

        if (header.cupsBitsPerColor != 1 && header.cupsBitsPerColor != 8) {
            fprintf(stderr, "ERROR: " PACKAGE ": Unsupported bitsPerColor %d\n", header.cupsBitsPerColor);
            break;
        }

        if (header.cupsColorSpace != CUPS_CSPACE_K  &&
            header.cupsColorSpace != CUPS_CSPACE_SW &&
            header.cupsColorSpace != CUPS_CSPACE_RGB &&
            header.cupsColorSpace != CUPS_CSPACE_SRGB) {

            fprintf(stderr, "ERROR: " PACKAGE ": Unsupported colorspace %d\n", header.cupsColorSpace);
            break;
        }

        /* Produce ppmraw output */
        len = snprintf(ppmheader, sizeof(ppmheader),
                       "P6\n# Image generated by " PACKAGE "\n%d %d\n%d\n",
                       header.cupsWidth, header.cupsHeight, 255);
        bytes_written = write(pfd[1], ppmheader, len);
        if (bytes_written < 0) {
            fprintf(stderr, "ERROR: " PACKAGE ": failed to write PPMRAW header (%d:%s)\n",
                            errno, strerror(errno));
            break;
        }

        pos_out = 0;

        for (line = 0; !interrupted && line < header.cupsHeight; line++) {
            bytes_read = cupsRasterReadPixels(ras, line_in, header.cupsBytesPerLine);
            if (bytes_read <= 0) {
                fprintf(stderr, "ERROR: " PACKAGE ": failed to read raster data %ld", bytes_read);
                interrupted = 1;
                break;
            }

            if (header.cupsColorSpace == CUPS_CSPACE_RGB || header.cupsColorSpace == CUPS_CSPACE_SRGB) {
                /* For RGB 8 Bit just copy */
                bytes_written = write(pfd[1], line_in, header.cupsBytesPerLine);
                if (bytes_written < 0)
                    break;

            } else {
                /* Make sure line_out is big enough
                 * PPM >= header.cupsWidth * 3 (RGB) */
                if (line_out && line_out_len < header.cupsWidth * 3) {
                    free(line_out);
                    line_out = 0;
                }

                if (!line_out) {
                    line_out_len = header.cupsWidth * 3;
                    line_out = malloc(line_out_len);
                }

                pos_in = 0;
                data = 0;
                
                for (x = 0; x < header.cupsWidth; x++) {
                    if (header.cupsBitsPerColor == 1) {
                        if ((x & 7) == 0)
                            data = line_in[pos_in++];

                        val = data & 0x80 ? 0 : 255;

                        data <<= 1;
                    } else
                        val = line_in[pos_in++];

                    /* Output is PPMRAW (RGB) */
                    line_out[pos_out++] = val;
                    line_out[pos_out++] = val;
                    line_out[pos_out++] = val;
                }
                bytes_written = write(pfd[1], line_out, pos_out);
                if (bytes_written < 0)
                    break;

            }
        }

        if (bytes_written < 0) {
            fprintf(stderr, "ERROR: " PACKAGE ": failed to write to pipe (%d:%s)\n",
                            errno, strerror(errno));
            break;
        }

        if (interrupted)
            break;

        pages++;
    }

    if (pages == 0)
        fprintf(stderr, "ERROR: " PACKAGE ": No pages were found.\n");

    if (bytes_written < 0) {
        fprintf(stderr, "ERROR: " PACKAGE ": Could not write print data. Most likely the CUPS backend failed.\n");
        return 1;
    }

    if (pid) {
        close(pfd[1]);
        fprintf(stderr, "NOTICE: " PACKAGE ": Waiting for printer driver (%d)\n", pid);
        waitpid(pid, &stat_loc, 0);
        fprintf(stderr, "NOTICE: " PACKAGE ": Printer driver finished (%d)\n", pid);
    }

    if (line_out)
        free(line_out);

    unlink(PAPERINF);
    unlink(RCFILE);
    return 0;
}
