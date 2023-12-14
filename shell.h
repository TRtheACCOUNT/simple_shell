#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3


#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr – a linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - arguments
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @rdfd: fd read from input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; 
	int cmd_buf_type; 
	int rdfd;
	int histcount;
} data_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(data_t *);
} builtin_table;



int cnvrt_alias(data_t *, char *);
int hsh(data_t *, char **);
int find_builtin(data_t *);
void fnd_cmd(data_t *);
void frk_cmd(data_t *);

int s_cmd(data_t *, char *);
char *dp_chrs(char *, int, int);
char *fnd_pth(data_t *, char *, char *);

int loophsh(char **);

void _owneputs(char *);
int _owneputchar(char);
int _ownputfd(char, int);
int _ownputsfd(char *, int);

int _ownstrlen(char *);
int _ownstrcmp(char *, char *);
char *ownstarts_with(const char *, const char *);
char *_ownstrcat(char *, char *);

char *_ownstrcpy(char *, char *);
char *_ownstrdup(const char *);
void _ownputs(char *);
int _ownputchar(char);

char *_ownstrncpy(char *, char *, int);
char *_ownstrncat(char *, char *, int);
char *_ownstrchr(char *, char);

char **ownstrtow(char *, char *);
char **ownstrtow2(char *, char);

int st_alias(data_t *, char *);
char *_mmst(char *, char, unsigned int);
void ffr(char **);
void *_rllc(void *, unsigned int, unsigned int);

int bfr(void **);

int reciprocative(data_t *);
int delim(char, char *);
int _lph(int);
int _cnvrt(char *);

int _cnvrtnt(char *);
void puts_error(data_t *, char *);
int ownputs_d(int, int);
char *cnvrt_nmbr(long int, int, int);
void rmv_cmnts(char *);

int _theexit(data_t *);
int _oncd(data_t *);
int _ownhelp(data_t *);

int _ownhistory(data_t *);
int _ownalias(data_t *);
int puts_alias(list_t *);
int _ownalias(data_t *);

ssize_t read_buf(data_t *, char *, size_t *);
ssize_t get_input(data_t *);
ssize_t npt_buf(data_t *, char **, size_t *);
int _owngetline(data_t *, char **, size_t *);
void sigintHandler(int);

void clr_data(data_t *);
void st_data(data_t *, char **);
void fr_data(data_t *, int);

char *_gtenv(data_t *, const char *);
int _ownenv(data_t *);
int _ownstenv(data_t *);
int _ownunstenv(data_t *);
int pplt_env_list(data_t *);

char **gt_nvrn(data_t *);
int _owunsetenv(data_t *, char *);
int _stenv(data_t *, char *, char *);

char *gt_hstry_fl(data_t *);
int wrt_hstry(data_t *);
int rd_hstry(data_t *);
int bld_hstry_lst(data_t *, char *, int);
int rnmbr_hstry(data_t *);

list_t *dd_nde(list_t **, const char *, int);
list_t *dd_nd_nd(list_t **, const char *, int);
size_t prnt_lst_str(const list_t *);
int dlte_nd_ndx(list_t **, unsigned int);
void fr_lst(list_t **);

size_t lst_ln(const list_t *);
char **lst_t_strngs(list_t *);
size_t prnt_lst(const list_t *);
list_t *nd_strts_wth(list_t *, char *, char);
ssize_t gt_nd_ndx(list_t *, list_t *);

int chain(data_t *, char *, size_t *);
void check_chain(data_t *, char *, size_t *, size_t, size_t);
int replace_alias(data_t *);
int replace_vars(data_t *);
int replace_string(char **, char *);

#endif
